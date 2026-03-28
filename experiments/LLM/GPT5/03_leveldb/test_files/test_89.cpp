// random_skewed_test_89.cc
#include "util/random.h"
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <algorithm>

namespace {

using leveldb::Random;

class RandomTest_89 : public ::testing::Test {};

// Normal operation: values are within the documented return type range and
// an obvious upper bound derived from the argument (observable via outputs).
TEST_F(RandomTest_89, Skewed_ReturnsValueWithinRange_89) {
  Random rnd(12345);

  // Try a variety of max_log values including small and large.
  const int cases[] = {0, 1, 5, 10, 16, 31};
  for (int max_log : cases) {
    for (int i = 0; i < 1000; ++i) {
      uint32_t v = rnd.Skewed(max_log);
      // Always non-negative due to unsigned return type.
      // Upper bound: strictly less than (1u << max_log) for max_log >= 1.
      if (max_log == 0) {
        EXPECT_EQ(0u, v) << "Skewed(0) should always yield 0 (observed result)";
      } else {
        uint32_t bound = (max_log >= 31) ? (1u << 31) : (1u << max_log);
        EXPECT_LT(v, bound) << "Value must be in [0, 2^max_log) for max_log=" << max_log;
      }
    }
  }
}

// Boundary case: max_log = 0 should deterministically produce 0 on every call.
TEST_F(RandomTest_89, Skewed_MaxLogZeroAlwaysZero_89) {
  Random rnd(7);
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(0u, rnd.Skewed(0));
  }
}

// Determinism with seed: two generators with the same seed produce the same sequence.
TEST_F(RandomTest_89, Skewed_DeterministicWithSameSeed_89) {
  Random a(123456789u);
  Random b(123456789u);

  const int max_log = 10;
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(a.Skewed(max_log), b.Skewed(max_log))
        << "Sequences must match for identical seeds at index " << i;
  }
}

// Different seeds: sequences should not be identical (very high probability).
TEST_F(RandomTest_89, Skewed_DifferentSeedsNotAllEqual_89) {
  Random a(1u);
  Random b(2u);

  const int max_log = 12;
  bool any_diff = false;
  for (int i = 0; i < 2000; ++i) {
    if (a.Skewed(max_log) != b.Skewed(max_log)) {
      any_diff = true;
      break;
    }
  }
  // This is a probabilistic check; if it ever fails, it indicates a serious issue.
  EXPECT_TRUE(any_diff) << "Sequences from different seeds unexpectedly matched for all samples.";
}

// Distribution property (observable): results are biased toward smaller values.
// We test that a large majority of samples fall below a mid-range threshold.
TEST_F(RandomTest_89, Skewed_IsBiasedTowardSmallerValues_89) {
  Random rnd(31337u);

  const int max_log = 10;                  // Range target: [0, 2^10)
  const uint32_t half_threshold = 1u << 9; // Midpoint proxy: 2^(max_log-1)
  const int samples = 50000;

  int below_half = 0;
  for (int i = 0; i < samples; ++i) {
    uint32_t v = rnd.Skewed(max_log);
    if (v < half_threshold) below_half++;
  }

  double ratio = static_cast<double>(below_half) / samples;
  // Expect a clear skew: safely require > 0.6 to avoid flakiness.
  EXPECT_GT(ratio, 0.60) << "Observed ratio below 0.5*range was " << ratio
                         << ", expected clear bias toward smaller values.";
}

}  // namespace
