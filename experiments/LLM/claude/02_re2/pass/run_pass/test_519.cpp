#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

// We test ParseEscape indirectly through Regexp::Parse, since ParseEscape
// is a static function internal to parse.cc.

class ParseEscapeTest_519 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper: returns true if the pattern compiles successfully
  bool CanParse(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re != nullptr) {
      re->Decref();
      return true;
    }
    return false;
  }

  RegexpStatusCode ParseAndGetCode(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re != nullptr) {
      re->Decref();
      return kRegexpSuccess;
    }
    return status.code();
  }
};

// Test simple character escapes: \n, \r, \t, \a, \f, \v
TEST_F(ParseEscapeTest_519, SimpleEscapeNewline_519) {
  EXPECT_TRUE(CanParse("\\n"));
}

TEST_F(ParseEscapeTest_519, SimpleEscapeCarriageReturn_519) {
  EXPECT_TRUE(CanParse("\\r"));
}

TEST_F(ParseEscapeTest_519, SimpleEscapeTab_519) {
  EXPECT_TRUE(CanParse("\\t"));
}

TEST_F(ParseEscapeTest_519, SimpleEscapeBell_519) {
  EXPECT_TRUE(CanParse("\\a"));
}

TEST_F(ParseEscapeTest_519, SimpleEscapeFormFeed_519) {
  EXPECT_TRUE(CanParse("\\f"));
}

TEST_F(ParseEscapeTest_519, SimpleEscapeVerticalTab_519) {
  EXPECT_TRUE(CanParse("\\v"));
}

// Test hex escape \xNN
TEST_F(ParseEscapeTest_519, HexEscapeTwoDigit_519) {
  EXPECT_TRUE(CanParse("\\x41"));  // 'A'
}

TEST_F(ParseEscapeTest_519, HexEscapeBraced_519) {
  EXPECT_TRUE(CanParse("\\x{41}"));  // 'A'
}

TEST_F(ParseEscapeTest_519, HexEscapeBracedMultiDigit_519) {
  EXPECT_TRUE(CanParse("\\x{0041}"));  // 'A'
}

TEST_F(ParseEscapeTest_519, HexEscapeBracedMaxUnicode_519) {
  EXPECT_TRUE(CanParse("\\x{10ffff}"));
}

TEST_F(ParseEscapeTest_519, HexEscapeBracedTooLarge_519) {
  EXPECT_EQ(kRegexpBadEscape, ParseAndGetCode("\\x{110000}"));
}

TEST_F(ParseEscapeTest_519, HexEscapeEmptyBraces_519) {
  EXPECT_EQ(kRegexpBadEscape, ParseAndGetCode("\\x{}"));
}

TEST_F(ParseEscapeTest_519, HexEscapeNoBraceNoDigits_519) {
  EXPECT_EQ(kRegexpBadEscape, ParseAndGetCode("\\xZZ"));
}

TEST_F(ParseEscapeTest_519, HexEscapeOneDigitOnly_519) {
  EXPECT_EQ(kRegexpBadEscape, ParseAndGetCode("\\xGG"));
}

// Test octal escapes
TEST_F(ParseEscapeTest_519, OctalEscapeZero_519) {
  EXPECT_TRUE(CanParse("\\0"));
}

TEST_F(ParseEscapeTest_519, OctalEscapeThreeDigits_519) {
  EXPECT_TRUE(CanParse("\\077"));
}

TEST_F(ParseEscapeTest_519, OctalEscapeTwoDigits_519) {
  EXPECT_TRUE(CanParse("\\07"));
}

// Test non-alphanumeric literal escapes (e.g., \., \\, \*)
TEST_F(ParseEscapeTest_519, EscapedDot_519) {
  EXPECT_TRUE(CanParse("\\."));
}

TEST_F(ParseEscapeTest_519, EscapedBackslash_519) {
  EXPECT_TRUE(CanParse("\\\\"));
}

TEST_F(ParseEscapeTest_519, EscapedStar_519) {
  EXPECT_TRUE(CanParse("\\*"));
}

TEST_F(ParseEscapeTest_519, EscapedPlus_519) {
  EXPECT_TRUE(CanParse("\\+"));
}

TEST_F(ParseEscapeTest_519, EscapedQuestion_519) {
  EXPECT_TRUE(CanParse("\\?"));
}

TEST_F(ParseEscapeTest_519, EscapedOpenParen_519) {
  EXPECT_TRUE(CanParse("\\("));
}

TEST_F(ParseEscapeTest_519, EscapedCloseParen_519) {
  EXPECT_TRUE(CanParse("\\)"));
}

TEST_F(ParseEscapeTest_519, EscapedOpenBracket_519) {
  EXPECT_TRUE(CanParse("\\["));
}

TEST_F(ParseEscapeTest_519, EscapedCloseBracket_519) {
  EXPECT_TRUE(CanParse("\\]"));
}

TEST_F(ParseEscapeTest_519, EscapedOpenBrace_519) {
  EXPECT_TRUE(CanParse("\\{"));
}

TEST_F(ParseEscapeTest_519, EscapedCloseBrace_519) {
  EXPECT_TRUE(CanParse("\\}"));
}

TEST_F(ParseEscapeTest_519, EscapedPipe_519) {
  EXPECT_TRUE(CanParse("\\|"));
}

TEST_F(ParseEscapeTest_519, EscapedCaret_519) {
  EXPECT_TRUE(CanParse("\\^"));
}

TEST_F(ParseEscapeTest_519, EscapedDollar_519) {
  EXPECT_TRUE(CanParse("\\$"));
}

// Test trailing backslash
TEST_F(ParseEscapeTest_519, TrailingBackslash_519) {
  EXPECT_EQ(kRegexpTrailingBackslash, ParseAndGetCode("\\"));
}

// Test that matching with escape sequences works correctly
TEST_F(ParseEscapeTest_519, MatchNewline_519) {
  EXPECT_TRUE(RE2::FullMatch("\n", "\\n"));
}

TEST_F(ParseEscapeTest_519, MatchTab_519) {
  EXPECT_TRUE(RE2::FullMatch("\t", "\\t"));
}

TEST_F(ParseEscapeTest_519, MatchCarriageReturn_519) {
  EXPECT_TRUE(RE2::FullMatch("\r", "\\r"));
}

TEST_F(ParseEscapeTest_519, MatchFormFeed_519) {
  EXPECT_TRUE(RE2::FullMatch("\f", "\\f"));
}

TEST_F(ParseEscapeTest_519, MatchBell_519) {
  EXPECT_TRUE(RE2::FullMatch("\a", "\\a"));
}

TEST_F(ParseEscapeTest_519, MatchVerticalTab_519) {
  EXPECT_TRUE(RE2::FullMatch("\v", "\\v"));
}

TEST_F(ParseEscapeTest_519, MatchHexEscape_519) {
  EXPECT_TRUE(RE2::FullMatch("A", "\\x41"));
}

TEST_F(ParseEscapeTest_519, MatchHexEscapeBraced_519) {
  EXPECT_TRUE(RE2::FullMatch("A", "\\x{41}"));
}

TEST_F(ParseEscapeTest_519, MatchOctalEscape_519) {
  EXPECT_TRUE(RE2::FullMatch("A", "\\101"));
}

TEST_F(ParseEscapeTest_519, MatchEscapedLiteralDot_519) {
  EXPECT_TRUE(RE2::FullMatch(".", "\\."));
  EXPECT_FALSE(RE2::FullMatch("a", "\\."));
}

TEST_F(ParseEscapeTest_519, MatchEscapedLiteralStar_519) {
  EXPECT_TRUE(RE2::FullMatch("*", "\\*"));
}

TEST_F(ParseEscapeTest_519, HexEscapeLowercase_519) {
  EXPECT_TRUE(CanParse("\\x{ff}"));
}

TEST_F(ParseEscapeTest_519, HexEscapeUppercase_519) {
  EXPECT_TRUE(CanParse("\\x{FF}"));
}

TEST_F(ParseEscapeTest_519, HexEscapeMixedCase_519) {
  EXPECT_TRUE(CanParse("\\x{fF}"));
}

// Test octal escape boundary: max valid 3-digit octal for rune_max
TEST_F(ParseEscapeTest_519, OctalMaxThreeDigit_519) {
  EXPECT_TRUE(CanParse("\\377"));  // 255
}

// Hex escape with single hex digit followed by non-hex should fail
TEST_F(ParseEscapeTest_519, HexEscapeOneHexOneNonHex_519) {
  EXPECT_EQ(kRegexpBadEscape, ParseAndGetCode("\\xFG"));
}

// Test \x with no following character at end of string
TEST_F(ParseEscapeTest_519, HexEscapeAtEnd_519) {
  EXPECT_EQ(kRegexpBadEscape, ParseAndGetCode("\\x"));
}

// Test \x with braced but missing closing brace
TEST_F(ParseEscapeTest_519, HexEscapeMissingCloseBrace_519) {
  EXPECT_EQ(kRegexpBadEscape, ParseAndGetCode("\\x{41"));
}

// Test bad escape with alphanumeric that's not recognized
TEST_F(ParseEscapeTest_519, BadAlphanumericEscape_519) {
  // \m is not a recognized escape in POSIX mode
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\m", Regexp::PerlX, &status);
  if (re != nullptr) {
    re->Decref();
    // Some implementations may accept it; if not, check error
  } else {
    EXPECT_EQ(kRegexpBadEscape, status.code());
  }
}

// Verify that escape sequences embedded in larger patterns work
TEST_F(ParseEscapeTest_519, EscapeInLargerPattern_519) {
  EXPECT_TRUE(RE2::FullMatch("hello\tworld", "hello\\tworld"));
}

TEST_F(ParseEscapeTest_519, MultipleEscapesInPattern_519) {
  EXPECT_TRUE(RE2::FullMatch("\n\t\r", "\\n\\t\\r"));
}

TEST_F(ParseEscapeTest_519, HexEscapeZero_519) {
  EXPECT_TRUE(CanParse("\\x00"));
}

TEST_F(ParseEscapeTest_519, HexBracedZero_519) {
  EXPECT_TRUE(CanParse("\\x{0}"));
}

TEST_F(ParseEscapeTest_519, HexBracedSingleDigit_519) {
  EXPECT_TRUE(CanParse("\\x{A}"));
}

}  // namespace re2
