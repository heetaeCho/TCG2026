#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

class GlobalReplaceTest_257 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset global replace count limit before each test
    RE2::FUZZING_ONLY_set_maximum_global_replace_count(-1);
  }

  void TearDown() override {
    RE2::FUZZING_ONLY_set_maximum_global_replace_count(-1);
  }
};

// Test basic global replacement with a simple pattern
TEST_F(GlobalReplaceTest_257, BasicReplacement_257) {
  std::string s = "yabba dabba doo";
  int count = RE2::GlobalReplace(&s, RE2("b"), "d");
  EXPECT_EQ(count, 4);
  EXPECT_EQ(s, "yadda dadda doo");
}

// Test when no match is found, string should remain unchanged
TEST_F(GlobalReplaceTest_257, NoMatchReturnsZero_257) {
  std::string s = "hello world";
  int count = RE2::GlobalReplace(&s, RE2("xyz"), "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello world");
}

// Test replacing all characters with empty string
TEST_F(GlobalReplaceTest_257, ReplaceWithEmptyString_257) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, RE2("a"), "");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "");
}

// Test replacing empty match (zero-width) pattern
TEST_F(GlobalReplaceTest_257, ZeroWidthMatch_257) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, RE2(""), "-");
  // Empty pattern matches at every position (before each char and at end)
  EXPECT_GT(count, 0);
  // Each position between characters (and at start/end) gets a "-"
  EXPECT_EQ(s, "-a-b-c-");
}

// Test replacement with capture groups
TEST_F(GlobalReplaceTest_257, ReplacementWithCaptureGroups_257) {
  std::string s = "foo bar baz";
  int count = RE2::GlobalReplace(&s, RE2("(\\w+)"), "[\\1]");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "[foo] [bar] [baz]");
}

// Test replacement on an empty string
TEST_F(GlobalReplaceTest_257, EmptyInputString_257) {
  std::string s = "";
  int count = RE2::GlobalReplace(&s, RE2("a"), "b");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "");
}

// Test empty pattern on empty string
TEST_F(GlobalReplaceTest_257, EmptyPatternOnEmptyString_257) {
  std::string s = "";
  int count = RE2::GlobalReplace(&s, RE2(""), "x");
  // Empty pattern should match once at start/end of empty string
  EXPECT_GE(count, 1);
}

// Test replacing with a single character
TEST_F(GlobalReplaceTest_257, SingleCharacterReplacement_257) {
  std::string s = "aabbcc";
  int count = RE2::GlobalReplace(&s, RE2("a"), "x");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "xxbbcc");
}

// Test replacing all occurrences of a multi-character pattern
TEST_F(GlobalReplaceTest_257, MultiCharPattern_257) {
  std::string s = "abcabcabc";
  int count = RE2::GlobalReplace(&s, RE2("abc"), "XY");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "XYXYXY");
}

// Test with a pattern that matches the entire string
TEST_F(GlobalReplaceTest_257, PatternMatchesEntireString_257) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, RE2("hello"), "world");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(s, "world");
}

// Test that maximum_global_replace_count limits replacements
TEST_F(GlobalReplaceTest_257, MaximumGlobalReplaceCountLimitsReplacements_257) {
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(2);
  std::string s = "aaaa";
  int count = RE2::GlobalReplace(&s, RE2("a"), "b");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "bbaa");
}

// Test maximum_global_replace_count set to 0 means no replacements
TEST_F(GlobalReplaceTest_257, MaximumGlobalReplaceCountZero_257) {
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(0);
  std::string s = "aaaa";
  int count = RE2::GlobalReplace(&s, RE2("a"), "b");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "aaaa");
}

// Test maximum_global_replace_count set to 1
TEST_F(GlobalReplaceTest_257, MaximumGlobalReplaceCountOne_257) {
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(1);
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, RE2("a"), "b");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(s, "baa");
}

// Test with rewrite referencing more groups than pattern has
TEST_F(GlobalReplaceTest_257, RewriteExceedsCapturingGroups_257) {
  std::string s = "hello";
  // Pattern has 0 capturing groups but rewrite references \1
  int count = RE2::GlobalReplace(&s, RE2("hello"), "\\1");
  // Should return false (0) since nvec > 1 + NumberOfCapturingGroups
  EXPECT_EQ(count, 0);
  // The string might or might not be modified depending on implementation
}

// Test replacement with multiple capture groups
TEST_F(GlobalReplaceTest_257, MultipleCaptureGroups_257) {
  std::string s = "12-34 56-78";
  int count = RE2::GlobalReplace(&s, RE2("(\\d+)-(\\d+)"), "\\2-\\1");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "34-12 78-56");
}

// Test with overlapping matches - greedy
TEST_F(GlobalReplaceTest_257, GreedyMatching_257) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, RE2("a+"), "b");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(s, "b");
}

// Test replacement preserves non-matching parts
TEST_F(GlobalReplaceTest_257, PreservesNonMatchingParts_257) {
  std::string s = "hello world hello";
  int count = RE2::GlobalReplace(&s, RE2("hello"), "hi");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "hi world hi");
}

// Test with special regex characters in replacement
TEST_F(GlobalReplaceTest_257, SpecialCharsInReplacement_257) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, RE2("b"), "\\0");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(s, "abc");  // \0 refers to the whole match
}

// Test with alternation pattern
TEST_F(GlobalReplaceTest_257, AlternationPattern_257) {
  std::string s = "cat and dog";
  int count = RE2::GlobalReplace(&s, RE2("cat|dog"), "pet");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "pet and pet");
}

// Test with dot pattern
TEST_F(GlobalReplaceTest_257, DotPattern_257) {
  std::string s = "abc";
  int count = RE2::GlobalReplace(&s, RE2("."), "x");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "xxx");
}

// Test with character class pattern
TEST_F(GlobalReplaceTest_257, CharacterClassPattern_257) {
  std::string s = "a1b2c3";
  int count = RE2::GlobalReplace(&s, RE2("[0-9]"), "#");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "a#b#c#");
}

// Test with Unicode/UTF-8 content
TEST_F(GlobalReplaceTest_257, UTF8Content_257) {
  std::string s = "café café";
  int count = RE2::GlobalReplace(&s, RE2("café"), "coffee");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "coffee coffee");
}

// Test replacement where result is longer than original
TEST_F(GlobalReplaceTest_257, ReplacementLongerThanMatch_257) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, RE2("a"), "xyz");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "xyzxyzxyz");
}

// Test replacement where result is shorter than original
TEST_F(GlobalReplaceTest_257, ReplacementShorterThanMatch_257) {
  std::string s = "abcabcabc";
  int count = RE2::GlobalReplace(&s, RE2("abc"), "x");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "xxx");
}

// Test with Latin1 encoding option
TEST_F(GlobalReplaceTest_257, Latin1Encoding_257) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("a", opts);
  std::string s = "banana";
  int count = RE2::GlobalReplace(&s, re, "o");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "bonono");
}

// Test adjacent matches
TEST_F(GlobalReplaceTest_257, AdjacentMatches_257) {
  std::string s = "aabb";
  int count = RE2::GlobalReplace(&s, RE2("a|b"), "x");
  EXPECT_EQ(count, 4);
  EXPECT_EQ(s, "xxxx");
}

// Test with a pattern that can match empty at end of string
TEST_F(GlobalReplaceTest_257, OptionalPatternMatchesEmptyAtEnd_257) {
  std::string s = "ab";
  int count = RE2::GlobalReplace(&s, RE2("a*"), "x");
  // "a*" matches "a" at pos 0, "" at pos 1 (skip 'b'), "" at pos 2
  EXPECT_GT(count, 0);
}

// Test resetting maximum global replace count to unlimited (-1)
TEST_F(GlobalReplaceTest_257, ResetMaximumGlobalReplaceCount_257) {
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(1);
  RE2::FUZZING_ONLY_set_maximum_global_replace_count(-1);
  std::string s = "aaaa";
  int count = RE2::GlobalReplace(&s, RE2("a"), "b");
  EXPECT_EQ(count, 4);
  EXPECT_EQ(s, "bbbb");
}

// Test invalid regex pattern
TEST_F(GlobalReplaceTest_257, InvalidRegexPattern_257) {
  RE2 re("(unclosed");
  std::string s = "hello";
  EXPECT_FALSE(re.ok());
  // With invalid regex, Match should fail, so count should be 0
  int count = RE2::GlobalReplace(&s, re, "x");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

// Test pattern with word boundary-like behavior using \b
TEST_F(GlobalReplaceTest_257, WordBoundaryPattern_257) {
  std::string s = "foo bar foobar";
  int count = RE2::GlobalReplace(&s, RE2("\\bfoo\\b"), "baz");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(s, "baz bar foobar");
}

// Test with newline in string
TEST_F(GlobalReplaceTest_257, NewlineInString_257) {
  std::string s = "hello\nworld\nhello";
  int count = RE2::GlobalReplace(&s, RE2("hello"), "hi");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "hi\nworld\nhi");
}

}  // namespace re2
