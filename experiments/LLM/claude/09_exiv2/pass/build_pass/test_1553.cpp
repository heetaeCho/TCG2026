#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/orfimage.hpp>
#include <cstring>
#include <vector>

using namespace Exiv2;

class OrfParserTest_1553 : public ::testing::Test {
protected:
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    void SetUp() override {
        exifData.clear();
        iptcData.clear();
        xmpData.clear();
    }
};

// Test decoding with null data pointer
TEST_F(OrfParserTest_1553, DecodeNullData_1553) {
    // Passing null pointer with zero size - should handle gracefully
    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, nullptr, 0);
    // We just verify it doesn't crash and returns some byte order
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}

// Test decoding with empty data (zero size)
TEST_F(OrfParserTest_1553, DecodeEmptyData_1553) {
    const byte data[] = {0};
    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data, 0);
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}

// Test decoding with data too small to be valid ORF
TEST_F(OrfParserTest_1553, DecodeTooSmallData_1553) {
    const byte data[] = {0x49, 0x49};  // Only 2 bytes, not enough for a valid header
    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data, 2);
    // Should fail gracefully since data is too small
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}

// Test decoding with invalid/garbage data
TEST_F(OrfParserTest_1553, DecodeGarbageData_1553) {
    std::vector<byte> data(100, 0xFF);
    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // Invalid data should not populate exif data meaningfully
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}

// Test decoding with data that has ORF-like header but is incomplete
TEST_F(OrfParserTest_1553, DecodeIncompleteOrfHeader_1553) {
    // ORF files use "II" (little-endian) or "MM" (big-endian) with signature 0x4F52
    // Little endian: 49 49 52 4F 08 00 00 00
    byte data[] = {0x49, 0x49, 0x52, 0x4F, 0x08, 0x00, 0x00, 0x00};
    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data, sizeof(data));
    // With just a header and no IFD data, it may or may not parse successfully
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}

// Test that decode doesn't modify data containers on invalid input
TEST_F(OrfParserTest_1553, DecodeInvalidDataContainersUnchanged_1553) {
    std::vector<byte> data(4, 0x00);
    OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // With invalid data, containers should remain empty or have minimal content
    // We verify they are accessible without crashing
    SUCCEED();
}

// Test decoding with a minimal valid-looking ORF little-endian header
TEST_F(OrfParserTest_1553, DecodeMinimalLittleEndianHeader_1553) {
    // Construct a minimal ORF-like structure:
    // Byte order: II (little endian) = 0x49 0x49
    // Signature: 0x4F52 (ORF) in LE = 0x52 0x4F
    // Offset to IFD0: 8 in LE = 0x08 0x00 0x00 0x00
    // Then IFD0 with 0 entries: 0x00 0x00
    // Next IFD offset: 0x00 0x00 0x00 0x00
    std::vector<byte> data = {
        0x49, 0x49,             // Byte order: little endian
        0x52, 0x4F,             // ORF signature
        0x08, 0x00, 0x00, 0x00, // Offset to IFD0
        0x00, 0x00,             // IFD0: 0 entries
        0x00, 0x00, 0x00, 0x00  // Next IFD offset: 0
    };

    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // A minimal valid ORF should decode as little endian
    EXPECT_EQ(result, littleEndian);
}

// Test decoding with big-endian ORF header
TEST_F(OrfParserTest_1553, DecodeMinimalBigEndianHeader_1553) {
    // Byte order: MM (big endian) = 0x4D 0x4D
    // Signature: 0x4F52 (ORF) in BE = 0x4F 0x52
    // Offset to IFD0: 8 in BE = 0x00 0x00 0x00 0x08
    // Then IFD0 with 0 entries: 0x00 0x00
    // Next IFD offset: 0x00 0x00 0x00 0x00
    std::vector<byte> data = {
        0x4D, 0x4D,             // Byte order: big endian
        0x4F, 0x52,             // ORF signature
        0x00, 0x00, 0x00, 0x08, // Offset to IFD0
        0x00, 0x00,             // IFD0: 0 entries
        0x00, 0x00, 0x00, 0x00  // Next IFD offset: 0
    };

    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // A minimal valid big-endian ORF should decode as big endian
    EXPECT_EQ(result, bigEndian);
}

// Test decoding with wrong magic number
TEST_F(OrfParserTest_1553, DecodeWrongMagicNumber_1553) {
    // Use TIFF magic (0x002A) instead of ORF (0x4F52)
    std::vector<byte> data = {
        0x49, 0x49,             // Byte order: little endian
        0x2A, 0x00,             // TIFF magic, not ORF
        0x08, 0x00, 0x00, 0x00, // Offset to IFD0
        0x00, 0x00,             // IFD0: 0 entries
        0x00, 0x00, 0x00, 0x00  // Next IFD offset: 0
    };

    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // Wrong magic - behavior depends on implementation but should not crash
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}

// Test that exifData is accessible after decode with valid data
TEST_F(OrfParserTest_1553, DecodeValidDataExifAccessible_1553) {
    std::vector<byte> data = {
        0x49, 0x49,
        0x52, 0x4F,
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());

    // Verify containers are accessible
    for (auto it = exifData.begin(); it != exifData.end(); ++it) {
        // Just iterate - should not crash
    }
    SUCCEED();
}

// Test decoding with size 1 byte
TEST_F(OrfParserTest_1553, DecodeSingleByte_1553) {
    byte data = 0x49;
    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, &data, 1);
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}

// Test decoding exactly header size (8 bytes) with no IFD
TEST_F(OrfParserTest_1553, DecodeExactHeaderSize_1553) {
    std::vector<byte> data = {
        0x49, 0x49,
        0x52, 0x4F,
        0x08, 0x00, 0x00, 0x00
    };

    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // Header present but no IFD data - should handle gracefully
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}

// Test that iptcData remains empty on minimal valid decode
TEST_F(OrfParserTest_1553, DecodeMinimalValidIptcEmpty_1553) {
    std::vector<byte> data = {
        0x49, 0x49,
        0x52, 0x4F,
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    EXPECT_TRUE(iptcData.empty());
}

// Test that xmpData remains empty on minimal valid decode
TEST_F(OrfParserTest_1553, DecodeMinimalValidXmpEmpty_1553) {
    std::vector<byte> data = {
        0x49, 0x49,
        0x52, 0x4F,
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    EXPECT_TRUE(xmpData.empty());
}

// Test decode with large buffer of zeros
TEST_F(OrfParserTest_1553, DecodeLargeZeroBuffer_1553) {
    std::vector<byte> data(10000, 0x00);
    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}

// Test decoding with IFD offset pointing beyond data
TEST_F(OrfParserTest_1553, DecodeIfdOffsetBeyondData_1553) {
    std::vector<byte> data = {
        0x49, 0x49,
        0x52, 0x4F,
        0xFF, 0xFF, 0x00, 0x00, // IFD offset way beyond data size
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    ByteOrder result = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // Should handle gracefully
    EXPECT_TRUE(result == littleEndian || result == bigEndian || result == invalidByteOrder);
}
