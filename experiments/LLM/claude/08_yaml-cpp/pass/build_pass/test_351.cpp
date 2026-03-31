#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test that include_left_endpoint returns true for left_closed_right_open
TEST(LeftClosedRightOpenTest_351, IncludeLeftEndpointReturnsTrue_351) {
    constexpr bool result = left_closed_right_open::include_left_endpoint();
    EXPECT_TRUE(result);
}

// Test that include_right_endpoint returns false for left_closed_right_open
TEST(LeftClosedRightOpenTest_351, IncludeRightEndpointReturnsFalse_351) {
    constexpr bool result = left_closed_right_open::include_right_endpoint();
    EXPECT_FALSE(result);
}

// Test that include_left_endpoint is noexcept
TEST(LeftClosedRightOpenTest_351, IncludeLeftEndpointIsNoexcept_351) {
    EXPECT_TRUE(noexcept(left_closed_right_open::include_left_endpoint()));
}

// Test that include_right_endpoint is noexcept
TEST(LeftClosedRightOpenTest_351, IncludeRightEndpointIsNoexcept_351) {
    EXPECT_TRUE(noexcept(left_closed_right_open::include_right_endpoint()));
}

// Test that include_left_endpoint is constexpr and can be used at compile time
TEST(LeftClosedRightOpenTest_351, IncludeLeftEndpointIsConstexpr_351) {
    static_assert(left_closed_right_open::include_left_endpoint() == true,
                  "include_left_endpoint should be true at compile time");
    SUCCEED();
}

// Test that include_right_endpoint is constexpr and can be used at compile time
TEST(LeftClosedRightOpenTest_351, IncludeRightEndpointIsConstexpr_351) {
    static_assert(left_closed_right_open::include_right_endpoint() == false,
                  "include_right_endpoint should be false at compile time");
    SUCCEED();
}

// Test that the struct is default constructible
TEST(LeftClosedRightOpenTest_351, IsDefaultConstructible_351) {
    left_closed_right_open instance;
    EXPECT_TRUE(instance.include_left_endpoint());
    EXPECT_FALSE(instance.include_right_endpoint());
}

// Test consistency: calling multiple times yields same results
TEST(LeftClosedRightOpenTest_351, ConsistentResults_351) {
    EXPECT_EQ(left_closed_right_open::include_left_endpoint(),
              left_closed_right_open::include_left_endpoint());
    EXPECT_EQ(left_closed_right_open::include_right_endpoint(),
              left_closed_right_open::include_right_endpoint());
}

// Test that left and right endpoints are complementary (left closed, right open)
TEST(LeftClosedRightOpenTest_351, LeftClosedRightOpenSemantics_351) {
    // For a left-closed, right-open interval: left is included, right is not
    EXPECT_TRUE(left_closed_right_open::include_left_endpoint());
    EXPECT_FALSE(left_closed_right_open::include_right_endpoint());
    // They should not be equal
    EXPECT_NE(left_closed_right_open::include_left_endpoint(),
              left_closed_right_open::include_right_endpoint());
}
