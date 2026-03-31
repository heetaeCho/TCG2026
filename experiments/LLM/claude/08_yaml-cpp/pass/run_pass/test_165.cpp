#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/mark.h"
#include "yaml-cpp/exceptions.h"

// Forward declare the function under test
namespace YAML {
namespace Exp {
unsigned ParseHex(const std::string& str, const Mark& mark);
}
}

class ParseHexTest_165 : public ::testing::Test {
protected:
    YAML::Mark mark;
};

// Normal operation tests

TEST_F(ParseHexTest_165, SingleDigitZero_165) {
    unsigned result = YAML::Exp::ParseHex("0", mark);
    EXPECT_EQ(0u, result);
}

TEST_F(ParseHexTest_165, SingleDigitNonZero_165) {
    unsigned result = YAML::Exp::ParseHex("9", mark);
    EXPECT_EQ(9u, result);
}

TEST_F(ParseHexTest_165, SingleLowercaseHexDigit_165) {
    unsigned result = YAML::Exp::ParseHex("a", mark);
    EXPECT_EQ(10u, result);
}

TEST_F(ParseHexTest_165, SingleUppercaseHexDigit_165) {
    unsigned result = YAML::Exp::ParseHex("A", mark);
    EXPECT_EQ(10u, result);
}

TEST_F(ParseHexTest_165, LowercaseF_165) {
    unsigned result = YAML::Exp::ParseHex("f", mark);
    EXPECT_EQ(15u, result);
}

TEST_F(ParseHexTest_165, UppercaseF_165) {
    unsigned result = YAML::Exp::ParseHex("F", mark);
    EXPECT_EQ(15u, result);
}

TEST_F(ParseHexTest_165, MultiDigitLowercase_165) {
    unsigned result = YAML::Exp::ParseHex("ff", mark);
    EXPECT_EQ(255u, result);
}

TEST_F(ParseHexTest_165, MultiDigitUppercase_165) {
    unsigned result = YAML::Exp::ParseHex("FF", mark);
    EXPECT_EQ(255u, result);
}

TEST_F(ParseHexTest_165, MixedCaseHex_165) {
    unsigned result = YAML::Exp::ParseHex("aB", mark);
    EXPECT_EQ(0xABu, result);
}

TEST_F(ParseHexTest_165, HexValue1234_165) {
    unsigned result = YAML::Exp::ParseHex("1234", mark);
    EXPECT_EQ(0x1234u, result);
}

TEST_F(ParseHexTest_165, HexValueABCDEF_165) {
    unsigned result = YAML::Exp::ParseHex("abcdef", mark);
    EXPECT_EQ(0xABCDEFu, result);
}

TEST_F(ParseHexTest_165, HexValueMixedDigitsAndLetters_165) {
    unsigned result = YAML::Exp::ParseHex("1a2B3c", mark);
    EXPECT_EQ(0x1A2B3Cu, result);
}

TEST_F(ParseHexTest_165, EightDigitHex_165) {
    unsigned result = YAML::Exp::ParseHex("DEADBEEF", mark);
    EXPECT_EQ(0xDEADBEEFu, result);
}

TEST_F(ParseHexTest_165, AllZeros_165) {
    unsigned result = YAML::Exp::ParseHex("0000", mark);
    EXPECT_EQ(0u, result);
}

TEST_F(ParseHexTest_165, LeadingZeros_165) {
    unsigned result = YAML::Exp::ParseHex("001F", mark);
    EXPECT_EQ(0x1Fu, result);
}

TEST_F(ParseHexTest_165, AllDecimalDigits_165) {
    unsigned result = YAML::Exp::ParseHex("1234567890", mark);
    EXPECT_EQ(0x1234567890u & 0xFFFFFFFFu, result);
}

TEST_F(ParseHexTest_165, TwoDigitHex10_165) {
    unsigned result = YAML::Exp::ParseHex("10", mark);
    EXPECT_EQ(16u, result);
}

// Boundary condition tests

TEST_F(ParseHexTest_165, EmptyString_165) {
    unsigned result = YAML::Exp::ParseHex("", mark);
    EXPECT_EQ(0u, result);
}

TEST_F(ParseHexTest_165, SingleCharacterBoundaryA_165) {
    EXPECT_EQ(10u, YAML::Exp::ParseHex("a", mark));
}

TEST_F(ParseHexTest_165, SingleCharacterBoundaryF_165) {
    EXPECT_EQ(15u, YAML::Exp::ParseHex("f", mark));
}

TEST_F(ParseHexTest_165, SingleCharacterBoundary0_165) {
    EXPECT_EQ(0u, YAML::Exp::ParseHex("0", mark));
}

TEST_F(ParseHexTest_165, SingleCharacterBoundary9_165) {
    EXPECT_EQ(9u, YAML::Exp::ParseHex("9", mark));
}

// Error / Exception tests

TEST_F(ParseHexTest_165, InvalidCharacterG_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("G", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterLowercaseG_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("g", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterSpace_165) {
    EXPECT_THROW(YAML::Exp::ParseHex(" ", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterMinus_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("-1", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterX_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("0x1A", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterAtEnd_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("1Z", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterAtBeginning_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("Z1", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterInMiddle_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("1G2", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterPeriod_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("1.2", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterNewline_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("\n", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterTab_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("\t", mark), YAML::ParserException);
}

TEST_F(ParseHexTest_165, InvalidCharacterExclamation_165) {
    EXPECT_THROW(YAML::Exp::ParseHex("!", mark), YAML::ParserException);
}

// Verify specific hex values

TEST_F(ParseHexTest_165, HexValue00FF_165) {
    EXPECT_EQ(0x00FFu, YAML::Exp::ParseHex("00FF", mark));
}

TEST_F(ParseHexTest_165, HexValueFFFF_165) {
    EXPECT_EQ(0xFFFFu, YAML::Exp::ParseHex("FFFF", mark));
}

TEST_F(ParseHexTest_165, HexValue7FFF_165) {
    EXPECT_EQ(0x7FFFu, YAML::Exp::ParseHex("7FFF", mark));
}

TEST_F(ParseHexTest_165, HexValueLowercaseDeadbeef_165) {
    unsigned result = YAML::Exp::ParseHex("deadbeef", mark);
    EXPECT_EQ(0xDEADBEEFu, result);
}

TEST_F(ParseHexTest_165, ConsistentCaseInsensitivity_165) {
    unsigned lower = YAML::Exp::ParseHex("abcdef", mark);
    unsigned upper = YAML::Exp::ParseHex("ABCDEF", mark);
    unsigned mixed = YAML::Exp::ParseHex("AbCdEf", mark);
    EXPECT_EQ(lower, upper);
    EXPECT_EQ(lower, mixed);
}
