#include <gtest/gtest.h>
#include <exiv2/psdimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <cstring>

namespace {

// Helper to create a minimal valid PSD file in memory
std::vector<unsigned char> createMinimalPsdFile() {
    std::vector<unsigned char> data;
    
    // PSD signature: "8BPS"
    data.push_back('8');
    data.push_back('B');
    data.push_back('P');
    data.push_back('S');
    
    // Version: 1 (big-endian uint16)
    data.push_back(0x00);
    data.push_back(0x01);
    
    // Reserved: 6 bytes of zeros
    for (int i = 0; i < 6; i++)
        data.push_back(0x00);
    
    // Number of channels: 3 (big-endian uint16)
    data.push_back(0x00);
    data.push_back(0x03);
    
    // Height: 1 (big-endian uint32)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x01);
    
    // Width: 1 (big-endian uint32)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x01);
    
    // Depth: 8 (big-endian uint16)
    data.push_back(0x00);
    data.push_back(0x08);
    
    // Color mode: RGB = 3 (big-endian uint16)
    data.push_back(0x00);
    data.push_back(0x03);
    
    // Color mode data length: 0 (big-endian uint32)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    
    // Image resources length: 0 (big-endian uint32)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    
    // Layer and mask info length: 0 (big-endian uint32)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    
    // Image data compression: raw = 0 (big-endian uint16)
    data.push_back(0x00);
    data.push_back(0x00);
    
    // Image data: 3 channels * 1 pixel = 3 bytes
    data.push_back(0xFF);
    data.push_back(0x00);
    data.push_back(0x00);
    
    return data;
}

// Helper to create invalid PSD data (wrong signature)
std::vector<unsigned char> createInvalidPsdFile() {
    std::vector<unsigned char> data;
    // Wrong signature
    data.push_back('X');
    data.push_back('X');
    data.push_back('X');
    data.push_back('X');
    // Some padding
    for (int i = 0; i < 50; i++)
        data.push_back(0x00);
    return data;
}

class PsdImageTest_1185 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<Exiv2::PsdImage> createPsdFromData(const std::vector<unsigned char>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::PsdImage>(std::move(io));
    }
};

// Test that mimeType returns the correct MIME type for PSD images
TEST_F(PsdImageTest_1185, MimeTypeReturnsCorrectValue_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_EQ(image->mimeType(), "image/x-photoshop");
}

// Test that mimeType is consistent across multiple calls
TEST_F(PsdImageTest_1185, MimeTypeConsistentAcrossCalls_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    std::string first = image->mimeType();
    std::string second = image->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "image/x-photoshop");
}

// Test that setComment throws (PSD does not support comments)
TEST_F(PsdImageTest_1185, SetCommentThrows_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_THROW(image->setComment("test comment"), Exiv2::Error);
}

// Test that setComment with empty string also throws
TEST_F(PsdImageTest_1185, SetCommentEmptyStringThrows_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_THROW(image->setComment(""), Exiv2::Error);
}

// Test readMetadata on a valid minimal PSD file
TEST_F(PsdImageTest_1185, ReadMetadataValidMinimalPsd_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_NO_THROW(image->readMetadata());
}

// Test readMetadata on an invalid PSD file (wrong signature)
TEST_F(PsdImageTest_1185, ReadMetadataInvalidSignatureThrows_1185) {
    auto data = createInvalidPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test readMetadata on empty data
TEST_F(PsdImageTest_1185, ReadMetadataEmptyDataThrows_1185) {
    std::vector<unsigned char> emptyData;
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    auto image = std::make_unique<Exiv2::PsdImage>(std::move(io));
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test readMetadata on truncated PSD file (only signature, no version)
TEST_F(PsdImageTest_1185, ReadMetadataTruncatedDataThrows_1185) {
    std::vector<unsigned char> truncated = {'8', 'B', 'P', 'S'};
    auto image = createPsdFromData(truncated);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that after readMetadata on minimal PSD, pixel dimensions are accessible
TEST_F(PsdImageTest_1185, ReadMetadataPixelDimensions_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 1u);
    EXPECT_EQ(image->pixelHeight(), 1u);
}

// Test writeMetadata on a valid minimal PSD 
TEST_F(PsdImageTest_1185, WriteMetadataValidPsd_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test writeMetadata without reading first (should throw or handle gracefully)
TEST_F(PsdImageTest_1185, WriteMetadataWithoutReadThrows_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    // Writing without reading first may throw because internal state isn't initialized
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test writeMetadata on empty/invalid data
TEST_F(PsdImageTest_1185, WriteMetadataEmptyDataThrows_1185) {
    std::vector<unsigned char> emptyData;
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    auto image = std::make_unique<Exiv2::PsdImage>(std::move(io));
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test that PsdImage is constructible with MemIo
TEST_F(PsdImageTest_1185, ConstructWithMemIo_1185) {
    auto data = createMinimalPsdFile();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    EXPECT_NO_THROW({
        Exiv2::PsdImage image(std::move(io));
    });
}

// Test that exifData is initially empty before readMetadata
TEST_F(PsdImageTest_1185, ExifDataEmptyBeforeRead_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_TRUE(image->exifData().empty());
}

// Test that iptcData is initially empty before readMetadata
TEST_F(PsdImageTest_1185, IptcDataEmptyBeforeRead_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_TRUE(image->iptcData().empty());
}

// Test that xmpData is initially empty before readMetadata
TEST_F(PsdImageTest_1185, XmpDataEmptyBeforeRead_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_TRUE(image->xmpData().empty());
}

// Test readMetadata on data with wrong version
TEST_F(PsdImageTest_1185, ReadMetadataWrongVersionThrows_1185) {
    auto data = createMinimalPsdFile();
    // Change version from 1 to 99
    data[4] = 0x00;
    data[5] = 0x63;
    auto image = createPsdFromData(data);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that reading metadata twice doesn't cause issues
TEST_F(PsdImageTest_1185, ReadMetadataTwice_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_NO_THROW(image->readMetadata());
}

// Test mimeType does not change after readMetadata
TEST_F(PsdImageTest_1185, MimeTypeUnchangedAfterRead_1185) {
    auto data = createMinimalPsdFile();
    auto image = createPsdFromData(data);
    std::string beforeRead = image->mimeType();
    image->readMetadata();
    std::string afterRead = image->mimeType();
    EXPECT_EQ(beforeRead, afterRead);
}

}  // namespace
