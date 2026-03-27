#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace log {



using namespace testing;



TEST(floor_log10_pow2Test_320, NormalOperation_PositiveExponent_320) {

    EXPECT_EQ(floor_log10_pow2(1), 0);

    EXPECT_EQ(floor_log10_pow2(5), 1);

    EXPECT_EQ(floor_log10_pow2(10), 3);

    EXPECT_EQ(floor_log10_pow2(1024), 9);

}



TEST(floor_log10_pow2Test_320, NormalOperation_NegativeExponent_320) {

    EXPECT_EQ(floor_log10_pow2(-1), -1);

    EXPECT_EQ(floor_log10_pow2(-5), -2);

    EXPECT_EQ(floor_log10_pow2(-10), -4);

    EXPECT_EQ(floor_log10_pow2(-1024), -10);

}



TEST(floor_log10_pow2Test_320, BoundaryCondition_MinExponent_320) {

    EXPECT_EQ(floor_log10_pow2(min_exponent), -788); // log10(2^-2620) is approximately -788.08

}



TEST(floor_log10_pow2Test_320, BoundaryCondition_MaxExponent_320) {

    EXPECT_EQ(floor_log10_pow2(max_exponent), 788); // log10(2^2620) is approximately 788.08

}



TEST(floor_log10_pow2Test_320, BoundaryCondition_ZeroExponent_320) {

    EXPECT_EQ(floor_log10_pow2(0), 0);

}



} } } } }
