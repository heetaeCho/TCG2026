#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/set.h"
#include "absl/strings/string_view.h"

#include <string>
#include <vector>
#include <memory>

namespace re2 {

class DFATest_448 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to compile a pattern into a Prog
  std::unique_ptr<Regexp, void(*)(Regexp*)> ParseRegexp(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    return std::unique_ptr<Regexp, void(*)(Regexp*)>(re, [](Regexp* r) { if (r) r->Decref(); });
  }
};

// Test basic DFA search via RE2 - simple match
TEST_F(DFATest_448, BasicMatchForward_448) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test DFA search with partial match
TEST_F(DFATest_448, PartialMatch_448) {
  RE2 re("ell");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
  EXPECT_FALSE(RE2::PartialMatch("world", re));
}

// Test DFA with anchored search
TEST_F(DFATest_448, AnchoredSearch_448) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

// Test DFA with empty string
TEST_F(DFATest_448, EmptyStringMatch_448) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
}

// Test DFA with empty pattern on non-empty string
TEST_F(DFATest_448, EmptyPatternPartialMatch_448) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
}

// Test DFA with character class
TEST_F(DFATest_448, CharacterClass_448) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
  EXPECT_FALSE(RE2::FullMatch("123", re));
}

// Test DFA with alternation
TEST_F(DFATest_448, Alternation_448) {
  RE2 re("cat|dog");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_FALSE(RE2::FullMatch("bird", re));
}

// Test DFA with repetition
TEST_F(DFATest_448, Repetition_448) {
  RE2 re("a*b");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("b", re));
  EXPECT_TRUE(RE2::FullMatch("ab", re));
  EXPECT_TRUE(RE2::FullMatch("aaab", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test DFA with complex pattern
TEST_F(DFATest_448, ComplexPattern_448) {
  RE2 re("[0-9]{3}-[0-9]{3}-[0-9]{4}");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("123-456-7890", re));
  EXPECT_FALSE(RE2::FullMatch("123-456-789", re));
  EXPECT_FALSE(RE2::FullMatch("abc-def-ghij", re));
}

// Test DFA search with long input
TEST_F(DFATest_448, LongInput_448) {
  RE2 re("a+b");
  ASSERT_TRUE(re.ok());
  std::string long_input(10000, 'a');
  long_input += 'b';
  EXPECT_TRUE(RE2::FullMatch(long_input, re));
}

// Test DFA with dot-star pattern
TEST_F(DFATest_448, DotStar_448) {
  RE2 re(".*hello.*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("say hello world", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("helo", re));
}

// Test PossibleMatchRange through Prog
TEST_F(DFATest_448, PossibleMatchRange_448) {
  RE2 re("abc[d-f]+");
  ASSERT_TRUE(re.ok());
  std::string min_match, max_match;
  EXPECT_TRUE(re.PossibleMatchRange(&min_match, &max_match, 10));
  // min should be <= "abcd" and max should be >= "abcf..."
  EXPECT_LE(min_match, "abcd");
  EXPECT_GE(max_match, "abcf");
}

// Test PossibleMatchRange with maxlen = 0
TEST_F(DFATest_448, PossibleMatchRangeZeroLen_448) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  std::string min_match, max_match;
  // maxlen of 0 should still work (may return false or trivial range)
  re.PossibleMatchRange(&min_match, &max_match, 0);
}

// Test DFA with small memory limit via RE2::Options
TEST_F(DFATest_448, SmallMemoryLimit_448) {
  RE2::Options opts;
  opts.set_max_mem(256);  // Very small memory
  RE2 re("a+b+c+", opts);
  // Even with small memory, it should still function (may fall back)
  if (re.ok()) {
    // Should still be able to match, potentially falling back to NFA
    EXPECT_TRUE(RE2::FullMatch("abc", re));
  }
}

// Test DFA no match on completely different content
TEST_F(DFATest_448, NoMatch_448) {
  RE2 re("xyz");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::PartialMatch("abcdefg", re));
}

// Test DFA with word boundary
TEST_F(DFATest_448, WordBoundary_448) {
  RE2 re("\\bhello\\b");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("sayhelloworld", re));
}

// Test DFA with multiple matches - first match behavior
TEST_F(DFATest_448, MultipleMatches_448) {
  RE2 re("(cat|concatenate)");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("concatenate", re));
}

// Test DFA with RE2::Set (exercises BuildAllStates indirectly)
TEST_F(DFATest_448, RE2Set_448) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  ASSERT_EQ(s.Add("hello", nullptr), 0);
  ASSERT_EQ(s.Add("world", nullptr), 1);
  ASSERT_TRUE(s.Compile());
  
  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test DFA with unicode characters
TEST_F(DFATest_448, UnicodeMatch_448) {
  RE2 re("café");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("café", re));
  EXPECT_FALSE(RE2::FullMatch("cafe", re));
}

// Test DFA with single character
TEST_F(DFATest_448, SingleCharMatch_448) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
}

// Test DFA with optional group
TEST_F(DFATest_448, OptionalGroup_448) {
  RE2 re("colou?r");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("color", re));
  EXPECT_TRUE(RE2::FullMatch("colour", re));
  EXPECT_FALSE(RE2::FullMatch("colouur", re));
}

// Test DFA PossibleMatchRange with simple pattern
TEST_F(DFATest_448, PossibleMatchRangeSimple_448) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::string min_match, max_match;
  EXPECT_TRUE(re.PossibleMatchRange(&min_match, &max_match, 10));
  EXPECT_LE(min_match, "hello");
  EXPECT_GE(max_match, "hello");
}

// Test DFA with null bytes in content
TEST_F(DFATest_448, NullBytesInContent_448) {
  RE2 re("a\\x00b");
  ASSERT_TRUE(re.ok());
  std::string text = std::string("a\0b", 3);
  EXPECT_TRUE(RE2::FullMatch(text, re));
}

// Test DFA stressed with many alternations
TEST_F(DFATest_448, ManyAlternations_448) {
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    if (i > 0) pattern += "|";
    pattern += "word" + std::to_string(i);
  }
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("word50", re));
  EXPECT_TRUE(RE2::FullMatch("word99", re));
  EXPECT_FALSE(RE2::FullMatch("word100", re));
}

// Test DFA with case-insensitive matching
TEST_F(DFATest_448, CaseInsensitive_448) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

// Test DFA with beginning/end anchors
TEST_F(DFATest_448, Anchors_448) {
  RE2 re("^abc");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("abcdef", re));
  EXPECT_FALSE(RE2::PartialMatch("xabcdef", re));
}

// Test that ok() returns false for invalid regex
TEST_F(DFATest_448, InvalidRegex_448) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
}

// Test DFA with longest match kind through RE2::Set
TEST_F(DFATest_448, LongestMatch_448) {
  RE2::Options opts;
  opts.set_longest_match(true);
  RE2 re("a+", opts);
  ASSERT_TRUE(re.ok());
  
  absl::string_view match;
  EXPECT_TRUE(RE2::PartialMatch("aaaa", re, &match));
  EXPECT_EQ(match, "aaaa");
}

}  // namespace re2
