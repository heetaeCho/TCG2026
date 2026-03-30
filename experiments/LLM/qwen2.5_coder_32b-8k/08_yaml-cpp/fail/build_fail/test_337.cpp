#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::trailing_zero;



// Test fixture for remove_t tests

class RemoveTrailingZerosTest_337 : public ::testing::Test {

protected:

    using Format = void; // Placeholder type as Format is not specified in the interface

    using DecimalSignificand = int64_t;

    using DecimalExponentType = int32_t;



    remove_t remover;

};



// Test normal operation with no trailing zeros

TEST_F(RemoveTrailingZerosTest_337, NoTrailingZeros_NormalOperation_337) {

    DecimalSignificand significand = 12345;

    DecimalExponentType exponent = -5;



    auto result = remover.no_trailing_zeros(significand, exponent);



    EXPECT_EQ(result.significand, 12345);

    EXPECT_EQ(result.exponent, -5);

}



// Test normal operation with trailing zeros

TEST_F(RemoveTrailingZerosTest_337, OnTrailingZeros_NormalOperation_337) {

    DecimalSignificand significand = 123450;

    DecimalExponentType exponent = -6;



    auto result = remover.on_trailing_zeros(significand, exponent);



    EXPECT_EQ(result.significand, 12345);

    EXPECT_EQ(result.exponent, -5);

}



// Test boundary condition with zero significand

TEST_F(RemoveTrailingZerosTest_337, NoTrailingZeros_ZeroSignificand_337) {

    DecimalSignificand significand = 0;

    DecimalExponentType exponent = 0;



    auto result = remover.no_trailing_zeros(significand, exponent);



    EXPECT_EQ(result.significand, 0);

    EXPECT_EQ(result.exponent, 0);

}



// Test boundary condition with zero significand

TEST_F(RemoveTrailingZerosTest_337, OnTrailingZeros_ZeroSignificand_337) {

    DecimalSignificand significand = 0;

    DecimalExponentType exponent = 0;



    auto result = remover.on_trailing_zeros(significand, exponent);



    EXPECT_EQ(result.significand, 0);

    EXPECT_EQ(result.exponent, 0);

}



// Test exceptional case with maximum significand value

TEST_F(RemoveTrailingZerosTest_337, NoTrailingZeros_MaxSignificand_337) {

    DecimalSignificand significand = std::numeric_limits<DecimalSignificand>::max();

    DecimalExponentType exponent = 0;



    auto result = remover.no_trailing_zeros(significand, exponent);



    EXPECT_EQ(result.significand, std::numeric_limits<DecimalSignificand>::max());

    EXPECT_EQ(result.exponent, 0);

}



// Test exceptional case with maximum significand value

TEST_F(RemoveTrailingZerosTest_337, OnTrailingZeros_MaxSignificand_337) {

    DecimalSignificand significand = std::numeric_limits<DecimalSignificand>::max();

    DecimalExponentType exponent = 0;



    auto result = remover.on_trailing_zeros(significand, exponent);



    EXPECT_EQ(result.significand, std::numeric_limits<DecimalSignificand>::max());

    EXPECT_EQ(result.exponent, 0);

}



// Test exceptional case with minimum significand value

TEST_F(RemoveTrailingZerosTest_337, NoTrailingZeros_MinSignificand_337) {

    DecimalSignificand significand = std::numeric_limits<DecimalSignificand>::min();

    DecimalExponentType exponent = 0;



    auto result = remover.no_trailing_zeros(significand, exponent);



    EXPECT_EQ(result.significand, std::numeric_limits<DecimalSignificand>::min());

    EXPECT_EQ(result.exponent, 0);

}



// Test exceptional case with minimum significand value

TEST_F(RemoveTrailingZerosTest_337, OnTrailingZeros_MinSignificand_337) {

    DecimalSignificand significand = std::numeric_limits<DecimalSignificand>::min();

    DecimalExponentType exponent = 0;



    auto result = remover.on_trailing_zeros(significand, exponent);



    EXPECT_EQ(result.significand, std::numeric_limits<DecimalSignificand>::min());

    EXPECT_EQ(result.exponent, 0);

}
