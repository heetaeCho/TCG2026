#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>
#include <stdexcept>

using namespace Exiv2;

class DataBufCmpBytesTest_1126 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: compare matching bytes at offset 0
TEST_F(DataBufCmpBytesTest_1126, CmpBytesEqualAtOffsetZero_1126) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    EXPECT_EQ(0, buf.cmpBytes(0, cmp, sizeof(cmp)));
}

// Normal operation: compare matching bytes at non-zero offset
TEST_F(DataBufCmpBytesTest_1126, CmpBytesEqualAtNonZeroOffset_1126) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x02, 0x03, 0x04};
    EXPECT_EQ(0, buf.cmpBytes(2, cmp, sizeof(cmp)));
}

// Normal operation: compare non-matching bytes - buffer data is less
TEST_F(DataBufCmpBytesTest_1126, CmpBytesNotEqualLessThan_1126) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01, 0x02, 0x04};
    EXPECT_LT(buf.cmpBytes(0, cmp, sizeof(cmp)), 0);
}

// Normal operation: compare non-matching bytes - buffer data is greater
TEST_F(DataBufCmpBytesTest_1126, CmpBytesNotEqualGreaterThan_1126) {
    const byte data[] = {0x01, 0x02, 0x05};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01, 0x02, 0x04};
    EXPECT_GT(buf.cmpBytes(0, cmp, sizeof(cmp)), 0);
}

// Boundary: compare single byte at last position
TEST_F(DataBufCmpBytesTest_1126, CmpBytesSingleByteAtEnd_1126) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x30};
    EXPECT_EQ(0, buf.cmpBytes(2, cmp, 1));
}

// Boundary: compare zero bytes (bufsize = 0)
TEST_F(DataBufCmpBytesTest_1126, CmpBytesZeroSize_1126) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0xFF};
    EXPECT_EQ(0, buf.cmpBytes(0, cmp, 0));
}

// Boundary: compare entire buffer
TEST_F(DataBufCmpBytesTest_1126, CmpBytesEntireBuffer_1126) {
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0xAA, 0xBB, 0xCC, 0xDD};
    EXPECT_EQ(0, buf.cmpBytes(0, cmp, sizeof(cmp)));
}

// Error: offset + bufsize exceeds buffer size (overflow)
TEST_F(DataBufCmpBytesTest_1126, CmpBytesThrowsOnOverflow_1126) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x02, 0x03, 0x04};
    EXPECT_THROW(buf.cmpBytes(1, cmp, sizeof(cmp)), std::out_of_range);
}

// Error: bufsize larger than buffer size
TEST_F(DataBufCmpBytesTest_1126, CmpBytesThrowsWhenBufsizeTooLarge_1126) {
    const byte data[] = {0x01, 0x02};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01, 0x02, 0x03};
    EXPECT_THROW(buf.cmpBytes(0, cmp, sizeof(cmp)), std::out_of_range);
}

// Error: offset beyond buffer size
TEST_F(DataBufCmpBytesTest_1126, CmpBytesThrowsWhenOffsetBeyondSize_1126) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01};
    EXPECT_THROW(buf.cmpBytes(10, cmp, sizeof(cmp)), std::out_of_range);
}

// Error: empty buffer with non-zero bufsize
TEST_F(DataBufCmpBytesTest_1126, CmpBytesThrowsOnEmptyBuffer_1126) {
    DataBuf buf;
    const byte cmp[] = {0x01};
    EXPECT_THROW(buf.cmpBytes(0, cmp, sizeof(cmp)), std::out_of_range);
}

// Boundary: empty buffer with zero bufsize should not throw
TEST_F(DataBufCmpBytesTest_1126, CmpBytesEmptyBufferZeroSize_1126) {
    DataBuf buf;
    const byte cmp[] = {0x01};
    EXPECT_EQ(0, buf.cmpBytes(0, cmp, 0));
}

// Boundary: offset at exact end of buffer with bufsize 0
TEST_F(DataBufCmpBytesTest_1126, CmpBytesOffsetAtEndZeroBufsize_1126) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01};
    EXPECT_EQ(0, buf.cmpBytes(3, cmp, 0));
}

// Normal: compare partial match at beginning
TEST_F(DataBufCmpBytesTest_1126, CmpBytesPartialPrefix_1126) {
    const byte data[] = {0x41, 0x42, 0x43, 0x44};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x41, 0x42};
    EXPECT_EQ(0, buf.cmpBytes(0, cmp, sizeof(cmp)));
}

// Normal: compare with offset and mismatch
TEST_F(DataBufCmpBytesTest_1126, CmpBytesOffsetMismatch_1126) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01, 0x03};
    int result = buf.cmpBytes(1, cmp, sizeof(cmp));
    // data[1]=0x01, data[2]=0x02 vs cmp[0]=0x01, cmp[1]=0x03 => 0x02 < 0x03
    EXPECT_LT(result, 0);
}

// Boundary: large offset causing overflow arithmetic
TEST_F(DataBufCmpBytesTest_1126, CmpBytesThrowsOnLargeOffset_1126) {
    const byte data[] = {0x01};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01};
    EXPECT_THROW(buf.cmpBytes(SIZE_MAX, cmp, 1), std::out_of_range);
}

// Boundary: large bufsize causing overflow
TEST_F(DataBufCmpBytesTest_1126, CmpBytesThrowsOnLargeBufsize_1126) {
    const byte data[] = {0x01};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01};
    EXPECT_THROW(buf.cmpBytes(0, cmp, SIZE_MAX), std::out_of_range);
}

// Test with DataBuf constructed with size (zero-initialized)
TEST_F(DataBufCmpBytesTest_1126, CmpBytesWithSizeConstructor_1126) {
    DataBuf buf(4);
    const byte cmp[] = {0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(0, buf.cmpBytes(0, cmp, sizeof(cmp)));
}

// Test comparison with single byte
TEST_F(DataBufCmpBytesTest_1126, CmpBytesSingleByte_1126) {
    const byte data[] = {0xFF};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0xFF};
    EXPECT_EQ(0, buf.cmpBytes(0, cmp, 1));
}

// Test that offset exactly at boundary works
TEST_F(DataBufCmpBytesTest_1126, CmpBytesExactBoundary_1126) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x04, 0x05};
    EXPECT_EQ(0, buf.cmpBytes(3, cmp, 2));
}

// Test that offset one past boundary throws
TEST_F(DataBufCmpBytesTest_1126, CmpBytesOnePastBoundary_1126) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x05, 0x06};
    EXPECT_THROW(buf.cmpBytes(4, cmp, 2), std::out_of_range);
}
