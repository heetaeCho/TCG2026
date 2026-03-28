#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class HexTest_125 : public ::testing::Test {
 protected:
  const RegEx& hex_ = Exp::Hex();
};

// Normal operation: Hex digits 0-9 should match
TEST_F(HexTest_125, MatchesDigit0_125) {
  EXPECT_TRUE(hex_.Matches('0'));
}

TEST_F(HexTest_125, MatchesDigit5_125) {
  EXPECT_TRUE(hex_.Matches('5'));
}

TEST_F(HexTest_125, MatchesDigit9_125) {
  EXPECT_TRUE(hex_.Matches('9'));
}

// Normal operation: Uppercase hex letters A-F should match
TEST_F(HexTest_125, MatchesUpperA_125) {
  EXPECT_TRUE(hex_.Matches('A'));
}

TEST_F(HexTest_125, MatchesUpperF_125) {
  EXPECT_TRUE(hex_.Matches('F'));
}

TEST_F(HexTest_125, MatchesUpperC_125) {
  EXPECT_TRUE(hex_.Matches('C'));
}

// Normal operation: Lowercase hex letters a-f should match
TEST_F(HexTest_125, MatchesLowerA_125) {
  EXPECT_TRUE(hex_.Matches('a'));
}

TEST_F(HexTest_125, MatchesLowerF_125) {
  EXPECT_TRUE(hex_.Matches('f'));
}

TEST_F(HexTest_125, MatchesLowerD_125) {
  EXPECT_TRUE(hex_.Matches('d'));
}

// Boundary conditions: Characters just outside hex digit range should not match
TEST_F(HexTest_125, DoesNotMatchCharBeforeZero_125) {
  EXPECT_FALSE(hex_.Matches('/'));  // '/' is ASCII 47, just before '0' (48)
}

TEST_F(HexTest_125, DoesNotMatchCharAfterNine_125) {
  EXPECT_FALSE(hex_.Matches(':'));  // ':' is ASCII 58, just after '9' (57)
}

TEST_F(HexTest_125, DoesNotMatchUpperG_125) {
  EXPECT_FALSE(hex_.Matches('G'));
}

TEST_F(HexTest_125, DoesNotMatchLowerG_125) {
  EXPECT_FALSE(hex_.Matches('g'));
}

TEST_F(HexTest_125, DoesNotMatchAtSignBeforeA_125) {
  EXPECT_FALSE(hex_.Matches('@'));  // '@' is ASCII 64, just before 'A' (65)
}

TEST_F(HexTest_125, DoesNotMatchBacktickBeforeLowerA_125) {
  EXPECT_FALSE(hex_.Matches('`'));  // '`' is ASCII 96, just before 'a' (97)
}

// Error/exceptional cases: Non-hex characters
TEST_F(HexTest_125, DoesNotMatchSpace_125) {
  EXPECT_FALSE(hex_.Matches(' '));
}

TEST_F(HexTest_125, DoesNotMatchNewline_125) {
  EXPECT_FALSE(hex_.Matches('\n'));
}

TEST_F(HexTest_125, DoesNotMatchNull_125) {
  EXPECT_FALSE(hex_.Matches('\0'));
}

TEST_F(HexTest_125, DoesNotMatchZ_125) {
  EXPECT_FALSE(hex_.Matches('Z'));
}

TEST_F(HexTest_125, DoesNotMatchLowerZ_125) {
  EXPECT_FALSE(hex_.Matches('z'));
}

TEST_F(HexTest_125, DoesNotMatchExclamation_125) {
  EXPECT_FALSE(hex_.Matches('!'));
}

TEST_F(HexTest_125, DoesNotMatchTilde_125) {
  EXPECT_FALSE(hex_.Matches('~'));
}

// All hex digits should match
TEST_F(HexTest_125, AllDigitsMatch_125) {
  for (char c = '0'; c <= '9'; ++c) {
    EXPECT_TRUE(hex_.Matches(c)) << "Failed for character: " << c;
  }
}

TEST_F(HexTest_125, AllUpperHexLettersMatch_125) {
  for (char c = 'A'; c <= 'F'; ++c) {
    EXPECT_TRUE(hex_.Matches(c)) << "Failed for character: " << c;
  }
}

TEST_F(HexTest_125, AllLowerHexLettersMatch_125) {
  for (char c = 'a'; c <= 'f'; ++c) {
    EXPECT_TRUE(hex_.Matches(c)) << "Failed for character: " << c;
  }
}

// Non-hex uppercase letters should not match
TEST_F(HexTest_125, NonHexUppercaseDoNotMatch_125) {
  for (char c = 'G'; c <= 'Z'; ++c) {
    EXPECT_FALSE(hex_.Matches(c)) << "Should not match character: " << c;
  }
}

// Non-hex lowercase letters should not match
TEST_F(HexTest_125, NonHexLowercaseDoNotMatch_125) {
  for (char c = 'g'; c <= 'z'; ++c) {
    EXPECT_FALSE(hex_.Matches(c)) << "Should not match character: " << c;
  }
}

// Test that Hex() returns the same reference (singleton pattern)
TEST_F(HexTest_125, ReturnsSameReference_125) {
  const RegEx& hex1 = Exp::Hex();
  const RegEx& hex2 = Exp::Hex();
  EXPECT_EQ(&hex1, &hex2);
}

// Test string-based Match for single hex character strings
TEST_F(HexTest_125, MatchSingleHexCharString_125) {
  EXPECT_TRUE(hex_.Matches(std::string("A")));
}

TEST_F(HexTest_125, MatchSingleDigitString_125) {
  EXPECT_TRUE(hex_.Matches(std::string("0")));
}

TEST_F(HexTest_125, MatchSingleLowerHexString_125) {
  EXPECT_TRUE(hex_.Matches(std::string("f")));
}

TEST_F(HexTest_125, DoesNotMatchNonHexString_125) {
  EXPECT_FALSE(hex_.Matches(std::string("G")));
}

// Test Match function returning length
TEST_F(HexTest_125, MatchReturnsOneForHexDigit_125) {
  EXPECT_EQ(1, hex_.Match(std::string("A")));
}

TEST_F(HexTest_125, MatchReturnsOneForDigit_125) {
  EXPECT_EQ(1, hex_.Match(std::string("5")));
}

TEST_F(HexTest_125, MatchReturnsNegativeForNonHex_125) {
  EXPECT_EQ(-1, hex_.Match(std::string("G")));
}

TEST_F(HexTest_125, MatchReturnsNegativeForEmptyString_125) {
  EXPECT_EQ(-1, hex_.Match(std::string("")));
}

// Test that Match on a longer string only matches the first character
TEST_F(HexTest_125, MatchOnlyFirstCharOfLongerString_125) {
  int result = hex_.Match(std::string("AB"));
  EXPECT_EQ(1, result);
}

}  // namespace
}  // namespace YAML
