#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test that include_right_endpoint returns true when is_closed is true
TEST(SymmetricBoundaryTest_344, IncludeRightEndpointReturnsTrueWhenClosed_344) {
    symmetric_boundary sb;
    sb.is_closed = true;
    EXPECT_TRUE(sb.include_right_endpoint());
}

// Test that include_right_endpoint returns false when is_closed is false
TEST(SymmetricBoundaryTest_344, IncludeRightEndpointReturnsFalseWhenOpen_344) {
    symmetric_boundary sb;
    sb.is_closed = false;
    EXPECT_FALSE(sb.include_right_endpoint());
}

// Test that include_left_endpoint returns true when is_closed is true
TEST(SymmetricBoundaryTest_344, IncludeLeftEndpointReturnsTrueWhenClosed_344) {
    symmetric_boundary sb;
    sb.is_closed = true;
    EXPECT_TRUE(sb.include_left_endpoint());
}

// Test that include_left_endpoint returns false when is_closed is false
TEST(SymmetricBoundaryTest_344, IncludeLeftEndpointReturnsFalseWhenOpen_344) {
    symmetric_boundary sb;
    sb.is_closed = false;
    EXPECT_FALSE(sb.include_left_endpoint());
}

// Test symmetry: both left and right endpoints should return the same value
TEST(SymmetricBoundaryTest_344, LeftAndRightEndpointsAreSymmetricWhenClosed_344) {
    symmetric_boundary sb;
    sb.is_closed = true;
    EXPECT_EQ(sb.include_left_endpoint(), sb.include_right_endpoint());
}

TEST(SymmetricBoundaryTest_344, LeftAndRightEndpointsAreSymmetricWhenOpen_344) {
    symmetric_boundary sb;
    sb.is_closed = false;
    EXPECT_EQ(sb.include_left_endpoint(), sb.include_right_endpoint());
}

// Test that the methods are noexcept
TEST(SymmetricBoundaryTest_344, MethodsAreNoexcept_344) {
    symmetric_boundary sb;
    sb.is_closed = true;
    EXPECT_TRUE(noexcept(sb.include_left_endpoint()));
    EXPECT_TRUE(noexcept(sb.include_right_endpoint()));
}

// Test that the methods are constexpr-compatible (can be used in constexpr context)
TEST(SymmetricBoundaryTest_344, ConstexprCompatibility_344) {
    // Verify the function can be called on a const object
    const symmetric_boundary sb_closed{true};
    EXPECT_TRUE(sb_closed.include_left_endpoint());
    EXPECT_TRUE(sb_closed.include_right_endpoint());

    const symmetric_boundary sb_open{false};
    EXPECT_FALSE(sb_open.include_left_endpoint());
    EXPECT_FALSE(sb_open.include_right_endpoint());
}

// Test toggling is_closed and verifying the endpoints change accordingly
TEST(SymmetricBoundaryTest_344, TogglingIsClosedChangesEndpoints_344) {
    symmetric_boundary sb;
    
    sb.is_closed = true;
    EXPECT_TRUE(sb.include_left_endpoint());
    EXPECT_TRUE(sb.include_right_endpoint());
    
    sb.is_closed = false;
    EXPECT_FALSE(sb.include_left_endpoint());
    EXPECT_FALSE(sb.include_right_endpoint());
    
    sb.is_closed = true;
    EXPECT_TRUE(sb.include_left_endpoint());
    EXPECT_TRUE(sb.include_right_endpoint());
}
