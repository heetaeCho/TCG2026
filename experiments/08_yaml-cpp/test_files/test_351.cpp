#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;



TEST_F(DragonBoxIntervalTypeTest_351, IncludeLeftEndpoint_ReturnsTrue_351) {

    EXPECT_TRUE(left_closed_right_open::include_left_endpoint());

}



TEST_F(DragonBoxIntervalTypeTest_351, IncludeRightEndpoint_ReturnsFalse_351) {

    EXPECT_FALSE(left_closed_right_open::include_right_endpoint());

}
