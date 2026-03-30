// File: ./TestProjects/yaml-cpp/test/dragonbox_is_sign_policy_test_416.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Include the header under test.
#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::dummy;
using YAML::jkj::dragonbox::detail::is_sign_policy;

struct PolicyWithSignPolicyInt {
  using sign_policy = int;
};

struct PolicyWithSignPolicyVoid {
  using sign_policy = void;
};

struct PolicyWithoutSignPolicy {
  // Intentionally no sign_policy
};

template <typename Policy>
constexpr bool IsInvocable() {
  return std::is_invocable_v<is_sign_policy, dummy<Policy>>;
}

class IsSignPolicyTest_416 : public ::testing::Test {};

}  // namespace

TEST_F(IsSignPolicyTest_416, InvocableWhenPolicyDefinesSignPolicy_416) {
  EXPECT_TRUE(IsInvocable<PolicyWithSignPolicyInt>());
  EXPECT_TRUE(IsInvocable<PolicyWithSignPolicyVoid>());
}

TEST_F(IsSignPolicyTest_416, NotInvocableWhenPolicyDoesNotDefineSignPolicy_416) {
  EXPECT_FALSE(IsInvocable<PolicyWithoutSignPolicy>());
}

TEST_F(IsSignPolicyTest_416, ReturnsTrueForPolicyWithSignPolicy_416) {
  constexpr is_sign_policy pred{};

  // Verify it can be evaluated at compile time and yields true.
  constexpr bool result = pred(dummy<PolicyWithSignPolicyInt>{});
  static_assert(result, "is_sign_policy should return true for PolicyWithSignPolicyInt");
  EXPECT_TRUE(result);
}

TEST_F(IsSignPolicyTest_416, IsNoexceptForPolicyWithSignPolicy_416) {
  constexpr is_sign_policy pred{};
  EXPECT_TRUE(noexcept(pred(dummy<PolicyWithSignPolicyInt>{})));
}

TEST_F(IsSignPolicyTest_416, ResultTypeIsBoolWhenInvocable_416) {
  // Boundary/typing check: when invocable, it should be usable as a bool.
  using ResultT = decltype(std::declval<is_sign_policy>()(std::declval<dummy<PolicyWithSignPolicyInt>>()));
  EXPECT_TRUE((std::is_same_v<ResultT, bool>));
}