// File: dragonbox_away_from_zero_t_test.cpp
//
// Unit tests for:
// YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::away_from_zero_t
//
// Constraints honored:
// - Treat as black box: only test observable behavior via public interface.
// - No private/internal access.
// - Verify return values, constexpr usability, and noexcept (observable via type traits).

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Policy =
    YAML::jkj::dragonbox::policy::binary_to_decimal_rounding::away_from_zero_t;

class AwayFromZeroRoundingPolicyTest_388 : public ::testing::Test {};

TEST_F(AwayFromZeroRoundingPolicyTest_388,
       PreferRoundDownReturnsFalseForTypicalValues_388) {
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{0}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{1}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{42}));

  EXPECT_FALSE(Policy::prefer_round_down(std::uint64_t{0}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint64_t{1}));
  EXPECT_FALSE(Policy::prefer_round_down(std::uint64_t{42}));
}

TEST_F(AwayFromZeroRoundingPolicyTest_388,
       PreferRoundDownReturnsFalseAtBoundaries_388) {
  EXPECT_FALSE(Policy::prefer_round_down(std::uint32_t{0}));
  EXPECT_FALSE(
      Policy::prefer_round_down(std::numeric_limits<std::uint32_t>::max()));

  EXPECT_FALSE(Policy::prefer_round_down(std::uint64_t{0}));
  EXPECT_FALSE(
      Policy::prefer_round_down(std::numeric_limits<std::uint64_t>::max()));
}

TEST_F(AwayFromZeroRoundingPolicyTest_388, PreferRoundDownIsNoexcept_388) {
  static_assert(noexcept(Policy::prefer_round_down(std::uint32_t{0})),
                "prefer_round_down(uint32_t) must be noexcept");
  static_assert(noexcept(Policy::prefer_round_down(std::uint64_t{0})),
                "prefer_round_down(uint64_t) must be noexcept");

  SUCCEED();
}

TEST_F(AwayFromZeroRoundingPolicyTest_388, PreferRoundDownReturnsBool_388) {
  static_assert(
      std::is_same_v<decltype(Policy::prefer_round_down(std::uint32_t{0})),
                     bool>,
      "prefer_round_down must return bool");
  static_assert(
      std::is_same_v<decltype(Policy::prefer_round_down(std::uint64_t{0})),
                     bool>,
      "prefer_round_down must return bool");

  SUCCEED();
}

TEST_F(AwayFromZeroRoundingPolicyTest_388,
       PreferRoundDownIsConstexprUsable_388) {
  constexpr bool v32 = Policy::prefer_round_down(std::uint32_t{123});
  constexpr bool v64 = Policy::prefer_round_down(std::uint64_t{456});

  static_assert(v32 == false, "constexpr evaluation must match runtime result");
  static_assert(v64 == false, "constexpr evaluation must match runtime result");

  EXPECT_FALSE(v32);
  EXPECT_FALSE(v64);
}

TEST_F(AwayFromZeroRoundingPolicyTest_388,
       PreferRoundDownWorksForOtherUnsignedCarrierTypes_388) {
  // The interface is templated; verify it can be instantiated with other
  // unsigned integer carrier types and behaves consistently.
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<unsigned char>(0)));
  EXPECT_FALSE(Policy::prefer_round_down(static_cast<unsigned char>(255)));

  EXPECT_FALSE(Policy::prefer_round_down(static_cast<unsigned long long>(0)));
  EXPECT_FALSE(Policy::prefer_round_down(
      std::numeric_limits<unsigned long long>::max()));
}

}  // namespace