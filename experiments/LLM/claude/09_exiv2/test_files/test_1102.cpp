#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <fstream>
#include <cstdio>
#include <vector>
#include <cstring>

namespace {

// Helper to create a temporary file with given content
class TempFile {
public:
    TempFile(const std::string& name, const std::vector<unsigned char>& content) : path_(name) {
        std::ofstream ofs(path_, std::ios::binary);
        if (!content.empty()) {
            ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
        }
        ofs.close();
    }
    ~TempFile() {
        std::remove(path_.c_str());
    }
    const std::string& path() const { return path_; }
private:
    std::string path_;
};

// JPEG file signature
std::vector<unsigned char> createMinimalJpeg() {
    // Minimal JPEG: SOI marker + APP0 + EOI
    std::vector<unsigned char> data = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
        0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
        0x00, 0x00, 0xFF, 0xD9
    };
    return data;
}

// PNG file signature
std::vector<unsigned char> createMinimalPng() {
    std::vector<unsigned char> data = {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, // PNG signature
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
        0xAE, 0x42, 0x60, 0x82
    };
    return data;
}

} // anonymous namespace

// Test getType with a valid JPEG file path
TEST(ImageFactoryTest_1102, GetTypeJpegFile_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    auto jpegData = createMinimalJpeg();
    TempFile tmp("test_image_1102.jpg", jpegData);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(tmp.path());
    EXPECT_EQ(type, Exiv2::ImageType::jpeg);
#else
    Exiv2::ImageType type = Exiv2::ImageFactory::getType("nonexistent.jpg");
    EXPECT_EQ(type, Exiv2::ImageType::none);
#endif
}

// Test getType with a valid PNG file path
TEST(ImageFactoryTest_1102, GetTypePngFile_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    auto pngData = createMinimalPng();
    TempFile tmp("test_image_1102.png", pngData);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(tmp.path());
    EXPECT_EQ(type, Exiv2::ImageType::png);
#else
    Exiv2::ImageType type = Exiv2::ImageFactory::getType("nonexistent.png");
    EXPECT_EQ(type, Exiv2::ImageType::none);
#endif
}

// Test getType with a nonexistent file
TEST(ImageFactoryTest_1102, GetTypeNonexistentFile_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    // Should throw or return none for nonexistent file
    try {
        Exiv2::ImageType type = Exiv2::ImageFactory::getType("/tmp/nonexistent_file_1102_xyz.jpg");
        // If it doesn't throw, it should return none
        EXPECT_EQ(type, Exiv2::ImageType::none);
    } catch (const Exiv2::Error&) {
        // Expected - file doesn't exist
        SUCCEED();
    }
#else
    Exiv2::ImageType type = Exiv2::ImageFactory::getType("/tmp/nonexistent_file_1102_xyz.jpg");
    EXPECT_EQ(type, Exiv2::ImageType::none);
#endif
}

// Test getType with an empty file
TEST(ImageFactoryTest_1102, GetTypeEmptyFile_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    std::vector<unsigned char> emptyData;
    TempFile tmp("test_empty_1102.dat", emptyData);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(tmp.path());
    EXPECT_EQ(type, Exiv2::ImageType::none);
#else
    Exiv2::ImageType type = Exiv2::ImageFactory::getType("empty.dat");
    EXPECT_EQ(type, Exiv2::ImageType::none);
#endif
}

// Test getType with random/garbage data
TEST(ImageFactoryTest_1102, GetTypeGarbageData_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    std::vector<unsigned char> garbageData = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    TempFile tmp("test_garbage_1102.dat", garbageData);
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(tmp.path());
    EXPECT_EQ(type, Exiv2::ImageType::none);
#else
    Exiv2::ImageType type = Exiv2::ImageFactory::getType("garbage.dat");
    EXPECT_EQ(type, Exiv2::ImageType::none);
#endif
}

// Test getType with empty string path
TEST(ImageFactoryTest_1102, GetTypeEmptyPath_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    try {
        Exiv2::ImageType type = Exiv2::ImageFactory::getType(std::string(""));
        EXPECT_EQ(type, Exiv2::ImageType::none);
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
#else
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(std::string(""));
    EXPECT_EQ(type, Exiv2::ImageType::none);
#endif
}

// Test getType with byte array for JPEG
TEST(ImageFactoryTest_1102, GetTypeFromBytesJpeg_1102) {
    auto jpegData = createMinimalJpeg();
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(jpegData.data(), jpegData.size());
    EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

// Test getType with byte array for PNG
TEST(ImageFactoryTest_1102, GetTypeFromBytesPng_1102) {
    auto pngData = createMinimalPng();
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(pngData.data(), pngData.size());
    EXPECT_EQ(type, Exiv2::ImageType::png);
}

// Test getType with byte array of garbage
TEST(ImageFactoryTest_1102, GetTypeFromBytesGarbage_1102) {
    std::vector<unsigned char> garbageData = {0x01, 0x02, 0x03, 0x04, 0x05};
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(garbageData.data(), garbageData.size());
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test getType with zero-size byte array
TEST(ImageFactoryTest_1102, GetTypeFromBytesZeroSize_1102) {
    unsigned char dummy = 0;
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(&dummy, 0);
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test open with byte array for JPEG
TEST(ImageFactoryTest_1102, OpenFromBytesJpeg_1102) {
    auto jpegData = createMinimalJpeg();
    auto image = Exiv2::ImageFactory::open(jpegData.data(), jpegData.size());
    ASSERT_NE(image, nullptr);
}

// Test open with garbage bytes should throw or return nullptr
TEST(ImageFactoryTest_1102, OpenFromBytesGarbage_1102) {
    std::vector<unsigned char> garbageData = {0x01, 0x02, 0x03, 0x04};
    EXPECT_THROW(
        Exiv2::ImageFactory::open(garbageData.data(), garbageData.size()),
        Exiv2::Error
    );
}

// Test open with file path for JPEG
TEST(ImageFactoryTest_1102, OpenFromFilePathJpeg_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    auto jpegData = createMinimalJpeg();
    TempFile tmp("test_open_1102.jpg", jpegData);
    auto image = Exiv2::ImageFactory::open(tmp.path());
    ASSERT_NE(image, nullptr);
#else
    GTEST_SKIP() << "Filesystem not enabled";
#endif
}

// Test open with nonexistent file path
TEST(ImageFactoryTest_1102, OpenNonexistentFilePath_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    EXPECT_THROW(
        Exiv2::ImageFactory::open("/tmp/nonexistent_open_1102_xyz.jpg"),
        Exiv2::Error
    );
#else
    GTEST_SKIP() << "Filesystem not enabled";
#endif
}

// Test create with JPEG type
TEST(ImageFactoryTest_1102, CreateJpegType_1102) {
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg);
        ASSERT_NE(image, nullptr);
    } catch (const Exiv2::Error&) {
        // Some implementations may not support creating without a path
        SUCCEED();
    }
}

// Test create with file path for JPEG
TEST(ImageFactoryTest_1102, CreateJpegWithPath_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    std::string path = "test_create_1102.jpg";
    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, path);
        ASSERT_NE(image, nullptr);
        std::remove(path.c_str());
    } catch (const Exiv2::Error&) {
        std::remove(path.c_str());
        SUCCEED();
    }
#else
    GTEST_SKIP() << "Filesystem not enabled";
#endif
}

// Test checkMode for JPEG with exif
TEST(ImageFactoryTest_1102, CheckModeJpegExif_1102) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdExif);
    // JPEG supports Exif, should be at least read
    EXPECT_NE(mode, Exiv2::AccessMode::amNone);
}

// Test checkMode for none type
TEST(ImageFactoryTest_1102, CheckModeNoneType_1102) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::none, Exiv2::MetadataId::mdExif);
    EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

// Test getType via BasicIo reference (using MemIo from bytes)
TEST(ImageFactoryTest_1102, GetTypeViaBasicIoJpeg_1102) {
    auto jpegData = createMinimalJpeg();
    Exiv2::MemIo memIo(jpegData.data(), jpegData.size());
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(memIo);
    EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

// Test getType via BasicIo reference with garbage
TEST(ImageFactoryTest_1102, GetTypeViaBasicIoGarbage_1102) {
    std::vector<unsigned char> garbage = {0xAA, 0xBB, 0xCC, 0xDD};
    Exiv2::MemIo memIo(garbage.data(), garbage.size());
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(memIo);
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test open with unique_ptr<BasicIo>
TEST(ImageFactoryTest_1102, OpenWithUniqueIo_1102) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);
}

// Test open with unique_ptr<BasicIo> garbage
TEST(ImageFactoryTest_1102, OpenWithUniqueIoGarbage_1102) {
    std::vector<unsigned char> garbage = {0x00, 0x00, 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(garbage.data(), garbage.size());
    EXPECT_THROW(
        Exiv2::ImageFactory::open(std::move(io)),
        Exiv2::Error
    );
}

// Test that JPEG checkType returns true for valid JPEG
TEST(ImageFactoryTest_1102, CheckTypeJpegValid_1102) {
    auto jpegData = createMinimalJpeg();
    Exiv2::MemIo memIo(jpegData.data(), jpegData.size());
    bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, memIo, false);
    EXPECT_TRUE(result);
}

// Test that JPEG checkType returns false for PNG data
TEST(ImageFactoryTest_1102, CheckTypeJpegWithPngData_1102) {
    auto pngData = createMinimalPng();
    Exiv2::MemIo memIo(pngData.data(), pngData.size());
    bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, memIo, false);
    EXPECT_FALSE(result);
}

// Test createIo
TEST(ImageFactoryTest_1102, CreateIo_1102) {
#ifdef EXV_ENABLE_FILESYSTEM
    auto jpegData = createMinimalJpeg();
    TempFile tmp("test_createio_1102.jpg", jpegData);
    auto io = Exiv2::ImageFactory::createIo(tmp.path(), false);
    ASSERT_NE(io, nullptr);
    EXPECT_EQ(io->path(), tmp.path());
#else
    GTEST_SKIP() << "Filesystem not enabled";
#endif
}
