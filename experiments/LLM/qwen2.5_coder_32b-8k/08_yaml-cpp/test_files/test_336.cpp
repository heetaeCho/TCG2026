#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::trailing_zero;



TEST_F(ignore_t_Test_336, no_trailing_zeros_ReturnsCorrectValues_336) {

    using DecimalSignificand = uint64_t;

    using DecimalExponentType = int32_t;



    DecimalSignificand significand = 12345;

    DecimalExponentType exponent = -6789;



    auto result = ignore_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(significand, exponent);



    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

}



TEST_F(ignore_t_Test_336, no_trailing_zeros_BoundaryConditions_336) {

    using DecimalSignificand = uint64_t;

    using DecimalExponentType = int32_t;



    // Test with zero significand

    auto result = ignore_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(0, 0);

    EXPECT_EQ(result.significand, 0);

    EXPECT_EQ(result.exponent, 0);



    // Test with max and min exponents

    result = ignore_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(1, std::numeric_limits<int32_t>::max());

    EXPECT_EQ(result.significand, 1);

    EXPECT_EQ(result.exponent, std::numeric_limits<int32_t>::max());



    result = ignore_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(1, std::numeric_limits<int32_t>::min());

    EXPECT_EQ(result.significand, 1);

    EXPECT_EQ(result.exponent, std::numeric_limits<int32_t>::min());



    // Test with max significand

    result = ignore_t::no_trailing_zeros<Format, DecimalSignificand, DecimalExponentType>(std::numeric_limits<uint64_t>::max(), 0);

    EXPECT_EQ(result.significand, std::numeric_limits<uint64_t>::max());

    EXPECT_EQ(result.exponent, 0);

}
