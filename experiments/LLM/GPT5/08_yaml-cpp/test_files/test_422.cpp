// File: ./TestProjects/yaml-cpp/test/dragonbox_is_binary_to_decimal_rounding_policy_test_422.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using Predicate = YAML::jkj::dragonbox::detail::is_binary_to_decimal_rounding_policy;

// Helper aliases to reduce verbosity in tests
template <class Policy>
using DummyT = YAML::jkj::dragonbox::detail::dummy<Policy>;

struct PolicyWithTypeAlias {
  using binary_to_decimal_rounding_policy = void;
};

struct PolicyWithDifferentTypeAlias {
  using binary_to_decimal_rounding_policy = int;
};

struct PolicyWithoutAlias {};

struct PolicyWithNonTypeMember {
  // Not a type; should not satisfy `typename Policy::binary_to_decimal_rounding_policy`
  static constexpr int binary_to_decimal_rounding_policy = 1;
};

struct PolicyWithPrivateAlias {
 private:
  using binary_to_decimal_rounding_policy = void;
};

}  // namespace

TEST(IsBinaryToDecimalRoundingPolicyTest_422, CallableWhenAliasExists_422) {
  constexpr Predicate pred{};

  static_assert(std::is_invocable_v<Predicate, DummyT<PolicyWithTypeAlias>>,
                "Predicate should be invocable when Policy defines the required nested type alias.");

  constexpr bool result = pred(DummyT<PolicyWithTypeAlias>{});
  EXPECT_TRUE(result);
}

TEST(IsBinaryToDecimalRoundingPolicyTest_422, CallableForDifferentAliasType_422) {
  constexpr Predicate pred{};

  static_assert(std::is_invocable_v<Predicate, DummyT<PolicyWithDifferentTypeAlias>>,
                "Predicate should be invocable when nested alias exists, regardless of the alias type.");

  constexpr bool result = pred(DummyT<PolicyWithDifferentTypeAlias>{});
  EXPECT_TRUE(result);
}

TEST(IsBinaryToDecimalRoundingPolicyTest_422, NotCallableWhenAliasMissing_422) {
  static_assert(!std::is_invocable_v<Predicate, DummyT<PolicyWithoutAlias>>,
                "Predicate should NOT be invocable when Policy lacks the required nested type alias.");

  SUCCEED();
}

TEST(IsBinaryToDecimalRoundingPolicyTest_422, NotCallableWhenMemberIsNotAType_422) {
  static_assert(!std::is_invocable_v<Predicate, DummyT<PolicyWithNonTypeMember>>,
                "Predicate should NOT be invocable when the member exists but is not a type.");

  SUCCEED();
}

TEST(IsBinaryToDecimalRoundingPolicyTest_422, NotCallableWhenAliasIsInaccessible_422) {
  static_assert(!std::is_invocable_v<Predicate, DummyT<PolicyWithPrivateAlias>>,
                "Predicate should NOT be invocable when the nested alias exists but is not accessible.");

  SUCCEED();
}

TEST(IsBinaryToDecimalRoundingPolicyTest_422, CallIsNoexceptWhenCallable_422) {
  constexpr Predicate pred{};

  static_assert(noexcept(pred(DummyT<PolicyWithTypeAlias>{})),
                "Callable operator() should be noexcept when instantiated.");

  EXPECT_TRUE((pred(DummyT<PolicyWithTypeAlias>{})));
}

TEST(IsBinaryToDecimalRoundingPolicyTest_422, ReturnValueIsConstexprTrue_422) {
  constexpr Predicate pred{};

  constexpr bool v1 = pred(DummyT<PolicyWithTypeAlias>{});
  constexpr bool v2 = pred(DummyT<PolicyWithDifferentTypeAlias>{});

  static_assert(v1, "Expected constexpr true when policy satisfies requirement.");
  static_assert(v2, "Expected constexpr true when policy satisfies requirement.");

  EXPECT_TRUE(v1);
  EXPECT_TRUE(v2);
}