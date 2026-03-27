#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



class ApproxTest_695 : public ::testing::Test {

protected:

    Catch::Approx approx;

    

    ApproxTest_695() : approx(10.0) {}

};



TEST_F(ApproxTest_695, DefaultConstructorSetsValue_695) {

    EXPECT_DOUBLE_EQ(approx.operator()(10.0).m_value, 10.0);

}



TEST_F(ApproxTest_695, EpsilonCanBeSetAndRetrieved_695) {

    approx.epsilon(0.1);

    Catch::Approx newApprox = approx(10.0);

    EXPECT_DOUBLE_EQ(newApprox.m_epsilon, 0.1 * 100.);

}



TEST_F(ApproxTest_695, MarginCanBeSetAndRetrieved_695) {

    approx.margin(0.2);

    Catch::Approx newApprox = approx(10.0);

    EXPECT_DOUBLE_EQ(newApprox.m_margin, 0.2);

}



TEST_F(ApproxTest_695, ScaleCanBeSetAndRetrieved_695) {

    approx.scale(0.3);

    Catch::Approx newApprox = approx(10.0);

    EXPECT_DOUBLE_EQ(newApprox.m_scale, 0.3);

}



TEST_F(ApproxTest_695, EqualityComparisonWithDefaultEpsilon_695) {

    EXPECT_TRUE(approx == 10.0 + std::numeric_limits<float>::epsilon() * 100.);

    EXPECT_FALSE(approx == 10.0 + 2 * std::numeric_limits<float>::epsilon() * 100.);

}



TEST_F(ApproxTest_695, EqualityComparisonWithCustomEpsilon_695) {

    approx.epsilon(0.01);

    EXPECT_TRUE(approx == 10.0 + 0.01);

    EXPECT_FALSE(approx == 10.0 + 0.02);

}



TEST_F(ApproxTest_695, EqualityComparisonWithMargin_695) {

    approx.margin(0.5);

    EXPECT_TRUE(approx == 9.5);

    EXPECT_TRUE(approx == 10.5);

    EXPECT_FALSE(approx == 9.4);

    EXPECT_FALSE(approx == 10.6);

}



TEST_F(ApproxTest_695, EqualityComparisonWithScale_695) {

    approx.scale(0.2);

    Catch::Approx newApprox = approx(10.0);

    EXPECT_TRUE(newApprox == 8.0); // 10.0 - (10.0 * 0.2)

    EXPECT_TRUE(newApprox == 12.0); // 10.0 + (10.0 * 0.2)

    EXPECT_FALSE(newApprox == 7.9);

    EXPECT_FALSE(newApprox == 12.1);

}



TEST_F(ApproxTest_695, NegativeOperatorInvertsValue_695) {

    Catch::Approx negApprox = approx.operator-();

    EXPECT_DOUBLE_EQ(negApprox.m_value, -10.0);

}



TEST_F(ApproxTest_695, CustomStaticFunctionCreatesNewInstance_695) {

    Catch::Approx customApprox = Catch::Approx::custom();

    EXPECT_NE(&customApprox, &approx);

}
