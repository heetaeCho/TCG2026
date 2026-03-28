#include <gtest/gtest.h>

#include "./TestProjects/poppler/splash/SplashTypes.h"



class SplashCMYK8YTest : public ::testing::Test {

protected:

    void SetUp() override {

        // No setup required for this simple function test

    }



    void TearDown() override {

        // No teardown required for this simple function test

    }

};



TEST_F(SplashCMYK8YTest, NormalOperation_1041) {

    SplashColor cmyk8 = {50, 60, 70, 80}; // Example values

    EXPECT_EQ(splashCMYK8Y(cmyk8), 70);

}



TEST_F(SplashCMYK8YTest, BoundaryCondition_Zero_1041) {

    SplashColor cmyk8 = {0, 0, 0, 0};

    EXPECT_EQ(splashCMYK8Y(cmyk8), 0);

}



TEST_F(SplashCMYK8YTest, BoundaryCondition_MaxValue_1041) {

    SplashColor cmyk8 = {255, 255, 255, 255};

    EXPECT_EQ(splashCMYK8Y(cmyk8), 255);

}



TEST_F(SplashCMYK8YTest, BoundaryCondition_MixedValues_1041) {

    SplashColor cmyk8 = {255, 128, 64, 32};

    EXPECT_EQ(splashCMYK8Y(cmyk8), 64);

}
