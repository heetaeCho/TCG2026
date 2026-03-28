// File: ./TestProjects/yaml-cpp/test/dragonbox_left_closed_right_open_test_352.cpp

#include <type_traits>

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using Interval =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::left_closed_right_open;

class LeftClosedRightOpenIntervalTypeTest_352 : public ::testing::Test {};

TEST_F(LeftClosedRightOpenIntervalTypeTest_352, IncludeRightEndpointReturnsFalse_352) {
  EXPECT_FALSE(Interval::include_right_endpoint());
}

TEST_F(LeftClosedRightOpenIntervalTypeTest_352, IncludeRightEndpointIsBoolConstexprAndNoexcept_352) {
  // Type is bool
  static_assert(std::is_same_v<decltype(Interval::include_right_endpoint()), bool>);

  // Can be evaluated at compile-time and is false
  static_assert(Interval::include_right_endpoint() == false);

  // Declared noexcept (observable property of the interface)
  EXPECT_TRUE(noexcept(Interval::include_right_endpoint()));

  // Also usable as a constexpr value in a runtime test context.
  constexpr bool v = Interval::include_right_endpoint();
  EXPECT_FALSE(v);
}

}  // namespace