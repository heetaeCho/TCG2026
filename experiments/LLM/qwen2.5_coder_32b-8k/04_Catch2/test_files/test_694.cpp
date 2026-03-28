#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



using namespace Catch;



// Test Fixture for Approx class

class ApproxTest_694 : public ::testing::Test {

protected:

    Approx defaultApprox;

    Approx customApprox;



    ApproxTest_694() : defaultApprox(1.0), customApprox(Approx::custom().epsilon(0.5).margin(0.2)) {}

};



// Test normal operation of equality comparison

TEST_F(ApproxTest_694, DefaultEqualityComparison_694) {

    EXPECT_TRUE(defaultApprox == 1.0);

    EXPECT_FALSE(defaultApprox == 2.0);

}



// Test custom epsilon and margin settings

TEST_F(ApproxTest_694, CustomEpsilonMargin_694) {

    EXPECT_TRUE(customApprox == 1.5); // Within margin of 0.2 from 1.0 with epsilon 0.5

    EXPECT_FALSE(customApprox == 1.8); // Exceeds margin of 0.2 from 1.0 even with epsilon 0.5

}



// Test negative values comparison

TEST_F(ApproxTest_694, NegativeValueComparison_694) {

    Approx negApprox(-1.0);

    EXPECT_TRUE(negApprox == -1.0);

    EXPECT_FALSE(negApprox == -2.0);

}



// Test boundary conditions with zero value

TEST_F(ApproxTest_694, ZeroValueComparison_694) {

    Approx zeroApprox(0.0);

    EXPECT_TRUE(zeroApprox == 0.0);

    EXPECT_TRUE(zeroApprox.epsilon(1e-5) == 1e-6); // Within epsilon of 1e-5

}



// Test boundary conditions with very small value

TEST_F(ApproxTest_694, SmallValueComparison_694) {

    Approx smallApprox(std::numeric_limits<double>::min());

    EXPECT_TRUE(smallApprox == std::numeric_limits<double>::min());

    EXPECT_FALSE(smallApprox == 2 * std::numeric_limits<double>::min()); // Exceeds epsilon

}



// Test string representation

TEST_F(ApproxTest_694, ToStringRepresentation_694) {

    EXPECT_EQ(defaultApprox.toString(), "Approx( 1.0 )");

    EXPECT_EQ(customApprox.toString(), "Approx( 1.0, with margin of 0.2 and epsilon of 0.5 )");

}
