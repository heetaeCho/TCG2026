#include <gtest/gtest.h>

#include "HtmlUtils.h"



class HtmlUtilsTest_2630 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



TEST_F(HtmlUtilsTest_2630, IsWithin_SameValues_ReturnsTrue_2630) {

    EXPECT_TRUE(is_within(1.0, 0.01, 1.0));

}



TEST_F(HtmlUtilsTest_2630, IsWithin_ThresholdRange_ReturnsTrue_2630) {

    EXPECT_TRUE(is_within(1.0, 0.1, 1.05));

}



TEST_F(HtmlUtilsTest_2630, IsWithin_OutsideThreshold_ReturnsFalse_2630) {

    EXPECT_FALSE(is_within(1.0, 0.01, 1.1));

}



TEST_F(HtmlUtilsTest_2630, IsWithin_NegativeValuesWithinThreshold_ReturnsTrue_2630) {

    EXPECT_TRUE(is_within(-1.0, 0.1, -1.05));

}



TEST_F(HtmlUtilsTest_2630, IsWithin_ZeroThreshold_DifferentValues_ReturnsFalse_2630) {

    EXPECT_FALSE(is_within(1.0, 0.0, 1.1));

}



TEST_F(HtmlUtilsTest_2630, IsWithin_LargeThreshold_AnyValues_ReturnsTrue_2630) {

    EXPECT_TRUE(is_within(1.0, 10.0, -5.0));

}
