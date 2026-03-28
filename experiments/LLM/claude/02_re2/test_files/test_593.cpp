#include "re2/set.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include "gtest/gtest.h"

namespace re2 {

class RE2SetTest_593 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic construction with default options and UNANCHORED
TEST_F(RE2SetTest_593, ConstructWithDefaultOptions_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  // Construction should succeed without crashing
}

// Test basic construction with ANCHOR_BOTH
TEST_F(RE2SetTest_593, ConstructWithAnchorBoth_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_BOTH);
}

// Test basic construction with ANCHOR_START
TEST_F(RE2SetTest_593, ConstructWithAnchorStart_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_START);
}

// Test Add returns non-negative index for valid pattern
TEST_F(RE2SetTest_593, AddValidPattern_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("hello", &error);
  EXPECT_GE(index, 0);
}

// Test Add returns -1 for invalid pattern
TEST_F(RE2SetTest_593, AddInvalidPattern_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("[invalid", &error);
  EXPECT_EQ(index, -1);
  EXPECT_FALSE(error.empty());
}

// Test Add multiple valid patterns returns increasing indices
TEST_F(RE2SetTest_593, AddMultiplePatterns_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int idx0 = s.Add("foo", &error);
  int idx1 = s.Add("bar", &error);
  int idx2 = s.Add("baz", &error);
  EXPECT_EQ(idx0, 0);
  EXPECT_EQ(idx1, 1);
  EXPECT_EQ(idx2, 2);
}

// Test Compile succeeds with valid patterns
TEST_F(RE2SetTest_593, CompileSucceeds_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  EXPECT_TRUE(s.Compile());
}

// Test Compile succeeds with no patterns (empty set)
TEST_F(RE2SetTest_593, CompileEmptySet_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  EXPECT_TRUE(s.Compile());
}

// Test Match finds matching pattern
TEST_F(RE2SetTest_593, MatchFindsPattern_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  s.Add("bar", &error);
  s.Add("baz", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foo", &matches));
  ASSERT_FALSE(matches.empty());
  EXPECT_EQ(matches[0], 0);
}

// Test Match returns false when no pattern matches
TEST_F(RE2SetTest_593, MatchNoMatch_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  s.Add("bar", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("xyz", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test Match with multiple matching patterns
TEST_F(RE2SetTest_593, MatchMultiplePatterns_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("fo.", &error);
  s.Add("foo", &error);
  s.Add("bar", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foo", &matches));
  // Both pattern 0 ("fo.") and pattern 1 ("foo") should match
  EXPECT_GE(matches.size(), 2u);
  // Check that indices 0 and 1 are present
  bool found0 = false, found1 = false;
  for (int idx : matches) {
    if (idx == 0) found0 = true;
    if (idx == 1) found1 = true;
  }
  EXPECT_TRUE(found0);
  EXPECT_TRUE(found1);
}

// Test Match with null vector (just check if any match exists)
TEST_F(RE2SetTest_593, MatchWithNullVector_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  EXPECT_TRUE(s.Match("hello world", nullptr));
  EXPECT_FALSE(s.Match("xyz", nullptr));
}

// Test Match on empty set returns false
TEST_F(RE2SetTest_593, MatchEmptySet_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("anything", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test ANCHOR_BOTH requires full match
TEST_F(RE2SetTest_593, AnchorBothFullMatch_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_BOTH);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foo", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  EXPECT_FALSE(s.Match("foobar", &matches));
  EXPECT_TRUE(matches.empty());

  matches.clear();
  EXPECT_FALSE(s.Match("barfoo", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test UNANCHORED matches substring
TEST_F(RE2SetTest_593, UnanchoredMatchesSubstring_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("barfoobar", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test Match with empty string
TEST_F(RE2SetTest_593, MatchEmptyString_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("", &matches));
}

// Test Match with pattern that matches empty string
TEST_F(RE2SetTest_593, MatchPatternMatchesEmptyString_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add(".*", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test Move constructor
TEST_F(RE2SetTest_593, MoveConstructor_593) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(std::move(s1));

  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello world", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test Move assignment operator
TEST_F(RE2SetTest_593, MoveAssignment_593) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(options, RE2::UNANCHORED);
  s2 = std::move(s1);

  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello world", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test Add with error parameter as nullptr (pattern valid)
TEST_F(RE2SetTest_593, AddWithNullError_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  int index = s.Add("valid", nullptr);
  EXPECT_GE(index, 0);
}

// Test Add with error parameter as nullptr (pattern invalid)
TEST_F(RE2SetTest_593, AddInvalidWithNullError_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  int index = s.Add("[invalid", nullptr);
  EXPECT_EQ(index, -1);
}

// Test Match with ErrorInfo overload
TEST_F(RE2SetTest_593, MatchWithErrorInfo_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  EXPECT_TRUE(s.Match("hello", &matches, &error_info));
  EXPECT_FALSE(matches.empty());
}

// Test that Add after Compile fails or behaves correctly
// (Cannot add patterns after compilation)
TEST_F(RE2SetTest_593, AddAfterCompile_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  // Adding after compile should return -1
  int index = s.Add("bar", &error);
  EXPECT_EQ(index, -1);
}

// Test regex patterns with special characters
TEST_F(RE2SetTest_593, SpecialRegexPatterns_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  EXPECT_GE(s.Add("a+b*c?", &error), 0);
  EXPECT_GE(s.Add("\\d+", &error), 0);
  EXPECT_GE(s.Add("[a-z]+", &error), 0);
  EXPECT_GE(s.Add("(foo|bar)", &error), 0);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("abc", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test with case-insensitive option
TEST_F(RE2SetTest_593, CaseInsensitiveOption_593) {
  RE2::Options options;
  options.set_case_sensitive(false);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("HELLO", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test with literal option
TEST_F(RE2SetTest_593, LiteralOption_593) {
  RE2::Options options;
  options.set_literal(true);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  // With literal mode, "a+b" should be treated as literal string
  s.Add("a+b", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("a+b", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  // "aab" should NOT match since "a+b" is literal
  EXPECT_FALSE(s.Match("aab", &matches));
}

// Test ANCHOR_START
TEST_F(RE2SetTest_593, AnchorStartMatch_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_START);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foobar", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  EXPECT_FALSE(s.Match("barfoo", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test with large number of patterns
TEST_F(RE2SetTest_593, ManyPatterns_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;

  for (int i = 0; i < 100; i++) {
    std::string pattern = "pattern" + std::to_string(i);
    int idx = s.Add(pattern, &error);
    EXPECT_EQ(idx, i);
  }
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("pattern50", &matches));
  bool found50 = false;
  for (int idx : matches) {
    if (idx == 50) found50 = true;
  }
  EXPECT_TRUE(found50);
}

// Test Match before Compile returns false
TEST_F(RE2SetTest_593, MatchBeforeCompile_593) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);

  // Match before compile should return false
  std::vector<int> matches;
  EXPECT_FALSE(s.Match("foo", &matches));
}

// Test never_capture is set in options
TEST_F(RE2SetTest_593, NeverCaptureIsSet_593) {
  // This tests that the constructor sets never_capture to true
  // We verify indirectly: patterns with captures should still work
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int idx = s.Add("(foo)(bar)", &error);
  EXPECT_GE(idx, 0);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foobar", &matches));
  EXPECT_FALSE(matches.empty());
}

}  // namespace re2
