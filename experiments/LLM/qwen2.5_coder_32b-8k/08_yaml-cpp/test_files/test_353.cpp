#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the correct header file is included for right_closed_left_open struct

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type;



class RightClosedLeftOpenTest_353 : public ::testing::Test {

protected:

    using IntervalType = right_closed_left_open;

};



TEST_F(RightClosedLeftOpenTest_353, IncludeLeftEndpoint_ReturnsFalse_353) {

    EXPECT_FALSE(IntervalType::include_left_endpoint());

}



TEST_F(RightClosedLeftOpenTest_353, IncludeRightEndpoint_ReturnsTrue_353) {

    EXPECT_TRUE(IntervalType::include_right_endpoint());

}

```


