#include <gtest/gtest.h>
#include "exiv2/types.hpp"

using namespace Exiv2;

// Test fixture for DataBuf tests
class DataBufTest_1129 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// === Constructor Tests ===

TEST_F(DataBufTest_1129, DefaultConstructor_CreatesEmptyBuffer_1129) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1129, SizeConstructor_CreatesBufferOfGivenSize_1129) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1129, SizeConstructor_ZeroSize_CreatesEmptyBuffer_1129) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1129, DataConstructor_CopiesData_1129) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
    EXPECT_FALSE(buf.empty());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.read_uint8(i), data[i]);
    }
}

TEST_F(DataBufTest_1129, DataConstructor_ZeroSize_CreatesEmptyBuffer_1129) {
    const byte data[] = {0x01};
    DataBuf buf(data, 0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// === alloc Tests ===

TEST_F(DataBufTest_1129, Alloc_AllocatesNewBuffer_1129) {
    DataBuf buf;
    buf.alloc(50);
    EXPECT_EQ(buf.size(), 50u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1129, Alloc_ZeroSize_1129) {
    DataBuf buf(10);
    buf.alloc(0);
    EXPECT_EQ(buf.size(), 0u);
}

// === resize Tests ===

TEST_F(DataBufTest_1129, Resize_IncreasesSize_1129) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1129, Resize_DecreasesSize_1129) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1129, Resize_ToZero_1129) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1129, Resize_PreservesExistingData_1129) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataBuf buf(data, 3);
    buf.resize(10);
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
    EXPECT_EQ(buf.read_uint8(2), 0xCC);
}

// === reset Tests ===

TEST_F(DataBufTest_1129, Reset_ClearsBuffer_1129) {
    DataBuf buf(100);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1129, Reset_OnEmptyBuffer_1129) {
    DataBuf buf;
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// === read_uint8 / write_uint8 Tests ===

TEST_F(DataBufTest_1129, WriteAndReadUint8_1129) {
    DataBuf buf(10);
    buf.write_uint8(0, 0x42);
    buf.write_uint8(5, 0xFF);
    buf.write_uint8(9, 0x00);
    EXPECT_EQ(buf.read_uint8(0), 0x42);
    EXPECT_EQ(buf.read_uint8(5), 0xFF);
    EXPECT_EQ(buf.read_uint8(9), 0x00);
}

TEST_F(DataBufTest_1129, WriteUint8_BoundaryValues_1129) {
    DataBuf buf(2);
    buf.write_uint8(0, 0x00);
    buf.write_uint8(1, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
    EXPECT_EQ(buf.read_uint8(1), 0xFF);
}

// === read_uint16 / write_uint16 Tests ===

TEST_F(DataBufTest_1129, WriteAndReadUint16_BigEndian_1129) {
    DataBuf buf(10);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1129, WriteAndReadUint16_LittleEndian_1129) {
    DataBuf buf(10);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1129, WriteUint16_BigEndian_ByteOrder_1129) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.read_uint8(1), 0xCD);
}

TEST_F(DataBufTest_1129, WriteUint16_LittleEndian_ByteOrder_1129) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xABCD, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xCD);
    EXPECT_EQ(buf.read_uint8(1), 0xAB);
}

TEST_F(DataBufTest_1129, WriteUint16_MaxValue_1129) {
    DataBuf buf(4);
    buf.write_uint16(0, 0xFFFF, bigEndian);
    buf.write_uint16(2, 0x0000, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xFFFF);
    EXPECT_EQ(buf.read_uint16(2, littleEndian), 0x0000);
}

TEST_F(DataBufTest_1129, WriteAndReadUint16_AtOffset_1129) {
    DataBuf buf(10);
    buf.write_uint16(4, 0x5678, bigEndian);
    EXPECT_EQ(buf.read_uint16(4, bigEndian), 0x5678);
}

// === read_uint32 / write_uint32 Tests ===

TEST_F(DataBufTest_1129, WriteAndReadUint32_BigEndian_1129) {
    DataBuf buf(10);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1129, WriteAndReadUint32_LittleEndian_1129) {
    DataBuf buf(10);
    buf.write_uint32(0, 0x12345678, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST_F(DataBufTest_1129, WriteUint32_BigEndian_ByteOrder_1129) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xDE);
    EXPECT_EQ(buf.read_uint8(1), 0xAD);
    EXPECT_EQ(buf.read_uint8(2), 0xBE);
    EXPECT_EQ(buf.read_uint8(3), 0xEF);
}

TEST_F(DataBufTest_1129, WriteUint32_LittleEndian_ByteOrder_1129) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xEF);
    EXPECT_EQ(buf.read_uint8(1), 0xBE);
    EXPECT_EQ(buf.read_uint8(2), 0xAD);
    EXPECT_EQ(buf.read_uint8(3), 0xDE);
}

TEST_F(DataBufTest_1129, WriteUint32_MaxValue_1129) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

TEST_F(DataBufTest_1129, WriteUint32_ZeroValue_1129) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x00000000, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x00000000u);
}

// === read_uint64 / write_uint64 Tests ===

TEST_F(DataBufTest_1129, WriteAndReadUint64_BigEndian_1129) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1129, WriteAndReadUint64_LittleEndian_1129) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1129, WriteUint64_BigEndian_ByteOrder_1129) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(7), 0x08);
}

TEST_F(DataBufTest_1129, WriteUint64_LittleEndian_ByteOrder_1129) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x08);
    EXPECT_EQ(buf.read_uint8(7), 0x01);
}

TEST_F(DataBufTest_1129, WriteUint64_MaxValue_1129) {
    DataBuf buf(8);
    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFULL);
}

// === cmpBytes Tests ===

TEST_F(DataBufTest_1129, CmpBytes_Equal_1129) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1129, CmpBytes_NotEqual_1129) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0xFF, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1129, CmpBytes_WithOffset_1129) {
    const byte data[] = {0x00, 0x00, 0xAA, 0xBB};
    DataBuf buf(data, 4);
    const byte cmp[] = {0xAA, 0xBB};
    EXPECT_EQ(buf.cmpBytes(2, cmp, 2), 0);
}

TEST_F(DataBufTest_1129, CmpBytes_PartialMatch_1129) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

TEST_F(DataBufTest_1129, CmpBytes_FirstByteDiffers_1129) {
    const byte data[] = {0x10, 0x20};
    DataBuf buf(data, 2);
    const byte cmp[] = {0x20, 0x20};
    EXPECT_NE(buf.cmpBytes(0, cmp, 2), 0);
}

// === data / c_data / c_str Tests ===

TEST_F(DataBufTest_1129, Data_ReturnsNonNullForNonEmptyBuffer_1129) {
    DataBuf buf(10);
    EXPECT_NE(buf.data(0), nullptr);
}

TEST_F(DataBufTest_1129, CData_ReturnsNonNullForNonEmptyBuffer_1129) {
    DataBuf buf(10);
    EXPECT_NE(buf.c_data(0), nullptr);
}

TEST_F(DataBufTest_1129, CStr_ReturnsNonNullForNonEmptyBuffer_1129) {
    DataBuf buf(10);
    EXPECT_NE(buf.c_str(0), nullptr);
}

TEST_F(DataBufTest_1129, CStr_ReturnsCorrectStringRepresentation_1129) {
    const char* str = "Hello";
    DataBuf buf(reinterpret_cast<const byte*>(str), 6); // includes null terminator
    EXPECT_STREQ(buf.c_str(0), "Hello");
}

TEST_F(DataBufTest_1129, CStr_WithOffset_1129) {
    const char* str = "Hello";
    DataBuf buf(reinterpret_cast<const byte*>(str), 6);
    EXPECT_STREQ(buf.c_str(2), "llo");
}

TEST_F(DataBufTest_1129, Data_WriteThroughPointer_1129) {
    DataBuf buf(4);
    byte* ptr = buf.data(0);
    ptr[0] = 0xAA;
    ptr[1] = 0xBB;
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
}

TEST_F(DataBufTest_1129, CData_WithOffset_1129) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    DataBuf buf(data, 4);
    const byte* ptr = buf.c_data(2);
    EXPECT_EQ(*ptr, 0x30);
}

// === size / empty Tests ===

TEST_F(DataBufTest_1129, Size_ReturnsCorrectSize_1129) {
    DataBuf buf(42);
    EXPECT_EQ(buf.size(), 42u);
}

TEST_F(DataBufTest_1129, Empty_ReturnsTrueForDefault_1129) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1129, Empty_ReturnsFalseForAllocated_1129) {
    DataBuf buf(1);
    EXPECT_FALSE(buf.empty());
}

// === begin / end Tests ===

TEST_F(DataBufTest_1129, BeginEnd_IterateOverData_1129) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    size_t count = 0;
    byte expected[] = {0x01, 0x02, 0x03};
    for (auto it = buf.begin(); it != buf.end(); ++it) {
        EXPECT_EQ(*it, expected[count]);
        ++count;
    }
    EXPECT_EQ(count, 3u);
}

TEST_F(DataBufTest_1129, BeginEnd_EmptyBuffer_1129) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}

// === Cross-endian read/write Tests ===

TEST_F(DataBufTest_1129, ReadUint16_CrossEndian_1129) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x1234, bigEndian);
    // Reading in opposite endianness should give swapped result
    uint16_t val = buf.read_uint16(0, littleEndian);
    EXPECT_EQ(val, 0x3412);
}

TEST_F(DataBufTest_1129, ReadUint32_CrossEndian_1129) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x12345678, bigEndian);
    uint32_t val = buf.read_uint32(0, littleEndian);
    EXPECT_EQ(val, 0x78563412u);
}

// === Multiple writes at different offsets ===

TEST_F(DataBufTest_1129, MultipleUint16Writes_1129) {
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

// === Alloc after data already exists ===

TEST_F(DataBufTest_1129, Alloc_ReplacesExistingData_1129) {
    const byte data[] = {0xAA, 0xBB};
    DataBuf buf(data, 2);
    EXPECT_EQ(buf.size(), 2u);
    buf.alloc(100);
    EXPECT_EQ(buf.size(), 100u);
}

// === Resize preserves data test ===

TEST_F(DataBufTest_1129, Resize_ShrinkPreservesPartialData_1129) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    buf.resize(3);
    EXPECT_EQ(buf.size(), 3u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
}

// === c_str consistency with c_data ===

TEST_F(DataBufTest_1129, CStr_ConsistentWithCData_1129) {
    const byte data[] = {0x41, 0x42, 0x43, 0x00}; // "ABC\0"
    DataBuf buf(data, 4);
    const char* str = buf.c_str(0);
    const byte* bdata = buf.c_data(0);
    EXPECT_EQ(reinterpret_cast<const byte*>(str), bdata);
}

TEST_F(DataBufTest_1129, CStr_WithOffsetConsistentWithCData_1129) {
    const byte data[] = {0x41, 0x42, 0x43, 0x00};
    DataBuf buf(data, 4);
    const char* str = buf.c_str(1);
    const byte* bdata = buf.c_data(1);
    EXPECT_EQ(reinterpret_cast<const byte*>(str), bdata);
}

// === Single byte buffer ===

TEST_F(DataBufTest_1129, SingleByteBuffer_1129) {
    DataBuf buf(1);
    buf.write_uint8(0, 0x99);
    EXPECT_EQ(buf.read_uint8(0), 0x99);
    EXPECT_EQ(buf.size(), 1u);
    EXPECT_FALSE(buf.empty());
}

// === Large buffer test ===

TEST_F(DataBufTest_1129, LargeBuffer_1129) {
    const size_t largeSize = 1000000;
    DataBuf buf(largeSize);
    EXPECT_EQ(buf.size(), largeSize);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(largeSize - 1, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(largeSize - 1), 0xFF);
}

// === cmpBytes with zero length ===

TEST_F(DataBufTest_1129, CmpBytes_ZeroLength_1129) {
    const byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    const byte cmp[] = {0xFF};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}
