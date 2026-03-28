#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



using namespace Catch;



class ApproxTest_693 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ApproxTest_693, DefaultConstructorSetsValueCorrectly_693) {

    double value = 10.0;

    Approx approx(value);

    EXPECT_TRUE(approx == value);

}



TEST_F(ApproxTest_693, TemplateConstructorSetsValueCorrectly_693) {

    int intValue = 5;

    Approx approx(intValue);

    EXPECT_TRUE(approx == static_cast<double>(intValue));

}



TEST_F(ApproxTest_693, CustomEpsilonWorksAsExpected_693) {

    double value = 10.0;

    double epsilon = 0.1;

    Approx approx(value).epsilon(epsilon);

    EXPECT_TRUE(approx == value + epsilon / 2);

    EXPECT_FALSE(approx == value + epsilon * 2);

}



TEST_F(ApproxTest_693, CustomMarginWorksAsExpected_693) {

    double value = 10.0;

    double margin = 0.5;

    Approx approx(value).margin(margin);

    EXPECT_TRUE(approx == value + margin / 2);

    EXPECT_FALSE(approx == value + margin * 2);

}



TEST_F(ApproxTest_693, CustomScaleWorksAsExpected_693) {

    double value = 10.0;

    double scale = 2.0;

    Approx approx(value).scale(scale);

    EXPECT_TRUE(approx == value + value * (std::numeric_limits<float>::epsilon() * 100. / scale));

}



TEST_F(ApproxTest_693, NegativeOperatorInvertsValue_693) {

    double value = -10.0;

    Approx approx(value);

    EXPECT_TRUE(-approx == static_cast<double>(-value));

}



TEST_F(ApproxTest_693, CustomMethodCreatesNewApproxObject_693) {

    double value = 10.0;

    Approx approx(value);

    Approx customApprox = approx.custom();

    EXPECT_TRUE(customApprox == value);

}



TEST_F(ApproxTest_693, ToStringReturnsNonEmptyString_693) {

    double value = 10.0;

    Approx approx(value);

    EXPECT_FALSE(approx.toString().empty());

}
