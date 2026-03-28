#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// Include necessary headers
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function to write a uint16_t in little-endian
static void writeUShortLE(byte* buf, uint16_t val) {
    buf[0] = static_cast<byte>(val & 0xFF);
    buf[1] = static_cast<byte>((val >> 8) & 0xFF);
}

// Helper function to write a uint16_t in big-endian
static void writeUShortBE(byte* buf, uint16_t val) {
    buf[0] = static_cast<byte>((val >> 8) & 0xFF);
    buf[1] = static_cast<byte>(val & 0xFF);
}

// Helper function to write a uint32_t in little-endian
static void writeULongLE(byte* buf, uint32_t val) {
    buf[0] = static_cast<byte>(val & 0xFF);
    buf[1] = static_cast<byte>((val >> 8) & 0xFF);
    buf[2] = static_cast<byte>((val >> 16) & 0xFF);
    buf[3] = static_cast<byte>((val >> 24) & 0xFF);
}

// Helper function to write a uint32_t in big-endian
static void writeULongBE(byte* buf, uint32_t val) {
    buf[0] = static_cast<byte>((val >> 24) & 0xFF);
    buf[1] = static_cast<byte>((val >> 16) & 0xFF);
    buf[2] = static_cast<byte>((val >> 8) & 0xFF);
    buf[3] = static_cast<byte>(val & 0xFF);
}

// Standard TIFF tag is 42 (0x002A)
static const uint16_t kStandardTiffTag = 42;
// JPEG-XR tag
static const uint16_t kJpegXrTag = 444;
// DCP tag
static const uint16_t kDcpTag = 17234;

class TiffHeaderBaseTest_1169 : public ::testing::Test {
protected:
    // Helper to build a valid little-endian TIFF header buffer
    void buildLittleEndianHeader(byte* buf, uint16_t tag, uint32_t offset) {
        buf[0] = 'I';
        buf[1] = 'I';
        writeUShortLE(buf + 2, tag);
        writeULongLE(buf + 4, offset);
    }

    // Helper to build a valid big-endian TIFF header buffer
    void buildBigEndianHeader(byte* buf, uint16_t tag, uint32_t offset) {
        buf[0] = 'M';
        buf[1] = 'M';
        writeUShortBE(buf + 2, tag);
        writeULongBE(buf + 4, offset);
    }
};

// Test: Null pointer returns false
TEST_F(TiffHeaderBaseTest_1169, ReadNullPointerReturnsFalse_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_FALSE(header.read(nullptr, 100));
}

// Test: Size less than 8 returns false
TEST_F(TiffHeaderBaseTest_1169, ReadSizeTooSmallReturnsFalse_1169) {
    byte buf[8] = {0};
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_FALSE(header.read(buf, 7));
}

// Test: Size exactly 0 returns false
TEST_F(TiffHeaderBaseTest_1169, ReadSizeZeroReturnsFalse_1169) {
    byte buf[8] = {0};
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_FALSE(header.read(buf, 0));
}

// Test: Invalid byte order marker returns false
TEST_F(TiffHeaderBaseTest_1169, ReadInvalidByteOrderReturnsFalse_1169) {
    byte buf[8] = {'X', 'X', 0, 42, 0, 0, 0, 8};
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_FALSE(header.read(buf, 8));
}

// Test: Mismatched byte order bytes returns false (e.g., 'I', 'M')
TEST_F(TiffHeaderBaseTest_1169, ReadMismatchedByteOrderReturnsFalse_1169) {
    byte buf[8] = {'I', 'M', 0, 42, 0, 0, 0, 8};
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_FALSE(header.read(buf, 8));
}

// Test: Valid little-endian header with matching tag
TEST_F(TiffHeaderBaseTest_1169, ReadValidLittleEndianMatchingTag_1169) {
    byte buf[8];
    buildLittleEndianHeader(buf, kStandardTiffTag, 8);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.byteOrder(), littleEndian);
    EXPECT_EQ(header.tag(), kStandardTiffTag);
    EXPECT_EQ(header.offset(), 8u);
}

// Test: Valid big-endian header with matching tag
TEST_F(TiffHeaderBaseTest_1169, ReadValidBigEndianMatchingTag_1169) {
    byte buf[8];
    buildBigEndianHeader(buf, kStandardTiffTag, 8);
    TiffHeaderBase header(kStandardTiffTag, 8, bigEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.byteOrder(), bigEndian);
    EXPECT_EQ(header.tag(), kStandardTiffTag);
    EXPECT_EQ(header.offset(), 8u);
}

// Test: JPEG-XR tag (444) is always accepted regardless of initial tag
TEST_F(TiffHeaderBaseTest_1169, ReadJpegXrTagAccepted_1169) {
    byte buf[8];
    buildLittleEndianHeader(buf, kJpegXrTag, 16);
    // Construct with a different tag (e.g., standard TIFF tag 42)
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.tag(), kJpegXrTag);
    EXPECT_EQ(header.offset(), 16u);
}

// Test: DCP tag (17234) is always accepted regardless of initial tag
TEST_F(TiffHeaderBaseTest_1169, ReadDcpTagAccepted_1169) {
    byte buf[8];
    buildBigEndianHeader(buf, kDcpTag, 32);
    TiffHeaderBase header(kStandardTiffTag, 8, bigEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.tag(), kDcpTag);
    EXPECT_EQ(header.offset(), 32u);
}

// Test: Non-matching tag (not 444, not 17234, not initial tag) returns false
TEST_F(TiffHeaderBaseTest_1169, ReadNonMatchingTagReturnsFalse_1169) {
    byte buf[8];
    uint16_t wrongTag = 999;
    buildLittleEndianHeader(buf, wrongTag, 8);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_FALSE(header.read(buf, 8));
}

// Test: Offset is correctly read in little-endian
TEST_F(TiffHeaderBaseTest_1169, ReadOffsetLittleEndian_1169) {
    byte buf[8];
    uint32_t expectedOffset = 0x12345678;
    buildLittleEndianHeader(buf, kStandardTiffTag, expectedOffset);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.offset(), expectedOffset);
}

// Test: Offset is correctly read in big-endian
TEST_F(TiffHeaderBaseTest_1169, ReadOffsetBigEndian_1169) {
    byte buf[8];
    uint32_t expectedOffset = 0xABCDEF01;
    buildBigEndianHeader(buf, kStandardTiffTag, expectedOffset);
    TiffHeaderBase header(kStandardTiffTag, 8, bigEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.offset(), expectedOffset);
}

// Test: Size exactly 8 is accepted (boundary)
TEST_F(TiffHeaderBaseTest_1169, ReadExactMinimumSize_1169) {
    byte buf[8];
    buildLittleEndianHeader(buf, kStandardTiffTag, 8);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
}

// Test: Size larger than 8 is accepted
TEST_F(TiffHeaderBaseTest_1169, ReadLargerSize_1169) {
    byte buf[16];
    memset(buf, 0, sizeof(buf));
    buildLittleEndianHeader(buf, kStandardTiffTag, 8);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_TRUE(header.read(buf, 16));
}

// Test: setByteOrder changes byte order
TEST_F(TiffHeaderBaseTest_1169, SetByteOrder_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test: setOffset changes offset
TEST_F(TiffHeaderBaseTest_1169, SetOffset_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_EQ(header.offset(), 0u);
    header.setOffset(42);
    EXPECT_EQ(header.offset(), 42u);
}

// Test: size() returns the constructed size
TEST_F(TiffHeaderBaseTest_1169, SizeReturnsConstructedValue_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_EQ(header.size(), 8u);
}

// Test: tag() returns the constructed tag before read
TEST_F(TiffHeaderBaseTest_1169, TagReturnsConstructedValue_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_EQ(header.tag(), kStandardTiffTag);
}

// Test: byteOrder() returns the constructed byte order before read
TEST_F(TiffHeaderBaseTest_1169, ByteOrderReturnsConstructedValue_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, bigEndian, 0);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test: offset() returns the constructed offset before read
TEST_F(TiffHeaderBaseTest_1169, OffsetReturnsConstructedValue_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 100);
    EXPECT_EQ(header.offset(), 100u);
}

// Test: Reading with big-endian correctly detects byte order from data
TEST_F(TiffHeaderBaseTest_1169, ReadOverridesByteOrderFromData_1169) {
    byte buf[8];
    // Construct with littleEndian but provide big-endian data
    buildBigEndianHeader(buf, kStandardTiffTag, 8);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test: Zero offset in little-endian
TEST_F(TiffHeaderBaseTest_1169, ReadZeroOffset_1169) {
    byte buf[8];
    buildLittleEndianHeader(buf, kStandardTiffTag, 0);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 100);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.offset(), 0u);
}

// Test: Reading with the tag matching the constructed tag_ (not 444 or 17234)
TEST_F(TiffHeaderBaseTest_1169, ReadCustomTagMatchesConstructed_1169) {
    uint16_t customTag = 555;
    byte buf[8];
    buildLittleEndianHeader(buf, customTag, 8);
    TiffHeaderBase header(customTag, 8, littleEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.tag(), customTag);
}

// Test: Tag that is neither 444, 17234, nor the initial tag_ should fail
TEST_F(TiffHeaderBaseTest_1169, ReadUnknownTagFails_1169) {
    uint16_t unknownTag = 12345;
    byte buf[8];
    buildLittleEndianHeader(buf, unknownTag, 8);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_FALSE(header.read(buf, 8));
}

// Test: write() produces a non-empty DataBuf for a valid header
TEST_F(TiffHeaderBaseTest_1169, WriteProducesData_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 8);
    DataBuf buf = header.write();
    EXPECT_GT(buf.size(), 0u);
}

// Test: print() does not crash
TEST_F(TiffHeaderBaseTest_1169, PrintDoesNotCrash_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 8);
    std::ostringstream os;
    EXPECT_NO_THROW(header.print(os, ""));
}

// Test: isImageTag returns a consistent value (default implementation)
TEST_F(TiffHeaderBaseTest_1169, IsImageTagDefault_1169) {
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    PrimaryGroups pg;
    // Just ensure it doesn't crash and returns a bool
    bool result = header.isImageTag(0, IfdId::ifd0Id, pg);
    // The default implementation returns false
    EXPECT_FALSE(result);
}

// Test: Multiple reads - second read with different byte order
TEST_F(TiffHeaderBaseTest_1169, MultipleReads_1169) {
    byte buf1[8];
    buildLittleEndianHeader(buf1, kStandardTiffTag, 8);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_TRUE(header.read(buf1, 8));
    EXPECT_EQ(header.byteOrder(), littleEndian);

    byte buf2[8];
    buildBigEndianHeader(buf2, kStandardTiffTag, 16);
    EXPECT_TRUE(header.read(buf2, 8));
    EXPECT_EQ(header.byteOrder(), bigEndian);
    EXPECT_EQ(header.offset(), 16u);
}

// Test: Maximum offset value
TEST_F(TiffHeaderBaseTest_1169, ReadMaxOffset_1169) {
    byte buf[8];
    buildLittleEndianHeader(buf, kStandardTiffTag, 0xFFFFFFFF);
    TiffHeaderBase header(kStandardTiffTag, 8, littleEndian, 0);
    EXPECT_TRUE(header.read(buf, 8));
    EXPECT_EQ(header.offset(), 0xFFFFFFFFu);
}
