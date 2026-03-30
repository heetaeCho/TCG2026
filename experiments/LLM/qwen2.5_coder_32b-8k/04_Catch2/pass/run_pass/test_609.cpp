#include <gtest/gtest.h>

#include "catch2/internal/catch_floating_point_helpers.hpp"



class FloatingPointHelpersTest_609 : public ::testing::Test {

protected:

    // Additional setup can be done here if needed.

};



TEST_F(FloatingPointHelpersTest_609, DirectCompare_EqualValues_ReturnTrue_609) {

    EXPECT_TRUE(Catch::Detail::directCompare(1.0, 1.0));

}



TEST_F(FloatingPointHelpersTest_609, DirectCompare_DifferentValues_ReturnFalse_609) {

    EXPECT_FALSE(Catch::Detail::directCompare(1.0, 2.0));

}



TEST_F(FloatingPointHelpersTest_609, DirectCompare_SameButNotExactlyEqualDueToPrecision_ReturnFalse_609) {

    double a = 0.1 * 7;

    double b = 0.7;

    EXPECT_FALSE(Catch::Detail::directCompare(a, b));

}



TEST_F(FloatingPointHelpersTest_609, DirectCompare_ZeroAndNegativeZero_ReturnTrue_609) {

    EXPECT_TRUE(Catch::Detail::directCompare(0.0, -0.0));

}



TEST_F(FloatingPointHelpersTest_609, DirectCompare_PositiveInfinityWithPositiveInfinity_ReturnTrue_609) {

    EXPECT_TRUE(Catch::Detail::directCompare(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()));

}



TEST_F(FloatingPointHelpersTest_609, DirectCompare_NegativeInfinityWithNegativeInfinity_ReturnTrue_609) {

    EXPECT_TRUE(Catch::Detail::directCompare(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity()));

}



TEST_F(FloatingPointHelpersTest_609, DirectCompare_PositiveInfinityWithNegativeInfinity_ReturnFalse_609) {

    EXPECT_FALSE(Catch::Detail::directCompare(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity()));

}



TEST_F(FloatingPointHelpersTest_609, DirectCompare_NotANumberWithNotANumber_ReturnFalse_609) {

    double nan = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE(Catch::Detail::directCompare(nan, nan));

}
