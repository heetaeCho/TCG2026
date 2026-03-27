#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "fptostring.cpp"



namespace YAML {

    namespace detail {

        namespace fp_formatting {

            std::string FpToString(double v, size_t precision);

        }

    }

}



using ::testing::Return;



TEST(FpToStringTest_433, NormalOperation_433) {

    EXPECT_EQ(YAML::FpToString(123.456, 2), "123.46");

    EXPECT_EQ(YAML::FpToString(-987.654, 3), "-987.654");

}



TEST(FpToStringTest_433, BoundaryConditions_433) {

    EXPECT_EQ(YAML::FpToString(0.0, 0), "0");

    EXPECT_EQ(YAML::FpToString(123.456, 0), "123");

}



TEST(FpToStringTest_433, LargePrecision_433) {

    EXPECT_EQ(YAML::FpToString(123.456789, 10), "123.4567890000");

}



TEST(FpToStringTest_433, VeryLargeNumber_433) {

    EXPECT_EQ(YAML::FpToString(1e10, 2), "10000000000.00");

}



TEST(FpToStringTest_433, VerySmallNumber_433) {

    EXPECT_EQ(YAML::FpToString(1e-10, 5), "0.00000");

}



TEST(FpToStringTest_433, NegativeVeryLargePrecision_433) {

    EXPECT_EQ(YAML::FpToString(123.456, 100), "123.456000000000005684341886080801486968994140625");

}



TEST(FpToStringTest_433, NaNValue_433) {

    EXPECT_EQ(YAML::FpToString(std::numeric_limits<double>::quiet_NaN(), 2), "nan");

}



TEST(FpToStringTest_433, PositiveInfinity_433) {

    EXPECT_EQ(YAML::FpToString(std::numeric_limits<double>::infinity(), 2), "inf");

}



TEST(FpToStringTest_433, NegativeInfinity_433) {

    EXPECT_EQ(YAML::FpToString(-std::numeric_limits<double>::infinity(), 2), "-inf");

}
