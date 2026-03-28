#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// ============================================================
// Test fixture
// ============================================================
class IsBinaryToDecimalRoundingPolicyTest_422 : public ::testing::Test {
protected:
    YAML::jkj::dragonbox::detail::is_binary_to_decimal_rounding_policy checker;
};

// A helper type that has the nested typedef expected by the policy checker.
struct ValidPolicy {
    using binary_to_decimal_rounding_policy = void;
};

// Another valid policy with a non-void nested type
struct ValidPolicyInt {
    using binary_to_decimal_rounding_policy = int;
};

// A type that does NOT have the nested typedef.
struct InvalidPolicy {};

// A type that has a similarly-named but wrong member (data member, not type alias).
struct WrongMemberPolicy {
    static constexpr int binary_to_decimal_rounding_policy = 0;
};

// A type that has a nested struct instead of a simple alias.
struct NestedStructPolicy {
    struct binary_to_decimal_rounding_policy {};
};

// Helper: SFINAE test – does operator() compile for a given Policy?
template <typename Checker, typename Policy, typename = void>
struct is_callable : std::false_type {};

template <typename Checker, typename Policy>
struct is_callable<
    Checker, Policy,
    decltype(void(std::declval<Checker>()(
        std::declval<YAML::jkj::dragonbox::detail::dummy<Policy>>()
    )))
> : std::true_type {};

// ============================================================
// Normal operation tests
// ============================================================

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, ReturnsTrueForValidPolicy_422) {
    // A type that defines binary_to_decimal_rounding_policy should be accepted
    constexpr bool result = checker(YAML::jkj::dragonbox::detail::dummy<ValidPolicy>{});
    EXPECT_TRUE(result);
}

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, ReturnsTrueForValidPolicyWithIntAlias_422) {
    constexpr bool result = checker(YAML::jkj::dragonbox::detail::dummy<ValidPolicyInt>{});
    EXPECT_TRUE(result);
}

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, ReturnsTrueForNestedStructPolicy_422) {
    constexpr bool result = checker(YAML::jkj::dragonbox::detail::dummy<NestedStructPolicy>{});
    EXPECT_TRUE(result);
}

// ============================================================
// Compile-time property tests (constexpr / noexcept)
// ============================================================

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, OperatorIsConstexpr_422) {
    // The result should be usable in a constexpr context.
    constexpr auto val = YAML::jkj::dragonbox::detail::is_binary_to_decimal_rounding_policy{}(
        YAML::jkj::dragonbox::detail::dummy<ValidPolicy>{});
    EXPECT_TRUE(val);
}

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, OperatorIsNoexcept_422) {
    // The operator() is declared noexcept; verify that.
    bool ne = noexcept(checker(YAML::jkj::dragonbox::detail::dummy<ValidPolicy>{}));
    EXPECT_TRUE(ne);
}

// ============================================================
// SFINAE / boundary tests
// ============================================================

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, SFINAESucceedsForValidPolicy_422) {
    bool callable = is_callable<
        YAML::jkj::dragonbox::detail::is_binary_to_decimal_rounding_policy,
        ValidPolicy>::value;
    EXPECT_TRUE(callable);
}

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, SFINAEFailsForInvalidPolicy_422) {
    // InvalidPolicy does not have the required nested type, so the overload
    // should be excluded by SFINAE.
    bool callable = is_callable<
        YAML::jkj::dragonbox::detail::is_binary_to_decimal_rounding_policy,
        InvalidPolicy>::value;
    EXPECT_FALSE(callable);
}

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, SFINAEFailsForWrongMemberPolicy_422) {
    // WrongMemberPolicy has a data member, not a type alias – should not match.
    bool callable = is_callable<
        YAML::jkj::dragonbox::detail::is_binary_to_decimal_rounding_policy,
        WrongMemberPolicy>::value;
    EXPECT_FALSE(callable);
}

// ============================================================
// Edge case: built-in / primitive types should not match
// ============================================================

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, SFINAEFailsForInt_422) {
    bool callable = is_callable<
        YAML::jkj::dragonbox::detail::is_binary_to_decimal_rounding_policy,
        int>::value;
    EXPECT_FALSE(callable);
}

TEST_F(IsBinaryToDecimalRoundingPolicyTest_422, SFINAEFailsForVoid_422) {
    bool callable = is_callable<
        YAML::jkj::dragonbox::detail::is_binary_to_decimal_rounding_policy,
        void>::value;
    EXPECT_FALSE(callable);
}

} // anonymous namespace
