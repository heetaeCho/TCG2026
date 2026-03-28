#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// A policy type that has the decimal_to_binary_rounding_policy type alias
struct ValidDecimalToBinaryPolicy {
    using decimal_to_binary_rounding_policy = void;
};

// A policy type that does NOT have the decimal_to_binary_rounding_policy type alias
struct InvalidPolicy {
    using some_other_policy = void;
};

// A policy type with a non-void decimal_to_binary_rounding_policy
struct ValidPolicyWithIntAlias {
    using decimal_to_binary_rounding_policy = int;
};

// A completely empty struct
struct EmptyPolicy {};

// Helper to detect if the operator() is valid via SFINAE
template <typename Checker, typename Policy, typename = void>
struct is_callable : std::false_type {};

template <typename Checker, typename Policy>
struct is_callable<Checker, Policy,
    std::void_t<decltype(std::declval<Checker>()(
        std::declval<YAML::jkj::dragonbox::detail::dummy<Policy>>()))>>
    : std::true_type {};

using IsDecimalToBinaryRoundingPolicy =
    YAML::jkj::dragonbox::detail::is_decimal_to_binary_rounding_policy;

// Test fixture
class IsDecimalToBinaryRoundingPolicyTest_420 : public ::testing::Test {
protected:
    IsDecimalToBinaryRoundingPolicy checker;
};

// Test that a valid policy (with decimal_to_binary_rounding_policy typedef) returns true
TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, ReturnsTrueForValidPolicy_420) {
    constexpr auto result = IsDecimalToBinaryRoundingPolicy{}(
        YAML::jkj::dragonbox::detail::dummy<ValidDecimalToBinaryPolicy>{});
    EXPECT_TRUE(result);
}

// Test that a valid policy with int alias also returns true
TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, ReturnsTrueForValidPolicyWithIntAlias_420) {
    constexpr auto result = IsDecimalToBinaryRoundingPolicy{}(
        YAML::jkj::dragonbox::detail::dummy<ValidPolicyWithIntAlias>{});
    EXPECT_TRUE(result);
}

// Test that the operator() is callable with a valid policy type (SFINAE check)
TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, IsCallableWithValidPolicy_420) {
    bool callable = is_callable<IsDecimalToBinaryRoundingPolicy, ValidDecimalToBinaryPolicy>::value;
    EXPECT_TRUE(callable);
}

// Test that the operator() is NOT callable with an invalid policy type (SFINAE should reject)
TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, IsNotCallableWithInvalidPolicy_420) {
    bool callable = is_callable<IsDecimalToBinaryRoundingPolicy, InvalidPolicy>::value;
    EXPECT_FALSE(callable);
}

// Test that the operator() is NOT callable with an empty policy type
TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, IsNotCallableWithEmptyPolicy_420) {
    bool callable = is_callable<IsDecimalToBinaryRoundingPolicy, EmptyPolicy>::value;
    EXPECT_FALSE(callable);
}

// Test that the result is constexpr (compile-time evaluable)
TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, ResultIsConstexpr_420) {
    constexpr IsDecimalToBinaryRoundingPolicy constexpr_checker{};
    constexpr bool result = constexpr_checker(
        YAML::jkj::dragonbox::detail::dummy<ValidDecimalToBinaryPolicy>{});
    EXPECT_TRUE(result);
}

// Test that the operator() is noexcept for a valid policy
TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, OperatorIsNoexceptForValidPolicy_420) {
    bool is_noexcept = noexcept(checker(
        YAML::jkj::dragonbox::detail::dummy<ValidDecimalToBinaryPolicy>{}));
    EXPECT_TRUE(is_noexcept);
}

// Test that the checker is default constructible
TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, IsDefaultConstructible_420) {
    EXPECT_TRUE(std::is_default_constructible<IsDecimalToBinaryRoundingPolicy>::value);
}

// Test with a struct that has decimal_to_binary_rounding_policy as a nested struct
struct PolicyWithNestedStruct {
    struct decimal_to_binary_rounding_policy {};
};

TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, ReturnsTrueForPolicyWithNestedStruct_420) {
    constexpr auto result = IsDecimalToBinaryRoundingPolicy{}(
        YAML::jkj::dragonbox::detail::dummy<PolicyWithNestedStruct>{});
    EXPECT_TRUE(result);
}

// Test that multiple calls yield consistent results
TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, ConsistentResults_420) {
    auto result1 = checker(
        YAML::jkj::dragonbox::detail::dummy<ValidDecimalToBinaryPolicy>{});
    auto result2 = checker(
        YAML::jkj::dragonbox::detail::dummy<ValidDecimalToBinaryPolicy>{});
    EXPECT_EQ(result1, result2);
    EXPECT_TRUE(result1);
}

} // anonymous namespace
