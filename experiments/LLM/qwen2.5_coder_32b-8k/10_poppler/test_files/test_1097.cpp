#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/SplashOutputDev.h"



class SplashGouraudPatternTest : public ::testing::Test {

protected:

    SplashGouraudPattern pattern;

};



TEST_F(SplashGouraudPatternTest_1097, GetColorReturnsFalseForAnyInput_1097) {

    int x = 0;

    int y = 0;

    SplashColorPtr c = nullptr; // Assuming SplashColorPtr is a pointer type



    EXPECT_FALSE(pattern.getColor(x, y, c));

}



TEST_F(SplashGouraudPatternTest_1097, GetColorReturnsFalseForNegativeCoordinates_1097) {

    int x = -1;

    int y = -1;

    SplashColorPtr c = nullptr;



    EXPECT_FALSE(pattern.getColor(x, y, c));

}



TEST_F(SplashGouraudPatternTest_1097, GetColorReturnsFalseForLargePositiveCoordinates_1097) {

    int x = std::numeric_limits<int>::max();

    int y = std::numeric_limits<int>::max();

    SplashColorPtr c = nullptr;



    EXPECT_FALSE(pattern.getColor(x, y, c));

}
