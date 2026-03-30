// File: ./TestProjects/yaml-cpp/test/parsehex_test_165.cpp

#include <gtest/gtest.h>

#include <string>

// Prefer real headers if available in your build.
// These are typical yaml-cpp public headers.
#include "yaml-cpp/mark.h"
#include "yaml-cpp/exceptions.h"

// If there is a public header that declares ParseHex (e.g., yaml-cpp/exp.h),
// you can include it instead of this forward declaration.
// We only rely on the function signature that is visible in the provided code.
namespace YAML {
namespace Exp {
unsigned ParseHex(const std::string& str, const Mark& mark);
}  // namespace Exp
}  // namespace YAML

namespace {

class ParseHexTest_165 : public ::testing::Test {
 protected:
  YAML::Mark mark_;
};

TEST_F(ParseHexTest_165, ParsesSingleDigit_165) {
  EXPECT_EQ(YAML::Exp::ParseHex("0", mark_), 0u);
  EXPECT_EQ(YAML::Exp::ParseHex("9", mark_), 9u);
  EXPECT_EQ(YAML::Exp::ParseHex("a", mark_), 10u);
  EXPECT_EQ(YAML::Exp::ParseHex("f", mark_), 15u);
  EXPECT_EQ(YAML::Exp::ParseHex("A", mark_), 10u);
  EXPECT_EQ(YAML::Exp::ParseHex("F", mark_), 15u);
}

TEST_F(ParseHexTest_165, ParsesMultipleDigitsLowercase_165) {
  EXPECT_EQ(YAML::Exp::ParseHex("10", mark_), 16u);
  EXPECT_EQ(YAML::Exp::ParseHex("1f", mark_), 31u);
  EXPECT_EQ(YAML::Exp::ParseHex("dead", mark_), 0xDEADu);
  EXPECT_EQ(YAML::Exp::ParseHex("beef", mark_), 0xBEEFu);
}

TEST_F(ParseHexTest_165, ParsesMultipleDigitsUppercase_165) {
  EXPECT_EQ(YAML::Exp::ParseHex("1F", mark_), 31u);
  EXPECT_EQ(YAML::Exp::ParseHex("DEAD", mark_), 0xDEADu);
  EXPECT_EQ(YAML::Exp::ParseHex("BEEF", mark_), 0xBEEFu);
}

TEST_F(ParseHexTest_165, ParsesMixedCase_165) {
  EXPECT_EQ(YAML::Exp::ParseHex("dEaD", mark_), 0xDEADu);
  EXPECT_EQ(YAML::Exp::ParseHex("BeEf", mark_), 0xBEEFu);
  EXPECT_EQ(YAML::Exp::ParseHex("0aBc", mark_), 0x0ABCu);
}

TEST_F(ParseHexTest_165, EmptyStringReturnsZero_165) {
  EXPECT_EQ(YAML::Exp::ParseHex("", mark_), 0u);
}

TEST_F(ParseHexTest_165, LeadingZerosPreservedNumerically_165) {
  EXPECT_EQ(YAML::Exp::ParseHex("0000", mark_), 0u);
  EXPECT_EQ(YAML::Exp::ParseHex("0001", mark_), 1u);
  EXPECT_EQ(YAML::Exp::ParseHex("00ff", mark_), 255u);
}

TEST_F(ParseHexTest_165, ThrowsParserExceptionOnInvalidCharacter_165) {
  // A clearly invalid hex character.
  try {
    (void)YAML::Exp::ParseHex("1g", mark_);
    FAIL() << "Expected YAML::ParserException to be thrown";
  } catch (const YAML::ParserException& e) {
    // Validate observable behavior: exception type and message content.
    // ErrorMsg::INVALID_HEX is documented as:
    // "bad character found while scanning hex number"
    const std::string msg = e.what() ? std::string(e.what()) : std::string();
    EXPECT_NE(msg.find("bad character found while scanning hex number"),
              std::string::npos);
  } catch (...) {
    FAIL() << "Expected YAML::ParserException, but caught a different exception";
  }
}

TEST_F(ParseHexTest_165, ThrowsParserExceptionOnNonHexPrefixLike0x_165) {
  // 'x' is not a hex digit here; the function expects only the hex digits.
  EXPECT_THROW((void)YAML::Exp::ParseHex("0x10", mark_), YAML::ParserException);
}

TEST_F(ParseHexTest_165, ThrowsParserExceptionOnWhitespace_165) {
  EXPECT_THROW((void)YAML::Exp::ParseHex(" 1", mark_), YAML::ParserException);
  EXPECT_THROW((void)YAML::Exp::ParseHex("1 ", mark_), YAML::ParserException);
  EXPECT_THROW((void)YAML::Exp::ParseHex("\t1", mark_), YAML::ParserException);
}

}  // namespace