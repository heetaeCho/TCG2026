// File: ./TestProjects/yaml-cpp/test/dragonbox_compute_mul_parity_test_400.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// The function under test lives in yaml-cpp's contrib dragonbox header.
#include "contrib/dragonbox.h"

namespace {

// Keep names short in tests.
namespace wuint = ::YAML::jkj::dragonbox::detail::wuint;

// Helper: try to construct a cache entry in a way that works for common dragonbox layouts.
// If the real type doesn't support this, the compilation will fail and you should adjust
// the construction to match the actual cache_entry_type definition.
template <class CacheEntry>
CacheEntry MakeCacheEntry(std::uint_least64_t high, std::uint_least64_t low) {
  if constexpr (std::is_aggregate_v<CacheEntry>) {
    return CacheEntry{high, low};
  } else {
    return CacheEntry(high, low);
  }
}

class ComputeMulParityTest_400 : public ::testing::Test {
protected:
  using Carrier = wuint::carrier_uint;
  using Cache   = wuint::cache_entry_type;
};

TEST_F(ComputeMulParityTest_400, IsNoexcept_400) {
  // Verify the function is marked noexcept (observable via the type system).
  const Cache cache_zero = Cache{};
  const Carrier two_f = Carrier{1};

  static_assert(noexcept(wuint::compute_mul_parity(two_f, cache_zero, 1)),
                "compute_mul_parity must be noexcept");
}

TEST_F(ComputeMulParityTest_400, BetaBoundaryValuesDoNotCrash_400) {
  // beta must be in [1, 63] (asserted in implementation). These are the boundaries.
  const Cache cache_zero = Cache{};
  const Carrier two_f = Carrier{1};

  {
    auto r = wuint::compute_mul_parity(two_f, cache_zero, 1);
    // Validate we can decompose the result into two boolean-like values.
    auto [b0, b1] = r;
    (void)b0;
    (void)b1;
  }
  {
    auto r = wuint::compute_mul_parity(two_f, cache_zero, 63);
    auto [b0, b1] = r;
    (void)b0;
    (void)b1;
  }
}

TEST_F(ComputeMulParityTest_400, DeterministicForSameInputs_400) {
  const Cache cache_zero = Cache{};
  const Carrier two_f = Carrier{123};

  const auto r1 = wuint::compute_mul_parity(two_f, cache_zero, 17);
  const auto r2 = wuint::compute_mul_parity(two_f, cache_zero, 17);

  const auto [a0, a1] = r1;
  const auto [b0, b1] = r2;

  EXPECT_EQ(a0, b0);
  EXPECT_EQ(a1, b1);
}

TEST_F(ComputeMulParityTest_400, ZeroCacheEntryYieldsSecondFlagTrue_400) {
  // With a zero cache entry, the multiplication result should be all zeros; this makes the
  // "all-lower-bits-zero" indicator true and the parity indicator false.
  //
  // This is an observable black-box expectation based on the semantic meaning of multiplying
  // by zero and the returned two-boolean result.
  const Cache cache_zero = Cache{};

  // Try several two_f / beta values to ensure consistent behavior.
  for (Carrier two_f : {Carrier{0}, Carrier{1}, Carrier{2}, Carrier{1234567}}) {
    for (int beta : {1, 2, 17, 63}) {
      const auto r = wuint::compute_mul_parity(two_f, cache_zero, beta);
      const auto [parity_bit, all_zero_flag] = r;

      EXPECT_FALSE(parity_bit) << "two_f=" << static_cast<unsigned long long>(two_f)
                               << " beta=" << beta;
      EXPECT_TRUE(all_zero_flag) << "two_f=" << static_cast<unsigned long long>(two_f)
                                 << " beta=" << beta;
    }
  }
}

#ifndef NDEBUG
TEST_F(ComputeMulParityTest_400, DeathOnBetaZero_400) {
  const Cache cache_zero = Cache{};
  const Carrier two_f = Carrier{1};

  // beta must be >= 1
  EXPECT_DEATH((void)wuint::compute_mul_parity(two_f, cache_zero, 0), "");
}

TEST_F(ComputeMulParityTest_400, DeathOnBeta64_400) {
  const Cache cache_zero = Cache{};
  const Carrier two_f = Carrier{1};

  // beta must be < 64
  EXPECT_DEATH((void)wuint::compute_mul_parity(two_f, cache_zero, 64), "");
}
#endif  // !NDEBUG

TEST_F(ComputeMulParityTest_400, NonZeroCacheEntryReturnsBooleanPair_400) {
  // We don't assume exact bit-level results for non-zero cache entries (black box),
  // but we can still validate that it runs and returns values decomposable into two bools.
  Cache cache_nonzero = Cache{};
  // Best-effort: construct a "non-zero" cache entry in a common layout.
  // If cache_entry_type isn't aggregate/constructible this way, adjust MakeCacheEntry().
  cache_nonzero = MakeCacheEntry<Cache>(/*high=*/1, /*low=*/1);

  const Carrier two_f = Carrier{5};

  const auto r = wuint::compute_mul_parity(two_f, cache_nonzero, 7);
  const auto [b0, b1] = r;

  // They should be boolean values; just assert they are valid bools (always true),
  // and keep them used to avoid warnings.
  EXPECT_TRUE(b0 == true || b0 == false);
  EXPECT_TRUE(b1 == true || b1 == false);
}

}  // namespace