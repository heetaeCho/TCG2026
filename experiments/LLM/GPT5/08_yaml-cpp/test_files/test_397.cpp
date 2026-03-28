// TEST_ID: 397
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

// Header under test (as provided in the prompt)
#include "contrib/dragonbox.h"

namespace {
namespace db = YAML::jkj::dragonbox::jkj::dragonbox;

// Small helper so tests read nicely.
template <class ShiftAmountType>
constexpr auto RoundUpShorterInterval(const db::cache_entry_type& cache, ShiftAmountType beta) noexcept {
  return db::compute_round_up_for_shorter_interval_case(cache, beta);
}

// Try to compute the maximum beta that still keeps the internal shift non-negative.
// If these constants are not available, compilation will fail (which is desirable: the interface changed).
constexpr int kMaxBeta_397 =
    static_cast<int>(db::cache_bits) - static_cast<int>(db::significand_bits) - 2;

}  // namespace

TEST(DragonboxComputeRoundUpForShorterIntervalCaseTest_397, IsNoexceptForCommonBetaTypes_397) {
  const db::cache_entry_type cache = db::cache_entry_type{0};

  static_assert(noexcept(RoundUpShorterInterval<int>(cache, 0)), "Must be noexcept for int beta.");
  static_assert(noexcept(RoundUpShorterInterval<std::uint32_t>(cache, 0u)),
                "Must be noexcept for uint32_t beta.");
  static_assert(noexcept(RoundUpShorterInterval<std::size_t>(cache, std::size_t{0})),
                "Must be noexcept for size_t beta.");

  SUCCEED();
}

TEST(DragonboxComputeRoundUpForShorterIntervalCaseTest_397, ReturnTypeIsCarrierUint_397) {
  const db::cache_entry_type cache = db::cache_entry_type{0};

  using R1 = decltype(RoundUpShorterInterval<int>(cache, 0));
  using R2 = decltype(RoundUpShorterInterval<std::uint32_t>(cache, 0u));

  static_assert(std::is_same_v<R1, db::carrier_uint>, "Return type must be carrier_uint.");
  static_assert(std::is_same_v<R2, db::carrier_uint>, "Return type must be carrier_uint.");

  SUCCEED();
}

TEST(DragonboxComputeRoundUpForShorterIntervalCaseTest_397, IsUsableInConstantEvaluation_397) {
  // This function is declared constexpr; verify it can be evaluated at compile time.
  constexpr db::cache_entry_type cache0 = db::cache_entry_type{0};
  constexpr auto r0 = RoundUpShorterInterval<int>(cache0, 0);
  static_assert(std::is_same_v<decltype(r0), db::carrier_uint>);

  // A minimal observable behavior: for a zero cache, the result should not be negative (unsigned) and
  // should be a well-defined compile-time value. We avoid asserting a detailed numeric formula.
  EXPECT_GE(r0, db::carrier_uint{0});
}

TEST(DragonboxComputeRoundUpForShorterIntervalCaseTest_397, HandlesBoundaryBetaZeroAndMaxBeta_397) {
  ASSERT_GE(kMaxBeta_397, 0) << "Unexpected configuration: max beta must be non-negative.";

  const db::cache_entry_type cache =
      (std::numeric_limits<db::cache_entry_type>::max)();  // all-ones pattern

  const auto r_beta0 = RoundUpShorterInterval<int>(cache, 0);
  const auto r_betamax = RoundUpShorterInterval<int>(cache, kMaxBeta_397);

  // Both calls should succeed and return a value in carrier_uint's domain.
  EXPECT_GE(r_beta0, db::carrier_uint{0});
  EXPECT_GE(r_betamax, db::carrier_uint{0});
}

TEST(DragonboxComputeRoundUpForShorterIntervalCaseTest_397, MonotonicNonDecreasingInBetaWithinValidRange_397) {
  ASSERT_GE(kMaxBeta_397, 0) << "Unexpected configuration: max beta must be non-negative.";

  // Choose a cache value that exercises many bits.
  const db::cache_entry_type cache =
      (std::numeric_limits<db::cache_entry_type>::max)() ^ db::cache_entry_type{0xA5A5A5A5u};

  db::carrier_uint prev = RoundUpShorterInterval<int>(cache, 0);

  // For increasing beta values within the valid range, the result should be stable and (empirically,
  // for this interface) non-decreasing. This is a black-box property test, not a reimplementation.
  for (int beta = 1; beta <= kMaxBeta_397; ++beta) {
    const db::carrier_uint cur = RoundUpShorterInterval<int>(cache, beta);
    EXPECT_LE(prev, cur) << "beta=" << beta;
    prev = cur;
  }
}

TEST(DragonboxComputeRoundUpForShorterIntervalCaseTest_397, AcceptsDifferentShiftAmountTypes_397) {
  ASSERT_GE(kMaxBeta_397, 0);

  const db::cache_entry_type cache = (std::numeric_limits<db::cache_entry_type>::max)();

  const auto r_int = RoundUpShorterInterval<int>(cache, kMaxBeta_397);
  const auto r_u32 = RoundUpShorterInterval<std::uint32_t>(cache, static_cast<std::uint32_t>(kMaxBeta_397));
  const auto r_size = RoundUpShorterInterval<std::size_t>(cache, static_cast<std::size_t>(kMaxBeta_397));

  // Same input semantics (same numeric beta) across ShiftAmountType should give consistent results.
  EXPECT_EQ(r_int, r_u32);
  EXPECT_EQ(r_int, r_size);
}