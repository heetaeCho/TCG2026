#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Test fixture for is_decimal_to_binary_rounding_policy
class IsDecimalToBinaryRoundingPolicyTest_419 : public ::testing::Test {
protected:
    YAML::jkj::dragonbox::detail::is_decimal_to_binary_rounding_policy checker;
};

// Test that the default (variadic) overload returns false for arbitrary types
TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, ReturnsFalseForInt_419) {
    bool result = checker(0);
    EXPECT_FALSE(result);
}

TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, ReturnsFalseForDouble_419) {
    bool result = checker(0.0);
    EXPECT_FALSE(result);
}

TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, ReturnsFalseForNullptr_419) {
    bool result = checker(nullptr);
    EXPECT_FALSE(result);
}

TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, ReturnsFalseForCharPointer_419) {
    const char* str = "test";
    bool result = checker(str);
    EXPECT_FALSE(result);
}

TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, ReturnsFalseForNoArgs_419) {
    // Calling with no arguments should still invoke the variadic overload
    bool result = checker();
    EXPECT_FALSE(result);
}

// Test that a struct without the decimal_to_binary_rounding_policy typedef returns false
struct NonPolicy {
    int value;
};

TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, ReturnsFalseForNonPolicyStruct_419) {
    // NonPolicy doesn't have decimal_to_binary_rounding_policy, so variadic overload is selected
    // We pass it by converting to the variadic parameter
    NonPolicy np{};
    bool result = checker(np);
    EXPECT_FALSE(result);
}

// Test with a struct that has the decimal_to_binary_rounding_policy typedef
// This should match the template overload and return true
struct MockDecimalToBinaryPolicy {
    using decimal_to_binary_rounding_policy = void;
};

TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, ReturnsTrueForPolicyWithTypedef_419) {
    // The template overload should be selected for types that define decimal_to_binary_rounding_policy
    // Using dummy<Policy> mechanism from the interface
    MockDecimalToBinaryPolicy policy{};
    // Depending on how dummy is defined, the SFINAE overload should detect the typedef
    // and return true. We test observable behavior:
    // If the template overload exists and works, it should return true.
    // However, since we can only call through operator(), we rely on the overload resolution.
    // Note: The exact behavior depends on the dummy template and overload resolution.
    // We test what's observable.
    bool result = checker(policy);
    // If the SFINAE overload is properly implemented, this should be true
    // But if it falls through to variadic, it would be false
    // We test both possibilities based on what the interface suggests
    // The interface suggests the template overload returns true for types with the typedef
    EXPECT_TRUE(result);
}

// Test constexpr nature of the operator
TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, IsConstexprFalseForBasicTypes_419) {
    constexpr YAML::jkj::dragonbox::detail::is_decimal_to_binary_rounding_policy constexpr_checker;
    constexpr bool result = constexpr_checker(42);
    EXPECT_FALSE(result);
    static_assert(!constexpr_checker(42), "Should be false for int");
}

// Test that the checker itself is noexcept
TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, OperatorIsNoexcept_419) {
    EXPECT_TRUE(noexcept(checker(0)));
    EXPECT_TRUE(noexcept(checker()));
}

// Test with multiple arguments (variadic)
TEST_F(IsDecimalToBinaryRoundingPolicyTest_419, ReturnsFalseForMultipleArgs_419) {
    bool result = checker(1, 2, 3);
    EXPECT_FALSE(result);
}

}  // namespace
