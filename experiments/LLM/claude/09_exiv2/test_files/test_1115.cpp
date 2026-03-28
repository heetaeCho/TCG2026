#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Default Construction
// ============================================================

TEST(DataBufTest_1115, DefaultConstructorCreatesEmptyBuffer_1115) {
  DataBuf buf;
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// Size Construction
// ============================================================

TEST(DataBufTest_1115, SizeConstructorAllocatesCorrectSize_1115) {
  DataBuf buf(100);
  EXPECT_EQ(buf.size(), 100u);
  EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_1115, SizeConstructorZeroSize_1115) {
  DataBuf buf(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// Data Construction
// ============================================================

TEST(DataBufTest_1115, DataConstructorCopiesData_1115) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  DataBuf buf(data, 5);
  EXPECT_EQ(buf.size(), 5u);
  EXPECT_FALSE(buf.empty());
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(buf.read_uint8(i), data[i]);
  }
}

TEST(DataBufTest_1115, DataConstructorZeroSize_1115) {
  const byte data[] = {0x01};
  DataBuf buf(data, 0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// alloc
// ============================================================

TEST(DataBufTest_1115, AllocResizesBuffer_1115) {
  DataBuf buf;
  buf.alloc(50);
  EXPECT_EQ(buf.size(), 50u);
}

TEST(DataBufTest_1115, AllocToZero_1115) {
  DataBuf buf(100);
  buf.alloc(0);
  EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_1115, AllocFromExistingSize_1115) {
  DataBuf buf(10);
  buf.alloc(20);
  EXPECT_EQ(buf.size(), 20u);
}

// ============================================================
// resize
// ============================================================

TEST(DataBufTest_1115, ResizeIncreasesSize_1115) {
  DataBuf buf(10);
  buf.resize(20);
  EXPECT_EQ(buf.size(), 20u);
}

TEST(DataBufTest_1115, ResizeDecreasesSize_1115) {
  DataBuf buf(20);
  buf.resize(5);
  EXPECT_EQ(buf.size(), 5u);
}

TEST(DataBufTest_1115, ResizeToZero_1115) {
  DataBuf buf(10);
  buf.resize(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// reset
// ============================================================

TEST(DataBufTest_1115, ResetClearsBuffer_1115) {
  DataBuf buf(100);
  buf.reset();
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_1115, ResetOnEmptyBuffer_1115) {
  DataBuf buf;
  buf.reset();
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

// ============================================================
// read_uint8 / write_uint8
// ============================================================

TEST(DataBufTest_1115, WriteAndReadUint8_1115) {
  DataBuf buf(10);
  buf.write_uint8(0, 0xAB);
  buf.write_uint8(9, 0xCD);
  EXPECT_EQ(buf.read_uint8(0), 0xAB);
  EXPECT_EQ(buf.read_uint8(9), 0xCD);
}

TEST(DataBufTest_1115, ReadUint8BoundaryValues_1115) {
  DataBuf buf(1);
  buf.write_uint8(0, 0x00);
  EXPECT_EQ(buf.read_uint8(0), 0x00);
  buf.write_uint8(0, 0xFF);
  EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

// ============================================================
// read_uint16 / write_uint16
// ============================================================

TEST(DataBufTest_1115, WriteAndReadUint16LittleEndian_1115) {
  DataBuf buf(10);
  buf.write_uint16(0, 0x1234, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST(DataBufTest_1115, WriteAndReadUint16BigEndian_1115) {
  DataBuf buf(10);
  buf.write_uint16(0, 0x1234, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST(DataBufTest_1115, WriteUint16BigEndianReadLittleEndian_1115) {
  DataBuf buf(10);
  buf.write_uint16(0, 0x1234, bigEndian);
  // Reading in opposite byte order should give swapped bytes
  uint16_t val = buf.read_uint16(0, littleEndian);
  EXPECT_EQ(val, 0x3412);
}

TEST(DataBufTest_1115, WriteAndReadUint16AtOffset_1115) {
  DataBuf buf(10);
  buf.write_uint16(4, 0xABCD, bigEndian);
  EXPECT_EQ(buf.read_uint16(4, bigEndian), 0xABCD);
}

TEST(DataBufTest_1115, WriteAndReadUint16BoundaryValue_1115) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x0000, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x0000);
  buf.write_uint16(0, 0xFFFF, littleEndian);
  EXPECT_EQ(buf.read_uint16(0, littleEndian), 0xFFFF);
}

// ============================================================
// read_uint32 / write_uint32
// ============================================================

TEST(DataBufTest_1115, WriteAndReadUint32LittleEndian_1115) {
  DataBuf buf(10);
  buf.write_uint32(0, 0x12345678, littleEndian);
  EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST(DataBufTest_1115, WriteAndReadUint32BigEndian_1115) {
  DataBuf buf(10);
  buf.write_uint32(0, 0x12345678, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST(DataBufTest_1115, WriteUint32BigEndianReadLittleEndian_1115) {
  DataBuf buf(10);
  buf.write_uint32(0, 0x12345678, bigEndian);
  uint32_t val = buf.read_uint32(0, littleEndian);
  EXPECT_EQ(val, 0x78563412u);
}

TEST(DataBufTest_1115, WriteAndReadUint32AtOffset_1115) {
  DataBuf buf(20);
  buf.write_uint32(8, 0xDEADBEEF, bigEndian);
  EXPECT_EQ(buf.read_uint32(8, bigEndian), 0xDEADBEEFu);
}

TEST(DataBufTest_1115, WriteAndReadUint32BoundaryValues_1115) {
  DataBuf buf(8);
  buf.write_uint32(0, 0x00000000, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x00000000u);
  buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

// ============================================================
// read_uint64 / write_uint64
// ============================================================

TEST(DataBufTest_1115, WriteAndReadUint64LittleEndian_1115) {
  DataBuf buf(16);
  buf.write_uint64(0, 0x0123456789ABCDEFull, littleEndian);
  EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0123456789ABCDEFull);
}

TEST(DataBufTest_1115, WriteAndReadUint64BigEndian_1115) {
  DataBuf buf(16);
  buf.write_uint64(0, 0x0123456789ABCDEFull, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0123456789ABCDEFull);
}

TEST(DataBufTest_1115, WriteUint64BigEndianReadLittleEndian_1115) {
  DataBuf buf(16);
  buf.write_uint64(0, 0x0123456789ABCDEFull, bigEndian);
  uint64_t val = buf.read_uint64(0, littleEndian);
  EXPECT_EQ(val, 0xEFCDAB8967452301ull);
}

TEST(DataBufTest_1115, WriteAndReadUint64AtOffset_1115) {
  DataBuf buf(20);
  buf.write_uint64(4, 0xFEDCBA9876543210ull, bigEndian);
  EXPECT_EQ(buf.read_uint64(4, bigEndian), 0xFEDCBA9876543210ull);
}

TEST(DataBufTest_1115, WriteAndReadUint64BoundaryValues_1115) {
  DataBuf buf(16);
  buf.write_uint64(0, 0x0000000000000000ull, littleEndian);
  EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0000000000000000ull);
  buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFull, littleEndian);
  EXPECT_EQ(buf.read_uint64(0, littleEndian), 0xFFFFFFFFFFFFFFFFull);
}

// ============================================================
// cmpBytes
// ============================================================

TEST(DataBufTest_1115, CmpBytesEqual_1115) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_1115, CmpBytesNotEqual_1115) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte cmp[] = {0x01, 0x02, 0x05, 0x04};
  EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_1115, CmpBytesAtOffset_1115) {
  const byte data[] = {0x00, 0x00, 0x01, 0x02, 0x03};
  DataBuf buf(data, 5);
  const byte cmp[] = {0x01, 0x02, 0x03};
  EXPECT_EQ(buf.cmpBytes(2, cmp, 3), 0);
}

TEST(DataBufTest_1115, CmpBytesPartialBuffer_1115) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte cmp[] = {0x01, 0x02};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

TEST(DataBufTest_1115, CmpBytesZeroLength_1115) {
  DataBuf buf(10);
  const byte cmp[] = {0x00};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}

// ============================================================
// data / c_data / c_str
// ============================================================

TEST(DataBufTest_1115, DataReturnsNonNullPointer_1115) {
  DataBuf buf(10);
  EXPECT_NE(buf.data(0), nullptr);
}

TEST(DataBufTest_1115, DataAtOffsetReturnsCorrectPointer_1115) {
  DataBuf buf(10);
  buf.write_uint8(5, 0xAA);
  byte* ptr = buf.data(5);
  EXPECT_EQ(*ptr, 0xAA);
}

TEST(DataBufTest_1115, CDataReturnsConstPointer_1115) {
  const byte data[] = {0x41, 0x42, 0x43};
  DataBuf buf(data, 3);
  const byte* ptr = buf.c_data(0);
  EXPECT_EQ(ptr[0], 0x41);
  EXPECT_EQ(ptr[1], 0x42);
  EXPECT_EQ(ptr[2], 0x43);
}

TEST(DataBufTest_1115, CDataAtOffset_1115) {
  const byte data[] = {0x00, 0x01, 0x02, 0x03};
  DataBuf buf(data, 4);
  const byte* ptr = buf.c_data(2);
  EXPECT_EQ(*ptr, 0x02);
}

TEST(DataBufTest_1115, CStrReturnsCharPointer_1115) {
  const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
  DataBuf buf(data, 6);
  const char* str = buf.c_str(0);
  EXPECT_STREQ(str, "Hello");
}

TEST(DataBufTest_1115, CStrAtOffset_1115) {
  const byte data[] = {0x00, 0x00, 'H', 'i', '\0'};
  DataBuf buf(data, 5);
  const char* str = buf.c_str(2);
  EXPECT_STREQ(str, "Hi");
}

// ============================================================
// begin / end iterators
// ============================================================

TEST(DataBufTest_1115, BeginEndIteratorsForNonEmptyBuffer_1115) {
  const byte data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, 3);
  auto it = buf.begin();
  auto endIt = buf.end();
  EXPECT_NE(it, endIt);
  size_t count = 0;
  for (auto i = buf.begin(); i != buf.end(); ++i) {
    ++count;
  }
  EXPECT_EQ(count, 3u);
}

TEST(DataBufTest_1115, BeginEndIteratorsForEmptyBuffer_1115) {
  DataBuf buf;
  EXPECT_EQ(buf.begin(), buf.end());
}

// ============================================================
// size / empty
// ============================================================

TEST(DataBufTest_1115, SizeReturnsCorrectValue_1115) {
  DataBuf buf(42);
  EXPECT_EQ(buf.size(), 42u);
}

TEST(DataBufTest_1115, EmptyReturnsTrueForDefaultConstructed_1115) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_1115, EmptyReturnsFalseForNonEmptyBuffer_1115) {
  DataBuf buf(1);
  EXPECT_FALSE(buf.empty());
}

// ============================================================
// Copy / Move semantics (if applicable)
// ============================================================

TEST(DataBufTest_1115, CopyConstructor_1115) {
  const byte data[] = {0x01, 0x02, 0x03};
  DataBuf original(data, 3);
  DataBuf copy(original);
  EXPECT_EQ(copy.size(), 3u);
  EXPECT_EQ(copy.read_uint8(0), 0x01);
  EXPECT_EQ(copy.read_uint8(1), 0x02);
  EXPECT_EQ(copy.read_uint8(2), 0x03);
}

TEST(DataBufTest_1115, MoveConstructor_1115) {
  const byte data[] = {0xAA, 0xBB};
  DataBuf original(data, 2);
  DataBuf moved(std::move(original));
  EXPECT_EQ(moved.size(), 2u);
  EXPECT_EQ(moved.read_uint8(0), 0xAA);
  EXPECT_EQ(moved.read_uint8(1), 0xBB);
}

TEST(DataBufTest_1115, CopyAssignment_1115) {
  const byte data[] = {0x10, 0x20};
  DataBuf original(data, 2);
  DataBuf copy;
  copy = original;
  EXPECT_EQ(copy.size(), 2u);
  EXPECT_EQ(copy.read_uint8(0), 0x10);
  EXPECT_EQ(copy.read_uint8(1), 0x20);
}

TEST(DataBufTest_1115, MoveAssignment_1115) {
  const byte data[] = {0xCC, 0xDD};
  DataBuf original(data, 2);
  DataBuf moved;
  moved = std::move(original);
  EXPECT_EQ(moved.size(), 2u);
  EXPECT_EQ(moved.read_uint8(0), 0xCC);
  EXPECT_EQ(moved.read_uint8(1), 0xDD);
}

// ============================================================
// Multiple writes and reads
// ============================================================

TEST(DataBufTest_1115, MultipleWritesAndReadsUint32_1115) {
  DataBuf buf(16);
  buf.write_uint32(0, 0x11111111, bigEndian);
  buf.write_uint32(4, 0x22222222, bigEndian);
  buf.write_uint32(8, 0x33333333, bigEndian);
  buf.write_uint32(12, 0x44444444, bigEndian);
  EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x11111111u);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x22222222u);
  EXPECT_EQ(buf.read_uint32(8, bigEndian), 0x33333333u);
  EXPECT_EQ(buf.read_uint32(12, bigEndian), 0x44444444u);
}

// ============================================================
// Write through data() pointer
// ============================================================

TEST(DataBufTest_1115, WriteViaDataPointer_1115) {
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
// Alloc after data written preserves nothing guarantee (just size)
// ============================================================

TEST(DataBufTest_1115, AllocChangesSize_1115) {
  DataBuf buf(5);
  buf.write_uint8(0, 0xFF);
  buf.alloc(10);
  EXPECT_EQ(buf.size(), 10u);
}

// ============================================================
// Resize preserves existing data (typical vector behavior)
// ============================================================

TEST(DataBufTest_1115, ResizePreservesExistingData_1115) {
  const byte data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, 3);
  buf.resize(6);
  EXPECT_EQ(buf.size(), 6u);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(1), 0x02);
  EXPECT_EQ(buf.read_uint8(2), 0x03);
}

// ============================================================
// Out-of-range read (exception behavior)
// ============================================================

TEST(DataBufTest_1115, ReadUint8OutOfRange_1115) {
  DataBuf buf(2);
  EXPECT_THROW(buf.read_uint8(5), std::exception);
}

TEST(DataBufTest_1115, ReadUint16OutOfRange_1115) {
  DataBuf buf(1);
  EXPECT_THROW(buf.read_uint16(0, bigEndian), std::exception);
}

TEST(DataBufTest_1115, ReadUint32OutOfRange_1115) {
  DataBuf buf(2);
  EXPECT_THROW(buf.read_uint32(0, bigEndian), std::exception);
}

TEST(DataBufTest_1115, ReadUint64OutOfRange_1115) {
  DataBuf buf(4);
  EXPECT_THROW(buf.read_uint64(0, bigEndian), std::exception);
}

TEST(DataBufTest_1115, WriteUint8OutOfRange_1115) {
  DataBuf buf(2);
  EXPECT_THROW(buf.write_uint8(5, 0xFF), std::exception);
}

TEST(DataBufTest_1115, WriteUint16OutOfRange_1115) {
  DataBuf buf(1);
  EXPECT_THROW(buf.write_uint16(0, 0xFFFF, bigEndian), std::exception);
}

TEST(DataBufTest_1115, WriteUint32OutOfRange_1115) {
  DataBuf buf(2);
  EXPECT_THROW(buf.write_uint32(0, 0xFFFFFFFF, bigEndian), std::exception);
}

TEST(DataBufTest_1115, WriteUint64OutOfRange_1115) {
  DataBuf buf(4);
  EXPECT_THROW(buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFull, bigEndian), std::exception);
}

// ============================================================
// Edge: exact fit for multi-byte reads/writes
// ============================================================

TEST(DataBufTest_1115, Uint16ExactFit_1115) {
  DataBuf buf(2);
  buf.write_uint16(0, 0xABCD, bigEndian);
  EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xABCD);
}

TEST(DataBufTest_1115, Uint32ExactFit_1115) {
  DataBuf buf(4);
  buf.write_uint32(0, 0xDEADBEEF, littleEndian);
  EXPECT_EQ(buf.read_uint32(0, littleEndian), 0xDEADBEEFu);
}

TEST(DataBufTest_1115, Uint64ExactFit_1115) {
  DataBuf buf(8);
  buf.write_uint64(0, 0x0102030405060708ull, bigEndian);
  EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ull);
}

// ============================================================
// Large buffer
// ============================================================

TEST(DataBufTest_1115, LargeBufferAllocation_1115) {
  DataBuf buf(1000000);
  EXPECT_EQ(buf.size(), 1000000u);
  buf.write_uint8(999999, 0x42);
  EXPECT_EQ(buf.read_uint8(999999), 0x42);
}
