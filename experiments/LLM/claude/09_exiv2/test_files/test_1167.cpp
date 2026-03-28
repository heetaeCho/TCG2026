#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffParserWorkerTest_1167 : public ::testing::Test {
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

// Test decode with null data and null header - should use default TiffHeader
TEST_F(TiffParserWorkerTest_1167, DecodeNullDataWithNullHeader_1167) {
    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        nullptr, 0,
        Tag::root,
        nullptr,
        nullptr
    );
    // With null data and size 0, parse should fail to produce a root dir,
    // but the default TiffHeader's byte order should still be returned
    // Default TiffHeader typically has littleEndian byte order
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian);
}

// Test decode with zero-size data and null header
TEST_F(TiffParserWorkerTest_1167, DecodeZeroSizeData_1167) {
    const byte data[] = {0x00};
    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        data, 0,
        Tag::root,
        nullptr,
        nullptr
    );
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian);
    // With zero size data, no EXIF data should be decoded
    EXPECT_TRUE(exifData.empty());
}

// Test decode with invalid/garbage data
TEST_F(TiffParserWorkerTest_1167, DecodeGarbageData_1167) {
    const byte garbageData[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8};
    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        garbageData, sizeof(garbageData),
        Tag::root,
        nullptr,
        nullptr
    );
    // Should return some byte order (from header parsing attempt)
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian);
}

// Test decode with a minimal valid TIFF structure (little-endian)
TEST_F(TiffParserWorkerTest_1167, DecodeMinimalValidTiffLittleEndian_1167) {
    // Minimal TIFF: II (little-endian), magic 42, offset to IFD0 = 8, 0 entries
    const byte tiffData[] = {
        0x49, 0x49,             // "II" - little endian
        0x2A, 0x00,             // Magic number 42
        0x08, 0x00, 0x00, 0x00, // Offset to IFD0 = 8
        0x00, 0x00              // Number of directory entries = 0
    };

    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tiffData, sizeof(tiffData),
        Tag::root,
        nullptr,
        nullptr
    );
    EXPECT_EQ(bo, littleEndian);
}

// Test decode with a minimal valid TIFF structure (big-endian)
TEST_F(TiffParserWorkerTest_1167, DecodeMinimalValidTiffBigEndian_1167) {
    // Minimal TIFF: MM (big-endian), magic 42, offset to IFD0 = 8, 0 entries
    const byte tiffData[] = {
        0x4D, 0x4D,             // "MM" - big endian
        0x00, 0x2A,             // Magic number 42
        0x00, 0x00, 0x00, 0x08, // Offset to IFD0 = 8
        0x00, 0x00              // Number of directory entries = 0
    };

    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tiffData, sizeof(tiffData),
        Tag::root,
        nullptr,
        nullptr
    );
    EXPECT_EQ(bo, bigEndian);
}

// Test decode with a custom TiffHeader
TEST_F(TiffParserWorkerTest_1167, DecodeWithCustomHeader_1167) {
    TiffHeader header;
    const byte tiffData[] = {
        0x49, 0x49,             // "II" - little endian
        0x2A, 0x00,             // Magic number 42
        0x08, 0x00, 0x00, 0x00, // Offset to IFD0 = 8
        0x00, 0x00              // Number of directory entries = 0
    };

    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tiffData, sizeof(tiffData),
        Tag::root,
        nullptr,
        &header
    );
    EXPECT_EQ(bo, littleEndian);
}

// Test that decode with data too small for a valid TIFF header doesn't crash
TEST_F(TiffParserWorkerTest_1167, DecodeTooSmallData_1167) {
    const byte tinyData[] = {0x49, 0x49};  // Only 2 bytes, not enough for TIFF header
    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tinyData, sizeof(tinyData),
        Tag::root,
        nullptr,
        nullptr
    );
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian);
    EXPECT_TRUE(exifData.empty());
}

// Test decode with valid TIFF containing one IFD entry
TEST_F(TiffParserWorkerTest_1167, DecodeWithOneIFDEntry_1167) {
    // TIFF with one IFD entry: ImageWidth = 100
    const byte tiffData[] = {
        0x49, 0x49,             // "II" - little endian
        0x2A, 0x00,             // Magic number 42
        0x08, 0x00, 0x00, 0x00, // Offset to IFD0 = 8
        0x01, 0x00,             // Number of directory entries = 1
        // Entry: tag=0x0100 (ImageWidth), type=3 (SHORT), count=1, value=100
        0x00, 0x01,             // Tag = 0x0100
        0x03, 0x00,             // Type = SHORT
        0x01, 0x00, 0x00, 0x00, // Count = 1
        0x64, 0x00, 0x00, 0x00, // Value = 100
        0x00, 0x00, 0x00, 0x00  // Next IFD offset = 0 (no more IFDs)
    };

    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tiffData, sizeof(tiffData),
        Tag::root,
        nullptr,
        nullptr
    );
    EXPECT_EQ(bo, littleEndian);
    // The decode should have populated some exif data
    // ImageWidth (tag 0x0100) should be present
}

// Test decode leaves iptcData and xmpData empty for simple TIFF
TEST_F(TiffParserWorkerTest_1167, DecodeSimpleTiffNoIptcNoXmp_1167) {
    const byte tiffData[] = {
        0x49, 0x49,
        0x2A, 0x00,
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00
    };

    TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tiffData, sizeof(tiffData),
        Tag::root,
        nullptr,
        nullptr
    );
    EXPECT_TRUE(iptcData.empty());
    EXPECT_TRUE(xmpData.empty());
}

// Test decode with wrong magic number
TEST_F(TiffParserWorkerTest_1167, DecodeWrongMagicNumber_1167) {
    const byte tiffData[] = {
        0x49, 0x49,             // "II" - little endian
        0x00, 0x00,             // Wrong magic number (should be 42)
        0x08, 0x00, 0x00, 0x00, // Offset to IFD0 = 8
        0x00, 0x00              // Number of directory entries = 0
    };

    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tiffData, sizeof(tiffData),
        Tag::root,
        nullptr,
        nullptr
    );
    // With wrong magic, the header read should fail and exifData should remain empty
    EXPECT_TRUE(exifData.empty());
}

// Test TiffHeaderBase basic operations
class TiffHeaderBaseTest_1167 : public ::testing::Test {};

TEST_F(TiffHeaderBaseTest_1167, DefaultTiffHeaderByteOrder_1167) {
    TiffHeader header;
    // Default TiffHeader should have a valid byte order
    ByteOrder bo = header.byteOrder();
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian);
}

TEST_F(TiffHeaderBaseTest_1167, TiffHeaderSetByteOrder_1167) {
    TiffHeader header;
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
    header.setByteOrder(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

TEST_F(TiffHeaderBaseTest_1167, TiffHeaderSetOffset_1167) {
    TiffHeader header;
    header.setOffset(16);
    EXPECT_EQ(header.offset(), 16u);
}

TEST_F(TiffHeaderBaseTest_1167, TiffHeaderSize_1167) {
    TiffHeader header;
    // Standard TIFF header size is 8 bytes
    EXPECT_EQ(header.size(), 8u);
}

TEST_F(TiffHeaderBaseTest_1167, TiffHeaderTag_1167) {
    TiffHeader header;
    // Standard TIFF magic is 0x002A = 42
    EXPECT_EQ(header.tag(), 0x002A);
}

TEST_F(TiffHeaderBaseTest_1167, TiffHeaderReadValidLittleEndian_1167) {
    TiffHeader header;
    const byte data[] = {
        0x49, 0x49,             // "II" - little endian
        0x2A, 0x00,             // Magic number 42
        0x08, 0x00, 0x00, 0x00  // Offset = 8
    };
    bool result = header.read(data, sizeof(data));
    EXPECT_TRUE(result);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    EXPECT_EQ(header.offset(), 8u);
}

TEST_F(TiffHeaderBaseTest_1167, TiffHeaderReadValidBigEndian_1167) {
    TiffHeader header;
    const byte data[] = {
        0x4D, 0x4D,             // "MM" - big endian
        0x00, 0x2A,             // Magic number 42
        0x00, 0x00, 0x00, 0x08  // Offset = 8
    };
    bool result = header.read(data, sizeof(data));
    EXPECT_TRUE(result);
    EXPECT_EQ(header.byteOrder(), bigEndian);
    EXPECT_EQ(header.offset(), 8u);
}

TEST_F(TiffHeaderBaseTest_1167, TiffHeaderReadInvalidData_1167) {
    TiffHeader header;
    const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header.read(data, sizeof(data));
    EXPECT_FALSE(result);
}

TEST_F(TiffHeaderBaseTest_1167, TiffHeaderReadTooSmall_1167) {
    TiffHeader header;
    const byte data[] = {0x49, 0x49, 0x2A, 0x00};
    bool result = header.read(data, sizeof(data));
    // Data is smaller than header size (8), should fail
    EXPECT_FALSE(result);
}

TEST_F(TiffHeaderBaseTest_1167, TiffHeaderWrite_1167) {
    TiffHeader header;
    DataBuf buf = header.write();
    EXPECT_EQ(buf.size(), 8u);
}

// Test decode returns byte order consistently with the header
TEST_F(TiffParserWorkerTest_1167, DecodeReturnsByteOrderFromHeader_1167) {
    TiffHeader header;
    header.setByteOrder(bigEndian);
    
    // Provide data that matches big-endian TIFF
    const byte tiffData[] = {
        0x4D, 0x4D,
        0x00, 0x2A,
        0x00, 0x00, 0x00, 0x08,
        0x00, 0x00
    };

    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tiffData, sizeof(tiffData),
        Tag::root,
        nullptr,
        &header
    );
    EXPECT_EQ(bo, bigEndian);
}

// Test that multiple calls to decode accumulate or reset data properly
TEST_F(TiffParserWorkerTest_1167, DecodeMultipleCalls_1167) {
    const byte tiffData[] = {
        0x49, 0x49,
        0x2A, 0x00,
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00
    };

    // First call
    TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tiffData, sizeof(tiffData),
        Tag::root,
        nullptr,
        nullptr
    );

    // Second call with same data - should not crash
    TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        tiffData, sizeof(tiffData),
        Tag::root,
        nullptr,
        nullptr
    );

    // No assertion about specific data count, just verify no crash
    SUCCEED();
}

// Test decode with a single byte
TEST_F(TiffParserWorkerTest_1167, DecodeSingleByte_1167) {
    const byte singleByte[] = {0x49};
    ByteOrder bo = TiffParserWorker::decode(
        exifData, iptcData, xmpData,
        singleByte, sizeof(singleByte),
        Tag::root,
        nullptr,
        nullptr
    );
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian);
    EXPECT_TRUE(exifData.empty());
}
