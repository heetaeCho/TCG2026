#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <stdexcept>
#include <cstring>

using namespace Exiv2;

class DataBufTest_1122 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Constructor Tests
// =============================================================================

TEST_F(DataBufTest_1122, DefaultConstructor_CreatesEmptyBuffer_1122) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1122, SizeConstructor_CreatesBufferOfGivenSize_1122) {
    DataBuf buf(16);
    EXPECT_EQ(buf.size(), 16u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1122, SizeConstructor_ZeroSize_CreatesEmptyBuffer_1122) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1122, DataConstructor_CopiesData_1122) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.size(), 4u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

// =============================================================================
// alloc / resize / reset Tests
// =============================================================================

TEST_F(DataBufTest_1122, Alloc_SetsSize_1122) {
    DataBuf buf;
    buf.alloc(32);
    EXPECT_EQ(buf.size(), 32u);
}

TEST_F(DataBufTest_1122, Resize_ChangesSize_1122) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1122, Resize_Shrink_1122) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1122, Reset_ClearsBuffer_1122) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// =============================================================================
// read_uint8 / write_uint8 Tests
// =============================================================================

TEST_F(DataBufTest_1122, WriteAndReadUint8_1122) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAB);
    buf.write_uint8(3, 0xCD);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.read_uint8(3), 0xCD);
}

TEST_F(DataBufTest_1122, ReadUint8_OutOfRange_Throws_1122) {
    DataBuf buf(2);
    EXPECT_THROW(buf.read_uint8(2), std::out_of_range);
}

TEST_F(DataBufTest_1122, ReadUint8_EmptyBuffer_Throws_1122) {
    DataBuf buf;
    EXPECT_THROW(buf.read_uint8(0), std::out_of_range);
}

// =============================================================================
// read_uint16 / write_uint16 Tests
// =============================================================================

TEST_F(DataBufTest_1122, WriteAndReadUint16_BigEndian_1122) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1122, WriteAndReadUint16_LittleEndian_1122) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1122, WriteAndReadUint16_WithOffset_1122) {
    DataBuf buf(8);
    buf.write_uint16(4, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint16(4, bigEndian), 0xABCD);
}

TEST_F(DataBufTest_1122, ReadUint16_InsufficientSize_Throws_1122) {
    DataBuf buf(1);
    EXPECT_THROW(buf.read_uint16(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1122, ReadUint16_OffsetOverflow_Throws_1122) {
    DataBuf buf(4);
    EXPECT_THROW(buf.read_uint16(3, bigEndian), std::out_of_range);
}

// =============================================================================
// read_uint32 / write_uint32 Tests
// =============================================================================

TEST_F(DataBufTest_1122, WriteAndReadUint32_BigEndian_1122) {
    DataBuf buf(8);
    buf.write_uint32(0, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xDEADBEEF);
}

TEST_F(DataBufTest_1122, WriteAndReadUint32_LittleEndian_1122) {
    DataBuf buf(8);
    buf.write_uint32(0, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0xDEADBEEF);
}

TEST_F(DataBufTest_1122, WriteAndReadUint32_WithOffset_1122) {
    DataBuf buf(12);
    buf.write_uint32(4, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x12345678);
}

TEST_F(DataBufTest_1122, ReadUint32_SizeLessThan4_Throws_1122) {
    DataBuf buf(3);
    EXPECT_THROW(buf.read_uint32(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1122, ReadUint32_OffsetCausesOverflow_Throws_1122) {
    DataBuf buf(6);
    EXPECT_THROW(buf.read_uint32(3, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1122, ReadUint32_ExactFit_1122) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x01020304);
}

TEST_F(DataBufTest_1122, ReadUint32_ExactFitAtOffset_1122) {
    DataBuf buf(8);
    buf.write_uint32(4, 0xCAFEBABE, littleEndian);
    EXPECT_EQ(buf.read_uint32(4, littleEndian), 0xCAFEBABE);
}

TEST_F(DataBufTest_1122, ReadUint32_OffsetAtBoundary_Throws_1122) {
    DataBuf buf(7);
    // offset=4 needs bytes 4,5,6,7 but size is 7, so byte 7 doesn't exist
    EXPECT_THROW(buf.read_uint32(4, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1122, ReadUint32_EmptyBuffer_Throws_1122) {
    DataBuf buf;
    EXPECT_THROW(buf.read_uint32(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1122, ReadUint32_ByteOrderDifference_1122) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    uint32_t be_val = buf.read_uint32(0, bigEndian);
    uint32_t le_val = buf.read_uint32(0, littleEndian);
    EXPECT_EQ(be_val, 0x01020304u);
    // Little endian reading the same bytes should give a different value
    EXPECT_NE(be_val, le_val);
}

// =============================================================================
// read_uint64 / write_uint64 Tests
// =============================================================================

TEST_F(DataBufTest_1122, WriteAndReadUint64_BigEndian_1122) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1122, WriteAndReadUint64_LittleEndian_1122) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1122, ReadUint64_InsufficientSize_Throws_1122) {
    DataBuf buf(7);
    EXPECT_THROW(buf.read_uint64(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1122, ReadUint64_OffsetOverflow_Throws_1122) {
    DataBuf buf(12);
    EXPECT_THROW(buf.read_uint64(5, bigEndian), std::out_of_range);
}

// =============================================================================
// cmpBytes Tests
// =============================================================================

TEST_F(DataBufTest_1122, CmpBytes_Equal_1122) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1122, CmpBytes_NotEqual_1122) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x04, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1122, CmpBytes_WithOffset_1122) {
    const byte data[] = {0x00, 0x00, 0x01, 0x02};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(2, cmp, 2), 0);
}

// =============================================================================
// data / c_data / c_str Tests
// =============================================================================

TEST_F(DataBufTest_1122, Data_ReturnsWritablePointer_1122) {
    DataBuf buf(4);
    byte* ptr = buf.data(0);
    EXPECT_NE(ptr, nullptr);
    ptr[0] = 0xFF;
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

TEST_F(DataBufTest_1122, CData_ReturnsConstPointer_1122) {
    const byte data[] = {0x10, 0x20};
    DataBuf buf(data, 2);
    const byte* ptr = buf.c_data(0);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0x10);
    EXPECT_EQ(ptr[1], 0x20);
}

TEST_F(DataBufTest_1122, CStr_ReturnsCharPointer_1122) {
    const byte data[] = {'H', 'i', '\0'};
    DataBuf buf(data, 3);
    const char* str = buf.c_str(0);
    EXPECT_STREQ(str, "Hi");
}

TEST_F(DataBufTest_1122, DataWithOffset_1122) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    byte* ptr = buf.data(2);
    EXPECT_EQ(*ptr, 0x03);
}

// =============================================================================
// size / empty Tests
// =============================================================================

TEST_F(DataBufTest_1122, Size_ReturnsCorrectSize_1122) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
}

TEST_F(DataBufTest_1122, Empty_TrueForDefault_1122) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1122, Empty_FalseForNonEmpty_1122) {
    DataBuf buf(1);
    EXPECT_FALSE(buf.empty());
}

// =============================================================================
// begin / end iterator Tests
// =============================================================================

TEST_F(DataBufTest_1122, BeginEnd_IterableRange_1122) {
    const byte data[] = {0x0A, 0x0B, 0x0C};
    DataBuf buf(data, 3);
    std::vector<byte> collected(buf.begin(), buf.end());
    ASSERT_EQ(collected.size(), 3u);
    EXPECT_EQ(collected[0], 0x0A);
    EXPECT_EQ(collected[1], 0x0B);
    EXPECT_EQ(collected[2], 0x0C);
}

TEST_F(DataBufTest_1122, BeginEnd_EmptyBuffer_1122) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}

// =============================================================================
// Mixed read/write across types
// =============================================================================

TEST_F(DataBufTest_1122, MixedReadWrite_MultipleTypes_1122) {
    DataBuf buf(16);
    buf.write_uint8(0, 0x11);
    buf.write_uint16(1, 0x2233, bigEndian);
    buf.write_uint32(4, 0x44556677, littleEndian);
    buf.write_uint64(8, 0x8899AABBCCDDEEFFULL, bigEndian);

    EXPECT_EQ(buf.read_uint8(0), 0x11);
    EXPECT_EQ(buf.read_uint16(1, bigEndian), 0x2233);
    EXPECT_EQ(buf.read_uint32(4, littleEndian), 0x44556677u);
    EXPECT_EQ(buf.read_uint64(8, bigEndian), 0x8899AABBCCDDEEFFULL);
}

// =============================================================================
// Boundary: exact size for read_uint32
// =============================================================================

TEST_F(DataBufTest_1122, ReadUint32_Size4Offset0_Success_1122) {
    DataBuf buf(4);
    buf.write_uint32(0, 42, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 42u);
}

TEST_F(DataBufTest_1122, ReadUint32_Size4Offset1_Throws_1122) {
    DataBuf buf(4);
    EXPECT_THROW(buf.read_uint32(1, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1122, ReadUint32_Size5Offset1_Success_1122) {
    DataBuf buf(5);
    buf.write_uint32(1, 0xAABBCCDD, littleEndian);
    EXPECT_EQ(buf.read_uint32(1, littleEndian), 0xAABBCCDD);
}

// =============================================================================
// Write then resize then read
// =============================================================================

TEST_F(DataBufTest_1122, ResizePreservesData_1122) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x12345678, bigEndian);
    buf.resize(8);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1122, AllocAfterData_1122) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAA);
    buf.alloc(8);
    // After alloc, data may or may not be preserved - test that size is correct
    EXPECT_EQ(buf.size(), 8u);
}

// =============================================================================
// Zero value tests
// =============================================================================

TEST_F(DataBufTest_1122, WriteAndReadZeroValues_1122) {
    DataBuf buf(8);
    buf.write_uint8(0, 0);
    buf.write_uint16(1, 0, bigEndian);
    buf.write_uint32(4, 0, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0u);
    EXPECT_EQ(buf.read_uint16(1, bigEndian), 0u);
    EXPECT_EQ(buf.read_uint32(4, littleEndian), 0u);
}

// =============================================================================
// Max value tests
// =============================================================================

TEST_F(DataBufTest_1122, WriteAndReadMaxUint32_1122) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

TEST_F(DataBufTest_1122, WriteAndReadMaxUint16_1122) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0xFFFFu);
}

TEST_F(DataBufTest_1122, WriteAndReadMaxUint8_1122) {
    DataBuf buf(1);
    buf.write_uint8(0, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0xFFu);
}
