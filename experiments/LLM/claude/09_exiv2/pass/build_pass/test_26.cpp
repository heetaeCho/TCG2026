#include <gtest/gtest.h>
#include "exiv2/types.hpp"

using namespace Exiv2;

// ============================================================
// Test Fixture
// ============================================================
class DataBufTest_26 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(DataBufTest_26, DefaultConstructor_CreatesEmptyBuffer_26) {
  DataBuf buf;
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_26, SizeConstructor_CreatesBufferOfGivenSize_26) {
  DataBuf buf(100);
  EXPECT_EQ(buf.size(), 100u);
  EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_26, SizeConstructor_ZeroSize_CreatesEmptyBuffer_26) {
  DataBuf buf(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_26, DataConstructor_CopiesData_26) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  DataBuf buf(data, 5);
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(1), 0x02);
  EXPECT_EQ(buf.read_uint8(2), 0x03);
  EXPECT_EQ(buf.read_uint8(3), 0x04);
  EXPECT_EQ(buf.read_uint8(4), 0x05);
}

TEST_F(DataBufTest_26, DataConstructor_ZeroSize_CreatesEmptyBuffer_26) {
  const byte data[] = {0x01};
  DataBuf buf(data, 0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// alloc / resize / reset Tests
// ============================================================

TEST_F(DataBufTest_26, Alloc_SetsBufferSize_26) {
  DataBuf buf;
  buf.alloc(50);
  EXPECT_EQ(buf.size(), 50u);
  EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_26, Alloc_ZeroSize_MakesEmpty_26) {
  DataBuf buf(10);
  buf.alloc(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_26, Resize_IncreasesSize_26) {
  DataBuf buf(10);
  buf.resize(20);
  EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_26, Resize_DecreasesSize_26) {
  DataBuf buf(20);
  buf.write_uint8(0, 0xAB);
  buf.resize(5);
  EXPECT_EQ(buf.size(), 5u);
  // Data at offset 0 should still be preserved
  EXPECT_EQ(buf.read_uint8(0), 0xAB);
}

TEST_F(DataBufTest_26, Resize_ToZero_26) {
  DataBuf buf(10);
  buf.resize(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_26, Reset_ClearsBuffer_26) {
  DataBuf buf(50);
  buf.reset();
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_26, Reset_OnEmptyBuffer_26) {
  DataBuf buf;
  buf.reset();
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// read/write uint8 Tests
// ============================================================

TEST_F(DataBufTest_26, ReadWriteUint8_BasicRoundTrip_26) {
  DataBuf buf(10);
  buf.write_uint8(0, 0x00);
  buf.write_uint8(1, 0xFF);
  buf.write_uint8(9, 0x42);
  EXPECT_EQ(buf.read_uint8(0), 0x00);
  EXPECT_EQ(buf.read_uint8(1), 0xFF);
  EXPECT_EQ(buf.read_uint8(9), 0x42);
}

TEST_F(DataBufTest_26, ReadWriteUint8_AllByteValues_26) {
  DataBuf buf(256);
  for (int i = 0; i < 256; ++i) {
    buf.write_uint8(static_cast<size_t>(i), static_cast<uint8_t>(i));
  }
  for (int i = 0; i < 256; ++i) {
    EXPECT_EQ(buf.read_uint8(static_cast<size_t>(i)), static_cast<uint8_t>(i));
  }
}

// ============================================================
// read/write uint16 Tests
// ============================================================

TEST_F(DataBufTest_26, ReadWriteUint16_LittleEndian_26) {
  DataBuf buf(10);
  buf.write_uint16(0, 0x1234, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_26, ReadWriteUint16_BigEndian_26) {
  DataBuf buf(10);
  buf.write_uint16(0, 0x1234, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_26, ReadWriteUint16_ByteOrderMatters_26) {
  DataBuf buf(10);
  buf.write_uint16(0, 0x0102, bigEndian);
  // Reading with opposite byte order should give different result
  uint16_t val_le = buf.read_uint16(0, littleEndian);
  uint16_t val_be = buf.read_uint16(0, bigEndian);
  EXPECT_EQ(val_be, 0x0102);
  EXPECT_EQ(val_le, 0x0201);
}

TEST_F(DataBufTest_26, ReadWriteUint16_MaxValue_26) {
  DataBuf buf(4);
  buf.write_uint16(0, 0xFFFF, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xFFFF);
  buf.write_uint16(2, 0xFFFF, littleEndian);
  EXPECT_EQ(buf.read_uint16(2, littleEndian), 0xFFFF);
}

TEST_F(DataBufTest_26, ReadWriteUint16_ZeroValue_26) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x0000, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x0000);
}

TEST_F(DataBufTest_26, ReadWriteUint16_AtOffset_26) {
  DataBuf buf(10);
  buf.write_uint16(4, 0xABCD, bigEndian);
  EXPECT_EQ(buf.read_uint16(4, bigEndian), 0xABCD);
}

// ============================================================
// read/write uint32 Tests
// ============================================================

TEST_F(DataBufTest_26, ReadWriteUint32_LittleEndian_26) {
  DataBuf buf(10);
  buf.write_uint32(0, 0x12345678, littleEndian);
  EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST_F(DataBufTest_26, ReadWriteUint32_BigEndian_26) {
  DataBuf buf(10);
  buf.write_uint32(0, 0x12345678, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_26, ReadWriteUint32_ByteOrderMatters_26) {
  DataBuf buf(10);
  buf.write_uint32(0, 0x01020304, bigEndian);
  uint32_t val_le = buf.read_uint32(0, littleEndian);
  uint32_t val_be = buf.read_uint32(0, bigEndian);
  EXPECT_EQ(val_be, 0x01020304u);
  EXPECT_EQ(val_le, 0x04030201u);
}

TEST_F(DataBufTest_26, ReadWriteUint32_MaxValue_26) {
  DataBuf buf(8);
  buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

TEST_F(DataBufTest_26, ReadWriteUint32_AtOffset_26) {
  DataBuf buf(20);
  buf.write_uint32(8, 0xDEADBEEF, littleEndian);
  EXPECT_EQ(buf.read_uint32(8, littleEndian), 0xDEADBEEFu);
}

// ============================================================
// read/write uint64 Tests
// ============================================================

TEST_F(DataBufTest_26, ReadWriteUint64_LittleEndian_26) {
  DataBuf buf(16);
  buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
  EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_26, ReadWriteUint64_BigEndian_26) {
  DataBuf buf(16);
  buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_26, ReadWriteUint64_ByteOrderMatters_26) {
  DataBuf buf(16);
  buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
  uint64_t val_be = buf.read_uint64(0, bigEndian);
  uint64_t val_le = buf.read_uint64(0, littleEndian);
  EXPECT_EQ(val_be, 0x0102030405060708ULL);
  EXPECT_EQ(val_le, 0x0807060504030201ULL);
}

TEST_F(DataBufTest_26, ReadWriteUint64_MaxValue_26) {
  DataBuf buf(8);
  buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFULL);
}

// ============================================================
// cmpBytes Tests
// ============================================================

TEST_F(DataBufTest_26, CmpBytes_EqualData_ReturnsZero_26) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_26, CmpBytes_DifferentData_ReturnsNonZero_26) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte cmp[] = {0x01, 0x02, 0x04, 0x04};
  EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_26, CmpBytes_AtOffset_26) {
  const byte data[] = {0x00, 0x00, 0x01, 0x02, 0x03};
  DataBuf buf(data, 5);
  const byte cmp[] = {0x01, 0x02, 0x03};
  EXPECT_EQ(buf.cmpBytes(2, cmp, 3), 0);
}

TEST_F(DataBufTest_26, CmpBytes_PartialMatch_26) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte cmp[] = {0x01, 0x02};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

TEST_F(DataBufTest_26, CmpBytes_ZeroSize_26) {
  const byte data[] = {0x01, 0x02};
  DataBuf buf(data, 2);
  const byte cmp[] = {0xFF};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}

// ============================================================
// data / c_data / c_str Tests
// ============================================================

TEST_F(DataBufTest_26, Data_ReturnsPointerToMutableData_26) {
  DataBuf buf(10);
  buf.write_uint8(0, 0xAA);
  byte* ptr = buf.data(0);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 0xAA);
  // Modify through pointer
  *ptr = 0xBB;
  EXPECT_EQ(buf.read_uint8(0), 0xBB);
}

TEST_F(DataBufTest_26, Data_AtOffset_26) {
  DataBuf buf(10);
  buf.write_uint8(5, 0x42);
  byte* ptr = buf.data(5);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 0x42);
}

TEST_F(DataBufTest_26, CData_ReturnsConstPointer_26) {
  const byte data[] = {0x10, 0x20, 0x30};
  DataBuf buf(data, 3);
  const byte* ptr = buf.c_data(0);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 0x10);
  EXPECT_EQ(ptr[1], 0x20);
  EXPECT_EQ(ptr[2], 0x30);
}

TEST_F(DataBufTest_26, CData_AtOffset_26) {
  const byte data[] = {0x10, 0x20, 0x30};
  DataBuf buf(data, 3);
  const byte* ptr = buf.c_data(1);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 0x20);
}

TEST_F(DataBufTest_26, CStr_ReturnsConstCharPointer_26) {
  const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
  DataBuf buf(data, 6);
  const char* str = buf.c_str(0);
  ASSERT_NE(str, nullptr);
  EXPECT_STREQ(str, "Hello");
}

TEST_F(DataBufTest_26, CStr_AtOffset_26) {
  const byte data[] = {0x00, 'H', 'i', '\0'};
  DataBuf buf(data, 4);
  const char* str = buf.c_str(1);
  ASSERT_NE(str, nullptr);
  EXPECT_STREQ(str, "Hi");
}

// ============================================================
// size / empty Tests
// ============================================================

TEST_F(DataBufTest_26, Size_ReturnsCorrectSize_26) {
  DataBuf buf(42);
  EXPECT_EQ(buf.size(), 42u);
}

TEST_F(DataBufTest_26, Empty_TrueForDefaultConstructed_26) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_26, Empty_FalseForNonEmptyBuffer_26) {
  DataBuf buf(1);
  EXPECT_FALSE(buf.empty());
}

// ============================================================
// begin / end Iterator Tests
// ============================================================

TEST_F(DataBufTest_26, BeginEnd_IterableRange_26) {
  const byte data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, 3);
  std::vector<byte> result(buf.begin(), buf.end());
  ASSERT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0], 0x01);
  EXPECT_EQ(result[1], 0x02);
  EXPECT_EQ(result[2], 0x03);
}

TEST_F(DataBufTest_26, BeginEnd_EmptyBuffer_26) {
  DataBuf buf;
  EXPECT_EQ(buf.begin(), buf.end());
}

TEST_F(DataBufTest_26, BeginEnd_DistanceEqualsSize_26) {
  DataBuf buf(15);
  auto dist = std::distance(buf.begin(), buf.end());
  EXPECT_EQ(static_cast<size_t>(dist), buf.size());
}

// ============================================================
// Copy / Move Semantics Tests
// ============================================================

TEST_F(DataBufTest_26, MoveConstructor_TransfersOwnership_26) {
  const byte data[] = {0xAA, 0xBB, 0xCC};
  DataBuf buf1(data, 3);
  DataBuf buf2(std::move(buf1));
  EXPECT_EQ(buf2.size(), 3u);
  EXPECT_EQ(buf2.read_uint8(0), 0xAA);
  EXPECT_EQ(buf2.read_uint8(1), 0xBB);
  EXPECT_EQ(buf2.read_uint8(2), 0xCC);
}

TEST_F(DataBufTest_26, MoveAssignment_TransfersOwnership_26) {
  const byte data[] = {0x11, 0x22};
  DataBuf buf1(data, 2);
  DataBuf buf2;
  buf2 = std::move(buf1);
  EXPECT_EQ(buf2.size(), 2u);
  EXPECT_EQ(buf2.read_uint8(0), 0x11);
  EXPECT_EQ(buf2.read_uint8(1), 0x22);
}

// ============================================================
// Mixed Operations Tests
// ============================================================

TEST_F(DataBufTest_26, AllocThenWrite_26) {
  DataBuf buf;
  buf.alloc(8);
  buf.write_uint32(0, 0xDEADBEEF, bigEndian);
  buf.write_uint32(4, 0xCAFEBABE, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xDEADBEEFu);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xCAFEBABEu);
}

TEST_F(DataBufTest_26, ResizePreservesExistingData_26) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x12345678, bigEndian);
  buf.resize(8);
  EXPECT_EQ(buf.size(), 8u);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_26, ResetThenAlloc_26) {
  DataBuf buf(10);
  buf.write_uint8(0, 0xFF);
  buf.reset();
  EXPECT_TRUE(buf.empty());
  buf.alloc(5);
  EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_26, WriteUint16ThenReadIndividualBytes_26) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x0102, bigEndian);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(1), 0x02);

  buf.write_uint16(2, 0x0102, littleEndian);
  EXPECT_EQ(buf.read_uint8(2), 0x02);
  EXPECT_EQ(buf.read_uint8(3), 0x01);
}

TEST_F(DataBufTest_26, WriteUint32ThenReadIndividualBytes_26) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x01020304, bigEndian);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(1), 0x02);
  EXPECT_EQ(buf.read_uint8(2), 0x03);
  EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST_F(DataBufTest_26, WriteUint64ThenReadSubParts_26) {
  DataBuf buf(8);
  buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x01020304u);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x05060708u);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x0102);
  EXPECT_EQ(buf.read_uint16(6, bigEndian), 0x0708);
}

// ============================================================
// Boundary: Large Buffer
// ============================================================

TEST_F(DataBufTest_26, LargeBuffer_AllocAndAccess_26) {
  const size_t largeSize = 1024 * 1024;  // 1 MB
  DataBuf buf(largeSize);
  EXPECT_EQ(buf.size(), largeSize);
  buf.write_uint8(0, 0x01);
  buf.write_uint8(largeSize - 1, 0xFF);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(largeSize - 1), 0xFF);
}

// ============================================================
// Edge case: Single byte buffer
// ============================================================

TEST_F(DataBufTest_26, SingleByteBuffer_26) {
  DataBuf buf(1);
  buf.write_uint8(0, 0x42);
  EXPECT_EQ(buf.size(), 1u);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.read_uint8(0), 0x42);
}

// ============================================================
// Overwrite Tests
// ============================================================

TEST_F(DataBufTest_26, OverwriteExistingData_26) {
  DataBuf buf(4);
  buf.write_uint32(0, 0xAAAAAAAA, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xAAAAAAAAu);
  buf.write_uint32(0, 0xBBBBBBBB, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xBBBBBBBBu);
}

// ============================================================
// cmpBytes with buffer data written via write functions
// ============================================================

TEST_F(DataBufTest_26, CmpBytes_AfterWrite_26) {
  DataBuf buf(4);
  buf.write_uint32(0, 0x01020304, bigEndian);
  const byte expected[] = {0x01, 0x02, 0x03, 0x04};
  EXPECT_EQ(buf.cmpBytes(0, expected, 4), 0);
}

// ============================================================
// Data pointer arithmetic consistency
// ============================================================

TEST_F(DataBufTest_26, DataPointerConsistency_26) {
  const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
  DataBuf buf(data, 5);
  
  byte* p0 = buf.data(0);
  byte* p2 = buf.data(2);
  EXPECT_EQ(p2 - p0, 2);
  EXPECT_EQ(*p2, 0x30);
}

TEST_F(DataBufTest_26, CDataPointerConsistency_26) {
  const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
  DataBuf buf(data, 5);
  
  const byte* p0 = buf.c_data(0);
  const byte* p3 = buf.c_data(3);
  EXPECT_EQ(p3 - p0, 3);
  EXPECT_EQ(*p3, 0x40);
}
