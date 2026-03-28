#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <stdexcept>
#include <cstring>

using namespace Exiv2;

class DataBufTest_1118 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(DataBufTest_1118, DefaultConstructor_CreatesEmptyBuffer_1118) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1118, SizeConstructor_CreatesBufferOfGivenSize_1118) {
    DataBuf buf(10);
    EXPECT_EQ(buf.size(), 10u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1118, SizeConstructor_ZeroSize_CreatesEmptyBuffer_1118) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1118, DataConstructor_CopiesData_1118) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
    EXPECT_FALSE(buf.empty());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.read_uint8(i), data[i]);
    }
}

TEST_F(DataBufTest_1118, DataConstructor_ZeroSize_CreatesEmptyBuffer_1118) {
    const byte data[] = {0x01};
    DataBuf buf(data, 0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ==================== alloc / resize / reset Tests ====================

TEST_F(DataBufTest_1118, Alloc_SetsSize_1118) {
    DataBuf buf;
    buf.alloc(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1118, Resize_ChangesSize_1118) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1118, Resize_ShrinkBuffer_1118) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1118, Resize_ToZero_1118) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1118, Reset_ClearsBuffer_1118) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1118, Reset_OnEmptyBuffer_1118) {
    DataBuf buf;
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ==================== read_uint8 / write_uint8 Tests ====================

TEST_F(DataBufTest_1118, ReadUint8_ReturnsCorrectValue_1118) {
    const byte data[] = {0xAB, 0xCD, 0xEF};
    DataBuf buf(data, 3);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.read_uint8(1), 0xCD);
    EXPECT_EQ(buf.read_uint8(2), 0xEF);
}

TEST_F(DataBufTest_1118, ReadUint8_OverflowThrows_1118) {
    DataBuf buf(3);
    EXPECT_THROW(buf.read_uint8(3), std::out_of_range);
    EXPECT_THROW(buf.read_uint8(100), std::out_of_range);
}

TEST_F(DataBufTest_1118, ReadUint8_EmptyBufferThrows_1118) {
    DataBuf buf;
    EXPECT_THROW(buf.read_uint8(0), std::out_of_range);
}

TEST_F(DataBufTest_1118, WriteUint8_WritesCorrectly_1118) {
    DataBuf buf(3);
    buf.write_uint8(0, 0x11);
    buf.write_uint8(1, 0x22);
    buf.write_uint8(2, 0x33);
    EXPECT_EQ(buf.read_uint8(0), 0x11);
    EXPECT_EQ(buf.read_uint8(1), 0x22);
    EXPECT_EQ(buf.read_uint8(2), 0x33);
}

TEST_F(DataBufTest_1118, WriteUint8_BoundaryValues_1118) {
    DataBuf buf(2);
    buf.write_uint8(0, 0x00);
    buf.write_uint8(1, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
    EXPECT_EQ(buf.read_uint8(1), 0xFF);
}

// ==================== read_uint16 / write_uint16 Tests ====================

TEST_F(DataBufTest_1118, WriteReadUint16_LittleEndian_1118) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1118, WriteReadUint16_BigEndian_1118) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1118, WriteReadUint16_DifferentOffsets_1118) {
    DataBuf buf(10);
    buf.write_uint16(0, 0xAABB, bigEndian);
    buf.write_uint16(2, 0xCCDD, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xAABB);
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 0xCCDD);
}

TEST_F(DataBufTest_1118, WriteReadUint16_ByteOrderMatters_1118) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x0102, bigEndian);
    // Reading with different byte order should give different result
    uint16_t le_val = buf.read_uint16(0, littleEndian);
    uint16_t be_val = buf.read_uint16(0, bigEndian);
    EXPECT_EQ(be_val, 0x0102);
    EXPECT_NE(le_val, be_val);
}

TEST_F(DataBufTest_1118, ReadUint16_OverflowThrows_1118) {
    DataBuf buf(1);
    EXPECT_THROW(buf.read_uint16(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1118, WriteReadUint16_BoundaryValues_1118) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x0000, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x0000);
    buf.write_uint16(0, 0xFFFF, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xFFFF);
}

// ==================== read_uint32 / write_uint32 Tests ====================

TEST_F(DataBufTest_1118, WriteReadUint32_BigEndian_1118) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1118, WriteReadUint32_LittleEndian_1118) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST_F(DataBufTest_1118, WriteReadUint32_AtOffset_1118) {
    DataBuf buf(12);
    buf.write_uint32(4, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xDEADBEEFu);
}

TEST_F(DataBufTest_1118, ReadUint32_OverflowThrows_1118) {
    DataBuf buf(3);
    EXPECT_THROW(buf.read_uint32(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1118, WriteReadUint32_BoundaryValues_1118) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x00000000, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x00000000u);
    buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

// ==================== read_uint64 / write_uint64 Tests ====================

TEST_F(DataBufTest_1118, WriteReadUint64_BigEndian_1118) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0123456789ABCDEFull, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0123456789ABCDEFull);
}

TEST_F(DataBufTest_1118, WriteReadUint64_LittleEndian_1118) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0123456789ABCDEFull, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0123456789ABCDEFull);
}

TEST_F(DataBufTest_1118, ReadUint64_OverflowThrows_1118) {
    DataBuf buf(7);
    EXPECT_THROW(buf.read_uint64(0, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1118, WriteReadUint64_BoundaryValues_1118) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0000000000000000ull, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0000000000000000ull);
    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFull, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFull);
}

// ==================== cmpBytes Tests ====================

TEST_F(DataBufTest_1118, CmpBytes_EqualData_ReturnsZero_1118) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1118, CmpBytes_DifferentData_ReturnsNonZero_1118) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x04, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1118, CmpBytes_WithOffset_1118) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03};
    EXPECT_EQ(buf.cmpBytes(1, cmp, 3), 0);
}

TEST_F(DataBufTest_1118, CmpBytes_PartialMatch_1118) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

// ==================== data / c_data / c_str Tests ====================

TEST_F(DataBufTest_1118, Data_ReturnsNonNull_1118) {
    DataBuf buf(10);
    EXPECT_NE(buf.data(0), nullptr);
}

TEST_F(DataBufTest_1118, Data_OffsetReturnsCorrectPointer_1118) {
    DataBuf buf(10);
    buf.write_uint8(5, 0xAA);
    byte* ptr = buf.data(5);
    EXPECT_EQ(*ptr, 0xAA);
}

TEST_F(DataBufTest_1118, CData_ReturnsConstPointer_1118) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data(0);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0x10);
    EXPECT_EQ(ptr[1], 0x20);
}

TEST_F(DataBufTest_1118, CStr_ReturnsCharPointer_1118) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(0);
    EXPECT_STREQ(str, "Hello");
}

TEST_F(DataBufTest_1118, CStr_WithOffset_1118) {
    const byte data[] = {'X', 'H', 'i', '\0'};
    DataBuf buf(data, 4);
    const char* str = buf.c_str(1);
    EXPECT_STREQ(str, "Hi");
}

// ==================== size / empty Tests ====================

TEST_F(DataBufTest_1118, Size_ReturnsCorrectSize_1118) {
    DataBuf buf(42);
    EXPECT_EQ(buf.size(), 42u);
}

TEST_F(DataBufTest_1118, Empty_ReturnsTrueForDefaultConstructed_1118) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1118, Empty_ReturnsFalseForNonEmptyBuffer_1118) {
    DataBuf buf(1);
    EXPECT_FALSE(buf.empty());
}

// ==================== begin / end Tests ====================

TEST_F(DataBufTest_1118, BeginEnd_IterableRange_1118) {
    const byte data[] = {1, 2, 3, 4, 5};
    DataBuf buf(data, 5);
    size_t count = 0;
    byte sum = 0;
    for (auto it = buf.begin(); it != buf.end(); ++it) {
        sum += *it;
        ++count;
    }
    EXPECT_EQ(count, 5u);
    EXPECT_EQ(sum, 15);
}

TEST_F(DataBufTest_1118, BeginEnd_EmptyBuffer_1118) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}

// ==================== Mixed Read/Write Tests ====================

TEST_F(DataBufTest_1118, MixedReadWrite_Uint8Uint16Uint32_1118) {
    DataBuf buf(16);
    buf.write_uint8(0, 0xFF);
    buf.write_uint16(1, 0x1234, bigEndian);
    buf.write_uint32(3, 0xDEADBEEF, bigEndian);

    EXPECT_EQ(buf.read_uint8(0), 0xFF);
    EXPECT_EQ(buf.read_uint16(1, bigEndian), 0x1234);
    EXPECT_EQ(buf.read_uint32(3, bigEndian), 0xDEADBEEFu);
}

TEST_F(DataBufTest_1118, AllocThenWrite_1118) {
    DataBuf buf;
    buf.alloc(8);
    buf.write_uint32(0, 0x12345678, littleEndian);
    buf.write_uint32(4, 0x9ABCDEF0, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
    EXPECT_EQ(buf.read_uint32(4, littleEndian), 0x9ABCDEF0u);
}

TEST_F(DataBufTest_1118, ResizePreservesExistingData_1118) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAA);
    buf.write_uint8(1, 0xBB);
    buf.resize(8);
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
    EXPECT_EQ(buf.size(), 8u);
}

TEST_F(DataBufTest_1118, WriteUint8_OverwritesPreviousValue_1118) {
    DataBuf buf(1);
    buf.write_uint8(0, 0x11);
    EXPECT_EQ(buf.read_uint8(0), 0x11);
    buf.write_uint8(0, 0x22);
    EXPECT_EQ(buf.read_uint8(0), 0x22);
}

// ==================== Boundary offset tests for multi-byte reads ====================

TEST_F(DataBufTest_1118, ReadUint16_AtLastValidOffset_1118) {
    DataBuf buf(4);
    buf.write_uint16(2, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 0xABCD);
}

TEST_F(DataBufTest_1118, ReadUint16_OverflowAtBoundary_1118) {
    DataBuf buf(3);
    // offset 2 + 2 bytes = 4, but size is 3 -> overflow
    EXPECT_THROW(buf.read_uint16(2, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1118, ReadUint32_AtLastValidOffset_1118) {
    DataBuf buf(8);
    buf.write_uint32(4, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1118, ReadUint32_OverflowAtBoundary_1118) {
    DataBuf buf(6);
    // offset 3 + 4 bytes = 7, but size is 6 -> overflow
    EXPECT_THROW(buf.read_uint32(3, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1118, ReadUint64_AtLastValidOffset_1118) {
    DataBuf buf(16);
    buf.write_uint64(8, 0xFEDCBA9876543210ull, bigEndian);
    EXPECT_EQ(buf.read_uint64(8, bigEndian), 0xFEDCBA9876543210ull);
}

TEST_F(DataBufTest_1118, ReadUint64_OverflowAtBoundary_1118) {
    DataBuf buf(10);
    // offset 3 + 8 bytes = 11, but size is 10 -> overflow
    EXPECT_THROW(buf.read_uint64(3, bigEndian), std::out_of_range);
}

// ==================== Large buffer test ====================

TEST_F(DataBufTest_1118, LargeBuffer_WriteAndReadBack_1118) {
    const size_t size = 10000;
    DataBuf buf(size);
    for (size_t i = 0; i < size; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i % 256));
    }
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(buf.read_uint8(i), static_cast<uint8_t>(i % 256));
    }
}

TEST_F(DataBufTest_1118, SingleByteBuffer_ReadUint8_1118) {
    DataBuf buf(1);
    buf.write_uint8(0, 42);
    EXPECT_EQ(buf.read_uint8(0), 42);
    EXPECT_THROW(buf.read_uint8(1), std::out_of_range);
}
