#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Helper to parse a regexp and get its string representation
// We test PushLiteral indirectly through Regexp::Parse and ToString/Dump

class PushLiteralTest_489 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper: parse a pattern, return the Dump string
  std::string ParseAndDump(const std::string& pattern, Regexp::ParseFlags flags) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    if (re == nullptr) return "";
    std::string dump = re->Dump();
    re->Decref();
    return dump;
  }

  // Helper: parse a pattern, return ToString
  std::string ParseAndToString(const std::string& pattern, Regexp::ParseFlags flags) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    if (re == nullptr) return "";
    std::string s = re->ToString();
    re->Decref();
    return s;
  }
};

// Test: Normal literal character without any special flags
TEST_F(PushLiteralTest_489, SimpleLiteral_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test: Literal with FoldCase flag on ASCII letter (should create char class)
TEST_F(PushLiteralTest_489, FoldCaseASCIILetter_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::FoldCase, &status);
  ASSERT_NE(re, nullptr);
  // With FoldCase, 'a' should fold to a character class containing 'a' and 'A'
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: FoldCase with uppercase letter
TEST_F(PushLiteralTest_489, FoldCaseUpperCase_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("A", Regexp::FoldCase, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: FoldCase with non-letter character (no folding needed)
TEST_F(PushLiteralTest_489, FoldCaseNonLetter_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("1", Regexp::FoldCase, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), '1');
  re->Decref();
}

// Test: FoldCase with Latin1 flag and ASCII letter
TEST_F(PushLiteralTest_489, FoldCaseLatin1Letter_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::Latin1);
  Regexp* re = Regexp::Parse("b", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: NeverNL flag with newline character - should produce NoMatch
TEST_F(PushLiteralTest_489, NeverNLWithNewline_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::NeverNL | Regexp::Literal);
  Regexp* re = Regexp::Parse("\n", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test: NeverNL flag with non-newline character - should be normal literal
TEST_F(PushLiteralTest_489, NeverNLWithNonNewline_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::NeverNL | Regexp::Literal);
  Regexp* re = Regexp::Parse("x", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

// Test: Multiple consecutive literal characters should concatenate (testing MaybeConcatString path)
TEST_F(PushLiteralTest_489, MultipleLiteralsConcat_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::Literal, &status);
  ASSERT_NE(re, nullptr);
  // Multiple literals should be concatenated into a LiteralString
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 3);
  re->Decref();
}

// Test: Two same consecutive literals (MaybeConcatString should merge)
TEST_F(PushLiteralTest_489, TwoSameLiterals_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("aa", Regexp::Literal, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 2);
  re->Decref();
}

// Test: Single character, no flags at all
TEST_F(PushLiteralTest_489, SingleCharNoFlags_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("z", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'z');
  re->Decref();
}

// Test: Unicode character with FoldCase (non-Latin1)
TEST_F(PushLiteralTest_489, FoldCaseUnicode_489) {
  RegexpStatus status;
  // Greek capital letter Sigma has case folding
  Regexp* re = Regexp::Parse("Σ", Regexp::FoldCase, &status);
  ASSERT_NE(re, nullptr);
  // Should create a char class for case-insensitive matching
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: Unicode character without FoldCase
TEST_F(PushLiteralTest_489, UnicodeWithoutFoldCase_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("Σ", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test: FoldCase with digit (no case folding needed)
TEST_F(PushLiteralTest_489, FoldCaseDigit_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("5", Regexp::FoldCase, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), '5');
  re->Decref();
}

// Test: FoldCase + NeverNL with newline
TEST_F(PushLiteralTest_489, FoldCaseNeverNLNewline_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::NeverNL | Regexp::Literal);
  Regexp* re = Regexp::Parse("\n", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test: Latin1 + FoldCase with 'Z' (boundary of uppercase range)
TEST_F(PushLiteralTest_489, FoldCaseLatin1UpperBound_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::Latin1);
  Regexp* re = Regexp::Parse("Z", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: Latin1 + FoldCase with 'a' (boundary of lowercase range)
TEST_F(PushLiteralTest_489, FoldCaseLatin1LowerBound_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::Latin1);
  Regexp* re = Regexp::Parse("a", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: Latin1 + FoldCase with 'z' (end of lowercase range)
TEST_F(PushLiteralTest_489, FoldCaseLatin1LowerEnd_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::Latin1);
  Regexp* re = Regexp::Parse("z", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: Latin1 + FoldCase with non-alphabetic character (e.g., '@')
TEST_F(PushLiteralTest_489, FoldCaseLatin1NonAlpha_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::Latin1 | Regexp::Literal);
  Regexp* re = Regexp::Parse("@", flags, &status);
  ASSERT_NE(re, nullptr);
  // '@' is not a letter, so no folding; should be literal
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), '@');
  re->Decref();
}

// Test: Empty string parse
TEST_F(PushLiteralTest_489, EmptyString_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test: Long string of literals should all be concatenated
TEST_F(PushLiteralTest_489, LongLiteralString_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcdefghij", Regexp::Literal, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 10);
  re->Decref();
}

// Test: Literal mode with special regex chars should treat them as literals
TEST_F(PushLiteralTest_489, LiteralModeSpecialChars_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a.b", Regexp::Literal, &status);
  ASSERT_NE(re, nullptr);
  // In literal mode, "a.b" should be 3 literal characters
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 3);
  re->Decref();
}

// Test: FoldCase with 'k' - has special Unicode folding (kelvin sign)
TEST_F(PushLiteralTest_489, FoldCaseKelvin_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("k", Regexp::FoldCase, &status);
  ASSERT_NE(re, nullptr);
  // 'k' folds to 'K' and also to the Kelvin sign (U+212A)
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: FoldCase with 's' - has special Unicode folding (long s)
TEST_F(PushLiteralTest_489, FoldCaseLongS_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("s", Regexp::FoldCase, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: Using Parse interface for PushLiteral with LikePerl flags
TEST_F(PushLiteralTest_489, LikePerlLiteral_489) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("x", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // LikePerl doesn't include FoldCase by default, so should be literal
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

// Test: Verify ToString roundtrip for simple literal
TEST_F(PushLiteralTest_489, ToStringRoundtrip_489) {
  std::string result = ParseAndToString("hello", Regexp::Literal);
  EXPECT_EQ(result, "hello");
}

// Test: FoldCase + Latin1 with character just outside A-Z range ('[' = 0x5B)
TEST_F(PushLiteralTest_489, FoldCaseLatin1JustOutsideUpperRange_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::Latin1 | Regexp::Literal);
  Regexp* re = Regexp::Parse("[", flags, &status);
  ASSERT_NE(re, nullptr);
  // '[' is just after 'Z', not a letter, should be literal
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test: Space character with FoldCase (no folding)
TEST_F(PushLiteralTest_489, FoldCaseSpace_489) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::Literal);
  Regexp* re = Regexp::Parse(" ", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), ' ');
  re->Decref();
}

}  // namespace re2
