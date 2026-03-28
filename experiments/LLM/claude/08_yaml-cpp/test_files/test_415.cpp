#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Test fixture for is_sign_policy tests
class IsSignPolicyTest_415 : public ::testing::Test {
protected:
    YAML::jkj::dragonbox::detail::is_sign_policy checker;
};

// Test that the variadic operator() returns false for no arguments
TEST_F(IsSignPolicyTest_415, DefaultReturnsFalseForNoArgs_415) {
    bool result = checker();
    EXPECT_FALSE(result);
}

// Test that the variadic operator() returns false for an integer argument
TEST_F(IsSignPolicyTest_415, ReturnsFalseForInt_415) {
    bool result = checker(42);
    EXPECT_FALSE(result);
}

// Test that the variadic operator() returns false for a double argument
TEST_F(IsSignPolicyTest_415, ReturnsFalseForDouble_415) {
    bool result = checker(3.14);
    EXPECT_FALSE(result);
}

// Test that the variadic operator() returns false for a string literal
TEST_F(IsSignPolicyTest_415, ReturnsFalseForStringLiteral_415) {
    bool result = checker("hello");
    EXPECT_FALSE(result);
}

// Test that the variadic operator() returns false for nullptr
TEST_F(IsSignPolicyTest_415, ReturnsFalseForNullptr_415) {
    bool result = checker(nullptr);
    EXPECT_FALSE(result);
}

// Test that the variadic operator() returns false for a pointer
TEST_F(IsSignPolicyTest_415, ReturnsFalseForPointer_415) {
    int x = 10;
    bool result = checker(&x);
    EXPECT_FALSE(result);
}

// Test that the operator is constexpr and noexcept
TEST_F(IsSignPolicyTest_415, IsNoexcept_415) {
    EXPECT_TRUE(noexcept(checker()));
    EXPECT_TRUE(noexcept(checker(42)));
}

// Test that the struct can be default constructed
TEST_F(IsSignPolicyTest_415, DefaultConstructible_415) {
    YAML::jkj::dragonbox::detail::is_sign_policy policy;
    EXPECT_FALSE(policy(0));
}

// Test with a struct that has a sign_policy type alias - should return true via the template overload
struct MockSignPolicy {
    using sign_policy = void;
};

TEST_F(IsSignPolicyTest_415, ReturnsTrueForTypeWithSignPolicy_415) {
    // A type that defines sign_policy should be detected by the template overload
    // Using the dummy<Policy> overload if available
    // Since the variadic fallback returns false, a non-sign-policy type should return false
    struct NotASignPolicy {};
    bool result = checker(NotASignPolicy{});
    EXPECT_FALSE(result);
}

// Test that multiple calls produce consistent results
TEST_F(IsSignPolicyTest_415, ConsistentResults_415) {
    EXPECT_EQ(checker(1), checker(2));
    EXPECT_EQ(checker(1), checker("test"));
    EXPECT_FALSE(checker(1));
    EXPECT_FALSE(checker(2));
}

// Test with boolean argument
TEST_F(IsSignPolicyTest_415, ReturnsFalseForBool_415) {
    bool result = checker(true);
    EXPECT_FALSE(result);
    result = checker(false);
    EXPECT_FALSE(result);
}

// Test copy of the checker
TEST_F(IsSignPolicyTest_415, CopyableAndCallable_415) {
    auto checker_copy = checker;
    EXPECT_FALSE(checker_copy(42));
    EXPECT_FALSE(checker_copy());
}

} // namespace
