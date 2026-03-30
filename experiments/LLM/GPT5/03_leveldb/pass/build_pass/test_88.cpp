// random_onein_test_88.cc
#include "util/random.h"

#include <gtest/gtest.h>
#include <limits>

namespace {

using leveldb::Random;

class RandomTest_88 : public ::testing::Test {};

// Normal operation: with n == 1, result must always be true.
TEST_F(RandomTest_88, OneInAlwaysTrueWhenNIs1_88) {
  Random rng(12345);
  for (int i = 0; i < 1000; ++i) {
    EXPECT_TRUE(rng.OneIn(1)) << "OneIn(1) should always be true";
  }
}

// Determinism with the same seed: sequences should match exactly.
TEST_F(RandomTest_88, DeterministicSequenceSameSeed_88) {
  Random rng1(98765);
  Random rng2(98765);
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(rng1.OneIn(7), rng2.OneIn(7)) << "Sequences must match for same seed";
  }
}

// Different seeds: sequences should not be identical for many trials.
// (We only assert that at least one outcome differs to avoid flakiness.)
TEST_F(RandomTest_88, DifferentSeedsYieldDifferentSequence_88) {
  Random rng1(1);
  Random rng2(2);

  int diff_count = 0;
  for (int i = 0; i < 200; ++i) {
    bool a = rng1.OneIn(7);
    bool b = rng2.OneIn(7);
    if (a != b) ++diff_count;
  }
  EXPECT_GT(diff_count, 0) << "Expected at least one differing outcome with different seeds";
}

// Boundary / large-n: calling with a very large n should not crash and returns a bool.
TEST_F(RandomTest_88, HandlesVeryLargeNWithoutCrash_88) {
  Random rng(123);
  const int large_n = std::numeric_limits<int>::max();
  // Just exercise the call several times to ensure it’s safe to invoke.
  for (int i = 0; i < 100; ++i) {
    // The value is a bool; any value (true/false) is acceptable as observable behavior.
    (void)rng.OneIn(large_n);
  }
}

// Exceptional / error case observable through the interface: n == 0.
// Expect process death (e.g., divide-by-zero) when OneIn(0) is invoked.
#if GTEST_HAS_DEATH_TEST
TEST_F(RandomTest_88, OneInZeroTriggersDeath_88) {
  EXPECT_DEATH(
      {
        Random rng(42);
        // Intentionally invoke with 0 to validate observable exceptional behavior.
        (void)rng.OneIn(0);
      },
      ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
