#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>
#include <stdexcept>

using namespace Exiv2;

class DataBufTest_1124 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(DataBufTest_1124, DefaultConstructor_CreatesEmptyBuffer_1124) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1124, SizeConstructor_AllocatesGivenSize_1124) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1124, SizeConstructor_ZeroSize_1124) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1124, DataConstructor_CopiesData_1124) {
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

TEST_F(DataBufTest_1124, Alloc_SetsSize_1124) {
    DataBuf buf;
    buf.alloc(50);
    EXPECT_EQ(buf.size(), 50u);
}

TEST_F(DataBufTest_1124, Resize_ChangesSize_1124) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1124, Resize_ShrinkSize_1124) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1124, Reset_ClearsBuffer_1124) {
    DataBuf buf(100);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// read_uint8 / write_uint8 Tests
// ============================================================

TEST_F(DataBufTest_1124, WriteAndReadUint8_1124) {
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

TEST_F(DataBufTest_1124, ReadUint8_BoundaryValues_1124) {
    DataBuf buf(1);
    buf.write_uint8(0, 0x00);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
    buf.write_uint8(0, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

// ============================================================
// read_uint16 / write_uint16 Tests
// ============================================================

TEST_F(DataBufTest_1124, WriteAndReadUint16_BigEndian_1124) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1124, WriteAndReadUint16_LittleEndian_1124) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1124, WriteUint16_BigEndian_ByteLayout_1124) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.read_uint8(1), 0xCD);
}

TEST_F(DataBufTest_1124, WriteUint16_LittleEndian_ByteLayout_1124) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xABCD, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xCD);
    EXPECT_EQ(buf.read_uint8(1), 0xAB);
}

TEST_F(DataBufTest_1124, WriteAndReadUint16_AtOffset_1124) {
    DataBuf buf(10);
    buf.write_uint16(4, 0x5678, bigEndian);
    EXPECT_EQ(buf.read_uint16(4, bigEndian), 0x5678);
}

// ============================================================
// read_uint32 / write_uint32 Tests
// ============================================================

TEST_F(DataBufTest_1124, WriteAndReadUint32_BigEndian_1124) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1124, WriteAndReadUint32_LittleEndian_1124) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST_F(DataBufTest_1124, WriteUint32_BigEndian_ByteLayout_1124) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xDE);
    EXPECT_EQ(buf.read_uint8(1), 0xAD);
    EXPECT_EQ(buf.read_uint8(2), 0xBE);
    EXPECT_EQ(buf.read_uint8(3), 0xEF);
}

TEST_F(DataBufTest_1124, WriteUint32_LittleEndian_ByteLayout_1124) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xEF);
    EXPECT_EQ(buf.read_uint8(1), 0xBE);
    EXPECT_EQ(buf.read_uint8(2), 0xAD);
    EXPECT_EQ(buf.read_uint8(3), 0xDE);
}

TEST_F(DataBufTest_1124, WriteAndReadUint32_AtOffset_1124) {
    DataBuf buf(12);
    buf.write_uint32(4, 0xCAFEBABE, littleEndian);
    EXPECT_EQ(buf.read_uint32(4, littleEndian), 0xCAFEBABEu);
}

// ============================================================
// read_uint64 / write_uint64 Tests
// ============================================================

TEST_F(DataBufTest_1124, WriteAndReadUint64_BigEndian_1124) {
    DataBuf buf(16);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), val);
}

TEST_F(DataBufTest_1124, WriteAndReadUint64_LittleEndian_1124) {
    DataBuf buf(16);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), val);
}

TEST_F(DataBufTest_1124, WriteAndReadUint64_AtOffset_1124) {
    DataBuf buf(20);
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    buf.write_uint64(8, val, bigEndian);
    EXPECT_EQ(buf.read_uint64(8, bigEndian), val);
}

TEST_F(DataBufTest_1124, ReadUint64_MaxValue_1124) {
    DataBuf buf(8);
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    buf.write_uint64(0, val, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), val);
}

TEST_F(DataBufTest_1124, ReadUint64_ZeroValue_1124) {
    DataBuf buf(8);
    buf.write_uint64(0, 0, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0u);
}

// ============================================================
// read_uint64 Overflow/Boundary Error Tests
// ============================================================

TEST_F(DataBufTest_1124, ReadUint64_EmptyBuffer_ThrowsOutOfRange_1124) {
    DataBuf buf;
    EXPECT_THROW(buf.read_uint64(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1124, ReadUint64_BufferTooSmall_ThrowsOutOfRange_1124) {
    DataBuf buf(7);
    EXPECT_THROW(buf.read_uint64(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1124, ReadUint64_OffsetCausesOverflow_ThrowsOutOfRange_1124) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x1234567890ABCDEFULL, bigEndian);
    // offset=1 means we need bytes 1..8, but buffer is only 8 bytes (indices 0..7)
    EXPECT_THROW(buf.read_uint64(1, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1124, ReadUint64_ExactFit_NoThrow_1124) {
    DataBuf buf(8);
    buf.write_uint64(0, 42, bigEndian);
    EXPECT_NO_THROW(buf.read_uint64(0, bigEndian));
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 42u);
}

TEST_F(DataBufTest_1124, ReadUint64_LargeOffset_ThrowsOutOfRange_1124) {
    DataBuf buf(16);
    // offset=9 means bytes 9..16, but buffer is only 16 bytes (indices 0..15)
    EXPECT_THROW(buf.read_uint64(9, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1124, ReadUint64_MaxValidOffset_1124) {
    DataBuf buf(16);
    uint64_t val = 0xABCDEF0123456789ULL;
    buf.write_uint64(8, val, littleEndian);
    EXPECT_EQ(buf.read_uint64(8, littleEndian), val);
}

// ============================================================
// cmpBytes Tests
// ============================================================

TEST_F(DataBufTest_1124, CmpBytes_Equal_1124) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1124, CmpBytes_NotEqual_1124) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x04, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1124, CmpBytes_AtOffset_1124) {
    const byte data[] = {0x00, 0x00, 0xAB, 0xCD};
    DataBuf buf(data, 4);
    const byte cmp[] = {0xAB, 0xCD};
    EXPECT_EQ(buf.cmpBytes(2, cmp, 2), 0);
}

TEST_F(DataBufTest_1124, CmpBytes_PartialCompare_1124) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

// ============================================================
// data / c_data / c_str Tests
// ============================================================

TEST_F(DataBufTest_1124, Data_ReturnsModifiablePointer_1124) {
    DataBuf buf(4);
    byte* ptr = buf.data(0);
    ASSERT_NE(ptr, nullptr);
    ptr[0] = 0xAA;
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
}

TEST_F(DataBufTest_1124, CData_ReturnsConstPointer_1124) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data(0);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0x10);
    EXPECT_EQ(ptr[1], 0x20);
    EXPECT_EQ(ptr[2], 0x30);
}

TEST_F(DataBufTest_1124, CData_AtOffset_1124) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data(1);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0x20);
}

TEST_F(DataBufTest_1124, CStr_ReturnsCharPointer_1124) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(0);
    EXPECT_STREQ(str, "Hello");
}

// ============================================================
// size / empty Tests
// ============================================================

TEST_F(DataBufTest_1124, Size_AfterAlloc_1124) {
    DataBuf buf;
    buf.alloc(42);
    EXPECT_EQ(buf.size(), 42u);
}

TEST_F(DataBufTest_1124, Empty_OnDefaultConstructed_1124) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1124, Empty_AfterAlloc_1124) {
    DataBuf buf;
    buf.alloc(10);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1124, Empty_AfterReset_1124) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// ByteOrder cross-read tests (endianness correctness)
// ============================================================

TEST_F(DataBufTest_1124, ReadUint64_BigEndian_ByteLayout_1124) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(1, 0x02);
    buf.write_uint8(2, 0x03);
    buf.write_uint8(3, 0x04);
    buf.write_uint8(4, 0x05);
    buf.write_uint8(5, 0x06);
    buf.write_uint8(6, 0x07);
    buf.write_uint8(7, 0x08);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1124, ReadUint64_LittleEndian_ByteLayout_1124) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x08);
    buf.write_uint8(1, 0x07);
    buf.write_uint8(2, 0x06);
    buf.write_uint8(3, 0x05);
    buf.write_uint8(4, 0x04);
    buf.write_uint8(5, 0x03);
    buf.write_uint8(6, 0x02);
    buf.write_uint8(7, 0x01);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

// ============================================================
// Multiple writes at different offsets
// ============================================================

TEST_F(DataBufTest_1124, MultipleUint32Writes_1124) {
    DataBuf buf(12);
    buf.write_uint32(0, 0x11111111, bigEndian);
    buf.write_uint32(4, 0x22222222, bigEndian);
    buf.write_uint32(8, 0x33333333, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x11111111u);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x22222222u);
    EXPECT_EQ(buf.read_uint32(8, bigEndian), 0x33333333u);
}

TEST_F(DataBufTest_1124, OverwriteValue_1124) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x1111111111111111ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x1111111111111111ULL);
    buf.write_uint64(0, 0x2222222222222222ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x2222222222222222ULL);
}

// ============================================================
// begin / end iterator tests
// ============================================================

TEST_F(DataBufTest_1124, BeginEnd_IterableRange_1124) {
    const byte data[] = {0x0A, 0x0B, 0x0C};
    DataBuf buf(data, 3);
    auto it = buf.begin();
    EXPECT_EQ(*it, 0x0A);
    ++it;
    EXPECT_EQ(*it, 0x0B);
    ++it;
    EXPECT_EQ(*it, 0x0C);
    ++it;
    EXPECT_EQ(it, buf.end());
}

TEST_F(DataBufTest_1124, BeginEnd_EmptyBuffer_1124) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}

// ============================================================
// Resize preserves existing data
// ============================================================

TEST_F(DataBufTest_1124, Resize_PreservesExistingData_1124) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    buf.resize(8);
    EXPECT_EQ(buf.size(), 8u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}
