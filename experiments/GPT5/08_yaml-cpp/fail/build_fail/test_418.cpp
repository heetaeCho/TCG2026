// File: ./TestProjects/yaml-cpp/test/dragonbox_is_trailing_zero_policy_test_418.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::is_trailing_zero_policy;
using YAML::jkj::dragonbox::detail::dummy;

struct PolicyWithTrailingZeroPolicyVoid {
  using trailing_zero_policy = void;
};

struct PolicyWithTrailingZeroPolicyInt {
  using trailing_zero_policy = int;
};

struct PolicyWithTrailingZeroPolicyStruct {
  struct trailing_zero_policy {};
};

struct PolicyWithoutTrailingZeroPolicy {
  // Intentionally no trailing_zero_policy
};

class IsTrailingZeroPolicyTest_418 : public ::testing::Test {};

TEST_F(IsTrailingZeroPolicyTest_418, InvocableAndReturnsTrueWhenPolicyHasTrailingZeroPolicy_418) {
  constexpr is_trailing_zero_policy sut{};

  // Observable behavior: callable when Policy::trailing_zero_policy exists.
  static_assert(std::is_invocable_v<decltype(sut), dummy<PolicyWithTrailingZeroPolicyVoid>>);

  // Observable behavior: returns true.
  constexpr bool v = sut(dummy<PolicyWithTrailingZeroPolicyVoid>{});
  static_assert(v);

  EXPECT_TRUE(sut(dummy<PolicyWithTrailingZeroPolicyVoid>{}));
}

TEST_F(IsTrailingZeroPolicyTest_418, NotInvocableWhenPolicyLacksTrailingZeroPolicy_418) {
  constexpr is_trailing_zero_policy sut{};

  // Observable behavior: not callable when Policy::trailing_zero_policy does not exist.
  static_assert(!std::is_invocable_v<decltype(sut), dummy<PolicyWithoutTrailingZeroPolicy>>);
}

TEST_F(IsTrailingZeroPolicyTest_418, WorksForDifferentTrailingZeroPolicyTypes_418) {
  constexpr is_trailing_zero_policy sut{};

  static_assert(std::is_invocable_v<decltype(sut), dummy<PolicyWithTrailingZeroPolicyInt>>);
  static_assert(std::is_invocable_v<decltype(sut), dummy<PolicyWithTrailingZeroPolicyStruct>>);

  EXPECT_TRUE(sut(dummy<PolicyWithTrailingZeroPolicyInt>{}));
  EXPECT_TRUE(sut(dummy<PolicyWithTrailingZeroPolicyStruct>{}));
}

TEST_F(IsTrailingZeroPolicyTest_418, IsNoexceptAndConstexprWhenInvocable_418) {
  constexpr is_trailing_zero_policy sut{};

  // Observable behavior: operator() is declared noexcept for valid Policies.
  static_assert(noexcept(sut(dummy<PolicyWithTrailingZeroPolicyVoid>{})));

  // Observable behavior: usable in constant evaluation.
  constexpr bool v = sut(dummy<PolicyWithTrailingZeroPolicyVoid>{});
  static_assert(v);

  EXPECT_TRUE(v);
}

}  // namespace