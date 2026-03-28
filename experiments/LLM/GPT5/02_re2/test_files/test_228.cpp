// File: re2_tostring_postvisit_test_228.cc
#include "re2/regexp.h"

#include <gtest/gtest.h>
#include <string>

using re2::Regexp;

// Helper: parse pattern with LikePerl flavor and return ToString().
// Treats the implementation as a black box.
static std::string Canon(const std::string& pattern,
                         Regexp::ParseFlags flags = Regexp::LikePerl) {
  Regexp* re = Regexp::Parse(pattern, flags, /*status=*/nullptr);
  EXPECT_NE(re, nullptr) << "Parse failed for pattern: " << pattern;
  if (!re) return std::string();
  std::string out = re->ToString();
  re->Decref();
  return out;
}

// ----- Normal operation -----

TEST(ToStringPostVisit_228, LiteralAndConcat_228) {
  EXPECT_EQ(Canon("a"), "a");
  EXPECT_EQ(Canon("abc"), "abc");  // exercises kRegexpLiteralString / concat path
}

TEST(ToStringPostVisit_228, AnyChar_228) {
  EXPECT_EQ(Canon("."), ".");
}

TEST(ToStringPostVisit_228, LineAnchors_228) {
  EXPECT_EQ(Canon("^"), "^");  // kRegexpBeginLine
  EXPECT_EQ(Canon("$"), "$");  // kRegexpEndLine
}

TEST(ToStringPostVisit_228, TextAnchors_228) {
  // BeginText and EndText canonical forms
  EXPECT_EQ(Canon("\\A"), "(?-m:^)");  // kRegexpBeginText prints (?-m:^)
  EXPECT_EQ(Canon("\\z"), "\\z");      // kRegexpEndText (no WasDollar flag)
}

TEST(ToStringPostVisit_228, WordBoundaries_228) {
  EXPECT_EQ(Canon("\\b"), "\\b");  // kRegexpWordBoundary
  EXPECT_EQ(Canon("\\B"), "\\B");  // kRegexpNoWordBoundary
}

TEST(ToStringPostVisit_228, Alternation_228) {
  EXPECT_EQ(Canon("a|b"), "a|b");       // kRegexpAlternate (joins with '|')
  EXPECT_EQ(Canon("a|b|c"), "a|b|c");   // multiple alternates
}

TEST(ToStringPostVisit_228, GreedyQuantifiers_228) {
  EXPECT_EQ(Canon("a*"), "a*");  // kRegexpStar
  EXPECT_EQ(Canon("a+"), "a+");  // kRegexpPlus
  EXPECT_EQ(Canon("a?"), "a?");  // kRegexpQuest
}

TEST(ToStringPostVisit_228, NonGreedyQuantifiers_228) {
  EXPECT_EQ(Canon("a*?"), "a*?");
  EXPECT_EQ(Canon("a+?"), "a+?");
  EXPECT_EQ(Canon("a??"), "a??");
}

TEST(ToStringPostVisit_228, RepeatForms_228) {
  EXPECT_EQ(Canon("a{3}"), "a{3}");       // exact
  EXPECT_EQ(Canon("a{2,}"), "a{2,}");     // open upper bound
  EXPECT_EQ(Canon("a{2,4}"), "a{2,4}");   // range
}

TEST(ToStringPostVisit_228, RepeatNonGreedy_228) {
  EXPECT_EQ(Canon("a{2,4}?"), "a{2,4}?");  // kRegexpRepeat + NonGreedy
}

TEST(ToStringPostVisit_228, CharClassBasic_228) {
  EXPECT_EQ(Canon("[a-c]"), "[a-c]");  // kRegexpCharClass with a range
}

TEST(ToStringPostVisit_228, CapturingGroup_228) {
  EXPECT_EQ(Canon("(ab)"), "(ab)");  // kRegexpCapture must close with ')'
}

// ----- Builder-only construct covered by PostVisit -----

TEST(ToStringPostVisit_228, HaveMatchEmitsTag_228) {
  // kRegexpHaveMatch prints "(?HaveMatch:%d)"
  Regexp* have = Regexp::HaveMatch(/*match_id=*/7, Regexp::NoParseFlags);
  ASSERT_NE(have, nullptr);
  std::string s = have->ToString();
  have->Decref();
  EXPECT_EQ(s, "(?HaveMatch:7)");
}
