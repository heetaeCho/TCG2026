#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test that include_left_endpoint returns true for closed interval
TEST(ClosedIntervalTypeTest_347, IncludeLeftEndpointReturnsTrue_347) {
    constexpr bool result = closed::include_left_endpoint();
    EXPECT_TRUE(result);
}

// Test that include_right_endpoint returns true for closed interval
TEST(ClosedIntervalTypeTest_347, IncludeRightEndpointReturnsTrue_347) {
    constexpr bool result = closed::include_right_endpoint();
    EXPECT_TRUE(result);
}

// Test that include_left_endpoint is noexcept
TEST(ClosedIntervalTypeTest_347, IncludeLeftEndpointIsNoexcept_347) {
    EXPECT_TRUE(noexcept(closed::include_left_endpoint()));
}

// Test that include_right_endpoint is noexcept
TEST(ClosedIntervalTypeTest_347, IncludeRightEndpointIsNoexcept_347) {
    EXPECT_TRUE(noexcept(closed::include_right_endpoint()));
}

// Test that include_left_endpoint is constexpr (compile-time evaluable)
TEST(ClosedIntervalTypeTest_347, IncludeLeftEndpointIsConstexpr_347) {
    static_assert(closed::include_left_endpoint() == true, "include_left_endpoint should be true at compile time");
    SUCCEED();
}

// Test that include_right_endpoint is constexpr (compile-time evaluable)
TEST(ClosedIntervalTypeTest_347, IncludeRightEndpointIsConstexpr_347) {
    static_assert(closed::include_right_endpoint() == true, "include_right_endpoint should be true at compile time");
    SUCCEED();
}

// Test that closed struct is default constructible
TEST(ClosedIntervalTypeTest_347, IsDefaultConstructible_347) {
    closed c;
    EXPECT_TRUE(c.include_left_endpoint());
    EXPECT_TRUE(c.include_right_endpoint());
}

// Test consistency: both endpoints are included (closed interval semantics)
TEST(ClosedIntervalTypeTest_347, BothEndpointsIncludedForClosedInterval_347) {
    EXPECT_EQ(closed::include_left_endpoint(), closed::include_right_endpoint());
    EXPECT_TRUE(closed::include_left_endpoint() && closed::include_right_endpoint());
}

// Test calling through an instance rather than statically
TEST(ClosedIntervalTypeTest_347, CallThroughInstance_347) {
    closed instance;
    bool left = instance.include_left_endpoint();
    bool right = instance.include_right_endpoint();
    EXPECT_TRUE(left);
    EXPECT_TRUE(right);
}

// Test multiple calls return consistent results
TEST(ClosedIntervalTypeTest_347, MultipleCallsReturnConsistentResults_347) {
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(closed::include_left_endpoint());
        EXPECT_TRUE(closed::include_right_endpoint());
    }
}
