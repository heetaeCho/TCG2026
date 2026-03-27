// File: ./TestProjects/yaml-cpp/test/dragonbox_open_interval_type_test_350.cpp

#include <gtest/gtest.h>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using OpenInterval =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::open;

// Compile-time verification for behavior that is explicitly defined in the provided code.
static_assert(OpenInterval::include_right_endpoint() == false,
              "open::include_right_endpoint() must be false per the provided implementation.");
static_assert(noexcept(OpenInterval::include_right_endpoint()),
              "open::include_right_endpoint() must be noexcept.");

class OpenIntervalTypeTest_350 : public ::testing::Test {};

TEST_F(OpenIntervalTypeTest_350, IncludeRightEndpointIsFalse_350) {
  // Observable behavior from the provided implementation:
  // include_right_endpoint() returns false.
  EXPECT_FALSE(OpenInterval::include_right_endpoint());
}

TEST_F(OpenIntervalTypeTest_350, IncludeRightEndpointIsConstexprUsable_350) {
  // Ensure it can be used in a constant expression (i.e., constexpr-friendly).
  constexpr bool v = OpenInterval::include_right_endpoint();
  (void)v;
  EXPECT_FALSE(v);
}

TEST_F(OpenIntervalTypeTest_350, IncludeRightEndpointIsNoexcept_350) {
  EXPECT_TRUE(noexcept(OpenInterval::include_right_endpoint()));
}

TEST_F(OpenIntervalTypeTest_350, IncludeLeftEndpointIsCallableAndReturnsBool_350) {
  // The partial code shows include_left_endpoint() exists (declared), but does not define its value.
  // We only verify observable/interface-level properties without inferring its internal logic.
  const bool v1 = OpenInterval::include_left_endpoint();
  const bool v2 = OpenInterval::include_left_endpoint();

  // Must return a bool (compile-time type check) and be callable repeatedly.
  static_assert(std::is_same_v<decltype(OpenInterval::include_left_endpoint()), bool>,
                "include_left_endpoint() must return bool.");
  (void)v1;
  (void)v2;

  // Optional stability check: repeated calls should be consistent for a policy-type function.
  EXPECT_EQ(v1, v2);
}

TEST_F(OpenIntervalTypeTest_350, IncludeLeftEndpointIsNoexcept_350) {
  EXPECT_TRUE(noexcept(OpenInterval::include_left_endpoint()));
}

}  // namespace