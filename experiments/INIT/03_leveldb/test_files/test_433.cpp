// File: util/hash_test_433.cc
#include "util/hash.h"

#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace leveldb {

class HashTest_433 : public ::testing::Test {
 protected:
  static uint32_t H(const char* data, size_t n, uint32_t seed) {
    return Hash(data, n, seed);
  }
};

// Empty input should be deterministic for the same seed.
TEST_F(HashTest_433, EmptyInput_Deterministic_433) {
  const uint32_t seed = 0x12345678u;
  uint32_t h1 = H("", 0, seed);
  uint32_t h2 = H("", 0, seed);
  EXPECT_EQ(h1, h2);
}

// Same bytes hashed multiple times with the same seed should be identical.
// Different seeds should (very likely) produce different results.
TEST_F(HashTest_433, DifferentSeeds_ProduceDifferentHashes_433) {
  const char* kData = "leveldb";
  const size_t n = 7;

  const uint32_t seed_a = 0x0u;
  const uint32_t seed_b = 0xdeadbeefu;

  uint32_t h_a1 = H(kData, n, seed_a);
  uint32_t h_a2 = H(kData, n, seed_a);
  EXPECT_EQ(h_a1, h_a2);  // determinism per seed

  uint32_t h_b = H(kData, n, seed_b);
  // Collisions are possible but extremely unlikely for this simple check.
  EXPECT_NE(h_a1, h_b);
}

// Boundary-length behavior: sizes 1, 2, and 3 exercise the tail handling.
// Hash results should be deterministic and typically differ as length changes.
TEST_F(HashTest_433, Length1_2_3_DeterministicAndUsuallyDistinct_433) {
  const char* kData = "abc";
  const uint32_t seed = 0x9e3779b9u;

  uint32_t h1a = H(kData, 1, seed);
  uint32_t h1b = H(kData, 1, seed);
  EXPECT_EQ(h1a, h1b);

  uint32_t h2 = H(kData, 2, seed);
  uint32_t h3 = H(kData, 3, seed);

  // These are not guaranteed to differ mathematically, but collisions are very unlikely.
  EXPECT_NE(h1a, h2);
  EXPECT_NE(h2, h3);
  EXPECT_NE(h1a, h3);
}

// Word-sized inputs (4, 8 bytes) should be hashed deterministically.
// Appending data (changing length/content) should typically change the hash.
TEST_F(HashTest_433, FourAndEightByteInputs_433) {
  const uint32_t seed = 0x13579bdu;

  const std::array<char, 4> four = {'A', 'B', 'C', 'D'};
  const std::array<char, 8> eight = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

  uint32_t h4a = H(four.data(), four.size(), seed);
  uint32_t h4b = H(four.data(), four.size(), seed);
  EXPECT_EQ(h4a, h4b);

  uint32_t h8 = H(eight.data(), eight.size(), seed);
  EXPECT_NE(h4a, h8);
}

// Embedded NUL bytes are part of the data and must affect the hash.
// Identical byte sequences produced via different containers should hash the same.
TEST_F(HashTest_433, IncludesZeroByte_EqualAcrossContainers_433) {
  const uint32_t seed = 0xabcdef01u;

  std::string s("a\0b", 3);
  std::vector<char> v = {'a', '\0', 'b'};

  uint32_t hs = H(s.data(), s.size(), seed);
  uint32_t hv = H(v.data(), v.size(), seed);
  EXPECT_EQ(hs, hv);

  // Changing a single byte (even if it's the NUL) should typically change the hash.
  std::vector<char> v2 = v;
  v2[1] = 'X';
  EXPECT_NE(hv, H(v2.data(), v2.size(), seed));
}

// The function takes a const pointer and must not modify input memory.
TEST_F(HashTest_433, InputBuffer_NotModified_433) {
  const uint32_t seed = 0x11111111u;

  std::array<char, 8> buf = {'a', 'b', 'c', 'd', 'X', 'Y', 'Z', 'W'};
  std::array<char, 8> before = buf;

  (void)H(buf.data(), 5 /* hash only a prefix */, seed);

  // Entire buffer should remain unchanged.
  EXPECT_EQ(0, std::memcmp(buf.data(), before.data(), before.size()));
}

// Hash should be independent of pointer alignment. Hashing the same slice
// from different base pointers should yield the same value.
TEST_F(HashTest_433, SameSlice_DifferentAlignment_SameHash_433) {
  const uint32_t seed = 0x2468aceu;

  std::vector<char> base;
  for (int i = 0; i < 16; ++i) base.push_back(static_cast<char>(i + 1));

  const char* p_aligned = base.data();      // slice starting at 0
  const char* p_unaligned = base.data() + 1; // slice starting at 1
  const size_t len_unaligned = base.size() - 1;

  // Build an identical copy of the unaligned slice into a contiguous buffer.
  std::vector<char> copy(p_unaligned, p_unaligned + len_unaligned);

  uint32_t h1 = H(p_unaligned, len_unaligned, seed);
  uint32_t h2 = H(copy.data(), copy.size(), seed);
  EXPECT_EQ(h1, h2);

  // As a sanity check, the hash of the full aligned buffer should typically differ.
  uint32_t h_full = H(p_aligned, base.size(), seed);
  EXPECT_NE(h1, h_full);
}

// Large input: identical buffers hash the same; flipping one byte should
// (with overwhelming probability) change the hash.
TEST_F(HashTest_433, LargeInput_SingleByteChangeAffectsHash_433) {
  const uint32_t seed = 0xf00ba7u;

  std::vector<char> big(1000);
  for (size_t i = 0; i < big.size(); ++i) big[i] = static_cast<char>(i & 0xFF);

  std::vector<char> big_copy = big;

  uint32_t h1 = H(big.data(), big.size(), seed);
  uint32_t h2 = H(big_copy.data(), big_copy.size(), seed);
  EXPECT_EQ(h1, h2);

  // Flip one byte in the middle.
  big_copy[500] ^= 0x01;
  uint32_t h3 = H(big_copy.data(), big_copy.size(), seed);
  EXPECT_NE(h1, h3);
}

}  // namespace leveldb
