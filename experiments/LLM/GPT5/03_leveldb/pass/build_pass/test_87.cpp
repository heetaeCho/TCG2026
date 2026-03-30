// random_uniform_test_87.cc
#include <gtest/gtest.h>
#include "util/random.h"

namespace {

using leveldb::Random;

// Basic range property for typical n
TEST(RandomTest_87, ReturnsInRange_87) {
  Random rng(12345);
  const int n = 10;
  for (int i = 0; i < 10000; ++i) {
    uint32_t v = rng.Uniform(n);
    EXPECT_LT(v, static_cast<uint32_t>(n));
  }
}

// Boundary: n == 1 must always return 0
TEST(RandomTest_87, ReturnsZeroWhenNIsOne_87) {
  Random rng(98765);
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(0u, rng.Uniform(1));
  }
}

// Determinism: same seed => identical sequence for the same n
TEST(RandomTest_87, DeterministicWithSameSeed_87) {
  const uint32_t seed = 13579;
  Random a(seed);
  Random b(seed);

  const int n = 1000;
  for (int i = 0; i < 2000; ++i) {
    EXPECT_EQ(a.Uniform(n), b.Uniform(n));
  }
}

// Sanity: different seeds should yield a different sequence (very likely).
// We only require that at least one of the first K values differs to avoid flakiness.
TEST(RandomTest_87, DifferentSeedsOftenDiffer_87) {
  Random a(1);
  Random b(2);

  const int n = 1000;
  bool any_diff = false;
  for (int i = 0; i < 2000; ++i) {
    if (a.Uniform(n) != b.Uniform(n)) {
      any_diff = true;
      break;
    }
  }
  EXPECT_TRUE(any_diff);
}

// Large-n boundary within int range
TEST(RandomTest_87, HandlesLargeN_87) {
  Random rng(424242);
  const int n = 2000000000; // 2e9, valid positive int
  for (int i = 0; i < 2000; ++i) {
    uint32_t v = rng.Uniform(n);
    // v should be in [0, n-1]
    ASSERT_LT(v, static_cast<uint32_t>(n));
  }
}

// Note on exceptional cases:
// Passing n <= 0 would make the result undefined for a modulo operation.
// Because the interface does not define behavior for n <= 0 and there is no
// documented error signaling, we intentionally avoid asserting any behavior.
// If your build defines a contract (e.g., debug assert), you may enable a death test:
//
// DISABLED example:
// TEST(RandomTest_87, DISABLED_UniformZeroIsUndefined_87) {
//   Random rng(7);
//   EXPECT_DEATH({ (void)rng.Uniform(0); }, ".*");
// }

}  // namespace
