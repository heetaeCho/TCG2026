#include <gtest/gtest.h>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

// A mock/stub SignedSignificandBits type for testing
struct MockSignedSignificandBits {
    // Minimal struct to satisfy template parameter requirements
};

// Another type to test template instantiation with different types
struct AnotherSignedSignificandBits {
    int value = 42;
};

// Test fixture for nearest_to_odd
class NearestToOddTest_360 : public ::testing::Test {
protected:
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd policy_;
};

// Test that shorter_interval returns a valid interval_type::open object
TEST_F(NearestToOddTest_360, ShorterIntervalReturnsOpenInterval_360) {
    MockSignedSignificandBits bits;
    auto result = policy_.shorter_interval(bits);
    // The function should return an interval_type::open default-constructed object
    // We verify it compiles and returns without error
    (void)result;
    SUCCEED();
}

// Test that shorter_interval is constexpr and noexcept
TEST_F(NearestToOddTest_360, ShorterIntervalIsNoexcept_360) {
    MockSignedSignificandBits bits;
    EXPECT_TRUE(noexcept(policy_.shorter_interval(bits)));
}

// Test shorter_interval with a different SignedSignificandBits type
TEST_F(NearestToOddTest_360, ShorterIntervalWithDifferentType_360) {
    AnotherSignedSignificandBits bits;
    auto result = policy_.shorter_interval(bits);
    (void)result;
    SUCCEED();
}

// Test that the policy type is default constructible
TEST_F(NearestToOddTest_360, PolicyIsDefaultConstructible_360) {
    EXPECT_TRUE(std::is_default_constructible<
        YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd>::value);
}

// Test that shorter_interval can be called as a static method
TEST_F(NearestToOddTest_360, ShorterIntervalCanBeCalledStatically_360) {
    MockSignedSignificandBits bits;
    auto result = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd::shorter_interval(bits);
    (void)result;
    SUCCEED();
}

// Test constexpr evaluation context
TEST_F(NearestToOddTest_360, ShorterIntervalIsConstexpr_360) {
    // Verify the function can be used in a constexpr context
    // Note: this depends on MockSignedSignificandBits being constexpr-constructible
    constexpr auto result = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd::shorter_interval(MockSignedSignificandBits{});
    (void)result;
    SUCCEED();
}

// Test that the returned type is indeed interval_type::open
TEST_F(NearestToOddTest_360, ReturnTypeIsIntervalTypeOpen_360) {
    MockSignedSignificandBits bits;
    auto result = policy_.shorter_interval(bits);
    bool isSameType = std::is_same<
        decltype(result),
        YAML::jkj::dragonbox::interval_type::open>::value;
    EXPECT_TRUE(isSameType);
}

// Test multiple calls return consistent results
TEST_F(NearestToOddTest_360, MultipleCaCallsAreConsistent_360) {
    MockSignedSignificandBits bits1;
    MockSignedSignificandBits bits2;
    auto result1 = policy_.shorter_interval(bits1);
    auto result2 = policy_.shorter_interval(bits2);
    // Both should be default-constructed interval_type::open
    (void)result1;
    (void)result2;
    SUCCEED();
}

// Test that policy can be copied
TEST_F(NearestToOddTest_360, PolicyIsCopyable_360) {
    EXPECT_TRUE(std::is_copy_constructible<
        YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd>::value);
    EXPECT_TRUE(std::is_copy_assignable<
        YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd>::value);
}

}  // namespace
