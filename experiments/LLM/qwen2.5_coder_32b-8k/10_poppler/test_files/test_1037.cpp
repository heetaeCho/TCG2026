#include <gtest/gtest.h>

#include "./TestProjects/poppler/splash/SplashTypes.h"



// Test fixture for SplashColorPtr related tests.

class SplashBGR8GTest_1037 : public ::testing::Test {

protected:

    SplashColorPtr color;

    

    void SetUp() override {

        // Allocate memory for the color array with 3 elements (B, G, R)

        color = new unsigned char[3];

    }



    void TearDown() override {

        // Free the allocated memory

        delete[] color;

    }

};



// Test that splashBGR8G returns the correct green component.

TEST_F(SplashBGR8GTest_1037, ReturnsGreenComponent_1037) {

    color[0] = 255; // Blue

    color[1] = 128; // Green

    color[2] = 64;  // Red

    

    EXPECT_EQ(splashBGR8G(color), 128);

}



// Test that splashBGR8G handles minimum boundary condition.

TEST_F(SplashBGR8GTest_1037, MinBoundaryCondition_1037) {

    color[0] = 0; // Blue

    color[1] = 0; // Green

    color[2] = 0; // Red

    

    EXPECT_EQ(splashBGR8G(color), 0);

}



// Test that splashBGR8G handles maximum boundary condition.

TEST_F(SplashBGR8GTest_1037, MaxBoundaryCondition_1037) {

    color[0] = 255; // Blue

    color[1] = 255; // Green

    color[2] = 255; // Red

    

    EXPECT_EQ(splashBGR8G(color), 255);

}



// Test that splashBGR8G is not affected by other components.

TEST_F(SplashBGR8GTest_1037, UnaffectedByOtherComponents_1037) {

    color[0] = 255; // Blue

    color[1] = 100; // Green

    color[2] = 50;  // Red

    

    EXPECT_EQ(splashBGR8G(color), 100);

}
