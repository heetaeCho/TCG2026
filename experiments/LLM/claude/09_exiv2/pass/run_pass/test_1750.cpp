#include <gtest/gtest.h>
#include "orfimage_int.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OrfHeaderTest_1750 : public ::testing::Test {
protected:
};

// Test that writing with little endian produces correct byte order marker 'I'
TEST_F(OrfHeaderTest_1750, WriteLittleEndianProducesCorrectByteOrderMarker_1750) {
    OrfHeader header(littleEndian);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.read_uint8(0), 'I');
    EXPECT_EQ(buf.read_uint8(1), 'I');
}

// Test that writing with big endian produces correct byte order marker 'M'
TEST_F(OrfHeaderTest_1750, WriteBigEndianProducesCorrectByteOrderMarker_1750) {
    OrfHeader header(bigEndian);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.read_uint8(0), 'M');
    EXPECT_EQ(buf.read_uint8(1), 'M');
}

// Test that the buffer size is 8 bytes
TEST_F(OrfHeaderTest_1750, WriteProduces8ByteBuffer_1750) {
    OrfHeader header(littleEndian);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.size(), 8u);
}

// Test that the signature is written correctly for little endian
TEST_F(OrfHeaderTest_1750, WriteLittleEndianSignature_1750) {
    OrfHeader header(littleEndian);
    DataBuf buf = header.write();
    // sig_ defaults to 20306 which is 0x4F52
    uint16_t sig = buf.read_uint16(2, littleEndian);
    EXPECT_EQ(sig, 0x4F52);
}

// Test that the signature is written correctly for big endian
TEST_F(OrfHeaderTest_1750, WriteBigEndianSignature_1750) {
    OrfHeader header(bigEndian);
    DataBuf buf = header.write();
    uint16_t sig = buf.read_uint16(2, bigEndian);
    EXPECT_EQ(sig, 0x4F52);
}

// Test that the offset is written as 0x00000008 for little endian
TEST_F(OrfHeaderTest_1750, WriteLittleEndianOffset_1750) {
    OrfHeader header(littleEndian);
    DataBuf buf = header.write();
    uint32_t offset = buf.read_uint32(4, littleEndian);
    EXPECT_EQ(offset, 0x00000008u);
}

// Test that the offset is written as 0x00000008 for big endian
TEST_F(OrfHeaderTest_1750, WriteBigEndianOffset_1750) {
    OrfHeader header(bigEndian);
    DataBuf buf = header.write();
    uint32_t offset = buf.read_uint32(4, bigEndian);
    EXPECT_EQ(offset, 0x00000008u);
}

// Test that byte order markers are duplicated (byte 0 == byte 1) for little endian
TEST_F(OrfHeaderTest_1750, WriteLittleEndianDuplicatedByteOrderMarker_1750) {
    OrfHeader header(littleEndian);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.read_uint8(0), buf.read_uint8(1));
}

// Test that byte order markers are duplicated (byte 0 == byte 1) for big endian
TEST_F(OrfHeaderTest_1750, WriteBigEndianDuplicatedByteOrderMarker_1750) {
    OrfHeader header(bigEndian);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.read_uint8(0), buf.read_uint8(1));
}

// Test byteOrder() returns the byte order set in the constructor
TEST_F(OrfHeaderTest_1750, ByteOrderReturnsConstructorValue_1750) {
    OrfHeader headerLE(littleEndian);
    EXPECT_EQ(headerLE.byteOrder(), littleEndian);

    OrfHeader headerBE(bigEndian);
    EXPECT_EQ(headerBE.byteOrder(), bigEndian);
}

// Test that the tag is 0x4F52
TEST_F(OrfHeaderTest_1750, TagIsCorrect_1750) {
    OrfHeader header(littleEndian);
    EXPECT_EQ(header.tag(), 0x4F52);
}

// Test that size() returns 8
TEST_F(OrfHeaderTest_1750, SizeReturns8_1750) {
    OrfHeader header(littleEndian);
    EXPECT_EQ(header.size(), 8u);
}

// Test that offset() returns 0x00000008
TEST_F(OrfHeaderTest_1750, OffsetReturns8_1750) {
    OrfHeader header(littleEndian);
    EXPECT_EQ(header.offset(), 0x00000008u);
}

// Test that writing with invalidByteOrder does not set 'I' or 'M' at byte 0
TEST_F(OrfHeaderTest_1750, WriteInvalidByteOrderDoesNotSetMarker_1750) {
    OrfHeader header(invalidByteOrder);
    DataBuf buf = header.write();
    // With invalidByteOrder, the switch default case is hit, so byte 0 stays as initialized (0)
    EXPECT_NE(buf.read_uint8(0), 'I');
    EXPECT_NE(buf.read_uint8(0), 'M');
}

// Test read with valid little endian ORF header data
TEST_F(OrfHeaderTest_1750, ReadValidLittleEndianHeader_1750) {
    OrfHeader header(littleEndian);
    DataBuf writtenBuf = header.write();
    bool result = header.read(writtenBuf.c_data(0), writtenBuf.size());
    EXPECT_TRUE(result);
}

// Test read with valid big endian ORF header data
TEST_F(OrfHeaderTest_1750, ReadValidBigEndianHeader_1750) {
    OrfHeader header(bigEndian);
    DataBuf writtenBuf = header.write();
    bool result = header.read(writtenBuf.c_data(0), writtenBuf.size());
    EXPECT_TRUE(result);
}

// Test read with too small data size
TEST_F(OrfHeaderTest_1750, ReadTooSmallDataReturnsFalse_1750) {
    OrfHeader header(littleEndian);
    uint8_t data[4] = {0};
    bool result = header.read(data, 4);
    EXPECT_FALSE(result);
}

// Test read with invalid byte order markers
TEST_F(OrfHeaderTest_1750, ReadInvalidByteOrderMarkerReturnsFalse_1750) {
    OrfHeader header(littleEndian);
    uint8_t data[8] = {0};
    // Set invalid byte order markers
    data[0] = 'X';
    data[1] = 'X';
    bool result = header.read(data, 8);
    EXPECT_FALSE(result);
}

// Test that setByteOrder changes the byte order used in write
TEST_F(OrfHeaderTest_1750, SetByteOrderChangesWriteOutput_1750) {
    OrfHeader header(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);

    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);

    DataBuf buf = header.write();
    EXPECT_EQ(buf.read_uint8(0), 'M');
    EXPECT_EQ(buf.read_uint8(1), 'M');
}

// Test write then read round-trip for little endian
TEST_F(OrfHeaderTest_1750, WriteReadRoundTripLittleEndian_1750) {
    OrfHeader writeHeader(littleEndian);
    DataBuf buf = writeHeader.write();

    OrfHeader readHeader(littleEndian);
    bool result = readHeader.read(buf.c_data(0), buf.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(readHeader.byteOrder(), littleEndian);
}

// Test write then read round-trip for big endian
TEST_F(OrfHeaderTest_1750, WriteReadRoundTripBigEndian_1750) {
    OrfHeader writeHeader(bigEndian);
    DataBuf buf = writeHeader.write();

    OrfHeader readHeader(bigEndian);
    bool result = readHeader.read(buf.c_data(0), buf.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(readHeader.byteOrder(), bigEndian);
}

// Test that invalidByteOrder write produces byte 1 == byte 0 (both should be 0)
TEST_F(OrfHeaderTest_1750, WriteInvalidByteOrderByte1EqualsByte0_1750) {
    OrfHeader header(invalidByteOrder);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.read_uint8(0), buf.read_uint8(1));
}
