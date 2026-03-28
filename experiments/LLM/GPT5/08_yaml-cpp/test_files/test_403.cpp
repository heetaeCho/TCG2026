// TEST_ID: 403
// File: dragonbox_compute_round_up_for_shorter_interval_case_test_403.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// Adjust include path as needed for your build setup.
#include "contrib/dragonbox.h"

namespace {

namespace db403 = YAML::jkj::dragonbox::detail::wuint;

// A tiny “reference expression” that matches the publicly visible formula in the provided snippet.
// Note: This does NOT inspect any private state; it only uses the public interface (cache.high())
// and public/visible constants/types from the header.
template <class ShiftAmountType>
constexpr db403::carrier_uint RefCompute403(const db403::cache_entry_type& cache,
                                            ShiftAmountType beta) {
  return ((cache.high() >>
           ShiftAmountType(db403::total_bits - db403::significand_bits - 2 - beta)) +
          1) /
         2;
}

class ComputeRoundUpForShorterIntervalCaseTest_403 : public ::testing::Test {
 protected:
  static constexpr db403::cache_entry_type MakeCache(std::uint64_t high,
                                                     std::uint64_t low = 0) {
    // cache_entry_type is expected to be constructible from (high, low) in this header family.
    // If your project uses a different cache_entry_type shape, adapt this helper accordingly.
    return db403::cache_entry_type{high, low};
  }
};

TEST_F(ComputeRoundUpForShorterIntervalCaseTest_403, IsNoexcept_403) {
  const auto cache = MakeCache(0, 0);

  EXPECT_TRUE(noexcept(db403::compute_round_up_for_shorter_interval_case(cache, std::uint32_t{0})));
  EXPECT_TRUE(noexcept(db403::compute_round_up_for_shorter_interval_case(cache, std::uint64_t{1})));
}

TEST_F(ComputeRoundUpForShorterIntervalCaseTest_403, WorksAsConstexpr_403) {
  constexpr auto cache = db403::cache_entry_type{0u, 0u};
  constexpr std::uint32_t beta = 0;

  constexpr auto v = db403::compute_round_up_for_shorter_interval_case(cache, beta);
  static_assert(std::is_same_v<decltype(v), const db403::carrier_uint>, "Return type must be carrier_uint");
  (void)v;

  SUCCEED();
}

TEST_F(ComputeRoundUpForShorterIntervalCaseTest_403, ComputesExpectedForBetaZero_403) {
  const auto cache = MakeCache(/*high=*/0x0123456789ABCDEFull, /*low=*/0);

  const std::uint32_t beta = 0;
  const auto actual = db403::compute_round_up_for_shorter_interval_case(cache, beta);
  const auto expected = RefCompute403(cache, beta);

  EXPECT_EQ(actual, expected);
}

TEST_F(ComputeRoundUpForShorterIntervalCaseTest_403, ComputesExpectedForSmallBetas_403) {
  const auto cache = MakeCache(/*high=*/0xFEDCBA9876543210ull, /*low=*/0);

  for (std::uint32_t beta : {0u, 1u, 2u, 3u}) {
    const auto actual = db403::compute_round_up_for_shorter_interval_case(cache, beta);
    const auto expected = RefCompute403(cache, beta);
    EXPECT_EQ(actual, expected) << "beta=" << beta;
  }
}

TEST_F(ComputeRoundUpForShorterIntervalCaseTest_403, HandlesZeroHighValue_403) {
  const auto cache = MakeCache(/*high=*/0ull, /*low=*/0ull);

  for (std::uint32_t beta : {0u, 1u, 2u}) {
    const auto actual = db403::compute_round_up_for_shorter_interval_case(cache, beta);
    const auto expected = RefCompute403(cache, beta);
    EXPECT_EQ(actual, expected) << "beta=" << beta;
  }
}

TEST_F(ComputeRoundUpForShorterIntervalCaseTest_403, HandlesMaxHighValue_403) {
  const auto cache = MakeCache(/*high=*/0xFFFFFFFFFFFFFFFFull, /*low=*/0ull);

  for (std::uint32_t beta : {0u, 1u, 2u, 3u}) {
    const auto actual = db403::compute_round_up_for_shorter_interval_case(cache, beta);
    const auto expected = RefCompute403(cache, beta);
    EXPECT_EQ(actual, expected) << "beta=" << beta;
  }
}

TEST_F(ComputeRoundUpForShorterIntervalCaseTest_403, AcceptsDifferentShiftAmountTypes_403) {
  const auto cache = MakeCache(/*high=*/0x1111222233334444ull, /*low=*/0ull);

  const auto actual_u32 = db403::compute_round_up_for_shorter_interval_case(cache, std::uint32_t{1});
  const auto expected_u32 = RefCompute403(cache, std::uint32_t{1});
  EXPECT_EQ(actual_u32, expected_u32);

  const auto actual_u64 = db403::compute_round_up_for_shorter_interval_case(cache, std::uint64_t{1});
  const auto expected_u64 = RefCompute403(cache, std::uint64_t{1});
  EXPECT_EQ(actual_u64, expected_u64);
}

}  // namespace