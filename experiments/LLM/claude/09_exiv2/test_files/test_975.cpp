#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/pngimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <memory>
#include <fstream>
#include <cstring>

using namespace Exiv2;

// Minimal valid PNG file data
static const unsigned char kMinimalPng[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,  // PNG signature
    // IHDR chunk
    0x00, 0x00, 0x00, 0x0D,  // chunk length = 13
    0x49, 0x48, 0x44, 0x52,  // "IHDR"
    0x00, 0x00, 0x00, 0x01,  // width = 1
    0x00, 0x00, 0x00, 0x01,  // height = 1
    0x08,                     // bit depth = 8
    0x02,                     // color type = 2 (RGB)
    0x00,                     // compression method
    0x00,                     // filter method
    0x00,                     // interlace method
    0x1E, 0x92, 0x6E, 0x05,  // CRC for IHDR
    // IDAT chunk
    0x00, 0x00, 0x00, 0x0C,  // chunk length = 12
    0x49, 0x44, 0x41, 0x54,  // "IDAT"
    0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x01,  // compressed data
    0xE2, 0x21, 0xBC, 0x33,  // CRC for IDAT
    // IEND chunk
    0x00, 0x00, 0x00, 0x00,  // chunk length = 0
    0x49, 0x45, 0x4E, 0x44,  // "IEND"
    0xAE, 0x42, 0x60, 0x82   // CRC for IEND
};

class PngImageTest_975 : public ::testing::Test {
protected:
    std::unique_ptr<PngImage> createPngImageFromData(const unsigned char* data, size_t size) {
        auto io = std::make_unique<MemIo>(data, size);
        return std::make_unique<PngImage>(std::move(io), false);
    }

    std::unique_ptr<PngImage> createEmptyPngImage() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<PngImage>(std::move(io), true);
    }
};

// Test that PngImage can be constructed with create=true
TEST_F(PngImageTest_975, ConstructWithCreate_975) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(PngImage img(std::move(io), true));
}

// Test that PngImage can be constructed with create=false
TEST_F(PngImageTest_975, ConstructWithoutCreate_975) {
    auto io = std::make_unique<MemIo>(kMinimalPng, sizeof(kMinimalPng));
    ASSERT_NO_THROW(PngImage img(std::move(io), false));
}

// Test that mimeType returns "image/png"
TEST_F(PngImageTest_975, MimeType_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    EXPECT_EQ(img->mimeType(), "image/png");
}

// Test readMetadata on a valid minimal PNG
TEST_F(PngImageTest_975, ReadMetadataValidPng_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    ASSERT_NO_THROW(img->readMetadata());
}

// Test readMetadata on empty data throws
TEST_F(PngImageTest_975, ReadMetadataEmptyDataThrows_975) {
    auto io = std::make_unique<MemIo>();
    auto img = std::make_unique<PngImage>(std::move(io), false);
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test readMetadata on invalid/corrupt data throws
TEST_F(PngImageTest_975, ReadMetadataInvalidDataThrows_975) {
    const unsigned char garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    auto img = createPngImageFromData(garbage, sizeof(garbage));
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test writeMetadata on a valid PNG after reading
TEST_F(PngImageTest_975, WriteMetadataAfterRead_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    ASSERT_NO_THROW(img->readMetadata());
    ASSERT_NO_THROW(img->writeMetadata());
}

// Test writeMetadata on empty MemIo (no valid PNG data) should throw
TEST_F(PngImageTest_975, WriteMetadataEmptyThrows_975) {
    auto io = std::make_unique<MemIo>();
    auto img = std::make_unique<PngImage>(std::move(io), false);
    EXPECT_THROW(img->writeMetadata(), Error);
}

// Test that after readMetadata, pixelWidth and pixelHeight are set correctly for minimal 1x1 PNG
TEST_F(PngImageTest_975, PixelDimensionsAfterRead_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    EXPECT_EQ(img->pixelWidth(), 1u);
    EXPECT_EQ(img->pixelHeight(), 1u);
}

// Test good() returns true for valid PNG
TEST_F(PngImageTest_975, GoodReturnsTrueForValidIo_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    EXPECT_TRUE(img->good());
}

// Test that exifData is initially empty
TEST_F(PngImageTest_975, ExifDataInitiallyEmpty_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    EXPECT_TRUE(img->exifData().empty());
}

// Test that iptcData is initially empty
TEST_F(PngImageTest_975, IptcDataInitiallyEmpty_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    EXPECT_TRUE(img->iptcData().empty());
}

// Test that xmpData is initially empty for a minimal PNG
TEST_F(PngImageTest_975, XmpDataInitiallyEmpty_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    EXPECT_TRUE(img->xmpData().empty());
}

// Test setting and clearing comment
TEST_F(PngImageTest_975, SetAndClearComment_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    img->setComment("Test comment");
    EXPECT_EQ(img->comment(), "Test comment");
    img->clearComment();
    EXPECT_TRUE(img->comment().empty());
}

// Test that clearMetadata clears everything
TEST_F(PngImageTest_975, ClearMetadata_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    img->setComment("Hello");
    img->clearMetadata();
    EXPECT_TRUE(img->comment().empty());
    EXPECT_TRUE(img->exifData().empty());
    EXPECT_TRUE(img->iptcData().empty());
    EXPECT_TRUE(img->xmpData().empty());
}

// Test that readMetadata on data with only the PNG signature (truncated) throws
TEST_F(PngImageTest_975, ReadMetadataTruncatedPngThrows_975) {
    const unsigned char pngSig[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    auto img = createPngImageFromData(pngSig, sizeof(pngSig));
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test writeMetadata after setting a comment on a valid PNG
TEST_F(PngImageTest_975, WriteMetadataWithComment_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    img->setComment("My test comment");
    ASSERT_NO_THROW(img->writeMetadata());
    // After write, re-read to verify comment persisted
    img->readMetadata();
    EXPECT_EQ(img->comment(), "My test comment");
}

// Test the io() accessor returns a valid reference
TEST_F(PngImageTest_975, IoAccessor_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    const BasicIo& io = img->io();
    EXPECT_EQ(io.size(), sizeof(kMinimalPng));
}

// Test printStructure doesn't crash on a valid PNG
TEST_F(PngImageTest_975, PrintStructureNoThrow_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    std::ostringstream oss;
    ASSERT_NO_THROW(img->printStructure(oss, kpsBasic, 0));
}

// Test that writeMetadata preserves image integrity (can be re-read after write)
TEST_F(PngImageTest_975, WriteAndRereadPreservesIntegrity_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    img->writeMetadata();
    // Re-read should still work
    ASSERT_NO_THROW(img->readMetadata());
    EXPECT_EQ(img->pixelWidth(), 1u);
    EXPECT_EQ(img->pixelHeight(), 1u);
}

// Test that setExifData and clearExifData work
TEST_F(PngImageTest_975, SetAndClearExifData_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    ExifData exif;
    img->setExifData(exif);
    img->clearExifData();
    EXPECT_TRUE(img->exifData().empty());
}

// Test that setIptcData and clearIptcData work
TEST_F(PngImageTest_975, SetAndClearIptcData_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    IptcData iptc;
    img->setIptcData(iptc);
    img->clearIptcData();
    EXPECT_TRUE(img->iptcData().empty());
}

// Test that setXmpData and clearXmpData work
TEST_F(PngImageTest_975, SetAndClearXmpData_975) {
    auto img = createPngImageFromData(kMinimalPng, sizeof(kMinimalPng));
    img->readMetadata();
    XmpData xmp;
    img->setXmpData(xmp);
    img->clearXmpData();
    EXPECT_TRUE(img->xmpData().empty());
}

// Test readMetadata with data that has wrong magic bytes
TEST_F(PngImageTest_975, ReadMetadataWrongMagicThrows_975) {
    unsigned char badData[sizeof(kMinimalPng)];
    std::memcpy(badData, kMinimalPng, sizeof(kMinimalPng));
    // Corrupt the PNG signature
    badData[0] = 0x00;
    badData[1] = 0x00;
    auto img = createPngImageFromData(badData, sizeof(badData));
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test that creating PngImage with create=true produces valid writable image
TEST_F(PngImageTest_975, CreateNewPngImage_975) {
    auto io = std::make_unique<MemIo>();
    auto img = std::make_unique<PngImage>(std::move(io), true);
    EXPECT_TRUE(img->good());
    EXPECT_EQ(img->mimeType(), "image/png");
}
