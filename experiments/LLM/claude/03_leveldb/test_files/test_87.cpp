#include "util/random.h"
#include <gtest/gtest.h>
#include <set>
#include <vector>

namespace leveldb {

class RandomTest_87 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test that Uniform returns values within [0, n)
TEST_F(RandomTest_87, UniformReturnsValuesInRange_87) {
  Random rng(42);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Uniform(100);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 100u);
  }
}

// Test Uniform with n=1 always returns 0
TEST_F(RandomTest_87, UniformWithOneAlwaysReturnsZero_87) {
  Random rng(123);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng.Uniform(1), 0u);
  }
}

// Test Uniform with n=2 returns only 0 or 1
TEST_F(RandomTest_87, UniformWithTwoReturnsBinary_87) {
  Random rng(456);
  bool saw_zero = false;
  bool saw_one = false;
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Uniform(2);
    EXPECT_LT(val, 2u);
    if (val == 0) saw_zero = true;
    if (val == 1) saw_one = true;
  }
  EXPECT_TRUE(saw_zero);
  EXPECT_TRUE(saw_one);
}

// Test Uniform with large n
TEST_F(RandomTest_87, UniformWithLargeN_87) {
  Random rng(789);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Uniform(1000000);
    EXPECT_LT(val, 1000000u);
  }
}

// Test OneIn returns true approximately 1/n of the time
TEST_F(RandomTest_87, OneInReturnsTrueApproximately_87) {
  Random rng(101);
  int count = 0;
  const int trials = 10000;
  for (int i = 0; i < trials; i++) {
    if (rng.OneIn(10)) count++;
  }
  // Expect roughly 1000 out of 10000, allow wide margin
  EXPECT_GT(count, 500);
  EXPECT_LT(count, 2000);
}

// Test OneIn with n=1 always returns true
TEST_F(RandomTest_87, OneInWithOneAlwaysTrue_87) {
  Random rng(202);
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(rng.OneIn(1));
  }
}

// Test OneIn with large n rarely returns true
TEST_F(RandomTest_87, OneInWithLargeNRarelyTrue_87) {
  Random rng(303);
  int count = 0;
  for (int i = 0; i < 10000; i++) {
    if (rng.OneIn(10000)) count++;
  }
  // Should be very few (roughly 1), allow some margin
  EXPECT_LT(count, 50);
}

// Test Skewed returns values within expected range [0, 2^max_log - 1]
TEST_F(RandomTest_87, SkewedReturnsValuesInRange_87) {
  Random rng(404);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Skewed(10);
    EXPECT_LT(val, (1u << 10));
  }
}

// Test Skewed with max_log=0 always returns 0
TEST_F(RandomTest_87, SkewedWithZeroMaxLog_87) {
  Random rng(505);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng.Skewed(0), 0u);
  }
}

// Test Skewed with max_log=1 returns 0 or 1
TEST_F(RandomTest_87, SkewedWithOneMaxLog_87) {
  Random rng(606);
  for (int i = 0; i < 1000; i++) {
    uint32_t val = rng.Skewed(1);
    EXPECT_LE(val, 1u);
  }
}

// Test that Next produces different values (not stuck)
TEST_F(RandomTest_87, NextProducesDifferentValues_87) {
  Random rng(707);
  std::set<uint32_t> values;
  for (int i = 0; i < 100; i++) {
    values.insert(rng.Uniform(1000000));
  }
  // Should have many distinct values
  EXPECT_GT(values.size(), 50u);
}

// Test determinism: same seed produces same sequence
TEST_F(RandomTest_87, DeterministicWithSameSeed_87) {
  Random rng1(808);
  Random rng2(808);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(rng1.Uniform(1000), rng2.Uniform(1000));
  }
}

// Test different seeds produce different sequences
TEST_F(RandomTest_87, DifferentSeedsProduceDifferentSequences_87) {
  Random rng1(909);
  Random rng2(910);
  bool all_same = true;
  for (int i = 0; i < 100; i++) {
    if (rng1.Uniform(1000000) != rng2.Uniform(1000000)) {
      all_same = false;
      break;
    }
  }
  EXPECT_FALSE(all_same);
}

// Test seed of 0 works
TEST_F(RandomTest_87, SeedZeroWorks_87) {
  Random rng(0);
  // Just verify it doesn't crash and produces values
  for (int i = 0; i < 100; i++) {
    uint32_t val = rng.Uniform(100);
    EXPECT_LT(val, 100u);
  }
}

// Test seed with large value
TEST_F(RandomTest_87, LargeSeedWorks_87) {
  Random rng(0x7fffffffu);
  for (int i = 0; i < 100; i++) {
    uint32_t val = rng.Uniform(100);
    EXPECT_LT(val, 100u);
  }
}

// Test Uniform produces reasonable distribution (not all same value)
TEST_F(RandomTest_87, UniformDistribution_87) {
  Random rng(1234);
  std::vector<int> buckets(10, 0);
  const int trials = 10000;
  for (int i = 0; i < trials; i++) {
    buckets[rng.Uniform(10)]++;
  }
  // Each bucket should have roughly 1000, check they're all non-zero
  for (int i = 0; i < 10; i++) {
    EXPECT_GT(buckets[i], 0);
    EXPECT_GT(buckets[i], 500);   // At least half of expected
    EXPECT_LT(buckets[i], 2000);  // At most double of expected
  }
}

// Test Skewed tends to produce smaller values more frequently
TEST_F(RandomTest_87, SkewedFavorsSmallValues_87) {
  Random rng(5678);
  int small_count = 0;
  const int trials = 10000;
  for (int i = 0; i < trials; i++) {
    uint32_t val = rng.Skewed(20);
    if (val < 16) small_count++;  // Values < 16 (2^4) should appear often
  }
  // Small values should be more common since lower max_log values are chosen too
  EXPECT_GT(small_count, trials / 4);
}

}  // namespace leveldb
