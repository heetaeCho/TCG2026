#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test fixture for asymmetric_boundary
class AsymmetricBoundaryTest_345 : public ::testing::Test {
protected:
    // Helper to create an asymmetric_boundary with a given is_left_closed value
};

// Test include_left_endpoint returns true when is_left_closed is true
TEST_F(AsymmetricBoundaryTest_345, IncludeLeftEndpointReturnsTrueWhenLeftClosed_345) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = true;
    EXPECT_TRUE(boundary.include_left_endpoint());
}

// Test include_left_endpoint returns false when is_left_closed is false
TEST_F(AsymmetricBoundaryTest_345, IncludeLeftEndpointReturnsFalseWhenLeftOpen_345) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = false;
    EXPECT_FALSE(boundary.include_left_endpoint());
}

// Test include_right_endpoint returns expected value when is_left_closed is true
TEST_F(AsymmetricBoundaryTest_345, IncludeRightEndpointWhenLeftClosed_345) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = true;
    // For an asymmetric boundary, right endpoint inclusion is typically opposite or independent
    // We observe the behavior without assuming implementation
    bool result = boundary.include_right_endpoint();
    // Asymmetric boundary: when left is closed, right is typically open
    EXPECT_FALSE(result);
}

// Test include_right_endpoint returns expected value when is_left_closed is false
TEST_F(AsymmetricBoundaryTest_345, IncludeRightEndpointWhenLeftOpen_345) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = false;
    bool result = boundary.include_right_endpoint();
    // Asymmetric boundary: when left is open, right is typically closed
    EXPECT_TRUE(result);
}

// Test that include_left_endpoint is noexcept
TEST_F(AsymmetricBoundaryTest_345, IncludeLeftEndpointIsNoexcept_345) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = true;
    EXPECT_TRUE(noexcept(boundary.include_left_endpoint()));
}

// Test that include_right_endpoint is noexcept
TEST_F(AsymmetricBoundaryTest_345, IncludeRightEndpointIsNoexcept_345) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = true;
    EXPECT_TRUE(noexcept(boundary.include_right_endpoint()));
}

// Test constexpr evaluation of include_left_endpoint with true
TEST_F(AsymmetricBoundaryTest_345, ConstexprIncludeLeftEndpointTrue_345) {
    constexpr asymmetric_boundary boundary{true};
    constexpr bool result = boundary.include_left_endpoint();
    EXPECT_TRUE(result);
}

// Test constexpr evaluation of include_left_endpoint with false
TEST_F(AsymmetricBoundaryTest_345, ConstexprIncludeLeftEndpointFalse_345) {
    constexpr asymmetric_boundary boundary{false};
    constexpr bool result = boundary.include_left_endpoint();
    EXPECT_FALSE(result);
}

// Test constexpr evaluation of include_right_endpoint with true
TEST_F(AsymmetricBoundaryTest_345, ConstexprIncludeRightEndpointWhenLeftClosed_345) {
    constexpr asymmetric_boundary boundary{true};
    constexpr bool result = boundary.include_right_endpoint();
    EXPECT_FALSE(result);
}

// Test constexpr evaluation of include_right_endpoint with false
TEST_F(AsymmetricBoundaryTest_345, ConstexprIncludeRightEndpointWhenLeftOpen_345) {
    constexpr asymmetric_boundary boundary{false};
    constexpr bool result = boundary.include_right_endpoint();
    EXPECT_TRUE(result);
}

// Test that the asymmetric property holds: left and right are never both closed or both open
TEST_F(AsymmetricBoundaryTest_345, AsymmetricPropertyHolds_345) {
    asymmetric_boundary boundary_closed;
    boundary_closed.is_left_closed = true;
    EXPECT_NE(boundary_closed.include_left_endpoint(), boundary_closed.include_right_endpoint());

    asymmetric_boundary boundary_open;
    boundary_open.is_left_closed = false;
    EXPECT_NE(boundary_open.include_left_endpoint(), boundary_open.include_right_endpoint());
}

// Test toggling is_left_closed changes behavior
TEST_F(AsymmetricBoundaryTest_345, TogglingIsLeftClosedChangesBehavior_345) {
    asymmetric_boundary boundary;
    boundary.is_left_closed = true;
    EXPECT_TRUE(boundary.include_left_endpoint());
    EXPECT_FALSE(boundary.include_right_endpoint());

    boundary.is_left_closed = false;
    EXPECT_FALSE(boundary.include_left_endpoint());
    EXPECT_TRUE(boundary.include_right_endpoint());
}
