#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <memory>
#include <sstream>
#include <cstring>

namespace {

// Minimal valid TIFF header (little-endian)
std::vector<uint8_t> createMinimalTiffData() {
    std::vector<uint8_t> data = {
        0x49, 0x49,       // Little-endian byte order ("II")
        0x2A, 0x00,       // TIFF magic number (42)
        0x08, 0x00, 0x00, 0x00, // Offset to first IFD (8)
        // Minimal IFD with 0 entries
        0x00, 0x00,       // Number of directory entries = 0
        0x00, 0x00, 0x00, 0x00  // Next IFD offset = 0 (no more IFDs)
    };
    return data;
}

// Create a big-endian TIFF header
std::vector<uint8_t> createMinimalTiffDataBigEndian() {
    std::vector<uint8_t> data = {
        0x4D, 0x4D,       // Big-endian byte order ("MM")
        0x00, 0x2A,       // TIFF magic number (42)
        0x00, 0x00, 0x00, 0x08, // Offset to first IFD (8)
        // Minimal IFD with 0 entries
        0x00, 0x00,       // Number of directory entries = 0
        0x00, 0x00, 0x00, 0x00  // Next IFD offset = 0
    };
    return data;
}

} // anonymous namespace

class NewTiffInstanceTest_1736 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that newTiffInstance returns a valid image when given valid TIFF data
TEST_F(NewTiffInstanceTest_1736, ValidTiffData_ReturnsNonNull_1736) {
    auto tiffData = createMinimalTiffData();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    // A valid TIFF should produce a non-null image
    EXPECT_NE(image, nullptr);
}

// Test that newTiffInstance returns a valid image for big-endian TIFF data
TEST_F(NewTiffInstanceTest_1736, ValidTiffDataBigEndian_ReturnsNonNull_1736) {
    auto tiffData = createMinimalTiffDataBigEndian();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    EXPECT_NE(image, nullptr);
}

// Test that newTiffInstance with create=true and empty IO creates a valid image
TEST_F(NewTiffInstanceTest_1736, CreateMode_EmptyIo_1736) {
    auto io = std::make_unique<Exiv2::MemIo>();
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), true);
    
    // When create=true, the function should create a new image
    // The result depends on whether good() returns true
    // We just test that no crash occurs and check the result
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test that newTiffInstance with invalid data returns nullptr (not good)
TEST_F(NewTiffInstanceTest_1736, InvalidData_ReturnsNull_1736) {
    // Provide completely invalid data (not a TIFF)
    std::vector<uint8_t> invalidData = {0x00, 0x01, 0x02, 0x03};
    auto io = std::make_unique<Exiv2::MemIo>(invalidData.data(), invalidData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    // Invalid TIFF data should result in nullptr (good() returns false)
    EXPECT_EQ(image, nullptr);
}

// Test that newTiffInstance with empty data and create=false returns nullptr
TEST_F(NewTiffInstanceTest_1736, EmptyData_CreateFalse_ReturnsNull_1736) {
    auto io = std::make_unique<Exiv2::MemIo>();
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    // Empty data with create=false should not be a valid TIFF
    EXPECT_EQ(image, nullptr);
}

// Test that newTiffInstance with truncated TIFF header returns nullptr
TEST_F(NewTiffInstanceTest_1736, TruncatedHeader_ReturnsNull_1736) {
    // Only the byte order mark, no magic number or IFD offset
    std::vector<uint8_t> truncated = {0x49, 0x49};
    auto io = std::make_unique<Exiv2::MemIo>(truncated.data(), truncated.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    EXPECT_EQ(image, nullptr);
}

// Test that the returned image provides access to io
TEST_F(NewTiffInstanceTest_1736, ValidImage_HasIoAccess_1736) {
    auto tiffData = createMinimalTiffData();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    ASSERT_NE(image, nullptr);
    // The image should have an accessible BasicIo reference
    EXPECT_NO_THROW(image->io());
}

// Test that the returned image is good
TEST_F(NewTiffInstanceTest_1736, ValidImage_IsGood_1736) {
    auto tiffData = createMinimalTiffData();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

// Test that the returned image has correct mime type for TIFF
TEST_F(NewTiffInstanceTest_1736, ValidImage_MimeType_1736) {
    auto tiffData = createMinimalTiffData();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    ASSERT_NE(image, nullptr);
    std::string mimeType = image->mimeType();
    EXPECT_EQ(mimeType, "image/tiff");
}

// Test with JPEG-like data (wrong format) returns nullptr
TEST_F(NewTiffInstanceTest_1736, JpegData_ReturnsNull_1736) {
    // JPEG magic bytes
    std::vector<uint8_t> jpegData = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    EXPECT_EQ(image, nullptr);
}

// Test with PNG-like data (wrong format) returns nullptr
TEST_F(NewTiffInstanceTest_1736, PngData_ReturnsNull_1736) {
    // PNG magic bytes
    std::vector<uint8_t> pngData = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    EXPECT_EQ(image, nullptr);
}

// Test that valid TIFF image has initial pixel dimensions of 0
TEST_F(NewTiffInstanceTest_1736, ValidImage_InitialPixelDimensions_1736) {
    auto tiffData = createMinimalTiffData();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    ASSERT_NE(image, nullptr);
    // Before reading metadata, pixel dimensions should be 0
    EXPECT_EQ(image->pixelWidth(), 0u);
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test with wrong magic number but valid byte order
TEST_F(NewTiffInstanceTest_1736, WrongMagicNumber_ReturnsNull_1736) {
    std::vector<uint8_t> data = {
        0x49, 0x49,       // Little-endian byte order ("II")
        0x00, 0x00,       // Wrong magic number (should be 42)
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    EXPECT_EQ(image, nullptr);
}

// Test that exifData is accessible on a valid TIFF image
TEST_F(NewTiffInstanceTest_1736, ValidImage_ExifDataAccessible_1736) {
    auto tiffData = createMinimalTiffData();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->exifData());
}

// Test that iptcData is accessible on a valid TIFF image
TEST_F(NewTiffInstanceTest_1736, ValidImage_IptcDataAccessible_1736) {
    auto tiffData = createMinimalTiffData();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->iptcData());
}

// Test that xmpData is accessible on a valid TIFF image
TEST_F(NewTiffInstanceTest_1736, ValidImage_XmpDataAccessible_1736) {
    auto tiffData = createMinimalTiffData();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->xmpData());
}

// Test that comment is empty initially
TEST_F(NewTiffInstanceTest_1736, ValidImage_CommentEmpty_1736) {
    auto tiffData = createMinimalTiffData();
    auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->comment().empty());
}

// Test single byte data returns nullptr
TEST_F(NewTiffInstanceTest_1736, SingleByteData_ReturnsNull_1736) {
    std::vector<uint8_t> singleByte = {0x49};
    auto io = std::make_unique<Exiv2::MemIo>(singleByte.data(), singleByte.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    EXPECT_EQ(image, nullptr);
}

// Test all zero bytes returns nullptr
TEST_F(NewTiffInstanceTest_1736, AllZeroBytes_ReturnsNull_1736) {
    std::vector<uint8_t> zeros(100, 0);
    auto io = std::make_unique<Exiv2::MemIo>(zeros.data(), zeros.size());
    
    Exiv2::Image::UniquePtr image = Exiv2::newTiffInstance(std::move(io), false);
    
    EXPECT_EQ(image, nullptr);
}
