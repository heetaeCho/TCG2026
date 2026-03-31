#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/pgfimage.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>

#include <cstring>
#include <memory>
#include <vector>

namespace {

// PGF magic bytes: "PGF" header
// PGF file format starts with a specific header structure
// The magic number for PGF is 0x50474600 ("PGF\0") or similar

class NewPgfInstanceTest_1713 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that creating a PGF image with an empty MemIo and create=false returns nullptr
// because there's no valid PGF data to read
TEST_F(NewPgfInstanceTest_1713, EmptyIoCreateFalse_ReturnsNull_1713) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newPgfInstance(std::move(io), false);
    // An empty IO with create=false should not produce a good image
    EXPECT_EQ(image, nullptr);
}

// Test that creating a PGF image with create=true on an empty MemIo succeeds
TEST_F(NewPgfInstanceTest_1713, EmptyIoCreateTrue_ReturnsValidImage_1713) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newPgfInstance(std::move(io), true);
    // With create=true, the image should be created successfully
    EXPECT_NE(image, nullptr);
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test that passing invalid/random data with create=false returns nullptr
TEST_F(NewPgfInstanceTest_1713, InvalidDataCreateFalse_ReturnsNull_1713) {
    const uint8_t invalidData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    auto io = std::make_unique<Exiv2::MemIo>(invalidData, sizeof(invalidData));
    auto image = Exiv2::newPgfInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that passing random non-PGF data with create=false returns nullptr
TEST_F(NewPgfInstanceTest_1713, RandomNonPgfData_ReturnsNull_1713) {
    std::vector<uint8_t> randomData(1024, 0xAB);
    auto io = std::make_unique<Exiv2::MemIo>(randomData.data(), randomData.size());
    auto image = Exiv2::newPgfInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with JPEG-like magic bytes (not PGF) returns nullptr
TEST_F(NewPgfInstanceTest_1713, JpegMagicBytes_ReturnsNull_1713) {
    const uint8_t jpegData[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46};
    auto io = std::make_unique<Exiv2::MemIo>(jpegData, sizeof(jpegData));
    auto image = Exiv2::newPgfInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with PNG-like magic bytes (not PGF) returns nullptr
TEST_F(NewPgfInstanceTest_1713, PngMagicBytes_ReturnsNull_1713) {
    const uint8_t pngData[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    auto io = std::make_unique<Exiv2::MemIo>(pngData, sizeof(pngData));
    auto image = Exiv2::newPgfInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that create=true returns an image with correct mime type
TEST_F(NewPgfInstanceTest_1713, CreateTrue_MimeType_1713) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newPgfInstance(std::move(io), true);
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->mimeType(), "image/x-pgf");
}

// Test that image created with create=true has zero dimensions initially
TEST_F(NewPgfInstanceTest_1713, CreateTrue_ZeroDimensions_1713) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newPgfInstance(std::move(io), true);
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->pixelWidth(), 0u);
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test with single byte data returns nullptr
TEST_F(NewPgfInstanceTest_1713, SingleByteData_ReturnsNull_1713) {
    const uint8_t singleByte[] = {0x50};
    auto io = std::make_unique<Exiv2::MemIo>(singleByte, sizeof(singleByte));
    auto image = Exiv2::newPgfInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with data that starts with "PGF" but is truncated
TEST_F(NewPgfInstanceTest_1713, TruncatedPgfHeader_ReturnsNull_1713) {
    // "PGF" magic but incomplete header
    const uint8_t truncatedPgf[] = {'P', 'G', 'F'};
    auto io = std::make_unique<Exiv2::MemIo>(truncatedPgf, sizeof(truncatedPgf));
    auto image = Exiv2::newPgfInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that created image's good() returns true
TEST_F(NewPgfInstanceTest_1713, CreateTrue_GoodReturnsTrue_1713) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newPgfInstance(std::move(io), true);
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

// Test that the io reference is accessible after creation
TEST_F(NewPgfInstanceTest_1713, CreateTrue_IoAccessible_1713) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newPgfInstance(std::move(io), true);
    ASSERT_NE(image, nullptr);
    // Just verify that io() doesn't throw
    EXPECT_NO_THROW(image->io());
}

// Test with large invalid data buffer
TEST_F(NewPgfInstanceTest_1713, LargeInvalidData_ReturnsNull_1713) {
    std::vector<uint8_t> largeData(65536, 0xFF);
    auto io = std::make_unique<Exiv2::MemIo>(largeData.data(), largeData.size());
    auto image = Exiv2::newPgfInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with all zeros data
TEST_F(NewPgfInstanceTest_1713, AllZerosData_ReturnsNull_1713) {
    std::vector<uint8_t> zeros(256, 0x00);
    auto io = std::make_unique<Exiv2::MemIo>(zeros.data(), zeros.size());
    auto image = Exiv2::newPgfInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that metadata operations work on a newly created PGF image
TEST_F(NewPgfInstanceTest_1713, CreateTrue_MetadataOps_1713) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newPgfInstance(std::move(io), true);
    ASSERT_NE(image, nullptr);
    
    // Should be able to clear metadata without issues
    EXPECT_NO_THROW(image->clearMetadata());
}

// Test that comment is initially empty on a created image
TEST_F(NewPgfInstanceTest_1713, CreateTrue_EmptyComment_1713) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newPgfInstance(std::move(io), true);
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->comment().empty());
}

}  // namespace
