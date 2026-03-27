#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_tostring.hpp"



using namespace Catch;



TEST(StringMakerTest_82, ConvertSignedCharToString_82) {

    signed char input = 100;

    std::string result = StringMaker<signed char>::convert(input);

    EXPECT_EQ(result, "100");

}



TEST(StringMakerTest_82, ConvertNegativeSignedCharToString_82) {

    signed char input = -50;

    std::string result = StringMaker<signed char>::convert(input);

    EXPECT_EQ(result, "-50");

}



TEST(StringMakerTest_82, ConvertZeroSignedCharToString_82) {

    signed char input = 0;

    std::string result = StringMaker<signed char>::convert(input);

    EXPECT_EQ(result, "0");

}



TEST(StringMakerTest_82, ConvertMaxSignedCharToString_82) {

    signed char input = SCHAR_MAX;

    std::string result = StringMaker<signed char>::convert(input);

    EXPECT_EQ(result, std::to_string(SCHAR_MAX));

}



TEST(StringMakerTest_82, ConvertMinSignedCharToString_82) {

    signed char input = SCHAR_MIN;

    std::string result = StringMaker<signed char>::convert(input);

    EXPECT_EQ(result, std::to_string(SCHAR_MIN));

}



TEST(StringMakerTest_82, ConvertSignedCharArrayToString_82) {

    signed char input[] = "Hello";

    std::string result = convert(input);

    EXPECT_EQ(result, "Hello");

}
