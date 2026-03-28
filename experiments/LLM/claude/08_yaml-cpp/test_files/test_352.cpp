#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test that include_right_endpoint returns false
TEST(LeftClosedRightOpenTest_352, IncludeRightEndpointReturnsFalse_352) {
    constexpr bool result = left_closed_right_open::include_right_endpoint();
    EXPECT_FALSE(result);
}

// Test that include_left_endpoint returns true
TEST(LeftClosedRightOpenTest_352, IncludeLeftEndpointReturnsTrue_352) {
    constexpr bool result = left_closed_right_open::include_left_endpoint();
    EXPECT_TRUE(result);
}

// Test that include_right_endpoint is noexcept
TEST(LeftClosedRightOpenTest_352, IncludeRightEndpointIsNoexcept_352) {
    EXPECT_TRUE(noexcept(left_closed_right_open::include_right_endpoint()));
}

// Test that include_left_endpoint is noexcept
TEST(LeftClosedRightOpenTest_352, IncludeLeftEndpointIsNoexcept_352) {
    EXPECT_TRUE(noexcept(left_closed_right_open::include_left_endpoint()));
}

// Test that the results are constexpr and can be used at compile time
TEST(LeftClosedRightOpenTest_352, ConstexprUsability_352) {
    static_assert(left_closed_right_open::include_left_endpoint() == true,
                  "include_left_endpoint should be true at compile time");
    static_assert(left_closed_right_open::include_right_endpoint() == false,
                  "include_right_endpoint should be false at compile time");
    SUCCEED();
}

// Test that the struct is default constructible
TEST(LeftClosedRightOpenTest_352, DefaultConstructible_352) {
    left_closed_right_open instance;
    EXPECT_FALSE(instance.include_right_endpoint());
    EXPECT_TRUE(instance.include_left_endpoint());
}

// Test consistency - calling multiple times yields same results
TEST(LeftClosedRightOpenTest_352, ConsistentResults_352) {
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(left_closed_right_open::include_left_endpoint());
        EXPECT_FALSE(left_closed_right_open::include_right_endpoint());
    }
}

// Test that left and right endpoints are different (left closed, right open)
TEST(LeftClosedRightOpenTest_352, LeftAndRightEndpointsDiffer_352) {
    EXPECT_NE(left_closed_right_open::include_left_endpoint(),
              left_closed_right_open::include_right_endpoint());
}
