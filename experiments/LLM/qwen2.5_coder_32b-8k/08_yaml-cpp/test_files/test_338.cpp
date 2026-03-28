#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::trailing_zero;



TEST_F(TrailingZeroTest_338, NoTrailingZeros_ReturnsCorrectSignificandAndExponent_338) {

    auto result = remove_t::no_trailing_zeros<int, int>(12345, 6789);

    EXPECT_EQ(result.significand, 12345);

    EXPECT_EQ(result.exponent, 6789);

}



TEST_F(TrailingZeroTest_338, NoTrailingZeros_BoundaryConditionSignificandZero_338) {

    auto result = remove_t::no_trailing_zeros<int, int>(0, 6789);

    EXPECT_EQ(result.significand, 0);

    EXPECT_EQ(result.exponent, 6789);

}



TEST_F(TrailingZeroTest_338, NoTrailingZeros_BoundaryConditionExponentZero_338) {

    auto result = remove_t::no_trailing_zeros<int, int>(12345, 0);

    EXPECT_EQ(result.significand, 12345);

    EXPECT_EQ(result.exponent, 0);

}



TEST_F(TrailingZeroTest_338, NoTrailingZeros_BoundaryConditionBothZero_338) {

    auto result = remove_t::no_trailing_zeros<int, int>(0, 0);

    EXPECT_EQ(result.significand, 0);

    EXPECT_EQ(result.exponent, 0);

}



TEST_F(TrailingZeroTest_338, NoTrailingZeros_NegativeSignificand_338) {

    auto result = remove_t::no_trailing_zeros<int, int>(-12345, 6789);

    EXPECT_EQ(result.significand, -12345);

    EXPECT_EQ(result.exponent, 6789);

}



TEST_F(TrailingZeroTest_338, NoTrailingZeros_NegativeExponent_338) {

    auto result = remove_t::no_trailing_zeros<int, int>(12345, -6789);

    EXPECT_EQ(result.significand, 12345);

    EXPECT_EQ(result.exponent, -6789);

}



TEST_F(TrailingZeroTest_338, NoTrailingZeros_NegativeBoth_338) {

    auto result = remove_t::no_trailing_zeros<int, int>(-12345, -6789);

    EXPECT_EQ(result.significand, -12345);

    EXPECT_EQ(result.exponent, -6789);

}



TEST_F(TrailingZeroTest_338, NoTrailingZeros_LargeSignificand_338) {

    auto result = remove_t::no_trailing_zeros<int, int>(std::numeric_limits<int>::max(), 6789);

    EXPECT_EQ(result.significand, std::numeric_limits<int>::max());

    EXPECT_EQ(result.exponent, 6789);

}



TEST_F(TrailingZeroTest_338, NoTrailingZeros_LargeExponent_338) {

    auto result = remove_t::no_trailing_zeros<int, int>(12345, std::numeric_limits<int>::max());

    EXPECT_EQ(result.significand, 12345);

    EXPECT_EQ(result.exponent, std::numeric_limits<int>::max());

}
