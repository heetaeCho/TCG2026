#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test that include_right_endpoint returns true
TEST(RightClosedLeftOpenTest_354, IncludeRightEndpointReturnsTrue_354) {
    constexpr bool result = right_closed_left_open::include_right_endpoint();
    EXPECT_TRUE(result);
}

// Test that include_left_endpoint returns false (left open means left endpoint is not included)
TEST(RightClosedLeftOpenTest_354, IncludeLeftEndpointReturnsFalse_354) {
    constexpr bool result = right_closed_left_open::include_left_endpoint();
    EXPECT_FALSE(result);
}

// Test that include_right_endpoint is noexcept
TEST(RightClosedLeftOpenTest_354, IncludeRightEndpointIsNoexcept_354) {
    EXPECT_TRUE(noexcept(right_closed_left_open::include_right_endpoint()));
}

// Test that include_left_endpoint is noexcept
TEST(RightClosedLeftOpenTest_354, IncludeLeftEndpointIsNoexcept_354) {
    EXPECT_TRUE(noexcept(right_closed_left_open::include_left_endpoint()));
}

// Test that include_right_endpoint is constexpr and can be used at compile time
TEST(RightClosedLeftOpenTest_354, IncludeRightEndpointIsConstexpr_354) {
    static_assert(right_closed_left_open::include_right_endpoint() == true,
                  "include_right_endpoint should be true at compile time");
    SUCCEED();
}

// Test that include_left_endpoint is constexpr and can be used at compile time
TEST(RightClosedLeftOpenTest_354, IncludeLeftEndpointIsConstexpr_354) {
    static_assert(right_closed_left_open::include_left_endpoint() == false,
                  "include_left_endpoint should be false at compile time");
    SUCCEED();
}

// Test that the struct can be instantiated
TEST(RightClosedLeftOpenTest_354, CanBeInstantiated_354) {
    right_closed_left_open instance;
    EXPECT_TRUE(instance.include_right_endpoint());
    EXPECT_FALSE(instance.include_left_endpoint());
}

// Test consistency: right closed and left open semantics
TEST(RightClosedLeftOpenTest_354, RightClosedLeftOpenSemantics_354) {
    // "right_closed" means right endpoint is included
    // "left_open" means left endpoint is NOT included
    constexpr bool right = right_closed_left_open::include_right_endpoint();
    constexpr bool left = right_closed_left_open::include_left_endpoint();
    
    EXPECT_TRUE(right);   // right closed -> included
    EXPECT_FALSE(left);   // left open -> not included
    EXPECT_NE(right, left); // They should be different for this interval type
}
