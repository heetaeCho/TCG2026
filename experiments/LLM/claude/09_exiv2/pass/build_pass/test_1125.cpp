#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <stdexcept>
#include <cstring>

using namespace Exiv2;

class DataBufTest_1125 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(DataBufTest_1125, DefaultConstructor_CreatesEmptyBuffer_1125) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1125, SizeConstructor_CreatesBufferOfGivenSize_1125) {
    DataBuf buf(16);
    EXPECT_EQ(buf.size(), 16u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1125, SizeConstructor_ZeroSize_1125) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1125, DataConstructor_CopiesData_1125) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.size(), 4u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

// ============================================================
// alloc / resize / reset Tests
// ============================================================

TEST_F(DataBufTest_1125, Alloc_SetsSize_1125) {
    DataBuf buf;
    buf.alloc(32);
    EXPECT_EQ(buf.size(), 32u);
}

TEST_F(DataBufTest_1125, Resize_ChangesSize_1125) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1125, Resize_Shrink_1125) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1125, Reset_ClearsBuffer_1125) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// write_uint8 / read_uint8 Tests
// ============================================================

TEST_F(DataBufTest_1125, WriteReadUint8_NormalOperation_1125) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAB);
    buf.write_uint8(1, 0xCD);
    buf.write_uint8(2, 0xEF);
    buf.write_uint8(3, 0x12);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.read_uint8(1), 0xCD);
    EXPECT_EQ(buf.read_uint8(2), 0xEF);
    EXPECT_EQ(buf.read_uint8(3), 0x12);
}

TEST_F(DataBufTest_1125, WriteUint8_LastByte_1125) {
    DataBuf buf(1);
    buf.write_uint8(0, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

// ============================================================
// write_uint16 / read_uint16 Tests
// ============================================================

TEST_F(DataBufTest_1125, WriteReadUint16_LittleEndian_1125) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1125, WriteReadUint16_BigEndian_1125) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1125, WriteReadUint16_AtOffset_1125) {
    DataBuf buf(8);
    buf.write_uint16(4, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint16(4, bigEndian), 0xABCD);
}

TEST_F(DataBufTest_1125, WriteReadUint16_EndiannessDifference_1125) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x0102, bigEndian);
    // Reading with different endianness should give different result
    uint16_t le_val = buf.read_uint16(0, littleEndian);
    uint16_t be_val = buf.read_uint16(0, bigEndian);
    EXPECT_EQ(be_val, 0x0102);
    EXPECT_NE(le_val, be_val);
}

// ============================================================
// write_uint32 / read_uint32 Tests
// ============================================================

TEST_F(DataBufTest_1125, WriteReadUint32_LittleEndian_1125) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST_F(DataBufTest_1125, WriteReadUint32_BigEndian_1125) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1125, WriteReadUint32_AtOffset_1125) {
    DataBuf buf(16);
    buf.write_uint32(8, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint32(8, bigEndian), 0xDEADBEEFu);
}

TEST_F(DataBufTest_1125, WriteReadUint32_MaxValue_1125) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xFFFFFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0xFFFFFFFFu);
}

TEST_F(DataBufTest_1125, WriteReadUint32_ZeroValue_1125) {
    DataBuf buf(4);
    buf.write_uint32(0, 0, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0u);
}

// ============================================================
// write_uint64 / read_uint64 Tests
// ============================================================

TEST_F(DataBufTest_1125, WriteReadUint64_LittleEndian_1125) {
    DataBuf buf(16);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), val);
}

TEST_F(DataBufTest_1125, WriteReadUint64_BigEndian_1125) {
    DataBuf buf(16);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), val);
}

TEST_F(DataBufTest_1125, WriteReadUint64_AtOffset_1125) {
    DataBuf buf(24);
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    buf.write_uint64(8, val, bigEndian);
    EXPECT_EQ(buf.read_uint64(8, bigEndian), val);
}

TEST_F(DataBufTest_1125, WriteReadUint64_MaxValue_1125) {
    DataBuf buf(8);
    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0xFFFFFFFFFFFFFFFFULL);
}

TEST_F(DataBufTest_1125, WriteReadUint64_ZeroValue_1125) {
    DataBuf buf(8);
    buf.write_uint64(0, 0ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0ULL);
}

TEST_F(DataBufTest_1125, WriteUint64_ExactFit_1125) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x123456789ABCDEF0ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x123456789ABCDEF0ULL);
}

// ============================================================
// write_uint64 Overflow / Boundary Tests
// ============================================================

TEST_F(DataBufTest_1125, WriteUint64_OverflowOnEmptyBuffer_1125) {
    DataBuf buf;
    EXPECT_THROW(buf.write_uint64(0, 0x1234, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1125, WriteUint64_OverflowSmallBuffer_1125) {
    DataBuf buf(7);
    EXPECT_THROW(buf.write_uint64(0, 0x1234, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1125, WriteUint64_OverflowOffsetTooLarge_1125) {
    DataBuf buf(16);
    EXPECT_THROW(buf.write_uint64(9, 0x1234, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1125, WriteUint64_OffsetAtBoundary_1125) {
    DataBuf buf(16);
    // offset 8 means bytes 8..15, which is exactly the end of a 16-byte buffer
    EXPECT_NO_THROW(buf.write_uint64(8, 0xABCDEF0123456789ULL, littleEndian));
    EXPECT_EQ(buf.read_uint64(8, littleEndian), 0xABCDEF0123456789ULL);
}

TEST_F(DataBufTest_1125, WriteUint64_OffsetJustPastBoundary_1125) {
    DataBuf buf(16);
    // offset 9 means bytes 9..16, which overflows a 16-byte buffer
    EXPECT_THROW(buf.write_uint64(9, 0x1234, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1125, WriteUint64_BufferExactly8Bytes_OffsetZero_1125) {
    DataBuf buf(8);
    EXPECT_NO_THROW(buf.write_uint64(0, 42, bigEndian));
}

TEST_F(DataBufTest_1125, WriteUint64_BufferExactly8Bytes_Offset1_1125) {
    DataBuf buf(8);
    EXPECT_THROW(buf.write_uint64(1, 42, bigEndian), std::out_of_range);
}

// ============================================================
// Endianness cross-check Tests
// ============================================================

TEST_F(DataBufTest_1125, WriteUint64_BigEndian_ReadLittleEndian_Mismatch_1125) {
    DataBuf buf(8);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, bigEndian);
    uint64_t readBE = buf.read_uint64(0, bigEndian);
    uint64_t readLE = buf.read_uint64(0, littleEndian);
    EXPECT_EQ(readBE, val);
    // When read as little-endian, it should be the byte-reversed value
    EXPECT_NE(readLE, val);
}

// ============================================================
// cmpBytes Tests
// ============================================================

TEST_F(DataBufTest_1125, CmpBytes_EqualData_1125) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.cmpBytes(0, data, 4), 0);
}

TEST_F(DataBufTest_1125, CmpBytes_PartialMatch_1125) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte partial[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(0, partial, 2), 0);
}

TEST_F(DataBufTest_1125, CmpBytes_AtOffset_1125) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte compare[] = {0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(2, compare, 2), 0);
}

TEST_F(DataBufTest_1125, CmpBytes_NotEqual_1125) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte compare[] = {0x01, 0xFF};
    EXPECT_NE(buf.cmpBytes(0, compare, 2), 0);
}

// ============================================================
// data / c_data / c_str Tests
// ============================================================

TEST_F(DataBufTest_1125, Data_ReturnsWritablePointer_1125) {
    DataBuf buf(8);
    byte* ptr = buf.data(0);
    EXPECT_NE(ptr, nullptr);
    // Writing through pointer
    ptr[0] = 0x42;
    EXPECT_EQ(buf.read_uint8(0), 0x42);
}

TEST_F(DataBufTest_1125, CData_ReturnsConstPointer_1125) {
    const byte data[] = {0xAA, 0xBB};
    DataBuf buf(data, 2);
    const byte* ptr = buf.c_data(0);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0xAA);
    EXPECT_EQ(ptr[1], 0xBB);
}

TEST_F(DataBufTest_1125, CStr_ReturnsCharPointer_1125) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(0);
    EXPECT_STREQ(str, "Hello");
}

TEST_F(DataBufTest_1125, CData_WithOffset_1125) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte* ptr = buf.c_data(2);
    EXPECT_EQ(ptr[0], 0x03);
    EXPECT_EQ(ptr[1], 0x04);
}

// ============================================================
// empty / size Tests
// ============================================================

TEST_F(DataBufTest_1125, Empty_OnDefault_1125) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1125, Empty_AfterAlloc_1125) {
    DataBuf buf;
    buf.alloc(10);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1125, Size_AfterResize_1125) {
    DataBuf buf(10);
    EXPECT_EQ(buf.size(), 10u);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// Multiple writes at different offsets
// ============================================================

TEST_F(DataBufTest_1125, MultipleWriteUint64_DifferentOffsets_1125) {
    DataBuf buf(24);
    buf.write_uint64(0, 0x1111111111111111ULL, bigEndian);
    buf.write_uint64(8, 0x2222222222222222ULL, bigEndian);
    buf.write_uint64(16, 0x3333333333333333ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x1111111111111111ULL);
    EXPECT_EQ(buf.read_uint64(8, bigEndian), 0x2222222222222222ULL);
    EXPECT_EQ(buf.read_uint64(16, bigEndian), 0x3333333333333333ULL);
}

TEST_F(DataBufTest_1125, MixedWritesSizes_1125) {
    DataBuf buf(16);
    buf.write_uint8(0, 0x01);
    buf.write_uint16(1, 0x0203, bigEndian);
    buf.write_uint32(3, 0x04050607, bigEndian);
    buf.write_uint64(7, 0x08090A0B0C0D0E0FULL, bigEndian);

    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint16(1, bigEndian), 0x0203);
    EXPECT_EQ(buf.read_uint32(3, bigEndian), 0x04050607u);
    EXPECT_EQ(buf.read_uint64(7, bigEndian), 0x08090A0B0C0D0E0FULL);
}

// ============================================================
// Overwrite tests
// ============================================================

TEST_F(DataBufTest_1125, WriteUint64_OverwritePreviousValue_1125) {
    DataBuf buf(8);
    buf.write_uint64(0, 0xAAAAAAAAAAAAAAAAULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xAAAAAAAAAAAAAAAAULL);
    buf.write_uint64(0, 0xBBBBBBBBBBBBBBBBULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xBBBBBBBBBBBBBBBBULL);
}

// ============================================================
// Iterator tests (begin/end)
// ============================================================

TEST_F(DataBufTest_1125, BeginEnd_IterateOverBuffer_1125) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, 3);
    std::vector<byte> result(buf.begin(), buf.end());
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 0x10);
    EXPECT_EQ(result[1], 0x20);
    EXPECT_EQ(result[2], 0x30);
}

TEST_F(DataBufTest_1125, BeginEnd_EmptyBuffer_1125) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}
