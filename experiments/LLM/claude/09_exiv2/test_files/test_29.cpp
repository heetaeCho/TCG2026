#include <gtest/gtest.h>
#include "exiv2/types.hpp"

using namespace Exiv2;

// ============================================================
// Default Constructor Tests
// ============================================================

TEST(DataBufTest_29, DefaultConstructor_IsEmpty_29) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// Size Constructor Tests
// ============================================================

TEST(DataBufTest_29, SizeConstructor_CreatesBufferOfGivenSize_29) {
  DataBuf buf(100);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), 100u);
}

TEST(DataBufTest_29, SizeConstructor_ZeroSize_IsEmpty_29) {
  DataBuf buf(0);
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_29, SizeConstructor_SingleByte_29) {
  DataBuf buf(1);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), 1u);
}

// ============================================================
// Data Pointer Constructor Tests
// ============================================================

TEST(DataBufTest_29, DataConstructor_CopiesData_29) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, sizeof(data));
  EXPECT_EQ(buf.size(), 4u);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(1), 0x02);
  EXPECT_EQ(buf.read_uint8(2), 0x03);
  EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST(DataBufTest_29, DataConstructor_ZeroSize_29) {
  const uint8_t data[] = {0x01};
  DataBuf buf(data, 0);
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// alloc Tests
// ============================================================

TEST(DataBufTest_29, Alloc_AllocatesNewBuffer_29) {
  DataBuf buf;
  buf.alloc(50);
  EXPECT_EQ(buf.size(), 50u);
  EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_29, Alloc_ZeroSize_MakesEmpty_29) {
  DataBuf buf(10);
  buf.alloc(0);
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_29, Alloc_OverwritesPreviousAllocation_29) {
  DataBuf buf(10);
  buf.alloc(20);
  EXPECT_EQ(buf.size(), 20u);
}

// ============================================================
// resize Tests
// ============================================================

TEST(DataBufTest_29, Resize_IncreasesSize_29) {
  DataBuf buf(10);
  buf.resize(20);
  EXPECT_EQ(buf.size(), 20u);
}

TEST(DataBufTest_29, Resize_DecreasesSize_29) {
  DataBuf buf(20);
  buf.resize(5);
  EXPECT_EQ(buf.size(), 5u);
}

TEST(DataBufTest_29, Resize_ToZero_29) {
  DataBuf buf(10);
  buf.resize(0);
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_29, Resize_PreservesExistingData_29) {
  const uint8_t data[] = {0xAA, 0xBB, 0xCC};
  DataBuf buf(data, 3);
  buf.resize(5);
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_EQ(buf.read_uint8(0), 0xAA);
  EXPECT_EQ(buf.read_uint8(1), 0xBB);
  EXPECT_EQ(buf.read_uint8(2), 0xCC);
}

// ============================================================
// reset Tests
// ============================================================

TEST(DataBufTest_29, Reset_ClearsBuffer_29) {
  DataBuf buf(50);
  buf.reset();
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_29, Reset_OnEmptyBuffer_29) {
  DataBuf buf;
  buf.reset();
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// read_uint8 / write_uint8 Tests
// ============================================================

TEST(DataBufTest_29, ReadWriteUint8_Normal_29) {
  DataBuf buf(4);
  buf.write_uint8(0, 0x00);
  buf.write_uint8(1, 0x7F);
  buf.write_uint8(2, 0x80);
  buf.write_uint8(3, 0xFF);
  EXPECT_EQ(buf.read_uint8(0), 0x00);
  EXPECT_EQ(buf.read_uint8(1), 0x7F);
  EXPECT_EQ(buf.read_uint8(2), 0x80);
  EXPECT_EQ(buf.read_uint8(3), 0xFF);
}

TEST(DataBufTest_29, ReadWriteUint8_Overwrite_29) {
  DataBuf buf(1);
  buf.write_uint8(0, 0x42);
  EXPECT_EQ(buf.read_uint8(0), 0x42);
  buf.write_uint8(0, 0x99);
  EXPECT_EQ(buf.read_uint8(0), 0x99);
}

// ============================================================
// read_uint16 / write_uint16 Tests
// ============================================================

TEST(DataBufTest_29, ReadWriteUint16_LittleEndian_29) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x1234, littleEndian);
  buf.write_uint16(2, 0xABCD, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
  EXPECT_EQ(buf.read_uint16(2, littleEndian), 0xABCD);
}

TEST(DataBufTest_29, ReadWriteUint16_BigEndian_29) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x1234, bigEndian);
  buf.write_uint16(2, 0xABCD, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
  EXPECT_EQ(buf.read_uint16(2, bigEndian), 0xABCD);
}

TEST(DataBufTest_29, ReadWriteUint16_EndiannessDifference_29) {
  DataBuf buf(2);
  buf.write_uint16(0, 0x0102, bigEndian);
  // Reading with different endianness should give a different value
  uint16_t bigVal = buf.read_uint16(0, bigEndian);
  uint16_t littleVal = buf.read_uint16(0, littleEndian);
  EXPECT_EQ(bigVal, 0x0102);
  EXPECT_EQ(littleVal, 0x0201);
}

TEST(DataBufTest_29, ReadWriteUint16_ZeroValue_29) {
  DataBuf buf(2);
  buf.write_uint16(0, 0x0000, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x0000);
}

TEST(DataBufTest_29, ReadWriteUint16_MaxValue_29) {
  DataBuf buf(2);
  buf.write_uint16(0, 0xFFFF, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xFFFF);
}

// ============================================================
// read_uint32 / write_uint32 Tests
// ============================================================

TEST(DataBufTest_29, ReadWriteUint32_LittleEndian_29) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x12345678, littleEndian);
  EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST(DataBufTest_29, ReadWriteUint32_BigEndian_29) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x12345678, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST(DataBufTest_29, ReadWriteUint32_EndiannessDifference_29) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x01020304, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x01020304u);
  EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x04030201u);
}

TEST(DataBufTest_29, ReadWriteUint32_ZeroValue_29) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x00000000, littleEndian);
  EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x00000000u);
}

TEST(DataBufTest_29, ReadWriteUint32_MaxValue_29) {
  DataBuf buf(4);
  buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

TEST(DataBufTest_29, ReadWriteUint32_AtOffset_29) {
  DataBuf buf(8);
  buf.write_uint32(4, 0xDEADBEEF, bigEndian);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xDEADBEEFu);
}

// ============================================================
// read_uint64 / write_uint64 Tests
// ============================================================

TEST(DataBufTest_29, ReadWriteUint64_LittleEndian_29) {
  DataBuf buf(8);
  buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
  EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

TEST(DataBufTest_29, ReadWriteUint64_BigEndian_29) {
  DataBuf buf(8);
  buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST(DataBufTest_29, ReadWriteUint64_ZeroValue_29) {
  DataBuf buf(8);
  buf.write_uint64(0, 0ULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0ULL);
}

TEST(DataBufTest_29, ReadWriteUint64_MaxValue_29) {
  DataBuf buf(8);
  buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, littleEndian);
  EXPECT_EQ(buf.read_uint64(0, littleEndian), 0xFFFFFFFFFFFFFFFFULL);
}

// ============================================================
// cmpBytes Tests
// ============================================================

TEST(DataBufTest_29, CmpBytes_Equal_29) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0x01, 0x02, 0x03, 0x04};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_29, CmpBytes_NotEqual_29) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0x01, 0x02, 0x04, 0x04};
  EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_29, CmpBytes_WithOffset_29) {
  const uint8_t data[] = {0x00, 0x00, 0xAA, 0xBB};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0xAA, 0xBB};
  EXPECT_EQ(buf.cmpBytes(2, cmp, 2), 0);
}

TEST(DataBufTest_29, CmpBytes_PartialCompare_29) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0x01, 0x02};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

TEST(DataBufTest_29, CmpBytes_LessThan_29) {
  const uint8_t data[] = {0x01, 0x02};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0x01, 0x03};
  EXPECT_LT(buf.cmpBytes(0, cmp, 2), 0);
}

TEST(DataBufTest_29, CmpBytes_GreaterThan_29) {
  const uint8_t data[] = {0x01, 0x04};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0x01, 0x03};
  EXPECT_GT(buf.cmpBytes(0, cmp, 2), 0);
}

// ============================================================
// data / c_data / c_str Tests
// ============================================================

TEST(DataBufTest_29, Data_ReturnsNonNullForNonEmpty_29) {
  DataBuf buf(10);
  EXPECT_NE(buf.data(0), nullptr);
}

TEST(DataBufTest_29, CData_ReturnsNonNullForNonEmpty_29) {
  DataBuf buf(10);
  EXPECT_NE(buf.c_data(0), nullptr);
}

TEST(DataBufTest_29, CStr_ReturnsNonNullForNonEmpty_29) {
  DataBuf buf(10);
  EXPECT_NE(buf.c_str(0), nullptr);
}

TEST(DataBufTest_29, Data_WithOffset_29) {
  const uint8_t data[] = {0x41, 0x42, 0x43};
  DataBuf buf(data, sizeof(data));
  byte* ptr0 = buf.data(0);
  byte* ptr1 = buf.data(1);
  EXPECT_EQ(ptr1 - ptr0, 1);
  EXPECT_EQ(*ptr0, 0x41);
  EXPECT_EQ(*ptr1, 0x42);
}

TEST(DataBufTest_29, CData_WithOffset_29) {
  const uint8_t data[] = {0x41, 0x42, 0x43};
  DataBuf buf(data, sizeof(data));
  const byte* ptr = buf.c_data(2);
  EXPECT_EQ(*ptr, 0x43);
}

TEST(DataBufTest_29, Data_ModifiableBuffer_29) {
  DataBuf buf(4);
  byte* ptr = buf.data(0);
  ptr[0] = 0xDE;
  ptr[1] = 0xAD;
  EXPECT_EQ(buf.read_uint8(0), 0xDE);
  EXPECT_EQ(buf.read_uint8(1), 0xAD);
}

// ============================================================
// empty / size Tests
// ============================================================

TEST(DataBufTest_29, Empty_TrueForDefault_29) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_29, Empty_FalseAfterAlloc_29) {
  DataBuf buf;
  buf.alloc(1);
  EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_29, Empty_TrueAfterReset_29) {
  DataBuf buf(10);
  buf.reset();
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_29, Size_CorrectAfterConstruction_29) {
  DataBuf buf(42);
  EXPECT_EQ(buf.size(), 42u);
}

TEST(DataBufTest_29, Size_ZeroAfterReset_29) {
  DataBuf buf(42);
  buf.reset();
  EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// begin / end iterator Tests
// ============================================================

TEST(DataBufTest_29, BeginEnd_EmptyBuffer_29) {
  DataBuf buf;
  EXPECT_EQ(buf.begin(), buf.end());
}

TEST(DataBufTest_29, BeginEnd_NonEmptyBuffer_29) {
  DataBuf buf(10);
  EXPECT_NE(buf.begin(), buf.end());
  EXPECT_EQ(std::distance(buf.begin(), buf.end()), 10);
}

TEST(DataBufTest_29, BeginEnd_IterateAndModify_29) {
  DataBuf buf(3);
  uint8_t val = 0;
  for (auto it = buf.begin(); it != buf.end(); ++it) {
    *it = val++;
  }
  EXPECT_EQ(buf.read_uint8(0), 0);
  EXPECT_EQ(buf.read_uint8(1), 1);
  EXPECT_EQ(buf.read_uint8(2), 2);
}

// ============================================================
// Copy semantics / Move semantics Tests
// ============================================================

TEST(DataBufTest_29, CopyConstructor_29) {
  const uint8_t data[] = {0x10, 0x20, 0x30};
  DataBuf original(data, sizeof(data));
  DataBuf copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.read_uint8(0), 0x10);
  EXPECT_EQ(copy.read_uint8(1), 0x20);
  EXPECT_EQ(copy.read_uint8(2), 0x30);
}

TEST(DataBufTest_29, MoveConstructor_29) {
  const uint8_t data[] = {0x10, 0x20, 0x30};
  DataBuf original(data, sizeof(data));
  DataBuf moved(std::move(original));
  EXPECT_EQ(moved.size(), 3u);
  EXPECT_EQ(moved.read_uint8(0), 0x10);
  EXPECT_EQ(moved.read_uint8(1), 0x20);
  EXPECT_EQ(moved.read_uint8(2), 0x30);
  // original should be empty after move
  EXPECT_TRUE(original.empty());
}

TEST(DataBufTest_29, CopyAssignment_29) {
  const uint8_t data[] = {0xAA, 0xBB};
  DataBuf original(data, sizeof(data));
  DataBuf copy;
  copy = original;
  EXPECT_EQ(copy.size(), 2u);
  EXPECT_EQ(copy.read_uint8(0), 0xAA);
  EXPECT_EQ(copy.read_uint8(1), 0xBB);
}

TEST(DataBufTest_29, MoveAssignment_29) {
  const uint8_t data[] = {0xAA, 0xBB};
  DataBuf original(data, sizeof(data));
  DataBuf moved;
  moved = std::move(original);
  EXPECT_EQ(moved.size(), 2u);
  EXPECT_EQ(moved.read_uint8(0), 0xAA);
  EXPECT_TRUE(original.empty());
}

// ============================================================
// Mixed read/write across types Tests
// ============================================================

TEST(DataBufTest_29, MixedReadWrite_Uint8AndUint16_29) {
  DataBuf buf(4);
  buf.write_uint8(0, 0xFF);
  buf.write_uint8(1, 0x00);
  // Reading as uint16 big endian: 0xFF00
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xFF00);
  // Reading as uint16 little endian: 0x00FF
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x00FF);
}

TEST(DataBufTest_29, MixedReadWrite_ByteLevel_29) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x01020304, bigEndian);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(1), 0x02);
  EXPECT_EQ(buf.read_uint8(2), 0x03);
  EXPECT_EQ(buf.read_uint8(3), 0x04);
}

// ============================================================
// Large buffer test
// ============================================================

TEST(DataBufTest_29, LargeBuffer_29) {
  const size_t largeSize = 1024 * 1024; // 1MB
  DataBuf buf(largeSize);
  EXPECT_EQ(buf.size(), largeSize);
  EXPECT_FALSE(buf.empty());
  // Write and read at boundaries
  buf.write_uint8(0, 0x01);
  buf.write_uint8(largeSize - 1, 0xFF);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(largeSize - 1), 0xFF);
}

// ============================================================
// Alloc after reset
// ============================================================

TEST(DataBufTest_29, AllocAfterReset_29) {
  DataBuf buf(10);
  buf.reset();
  EXPECT_TRUE(buf.empty());
  buf.alloc(5);
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_FALSE(buf.empty());
}

// ============================================================
// Multiple resizes
// ============================================================

TEST(DataBufTest_29, MultipleResizes_29) {
  DataBuf buf;
  buf.resize(10);
  EXPECT_EQ(buf.size(), 10u);
  buf.resize(100);
  EXPECT_EQ(buf.size(), 100u);
  buf.resize(5);
  EXPECT_EQ(buf.size(), 5u);
  buf.resize(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// Offset boundary for multi-byte read/write
// ============================================================

TEST(DataBufTest_29, ReadWriteUint32_AtLastValidOffset_29) {
  DataBuf buf(8);
  buf.write_uint32(4, 0xCAFEBABE, bigEndian);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xCAFEBABEu);
}

TEST(DataBufTest_29, ReadWriteUint64_AtOffset_29) {
  DataBuf buf(16);
  buf.write_uint64(8, 0xDEADC0DEBEEFCAFEULL, littleEndian);
  EXPECT_EQ(buf.read_uint64(8, littleEndian), 0xDEADC0DEBEEFCAFEULL);
}

// ============================================================
// CmpBytes with zero length
// ============================================================

TEST(DataBufTest_29, CmpBytes_ZeroLength_29) {
  const uint8_t data[] = {0x01, 0x02};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0xFF};
  // Comparing 0 bytes should be equal
  EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}
