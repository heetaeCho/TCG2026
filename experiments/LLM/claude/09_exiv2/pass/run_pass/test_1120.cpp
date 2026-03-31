#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <stdexcept>

using namespace Exiv2;

class DataBufTest_1120 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(DataBufTest_1120, DefaultConstructor_CreatesEmptyBuffer_1120) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1120, SizeConstructor_CreatesBufferOfGivenSize_1120) {
    DataBuf buf(10);
    EXPECT_EQ(buf.size(), 10u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1120, SizeConstructor_ZeroSize_1120) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1120, DataConstructor_CopiesData_1120) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    EXPECT_EQ(buf.size(), 4u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

// ============================================================
// alloc, resize, reset Tests
// ============================================================

TEST_F(DataBufTest_1120, Alloc_SetsSize_1120) {
    DataBuf buf;
    buf.alloc(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1120, Resize_ChangesSize_1120) {
    DataBuf buf(10);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
    buf.resize(15);
    EXPECT_EQ(buf.size(), 15u);
}

TEST_F(DataBufTest_1120, Reset_ClearsBuffer_1120) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// read_uint8 / write_uint8 Tests
// ============================================================

TEST_F(DataBufTest_1120, ReadWriteUint8_Normal_1120) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAB);
    buf.write_uint8(1, 0xCD);
    buf.write_uint8(2, 0xEF);
    buf.write_uint8(3, 0x01);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.read_uint8(1), 0xCD);
    EXPECT_EQ(buf.read_uint8(2), 0xEF);
    EXPECT_EQ(buf.read_uint8(3), 0x01);
}

TEST_F(DataBufTest_1120, ReadUint8_BoundaryValues_1120) {
    DataBuf buf(2);
    buf.write_uint8(0, 0x00);
    buf.write_uint8(1, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
    EXPECT_EQ(buf.read_uint8(1), 0xFF);
}

// ============================================================
// read_uint16 / write_uint16 Tests
// ============================================================

TEST_F(DataBufTest_1120, ReadUint16_LittleEndian_1120) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1120, ReadUint16_BigEndian_1120) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1120, ReadUint16_AtOffset_1120) {
    DataBuf buf(6);
    buf.write_uint16(2, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 0xABCD);
}

TEST_F(DataBufTest_1120, ReadUint16_LastValidOffset_1120) {
    DataBuf buf(4);
    buf.write_uint16(2, 0x5678, littleEndian);
    EXPECT_EQ(buf.read_uint16(2, littleEndian), 0x5678);
}

TEST_F(DataBufTest_1120, ReadUint16_OverflowThrows_1120) {
    DataBuf buf(2);
    // Offset 1 means we need bytes at index 1 and 2, but size is 2 (indices 0,1)
    EXPECT_THROW(buf.read_uint16(1, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1120, ReadUint16_EmptyBufferThrows_1120) {
    DataBuf buf;
    EXPECT_THROW(buf.read_uint16(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1120, ReadUint16_SizeOneThrows_1120) {
    DataBuf buf(1);
    EXPECT_THROW(buf.read_uint16(0, littleEndian), std::out_of_range);
}

TEST_F(DataBufTest_1120, ReadUint16_ExactSizeTwoAtOffsetZero_1120) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0102, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x0102);
}

TEST_F(DataBufTest_1120, ReadUint16_OffsetEqualsSizeThrows_1120) {
    DataBuf buf(4);
    EXPECT_THROW(buf.read_uint16(4, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1120, ReadUint16_OffsetBeyondSizeThrows_1120) {
    DataBuf buf(4);
    EXPECT_THROW(buf.read_uint16(100, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1120, ReadUint16_ByteOrderMatters_1120) {
    DataBuf buf(2);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(1, 0x02);
    uint16_t be = buf.read_uint16(0, bigEndian);
    uint16_t le = buf.read_uint16(0, littleEndian);
    EXPECT_EQ(be, 0x0102);
    EXPECT_EQ(le, 0x0201);
}

TEST_F(DataBufTest_1120, WriteReadUint16_ZeroValue_1120) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0000, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x0000);
}

TEST_F(DataBufTest_1120, WriteReadUint16_MaxValue_1120) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0xFFFF);
}

// ============================================================
// read_uint32 / write_uint32 Tests
// ============================================================

TEST_F(DataBufTest_1120, ReadWriteUint32_BigEndian_1120) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1120, ReadWriteUint32_LittleEndian_1120) {
    DataBuf buf(8);
    buf.write_uint32(2, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint32(2, littleEndian), 0xDEADBEEFu);
}

TEST_F(DataBufTest_1120, ReadUint32_OverflowThrows_1120) {
    DataBuf buf(4);
    EXPECT_THROW(buf.read_uint32(1, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1120, ReadUint32_EmptyBufferThrows_1120) {
    DataBuf buf;
    EXPECT_THROW(buf.read_uint32(0, bigEndian), std::out_of_range);
}

// ============================================================
// read_uint64 / write_uint64 Tests
// ============================================================

TEST_F(DataBufTest_1120, ReadWriteUint64_BigEndian_1120) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1120, ReadWriteUint64_LittleEndian_1120) {
    DataBuf buf(16);
    buf.write_uint64(4, 0xFEDCBA9876543210ULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(4, littleEndian), 0xFEDCBA9876543210ULL);
}

TEST_F(DataBufTest_1120, ReadUint64_OverflowThrows_1120) {
    DataBuf buf(8);
    EXPECT_THROW(buf.read_uint64(1, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1120, ReadUint64_EmptyBufferThrows_1120) {
    DataBuf buf;
    EXPECT_THROW(buf.read_uint64(0, bigEndian), std::out_of_range);
}

// ============================================================
// cmpBytes Tests
// ============================================================

TEST_F(DataBufTest_1120, CmpBytes_Equal_1120) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, sizeof(cmp)), 0);
}

TEST_F(DataBufTest_1120, CmpBytes_NotEqual_1120) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01, 0x02, 0x04, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, sizeof(cmp)), 0);
}

TEST_F(DataBufTest_1120, CmpBytes_WithOffset_1120) {
    const byte data[] = {0xAA, 0xBB, 0x01, 0x02};
    DataBuf buf(data, sizeof(data));
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(2, cmp, sizeof(cmp)), 0);
}

// ============================================================
// data, c_data, c_str Tests
// ============================================================

TEST_F(DataBufTest_1120, Data_ReturnsNonNull_1120) {
    DataBuf buf(10);
    EXPECT_NE(buf.data(0), nullptr);
}

TEST_F(DataBufTest_1120, CData_ReturnsNonNull_1120) {
    DataBuf buf(10);
    EXPECT_NE(buf.c_data(0), nullptr);
}

TEST_F(DataBufTest_1120, CStr_ReturnsNonNull_1120) {
    DataBuf buf(10);
    EXPECT_NE(buf.c_str(0), nullptr);
}

TEST_F(DataBufTest_1120, Data_CanModifyData_1120) {
    DataBuf buf(4);
    byte* ptr = buf.data(0);
    ptr[0] = 0x42;
    EXPECT_EQ(buf.read_uint8(0), 0x42);
}

TEST_F(DataBufTest_1120, CData_WithOffset_1120) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, sizeof(data));
    const byte* ptr = buf.c_data(1);
    EXPECT_EQ(*ptr, 0x20);
}

// ============================================================
// empty / size Tests
// ============================================================

TEST_F(DataBufTest_1120, Empty_AfterDefaultConstruction_1120) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1120, Empty_AfterAlloc_1120) {
    DataBuf buf;
    buf.alloc(5);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1120, Size_AfterResize_1120) {
    DataBuf buf(10);
    EXPECT_EQ(buf.size(), 10u);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// begin / end Tests
// ============================================================

TEST_F(DataBufTest_1120, BeginEnd_IterableRange_1120) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, sizeof(data));
    size_t count = 0;
    for (auto it = buf.begin(); it != buf.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3u);
}

TEST_F(DataBufTest_1120, BeginEnd_EmptyBuffer_1120) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}

// ============================================================
// Cross-endian consistency Tests
// ============================================================

TEST_F(DataBufTest_1120, WriteUint16BE_ReadUint16LE_DifferentValues_1120) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0102, bigEndian);
    // Reading as little endian should give a different value (unless symmetric)
    uint16_t le_val = buf.read_uint16(0, littleEndian);
    EXPECT_EQ(le_val, 0x0201);
}

TEST_F(DataBufTest_1120, WriteUint32BE_ReadUint32LE_1120) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    uint32_t le_val = buf.read_uint32(0, littleEndian);
    EXPECT_EQ(le_val, 0x04030201u);
}

// ============================================================
// Multiple writes at different offsets
// ============================================================

TEST_F(DataBufTest_1120, MultipleUint16Writes_1120) {
    DataBuf buf(8);
    buf.write_uint16(0, 0x1111, bigEndian);
    buf.write_uint16(2, 0x2222, bigEndian);
    buf.write_uint16(4, 0x3333, bigEndian);
    buf.write_uint16(6, 0x4444, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1111);
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 0x2222);
    EXPECT_EQ(buf.read_uint16(4, bigEndian), 0x3333);
    EXPECT_EQ(buf.read_uint16(6, bigEndian), 0x4444);
}

// ============================================================
// Overwrite tests
// ============================================================

TEST_F(DataBufTest_1120, OverwriteUint16_1120) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
    buf.write_uint16(0, 0x5678, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x5678);
}
