// File: parse_pushdot_test_493.cc

#include <gtest/gtest.h>

// Forward-declare RegexpStatus to avoid needing its full definition for these tests.
namespace re2 { class RegexpStatus; }

// Pull in the implementation so we can construct ParseState and call its methods.
// This is acceptable for testing the observable behavior of PushDot().
#include "re2/parse.cc"

using re2::Regexp;

// Helper to safely finish and return the top-level Regexp*, or nullptr on failure.
static Regexp* FinishOrNull(Regexp::ParseState& ps) {
  return ps.DoFinish();
}

// --- Tests ---

// Dot with DotNL (and NOT NeverNL) should act like "any character" => kRegexpAnyChar.
TEST(ParseStatePushDotTest_493, AnyCharWhenDotNLAndNotNeverNL_493) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(Regexp::DotNL);
  re2::RegexpStatus* status = nullptr;

  Regexp::ParseState ps(flags, /*whole_regexp=*/absl::string_view(), status);

  ASSERT_TRUE(ps.PushDot()) << "PushDot should succeed";

  Regexp* re = FinishOrNull(ps);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), re2::kRegexpAnyChar);

  // Cleanup if reference counting is available.
  re->Decref();
}

// Dot with DotNL AND NeverNL must not match '\n' => builds a CharClass (no FoldCase).
TEST(ParseStatePushDotTest_493, CharClassWhenDotNLButNeverNL_493) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::DotNL | Regexp::NeverNL | Regexp::FoldCase);
  re2::RegexpStatus* status = nullptr;

  Regexp::ParseState ps(flags, /*whole_regexp=*/absl::string_view(), status);

  ASSERT_TRUE(ps.PushDot()) << "PushDot should succeed";

  Regexp* re = FinishOrNull(ps);
  ASSERT_NE(re, nullptr);

  // Should be a character class when NeverNL is set.
  EXPECT_EQ(re->op(), re2::kRegexpCharClass);

  // FoldCase must be stripped on the created char-class node.
  EXPECT_EQ((re->parse_flags() & Regexp::FoldCase), 0)
      << "FoldCase should be cleared for the char class node";

  // The class should exclude '\n' but include others around it.
  ASSERT_NE(re->ccb_, nullptr) << "Expected builder to be present for CharClass";
  EXPECT_FALSE(re->ccb_->Contains('\n')) << "Newline must be excluded";
  EXPECT_TRUE(re->ccb_->Contains('\n' - 1)) << "Value just below newline should be included";
  EXPECT_TRUE(re->ccb_->Contains('\n' + 1)) << "Value just above newline should be included";
  EXPECT_TRUE(re->ccb_->Contains('a')) << "Typical non-newline ASCII should be included";

  re->Decref();
}

// Default flags (no DotNL): '.' should be a char class excluding '\n'.
TEST(ParseStatePushDotTest_493, CharClassDefaultFlags_ExcludesNewline_493) {
  Regexp::ParseFlags flags = Regexp::NoParseFlags;
  re2::RegexpStatus* status = nullptr;

  Regexp::ParseState ps(flags, /*whole_regexp=*/absl::string_view(), status);

  ASSERT_TRUE(ps.PushDot()) << "PushDot should succeed under default flags";

  Regexp* re = FinishOrNull(ps);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), re2::kRegexpCharClass);

  ASSERT_NE(re->ccb_, nullptr);
  EXPECT_FALSE(re->ccb_->Contains('\n')) << "Newline must be excluded by default '.'";
  EXPECT_TRUE(re->ccb_->Contains(0)) << "Range should include 0";
  EXPECT_TRUE(re->ccb_->Contains(' ')) << "Space should be included";
  EXPECT_TRUE(re->ccb_->Contains('z')) << "General letters should be included";

  re->Decref();
}
