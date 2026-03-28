#include <gtest/gtest.h>



// Assuming SplashGouraudPattern is part of a larger class or used in some context

// Here we are testing the SplashGouraudPattern class based on its public interface



class SplashGouraudPatternTest : public ::testing::Test {

protected:

    SplashGouraudPattern pattern;

};



TEST_F(SplashGouraudPatternTest_1098, TestPosition_ReturnsFalseForArbitraryCoordinates_1098) {

    EXPECT_FALSE(pattern.testPosition(10, 20));

}



TEST_F(SplashGouraudPatternTest_1098, TestPosition_ReturnsFalseForZeroCoordinates_1098) {

    EXPECT_FALSE(pattern.testPosition(0, 0));

}



TEST_F(SplashGouraudPatternTest_1098, TestPosition_ReturnsFalseForNegativeCoordinates_1098) {

    EXPECT_FALSE(pattern.testPosition(-5, -10));

}
