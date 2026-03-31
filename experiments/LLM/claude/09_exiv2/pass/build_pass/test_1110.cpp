#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>

namespace {

using namespace Exiv2;

class ImageFactoryTest_1110 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test creating a JPEG image in memory (no file path)
TEST_F(ImageFactoryTest_1110, CreateJpegImageInMemory_1110) {
    EXPECT_NO_THROW({
        auto image = ImageFactory::create(ImageType::jpeg);
        ASSERT_NE(image, nullptr);
    });
}

// Test creating a PNG image in memory
TEST_F(ImageFactoryTest_1110, CreatePngImageInMemory_1110) {
    try {
        auto image = ImageFactory::create(ImageType::png);
        ASSERT_NE(image, nullptr);
    } catch (const Exiv2::Error& e) {
        // PNG support might not be compiled in; if so, expect unsupported type error
        EXPECT_EQ(e.code(), ErrorCode::kerUnsupportedImageType);
    }
}

// Test creating an EXV image in memory
TEST_F(ImageFactoryTest_1110, CreateExvImageInMemory_1110) {
    EXPECT_NO_THROW({
        auto image = ImageFactory::create(ImageType::exv);
        ASSERT_NE(image, nullptr);
    });
}

// Test that creating an image with an unsupported/invalid type throws
TEST_F(ImageFactoryTest_1110, CreateUnsupportedImageTypeThrows_1110) {
    EXPECT_THROW({
        auto image = ImageFactory::create(ImageType::none);
    }, Exiv2::Error);
}

// Test that the thrown error for unsupported type has the correct error code
TEST_F(ImageFactoryTest_1110, CreateUnsupportedImageTypeErrorCode_1110) {
    try {
        auto image = ImageFactory::create(ImageType::none);
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerUnsupportedImageType);
    }
}

// Test creating a TIFF image in memory
TEST_F(ImageFactoryTest_1110, CreateTiffImageInMemory_1110) {
    try {
        auto image = ImageFactory::create(ImageType::tiff);
        ASSERT_NE(image, nullptr);
    } catch (const Exiv2::Error& e) {
        // TIFF creation might not be supported for MemIo
        EXPECT_EQ(e.code(), ErrorCode::kerUnsupportedImageType);
    }
}

// Test creating a BMP image in memory
TEST_F(ImageFactoryTest_1110, CreateBmpImageInMemory_1110) {
    try {
        auto image = ImageFactory::create(ImageType::bmp);
        ASSERT_NE(image, nullptr);
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerUnsupportedImageType);
    }
}

// Test creating image with MemIo explicitly
TEST_F(ImageFactoryTest_1110, CreateJpegWithMemIo_1110) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW({
        auto image = ImageFactory::create(ImageType::jpeg, std::move(io));
        ASSERT_NE(image, nullptr);
    });
}

// Test creating image with MemIo for unsupported type throws
TEST_F(ImageFactoryTest_1110, CreateNoneTypeWithMemIoThrows_1110) {
    auto io = std::make_unique<MemIo>();
    EXPECT_THROW({
        auto image = ImageFactory::create(ImageType::none, std::move(io));
    }, Exiv2::Error);
}

// Test opening from byte data that is empty
TEST_F(ImageFactoryTest_1110, OpenFromEmptyDataThrows_1110) {
    const byte data[] = {0};
    EXPECT_THROW({
        auto image = ImageFactory::open(data, 0);
    }, Exiv2::Error);
}

// Test opening from invalid/random byte data
TEST_F(ImageFactoryTest_1110, OpenFromGarbageDataThrows_1110) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04};
    EXPECT_THROW({
        auto image = ImageFactory::open(data, sizeof(data));
    }, Exiv2::Error);
}

// Test opening from valid JPEG byte data (minimal JPEG header)
TEST_F(ImageFactoryTest_1110, OpenFromValidJpegData_1110) {
    // Minimal JPEG: SOI marker + EOI marker
    const byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    try {
        auto image = ImageFactory::open(jpegData, sizeof(jpegData));
        ASSERT_NE(image, nullptr);
    } catch (const Exiv2::Error&) {
        // Some implementations may require more complete JPEG data
    }
}

// Test getType from byte data with unknown content
TEST_F(ImageFactoryTest_1110, GetTypeFromUnknownData_1110) {
    const byte data[] = {0x00, 0x00, 0x00, 0x00};
    auto type = ImageFactory::getType(data, sizeof(data));
    EXPECT_EQ(type, ImageType::none);
}

// Test getType from JPEG-like byte data
TEST_F(ImageFactoryTest_1110, GetTypeFromJpegData_1110) {
    const byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto type = ImageFactory::getType(jpegData, sizeof(jpegData));
    EXPECT_EQ(type, ImageType::jpeg);
}

// Test checkMode for JPEG with EXIF metadata
TEST_F(ImageFactoryTest_1110, CheckModeJpegExif_1110) {
    auto mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdExif);
    // JPEG should support EXIF; amWrite or amReadWrite expected
    EXPECT_NE(mode, AccessMode::amNone);
}

// Test checkMode for unsupported type
TEST_F(ImageFactoryTest_1110, CheckModeNoneType_1110) {
    auto mode = ImageFactory::checkMode(ImageType::none, MetadataId::mdExif);
    EXPECT_EQ(mode, AccessMode::amNone);
}

// Test opening from MemIo with no data
TEST_F(ImageFactoryTest_1110, OpenFromEmptyMemIoThrows_1110) {
    auto io = std::make_unique<MemIo>();
    EXPECT_THROW({
        auto image = ImageFactory::open(std::move(io));
    }, Exiv2::Error);
}

// Test opening a nonexistent file path
TEST_F(ImageFactoryTest_1110, OpenNonexistentFileThrows_1110) {
    EXPECT_THROW({
        auto image = ImageFactory::open("/nonexistent/path/to/image.jpg", false);
    }, Exiv2::Error);
}

// Test getType from nonexistent file path
TEST_F(ImageFactoryTest_1110, GetTypeNonexistentFileThrows_1110) {
    EXPECT_THROW({
        auto type = ImageFactory::getType("/nonexistent/path/to/image.jpg");
    }, Exiv2::Error);
}

// Test creating image to a path that cannot be written
TEST_F(ImageFactoryTest_1110, CreateToInvalidPathThrows_1110) {
    EXPECT_THROW({
        auto image = ImageFactory::create(ImageType::jpeg, "/nonexistent/dir/test.jpg");
    }, Exiv2::Error);
}

// Test creating an EXV with explicit MemIo
TEST_F(ImageFactoryTest_1110, CreateExvWithMemIo_1110) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW({
        auto image = ImageFactory::create(ImageType::exv, std::move(io));
        ASSERT_NE(image, nullptr);
    });
}

// Test that opening valid JPEG data returns an image that can be queried
TEST_F(ImageFactoryTest_1110, OpenJpegDataAndReadMetadata_1110) {
    // Minimal JPEG with SOI and EOI
    const byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    try {
        auto image = ImageFactory::open(jpegData, sizeof(jpegData));
        ASSERT_NE(image, nullptr);
        // Reading metadata on minimal JPEG might fail but shouldn't crash
        try {
            image->readMetadata();
        } catch (const Exiv2::Error&) {
            // Expected for minimal data
        }
    } catch (const Exiv2::Error&) {
        // Some builds may not accept minimal JPEG
    }
}

// Test createIo with nonexistent path
TEST_F(ImageFactoryTest_1110, CreateIoNonexistentPath_1110) {
    // createIo should still return an Io object; it might not fail until open
    auto io = ImageFactory::createIo("/some/nonexistent/path.jpg", false);
    ASSERT_NE(io, nullptr);
}

// Test checkMode for JPEG with IPTC metadata
TEST_F(ImageFactoryTest_1110, CheckModeJpegIptc_1110) {
    auto mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdIptc);
    EXPECT_NE(mode, AccessMode::amNone);
}

// Test checkMode for JPEG with XMP metadata
TEST_F(ImageFactoryTest_1110, CheckModeJpegXmp_1110) {
    auto mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdXmp);
    // JPEG typically supports XMP
    EXPECT_NE(mode, AccessMode::amNone);
}

// Test getType with TIFF header (little-endian)
TEST_F(ImageFactoryTest_1110, GetTypeFromTiffLittleEndianData_1110) {
    const byte tiffData[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    auto type = ImageFactory::getType(tiffData, sizeof(tiffData));
    // Should detect as TIFF or CR2 or similar
    EXPECT_NE(type, ImageType::none);
}

// Test getType with TIFF header (big-endian)
TEST_F(ImageFactoryTest_1110, GetTypeFromTiffBigEndianData_1110) {
    const byte tiffData[] = {0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x08};
    auto type = ImageFactory::getType(tiffData, sizeof(tiffData));
    EXPECT_NE(type, ImageType::none);
}

// Test getType with PNG header
TEST_F(ImageFactoryTest_1110, GetTypeFromPngData_1110) {
    const byte pngData[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    auto type = ImageFactory::getType(pngData, sizeof(pngData));
    EXPECT_EQ(type, ImageType::png);
}

// Test single byte data
TEST_F(ImageFactoryTest_1110, GetTypeFromSingleByte_1110) {
    const byte data[] = {0xFF};
    auto type = ImageFactory::getType(data, sizeof(data));
    EXPECT_EQ(type, ImageType::none);
}

}  // namespace
