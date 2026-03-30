#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashTypes.h"



class SplashBGR8BTest : public ::testing::Test {

protected:

    // No need to set up or tear down for this simple function.

};



TEST_F(SplashBGR8BTest, NormalOperation_1038) {

    unsigned char bgr8[] = {123, 45, 67};

    EXPECT_EQ(splashBGR8B(bgr8), 123);

}



TEST_F(SplashBGR8BTest, BoundaryCondition_Zero_1038) {

    unsigned char bgr8[] = {0, 255, 255};

    EXPECT_EQ(splashBGR8B(bgr8), 0);

}



TEST_F(SplashBGR8BTest, BoundaryCondition_MaxValue_1038) {

    unsigned char bgr8[] = {255, 0, 0};

    EXPECT_EQ(splashBGR8B(bgr8), 255);

}
