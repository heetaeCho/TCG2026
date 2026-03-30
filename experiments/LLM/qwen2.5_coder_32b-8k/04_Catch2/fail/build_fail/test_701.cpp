#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



using namespace Catch;



TEST_F(ApproxTests_701, DefaultConstructorSetsDefaultEpsilon_701) {

    Approx approx(1.0);

    EXPECT_EQ(approx.epsilon(), std::numeric_limits<float>::epsilon() * 100.);

}



TEST_F(ApproxTests_701, CustomEpsilonIsSetCorrectly_701) {

    Approx approx(1.0).epsilon(0.01);

    EXPECT_DOUBLE_EQ(approx.epsilon(), 0.01);

}



TEST_F(ApproxTests_701, EpsilonCanBeChained_701) {

    Approx approx = Approx(1.0).epsilon(0.01).margin(0.02);

    EXPECT_DOUBLE_EQ(approx.epsilon(), 0.01);

    EXPECT_DOUBLE_EQ(approx.margin(), 0.02);

}



TEST_F(ApproxTests_701, MarginCanBeSetCorrectly_701) {

    Approx approx(1.0).margin(0.02);

    EXPECT_DOUBLE_EQ(approx.margin(), 0.02);

}



TEST_F(ApproxTests_701, ScaleCanBeSetCorrectly_701) {

    Approx approx(1.0).scale(0.5);

    EXPECT_DOUBLE_EQ(approx.scale(), 0.5);

}



TEST_F(ApproxTests_701, CustomApproxReturnsNewInstance_701) {

    Approx approx = Approx::custom();

    EXPECT_DOUBLE_EQ(approx.epsilon(), std::numeric_limits<float>::epsilon() * 100.);

}



TEST_F(ApproxTests_701, NegativeOperatorCreatesNewInstanceWithNegativeValue_701) {

    Approx approx(1.0);

    Approx negApprox = -approx;

    EXPECT_DOUBLE_EQ(negApprox.value(), -1.0);

}



TEST_F(ApproxTests_701, EqualityComparisonWithDefaultEpsilon_701) {

    Approx approx(1.0);

    EXPECT_TRUE(approx == 1.0 + std::numeric_limits<float>::epsilon() * 100.);

    EXPECT_FALSE(approx == 1.0 + 1.0);

}



TEST_F(ApproxTests_701, EqualityComparisonWithCustomEpsilon_701) {

    Approx approx(1.0).epsilon(0.01);

    EXPECT_TRUE(approx == 1.005);

    EXPECT_FALSE(approx == 1.02);

}



TEST_F(ApproxTests_701, ToStringReturnsCorrectString_701) {

    Approx approx(1.0).epsilon(0.01).margin(0.02);

    EXPECT_EQ(approx.toString(), "Approx( 1 )");

}
