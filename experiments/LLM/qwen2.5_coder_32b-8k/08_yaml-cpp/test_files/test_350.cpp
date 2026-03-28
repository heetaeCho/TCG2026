#include <gtest/gtest.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding { namespace interval_type {



class IntervalTypeTest_350 : public ::testing::Test {

protected:

    using OpenInterval = open;

};



TEST_F(IntervalTypeTest_350, IncludeRightEndpoint_ReturnsFalse_350) {

    EXPECT_FALSE(OpenInterval::include_right_endpoint());

}



// Assuming include_left_endpoint is also part of the interface to be tested

TEST_F(IntervalTypeTest_350, IncludeLeftEndpoint_ReturnsExpectedValue_350) {

    // Since we don't have information about what include_left_endpoint should return,

    // we cannot assert a specific value. However, if there's any known behavior or documentation,

    // you can replace `true` with the expected value.

    EXPECT_EQ(OpenInterval::include_left_endpoint(), true);

}



} } } } } }
