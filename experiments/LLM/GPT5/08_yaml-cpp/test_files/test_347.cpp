// File: ./TestProjects/yaml-cpp/test/dragonbox_interval_closed_test_347.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using ClosedInterval =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::closed;

}  // namespace

// NOTE: These tests only validate observable interface behavior of the policy type.

TEST(DragonboxClosedIntervalTest_347, IncludeLeftEndpointIsBoolNoexceptAndConstexpr_347) {
  // Type + noexcept checks (compile-time)
  static_assert(std::is_same_v<decltype(ClosedInterval::include_left_endpoint()), bool>,
                "include_left_endpoint() must return bool");
  static_assert(noexcept(ClosedInterval::include_left_endpoint()),
                "include_left_endpoint() must be noexcept");

  // Constexpr usability (compile-time)
  constexpr bool left = ClosedInterval::include_left_endpoint();
  (void)left;

  // Observable runtime behavior
  EXPECT_TRUE(ClosedInterval::include_left_endpoint());
}

TEST(DragonboxClosedIntervalTest_347, IncludeRightEndpointIsBoolNoexceptAndConstexpr_347) {
  // Type + noexcept checks (compile-time)
  static_assert(std::is_same_v<decltype(ClosedInterval::include_right_endpoint()), bool>,
                "include_right_endpoint() must return bool");
  static_assert(noexcept(ClosedInterval::include_right_endpoint()),
                "include_right_endpoint() must be noexcept");

  // Constexpr usability (compile-time)
  constexpr bool right = ClosedInterval::include_right_endpoint();
  (void)right;

  // Observable runtime behavior
  EXPECT_TRUE(ClosedInterval::include_right_endpoint());
}

TEST(DragonboxClosedIntervalTest_347, ClosedIntervalIncludesBothEndpoints_347) {
  // Normal operation: both endpoints should be included for a "closed" interval.
  const bool left = ClosedInterval::include_left_endpoint();
  const bool right = ClosedInterval::include_right_endpoint();

  EXPECT_TRUE(left);
  EXPECT_TRUE(right);
}