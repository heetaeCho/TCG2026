#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test that include_right_endpoint returns true for closed interval
TEST(ClosedIntervalTest_348, IncludeRightEndpointReturnsTrue_348) {
    constexpr bool result = closed::include_right_endpoint();
    EXPECT_TRUE(result);
}

// Test that include_left_endpoint returns true for closed interval
TEST(ClosedIntervalTest_348, IncludeLeftEndpointReturnsTrue_348) {
    constexpr bool result = closed::include_left_endpoint();
    EXPECT_TRUE(result);
}

// Test that include_right_endpoint is noexcept
TEST(ClosedIntervalTest_348, IncludeRightEndpointIsNoexcept_348) {
    EXPECT_TRUE(noexcept(closed::include_right_endpoint()));
}

// Test that include_left_endpoint is noexcept
TEST(ClosedIntervalTest_348, IncludeLeftEndpointIsNoexcept_348) {
    EXPECT_TRUE(noexcept(closed::include_left_endpoint()));
}

// Test that include_right_endpoint is constexpr (compile-time evaluable)
TEST(ClosedIntervalTest_348, IncludeRightEndpointIsConstexpr_348) {
    static_assert(closed::include_right_endpoint() == true, "include_right_endpoint should be true at compile time");
    SUCCEED();
}

// Test that include_left_endpoint is constexpr (compile-time evaluable)
TEST(ClosedIntervalTest_348, IncludeLeftEndpointIsConstexpr_348) {
    static_assert(closed::include_left_endpoint() == true, "include_left_endpoint should be true at compile time");
    SUCCEED();
}

// Test that both endpoints are consistent for a closed interval (both true)
TEST(ClosedIntervalTest_348, BothEndpointsIncluded_348) {
    EXPECT_EQ(closed::include_left_endpoint(), closed::include_right_endpoint());
    EXPECT_TRUE(closed::include_left_endpoint() && closed::include_right_endpoint());
}

// Test that an instance of closed can be created and used
TEST(ClosedIntervalTest_348, InstanceCallsWork_348) {
    closed c;
    EXPECT_TRUE(c.include_left_endpoint());
    EXPECT_TRUE(c.include_right_endpoint());
}
