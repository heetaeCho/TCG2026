// File: ./TestProjects/yaml-cpp/test/dragonbox_is_sign_policy_test_415.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::is_sign_policy;

// Helper policy types for overload/SFINAE behavior.
struct PolicyWithSignPolicy {
  using sign_policy = void;
};

struct PolicyWithDifferentSignPolicy {
  struct sign_policy {};
};

struct PolicyWithoutSignPolicy {};

// A type that is definitely not a dummy<Policy>.
struct NotADummy {};

}  // namespace

// NOTE: These tests are written purely from the public signatures shown:
// - constexpr bool operator()(...) const noexcept;
// - template <class Policy, class = typename Policy::sign_policy>
//   constexpr bool operator()(dummy<Policy>) const noexcept;
//
// Observable behavior we test:
// - The ellipsis overload returns false.
// - A Policy with the required nested ::sign_policy should make the template
//   overload viable when called with dummy<Policy>.

TEST(IsSignPolicyTest_415, EllipsisOverloadReturnsFalseForArbitraryArgument_415) {
  constexpr is_sign_policy detector{};

  // Any arbitrary argument should match operator(...), which returns false.
  EXPECT_FALSE(detector(0));
  EXPECT_FALSE(detector(NotADummy{}));
}

TEST(IsSignPolicyTest_415, TemplateOverloadIsViableWhenPolicyDefinesSignPolicy_415) {
  constexpr is_sign_policy detector{};

  // If dummy<T> exists in the header as expected, this should call the template
  // overload and return true for policies that define Policy::sign_policy.
  EXPECT_TRUE((detector(YAML::jkj::dragonbox::detail::dummy<PolicyWithSignPolicy>{})));
  EXPECT_TRUE((detector(YAML::jkj::dragonbox::detail::dummy<PolicyWithDifferentSignPolicy>{})));
}

TEST(IsSignPolicyTest_415, FallsBackToEllipsisWhenPolicyLacksSignPolicy_415) {
  constexpr is_sign_policy detector{};

  // For a policy without Policy::sign_policy, the template overload should not
  // participate (SFINAE), so the ellipsis overload should be chosen => false.
  EXPECT_FALSE((detector(YAML::jkj::dragonbox::detail::dummy<PolicyWithoutSignPolicy>{})));
}

TEST(IsSignPolicyTest_415, ConstexprCallableAndNoexceptUsage_415) {
  constexpr is_sign_policy detector{};

  // Verify it can be used in constant evaluation contexts.
  constexpr bool has_sign =
      detector(YAML::jkj::dragonbox::detail::dummy<PolicyWithSignPolicy>{});
  constexpr bool no_sign =
      detector(YAML::jkj::dragonbox::detail::dummy<PolicyWithoutSignPolicy>{});
  constexpr bool arbitrary = detector(12345);

  EXPECT_TRUE(has_sign);
  EXPECT_FALSE(no_sign);
  EXPECT_FALSE(arbitrary);

  // The signature says noexcept; we validate the expression is noexcept.
  static_assert(noexcept(detector(0)), "operator()(...) should be noexcept");
  static_assert(noexcept(detector(YAML::jkj::dragonbox::detail::dummy<PolicyWithSignPolicy>{})),
                "template operator()(dummy<Policy>) should be noexcept");
}