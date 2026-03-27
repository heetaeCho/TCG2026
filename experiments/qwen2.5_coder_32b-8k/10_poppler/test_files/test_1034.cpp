#include <gtest/gtest.h>



// Assuming SplashColorPtr is defined as an array of unsigned chars

typedef unsigned char* SplashColorPtr;



unsigned char splashRGB8G(SplashColorPtr rgb8) { return rgb8[1]; }



class SplashTypesTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary test state here if needed

    }

};



TEST_F(SplashTypesTest_1034, NormalOperation_1034) {

    unsigned char color[] = {255, 128, 64}; // Example RGB values

    SplashColorPtr rgb8 = color;

    EXPECT_EQ(splashRGB8G(rgb8), 128);

}



TEST_F(SplashTypesTest_1034, BoundaryConditionsMinValue_1034) {

    unsigned char color[] = {0, 0, 0}; // Minimum RGB values

    SplashColorPtr rgb8 = color;

    EXPECT_EQ(splashRGB8G(rgb8), 0);

}



TEST_F(SplashTypesTest_1034, BoundaryConditionsMaxValue_1034) {

    unsigned char color[] = {255, 255, 255}; // Maximum RGB values

    SplashColorPtr rgb8 = color;

    EXPECT_EQ(splashRGB8G(rgb8), 255);

}

```


