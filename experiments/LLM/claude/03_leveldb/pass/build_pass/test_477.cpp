#include "util/random.h"
#include <gtest/gtest.h>
#include <set>
#include <cstdint>

namespace leveldb {

// Test fixture for Random class
class RandomTest_477 : public ::testing::Test {
 protected:
};

// --- Constructor Tests ---

TEST_F(RandomTest_477, ConstructorWithNormalSeed_477) {
  // Should construct without issues with a normal seed
  Random rng(42);
  // Verify it can produce values
  uint32_t val = rng.Next();
  EXPECT_GT(val, 0u);
}

TEST_F(RandomTest_477, ConstructorWithZeroSeed_477) {
  // Seed 0 should be adjusted to 1 internally
  Random rng(0);
  uint32_t val = rng.Next();
  EXPECT_GT(val, 0u);
}

TEST_F(RandomTest_477, ConstructorWithMaxSeed_477) {
  // Seed 2147483647 (0x7FFFFFFF) should be adjusted to 1
  Random rng(2147483647L);
  uint32_t val = rng.Next();
  EXPECT_GT(val, 0u);
}

TEST_F(RandomTest_477, ConstructorWithHighBitSet_477) {
  // High bit should be masked off (& 0x7fffffffu)
  Random rng(0x80000001u);  // After masking: 1
  uint32_t val = rng.Next();
  EXPECT_GT(val, 0u);
}

TEST_F(RandomTest_477, ConstructorWithAllBitsSet_477) {
  // 0xFFFFFFFF & 0x7FFFFFFF = 0x7FFFFFFF = 2147483647, should be adjusted to 1
  Random rng(0xFFFFFFFFu);
  uint32_t val = rng.Next();
  EXPECT_GT(val, 0u);
}

TEST_F(RandomTest_477, ConstructorSeedMaskingResultsInZero_477) {
  // 0x80000000 & 0x7FFFFFFF = 0, should be adjusted to 1
  Random rng(0x80000000u);
  uint32_t val = rng.Next();
  EXPECT_GT(val, 0u);
}

// --- Next() Tests ---

TEST_F(RandomTest_477, NextProducesNonZeroValues_477) {
  Random rng(1);
  for (int i = 0; i < 100; i++) {
    uint32_t val = rng.Next();
    // Next() should produce values in range [1, 2^31 - 2] based on typical LCG
    EXPECT_GT(val, 0u);
  }
}

TEST_F(RandomTest_477, NextProducesVaryingValues_477) {
  Random rng(301);
  std::set<uint32_t> values;
  for (int i = 0; i < 100; i++) {
    values.insert(rng.Next());
  }
  // Should produce many distinct values
  EXPECT_GT(values.size(), 50u);
}

TEST_F(RandomTest_477, NextIsDeterministic_477) {
  Random rng1(42);
  Random rng2(42);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng1.Next(), rng2.Next());
  }
}

TEST_F(RandomTest_477, DifferentSeedsProduceDifferentSequences_477) {
  Random rng1(1);
  Random rng2(2);
  // At least one of the first few values should differ
  bool differs = false;
  for (int i = 0; i < 10; i++) {
    if (rng1.Next() != rng2.Next()) {
      differs = true;
      break;
    }
  }
  EXPECT_TRUE(differs);
}

// --- Uniform() Tests ---

TEST_F(RandomTest_477, UniformReturnsWithinRange_477) {
  Random rng(7);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Uniform(10);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 10u);
  }
}

TEST_F(RandomTest_477, UniformWithOne_477) {
  Random rng(13);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng.Uniform(1), 0u);
  }
}

TEST_F(RandomTest_477, UniformWithLargeN_477) {
  Random rng(99);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Uniform(1000000);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 1000000u);
  }
}

TEST_F(RandomTest_477, UniformDistributionIsReasonable_477) {
  Random rng(123);
  int counts[10] = {0};
  const int iterations = 10000;
  for (int i = 0; i < iterations; i++) {
    uint32_t val = rng.Uniform(10);
    counts[val]++;
  }
  // Each bucket should have roughly iterations/10 = 1000, allow wide margin
  for (int i = 0; i < 10; i++) {
    EXPECT_GT(counts[i], 500);
    EXPECT_LT(counts[i], 1500);
  }
}

// --- OneIn() Tests ---

TEST_F(RandomTest_477, OneInOneAlwaysReturnsTrue_477) {
  Random rng(42);
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(rng.OneIn(1));
  }
}

TEST_F(RandomTest_477, OneInLargeNumberMostlyReturnsFalse_477) {
  Random rng(42);
  int true_count = 0;
  const int iterations = 10000;
  for (int i = 0; i < iterations; i++) {
    if (rng.OneIn(10000)) {
      true_count++;
    }
  }
  // Expected ~1, allow some margin
  EXPECT_LT(true_count, 20);
}

TEST_F(RandomTest_477, OneInReturnsBool_477) {
  Random rng(42);
  // Just verify it returns true or false (compiles and runs correctly)
  bool result = rng.OneIn(2);
  EXPECT_TRUE(result == true || result == false);
}

TEST_F(RandomTest_477, OneInTwoReturnsTrueRoughlyHalfTheTime_477) {
  Random rng(42);
  int true_count = 0;
  const int iterations = 10000;
  for (int i = 0; i < iterations; i++) {
    if (rng.OneIn(2)) {
      true_count++;
    }
  }
  // Should be roughly 50%, allow margin
  EXPECT_GT(true_count, 4000);
  EXPECT_LT(true_count, 6000);
}

// --- Skewed() Tests ---

TEST_F(RandomTest_477, SkewedWithZero_477) {
  Random rng(42);
  for (int i = 0; i < 100; i++) {
    // max_log = 0 means range is [0, 1), so always 0
    uint32_t val = rng.Skewed(0);
    EXPECT_EQ(val, 0u);
  }
}

TEST_F(RandomTest_477, SkewedReturnsWithinRange_477) {
  Random rng(42);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Skewed(10);
    // Skewed(10) should return values in [0, 2^10 - 1] = [0, 1023]
    EXPECT_LE(val, 1023u);
  }
}

TEST_F(RandomTest_477, SkewedProducesSmallAndLargeValues_477) {
  Random rng(42);
  bool has_small = false;
  bool has_large = false;
  for (int i = 0; i < 10000; i++) {
    uint32_t val = rng.Skewed(10);
    if (val < 10) has_small = true;
    if (val > 100) has_large = true;
  }
  EXPECT_TRUE(has_small);
  EXPECT_TRUE(has_large);
}

TEST_F(RandomTest_477, SkewedIsDeterministic_477) {
  Random rng1(42);
  Random rng2(42);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng1.Skewed(10), rng2.Skewed(10));
  }
}

TEST_F(RandomTest_477, SkewedWithMaxLog1_477) {
  Random rng(42);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Skewed(1);
    // Skewed(1) picks base in Uniform(2) -> {0, 1}
    // If base=0: Uniform(1)=0, if base=1: Uniform(2) in {0,1}
    EXPECT_LE(val, 1u);
  }
}

}  // namespace leveldb
