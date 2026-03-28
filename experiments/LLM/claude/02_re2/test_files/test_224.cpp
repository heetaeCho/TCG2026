#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class ToStringTest_224 : public ::testing::Test {
 protected:
  Regexp* ParseRegexp(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    return re;
  }
};

// Test basic literal string round-trip
TEST_F(ToStringTest_224, LiteralString_224) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "hello");
  re->Decref();
}

// Test alternation
TEST_F(ToStringTest_224, Alternation_224) {
  Regexp* re = ParseRegexp("a|b");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a|b");
  re->Decref();
}

// Test star quantifier
TEST_F(ToStringTest_224, StarQuantifier_224) {
  Regexp* re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a*");
  re->Decref();
}

// Test plus quantifier
TEST_F(ToStringTest_224, PlusQuantifier_224) {
  Regexp* re = ParseRegexp("a+");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a+");
  re->Decref();
}

// Test question mark quantifier
TEST_F(ToStringTest_224, QuestQuantifier_224) {
  Regexp* re = ParseRegexp("a?");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a?");
  re->Decref();
}

// Test grouped expression
TEST_F(ToStringTest_224, GroupedExpression_224) {
  Regexp* re = ParseRegexp("(abc)");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "(abc)");
  re->Decref();
}

// Test character class
TEST_F(ToStringTest_224, CharacterClass_224) {
  Regexp* re = ParseRegexp("[abc]");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[a-c]");
  re->Decref();
}

// Test dot (any character)
TEST_F(ToStringTest_224, DotAnyChar_224) {
  Regexp* re = ParseRegexp(".");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  // The dot should be preserved in some form
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test anchors
TEST_F(ToStringTest_224, BeginAnchor_224) {
  Regexp* re = ParseRegexp("^abc");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_NE(s.find("abc"), std::string::npos);
  re->Decref();
}

TEST_F(ToStringTest_224, EndAnchor_224) {
  Regexp* re = ParseRegexp("abc$");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_NE(s.find("abc"), std::string::npos);
  re->Decref();
}

// Test repeat with bounds {n,m}
TEST_F(ToStringTest_224, RepeatBounds_224) {
  Regexp* re = ParseRegexp("a{2,5}");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a{2,5}");
  re->Decref();
}

// Test exact repeat {n}
TEST_F(ToStringTest_224, ExactRepeat_224) {
  Regexp* re = ParseRegexp("a{3}");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a{3}");
  re->Decref();
}

// Test repeat with minimum only {n,}
TEST_F(ToStringTest_224, RepeatMinOnly_224) {
  Regexp* re = ParseRegexp("a{2,}");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a{2,}");
  re->Decref();
}

// Test non-greedy quantifiers
TEST_F(ToStringTest_224, NonGreedyStar_224) {
  Regexp* re = ParseRegexp("a*?");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a*?");
  re->Decref();
}

TEST_F(ToStringTest_224, NonGreedyPlus_224) {
  Regexp* re = ParseRegexp("a+?");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a+?");
  re->Decref();
}

TEST_F(ToStringTest_224, NonGreedyQuest_224) {
  Regexp* re = ParseRegexp("a??");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a??");
  re->Decref();
}

// Test nested groups
TEST_F(ToStringTest_224, NestedGroups_224) {
  Regexp* re = ParseRegexp("((a)(b))");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_NE(s.find("a"), std::string::npos);
  EXPECT_NE(s.find("b"), std::string::npos);
  re->Decref();
}

// Test empty regex
TEST_F(ToStringTest_224, EmptyRegex_224) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  // Empty regex should produce some valid output
  re->Decref();
}

// Test concatenation of literals
TEST_F(ToStringTest_224, Concatenation_224) {
  Regexp* re = ParseRegexp("abcdef");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abcdef");
  re->Decref();
}

// Test complex expression
TEST_F(ToStringTest_224, ComplexExpression_224) {
  Regexp* re = ParseRegexp("(a+|b*)?c{2,4}");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test escaped special characters
TEST_F(ToStringTest_224, EscapedSpecialChars_224) {
  Regexp* re = ParseRegexp("a\\.b");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_NE(s.find("a"), std::string::npos);
  EXPECT_NE(s.find("b"), std::string::npos);
  re->Decref();
}

// Test named capture group
TEST_F(ToStringTest_224, NamedCapture_224) {
  Regexp* re = ParseRegexp("(?P<name>abc)");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_NE(s.find("abc"), std::string::npos);
  re->Decref();
}

// Test non-capturing group
TEST_F(ToStringTest_224, NonCapturingGroup_224) {
  Regexp* re = ParseRegexp("(?:abc)");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_NE(s.find("abc"), std::string::npos);
  re->Decref();
}

// Test character class with range
TEST_F(ToStringTest_224, CharClassRange_224) {
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[a-z]");
  re->Decref();
}

// Test negated character class
TEST_F(ToStringTest_224, NegatedCharClass_224) {
  Regexp* re = ParseRegexp("[^abc]");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_NE(s.find("[^"), std::string::npos);
  re->Decref();
}

// Test word boundary
TEST_F(ToStringTest_224, WordBoundary_224) {
  Regexp* re = ParseRegexp("\\b");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test \\d shorthand
TEST_F(ToStringTest_224, DigitShorthand_224) {
  Regexp* re = ParseRegexp("\\d+");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test multiple alternation branches
TEST_F(ToStringTest_224, MultipleAlternation_224) {
  Regexp* re = ParseRegexp("a|b|c|d");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_NE(s.find("|"), std::string::npos);
  re->Decref();
}

// Test that ToString of a parsed and re-parsed expression is consistent
TEST_F(ToStringTest_224, RoundTrip_224) {
  std::string original = "a(b+|c*)?d{2,5}";
  Regexp* re1 = ParseRegexp(original);
  ASSERT_NE(re1, nullptr);
  std::string s1 = re1->ToString();
  
  Regexp* re2 = ParseRegexp(s1);
  ASSERT_NE(re2, nullptr);
  std::string s2 = re2->ToString();
  
  EXPECT_EQ(s1, s2);
  re1->Decref();
  re2->Decref();
}

// Test repeat {0,1} is equivalent to ?
TEST_F(ToStringTest_224, RepeatZeroOne_224) {
  Regexp* re = ParseRegexp("a{0,1}");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  // {0,1} should be simplified to a?
  EXPECT_EQ(s, "a?");
  re->Decref();
}

// Test repeat {0,} is equivalent to *
TEST_F(ToStringTest_224, RepeatZeroUnbounded_224) {
  Regexp* re = ParseRegexp("a{0,}");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a*");
  re->Decref();
}

// Test repeat {1,} is equivalent to +
TEST_F(ToStringTest_224, RepeatOneUnbounded_224) {
  Regexp* re = ParseRegexp("a{1,}");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a+");
  re->Decref();
}

// Test case-insensitive flag
TEST_F(ToStringTest_224, CaseInsensitive_224) {
  Regexp* re = ParseRegexp("(?i)abc");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test single character
TEST_F(ToStringTest_224, SingleChar_224) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a");
  re->Decref();
}

// Test special regex metacharacter in literal context
TEST_F(ToStringTest_224, MetacharEscaped_224) {
  Regexp* re = ParseRegexp("\\(");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "\\(");
  re->Decref();
}

// Test complex nested expression
TEST_F(ToStringTest_224, DeepNesting_224) {
  Regexp* re = ParseRegexp("((((a))))");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_NE(s.find("a"), std::string::npos);
  re->Decref();
}

}  // namespace re2
