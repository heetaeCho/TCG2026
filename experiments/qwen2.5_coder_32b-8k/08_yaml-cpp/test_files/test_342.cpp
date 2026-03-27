#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::trailing_zero;



class DragonboxReportTTest_342 : public ::testing::Test {

protected:

    using DecimalSignificandType = uint64_t;

    using DecimalExponentType = int64_t;

};



TEST_F(DragonboxReportTTest_342, NoTrailingZeros_ReturnsCorrectValues_342) {

    DecimalSignificandType significand = 12345;

    DecimalExponentType exponent = -10;

    auto result = report_t::no_trailing_zeros<YAML::jkj::dragonbox::policy::format_standard>(significand, exponent);

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

    EXPECT_FALSE(result.hasTrailingZeros);

}



TEST_F(DragonboxReportTTest_342, NoTrailingZeros_BoundaryConditionZeroSignificand_342) {

    DecimalSignificandType significand = 0;

    DecimalExponentType exponent = -10;

    auto result = report_t::no_trailing_zeros<YAML::jkj::dragonbox::policy::format_standard>(significand, exponent);

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

    EXPECT_FALSE(result.hasTrailingZeros);

}



TEST_F(DragonboxReportTTest_342, NoTrailingZeros_BoundaryConditionMaxSignificand_342) {

    DecimalSignificandType significand = std::numeric_limits<DecimalSignificandType>::max();

    DecimalExponentType exponent = -10;

    auto result = report_t::no_trailing_zeros<YAML::jkj::dragonbox::policy::format_standard>(significand, exponent);

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

    EXPECT_FALSE(result.hasTrailingZeros);

}



TEST_F(DragonboxReportTTest_342, NoTrailingZeros_BoundaryConditionMinExponent_342) {

    DecimalSignificandType significand = 12345;

    DecimalExponentType exponent = std::numeric_limits<DecimalExponentType>::min();

    auto result = report_t::no_trailing_zeros<YAML::jkj::dragonbox::policy::format_standard>(significand, exponent);

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

    EXPECT_FALSE(result.hasTrailingZeros);

}



TEST_F(DragonboxReportTTest_342, NoTrailingZeros_BoundaryConditionMaxExponent_342) {

    DecimalSignificandType significand = 12345;

    DecimalExponentType exponent = std::numeric_limits<DecimalExponentType>::max();

    auto result = report_t::no_trailing_zeros<YAML::jkj::dragonbox::policy::format_standard>(significand, exponent);

    EXPECT_EQ(result.significand, significand);

    EXPECT_EQ(result.exponent, exponent);

    EXPECT_FALSE(result.hasTrailingZeros);

}
