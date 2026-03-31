#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/pgfimage.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <cstring>
#include <fstream>
#include <memory>
#include <vector>

using namespace Exiv2;

namespace {

// Helper function to create a minimal valid PGF file in memory
// PGF magic number is "PGF" (0x50, 0x47, 0x46)
// This creates a minimal structure that isPgfType would accept
std::vector<byte> createMinimalPgfData() {
    // PGF file structure:
    // - Magic number: 3 bytes "PGF"
    // - Header size: 4 bytes (little or big endian depending on platform)
    // - PGF header structure with width, height, etc.
    // We need to create something that passes isPgfType check
    
    // A minimal PGF-like structure
    std::vector<byte> data;
    
    // PGF magic bytes
    data.push_back(0x50); // 'P'
    data.push_back(0x47); // 'G'
    data.push_back(0x46); // 'F'
    
    // Version info / magic number area (readPgfMagicNumber reads more)
    // The exact format depends on implementation, but we need enough bytes
    // to pass the checks. Let's create a reasonable structure.
    
    // Additional magic number bytes (typically 8 bytes total for the magic area)
    data.push_back(0x36); // version
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    
    // Header size (4 bytes, little endian) - minimal header
    uint32_t headerSize = 28; // typical minimal PGF header
    data.push_back(static_cast<byte>(headerSize & 0xFF));
    data.push_back(static_cast<byte>((headerSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>((headerSize >> 16) & 0xFF));
    data.push_back(static_cast<byte>((headerSize >> 24) & 0xFF));
    
    // PGF Header structure - width (4 bytes)
    uint32_t width = 100;
    data.push_back(static_cast<byte>(width & 0xFF));
    data.push_back(static_cast<byte>((width >> 8) & 0xFF));
    data.push_back(static_cast<byte>((width >> 16) & 0xFF));
    data.push_back(static_cast<byte>((width >> 24) & 0xFF));
    
    // Height (4 bytes)
    uint32_t height = 100;
    data.push_back(static_cast<byte>(height & 0xFF));
    data.push_back(static_cast<byte>((height >> 8) & 0xFF));
    data.push_back(static_cast<byte>((height >> 16) & 0xFF));
    data.push_back(static_cast<byte>((height >> 24) & 0xFF));
    
    // Fill remaining header bytes
    while (data.size() < headerSize + 8) {
        data.push_back(0x00);
    }
    
    return data;
}

// Create completely invalid data (not a PGF file at all)
std::vector<byte> createNonPgfData() {
    std::vector<byte> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                               0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    return data;
}

// Create data that looks like JPEG (definitely not PGF)
std::vector<byte> createJpegLikeData() {
    std::vector<byte> data = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
                               0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01};
    return data;
}

} // namespace

class PgfImageTest_1711 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that creating a PgfImage with valid BasicIo works
TEST_F(PgfImageTest_1711, ConstructionWithMemIo_1711) {
    auto data = createMinimalPgfData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    ASSERT_NO_THROW(PgfImage pgf(std::move(io), false));
}

// Test that creating a PgfImage for creation works
TEST_F(PgfImageTest_1711, ConstructionForCreate_1711) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(PgfImage pgf(std::move(io), true));
}

// Test readMetadata with non-PGF data throws error
TEST_F(PgfImageTest_1711, ReadMetadataWithNonPgfData_1711) {
    auto data = createNonPgfData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    PgfImage pgf(std::move(io), false);
    EXPECT_THROW(pgf.readMetadata(), Error);
}

// Test readMetadata with JPEG-like data throws kerNotAnImage
TEST_F(PgfImageTest_1711, ReadMetadataWithJpegData_1711) {
    auto data = createJpegLikeData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    PgfImage pgf(std::move(io), false);
    EXPECT_THROW(pgf.readMetadata(), Error);
}

// Test readMetadata with empty data throws
TEST_F(PgfImageTest_1711, ReadMetadataWithEmptyData_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), false);
    EXPECT_THROW(pgf.readMetadata(), Error);
}

// Test that mimeType returns correct MIME type for PGF
TEST_F(PgfImageTest_1711, MimeTypeReturnsPgf_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    std::string mime = pgf.mimeType();
    EXPECT_EQ(mime, "image/pgf");
}

// Test that imageType returns PGF
TEST_F(PgfImageTest_1711, ImageTypeIsPgf_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    EXPECT_EQ(pgf.imageType(), ImageType::pgf);
}

// Test that after construction, metadata containers are accessible
TEST_F(PgfImageTest_1711, MetadataAccessible_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    EXPECT_TRUE(pgf.exifData().empty());
    EXPECT_TRUE(pgf.iptcData().empty());
    EXPECT_TRUE(pgf.xmpData().empty());
}

// Test that pixel dimensions are zero before reading metadata
TEST_F(PgfImageTest_1711, PixelDimensionsZeroBeforeRead_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    EXPECT_EQ(pgf.pixelWidth(), 0u);
    EXPECT_EQ(pgf.pixelHeight(), 0u);
}

// Test readMetadata with very small data (just a few bytes)
TEST_F(PgfImageTest_1711, ReadMetadataWithTooSmallData_1711) {
    std::vector<byte> data = {0x50, 0x47, 0x46}; // Just "PGF"
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    PgfImage pgf(std::move(io), false);
    EXPECT_THROW(pgf.readMetadata(), Error);
}

// Test readMetadata with single byte data
TEST_F(PgfImageTest_1711, ReadMetadataWithSingleByte_1711) {
    std::vector<byte> data = {0x50};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    PgfImage pgf(std::move(io), false);
    EXPECT_THROW(pgf.readMetadata(), Error);
}

// Test writeMetadata on empty/new image
TEST_F(PgfImageTest_1711, WriteMetadataOnNewImage_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    // Writing metadata on a newly created (empty) image should throw
    // because there's no valid PGF data to write to
    EXPECT_THROW(pgf.writeMetadata(), Error);
}

// Test that good() returns appropriate value
TEST_F(PgfImageTest_1711, GoodOnNewImage_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    // good() depends on IO state
    // For a MemIo that's not been opened for read, behavior may vary
    EXPECT_NO_THROW(pgf.good());
}

// Test that metadata can be set and cleared
TEST_F(PgfImageTest_1711, SetAndClearExifData_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    ExifData exifData;
    pgf.setExifData(exifData);
    EXPECT_TRUE(pgf.exifData().empty());
    
    pgf.clearExifData();
    EXPECT_TRUE(pgf.exifData().empty());
}

// Test that metadata can be set and cleared for IPTC
TEST_F(PgfImageTest_1711, SetAndClearIptcData_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    IptcData iptcData;
    pgf.setIptcData(iptcData);
    EXPECT_TRUE(pgf.iptcData().empty());
    
    pgf.clearIptcData();
    EXPECT_TRUE(pgf.iptcData().empty());
}

// Test that metadata can be set and cleared for XMP
TEST_F(PgfImageTest_1711, SetAndClearXmpData_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    XmpData xmpData;
    pgf.setXmpData(xmpData);
    EXPECT_TRUE(pgf.xmpData().empty());
    
    pgf.clearXmpData();
    EXPECT_TRUE(pgf.xmpData().empty());
}

// Test clearMetadata
TEST_F(PgfImageTest_1711, ClearMetadata_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    EXPECT_NO_THROW(pgf.clearMetadata());
    EXPECT_TRUE(pgf.exifData().empty());
    EXPECT_TRUE(pgf.iptcData().empty());
    EXPECT_TRUE(pgf.xmpData().empty());
}

// Test supportsMetadata
TEST_F(PgfImageTest_1711, SupportsExifMetadata_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    // PGF supports Exif, IPTC, XMP, and Comment metadata
    EXPECT_TRUE(pgf.supportsMetadata(MetadataId::mdExif));
    EXPECT_TRUE(pgf.supportsMetadata(MetadataId::mdIptc));
    EXPECT_TRUE(pgf.supportsMetadata(MetadataId::mdXmp));
    EXPECT_TRUE(pgf.supportsMetadata(MetadataId::mdComment));
}

// Test reading truncated PGF header
TEST_F(PgfImageTest_1711, ReadMetadataTruncatedHeader_1711) {
    // PGF magic followed by truncated header
    std::vector<byte> data = {0x50, 0x47, 0x46, 0x36, 0x00, 0x00};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    PgfImage pgf(std::move(io), false);
    EXPECT_THROW(pgf.readMetadata(), Error);
}

// Test with corrupted PGF header size (very large value)
TEST_F(PgfImageTest_1711, ReadMetadataCorruptedHeaderSize_1711) {
    std::vector<byte> data(64, 0);
    // PGF magic
    data[0] = 0x50;
    data[1] = 0x47;
    data[2] = 0x46;
    data[3] = 0x36; // version
    
    // Set an absurdly large header size
    data[8] = 0xFF;
    data[9] = 0xFF;
    data[10] = 0xFF;
    data[11] = 0xFF;
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    PgfImage pgf(std::move(io), false);
    EXPECT_THROW(pgf.readMetadata(), Error);
}

// Test io() accessor
TEST_F(PgfImageTest_1711, IoAccessor_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    EXPECT_NO_THROW(pgf.io());
}

// Test comment accessor
TEST_F(PgfImageTest_1711, CommentAccessor_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    EXPECT_TRUE(pgf.comment().empty());
}

// Test setComment
TEST_F(PgfImageTest_1711, SetComment_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    pgf.setComment("Test comment");
    EXPECT_EQ(pgf.comment(), "Test comment");
}

// Test clearComment
TEST_F(PgfImageTest_1711, ClearComment_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    pgf.setComment("Test comment");
    pgf.clearComment();
    EXPECT_TRUE(pgf.comment().empty());
}

// Test with data that has PGF magic but zero-length remaining
TEST_F(PgfImageTest_1711, ReadMetadataWithInsufficientData_1711) {
    // Create data with PGF-like start but not enough for full header
    std::vector<byte> data(12, 0);
    data[0] = 0x50; // P
    data[1] = 0x47; // G
    data[2] = 0x46; // F
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    PgfImage pgf(std::move(io), false);
    EXPECT_THROW(pgf.readMetadata(), Error);
}

// Test byte order
TEST_F(PgfImageTest_1711, ByteOrder_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    // Byte order should be accessible
    EXPECT_NO_THROW(pgf.byteOrder());
}

// Test ICC profile initially not defined
TEST_F(PgfImageTest_1711, IccProfileNotDefined_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    EXPECT_FALSE(pgf.iccProfileDefined());
}

// Test xmpPacket accessor on new image
TEST_F(PgfImageTest_1711, XmpPacketEmpty_1711) {
    auto io = std::make_unique<MemIo>();
    PgfImage pgf(std::move(io), true);
    
    EXPECT_TRUE(pgf.xmpPacket().empty());
}
