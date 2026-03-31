#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace {

using Exiv2::DataBuf;
using Exiv2::byte;
using Exiv2::makeSlice;
using Exiv2::Slice;

// ============================================================
// Tests for makeSlice
// ============================================================

class MakeSliceTest_1132 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(MakeSliceTest_1132, NormalSliceFromDataBuf_1132) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  DataBuf buf(data, 5);
  auto slice = makeSlice(buf, 0, 5);
  EXPECT_EQ(slice.size(), 5u);
  EXPECT_EQ(slice.at(0), 0x01);
  EXPECT_EQ(slice.at(4), 0x05);
}

TEST_F(MakeSliceTest_1132, SubSliceFromDataBuf_1132) {
  const byte data[] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E};
  DataBuf buf(data, 5);
  auto slice = makeSlice(buf, 1, 4);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 0x0B);
  EXPECT_EQ(slice.at(1), 0x0C);
  EXPECT_EQ(slice.at(2), 0x0D);
}

TEST_F(MakeSliceTest_1132, EmptySliceBeginEqualsEnd_1132) {
  const byte data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, 3);
  auto slice = makeSlice(buf, 2, 2);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(MakeSliceTest_1132, SliceFromEmptyBufWithZeroRange_1132) {
  DataBuf buf;
  auto slice = makeSlice(buf, 0, 0);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(MakeSliceTest_1132, SliceEndExceedsBufferSizeThrows_1132) {
  const byte data[] = {0x01, 0x02};
  DataBuf buf(data, 2);
  EXPECT_THROW(makeSlice(buf, 0, 3), std::overflow_error);
}

TEST_F(MakeSliceTest_1132, SliceEndExceedsEmptyBufferThrows_1132) {
  DataBuf buf;
  EXPECT_THROW(makeSlice(buf, 0, 1), std::overflow_error);
}

TEST_F(MakeSliceTest_1132, SliceBeginExceedsEndThrows_1132) {
  const byte data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, 3);
  EXPECT_THROW(makeSlice(buf, 2, 1), std::out_of_range);
}

TEST_F(MakeSliceTest_1132, FullBufferSlice_1132) {
  const byte data[] = {0xFF, 0xFE, 0xFD, 0xFC};
  DataBuf buf(data, 4);
  auto slice = makeSlice(buf, 0, 4);
  EXPECT_EQ(slice.size(), 4u);
  for (size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(slice.at(i), data[i]);
  }
}

TEST_F(MakeSliceTest_1132, SingleByteSlice_1132) {
  const byte data[] = {0x42};
  DataBuf buf(data, 1);
  auto slice = makeSlice(buf, 0, 1);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 0x42);
}

// ============================================================
// Tests for DataBuf
// ============================================================

class DataBufTest_1132 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(DataBufTest_1132, DefaultConstructorCreatesEmptyBuffer_1132) {
  DataBuf buf;
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1132, SizeConstructorAllocatesCorrectSize_1132) {
  DataBuf buf(10);
  EXPECT_EQ(buf.size(), 10u);
  EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1132, DataConstructorCopiesData_1132) {
  const byte data[] = {0x01, 0x02, 0x03};
  DataBuf buf(data, 3);
  EXPECT_EQ(buf.size(), 3u);
  EXPECT_EQ(buf.c_data(0)[0], 0x01);
  EXPECT_EQ(buf.c_data(0)[1], 0x02);
  EXPECT_EQ(buf.c_data(0)[2], 0x03);
}

TEST_F(DataBufTest_1132, AllocChangesSize_1132) {
  DataBuf buf;
  buf.alloc(20);
  EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1132, ResizeChangesSize_1132) {
  DataBuf buf(10);
  buf.resize(5);
  EXPECT_EQ(buf.size(), 5u);
  buf.resize(15);
  EXPECT_EQ(buf.size(), 15u);
}

TEST_F(DataBufTest_1132, ResetClearsBuffer_1132) {
  DataBuf buf(10);
  buf.reset();
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1132, ReadWriteUint8_1132) {
  DataBuf buf(4);
  buf.write_uint8(0, 0xAB);
  buf.write_uint8(3, 0xCD);
  EXPECT_EQ(buf.read_uint8(0), 0xAB);
  EXPECT_EQ(buf.read_uint8(3), 0xCD);
}

TEST_F(DataBufTest_1132, ReadWriteUint16BigEndian_1132) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x1234, Exiv2::bigEndian);
  EXPECT_EQ(buf.read_uint16(0, Exiv2::bigEndian), 0x1234);
}

TEST_F(DataBufTest_1132, ReadWriteUint16LittleEndian_1132) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x1234, Exiv2::littleEndian);
  EXPECT_EQ(buf.read_uint16(0, Exiv2::littleEndian), 0x1234);
}

TEST_F(DataBufTest_1132, ReadWriteUint32BigEndian_1132) {
  DataBuf buf(8);
  buf.write_uint32(0, 0xDEADBEEF, Exiv2::bigEndian);
  EXPECT_EQ(buf.read_uint32(0, Exiv2::bigEndian), 0xDEADBEEF);
}

TEST_F(DataBufTest_1132, ReadWriteUint32LittleEndian_1132) {
  DataBuf buf(8);
  buf.write_uint32(0, 0xDEADBEEF, Exiv2::littleEndian);
  EXPECT_EQ(buf.read_uint32(0, Exiv2::littleEndian), 0xDEADBEEF);
}

TEST_F(DataBufTest_1132, ReadWriteUint64BigEndian_1132) {
  DataBuf buf(16);
  uint64_t val = 0x0102030405060708ULL;
  buf.write_uint64(0, val, Exiv2::bigEndian);
  EXPECT_EQ(buf.read_uint64(0, Exiv2::bigEndian), val);
}

TEST_F(DataBufTest_1132, ReadWriteUint64LittleEndian_1132) {
  DataBuf buf(16);
  uint64_t val = 0x0102030405060708ULL;
  buf.write_uint64(0, val, Exiv2::littleEndian);
  EXPECT_EQ(buf.read_uint64(0, Exiv2::littleEndian), val);
}

TEST_F(DataBufTest_1132, CmpBytesEqual_1132) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
  EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1132, CmpBytesNotEqual_1132) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte cmp[] = {0x01, 0x02, 0xFF, 0x04};
  EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1132, CmpBytesWithOffset_1132) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte cmp[] = {0x02, 0x03};
  EXPECT_EQ(buf.cmpBytes(1, cmp, 2), 0);
}

TEST_F(DataBufTest_1132, DataPointerAccessMutable_1132) {
  DataBuf buf(4);
  byte* ptr = buf.data(0);
  ASSERT_NE(ptr, nullptr);
  ptr[0] = 0x42;
  EXPECT_EQ(buf.read_uint8(0), 0x42);
}

TEST_F(DataBufTest_1132, CDataPointerAccessConst_1132) {
  const byte data[] = {0xAA, 0xBB};
  DataBuf buf(data, 2);
  const byte* ptr = buf.c_data(0);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 0xAA);
  EXPECT_EQ(ptr[1], 0xBB);
}

TEST_F(DataBufTest_1132, CStrAccess_1132) {
  const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
  DataBuf buf(data, 6);
  const char* str = buf.c_str(0);
  EXPECT_STREQ(str, "Hello");
}

TEST_F(DataBufTest_1132, DataWithOffset_1132) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  const byte* ptr = buf.c_data(2);
  EXPECT_EQ(*ptr, 0x03);
}

TEST_F(DataBufTest_1132, EmptyOnNonEmptyBuffer_1132) {
  DataBuf buf(1);
  EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1132, SizeZeroConstructor_1132) {
  DataBuf buf(0);
  EXPECT_EQ(buf.size(), 0u);
  EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1132, WriteUint16AtOffset_1132) {
  DataBuf buf(8);
  buf.write_uint16(4, 0xABCD, Exiv2::bigEndian);
  EXPECT_EQ(buf.read_uint16(4, Exiv2::bigEndian), 0xABCD);
}

TEST_F(DataBufTest_1132, WriteUint32AtOffset_1132) {
  DataBuf buf(12);
  buf.write_uint32(4, 0x12345678, Exiv2::littleEndian);
  EXPECT_EQ(buf.read_uint32(4, Exiv2::littleEndian), 0x12345678u);
}

TEST_F(DataBufTest_1132, WriteUint64AtOffset_1132) {
  DataBuf buf(16);
  uint64_t val = 0xAABBCCDDEEFF0011ULL;
  buf.write_uint64(8, val, Exiv2::bigEndian);
  EXPECT_EQ(buf.read_uint64(8, Exiv2::bigEndian), val);
}

TEST_F(DataBufTest_1132, EndiannessMismatchGivesDifferentResult_1132) {
  DataBuf buf(4);
  buf.write_uint16(0, 0x0102, Exiv2::bigEndian);
  // Reading with opposite endianness should give a different value (unless symmetric)
  uint16_t le_val = buf.read_uint16(0, Exiv2::littleEndian);
  // 0x0102 in big endian is bytes [0x01, 0x02], reading as little endian gives 0x0201
  EXPECT_EQ(le_val, 0x0201);
}

TEST_F(DataBufTest_1132, AllocZeroMakesEmpty_1132) {
  DataBuf buf(10);
  buf.alloc(0);
  EXPECT_EQ(buf.size(), 0u);
}

TEST_F(DataBufTest_1132, ResizeToZeroMakesEmpty_1132) {
  DataBuf buf(10);
  buf.resize(0);
  EXPECT_EQ(buf.size(), 0u);
}

TEST_F(DataBufTest_1132, ResizePreservesExistingData_1132) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  buf.resize(8);
  EXPECT_EQ(buf.size(), 8u);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(1), 0x02);
  EXPECT_EQ(buf.read_uint8(2), 0x03);
  EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST_F(DataBufTest_1132, LargeBuffer_1132) {
  DataBuf buf(10000);
  EXPECT_EQ(buf.size(), 10000u);
  buf.write_uint8(9999, 0xFF);
  EXPECT_EQ(buf.read_uint8(9999), 0xFF);
}

}  // namespace
