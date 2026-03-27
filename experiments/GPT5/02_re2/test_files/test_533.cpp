#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

// RE2 bits exposed in the prompt
#include "re2/regexp.h"
#include "re2/parse.cc"  // Provides re2::Regexp::ParseState and ParsePerlFlags

using re2::RegexpStatus;
using re2::RegexpStatusCode;
using re2::Regexp;
using re2::kRegexpBadPerlOp;
using re2::kRegexpInternalError;
using re2::kRegexpBadNamedCapture;

class ParsePerlFlagsTest_533 : public ::testing::Test {
protected:
  static Regexp::ParseFlags F(...) { return Regexp::ParseFlags(...); } // (not used; keep empty)
};

// --- Invalid entry / guard checks ---

TEST_F(ParsePerlFlagsTest_533, FailsWithoutPerlXFlag_533) {
  RegexpStatus st;
  std::string pattern = "(?i)";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::NoParseFlags, pattern, &st);
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(st.code(), kRegexpInternalError);
}

TEST_F(ParsePerlFlagsTest_533, FailsWhenNotStartingWithQuestionParen_533) {
  RegexpStatus st;
  std::string pattern = "abc";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(st.code(), kRegexpInternalError);
}

// --- Disallowed Perl constructs (?= ?! ?<= ?<!) ---

TEST_F(ParsePerlFlagsTest_533, RejectsLookaheadOp_533) {
  RegexpStatus st;
  std::string pattern = "(?=a)rest";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(st.code(), kRegexpBadPerlOp);
  EXPECT_EQ(st.error_arg(), absl::string_view("(?="));
}

TEST_F(ParsePerlFlagsTest_533, RejectsLookbehindOp_533) {
  RegexpStatus st;
  std::string pattern = "(?<=a)rest";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(st.code(), kRegexpBadPerlOp);
  EXPECT_EQ(st.error_arg(), absl::string_view("(?<="));
}

// --- Named capture handling ---

TEST_F(ParsePerlFlagsTest_533, NamedCaptureMissingAngleCloseSetsBadNamedCapture_533) {
  RegexpStatus st;
  std::string pattern = "(?<name";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(st.code(), kRegexpBadNamedCapture);
  EXPECT_EQ(st.error_arg(), absl::string_view(pattern));  // whole input reported
}

TEST_F(ParsePerlFlagsTest_533, NamedCaptureInvalidNameReportsCaptureToken_533) {
  RegexpStatus st;
  std::string pattern = "(?<1abc>";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(st.code(), kRegexpBadNamedCapture);
  EXPECT_EQ(st.error_arg(), absl::string_view("(?<1abc>"));
}

TEST_F(ParsePerlFlagsTest_533, NamedCaptureValidAdvancesInputAndSucceeds_533) {
  RegexpStatus st;
  std::string pattern = "(?<cap>XYZ)";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  ASSERT_TRUE(ps.ParsePerlFlags(&s));               // should succeed
  EXPECT_TRUE(st.ok());
  EXPECT_EQ(s, absl::string_view("XYZ)"));         // advanced past the `>` only
  // Flags unchanged aside from PerlX being retained
  EXPECT_TRUE(ps.flags() & Regexp::PerlX);
}

// --- Flag toggling behavior ---

TEST_F(ParsePerlFlagsTest_533, ParsesEnableFoldCaseAndClearsOneLine_533) {
  RegexpStatus st;
  std::string pattern = "(?im)rest";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(static_cast<Regexp::ParseFlags>(Regexp::PerlX | Regexp::OneLine),
                             pattern, &st);
  ASSERT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, absl::string_view("rest"));

  EXPECT_TRUE(ps.flags() & Regexp::PerlX);
  EXPECT_TRUE(ps.flags() & Regexp::FoldCase);       // i enabled
  EXPECT_FALSE(ps.flags() & Regexp::OneLine);       // m clears OneLine
}

TEST_F(ParsePerlFlagsTest_533, NegatedMEnablesOneLine_533) {
  RegexpStatus st;
  std::string pattern = "(?-m)X";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  ASSERT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, absl::string_view("X"));
  EXPECT_TRUE(ps.flags() & Regexp::OneLine);
}

TEST_F(ParsePerlFlagsTest_533, SetsDotNLAndNonGreedy_533) {
  RegexpStatus st;
  std::string pattern = "(?sU)";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  ASSERT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_TRUE(ps.flags() & Regexp::DotNL);
  EXPECT_TRUE(ps.flags() & Regexp::NonGreedy);
  EXPECT_TRUE(s.empty());
}

// --- Minus handling and unknowns ---

TEST_F(ParsePerlFlagsTest_533, MinusWithNoFollowingFlagIsError_533) {
  RegexpStatus st;
  std::string pattern = "(?-)";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(st.code(), kRegexpBadPerlOp);
  EXPECT_EQ(st.error_arg(), absl::string_view("(?-)"));
}

TEST_F(ParsePerlFlagsTest_533, SecondMinusIsError_533) {
  RegexpStatus st;
  std::string pattern = "(?-i-)x";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(st.code(), kRegexpBadPerlOp);
  EXPECT_EQ(st.error_arg(), absl::string_view("(?-i-"));
}

TEST_F(ParsePerlFlagsTest_533, UnknownFlagTriggersBadPerlOp_533) {
  RegexpStatus st;
  std::string pattern = "(?q)";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  EXPECT_FALSE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(st.code(), kRegexpBadPerlOp);
  EXPECT_EQ(st.error_arg(), absl::string_view("(?q"));
}

// --- Non-capturing with colon ---

TEST_F(ParsePerlFlagsTest_533, ColonFormStartsNonCapturingAndAdvancesInput_533) {
  RegexpStatus st;
  std::string pattern = "(?i:abc)";
  absl::string_view s(pattern);

  re2::Regexp::ParseState ps(Regexp::PerlX, pattern, &st);
  ASSERT_TRUE(ps.ParsePerlFlags(&s));
  EXPECT_EQ(s, absl::string_view("abc)"));          // immediately after ':'
  EXPECT_TRUE(ps.flags() & Regexp::FoldCase);       // i applied
  EXPECT_TRUE(st.ok());
}
