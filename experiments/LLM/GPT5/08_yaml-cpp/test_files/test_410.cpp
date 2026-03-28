// TEST_ID: 410
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using Impl = YAML::jkj::dragonbox::detail::impl;

class DragonboxLeftEndpointShorterIntervalTest_410 : public ::testing::Test {};

TEST_F(DragonboxLeftEndpointShorterIntervalTest_410, IsNoexcept_410) {
  static_assert(noexcept(Impl::is_left_endpoint_integer_shorter_interval(
      Impl::case_shorter_interval_left_endpoint_lower_threshold)));
  EXPECT_NO_THROW({
    (void)Impl::is_left_endpoint_integer_shorter_interval(
        Impl::case_shorter_interval_left_endpoint_lower_threshold);
  });
}

TEST_F(DragonboxLeftEndpointShorterIntervalTest_410, ReturnsTrueAtLowerThreshold_410) {
  const auto lower = Impl::case_shorter_interval_left_endpoint_lower_threshold;
  EXPECT_TRUE(Impl::is_left_endpoint_integer_shorter_interval(lower));
}

TEST_F(DragonboxLeftEndpointShorterIntervalTest_410, ReturnsTrueAtUpperThreshold_410) {
  const auto upper = Impl::case_shorter_interval_left_endpoint_upper_threshold;
  EXPECT_TRUE(Impl::is_left_endpoint_integer_shorter_interval(upper));
}

TEST_F(DragonboxLeftEndpointShorterIntervalTest_410, ReturnsFalseJustBelowLowerThreshold_410) {
  const auto lower = Impl::case_shorter_interval_left_endpoint_lower_threshold;
  EXPECT_FALSE(Impl::is_left_endpoint_integer_shorter_interval(lower - 1));
}

TEST_F(DragonboxLeftEndpointShorterIntervalTest_410, ReturnsFalseJustAboveUpperThreshold_410) {
  const auto upper = Impl::case_shorter_interval_left_endpoint_upper_threshold;
  EXPECT_FALSE(Impl::is_left_endpoint_integer_shorter_interval(upper + 1));
}

TEST_F(DragonboxLeftEndpointShorterIntervalTest_410, ReturnsTrueInsideInterval_410) {
  const auto lower = Impl::case_shorter_interval_left_endpoint_lower_threshold;
  const auto upper = Impl::case_shorter_interval_left_endpoint_upper_threshold;

  // Pick a value safely inside the interval (avoids relying on any additional invariants).
  const auto mid = lower + (upper - lower) / 2;
  EXPECT_TRUE(Impl::is_left_endpoint_integer_shorter_interval(mid));
}

TEST_F(DragonboxLeftEndpointShorterIntervalTest_410, ReturnsFalseWellOutsideInterval_410) {
  const auto lower = Impl::case_shorter_interval_left_endpoint_lower_threshold;
  const auto upper = Impl::case_shorter_interval_left_endpoint_upper_threshold;

  EXPECT_FALSE(Impl::is_left_endpoint_integer_shorter_interval(lower - 10));
  EXPECT_FALSE(Impl::is_left_endpoint_integer_shorter_interval(upper + 10));
}

TEST_F(DragonboxLeftEndpointShorterIntervalTest_410, CanBeEvaluatedAtCompileTime_410) {
  constexpr auto lower = Impl::case_shorter_interval_left_endpoint_lower_threshold;
  constexpr auto upper = Impl::case_shorter_interval_left_endpoint_upper_threshold;

  static_assert(Impl::is_left_endpoint_integer_shorter_interval(lower),
                "Expected true at lower threshold");
  static_assert(Impl::is_left_endpoint_integer_shorter_interval(upper),
                "Expected true at upper threshold");
  static_assert(!Impl::is_left_endpoint_integer_shorter_interval(lower - 1),
                "Expected false just below lower threshold");
  static_assert(!Impl::is_left_endpoint_integer_shorter_interval(upper + 1),
                "Expected false just above upper threshold");
}

}  // namespace