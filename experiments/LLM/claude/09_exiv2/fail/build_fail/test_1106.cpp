#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <cstdio>
#include <vector>
#include <cstring>

namespace {

// Helper to create a temporary file with given content
class TempFile {
public:
    explicit TempFile(const std::string& name, const std::vector<unsigned char>& content = {})
        : filename_(name) {
        std::ofstream ofs(filename_, std::ios::binary);
        if (!content.empty()) {
            ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
        }
        ofs.close();
    }
    ~TempFile() {
        std::remove(filename_.c_str());
    }
    const std::string& path() const { return filename_; }
private:
    std::string filename_;
};

// Minimal JPEG content (SOI + EOI markers)
std::vector<unsigned char> minimalJpeg() {
    return {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
            'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
            0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
            0xFF, 0xD9};
}

// Minimal PNG header
std::vector<unsigned char> minimalPng() {
    return {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
            // IHDR chunk
            0x00, 0x00, 0x00, 0x0D, // length
            0x49, 0x48, 0x44, 0x52, // IHDR
            0x00, 0x00, 0x00, 0x01, // width
            0x00, 0x00, 0x00, 0x01, // height
            0x08, 0x02,             // bit depth, color type
            0x00, 0x00, 0x00,       // compression, filter, interlace
            0x90, 0x77, 0x53, 0xDE, // CRC
            // IEND chunk
            0x00, 0x00, 0x00, 0x00,
            0x49, 0x45, 0x4E, 0x44,
            0xAE, 0x42, 0x60, 0x82};
}

} // anonymous namespace

// Test opening a non-existent file throws an exception
TEST(ImageFactoryTest_1106, OpenNonExistentFileThrows_1106) {
    EXPECT_THROW(
        Exiv2::ImageFactory::open("this_file_does_not_exist_at_all.jpg", false),
        Exiv2::Error
    );
}

// Test opening a file with unknown/garbage content throws kerFileContainsUnknownImageType
TEST(ImageFactoryTest_1106, OpenGarbageFileThrowsUnknownImageType_1106) {
    std::vector<unsigned char> garbage = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    TempFile tmp("test_garbage_1106.bin", garbage);
    
    try {
        auto image = Exiv2::ImageFactory::open(tmp.path(), false);
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        // Should be kerFileContainsUnknownImageType
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFileContainsUnknownImageType);
    }
}

// Test opening a valid JPEG file succeeds
TEST(ImageFactoryTest_1106, OpenValidJpegSucceeds_1106) {
    TempFile tmp("test_valid_1106.jpg", minimalJpeg());
    
    EXPECT_NO_THROW({
        auto image = Exiv2::ImageFactory::open(tmp.path(), false);
        EXPECT_NE(image, nullptr);
    });
}

// Test opening an empty file throws
TEST(ImageFactoryTest_1106, OpenEmptyFileThrows_1106) {
    TempFile tmp("test_empty_1106.bin", {});
    
    EXPECT_THROW(
        Exiv2::ImageFactory::open(tmp.path(), false),
        Exiv2::Error
    );
}

// Test open from memory with valid JPEG data
TEST(ImageFactoryTest_1106, OpenFromMemoryValidJpeg_1106) {
    auto data = minimalJpeg();
    
    EXPECT_NO_THROW({
        auto image = Exiv2::ImageFactory::open(data.data(), data.size());
        EXPECT_NE(image, nullptr);
    });
}

// Test open from memory with garbage data throws
TEST(ImageFactoryTest_1106, OpenFromMemoryGarbageThrows_1106) {
    std::vector<Exiv2::byte> garbage = {0x00, 0x01, 0x02, 0x03};
    
    try {
        auto image = Exiv2::ImageFactory::open(garbage.data(), garbage.size());
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerMemoryContainsUnknownImageType);
    }
}

// Test open from memory with zero size
TEST(ImageFactoryTest_1106, OpenFromMemoryZeroSizeThrows_1106) {
    Exiv2::byte dummy = 0;
    EXPECT_THROW(
        Exiv2::ImageFactory::open(&dummy, 0),
        Exiv2::Error
    );
}

// Test open from memory with nullptr
TEST(ImageFactoryTest_1106, OpenFromMemoryNullptrThrows_1106) {
    EXPECT_THROW(
        Exiv2::ImageFactory::open(static_cast<const Exiv2::byte*>(nullptr), 0),
        Exiv2::Error
    );
}

// Test getType with valid JPEG file
TEST(ImageFactoryTest_1106, GetTypeValidJpegFile_1106) {
    TempFile tmp("test_type_jpeg_1106.jpg", minimalJpeg());
    
    EXPECT_NO_THROW({
        auto type = Exiv2::ImageFactory::getType(tmp.path());
        EXPECT_NE(type, Exiv2::ImageType::none);
    });
}

// Test getType with non-existent file
TEST(ImageFactoryTest_1106, GetTypeNonExistentFileThrows_1106) {
    EXPECT_THROW(
        Exiv2::ImageFactory::getType("nonexistent_file_1106.jpg"),
        Exiv2::Error
    );
}

// Test getType from memory with valid JPEG data
TEST(ImageFactoryTest_1106, GetTypeFromMemoryValidJpeg_1106) {
    auto data = minimalJpeg();
    auto type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_NE(type, Exiv2::ImageType::none);
}

// Test getType from memory with garbage data returns none
TEST(ImageFactoryTest_1106, GetTypeFromMemoryGarbageReturnsNone_1106) {
    std::vector<Exiv2::byte> garbage = {0x00, 0x01, 0x02, 0x03};
    auto type = Exiv2::ImageFactory::getType(garbage.data(), garbage.size());
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test create with a file path for JPEG type
TEST(ImageFactoryTest_1106, CreateJpegImageToFile_1106) {
    std::string path = "test_create_1106.jpg";
    EXPECT_NO_THROW({
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, path);
        EXPECT_NE(image, nullptr);
    });
    std::remove(path.c_str());
}

// Test create with unsupported/none type throws
TEST(ImageFactoryTest_1106, CreateNoneTypeThrows_1106) {
    EXPECT_THROW(
        Exiv2::ImageFactory::create(Exiv2::ImageType::none, "test_none_1106.bin"),
        Exiv2::Error
    );
}

// Test create without file (memory-based)
TEST(ImageFactoryTest_1106, CreateJpegInMemory_1106) {
    EXPECT_NO_THROW({
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg);
        EXPECT_NE(image, nullptr);
    });
}

// Test createIo with a valid path
TEST(ImageFactoryTest_1106, CreateIoValidPath_1106) {
    TempFile tmp("test_createio_1106.jpg", minimalJpeg());
    
    EXPECT_NO_THROW({
        auto io = Exiv2::ImageFactory::createIo(tmp.path(), false);
        EXPECT_NE(io, nullptr);
    });
}

// Test open with a path and useCurl=false for non-existent path
TEST(ImageFactoryTest_1106, OpenWithCurlFalseNonExistent_1106) {
    EXPECT_THROW(
        Exiv2::ImageFactory::open("absolutely_nonexistent_path_1106.xyz", false),
        Exiv2::Error
    );
}

// Test that opening a valid JPEG returns an image that can be read
TEST(ImageFactoryTest_1106, OpenValidJpegCanReadMetadata_1106) {
    TempFile tmp("test_read_meta_1106.jpg", minimalJpeg());
    
    auto image = Exiv2::ImageFactory::open(tmp.path(), false);
    ASSERT_NE(image, nullptr);
    
    EXPECT_NO_THROW({
        image->readMetadata();
    });
}

// Test checkMode for JPEG and various metadata types
TEST(ImageFactoryTest_1106, CheckModeJpegExif_1106) {
    auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdExif);
    // JPEG supports Exif, so it should be read-write or at least read
    EXPECT_NE(mode, Exiv2::AccessMode::amNone);
}

TEST(ImageFactoryTest_1106, CheckModeNoneType_1106) {
    auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::none, Exiv2::MetadataId::mdExif);
    EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

// Test opening a file with only 1 byte (boundary)
TEST(ImageFactoryTest_1106, OpenSingleByteFileThrows_1106) {
    TempFile tmp("test_1byte_1106.bin", {0xFF});
    
    EXPECT_THROW(
        Exiv2::ImageFactory::open(tmp.path(), false),
        Exiv2::Error
    );
}

// Test opening a file with just JPEG SOI marker but nothing else
TEST(ImageFactoryTest_1106, OpenIncompleteJpeg_1106) {
    TempFile tmp("test_incomplete_jpeg_1106.jpg", {0xFF, 0xD8});
    
    // This may or may not succeed depending on implementation
    // but should not crash
    try {
        auto image = Exiv2::ImageFactory::open(tmp.path(), false);
        // If it opens, it should be non-null
        EXPECT_NE(image, nullptr);
    } catch (const Exiv2::Error&) {
        // Acceptable to throw
    }
}

// Test getType from memory with minimal PNG
TEST(ImageFactoryTest_1106, GetTypeFromMemoryPng_1106) {
    auto data = minimalPng();
    auto type = Exiv2::ImageFactory::getType(data.data(), data.size());
    EXPECT_NE(type, Exiv2::ImageType::none);
}

// Test open from BasicIo unique_ptr with valid data
TEST(ImageFactoryTest_1106, OpenFromBasicIoPtr_1106) {
    TempFile tmp("test_basicio_1106.jpg", minimalJpeg());
    
    auto io = Exiv2::ImageFactory::createIo(tmp.path(), false);
    ASSERT_NE(io, nullptr);
    
    EXPECT_NO_THROW({
        auto image = Exiv2::ImageFactory::open(std::move(io));
        EXPECT_NE(image, nullptr);
    });
}

// Test that error message is non-empty for unknown image type
TEST(ImageFactoryTest_1106, ErrorMessageNonEmpty_1106) {
    try {
        Exiv2::ImageFactory::open("this_does_not_exist_1106.bin", false);
        FAIL() << "Expected exception";
    } catch (const Exiv2::Error& e) {
        std::string msg = e.what();
        EXPECT_FALSE(msg.empty());
    }
}
