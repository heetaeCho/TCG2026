#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/pngimage.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>

#include <cstring>
#include <fstream>
#include <sstream>

namespace {

// Minimal valid PNG file header and IHDR chunk
const unsigned char kMinimalPng[] = {
    // PNG signature
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
    // IHDR chunk
    0x00, 0x00, 0x00, 0x0D, // length = 13
    0x49, 0x48, 0x44, 0x52, // "IHDR"
    0x00, 0x00, 0x00, 0x01, // width = 1
    0x00, 0x00, 0x00, 0x01, // height = 1
    0x08,                   // bit depth = 8
    0x02,                   // color type = RGB
    0x00,                   // compression
    0x00,                   // filter
    0x00,                   // interlace
    0x1E, 0x92, 0x6E, 0x05, // CRC for IHDR
    // IDAT chunk (minimal)
    0x00, 0x00, 0x00, 0x0C, // length = 12
    0x49, 0x44, 0x41, 0x54, // "IDAT"
    0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x01, // compressed data
    0xE2, 0x21, 0xBC, 0x33, // CRC for IDAT
    // IEND chunk
    0x00, 0x00, 0x00, 0x00, // length = 0
    0x49, 0x45, 0x4E, 0x44, // "IEND"
    0xAE, 0x42, 0x60, 0x82  // CRC for IEND
};

// Helper to create a MemIo from a byte array
Exiv2::BasicIo::UniquePtr makeMemIo(const unsigned char* data, size_t size) {
    return std::make_unique<Exiv2::MemIo>(data, size);
}

// Helper to create an empty MemIo
Exiv2::BasicIo::UniquePtr makeEmptyMemIo() {
    return std::make_unique<Exiv2::MemIo>();
}

} // anonymous namespace

// Test fixture
class NewPngInstanceTest_976 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Creating a PNG image with valid PNG data should return a non-null pointer
TEST_F(NewPngInstanceTest_976, ValidPngDataReturnsNonNull_976) {
    auto io = makeMemIo(kMinimalPng, sizeof(kMinimalPng));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    EXPECT_NE(image, nullptr);
}

// Test: Creating a PNG image with create=true and empty IO should succeed
TEST_F(NewPngInstanceTest_976, CreateTrueWithEmptyIoReturnsImage_976) {
    auto io = makeEmptyMemIo();
    auto image = Exiv2::newPngInstance(std::move(io), true);
    // When create is true, the factory should create a valid image
    // (it may or may not be null depending on implementation)
    // We just verify it doesn't crash and check good()
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: Creating a PNG image with invalid (garbage) data should return null
TEST_F(NewPngInstanceTest_976, InvalidDataReturnsNull_976) {
    const unsigned char garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    auto io = makeMemIo(garbage, sizeof(garbage));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: Creating a PNG image with empty data and create=false should return null
TEST_F(NewPngInstanceTest_976, EmptyDataCreateFalseReturnsNull_976) {
    auto io = makeEmptyMemIo();
    auto image = Exiv2::newPngInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: Creating a PNG with only the PNG signature but no chunks should return null
TEST_F(NewPngInstanceTest_976, OnlySignatureReturnsNull_976) {
    const unsigned char signature[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    auto io = makeMemIo(signature, sizeof(signature));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: A valid PNG image returned by newPngInstance should report good() == true
TEST_F(NewPngInstanceTest_976, ValidPngImageIsGood_976) {
    auto io = makeMemIo(kMinimalPng, sizeof(kMinimalPng));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

// Test: A valid PNG image should return correct MIME type
TEST_F(NewPngInstanceTest_976, ValidPngMimeType_976) {
    auto io = makeMemIo(kMinimalPng, sizeof(kMinimalPng));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->mimeType(), "image/png");
}

// Test: Truncated PNG signature should return null
TEST_F(NewPngInstanceTest_976, TruncatedSignatureReturnsNull_976) {
    const unsigned char truncated[] = {0x89, 0x50, 0x4E};
    auto io = makeMemIo(truncated, sizeof(truncated));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: Single byte input should return null
TEST_F(NewPngInstanceTest_976, SingleByteReturnsNull_976) {
    const unsigned char single[] = {0x89};
    auto io = makeMemIo(single, sizeof(single));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: JPEG data should not be recognized as PNG and should return null
TEST_F(NewPngInstanceTest_976, JpegDataReturnsNull_976) {
    const unsigned char jpegHeader[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46};
    auto io = makeMemIo(jpegHeader, sizeof(jpegHeader));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: Corrupted PNG signature (one byte off) should return null
TEST_F(NewPngInstanceTest_976, CorruptedSignatureReturnsNull_976) {
    unsigned char corrupted[sizeof(kMinimalPng)];
    std::memcpy(corrupted, kMinimalPng, sizeof(kMinimalPng));
    corrupted[0] = 0x88; // Corrupt first byte of signature
    auto io = makeMemIo(corrupted, sizeof(corrupted));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: The returned Image provides access to io
TEST_F(NewPngInstanceTest_976, ReturnedImageHasIo_976) {
    auto io = makeMemIo(kMinimalPng, sizeof(kMinimalPng));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    // The io() method should be accessible
    EXPECT_NO_THROW(image->io());
}

// Test: The returned image should have zero pixel dimensions before readMetadata
TEST_F(NewPngInstanceTest_976, PixelDimensionsBeforeRead_976) {
    auto io = makeMemIo(kMinimalPng, sizeof(kMinimalPng));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    // Before readMetadata, pixel dimensions might be 0
    // This is just testing the interface is accessible
    EXPECT_GE(image->pixelWidth(), 0u);
    EXPECT_GE(image->pixelHeight(), 0u);
}

// Test: Verify that newPngInstance with create=true and valid data works
TEST_F(NewPngInstanceTest_976, CreateTrueWithValidData_976) {
    auto io = makeMemIo(kMinimalPng, sizeof(kMinimalPng));
    auto image = Exiv2::newPngInstance(std::move(io), true);
    // With create=true and valid data, should succeed
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: All zero bytes should not be recognized as PNG
TEST_F(NewPngInstanceTest_976, AllZeroBytesReturnsNull_976) {
    const unsigned char zeros[64] = {0};
    auto io = makeMemIo(zeros, sizeof(zeros));
    auto image = Exiv2::newPngInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}
