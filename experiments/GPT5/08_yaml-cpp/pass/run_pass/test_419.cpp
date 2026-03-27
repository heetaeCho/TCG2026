// File: test_is_decimal_to_binary_rounding_policy_419.cpp
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Alias the type under test (exact namespaces from the provided header path/snippet).
using PolicyDetector =
    YAML::jkj::dragonbox::detail::is_decimal_to_binary_rounding_policy;

// A policy type that *does* define the expected nested type name.
struct HasRoundingPolicyType {
  using decimal_to_binary_rounding_policy = void;
};

// A policy type that does *not* define the nested type name.
struct NoRoundingPolicyType {};

// Another variant with a different (wrong) nested name.
struct HasDifferentNestedType {
  using not_decimal_to_binary_rounding_policy = void;
};

}  // namespace

// Normal operation: type with the expected nested member should be detected.
TEST(IsDecimalToBinaryRoundingPolicyTest_419, DetectsPolicyWithNestedType_419) {
  constexpr PolicyDetector detector{};
  EXPECT_TRUE(detector(YAML::jkj::dragonbox::detail::dummy<HasRoundingPolicyType>{}));
}

// Normal operation: type without the nested member should not be detected.
TEST(IsDecimalToBinaryRoundingPolicyTest_419, RejectsPolicyWithoutNestedType_419) {
  constexpr PolicyDetector detector{};
  EXPECT_FALSE(detector(YAML::jkj::dragonbox::detail::dummy<NoRoundingPolicyType>{}));
}

// Boundary/edge: type with a similarly-named but incorrect nested type should not be detected.
TEST(IsDecimalToBinaryRoundingPolicyTest_419, RejectsPolicyWithDifferentNestedType_419) {
  constexpr PolicyDetector detector{};
  EXPECT_FALSE(detector(YAML::jkj::dragonbox::detail::dummy<HasDifferentNestedType>{}));
}

// Error/exceptional (observable): calling the ellipsis overload should be safe and return false.
// This verifies behavior for "unknown / mismatched argument" cases.
TEST(IsDecimalToBinaryRoundingPolicyTest_419, EllipsisOverloadReturnsFalse_419) {
  constexpr PolicyDetector detector{};
  EXPECT_FALSE(detector(0));                 // int argument
  EXPECT_FALSE(detector("not a dummy"));     // const char*
  EXPECT_FALSE(detector(nullptr));           // nullptr_t
}

// Boundary: detector should be usable in a constant-evaluated context (constexpr).
TEST(IsDecimalToBinaryRoundingPolicyTest_419, WorksInConstexprContext_419) {
  constexpr PolicyDetector detector{};
  constexpr bool has_policy =
      detector(YAML::jkj::dragonbox::detail::dummy<HasRoundingPolicyType>{});
  constexpr bool no_policy =
      detector(YAML::jkj::dragonbox::detail::dummy<NoRoundingPolicyType>{});

  static_assert(has_policy, "Expected HasRoundingPolicyType to be detected.");
  static_assert(!no_policy, "Expected NoRoundingPolicyType to be rejected.");

  EXPECT_TRUE(has_policy);
  EXPECT_FALSE(no_policy);
}

// Boundary: ensure noexcept is honored for the observable call patterns we use.
TEST(IsDecimalToBinaryRoundingPolicyTest_419, CallsAreNoexcept_419) {
  constexpr PolicyDetector detector{};

  EXPECT_TRUE(noexcept(
      detector(YAML::jkj::dragonbox::detail::dummy<HasRoundingPolicyType>{})));
  EXPECT_TRUE(noexcept(
      detector(YAML::jkj::dragonbox::detail::dummy<NoRoundingPolicyType>{})));
  EXPECT_TRUE(noexcept(detector(123)));
}