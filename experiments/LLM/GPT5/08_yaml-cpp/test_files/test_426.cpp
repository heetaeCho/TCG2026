// File: ./TestProjects/yaml-cpp/test/dragonbox_is_preferred_integer_types_policy_test_426.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using Detector = YAML::jkj::dragonbox::detail::is_preferred_integer_types_policy;

struct PolicyWithPreferredIntegerTypesPolicy {
  using preferred_integer_types_policy = void;
};

struct PolicyWithNonVoidPreferredIntegerTypesPolicy {
  struct preferred_integer_types_policy {};
};

struct PolicyWithoutPreferredIntegerTypesPolicy {};

// Helper alias to shorten dummy usage in tests.
template <class Policy>
using Dummy = YAML::jkj::dragonbox::detail::dummy<Policy>;

}  // namespace

TEST(IsPreferredIntegerTypesPolicyTest_426, ReturnsTrueWhenPolicyDefinesNestedType_426) {
  constexpr Detector detector{};

  constexpr bool result = detector(Dummy<PolicyWithPreferredIntegerTypesPolicy>{});
  static_assert(result, "Expected detector to return true when nested type exists.");

  EXPECT_TRUE(result);
}

TEST(IsPreferredIntegerTypesPolicyTest_426, ReturnsTrueWhenNestedTypeIsNonVoid_426) {
  constexpr Detector detector{};

  constexpr bool result = detector(Dummy<PolicyWithNonVoidPreferredIntegerTypesPolicy>{});
  static_assert(result, "Expected detector to return true for any nested type definition.");

  EXPECT_TRUE(result);
}

TEST(IsPreferredIntegerTypesPolicyTest_426, ReturnsFalseWhenPolicyDoesNotDefineNestedType_426) {
  // This test verifies observable behavior for a policy that lacks the required nested type.
  // If the underlying interface provides a fallback, it should return false.
  constexpr Detector detector{};

  constexpr bool result = detector(Dummy<PolicyWithoutPreferredIntegerTypesPolicy>{});
  EXPECT_FALSE(result);
}

TEST(IsPreferredIntegerTypesPolicyTest_426, OperatorIsNoexceptForDetectedPolicy_426) {
  constexpr Detector detector{};

  static_assert(noexcept(detector(Dummy<PolicyWithPreferredIntegerTypesPolicy>{})),
                "Expected operator() to be noexcept for a detected policy.");

  EXPECT_TRUE(noexcept(detector(Dummy<PolicyWithPreferredIntegerTypesPolicy>{})));
}

TEST(IsPreferredIntegerTypesPolicyTest_426, OperatorIsUsableInConstantEvaluation_426) {
  constexpr Detector detector{};

  // Verifies that the call can be evaluated at compile time (constexpr-friendly).
  constexpr bool result_true = detector(Dummy<PolicyWithPreferredIntegerTypesPolicy>{});
  static_assert(result_true, "Expected constexpr evaluation to succeed and be true.");

  EXPECT_TRUE(result_true);
}