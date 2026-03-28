#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

// Test suite for check_policy_list_validity function
class CheckPolicyListValidityTest_413 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the function returns true when called with no arguments equivalent
// (i.e., with a default-constructible type)
TEST_F(CheckPolicyListValidityTest_413, ReturnsTrueWithEmptyStruct_413) {
    struct EmptyList {};
    constexpr bool result = YAML::jkj::dragonbox::detail::check_policy_list_validity(EmptyList{});
    EXPECT_TRUE(result);
}

// Test that the function is constexpr and evaluates at compile time
TEST_F(CheckPolicyListValidityTest_413, IsConstexpr_413) {
    struct SomeType {};
    constexpr bool result = YAML::jkj::dragonbox::detail::check_policy_list_validity(SomeType{});
    static_assert(result == true, "check_policy_list_validity should return true at compile time");
    EXPECT_TRUE(result);
}

// Test that the function is noexcept
TEST_F(CheckPolicyListValidityTest_413, IsNoexcept_413) {
    struct SomeType {};
    EXPECT_TRUE(noexcept(YAML::jkj::dragonbox::detail::check_policy_list_validity(SomeType{})));
}

// Test with an int as the template parameter
TEST_F(CheckPolicyListValidityTest_413, ReturnsTrueWithInt_413) {
    constexpr bool result = YAML::jkj::dragonbox::detail::check_policy_list_validity(0);
    EXPECT_TRUE(result);
}

// Test with a double as the template parameter
TEST_F(CheckPolicyListValidityTest_413, ReturnsTrueWithDouble_413) {
    constexpr bool result = YAML::jkj::dragonbox::detail::check_policy_list_validity(0.0);
    EXPECT_TRUE(result);
}

// Test with a char as the template parameter
TEST_F(CheckPolicyListValidityTest_413, ReturnsTrueWithChar_413) {
    constexpr bool result = YAML::jkj::dragonbox::detail::check_policy_list_validity('a');
    EXPECT_TRUE(result);
}

// Test with a boolean as the template parameter
TEST_F(CheckPolicyListValidityTest_413, ReturnsTrueWithBool_413) {
    constexpr bool result = YAML::jkj::dragonbox::detail::check_policy_list_validity(true);
    EXPECT_TRUE(result);
}

// Test with a struct containing data members
TEST_F(CheckPolicyListValidityTest_413, ReturnsTrueWithStructWithMembers_413) {
    struct StructWithMembers {
        int x = 0;
        double y = 0.0;
    };
    constexpr bool result = YAML::jkj::dragonbox::detail::check_policy_list_validity(StructWithMembers{});
    EXPECT_TRUE(result);
}

// Test runtime call also returns true
TEST_F(CheckPolicyListValidityTest_413, ReturnsTrueAtRuntime_413) {
    struct RuntimeType {};
    RuntimeType rt;
    bool result = YAML::jkj::dragonbox::detail::check_policy_list_validity(rt);
    EXPECT_TRUE(result);
}

// Test with nullptr_t
TEST_F(CheckPolicyListValidityTest_413, ReturnsTrueWithNullptrT_413) {
    constexpr bool result = YAML::jkj::dragonbox::detail::check_policy_list_validity(nullptr);
    EXPECT_TRUE(result);
}
