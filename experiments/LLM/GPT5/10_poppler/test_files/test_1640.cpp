// TEST_ID: 1640
// Unit tests for sha512Sigma1() in poppler/Decrypt.cc
//
// Notes:
// - sha512Sigma1() is a static inline helper (not part of a public header interface).
// - To test it without re-implementing its logic, we include the implementation unit
//   so the symbol is available in this translation unit.
// - These tests focus on observable black-box properties (determinism, boundary inputs,
//   and simple invariants for special bit-patterns).

#include <gtest/gtest.h>

#include <cstdint>

#if defined(__GNUG__) || defined(__clang__)
#include <limits>
#endif

// Include the implementation file to access the static inline helper.
// The build system for this test target should compile this test without also
// separately compiling/linking Decrypt.cc into the same binary (to avoid ODR issues).
#include "Decrypt.cc"

namespace {

class Sha512Sigma1Test_1640 : public ::testing::Test {};

static int Popcount64(uint64_t v) {
#if defined(__GNUG__) || defined(__clang__)
  return __builtin_popcountll(static_cast<unsigned long long>(v));
#else
  // Portable fallback (used only if builtin isn't available).
  int c = 0;
  while (v) {
    v &= (v - 1);
    ++c;
  }
  return c;
#endif
}

TEST_F(Sha512Sigma1Test_1640, ZeroInputReturnsZero_1640) {
  const uint64_t x = 0ULL;
  const uint64_t y = sha512Sigma1(x);
  EXPECT_EQ(y, 0ULL);
}

TEST_F(Sha512Sigma1Test_1640, AllOnesInputReturnsAllOnes_1640) {
  const uint64_t x = ~0ULL;
  const uint64_t y = sha512Sigma1(x);
  EXPECT_EQ(y, ~0ULL);
}

TEST_F(Sha512Sigma1Test_1640, DeterministicForSameInput_1640) {
  const uint64_t x = 0x0123456789ABCDEFULL;
  const uint64_t y1 = sha512Sigma1(x);
  const uint64_t y2 = sha512Sigma1(x);
  EXPECT_EQ(y1, y2);
}

TEST_F(Sha512Sigma1Test_1640, DifferentInputsUsuallyProduceDifferentOutputs_1640) {
  // This is a sanity check (not a cryptographic guarantee), using two very distinct inputs.
  const uint64_t x1 = 0ULL;
  const uint64_t x2 = 1ULL;
  const uint64_t y1 = sha512Sigma1(x1);
  const uint64_t y2 = sha512Sigma1(x2);
  EXPECT_NE(y1, y2);
}

TEST_F(Sha512Sigma1Test_1640, SingleBitInputProducesLimitedSetBits_1640) {
  // For a single-bit input, the output should not explode in bit population.
  // This checks a simple invariant: popcount is small and non-zero.
  const uint64_t x = 1ULL;
  const uint64_t y = sha512Sigma1(x);

  const int pc = Popcount64(y);
  EXPECT_GT(pc, 0);
  EXPECT_LE(pc, 6);  // Conservative upper bound for this style of bit-mixing.
}

TEST_F(Sha512Sigma1Test_1640, SingleHighBitBoundaryInputProducesLimitedSetBits_1640) {
  // Boundary bit position (top bit set).
  const uint64_t x = (1ULL << 63);
  const uint64_t y = sha512Sigma1(x);

  const int pc = Popcount64(y);
  EXPECT_GT(pc, 0);
  EXPECT_LE(pc, 6);  // Conservative upper bound.
}

TEST_F(Sha512Sigma1Test_1640, AlternatingBitPatternsDoNotCrashAndAreDeterministic_1640) {
  const uint64_t x1 = 0xAAAAAAAAAAAAAAAAULL;
  const uint64_t x2 = 0x5555555555555555ULL;

  const uint64_t y1a = sha512Sigma1(x1);
  const uint64_t y1b = sha512Sigma1(x1);
  const uint64_t y2a = sha512Sigma1(x2);
  const uint64_t y2b = sha512Sigma1(x2);

  EXPECT_EQ(y1a, y1b);
  EXPECT_EQ(y2a, y2b);
  EXPECT_NE(y1a, y2a);  // sanity for two complementary patterns
}

}  // namespace