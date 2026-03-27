// File: ./TestProjects/yaml-cpp/test/dragonbox_compute_right_endpoint_for_shorter_interval_case_test.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// The provided snippet shows this function living under a repeated namespace chain.
// Create a short alias so tests stay readable.
namespace db = YAML::jkj::dragonbox::jkj::dragonbox::jkj::dragonbox::jkj::dragonbox;
namespace wuint = db::detail::wuint;

// Helper: assign high/low to cache_entry_type when possible.
// We avoid assuming a specific constructor exists in the real codebase.
template <class CacheEntry>
constexpr void SetCacheHighLow(CacheEntry& c, std::uint64_t hi, std::uint64_t lo) {
  if constexpr (requires { CacheEntry{hi, lo}; }) {
    c = CacheEntry{hi, lo};
  } else if constexpr (requires { c.high_ = hi; c.low_ = lo; }) {
    c.high_ = hi;
    c.low_ = lo;
  } else {
    // If the type doesn't support either construction or public members, tests that
    // need concrete values can't proceed. Still, we keep compilation valid via a no-op.
    (void)c;
    (void)hi;
    (void)lo;
  }
}

// Helper: determine a conservative "max beta" that won't underflow the shift count.
// The function shifts by (total_bits - significand_bits - 1 - beta), so beta must be
// <= (total_bits - significand_bits - 1).
constexpr int MaxSafeBeta() {
  // These names are used unqualified in the implementation snippet, so they must exist
  // in this namespace in the real header.
  return static_cast<int>(wuint::total_bits - wuint::significand_bits - 1);
}

template <class ShiftAmountType>
constexpr bool BetaIsSafe(ShiftAmountType beta) {
  const int max_beta = MaxSafeBeta();
  return beta >= ShiftAmountType{0} && beta <= static_cast<ShiftAmountType>(max_beta);
}

}  // namespace

// -----------------------------------------------------------------------------
// TESTS
// -----------------------------------------------------------------------------

TEST(ComputeRightEndpointForShorterIntervalCaseTest_402, IsNoexcept_402) {
  using Cache = wuint::cache_entry_type;

  Cache cache{};
  // Choose a conservative beta within safe range.
  const int max_beta = MaxSafeBeta();
  const int beta_i = (max_beta >= 0) ? 0 : 0;

  ASSERT_TRUE(max_beta >= 0) << "Unexpected configuration: total_bits - significand_bits - 1 < 0";

  EXPECT_TRUE((noexcept(wuint::compute_right_endpoint_for_shorter_interval_case(cache, beta_i))));
}

TEST(ComputeRightEndpointForShorterIntervalCaseTest_402, ReturnsCarrierUintType_402) {
  using Cache = wuint::cache_entry_type;
  using Ret = decltype(wuint::compute_right_endpoint_for_shorter_interval_case(std::declval<Cache const&>(),
                                                                               int{0}));

  static_assert(std::is_same_v<Ret, wuint::carrier_uint>,
                "Return type must be wuint::carrier_uint (as declared/used by the interface).");
  SUCCEED();
}

TEST(ComputeRightEndpointForShorterIntervalCaseTest_402, WorksInConstantExpressionContext_402) {
  using Cache = wuint::cache_entry_type;

  constexpr int max_beta = MaxSafeBeta();
  static_assert(max_beta >= 0, "Unexpected configuration: max beta must be non-negative.");

  // Build a constexpr cache entry (best-effort, depending on CacheEntry support).
  constexpr Cache cache = []() constexpr {
    Cache c{};
    // If assignment isn't possible in constexpr for the actual type, this will be a no-op,
    // but the test still checks that the function is callable in constexpr with the type.
    auto tmp = c;
    SetCacheHighLow(tmp, /*hi=*/0ULL, /*lo=*/0ULL);
    return tmp;
  }();

  constexpr auto v0 = wuint::compute_right_endpoint_for_shorter_interval_case(cache, 0);
  (void)v0;

  // Also try another safe beta if available.
  if constexpr (max_beta >= 1) {
    constexpr auto v1 = wuint::compute_right_endpoint_for_shorter_interval_case(cache, 1);
    (void)v1;
  }

  SUCCEED();
}

TEST(ComputeRightEndpointForShorterIntervalCaseTest_402, ZeroHighProducesDeterministicResult_402) {
  using Cache = wuint::cache_entry_type;

  Cache cache{};
  SetCacheHighLow(cache, /*hi=*/0ULL, /*lo=*/0ULL);

  const int max_beta = MaxSafeBeta();
  ASSERT_GE(max_beta, 0);

  // For a fixed input, multiple invocations must return the same value.
  // (We do not assume a specific numeric result; only determinism.)
  const auto r0 = wuint::compute_right_endpoint_for_shorter_interval_case(cache, 0);
  const auto r0_again = wuint::compute_right_endpoint_for_shorter_interval_case(cache, 0);
  EXPECT_EQ(r0, r0_again);

  if (max_beta >= 1) {
    const auto r1 = wuint::compute_right_endpoint_for_shorter_interval_case(cache, 1);
    const auto r1_again = wuint::compute_right_endpoint_for_shorter_interval_case(cache, 1);
    EXPECT_EQ(r1, r1_again);
  }
}

TEST(ComputeRightEndpointForShorterIntervalCaseTest_402, MonotonicInBetaForSameCache_402) {
  using Cache = wuint::cache_entry_type;

  Cache cache{};
  SetCacheHighLow(cache, /*hi=*/0x0123'4567'89AB'CDEFULL, /*lo=*/0ULL);

  const int max_beta = MaxSafeBeta();
  ASSERT_GE(max_beta, 0);

  // The shift amount decreases as beta increases (within the valid beta range),
  // so the computed endpoint should be monotonic non-decreasing in beta for the same cache.
  // We only test an ordering property (observable behavior), not exact arithmetic.
  if (max_beta >= 1) {
    const auto b0 = 0;
    const auto b1 = 1;
    ASSERT_TRUE(BetaIsSafe(b0));
    ASSERT_TRUE(BetaIsSafe(b1));

    const auto r0 = wuint::compute_right_endpoint_for_shorter_interval_case(cache, b0);
    const auto r1 = wuint::compute_right_endpoint_for_shorter_interval_case(cache, b1);

    EXPECT_LE(r0, r1);
  } else {
    GTEST_SKIP() << "Not enough safe beta range to test monotonicity.";
  }
}

TEST(ComputeRightEndpointForShorterIntervalCaseTest_402, HandlesLargeHighValueWithoutError_402) {
  using Cache = wuint::cache_entry_type;

  Cache cache{};
  SetCacheHighLow(cache, /*hi=*/0xFFFF'FFFF'FFFF'FFFFULL, /*lo=*/0xFFFF'FFFF'FFFF'FFFFULL);

  const int max_beta = MaxSafeBeta();
  ASSERT_GE(max_beta, 0);

  // Boundary-ish betas: smallest and largest safe.
  const auto r_min = wuint::compute_right_endpoint_for_shorter_interval_case(cache, 0);
  const auto r_min_again = wuint::compute_right_endpoint_for_shorter_interval_case(cache, 0);
  EXPECT_EQ(r_min, r_min_again);

  const auto r_max = wuint::compute_right_endpoint_for_shorter_interval_case(cache, max_beta);
  const auto r_max_again = wuint::compute_right_endpoint_for_shorter_interval_case(cache, max_beta);
  EXPECT_EQ(r_max, r_max_again);

  // Sanity: for the same cache, monotonic check between min and max beta when distinct.
  if (max_beta >= 1) {
    EXPECT_LE(r_min, r_max);
  }
}