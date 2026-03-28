#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;



class SymmetricBoundaryTest_343 : public ::testing::Test {

protected:

    symmetric_boundary boundary;

};



TEST_F(SymmetricBoundaryTest_343, IncludeLeftEndpoint_Open_343) {

    boundary.is_closed = false;

    EXPECT_FALSE(boundary.include_left_endpoint());

}



TEST_F(SymmetricBoundaryTest_343, IncludeLeftEndpoint_Closed_343) {

    boundary.is_closed = true;

    EXPECT_TRUE(boundary.include_left_endpoint());

}



// Assuming include_right_endpoint has similar behavior to include_left_endpoint

TEST_F(SymmetricBoundaryTest_343, IncludeRightEndpoint_Open_343) {

    boundary.is_closed = false;

    EXPECT_FALSE(boundary.include_right_endpoint());

}



TEST_F(SymmetricBoundaryTest_343, IncludeRightEndpoint_Closed_343) {

    boundary.is_closed = true;

    EXPECT_TRUE(boundary.include_right_endpoint());

}
