#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashMath.h"



class SplashRoundTest_1559 : public ::testing::Test {

protected:

    void SetUp() override {

        // No setup needed for this function, as it is static and does not require an instance.

    }



    void TearDown() override {

        // No teardown needed.

    }

};



TEST_F(SplashRoundTest_1559, PositiveNumberRounding_1559) {

    EXPECT_EQ(splashRound(2.3), 2);

    EXPECT_EQ(splashRound(2.5), 3);

    EXPECT_EQ(splashRound(2.7), 3);

}



TEST_F(SplashRoundTest_1559, NegativeNumberRounding_1559) {

    EXPECT_EQ(splashRound(-2.3), -2);

    EXPECT_EQ(splashRound(-2.5), -2);

    EXPECT_EQ(splashRound(-2.7), -3);

}



TEST_F(SplashRoundTest_1559, ZeroRounding_1559) {

    EXPECT_EQ(splashRound(0.0), 0);

    EXPECT_EQ(splashRound(-0.0), 0);

}



TEST_F(SplashRoundTest_1559, BoundaryConditions_1559) {

    EXPECT_EQ(splashRound(0.49999999), 0);

    EXPECT_EQ(splashRound(0.5), 1);

    EXPECT_EQ(splashRound(-0.49999999), 0);

    EXPECT_EQ(splashRound(-0.5), 0);

}



TEST_F(SplashRoundTest_1559, LargePositiveNumber_1559) {

    EXPECT_EQ(splashRound(123456789.5), 123456790);

    EXPECT_EQ(splashRound(123456789.49999999), 123456789);

}



TEST_F(SplashRoundTest_1559, LargeNegativeNumber_1559) {

    EXPECT_EQ(splashRound(-123456789.5), -123456789);

    EXPECT_EQ(splashRound(-123456789.49999999), -123456790);

}
