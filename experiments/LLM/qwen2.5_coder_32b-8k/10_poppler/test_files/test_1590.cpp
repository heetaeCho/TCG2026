#include <gtest/gtest.h>

#include <climits>



// Assuming the clipColor function is part of a class or namespace.

// For this example, we will assume it's in a namespace called SplashOutputDev.



namespace SplashOutputDev {

    static void clipColor(int rIn, int gIn, int bIn, unsigned char *rOut, unsigned char *gOut, unsigned char *bOut);

}



// Test suite for the clipColor function

class ClipColorTest_1590 : public ::testing::Test {

protected:

    unsigned char rOut = 0;

    unsigned char gOut = 0;

    unsigned char bOut = 0;



    void checkResult(int expectedR, int expectedG, int expectedB) {

        EXPECT_EQ(expectedR, static_cast<int>(rOut));

        EXPECT_EQ(expectedG, static_cast<int>(gOut));

        EXPECT_EQ(expectedB, static_cast<int>(bOut));

    }

};



// Test normal operation

TEST_F(ClipColorTest_1590, NormalOperation_1590) {

    SplashOutputDev::clipColor(128, 128, 128, &rOut, &gOut, &bOut);

    checkResult(128, 128, 128);



    SplashOutputDev::clipColor(0, 255, 0, &rOut, &gOut, &bOut);

    checkResult(0, 255, 0);

}



// Test boundary conditions

TEST_F(ClipColorTest_1590, BoundaryConditions_1590) {

    SplashOutputDev::clipColor(0, 0, 0, &rOut, &gOut, &bOut);

    checkResult(0, 0, 0);



    SplashOutputDev::clipColor(255, 255, 255, &rOut, &gOut, &bOut);

    checkResult(255, 255, 255);

}



// Test when rgbMin < 0

TEST_F(ClipColorTest_1590, RgbMinLessThanZero_1590) {

    SplashOutputDev::clipColor(-10, -10, -10, &rOut, &gOut, &bOut);

    checkResult(0, 0, 0);



    SplashOutputDev::clipColor(-10, 255, 255, &rOut, &gOut, &bOut);

    checkResult(0, 255, 255);

}



// Test when rgbMax > 255

TEST_F(ClipColorTest_1590, RgbMaxGreaterThan255_1590) {

    SplashOutputDev::clipColor(300, 300, 300, &rOut, &gOut, &bOut);

    checkResult(255, 255, 255);



    SplashOutputDev::clipColor(300, 100, 100, &rOut, &gOut, &bOut);

    checkResult(255, 87, 87);

}
