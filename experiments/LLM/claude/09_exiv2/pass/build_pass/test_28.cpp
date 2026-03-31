#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Default Constructor Tests
// ============================================================

TEST(DataBufTest_28, DefaultConstructor_SizeIsZero_28) {
  DataBuf buf;
  EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_28, DefaultConstructor_IsEmpty_28) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// Size Constructor Tests
// ============================================================

TEST(DataBufTest_28, SizeConstructor_CreatesBufferOfGivenSize_28) {
  DataBuf buf(100);
  EXPECT_EQ(buf.size(), 100u);
  EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_28, SizeConstructor_ZeroSize_28) {
  DataBuf buf(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_28, SizeConstructor_SizeOne_28) {
  DataBuf buf(1);
  EXPECT_EQ(buf.size(), 1u);
  EXPECT_FALSE(buf.empty());
}

// ============================================================
// Data + Size Constructor Tests
// ============================================================

TEST(DataBufTest_28, DataConstructor_CopiesData_28) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  DataBuf buf(data, sizeof(data));
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(4), 0x05);
}

TEST(DataBufTest_28, DataConstructor_ZeroLength_28) {
  const byte data[] = {0x01};
  DataBuf buf(data, 0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// alloc Tests
// ============================================================

TEST(DataBufTest_28, Alloc_SetsSize_28) {
  DataBuf buf;
  buf.alloc(50);
  EXPECT_EQ(buf.size(), 50u);
}

TEST(DataBufTest_28, Alloc_ZeroSize_28) {
  DataBuf buf(10);
  buf.alloc(0);
  EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_28, Alloc_ReallocateLarger_28) {
  DataBuf buf(10);
  buf.alloc(100);
  EXPECT_EQ(buf.size(), 100u);
}

// ============================================================
// resize Tests
// ============================================================

TEST(DataBufTest_28, Resize_Grow_28) {
  DataBuf buf(10);
  buf.resize(20);
  EXPECT_EQ(buf.size(), 20u);
}

TEST(DataBufTest_28, Resize_Shrink_28) {
  DataBuf buf(20);
  buf.resize(5);
  EXPECT_EQ(buf.size(), 5u);
}

TEST(DataBufTest_28, Resize_ToZero_28) {
  DataBuf buf(10);
  buf.resize(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_28, Resize_PreservesExistingData_28) {
  const byte data[] = {0xAA, 0xBB, 0xCC};
  DataBuf buf(data, sizeof(data));
  buf.resize(10);
  EXPECT_EQ(buf.read_uint8(0), 0xAA);
  EXPECT_EQ(buf.read_uint8(1), 0xBB);
  EXPECT_EQ(buf.read_uint8(2), 0xCC);
}

// ============================================================
// reset Tests
// ============================================================

TEST(DataBufTest_28, Reset_ClearsBuffer_28) {
  DataBuf buf(100);
  buf.reset();
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_28, Reset_OnEmptyBuffer_28) {
  DataBuf buf;
  buf.reset();
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// read_uint8 / write_uint8 Tests
// ============================================================

TEST(DataBufTest_28, ReadWriteUint8_Basic_28) {
  DataBuf buf(4);
  buf.write_uint8(0, 0x12);
  buf.write_uint8(1, 0x34);
  buf.write_uint8(2, 0x56);
  buf.write_uint8(3, 0x78);
  EXPECT_EQ(buf.read_uint8(0), 0x12);
  EXPECT_EQ(buf.read_uint8(1), 0x34);
  EXPECT_EQ(buf.read_uint8(2), 0x56);
  EXPECT_EQ(buf.read_uint8(3), 0x78);
}

TEST(DataBufTest_28, ReadWriteUint8_BoundaryValues_28) {
  DataBuf buf(2);
  buf.write_uint8(0, 0x00);
  buf.write_uint8(1, 0xFF);
  EXPECT_EQ(buf.read_uint8(0), 0x00);
  EXPECT_EQ(buf.read_uint8(1), 0xFF);
}

// ============================================================
// read_uint16 / write_uint16 Tests
// ============================================================

TEST(DataBufTest_28, ReadWriteUint16_LittleEndian_28) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x1234, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST(DataBufTest_28, ReadWriteUint16_BigEndian_28) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x1234, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST(DataBufTest_28, ReadWriteUint16_DifferentByteOrders_28) {
  DataBuf buf(4);
  buf.write_uint16(0, 0xAABB, bigEndian);
  // Reading with different byte order should give a different result
  uint16_t readLE = buf.read_uint16(0, littleEndian);
  uint16_t readBE = buf.read_uint16(0, bigEndian);
  EXPECT_EQ(readBE, 0xAABB);
  EXPECT_NE(readLE, readBE);
}

TEST(DataBufTest_28, ReadWriteUint16_AtOffset_28) {
  DataBuf buf(8);
  buf.write_uint16(2, 0x5678, bigEndian);
  buf.write_uint16(4, 0x9ABC, littleEndian);
  EXPECT_EQ(buf.read_uint16(2, bigEndian), 0x5678);
  EXPECT_EQ(buf.read_uint16(4, littleEndian), 0x9ABC);
}

TEST(DataBufTest_28, ReadWriteUint16_BoundaryValues_28) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x0000, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x0000);
  buf.write_uint16(0, 0xFFFF, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xFFFF);
}

// ============================================================
// read_uint32 / write_uint32 Tests
// ============================================================

TEST(DataBufTest_28, ReadWriteUint32_LittleEndian_28) {
  DataBuf buf(8);
  buf.write_uint32(0, 0x12345678, littleEndian);
  EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST(DataBufTest_28, ReadWriteUint32_BigEndian_28) {
  DataBuf buf(8);
  buf.write_uint32(0, 0x12345678, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST(DataBufTest_28, ReadWriteUint32_AtOffset_28) {
  DataBuf buf(12);
  buf.write_uint32(4, 0xDEADBEEF, bigEndian);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xDEADBEEFu);
}

TEST(DataBufTest_28, ReadWriteUint32_BoundaryValues_28) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x00000000, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x00000000u);
  buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

// ============================================================
// read_uint64 / write_uint64 Tests
// ============================================================

TEST(DataBufTest_28, ReadWriteUint64_LittleEndian_28) {
  DataBuf buf(16);
  buf.write_uint64(0, 0x123456789ABCDEF0ULL, littleEndian);
  EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x123456789ABCDEF0ULL);
}

TEST(DataBufTest_28, ReadWriteUint64_BigEndian_28) {
  DataBuf buf(16);
  buf.write_uint64(0, 0x123456789ABCDEF0ULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x123456789ABCDEF0ULL);
}

TEST(DataBufTest_28, ReadWriteUint64_AtOffset_28) {
  DataBuf buf(20);
  buf.write_uint64(8, 0xFEDCBA9876543210ULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(8, bigEndian), 0xFEDCBA9876543210ULL);
}

TEST(DataBufTest_28, ReadWriteUint64_BoundaryValues_28) {
  DataBuf buf(8);
  buf.write_uint64(0, 0x0000000000000000ULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0000000000000000ULL);
  buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFULL);
}

// ============================================================
// cmpBytes Tests
// ============================================================

TEST(DataBufTest_28, CmpBytes_Equal_28) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, sizeof(data));
  const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
  EXPECT_EQ(buf.cmpBytes(0, cmp, sizeof(cmp)), 0);
}

TEST(DataBufTest_28, CmpBytes_NotEqual_28) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, sizeof(data));
  const byte cmp[] = {0x01, 0x02, 0x05, 0x04};
  EXPECT_NE(buf.cmpBytes(0, cmp, sizeof(cmp)), 0);
}

TEST(DataBufTest_28, CmpBytes_AtOffset_28) {
  const byte data[] = {0x00, 0x00, 0xAA, 0xBB};
  DataBuf buf(data, sizeof(data));
  const byte cmp[] = {0xAA, 0xBB};
  EXPECT_EQ(buf.cmpBytes(2, cmp, sizeof(cmp)), 0);
}

TEST(DataBufTest_28, CmpBytes_PartialMatch_28) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, sizeof(data));
  const byte cmp[] = {0x01, 0x02};
  EXPECT_EQ(buf.cmpBytes(0, cmp, sizeof(cmp)), 0);
}

TEST(DataBufTest_28, CmpBytes_ZeroLength_28) {
  const byte data[] = {0x01, 0x02};
  DataBuf buf(data, sizeof(data));
  const byte cmp[] = {0xFF};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}

// ============================================================
// data / c_data / c_str Tests
// ============================================================

TEST(DataBufTest_28, Data_ReturnsNonNull_28) {
  DataBuf buf(10);
  EXPECT_NE(buf.data(0), nullptr);
}

TEST(DataBufTest_28, Data_AtOffset_28) {
  DataBuf buf(10);
  byte* p0 = buf.data(0);
  byte* p5 = buf.data(5);
  EXPECT_EQ(p5 - p0, 5);
}

TEST(DataBufTest_28, CData_ReturnsNonNull_28) {
  DataBuf buf(10);
  const byte* p = buf.c_data(0);
  EXPECT_NE(p, nullptr);
}

TEST(DataBufTest_28, CData_AtOffset_28) {
  DataBuf buf(10);
  const byte* p0 = buf.c_data(0);
  const byte* p3 = buf.c_data(3);
  EXPECT_EQ(p3 - p0, 3);
}

TEST(DataBufTest_28, CStr_ReturnsNonNull_28) {
  DataBuf buf(10);
  const char* s = buf.c_str(0);
  EXPECT_NE(s, nullptr);
}

TEST(DataBufTest_28, CStr_AtOffset_28) {
  const byte data[] = "Hello";
  DataBuf buf(data, 6); // include null terminator
  const char* s = buf.c_str(0);
  EXPECT_STREQ(s, "Hello");
}

// ============================================================
// data() write-through test
// ============================================================

TEST(DataBufTest_28, Data_WriteThrough_28) {
  DataBuf buf(4);
  byte* p = buf.data(0);
  p[0] = 0xAB;
  p[1] = 0xCD;
  EXPECT_EQ(buf.read_uint8(0), 0xAB);
  EXPECT_EQ(buf.read_uint8(1), 0xCD);
}

// ============================================================
// begin / end Tests
// ============================================================

TEST(DataBufTest_28, BeginEnd_EmptyBuffer_28) {
  DataBuf buf;
  EXPECT_EQ(buf.begin(), buf.end());
}

TEST(DataBufTest_28, BeginEnd_NonEmptyBuffer_28) {
  DataBuf buf(10);
  EXPECT_NE(buf.begin(), buf.end());
  EXPECT_EQ(std::distance(buf.begin(), buf.end()), 10);
}

TEST(DataBufTest_28, BeginEnd_Iteration_28) {
  const byte data[] = {1, 2, 3, 4, 5};
  DataBuf buf(data, sizeof(data));
  byte sum = 0;
  for (auto it = buf.begin(); it != buf.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 15);
}

// ============================================================
// empty Tests
// ============================================================

TEST(DataBufTest_28, Empty_NewBuffer_28) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_28, Empty_AfterAlloc_28) {
  DataBuf buf;
  buf.alloc(10);
  EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_28, Empty_AfterReset_28) {
  DataBuf buf(10);
  EXPECT_FALSE(buf.empty());
  buf.reset();
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// Mixed operations (integration-like tests)
// ============================================================

TEST(DataBufTest_28, MixedReadWrite_MultipleTypes_28) {
  DataBuf buf(15);
  buf.write_uint8(0, 0xFF);
  buf.write_uint16(1, 0x1234, bigEndian);
  buf.write_uint32(3, 0xDEADBEEF, littleEndian);
  buf.write_uint64(7, 0x0102030405060708ULL, bigEndian);

  EXPECT_EQ(buf.read_uint8(0), 0xFF);
  EXPECT_EQ(buf.read_uint16(1, bigEndian), 0x1234);
  EXPECT_EQ(buf.read_uint32(3, littleEndian), 0xDEADBEEFu);
  EXPECT_EQ(buf.read_uint64(7, bigEndian), 0x0102030405060708ULL);
}

TEST(DataBufTest_28, AllocThenWriteAndRead_28) {
  DataBuf buf;
  buf.alloc(4);
  buf.write_uint32(0, 0xCAFEBABE, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xCAFEBABEu);
}

TEST(DataBufTest_28, ResizePreservesDataThenExtend_28) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x11223344, bigEndian);
  buf.resize(8);
  EXPECT_EQ(buf.size(), 8u);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x11223344u);
  buf.write_uint32(4, 0x55667788, bigEndian);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x55667788u);
}

TEST(DataBufTest_28, CopyConstructor_28) {
  const byte data[] = {0x0A, 0x0B, 0x0C};
  DataBuf original(data, sizeof(data));
  DataBuf copy(original);
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.read_uint8(0), 0x0A);
  EXPECT_EQ(copy.read_uint8(1), 0x0B);
  EXPECT_EQ(copy.read_uint8(2), 0x0C);
}

TEST(DataBufTest_28, MoveConstructor_28) {
  const byte data[] = {0x0A, 0x0B, 0x0C};
  DataBuf original(data, sizeof(data));
  DataBuf moved(std::move(original));
  EXPECT_EQ(moved.size(), 3u);
  EXPECT_EQ(moved.read_uint8(0), 0x0A);
  EXPECT_EQ(moved.read_uint8(2), 0x0C);
}

TEST(DataBufTest_28, CmpBytes_LessThan_28) {
  const byte data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, sizeof(data));
  const byte cmp[] = {0x01, 0x02, 0x04};
  int result = buf.cmpBytes(0, cmp, sizeof(cmp));
  EXPECT_LT(result, 0);  // 0x03 < 0x04
}

TEST(DataBufTest_28, CmpBytes_GreaterThan_28) {
  const byte data[] = {0x01, 0x02, 0x05};
  DataBuf buf(data, sizeof(data));
  const byte cmp[] = {0x01, 0x02, 0x04};
  int result = buf.cmpBytes(0, cmp, sizeof(cmp));
  EXPECT_GT(result, 0);  // 0x05 > 0x04
}

TEST(DataBufTest_28, DataConstructor_IndependentOfSource_28) {
  byte data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, sizeof(data));
  // Modify original data
  data[0] = 0xFF;
  // Buffer should retain original values
  EXPECT_EQ(buf.read_uint8(0), 0x01);
}

TEST(DataBufTest_28, LargeBuffer_28) {
  const size_t largeSize = 1024 * 1024; // 1 MB
  DataBuf buf(largeSize);
  EXPECT_EQ(buf.size(), largeSize);
  buf.write_uint8(0, 0xAA);
  buf.write_uint8(largeSize - 1, 0xBB);
  EXPECT_EQ(buf.read_uint8(0), 0xAA);
  EXPECT_EQ(buf.read_uint8(largeSize - 1), 0xBB);
}
