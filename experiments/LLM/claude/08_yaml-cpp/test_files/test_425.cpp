#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// A dummy policy that has the preferred_integer_types_policy tag
struct PolicyWithTag {
    using preferred_integer_types_policy = void;
};

// A dummy policy that does NOT have the preferred_integer_types_policy tag
struct PolicyWithoutTag {
    int some_member = 42;
};

// Test fixture
class IsPreferredIntegerTypesPolicyTest_425 : public ::testing::Test {
protected:
    YAML::jkj::dragonbox::detail::is_preferred_integer_types_policy checker;
};

// Test that the variadic fallback operator() returns false for an int
TEST_F(IsPreferredIntegerTypesPolicyTest_425, ReturnsFalseForInt_425) {
    EXPECT_FALSE(checker(0));
}

// Test that the variadic fallback operator() returns false for a double
TEST_F(IsPreferredIntegerTypesPolicyTest_425, ReturnsFalseForDouble_425) {
    EXPECT_FALSE(checker(3.14));
}

// Test that the variadic fallback operator() returns false for a pointer
TEST_F(IsPreferredIntegerTypesPolicyTest_425, ReturnsFalseForNullptr_425) {
    EXPECT_FALSE(checker(nullptr));
}

// Test that the variadic fallback operator() returns false for a string literal
TEST_F(IsPreferredIntegerTypesPolicyTest_425, ReturnsFalseForStringLiteral_425) {
    EXPECT_FALSE(checker("hello"));
}

// Test that the variadic fallback returns false for a policy without the tag
TEST_F(IsPreferredIntegerTypesPolicyTest_425, ReturnsFalseForPolicyWithoutTag_425) {
    PolicyWithoutTag p;
    // This should use the variadic fallback since PolicyWithoutTag
    // does not have preferred_integer_types_policy typedef
    EXPECT_FALSE(checker(p));
}

// Test that the operator() is constexpr and noexcept for the fallback
TEST_F(IsPreferredIntegerTypesPolicyTest_425, FallbackIsNoexcept_425) {
    EXPECT_TRUE(noexcept(checker(42)));
}

// Test with no arguments (variadic accepts zero args too)
TEST_F(IsPreferredIntegerTypesPolicyTest_425, ReturnsFalseForNoArgs_425) {
    EXPECT_FALSE(checker());
}

// Test with multiple arguments via the variadic fallback
TEST_F(IsPreferredIntegerTypesPolicyTest_425, ReturnsFalseForMultipleArgs_425) {
    EXPECT_FALSE(checker(1, 2, 3));
}

// Test constexpr evaluation of the fallback
TEST_F(IsPreferredIntegerTypesPolicyTest_425, ConstexprFallbackEvaluation_425) {
    constexpr YAML::jkj::dragonbox::detail::is_preferred_integer_types_policy constexpr_checker;
    constexpr bool result = constexpr_checker(100);
    EXPECT_FALSE(result);
}

} // namespace
