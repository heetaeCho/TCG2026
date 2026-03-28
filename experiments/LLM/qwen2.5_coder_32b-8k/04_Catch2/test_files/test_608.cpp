#include <gtest/gtest.h>

#include "catch2/internal/catch_floating_point_helpers.hpp"



using namespace Catch::Detail;



// Test Fixture for directCompare function tests

class DirectCompareTest_608 : public ::testing::Test {

protected:

    // You can add any necessary setup or teardown here if needed.

};



TEST_F(DirectCompareTest_608, EqualValuesReturnTrue_608) {

    EXPECT_TRUE(directCompare(1.0f, 1.0f));

}



TEST_F(DirectCompareTest_608, DifferentValuesReturnFalse_608) {

    EXPECT_FALSE(directCompare(1.0f, 2.0f));

}



TEST_F(DirectCompareTest_608, NegativeEqualValuesReturnTrue_608) {

    EXPECT_TRUE(directCompare(-1.0f, -1.0f));

}



TEST_F(DirectCompareTest_608, NegativeAndPositiveSameMagnitudeValuesReturnFalse_608) {

    EXPECT_FALSE(directCompare(1.0f, -1.0f));

}



TEST_F(DirectCompareTest_608, ZeroAndZeroReturnTrue_608) {

    EXPECT_TRUE(directCompare(0.0f, 0.0f));

}



TEST_F(DirectCompareTest_608, SmallEpsilonValuesReturnFalse_608) {

    EXPECT_FALSE(directCompare(1.0e-7f, 0.0f));

}



TEST_F(DirectCompareTest_608, LargeNumberComparison_608) {

    EXPECT_TRUE(directCompare(3.4028235E+38f, 3.4028235E+38f));

}



TEST_F(DirectCompareTest_608, NaNValuesReturnFalse_608) {

    float nanValue = std::numeric_limits<float>::quiet_NaN();

    EXPECT_FALSE(directCompare(nanValue, nanValue));

}
