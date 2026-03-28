#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Test fixture for ParsePerlFlags
class ParsePerlFlagsTest_533 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to create a ParseState with PerlX enabled
  std::unique_ptr<Regexp::ParseState> MakeState(
      Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
          Regexp::PerlX | Regexp::OneLine)) {
    absl::string_view whole("(?:test)");
    return std::make_unique<Regexp::ParseState>(flags, whole, &status_);
  }

  RegexpStatus status_;
};

// Test that calling ParsePerlFlags without PerlX flag set returns false
// with kRegexpInternalError
TEST_F(ParsePerlFlagsTest_533, NoPerlXFlagReturnsInternalError_533) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "(?:test)", &status_);
  absl::string_view s("(?:test)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpInternalError);
}

// Test that string too short (less than 2 chars) returns false
TEST_F(ParsePerlFlagsTest_533, TooShortStringReturnsInternalError_533) {
  Regexp::ParseState ps(Regexp::PerlX, "(", &status_);
  absl::string_view s("(");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpInternalError);
}

// Test that string not starting with '(' returns false
TEST_F(ParsePerlFlagsTest_533, NotStartingWithParenReturnsInternalError_533) {
  Regexp::ParseState ps(Regexp::PerlX, "x?i)", &status_);
  absl::string_view s("x?i)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpInternalError);
}

// Test that string not having '?' as second char returns false
TEST_F(ParsePerlFlagsTest_533, NoQuestionMarkReturnsInternalError_533) {
  Regexp::ParseState ps(Regexp::PerlX, "(xi)", &status_);
  absl::string_view s("(xi)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpInternalError);
}

// Test positive lookahead (?= returns kRegexpBadPerlOp
TEST_F(ParsePerlFlagsTest_533, PositiveLookaheadReturnsBadPerlOp_533) {
  Regexp::ParseState ps(Regexp::PerlX, "(?=abc)", &status_);
  absl::string_view s("(?=abc)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadPerlOp);
}

// Test negative lookahead (?! returns kRegexpBadPerlOp
TEST_F(ParsePerlFlagsTest_533, NegativeLookaheadReturnsBadPerlOp_533) {
  Regexp::ParseState ps(Regexp::PerlX, "(?!abc)", &status_);
  absl::string_view s("(?!abc)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadPerlOp);
}

// Test positive lookbehind (?<= returns kRegexpBadPerlOp
TEST_F(ParsePerlFlagsTest_533, PositiveLookbehindReturnsBadPerlOp_533) {
  Regexp::ParseState ps(Regexp::PerlX, "(?<=abc)", &status_);
  absl::string_view s("(?<=abc)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadPerlOp);
}

// Test negative lookbehind (?<! returns kRegexpBadPerlOp
TEST_F(ParsePerlFlagsTest_533, NegativeLookbehindReturnsBadPerlOp_533) {
  Regexp::ParseState ps(Regexp::PerlX, "(?<!abc)", &status_);
  absl::string_view s("(?<!abc)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadPerlOp);
}

// Test named capture (?P<name> with valid name
TEST_F(ParsePerlFlagsTest_533, NamedCapturePStyle_533) {
  absl::string_view whole("(?P<name>abc)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?P<name>abc)");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  // After parsing, s should have the prefix removed up to and including '>'
  EXPECT_EQ(s, "abc)");
}

// Test named capture (?<name> style with valid name
TEST_F(ParsePerlFlagsTest_533, NamedCaptureAngleBracketStyle_533) {
  absl::string_view whole("(?<name>abc)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?<name>abc)");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc)");
}

// Test named capture with missing closing '>'
TEST_F(ParsePerlFlagsTest_533, NamedCaptureMissingClosingAngleBracket_533) {
  absl::string_view whole("(?P<name");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?P<name");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadNamedCapture);
}

// Test named capture with invalid name (e.g., starts with digit)
TEST_F(ParsePerlFlagsTest_533, NamedCaptureInvalidName_533) {
  absl::string_view whole("(?P<1name>abc)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?P<1name>abc)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadNamedCapture);
}

// Test named capture with empty name
TEST_F(ParsePerlFlagsTest_533, NamedCaptureEmptyName_533) {
  absl::string_view whole("(?P<>abc)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?P<>abc)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadNamedCapture);
}

// Test flag 'i' sets FoldCase
TEST_F(ParsePerlFlagsTest_533, FlagI_SetsFoldCase_533) {
  absl::string_view whole("(?i)abc");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?i)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_TRUE(ps.flags() & Regexp::FoldCase);
}

// Test flag 's' sets DotNL
TEST_F(ParsePerlFlagsTest_533, FlagS_SetsDotNL_533) {
  absl::string_view whole("(?s)abc");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?s)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_TRUE(ps.flags() & Regexp::DotNL);
}

// Test flag 'm' clears OneLine
TEST_F(ParsePerlFlagsTest_533, FlagM_ClearsOneLine_533) {
  absl::string_view whole("(?m)abc");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::OneLine);
  Regexp::ParseState ps(flags, whole, &status_);
  absl::string_view s("(?m)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_FALSE(ps.flags() & Regexp::OneLine);
}

// Test flag 'U' sets NonGreedy
TEST_F(ParsePerlFlagsTest_533, FlagU_SetsNonGreedy_533) {
  absl::string_view whole("(?U)abc");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?U)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_TRUE(ps.flags() & Regexp::NonGreedy);
}

// Test negated flag '-i' clears FoldCase
TEST_F(ParsePerlFlagsTest_533, NegatedFlagI_ClearsFoldCase_533) {
  absl::string_view whole("(?-i)abc");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::FoldCase);
  Regexp::ParseState ps(flags, whole, &status_);
  absl::string_view s("(?-i)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_FALSE(ps.flags() & Regexp::FoldCase);
}

// Test negated flag '-s' clears DotNL
TEST_F(ParsePerlFlagsTest_533, NegatedFlagS_ClearsDotNL_533) {
  absl::string_view whole("(?-s)abc");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::DotNL);
  Regexp::ParseState ps(flags, whole, &status_);
  absl::string_view s("(?-s)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_FALSE(ps.flags() & Regexp::DotNL);
}

// Test negated flag '-m' sets OneLine
TEST_F(ParsePerlFlagsTest_533, NegatedFlagM_SetsOneLine_533) {
  absl::string_view whole("(?-m)abc");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?-m)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_TRUE(ps.flags() & Regexp::OneLine);
}

// Test negated flag '-U' clears NonGreedy
TEST_F(ParsePerlFlagsTest_533, NegatedFlagU_ClearsNonGreedy_533) {
  absl::string_view whole("(?-U)abc");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::NonGreedy);
  Regexp::ParseState ps(flags, whole, &status_);
  absl::string_view s("(?-U)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_FALSE(ps.flags() & Regexp::NonGreedy);
}

// Test multiple flags (?ism)
TEST_F(ParsePerlFlagsTest_533, MultipleFlags_533) {
  absl::string_view whole("(?is)abc");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?is)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_TRUE(ps.flags() & Regexp::FoldCase);
  EXPECT_TRUE(ps.flags() & Regexp::DotNL);
}

// Test non-capturing group (?:
TEST_F(ParsePerlFlagsTest_533, NonCapturingGroup_533) {
  absl::string_view whole("(?:abc)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?:abc)");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc)");
}

// Test flags with non-capturing group (?i:
TEST_F(ParsePerlFlagsTest_533, FlagsWithNonCapturingGroup_533) {
  absl::string_view whole("(?i:abc)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?i:abc)");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc)");
  EXPECT_TRUE(ps.flags() & Regexp::FoldCase);
}

// Test negated flags with non-capturing group (?-i:
TEST_F(ParsePerlFlagsTest_533, NegatedFlagsWithNonCapturingGroup_533) {
  absl::string_view whole("(?-i:abc)");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::FoldCase);
  Regexp::ParseState ps(flags, whole, &status_);
  absl::string_view s("(?-i:abc)");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc)");
  EXPECT_FALSE(ps.flags() & Regexp::FoldCase);
}

// Test bad perl op with unknown flag character
TEST_F(ParsePerlFlagsTest_533, UnknownFlagCharReturnsBadPerlOp_533) {
  absl::string_view whole("(?z)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?z)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadPerlOp);
}

// Test double negation (?--i) is invalid
TEST_F(ParsePerlFlagsTest_533, DoubleNegationReturnsBadPerlOp_533) {
  absl::string_view whole("(?--i)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?--i)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadPerlOp);
}

// Test negation with no flags (?-) is invalid
TEST_F(ParsePerlFlagsTest_533, NegationWithNoFlagsReturnsBadPerlOp_533) {
  absl::string_view whole("(?-)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?-)");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadPerlOp);
}

// Test empty flags with just close paren (?), which means negated=false, sawflags=false
// but since it hits ')' case with no negation and no flags, it should succeed
// (negated is false, so the check `negated && !sawflags` won't trigger)
TEST_F(ParsePerlFlagsTest_533, EmptyFlagsWithCloseParen_533) {
  absl::string_view whole("(?)abc");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
}

// Test empty string after "(?" returns BadPerlOp
TEST_F(ParsePerlFlagsTest_533, EmptyAfterQuestionMark_533) {
  absl::string_view whole("(?");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadPerlOp);
}

// Test flags combination (?is-m)
TEST_F(ParsePerlFlagsTest_533, FlagsCombinationPositiveAndNegative_533) {
  absl::string_view whole("(?is-m)abc");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?is-m)abc");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc");
  EXPECT_TRUE(ps.flags() & Regexp::FoldCase);
  EXPECT_TRUE(ps.flags() & Regexp::DotNL);
  EXPECT_TRUE(ps.flags() & Regexp::OneLine);  // -m sets OneLine
}

// Test named capture with angle bracket style missing closing bracket
TEST_F(ParsePerlFlagsTest_533, NamedCaptureAngleMissingClose_533) {
  absl::string_view whole("(?<name");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?<name");
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(status_.code(), kRegexpBadNamedCapture);
}

// Test named capture (?P<name>) with valid name containing underscores
TEST_F(ParsePerlFlagsTest_533, NamedCaptureWithUnderscore_533) {
  absl::string_view whole("(?P<my_name>abc)");
  Regexp::ParseState ps(Regexp::PerlX, whole, &status_);
  absl::string_view s("(?P<my_name>abc)");
  EXPECT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, "abc)");
}

}  // namespace re2
