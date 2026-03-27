#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



using namespace Catch;



TEST(ApproxTest_699, Constructor_DefaultValue_699) {

    Approx approx(42.0);

    EXPECT_TRUE(approx == 42.0);

}



TEST(ApproxTest_699, Constructor_NegativeValue_699) {

    Approx approx(-10.5);

    EXPECT_TRUE(approx == -10.5);

}



TEST(ApproxTest_699, Constructor_ZeroValue_699) {

    Approx approx(0.0);

    EXPECT_TRUE(approx == 0.0);

}



TEST(ApproxTest_699, OperatorEqual_DefaultTolerance_699) {

    Approx approx(42.0);

    EXPECT_TRUE(approx == 42.0);

    EXPECT_FALSE(approx == 43.0);

}



TEST(ApproxTest_699, OperatorGreaterOrEqual_SameValue_699) {

    Approx approx(42.0);

    EXPECT_TRUE(42.0 >= approx);

}



TEST(ApproxTest_699, OperatorGreaterOrEqual_LargerValue_699) {

    Approx approx(42.0);

    EXPECT_TRUE(43.0 >= approx);

}



TEST(ApproxTest_699, OperatorGreaterOrEqual_SmallerValue_699) {

    Approx approx(42.0);

    EXPECT_FALSE(41.0 >= approx);

}



TEST(ApproxTest_699, Epsilon_SetAndCheck_699) {

    Approx approx(42.0).epsilon(0.1);

    EXPECT_TRUE(approx == 42.1);

    EXPECT_FALSE(approx == 42.2);

}



TEST(ApproxTest_699, Margin_SetAndCheck_699) {

    Approx approx(42.0).margin(0.5);

    EXPECT_TRUE(approx == 42.6);

    EXPECT_FALSE(approx == 43.1);

}



TEST(ApproxTest_699, Scale_SetAndCheck_699) {

    Approx approx(42.0).scale(0.1);

    EXPECT_TRUE(approx == 42.5);

    EXPECT_FALSE(approx == 43.0);

}



TEST(ApproxTest_699, Custom_DefaultValues_699) {

    Approx customApprox = Approx::custom();

    EXPECT_TRUE(customApprox.epsilon() == std::numeric_limits<float>::epsilon() * 100.);

    EXPECT_TRUE(customApprox.margin() == 0.0);

    EXPECT_TRUE(customApprox.scale() == 0.0);

}



TEST(ApproxTest_699, ToString_CheckOutput_699) {

    Approx approx(42.0).epsilon(0.1).margin(0.5).scale(0.2);

    std::string expected = "Approx( 42.0, eps=0.000001, margin=0.5, scale=0.2 )";

    EXPECT_EQ(approx.toString(), expected);

}
