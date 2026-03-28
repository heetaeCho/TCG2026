#include "util/random.h"
#include <gtest/gtest.h>
#include <set>
#include <vector>

namespace leveldb {

// Test that OneIn(1) always returns true since Next() % 1 == 0 always
TEST(RandomTest_88, OneInOneAlwaysReturnsTrue_88) {
  Random rng(42);
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(rng.OneIn(1));
  }
}

// Test that OneIn with a large n returns false at least sometimes and true at least sometimes
TEST(RandomTest_88, OneInLargeNReturnsMixedResults_88) {
  Random rng(301);
  int true_count = 0;
  int false_count = 0;
  const int iterations = 10000;
  for (int i = 0; i < iterations; i++) {
    if (rng.OneIn(10)) {
      true_count++;
    } else {
      false_count++;
    }
  }
  // With n=10, we expect roughly 10% true. Allow wide margin.
  EXPECT_GT(true_count, 0);
  EXPECT_GT(false_count, 0);
  // Roughly 10% should be true, check it's in reasonable range [1%, 30%]
  EXPECT_GT(true_count, iterations / 100);
  EXPECT_LT(true_count, iterations * 3 / 10);
}

// Test that OneIn(2) returns roughly 50% true
TEST(RandomTest_88, OneInTwoReturnsRoughlyHalf_88) {
  Random rng(12345);
  int true_count = 0;
  const int iterations = 10000;
  for (int i = 0; i < iterations; i++) {
    if (rng.OneIn(2)) {
      true_count++;
    }
  }
  // Expect roughly 50%, allow range [35%, 65%]
  EXPECT_GT(true_count, iterations * 35 / 100);
  EXPECT_LT(true_count, iterations * 65 / 100);
}

// Test that Next() produces different values (not stuck)
TEST(RandomTest_88, NextProducesDifferentValues_88) {
  Random rng(7);
  std::set<uint32_t> values;
  for (int i = 0; i < 100; i++) {
    values.insert(rng.Next());
  }
  // Should have many distinct values
  EXPECT_GT(values.size(), 90u);
}

// Test that Uniform(n) returns values in [0, n)
TEST(RandomTest_88, UniformReturnsValuesInRange_88) {
  Random rng(999);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Uniform(100);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 100u);
  }
}

// Test Uniform(1) always returns 0
TEST(RandomTest_88, UniformOneAlwaysReturnsZero_88) {
  Random rng(42);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng.Uniform(1), 0u);
  }
}

// Test that Skewed returns values within expected range
TEST(RandomTest_88, SkewedReturnsValuesInRange_88) {
  Random rng(500);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Skewed(5);
    // max_log=5 means uniform in [0,5], then 1<<uniform gives max 32
    // Skewed should return Uniform(1 << uniform), so result in [0, 31]
    EXPECT_LT(val, 32u);
  }
}

// Test Skewed(0) always returns 0 (since Uniform(1) == 0)
TEST(RandomTest_88, SkewedZeroAlwaysReturnsZero_88) {
  Random rng(123);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng.Skewed(0), 0u);
  }
}

// Test determinism: same seed produces same sequence
TEST(RandomTest_88, SameSeedProducesSameSequence_88) {
  Random rng1(42);
  Random rng2(42);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng1.Next(), rng2.Next());
  }
}

// Test different seeds produce different sequences
TEST(RandomTest_88, DifferentSeedsProduceDifferentSequences_88) {
  Random rng1(42);
  Random rng2(43);
  bool all_same = true;
  for (int i = 0; i < 100; i++) {
    if (rng1.Next() != rng2.Next()) {
      all_same = false;
      break;
    }
  }
  EXPECT_FALSE(all_same);
}

// Test seed 0 doesn't break (edge case for seed masking)
TEST(RandomTest_88, SeedZeroWorks_88) {
  Random rng(0);
  // Should still produce values without crashing
  uint32_t val = rng.Next();
  // Just ensure it doesn't crash and returns something
  (void)val;
  EXPECT_TRUE(true);
}

// Test OneIn with various small values of n
TEST(RandomTest_88, OneInVariousSmallN_88) {
  Random rng(77);
  // Just ensure no crashes for small n values
  for (int n = 1; n <= 10; n++) {
    bool result = rng.OneIn(n);
    (void)result;  // Just checking it doesn't crash
  }
  EXPECT_TRUE(true);
}

// Test that Uniform covers the full range
TEST(RandomTest_88, UniformCoversFullRange_88) {
  Random rng(2023);
  std::set<uint32_t> seen;
  // With n=5, after enough iterations we should see all values 0-4
  for (int i = 0; i < 1000; i++) {
    seen.insert(rng.Uniform(5));
  }
  EXPECT_EQ(seen.size(), 5u);
}

}  // namespace leveldb
