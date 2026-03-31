#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// Test fixture for DataBuf tests
class DataBufTest_1117 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Construction ====================

TEST_F(DataBufTest_1117, DefaultConstructor_CreatesEmptyBuffer_1117) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ==================== Size Constructor ====================

TEST_F(DataBufTest_1117, SizeConstructor_CreatesBufferOfGivenSize_1117) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1117, SizeConstructor_ZeroSize_CreatesEmptyBuffer_1117) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ==================== Data Constructor ====================

TEST_F(DataBufTest_1117, DataConstructor_CopiesDataCorrectly_1117) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
    EXPECT_FALSE(buf.empty());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.read_uint8(i), data[i]);
    }
}

TEST_F(DataBufTest_1117, DataConstructor_ZeroSize_CreatesEmptyBuffer_1117) {
    const byte data[] = {0x01};
    DataBuf buf(data, 0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ==================== reset() ====================

TEST_F(DataBufTest_1117, Reset_ClearsBuffer_1117) {
    DataBuf buf(50);
    EXPECT_EQ(buf.size(), 50u);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1117, Reset_OnEmptyBuffer_RemainsEmpty_1117) {
    DataBuf buf;
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ==================== alloc() ====================

TEST_F(DataBufTest_1117, Alloc_AllocatesGivenSize_1117) {
    DataBuf buf;
    buf.alloc(64);
    EXPECT_EQ(buf.size(), 64u);
}

TEST_F(DataBufTest_1117, Alloc_ZeroSize_1117) {
    DataBuf buf(10);
    buf.alloc(0);
    EXPECT_EQ(buf.size(), 0u);
}

// ==================== resize() ====================

TEST_F(DataBufTest_1117, Resize_IncreasesSize_1117) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1117, Resize_DecreasesSize_1117) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1117, Resize_ToZero_1117) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1117, Resize_PreservesExistingData_1117) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataBuf buf(data, 3);
    buf.resize(10);
    EXPECT_EQ(buf.size(), 10u);
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
    EXPECT_EQ(buf.read_uint8(2), 0xCC);
}

// ==================== read_uint8 / write_uint8 ====================

TEST_F(DataBufTest_1117, ReadWriteUint8_BasicOperation_1117) {
    DataBuf buf(10);
    buf.write_uint8(0, 0x42);
    EXPECT_EQ(buf.read_uint8(0), 0x42);
}

TEST_F(DataBufTest_1117, ReadWriteUint8_AllPositions_1117) {
    DataBuf buf(5);
    for (size_t i = 0; i < 5; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i + 10));
    }
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.read_uint8(i), static_cast<uint8_t>(i + 10));
    }
}

TEST_F(DataBufTest_1117, ReadWriteUint8_BoundaryValues_1117) {
    DataBuf buf(2);
    buf.write_uint8(0, 0x00);
    buf.write_uint8(1, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
    EXPECT_EQ(buf.read_uint8(1), 0xFF);
}

// ==================== read_uint16 / write_uint16 ====================

TEST_F(DataBufTest_1117, ReadWriteUint16_LittleEndian_1117) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1117, ReadWriteUint16_BigEndian_1117) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1117, ReadWriteUint16_ByteOrderMatters_1117) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x0102, bigEndian);
    // Reading with wrong byte order should give different result
    uint16_t bigVal = buf.read_uint16(0, bigEndian);
    uint16_t littleVal = buf.read_uint16(0, littleEndian);
    EXPECT_EQ(bigVal, 0x0102);
    EXPECT_EQ(littleVal, 0x0201);
}

TEST_F(DataBufTest_1117, ReadWriteUint16_AtOffset_1117) {
    DataBuf buf(10);
    buf.write_uint16(4, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint16(4, bigEndian), 0xABCD);
}

TEST_F(DataBufTest_1117, ReadWriteUint16_BoundaryValues_1117) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x0000, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x0000);
    buf.write_uint16(0, 0xFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0xFFFF);
}

// ==================== read_uint32 / write_uint32 ====================

TEST_F(DataBufTest_1117, ReadWriteUint32_LittleEndian_1117) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST_F(DataBufTest_1117, ReadWriteUint32_BigEndian_1117) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1117, ReadWriteUint32_AtOffset_1117) {
    DataBuf buf(16);
    buf.write_uint32(8, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint32(8, bigEndian), 0xDEADBEEFu);
}

TEST_F(DataBufTest_1117, ReadWriteUint32_BoundaryValues_1117) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x00000000, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x00000000u);
    buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

// ==================== read_uint64 / write_uint64 ====================

TEST_F(DataBufTest_1117, ReadWriteUint64_LittleEndian_1117) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1117, ReadWriteUint64_BigEndian_1117) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1117, ReadWriteUint64_AtOffset_1117) {
    DataBuf buf(24);
    buf.write_uint64(8, 0xFEDCBA9876543210ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(8, bigEndian), 0xFEDCBA9876543210ULL);
}

TEST_F(DataBufTest_1117, ReadWriteUint64_BoundaryValues_1117) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0000000000000000ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0000000000000000ULL);
    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFULL);
}

// ==================== cmpBytes() ====================

TEST_F(DataBufTest_1117, CmpBytes_EqualData_ReturnsZero_1117) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1117, CmpBytes_DifferentData_ReturnsNonZero_1117) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x04, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1117, CmpBytes_AtOffset_1117) {
    const byte data[] = {0x00, 0x00, 0x01, 0x02, 0x03};
    DataBuf buf(data, 5);
    const byte cmp[] = {0x01, 0x02, 0x03};
    EXPECT_EQ(buf.cmpBytes(2, cmp, 3), 0);
}

TEST_F(DataBufTest_1117, CmpBytes_ZeroSize_1117) {
    const byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    const byte cmp[] = {0xFF};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}

TEST_F(DataBufTest_1117, CmpBytes_LessThan_ReturnsNegative_1117) {
    const byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    const byte cmp[] = {0x01, 0x03};
    EXPECT_LT(buf.cmpBytes(0, cmp, 2), 0);
}

TEST_F(DataBufTest_1117, CmpBytes_GreaterThan_ReturnsPositive_1117) {
    const byte data[] = {0x01, 0x04};
    DataBuf buf(data, 2);
    const byte cmp[] = {0x01, 0x03};
    EXPECT_GT(buf.cmpBytes(0, cmp, 2), 0);
}

// ==================== data() ====================

TEST_F(DataBufTest_1117, Data_ReturnsWritablePointer_1117) {
    DataBuf buf(10);
    byte* ptr = buf.data(0);
    EXPECT_NE(ptr, nullptr);
    ptr[0] = 0xAA;
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
}

TEST_F(DataBufTest_1117, Data_AtOffset_1117) {
    DataBuf buf(10);
    buf.write_uint8(5, 0xBB);
    byte* ptr = buf.data(5);
    EXPECT_EQ(*ptr, 0xBB);
}

// ==================== c_data() ====================

TEST_F(DataBufTest_1117, CData_ReturnsConstPointer_1117) {
    const byte data[] = {0xDE, 0xAD};
    DataBuf buf(data, 2);
    const byte* ptr = buf.c_data(0);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0xDE);
    EXPECT_EQ(ptr[1], 0xAD);
}

TEST_F(DataBufTest_1117, CData_AtOffset_1117) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03};
    DataBuf buf(data, 4);
    const byte* ptr = buf.c_data(2);
    EXPECT_EQ(*ptr, 0x02);
}

// ==================== c_str() ====================

TEST_F(DataBufTest_1117, CStr_ReturnsCharPointer_1117) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(0);
    EXPECT_STREQ(str, "Hello");
}

TEST_F(DataBufTest_1117, CStr_AtOffset_1117) {
    const byte data[] = {'X', 'Y', 'H', 'i', '\0'};
    DataBuf buf(data, 5);
    const char* str = buf.c_str(2);
    EXPECT_STREQ(str, "Hi");
}

// ==================== size() and empty() ====================

TEST_F(DataBufTest_1117, Size_ReturnsCorrectSize_1117) {
    DataBuf buf(42);
    EXPECT_EQ(buf.size(), 42u);
}

TEST_F(DataBufTest_1117, Empty_TrueForDefault_1117) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1117, Empty_FalseForNonEmpty_1117) {
    DataBuf buf(1);
    EXPECT_FALSE(buf.empty());
}

// ==================== begin() / end() ====================

TEST_F(DataBufTest_1117, BeginEnd_IterateOverBuffer_1117) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, 3);
    size_t count = 0;
    byte expected[] = {0x10, 0x20, 0x30};
    for (auto it = buf.begin(); it != buf.end(); ++it) {
        EXPECT_EQ(*it, expected[count]);
        ++count;
    }
    EXPECT_EQ(count, 3u);
}

TEST_F(DataBufTest_1117, BeginEnd_EmptyBuffer_1117) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}

// ==================== Copy/Move semantics ====================

TEST_F(DataBufTest_1117, MoveConstructor_TransfersOwnership_1117) {
    DataBuf buf1(10);
    buf1.write_uint8(0, 0xAA);
    DataBuf buf2(std::move(buf1));
    EXPECT_EQ(buf2.size(), 10u);
    EXPECT_EQ(buf2.read_uint8(0), 0xAA);
}

TEST_F(DataBufTest_1117, MoveAssignment_TransfersOwnership_1117) {
    DataBuf buf1(10);
    buf1.write_uint8(0, 0xBB);
    DataBuf buf2;
    buf2 = std::move(buf1);
    EXPECT_EQ(buf2.size(), 10u);
    EXPECT_EQ(buf2.read_uint8(0), 0xBB);
}

// ==================== Mixed type read/write at various offsets ====================

TEST_F(DataBufTest_1117, MixedReadWrite_MultipleTypes_1117) {
    DataBuf buf(20);
    buf.write_uint8(0, 0x01);
    buf.write_uint16(1, 0x0203, bigEndian);
    buf.write_uint32(3, 0x04050607, bigEndian);
    buf.write_uint64(7, 0x08090A0B0C0D0E0FULL, bigEndian);

    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint16(1, bigEndian), 0x0203);
    EXPECT_EQ(buf.read_uint32(3, bigEndian), 0x04050607u);
    EXPECT_EQ(buf.read_uint64(7, bigEndian), 0x08090A0B0C0D0E0FULL);
}

// ==================== Alloc after data ====================

TEST_F(DataBufTest_1117, Alloc_AfterExistingData_1117) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    EXPECT_EQ(buf.size(), 3u);
    buf.alloc(10);
    EXPECT_EQ(buf.size(), 10u);
}

// ==================== Overwrite values ====================

TEST_F(DataBufTest_1117, WriteUint8_Overwrite_1117) {
    DataBuf buf(1);
    buf.write_uint8(0, 0x11);
    EXPECT_EQ(buf.read_uint8(0), 0x11);
    buf.write_uint8(0, 0x22);
    EXPECT_EQ(buf.read_uint8(0), 0x22);
}

TEST_F(DataBufTest_1117, WriteUint32_Overwrite_1117) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x11111111, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x11111111u);
    buf.write_uint32(0, 0x22222222, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x22222222u);
}

// ==================== Large buffer ====================

TEST_F(DataBufTest_1117, LargeBuffer_AllocAndUse_1117) {
    DataBuf buf(1000000);
    EXPECT_EQ(buf.size(), 1000000u);
    buf.write_uint8(999999, 0xFF);
    EXPECT_EQ(buf.read_uint8(999999), 0xFF);
}

// ==================== Data pointer consistency ====================

TEST_F(DataBufTest_1117, DataPointer_ConsistentWithCData_1117) {
    DataBuf buf(10);
    buf.write_uint8(0, 0x42);
    const byte* cptr = buf.c_data(0);
    byte* ptr = buf.data(0);
    EXPECT_EQ(*cptr, *ptr);
    EXPECT_EQ(*cptr, 0x42);
}
