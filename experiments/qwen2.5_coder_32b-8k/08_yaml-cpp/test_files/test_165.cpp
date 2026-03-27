#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/exp.cpp"

#include "./yaml-cpp/mark.h"

#include "./yaml-cpp/exceptions.h"



using namespace YAML;

using namespace Exp;



TEST(ParseHexTest_165, NormalOperation_165) {

    Mark mark;

    EXPECT_EQ(ParseHex("1a", mark), 26);

}



TEST(ParseHexTest_165, UpperCaseLetters_165) {

    Mark mark;

    EXPECT_EQ(ParseHex("AB", mark), 171);

}



TEST(ParseHexTest_165, MixedCaseLetters_165) {

    Mark mark;

    EXPECT_EQ(ParseHex("aBc", mark), 2748);

}



TEST(ParseHexTest_165, SingleDigit_165) {

    Mark mark;

    EXPECT_EQ(ParseHex("f", mark), 15);

}



TEST(ParseHexTest_165, ZeroValue_165) {

    Mark mark;

    EXPECT_EQ(ParseHex("0", mark), 0);

}



TEST(ParseHexTest_165, LongHexString_165) {

    Mark mark;

    EXPECT_EQ(ParseHex("123456789abcdef", mark), 81985529216486895);

}



TEST(ParseHexTest_165, InvalidCharacter_165) {

    Mark mark;

    EXPECT_THROW(ParseHex("1g", mark), ParserException);

}



TEST(ParseHexTest_165, EmptyString_165) {

    Mark mark;

    EXPECT_THROW(ParseHex("", mark), ParserException);

}



TEST(ParseHexTest_165, SpecialCharacters_165) {

    Mark mark;

    EXPECT_THROW(ParseHex("!@#", mark), ParserException);

}
