#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"



using namespace Catch;



// Test Suite for StringMaker<double> convert function

class StringMakerDoubleTest_279 : public ::testing::Test {

protected:

    double precision = 6; // Assuming the default precision is set to 6

};



TEST_F(StringMakerDoubleTest_279, ConvertNormalValue_279) {

    double value = 123.456789;

    std::string result = StringMaker<double>::convert(value);

    EXPECT_EQ(result, "123.456789");

}



TEST_F(StringMakerDoubleTest_279, ConvertNegativeValue_279) {

    double value = -987.654321;

    std::string result = StringMaker<double>::convert(value);

    EXPECT_EQ(result, "-987.654321");

}



TEST_F(StringMakerDoubleTest_279, ConvertZeroValue_279) {

    double value = 0.0;

    std::string result = StringMaker<double>::convert(value);

    EXPECT_EQ(result, "0.000000");

}



TEST_F(StringMakerDoubleTest_279, ConvertLargeValue_279) {

    double value = 1.23456789e10;

    std::string result = StringMaker<double>::convert(value);

    EXPECT_EQ(result, "12345678900");

}



TEST_F(StringMakerDoubleTest_279, ConvertSmallValue_279) {

    double value = 1.23456789e-10;

    std::string result = StringMaker<double>::convert(value);

    EXPECT_EQ(result, "0.000000");

}



TEST_F(StringMakerDoubleTest_279, ConvertBoundaryMaxValue_279) {

    double value = DBL_MAX;

    std::string result = StringMaker<double>::convert(value);

    // The exact string representation might vary based on the platform and compiler

    EXPECT_TRUE(result.find("1.797693e+308") != std::string::npos || result.find("1.7976931348623157e+308") != std::string::npos);

}



TEST_F(StringMakerDoubleTest_279, ConvertBoundaryMinValue_279) {

    double value = DBL_MIN;

    std::string result = StringMaker<double>::convert(value);

    // The exact string representation might vary based on the platform and compiler

    EXPECT_TRUE(result.find("2.225074e-308") != std::string::npos || result.find("2.2250738585072014e-308") != std::string::npos);

}



TEST_F(StringMakerDoubleTest_279, ConvertNaNValue_279) {

    double value = std::numeric_limits<double>::quiet_NaN();

    std::string result = StringMaker<double>::convert(value);

    EXPECT_TRUE(result.find("nan") != std::string::npos || result.find("-nan") != std::string::npos);

}



TEST_F(StringMakerDoubleTest_279, ConvertInfinityValue_279) {

    double value = std::numeric_limits<double>::infinity();

    std::string result = StringMaker<double>::convert(value);

    EXPECT_EQ(result, "inf");

}



TEST_F(StringMakerDoubleTest_279, ConvertNegativeInfinityValue_279) {

    double value = -std::numeric_limits<double>::infinity();

    std::string result = StringMaker<double>::convert(value);

    EXPECT_EQ(result, "-inf");

}
