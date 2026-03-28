#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/pngimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <exiv2/image.hpp>

#include <cstring>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>

using namespace Exiv2;

namespace {

// PNG signature bytes
const unsigned char PNG_SIGNATURE[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

// Helper to create a minimal valid PNG in memory
std::vector<unsigned char> createMinimalPng(uint32_t width = 1, uint32_t height = 1) {
    std::vector<unsigned char> png;

    // PNG signature
    png.insert(png.end(), PNG_SIGNATURE, PNG_SIGNATURE + 8);

    // IHDR chunk
    // Data: width(4) + height(4) + bitdepth(1) + colortype(1) + compression(1) + filter(1) + interlace(1) = 13 bytes
    uint32_t ihdrLen = 13;
    // Length (big endian)
    png.push_back((ihdrLen >> 24) & 0xFF);
    png.push_back((ihdrLen >> 16) & 0xFF);
    png.push_back((ihdrLen >> 8) & 0xFF);
    png.push_back(ihdrLen & 0xFF);
    // Chunk type "IHDR"
    png.push_back('I'); png.push_back('H'); png.push_back('D'); png.push_back('R');
    // Width (big endian)
    png.push_back((width >> 24) & 0xFF);
    png.push_back((width >> 16) & 0xFF);
    png.push_back((width >> 8) & 0xFF);
    png.push_back(width & 0xFF);
    // Height (big endian)
    png.push_back((height >> 24) & 0xFF);
    png.push_back((height >> 16) & 0xFF);
    png.push_back((height >> 8) & 0xFF);
    png.push_back(height & 0xFF);
    // Bit depth, color type, compression, filter, interlace
    png.push_back(8);  // bit depth
    png.push_back(2);  // color type (RGB)
    png.push_back(0);  // compression
    png.push_back(0);  // filter
    png.push_back(0);  // interlace
    // CRC (4 bytes) - we need to compute or just put placeholder
    // For simplicity, compute CRC over chunk type + data
    // We'll use a simple CRC placeholder - the PNG reader in exiv2 may or may not check CRC
    // The readChunk function reads 4 bytes for CRC after chunk data
    uint32_t crc = 0; // placeholder
    png.push_back((crc >> 24) & 0xFF);
    png.push_back((crc >> 16) & 0xFF);
    png.push_back((crc >> 8) & 0xFF);
    png.push_back(crc & 0xFF);

    // IEND chunk
    uint32_t iendLen = 0;
    png.push_back((iendLen >> 24) & 0xFF);
    png.push_back((iendLen >> 16) & 0xFF);
    png.push_back((iendLen >> 8) & 0xFF);
    png.push_back(iendLen & 0xFF);
    png.push_back('I'); png.push_back('E'); png.push_back('N'); png.push_back('D');
    // CRC for IEND
    png.push_back(0); png.push_back(0); png.push_back(0); png.push_back(0);

    return png;
}

// Helper to create a PNG with only signature (no valid chunks after)
std::vector<unsigned char> createPngSignatureOnly() {
    std::vector<unsigned char> png;
    png.insert(png.end(), PNG_SIGNATURE, PNG_SIGNATURE + 8);
    return png;
}

// Helper to write bytes to a temporary file and return the path
std::string writeTempFile(const std::vector<unsigned char>& data, const std::string& suffix = ".png") {
    std::string path = std::tmpnam(nullptr);
    path += suffix;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

// Helper to remove temp file
void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
}

// Create a PNG with a chunk that has length exceeding remaining data
std::vector<unsigned char> createPngWithBadChunkLength() {
    std::vector<unsigned char> png;
    png.insert(png.end(), PNG_SIGNATURE, PNG_SIGNATURE + 8);

    // IHDR with valid structure
    uint32_t ihdrLen = 13;
    png.push_back((ihdrLen >> 24) & 0xFF);
    png.push_back((ihdrLen >> 16) & 0xFF);
    png.push_back((ihdrLen >> 8) & 0xFF);
    png.push_back(ihdrLen & 0xFF);
    png.push_back('I'); png.push_back('H'); png.push_back('D'); png.push_back('R');
    // width=1, height=1
    png.push_back(0); png.push_back(0); png.push_back(0); png.push_back(1);
    png.push_back(0); png.push_back(0); png.push_back(0); png.push_back(1);
    png.push_back(8); png.push_back(2); png.push_back(0); png.push_back(0); png.push_back(0);
    // CRC
    png.push_back(0); png.push_back(0); png.push_back(0); png.push_back(0);

    // A chunk with absurdly large length
    uint32_t badLen = 0xFFFFFF00;
    png.push_back((badLen >> 24) & 0xFF);
    png.push_back((badLen >> 16) & 0xFF);
    png.push_back((badLen >> 8) & 0xFF);
    png.push_back(badLen & 0xFF);
    png.push_back('t'); png.push_back('E'); png.push_back('X'); png.push_back('t');
    // No actual data follows - should trigger error

    return png;
}

// Create non-PNG file
std::vector<unsigned char> createNonPngData() {
    std::vector<unsigned char> data = {'N', 'O', 'T', 'P', 'N', 'G', '!', '!'};
    return data;
}

} // anonymous namespace

class PngImageTest_974 : public ::testing::Test {
protected:
    void TearDown() override {
        for (auto& path : tempFiles_) {
            removeTempFile(path);
        }
    }

    std::string createTempPng(const std::vector<unsigned char>& data) {
        std::string path = writeTempFile(data);
        tempFiles_.push_back(path);
        return path;
    }

    std::vector<std::string> tempFiles_;
};

// Test reading metadata from a valid minimal PNG
TEST_F(PngImageTest_974, ReadMetadataMinimalPng_974) {
    auto pngData = createMinimalPng(100, 200);
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_NO_THROW(img.readMetadata());
    EXPECT_EQ(img.pixelWidth(), 100u);
    EXPECT_EQ(img.pixelHeight(), 200u);
}

// Test that reading metadata from a non-PNG file throws
TEST_F(PngImageTest_974, ReadMetadataNotPng_974) {
    auto nonPngData = createNonPngData();
    std::string path = createTempPng(nonPngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Error);
}

// Test that reading from a non-existent file throws
TEST_F(PngImageTest_974, ReadMetadataFileNotFound_974) {
    auto io = std::make_unique<FileIo>("/nonexistent/path/to/file.png");
    PngImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Error);
}

// Test that reading a PNG with oversized chunk length throws
TEST_F(PngImageTest_974, ReadMetadataBadChunkLength_974) {
    auto pngData = createPngWithBadChunkLength();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Error);
}

// Test that mimeType returns expected value for PNG
TEST_F(PngImageTest_974, MimeType_974) {
    auto pngData = createMinimalPng();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_EQ(img.mimeType(), "image/png");
}

// Test reading metadata with 1x1 pixel dimensions
TEST_F(PngImageTest_974, ReadMetadata1x1_974) {
    auto pngData = createMinimalPng(1, 1);
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_NO_THROW(img.readMetadata());
    EXPECT_EQ(img.pixelWidth(), 1u);
    EXPECT_EQ(img.pixelHeight(), 1u);
}

// Test reading metadata with large pixel dimensions
TEST_F(PngImageTest_974, ReadMetadataLargeDimensions_974) {
    auto pngData = createMinimalPng(4096, 4096);
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_NO_THROW(img.readMetadata());
    EXPECT_EQ(img.pixelWidth(), 4096u);
    EXPECT_EQ(img.pixelHeight(), 4096u);
}

// Test that initial pixel dimensions are zero before reading
TEST_F(PngImageTest_974, InitialPixelDimensionsZero_974) {
    auto pngData = createMinimalPng();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test that exifData is empty for a minimal PNG without EXIF
TEST_F(PngImageTest_974, EmptyExifDataForMinimalPng_974) {
    auto pngData = createMinimalPng();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    img.readMetadata();
    EXPECT_TRUE(img.exifData().empty());
}

// Test that iptcData is empty for a minimal PNG without IPTC
TEST_F(PngImageTest_974, EmptyIptcDataForMinimalPng_974) {
    auto pngData = createMinimalPng();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    img.readMetadata();
    EXPECT_TRUE(img.iptcData().empty());
}

// Test that xmpData is empty for a minimal PNG without XMP
TEST_F(PngImageTest_974, EmptyXmpDataForMinimalPng_974) {
    auto pngData = createMinimalPng();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    img.readMetadata();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test PNG truncated after signature (no chunks)
TEST_F(PngImageTest_974, ReadMetadataTruncatedAfterSignature_974) {
    auto pngData = createPngSignatureOnly();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Error);
}

// Test that the image is created with correct type
TEST_F(PngImageTest_974, ImageTypeIsPng_974) {
    auto pngData = createMinimalPng();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_EQ(img.imageType(), ImageType::png);
}

// Test reading with an empty file
TEST_F(PngImageTest_974, ReadMetadataEmptyFile_974) {
    std::vector<unsigned char> emptyData;
    std::string path = createTempPng(emptyData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Error);
}

// Test that good() returns true for a valid file
TEST_F(PngImageTest_974, GoodReturnsTrueForValidFile_974) {
    auto pngData = createMinimalPng();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_TRUE(img.good());
}

// Test reading from MemIo with valid PNG data
TEST_F(PngImageTest_974, ReadMetadataFromMemIo_974) {
    auto pngData = createMinimalPng(320, 240);

    auto io = std::make_unique<MemIo>(pngData.data(), pngData.size());
    PngImage img(std::move(io), false);

    EXPECT_NO_THROW(img.readMetadata());
    EXPECT_EQ(img.pixelWidth(), 320u);
    EXPECT_EQ(img.pixelHeight(), 240u);
}

// Test reading from MemIo with non-PNG data
TEST_F(PngImageTest_974, ReadMetadataFromMemIoNotPng_974) {
    auto nonPngData = createNonPngData();

    auto io = std::make_unique<MemIo>(nonPngData.data(), nonPngData.size());
    PngImage img(std::move(io), false);

    EXPECT_THROW(img.readMetadata(), Error);
}

// Test reading multiple times resets metadata
TEST_F(PngImageTest_974, ReadMetadataTwiceResetsState_974) {
    auto pngData = createMinimalPng(50, 75);
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    img.readMetadata();
    EXPECT_EQ(img.pixelWidth(), 50u);
    EXPECT_EQ(img.pixelHeight(), 75u);

    // Read again - should still produce same results
    img.readMetadata();
    EXPECT_EQ(img.pixelWidth(), 50u);
    EXPECT_EQ(img.pixelHeight(), 75u);
}

// Test that iccProfile is not defined for minimal PNG
TEST_F(PngImageTest_974, NoIccProfileForMinimalPng_974) {
    auto pngData = createMinimalPng();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    img.readMetadata();
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test with PNG that has an unknown chunk type (should be skipped)
TEST_F(PngImageTest_974, ReadMetadataSkipsUnknownChunks_974) {
    std::vector<unsigned char> png;
    png.insert(png.end(), PNG_SIGNATURE, PNG_SIGNATURE + 8);

    // IHDR
    uint32_t ihdrLen = 13;
    png.push_back((ihdrLen >> 24) & 0xFF);
    png.push_back((ihdrLen >> 16) & 0xFF);
    png.push_back((ihdrLen >> 8) & 0xFF);
    png.push_back(ihdrLen & 0xFF);
    png.push_back('I'); png.push_back('H'); png.push_back('D'); png.push_back('R');
    png.push_back(0); png.push_back(0); png.push_back(0); png.push_back(10); // width=10
    png.push_back(0); png.push_back(0); png.push_back(0); png.push_back(20); // height=20
    png.push_back(8); png.push_back(2); png.push_back(0); png.push_back(0); png.push_back(0);
    png.push_back(0); png.push_back(0); png.push_back(0); png.push_back(0); // CRC

    // Unknown chunk "uNKn" with 4 bytes of data
    uint32_t unknLen = 4;
    png.push_back((unknLen >> 24) & 0xFF);
    png.push_back((unknLen >> 16) & 0xFF);
    png.push_back((unknLen >> 8) & 0xFF);
    png.push_back(unknLen & 0xFF);
    png.push_back('u'); png.push_back('N'); png.push_back('K'); png.push_back('n');
    png.push_back(0xDE); png.push_back(0xAD); png.push_back(0xBE); png.push_back(0xEF);
    png.push_back(0); png.push_back(0); png.push_back(0); png.push_back(0); // CRC

    // IEND
    uint32_t iendLen = 0;
    png.push_back((iendLen >> 24) & 0xFF);
    png.push_back((iendLen >> 16) & 0xFF);
    png.push_back((iendLen >> 8) & 0xFF);
    png.push_back(iendLen & 0xFF);
    png.push_back('I'); png.push_back('E'); png.push_back('N'); png.push_back('D');
    png.push_back(0); png.push_back(0); png.push_back(0); png.push_back(0); // CRC

    std::string path = createTempPng(png);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_NO_THROW(img.readMetadata());
    EXPECT_EQ(img.pixelWidth(), 10u);
    EXPECT_EQ(img.pixelHeight(), 20u);
}

// Test supportsMetadata for PNG
TEST_F(PngImageTest_974, SupportsMetadata_974) {
    auto pngData = createMinimalPng();
    std::string path = createTempPng(pngData);

    auto io = std::make_unique<FileIo>(path);
    PngImage img(std::move(io), false);

    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdExif));
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdIptc));
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdXmp));
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdComment));
}
