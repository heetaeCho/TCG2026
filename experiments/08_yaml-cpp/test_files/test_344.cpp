#include <gtest/gtest.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding { namespace interval_type {



class SymmetricBoundaryTest : public ::testing::Test {

protected:

    symmetric_boundary boundary;

};



TEST_F(SymmetricBoundaryTest_344, IncludeRightEndpoint_ReturnsTrueWhenIsClosedIsTrue_344) {

    boundary.is_closed = true;

    EXPECT_TRUE(boundary.include_right_endpoint());

}



TEST_F(SymmetricBoundaryTest_344, IncludeRightEndpoint_ReturnsFalseWhenIsClosedIsFalse_344) {

    boundary.is_closed = false;

    EXPECT_FALSE(boundary.include_right_endpoint());

}



TEST_F(SymmetricBoundaryTest_344, Boundary_DefaultConstructor_InitializesIsClosedToDefault_344) {

    symmetric_boundary defaultBoundary;

    // Assuming is_closed has a default value of false if not explicitly initialized

    EXPECT_FALSE(defaultBoundary.is_closed);

}



}}}}}}
