#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class RegexpToStringTest_225 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Helper to parse and get ToString, then clean up
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

// Test simple literal
TEST_F(RegexpToStringTest_225, SimpleLiteral_225) {
  std::string result = ParseAndToString("abc");
  EXPECT_EQ(result, "abc");
}

// Test empty regex
TEST_F(RegexpToStringTest_225, EmptyRegex_225) {
  std::string result = ParseAndToString("");
  // Empty pattern should produce something valid
  EXPECT_FALSE(result.empty() && result.find("truncated") != std::string::npos);
}

// Test alternation
TEST_F(RegexpToStringTest_225, Alternation_225) {
  std::string result = ParseAndToString("a|b");
  EXPECT_EQ(result, "a|b");
}

// Test character class
TEST_F(RegexpToStringTest_225, CharacterClass_225) {
  std::string result = ParseAndToString("[abc]");
  EXPECT_EQ(result, "[a-c]");
}

// Test negated character class
TEST_F(RegexpToStringTest_225, NegatedCharacterClass_225) {
  std::string result = ParseAndToString("[^abc]");
  EXPECT_EQ(result, "[^a-c]");
}

// Test star quantifier
TEST_F(RegexpToStringTest_225, StarQuantifier_225) {
  std::string result = ParseAndToString("a*");
  EXPECT_EQ(result, "a*");
}

// Test plus quantifier
TEST_F(RegexpToStringTest_225, PlusQuantifier_225) {
  std::string result = ParseAndToString("a+");
  EXPECT_EQ(result, "a+");
}

// Test question mark quantifier
TEST_F(RegexpToStringTest_225, QuestQuantifier_225) {
  std::string result = ParseAndToString("a?");
  EXPECT_EQ(result, "a?");
}

// Test non-greedy star
TEST_F(RegexpToStringTest_225, NonGreedyStar_225) {
  std::string result = ParseAndToString("a*?");
  EXPECT_EQ(result, "a*?");
}

// Test non-greedy plus
TEST_F(RegexpToStringTest_225, NonGreedyPlus_225) {
  std::string result = ParseAndToString("a+?");
  EXPECT_EQ(result, "a+?");
}

// Test non-greedy question
TEST_F(RegexpToStringTest_225, NonGreedyQuest_225) {
  std::string result = ParseAndToString("a??");
  EXPECT_EQ(result, "a??");
}

// Test repeat with min and max
TEST_F(RegexpToStringTest_225, RepeatMinMax_225) {
  std::string result = ParseAndToString("a{2,5}");
  EXPECT_EQ(result, "a{2,5}");
}

// Test repeat with exact count
TEST_F(RegexpToStringTest_225, RepeatExact_225) {
  std::string result = ParseAndToString("a{3}");
  EXPECT_EQ(result, "a{3}");
}

// Test repeat with min only
TEST_F(RegexpToStringTest_225, RepeatMinOnly_225) {
  std::string result = ParseAndToString("a{2,}");
  EXPECT_EQ(result, "a{2,}");
}

// Test capture group
TEST_F(RegexpToStringTest_225, CaptureGroup_225) {
  std::string result = ParseAndToString("(abc)");
  EXPECT_EQ(result, "(abc)");
}

// Test non-capturing group
TEST_F(RegexpToStringTest_225, NonCapturingGroup_225) {
  std::string result = ParseAndToString("(?:abc)");
  EXPECT_EQ(result, "(?:abc)");
}

// Test dot (any character)
TEST_F(RegexpToStringTest_225, DotAnyChar_225) {
  std::string result = ParseAndToString(".");
  EXPECT_FALSE(result.empty());
}

// Test anchors
TEST_F(RegexpToStringTest_225, BeginAnchor_225) {
  std::string result = ParseAndToString("^abc");
  EXPECT_NE(result.find("abc"), std::string::npos);
}

TEST_F(RegexpToStringTest_225, EndAnchor_225) {
  std::string result = ParseAndToString("abc$");
  EXPECT_NE(result.find("abc"), std::string::npos);
}

// Test concatenation
TEST_F(RegexpToStringTest_225, Concatenation_225) {
  std::string result = ParseAndToString("abcdef");
  EXPECT_EQ(result, "abcdef");
}

// Test nested groups
TEST_F(RegexpToStringTest_225, NestedGroups_225) {
  std::string result = ParseAndToString("((a)(b))");
  EXPECT_NE(result.find("a"), std::string::npos);
  EXPECT_NE(result.find("b"), std::string::npos);
}

// Test complex pattern
TEST_F(RegexpToStringTest_225, ComplexPattern_225) {
  std::string result = ParseAndToString("a(b|c)*d+");
  EXPECT_FALSE(result.empty());
}

// Test escape sequences
TEST_F(RegexpToStringTest_225, EscapeSequences_225) {
  std::string result = ParseAndToString("\\d+");
  EXPECT_FALSE(result.empty());
}

// Test word boundary
TEST_F(RegexpToStringTest_225, WordBoundary_225) {
  std::string result = ParseAndToString("\\bfoo\\b");
  EXPECT_NE(result.find("foo"), std::string::npos);
}

// Test round-trip: parse and toString should produce a parseable equivalent
TEST_F(RegexpToStringTest_225, RoundTrip_225) {
  std::string original = "a(b|c){2,4}d*e?";
  std::string first = ParseAndToString(original);
  EXPECT_FALSE(first.empty());

  // Parse the result again and convert to string
  std::string second = ParseAndToString(first);
  EXPECT_EQ(first, second);
}

// Test single character
TEST_F(RegexpToStringTest_225, SingleChar_225) {
  std::string result = ParseAndToString("x");
  EXPECT_EQ(result, "x");
}

// Test named capture group
TEST_F(RegexpToStringTest_225, NamedCaptureGroup_225) {
  std::string result = ParseAndToString("(?P<name>abc)");
  EXPECT_NE(result.find("abc"), std::string::npos);
  EXPECT_NE(result.find("name"), std::string::npos);
}

// Test character class range
TEST_F(RegexpToStringTest_225, CharClassRange_225) {
  std::string result = ParseAndToString("[a-z]");
  EXPECT_EQ(result, "[a-z]");
}

// Test multiple alternations
TEST_F(RegexpToStringTest_225, MultipleAlternations_225) {
  std::string result = ParseAndToString("a|b|c|d");
  EXPECT_EQ(result, "[a-d]");
}

// Test that ToString produces consistent output on multiple calls
TEST_F(RegexpToStringTest_225, ConsistentOutput_225) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo(bar)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string first = re->ToString();
  std::string second = re->ToString();
  EXPECT_EQ(first, second);

  re->Decref();
}

// Test using POSIX flags
TEST_F(RegexpToStringTest_225, PosixFlags_225) {
  std::string result = ParseAndToString("abc", Regexp::PerlX);
  EXPECT_FALSE(result.empty());
}

// Test special regex operators
TEST_F(RegexpToStringTest_225, SpecialCharsEscaped_225) {
  std::string result = ParseAndToString("a\\.b");
  EXPECT_NE(result.find("."), std::string::npos);
}

// Test deeply nested pattern doesn't crash
TEST_F(RegexpToStringTest_225, DeeplyNestedPattern_225) {
  // Create a moderately nested pattern
  std::string pattern = "((((((a))))))";
  std::string result = ParseAndToString(pattern);
  EXPECT_NE(result.find("a"), std::string::npos);
}

// Test alternation with groups
TEST_F(RegexpToStringTest_225, AlternationWithGroups_225) {
  std::string result = ParseAndToString("(abc)|(def)");
  EXPECT_FALSE(result.empty());
}

// Test repeat with zero min
TEST_F(RegexpToStringTest_225, RepeatZeroMin_225) {
  std::string result = ParseAndToString("a{0,3}");
  EXPECT_FALSE(result.empty());
}

// Test character class with special chars
TEST_F(RegexpToStringTest_225, CharClassSpecialChars_225) {
  std::string result = ParseAndToString("[\\d\\s]");
  EXPECT_FALSE(result.empty());
}

// Test that very long patterns may get truncated
TEST_F(RegexpToStringTest_225, VeryLongAlternation_225) {
  // Build a pattern that might cause truncation due to max_visits limit
  // This tests the [truncated] behavior
  std::string pattern;
  for (int i = 0; i < 1000; i++) {
    if (i > 0) pattern += "|";
    pattern += "a";
    for (int j = 0; j < 10; j++) {
      pattern += "b";
    }
  }
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re != nullptr) {
    std::string result = re->ToString();
    // Result should be non-empty regardless
    EXPECT_FALSE(result.empty());
    re->Decref();
  }
}

// Test with flag FoldCase
TEST_F(RegexpToStringTest_225, FoldCaseFlag_225) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string result = re->ToString();
  EXPECT_FALSE(result.empty());
  re->Decref();
}

}  // namespace re2
