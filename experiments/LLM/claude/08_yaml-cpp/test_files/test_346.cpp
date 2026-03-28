#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test: When is_left_closed is true, include_left_endpoint returns true
TEST(AsymmetricBoundaryTest_346, IncludeLeftEndpointWhenLeftClosed_346) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = true;
    EXPECT_TRUE(boundary.include_left_endpoint());
}

// Test: When is_left_closed is false, include_left_endpoint returns false
TEST(AsymmetricBoundaryTest_346, IncludeLeftEndpointWhenLeftOpen_346) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = false;
    EXPECT_FALSE(boundary.include_left_endpoint());
}

// Test: When is_left_closed is true, include_right_endpoint returns false
// (asymmetric: right is opposite of left)
TEST(AsymmetricBoundaryTest_346, IncludeRightEndpointWhenLeftClosed_346) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = true;
    EXPECT_FALSE(boundary.include_right_endpoint());
}

// Test: When is_left_closed is false, include_right_endpoint returns true
TEST(AsymmetricBoundaryTest_346, IncludeRightEndpointWhenLeftOpen_346) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = false;
    EXPECT_TRUE(boundary.include_right_endpoint());
}

// Test: Verify asymmetric property - left and right endpoints are never both included
TEST(AsymmetricBoundaryTest_346, AsymmetricPropertyLeftClosedTrue_346) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = true;
    EXPECT_NE(boundary.include_left_endpoint(), boundary.include_right_endpoint());
}

// Test: Verify asymmetric property with is_left_closed = false
TEST(AsymmetricBoundaryTest_346, AsymmetricPropertyLeftClosedFalse_346) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = false;
    EXPECT_NE(boundary.include_left_endpoint(), boundary.include_right_endpoint());
}

// Test: Constexpr behavior - include_left_endpoint can be evaluated at compile time
TEST(AsymmetricBoundaryTest_346, ConstexprIncludeLeftEndpoint_346) {
    constexpr asymmetric_boundary boundary_closed{true};
    constexpr bool left_result = boundary_closed.include_left_endpoint();
    EXPECT_TRUE(left_result);

    constexpr asymmetric_boundary boundary_open{false};
    constexpr bool left_result_open = boundary_open.include_left_endpoint();
    EXPECT_FALSE(left_result_open);
}

// Test: Constexpr behavior - include_right_endpoint can be evaluated at compile time
TEST(AsymmetricBoundaryTest_346, ConstexprIncludeRightEndpoint_346) {
    constexpr asymmetric_boundary boundary_closed{true};
    constexpr bool right_result = boundary_closed.include_right_endpoint();
    EXPECT_FALSE(right_result);

    constexpr asymmetric_boundary boundary_open{false};
    constexpr bool right_result_open = boundary_open.include_right_endpoint();
    EXPECT_TRUE(right_result_open);
}

// Test: Noexcept guarantee for include_left_endpoint
TEST(AsymmetricBoundaryTest_346, IncludeLeftEndpointIsNoexcept_346) {
    asymmetric_boundary boundary{true};
    EXPECT_TRUE(noexcept(boundary.include_left_endpoint()));
}

// Test: Noexcept guarantee for include_right_endpoint
TEST(AsymmetricBoundaryTest_346, IncludeRightEndpointIsNoexcept_346) {
    asymmetric_boundary boundary{true};
    EXPECT_TRUE(noexcept(boundary.include_right_endpoint()));
}

// Test: Modifying is_left_closed changes the endpoint results
TEST(AsymmetricBoundaryTest_346, ModifyingIsLeftClosedChangesResults_346) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = true;
    EXPECT_TRUE(boundary.include_left_endpoint());
    EXPECT_FALSE(boundary.include_right_endpoint());

    boundary.is_left_closed = false;
    EXPECT_FALSE(boundary.include_left_endpoint());
    EXPECT_TRUE(boundary.include_right_endpoint());
}
