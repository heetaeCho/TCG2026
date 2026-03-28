#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



using namespace Catch;



// Test fixture for Approx class

class ApproxTest_692 : public ::testing::Test {

protected:

    // Helper function to create an Approx object with default values

    Approx createDefaultApprox() const {

        return Approx(0.0);

    }

};



// Test normal operation of constructor and equality comparison

TEST_F(ApproxTest_692, ConstructorAndEqualityComparison_692) {

    Approx approx = Approx(1.0);

    EXPECT_TRUE(approx(1.0));

    EXPECT_FALSE(approx(2.0));

}



// Test setting and using margin

TEST_F(ApproxTest_692, MarginUsage_692) {

    Approx approx = Approx(1.0).margin(0.5);

    EXPECT_TRUE(approx(1.4));

    EXPECT_FALSE(approx(1.6));

}



// Test setting and using epsilon

TEST_F(ApproxTest_692, EpsilonUsage_692) {

    Approx approx = Approx(1.0).epsilon(0.1);

    EXPECT_TRUE(approx(1.1));

    EXPECT_FALSE(approx(1.2));

}



// Test setting and using scale

TEST_F(ApproxTest_692, ScaleUsage_692) {

    Approx approx = Approx(1.0).scale(0.5);

    EXPECT_TRUE(approx(1.1));

    EXPECT_FALSE(approx(1.2));

}



// Test custom creation and usage

TEST_F(ApproxTest_692, CustomCreation_692) {

    Approx approx = Approx::custom().epsilon(0.1).margin(0.5);

    EXPECT_TRUE(approx(1.15));

    EXPECT_FALSE(approx(1.3));

}



// Test negative value handling

TEST_F(ApproxTest_692, NegativeValueHandling_692) {

    Approx approx = Approx(-1.0).epsilon(0.1);

    EXPECT_TRUE(approx(-1.1));

    EXPECT_FALSE(approx(-1.2));

}



// Test zero value handling with margin and epsilon

TEST_F(ApproxTest_692, ZeroValueHandling_692) {

    Approx approx = Approx(0.0).epsilon(0.1);

    EXPECT_TRUE(approx(0.1));

    EXPECT_FALSE(approx(0.2));



    Approx approxMargin = Approx(0.0).margin(0.1);

    EXPECT_TRUE(approxMargin(0.1));

    EXPECT_FALSE(approxMargin(0.2));

}



// Test boundary conditions for margin and epsilon

TEST_F(ApproxTest_692, BoundaryConditions_692) {

    Approx approx = Approx(1.0).margin(0.0);

    EXPECT_TRUE(approx(1.0));

    EXPECT_FALSE(approx(1.001));



    Approx approxEpsilon = Approx(1.0).epsilon(0.0);

    EXPECT_TRUE(approxEpsilon(1.0));

    EXPECT_FALSE(approxEpsilon(1.001));

}
