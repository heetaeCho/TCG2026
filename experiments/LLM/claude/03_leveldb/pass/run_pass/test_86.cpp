#include "util/random.h"
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <cstdint>

namespace leveldb {

// Test that Next() returns values within valid range [1, 2^31-1)
TEST(RandomTest_86, NextReturnsWithinValidRange_86) {
  Random rng(42);
  for (int i = 0; i < 10000; i++) {
    uint32_t val = rng.Next();
    EXPECT_GT(val, 0u);
    EXPECT_LE(val, 2147483646u);  // 2^31 - 2
  }
}

// Test that Next() is deterministic for same seed
TEST(RandomTest_86, NextIsDeterministicForSameSeed_86) {
  Random rng1(12345);
  Random rng2(12345);
  for (int i = 0; i < 1000; i++) {
    EXPECT_EQ(rng1.Next(), rng2.Next());
  }
}

// Test that different seeds produce different sequences
TEST(RandomTest_86, DifferentSeedsProduceDifferentSequences_86) {
  Random rng1(1);
  Random rng2(2);
  bool all_same = true;
  for (int i = 0; i < 100; i++) {
    if (rng1.Next() != rng2.Next()) {
      all_same = false;
      break;
    }
  }
  EXPECT_FALSE(all_same);
}

// Test seed of 0 (edge case: seed_ = 0 & 0x7fffffff = 0)
TEST(RandomTest_86, SeedZero_86) {
  Random rng(0);
  // Even with seed 0, Next() should still return values
  uint32_t val = rng.Next();
  // seed_ * A = 0, so (0 >> 31) + (0 & M) = 0, seed_ stays 0
  // This is a degenerate case but should not crash
  // We just verify it doesn't crash and returns a value
  (void)val;
}

// Test seed with high bit set (should be masked by constructor)
TEST(RandomTest_86, SeedWithHighBitSetIsMasked_86) {
  Random rng1(0x80000001u);  // High bit set, masked to 1
  Random rng2(1);             // Same effective seed
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng1.Next(), rng2.Next());
  }
}

// Test seed 0x7fffffff (maximum valid seed)
TEST(RandomTest_86, MaxSeed_86) {
  Random rng(0x7fffffffu);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Next();
    EXPECT_GT(val, 0u);
    EXPECT_LE(val, 2147483646u);
  }
}

// Test Uniform returns values in [0, n)
TEST(RandomTest_86, UniformReturnsWithinRange_86) {
  Random rng(301);
  for (int i = 0; i < 10000; i++) {
    uint32_t val = rng.Uniform(10);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 10u);
  }
}

// Test Uniform(1) always returns 0
TEST(RandomTest_86, UniformOneAlwaysReturnsZero_86) {
  Random rng(42);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng.Uniform(1), 0u);
  }
}

// Test Uniform with large n
TEST(RandomTest_86, UniformLargeN_86) {
  Random rng(123);
  for (int i = 0; i < 10000; i++) {
    uint32_t val = rng.Uniform(1000000);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 1000000u);
  }
}

// Test OneIn returns bool
TEST(RandomTest_86, OneInReturnsBool_86) {
  Random rng(42);
  int true_count = 0;
  int iterations = 100000;
  for (int i = 0; i < iterations; i++) {
    if (rng.OneIn(10)) {
      true_count++;
    }
  }
  // Expect roughly 10% true, allow wide margin
  EXPECT_GT(true_count, iterations / 100);      // at least 1%
  EXPECT_LT(true_count, iterations * 3 / 10);   // less than 30%
}

// Test OneIn(1) always returns true
TEST(RandomTest_86, OneInOneAlwaysTrue_86) {
  Random rng(42);
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(rng.OneIn(1));
  }
}

// Test OneIn with large n rarely returns true
TEST(RandomTest_86, OneInLargeNRarelyTrue_86) {
  Random rng(42);
  int true_count = 0;
  for (int i = 0; i < 10000; i++) {
    if (rng.OneIn(10000)) {
      true_count++;
    }
  }
  // With n=10000 and 10000 trials, expect ~1 true, allow up to 10
  EXPECT_LT(true_count, 20);
}

// Test Skewed returns values in expected range [0, 2^max_log - 1]
TEST(RandomTest_86, SkewedReturnsWithinRange_86) {
  Random rng(42);
  for (int i = 0; i < 10000; i++) {
    uint32_t val = rng.Skewed(10);
    EXPECT_LT(val, (1u << 10));
  }
}

// Test Skewed(0) always returns 0
TEST(RandomTest_86, SkewedZeroAlwaysReturnsZero_86) {
  Random rng(42);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng.Skewed(0), 0u);
  }
}

// Test Skewed(1) returns 0 or 1
TEST(RandomTest_86, SkewedOneReturnsZeroOrOne_86) {
  Random rng(42);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Skewed(1);
    EXPECT_LE(val, 1u);
  }
}

// Test that Skewed distribution is skewed toward smaller values
TEST(RandomTest_86, SkewedDistributionIsSkewed_86) {
  Random rng(42);
  int small_count = 0;
  int total = 100000;
  for (int i = 0; i < total; i++) {
    uint32_t val = rng.Skewed(10);
    if (val < 4) {
      small_count++;
    }
  }
  // Small values should appear more frequently than uniform distribution
  // Under uniform over [0, 1024), P(val < 4) ~ 4/1024 ~ 0.4%
  // With skewing, should be much higher
  EXPECT_GT(small_count, total / 10);  // at least 10%
}

// Test Next produces varied output (not stuck)
TEST(RandomTest_86, NextProducesVariedOutput_86) {
  Random rng(1);
  std::set<uint32_t> values;
  for (int i = 0; i < 1000; i++) {
    values.insert(rng.Next());
  }
  // Should produce many unique values
  EXPECT_GT(values.size(), 900u);
}

// Test Uniform produces all values in range for small n
TEST(RandomTest_86, UniformCoversAllValuesSmallRange_86) {
  Random rng(42);
  std::set<uint32_t> values;
  for (int i = 0; i < 10000; i++) {
    values.insert(rng.Uniform(5));
  }
  // Should cover all values 0-4
  EXPECT_EQ(values.size(), 5u);
}

// Test seed 1 produces known first value (deterministic check)
TEST(RandomTest_86, SeedOneFirstValue_86) {
  Random rng(1);
  uint32_t first = rng.Next();
  // Based on LCG: seed=1, product = 1*16807 = 16807
  // new_seed = (16807 >> 31) + (16807 & M) = 0 + 16807 = 16807
  EXPECT_EQ(first, 16807u);
}

// Test seed 1 second value
TEST(RandomTest_86, SeedOneSecondValue_86) {
  Random rng(1);
  rng.Next();  // first: 16807
  uint32_t second = rng.Next();
  // seed=16807, product = 16807 * 16807 = 282475249
  // new_seed = (282475249 >> 31) + (282475249 & M) = 0 + 282475249 = 282475249
  EXPECT_EQ(second, 282475249u);
}

// Test many iterations don't produce zero
TEST(RandomTest_86, NextNeverReturnsZeroForNonZeroSeed_86) {
  Random rng(1);
  for (int i = 0; i < 100000; i++) {
    EXPECT_NE(rng.Next(), 0u);
  }
}

// Test Uniform(2) produces both 0 and 1
TEST(RandomTest_86, UniformTwoProducesBothValues_86) {
  Random rng(42);
  bool seen_zero = false, seen_one = false;
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Uniform(2);
    if (val == 0) seen_zero = true;
    if (val == 1) seen_one = true;
    if (seen_zero && seen_one) break;
  }
  EXPECT_TRUE(seen_zero);
  EXPECT_TRUE(seen_one);
}

}  // namespace leveldb
