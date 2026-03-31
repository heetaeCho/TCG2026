#include "util/crc32c.h"
#include <gtest/gtest.h>
#include <cstdint>

namespace leveldb {
namespace crc32c {

// We need access to Extend and Value functions as well as Mask
// Based on the header, we know about Unmask and kMaskDelta
// Let's also include the full header which likely has Mask, Extend, Value

// Forward declarations for functions likely in crc32c.h but not shown in partial code
extern uint32_t Extend(uint32_t crc, const char* data, size_t n);
extern uint32_t Value(const char* data, size_t n);
extern uint32_t Mask(uint32_t crc);

TEST(CRC32CTest_322, UnmaskBasicZero_322) {
  // Unmasking a masked zero should give back zero
  // Mask(0) would produce some value, and Unmask of that should return 0
  uint32_t masked = Mask(0);
  EXPECT_EQ(0u, Unmask(masked));
}

TEST(CRC32CTest_322, UnmaskRoundTrip_322) {
  // For any CRC value, Unmask(Mask(crc)) == crc
  uint32_t test_values[] = {0, 1, 0xFFFFFFFF, 0x80000000, 0x12345678, 42, 0xDEADBEEF};
  for (uint32_t val : test_values) {
    uint32_t masked = Mask(val);
    EXPECT_EQ(val, Unmask(masked));
  }
}

TEST(CRC32CTest_322, MaskChangesValue_322) {
  // Mask should change the CRC value (it shouldn't be identity for typical values)
  uint32_t crc = 0x12345678;
  uint32_t masked = Mask(crc);
  EXPECT_NE(crc, masked);
}

TEST(CRC32CTest_322, MaskIsNotIdentityForZero_322) {
  // Mask(0) should not be 0
  uint32_t masked = Mask(0);
  EXPECT_NE(0u, masked);
}

TEST(CRC32CTest_322, DoubleMaskIsNotSameAsSingleMask_322) {
  // Masking twice should give a different result than masking once
  uint32_t crc = 100;
  uint32_t masked_once = Mask(crc);
  uint32_t masked_twice = Mask(masked_once);
  EXPECT_NE(masked_once, masked_twice);
}

TEST(CRC32CTest_322, DoubleUnmaskRecoversDoubleMask_322) {
  uint32_t crc = 0xABCDEF01;
  uint32_t masked_twice = Mask(Mask(crc));
  uint32_t recovered = Unmask(Unmask(masked_twice));
  EXPECT_EQ(crc, recovered);
}

TEST(CRC32CTest_322, ValueEmptyString_322) {
  // CRC of empty data
  uint32_t crc = Value("", 0);
  // Just verify it returns a deterministic value
  EXPECT_EQ(crc, Value("", 0));
}

TEST(CRC32CTest_322, ValueNonEmpty_322) {
  const char* data = "hello";
  uint32_t crc = Value(data, 5);
  // Verify determinism
  EXPECT_EQ(crc, Value(data, 5));
}

TEST(CRC32CTest_322, ValueDifferentDataDifferentCRC_322) {
  uint32_t crc1 = Value("hello", 5);
  uint32_t crc2 = Value("world", 5);
  EXPECT_NE(crc1, crc2);
}

TEST(CRC32CTest_322, ExtendFromZero_322) {
  // Extend from 0 should be the same as Value
  const char* data = "test data";
  size_t len = 9;
  uint32_t crc_value = Value(data, len);
  uint32_t crc_extend = Extend(0, data, len);
  EXPECT_EQ(crc_value, crc_extend);
}

TEST(CRC32CTest_322, ExtendIncrementally_322) {
  // CRC computed incrementally should match CRC computed all at once
  const char* data = "hello world";
  uint32_t full_crc = Value(data, 11);
  
  uint32_t partial_crc = Extend(0, data, 5);       // "hello"
  partial_crc = Extend(partial_crc, data + 5, 6);   // " world"
  
  EXPECT_EQ(full_crc, partial_crc);
}

TEST(CRC32CTest_322, ExtendEmptyData_322) {
  // Extending with empty data should not change CRC
  uint32_t initial_crc = Value("abc", 3);
  uint32_t extended_crc = Extend(initial_crc, "", 0);
  EXPECT_EQ(initial_crc, extended_crc);
}

TEST(CRC32CTest_322, UnmaskWithMaxUint32_322) {
  // Test Unmask with edge value 0xFFFFFFFF
  uint32_t result = Unmask(0xFFFFFFFF);
  // Just ensure it doesn't crash and returns deterministic value
  EXPECT_EQ(result, Unmask(0xFFFFFFFF));
}

TEST(CRC32CTest_322, MaskUnmaskAllOnes_322) {
  uint32_t crc = 0xFFFFFFFF;
  EXPECT_EQ(crc, Unmask(Mask(crc)));
}

TEST(CRC32CTest_322, KnownCRC32CValues_322) {
  // CRC32C of known test vectors
  // CRC32C("") = 0
  // But the actual initial value might differ based on implementation
  // Just test consistency
  uint32_t empty_crc = Value("", 0);
  EXPECT_EQ(empty_crc, Value("", 0));
}

TEST(CRC32CTest_322, SingleByteValues_322) {
  // Different single bytes should produce different CRCs
  char a = 'a';
  char b = 'b';
  uint32_t crc_a = Value(&a, 1);
  uint32_t crc_b = Value(&b, 1);
  EXPECT_NE(crc_a, crc_b);
}

TEST(CRC32CTest_322, ExtendMultipleChunks_322) {
  // Test extending with multiple chunks matches full computation
  const char* data = "The quick brown fox jumps over the lazy dog";
  size_t total_len = strlen(data);
  
  uint32_t full_crc = Value(data, total_len);
  
  uint32_t chunk_crc = 0;
  size_t chunk_size = 7;
  for (size_t i = 0; i < total_len; i += chunk_size) {
    size_t len = std::min(chunk_size, total_len - i);
    chunk_crc = Extend(chunk_crc, data + i, len);
  }
  
  EXPECT_EQ(full_crc, chunk_crc);
}

TEST(CRC32CTest_322, MaskDeltaConstant_322) {
  // Verify the known constant
  EXPECT_EQ(2726488792UL, kMaskDelta);
}

}  // namespace crc32c
}  // namespace leveldb
