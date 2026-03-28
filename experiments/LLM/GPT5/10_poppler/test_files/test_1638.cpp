// Decrypt_sha512Maj_test_1638.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <random>

// NOTE:
// sha512Maj() is declared as "static inline" inside Decrypt.cc.
// To test it as a black-box via its provided signature, we include the
// implementation unit so the symbol is available in this translation unit.
//
// If your build already compiles Decrypt.cc separately into the same test
// binary, including it here would cause ODR/linker issues. In that case,
// move these tests next to Decrypt.cc in a dedicated TU that doesn't also
// compile Decrypt.cc, or expose the helper via a test-only header.
#include "Decrypt.cc"

namespace {

// Independent expected-value computation using the *definition* of "majority"
// at the bit level (not the same algebraic expression as the implementation).
static uint64_t MajorityByCountingBits(uint64_t x, uint64_t y, uint64_t z) {
  uint64_t out = 0;
  for (int bit = 0; bit < 64; ++bit) {
    const uint64_t mask = (uint64_t{1} << bit);
    const int cnt = ((x & mask) ? 1 : 0) + ((y & mask) ? 1 : 0) + ((z & mask) ? 1 : 0);
    if (cnt >= 2) {
      out |= mask;
    }
  }
  return out;
}

class Sha512MajTest_1638 : public ::testing::Test {};

}  // namespace

TEST_F(Sha512MajTest_1638, AllZerosReturnsZero_1638) {
  EXPECT_EQ(sha512Maj(0ull, 0ull, 0ull), 0ull);
}

TEST_F(Sha512MajTest_1638, AllOnesReturnsAllOnes_1638) {
  constexpr uint64_t kAllOnes = ~uint64_t{0};
  EXPECT_EQ(sha512Maj(kAllOnes, kAllOnes, kAllOnes), kAllOnes);
}

TEST_F(Sha512MajTest_1638, TwoInputsSameDominatesResult_1638) {
  constexpr uint64_t a = 0x0123456789abcdefULL;
  constexpr uint64_t b = 0xfedcba9876543210ULL;

  // If two inputs are identical, majority should equal that value for every bit.
  EXPECT_EQ(sha512Maj(a, a, b), a);
  EXPECT_EQ(sha512Maj(a, b, a), a);
  EXPECT_EQ(sha512Maj(b, a, a), a);

  EXPECT_EQ(sha512Maj(b, b, a), b);
  EXPECT_EQ(sha512Maj(b, a, b), b);
  EXPECT_EQ(sha512Maj(a, b, b), b);
}

TEST_F(Sha512MajTest_1638, SimpleBoundaryPatterns_1638) {
  constexpr uint64_t kAllOnes = ~uint64_t{0};
  constexpr uint64_t kAltA = 0xAAAAAAAAAAAAAAAAULL;
  constexpr uint64_t kAlt5 = 0x5555555555555555ULL;

  // Majority of (0, 1, 1) => 1
  EXPECT_EQ(sha512Maj(0ull, kAllOnes, kAllOnes), kAllOnes);

  // Majority of (0, 0, 1) => 0
  EXPECT_EQ(sha512Maj(0ull, 0ull, kAllOnes), 0ull);

  // Alternating patterns: bitwise majority should match per-bit counting.
  EXPECT_EQ(sha512Maj(kAltA, kAlt5, kAllOnes), MajorityByCountingBits(kAltA, kAlt5, kAllOnes));
  EXPECT_EQ(sha512Maj(kAltA, kAlt5, 0ull), MajorityByCountingBits(kAltA, kAlt5, 0ull));
}

TEST_F(Sha512MajTest_1638, IsCommutativeAcrossArguments_1638) {
  constexpr uint64_t x = 0x0f0f0f0f0f0f0f0fULL;
  constexpr uint64_t y = 0x3333333333333333ULL;
  constexpr uint64_t z = 0xaaaaaaaaaaaaaaaaULL;

  const uint64_t r_xyz = sha512Maj(x, y, z);

  // Verify permutations produce the same observable output.
  EXPECT_EQ(sha512Maj(x, z, y), r_xyz);
  EXPECT_EQ(sha512Maj(y, x, z), r_xyz);
  EXPECT_EQ(sha512Maj(y, z, x), r_xyz);
  EXPECT_EQ(sha512Maj(z, x, y), r_xyz);
  EXPECT_EQ(sha512Maj(z, y, x), r_xyz);
}

TEST_F(Sha512MajTest_1638, MatchesBitCountingDefinitionOnDeterministicRandomSamples_1638) {
  std::mt19937_64 rng(1638u);  // deterministic
  for (int i = 0; i < 200; ++i) {
    const uint64_t x = rng();
    const uint64_t y = rng();
    const uint64_t z = rng();

    const uint64_t got = sha512Maj(x, y, z);
    const uint64_t expected = MajorityByCountingBits(x, y, z);

    EXPECT_EQ(got, expected) << "Mismatch on iteration " << i;
  }
}