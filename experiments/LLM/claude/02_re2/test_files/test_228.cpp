#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

class RegexpToStringTest_228 : public ::testing::Test {
 protected:
  // Helper to parse a regex string, convert back to string via ToString(),
  // and return the result. Caller is responsible for understanding that
  // ToString() may normalize the regex.
  std::string RoundTrip(const std::string& pattern,
                        Regexp::ParseFlags flags = Regexp::LikePerl) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    if (re == nullptr) {
      return "";
    }
    std::string result = re->ToString();
    re->Decref();
    return result;
  }
};

// Test literal characters round-trip
TEST_F(RegexpToStringTest_228, LiteralSimple_228) {
  EXPECT_EQ("abc", RoundTrip("abc"));
}

// Test dot (any character)
TEST_F(RegexpToStringTest_228, AnyChar_228) {
  EXPECT_EQ(".", RoundTrip("."));
}

// Test star quantifier
TEST_F(RegexpToStringTest_228, Star_228) {
  EXPECT_EQ("a*", RoundTrip("a*"));
}

// Test plus quantifier
TEST_F(RegexpToStringTest_228, Plus_228) {
  EXPECT_EQ("a+", RoundTrip("a+"));
}

// Test quest quantifier
TEST_F(RegexpToStringTest_228, Quest_228) {
  EXPECT_EQ("a?", RoundTrip("a?"));
}

// Test non-greedy star
TEST_F(RegexpToStringTest_228, NonGreedyStar_228) {
  EXPECT_EQ("a*?", RoundTrip("a*?"));
}

// Test non-greedy plus
TEST_F(RegexpToStringTest_228, NonGreedyPlus_228) {
  EXPECT_EQ("a+?", RoundTrip("a+?"));
}

// Test non-greedy quest
TEST_F(RegexpToStringTest_228, NonGreedyQuest_228) {
  EXPECT_EQ("a??", RoundTrip("a??"));
}

// Test alternation
TEST_F(RegexpToStringTest_228, Alternate_228) {
  EXPECT_EQ("a|b", RoundTrip("a|b"));
}

// Test concatenation
TEST_F(RegexpToStringTest_228, Concat_228) {
  EXPECT_EQ("ab", RoundTrip("ab"));
}

// Test capture group
TEST_F(RegexpToStringTest_228, Capture_228) {
  EXPECT_EQ("(a)", RoundTrip("(a)"));
}

// Test begin line anchor
TEST_F(RegexpToStringTest_228, BeginLine_228) {
  EXPECT_EQ("^", RoundTrip("^"));
}

// Test end line anchor
TEST_F(RegexpToStringTest_228, EndLine_228) {
  EXPECT_EQ("$", RoundTrip("$"));
}

// Test word boundary
TEST_F(RegexpToStringTest_228, WordBoundary_228) {
  EXPECT_EQ("\\b", RoundTrip("\\b"));
}

// Test no word boundary
TEST_F(RegexpToStringTest_228, NoWordBoundary_228) {
  EXPECT_EQ("\\B", RoundTrip("\\B"));
}

// Test character class
TEST_F(RegexpToStringTest_228, CharClass_228) {
  EXPECT_EQ("[a-z]", RoundTrip("[a-z]"));
}

// Test negated character class
TEST_F(RegexpToStringTest_228, NegatedCharClass_228) {
  EXPECT_EQ("[^a-z]", RoundTrip("[^a-z]"));
}

// Test repeat {n}
TEST_F(RegexpToStringTest_228, RepeatExact_228) {
  EXPECT_EQ("a{3}", RoundTrip("a{3}"));
}

// Test repeat {n,m}
TEST_F(RegexpToStringTest_228, RepeatRange_228) {
  EXPECT_EQ("a{2,5}", RoundTrip("a{2,5}"));
}

// Test repeat {n,}
TEST_F(RegexpToStringTest_228, RepeatMin_228) {
  EXPECT_EQ("a{2,}", RoundTrip("a{2,}"));
}

// Test non-greedy repeat
TEST_F(RegexpToStringTest_228, NonGreedyRepeat_228) {
  EXPECT_EQ("a{2,5}?", RoundTrip("a{2,5}?"));
}

// Test empty match
TEST_F(RegexpToStringTest_228, EmptyMatch_228) {
  // An empty string parses to empty match
  std::string result = RoundTrip("(?:)");
  // The result should represent the empty match
  EXPECT_FALSE(result.empty() && result != "(?:)");
}

// Test \\C (any byte)
TEST_F(RegexpToStringTest_228, AnyByte_228) {
  EXPECT_EQ("\\C", RoundTrip("\\C"));
}

// Test complex expression round-trip
TEST_F(RegexpToStringTest_228, ComplexExpression_228) {
  std::string result = RoundTrip("(a|b)*c+[0-9]{2,4}");
  // Verify it produces a non-empty string
  EXPECT_FALSE(result.empty());
}

// Test nested groups
TEST_F(RegexpToStringTest_228, NestedGroups_228) {
  std::string result = RoundTrip("((a)(b))");
  EXPECT_FALSE(result.empty());
}

// Test alternation with more than two options
TEST_F(RegexpToStringTest_228, MultiAlternate_228) {
  EXPECT_EQ("a|b|c", RoundTrip("a|b|c"));
}

// Test escaped literal characters
TEST_F(RegexpToStringTest_228, EscapedLiteral_228) {
  std::string result = RoundTrip("\\.");
  // Should produce a literal dot, possibly escaped
  EXPECT_FALSE(result.empty());
}

// Test FoldCase flag on literal
TEST_F(RegexpToStringTest_228, FoldCaseLiteral_228) {
  std::string result = RoundTrip("(?i:a)");
  EXPECT_FALSE(result.empty());
}

// Test begin text (?-m:^)
TEST_F(RegexpToStringTest_228, BeginText_228) {
  // In OneLine mode, ^ becomes begin-text
  std::string result = RoundTrip("^", static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::OneLine));
  EXPECT_FALSE(result.empty());
}

// Test end text with WasDollar
TEST_F(RegexpToStringTest_228, EndText_228) {
  std::string result = RoundTrip("$", static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::OneLine));
  EXPECT_FALSE(result.empty());
}

// Test \\z (end of text)
TEST_F(RegexpToStringTest_228, EndTextBackslashZ_228) {
  std::string result = RoundTrip("\\z",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl | Regexp::PerlX));
  EXPECT_FALSE(result.empty());
}

// Test HaveMatch via factory method
TEST_F(RegexpToStringTest_228, HaveMatch_228) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  std::string result = re->ToString();
  EXPECT_NE(result.find("HaveMatch"), std::string::npos);
  EXPECT_NE(result.find("42"), std::string::npos);
  re->Decref();
}

// Test single character class [a]
TEST_F(RegexpToStringTest_228, SingleCharClass_228) {
  std::string result = RoundTrip("[a]");
  EXPECT_FALSE(result.empty());
}

// Test character class with multiple ranges
TEST_F(RegexpToStringTest_228, MultiRangeCharClass_228) {
  std::string result = RoundTrip("[a-zA-Z0-9]");
  EXPECT_FALSE(result.empty());
}

// Test that ToString on a star-in-alternation produces correct precedence
TEST_F(RegexpToStringTest_228, PrecedenceStarInAlternate_228) {
  std::string result = RoundTrip("a*|b+");
  EXPECT_EQ("a*|b+", result);
}

// Test alternation within a group
TEST_F(RegexpToStringTest_228, AlternateInGroup_228) {
  std::string result = RoundTrip("(a|b)c");
  EXPECT_EQ("(a|b)c", result);
}

// Test quantifier on group
TEST_F(RegexpToStringTest_228, QuantifierOnGroup_228) {
  std::string result = RoundTrip("(ab)+");
  EXPECT_EQ("(ab)+", result);
}

// Test double round-trip stability
TEST_F(RegexpToStringTest_228, DoubleRoundTrip_228) {
  std::string first = RoundTrip("(a|b)*c+[0-9]");
  std::string second = RoundTrip(first);
  EXPECT_EQ(first, second);
}

// Test literal string with special chars
TEST_F(RegexpToStringTest_228, LiteralSpecialChars_228) {
  std::string result = RoundTrip("\\(\\)\\[\\]",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl));
  EXPECT_FALSE(result.empty());
}

// Test that {0,} is equivalent to *
TEST_F(RegexpToStringTest_228, RepeatZeroOrMore_228) {
  std::string result = RoundTrip("a{0,}");
  // May be normalized to a*
  EXPECT_TRUE(result == "a*" || result == "a{0,}");
}

// Test that {1,} is equivalent to +
TEST_F(RegexpToStringTest_228, RepeatOneOrMore_228) {
  std::string result = RoundTrip("a{1,}");
  // May be normalized to a+
  EXPECT_TRUE(result == "a+" || result == "a{1,}");
}

// Test that {0,1} is equivalent to ?
TEST_F(RegexpToStringTest_228, RepeatZeroOrOne_228) {
  std::string result = RoundTrip("a{0,1}");
  // May be normalized to a?
  EXPECT_TRUE(result == "a?" || result == "a{0,1}");
}

}  // namespace re2
