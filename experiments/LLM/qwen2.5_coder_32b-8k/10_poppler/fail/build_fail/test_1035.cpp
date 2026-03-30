#include <gtest/gtest.h>



// Assuming SplashColorPtr is defined somewhere in the codebase.

typedef unsigned char* SplashColorPtr;



// Test fixture for SplashTypesTest_1035

class SplashTypesTest_1035 : public ::testing::Test {

protected:

    // Setup method to initialize any common objects before each test.

    void SetUp() override {

        color = new unsigned char[3];  // Allocate memory for RGB color values

    }



    // Teardown method to clean up after each test.

    void TearDown() override {

        delete[] color;  // Free the allocated memory

    }



    SplashColorPtr color;

};



// Test case to verify normal operation of splashRGB8B function

TEST_F(SplashTypesTest_1035, NormalOperation_1035) {

    color[0] = 255;  // R value

    color[1] = 128;  // G value

    color[2] = 64;   // B value



    EXPECT_EQ(splashRGB8B(color), 64);

}



// Test case to verify boundary conditions of splashRGB8B function with minimum values

TEST_F(SplashTypesTest_1035, BoundaryConditionMin_1035) {

    color[0] = 0;  // R value

    color[1] = 0;  // G value

    color[2] = 0;  // B value



    EXPECT_EQ(splashRGB8B(color), 0);

}



// Test case to verify boundary conditions of splashRGB8B function with maximum values

TEST_F(SplashTypesTest_1035, BoundaryConditionMax_1035) {

    color[0] = 255;  // R value

    color[1] = 255;  // G value

    color[2] = 255;  // B value



    EXPECT_EQ(splashRGB8B(color), 255);

}
