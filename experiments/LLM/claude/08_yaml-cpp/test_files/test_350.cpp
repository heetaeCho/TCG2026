#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test that include_right_endpoint returns false for the open interval type
TEST(OpenIntervalType_350, IncludeRightEndpointReturnsFalse_350) {
    constexpr bool result = open::include_right_endpoint();
    EXPECT_FALSE(result);
}

// Test that include_left_endpoint returns false for the open interval type
TEST(OpenIntervalType_350, IncludeLeftEndpointReturnsFalse_350) {
    constexpr bool result = open::include_left_endpoint();
    EXPECT_FALSE(result);
}

// Test that the functions are noexcept
TEST(OpenIntervalType_350, IncludeRightEndpointIsNoexcept_350) {
    EXPECT_TRUE(noexcept(open::include_right_endpoint()));
}

TEST(OpenIntervalType_350, IncludeLeftEndpointIsNoexcept_350) {
    EXPECT_TRUE(noexcept(open::include_left_endpoint()));
}

// Test that the functions are constexpr and can be used in compile-time contexts
TEST(OpenIntervalType_350, IncludeRightEndpointIsConstexpr_350) {
    static_assert(open::include_right_endpoint() == false, "include_right_endpoint should be false at compile time");
    SUCCEED();
}

TEST(OpenIntervalType_350, IncludeLeftEndpointIsConstexpr_350) {
    static_assert(open::include_left_endpoint() == false, "include_left_endpoint should be false at compile time");
    SUCCEED();
}

// Test that an instance of open can be created and methods called on it
TEST(OpenIntervalType_350, InstanceMethodCalls_350) {
    open instance;
    EXPECT_FALSE(instance.include_left_endpoint());
    EXPECT_FALSE(instance.include_right_endpoint());
}

// Test consistency: both endpoints should be excluded for an open interval
TEST(OpenIntervalType_350, BothEndpointsExcluded_350) {
    EXPECT_EQ(open::include_left_endpoint(), open::include_right_endpoint());
    EXPECT_FALSE(open::include_left_endpoint() || open::include_right_endpoint());
}
