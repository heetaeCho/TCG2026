// TEST_ID: 425
#include <gtest/gtest.h>

#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::is_preferred_integer_types_policy;

// Some headers define dummy<> inside the same namespace (as suggested by the prompt).
template <class Policy>
using DummyT = YAML::jkj::dragonbox::detail::dummy<Policy>;

class IsPreferredIntegerTypesPolicyTest_425 : public ::testing::Test {};

TEST_F(IsPreferredIntegerTypesPolicyTest_425, EllipsisOverloadReturnsFalseForArbitraryArgs_425) {
  constexpr is_preferred_integer_types_policy policy{};

  EXPECT_FALSE(policy(0));
  EXPECT_FALSE(policy(1u));
  EXPECT_FALSE(policy(3.14));
  EXPECT_FALSE(policy("hello"));
  EXPECT_FALSE(policy(nullptr));
}

TEST_F(IsPreferredIntegerTypesPolicyTest_425, DummyWithoutPreferredTypeFallsBackToEllipsisAndReturnsFalse_425) {
  struct NoPreferredTypePolicy {};

  constexpr is_preferred_integer_types_policy policy{};
  constexpr bool result = policy(DummyT<NoPreferredTypePolicy>{});

  static_assert(std::is_same_v<decltype(result), const bool>);
  static_assert(noexcept(policy(DummyT<NoPreferredTypePolicy>{})));
  static_assert(result == false);

  EXPECT_FALSE(policy(DummyT<NoPreferredTypePolicy>{}));
}

TEST_F(IsPreferredIntegerTypesPolicyTest_425, DummyWithPreferredTypeIsCallableAndNoexceptConstexpr_425) {
  struct HasPreferredTypePolicy {
    using preferred_integer_types_policy = int;
  };

  constexpr is_preferred_integer_types_policy policy{};

  // This must be well-formed (template overload should participate; regardless of return value).
  constexpr bool constexpr_result = policy(DummyT<HasPreferredTypePolicy>{});

  static_assert(std::is_same_v<decltype(constexpr_result), const bool>);
  static_assert(noexcept(policy(DummyT<HasPreferredTypePolicy>{})));

  // Verify runtime call matches constexpr evaluation (no assumptions about true/false).
  const bool runtime_result = policy(DummyT<HasPreferredTypePolicy>{});
  EXPECT_EQ(runtime_result, constexpr_result);
}

TEST_F(IsPreferredIntegerTypesPolicyTest_425, CopyConstructedPolicyBehavesTheSame_425) {
  struct NoPreferredTypePolicy {};
  struct HasPreferredTypePolicy {
    using preferred_integer_types_policy = void;
  };

  constexpr is_preferred_integer_types_policy original{};
  constexpr is_preferred_integer_types_policy copy = original;

  EXPECT_EQ(original(123), copy(123));
  EXPECT_EQ(original(DummyT<NoPreferredTypePolicy>{}), copy(DummyT<NoPreferredTypePolicy>{}));
  EXPECT_EQ(original(DummyT<HasPreferredTypePolicy>{}), copy(DummyT<HasPreferredTypePolicy>{}));
}

}  // namespace