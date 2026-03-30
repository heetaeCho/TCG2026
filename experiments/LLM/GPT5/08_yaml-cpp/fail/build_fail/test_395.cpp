// TEST_ID: 395
// File: dragonbox_compute_left_endpoint_for_shorter_interval_case_test_395.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// The function is nested under duplicated namespaces in the provided header snippet:
// YAML::jkj::dragonbox::jkj::dragonbox::compute_left_endpoint_for_shorter_interval_case
namespace dragonbox_ns = ::YAML::jkj::dragonbox::jkj::dragonbox;

using CacheEntry = dragonbox_ns::cache_entry_type;
using CarrierUInt = dragonbox_ns::carrier_uint;

// NOTE: This helper computes an "expected" value using the same publicly visible
// header expression (treated as the specification for this unit test).
// It is written defensively with wide intermediate types to reduce risk of overflow.
template <class ShiftAmountType>
constexpr CarrierUInt Expected(CacheEntry cache, ShiftAmountType beta) {
  // Compute: (cache - (cache >> (significand_bits + 2))) >> (cache_bits - significand_bits - 1 - beta)
  // using the same named constants/types from the header.
  const CacheEntry sub = CacheEntry(cache - CacheEntry(cache >> (dragonbox_ns::significand_bits + 2)));
  const ShiftAmountType shift =
      ShiftAmountType(dragonbox_ns::cache_bits - dragonbox_ns::significand_bits - 1 - beta);
  return CarrierUInt(sub >> shift);
}

constexpr int kMaxSafeBeta =
    int(dragonbox_ns::cache_bits - dragonbox_ns::significand_bits - 1);

}  // namespace

TEST(ComputeLeftEndpointForShorterIntervalCaseTest_395, IsNoexcept_395) {
  // Pick a safe beta in range.
  constexpr int beta = 0;
  constexpr CacheEntry cache = CacheEntry{1};

  static_assert(
      noexcept(dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<int>(cache, beta)),
      "compute_left_endpoint_for_shorter_interval_case should be noexcept.");

  SUCCEED();
}

TEST(ComputeLeftEndpointForShorterIntervalCaseTest_395, IsConstexprEvaluable_395) {
  constexpr CacheEntry cache = CacheEntry{0x123456789abcdef0ull};
  constexpr int beta = 0;

  constexpr CarrierUInt v =
      dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<int>(cache, beta);

  // Basic sanity: constexpr computed value is a valid CarrierUInt.
  static_assert(std::is_same_v<decltype(v), const CarrierUInt>, "Return type mismatch.");
  SUCCEED();
}

TEST(ComputeLeftEndpointForShorterIntervalCaseTest_395, HandlesBetaAtLowerBound_395) {
  const CacheEntry cache = CacheEntry{0xdeadbeefcafebabeull};
  const int beta = 0;

  const CarrierUInt got =
      dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<int>(cache, beta);
  const CarrierUInt expected = Expected<int>(cache, beta);

  EXPECT_EQ(got, expected);
}

TEST(ComputeLeftEndpointForShorterIntervalCaseTest_395, HandlesBetaAtUpperBoundShiftZero_395) {
  ASSERT_GE(kMaxSafeBeta, 0);

  const CacheEntry cache = CacheEntry{0x0123456789abcdefull};
  const int beta = kMaxSafeBeta;  // makes shift count zero

  const CarrierUInt got =
      dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<int>(cache, beta);
  const CarrierUInt expected = Expected<int>(cache, beta);

  EXPECT_EQ(got, expected);
}

TEST(ComputeLeftEndpointForShorterIntervalCaseTest_395, WorksWithDifferentShiftAmountTypes_395) {
  const CacheEntry cache = CacheEntry{0xfedcba9876543210ull};
  const int beta_i = 3;
  const unsigned beta_u = 3u;
  const std::uint32_t beta_u32 = 3u;

  const CarrierUInt got_i =
      dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<int>(cache, beta_i);
  const CarrierUInt got_u =
      dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<unsigned>(cache, beta_u);
  const CarrierUInt got_u32 =
      dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<std::uint32_t>(cache, beta_u32);

  // All should match when the numeric beta value matches.
  EXPECT_EQ(got_i, got_u);
  EXPECT_EQ(got_i, got_u32);
}

TEST(ComputeLeftEndpointForShorterIntervalCaseTest_395, RepresentativeValuesMatchSpecification_395) {
  // Use a few representative cache values and safe betas.
  struct Case {
    CacheEntry cache;
    int beta;
  };

  const Case cases[] = {
      {CacheEntry{0ull}, 0},
      {CacheEntry{1ull}, 0},
      {CacheEntry{std::numeric_limits<std::uint64_t>::max()}, 0},
      {CacheEntry{0x8000000000000000ull}, 1},
      {CacheEntry{0x7fffffffffffffffull}, 2},
      {CacheEntry{0x1111111111111111ull}, 3},
      {CacheEntry{0xaaaaaaaaaaaaaaaaull}, 4},
      {CacheEntry{0x0123456789abcdefull}, 5},
  };

  for (const auto& tc : cases) {
    if (tc.beta < 0 || tc.beta > kMaxSafeBeta) {
      continue;  // keep the test within well-defined shift ranges
    }
    const CarrierUInt got =
        dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<int>(tc.cache, tc.beta);
    const CarrierUInt expected = Expected<int>(tc.cache, tc.beta);

    EXPECT_EQ(got, expected) << "cache=" << static_cast<unsigned long long>(tc.cache)
                             << " beta=" << tc.beta;
  }
}

TEST(ComputeLeftEndpointForShorterIntervalCaseTest_395, DeterministicForSameInputs_395) {
  const CacheEntry cache = CacheEntry{0x4242424242424242ull};
  const int beta = 2;

  const CarrierUInt a =
      dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<int>(cache, beta);
  const CarrierUInt b =
      dragonbox_ns::compute_left_endpoint_for_shorter_interval_case<int>(cache, beta);

  EXPECT_EQ(a, b);
}