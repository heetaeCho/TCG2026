#include <gtest/gtest.h>

// Include the header under test
#include "contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;

// Test fixture for symmetric_boundary
class SymmetricBoundaryTest_343 : public ::testing::Test {
protected:
    // Setup if needed
};

// Test that when is_closed is true, include_left_endpoint returns true
TEST_F(SymmetricBoundaryTest_343, IncludeLeftEndpoint_WhenClosed_ReturnsTrue_343) {
    symmetric_boundary sb;
    sb.is_closed = true;
    EXPECT_TRUE(sb.include_left_endpoint());
}

// Test that when is_closed is false, include_left_endpoint returns false
TEST_F(SymmetricBoundaryTest_343, IncludeLeftEndpoint_WhenOpen_ReturnsFalse_343) {
    symmetric_boundary sb;
    sb.is_closed = false;
    EXPECT_FALSE(sb.include_left_endpoint());
}

// Test that when is_closed is true, include_right_endpoint returns true
TEST_F(SymmetricBoundaryTest_343, IncludeRightEndpoint_WhenClosed_ReturnsTrue_343) {
    symmetric_boundary sb;
    sb.is_closed = true;
    EXPECT_TRUE(sb.include_right_endpoint());
}

// Test that when is_closed is false, include_right_endpoint returns false
TEST_F(SymmetricBoundaryTest_343, IncludeRightEndpoint_WhenOpen_ReturnsFalse_343) {
    symmetric_boundary sb;
    sb.is_closed = false;
    EXPECT_FALSE(sb.include_right_endpoint());
}

// Test symmetry: both endpoints should return the same value when is_closed is true
TEST_F(SymmetricBoundaryTest_343, Symmetry_WhenClosed_BothEndpointsMatch_343) {
    symmetric_boundary sb;
    sb.is_closed = true;
    EXPECT_EQ(sb.include_left_endpoint(), sb.include_right_endpoint());
}

// Test symmetry: both endpoints should return the same value when is_closed is false
TEST_F(SymmetricBoundaryTest_343, Symmetry_WhenOpen_BothEndpointsMatch_343) {
    symmetric_boundary sb;
    sb.is_closed = false;
    EXPECT_EQ(sb.include_left_endpoint(), sb.include_right_endpoint());
}

// Test that include_left_endpoint is noexcept
TEST_F(SymmetricBoundaryTest_343, IncludeLeftEndpoint_IsNoexcept_343) {
    symmetric_boundary sb;
    sb.is_closed = true;
    EXPECT_TRUE(noexcept(sb.include_left_endpoint()));
}

// Test that include_right_endpoint is noexcept
TEST_F(SymmetricBoundaryTest_343, IncludeRightEndpoint_IsNoexcept_343) {
    symmetric_boundary sb;
    sb.is_closed = true;
    EXPECT_TRUE(noexcept(sb.include_right_endpoint()));
}

// Test constexpr capability with is_closed = true
TEST_F(SymmetricBoundaryTest_343, ConstexprUsage_Closed_343) {
    constexpr symmetric_boundary sb{true};
    constexpr bool left = sb.include_left_endpoint();
    constexpr bool right = sb.include_right_endpoint();
    EXPECT_TRUE(left);
    EXPECT_TRUE(right);
}

// Test constexpr capability with is_closed = false
TEST_F(SymmetricBoundaryTest_343, ConstexprUsage_Open_343) {
    constexpr symmetric_boundary sb{false};
    constexpr bool left = sb.include_left_endpoint();
    constexpr bool right = sb.include_right_endpoint();
    EXPECT_FALSE(left);
    EXPECT_FALSE(right);
}

// Test toggling is_closed and verifying behavior changes
TEST_F(SymmetricBoundaryTest_343, ToggleIsClosed_343) {
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

// Test copy behavior
TEST_F(SymmetricBoundaryTest_343, CopyBehavior_343) {
    symmetric_boundary sb1;
    sb1.is_closed = true;
    
    symmetric_boundary sb2 = sb1;
    EXPECT_TRUE(sb2.include_left_endpoint());
    EXPECT_TRUE(sb2.include_right_endpoint());
    
    sb1.is_closed = false;
    // sb2 should remain unchanged after copy
    EXPECT_TRUE(sb2.include_left_endpoint());
    EXPECT_TRUE(sb2.include_right_endpoint());
}
