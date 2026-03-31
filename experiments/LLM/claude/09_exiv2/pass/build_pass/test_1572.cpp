#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"
#include "exiv2/xmp_exiv2.hpp"

using namespace Exiv2;

// Helper to create a MemIo with specific binary content for fileProperties
// fileProperties reads:
//   16 bytes: GUID (FileID)
//   8 bytes: FileLength (QWORD)
//   8 bytes: CreationDate (QWORD)
//   8 bytes: DataPackets (QWORD)
//   8 bytes: duration (QWORD)
//   8 bytes: SendDuration (QWORD)
//   8 bytes: Preroll (QWORD)
//   4 bytes: Flags (ignored)
//   4 bytes: MinDataPacketSize (ignored)
//   4 bytes: MaxDataPacketSize (ignored)
//   4 bytes: MaxBitRate (DWORD)
// Total: 16 + 6*8 + 3*4 + 4 = 16 + 48 + 12 + 4 = 80 bytes

static std::vector<uint8_t> createFilePropertiesData() {
    std::vector<uint8_t> data(80, 0);
    
    // FileID GUID (16 bytes) - some recognizable pattern
    for (int i = 0; i < 16; i++) {
        data[i] = static_cast<uint8_t>(i + 1);
    }
    
    // FileLength (8 bytes, little-endian QWORD) = 1024
    data[16] = 0x00;
    data[17] = 0x04;
    data[18] = 0x00;
    data[19] = 0x00;
    data[20] = 0x00;
    data[21] = 0x00;
    data[22] = 0x00;
    data[23] = 0x00;
    
    // CreationDate (8 bytes) = 500
    data[24] = 0xF4;
    data[25] = 0x01;
    data[26] = 0x00;
    data[27] = 0x00;
    data[28] = 0x00;
    data[29] = 0x00;
    data[30] = 0x00;
    data[31] = 0x00;
    
    // DataPackets (8 bytes) = 100
    data[32] = 0x64;
    data[33] = 0x00;
    data[34] = 0x00;
    data[35] = 0x00;
    data[36] = 0x00;
    data[37] = 0x00;
    data[38] = 0x00;
    data[39] = 0x00;
    
    // duration (8 bytes) = 30000000 (3 seconds in 100ns units)
    data[40] = 0x80;
    data[41] = 0xC9;
    data[42] = 0xC9;
    data[43] = 0x01;
    data[44] = 0x00;
    data[45] = 0x00;
    data[46] = 0x00;
    data[47] = 0x00;
    
    // SendDuration (8 bytes) = 30000000
    data[48] = 0x80;
    data[49] = 0xC9;
    data[50] = 0xC9;
    data[51] = 0x01;
    data[52] = 0x00;
    data[53] = 0x00;
    data[54] = 0x00;
    data[55] = 0x00;
    
    // Preroll (8 bytes) = 2000
    data[56] = 0xD0;
    data[57] = 0x07;
    data[58] = 0x00;
    data[59] = 0x00;
    data[60] = 0x00;
    data[61] = 0x00;
    data[62] = 0x00;
    data[63] = 0x00;
    
    // Flags (4 bytes, ignored)
    data[64] = 0x00;
    data[65] = 0x00;
    data[66] = 0x00;
    data[67] = 0x00;
    
    // MinDataPacketSize (4 bytes, ignored)
    data[68] = 0x00;
    data[69] = 0x00;
    data[70] = 0x00;
    data[71] = 0x00;
    
    // MaxDataPacketSize (4 bytes, ignored)
    data[72] = 0x00;
    data[73] = 0x00;
    data[74] = 0x00;
    data[75] = 0x00;
    
    // MaxBitRate (4 bytes, DWORD) = 128000
    data[76] = 0x00;
    data[77] = 0xF4;
    data[78] = 0x01;
    data[79] = 0x00;
    
    return data;
}

// We need a valid ASF file header to construct AsfVideo properly.
// The ASF Header Object GUID is: 75B22630-668E-11CF-A6D9-00AA0062CE6C
// We'll build a minimal ASF file that can be opened.

// Build a complete minimal ASF file buffer for testing readMetadata with file properties
static std::vector<uint8_t> buildMinimalAsfWithFileProperties() {
    // ASF Header Object GUID
    const uint8_t headerGuid[] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    
    // ASF File Properties Object GUID
    const uint8_t filePropsGuid[] = {
        0xA1, 0xDC, 0xAB, 0x8C, 0x47, 0xA9, 0xCF, 0x11,
        0x8E, 0xE4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65
    };
    
    std::vector<uint8_t> fileData;
    
    // We'll construct the file properties object
    // Object: GUID(16) + Size(8) + data(80) = 104 bytes
    size_t filePropObjSize = 16 + 8 + 80;
    
    // Header Object: GUID(16) + Size(8) + NumHeaders(4) + Reserved(2) = 30 + child objects
    size_t headerObjSize = 30 + filePropObjSize;
    
    // Header Object GUID
    fileData.insert(fileData.end(), headerGuid, headerGuid + 16);
    
    // Header Object Size (8 bytes, little-endian)
    for (int i = 0; i < 8; i++) {
        fileData.push_back(static_cast<uint8_t>((headerObjSize >> (i * 8)) & 0xFF));
    }
    
    // Number of header objects (4 bytes, little-endian) = 1
    fileData.push_back(0x01);
    fileData.push_back(0x00);
    fileData.push_back(0x00);
    fileData.push_back(0x00);
    
    // Reserved1 (1 byte) + Reserved2 (1 byte)
    fileData.push_back(0x01);
    fileData.push_back(0x02);
    
    // File Properties Object
    // GUID
    fileData.insert(fileData.end(), filePropsGuid, filePropsGuid + 16);
    
    // Size (8 bytes, little-endian)
    for (int i = 0; i < 8; i++) {
        fileData.push_back(static_cast<uint8_t>((filePropObjSize >> (i * 8)) & 0xFF));
    }
    
    // File Properties data (80 bytes)
    auto propData = createFilePropertiesData();
    fileData.insert(fileData.end(), propData.begin(), propData.end());
    
    return fileData;
}

class AsfVideoTest_1572 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test: AsfVideo constructor with valid IO
TEST_F(AsfVideoTest_1572, ConstructorWithValidIo_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    ASSERT_NO_THROW(AsfVideo video(std::move(io)));
}

// Test: mimeType returns correct type
TEST_F(AsfVideoTest_1572, MimeTypeReturnsCorrectValue_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_EQ(video.mimeType(), "video/x-ms-asf");
}

// Test: readMetadata populates XMP data with file properties
TEST_F(AsfVideoTest_1572, ReadMetadataPopulatesFileProperties_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    ASSERT_NO_THROW(video.readMetadata());
    
    XmpData& xmp = video.xmpData();
    
    // Check that FileID was populated
    auto it = xmp.findKey(XmpKey("Xmp.video.FileID"));
    EXPECT_NE(it, xmp.end());
    
    // Check that FileLength was populated
    it = xmp.findKey(XmpKey("Xmp.video.FileLength"));
    EXPECT_NE(it, xmp.end());
    
    // Check that duration was populated
    it = xmp.findKey(XmpKey("Xmp.video.duration"));
    EXPECT_NE(it, xmp.end());
    
    // Check that MaxBitRate was populated
    it = xmp.findKey(XmpKey("Xmp.video.MaxBitRate"));
    EXPECT_NE(it, xmp.end());
}

// Test: readMetadata populates CreationDate
TEST_F(AsfVideoTest_1572, ReadMetadataPopulatesCreationDate_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    ASSERT_NO_THROW(video.readMetadata());
    
    XmpData& xmp = video.xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.CreationDate"));
    EXPECT_NE(it, xmp.end());
}

// Test: readMetadata populates DataPackets
TEST_F(AsfVideoTest_1572, ReadMetadataPopulatesDataPackets_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    ASSERT_NO_THROW(video.readMetadata());
    
    XmpData& xmp = video.xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.DataPackets"));
    EXPECT_NE(it, xmp.end());
}

// Test: readMetadata populates SendDuration
TEST_F(AsfVideoTest_1572, ReadMetadataPopulatesSendDuration_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    ASSERT_NO_THROW(video.readMetadata());
    
    XmpData& xmp = video.xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SendDuration"));
    EXPECT_NE(it, xmp.end());
}

// Test: readMetadata populates Preroll
TEST_F(AsfVideoTest_1572, ReadMetadataPopulatesPreroll_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    ASSERT_NO_THROW(video.readMetadata());
    
    XmpData& xmp = video.xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.Preroll"));
    EXPECT_NE(it, xmp.end());
}

// Test: readMetadata with truncated data throws exception
TEST_F(AsfVideoTest_1572, ReadMetadataWithTruncatedDataThrows_1572) {
    // Only provide header GUID but truncated size
    const uint8_t headerGuid[] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    
    std::vector<uint8_t> truncData(headerGuid, headerGuid + 16);
    // Add a partial size (only 4 bytes instead of 8)
    truncData.push_back(0x00);
    truncData.push_back(0x00);
    truncData.push_back(0x00);
    truncData.push_back(0x00);
    
    auto io = std::make_unique<MemIo>(truncData.data(), truncData.size());
    AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test: readMetadata with empty data throws
TEST_F(AsfVideoTest_1572, ReadMetadataWithEmptyDataThrows_1572) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test: writeMetadata throws (ASF write is not supported based on typical implementations)
TEST_F(AsfVideoTest_1572, WriteMetadataThrows_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.writeMetadata(), Exiv2::Error);
}

// Test: GUIDTag to_string produces expected format
TEST_F(AsfVideoTest_1572, GUIDTagToString_1572) {
    uint8_t bytes[16] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    
    AsfVideo::GUIDTag tag(bytes);
    std::string str = tag.to_string();
    
    // The string should not be empty
    EXPECT_FALSE(str.empty());
}

// Test: GUIDTag equality operator
TEST_F(AsfVideoTest_1572, GUIDTagEquality_1572) {
    uint8_t bytes1[16] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    uint8_t bytes2[16] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    
    AsfVideo::GUIDTag tag1(bytes1);
    AsfVideo::GUIDTag tag2(bytes2);
    
    EXPECT_TRUE(tag1 == tag2);
}

// Test: GUIDTag inequality
TEST_F(AsfVideoTest_1572, GUIDTagInequality_1572) {
    uint8_t bytes1[16] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    uint8_t bytes2[16] = {
        0xA1, 0xDC, 0xAB, 0x8C, 0x47, 0xA9, 0xCF, 0x11,
        0x8E, 0xE4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65
    };
    
    AsfVideo::GUIDTag tag1(bytes1);
    AsfVideo::GUIDTag tag2(bytes2);
    
    EXPECT_FALSE(tag1 == tag2);
}

// Test: GUIDTag less-than operator
TEST_F(AsfVideoTest_1572, GUIDTagLessThan_1572) {
    uint8_t bytes1[16] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    uint8_t bytes2[16] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    
    AsfVideo::GUIDTag tag1(bytes1);
    AsfVideo::GUIDTag tag2(bytes2);
    
    EXPECT_TRUE(tag1 < tag2);
    EXPECT_FALSE(tag2 < tag1);
}

// Test: GUIDTag constructed from constexpr
TEST_F(AsfVideoTest_1572, GUIDTagConstexprConstruction_1572) {
    constexpr AsfVideo::GUIDTag tag(0x75B22630, 0x668E, 0x11CF,
        {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C});
    
    std::string str = tag.to_string();
    EXPECT_FALSE(str.empty());
}

// Test: GUIDTag self equality
TEST_F(AsfVideoTest_1572, GUIDTagSelfEquality_1572) {
    uint8_t bytes[16] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10
    };
    
    AsfVideo::GUIDTag tag(bytes);
    EXPECT_TRUE(tag == tag);
    EXPECT_FALSE(tag < tag);
}

// Test: readMetadata with file properties containing all zeros
TEST_F(AsfVideoTest_1572, ReadMetadataWithZeroFileProperties_1572) {
    // Build ASF with all-zero file properties data
    const uint8_t headerGuid[] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    const uint8_t filePropsGuid[] = {
        0xA1, 0xDC, 0xAB, 0x8C, 0x47, 0xA9, 0xCF, 0x11,
        0x8E, 0xE4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65
    };
    
    std::vector<uint8_t> fileData;
    
    size_t filePropObjSize = 16 + 8 + 80;
    size_t headerObjSize = 30 + filePropObjSize;
    
    fileData.insert(fileData.end(), headerGuid, headerGuid + 16);
    for (int i = 0; i < 8; i++) {
        fileData.push_back(static_cast<uint8_t>((headerObjSize >> (i * 8)) & 0xFF));
    }
    fileData.push_back(0x01);
    fileData.push_back(0x00);
    fileData.push_back(0x00);
    fileData.push_back(0x00);
    fileData.push_back(0x01);
    fileData.push_back(0x02);
    
    fileData.insert(fileData.end(), filePropsGuid, filePropsGuid + 16);
    for (int i = 0; i < 8; i++) {
        fileData.push_back(static_cast<uint8_t>((filePropObjSize >> (i * 8)) & 0xFF));
    }
    
    // All zeros for file properties data
    std::vector<uint8_t> zeroData(80, 0);
    fileData.insert(fileData.end(), zeroData.begin(), zeroData.end());
    
    auto io = std::make_unique<MemIo>(fileData.data(), fileData.size());
    AsfVideo video(std::move(io));
    
    ASSERT_NO_THROW(video.readMetadata());
    
    XmpData& xmp = video.xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.FileLength"));
    EXPECT_NE(it, xmp.end());
    if (it != xmp.end()) {
        EXPECT_EQ(it->toInt64(), 0);
    }
}

// Test: image type is ASF
TEST_F(AsfVideoTest_1572, ImageTypeIsAsf_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    EXPECT_EQ(video.imageType(), ImageType::asf);
}

// Test: readMetadata with insufficient data for file properties object
TEST_F(AsfVideoTest_1572, ReadMetadataInsufficientFilePropsData_1572) {
    const uint8_t headerGuid[] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    const uint8_t filePropsGuid[] = {
        0xA1, 0xDC, 0xAB, 0x8C, 0x47, 0xA9, 0xCF, 0x11,
        0x8E, 0xE4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65
    };
    
    std::vector<uint8_t> fileData;
    
    // Claim a large object but provide truncated data
    size_t filePropObjSize = 16 + 8 + 80;
    size_t headerObjSize = 30 + filePropObjSize;
    
    fileData.insert(fileData.end(), headerGuid, headerGuid + 16);
    for (int i = 0; i < 8; i++) {
        fileData.push_back(static_cast<uint8_t>((headerObjSize >> (i * 8)) & 0xFF));
    }
    fileData.push_back(0x01);
    fileData.push_back(0x00);
    fileData.push_back(0x00);
    fileData.push_back(0x00);
    fileData.push_back(0x01);
    fileData.push_back(0x02);
    
    // File Properties GUID
    fileData.insert(fileData.end(), filePropsGuid, filePropsGuid + 16);
    for (int i = 0; i < 8; i++) {
        fileData.push_back(static_cast<uint8_t>((filePropObjSize >> (i * 8)) & 0xFF));
    }
    
    // Only provide 10 bytes instead of 80
    std::vector<uint8_t> shortData(10, 0);
    fileData.insert(fileData.end(), shortData.begin(), shortData.end());
    
    auto io = std::make_unique<MemIo>(fileData.data(), fileData.size());
    AsfVideo video(std::move(io));
    
    // Should throw due to insufficient data
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test: XmpData initially empty before readMetadata
TEST_F(AsfVideoTest_1572, XmpDataEmptyBeforeRead_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    EXPECT_TRUE(video.xmpData().empty());
}

// Test: XmpData not empty after readMetadata
TEST_F(AsfVideoTest_1572, XmpDataNotEmptyAfterRead_1572) {
    auto data = buildMinimalAsfWithFileProperties();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    ASSERT_NO_THROW(video.readMetadata());
    EXPECT_FALSE(video.xmpData().empty());
}

// Test: GUIDTag all zeros
TEST_F(AsfVideoTest_1572, GUIDTagAllZeros_1572) {
    uint8_t bytes[16] = {0};
    AsfVideo::GUIDTag tag(bytes);
    std::string str = tag.to_string();
    EXPECT_FALSE(str.empty());
}

// Test: GUIDTag all 0xFF
TEST_F(AsfVideoTest_1572, GUIDTagAllFF_1572) {
    uint8_t bytes[16];
    memset(bytes, 0xFF, 16);
    AsfVideo::GUIDTag tag(bytes);
    std::string str = tag.to_string();
    EXPECT_FALSE(str.empty());
}

// Test: GUIDTag constexpr equality with byte-constructed
TEST_F(AsfVideoTest_1572, GUIDTagConstexprMatchesByteConstructed_1572) {
    // The ASF header GUID in standard form: 75B22630-668E-11CF-A6D9-00AA0062CE6C
    // As stored in little-endian bytes:
    uint8_t bytes[] = {
        0x30, 0x26, 0xB2, 0x75,  // data1 LE
        0x8E, 0x66,              // data2 LE
        0xCF, 0x11,              // data3 LE
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C  // data4
    };
    
    AsfVideo::GUIDTag tag1(bytes);
    AsfVideo::GUIDTag tag2(0x75B22630, 0x668E, 0x11CF,
        {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C});
    
    EXPECT_TRUE(tag1 == tag2);
}
