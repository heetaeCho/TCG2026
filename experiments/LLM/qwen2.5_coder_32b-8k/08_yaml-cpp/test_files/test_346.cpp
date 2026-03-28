#include <gtest/gtest.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding { namespace interval_type {



class AsymmetricBoundaryTest : public ::testing::Test {

protected:

    asymmetric_boundary boundary;

};



TEST_F(AsymmetricBoundaryTest_346, IncludeRightEndpoint_ReturnsFalseWhenIsLeftClosedTrue_346) {

    boundary.is_left_closed = true;

    EXPECT_FALSE(boundary.include_right_endpoint());

}



TEST_F(AsymmetricBoundaryTest_346, IncludeRightEndpoint_ReturnsTrueWhenIsLeftClosedFalse_346) {

    boundary.is_left_closed = false;

    EXPECT_TRUE(boundary.include_right_endpoint());

}



} // namespace interval_type

} // namespace decimal_to_binary_rounding

} // namespace policy

} // namespace dragonbox

} // namespace jkj

} // namespace YAML
