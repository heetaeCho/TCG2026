#include "util/random.h"
#include <gtest/gtest.h>
#include <set>
#include <cstdint>

namespace leveldb {

// Test that Next() returns values within valid range (31-bit positive values)
TEST(RandomTest_89, NextReturnsNonZeroValues_89) {
  Random rng(42);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Next();
    // seed_ is masked with 0x7fffffffu, so values should be in [1, 2^31 - 1) range
    EXPECT_GT(val, 0u);
    EXPECT_LT(val, 0x7fffffffu);
  }
}

// Test that Uniform returns values in [0, n)
TEST(RandomTest_89, UniformReturnsValuesInRange_89) {
  Random rng(101);
  for (int n = 1; n <= 100; n++) {
    for (int i = 0; i < 100; i++) {
      uint32_t val = rng.Uniform(n);
      EXPECT_GE(val, 0u);
      EXPECT_LT(val, static_cast<uint32_t>(n));
    }
  }
}

// Test Uniform(1) always returns 0
TEST(RandomTest_89, UniformOneAlwaysReturnsZero_89) {
  Random rng(7);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng.Uniform(1), 0u);
  }
}

// Test Uniform with large n
TEST(RandomTest_89, UniformLargeN_89) {
  Random rng(999);
  int n = 1000000;
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Uniform(n);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, static_cast<uint32_t>(n));
  }
}

// Test that OneIn(1) always returns true
TEST(RandomTest_89, OneInOneAlwaysTrue_89) {
  Random rng(12345);
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(rng.OneIn(1));
  }
}

// Test that OneIn returns bool values and with large n mostly returns false
TEST(RandomTest_89, OneInReturnsBool_89) {
  Random rng(54321);
  int true_count = 0;
  int iterations = 10000;
  for (int i = 0; i < iterations; i++) {
    if (rng.OneIn(10000)) {
      true_count++;
    }
  }
  // With n=10000, expected ~1 true per 10000 calls. Should be very few.
  EXPECT_LT(true_count, 100);  // Very generous upper bound
}

// Test that OneIn(2) returns roughly 50% true
TEST(RandomTest_89, OneInTwoApproximatelyHalf_89) {
  Random rng(77);
  int true_count = 0;
  int iterations = 10000;
  for (int i = 0; i < iterations; i++) {
    if (rng.OneIn(2)) {
      true_count++;
    }
  }
  // Should be roughly 50%, allow wide margin
  EXPECT_GT(true_count, 3000);
  EXPECT_LT(true_count, 7000);
}

// Test Skewed returns values in valid range [0, 2^max_log)
TEST(RandomTest_89, SkewedReturnsValuesInRange_89) {
  Random rng(42);
  for (int max_log = 0; max_log <= 20; max_log++) {
    uint32_t upper_bound = 1u << max_log;
    for (int i = 0; i < 100; i++) {
      uint32_t val = rng.Skewed(max_log);
      EXPECT_GE(val, 0u);
      EXPECT_LT(val, upper_bound);
    }
  }
}

// Test Skewed(0) always returns 0
TEST(RandomTest_89, SkewedZeroAlwaysReturnsZero_89) {
  Random rng(123);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng.Skewed(0), 0u);
  }
}

// Test that different seeds produce different sequences
TEST(RandomTest_89, DifferentSeedsDifferentSequences_89) {
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

// Test that same seed produces same sequence (deterministic)
TEST(RandomTest_89, SameSeedSameSequence_89) {
  Random rng1(42);
  Random rng2(42);
  for (int i = 0; i < 1000; i++) {
    EXPECT_EQ(rng1.Next(), rng2.Next());
  }
}

// Test that Uniform produces some variety of values
TEST(RandomTest_89, UniformProducesVariety_89) {
  Random rng(555);
  std::set<uint32_t> values;
  for (int i = 0; i < 1000; i++) {
    values.insert(rng.Uniform(1000));
  }
  // Should produce many distinct values
  EXPECT_GT(values.size(), 500u);
}

// Test Skewed produces variety including both small and large values
TEST(RandomTest_89, SkewedProducesVariety_89) {
  Random rng(999);
  bool has_small = false;
  bool has_large = false;
  for (int i = 0; i < 10000; i++) {
    uint32_t val = rng.Skewed(10);
    if (val < 4) has_small = true;
    if (val >= 256) has_large = true;
  }
  EXPECT_TRUE(has_small);
  EXPECT_TRUE(has_large);
}

// Test with seed 0
TEST(RandomTest_89, SeedZero_89) {
  Random rng(0);
  // Should still produce valid values
  for (int i = 0; i < 100; i++) {
    uint32_t val = rng.Next();
    EXPECT_GT(val, 0u);
    EXPECT_LT(val, 0x7fffffffu);
  }
}

// Test with max seed value
TEST(RandomTest_89, MaxSeedValue_89) {
  Random rng(0x7fffffffu);
  for (int i = 0; i < 100; i++) {
    uint32_t val = rng.Next();
    EXPECT_GT(val, 0u);
    EXPECT_LT(val, 0x7fffffffu);
  }
}

// Test Uniform with power of 2
TEST(RandomTest_89, UniformPowerOfTwo_89) {
  Random rng(333);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Uniform(256);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 256u);
  }
}

// Test Skewed with max_log = 1 returns 0 or 1
TEST(RandomTest_89, SkewedOneReturnsZeroOrOne_89) {
  Random rng(444);
  std::set<uint32_t> values;
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Skewed(1);
    EXPECT_LT(val, 2u);
    values.insert(val);
  }
  // Should see both 0 and 1
  EXPECT_EQ(values.size(), 2u);
}

}  // namespace leveldb
