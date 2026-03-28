#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_approx.cpp"



using namespace Catch::literals;



TEST(CatchApproxTest_707, ConstructionFromLongDouble_707) {

    auto approx = 1.0L_a;

    EXPECT_DOUBLE_EQ(approx.value(), 1.0);

}



TEST(CatchApproxTest_707, ComparisonWithEqualValue_707) {

    auto approx = 1.0L_a;

    EXPECT_TRUE(approx == 1.0);

}



TEST(CatchApproxTest_707, ComparisonWithDifferentValueWithinMargin_707) {

    auto approx = 1.0L_a;

    EXPECT_TRUE(approx == 1.0000001);

}



TEST(CatchApproxTest_707, ComparisonWithDifferentValueOutsideMargin_707) {

    auto approx = 1.0L_a;

    EXPECT_FALSE(approx == 2.0);

}



TEST(CatchApproxTest_707, SetCustomMarginAndCompareWithinNewMargin_707) {

    auto approx = 1.0L_a.margin(0.5);

    EXPECT_TRUE(approx == 1.4);

}



TEST(CatchApproxTest_707, SetCustomMarginAndCompareOutsideNewMargin_707) {

    auto approx = 1.0L_a.margin(0.05);

    EXPECT_FALSE(approx == 1.1);

}



TEST(CatchApproxTest_707, UseDefaultEpsilonForComparison_707) {

    auto approx = 1.0L_a.epsilon(0.0);

    EXPECT_TRUE(approx == (1.0 + std::numeric_limits<double>::epsilon()));

}
