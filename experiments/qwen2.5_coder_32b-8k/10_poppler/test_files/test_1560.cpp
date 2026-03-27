#include <gtest/gtest.h>



// Assuming SplashCoord is a typedef for a floating-point type like double or float.

typedef double SplashCoord;



namespace {



TEST(splashAvgTest_1560, NormalOperation_1560) {

    EXPECT_DOUBLE_EQ(2.5, splashAvg(2.0, 3.0));

}



TEST(splashAvgTest_1560, BoundaryCondition_ZeroValues_1560) {

    EXPECT_DOUBLE_EQ(0.0, splashAvg(0.0, 0.0));

}



TEST(splashAvgTest_1560, BoundaryCondition_NegativeValues_1560) {

    EXPECT_DOUBLE_EQ(-2.5, splashAvg(-3.0, -2.0));

}



TEST(splashAvgTest_1560, BoundaryCondition_MixedSigns_1560) {

    EXPECT_DOUBLE_EQ(0.0, splashAvg(-1.0, 1.0));

}



TEST(splashAvgTest_1560, LargeValues_1560) {

    EXPECT_DOUBLE_EQ(1e9, splashAvg(1e9, 1e9));

}



} // namespace
