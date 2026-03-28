#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <stdexcept>
#include <cstring>

using namespace Exiv2;

class DataBufTest_1123 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(DataBufTest_1123, DefaultConstructor_CreatesEmptyBuffer_1123) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1123, SizeConstructor_CreatesBufferOfGivenSize_1123) {
    DataBuf buf(16);
    EXPECT_EQ(buf.size(), 16u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1123, SizeConstructor_ZeroSize_CreatesEmptyBuffer_1123) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1123, DataConstructor_CopiesData_1123) {
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

TEST_F(DataBufTest_1123, Alloc_SetsBufferSize_1123) {
    DataBuf buf;
    buf.alloc(32);
    EXPECT_EQ(buf.size(), 32u);
}

TEST_F(DataBufTest_1123, Resize_ChangesBufferSize_1123) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1123, Resize_ShrinkBuffer_1123) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1123, Reset_ClearsBuffer_1123) {
    DataBuf buf(16);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// write_uint32 / read_uint32 Tests
// ============================================================

TEST_F(DataBufTest_1123, WriteUint32_LittleEndian_ReadBack_1123) {
    DataBuf buf(8);
    uint32_t value = 0x12345678;
    buf.write_uint32(0, value, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), value);
}

TEST_F(DataBufTest_1123, WriteUint32_BigEndian_ReadBack_1123) {
    DataBuf buf(8);
    uint32_t value = 0x12345678;
    buf.write_uint32(0, value, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), value);
}

TEST_F(DataBufTest_1123, WriteUint32_AtOffset_1123) {
    DataBuf buf(8);
    uint32_t value = 0xDEADBEEF;
    buf.write_uint32(4, value, bigEndian);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), value);
}

TEST_F(DataBufTest_1123, WriteUint32_AtMaxValidOffset_1123) {
    DataBuf buf(8);
    uint32_t value = 0xCAFEBABE;
    buf.write_uint32(4, value, littleEndian);
    EXPECT_EQ(buf.read_uint32(4, littleEndian), value);
}

TEST_F(DataBufTest_1123, WriteUint32_OverflowThrows_1123) {
    DataBuf buf(4);
    EXPECT_THROW(buf.write_uint32(1, 0x12345678, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1123, WriteUint32_ExactFit_1123) {
    DataBuf buf(4);
    EXPECT_NO_THROW(buf.write_uint32(0, 0x12345678, bigEndian));
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1123, WriteUint32_EmptyBuffer_Throws_1123) {
    DataBuf buf;
    EXPECT_THROW(buf.write_uint32(0, 0x12345678, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1123, WriteUint32_BufferTooSmall_Throws_1123) {
    DataBuf buf(3);
    EXPECT_THROW(buf.write_uint32(0, 0x12345678, littleEndian), std::out_of_range);
}

TEST_F(DataBufTest_1123, WriteUint32_OffsetCausesOverflow_Throws_1123) {
    DataBuf buf(8);
    EXPECT_THROW(buf.write_uint32(5, 0x12345678, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1123, WriteUint32_LargeOffset_Throws_1123) {
    DataBuf buf(8);
    EXPECT_THROW(buf.write_uint32(100, 0x12345678, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1123, WriteUint32_ZeroValue_1123) {
    DataBuf buf(4);
    buf.write_uint32(0, 0, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0u);
}

TEST_F(DataBufTest_1123, WriteUint32_MaxValue_1123) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xFFFFFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0xFFFFFFFFu);
}

TEST_F(DataBufTest_1123, WriteUint32_DifferentEndianness_GivesDifferentBytes_1123) {
    DataBuf bufBE(4);
    DataBuf bufLE(4);
    uint32_t value = 0x01020304;
    bufBE.write_uint32(0, value, bigEndian);
    bufLE.write_uint32(0, value, littleEndian);

    // Reading with the wrong endianness should give a different value (unless value is palindromic)
    EXPECT_NE(bufBE.read_uint32(0, littleEndian), value);
    EXPECT_NE(bufLE.read_uint32(0, bigEndian), value);
}

// ============================================================
// write_uint8 / read_uint8 Tests
// ============================================================

TEST_F(DataBufTest_1123, WriteUint8_ReadBack_1123) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAB);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
}

TEST_F(DataBufTest_1123, WriteUint8_AtLastPosition_1123) {
    DataBuf buf(4);
    buf.write_uint8(3, 0xFF);
    EXPECT_EQ(buf.read_uint8(3), 0xFF);
}

// ============================================================
// write_uint16 / read_uint16 Tests
// ============================================================

TEST_F(DataBufTest_1123, WriteUint16_BigEndian_ReadBack_1123) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1123, WriteUint16_LittleEndian_ReadBack_1123) {
    DataBuf buf(4);
    buf.write_uint16(2, 0xABCD, littleEndian);
    EXPECT_EQ(buf.read_uint16(2, littleEndian), 0xABCD);
}

// ============================================================
// write_uint64 / read_uint64 Tests
// ============================================================

TEST_F(DataBufTest_1123, WriteUint64_BigEndian_ReadBack_1123) {
    DataBuf buf(8);
    uint64_t value = 0x0102030405060708ULL;
    buf.write_uint64(0, value, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), value);
}

TEST_F(DataBufTest_1123, WriteUint64_LittleEndian_ReadBack_1123) {
    DataBuf buf(8);
    uint64_t value = 0xDEADBEEFCAFEBABEULL;
    buf.write_uint64(0, value, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), value);
}

// ============================================================
// data / c_data / c_str Tests
// ============================================================

TEST_F(DataBufTest_1123, Data_ReturnsNonNullForNonEmptyBuffer_1123) {
    DataBuf buf(8);
    EXPECT_NE(buf.data(0), nullptr);
}

TEST_F(DataBufTest_1123, CData_ReturnsNonNullForNonEmptyBuffer_1123) {
    DataBuf buf(8);
    EXPECT_NE(buf.c_data(0), nullptr);
}

TEST_F(DataBufTest_1123, CStr_ReturnsNonNullForNonEmptyBuffer_1123) {
    DataBuf buf(8);
    EXPECT_NE(buf.c_str(0), nullptr);
}

TEST_F(DataBufTest_1123, Data_WithOffset_ReturnsCorrectPointer_1123) {
    DataBuf buf(8);
    buf.write_uint8(4, 0x42);
    byte* p = buf.data(4);
    EXPECT_EQ(*p, 0x42);
}

// ============================================================
// cmpBytes Tests
// ============================================================

TEST_F(DataBufTest_1123, CmpBytes_EqualData_ReturnsZero_1123) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.cmpBytes(0, data, 4), 0);
}

TEST_F(DataBufTest_1123, CmpBytes_DifferentData_ReturnsNonZero_1123) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    const byte other[] = {0x01, 0x02, 0x03, 0x05};
    DataBuf buf(data, 4);
    EXPECT_NE(buf.cmpBytes(0, other, 4), 0);
}

TEST_F(DataBufTest_1123, CmpBytes_PartialCompare_1123) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    const byte partial[] = {0x01, 0x02};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.cmpBytes(0, partial, 2), 0);
}

TEST_F(DataBufTest_1123, CmpBytes_WithOffset_1123) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    const byte expected[] = {0x03, 0x04};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.cmpBytes(2, expected, 2), 0);
}

// ============================================================
// empty / size Tests
// ============================================================

TEST_F(DataBufTest_1123, Empty_ReturnsTrueForDefault_1123) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1123, Empty_ReturnsFalseAfterAlloc_1123) {
    DataBuf buf;
    buf.alloc(10);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1123, Size_ReturnsCorrectValue_1123) {
    DataBuf buf(42);
    EXPECT_EQ(buf.size(), 42u);
}

// ============================================================
// begin / end Tests
// ============================================================

TEST_F(DataBufTest_1123, BeginEnd_IteratorRange_1123) {
    DataBuf buf(4);
    buf.write_uint8(0, 'A');
    buf.write_uint8(1, 'B');
    buf.write_uint8(2, 'C');
    buf.write_uint8(3, 'D');

    std::string result;
    for (auto it = buf.begin(); it != buf.end(); ++it) {
        result += static_cast<char>(*it);
    }
    EXPECT_EQ(result, "ABCD");
}

// ============================================================
// Multiple writes and reads
// ============================================================

TEST_F(DataBufTest_1123, MultipleUint32Writes_1123) {
    DataBuf buf(16);
    buf.write_uint32(0, 0x11111111, bigEndian);
    buf.write_uint32(4, 0x22222222, bigEndian);
    buf.write_uint32(8, 0x33333333, bigEndian);
    buf.write_uint32(12, 0x44444444, bigEndian);

    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x11111111u);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x22222222u);
    EXPECT_EQ(buf.read_uint32(8, bigEndian), 0x33333333u);
    EXPECT_EQ(buf.read_uint32(12, bigEndian), 0x44444444u);
}

TEST_F(DataBufTest_1123, WriteUint32_OverwritesPrevious_1123) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x11111111, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x11111111u);

    buf.write_uint32(0, 0x22222222, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x22222222u);
}

TEST_F(DataBufTest_1123, ResizePreservesExistingData_1123) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xDEADBEEF, bigEndian);
    buf.resize(8);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xDEADBEEFu);
    EXPECT_EQ(buf.size(), 8u);
}

// ============================================================
// Boundary: offset exactly at size - 4 for uint32
// ============================================================

TEST_F(DataBufTest_1123, WriteUint32_ExactBoundary_1123) {
    DataBuf buf(100);
    // Write at offset 96 (last valid position for uint32 in a 100-byte buffer)
    EXPECT_NO_THROW(buf.write_uint32(96, 0xAABBCCDD, bigEndian));
    EXPECT_EQ(buf.read_uint32(96, bigEndian), 0xAABBCCDDu);

    // offset 97 should overflow
    EXPECT_THROW(buf.write_uint32(97, 0x12345678, bigEndian), std::out_of_range);
}

// ============================================================
// Endianness verification through byte-level inspection
// ============================================================

TEST_F(DataBufTest_1123, WriteUint32_BigEndian_ByteOrder_1123) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST_F(DataBufTest_1123, WriteUint32_LittleEndian_ByteOrder_1123) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x04);
    EXPECT_EQ(buf.read_uint8(1), 0x03);
    EXPECT_EQ(buf.read_uint8(2), 0x02);
    EXPECT_EQ(buf.read_uint8(3), 0x01);
}
