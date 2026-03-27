#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_approx.hpp"



using namespace Catch;



// Test Fixture for Approx class

class ApproxTest_703 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialization code here if needed

    }



    void TearDown() override {

        // Cleanup code here if needed

    }

};



// Normal operation: scale sets the correct scale value

TEST_F(ApproxTest_703, ScaleSetsCorrectScaleValue_703) {

    Approx approx(1.0);

    auto& scaledApprox = approx.scale(2.5);

    EXPECT_DOUBLE_EQ(scaledApprox.scale(1.0), 2.5); // Assuming scale can be retrieved for testing

}



// Boundary condition: scale with zero

TEST_F(ApproxTest_703, ScaleWithZero_703) {

    Approx approx(1.0);

    auto& scaledApprox = approx.scale(0);

    EXPECT_DOUBLE_EQ(scaledApprox.scale(1.0), 0); // Assuming scale can be retrieved for testing

}



// Boundary condition: scale with negative value

TEST_F(ApproxTest_703, ScaleWithNegativeValue_703) {

    Approx approx(1.0);

    auto& scaledApprox = approx.scale(-2.5);

    EXPECT_DOUBLE_EQ(scaledApprox.scale(1.0), -2.5); // Assuming scale can be retrieved for testing

}



// Exceptional case: scale with non-numeric type (not applicable here as template constraint ensures numeric types)



// Verification of external interactions: Not applicable as Approx does not interact with external collaborators



// Normal operation: epsilon sets the correct epsilon value

TEST_F(ApproxTest_703, EpsilonSetsCorrectEpsilonValue_703) {

    Approx approx(1.0);

    auto& epsilonApprox = approx.epsilon(0.01);

    EXPECT_DOUBLE_EQ(epsilonApprox.epsilon(), 0.01); // Assuming epsilon can be retrieved for testing

}



// Boundary condition: epsilon with zero

TEST_F(ApproxTest_703, EpsilonWithZero_703) {

    Approx approx(1.0);

    auto& epsilonApprox = approx.epsilon(0);

    EXPECT_DOUBLE_EQ(epsilonApprox.epsilon(), 0); // Assuming epsilon can be retrieved for testing

}



// Boundary condition: epsilon with negative value

TEST_F(ApproxTest_703, EpsilonWithNegativeValue_703) {

    Approx approx(1.0);

    auto& epsilonApprox = approx.epsilon(-0.01);

    EXPECT_DOUBLE_EQ(epsilonApprox.epsilon(), -0.01); // Assuming epsilon can be retrieved for testing

}



// Normal operation: margin sets the correct margin value

TEST_F(ApproxTest_703, MarginSetsCorrectMarginValue_703) {

    Approx approx(1.0);

    auto& marginApprox = approx.margin(0.02);

    EXPECT_DOUBLE_EQ(marginApprox.margin(), 0.02); // Assuming margin can be retrieved for testing

}



// Boundary condition: margin with zero

TEST_F(ApproxTest_703, MarginWithZero_703) {

    Approx approx(1.0);

    auto& marginApprox = approx.margin(0);

    EXPECT_DOUBLE_EQ(marginApprox.margin(), 0); // Assuming margin can be retrieved for testing

}



// Boundary condition: margin with negative value

TEST_F(ApproxTest_703, MarginWithNegativeValue_703) {

    Approx approx(1.0);

    auto& marginApprox = approx.margin(-0.02);

    EXPECT_DOUBLE_EQ(marginApprox.margin(), -0.02); // Assuming margin can be retrieved for testing

}



// Normal operation: operator() checks approximate equality

TEST_F(ApproxTest_703, OperatorChecksApproximateEquality_703) {

    Approx approx(1.0);

    EXPECT_TRUE(approx(1.0001));

    EXPECT_FALSE(approx(1.1));

}



// Exceptional case: operator() with non-numeric type (not applicable here as template constraint ensures numeric types)



// Normal operation: toString returns a string representation

TEST_F(ApproxTest_703, ToStringReturnsStringRepresentation_703) {

    Approx approx(1.0);

    std::string str = approx.toString();

    EXPECT_FALSE(str.empty());

}



// Normal operation: operator- negates the value

TEST_F(ApproxTest_703, OperatorNegatesValue_703) {

    Approx approx(1.0);

    Approx negatedApprox = -approx;

    EXPECT_TRUE(negatedApprox(-1.0));

}
