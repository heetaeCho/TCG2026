#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail;

// Define some test policy types to use with check_policy_validity
struct TestPolicyA {};
struct TestPolicyB {};
struct TestPolicyInt {};

class CheckPolicyValidityTest_411 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that check_policy_validity returns false for an empty detector_default_pair_list
// with a simple policy type
TEST_F(CheckPolicyValidityTest_411, ReturnsFalseForEmptyPairList_TestPolicyA_411) {
    constexpr bool result = check_policy_validity(dummy<TestPolicyA>{}, detector_default_pair_list<>{});
    EXPECT_FALSE(result);
}

// Test that check_policy_validity returns false for a different policy type
// with an empty detector_default_pair_list
TEST_F(CheckPolicyValidityTest_411, ReturnsFalseForEmptyPairList_TestPolicyB_411) {
    constexpr bool result = check_policy_validity(dummy<TestPolicyB>{}, detector_default_pair_list<>{});
    EXPECT_FALSE(result);
}

// Test that check_policy_validity returns false with yet another policy type
TEST_F(CheckPolicyValidityTest_411, ReturnsFalseForEmptyPairList_TestPolicyInt_411) {
    constexpr bool result = check_policy_validity(dummy<TestPolicyInt>{}, detector_default_pair_list<>{});
    EXPECT_FALSE(result);
}

// Test that the function is indeed constexpr - it can be used in a static_assert context
TEST_F(CheckPolicyValidityTest_411, IsConstexpr_411) {
    static_assert(check_policy_validity(dummy<TestPolicyA>{}, detector_default_pair_list<>{}) == false,
                  "check_policy_validity with empty pair list should be false at compile time");
    SUCCEED();
}

// Test that the function is noexcept as declared
TEST_F(CheckPolicyValidityTest_411, IsNoexcept_411) {
    constexpr bool is_noexcept = noexcept(
        check_policy_validity(dummy<TestPolicyA>{}, detector_default_pair_list<>{})
    );
    EXPECT_TRUE(is_noexcept);
}

// Test with int as policy type (built-in type)
TEST_F(CheckPolicyValidityTest_411, ReturnsFalseForBuiltInTypePolicy_411) {
    constexpr bool result = check_policy_validity(dummy<int>{}, detector_default_pair_list<>{});
    EXPECT_FALSE(result);
}

// Test with double as policy type (another built-in type)
TEST_F(CheckPolicyValidityTest_411, ReturnsFalseForDoublePolicy_411) {
    constexpr bool result = check_policy_validity(dummy<double>{}, detector_default_pair_list<>{});
    EXPECT_FALSE(result);
}

// Test that the return type is bool
TEST_F(CheckPolicyValidityTest_411, ReturnTypeisBool_411) {
    auto result = check_policy_validity(dummy<TestPolicyA>{}, detector_default_pair_list<>{});
    bool is_same = std::is_same<decltype(result), bool>::value;
    EXPECT_TRUE(is_same);
}
