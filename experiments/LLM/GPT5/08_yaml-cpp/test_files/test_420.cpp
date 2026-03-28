// TEST_ID: 420
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Helper: detect whether Functor()(dummy<Policy>) is a well-formed expression.
template <class Functor, class Policy, class = void>
struct IsInvocableWithDummy : std::false_type {};

template <class Functor, class Policy>
struct IsInvocableWithDummy<
    Functor,
    Policy,
    std::void_t<decltype(std::declval<const Functor&>()(
        std::declval<YAML::jkj::dragonbox::detail::dummy<Policy>>()))>> : std::true_type {};

template <class Functor, class Policy>
inline constexpr bool IsInvocableWithDummyV = IsInvocableWithDummy<Functor, Policy>::value;

// Policies for testing.
struct PolicyWithRoundingTag {
  // The interface under test requires this nested type name to exist.
  using decimal_to_binary_rounding_policy = void;
};

struct PolicyWithoutRoundingTag {
  // Intentionally missing decimal_to_binary_rounding_policy
};

using Functor = YAML::jkj::dragonbox::detail::is_decimal_to_binary_rounding_policy;

}  // namespace

TEST(DragonboxIsDecimalToBinaryRoundingPolicyTest_420, InvocableWhenPolicyProvidesRequiredNestedType_420) {
  // Observable behavior based on signature/SFINAE: operator() participates only when the
  // nested type Policy::decimal_to_binary_rounding_policy exists.
  static_assert(IsInvocableWithDummyV<Functor, PolicyWithRoundingTag>,
                "Expected functor to be invocable when nested type exists.");

  const Functor f{};

  // Validate return type and runtime-visible return value.
  const bool result =
      f(std::declval<YAML::jkj::dragonbox::detail::dummy<PolicyWithRoundingTag>>());
  EXPECT_TRUE(result);
}

TEST(DragonboxIsDecimalToBinaryRoundingPolicyTest_420, NotInvocableWhenPolicyLacksRequiredNestedType_420) {
  // Observable behavior via expression validity: call should be ill-formed (SFINAE) when the nested type is missing.
  static_assert(!IsInvocableWithDummyV<Functor, PolicyWithoutRoundingTag>,
                "Expected functor to NOT be invocable when nested type is missing.");

  SUCCEED();  // This is a compile-time property test.
}

TEST(DragonboxIsDecimalToBinaryRoundingPolicyTest_420, IsNoexceptForEligiblePolicy_420) {
  static_assert(IsInvocableWithDummyV<Functor, PolicyWithRoundingTag>,
                "Precondition: invocable for this policy.");

  static_assert(noexcept(std::declval<const Functor&>()(
                    std::declval<YAML::jkj::dragonbox::detail::dummy<PolicyWithRoundingTag>>())),
                "operator() should be noexcept when viable, per interface.");
  SUCCEED();
}

TEST(DragonboxIsDecimalToBinaryRoundingPolicyTest_420, CanBeConstantEvaluatedForEligiblePolicy_420) {
  static_assert(IsInvocableWithDummyV<Functor, PolicyWithRoundingTag>,
                "Precondition: invocable for this policy.");

  // The interface shows constexpr; verify it can be used in constant evaluation.
  constexpr Functor f{};
  // Use an unevaluated dummy argument in a way that's compatible with constant evaluation.
  // (We rely on the type being usable; if dummy is not literal/constructible, this test will fail to compile,
  // which correctly reflects the observable constraints of the provided interface in this codebase.)
  constexpr bool v = f(YAML::jkj::dragonbox::detail::dummy<PolicyWithRoundingTag>{});
  static_assert(v, "Expected constexpr evaluation to yield true for eligible policy.");
  EXPECT_TRUE(v);
}