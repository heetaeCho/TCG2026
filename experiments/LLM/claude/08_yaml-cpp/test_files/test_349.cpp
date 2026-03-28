#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using OpenInterval = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::open;

TEST(OpenIntervalTest_349, IncludeLeftEndpointReturnsFalse_349) {
    constexpr bool result = OpenInterval::include_left_endpoint();
    EXPECT_FALSE(result);
}

TEST(OpenIntervalTest_349, IncludeRightEndpointReturnsFalse_349) {
    constexpr bool result = OpenInterval::include_right_endpoint();
    EXPECT_FALSE(result);
}

TEST(OpenIntervalTest_349, IncludeLeftEndpointIsNoexcept_349) {
    EXPECT_TRUE(noexcept(OpenInterval::include_left_endpoint()));
}

TEST(OpenIntervalTest_349, IncludeRightEndpointIsNoexcept_349) {
    EXPECT_TRUE(noexcept(OpenInterval::include_right_endpoint()));
}

TEST(OpenIntervalTest_349, IncludeLeftEndpointIsConstexpr_349) {
    // Verify it can be used in a constexpr context
    static_assert(OpenInterval::include_left_endpoint() == false, "include_left_endpoint should be false at compile time");
    SUCCEED();
}

TEST(OpenIntervalTest_349, IncludeRightEndpointIsConstexpr_349) {
    // Verify it can be used in a constexpr context
    static_assert(OpenInterval::include_right_endpoint() == false, "include_right_endpoint should be false at compile time");
    SUCCEED();
}

TEST(OpenIntervalTest_349, BothEndpointsExcluded_349) {
    // An open interval excludes both endpoints
    EXPECT_FALSE(OpenInterval::include_left_endpoint());
    EXPECT_FALSE(OpenInterval::include_right_endpoint());
}

TEST(OpenIntervalTest_349, ConsistentReturnValues_349) {
    // Multiple calls should return the same value
    EXPECT_EQ(OpenInterval::include_left_endpoint(), OpenInterval::include_left_endpoint());
    EXPECT_EQ(OpenInterval::include_right_endpoint(), OpenInterval::include_right_endpoint());
}
