#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <stdexcept>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for c_data()
// ============================================================

TEST(DataBufCDataTest_1128, DefaultConstructedBuffer_ReturnsNullptr_1128) {
    DataBuf buf;
    EXPECT_EQ(buf.c_data(0), nullptr);
}

TEST(DataBufCDataTest_1128, EmptyBuffer_OffsetZero_ReturnsNullptr_1128) {
    DataBuf buf(0);
    EXPECT_EQ(buf.c_data(0), nullptr);
}

TEST(DataBufCDataTest_1128, NonEmptyBuffer_OffsetZero_ReturnsValidPointer_1128) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data(0);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 0x01);
}

TEST(DataBufCDataTest_1128, NonEmptyBuffer_OffsetMiddle_ReturnsCorrectPointer_1128) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    DataBuf buf(data, 4);
    const byte* ptr = buf.c_data(2);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 0x30);
}

TEST(DataBufCDataTest_1128, NonEmptyBuffer_OffsetLastElement_ReturnsCorrectPointer_1128) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data(2);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 0xCC);
}

TEST(DataBufCDataTest_1128, NonEmptyBuffer_OffsetEqualsSize_ReturnsNullptr_1128) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    EXPECT_EQ(buf.c_data(3), nullptr);
}

TEST(DataBufCDataTest_1128, NonEmptyBuffer_OffsetGreaterThanSize_ThrowsOutOfRange_1128) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    EXPECT_THROW(buf.c_data(4), std::out_of_range);
}

TEST(DataBufCDataTest_1128, NonEmptyBuffer_OffsetMuchGreaterThanSize_ThrowsOutOfRange_1128) {
    const byte data[] = {0x01};
    DataBuf buf(data, 1);
    EXPECT_THROW(buf.c_data(100), std::out_of_range);
}

TEST(DataBufCDataTest_1128, SingleByteBuffer_OffsetZero_ReturnsValidPointer_1128) {
    const byte data[] = {0xFF};
    DataBuf buf(data, 1);
    const byte* ptr = buf.c_data(0);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 0xFF);
}

TEST(DataBufCDataTest_1128, SingleByteBuffer_OffsetOne_ReturnsNullptr_1128) {
    const byte data[] = {0xFF};
    DataBuf buf(data, 1);
    EXPECT_EQ(buf.c_data(1), nullptr);
}

TEST(DataBufCDataTest_1128, SingleByteBuffer_OffsetTwo_ThrowsOutOfRange_1128) {
    const byte data[] = {0xFF};
    DataBuf buf(data, 1);
    EXPECT_THROW(buf.c_data(2), std::out_of_range);
}

// ============================================================
// Tests for other DataBuf methods (based on interface)
// ============================================================

TEST(DataBufTest_1128, ConstructWithSize_HasCorrectSize_1128) {
    DataBuf buf(10);
    EXPECT_EQ(buf.size(), 10u);
    EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_1128, ConstructWithData_HasCorrectSize_1128) {
    const byte data[] = {1, 2, 3, 4, 5};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST(DataBufTest_1128, DefaultConstructed_IsEmpty_1128) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_1128, Alloc_ChangesSize_1128) {
    DataBuf buf;
    buf.alloc(20);
    EXPECT_EQ(buf.size(), 20u);
    EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_1128, Resize_ChangesSize_1128) {
    DataBuf buf(10);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
    buf.resize(15);
    EXPECT_EQ(buf.size(), 15u);
}

TEST(DataBufTest_1128, Reset_MakesEmpty_1128) {
    DataBuf buf(10);
    EXPECT_FALSE(buf.empty());
    buf.reset();
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_1128, ReadWriteUint8_1128) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x42);
    buf.write_uint8(3, 0xAB);
    EXPECT_EQ(buf.read_uint8(0), 0x42);
    EXPECT_EQ(buf.read_uint8(3), 0xAB);
}

TEST(DataBufTest_1128, ReadWriteUint16_BigEndian_1128) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST(DataBufTest_1128, ReadWriteUint16_LittleEndian_1128) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x5678, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x5678);
}

TEST(DataBufTest_1128, ReadWriteUint32_BigEndian_1128) {
    DataBuf buf(8);
    buf.write_uint32(0, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xDEADBEEF);
}

TEST(DataBufTest_1128, ReadWriteUint32_LittleEndian_1128) {
    DataBuf buf(8);
    buf.write_uint32(2, 0xCAFEBABE, littleEndian);
    EXPECT_EQ(buf.read_uint32(2, littleEndian), 0xCAFEBABE);
}

TEST(DataBufTest_1128, ReadWriteUint64_BigEndian_1128) {
    DataBuf buf(16);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), val);
}

TEST(DataBufTest_1128, ReadWriteUint64_LittleEndian_1128) {
    DataBuf buf(16);
    uint64_t val = 0xFEDCBA9876543210ULL;
    buf.write_uint64(4, val, littleEndian);
    EXPECT_EQ(buf.read_uint64(4, littleEndian), val);
}

TEST(DataBufTest_1128, CmpBytes_Equal_1128) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_1128, CmpBytes_NotEqual_1128) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0xFF, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_1128, CmpBytes_WithOffset_1128) {
    const byte data[] = {0xAA, 0xBB, 0x01, 0x02};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(2, cmp, 2), 0);
}

TEST(DataBufTest_1128, Data_NonConst_ReturnsWritablePointer_1128) {
    DataBuf buf(4);
    byte* ptr = buf.data(0);
    ASSERT_NE(ptr, nullptr);
    ptr[0] = 0x42;
    EXPECT_EQ(buf.read_uint8(0), 0x42);
}

TEST(DataBufTest_1128, CStr_ReturnsCharPointer_1128) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(0);
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "Hello");
}

TEST(DataBufTest_1128, CStr_WithOffset_1128) {
    const byte data[] = {'X', 'Y', 'H', 'i', '\0'};
    DataBuf buf(data, 5);
    const char* str = buf.c_str(2);
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "Hi");
}

TEST(DataBufTest_1128, AfterReset_CDataReturnsNullptr_1128) {
    const byte data[] = {1, 2, 3};
    DataBuf buf(data, 3);
    ASSERT_NE(buf.c_data(0), nullptr);
    buf.reset();
    EXPECT_EQ(buf.c_data(0), nullptr);
}

TEST(DataBufTest_1128, AllocZero_IsEmpty_1128) {
    DataBuf buf;
    buf.alloc(0);
    EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_1128, ResizeToZero_IsEmpty_1128) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufCDataTest_1128, AfterAlloc_CDataOffsetZero_ReturnsNonNull_1128) {
    DataBuf buf;
    buf.alloc(5);
    EXPECT_NE(buf.c_data(0), nullptr);
}

TEST(DataBufCDataTest_1128, EmptyAfterReset_OffsetOne_ThrowsOrReturnsNull_1128) {
    DataBuf buf(3);
    buf.reset();
    // pData_ is empty, offset 0 should return nullptr
    EXPECT_EQ(buf.c_data(0), nullptr);
}

TEST(DataBufTest_1128, BeginEndIterators_1128) {
    DataBuf buf(3);
    buf.write_uint8(0, 0x10);
    buf.write_uint8(1, 0x20);
    buf.write_uint8(2, 0x30);
    auto it = buf.begin();
    EXPECT_EQ(*it, 0x10);
    ++it;
    EXPECT_EQ(*it, 0x20);
    ++it;
    EXPECT_EQ(*it, 0x30);
    ++it;
    EXPECT_EQ(it, buf.end());
}

TEST(DataBufTest_1128, ConstructFromPointerAndSize_DataIntegrity_1128) {
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.read_uint8(0), 0xDE);
    EXPECT_EQ(buf.read_uint8(1), 0xAD);
    EXPECT_EQ(buf.read_uint8(2), 0xBE);
    EXPECT_EQ(buf.read_uint8(3), 0xEF);
}

TEST(DataBufTest_1128, Uint16_EndianConsistency_1128) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0102, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    
    buf.write_uint16(0, 0x0102, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x02);
    EXPECT_EQ(buf.read_uint8(1), 0x01);
}

TEST(DataBufTest_1128, Uint32_EndianConsistency_1128) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
    
    buf.write_uint32(0, 0x01020304, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x04);
    EXPECT_EQ(buf.read_uint8(1), 0x03);
    EXPECT_EQ(buf.read_uint8(2), 0x02);
    EXPECT_EQ(buf.read_uint8(3), 0x01);
}
