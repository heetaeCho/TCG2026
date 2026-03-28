// File: ./TestProjects/yaml-cpp/test/dragonbox_right_closed_left_open_test_353.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Interval = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::right_closed_left_open;

// Compile-time (translation-unit) checks (still black-box: only uses the public interface).
static_assert(std::is_empty_v<Interval>, "Interval policy type should be an empty policy struct.");
static_assert(std::is_trivially_default_constructible_v<Interval>,
              "Interval policy type should be trivially default constructible.");

static_assert(noexcept(Interval::include_left_endpoint()),
              "include_left_endpoint() should be noexcept.");
static_assert(noexcept(Interval::include_right_endpoint()),
              "include_right_endpoint() should be noexcept.");

// Ensure constexpr-evaluability (no assumptions about internal logic; just checks it can be used in constant expressions).
static_assert(std::is_same_v<decltype(Interval::include_left_endpoint()), const bool>,
              "include_left_endpoint() should return bool (const in unevaluated context for constexpr).");
static_assert(std::is_same_v<decltype(Interval::include_right_endpoint()), const bool>,
              "include_right_endpoint() should return bool (const in unevaluated context for constexpr).");

}  // namespace

TEST(DragonboxRightClosedLeftOpenTest_353, IncludeLeftEndpointIsFalse_353) {
  // Observable behavior: return value.
  EXPECT_FALSE(Interval::include_left_endpoint());
}

TEST(DragonboxRightClosedLeftOpenTest_353, IncludeRightEndpointIsTrue_353) {
  // Observable behavior: return value.
  EXPECT_TRUE(Interval::include_right_endpoint());
}

TEST(DragonboxRightClosedLeftOpenTest_353, EndpointsAreNotBothIncluded_353) {
  // Boundary/consistency check for an interval policy named "right-closed, left-open".
  // This does not re-implement logic; it verifies observable properties implied by the interface naming.
  const bool left = Interval::include_left_endpoint();
  const bool right = Interval::include_right_endpoint();

  EXPECT_FALSE(left);
  EXPECT_TRUE(right);
  EXPECT_NE(left, right);
}

TEST(DragonboxRightClosedLeftOpenTest_353, FunctionsAreNoexceptAtCallSite_353) {
  // Verifies the noexcept contract is observable at the call site.
  EXPECT_TRUE(noexcept(Interval::include_left_endpoint()));
  EXPECT_TRUE(noexcept(Interval::include_right_endpoint()));
}

TEST(DragonboxRightClosedLeftOpenTest_353, CanBeUsedInConstexprContext_353) {
  // Boundary case: ensure these are usable in constexpr contexts (e.g., template params, static_assert scenarios).
  constexpr bool left = Interval::include_left_endpoint();
  constexpr bool right = Interval::include_right_endpoint();

  EXPECT_FALSE(left);
  EXPECT_TRUE(right);
}