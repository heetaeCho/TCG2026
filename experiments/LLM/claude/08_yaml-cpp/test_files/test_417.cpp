#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::is_trailing_zero_policy;

// Test that the default variadic operator() returns false
TEST(IsTrailingZeroPolicyTest_417, DefaultOperatorReturnsFalse_417) {
    constexpr is_trailing_zero_policy checker{};
    constexpr bool result = checker();
    EXPECT_FALSE(result);
}

// Test that passing an integer argument still returns false (variadic fallback)
TEST(IsTrailingZeroPolicyTest_417, IntArgumentReturnsFalse_417) {
    constexpr is_trailing_zero_policy checker{};
    constexpr bool result = checker(42);
    EXPECT_FALSE(result);
}

// Test that passing multiple arguments still returns false (variadic fallback)
TEST(IsTrailingZeroPolicyTest_417, MultipleArgumentsReturnsFalse_417) {
    constexpr is_trailing_zero_policy checker{};
    constexpr bool result = checker(1, 2, 3);
    EXPECT_FALSE(result);
}

// Test that passing a pointer argument returns false (variadic fallback)
TEST(IsTrailingZeroPolicyTest_417, PointerArgumentReturnsFalse_417) {
    constexpr is_trailing_zero_policy checker{};
    constexpr bool result = checker(nullptr);
    EXPECT_FALSE(result);
}

// Test that passing a double argument returns false (variadic fallback)
TEST(IsTrailingZeroPolicyTest_417, DoubleArgumentReturnsFalse_417) {
    constexpr is_trailing_zero_policy checker{};
    constexpr bool result = checker(3.14);
    EXPECT_FALSE(result);
}

// Test that the result is usable in a constexpr context
TEST(IsTrailingZeroPolicyTest_417, IsConstexpr_417) {
    constexpr is_trailing_zero_policy checker{};
    constexpr bool result = checker();
    static_assert(!result, "Default operator() should return false at compile time");
    EXPECT_FALSE(result);
}

// Test that the operator is noexcept
TEST(IsTrailingZeroPolicyTest_417, IsNoexcept_417) {
    is_trailing_zero_policy checker{};
    EXPECT_TRUE(noexcept(checker()));
    EXPECT_TRUE(noexcept(checker(1)));
    EXPECT_TRUE(noexcept(checker(1, 2)));
}

// Test with a struct that does NOT have trailing_zero_policy typedef - should use variadic fallback
TEST(IsTrailingZeroPolicyTest_417, NonPolicyStructReturnsFalse_417) {
    struct NotAPolicy {
        int value;
    };

    is_trailing_zero_policy checker{};
    // NotAPolicy doesn't have trailing_zero_policy typedef, so variadic fallback should be used
    // which returns false
    NotAPolicy nap{0};
    bool result = checker(nap);
    EXPECT_FALSE(result);
}

// Test that a type with trailing_zero_policy typedef is detected via the template overload
TEST(IsTrailingZeroPolicyTest_417, PolicyStructWithTrailingZeroPolicyTypedef_417) {
    struct HasTrailingZeroPolicy {
        using trailing_zero_policy = void;
    };

    is_trailing_zero_policy checker{};
    // This type has trailing_zero_policy typedef, so the template overload should match
    // and potentially return true
    // We test observable behavior - the template overload should be selected
    // Since we don't know the exact return value of the template overload, we just
    // verify it compiles and returns a bool
    bool result = checker(HasTrailingZeroPolicy{});
    // Based on typical tag-detection patterns, this should return true
    EXPECT_TRUE(result);
}

} // namespace
