#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace trailing_zero {



using namespace YAML::jkj::dragonbox;



TEST_F(DragonboxTest_340, NoTrailingZeros_ReturnsCorrectValues_340) {

    using DecimalSignificand = uint64_t;

    using DecimalExponentType = int;



    DecimalSignificand significand = 12345;

    DecimalExponentType exponent = -2;



    auto result = remove_compact_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(significand, exponent);



    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(DragonboxTest_340, NoTrailingZeros_BoundaryConditionZeroSignificand_340) {

    using DecimalSignificand = uint64_t;

    using DecimalExponentType = int;



    DecimalSignificand significand = 0;

    DecimalExponentType exponent = -2;



    auto result = remove_compact_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(significand, exponent);



    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(DragonboxTest_340, NoTrailingZeros_BoundaryConditionMaxSignificand_340) {

    using DecimalSignificand = uint64_t;

    using DecimalExponentType = int;



    DecimalSignificand significand = std::numeric_limits<DecimalSignificand>::max();

    DecimalExponentType exponent = 2;



    auto result = remove_compact_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(significand, exponent);



    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(DragonboxTest_340, NoTrailingZeros_BoundaryConditionMinExponent_340) {

    using DecimalSignificand = uint64_t;

    using DecimalExponentType = int;



    DecimalSignificand significand = 12345;

    DecimalExponentType exponent = std::numeric_limits<DecimalExponentType>::min();



    auto result = remove_compact_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(significand, exponent);



    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(DragonboxTest_340, NoTrailingZeros_BoundaryConditionMaxExponent_340) {

    using DecimalSignificand = uint64_t;

    using DecimalExponentType = int;



    DecimalSignificand significand = 12345;

    DecimalExponentType exponent = std::numeric_limits<DecimalExponentType>::max();



    auto result = remove_compact_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(significand, exponent);



    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



}}}}} // namespace YAML::jkj::dragonbox::policy::trailing_zero
