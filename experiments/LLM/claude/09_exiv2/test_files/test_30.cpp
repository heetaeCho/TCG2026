#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <exiv2/slice.hpp>
#include <vector>
#include <cstdint>

namespace {

class GetUShortTest_30 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Normal operation: little endian with typical values
TEST_F(GetUShortTest_30, LittleEndianTypicalValue_30) {
  std::vector<Exiv2::byte> data = {0x01, 0x02};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::littleEndian);
  // little endian: buf[1] << 8 | buf[0] = 0x02 << 8 | 0x01 = 0x0201
  EXPECT_EQ(result, 0x0201);
}

// Normal operation: big endian with typical values
TEST_F(GetUShortTest_30, BigEndianTypicalValue_30) {
  std::vector<Exiv2::byte> data = {0x01, 0x02};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::bigEndian);
  // big endian: buf[0] << 8 | buf[1] = 0x01 << 8 | 0x02 = 0x0102
  EXPECT_EQ(result, 0x0102);
}

// Boundary: both bytes are zero
TEST_F(GetUShortTest_30, AllZerosLittleEndian_30) {
  std::vector<Exiv2::byte> data = {0x00, 0x00};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::littleEndian);
  EXPECT_EQ(result, 0x0000);
}

TEST_F(GetUShortTest_30, AllZerosBigEndian_30) {
  std::vector<Exiv2::byte> data = {0x00, 0x00};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::bigEndian);
  EXPECT_EQ(result, 0x0000);
}

// Boundary: maximum value (0xFFFF)
TEST_F(GetUShortTest_30, MaxValueLittleEndian_30) {
  std::vector<Exiv2::byte> data = {0xFF, 0xFF};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::littleEndian);
  EXPECT_EQ(result, 0xFFFF);
}

TEST_F(GetUShortTest_30, MaxValueBigEndian_30) {
  std::vector<Exiv2::byte> data = {0xFF, 0xFF};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::bigEndian);
  EXPECT_EQ(result, 0xFFFF);
}

// Boundary: only high byte set
TEST_F(GetUShortTest_30, HighByteOnlyLittleEndian_30) {
  std::vector<Exiv2::byte> data = {0x00, 0xFF};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::littleEndian);
  // LE: buf[1]<<8 | buf[0] = 0xFF00
  EXPECT_EQ(result, 0xFF00);
}

TEST_F(GetUShortTest_30, HighByteOnlyBigEndian_30) {
  std::vector<Exiv2::byte> data = {0xFF, 0x00};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::bigEndian);
  // BE: buf[0]<<8 | buf[1] = 0xFF00
  EXPECT_EQ(result, 0xFF00);
}

// Boundary: only low byte set
TEST_F(GetUShortTest_30, LowByteOnlyLittleEndian_30) {
  std::vector<Exiv2::byte> data = {0xFF, 0x00};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::littleEndian);
  // LE: buf[1]<<8 | buf[0] = 0x00FF
  EXPECT_EQ(result, 0x00FF);
}

TEST_F(GetUShortTest_30, LowByteOnlyBigEndian_30) {
  std::vector<Exiv2::byte> data = {0x00, 0xFF};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::bigEndian);
  // BE: buf[0]<<8 | buf[1] = 0x00FF
  EXPECT_EQ(result, 0x00FF);
}

// Verify endianness swap: same data, different byte orders yield swapped results
TEST_F(GetUShortTest_30, EndianSwapConsistency_30) {
  std::vector<Exiv2::byte> data = {0xAB, 0xCD};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t le_result = Exiv2::getUShort(slice, Exiv2::littleEndian);
  uint16_t be_result = Exiv2::getUShort(slice, Exiv2::bigEndian);
  // LE: 0xCDAB, BE: 0xABCD
  EXPECT_EQ(le_result, 0xCDAB);
  EXPECT_EQ(be_result, 0xABCD);
  // They should be byte-swapped versions of each other
  EXPECT_EQ(le_result, static_cast<uint16_t>((be_result >> 8) | (be_result << 8)));
}

// Test with a slice that starts at an offset within a larger buffer
TEST_F(GetUShortTest_30, SliceWithOffsetLittleEndian_30) {
  std::vector<Exiv2::byte> data = {0x00, 0x00, 0x34, 0x12, 0x00};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 2, 4);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::littleEndian);
  // LE: buf[1]<<8 | buf[0] = 0x12 << 8 | 0x34 = 0x1234
  EXPECT_EQ(result, 0x1234);
}

TEST_F(GetUShortTest_30, SliceWithOffsetBigEndian_30) {
  std::vector<Exiv2::byte> data = {0x00, 0x00, 0x12, 0x34, 0x00};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 2, 4);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::bigEndian);
  // BE: buf[0]<<8 | buf[1] = 0x12 << 8 | 0x34 = 0x1234
  EXPECT_EQ(result, 0x1234);
}

// Test with value 1 in different endianness
TEST_F(GetUShortTest_30, ValueOneLittleEndian_30) {
  std::vector<Exiv2::byte> data = {0x01, 0x00};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::littleEndian);
  EXPECT_EQ(result, 1);
}

TEST_F(GetUShortTest_30, ValueOneBigEndian_30) {
  std::vector<Exiv2::byte> data = {0x00, 0x01};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::bigEndian);
  EXPECT_EQ(result, 1);
}

// Test with value 256 in different endianness
TEST_F(GetUShortTest_30, Value256LittleEndian_30) {
  std::vector<Exiv2::byte> data = {0x00, 0x01};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::littleEndian);
  EXPECT_EQ(result, 256);
}

TEST_F(GetUShortTest_30, Value256BigEndian_30) {
  std::vector<Exiv2::byte> data = {0x01, 0x00};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result = Exiv2::getUShort(slice, Exiv2::bigEndian);
  EXPECT_EQ(result, 256);
}

// Test that identical byte patterns with same endianness produce same result (idempotency)
TEST_F(GetUShortTest_30, IdempotentCall_30) {
  std::vector<Exiv2::byte> data = {0x42, 0x24};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 2);
  uint16_t result1 = Exiv2::getUShort(slice, Exiv2::bigEndian);
  uint16_t result2 = Exiv2::getUShort(slice, Exiv2::bigEndian);
  EXPECT_EQ(result1, result2);
}

// Error case: slice too small should throw (if at() checks bounds)
TEST_F(GetUShortTest_30, SliceTooSmallThrows_30) {
  std::vector<Exiv2::byte> data = {0x01};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 1);
  EXPECT_THROW(Exiv2::getUShort(slice, Exiv2::littleEndian), std::out_of_range);
}

TEST_F(GetUShortTest_30, EmptySliceThrows_30) {
  std::vector<Exiv2::byte> data = {};
  auto slice = Exiv2::Slice<std::vector<Exiv2::byte>>(data, 0, 0);
  EXPECT_THROW(Exiv2::getUShort(slice, Exiv2::bigEndian), std::out_of_range);
}

}  // namespace
