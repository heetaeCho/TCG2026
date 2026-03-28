// File: test_dragonbox_log_is_in_range_316.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

namespace db = YAML::jkj::dragonbox;
namespace logns = YAML::jkj::dragonbox::detail::log;
namespace stdr = YAML::jkj::dragonbox::detail::stdr;

// Test-only Info provider for tiers.
template <stdr::size_t Tier>
struct TestInfo;

template <>
struct TestInfo<0> {
  static constexpr stdr::int_least32_t min_exponent = -10;
  static constexpr stdr::int_least32_t max_exponent = 10;
};

template <>
struct TestInfo<1> {
  static constexpr stdr::int_least32_t min_exponent = -100;
  static constexpr stdr::int_least32_t max_exponent = 100;
};

class IsInRangeTest_316 : public ::testing::Test {};

}  // namespace

TEST_F(IsInRangeTest_316, ReturnsTrueWhenMinAndMaxWithinSupportedRange_316) {
  // Tier 0 supports [-10, 10]
  constexpr bool in_range =
      logns::is_in_range<TestInfo, -10, 10, /*current_tier=*/0>(0);
  EXPECT_TRUE(in_range);

  constexpr bool also_in_range =
      logns::is_in_range<TestInfo, -5, 0, /*current_tier=*/0>(123);
  EXPECT_TRUE(also_in_range);
}

TEST_F(IsInRangeTest_316, ReturnsTrueOnBoundaryEquality_316) {
  // Equality at both ends should be considered "in range" based on the interface's comparisons.
  constexpr bool min_eq =
      logns::is_in_range<TestInfo, -10, 0, /*current_tier=*/0>(0);
  constexpr bool max_eq =
      logns::is_in_range<TestInfo, 0, 10, /*current_tier=*/0>(0);
  constexpr bool both_eq =
      logns::is_in_range<TestInfo, -10, 10, /*current_tier=*/0>(0);

  EXPECT_TRUE(min_eq);
  EXPECT_TRUE(max_eq);
  EXPECT_TRUE(both_eq);
}

TEST_F(IsInRangeTest_316, ReturnsFalseWhenMinExponentBelowSupportedMin_316) {
  // Tier 0 supports min_exponent >= -10
  constexpr bool out_of_range =
      logns::is_in_range<TestInfo, -11, 0, /*current_tier=*/0>(0);
  EXPECT_FALSE(out_of_range);
}

TEST_F(IsInRangeTest_316, ReturnsFalseWhenMaxExponentAboveSupportedMax_316) {
  // Tier 0 supports max_exponent <= 10
  constexpr bool out_of_range =
      logns::is_in_range<TestInfo, 0, 11, /*current_tier=*/0>(0);
  EXPECT_FALSE(out_of_range);
}

TEST_F(IsInRangeTest_316, UsesCurrentTierToDetermineSupportedRange_316) {
  // Same requested range, different tier => potentially different result.
  // Tier 0 supports [-10, 10], tier 1 supports [-100, 100].
  constexpr bool tier0_result =
      logns::is_in_range<TestInfo, -50, 50, /*current_tier=*/0>(0);
  constexpr bool tier1_result =
      logns::is_in_range<TestInfo, -50, 50, /*current_tier=*/1>(0);

  EXPECT_FALSE(tier0_result);
  EXPECT_TRUE(tier1_result);
}

TEST_F(IsInRangeTest_316, ResultIsConsistentAcrossDifferentRuntimeArguments_316) {
  // The interface takes an int parameter; verify observable behavior is consistent
  // for different passed values for the same template instantiation.
  const bool r1 = logns::is_in_range<TestInfo, -10, 10, /*current_tier=*/0>(0);
  const bool r2 = logns::is_in_range<TestInfo, -10, 10, /*current_tier=*/0>(-1);
  const bool r3 = logns::is_in_range<TestInfo, -10, 10, /*current_tier=*/0>(999);

  EXPECT_EQ(r1, r2);
  EXPECT_EQ(r2, r3);
}

TEST_F(IsInRangeTest_316, IsNoexcept_316) {
  // Observable contract: function is declared noexcept.
  EXPECT_TRUE((noexcept(logns::is_in_range<TestInfo, -10, 10, /*current_tier=*/0>(0))));
}

// Optional compile-time checks to ensure constexpr usability (still black-box: no logic re-implementation).
static_assert(logns::is_in_range<TestInfo, -10, 10, /*current_tier=*/0>(0),
              "Expected to be in range at compile time.");
static_assert(!logns::is_in_range<TestInfo, -11, 10, /*current_tier=*/0>(0),
              "Expected to be out of range at compile time.");