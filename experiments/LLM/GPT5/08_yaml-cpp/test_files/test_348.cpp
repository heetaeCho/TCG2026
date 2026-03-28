// File: ./TestProjects/yaml-cpp/test/dragonbox_closed_interval_test_348.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using ClosedInterval =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::closed;

// SFINAE detection for include_left_endpoint()
template <typename T, typename = void>
struct HasIncludeLeftEndpoint : std::false_type {};

template <typename T>
struct HasIncludeLeftEndpoint<T, std::void_t<decltype(T::include_left_endpoint())>>
    : std::true_type {};

}  // namespace

// Normal operation: include_right_endpoint() returns true.
TEST(ClosedIntervalTest_348, IncludeRightEndpointReturnsTrue_348) {
  EXPECT_TRUE(ClosedInterval::include_right_endpoint());
}

// Boundary/behavioral property: callable in a constexpr context (compile-time).
TEST(ClosedIntervalTest_348, IncludeRightEndpointIsConstexprUsable_348) {
  constexpr bool v = ClosedInterval::include_right_endpoint();
  static_assert(v, "closed::include_right_endpoint() must be usable at compile time and be true");
  EXPECT_TRUE(v);
}

// Error/exceptional property: function is declared noexcept (observable via noexcept operator).
TEST(ClosedIntervalTest_348, IncludeRightEndpointIsNoexcept_348) {
  EXPECT_TRUE(noexcept(ClosedInterval::include_right_endpoint()));
}

// Verification of related interface (if present): include_left_endpoint exists, returns bool, and is noexcept.
// This test does NOT assume its return value (black-box), only that the API is callable.
TEST(ClosedIntervalTest_348, IncludeLeftEndpointIsCallableIfPresent_348) {
  if constexpr (HasIncludeLeftEndpoint<ClosedInterval>::value) {
    // Must be a bool-returning call (or convertible to bool).
    static_assert(std::is_convertible_v<decltype(ClosedInterval::include_left_endpoint()), bool>,
                  "include_left_endpoint() must return (or be convertible to) bool");
    EXPECT_TRUE(noexcept(ClosedInterval::include_left_endpoint()));
    // Don't assert the value; just ensure it can be evaluated.
    (void)ClosedInterval::include_left_endpoint();
    SUCCEED();
  } else {
    // If the symbol is not present in a given build configuration, the test remains valid.
    SUCCEED();
  }
}