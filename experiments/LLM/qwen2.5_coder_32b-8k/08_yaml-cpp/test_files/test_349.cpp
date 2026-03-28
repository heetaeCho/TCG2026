#include <gtest/gtest.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding { namespace interval_type {



class OpenIntervalTest_349 : public ::testing::Test {

protected:

    using Interval = open;

};



TEST_F(OpenIntervalTest_349, IncludeLeftEndpoint_ReturnsFalse_349) {

    EXPECT_FALSE(Interval::include_left_endpoint());

}



TEST_F(OpenIntervalTest_349, IncludeRightEndpoint_ReturnsTrue_349) {

    EXPECT_TRUE(Interval::include_right_endpoint());

}



} } } } } }
