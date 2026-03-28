#include <gtest/gtest.h>



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;



TEST_F(ClosedIntervalTest_347, IncludeLeftEndpoint_ReturnsTrue_347) {

    EXPECT_TRUE(closed::include_left_endpoint());

}



TEST_F(ClosedIntervalTest_347, IncludeRightEndpoint_ReturnsTrue_347) {

    EXPECT_TRUE(closed::include_right_endpoint());

}

```


