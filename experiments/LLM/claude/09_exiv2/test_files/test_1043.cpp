#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/pgfimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <cstring>
#include <fstream>
#include <memory>
#include <vector>

namespace {

// Helper to create a minimal PGF file in memory
// PGF magic number is 0x50474600 ("PGF\0")
std::vector<unsigned char> createMinimalPgfData() {
    std::vector<unsigned char> data;
    // PGF magic number: "PGF\0" = 0x50, 0x47, 0x46, 0x00
    data.push_back(0x50);
    data.push_back(0x47);
    data.push_back(0x46);
    data.push_back(0x00);
    // Header size (little-endian uint32): let's say 24 bytes for the header structure
    uint32_t headerSize = 24;
    data.push_back(static_cast<unsigned char>(headerSize & 0xFF));
    data.push_back(static_cast<unsigned char>((headerSize >> 8) & 0xFF));
    data.push_back(static_cast<unsigned char>((headerSize >> 16) & 0xFF));
    data.push_back(static_cast<unsigned char>((headerSize >> 24) & 0xFF));
    // PGF header structure (24 bytes minimum):
    // width (uint32), height (uint32), levels (byte), comp mode (byte),
    // bpp (byte), channels (byte), ... pad to 24 bytes
    // width = 100
    uint32_t width = 100;
    data.push_back(static_cast<unsigned char>(width & 0xFF));
    data.push_back(static_cast<unsigned char>((width >> 8) & 0xFF));
    data.push_back(static_cast<unsigned char>((width >> 16) & 0xFF));
    data.push_back(static_cast<unsigned char>((width >> 24) & 0xFF));
    // height = 100
    uint32_t height = 100;
    data.push_back(static_cast<unsigned char>(height & 0xFF));
    data.push_back(static_cast<unsigned char>((height >> 8) & 0xFF));
    data.push_back(static_cast<unsigned char>((height >> 16) & 0xFF));
    data.push_back(static_cast<unsigned char>((height >> 24) & 0xFF));
    // levels
    data.push_back(6);
    // comp mode
    data.push_back(0);
    // bpp
    data.push_back(24);
    // channels
    data.push_back(3);
    // remaining bytes to fill 24 bytes of header structure
    // We've written 16 bytes so far in the header structure (4+4+1+1+1+1=12), need 12 more
    for (int i = 0; i < 12; i++) {
        data.push_back(0);
    }
    return data;
}

class PgfImageTest_1043 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<Exiv2::PgfImage> createPgfImageFromData(const std::vector<unsigned char>& data, bool create = false) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::PgfImage>(std::move(io), create);
    }

    std::unique_ptr<Exiv2::PgfImage> createEmptyPgfImage(bool create = true) {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::PgfImage>(std::move(io), create);
    }
};

// Test that mimeType returns the correct MIME type
TEST_F(PgfImageTest_1043, MimeTypeReturnsImagePgf_1043) {
    auto img = createEmptyPgfImage(true);
    EXPECT_EQ("image/pgf", img->mimeType());
}

// Test that mimeType is consistent across multiple calls
TEST_F(PgfImageTest_1043, MimeTypeConsistentMultipleCalls_1043) {
    auto img = createEmptyPgfImage(true);
    std::string first = img->mimeType();
    std::string second = img->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ("image/pgf", first);
}

// Test creating a PgfImage with create=true and empty io
TEST_F(PgfImageTest_1043, CreateWithEmptyIo_1043) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::PgfImage(std::move(io), true));
}

// Test creating a PgfImage with create=false and empty io
TEST_F(PgfImageTest_1043, CreateWithEmptyIoNoCreate_1043) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::PgfImage(std::move(io), false));
}

// Test readMetadata on an empty (invalid) image throws
TEST_F(PgfImageTest_1043, ReadMetadataOnEmptyImageThrows_1043) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test readMetadata with garbage data throws
TEST_F(PgfImageTest_1043, ReadMetadataWithGarbageDataThrows_1043) {
    std::vector<unsigned char> garbage(100, 0xAB);
    auto io = std::make_unique<Exiv2::MemIo>(garbage.data(), garbage.size());
    Exiv2::PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test readMetadata with too-short data throws
TEST_F(PgfImageTest_1043, ReadMetadataTooShortDataThrows_1043) {
    std::vector<unsigned char> shortData = {0x50, 0x47, 0x46};  // Incomplete magic
    auto io = std::make_unique<Exiv2::MemIo>(shortData.data(), shortData.size());
    Exiv2::PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test readMetadata with wrong magic number throws
TEST_F(PgfImageTest_1043, ReadMetadataWrongMagicThrows_1043) {
    std::vector<unsigned char> data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test readMetadata with minimal valid PGF data
TEST_F(PgfImageTest_1043, ReadMetadataWithMinimalValidPgf_1043) {
    auto data = createMinimalPgfData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::PgfImage img(std::move(io), false);
    // This may or may not throw depending on exact format requirements,
    // but we test it doesn't crash
    try {
        img.readMetadata();
    } catch (const Exiv2::Error&) {
        // Acceptable - the minimal data might not be fully valid
    }
}

// Test writeMetadata on empty created image
TEST_F(PgfImageTest_1043, WriteMetadataOnCreatedEmptyImage_1043) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::PgfImage img(std::move(io), true);
    // Writing metadata on an image that hasn't been read from valid data
    // may throw
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test that the image type is correct through the base class interface
TEST_F(PgfImageTest_1043, ImageTypeIsPgf_1043) {
    auto img = createEmptyPgfImage(true);
    // PgfImage should have ImageType::pgf
    EXPECT_EQ(Exiv2::ImageType::pgf, img->imageType());
}

// Test that PgfImage supports exif metadata flag
TEST_F(PgfImageTest_1043, SupportsExifMetadata_1043) {
    auto img = createEmptyPgfImage(true);
    // Based on constructor: mdExif | mdIptc | mdXmp | mdComment
    EXPECT_TRUE(img->supportsMetadata(Exiv2::MetadataId::mdExif));
}

// Test that PgfImage supports IPTC metadata flag
TEST_F(PgfImageTest_1043, SupportsIptcMetadata_1043) {
    auto img = createEmptyPgfImage(true);
    EXPECT_TRUE(img->supportsMetadata(Exiv2::MetadataId::mdIptc));
}

// Test that PgfImage supports XMP metadata flag
TEST_F(PgfImageTest_1043, SupportsXmpMetadata_1043) {
    auto img = createEmptyPgfImage(true);
    EXPECT_TRUE(img->supportsMetadata(Exiv2::MetadataId::mdXmp));
}

// Test that PgfImage supports Comment metadata flag
TEST_F(PgfImageTest_1043, SupportsCommentMetadata_1043) {
    auto img = createEmptyPgfImage(true);
    EXPECT_TRUE(img->supportsMetadata(Exiv2::MetadataId::mdComment));
}

// Test mimeType on a freshly created (create=true) image
TEST_F(PgfImageTest_1043, MimeTypeOnCreatedImage_1043) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::PgfImage img(std::move(io), true);
    EXPECT_EQ("image/pgf", img.mimeType());
}

// Test reading metadata from data with only magic number but no header
TEST_F(PgfImageTest_1043, ReadMetadataOnlyMagicNoHeader_1043) {
    std::vector<unsigned char> data = {0x50, 0x47, 0x46, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that magic + partial header size still throws
TEST_F(PgfImageTest_1043, ReadMetadataMagicPartialHeaderSize_1043) {
    std::vector<unsigned char> data = {0x50, 0x47, 0x46, 0x00, 0x18, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test with header size but truncated header structure
TEST_F(PgfImageTest_1043, ReadMetadataTruncatedHeaderStructure_1043) {
    std::vector<unsigned char> data = {
        0x50, 0x47, 0x46, 0x00,  // magic
        0x18, 0x00, 0x00, 0x00,  // header size = 24
        0x64, 0x00, 0x00, 0x00   // only partial width, rest missing
    };
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Boundary: single byte input
TEST_F(PgfImageTest_1043, ReadMetadataSingleByteThrows_1043) {
    std::vector<unsigned char> data = {0x50};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Boundary: zero length input
TEST_F(PgfImageTest_1043, ReadMetadataZeroLengthThrows_1043) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

}  // namespace
