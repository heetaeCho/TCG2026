#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::trailing_zero;



TEST(report_t_Test_341, OnTrailingZeros_ReturnsCorrectValue_341) {

    unsigned_decimal_fp<int, int, true> result = report_t::on_trailing_zeros(123, 456);

    EXPECT_EQ(result.significand, 123);

    EXPECT_EQ(result.exponent, 456);

    EXPECT_TRUE(result.hasTrailingZeros);

}



TEST(report_t_Test_341, OnTrailingZeros_BoundaryConditionSignificandZero_341) {

    unsigned_decimal_fp<int, int, true> result = report_t::on_trailing_zeros(0, 456);

    EXPECT_EQ(result.significand, 0);

    EXPECT_EQ(result.exponent, 456);

    EXPECT_TRUE(result.hasTrailingZeros);

}



TEST(report_t_Test_341, OnTrailingZeros_BoundaryConditionExponentZero_341) {

    unsigned_decimal_fp<int, int, true> result = report_t::on_trailing_zeros(123, 0);

    EXPECT_EQ(result.significand, 123);

    EXPECT_EQ(result.exponent, 0);

    EXPECT_TRUE(result.hasTrailingZeros);

}



// Assuming no_trailing_zeros behaves similarly but sets hasTrailingZeros to false

TEST(report_t_Test_341, NoTrailingZeros_ReturnsCorrectValue_341) {

    unsigned_decimal_fp<int, int, true> result = report_t::no_trailing_zeros(123, 456);

    EXPECT_EQ(result.significand, 123);

    EXPECT_EQ(result.exponent, 456);

    EXPECT_FALSE(result.hasTrailingZeros);

}



TEST(report_t_Test_341, NoTrailingZeros_BoundaryConditionSignificandZero_341) {

    unsigned_decimal_fp<int, int, true> result = report_t::no_trailing_zeros(0, 456);

    EXPECT_EQ(result.significand, 0);

    EXPECT_EQ(result.exponent, 456);

    EXPECT_FALSE(result.hasTrailingZeros);

}



TEST(report_t_Test_341, NoTrailingZeros_BoundaryConditionExponentZero_341) {

    unsigned_decimal_fp<int, int, true> result = report_t::no_trailing_zeros(123, 0);

    EXPECT_EQ(result.significand, 123);

    EXPECT_EQ(result.exponent, 0);

    EXPECT_FALSE(result.hasTrailingZeros);

}
