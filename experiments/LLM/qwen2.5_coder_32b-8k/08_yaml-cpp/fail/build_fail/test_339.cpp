#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::trailing_zero;



// Mocking external collaborators if needed, but in this case, no need to mock as we treat it as a black box.



TEST_F(TrailingZeroPolicyTest_339, NormalOperation_339) {

    // Test with normal values

    uint64_t significand = 12345;

    int exponent = -5;

    unsigned_decimal_fp<uint64_t, int, false> result = remove_compact_t::on_trailing_zeros<format_standard>(significand, exponent);

    

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(TrailingZeroPolicyTest_339, BoundaryCondition_ZeroSignificand_339) {

    // Test with zero significand

    uint64_t significand = 0;

    int exponent = -5;

    unsigned_decimal_fp<uint64_t, int, false> result = remove_compact_t::on_trailing_zeros<format_standard>(significand, exponent);

    

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(TrailingZeroPolicyTest_339, BoundaryCondition_MaxSignificand_339) {

    // Test with max significand value

    uint64_t significand = UINT64_MAX;

    int exponent = -5;

    unsigned_decimal_fp<uint64_t, int, false> result = remove_compact_t::on_trailing_zeros<format_standard>(significand, exponent);

    

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(TrailingZeroPolicyTest_339, BoundaryCondition_MaxExponent_339) {

    // Test with max exponent value

    uint64_t significand = 12345;

    int exponent = INT_MAX;

    unsigned_decimal_fp<uint64_t, int, false> result = remove_compact_t::on_trailing_zeros<format_standard>(significand, exponent);

    

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(TrailingZeroPolicyTest_339, BoundaryCondition_MinExponent_339) {

    // Test with min exponent value

    uint64_t significand = 12345;

    int exponent = INT_MIN;

    unsigned_decimal_fp<uint64_t, int, false> result = remove_compact_t::on_trailing_zeros<format_standard>(significand, exponent);

    

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(TrailingZeroPolicyTest_339, NoTrailingZeros_339) {

    // Test with no trailing zeros

    uint64_t significand = 12345;

    int exponent = -5;

    unsigned_decimal_fp<uint64_t, int, false> result = remove_compact_t::no_trailing_zeros<format_standard>(significand, exponent);

    

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}
