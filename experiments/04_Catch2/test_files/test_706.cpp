#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



class ApproxTest : public ::testing::Test {

protected:

    Catch::Approx approx;

    

    ApproxTest() : approx(42.0) {}

};



TEST_F(ApproxTest_706, ToString_ReturnsCorrectString_706) {

    EXPECT_EQ(approx.toString(), "Approx( 42 )");

}



TEST_F(ApproxTest_706, ConstructorWithDouble_SetsValueCorrectly_706) {

    Catch::Approx approx(3.14);

    EXPECT_EQ(approx.toString(), "Approx( 3.14 )");

}



TEST_F(ApproxTest_706, Custom_ReturnsNewInstance_706) {

    auto customApprox = Catch::Approx::custom();

    EXPECT_NE(&customApprox, &approx);

}



TEST_F(ApproxTest_706, UnaryMinus_ReturnsNegatedValue_706) {

    auto negatedApprox = -approx;

    EXPECT_EQ(negatedApprox.toString(), "Approx( -42 )");

}



TEST_F(ApproxTest_706, OperatorCallWithDouble_SetsNewValue_706) {

    auto newApprox = approx(100.0);

    EXPECT_EQ(newApprox.toString(), "Approx( 100 )");

}



TEST_F(ApproxTest_706, EpsilonSetsNewEpsilon_ReturnsReferenceToSelf_706) {

    auto& modifiedApprox = approx.epsilon(0.5);

    EXPECT_EQ(&modifiedApprox, &approx);

}



TEST_F(ApproxTest_706, MarginSetsNewMargin_ReturnsReferenceToSelf_706) {

    auto& modifiedApprox = approx.margin(0.1);

    EXPECT_EQ(&modifiedApprox, &approx);

}



TEST_F(ApproxTest_706, ScaleSetsNewScale_ReturnsReferenceToSelf_706) {

    auto& modifiedApprox = approx.scale(2.0);

    EXPECT_EQ(&modifiedApprox, &approx);

}
