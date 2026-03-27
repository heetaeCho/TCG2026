#include <gtest/gtest.h>

#include "./TestProjects/poppler/splash/SplashMath.h"



class SplashMathTest_1557 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



// Test normal operation with positive numbers

TEST_F(SplashMathTest_1557, PositiveNumberFlooring_1557) {

    EXPECT_EQ(splashFloor(3.7), 3);

    EXPECT_EQ(splashFloor(2.0), 2);

}



// Test normal operation with negative numbers

TEST_F(SplashMathTest_1557, NegativeNumberFlooring_1557) {

    EXPECT_EQ(splashFloor(-3.7), -4);

    EXPECT_EQ(splashFloor(-2.0), -2);

}



// Test boundary condition with zero

TEST_F(SplashMathTest_1557, ZeroFlooring_1557) {

    EXPECT_EQ(splashFloor(0.0), 0);

}



// Test boundary condition with large positive number

TEST_F(SplashMathTest_1557, LargePositiveNumberFlooring_1557) {

    EXPECT_EQ(splashFloor(987654321.987654321), 987654321);

}



// Test boundary condition with large negative number

TEST_F(SplashMathTest_1557, LargeNegativeNumberFlooring_1557) {

    EXPECT_EQ(splashFloor(-987654321.987654321), -987654322);

}



// Test exceptional case with positive edge case

TEST_F(SplashMathTest_1557, PositiveEdgeCaseFlooring_1557) {

    EXPECT_EQ(splashFloor(0.999999999), 0);

}



// Test exceptional case with negative edge case

TEST_F(SplashMathTest_1557, NegativeEdgeCaseFlooring_1557) {

    EXPECT_EQ(splashFloor(-0.999999999), -1);

}
