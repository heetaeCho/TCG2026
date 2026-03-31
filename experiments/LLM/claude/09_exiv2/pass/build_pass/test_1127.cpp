#include <gtest/gtest.h>
#include "exiv2/types.hpp"

using namespace Exiv2;

// Test fixture for DataBuf tests
class DataBufTest_1127 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(DataBufTest_1127, DefaultConstructor_CreatesEmptyBuffer_1127) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1127, SizeConstructor_CreatesBufferOfGivenSize_1127) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1127, SizeConstructor_ZeroSize_CreatesEmptyBuffer_1127) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1127, DataConstructor_CopiesData_1127) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
    EXPECT_FALSE(buf.empty());
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(4), 0x05);
}

TEST_F(DataBufTest_1127, DataConstructor_ZeroSize_CreatesEmptyBuffer_1127) {
    const byte data[] = {0x01};
    DataBuf buf(data, 0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ==================== alloc / resize / reset Tests ====================

TEST_F(DataBufTest_1127, Alloc_SetsBufferSize_1127) {
    DataBuf buf;
    buf.alloc(50);
    EXPECT_EQ(buf.size(), 50u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1127, Alloc_ZeroSize_MakesEmpty_1127) {
    DataBuf buf(10);
    buf.alloc(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1127, Resize_IncreasesSize_1127) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1127, Resize_DecreasesSize_1127) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1127, Resize_PreservesExistingData_1127) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataBuf buf(data, 3);
    buf.resize(10);
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
    EXPECT_EQ(buf.read_uint8(2), 0xCC);
}

TEST_F(DataBufTest_1127, Reset_MakesBufferEmpty_1127) {
    DataBuf buf(100);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ==================== read_uint8 / write_uint8 Tests ====================

TEST_F(DataBufTest_1127, WriteAndReadUint8_1127) {
    DataBuf buf(10);
    buf.write_uint8(0, 0x42);
    buf.write_uint8(9, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x42);
    EXPECT_EQ(buf.read_uint8(9), 0xFF);
}

TEST_F(DataBufTest_1127, WriteUint8_ZeroValue_1127) {
    DataBuf buf(1);
    buf.write_uint8(0, 0x00);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
}

TEST_F(DataBufTest_1127, WriteUint8_MaxValue_1127) {
    DataBuf buf(1);
    buf.write_uint8(0, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

// ==================== read_uint16 / write_uint16 Tests ====================

TEST_F(DataBufTest_1127, WriteAndReadUint16_BigEndian_1127) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1127, WriteAndReadUint16_LittleEndian_1127) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1127, WriteUint16_BigEndian_ByteOrder_1127) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.read_uint8(1), 0xCD);
}

TEST_F(DataBufTest_1127, WriteUint16_LittleEndian_ByteOrder_1127) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xABCD, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xCD);
    EXPECT_EQ(buf.read_uint8(1), 0xAB);
}

TEST_F(DataBufTest_1127, WriteUint16_AtOffset_1127) {
    DataBuf buf(10);
    buf.write_uint16(4, 0xBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint16(4, bigEndian), 0xBEEF);
}

TEST_F(DataBufTest_1127, WriteAndReadUint16_ZeroValue_1127) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0000, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x0000);
}

TEST_F(DataBufTest_1127, WriteAndReadUint16_MaxValue_1127) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0xFFFF);
}

// ==================== read_uint32 / write_uint32 Tests ====================

TEST_F(DataBufTest_1127, WriteAndReadUint32_BigEndian_1127) {
    DataBuf buf(8);
    buf.write_uint32(0, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xDEADBEEF);
}

TEST_F(DataBufTest_1127, WriteAndReadUint32_LittleEndian_1127) {
    DataBuf buf(8);
    buf.write_uint32(0, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0xDEADBEEF);
}

TEST_F(DataBufTest_1127, WriteUint32_BigEndian_ByteOrder_1127) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST_F(DataBufTest_1127, WriteUint32_LittleEndian_ByteOrder_1127) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x04);
    EXPECT_EQ(buf.read_uint8(1), 0x03);
    EXPECT_EQ(buf.read_uint8(2), 0x02);
    EXPECT_EQ(buf.read_uint8(3), 0x01);
}

TEST_F(DataBufTest_1127, WriteAndReadUint32_AtOffset_1127) {
    DataBuf buf(20);
    buf.write_uint32(8, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(8, bigEndian), 0x12345678);
}

TEST_F(DataBufTest_1127, WriteAndReadUint32_ZeroValue_1127) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x00000000, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x00000000u);
}

TEST_F(DataBufTest_1127, WriteAndReadUint32_MaxValue_1127) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xFFFFFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0xFFFFFFFF);
}

// ==================== read_uint64 / write_uint64 Tests ====================

TEST_F(DataBufTest_1127, WriteAndReadUint64_BigEndian_1127) {
    DataBuf buf(16);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), val);
}

TEST_F(DataBufTest_1127, WriteAndReadUint64_LittleEndian_1127) {
    DataBuf buf(16);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), val);
}

TEST_F(DataBufTest_1127, WriteUint64_BigEndian_ByteOrder_1127) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(7), 0x08);
}

TEST_F(DataBufTest_1127, WriteUint64_LittleEndian_ByteOrder_1127) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x08);
    EXPECT_EQ(buf.read_uint8(7), 0x01);
}

TEST_F(DataBufTest_1127, WriteAndReadUint64_AtOffset_1127) {
    DataBuf buf(20);
    uint64_t val = 0xAABBCCDDEEFF0011ULL;
    buf.write_uint64(4, val, bigEndian);
    EXPECT_EQ(buf.read_uint64(4, bigEndian), val);
}

TEST_F(DataBufTest_1127, WriteAndReadUint64_ZeroValue_1127) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0ULL);
}

TEST_F(DataBufTest_1127, WriteAndReadUint64_MaxValue_1127) {
    DataBuf buf(8);
    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0xFFFFFFFFFFFFFFFFULL);
}

// ==================== data / c_data / c_str Tests ====================

TEST_F(DataBufTest_1127, Data_ReturnsNonNullForNonEmpty_1127) {
    DataBuf buf(10);
    EXPECT_NE(buf.data(0), nullptr);
}

TEST_F(DataBufTest_1127, Data_WithOffset_1127) {
    DataBuf buf(10);
    buf.write_uint8(5, 0x42);
    byte* ptr = buf.data(5);
    EXPECT_EQ(*ptr, 0x42);
}

TEST_F(DataBufTest_1127, Data_ModificationAffectsBuffer_1127) {
    DataBuf buf(10);
    byte* ptr = buf.data(3);
    *ptr = 0x99;
    EXPECT_EQ(buf.read_uint8(3), 0x99);
}

TEST_F(DataBufTest_1127, CData_ReturnsConstPointer_1127) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data(0);
    EXPECT_EQ(ptr[0], 0x10);
    EXPECT_EQ(ptr[1], 0x20);
    EXPECT_EQ(ptr[2], 0x30);
}

TEST_F(DataBufTest_1127, CData_WithOffset_1127) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data(1);
    EXPECT_EQ(*ptr, 0x20);
}

TEST_F(DataBufTest_1127, CStr_ReturnsCharPointer_1127) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(0);
    EXPECT_STREQ(str, "Hello");
}

TEST_F(DataBufTest_1127, CStr_WithOffset_1127) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(2);
    EXPECT_STREQ(str, "llo");
}

// ==================== cmpBytes Tests ====================

TEST_F(DataBufTest_1127, CmpBytes_EqualData_ReturnsZero_1127) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1127, CmpBytes_DifferentData_ReturnsNonZero_1127) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0xFF, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1127, CmpBytes_WithOffset_1127) {
    const byte data[] = {0xAA, 0xBB, 0x01, 0x02, 0x03};
    DataBuf buf(data, 5);
    const byte cmp[] = {0x01, 0x02, 0x03};
    EXPECT_EQ(buf.cmpBytes(2, cmp, 3), 0);
}

TEST_F(DataBufTest_1127, CmpBytes_PartialMatch_1127) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

TEST_F(DataBufTest_1127, CmpBytes_ZeroSize_1127) {
    const byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    const byte cmp[] = {0xFF};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}

TEST_F(DataBufTest_1127, CmpBytes_LessThan_1127) {
    const byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    const byte cmp[] = {0x01, 0x03};
    EXPECT_LT(buf.cmpBytes(0, cmp, 2), 0);
}

TEST_F(DataBufTest_1127, CmpBytes_GreaterThan_1127) {
    const byte data[] = {0x01, 0x03};
    DataBuf buf(data, 2);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_GT(buf.cmpBytes(0, cmp, 2), 0);
}

// ==================== size / empty Tests ====================

TEST_F(DataBufTest_1127, Size_AfterConstruction_1127) {
    DataBuf buf(42);
    EXPECT_EQ(buf.size(), 42u);
}

TEST_F(DataBufTest_1127, Empty_ForDefaultConstructed_1127) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1127, Empty_ForNonEmptyBuffer_1127) {
    DataBuf buf(1);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1127, Size_AfterReset_1127) {
    DataBuf buf(50);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1127, Size_AfterResize_1127) {
    DataBuf buf(10);
    buf.resize(25);
    EXPECT_EQ(buf.size(), 25u);
}

// ==================== begin / end Tests ====================

TEST_F(DataBufTest_1127, BeginEnd_NonEmptyBuffer_1127) {
    DataBuf buf(10);
    auto b = buf.begin();
    auto e = buf.end();
    EXPECT_EQ(static_cast<size_t>(e - b), 10u);
}

TEST_F(DataBufTest_1127, BeginEnd_EmptyBuffer_1127) {
    DataBuf buf;
    auto b = buf.begin();
    auto e = buf.end();
    EXPECT_EQ(b, e);
}

TEST_F(DataBufTest_1127, BeginEnd_IterateAndModify_1127) {
    DataBuf buf(5);
    byte val = 0;
    for (auto it = buf.begin(); it != buf.end(); ++it) {
        *it = val++;
    }
    EXPECT_EQ(buf.read_uint8(0), 0);
    EXPECT_EQ(buf.read_uint8(1), 1);
    EXPECT_EQ(buf.read_uint8(4), 4);
}

// ==================== Cross-endianness consistency Tests ====================

TEST_F(DataBufTest_1127, ReadUint16_CrossEndian_1127) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x1234, bigEndian);
    // Read with different endianness should give byte-swapped result
    uint16_t le_val = buf.read_uint16(0, littleEndian);
    EXPECT_EQ(le_val, 0x3412);
}

TEST_F(DataBufTest_1127, ReadUint32_CrossEndian_1127) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    uint32_t le_val = buf.read_uint32(0, littleEndian);
    EXPECT_EQ(le_val, 0x04030201u);
}

// ==================== Multiple writes at different offsets ====================

TEST_F(DataBufTest_1127, MultipleWritesAtDifferentOffsets_1127) {
    DataBuf buf(16);
    buf.write_uint32(0, 0x11223344, bigEndian);
    buf.write_uint32(4, 0x55667788, bigEndian);
    buf.write_uint32(8, 0x99AABBCC, bigEndian);
    buf.write_uint32(12, 0xDDEEFF00, bigEndian);

    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x11223344u);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x55667788u);
    EXPECT_EQ(buf.read_uint32(8, bigEndian), 0x99AABBCCu);
    EXPECT_EQ(buf.read_uint32(12, bigEndian), 0xDDEEFF00u);
}

// ==================== Alloc after data existing ====================

TEST_F(DataBufTest_1127, Alloc_AfterExistingData_1127) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    EXPECT_EQ(buf.size(), 3u);
    buf.alloc(10);
    EXPECT_EQ(buf.size(), 10u);
}

// ==================== Copy semantics ====================

TEST_F(DataBufTest_1127, CopyConstruction_1127) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataBuf buf1(data, 3);
    DataBuf buf2(buf1);
    EXPECT_EQ(buf2.size(), 3u);
    EXPECT_EQ(buf2.read_uint8(0), 0xAA);
    EXPECT_EQ(buf2.read_uint8(1), 0xBB);
    EXPECT_EQ(buf2.read_uint8(2), 0xCC);
    // Modify buf2 should not affect buf1
    buf2.write_uint8(0, 0xFF);
    EXPECT_EQ(buf1.read_uint8(0), 0xAA);
    EXPECT_EQ(buf2.read_uint8(0), 0xFF);
}

TEST_F(DataBufTest_1127, MoveConstruction_1127) {
    const byte data[] = {0x11, 0x22, 0x33};
    DataBuf buf1(data, 3);
    DataBuf buf2(std::move(buf1));
    EXPECT_EQ(buf2.size(), 3u);
    EXPECT_EQ(buf2.read_uint8(0), 0x11);
    EXPECT_EQ(buf2.read_uint8(1), 0x22);
    EXPECT_EQ(buf2.read_uint8(2), 0x33);
}

// ==================== Resize preserves, then new data can be written ====================

TEST_F(DataBufTest_1127, ResizeAndWriteNewRegion_1127) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xDEADBEEF, bigEndian);
    buf.resize(8);
    buf.write_uint32(4, 0xCAFEBABE, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xDEADBEEFu);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xCAFEBABEu);
}

// ==================== data() returns pointer consistent with c_data() ====================

TEST_F(DataBufTest_1127, DataAndCDataConsistency_1127) {
    DataBuf buf(10);
    buf.write_uint8(5, 0x42);
    const byte* cptr = buf.c_data(5);
    byte* ptr = buf.data(5);
    EXPECT_EQ(*cptr, *ptr);
    EXPECT_EQ(static_cast<const byte*>(ptr), cptr);
}

// ==================== Large buffer test ====================

TEST_F(DataBufTest_1127, LargeBuffer_1127) {
    size_t largeSize = 1024 * 1024; // 1MB
    DataBuf buf(largeSize);
    EXPECT_EQ(buf.size(), largeSize);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(largeSize - 1, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(largeSize - 1), 0xFF);
}

// ==================== Single byte buffer ====================

TEST_F(DataBufTest_1127, SingleByteBoundary_1127) {
    DataBuf buf(1);
    buf.write_uint8(0, 0xAB);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.size(), 1u);
    EXPECT_FALSE(buf.empty());
}

// ==================== Resize to zero ====================

TEST_F(DataBufTest_1127, ResizeToZero_1127) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}
