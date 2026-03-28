#include <gtest/gtest.h>

#include "fptostring.cpp"



namespace YAML {

namespace detail {

namespace fp_formatting {



class FpToStringTest_431 : public ::testing::Test {};



TEST_F(FpToStringTest_431, ZeroValue_431) {

    EXPECT_EQ(FpToString(0.0), "0");

}



TEST_F(FpToStringTest_431, PositiveInfinity_431) {

    EXPECT_EQ(FpToString(std::numeric_limits<double>::infinity()), "inf");

}



TEST_F(FpToStringTest_431, NegativeInfinity_431) {

    EXPECT_EQ(FpToString(-std::numeric_limits<double>::infinity()), "-inf");

}



TEST_F(FpToStringTest_431, NaNValue_431) {

    EXPECT_EQ(FpToString(std::numeric_limits<double>::quiet_NaN()), "nan");

}



TEST_F(FpToStringTest_431, NormalValueDefaultPrecision_431) {

    EXPECT_EQ(FpToString(0.123456789), "0.123457");

}



TEST_F(FpToStringTest_431, NormalValueCustomPrecision_431) {

    EXPECT_EQ(FpToString(0.123456789, 4), "0.1235");

}



TEST_F(FpToStringTest_431, LargeExponentDefaultPrecision_431) {

    EXPECT_EQ(FpToString(1e10), "1e+10");

}



TEST_F(FpToStringTest_431, SmallExponentDefaultPrecision_431) {

    EXPECT_EQ(FpToString(1e-6), "1e-06");

}



TEST_F(FpToStringTest_431, LargeValueWithTrailingZeros_431) {

    EXPECT_EQ(FpToString(123.0), "123");

}



TEST_F(FpToStringTest_431, SmallValueWithLeadingZeros_431) {

    EXPECT_EQ(FpToString(0.000123), "0.000123");

}



}  // namespace fp_formatting

}  // namespace detail

}  // namespace YAML
