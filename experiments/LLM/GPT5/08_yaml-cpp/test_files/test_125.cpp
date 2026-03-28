// TEST_ID: 125
//
// Unit tests for YAML::Exp::Hex()
// File under test: ./TestProjects/yaml-cpp/src/exp.h
//
// Constraints respected:
// - Treat implementation as black box (test observable behavior only via public RegEx API).
// - No access to internal/private state.
// - No re-implementation of internal logic beyond what is observable.
// - Includes normal, boundary, and error/exception-like observable cases.
//
// Note: These tests assume the project exposes YAML::Exp::Hex() and YAML::RegEx::Matches/Match.

#include <gtest/gtest.h>

#include <string>

#include "exp.h"        // YAML::Exp::Hex()
#include "regex_yaml.h" // YAML::RegEx

namespace {

using YAML::RegEx;

class HexExpTest_125 : public ::testing::Test {
protected:
  const RegEx& hex_ = YAML::Exp::Hex();
};

TEST_F(HexExpTest_125, MatchesAllDecimalDigits_125) {
  for (char ch = '0'; ch <= '9'; ++ch) {
    EXPECT_TRUE(hex_.Matches(ch)) << "Expected Matches for digit: " << ch;
  }
}

TEST_F(HexExpTest_125, MatchesUppercaseAF_125) {
  for (char ch = 'A'; ch <= 'F'; ++ch) {
    EXPECT_TRUE(hex_.Matches(ch)) << "Expected Matches for uppercase: " << ch;
  }
}

TEST_F(HexExpTest_125, MatchesLowercaseAF_125) {
  for (char ch = 'a'; ch <= 'f'; ++ch) {
    EXPECT_TRUE(hex_.Matches(ch)) << "Expected Matches for lowercase: " << ch;
  }
}

TEST_F(HexExpTest_125, RejectsJustOutsideUppercaseRange_125) {
  EXPECT_FALSE(hex_.Matches('@')); // before 'A'
  EXPECT_FALSE(hex_.Matches('G')); // after  'F'
}

TEST_F(HexExpTest_125, RejectsJustOutsideLowercaseRange_125) {
  EXPECT_FALSE(hex_.Matches('`')); // before 'a'
  EXPECT_FALSE(hex_.Matches('g')); // after  'f'
}

TEST_F(HexExpTest_125, RejectsNonHexLettersAndPunctuation_125) {
  const std::string non_hex = "xyzXYZ-_+?/,:;[]{}()";
  for (char ch : non_hex) {
    EXPECT_FALSE(hex_.Matches(ch)) << "Expected non-hex to be rejected: " << ch;
  }
}

TEST_F(HexExpTest_125, StringMatchesSingleHexCharacter_125) {
  EXPECT_TRUE(hex_.Matches(std::string("0")));
  EXPECT_TRUE(hex_.Matches(std::string("9")));
  EXPECT_TRUE(hex_.Matches(std::string("A")));
  EXPECT_TRUE(hex_.Matches(std::string("F")));
  EXPECT_TRUE(hex_.Matches(std::string("a")));
  EXPECT_TRUE(hex_.Matches(std::string("f")));
}

TEST_F(HexExpTest_125, StringRejectsSingleNonHexCharacter_125) {
  EXPECT_FALSE(hex_.Matches(std::string("G")));
  EXPECT_FALSE(hex_.Matches(std::string("g")));
  EXPECT_FALSE(hex_.Matches(std::string("z")));
  EXPECT_FALSE(hex_.Matches(std::string("!")));
  EXPECT_FALSE(hex_.Matches(std::string(" ")));
}

TEST_F(HexExpTest_125, StringBoundaryCasesEmptyAndMultiChar_125) {
  // Observable boundary/error-like behaviors through the interface:
  // - Empty should not represent a single hex character.
  // - Multi-character should not represent a single hex character.
  EXPECT_FALSE(hex_.Matches(std::string("")));
  EXPECT_FALSE(hex_.Matches(std::string("0F")));
  EXPECT_FALSE(hex_.Matches(std::string("af")));
  EXPECT_FALSE(hex_.Matches(std::string("F0")));
}

TEST_F(HexExpTest_125, MatchReturnsNonNegativeForValidSingleChar_125) {
  // We do not assume exact return value semantics beyond "success is observable".
  // Here we only check it indicates a successful match somehow (commonly >0).
  // If this project uses 1 for single-char match, these still pass.
  EXPECT_GT(hex_.Match(std::string("0")), 0);
  EXPECT_GT(hex_.Match(std::string("A")), 0);
  EXPECT_GT(hex_.Match(std::string("f")), 0);
}

TEST_F(HexExpTest_125, MatchReturnsZeroOrNegativeForInvalidOrEmpty_125) {
  // We avoid assuming whether failure is 0 or -1; accept either as "not successful".
  const int empty = hex_.Match(std::string(""));
  EXPECT_LE(empty, 0);

  const int bad1 = hex_.Match(std::string("G"));
  EXPECT_LE(bad1, 0);

  const int bad2 = hex_.Match(std::string("0F")); // multi-char, not a single token
  EXPECT_LE(bad2, 0);
}

TEST_F(HexExpTest_125, ReturnsSameInstanceAcrossCalls_125) {
  // The interface returns const RegEx&; observable behavior: repeated calls refer to same object.
  const RegEx* p1 = &YAML::Exp::Hex();
  const RegEx* p2 = &YAML::Exp::Hex();
  EXPECT_EQ(p1, p2);
}

}  // namespace
