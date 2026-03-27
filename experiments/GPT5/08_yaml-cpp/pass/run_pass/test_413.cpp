// File: test_check_policy_list_validity_413.cpp

#include <gtest/gtest.h>

#include <array>
#include <type_traits>
#include <utility>

// Target header (as provided in the prompt)
#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::check_policy_list_validity;

struct SimplePolicyListLike_413 {
  int a = 0;
  double b = 0.0;
};

struct MoveOnlyPolicyListLike_413 {
  MoveOnlyPolicyListLike_413() = default;
  MoveOnlyPolicyListLike_413(const MoveOnlyPolicyListLike_413&) = delete;
  MoveOnlyPolicyListLike_413& operator=(const MoveOnlyPolicyListLike_413&) = delete;
  MoveOnlyPolicyListLike_413(MoveOnlyPolicyListLike_413&&) noexcept = default;
  MoveOnlyPolicyListLike_413& operator=(MoveOnlyPolicyListLike_413&&) noexcept = default;
};

struct LargePolicyListLike_413 {
  std::array<int, 1024> data{};
};

}  // namespace

TEST(DragonboxPolicyListValidityTest_413, ReturnsTrueForInt_413) {
  EXPECT_TRUE(check_policy_list_validity(0));
}

TEST(DragonboxPolicyListValidityTest_413, ReturnsTrueForSimpleStruct_413) {
  SimplePolicyListLike_413 v;
  EXPECT_TRUE(check_policy_list_validity(v));
}

TEST(DragonboxPolicyListValidityTest_413, ReturnsTrueForConstArgument_413) {
  const SimplePolicyListLike_413 v{};
  EXPECT_TRUE(check_policy_list_validity(v));
}

TEST(DragonboxPolicyListValidityTest_413, ReturnsTrueForRvalueTemporary_413) {
  EXPECT_TRUE(check_policy_list_validity(SimplePolicyListLike_413{}));
}

TEST(DragonboxPolicyListValidityTest_413, AcceptsMoveOnlyType_413) {
  // Passing an rvalue allows move construction into the by-value parameter.
  EXPECT_TRUE(check_policy_list_validity(MoveOnlyPolicyListLike_413{}));
}

TEST(DragonboxPolicyListValidityTest_413, HandlesLargeValueTypeByValue_413) {
  LargePolicyListLike_413 big;
  big.data[0] = 123;
  big.data[1023] = 456;
  EXPECT_TRUE(check_policy_list_validity(big));
}

TEST(DragonboxPolicyListValidityTest_413, IsNoexcept_413) {
  static_assert(noexcept(check_policy_list_validity(0)),
                "check_policy_list_validity should be noexcept for int arguments");
  static_assert(noexcept(check_policy_list_validity(SimplePolicyListLike_413{})),
                "check_policy_list_validity should be noexcept for simple struct arguments");

  // Also assert at runtime (doesn't prove noexcept, but keeps the test consistent with others).
  EXPECT_TRUE(noexcept(check_policy_list_validity(0)));
}

TEST(DragonboxPolicyListValidityTest_413, UsableInConstexprContext_413) {
  // Verify it can be evaluated in a constant expression context.
  constexpr bool kOk1 = check_policy_list_validity(0);
  static_assert(kOk1, "Expected check_policy_list_validity(0) to be true at compile time");

  constexpr SimplePolicyListLike_413 kObj{};
  constexpr bool kOk2 = check_policy_list_validity(kObj);
  static_assert(kOk2, "Expected check_policy_list_validity(obj) to be true at compile time");

  EXPECT_TRUE(kOk1);
  EXPECT_TRUE(kOk2);
}