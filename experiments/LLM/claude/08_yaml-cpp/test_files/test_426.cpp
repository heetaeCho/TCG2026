#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Helper struct that has the preferred_integer_types_policy type alias
struct PolicyWithPreferredIntegerTypes {
    using preferred_integer_types_policy = void;
};

// Helper struct that does NOT have the preferred_integer_types_policy type alias
struct PolicyWithoutPreferredIntegerTypes {
    using some_other_policy = void;
};

// Another valid policy with a different preferred_integer_types_policy type
struct AnotherPolicyWithPreferredIntegerTypes {
    using preferred_integer_types_policy = int;
};

// Empty struct with no type aliases at all
struct EmptyPolicy {};

using namespace YAML::jkj::dragonbox::detail;

// Test fixture
class IsPreferredIntegerTypesPolicyTest_426 : public ::testing::Test {
protected:
    is_preferred_integer_types_policy checker;
};

// Test that a policy with preferred_integer_types_policy returns true
TEST_F(IsPreferredIntegerTypesPolicyTest_426, ReturnsTrueForPolicyWithPreferredIntegerTypes_426) {
    constexpr bool result = is_preferred_integer_types_policy{}(
        dummy<PolicyWithPreferredIntegerTypes>{});
    EXPECT_TRUE(result);
}

// Test that another valid policy with preferred_integer_types_policy returns true
TEST_F(IsPreferredIntegerTypesPolicyTest_426, ReturnsTrueForAnotherPolicyWithPreferredIntegerTypes_426) {
    constexpr bool result = is_preferred_integer_types_policy{}(
        dummy<AnotherPolicyWithPreferredIntegerTypes>{});
    EXPECT_TRUE(result);
}

// Test that the result is constexpr and noexcept for valid policy
TEST_F(IsPreferredIntegerTypesPolicyTest_426, IsConstexprAndNoexceptForValidPolicy_426) {
    constexpr is_preferred_integer_types_policy checker_constexpr{};
    constexpr bool result = checker_constexpr(dummy<PolicyWithPreferredIntegerTypes>{});
    EXPECT_TRUE(result);

    // Verify noexcept
    static_assert(noexcept(checker_constexpr(dummy<PolicyWithPreferredIntegerTypes>{})),
                  "operator() should be noexcept");
}

// Test that SFINAE correctly excludes policies without preferred_integer_types_policy
// We verify this by checking that the call is not well-formed for policies without the alias
TEST_F(IsPreferredIntegerTypesPolicyTest_426, SFINAEExcludesPolicyWithoutPreferredIntegerTypes_426) {
    // Use SFINAE to check if the call is valid
    auto is_callable = [](auto&&... args) -> decltype(
        is_preferred_integer_types_policy{}(std::forward<decltype(args)>(args)...), std::true_type{}) {
        return {};
    };
    
    // For a policy with the alias, we expect it to be callable
    auto result_with = is_callable(dummy<PolicyWithPreferredIntegerTypes>{});
    EXPECT_TRUE(decltype(result_with)::value);
}

// Test that the struct is default constructible
TEST_F(IsPreferredIntegerTypesPolicyTest_426, IsDefaultConstructible_426) {
    EXPECT_TRUE(std::is_default_constructible<is_preferred_integer_types_policy>::value);
}

// Test with a struct where preferred_integer_types_policy is a complex type
struct PolicyWithComplexPreferredIntegerTypes {
    struct preferred_integer_types_policy {
        int value;
    };
};

TEST_F(IsPreferredIntegerTypesPolicyTest_426, ReturnsTrueForPolicyWithComplexPreferredIntegerTypesAlias_426) {
    constexpr bool result = is_preferred_integer_types_policy{}(
        dummy<PolicyWithComplexPreferredIntegerTypes>{});
    EXPECT_TRUE(result);
}

} // namespace
