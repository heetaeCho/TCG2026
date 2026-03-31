#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Helper struct that HAS a trailing_zero_policy type alias
struct PolicyWithTrailingZero {
    using trailing_zero_policy = void;
};

// Helper struct that does NOT have a trailing_zero_policy type alias
struct PolicyWithoutTrailingZero {
    using some_other_policy = void;
};

// Another valid policy with a different trailing_zero_policy type
struct PolicyWithIntTrailingZero {
    using trailing_zero_policy = int;
};

// Empty struct with no type aliases at all
struct EmptyPolicy {};

using namespace YAML::jkj::dragonbox::detail;

// Test fixture
class IsTrailingZeroPolicyTest_418 : public ::testing::Test {
protected:
    is_trailing_zero_policy checker;
};

// Test that a policy with trailing_zero_policy type alias returns true
TEST_F(IsTrailingZeroPolicyTest_418, ReturnsTrueForPolicyWithTrailingZeroPolicy_418) {
    constexpr is_trailing_zero_policy c;
    constexpr bool result = c(dummy<PolicyWithTrailingZero>{});
    EXPECT_TRUE(result);
}

// Test that a policy with a different trailing_zero_policy type still returns true
TEST_F(IsTrailingZeroPolicyTest_418, ReturnsTrueForPolicyWithIntTrailingZeroPolicy_418) {
    constexpr is_trailing_zero_policy c;
    constexpr bool result = c(dummy<PolicyWithIntTrailingZero>{});
    EXPECT_TRUE(result);
}

// Test that the result is constexpr and noexcept
TEST_F(IsTrailingZeroPolicyTest_418, IsConstexprAndNoexcept_418) {
    constexpr is_trailing_zero_policy c;
    // Verify noexcept
    static_assert(noexcept(c(dummy<PolicyWithTrailingZero>{})),
                  "operator() should be noexcept");
    // Verify constexpr
    constexpr bool result = c(dummy<PolicyWithTrailingZero>{});
    EXPECT_TRUE(result);
}

// Test SFINAE: operator() should not be callable for a policy without trailing_zero_policy
// We verify this through a type trait check
TEST_F(IsTrailingZeroPolicyTest_418, SFINAEExcludesPolicyWithoutTrailingZeroPolicy_418) {
    // Use SFINAE to check if the call is valid
    auto is_callable = [](auto&& checker, auto&& arg) -> decltype(checker(arg), std::true_type{}) {
        return {};
    };
    
    // For PolicyWithTrailingZero, it should be callable
    auto callable_with = std::is_invocable<is_trailing_zero_policy, dummy<PolicyWithTrailingZero>>::value;
    EXPECT_TRUE(callable_with);
    
    // For PolicyWithoutTrailingZero, it should NOT be callable (SFINAE)
    auto callable_without = std::is_invocable<is_trailing_zero_policy, dummy<PolicyWithoutTrailingZero>>::value;
    EXPECT_FALSE(callable_without);
}

// Test SFINAE: operator() should not be callable for an empty policy
TEST_F(IsTrailingZeroPolicyTest_418, SFINAEExcludesEmptyPolicy_418) {
    auto callable_empty = std::is_invocable<is_trailing_zero_policy, dummy<EmptyPolicy>>::value;
    EXPECT_FALSE(callable_empty);
}

// Test that the struct is default constructible
TEST_F(IsTrailingZeroPolicyTest_418, IsDefaultConstructible_418) {
    EXPECT_TRUE(std::is_default_constructible<is_trailing_zero_policy>::value);
}

// Test that the return type is bool
TEST_F(IsTrailingZeroPolicyTest_418, ReturnTypeisBool_418) {
    using ReturnType = decltype(std::declval<is_trailing_zero_policy>()(dummy<PolicyWithTrailingZero>{}));
    EXPECT_TRUE((std::is_same<ReturnType, bool>::value));
}

// Test multiple invocations return consistent results
TEST_F(IsTrailingZeroPolicyTest_418, ConsistentResultsOnMultipleInvocations_418) {
    is_trailing_zero_policy c;
    bool result1 = c(dummy<PolicyWithTrailingZero>{});
    bool result2 = c(dummy<PolicyWithTrailingZero>{});
    EXPECT_EQ(result1, result2);
    EXPECT_TRUE(result1);
}

} // anonymous namespace
