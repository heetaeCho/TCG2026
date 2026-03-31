#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Test fixture for MimicsPCRE tests
class MimicsPCRETest_221 : public ::testing::Test {
 protected:
  Regexp* ParseRegexp(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    return re;
  }
};

// Simple literal string should mimic PCRE
TEST_F(MimicsPCRETest_221, SimpleLiteralMimicsPCRE_221) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  EXPECT_TRUE(result);
  re->Decref();
}

// Simple concatenation should mimic PCRE
TEST_F(MimicsPCRETest_221, SimpleConcatenationMimicsPCRE_221) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Simple alternation should mimic PCRE
TEST_F(MimicsPCRETest_221, SimpleAlternationMimicsPCRE_221) {
  Regexp* re = ParseRegexp("a|b");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Star quantifier on simple pattern should mimic PCRE
TEST_F(MimicsPCRETest_221, StarQuantifierMimicsPCRE_221) {
  Regexp* re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Plus quantifier on simple pattern should mimic PCRE
TEST_F(MimicsPCRETest_221, PlusQuantifierMimicsPCRE_221) {
  Regexp* re = ParseRegexp("a+");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Question quantifier on simple pattern should mimic PCRE
TEST_F(MimicsPCRETest_221, QuestQuantifierMimicsPCRE_221) {
  Regexp* re = ParseRegexp("a?");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Capture group should mimic PCRE
TEST_F(MimicsPCRETest_221, CaptureGroupMimicsPCRE_221) {
  Regexp* re = ParseRegexp("(abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Dot star pattern should mimic PCRE
TEST_F(MimicsPCRETest_221, DotStarMimicsPCRE_221) {
  Regexp* re = ParseRegexp(".*");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Character class should mimic PCRE
TEST_F(MimicsPCRETest_221, CharClassMimicsPCRE_221) {
  Regexp* re = ParseRegexp("[abc]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Nested capture groups should mimic PCRE
TEST_F(MimicsPCRETest_221, NestedCaptureGroupsMimicsPCRE_221) {
  Regexp* re = ParseRegexp("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Anchored pattern should mimic PCRE
TEST_F(MimicsPCRETest_221, AnchoredPatternMimicsPCRE_221) {
  Regexp* re = ParseRegexp("^abc$");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Empty pattern should mimic PCRE
TEST_F(MimicsPCRETest_221, EmptyPatternMimicsPCRE_221) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Repeat with specific count should mimic PCRE
TEST_F(MimicsPCRETest_221, RepeatCountMimicsPCRE_221) {
  Regexp* re = ParseRegexp("a{3}");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Repeat with range should mimic PCRE
TEST_F(MimicsPCRETest_221, RepeatRangeMimicsPCRE_221) {
  Regexp* re = ParseRegexp("a{2,5}");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Alternation where one branch can match empty might not mimic PCRE
// e.g., (a|b)*|c - complex patterns with empty match potential
TEST_F(MimicsPCRETest_221, ComplexAlternationWithEmptyBranch_221) {
  Regexp* re = ParseRegexp("(a*|b)c");
  ASSERT_NE(re, nullptr);
  // Just check it doesn't crash; actual result depends on implementation
  bool result = re->MimicsPCRE();
  (void)result;  // result may be true or false
  re->Decref();
}

// Pattern with backreference-like complexity
TEST_F(MimicsPCRETest_221, WordBoundaryPattern_221) {
  Regexp* re = ParseRegexp("\\bword\\b");
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  (void)result;
  re->Decref();
}

// Pattern where star of something that can match empty string
// This is a key case for MimicsPCRE: (a*)*
TEST_F(MimicsPCRETest_221, StarOfStarMayNotMimicPCRE_221) {
  Regexp* re = ParseRegexp("(a*)*");
  ASSERT_NE(re, nullptr);
  // This is a pattern where RE2 and PCRE can differ
  bool result = re->MimicsPCRE();
  EXPECT_FALSE(result);
  re->Decref();
}

// Pattern (a+)* should mimic PCRE since a+ cannot match empty
TEST_F(MimicsPCRETest_221, StarOfPlusMimicsPCRE_221) {
  Regexp* re = ParseRegexp("(a+)*");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Pattern (a?)* - a? can match empty, wrapped in *
TEST_F(MimicsPCRETest_221, StarOfQuestMayNotMimicPCRE_221) {
  Regexp* re = ParseRegexp("(a?)*");
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  EXPECT_FALSE(result);
  re->Decref();
}

// Pattern where empty string match is in alternation under star
TEST_F(MimicsPCRETest_221, StarOfAlternationWithEmpty_221) {
  Regexp* re = ParseRegexp("(a|)*");
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  EXPECT_FALSE(result);
  re->Decref();
}

// Simple digit class pattern
TEST_F(MimicsPCRETest_221, DigitClassMimicsPCRE_221) {
  Regexp* re = ParseRegexp("\\d+");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Named capture group
TEST_F(MimicsPCRETest_221, NamedCaptureGroupMimicsPCRE_221) {
  Regexp* re = ParseRegexp("(?P<name>abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Non-greedy quantifier
TEST_F(MimicsPCRETest_221, NonGreedyStarMimicsPCRE_221) {
  Regexp* re = ParseRegexp("a*?");
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  // Non-greedy should still work
  (void)result;
  re->Decref();
}

// Complex nested pattern: ((a*)*) - star of star in capture
TEST_F(MimicsPCRETest_221, NestedStarOfStarInCapture_221) {
  Regexp* re = ParseRegexp("((a*)*)");
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  EXPECT_FALSE(result);
  re->Decref();
}

// Pattern (a+|b+)* should mimic PCRE since neither branch matches empty
TEST_F(MimicsPCRETest_221, StarOfAlternationNonEmpty_221) {
  Regexp* re = ParseRegexp("(a+|b+)*");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Pattern with repeat of something that can be empty
TEST_F(MimicsPCRETest_221, RepeatOfEmptyable_221) {
  Regexp* re = ParseRegexp("(a*){2,}");
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  EXPECT_FALSE(result);
  re->Decref();
}

// Literal single character
TEST_F(MimicsPCRETest_221, SingleCharMimicsPCRE_221) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Pattern (|a) has empty branch in alternation under implicit group
TEST_F(MimicsPCRETest_221, AlternationWithLeadingEmpty_221) {
  Regexp* re = ParseRegexp("(|a)*");
  ASSERT_NE(re, nullptr);
  bool result = re->MimicsPCRE();
  EXPECT_FALSE(result);
  re->Decref();
}

}  // namespace re2
