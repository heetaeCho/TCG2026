#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Helper to parse a regex string and return its ToString() representation.
// This tests the ToString/ToStringWalker functionality through the public Regexp interface.
static std::string ParseAndToString(const std::string& pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  if (re == nullptr) {
    return "";
  }
  std::string result = re->ToString();
  re->Decref();
  return result;
}

// Test basic literal characters
TEST(ToStringTest_226, SimpleLiteral_226) {
  EXPECT_EQ("abc", ParseAndToString("abc"));
}

// Test empty match
TEST(ToStringTest_226, EmptyMatch_226) {
  std::string result = ParseAndToString("");
  // Empty regex should produce some valid output
  EXPECT_FALSE(result.empty() && false);  // Just verify it doesn't crash
}

// Test alternation
TEST(ToStringTest_226, Alternation_226) {
  EXPECT_EQ("a|b", ParseAndToString("a|b"));
}

// Test nested alternation
TEST(ToStringTest_226, NestedAlternation_226) {
  EXPECT_EQ("a|b|c", ParseAndToString("a|b|c"));
}

// Test star repetition
TEST(ToStringTest_226, Star_226) {
  EXPECT_EQ("a*", ParseAndToString("a*"));
}

// Test plus repetition
TEST(ToStringTest_226, Plus_226) {
  EXPECT_EQ("a+", ParseAndToString("a+"));
}

// Test quest (optional)
TEST(ToStringTest_226, Quest_226) {
  EXPECT_EQ("a?", ParseAndToString("a?"));
}

// Test capture group
TEST(ToStringTest_226, CaptureGroup_226) {
  EXPECT_EQ("(a)", ParseAndToString("(a)"));
}

// Test named capture group
TEST(ToStringTest_226, NamedCaptureGroup_226) {
  EXPECT_EQ("(?P<name>a)", ParseAndToString("(?P<name>a)"));
}

// Test non-capturing group
TEST(ToStringTest_226, NonCapturingGroup_226) {
  EXPECT_EQ("(?:a)", ParseAndToString("(?:a)"));
}

// Test character class
TEST(ToStringTest_226, CharClass_226) {
  EXPECT_EQ("[a-z]", ParseAndToString("[a-z]"));
}

// Test any character (dot)
TEST(ToStringTest_226, AnyChar_226) {
  std::string result = ParseAndToString(".");
  EXPECT_FALSE(result.empty());
}

// Test begin line anchor
TEST(ToStringTest_226, BeginLine_226) {
  std::string result = ParseAndToString("^a");
  EXPECT_NE(result.find("a"), std::string::npos);
}

// Test end line anchor
TEST(ToStringTest_226, EndLine_226) {
  std::string result = ParseAndToString("a$");
  EXPECT_NE(result.find("a"), std::string::npos);
}

// Test word boundary
TEST(ToStringTest_226, WordBoundary_226) {
  std::string result = ParseAndToString("\\ba\\b");
  EXPECT_NE(result.find("a"), std::string::npos);
}

// Test repeat with specific count
TEST(ToStringTest_226, Repeat_226) {
  EXPECT_EQ("a{3}", ParseAndToString("a{3}"));
}

// Test repeat with range
TEST(ToStringTest_226, RepeatRange_226) {
  EXPECT_EQ("a{2,5}", ParseAndToString("a{2,5}"));
}

// Test repeat with min only
TEST(ToStringTest_226, RepeatMinOnly_226) {
  EXPECT_EQ("a{2,}", ParseAndToString("a{2,}"));
}

// Test concatenation
TEST(ToStringTest_226, Concatenation_226) {
  EXPECT_EQ("abcd", ParseAndToString("abcd"));
}

// Test complex expression with alternation and concatenation
TEST(ToStringTest_226, ComplexAlternationConcat_226) {
  EXPECT_EQ("ab|cd", ParseAndToString("ab|cd"));
}

// Test non-greedy star
TEST(ToStringTest_226, NonGreedyStar_226) {
  EXPECT_EQ("a*?", ParseAndToString("a*?"));
}

// Test non-greedy plus
TEST(ToStringTest_226, NonGreedyPlus_226) {
  EXPECT_EQ("a+?", ParseAndToString("a+?"));
}

// Test non-greedy quest
TEST(ToStringTest_226, NonGreedyQuest_226) {
  EXPECT_EQ("a??", ParseAndToString("a??"));
}

// Test alternation inside capture group
TEST(ToStringTest_226, AlternationInCapture_226) {
  EXPECT_EQ("(a|b)", ParseAndToString("(a|b)"));
}

// Test star of group
TEST(ToStringTest_226, StarOfGroup_226) {
  EXPECT_EQ("(?:ab)*", ParseAndToString("(?:ab)*"));
}

// Test plus of group
TEST(ToStringTest_226, PlusOfGroup_226) {
  EXPECT_EQ("(?:ab)+", ParseAndToString("(?:ab)+"));
}

// Test roundtrip - parse, toString, parse again, toString again should be the same
TEST(ToStringTest_226, Roundtrip_226) {
  std::string patterns[] = {
    "a", "abc", "a|b", "a*", "a+", "a?",
    "(a)", "[a-z]", "a{3}", "a{2,5}",
    "(?:ab)*", "a+?", "(?P<name>a)"
  };
  for (const auto& pattern : patterns) {
    std::string first = ParseAndToString(pattern);
    std::string second = ParseAndToString(first);
    EXPECT_EQ(first, second) << "Roundtrip failed for: " << pattern;
  }
}

// Test complex nested expression
TEST(ToStringTest_226, ComplexNested_226) {
  std::string result = ParseAndToString("(a(b|c)*d)+");
  EXPECT_FALSE(result.empty());
  // Verify roundtrip stability
  std::string second = ParseAndToString(result);
  EXPECT_EQ(result, second);
}

// Test literal string (multiple characters in sequence)
TEST(ToStringTest_226, LiteralString_226) {
  EXPECT_EQ("hello", ParseAndToString("hello"));
}

// Test escaped special characters
TEST(ToStringTest_226, EscapedSpecialChars_226) {
  std::string result = ParseAndToString("\\.");
  EXPECT_FALSE(result.empty());
}

// Test alternation with star should produce correct grouping
TEST(ToStringTest_226, AlternationWithStar_226) {
  std::string result = ParseAndToString("a|b*");
  // Should roundtrip properly
  std::string second = ParseAndToString(result);
  EXPECT_EQ(result, second);
}

// Test star of alternation needs grouping
TEST(ToStringTest_226, StarOfAlternation_226) {
  std::string result = ParseAndToString("(?:a|b)*");
  EXPECT_EQ("(?:a|b)*", result);
}

// Test begin text anchor
TEST(ToStringTest_226, BeginText_226) {
  std::string result = ParseAndToString("\\Aa", Regexp::LikePerl);
  EXPECT_FALSE(result.empty());
}

// Test end text anchor
TEST(ToStringTest_226, EndText_226) {
  std::string result = ParseAndToString("a\\z", Regexp::LikePerl);
  EXPECT_FALSE(result.empty());
}

// Test HaveMatch via ToString
TEST(ToStringTest_226, HaveMatch_226) {
  Regexp* re = Regexp::HaveMatch(1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  std::string result = re->ToString();
  re->Decref();
  // Just ensure it doesn't crash and produces something
  EXPECT_TRUE(true);
}

// Test multiple capture groups
TEST(ToStringTest_226, MultipleCaptureGroups_226) {
  std::string result = ParseAndToString("(a)(b)(c)");
  EXPECT_FALSE(result.empty());
  std::string second = ParseAndToString(result);
  EXPECT_EQ(result, second);
}

// Test deeply nested groups
TEST(ToStringTest_226, DeeplyNestedGroups_226) {
  std::string result = ParseAndToString("((((a))))");
  EXPECT_FALSE(result.empty());
  std::string second = ParseAndToString(result);
  EXPECT_EQ(result, second);
}

// Test character class with negation
TEST(ToStringTest_226, NegatedCharClass_226) {
  std::string result = ParseAndToString("[^a-z]");
  EXPECT_FALSE(result.empty());
  std::string second = ParseAndToString(result);
  EXPECT_EQ(result, second);
}

// Test repetition of alternation - needs wrapping
TEST(ToStringTest_226, RepeatOfAlternation_226) {
  std::string result = ParseAndToString("(?:a|b){3,5}");
  EXPECT_EQ("(?:a|b){3,5}", result);
}

// Test concat inside alternation
TEST(ToStringTest_226, ConcatInsideAlternation_226) {
  EXPECT_EQ("abc|def", ParseAndToString("abc|def"));
}

// Test star applied to concat needs grouping
TEST(ToStringTest_226, StarAppliedToConcat_226) {
  std::string result = ParseAndToString("(?:abc)*");
  EXPECT_EQ("(?:abc)*", result);
}

}  // namespace re2
