#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



using namespace Catch;



// Test fixture for Approx class tests

class ApproxTest_698 : public ::testing::Test {

protected:

    Approx defaultApprox;

    Approx customApprox;



    ApproxTest_698() 

        : defaultApprox(1.0), 

          customApprox(Approx::custom().epsilon(0.01).margin(0.02).scale(1.0)) {}

};



// Test normal operation of equality comparison

TEST_F(ApproxTest_698, DefaultEqualityComparison_698) {

    EXPECT_TRUE(defaultApprox == 1.0);

    EXPECT_FALSE(defaultApprox == 2.0);

}



// Test custom Approx with specified epsilon, margin, and scale

TEST_F(ApproxTest_698, CustomEqualityComparison_698) {

    EXPECT_TRUE(customApprox == 1.01); // within epsilon

    EXPECT_TRUE(customApprox == 1.02); // within margin

    EXPECT_FALSE(customApprox == 1.03); // outside both epsilon and margin

}



// Test boundary conditions for default Approx

TEST_F(ApproxTest_698, DefaultBoundaryConditions_698) {

    EXPECT_TRUE(defaultApprox == 1.0 + std::numeric_limits<float>::epsilon() * 100);

    EXPECT_FALSE(defaultApprox == 1.0 + std::numeric_limits<float>::epsilon() * 200);

}



// Test boundary conditions for custom Approx

TEST_F(ApproxTest_698, CustomBoundaryConditions_698) {

    EXPECT_TRUE(customApprox == 1.0 + 0.005); // within epsilon

    EXPECT_TRUE(customApprox == 1.0 + 0.02);  // within margin

    EXPECT_FALSE(customApprox == 1.0 + 0.03); // outside both epsilon and margin

}



// Test exception handling for invalid types (not applicable here as constructor template ensures valid types)

// No need for exceptional case tests as the class is templated to accept only constructible-to-double types



// Test toString method output for default Approx

TEST_F(ApproxTest_698, DefaultToString_698) {

    EXPECT_EQ(defaultApprox.toString(), "Approx( 1.0 )");

}



// Test toString method output for custom Approx

TEST_F(ApproxTest_698, CustomToString_698) {

    EXPECT_EQ(customApprox.toString(), "Approx( 1 ).epsilon( 0.01 ).margin( 0.02 ).scale( 1 )");

}
