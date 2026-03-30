// File: ./TestProjects/yaml-cpp/test/dragonbox_asymmetric_boundary_test_345.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::asymmetric_boundary;

TEST(AsymmetricBoundaryTest_345, IncludeLeftEndpointReflectsIsLeftClosedTrue_345) {
  asymmetric_boundary b{};
  b.is_left_closed = true;

  EXPECT_TRUE(b.include_left_endpoint());
  // Stability: repeated calls should be consistent (observable behavior).
  EXPECT_TRUE(b.include_left_endpoint());
}

TEST(AsymmetricBoundaryTest_345, IncludeLeftEndpointReflectsIsLeftClosedFalse_345) {
  asymmetric_boundary b{};
  b.is_left_closed = false;

  EXPECT_FALSE(b.include_left_endpoint());
  EXPECT_FALSE(b.include_left_endpoint());
}

TEST(AsymmetricBoundaryTest_345, IncludeLeftEndpointIsNoexcept_345) {
  asymmetric_boundary b{};
  b.is_left_closed = true;

  static_assert(noexcept(std::declval<const asymmetric_boundary&>().include_left_endpoint()),
                "include_left_endpoint() must be noexcept");
  (void)b;  // keep runtime unused warnings away in some builds
}

TEST(AsymmetricBoundaryTest_345, IncludeLeftEndpointIsConstexprEvaluable_345) {
  // Verify compile-time evaluation works (function is declared constexpr).
  constexpr asymmetric_boundary b_true{true};
  constexpr asymmetric_boundary b_false{false};

  static_assert(b_true.include_left_endpoint(), "Expected left endpoint included when left-closed");
  static_assert(!b_false.include_left_endpoint(),
                "Expected left endpoint excluded when not left-closed");
}

TEST(AsymmetricBoundaryTest_345, IncludeRightEndpointIsCallableAndReturnsBool_345) {
  // We do NOT assert semantic behavior of include_right_endpoint(), since it is not provided.
  // Only verify it is a callable const member and returns bool.
  static_assert(std::is_same_v<decltype(std::declval<const asymmetric_boundary&>().include_right_endpoint()),
                               bool>,
                "include_right_endpoint() must return bool");
}

TEST(AsymmetricBoundaryTest_345, IncludeRightEndpointIsNoexcept_345) {
  // We do NOT assert its value; only its exception specification is observable via the signature.
  static_assert(noexcept(std::declval<const asymmetric_boundary&>().include_right_endpoint()),
                "include_right_endpoint() must be noexcept");
}

TEST(AsymmetricBoundaryTest_345, IncludeRightEndpointIsConstexprEvaluable_345) {
  // We do NOT assert what value it returns; only that it can be evaluated in a constant expression.
  constexpr asymmetric_boundary b{true};
  constexpr bool v = b.include_right_endpoint();
  (void)v;
  SUCCEED();
}

}  // namespace