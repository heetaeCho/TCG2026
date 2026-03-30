// File: ./TestProjects/yaml-cpp/test/dragonbox_asymmetric_boundary_test_346.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::asymmetric_boundary;

TEST(AsymmetricBoundaryTest_346, IncludeRightEndpointTrueWhenLeftIsOpen_346) {
  asymmetric_boundary b{false};  // is_left_closed = false
  EXPECT_TRUE(b.include_right_endpoint());
}

TEST(AsymmetricBoundaryTest_346, IncludeRightEndpointFalseWhenLeftIsClosed_346) {
  asymmetric_boundary b{true};  // is_left_closed = true
  EXPECT_FALSE(b.include_right_endpoint());
}

TEST(AsymmetricBoundaryTest_346, MethodsAreNoexcept_346) {
  static_assert(noexcept(std::declval<const asymmetric_boundary&>().include_left_endpoint()),
                "include_left_endpoint() must be noexcept");
  static_assert(noexcept(std::declval<const asymmetric_boundary&>().include_right_endpoint()),
                "include_right_endpoint() must be noexcept");
  SUCCEED();
}

TEST(AsymmetricBoundaryTest_346, IncludeRightEndpointIsConstexprEvaluable_346) {
  // Verifies the constexpr contract for include_right_endpoint() in a way that's observable.
  constexpr asymmetric_boundary closed_left{true};
  constexpr asymmetric_boundary open_left{false};

  static_assert(!closed_left.include_right_endpoint(),
                "When is_left_closed is true, right endpoint must not be included.");
  static_assert(open_left.include_right_endpoint(),
                "When is_left_closed is false, right endpoint must be included.");

  SUCCEED();
}

}  // namespace