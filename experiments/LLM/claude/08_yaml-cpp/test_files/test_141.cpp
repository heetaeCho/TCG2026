#include <gtest/gtest.h>
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class URIRegExTest_141 : public ::testing::Test {
 protected:
  const RegEx& uri_ = Exp::URI();
};

// Test that URI() returns the same instance each time (static)
TEST_F(URIRegExTest_141, ReturnsSameInstance_141) {
  const RegEx& uri1 = Exp::URI();
  const RegEx& uri2 = Exp::URI();
  EXPECT_EQ(&uri1, &uri2);
}

// Test that basic alphabetic characters match (part of Word())
TEST_F(URIRegExTest_141, MatchesLowercaseLetters_141) {
  EXPECT_TRUE(uri_.Matches('a'));
  EXPECT_TRUE(uri_.Matches('m'));
  EXPECT_TRUE(uri_.Matches('z'));
}

TEST_F(URIRegExTest_141, MatchesUppercaseLetters_141) {
  EXPECT_TRUE(uri_.Matches('A'));
  EXPECT_TRUE(uri_.Matches('M'));
  EXPECT_TRUE(uri_.Matches('Z'));
}

// Test that digits match (part of Word())
TEST_F(URIRegExTest_141, MatchesDigits_141) {
  EXPECT_TRUE(uri_.Matches('0'));
  EXPECT_TRUE(uri_.Matches('5'));
  EXPECT_TRUE(uri_.Matches('9'));
}

// Test that hyphen matches (part of Word())
TEST_F(URIRegExTest_141, MatchesHyphen_141) {
  EXPECT_TRUE(uri_.Matches('-'));
}

// Test special URI characters from the explicit set "#;/?:@&=+$,_.!~*'()[]"
TEST_F(URIRegExTest_141, MatchesHashSign_141) {
  EXPECT_TRUE(uri_.Matches('#'));
}

TEST_F(URIRegExTest_141, MatchesSemicolon_141) {
  EXPECT_TRUE(uri_.Matches(';'));
}

TEST_F(URIRegExTest_141, MatchesSlash_141) {
  EXPECT_TRUE(uri_.Matches('/'));
}

TEST_F(URIRegExTest_141, MatchesQuestionMark_141) {
  EXPECT_TRUE(uri_.Matches('?'));
}

TEST_F(URIRegExTest_141, MatchesColon_141) {
  EXPECT_TRUE(uri_.Matches(':'));
}

TEST_F(URIRegExTest_141, MatchesAtSign_141) {
  EXPECT_TRUE(uri_.Matches('@'));
}

TEST_F(URIRegExTest_141, MatchesAmpersand_141) {
  EXPECT_TRUE(uri_.Matches('&'));
}

TEST_F(URIRegExTest_141, MatchesEquals_141) {
  EXPECT_TRUE(uri_.Matches('='));
}

TEST_F(URIRegExTest_141, MatchesPlus_141) {
  EXPECT_TRUE(uri_.Matches('+'));
}

TEST_F(URIRegExTest_141, MatchesDollar_141) {
  EXPECT_TRUE(uri_.Matches('$'));
}

TEST_F(URIRegExTest_141, MatchesComma_141) {
  EXPECT_TRUE(uri_.Matches(','));
}

TEST_F(URIRegExTest_141, MatchesUnderscore_141) {
  EXPECT_TRUE(uri_.Matches('_'));
}

TEST_F(URIRegExTest_141, MatchesDot_141) {
  EXPECT_TRUE(uri_.Matches('.'));
}

TEST_F(URIRegExTest_141, MatchesExclamationMark_141) {
  EXPECT_TRUE(uri_.Matches('!'));
}

TEST_F(URIRegExTest_141, MatchesTilde_141) {
  EXPECT_TRUE(uri_.Matches('~'));
}

TEST_F(URIRegExTest_141, MatchesAsterisk_141) {
  EXPECT_TRUE(uri_.Matches('*'));
}

TEST_F(URIRegExTest_141, MatchesSingleQuote_141) {
  EXPECT_TRUE(uri_.Matches('\''));
}

TEST_F(URIRegExTest_141, MatchesOpenParen_141) {
  EXPECT_TRUE(uri_.Matches('('));
}

TEST_F(URIRegExTest_141, MatchesCloseParen_141) {
  EXPECT_TRUE(uri_.Matches(')'));
}

TEST_F(URIRegExTest_141, MatchesOpenBracket_141) {
  EXPECT_TRUE(uri_.Matches('['));
}

TEST_F(URIRegExTest_141, MatchesCloseBracket_141) {
  EXPECT_TRUE(uri_.Matches(']'));
}

// Test percent-encoded sequences (%HexHex)
TEST_F(URIRegExTest_141, MatchesPercentEncodedLowerHex_141) {
  std::string s = "%2f";
  int result = uri_.Match(s);
  EXPECT_EQ(result, 3);
}

TEST_F(URIRegExTest_141, MatchesPercentEncodedUpperHex_141) {
  std::string s = "%2F";
  int result = uri_.Match(s);
  EXPECT_EQ(result, 3);
}

TEST_F(URIRegExTest_141, MatchesPercentEncodedZeros_141) {
  std::string s = "%00";
  int result = uri_.Match(s);
  EXPECT_EQ(result, 3);
}

TEST_F(URIRegExTest_141, MatchesPercentEncodedFF_141) {
  std::string s = "%FF";
  int result = uri_.Match(s);
  EXPECT_EQ(result, 3);
}

TEST_F(URIRegExTest_141, MatchesPercentEncodedMixedCase_141) {
  std::string s = "%aB";
  int result = uri_.Match(s);
  EXPECT_EQ(result, 3);
}

// Test that characters NOT in the URI set do NOT match
TEST_F(URIRegExTest_141, DoesNotMatchSpace_141) {
  EXPECT_FALSE(uri_.Matches(' '));
}

TEST_F(URIRegExTest_141, DoesNotMatchTab_141) {
  EXPECT_FALSE(uri_.Matches('\t'));
}

TEST_F(URIRegExTest_141, DoesNotMatchNewline_141) {
  EXPECT_FALSE(uri_.Matches('\n'));
}

TEST_F(URIRegExTest_141, DoesNotMatchCarriageReturn_141) {
  EXPECT_FALSE(uri_.Matches('\r'));
}

TEST_F(URIRegExTest_141, DoesNotMatchBackslash_141) {
  EXPECT_FALSE(uri_.Matches('\\'));
}

TEST_F(URIRegExTest_141, DoesNotMatchCaret_141) {
  EXPECT_FALSE(uri_.Matches('^'));
}

TEST_F(URIRegExTest_141, DoesNotMatchBacktick_141) {
  EXPECT_FALSE(uri_.Matches('`'));
}

TEST_F(URIRegExTest_141, DoesNotMatchOpenBrace_141) {
  EXPECT_FALSE(uri_.Matches('{'));
}

TEST_F(URIRegExTest_141, DoesNotMatchCloseBrace_141) {
  EXPECT_FALSE(uri_.Matches('}'));
}

TEST_F(URIRegExTest_141, DoesNotMatchPipe_141) {
  EXPECT_FALSE(uri_.Matches('|'));
}

TEST_F(URIRegExTest_141, DoesNotMatchDoubleQuote_141) {
  EXPECT_FALSE(uri_.Matches('"'));
}

TEST_F(URIRegExTest_141, DoesNotMatchLessThan_141) {
  EXPECT_FALSE(uri_.Matches('<'));
}

TEST_F(URIRegExTest_141, DoesNotMatchGreaterThan_141) {
  EXPECT_FALSE(uri_.Matches('>'));
}

// Test string matching for typical URI strings
TEST_F(URIRegExTest_141, MatchesSimpleURIString_141) {
  std::string s = "http";
  int result = uri_.Match(s);
  EXPECT_EQ(result, 1);  // Match returns length of first match
}

TEST_F(URIRegExTest_141, MatchesWordString_141) {
  std::string s = "abc123";
  int result = uri_.Match(s);
  EXPECT_GE(result, 1);
}

// Test empty string
TEST_F(URIRegExTest_141, DoesNotMatchEmptyString_141) {
  std::string s = "";
  int result = uri_.Match(s);
  EXPECT_LE(result, 0);
}

// Test percent with non-hex characters should only match if partial
TEST_F(URIRegExTest_141, PercentFollowedByNonHex_141) {
  std::string s = "%GG";
  // '%' alone is not in the simple char set, and %GG is not valid hex encoding
  // The behavior depends on implementation - percent alone shouldn't match as single char
  int result = uri_.Match(s);
  // %GG - 'G' is not a valid hex digit, so the percent-encoded form doesn't match
  // and '%' by itself is not in the URI character set
  EXPECT_LE(result, 0);
}

// Test percent with only one hex digit
TEST_F(URIRegExTest_141, PercentWithOneHexDigit_141) {
  std::string s = "%2";
  int result = uri_.Match(s);
  // Not enough characters for %HH pattern, and % alone not valid
  EXPECT_LE(result, 0);
}

// Test percent alone
TEST_F(URIRegExTest_141, PercentAlone_141) {
  EXPECT_FALSE(uri_.Matches('%'));
}

// Test single character matching via Match (string overload)
TEST_F(URIRegExTest_141, MatchSingleValidChar_141) {
  std::string s = "a";
  int result = uri_.Match(s);
  EXPECT_EQ(result, 1);
}

TEST_F(URIRegExTest_141, MatchSingleSpecialChar_141) {
  std::string s = "#";
  int result = uri_.Match(s);
  EXPECT_EQ(result, 1);
}

TEST_F(URIRegExTest_141, MatchSingleInvalidChar_141) {
  std::string s = " ";
  int result = uri_.Match(s);
  EXPECT_LE(result, 0);
}

// Boundary: null character
TEST_F(URIRegExTest_141, DoesNotMatchNullChar_141) {
  EXPECT_FALSE(uri_.Matches('\0'));
}

// Boundary: DEL character
TEST_F(URIRegExTest_141, DoesNotMatchDEL_141) {
  EXPECT_FALSE(uri_.Matches('\x7F'));
}

// Test all hex digits in percent encoding
TEST_F(URIRegExTest_141, PercentEncodedAllHexDigits_141) {
  for (char c = '0'; c <= '9'; ++c) {
    std::string s = "%";
    s += c;
    s += c;
    int result = uri_.Match(s);
    EXPECT_EQ(result, 3) << "Failed for %" << c << c;
  }
  for (char c = 'a'; c <= 'f'; ++c) {
    std::string s = "%";
    s += c;
    s += c;
    int result = uri_.Match(s);
    EXPECT_EQ(result, 3) << "Failed for %" << c << c;
  }
  for (char c = 'A'; c <= 'F'; ++c) {
    std::string s = "%";
    s += c;
    s += c;
    int result = uri_.Match(s);
    EXPECT_EQ(result, 3) << "Failed for %" << c << c;
  }
}

}  // namespace
}  // namespace YAML
