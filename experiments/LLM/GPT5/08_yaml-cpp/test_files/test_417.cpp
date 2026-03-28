// File: ./TestProjects/yaml-cpp/test/dragonbox_is_trailing_zero_policy_test_417.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::is_trailing_zero_policy;
using YAML::jkj::dragonbox::detail::dummy;

// Policy that satisfies the SFINAE condition: has nested trailing_zero_policy.
struct PolicyWithTrailingZeroPolicy {
  using trailing_zero_policy = void;
};

// Policy that does NOT satisfy the SFINAE condition.
struct PolicyWithoutTrailingZeroPolicy {};

// Detect whether the constrained template operator()<P> exists (is well-formed).
template <typename P, typename = void>
struct HasTemplateOperatorOverload : std::false_type {};

template <typename P>
struct HasTemplateOperatorOverload<
    P, std::void_t<decltype(&is_trailing_zero_policy::template operator()<P>)>>
    : std::true_type {};

class IsTrailingZeroPolicyTest_417 : public ::testing::Test {};

}  // namespace

TEST_F(IsTrailingZeroPolicyTest_417, EllipsisOverloadReturnsFalseForArbitraryArgs_417) {
  constexpr is_trailing_zero_policy pred{};

  // Observable behavior from the provided implementation: operator()(...) returns false.
  static_assert(pred(0) == false, "ellipsis overload should return false");
  static_assert(pred(nullptr) == false, "ellipsis overload should return false");
  static_assert(pred("text") == false, "ellipsis overload should return false");

  EXPECT_FALSE(pred(0));
  EXPECT_FALSE(pred(nullptr));
  EXPECT_FALSE(pred("text"));
}

TEST_F(IsTrailingZeroPolicyTest_417, EllipsisOverloadIsNoexcept_417) {
  constexpr is_trailing_zero_policy pred{};
  static_assert(noexcept(pred(123)), "ellipsis overload must be noexcept");
  EXPECT_TRUE((noexcept(pred(123))));
}

TEST_F(IsTrailingZeroPolicyTest_417, TemplateOverloadExistsWhenPolicyHasTrailingZeroPolicy_417) {
  // Verify the constrained template operator() participates only when Policy::trailing_zero_policy exists.
  static_assert(HasTemplateOperatorOverload<PolicyWithTrailingZeroPolicy>::value,
                "template operator()<PolicyWithTrailingZeroPolicy> should exist");
  static_assert(!HasTemplateOperatorOverload<PolicyWithoutTrailingZeroPolicy>::value,
                "template operator()<PolicyWithoutTrailingZeroPolicy> should not exist");

  EXPECT_TRUE((HasTemplateOperatorOverload<PolicyWithTrailingZeroPolicy>::value));
  EXPECT_FALSE((HasTemplateOperatorOverload<PolicyWithoutTrailingZeroPolicy>::value));
}

TEST_F(IsTrailingZeroPolicyTest_417, CallWithDummyIsWellFormedAndReturnsBool_417) {
  constexpr is_trailing_zero_policy pred{};

  // Calling with dummy<PolicyWithTrailingZeroPolicy> should be well-formed (template overload available).
  // We do NOT assume the return value, only that it is a bool and usable in a constexpr context.
  constexpr bool with_tzp = pred(dummy<PolicyWithTrailingZeroPolicy>{});
  (void)with_tzp;

  static_assert(std::is_same<decltype(pred(dummy<PolicyWithTrailingZeroPolicy>{})), bool>::value,
                "operator() must return bool");
  static_assert(noexcept(pred(dummy<PolicyWithTrailingZeroPolicy>{})),
                "operator() with dummy must be noexcept");

  // For a policy without trailing_zero_policy, the constrained template overload should not exist;
  // the ellipsis overload must still make the call well-formed, and per provided code it returns false.
  constexpr bool without_tzp = pred(dummy<PolicyWithoutTrailingZeroPolicy>{});
  static_assert(without_tzp == false, "ellipsis overload should return false");
  EXPECT_FALSE(without_tzp);
}