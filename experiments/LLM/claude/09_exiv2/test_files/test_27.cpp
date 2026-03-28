#include <gtest/gtest.h>
#include "exiv2/types.hpp"

using namespace Exiv2;

// ============================================================
// Default Construction Tests
// ============================================================

TEST(DataBufTest_27, DefaultConstructor_EmptyBuffer_27) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// Size Constructor Tests
// ============================================================

TEST(DataBufTest_27, SizeConstructor_CreatesBufferOfGivenSize_27) {
  DataBuf buf(100);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), 100u);
}

TEST(DataBufTest_27, SizeConstructor_ZeroSize_27) {
  DataBuf buf(0);
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// Data + Size Constructor Tests
// ============================================================

TEST(DataBufTest_27, DataConstructor_CopiesData_27) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  DataBuf buf(data, sizeof(data));
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_FALSE(buf.empty());
  for (size_t i = 0; i < sizeof(data); ++i) {
    EXPECT_EQ(buf.read_uint8(i), data[i]);
  }
}

TEST(DataBufTest_27, DataConstructor_ZeroSize_27) {
  const uint8_t data[] = {0x01};
  DataBuf buf(data, 0);
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// alloc Tests
// ============================================================

TEST(DataBufTest_27, Alloc_AllocatesNewBuffer_27) {
  DataBuf buf;
  buf.alloc(50);
  EXPECT_EQ(buf.size(), 50u);
  EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_27, Alloc_ZeroSize_27) {
  DataBuf buf(10);
  buf.alloc(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// resize Tests
// ============================================================

TEST(DataBufTest_27, Resize_IncreasesSize_27) {
  DataBuf buf(10);
  buf.resize(20);
  EXPECT_EQ(buf.size(), 20u);
}

TEST(DataBufTest_27, Resize_DecreasesSize_27) {
  DataBuf buf(20);
  buf.resize(5);
  EXPECT_EQ(buf.size(), 5u);
}

TEST(DataBufTest_27, Resize_ToZero_27) {
  DataBuf buf(10);
  buf.resize(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_27, Resize_PreservesExistingData_27) {
  const uint8_t data[] = {0xAA, 0xBB, 0xCC};
  DataBuf buf(data, sizeof(data));
  buf.resize(10);
  EXPECT_EQ(buf.size(), 10u);
  EXPECT_EQ(buf.read_uint8(0), 0xAA);
  EXPECT_EQ(buf.read_uint8(1), 0xBB);
  EXPECT_EQ(buf.read_uint8(2), 0xCC);
}

// ============================================================
// reset Tests
// ============================================================

TEST(DataBufTest_27, Reset_ClearsBuffer_27) {
  DataBuf buf(100);
  buf.reset();
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_27, Reset_OnEmptyBuffer_27) {
  DataBuf buf;
  buf.reset();
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// read_uint8 / write_uint8 Tests
// ============================================================

TEST(DataBufTest_27, ReadWriteUint8_Normal_27) {
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

// ============================================================
// read_uint16 / write_uint16 Tests
// ============================================================

TEST(DataBufTest_27, ReadWriteUint16_LittleEndian_27) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x1234, littleEndian);
  buf.write_uint16(2, 0xABCD, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
  EXPECT_EQ(buf.read_uint16(2, littleEndian), 0xABCD);
}

TEST(DataBufTest_27, ReadWriteUint16_BigEndian_27) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x1234, bigEndian);
  buf.write_uint16(2, 0xABCD, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
  EXPECT_EQ(buf.read_uint16(2, bigEndian), 0xABCD);
}

TEST(DataBufTest_27, ReadWriteUint16_EndianMismatch_27) {
  DataBuf buf(2);
  buf.write_uint16(0, 0x0102, bigEndian);
  // Reading with opposite endianness should give swapped bytes
  uint16_t val = buf.read_uint16(0, littleEndian);
  EXPECT_EQ(val, 0x0201);
}

TEST(DataBufTest_27, ReadWriteUint16_BoundaryValues_27) {
  DataBuf buf(2);
  buf.write_uint16(0, 0x0000, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x0000);
  buf.write_uint16(0, 0xFFFF, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0xFFFF);
}

// ============================================================
// read_uint32 / write_uint32 Tests
// ============================================================

TEST(DataBufTest_27, ReadWriteUint32_LittleEndian_27) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x12345678, littleEndian);
  EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST(DataBufTest_27, ReadWriteUint32_BigEndian_27) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x12345678, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST(DataBufTest_27, ReadWriteUint32_EndianMismatch_27) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x01020304, bigEndian);
  uint32_t val = buf.read_uint32(0, littleEndian);
  EXPECT_EQ(val, 0x04030201u);
}

TEST(DataBufTest_27, ReadWriteUint32_BoundaryValues_27) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x00000000, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x00000000u);
  buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

// ============================================================
// read_uint64 / write_uint64 Tests
// ============================================================

TEST(DataBufTest_27, ReadWriteUint64_LittleEndian_27) {
  DataBuf buf(8);
  buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
  EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

TEST(DataBufTest_27, ReadWriteUint64_BigEndian_27) {
  DataBuf buf(8);
  buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST(DataBufTest_27, ReadWriteUint64_EndianMismatch_27) {
  DataBuf buf(8);
  buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
  uint64_t val = buf.read_uint64(0, littleEndian);
  EXPECT_EQ(val, 0x0807060504030201ULL);
}

TEST(DataBufTest_27, ReadWriteUint64_BoundaryValues_27) {
  DataBuf buf(8);
  buf.write_uint64(0, 0x0000000000000000ULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0000000000000000ULL);
  buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFULL);
}

// ============================================================
// cmpBytes Tests
// ============================================================

TEST(DataBufTest_27, CmpBytes_EqualData_27) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, sizeof(data));
  EXPECT_EQ(buf.cmpBytes(0, data, sizeof(data)), 0);
}

TEST(DataBufTest_27, CmpBytes_DifferentData_27) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  const uint8_t other[] = {0x01, 0x02, 0x05, 0x04};
  DataBuf buf(data, sizeof(data));
  EXPECT_NE(buf.cmpBytes(0, other, sizeof(other)), 0);
}

TEST(DataBufTest_27, CmpBytes_WithOffset_27) {
  const uint8_t data[] = {0xAA, 0xBB, 0x01, 0x02, 0x03};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0x01, 0x02, 0x03};
  EXPECT_EQ(buf.cmpBytes(2, cmp, sizeof(cmp)), 0);
}

TEST(DataBufTest_27, CmpBytes_ZeroSize_27) {
  const uint8_t data[] = {0x01, 0x02};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0xFF};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}

TEST(DataBufTest_27, CmpBytes_PartialMatch_27) {
  const uint8_t data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0x01, 0x02};
  EXPECT_EQ(buf.cmpBytes(0, cmp, sizeof(cmp)), 0);
}

// ============================================================
// data / c_data / c_str Tests
// ============================================================

TEST(DataBufTest_27, Data_ReturnsValidPointer_27) {
  const uint8_t data[] = {0x41, 0x42, 0x43};
  DataBuf buf(data, sizeof(data));
  byte* ptr = buf.data(0);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 0x41);
  EXPECT_EQ(ptr[1], 0x42);
  EXPECT_EQ(ptr[2], 0x43);
}

TEST(DataBufTest_27, Data_WithOffset_27) {
  const uint8_t data[] = {0x41, 0x42, 0x43, 0x44};
  DataBuf buf(data, sizeof(data));
  byte* ptr = buf.data(2);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 0x43);
  EXPECT_EQ(ptr[1], 0x44);
}

TEST(DataBufTest_27, CData_ReturnsConstPointer_27) {
  const uint8_t data[] = {0x10, 0x20, 0x30};
  DataBuf buf(data, sizeof(data));
  const byte* ptr = buf.c_data(0);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 0x10);
}

TEST(DataBufTest_27, CData_WithOffset_27) {
  const uint8_t data[] = {0x10, 0x20, 0x30};
  DataBuf buf(data, sizeof(data));
  const byte* ptr = buf.c_data(1);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 0x20);
}

TEST(DataBufTest_27, CStr_ReturnsCharPointer_27) {
  const uint8_t data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
  DataBuf buf(data, sizeof(data));
  const char* str = buf.c_str(0);
  ASSERT_NE(str, nullptr);
  EXPECT_STREQ(str, "Hello");
}

TEST(DataBufTest_27, CStr_WithOffset_27) {
  const uint8_t data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
  DataBuf buf(data, sizeof(data));
  const char* str = buf.c_str(2);
  ASSERT_NE(str, nullptr);
  EXPECT_STREQ(str, "llo");
}

// ============================================================
// Modification through data() pointer
// ============================================================

TEST(DataBufTest_27, Data_ModificationReflectedInRead_27) {
  DataBuf buf(4);
  byte* ptr = buf.data(0);
  ptr[0] = 0xDE;
  ptr[1] = 0xAD;
  ptr[2] = 0xBE;
  ptr[3] = 0xEF;
  EXPECT_EQ(buf.read_uint8(0), 0xDE);
  EXPECT_EQ(buf.read_uint8(1), 0xAD);
  EXPECT_EQ(buf.read_uint8(2), 0xBE);
  EXPECT_EQ(buf.read_uint8(3), 0xEF);
}

// ============================================================
// begin / end Iterator Tests
// ============================================================

TEST(DataBufTest_27, BeginEnd_Iteration_27) {
  const uint8_t data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, sizeof(data));
  size_t count = 0;
  uint8_t expected[] = {0x01, 0x02, 0x03};
  for (auto it = buf.begin(); it != buf.end(); ++it) {
    EXPECT_EQ(*it, expected[count]);
    ++count;
  }
  EXPECT_EQ(count, 3u);
}

TEST(DataBufTest_27, BeginEnd_EmptyBuffer_27) {
  DataBuf buf;
  EXPECT_EQ(buf.begin(), buf.end());
}

TEST(DataBufTest_27, BeginEnd_DistanceEqualsSize_27) {
  DataBuf buf(42);
  auto dist = std::distance(buf.begin(), buf.end());
  EXPECT_EQ(static_cast<size_t>(dist), buf.size());
}

// ============================================================
// size / empty Tests
// ============================================================

TEST(DataBufTest_27, Size_AfterConstruction_27) {
  DataBuf buf(256);
  EXPECT_EQ(buf.size(), 256u);
}

TEST(DataBufTest_27, Empty_DefaultConstructed_27) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_27, Empty_NonEmptyBuffer_27) {
  DataBuf buf(1);
  EXPECT_FALSE(buf.empty());
}

// ============================================================
// Copy / Move Semantics Tests
// ============================================================

TEST(DataBufTest_27, CopyConstruction_27) {
  const uint8_t data[] = {0x0A, 0x0B, 0x0C};
  DataBuf buf1(data, sizeof(data));
  DataBuf buf2(buf1);
  EXPECT_EQ(buf2.size(), buf1.size());
  for (size_t i = 0; i < buf1.size(); ++i) {
    EXPECT_EQ(buf2.read_uint8(i), buf1.read_uint8(i));
  }
}

TEST(DataBufTest_27, MoveConstruction_27) {
  const uint8_t data[] = {0x0A, 0x0B, 0x0C};
  DataBuf buf1(data, sizeof(data));
  DataBuf buf2(std::move(buf1));
  EXPECT_EQ(buf2.size(), 3u);
  EXPECT_EQ(buf2.read_uint8(0), 0x0A);
  EXPECT_EQ(buf2.read_uint8(1), 0x0B);
  EXPECT_EQ(buf2.read_uint8(2), 0x0C);
}

TEST(DataBufTest_27, CopyAssignment_27) {
  const uint8_t data[] = {0x01, 0x02};
  DataBuf buf1(data, sizeof(data));
  DataBuf buf2;
  buf2 = buf1;
  EXPECT_EQ(buf2.size(), 2u);
  EXPECT_EQ(buf2.read_uint8(0), 0x01);
  EXPECT_EQ(buf2.read_uint8(1), 0x02);
}

TEST(DataBufTest_27, MoveAssignment_27) {
  const uint8_t data[] = {0x01, 0x02};
  DataBuf buf1(data, sizeof(data));
  DataBuf buf2;
  buf2 = std::move(buf1);
  EXPECT_EQ(buf2.size(), 2u);
  EXPECT_EQ(buf2.read_uint8(0), 0x01);
  EXPECT_EQ(buf2.read_uint8(1), 0x02);
}

// ============================================================
// Mixed read/write at various offsets
// ============================================================

TEST(DataBufTest_27, ReadWriteUint16_AtNonZeroOffset_27) {
  DataBuf buf(10);
  buf.write_uint16(4, 0xBEEF, bigEndian);
  EXPECT_EQ(buf.read_uint16(4, bigEndian), 0xBEEF);
}

TEST(DataBufTest_27, ReadWriteUint32_AtNonZeroOffset_27) {
  DataBuf buf(12);
  buf.write_uint32(8, 0xDEADBEEF, littleEndian);
  EXPECT_EQ(buf.read_uint32(8, littleEndian), 0xDEADBEEFu);
}

TEST(DataBufTest_27, ReadWriteUint64_AtNonZeroOffset_27) {
  DataBuf buf(16);
  buf.write_uint64(8, 0xCAFEBABEDEADBEEFULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(8, bigEndian), 0xCAFEBABEDEADBEEFULL);
}

// ============================================================
// Alloc then write then read
// ============================================================

TEST(DataBufTest_27, AllocThenWriteRead_27) {
  DataBuf buf;
  buf.alloc(8);
  buf.write_uint32(0, 0x11223344, bigEndian);
  buf.write_uint32(4, 0x55667788, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x11223344u);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x55667788u);
}

// ============================================================
// Resize preserves data and allows new writes
// ============================================================

TEST(DataBufTest_27, ResizeAndWriteNewArea_27) {
  DataBuf buf(4);
  buf.write_uint32(0, 0xAAAAAAAA, bigEndian);
  buf.resize(8);
  buf.write_uint32(4, 0xBBBBBBBB, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xAAAAAAAAu);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xBBBBBBBBu);
}

// ============================================================
// Large buffer test
// ============================================================

TEST(DataBufTest_27, LargeBuffer_27) {
  const size_t largeSize = 1024 * 1024; // 1MB
  DataBuf buf(largeSize);
  EXPECT_EQ(buf.size(), largeSize);
  EXPECT_FALSE(buf.empty());
  buf.write_uint8(0, 0x01);
  buf.write_uint8(largeSize - 1, 0xFF);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(largeSize - 1), 0xFF);
}

// ============================================================
// Overwrite existing data
// ============================================================

TEST(DataBufTest_27, OverwriteData_27) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x12345678, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
  buf.write_uint32(0, 0xAABBCCDD, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xAABBCCDDu);
}

// ============================================================
// Single byte buffer
// ============================================================

TEST(DataBufTest_27, SingleByteBuffer_27) {
  DataBuf buf(1);
  EXPECT_EQ(buf.size(), 1u);
  EXPECT_FALSE(buf.empty());
  buf.write_uint8(0, 0x42);
  EXPECT_EQ(buf.read_uint8(0), 0x42);
}

// ============================================================
// cmpBytes with buffer data at boundary
// ============================================================

TEST(DataBufTest_27, CmpBytes_AtEndOfBuffer_27) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  DataBuf buf(data, sizeof(data));
  const uint8_t cmp[] = {0x04, 0x05};
  EXPECT_EQ(buf.cmpBytes(3, cmp, sizeof(cmp)), 0);
}

// ============================================================
// Verify data pointer consistency
// ============================================================

TEST(DataBufTest_27, DataPointerConsistencyWithCData_27) {
  const uint8_t data[] = {0xAA, 0xBB};
  DataBuf buf(data, sizeof(data));
  const byte* cptr = buf.c_data(0);
  byte* mptr = buf.data(0);
  EXPECT_EQ(static_cast<const byte*>(mptr), cptr);
}
