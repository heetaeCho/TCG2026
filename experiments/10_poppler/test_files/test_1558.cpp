#include <gtest/gtest.h>

#include "SplashMath.h"



// Test fixture for SplashMath tests

class SplashMathTest_1558 : public ::testing::Test {

protected:

    // Any setup or teardown can go here if needed in future tests

};



// Normal operation test cases

TEST_F(SplashMathTest_1558, splashCeil_PositiveInteger_1558) {

    EXPECT_EQ(splashCeil(4.0), 4);

}



TEST_F(SplashMathTest_1558, splashCeil_NegativeInteger_1558) {

    EXPECT_EQ(splashCeil(-4.0), -4);

}



TEST_F(SplashMathTest_1558, splashCeil_PositiveFraction_1558) {

    EXPECT_EQ(splashCeil(4.3), 5);

}



TEST_F(SplashMathTest_1558, splashCeil_NegativeFraction_1558) {

    EXPECT_EQ(splashCeil(-4.3), -4);

}



// Boundary conditions test cases

TEST_F(SplashMathTest_1558, splashCeil_Zero_1558) {

    EXPECT_EQ(splashCeil(0.0), 0);

}



TEST_F(SplashMathTest_1558, splashCeil_MaxInt_1558) {

    EXPECT_EQ(splashCeil(static_cast<SplashCoord>(INT_MAX)), INT_MAX);

}



TEST_F(SplashMathTest_1558, splashCeil_MinInt_1558) {

    EXPECT_EQ(splashCeil(static_cast<SplashCoord>(INT_MIN)), INT_MIN);

}



// Exceptional or error cases test cases

// In this case, there are no observable exceptional or error cases for the function



```


