#include <gtest/gtest.h>

#include <catch2/catch_approx.hpp>



using namespace Catch;



class ApproxTest : public ::testing::Test {

protected:

    ApproxTest() {}

};



TEST_F(ApproxTest_702, ConstructorDouble_702) {

    Approx approx(1.0);

}



TEST_F(ApproxTest_702, ConstructorTemplate_702) {

    Approx approx = Approx(1);

}



TEST_F(ApproxTest_702, MarginNormalOperation_702) {

    Approx approx = Approx(1.0).margin(0.1);

}



TEST_F(ApproxTest_702, MarginBoundaryCondition_702) {

    Approx approx = Approx(1.0).margin(0.0);

}



TEST_F(ApproxTest_702, EpsilonNormalOperation_702) {

    Approx approx = Approx(1.0).epsilon(0.1);

}



TEST_F(ApproxTest_702, EpsilonBoundaryCondition_702) {

    Approx approx = Approx(1.0).epsilon(0.0);

}



TEST_F(ApproxTest_702, ScaleNormalOperation_702) {

    Approx approx = Approx(1.0).scale(2.0);

}



TEST_F(ApproxTest_702, ScaleBoundaryCondition_702) {

    Approx approx = Approx(1.0).scale(0.0);

}



TEST_F(ApproxTest_702, CustomStaticMethod_702) {

    Approx approx = Approx::custom();

}



TEST_F(ApproxTest_702, NegationOperator_702) {

    Approx approx = Approx(1.0);

    Approx negatedApprox = -approx;

}



TEST_F(ApproxTest_702, ToStringMethod_702) {

    Approx approx = Approx(1.0);

    std::string str = approx.toString();

}



TEST_F(ApproxTest_702, CallOperatorNormalOperation_702) {

    Approx approx = Approx(1.0);

    bool result = approx(1.1);

}



TEST_F(ApproxTest_702, CallOperatorBoundaryCondition_702) {

    Approx approx = Approx(1.0).margin(0.0);

    bool result = approx(1.0);

}
