#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "types.cpp" // Assuming the file is included this way for testing



using namespace Exiv2;

using namespace ::testing;



// Test fixture for Rational parsing tests

class RationalParsingTest_1160 : public ::testing::Test {

protected:

    bool ok = false;

};



TEST_F(RationalParsingTest_1160, ParseValidRationalString_1160) {

    std::string validRationalStr = "3/4";

    auto result = parseRational(validRationalStr, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result.numerator(), 3);

    EXPECT_EQ(result.denominator(), 4);

}



TEST_F(RationalParsingTest_1160, ParseValidLongStringAsRational_1160) {

    std::string validLongStr = "5";

    auto result = parseRational(validLongStr, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result.numerator(), 5);

    EXPECT_EQ(result.denominator(), 1);

}



TEST_F(RationalParsingTest_1160, ParseValidFloatStringAsRational_1160) {

    std::string validFloatStr = "2.5";

    auto result = parseRational(validFloatStr, ok);

    EXPECT_TRUE(ok);

    // floatToRationalCast might introduce small errors, so we check within a tolerance

    EXPECT_NEAR(static_cast<double>(result.numerator()) / result.denominator(), 2.5, 0.0001);

}



TEST_F(RationalParsingTest_1160, ParseValidBoolStringAsRational_1160) {

    std::string validBoolStr = "true";

    auto result = parseRational(validBoolStr, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result.numerator(), 1);

    EXPECT_EQ(result.denominator(), 1);



    validBoolStr = "false";

    result = parseRational(validBoolStr, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result.numerator(), 0);

    EXPECT_EQ(result.denominator(), 1);

}



TEST_F(RationalParsingTest_1160, ParseInvalidString_1160) {

    std::string invalidStr = "invalid";

    auto result = parseRational(invalidStr, ok);

    EXPECT_FALSE(ok);

    // Result should be default constructed Rational (0/1)

    EXPECT_EQ(result.numerator(), 0);

    EXPECT_EQ(result.denominator(), 1);

}



TEST_F(RationalParsingTest_1160, ParseEmptyString_1160) {

    std::string emptyStr = "";

    auto result = parseRational(emptyStr, ok);

    EXPECT_FALSE(ok);

    // Result should be default constructed Rational (0/1)

    EXPECT_EQ(result.numerator(), 0);

    EXPECT_EQ(result.denominator(), 1);

}



TEST_F(RationalParsingTest_1160, ParseBoundaryValueForLong_1160) {

    std::string boundaryStr = "2147483647"; // Max int value

    auto result = parseRational(boundaryStr, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result.numerator(), 2147483647);

    EXPECT_EQ(result.denominator(), 1);



    boundaryStr = "-2147483648"; // Min int value

    result = parseRational(boundaryStr, ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result.numerator(), -2147483648);

    EXPECT_EQ(result.denominator(), 1);

}



TEST_F(RationalParsingTest_1160, ParseBoundaryValueForFloat_1160) {

    std::string boundaryStr = "3.402823e+38"; // Max float value

    auto result = parseRational(boundaryStr, ok);

    EXPECT_TRUE(ok);

    // floatToRationalCast might introduce small errors, so we check within a tolerance

    EXPECT_NEAR(static_cast<double>(result.numerator()) / result.denominator(), 3.402823e+38, 1e+35);



    boundaryStr = "-3.402823e+38"; // Min float value (negative)

    result = parseRational(boundaryStr, ok);

    EXPECT_TRUE(ok);

    // floatToRationalCast might introduce small errors, so we check within a tolerance

    EXPECT_NEAR(static_cast<double>(result.numerator()) / result.denominator(), -3.402823e+38, 1e+35);

}
