#include <gtest/gtest.h>

#include <catch2/catch_approx.hpp>



using namespace Catch;



// Test Fixture for Approx class

class ApproxTest_709 : public ::testing::Test {

protected:

    Approx defaultApprox;

    Approx customApprox;



    ApproxTest_709() 

        : defaultApprox(42.0), 

          customApprox(Approx(42.0).epsilon(1e-6).margin(1e-12)) {}

};



// Test for normal operation of toString()

TEST_F(ApproxTest_709, ToString_ReturnsExpectedString_709) {

    EXPECT_EQ(defaultApprox.toString(), "is approximately 42");

}



// Test boundary conditions with zero value

TEST_F(ApproxTest_709, ToString_ZeroValue_ReturnsExpectedString_709) {

    Approx zeroApprox(0.0);

    EXPECT_EQ(zeroApprox.toString(), "is approximately 0");

}



// Test boundary conditions with negative value

TEST_F(ApproxTest_709, ToString_NegativeValue_ReturnsExpectedString_709) {

    Approx negativeApprox(-42.0);

    EXPECT_EQ(negativeApprox.toString(), "is approximately -42");

}



// Test for custom epsilon and margin settings

TEST_F(ApproxTest_709, CustomEpsilonMargin_ReturnsExpectedString_709) {

    std::string expected = "is approximately 42 (with an absolute error of <= 1e-12 or a relative error of <= 1e-6%)";

    EXPECT_EQ(customApprox.toString(), expected);

}



// Test for operator()

TEST_F(ApproxTest_709, Operator_ReturnsNewApproxObject_709) {

    Approx newApprox = defaultApprox(3.14);

    std::string expected = "is approximately 3.14";

    EXPECT_EQ(newApprox.toString(), expected);

}



// Test for operator-()

TEST_F(ApproxTest_709, OperatorNegation_ReturnsNewApproxObject_709) {

    Approx negatedApprox = -defaultApprox;

    std::string expected = "is approximately -42";

    EXPECT_EQ(negatedApprox.toString(), expected);

}



// Test for setting epsilon

TEST_F(ApproxTest_709, SetEpsilon_ReturnsNewApproxObject_709) {

    Approx newApprox = defaultApprox.epsilon(1e-3);

    std::string expected = "is approximately 42 (with an absolute error of <= 0 or a relative error of <= 0.001%)";

    EXPECT_EQ(newApprox.toString(), expected);

}



// Test for setting margin

TEST_F(ApproxTest_709, SetMargin_ReturnsNewApproxObject_709) {

    Approx newApprox = defaultApprox.margin(1e-3);

    std::string expected = "is approximately 42 (with an absolute error of <= 0.001 or a relative error of <= 0%)";

    EXPECT_EQ(newApprox.toString(), expected);

}



// Test for setting scale

TEST_F(ApproxTest_709, SetScale_ReturnsNewApproxObject_709) {

    Approx newApprox = defaultApprox.scale(1e3);

    std::string expected = "is approximately 42 (with an absolute error of <= 0 or a relative error of <= 100%)";

    EXPECT_EQ(newApprox.toString(), expected);

}
