#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



using namespace Catch;



// Test fixture for Approx class tests with TEST_ID 696

class ApproxTest_696 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed (not required in this case)

    }



    void TearDown() override {

        // Teardown code if needed (not required in this case)

    }

};



// Test normal operation of Approx with default constructor

TEST_F(ApproxTest_696, DefaultConstructor_NormalOperation_696) {

    Approx approx(1.0);

    EXPECT_TRUE(approx == 1.0);

}



// Test normal operation of Approx with custom epsilon

TEST_F(ApproxTest_696, CustomEpsilon_NormalOperation_696) {

    Approx approx = Approx(1.0).epsilon(0.1);

    EXPECT_TRUE(approx == 1.1);

}



// Test normal operation of Approx with custom margin

TEST_F(ApproxTest_696, CustomMargin_NormalOperation_696) {

    Approx approx = Approx(1.0).margin(0.2);

    EXPECT_TRUE(approx == 1.2);

}



// Test boundary condition where values are exactly equal

TEST_F(ApproxTest_696, ExactEquality_BoundaryCondition_696) {

    Approx approx(1.0);

    EXPECT_TRUE(approx == 1.0);

}



// Test boundary condition where values are not approximately equal

TEST_F(ApproxTest_696, NotApproximatelyEqual_BoundaryCondition_696) {

    Approx approx(1.0);

    EXPECT_FALSE(approx == 2.0);

}



// Test exceptional case with negative margin (should still work but is unusual)

TEST_F(ApproxTest_696, NegativeMargin_ExceptionalCase_696) {

    Approx approx = Approx(1.0).margin(-0.1);

    EXPECT_TRUE(approx == 1.0);

}



// Test exceptional case with zero epsilon

TEST_F(ApproxTest_696, ZeroEpsilon_ExceptionalCase_696) {

    Approx approx = Approx(1.0).epsilon(0.0);

    EXPECT_FALSE(approx == 1.00001);

}



// Test negative value comparison

TEST_F(ApproxTest_696, NegativeValueComparison_NormalOperation_696) {

    Approx approx(-1.0);

    EXPECT_TRUE(approx == -1.0);

}



// Test usage of operator-()

TEST_F(ApproxTest_696, OperatorMinus_UnaryOperator_696) {

    Approx approx = -Approx(1.0);

    EXPECT_TRUE(approx == -1.0);

}



// Test toString() method

TEST_F(ApproxTest_696, ToString_MethodCall_696) {

    Approx approx(1.0);

    std::string str = approx.toString();

    EXPECT_EQ(str.find("Approx"), 0); // Check if the string starts with "Approx"

}
