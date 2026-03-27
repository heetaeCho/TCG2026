#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_approx.hpp"



using namespace Catch;



// Test fixture for Approx class

class ApproxTest_697 : public ::testing::Test {

protected:

    Approx approx;

    

    ApproxTest_697() : approx(1.0) {}

};



// Test normal operation of equality comparison with default epsilon and margin

TEST_F(ApproxTest_697, DefaultEqualityComparison_697) {

    EXPECT_TRUE(approx == 1.0);

    EXPECT_FALSE(approx == 2.0);

}



// Test boundary conditions for equality comparison

TEST_F(ApproxTest_697, BoundaryEqualityComparison_697) {

    EXPECT_TRUE(approx == Approx(1.0).epsilon(0.1));

    EXPECT_FALSE(approx == Approx(1.2).epsilon(0.05));

}



// Test setting and using custom epsilon

TEST_F(ApproxTest_697, CustomEpsilonComparison_697) {

    approx.epsilon(0.2);

    EXPECT_TRUE(approx == 1.1);

    EXPECT_FALSE(approx == 1.3);

}



// Test setting and using custom margin

TEST_F(ApproxTest_697, CustomMarginComparison_697) {

    approx.margin(0.15);

    EXPECT_TRUE(approx == 1.15);

    EXPECT_FALSE(approx == 1.25);

}



// Test setting and using custom scale

TEST_F(ApproxTest_697, CustomScaleComparison_697) {

    approx.scale(0.5);

    EXPECT_TRUE(approx == Approx(2.0).scale(0.5));

    EXPECT_FALSE(approx == Approx(3.0).scale(0.5));

}



// Test negative value comparison

TEST_F(ApproxTest_697, NegativeValueComparison_697) {

    Approx negApprox(-1.0);

    EXPECT_TRUE(negApprox == -1.0);

    EXPECT_FALSE(negApprox == 1.0);

}



// Test chaining of modifiers

TEST_F(ApproxTest_697, ChainedModifiersComparison_697) {

    approx.epsilon(0.2).margin(0.15);

    EXPECT_TRUE(approx == 1.2);

    EXPECT_FALSE(approx == 1.4);

}



// Test equality comparison with different types

TEST_F(ApproxTest_697, TypeCompatibilityComparison_697) {

    EXPECT_TRUE(approx == static_cast<float>(1.0));

    EXPECT_TRUE(approx == static_cast<int>(1));

}
