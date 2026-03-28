#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <sstream>
#include <fstream>
#include <cstring>

// Include the necessary Exiv2 headers
#include <exiv2/pngimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

namespace {

// Helper function to create a minimal valid PNG file in memory
std::vector<unsigned char> createMinimalPng() {
    // Minimal PNG: signature + IHDR + IEND
    std::vector<unsigned char> png;
    
    // PNG signature
    unsigned char signature[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    png.insert(png.end(), signature, signature + 8);
    
    // IHDR chunk
    // Length: 13 bytes
    unsigned char ihdr_length[] = {0x00, 0x00, 0x00, 0x0D};
    png.insert(png.end(), ihdr_length, ihdr_length + 4);
    
    // Type: IHDR
    unsigned char ihdr_type[] = {0x49, 0x48, 0x44, 0x52};
    png.insert(png.end(), ihdr_type, ihdr_type + 4);
    
    // Width: 1, Height: 1, Bit depth: 8, Color type: 2 (RGB), 
    // Compression: 0, Filter: 0, Interlace: 0
    unsigned char ihdr_data[] = {
        0x00, 0x00, 0x00, 0x01,  // width
        0x00, 0x00, 0x00, 0x01,  // height
        0x08,                     // bit depth
        0x02,                     // color type (RGB)
        0x00,                     // compression method
        0x00,                     // filter method
        0x00                      // interlace method
    };
    png.insert(png.end(), ihdr_data, ihdr_data + 13);
    
    // CRC for IHDR (precomputed for this specific IHDR)
    unsigned char ihdr_crc[] = {0x1E, 0x92, 0x6E, 0x05};
    png.insert(png.end(), ihdr_crc, ihdr_crc + 4);
    
    // IDAT chunk (minimal compressed data for 1x1 RGB image)
    unsigned char idat_length[] = {0x00, 0x00, 0x00, 0x0C};
    png.insert(png.end(), idat_length, idat_length + 4);
    
    unsigned char idat_type[] = {0x49, 0x44, 0x41, 0x54};
    png.insert(png.end(), idat_type, idat_type + 4);
    
    // zlib compressed data for a single row: filter byte (0) + 3 bytes RGB
    unsigned char idat_data[] = {0x08, 0xD7, 0x63, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01};
    png.insert(png.end(), idat_data, idat_data + 12);
    
    // CRC for IDAT
    unsigned char idat_crc[] = {0x27, 0x06, 0x10, 0x20};
    png.insert(png.end(), idat_crc, idat_crc + 4);
    
    // IEND chunk
    unsigned char iend_length[] = {0x00, 0x00, 0x00, 0x00};
    png.insert(png.end(), iend_length, iend_length + 4);
    
    unsigned char iend_type[] = {0x49, 0x45, 0x4E, 0x44};
    png.insert(png.end(), iend_type, iend_type + 4);
    
    // CRC for IEND
    unsigned char iend_crc[] = {0xAE, 0x42, 0x60, 0x82};
    png.insert(png.end(), iend_crc, iend_crc + 4);
    
    return png;
}

// Helper to create a MemIo from PNG data
std::unique_ptr<Exiv2::MemIo> createPngMemIo() {
    auto pngData = createMinimalPng();
    auto memIo = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    return memIo;
}

// Helper to create a MemIo with invalid data
std::unique_ptr<Exiv2::MemIo> createInvalidMemIo() {
    unsigned char garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    auto memIo = std::make_unique<Exiv2::MemIo>(garbage, sizeof(garbage));
    return memIo;
}

// Helper to create an empty MemIo
std::unique_ptr<Exiv2::MemIo> createEmptyMemIo() {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    return memIo;
}

} // anonymous namespace

class PngImageTest_967 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that mimeType returns the correct MIME type for PNG images
TEST_F(PngImageTest_967, MimeTypeReturnsPngMime_967) {
    auto io = createPngMemIo();
    Exiv2::PngImage img(std::move(io), false);
    EXPECT_EQ(img.mimeType(), "image/png");
}

// Test creating a PngImage with create=false (open existing)
TEST_F(PngImageTest_967, ConstructWithCreateFalse_967) {
    auto io = createPngMemIo();
    EXPECT_NO_THROW({
        Exiv2::PngImage img(std::move(io), false);
    });
}

// Test creating a PngImage with create=true (create new)
TEST_F(PngImageTest_967, ConstructWithCreateTrue_967) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW({
        Exiv2::PngImage img(std::move(io), true);
    });
}

// Test readMetadata on a valid minimal PNG
TEST_F(PngImageTest_967, ReadMetadataOnMinimalPng_967) {
    auto pngData = createMinimalPng();
    auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    Exiv2::PngImage img(std::move(io), false);
    
    // Should not throw on a valid PNG
    EXPECT_NO_THROW(img.readMetadata());
}

// Test readMetadata on empty IO throws
TEST_F(PngImageTest_967, ReadMetadataOnEmptyIoThrows_967) {
    auto io = createEmptyMemIo();
    Exiv2::PngImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test readMetadata on invalid (non-PNG) data throws
TEST_F(PngImageTest_967, ReadMetadataOnInvalidDataThrows_967) {
    auto io = createInvalidMemIo();
    Exiv2::PngImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test writeMetadata on a valid PNG
TEST_F(PngImageTest_967, WriteMetadataOnValidPng_967) {
    auto pngData = createMinimalPng();
    auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    Exiv2::PngImage img(std::move(io), false);
    
    // Read first, then write
    EXPECT_NO_THROW(img.readMetadata());
    EXPECT_NO_THROW(img.writeMetadata());
}

// Test writeMetadata on empty IO throws
TEST_F(PngImageTest_967, WriteMetadataOnEmptyIoThrows_967) {
    auto io = createEmptyMemIo();
    Exiv2::PngImage img(std::move(io), false);
    
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test mimeType consistency - calling it multiple times returns same result
TEST_F(PngImageTest_967, MimeTypeConsistency_967) {
    auto io = createPngMemIo();
    Exiv2::PngImage img(std::move(io), false);
    
    std::string first = img.mimeType();
    std::string second = img.mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "image/png");
}

// Test printStructure with option none
TEST_F(PngImageTest_967, PrintStructureNone_967) {
    auto pngData = createMinimalPng();
    auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    Exiv2::PngImage img(std::move(io), false);
    
    std::ostringstream oss;
    EXPECT_NO_THROW(img.printStructure(oss, Exiv2::kpsNone, 0));
}

// Test printStructure with basic structure option on valid PNG
TEST_F(PngImageTest_967, PrintStructureBasic_967) {
    auto pngData = createMinimalPng();
    auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    Exiv2::PngImage img(std::move(io), false);
    
    std::ostringstream oss;
    EXPECT_NO_THROW(img.printStructure(oss, Exiv2::kpsBasic, 0));
}

// Test that reading metadata from PNG with only signature but truncated throws
TEST_F(PngImageTest_967, ReadMetadataTruncatedPngThrows_967) {
    // Only the PNG signature, no chunks
    unsigned char signature[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    auto io = std::make_unique<Exiv2::MemIo>(signature, sizeof(signature));
    Exiv2::PngImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test creating PngImage with create=true produces writable image
TEST_F(PngImageTest_967, CreateNewPngImage_967) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::PngImage img(std::move(io), true);
    
    EXPECT_EQ(img.mimeType(), "image/png");
}

// Test that single-byte data fails as invalid PNG
TEST_F(PngImageTest_967, ReadMetadataSingleByteThrows_967) {
    unsigned char singleByte[] = {0x89};
    auto io = std::make_unique<Exiv2::MemIo>(singleByte, 1);
    Exiv2::PngImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test printStructure on empty/invalid IO
TEST_F(PngImageTest_967, PrintStructureOnEmptyIo_967) {
    auto io = createEmptyMemIo();
    Exiv2::PngImage img(std::move(io), false);
    
    std::ostringstream oss;
    // Depending on the option, this may or may not throw
    // kpsNone typically does nothing
    EXPECT_NO_THROW(img.printStructure(oss, Exiv2::kpsNone, 0));
}

// Test that writeMetadata on invalid data throws
TEST_F(PngImageTest_967, WriteMetadataOnInvalidDataThrows_967) {
    auto io = createInvalidMemIo();
    Exiv2::PngImage img(std::move(io), false);
    
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test printStructure with depth parameter
TEST_F(PngImageTest_967, PrintStructureWithDepth_967) {
    auto pngData = createMinimalPng();
    auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    Exiv2::PngImage img(std::move(io), false);
    
    std::ostringstream oss;
    EXPECT_NO_THROW(img.printStructure(oss, Exiv2::kpsBasic, 5));
}

// Test that after readMetadata, exifData is accessible (even if empty)
TEST_F(PngImageTest_967, ExifDataAccessibleAfterRead_967) {
    auto pngData = createMinimalPng();
    auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    Exiv2::PngImage img(std::move(io), false);
    
    EXPECT_NO_THROW(img.readMetadata());
    // Minimal PNG has no EXIF data, so exifData should be empty
    EXPECT_TRUE(img.exifData().empty());
}

// Test that after readMetadata, iptcData is accessible (even if empty)
TEST_F(PngImageTest_967, IptcDataAccessibleAfterRead_967) {
    auto pngData = createMinimalPng();
    auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    Exiv2::PngImage img(std::move(io), false);
    
    EXPECT_NO_THROW(img.readMetadata());
    EXPECT_TRUE(img.iptcData().empty());
}

// Test that after readMetadata, xmpData is accessible (even if empty)
TEST_F(PngImageTest_967, XmpDataAccessibleAfterRead_967) {
    auto pngData = createMinimalPng();
    auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
    Exiv2::PngImage img(std::move(io), false);
    
    EXPECT_NO_THROW(img.readMetadata());
    EXPECT_TRUE(img.xmpData().empty());
}
