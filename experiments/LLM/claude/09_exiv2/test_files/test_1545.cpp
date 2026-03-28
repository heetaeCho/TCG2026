#include <gtest/gtest.h>
#include "cr2header_int.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Cr2HeaderTest_1545 : public ::testing::Test {
protected:
};

// Test that Cr2Header with little endian byte order produces correct write output
TEST_F(Cr2HeaderTest_1545, WriteLittleEndian_ByteOrderMarker_1545) {
    Cr2Header header(littleEndian);
    DataBuf buf = header.write();

    // For little endian, first two bytes should be 'I', 'I'
    EXPECT_EQ(buf.read_uint8(0), 'I');
    EXPECT_EQ(buf.read_uint8(1), 'I');
}

TEST_F(Cr2HeaderTest_1545, WriteBigEndian_ByteOrderMarker_1545) {
    Cr2Header header(bigEndian);
    DataBuf buf = header.write();

    // For big endian, first two bytes should be 'M', 'M'
    EXPECT_EQ(buf.read_uint8(0), 'M');
    EXPECT_EQ(buf.read_uint8(1), 'M');
}

// Test that write produces a buffer of size 16
TEST_F(Cr2HeaderTest_1545, WriteBufferSize_1545) {
    Cr2Header header(littleEndian);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.size(), 16u);
}

TEST_F(Cr2HeaderTest_1545, WriteBigEndianBufferSize_1545) {
    Cr2Header header(bigEndian);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.size(), 16u);
}

// Test the tag value (42 for TIFF) at offset 2
TEST_F(Cr2HeaderTest_1545, WriteLittleEndian_TagValue_1545) {
    Cr2Header header(littleEndian);
    DataBuf buf = header.write();

    uint16_t tag = buf.read_uint16(2, littleEndian);
    EXPECT_EQ(tag, 42u);
}

TEST_F(Cr2HeaderTest_1545, WriteBigEndian_TagValue_1545) {
    Cr2Header header(bigEndian);
    DataBuf buf = header.write();

    uint16_t tag = buf.read_uint16(2, bigEndian);
    EXPECT_EQ(tag, 42u);
}

// Test the offset value at position 4 (should be 0x00000010 = 16)
TEST_F(Cr2HeaderTest_1545, WriteLittleEndian_OffsetValue_1545) {
    Cr2Header header(littleEndian);
    DataBuf buf = header.write();

    uint32_t offset = buf.read_uint32(4, littleEndian);
    EXPECT_EQ(offset, 0x00000010u);
}

TEST_F(Cr2HeaderTest_1545, WriteBigEndian_OffsetValue_1545) {
    Cr2Header header(bigEndian);
    DataBuf buf = header.write();

    uint32_t offset = buf.read_uint32(4, bigEndian);
    EXPECT_EQ(offset, 0x00000010u);
}

// Test the offset2 value at position 12 (should be 0x00000000)
TEST_F(Cr2HeaderTest_1545, WriteLittleEndian_Offset2Value_1545) {
    Cr2Header header(littleEndian);
    DataBuf buf = header.write();

    uint32_t offset2 = buf.read_uint32(12, littleEndian);
    EXPECT_EQ(offset2, 0x00000000u);
}

TEST_F(Cr2HeaderTest_1545, WriteBigEndian_Offset2Value_1545) {
    Cr2Header header(bigEndian);
    DataBuf buf = header.write();

    uint32_t offset2 = buf.read_uint32(12, bigEndian);
    EXPECT_EQ(offset2, 0x00000000u);
}

// Test byteOrder() returns what was set in constructor
TEST_F(Cr2HeaderTest_1545, ByteOrderLittleEndian_1545) {
    Cr2Header header(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

TEST_F(Cr2HeaderTest_1545, ByteOrderBigEndian_1545) {
    Cr2Header header(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test tag() returns 42
TEST_F(Cr2HeaderTest_1545, TagValue_1545) {
    Cr2Header header(littleEndian);
    EXPECT_EQ(header.tag(), 42u);
}

// Test size() returns 16
TEST_F(Cr2HeaderTest_1545, SizeValue_1545) {
    Cr2Header header(littleEndian);
    EXPECT_EQ(header.size(), 16u);
}

// Test offset() returns 0x00000010
TEST_F(Cr2HeaderTest_1545, OffsetValue_1545) {
    Cr2Header header(littleEndian);
    EXPECT_EQ(header.offset(), 0x00000010u);
}

// Test offset2addr() static method
TEST_F(Cr2HeaderTest_1545, Offset2Addr_1545) {
    uint32_t addr = Cr2Header::offset2addr();
    // offset2addr should return the offset within the header where offset2 is stored
    // Based on the write() implementation, offset2 is at position 12
    EXPECT_EQ(addr, 12u);
}

// Test CR2 signature bytes at offset 8-11
TEST_F(Cr2HeaderTest_1545, WriteLittleEndian_Cr2Signature_1545) {
    Cr2Header header(littleEndian);
    DataBuf buf = header.write();

    // CR2 signature is typically "CR" followed by version bytes
    // Check bytes at offset 8-11 contain the CR2 signature
    EXPECT_EQ(buf.read_uint8(8), 'C');
    EXPECT_EQ(buf.read_uint8(9), 'R');
}

TEST_F(Cr2HeaderTest_1545, WriteBigEndian_Cr2Signature_1545) {
    Cr2Header header(bigEndian);
    DataBuf buf = header.write();

    EXPECT_EQ(buf.read_uint8(8), 'C');
    EXPECT_EQ(buf.read_uint8(9), 'R');
}

// Test read with valid CR2 header data (little endian)
TEST_F(Cr2HeaderTest_1545, ReadValidLittleEndianHeader_1545) {
    Cr2Header header(littleEndian);
    DataBuf buf = header.write();

    Cr2Header readHeader(littleEndian);
    bool result = readHeader.read(buf.c_data(0), buf.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(readHeader.byteOrder(), littleEndian);
}

// Test read with valid CR2 header data (big endian)
TEST_F(Cr2HeaderTest_1545, ReadValidBigEndianHeader_1545) {
    Cr2Header header(bigEndian);
    DataBuf buf = header.write();

    Cr2Header readHeader(bigEndian);
    bool result = readHeader.read(buf.c_data(0), buf.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(readHeader.byteOrder(), bigEndian);
}

// Test read with insufficient data size
TEST_F(Cr2HeaderTest_1545, ReadInsufficientData_1545) {
    Cr2Header header(littleEndian);
    byte smallBuf[4] = {0};
    bool result = header.read(smallBuf, 4);
    EXPECT_FALSE(result);
}

// Test read with zero size
TEST_F(Cr2HeaderTest_1545, ReadZeroSize_1545) {
    Cr2Header header(littleEndian);
    byte emptyBuf[1] = {0};
    bool result = header.read(emptyBuf, 0);
    EXPECT_FALSE(result);
}

// Test read with invalid byte order marker
TEST_F(Cr2HeaderTest_1545, ReadInvalidByteOrderMarker_1545) {
    Cr2Header header(littleEndian);
    DataBuf buf = header.write();

    // Corrupt the byte order marker
    buf.write_uint8(0, 'X');
    buf.write_uint8(1, 'X');

    Cr2Header readHeader(littleEndian);
    bool result = readHeader.read(buf.c_data(0), buf.size());
    EXPECT_FALSE(result);
}

// Test setByteOrder changes the byte order
TEST_F(Cr2HeaderTest_1545, SetByteOrder_1545) {
    Cr2Header header(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);

    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test write after changing byte order
TEST_F(Cr2HeaderTest_1545, WriteAfterSetByteOrder_1545) {
    Cr2Header header(littleEndian);
    header.setByteOrder(bigEndian);
    DataBuf buf = header.write();

    EXPECT_EQ(buf.read_uint8(0), 'M');
    EXPECT_EQ(buf.read_uint8(1), 'M');
}

// Test that write output is consistent (calling write twice produces same result)
TEST_F(Cr2HeaderTest_1545, WriteConsistency_1545) {
    Cr2Header header(littleEndian);
    DataBuf buf1 = header.write();
    DataBuf buf2 = header.write();

    EXPECT_EQ(buf1.size(), buf2.size());
    for (size_t i = 0; i < buf1.size(); ++i) {
        EXPECT_EQ(buf1.read_uint8(i), buf2.read_uint8(i));
    }
}

// Test round-trip: write then read
TEST_F(Cr2HeaderTest_1545, RoundTripLittleEndian_1545) {
    Cr2Header writeHeader(littleEndian);
    DataBuf buf = writeHeader.write();

    Cr2Header readHeader(littleEndian);
    EXPECT_TRUE(readHeader.read(buf.c_data(0), buf.size()));
    EXPECT_EQ(readHeader.byteOrder(), littleEndian);
    EXPECT_EQ(readHeader.tag(), 42u);
}

TEST_F(Cr2HeaderTest_1545, RoundTripBigEndian_1545) {
    Cr2Header writeHeader(bigEndian);
    DataBuf buf = writeHeader.write();

    Cr2Header readHeader(bigEndian);
    EXPECT_TRUE(readHeader.read(buf.c_data(0), buf.size()));
    EXPECT_EQ(readHeader.byteOrder(), bigEndian);
    EXPECT_EQ(readHeader.tag(), 42u);
}
