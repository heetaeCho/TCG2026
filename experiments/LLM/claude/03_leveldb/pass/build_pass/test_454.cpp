#include "gtest/gtest.h"
#include "util/crc32c.h"
#include <string>
#include <cstring>

namespace leveldb {
namespace crc32c {

// Test normal CRC32C computation on a known string
TEST(CRC32CTest_454, ValueOfEmptyData_454) {
  // CRC32C of empty data should be 0
  uint32_t crc = Value("", 0);
  EXPECT_EQ(crc, 0u);
}

TEST(CRC32CTest_454, ValueOfKnownString_454) {
  // Compute CRC of a known string and verify it's deterministic
  const char* data = "hello";
  uint32_t crc1 = Value(data, 5);
  uint32_t crc2 = Value(data, 5);
  EXPECT_EQ(crc1, crc2);
}

TEST(CRC32CTest_454, ValueOfSingleByte_454) {
  const char data = 'a';
  uint32_t crc = Value(&data, 1);
  // Just verify it produces a non-trivial result
  EXPECT_NE(crc, 0u);
}

TEST(CRC32CTest_454, DifferentDataProducesDifferentCRC_454) {
  uint32_t crc1 = Value("abc", 3);
  uint32_t crc2 = Value("def", 3);
  EXPECT_NE(crc1, crc2);
}

TEST(CRC32CTest_454, ExtendFromZeroEqualsValue_454) {
  // Extend with initial CRC of 0 should produce the same result as Value
  const char* data = "hello world";
  size_t len = strlen(data);
  uint32_t crc_value = Value(data, len);
  uint32_t crc_extend = Extend(0, data, len);
  EXPECT_EQ(crc_value, crc_extend);
}

TEST(CRC32CTest_454, ExtendIsIncremental_454) {
  // CRC computed in one shot should equal CRC computed incrementally
  const char* data = "hello world";
  size_t total_len = strlen(data);
  
  uint32_t crc_full = Value(data, total_len);
  
  // Compute in two parts
  uint32_t crc_partial = Value(data, 5);           // "hello"
  uint32_t crc_incremental = Extend(crc_partial, data + 5, total_len - 5); // " world"
  
  EXPECT_EQ(crc_full, crc_incremental);
}

TEST(CRC32CTest_454, ExtendEmptyDoesNotChangeCRC_454) {
  uint32_t crc = Value("test", 4);
  uint32_t crc_extended = Extend(crc, "", 0);
  EXPECT_EQ(crc, crc_extended);
}

TEST(CRC32CTest_454, MaskAndUnmask_454) {
  uint32_t crc = Value("foo", 3);
  uint32_t masked = Mask(crc);
  // Masked value should be different from original (unless extremely unlikely collision)
  EXPECT_NE(crc, masked);
  // Unmasking should recover the original
  uint32_t unmasked = Unmask(masked);
  EXPECT_EQ(crc, unmasked);
}

TEST(CRC32CTest_454, MaskIsNotIdentity_454) {
  uint32_t crc = Value("bar", 3);
  EXPECT_NE(crc, Mask(crc));
}

TEST(CRC32CTest_454, DoubleMaskIsNotSingleMask_454) {
  uint32_t crc = Value("baz", 3);
  uint32_t masked_once = Mask(crc);
  uint32_t masked_twice = Mask(masked_once);
  EXPECT_NE(masked_once, masked_twice);
}

TEST(CRC32CTest_454, UnmaskOfDoubleMaskRecoversSingleMask_454) {
  uint32_t crc = Value("test", 4);
  uint32_t masked = Mask(crc);
  uint32_t double_masked = Mask(masked);
  uint32_t unmasked_once = Unmask(double_masked);
  EXPECT_EQ(masked, unmasked_once);
  uint32_t unmasked_twice = Unmask(unmasked_once);
  EXPECT_EQ(crc, unmasked_twice);
}

TEST(CRC32CTest_454, MaskOfZero_454) {
  uint32_t masked = Mask(0);
  uint32_t unmasked = Unmask(masked);
  EXPECT_EQ(0u, unmasked);
}

TEST(CRC32CTest_454, MaskOfMaxUint32_454) {
  uint32_t val = 0xFFFFFFFF;
  uint32_t masked = Mask(val);
  uint32_t unmasked = Unmask(masked);
  EXPECT_EQ(val, unmasked);
}

TEST(CRC32CTest_454, LargeDataCRC_454) {
  // Test with a larger buffer
  std::string large_data(10000, 'x');
  uint32_t crc = Value(large_data.data(), large_data.size());
  // Should be deterministic
  uint32_t crc2 = Value(large_data.data(), large_data.size());
  EXPECT_EQ(crc, crc2);
  EXPECT_NE(crc, 0u);
}

TEST(CRC32CTest_454, IncrementalMultipleExtends_454) {
  const char* data = "abcdefghijklmnop";
  size_t total_len = strlen(data);
  
  uint32_t crc_full = Value(data, total_len);
  
  // Build up incrementally one byte at a time
  uint32_t crc_inc = 0;
  for (size_t i = 0; i < total_len; i++) {
    crc_inc = Extend(crc_inc, data + i, 1);
  }
  
  EXPECT_EQ(crc_full, crc_inc);
}

TEST(CRC32CTest_454, SubstringProducesDifferentCRC_454) {
  uint32_t crc1 = Value("hello", 5);
  uint32_t crc2 = Value("hello", 4);  // "hell"
  EXPECT_NE(crc1, crc2);
}

TEST(CRC32CTest_454, BinaryDataCRC_454) {
  // Test with binary data including null bytes
  const char data[] = {'\0', '\1', '\2', '\3', '\4'};
  uint32_t crc = Value(data, sizeof(data));
  uint32_t crc2 = Value(data, sizeof(data));
  EXPECT_EQ(crc, crc2);
  EXPECT_NE(crc, 0u);
}

}  // namespace crc32c
}  // namespace leveldb
