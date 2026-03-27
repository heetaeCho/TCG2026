#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;



TEST_F(IntervalTypeTests_354, IncludeRightEndpoint_ReturnsTrue_354) {

    EXPECT_TRUE(right_closed_left_open::include_right_endpoint());

}



TEST_F(IntervalTypeTests_354, IncludeLeftEndpoint_ReturnsFalse_354) {

    EXPECT_FALSE(right_closed_left_open::include_left_endpoint());

}

```


