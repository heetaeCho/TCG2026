#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;



class LeftClosedRightOpenTest_352 : public ::testing::Test {

protected:

    left_closed_right_open interval;

};



TEST_F(LeftClosedRightOpenTest_352, IncludeLeftEndpoint_ReturnsTrue_352) {

    EXPECT_TRUE(left_closed_right_open::include_left_endpoint());

}



TEST_F(LeftClosedRightOpenTest_352, IncludeRightEndpoint_ReturnsFalse_352) {

    EXPECT_FALSE(interval.include_right_endpoint());

}
