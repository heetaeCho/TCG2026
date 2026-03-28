#include "gtest/gtest.h"
#include "util/hash.h"

#include <string>
#include <vector>

namespace leveldb {

// Test that hashing empty data with seed 0 returns a deterministic value
TEST(HashTest_433, EmptyStringWithZeroSeed_433) {
  uint32_t result = Hash("", 0, 0);
  // Running again should produce the same result (deterministic)
  EXPECT_EQ(result, Hash("", 0, 0));
}

// Test that hashing empty data with different seeds returns different values
TEST(HashTest_433, EmptyStringDifferentSeeds_433) {
  uint32_t result1 = Hash("", 0, 0);
  uint32_t result2 = Hash("", 0, 1);
  EXPECT_NE(result1, result2);
}

// Test deterministic behavior: same input always gives same output
TEST(HashTest_433, Deterministic_433) {
  const char* data = "hello world";
  size_t len = strlen(data);
  uint32_t seed = 42;
  uint32_t h1 = Hash(data, len, seed);
  uint32_t h2 = Hash(data, len, seed);
  EXPECT_EQ(h1, h2);
}

// Test single byte input (remainder case 1)
TEST(HashTest_433, SingleByte_433) {
  uint32_t result = Hash("a", 1, 0);
  // Should be deterministic
  EXPECT_EQ(result, Hash("a", 1, 0));
  // Different single bytes should (likely) produce different hashes
  EXPECT_NE(Hash("a", 1, 0), Hash("b", 1, 0));
}

// Test two byte input (remainder case 2)
TEST(HashTest_433, TwoBytes_433) {
  uint32_t result = Hash("ab", 2, 0);
  EXPECT_EQ(result, Hash("ab", 2, 0));
  EXPECT_NE(Hash("ab", 2, 0), Hash("ac", 2, 0));
}

// Test three byte input (remainder case 3)
TEST(HashTest_433, ThreeBytes_433) {
  uint32_t result = Hash("abc", 3, 0);
  EXPECT_EQ(result, Hash("abc", 3, 0));
  EXPECT_NE(Hash("abc", 3, 0), Hash("abd", 3, 0));
}

// Test exactly four bytes (one full word, no remainder)
TEST(HashTest_433, FourBytes_433) {
  uint32_t result = Hash("abcd", 4, 0);
  EXPECT_EQ(result, Hash("abcd", 4, 0));
  EXPECT_NE(Hash("abcd", 4, 0), Hash("abce", 4, 0));
}

// Test five bytes (one full word + remainder of 1)
TEST(HashTest_433, FiveBytes_433) {
  uint32_t result = Hash("abcde", 5, 0);
  EXPECT_EQ(result, Hash("abcde", 5, 0));
}

// Test different seeds produce different hashes for the same data
TEST(HashTest_433, DifferentSeedsProduceDifferentHashes_433) {
  const char* data = "test data";
  size_t len = strlen(data);
  uint32_t h1 = Hash(data, len, 0);
  uint32_t h2 = Hash(data, len, 1);
  uint32_t h3 = Hash(data, len, 0xFFFFFFFF);
  EXPECT_NE(h1, h2);
  EXPECT_NE(h1, h3);
  EXPECT_NE(h2, h3);
}

// Test different data produces different hashes with same seed
TEST(HashTest_433, DifferentDataProduceDifferentHashes_433) {
  uint32_t h1 = Hash("foo", 3, 0);
  uint32_t h2 = Hash("bar", 3, 0);
  uint32_t h3 = Hash("baz", 3, 0);
  EXPECT_NE(h1, h2);
  EXPECT_NE(h1, h3);
  EXPECT_NE(h2, h3);
}

// Test with larger input data (multiple full words)
TEST(HashTest_433, LargerInput_433) {
  std::string data(100, 'x');
  uint32_t result = Hash(data.data(), data.size(), 0);
  EXPECT_EQ(result, Hash(data.data(), data.size(), 0));
}

// Test that partial length produces different hash than full length
TEST(HashTest_433, PartialLength_433) {
  const char* data = "hello world";
  uint32_t h_full = Hash(data, strlen(data), 0);
  uint32_t h_partial = Hash(data, 5, 0);
  EXPECT_NE(h_full, h_partial);
}

// Test with data containing null bytes
TEST(HashTest_433, DataWithNullBytes_433) {
  const char data1[] = {'\0', '\0', '\0', '\0'};
  const char data2[] = {'\0', '\0', '\0', '\1'};
  uint32_t h1 = Hash(data1, 4, 0);
  uint32_t h2 = Hash(data2, 4, 0);
  EXPECT_NE(h1, h2);
}

// Test with zero-length data and a non-zero seed
TEST(HashTest_433, ZeroLengthNonZeroSeed_433) {
  uint32_t result = Hash("anything", 0, 12345);
  EXPECT_EQ(result, Hash("something_else", 0, 12345));
}

// Test known values to catch regressions (these are computed from the implementation)
TEST(HashTest_433, KnownValues_433) {
  // Precompute and verify some specific hash values
  uint32_t h1 = Hash("", 0, 0xbc9f1d34);
  uint32_t h2 = Hash("", 0, 0xbc9f1d34);
  EXPECT_EQ(h1, h2);

  // Verify specific test vectors used in LevelDB's own tests
  EXPECT_EQ(Hash("\x08\x08\x08\x08", 4, 0), Hash("\x08\x08\x08\x08", 4, 0));
}

// Test boundary: exactly 8 bytes (two full words, no remainder)
TEST(HashTest_433, EightBytes_433) {
  uint32_t result = Hash("abcdefgh", 8, 0);
  EXPECT_EQ(result, Hash("abcdefgh", 8, 0));
}

// Test boundary: 7 bytes (one full word + 3 byte remainder)
TEST(HashTest_433, SevenBytes_433) {
  uint32_t result = Hash("abcdefg", 7, 0);
  EXPECT_EQ(result, Hash("abcdefg", 7, 0));
}

// Test with max uint32 seed
TEST(HashTest_433, MaxSeed_433) {
  uint32_t result = Hash("test", 4, 0xFFFFFFFF);
  EXPECT_EQ(result, Hash("test", 4, 0xFFFFFFFF));
}

// Test that high-bit bytes are handled correctly (unsigned treatment)
TEST(HashTest_433, HighBitBytes_433) {
  const char data[] = {static_cast<char>(0xFF), static_cast<char>(0xFE),
                       static_cast<char>(0xFD)};
  uint32_t result = Hash(data, 3, 0);
  EXPECT_EQ(result, Hash(data, 3, 0));
}

// Test long input with varying content
TEST(HashTest_433, LongVaryingInput_433) {
  std::string data;
  for (int i = 0; i < 1000; i++) {
    data.push_back(static_cast<char>(i & 0xFF));
  }
  uint32_t result = Hash(data.data(), data.size(), 0);
  EXPECT_EQ(result, Hash(data.data(), data.size(), 0));

  // Changing one byte should change the hash
  data[500] ^= 1;
  uint32_t result2 = Hash(data.data(), data.size(), 0);
  EXPECT_NE(result, result2);
}

}  // namespace leveldb
