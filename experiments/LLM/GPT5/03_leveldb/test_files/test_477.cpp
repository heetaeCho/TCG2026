// random_constructor_test_477.cc
#include "util/random.h"
#include <gtest/gtest.h>
#include <vector>
#include <cstdint>

using leveldb::Random;

namespace {

// Helper: generate a short, observable sequence using only the public API.
static std::vector<uint32_t> GenerateNexts(Random* rng, int count) {
  std::vector<uint32_t> out;
  out.reserve(count);
  for (int i = 0; i < count; ++i) {
    out.push_back(rng->Next());
  }
  return out;
}

}  // namespace

class RandomTest_477 : public ::testing::Test {
 protected:
  // Keep sequences short to stay fast and deterministic.
  static constexpr int kSeqLen = 8;
};

// Normal operation: same seed -> identical observable sequence
TEST_F(RandomTest_477, SameSeedProducesIdenticalSequence_477) {
  Random a(12345u);
  Random b(12345u);

  auto seq_a = GenerateNexts(&a, kSeqLen);
  auto seq_b = GenerateNexts(&b, kSeqLen);

  EXPECT_EQ(seq_a, seq_b);
}

// Normal operation: different seeds -> (likely) different observable sequence
// We only assert the first value differs to avoid overspecifying behavior.
TEST_F(RandomTest_477, DifferentSeedsLikelyDifferentFirstValue_477) {
  Random a(12345u);
  Random b(67890u);

  uint32_t first_a = a.Next();
  uint32_t first_b = b.Next();

  EXPECT_NE(first_a, first_b);
}

// Boundary: constructor handles seed 0 by mapping to a valid internal seed.
// Observable behavior: Random(0) should produce the same sequence as Random(1).
TEST_F(RandomTest_477, ZeroSeedBehavesLikeOne_477) {
  Random zero_seed(0u);
  Random one_seed(1u);

  auto seq_zero = GenerateNexts(&zero_seed, kSeqLen);
  auto seq_one  = GenerateNexts(&one_seed,  kSeqLen);

  EXPECT_EQ(seq_zero, seq_one);
}

// Boundary: constructor handles seed 0x7fffffff similarly to a valid non-edge seed.
// Observable behavior: Random(0x7fffffff) should match Random(1).
TEST_F(RandomTest_477, MaxPositive31BitSeedBehavesLikeOne_477) {
  Random max31(0x7fffffffu);
  Random one(1u);

  auto seq_max31 = GenerateNexts(&max31, kSeqLen);
  auto seq_one   = GenerateNexts(&one,   kSeqLen);

  EXPECT_EQ(seq_max31, seq_one);
}

// Boundary: high bit is masked off by the constructor.
// Observable behavior: Random(0x80000005) should behave like Random(0x00000005).
TEST_F(RandomTest_477, HighBitMaskedOffMatchesLowerValue_477) {
  Random high_bit(0x80000005u);
  Random low_val (0x00000005u);

  auto seq_high = GenerateNexts(&high_bit, kSeqLen);
  auto seq_low  = GenerateNexts(&low_val,  kSeqLen);

  EXPECT_EQ(seq_high, seq_low);
}
