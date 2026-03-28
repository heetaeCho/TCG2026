#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <stdexcept>
#include <cstring>

using namespace Exiv2;

class DataBufTest_1121 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(DataBufTest_1121, DefaultConstructor_CreatesEmptyBuffer_1121) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1121, SizeConstructor_CreatesBufferOfGivenSize_1121) {
    DataBuf buf(10);
    EXPECT_EQ(buf.size(), 10u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1121, SizeConstructor_ZeroSize_CreatesEmptyBuffer_1121) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1121, DataConstructor_CopiesData_1121) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.size(), 4u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

// ==================== alloc / resize / reset Tests ====================

TEST_F(DataBufTest_1121, Alloc_SetsBufferSize_1121) {
    DataBuf buf;
    buf.alloc(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1121, Resize_ChangesBufferSize_1121) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1121, Resize_Shrink_1121) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1121, Reset_ClearsBuffer_1121) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ==================== write_uint8 / read_uint8 Tests ====================

TEST_F(DataBufTest_1121, WriteReadUint8_Normal_1121) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAB);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
}

TEST_F(DataBufTest_1121, WriteReadUint8_LastByte_1121) {
    DataBuf buf(4);
    buf.write_uint8(3, 0xFF);
    EXPECT_EQ(buf.read_uint8(3), 0xFF);
}

TEST_F(DataBufTest_1121, WriteReadUint8_Zero_1121) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x00);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
}

// ==================== write_uint16 / read_uint16 Tests ====================

TEST_F(DataBufTest_1121, WriteReadUint16_LittleEndian_1121) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1121, WriteReadUint16_BigEndian_1121) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1121, WriteUint16_AtOffset_1121) {
    DataBuf buf(4);
    buf.write_uint16(2, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 0xABCD);
}

TEST_F(DataBufTest_1121, WriteUint16_OverflowThrows_BufferTooSmall_1121) {
    DataBuf buf(1);
    EXPECT_THROW(buf.write_uint16(0, 0x1234, littleEndian), std::out_of_range);
}

TEST_F(DataBufTest_1121, WriteUint16_OverflowThrows_OffsetTooLarge_1121) {
    DataBuf buf(4);
    EXPECT_THROW(buf.write_uint16(3, 0x1234, littleEndian), std::out_of_range);
}

TEST_F(DataBufTest_1121, WriteUint16_OverflowThrows_EmptyBuffer_1121) {
    DataBuf buf;
    EXPECT_THROW(buf.write_uint16(0, 0x1234, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1121, WriteUint16_ExactFit_NoThrow_1121) {
    DataBuf buf(2);
    EXPECT_NO_THROW(buf.write_uint16(0, 0x5678, bigEndian));
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x5678);
}

TEST_F(DataBufTest_1121, WriteUint16_MaxValue_1121) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0xFFFF);
}

TEST_F(DataBufTest_1121, WriteUint16_ZeroValue_1121) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0000, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x0000);
}

TEST_F(DataBufTest_1121, WriteUint16_ByteOrderMatters_1121) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0102, bigEndian);
    // Reading with different byte order should give different result
    uint16_t lVal = buf.read_uint16(0, littleEndian);
    uint16_t bVal = buf.read_uint16(0, bigEndian);
    EXPECT_EQ(bVal, 0x0102);
    EXPECT_NE(lVal, bVal);  // unless value is palindromic in bytes
}

// ==================== write_uint32 / read_uint32 Tests ====================

TEST_F(DataBufTest_1121, WriteReadUint32_BigEndian_1121) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1121, WriteReadUint32_LittleEndian_1121) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST_F(DataBufTest_1121, WriteReadUint32_AtOffset_1121) {
    DataBuf buf(8);
    buf.write_uint32(4, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xDEADBEEFu);
}

TEST_F(DataBufTest_1121, WriteUint32_OverflowThrows_1121) {
    DataBuf buf(3);
    EXPECT_THROW(buf.write_uint32(0, 0x12345678, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1121, WriteUint32_OffsetOverflow_1121) {
    DataBuf buf(8);
    EXPECT_THROW(buf.write_uint32(5, 0x12345678, bigEndian), std::out_of_range);
}

// ==================== write_uint64 / read_uint64 Tests ====================

TEST_F(DataBufTest_1121, WriteReadUint64_BigEndian_1121) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x123456789ABCDEF0ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x123456789ABCDEF0ULL);
}

TEST_F(DataBufTest_1121, WriteReadUint64_LittleEndian_1121) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x123456789ABCDEF0ULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x123456789ABCDEF0ULL);
}

TEST_F(DataBufTest_1121, WriteReadUint64_AtOffset_1121) {
    DataBuf buf(16);
    buf.write_uint64(8, 0xFEDCBA9876543210ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(8, bigEndian), 0xFEDCBA9876543210ULL);
}

TEST_F(DataBufTest_1121, WriteUint64_OverflowThrows_1121) {
    DataBuf buf(7);
    EXPECT_THROW(buf.write_uint64(0, 0x0ULL, bigEndian), std::out_of_range);
}

// ==================== cmpBytes Tests ====================

TEST_F(DataBufTest_1121, CmpBytes_Equal_1121) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.cmpBytes(0, data, 4), 0);
}

TEST_F(DataBufTest_1121, CmpBytes_NotEqual_1121) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    const byte other[] = {0x01, 0x02, 0x05, 0x04};
    DataBuf buf(data, 4);
    EXPECT_NE(buf.cmpBytes(0, other, 4), 0);
}

TEST_F(DataBufTest_1121, CmpBytes_WithOffset_1121) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03};
    DataBuf buf(data, 4);
    const byte expected[] = {0x01, 0x02, 0x03};
    EXPECT_EQ(buf.cmpBytes(1, expected, 3), 0);
}

// ==================== data / c_data / c_str Tests ====================

TEST_F(DataBufTest_1121, Data_ReturnsNonNull_1121) {
    DataBuf buf(10);
    EXPECT_NE(buf.data(0), nullptr);
}

TEST_F(DataBufTest_1121, CData_ReturnsNonNull_1121) {
    DataBuf buf(10);
    EXPECT_NE(buf.c_data(0), nullptr);
}

TEST_F(DataBufTest_1121, CStr_ReturnsNonNull_1121) {
    DataBuf buf(10);
    EXPECT_NE(buf.c_str(0), nullptr);
}

TEST_F(DataBufTest_1121, Data_WithOffset_1121) {
    DataBuf buf(10);
    buf.write_uint8(5, 0xAA);
    byte* ptr = buf.data(5);
    EXPECT_EQ(*ptr, 0xAA);
}

// ==================== size / empty Tests ====================

TEST_F(DataBufTest_1121, Size_ReturnsCorrectSize_1121) {
    DataBuf buf(42);
    EXPECT_EQ(buf.size(), 42u);
}

TEST_F(DataBufTest_1121, Empty_TrueForDefault_1121) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1121, Empty_FalseForNonEmpty_1121) {
    DataBuf buf(1);
    EXPECT_FALSE(buf.empty());
}

// ==================== begin / end Tests ====================

TEST_F(DataBufTest_1121, BeginEnd_IterableRange_1121) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    size_t count = 0;
    for (auto it = buf.begin(); it != buf.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3u);
}

// ==================== Combined Read/Write with Multiple Types ====================

TEST_F(DataBufTest_1121, MultipleWritesDoNotInterfere_1121) {
    DataBuf buf(16);
    buf.write_uint8(0, 0x11);
    buf.write_uint16(1, 0x2233, bigEndian);
    buf.write_uint32(4, 0x44556677, bigEndian);
    buf.write_uint64(8, 0x8899AABBCCDDEEFFULL, bigEndian);

    EXPECT_EQ(buf.read_uint8(0), 0x11);
    EXPECT_EQ(buf.read_uint16(1, bigEndian), 0x2233);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x44556677u);
    EXPECT_EQ(buf.read_uint64(8, bigEndian), 0x8899AABBCCDDEEFFULL);
}

// ==================== Boundary: write_uint16 at last valid position ====================

TEST_F(DataBufTest_1121, WriteUint16_LastValidOffset_1121) {
    DataBuf buf(10);
    // Last valid offset for uint16 is size - 2 = 8
    EXPECT_NO_THROW(buf.write_uint16(8, 0x1234, bigEndian));
    EXPECT_EQ(buf.read_uint16(8, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1121, WriteUint16_OnePassLastValid_Throws_1121) {
    DataBuf buf(10);
    // Offset 9 means we need bytes [9, 10], but buffer is only 10 bytes [0..9]
    EXPECT_THROW(buf.write_uint16(9, 0x1234, bigEndian), std::out_of_range);
}

// ==================== Overwrite test ====================

TEST_F(DataBufTest_1121, WriteUint16_OverwritePreviousValue_1121) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1111, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1111);
    buf.write_uint16(0, 0x2222, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x2222);
}

// ==================== Endianness consistency ====================

TEST_F(DataBufTest_1121, WriteUint16_BigEndian_ByteLayout_1121) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0102, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
}

TEST_F(DataBufTest_1121, WriteUint16_LittleEndian_ByteLayout_1121) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0102, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x02);
    EXPECT_EQ(buf.read_uint8(1), 0x01);
}

TEST_F(DataBufTest_1121, WriteUint32_BigEndian_ByteLayout_1121) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST_F(DataBufTest_1121, WriteUint32_LittleEndian_ByteLayout_1121) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x04);
    EXPECT_EQ(buf.read_uint8(1), 0x03);
    EXPECT_EQ(buf.read_uint8(2), 0x02);
    EXPECT_EQ(buf.read_uint8(3), 0x01);
}

// ==================== Resize then write ====================

TEST_F(DataBufTest_1121, ResizeThenWrite_1121) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
    buf.resize(4);
    EXPECT_EQ(buf.size(), 4u);
    buf.write_uint16(0, 0xBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xBEEF);
}

// ==================== Alloc then write ====================

TEST_F(DataBufTest_1121, AllocThenWrite_1121) {
    DataBuf buf;
    buf.alloc(8);
    buf.write_uint64(0, 0xDEADC0DE12345678ULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0xDEADC0DE12345678ULL);
}

// ==================== Reset and verify empty ====================

TEST_F(DataBufTest_1121, ResetAfterWrite_1121) {
    DataBuf buf(10);
    buf.write_uint8(0, 0xFF);
    buf.reset();
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
}
