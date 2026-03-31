#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <cstdio>
#include <filesystem>

namespace {

// Helper to create a temporary file path
std::string getTempFilePath(const std::string& suffix = ".jpg") {
    std::string path = std::filesystem::temp_directory_path().string() + "/exiv2_test_1109_" + suffix;
    return path;
}

// Helper to create a minimal JPEG file
void createMinimalJpeg(const std::string& path) {
    std::ofstream ofs(path, std::ios::binary);
    // Minimal JPEG: SOI + EOI
    unsigned char data[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                            'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
                            0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
                            0xFF, 0xD9};
    ofs.write(reinterpret_cast<char*>(data), sizeof(data));
    ofs.close();
}

// Helper to clean up a file
void removeFile(const std::string& path) {
    std::remove(path.c_str());
}

class ImageFactoryTest_1109 : public ::testing::Test {
protected:
    void TearDown() override {
        for (const auto& f : filesToCleanup_) {
            removeFile(f);
        }
    }

    void trackFile(const std::string& path) {
        filesToCleanup_.push_back(path);
    }

    std::vector<std::string> filesToCleanup_;
};

// Test: create() with a valid JPEG type creates a non-null image
TEST_F(ImageFactoryTest_1109, CreateJpegImage_1109) {
    std::string path = getTempFilePath("create_jpeg.jpg");
    trackFile(path);

    Exiv2::Image::UniquePtr image;
    ASSERT_NO_THROW(image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, path));
    ASSERT_NE(image, nullptr);
}

// Test: create() with a valid PNG type creates a non-null image
TEST_F(ImageFactoryTest_1109, CreatePngImage_1109) {
    std::string path = getTempFilePath("create_png.png");
    trackFile(path);

    try {
        auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::png, path);
        // If PNG support is compiled in, image should be valid
        EXPECT_NE(image, nullptr);
    } catch (const Exiv2::Error& e) {
        // PNG might not be supported - that's acceptable
        EXPECT_TRUE(e.code() == Exiv2::ErrorCode::kerUnsupportedImageType ||
                    e.code() == Exiv2::ErrorCode::kerFileOpenFailed);
    }
}

// Test: create() with invalid path throws an error
TEST_F(ImageFactoryTest_1109, CreateWithInvalidPathThrows_1109) {
    std::string invalidPath = "/nonexistent/directory/that/does/not/exist/test.jpg";
    EXPECT_THROW(Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, invalidPath), Exiv2::Error);
}

// Test: create() with unsupported image type throws
TEST_F(ImageFactoryTest_1109, CreateWithUnsupportedTypeThrows_1109) {
    std::string path = getTempFilePath("unsupported.xyz");
    trackFile(path);

    EXPECT_THROW(
        Exiv2::ImageFactory::create(Exiv2::ImageType::none, path),
        Exiv2::Error
    );
}

// Test: open() with a valid JPEG file returns a non-null image
TEST_F(ImageFactoryTest_1109, OpenValidJpegFile_1109) {
    std::string path = getTempFilePath("open_valid.jpg");
    trackFile(path);
    createMinimalJpeg(path);

    Exiv2::Image::UniquePtr image;
    ASSERT_NO_THROW(image = Exiv2::ImageFactory::open(path));
    ASSERT_NE(image, nullptr);
}

// Test: open() with a non-existent file throws
TEST_F(ImageFactoryTest_1109, OpenNonExistentFileThrows_1109) {
    std::string path = "/nonexistent/path/to/file.jpg";
    EXPECT_THROW(Exiv2::ImageFactory::open(path), Exiv2::Error);
}

// Test: open() with byte data for a valid JPEG
TEST_F(ImageFactoryTest_1109, OpenFromByteData_1109) {
    unsigned char data[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                            'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
                            0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
                            0xFF, 0xD9};

    Exiv2::Image::UniquePtr image;
    ASSERT_NO_THROW(image = Exiv2::ImageFactory::open(data, sizeof(data)));
    ASSERT_NE(image, nullptr);
}

// Test: open() with empty/invalid byte data throws
TEST_F(ImageFactoryTest_1109, OpenFromInvalidByteDataThrows_1109) {
    unsigned char data[] = {0x00, 0x00, 0x00};
    EXPECT_THROW(Exiv2::ImageFactory::open(data, sizeof(data)), Exiv2::Error);
}

// Test: open() with zero-size data throws
TEST_F(ImageFactoryTest_1109, OpenFromZeroSizeDataThrows_1109) {
    unsigned char data[] = {0x00};
    EXPECT_THROW(Exiv2::ImageFactory::open(data, 0), Exiv2::Error);
}

// Test: getType() with a valid JPEG file returns jpeg type
TEST_F(ImageFactoryTest_1109, GetTypeFromJpegFile_1109) {
    std::string path = getTempFilePath("gettype.jpg");
    trackFile(path);
    createMinimalJpeg(path);

    Exiv2::ImageType type = Exiv2::ImageFactory::getType(path);
    EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

// Test: getType() from byte data for JPEG returns jpeg type
TEST_F(ImageFactoryTest_1109, GetTypeFromJpegByteData_1109) {
    unsigned char data[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                            'J', 'F', 'I', 'F', 0x00, 0x01, 0x01, 0x00,
                            0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
                            0xFF, 0xD9};

    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data, sizeof(data));
    EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

// Test: getType() with non-existent file throws
TEST_F(ImageFactoryTest_1109, GetTypeNonExistentFileThrows_1109) {
    EXPECT_THROW(Exiv2::ImageFactory::getType("/nonexistent/file.jpg"), Exiv2::Error);
}

// Test: getType() with unknown data returns none
TEST_F(ImageFactoryTest_1109, GetTypeUnknownDataReturnsNone_1109) {
    unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    Exiv2::ImageType type = Exiv2::ImageFactory::getType(data, sizeof(data));
    EXPECT_EQ(type, Exiv2::ImageType::none);
}

// Test: open() with BasicIo unique_ptr
TEST_F(ImageFactoryTest_1109, OpenWithBasicIo_1109) {
    std::string path = getTempFilePath("open_io.jpg");
    trackFile(path);
    createMinimalJpeg(path);

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::Image::UniquePtr image;
    ASSERT_NO_THROW(image = Exiv2::ImageFactory::open(std::move(io)));
    ASSERT_NE(image, nullptr);
}

// Test: create() without path (MemIo based)
TEST_F(ImageFactoryTest_1109, CreateWithoutPath_1109) {
    Exiv2::Image::UniquePtr image;
    ASSERT_NO_THROW(image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg));
    ASSERT_NE(image, nullptr);
}

// Test: create() with unsupported type without path throws
TEST_F(ImageFactoryTest_1109, CreateWithoutPathUnsupportedType_1109) {
    EXPECT_THROW(
        Exiv2::ImageFactory::create(Exiv2::ImageType::none),
        Exiv2::Error
    );
}

// Test: checkMode() returns a valid AccessMode for known type and metadata
TEST_F(ImageFactoryTest_1109, CheckModeForJpegExif_1109) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdExif);
    // JPEG should support Exif read/write
    EXPECT_NE(mode, Exiv2::AccessMode::amNone);
}

// Test: checkMode() for unsupported combination
TEST_F(ImageFactoryTest_1109, CheckModeForNoneType_1109) {
    Exiv2::AccessMode mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::none, Exiv2::MetadataId::mdExif);
    EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

// Test: create() with BasicIo for JPEG type
TEST_F(ImageFactoryTest_1109, CreateWithBasicIo_1109) {
    std::string path = getTempFilePath("create_io.jpg");
    trackFile(path);

    // Create a file first so FileIo can be opened
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }

    auto io = std::make_unique<Exiv2::FileIo>(path);
    ASSERT_EQ(io->open("w+b"), 0);
    io->close();

    Exiv2::Image::UniquePtr image;
    ASSERT_NO_THROW(image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, std::move(io)));
    ASSERT_NE(image, nullptr);
}

// Test: createIo returns a non-null BasicIo for a valid path
TEST_F(ImageFactoryTest_1109, CreateIoValidPath_1109) {
    std::string path = getTempFilePath("createio.jpg");
    trackFile(path);

    // Create the file
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }

    Exiv2::BasicIo::UniquePtr io;
    ASSERT_NO_THROW(io = Exiv2::ImageFactory::createIo(path, false));
    ASSERT_NE(io, nullptr);
}

// Test: Verify the created file exists on disk after create()
TEST_F(ImageFactoryTest_1109, CreateJpegCreatesFileOnDisk_1109) {
    std::string path = getTempFilePath("file_on_disk.jpg");
    trackFile(path);

    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, path);
    ASSERT_NE(image, nullptr);

    // File should exist on disk
    EXPECT_TRUE(std::filesystem::exists(path));
}

// Test: open() with an empty file throws (not a valid image)
TEST_F(ImageFactoryTest_1109, OpenEmptyFileThrows_1109) {
    std::string path = getTempFilePath("empty.jpg");
    trackFile(path);

    // Create an empty file
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }

    EXPECT_THROW(Exiv2::ImageFactory::open(path), Exiv2::Error);
}

// Test: getType() with a BasicIo reference
TEST_F(ImageFactoryTest_1109, GetTypeFromBasicIo_1109) {
    std::string path = getTempFilePath("gettype_io.jpg");
    trackFile(path);
    createMinimalJpeg(path);

    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);

    Exiv2::ImageType type = Exiv2::ImageFactory::getType(io);
    EXPECT_EQ(type, Exiv2::ImageType::jpeg);

    io.close();
}

// Test: checkType() with JPEG type and valid JPEG BasicIo returns true
TEST_F(ImageFactoryTest_1109, CheckTypeJpegValid_1109) {
    std::string path = getTempFilePath("checktype.jpg");
    trackFile(path);
    createMinimalJpeg(path);

    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);

    bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, io, false);
    EXPECT_TRUE(result);

    io.close();
}

// Test: checkType() with wrong type returns false
TEST_F(ImageFactoryTest_1109, CheckTypeWrongTypeReturnsFalse_1109) {
    std::string path = getTempFilePath("checktype_wrong.jpg");
    trackFile(path);
    createMinimalJpeg(path);

    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);

    // PNG check on a JPEG file should return false
    bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::png, io, false);
    EXPECT_FALSE(result);

    io.close();
}

// Test: Multiple create() calls with same path should work
TEST_F(ImageFactoryTest_1109, MultipleCreatesOnSamePath_1109) {
    std::string path = getTempFilePath("multi_create.jpg");
    trackFile(path);

    auto image1 = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, path);
    ASSERT_NE(image1, nullptr);

    auto image2 = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, path);
    ASSERT_NE(image2, nullptr);
}

// Test: open from byte data with null pointer throws
TEST_F(ImageFactoryTest_1109, OpenFromNullByteDataThrows_1109) {
    EXPECT_THROW(Exiv2::ImageFactory::open(nullptr, 0), Exiv2::Error);
}

}  // namespace
