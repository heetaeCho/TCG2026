#include "util/crc32c.h"

#include <cstring>
#include <string>

#include "gtest/gtest.h"

namespace leveldb {
namespace crc32c {

// Test that Value on empty data returns a consistent result (likely 0 or some fixed value)
TEST(CRC32CTest_320, EmptyDataReturnsConsistentValue_320) {
  uint32_t crc = Value("", 0);
  // Calling again with the same input should return the same result
  uint32_t crc2 = Value("", 0);
  EXPECT_EQ(crc, crc2);
}

// Test that Value on empty data equals Extend(0, data, 0)
TEST(CRC32CTest_320, ValueEqualsExtendWithZeroInit_320) {
  const char* data = "hello";
  size_t n = 5;
  uint32_t from_value = Value(data, n);
  uint32_t from_extend = Extend(0, data, n);
  EXPECT_EQ(from_value, from_extend);
}

// Test that CRC of known data produces a non-zero value
TEST(CRC32CTest_320, NonEmptyDataProducesNonZeroCRC_320) {
  const char* data = "hello world";
  uint32_t crc = Value(data, strlen(data));
  // It's extremely unlikely that a non-empty string has CRC32C of 0
  // but this is a sanity check
  EXPECT_NE(crc, 0u);
}

// Test that different data produces different CRCs
TEST(CRC32CTest_320, DifferentDataProducesDifferentCRCs_320) {
  uint32_t crc1 = Value("hello", 5);
  uint32_t crc2 = Value("world", 5);
  EXPECT_NE(crc1, crc2);
}

// Test that the same data always produces the same CRC (determinism)
TEST(CRC32CTest_320, SameDataProducesSameCRC_320) {
  const char* data = "test data for crc";
  size_t n = strlen(data);
  uint32_t crc1 = Value(data, n);
  uint32_t crc2 = Value(data, n);
  EXPECT_EQ(crc1, crc2);
}

// Test that Extend can be used to compute CRC incrementally
TEST(CRC32CTest_320, ExtendIsIncremental_320) {
  const char* data = "hello world";
  size_t len = strlen(data);

  // Compute CRC of entire string at once
  uint32_t full_crc = Value(data, len);

  // Compute CRC incrementally: first "hello " then "world"
  uint32_t partial_crc = Extend(0, data, 6);
  uint32_t incremental_crc = Extend(partial_crc, data + 6, len - 6);

  EXPECT_EQ(full_crc, incremental_crc);
}

// Test single byte CRC
TEST(CRC32CTest_320, SingleByteCRC_320) {
  uint32_t crc_a = Value("a", 1);
  uint32_t crc_b = Value("b", 1);
  EXPECT_NE(crc_a, crc_b);
  // Ensure they are consistent
  EXPECT_EQ(crc_a, Value("a", 1));
  EXPECT_EQ(crc_b, Value("b", 1));
}

// Test that computing CRC with length 0 on non-null pointer gives same result as empty
TEST(CRC32CTest_320, ZeroLengthOnNonNullPointer_320) {
  const char* data = "some data";
  uint32_t crc = Value(data, 0);
  uint32_t crc_empty = Value("", 0);
  EXPECT_EQ(crc, crc_empty);
}

// Test Extend with initial value of 0 and zero length
TEST(CRC32CTest_320, ExtendZeroInitZeroLength_320) {
  uint32_t crc = Extend(0, "", 0);
  // Should be the identity (initial CRC)
  EXPECT_EQ(crc, Value("", 0));
}

// Test CRC on larger data
TEST(CRC32CTest_320, LargerDataCRC_320) {
  std::string large_data(4096, 'x');
  uint32_t crc1 = Value(large_data.data(), large_data.size());
  uint32_t crc2 = Value(large_data.data(), large_data.size());
  EXPECT_EQ(crc1, crc2);

  // Different large data should produce different CRC
  std::string large_data2(4096, 'y');
  uint32_t crc3 = Value(large_data2.data(), large_data2.size());
  EXPECT_NE(crc1, crc3);
}

// Test that a prefix of a string has a different CRC than the whole string
TEST(CRC32CTest_320, PrefixDiffersFromFull_320) {
  const char* data = "hello world";
  uint32_t crc_prefix = Value(data, 5);
  uint32_t crc_full = Value(data, strlen(data));
  EXPECT_NE(crc_prefix, crc_full);
}

// Test Extend with a non-zero initial CRC value
TEST(CRC32CTest_320, ExtendWithNonZeroInitialCRC_320) {
  uint32_t init_crc = Value("hello", 5);
  uint32_t extended = Extend(init_crc, " world", 6);
  uint32_t full = Value("hello world", 11);
  EXPECT_EQ(extended, full);
}

// Test that all-zero data has a valid CRC
TEST(CRC32CTest_320, AllZeroData_320) {
  char zeros[256];
  memset(zeros, 0, sizeof(zeros));
  uint32_t crc = Value(zeros, sizeof(zeros));
  // Just ensure determinism
  EXPECT_EQ(crc, Value(zeros, sizeof(zeros)));
}

// Test all byte values (0x00 through 0xFF) - each single byte should produce unique CRC
TEST(CRC32CTest_320, SingleByteUniqueness_320) {
  // While not guaranteed in general, for CRC32C single bytes should all be unique
  std::set<uint32_t> crcs;
  // Use a simpler check: just verify a few distinct bytes give distinct CRCs
  char b1 = 0x00;
  char b2 = 0x01;
  char b3 = static_cast<char>(0xFF);
  uint32_t c1 = Value(&b1, 1);
  uint32_t c2 = Value(&b2, 1);
  uint32_t c3 = Value(&b3, 1);
  EXPECT_NE(c1, c2);
  EXPECT_NE(c1, c3);
  EXPECT_NE(c2, c3);
}

}  // namespace crc32c
}  // namespace leveldb
