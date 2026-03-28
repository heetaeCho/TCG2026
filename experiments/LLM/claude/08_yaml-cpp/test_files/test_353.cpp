#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test that include_left_endpoint returns false
TEST(RightClosedLeftOpenTest_353, IncludeLeftEndpointReturnsFalse_353) {
    constexpr bool result = right_closed_left_open::include_left_endpoint();
    EXPECT_FALSE(result);
}

// Test that include_right_endpoint returns true
TEST(RightClosedLeftOpenTest_353, IncludeRightEndpointReturnsTrue_353) {
    constexpr bool result = right_closed_left_open::include_right_endpoint();
    EXPECT_TRUE(result);
}

// Test that include_left_endpoint is constexpr
TEST(RightClosedLeftOpenTest_353, IncludeLeftEndpointIsConstexpr_353) {
    static_assert(right_closed_left_open::include_left_endpoint() == false,
                  "include_left_endpoint should be constexpr and return false");
    SUCCEED();
}

// Test that include_right_endpoint is constexpr
TEST(RightClosedLeftOpenTest_353, IncludeRightEndpointIsConstexpr_353) {
    static_assert(right_closed_left_open::include_right_endpoint() == true,
                  "include_right_endpoint should be constexpr and return true");
    SUCCEED();
}

// Test that include_left_endpoint is noexcept
TEST(RightClosedLeftOpenTest_353, IncludeLeftEndpointIsNoexcept_353) {
    EXPECT_TRUE(noexcept(right_closed_left_open::include_left_endpoint()));
}

// Test that include_right_endpoint is noexcept
TEST(RightClosedLeftOpenTest_353, IncludeRightEndpointIsNoexcept_353) {
    EXPECT_TRUE(noexcept(right_closed_left_open::include_right_endpoint()));
}

// Test that the struct can be instantiated
TEST(RightClosedLeftOpenTest_353, CanBeInstantiated_353) {
    right_closed_left_open instance;
    EXPECT_FALSE(instance.include_left_endpoint());
    EXPECT_TRUE(instance.include_right_endpoint());
}

// Test consistency - calling multiple times yields same result
TEST(RightClosedLeftOpenTest_353, ConsistentResults_353) {
    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(right_closed_left_open::include_left_endpoint());
        EXPECT_TRUE(right_closed_left_open::include_right_endpoint());
    }
}

// Test that the semantics match "right closed, left open" interval: (a, b]
// Left open means left endpoint is NOT included
// Right closed means right endpoint IS included
TEST(RightClosedLeftOpenTest_353, SemanticsMatchRightClosedLeftOpen_353) {
    // Left open => left endpoint not included
    EXPECT_FALSE(right_closed_left_open::include_left_endpoint());
    // Right closed => right endpoint included
    EXPECT_TRUE(right_closed_left_open::include_right_endpoint());
}
