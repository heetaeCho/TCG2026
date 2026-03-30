#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashMath.h"



class SplashPowTest : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed in future tests.

};



TEST_F(SplashPowTest_1562, PositiveExponentiation_1562) {

    EXPECT_FLOAT_EQ(splashPow(2.0, 3.0), 8.0);

}



TEST_F(SplashPowTest_1562, ZeroExponent_1562) {

    EXPECT_FLOAT_EQ(splashPow(5.0, 0.0), 1.0);

}



TEST_F(SplashPowTest_1562, NegativeBaseAndEvenExponent_1562) {

    EXPECT_FLOAT_EQ(splashPow(-4.0, 2.0), 16.0);

}



TEST_F(SplashPowTest_1562, NegativeBaseAndOddExponent_1562) {

    EXPECT_FLOAT_EQ(splashPow(-3.0, 3.0), -27.0);

}



TEST_F(SplashPowTest_1562, FractionalExponent_1562) {

    EXPECT_FLOAT_EQ(splashPow(4.0, 0.5), 2.0);

}



TEST_F(SplashPowTest_1562, LargeBaseAndLargeExponent_1562) {

    EXPECT_FLOAT_EQ(splashPow(10.0, 5.0), 100000.0);

}



TEST_F(SplashPowTest_1562, SmallBaseAndLargeExponent_1562) {

    EXPECT_FLOAT_EQ(splashPow(0.1, 3.0), 0.001);

}
