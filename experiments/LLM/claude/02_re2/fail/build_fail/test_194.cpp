#include <string>
#include "gtest/gtest.h"
#include "util/pcre.h"
#include "absl/strings/string_view.h"

namespace re2 {

class PCREGlobalReplaceTest_194 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Normal operation: simple replacement of a single occurrence
TEST_F(PCREGlobalReplaceTest_194, SingleOccurrenceReplacement_194) {
  std::string str = "hello world";
  PCRE pattern("world");
  int count = PCRE::GlobalReplace(&str, pattern, "there");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "hello there");
}

// Normal operation: multiple occurrences replaced
TEST_F(PCREGlobalReplaceTest_194, MultipleOccurrencesReplacement_194) {
  std::string str = "aaa";
  PCRE pattern("a");
  int count = PCRE::GlobalReplace(&str, pattern, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

// No match: pattern not found in string
TEST_F(PCREGlobalReplaceTest_194, NoMatchReturnsZero_194) {
  std::string str = "hello world";
  PCRE pattern("xyz");
  int count = PCRE::GlobalReplace(&str, pattern, "replaced");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello world");
}

// Boundary: empty string input
TEST_F(PCREGlobalReplaceTest_194, EmptyStringInput_194) {
  std::string str = "";
  PCRE pattern("a");
  int count = PCRE::GlobalReplace(&str, pattern, "b");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "");
}

// Boundary: pattern that matches empty string
TEST_F(PCREGlobalReplaceTest_194, EmptyPatternMatch_194) {
  std::string str = "ab";
  PCRE pattern("");
  int count = PCRE::GlobalReplace(&str, pattern, "X");
  // Empty pattern matches at each position, including start and after each char
  // Expected: "XaXbX" with count=3
  EXPECT_GE(count, 1);
  // The string should have X inserted at boundaries
}

// Normal: replacement with capture group reference
TEST_F(PCREGlobalReplaceTest_194, ReplacementWithCaptureGroup_194) {
  std::string str = "hello world";
  PCRE pattern("(\\w+)");
  int count = PCRE::GlobalReplace(&str, pattern, "[\\1]");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "[hello] [world]");
}

// Normal: replace all digits
TEST_F(PCREGlobalReplaceTest_194, ReplaceAllDigits_194) {
  std::string str = "a1b2c3";
  PCRE pattern("\\d");
  int count = PCRE::GlobalReplace(&str, pattern, "#");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "a#b#c#");
}

// Normal: replace with empty rewrite (deletion)
TEST_F(PCREGlobalReplaceTest_194, ReplaceWithEmptyRewrite_194) {
  std::string str = "a1b2c3";
  PCRE pattern("\\d");
  int count = PCRE::GlobalReplace(&str, pattern, "");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "abc");
}

// Boundary: entire string matches
TEST_F(PCREGlobalReplaceTest_194, EntireStringMatches_194) {
  std::string str = "hello";
  PCRE pattern("hello");
  int count = PCRE::GlobalReplace(&str, pattern, "bye");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "bye");
}

// Normal: overlapping potential matches (greedy)
TEST_F(PCREGlobalReplaceTest_194, GreedyMatching_194) {
  std::string str = "aaa";
  PCRE pattern("aa");
  int count = PCRE::GlobalReplace(&str, pattern, "b");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "ba");
}

// Normal: pattern at beginning
TEST_F(PCREGlobalReplaceTest_194, PatternAtBeginning_194) {
  std::string str = "abc def";
  PCRE pattern("abc");
  int count = PCRE::GlobalReplace(&str, pattern, "xyz");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "xyz def");
}

// Normal: pattern at end
TEST_F(PCREGlobalReplaceTest_194, PatternAtEnd_194) {
  std::string str = "abc def";
  PCRE pattern("def");
  int count = PCRE::GlobalReplace(&str, pattern, "xyz");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "abc xyz");
}

// Boundary: single character string, matches
TEST_F(PCREGlobalReplaceTest_194, SingleCharStringMatches_194) {
  std::string str = "a";
  PCRE pattern("a");
  int count = PCRE::GlobalReplace(&str, pattern, "b");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "b");
}

// Boundary: single character string, no match
TEST_F(PCREGlobalReplaceTest_194, SingleCharStringNoMatch_194) {
  std::string str = "a";
  PCRE pattern("b");
  int count = PCRE::GlobalReplace(&str, pattern, "c");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "a");
}

// Normal: replacement longer than original match
TEST_F(PCREGlobalReplaceTest_194, ReplacementLongerThanMatch_194) {
  std::string str = "ab";
  PCRE pattern("a");
  int count = PCRE::GlobalReplace(&str, pattern, "xyz");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "xyzb");
}

// Normal: replacement shorter than original match
TEST_F(PCREGlobalReplaceTest_194, ReplacementShorterThanMatch_194) {
  std::string str = "abcabc";
  PCRE pattern("abc");
  int count = PCRE::GlobalReplace(&str, pattern, "x");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "xx");
}

// Test Replace (single replacement)
TEST_F(PCREGlobalReplaceTest_194, ReplaceFirstOccurrence_194) {
  std::string str = "aaa";
  PCRE pattern("a");
  bool result = PCRE::Replace(&str, pattern, "b");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "baa");
}

// Test Replace with no match
TEST_F(PCREGlobalReplaceTest_194, ReplaceNoMatch_194) {
  std::string str = "hello";
  PCRE pattern("xyz");
  bool result = PCRE::Replace(&str, pattern, "abc");
  EXPECT_FALSE(result);
  EXPECT_EQ(str, "hello");
}

// Test Extract
TEST_F(PCREGlobalReplaceTest_194, ExtractBasic_194) {
  std::string out;
  PCRE pattern("(\\w+)@(\\w+)");
  bool result = PCRE::Extract("user@host", pattern, "\\1 at \\2", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "user at host");
}

// Test Extract with no match
TEST_F(PCREGlobalReplaceTest_194, ExtractNoMatch_194) {
  std::string out;
  PCRE pattern("(\\d+)");
  bool result = PCRE::Extract("hello", pattern, "\\1", &out);
  EXPECT_FALSE(result);
}

// Test QuoteMeta
TEST_F(PCREGlobalReplaceTest_194, QuoteMetaSpecialChars_194) {
  std::string quoted = PCRE::QuoteMeta("a.b*c?d");
  // The quoted string should be safe to use as a literal pattern
  PCRE pattern(quoted);
  std::string str = "a.b*c?d";
  int count = PCRE::GlobalReplace(&str, pattern, "X");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "X");
}

// Test QuoteMeta on plain string
TEST_F(PCREGlobalReplaceTest_194, QuoteMetaPlainString_194) {
  std::string quoted = PCRE::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

// Test NumberOfCapturingGroups
TEST_F(PCREGlobalReplaceTest_194, NumberOfCapturingGroups_194) {
  PCRE pattern("(a)(b)(c)");
  EXPECT_EQ(pattern.NumberOfCapturingGroups(), 3);
}

TEST_F(PCREGlobalReplaceTest_194, NumberOfCapturingGroupsZero_194) {
  PCRE pattern("abc");
  EXPECT_EQ(pattern.NumberOfCapturingGroups(), 0);
}

// Test CheckRewriteString
TEST_F(PCREGlobalReplaceTest_194, CheckRewriteStringValid_194) {
  PCRE pattern("(a)(b)");
  std::string error;
  bool result = pattern.CheckRewriteString("\\1-\\2", &error);
  EXPECT_TRUE(result);
}

TEST_F(PCREGlobalReplaceTest_194, CheckRewriteStringInvalid_194) {
  PCRE pattern("(a)");
  std::string error;
  bool result = pattern.CheckRewriteString("\\2", &error);
  EXPECT_FALSE(result);
  EXPECT_FALSE(error.empty());
}

// Test pattern accessor
TEST_F(PCREGlobalReplaceTest_194, PatternAccessor_194) {
  PCRE pattern("hello.*world");
  EXPECT_EQ(pattern.pattern(), "hello.*world");
}

// Test GlobalReplace with special regex characters in replacement
TEST_F(PCREGlobalReplaceTest_194, GlobalReplaceSpecialCharsInText_194) {
  std::string str = "foo.bar.baz";
  PCRE pattern("\\.");
  int count = PCRE::GlobalReplace(&str, pattern, "-");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "foo-bar-baz");
}

// Test consecutive matches
TEST_F(PCREGlobalReplaceTest_194, ConsecutiveMatches_194) {
  std::string str = "abab";
  PCRE pattern("ab");
  int count = PCRE::GlobalReplace(&str, pattern, "c");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "cc");
}

// Test DoMatch basic
TEST_F(PCREGlobalReplaceTest_194, DoMatchBasic_194) {
  PCRE pattern("hello");
  bool result = pattern.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCREGlobalReplaceTest_194, DoMatchNoMatch_194) {
  PCRE pattern("xyz");
  bool result = pattern.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_FALSE(result);
}

TEST_F(PCREGlobalReplaceTest_194, DoMatchAnchored_194) {
  PCRE pattern("hello");
  bool result = pattern.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCREGlobalReplaceTest_194, DoMatchAnchoredFail_194) {
  PCRE pattern("world");
  bool result = pattern.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0);
  EXPECT_FALSE(result);
}

}  // namespace re2
