// File: ./TestProjects/yaml-cpp/test/dragonbox_is_binary_to_decimal_rounding_policy_test_421.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

namespace d = YAML::jkj::dragonbox::detail;

// A policy type that does NOT opt into the binary_to_decimal_rounding_policy marker.
struct PolicyWithoutMarker_421 {};

// A policy type that DOES opt into the binary_to_decimal_rounding_policy marker.
// The interface hints the presence of `typename Policy::binary_to_decimal_rounding_policy`
// enables the template overload.
struct PolicyWithMarker_421 {
  using binary_to_decimal_rounding_policy = void;
};

}  // namespace

TEST(IsBinaryToDecimalRoundingPolicyTest_421, EllipsisOverloadReturnsFalse_421) {
  constexpr d::is_binary_to_decimal_rounding_policy pred{};

  // Observable from the provided partial code: the `operator()(...)` overload returns false.
  EXPECT_FALSE(pred(0));
  EXPECT_FALSE(pred(1, 2, 3));
  EXPECT_FALSE(pred("anything"));
}

TEST(IsBinaryToDecimalRoundingPolicyTest_421, PolicyWithoutMarkerFallsBackToEllipsisAndReturnsFalse_421) {
  constexpr d::is_binary_to_decimal_rounding_policy pred{};

  // If the marker does not exist, the template overload should be SFINAE-disabled and
  // the ellipsis overload should remain viable; it returns false (observable behavior).
  constexpr bool result = pred(d::dummy<PolicyWithoutMarker_421>{});
  static_assert(!result, "Expected fallback overload to return false.");
  EXPECT_FALSE(result);
}

TEST(IsBinaryToDecimalRoundingPolicyTest_421, PolicyWithMarkerIsCallableViaDummy_421) {
  constexpr d::is_binary_to_decimal_rounding_policy pred{};

  // This test validates the *presence/viability* of the template overload path (enabled by the marker)
  // via successful compilation and evaluation in a constexpr context.
  //
  // We also assert a boolean result for the opt-in policy (typical for such predicates).
  constexpr bool result = pred(d::dummy<PolicyWithMarker_421>{});
  EXPECT_TRUE(result);
}

TEST(IsBinaryToDecimalRoundingPolicyTest_421, CallOperatorIsNoexcept_421) {
  constexpr d::is_binary_to_decimal_rounding_policy pred{};

  // Both overloads are declared noexcept in the interface.
  EXPECT_TRUE(noexcept(pred(123)));
  EXPECT_TRUE((noexcept(pred(d::dummy<PolicyWithoutMarker_421>{}))));
  EXPECT_TRUE((noexcept(pred(d::dummy<PolicyWithMarker_421>{}))));
}

TEST(IsBinaryToDecimalRoundingPolicyTest_421, WorksInConstexprContext_421) {
  constexpr d::is_binary_to_decimal_rounding_policy pred{};

  // Ensure it can be used at compile-time (interface declares constexpr).
  constexpr bool a = pred(3.14);
  constexpr bool b = pred(d::dummy<PolicyWithoutMarker_421>{});
  constexpr bool c = pred(d::dummy<PolicyWithMarker_421>{});

  (void)a;
  (void)b;
  (void)c;

  // At least the fallback observable behavior must hold.
  static_assert(a == false, "Ellipsis overload should yield false in constexpr context.");
  static_assert(b == false, "Fallback path should yield false in constexpr context.");
}