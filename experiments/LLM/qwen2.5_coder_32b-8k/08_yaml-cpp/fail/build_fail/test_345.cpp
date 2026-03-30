#include <gtest/gtest.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding { namespace interval_type {



class AsymmetricBoundaryTest : public ::testing::Test {

protected:

    asymmetric_boundary boundary_open;

    asymmetric_boundary boundary_left_closed;



    AsymmetricBoundaryTest() 

        : boundary_open{false}, 

          boundary_left_closed{true} {}

};



TEST_F(AsymmetricBoundaryTest_345, IncludeLeftEndpoint_Open_345) {

    EXPECT_FALSE(boundary_open.include_left_endpoint());

}



TEST_F(AsymmetricBoundaryTest_345, IncludeLeftEndpoint_LeftClosed_345) {

    EXPECT_TRUE(boundary_left_closed.include_left_endpoint());

}



// Assuming include_right_endpoint is not provided in the interface,

// we cannot test it without additional information. However, if it were part of the interface:

TEST_F(AsymmetricBoundaryTest_345, IncludeRightEndpoint_Open_345) {

    EXPECT_FALSE(boundary_open.include_right_endpoint());

}



TEST_F(AsymmetricBoundaryTest_345, IncludeRightEndpoint_LeftClosed_345) {

    EXPECT_TRUE(boundary_left_closed.include_right_endpoint());

}



} } } } } } // namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type
