#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::trailing_zero;



// Fixture class for ignore_t tests

class IgnoreTPolicyTest : public ::testing::Test {

protected:

    using DecimalSignificand = uint64_t;

    using DecimalExponentType = int32_t;

    using ResultType = unsigned_decimal_fp<DecimalSignificand, DecimalExponentType, false>;



    DecimalSignificand significand;

    DecimalExponentType exponent;

    ResultType expected_result;



    void SetUp() override {

        significand = 123456789;

        exponent = -42;

        expected_result = {significand, exponent};

    }

};



TEST_F(IgnoreTPolicyTest, OnTrailingZeros_ReturnsCorrectResult_335) {

    auto result = ignore_t::on_trailing_zeros(significand, exponent);

    EXPECT_EQ(result.significand, expected_result.significand);

    EXPECT_EQ(result.exponent, expected_result.exponent);

}



TEST_F(IgnoreTPolicyTest, NoTrailingZeros_ReturnsCorrectResult_335) {

    auto result = ignore_t::no_trailing_zeros(significand, exponent);

    EXPECT_EQ(result.significand, expected_result.significand);

    EXPECT_EQ(result.exponent, expected_result.exponent);

}



TEST_F(IgnoreTPolicyTest, OnTrailingZeros_BoundaryCondition_335) {

    significand = 0;

    exponent = 0;

    expected_result = {significand, exponent};

    auto result = ignore_t::on_trailing_zeros(significand, exponent);

    EXPECT_EQ(result.significand, expected_result.significand);

    EXPECT_EQ(result.exponent, expected_result.exponent);

}



TEST_F(IgnoreTPolicyTest, NoTrailingZeros_BoundaryCondition_335) {

    significand = 0;

    exponent = 0;

    expected_result = {significand, exponent};

    auto result = ignore_t::no_trailing_zeros(significand, exponent);

    EXPECT_EQ(result.significand, expected_result.significand);

    EXPECT_EQ(result.exponent, expected_result.exponent);

}



TEST_F(IgnoreTPolicyTest, OnTrailingZeros_MaxSignificand_335) {

    significand = std::numeric_limits<DecimalSignificand>::max();

    exponent = std::numeric_limits<DecimalExponentType>::min();

    expected_result = {significand, exponent};

    auto result = ignore_t::on_trailing_zeros(significand, exponent);

    EXPECT_EQ(result.significand, expected_result.significand);

    EXPECT_EQ(result.exponent, expected_result.exponent);

}



TEST_F(IgnoreTPolicyTest, NoTrailingZeros_MaxSignificand_335) {

    significand = std::numeric_limits<DecimalSignificand>::max();

    exponent = std::numeric_limits<DecimalExponentType>::min();

    expected_result = {significand, exponent};

    auto result = ignore_t::no_trailing_zeros(significand, exponent);

    EXPECT_EQ(result.significand, expected_result.significand);

    EXPECT_EQ(result.exponent, expected_result.exponent);

}



TEST_F(IgnoreTPolicyTest, OnTrailingZeros_MinExponent_335) {

    significand = 1;

    exponent = std::numeric_limits<DecimalExponentType>::min();

    expected_result = {significand, exponent};

    auto result = ignore_t::on_trailing_zeros(significand, exponent);

    EXPECT_EQ(result.significand, expected_result.significand);

    EXPECT_EQ(result.exponent, expected_result.exponent);

}



TEST_F(IgnoreTPolicyTest, NoTrailingZeros_MinExponent_335) {

    significand = 1;

    exponent = std::numeric_limits<DecimalExponentType>::min();

    expected_result = {significand, exponent};

    auto result = ignore_t::no_trailing_zeros(significand, exponent);

    EXPECT_EQ(result.significand, expected_result.significand);

    EXPECT_EQ(result.exponent, expected_result.exponent);

}
