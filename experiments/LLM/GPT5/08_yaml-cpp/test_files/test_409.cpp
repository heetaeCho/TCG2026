// File: ./TestProjects/yaml-cpp/test/dragonbox_right_endpoint_shorter_interval_test_409.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::impl;

// These threshold constants are referenced by impl::is_right_endpoint_integer_shorter_interval()
// in the provided implementation snippet.
using YAML::jkj::dragonbox::detail::case_shorter_interval_right_endpoint_lower_threshold;
using YAML::jkj::dragonbox::detail::case_shorter_interval_right_endpoint_upper_threshold;

class RightEndpointIntegerShorterIntervalTest_409 : public ::testing::Test {};

TEST_F(RightEndpointIntegerShorterIntervalTest_409, IsNoexcept_409) {
  static_assert(
      noexcept(impl::is_right_endpoint_integer_shorter_interval(
          case_shorter_interval_right_endpoint_lower_threshold)),
      "is_right_endpoint_integer_shorter_interval should be noexcept");
}

TEST_F(RightEndpointIntegerShorterIntervalTest_409, LowerThresholdIsTrue_409) {
  EXPECT_TRUE(impl::is_right_endpoint_integer_shorter_interval(
      case_shorter_interval_right_endpoint_lower_threshold));

  // Also validate constexpr-ness in an observable way.
  constexpr bool v = impl::is_right_endpoint_integer_shorter_interval(
      case_shorter_interval_right_endpoint_lower_threshold);
  static_assert(v, "Lower threshold should yield true");
  EXPECT_TRUE(v);
}

TEST_F(RightEndpointIntegerShorterIntervalTest_409, UpperThresholdIsTrue_409) {
  EXPECT_TRUE(impl::is_right_endpoint_integer_shorter_interval(
      case_shorter_interval_right_endpoint_upper_threshold));

  constexpr bool v = impl::is_right_endpoint_integer_shorter_interval(
      case_shorter_interval_right_endpoint_upper_threshold);
  static_assert(v, "Upper threshold should yield true");
  EXPECT_TRUE(v);
}

TEST_F(RightEndpointIntegerShorterIntervalTest_409, BelowLowerThresholdIsFalse_409) {
  // Boundary condition: just below the inclusive lower threshold.
  const auto below = case_shorter_interval_right_endpoint_lower_threshold - 1;
  EXPECT_FALSE(impl::is_right_endpoint_integer_shorter_interval(below));
}

TEST_F(RightEndpointIntegerShorterIntervalTest_409, AboveUpperThresholdIsFalse_409) {
  // Boundary condition: just above the inclusive upper threshold.
  const auto above = case_shorter_interval_right_endpoint_upper_threshold + 1;
  EXPECT_FALSE(impl::is_right_endpoint_integer_shorter_interval(above));
}

TEST_F(RightEndpointIntegerShorterIntervalTest_409, MidpointWithinRangeIsTrue_409) {
  // Normal operation: choose a value inside [lower, upper] if the range is non-empty.
  const auto lower = case_shorter_interval_right_endpoint_lower_threshold;
  const auto upper = case_shorter_interval_right_endpoint_upper_threshold;

  // If lower == upper, midpoint is that same value and should still be true.
  const auto mid = lower + (upper - lower) / 2;
  EXPECT_TRUE(impl::is_right_endpoint_integer_shorter_interval(mid));
}

TEST_F(RightEndpointIntegerShorterIntervalTest_409, WorksForFarOutOfRangeValues_409) {
  // Error/robustness style checks: far below/above should be false.
  const auto lower = case_shorter_interval_right_endpoint_lower_threshold;
  const auto upper = case_shorter_interval_right_endpoint_upper_threshold;

  EXPECT_FALSE(impl::is_right_endpoint_integer_shorter_interval(lower - 1000));
  EXPECT_FALSE(impl::is_right_endpoint_integer_shorter_interval(upper + 1000));
}

}  // namespace