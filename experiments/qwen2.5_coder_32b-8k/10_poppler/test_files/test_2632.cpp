#include <gtest/gtest.h>

#include "HtmlUtils.h"



class HtmlUtilsTest_2632 : public ::testing::Test {

protected:

    std::array<double, 6> mat;

};



TEST_F(HtmlUtilsTest_2632, MatWithNegativeFirstElement_ReturnsTrue_2632) {

    mat = {-1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_TRUE(isMatRotOrSkew(mat));

}



TEST_F(HtmlUtilsTest_2632, MatWithFirstElementZero_ReturnsFalse_2632) {

    mat = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_FALSE(isMatRotOrSkew(mat));

}



TEST_F(HtmlUtilsTest_2632, MatWithFirstElementPositive_ReturnsFalse_2632) {

    mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_FALSE(isMatRotOrSkew(mat));

}



TEST_F(HtmlUtilsTest_2632, MatWithSecondElementSlightlyAboveThreshold_ReturnsTrue_2632) {

    mat = {1.0, 0.101, 0.0, 1.0, 0.0, 0.0};

    EXPECT_TRUE(isMatRotOrSkew(mat));

}



TEST_F(HtmlUtilsTest_2632, MatWithSecondElementSlightlyBelowThreshold_ReturnsFalse_2632) {

    mat = {1.0, 0.099, 0.0, 1.0, 0.0, 0.0};

    EXPECT_FALSE(isMatRotOrSkew(mat));

}



TEST_F(HtmlUtilsTest_2632, MatWithSecondElementExactlyThreshold_ReturnsFalse_2632) {

    mat = {1.0, 0.1, 0.0, 1.0, 0.0, 0.0};

    EXPECT_FALSE(isMatRotOrSkew(mat));

}



TEST_F(HtmlUtilsTest_2632, MatWithBothConditionsMet_ReturnsTrue_2632) {

    mat = {-1.0, 0.101, 0.0, 1.0, 0.0, 0.0};

    EXPECT_TRUE(isMatRotOrSkew(mat));

}



TEST_F(HtmlUtilsTest_2632, MatWithBothConditionsNotMet_ReturnsFalse_2632) {

    mat = {1.0, 0.099, 0.0, 1.0, 0.0, 0.0};

    EXPECT_FALSE(isMatRotOrSkew(mat));

}
