#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashMath.h"



// Test Suite for splashDist function

class SplashMathTest_1563 : public ::testing::Test {

protected:

    // You can set up any common state here, if necessary.

};



// Test normal operation with positive coordinates

TEST_F(SplashMathTest_1563, NormalOperationPositiveCoordinates_1563) {

    EXPECT_DOUBLE_EQ(splashDist(0.0, 0.0, 3.0, 4.0), 5.0);

}



// Test normal operation with negative coordinates

TEST_F(SplashMathTest_1563, NormalOperationNegativeCoordinates_1563) {

    EXPECT_DOUBLE_EQ(splashDist(-3.0, -4.0, 0.0, 0.0), 5.0);

}



// Test boundary condition where points are the same

TEST_F(SplashMathTest_1563, BoundaryConditionSamePoints_1563) {

    EXPECT_DOUBLE_EQ(splashDist(5.0, 5.0, 5.0, 5.0), 0.0);

}



// Test boundary condition with one coordinate being zero

TEST_F(SplashMathTest_1563, BoundaryConditionOneCoordinateZero_1563) {

    EXPECT_DOUBLE_EQ(splashDist(0.0, 0.0, 5.0, 0.0), 5.0);

}



// Test boundary condition with both coordinates being zero

TEST_F(SplashMathTest_1563, BoundaryConditionBothCoordinatesZero_1563) {

    EXPECT_DOUBLE_EQ(splashDist(0.0, 0.0, 0.0, 0.0), 0.0);

}



// Test normal operation with large coordinates

TEST_F(SplashMathTest_1563, NormalOperationLargeCoordinates_1563) {

    EXPECT_DOUBLE_EQ(splashDist(-1000.0, -1000.0, 1000.0, 1000.0), 2828.4271247461903);

}



// Test normal operation with small coordinates

TEST_F(SplashMathTest_1563, NormalOperationSmallCoordinates_1563) {

    EXPECT_DOUBLE_EQ(splashDist(0.001, 0.001, 0.002, 0.002), 0.001414213562373095);

}
