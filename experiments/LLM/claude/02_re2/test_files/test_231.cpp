#include "re2/set.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <memory>
#include "gtest/gtest.h"

namespace re2 {

class RE2SetTest_231 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic construction with default options and UNANCHORED
TEST_F(RE2SetTest_231, ConstructWithDefaultOptions_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  // Just verify it doesn't crash
}

// Test basic construction with ANCHOR_BOTH
TEST_F(RE2SetTest_231, ConstructWithAnchorBoth_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_BOTH);
}

// Test Add with a valid pattern
TEST_F(RE2SetTest_231, AddValidPattern_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("hello", &error);
  EXPECT_EQ(index, 0);
}

// Test Add multiple valid patterns
TEST_F(RE2SetTest_231, AddMultipleValidPatterns_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  EXPECT_EQ(s.Add("hello", &error), 0);
  EXPECT_EQ(s.Add("world", &error), 1);
  EXPECT_EQ(s.Add("foo", &error), 2);
}

// Test Add with an invalid pattern
TEST_F(RE2SetTest_231, AddInvalidPattern_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("[invalid", &error);
  EXPECT_EQ(index, -1);
  EXPECT_FALSE(error.empty());
}

// Test Compile with no patterns
TEST_F(RE2SetTest_231, CompileEmpty_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  bool compiled = s.Compile();
  EXPECT_TRUE(compiled);
}

// Test Compile with valid patterns
TEST_F(RE2SetTest_231, CompileWithPatterns_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  bool compiled = s.Compile();
  EXPECT_TRUE(compiled);
}

// Test Match with a matching pattern (UNANCHORED)
TEST_F(RE2SetTest_231, MatchSinglePattern_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool matched = s.Match("say hello world", &matches);
  EXPECT_TRUE(matched);
  ASSERT_EQ(matches.size(), 1);
  EXPECT_EQ(matches[0], 0);
}

// Test Match with no matching pattern
TEST_F(RE2SetTest_231, MatchNoMatch_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool matched = s.Match("goodbye", &matches);
  EXPECT_FALSE(matched);
  EXPECT_TRUE(matches.empty());
}

// Test Match with multiple matching patterns
TEST_F(RE2SetTest_231, MatchMultiplePatterns_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool matched = s.Match("hello world", &matches);
  EXPECT_TRUE(matched);
  EXPECT_GE(matches.size(), 1u);

  // Both "hello" and "world" should match
  bool found_hello = false, found_world = false;
  for (int idx : matches) {
    if (idx == 0) found_hello = true;
    if (idx == 1) found_world = true;
  }
  EXPECT_TRUE(found_hello);
  EXPECT_TRUE(found_world);
}

// Test Match with ANCHOR_BOTH - full match required
TEST_F(RE2SetTest_231, MatchAnchorBoth_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_BOTH);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  // Exact match should work
  EXPECT_TRUE(s.Match("hello", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  // Partial match should not work with ANCHOR_BOTH
  EXPECT_FALSE(s.Match("say hello", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test Match with nullptr vector
TEST_F(RE2SetTest_231, MatchWithNullVector_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  bool matched = s.Match("hello", nullptr);
  EXPECT_TRUE(matched);
}

// Test Match with empty text
TEST_F(RE2SetTest_231, MatchEmptyText_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool matched = s.Match("", &matches);
  EXPECT_FALSE(matched);
}

// Test Match with empty text and pattern that matches empty
TEST_F(RE2SetTest_231, MatchEmptyTextWithEmptyPattern_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add(".*", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool matched = s.Match("", &matches);
  EXPECT_TRUE(matched);
}

// Test Match with ErrorInfo overload
TEST_F(RE2SetTest_231, MatchWithErrorInfo_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  bool matched = s.Match("hello world", &matches, &error_info);
  EXPECT_TRUE(matched);
  EXPECT_FALSE(matches.empty());
}

// Test move constructor
TEST_F(RE2SetTest_231, MoveConstructor_231) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  s1.Add("world", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(std::move(s1));

  std::vector<int> matches;
  bool matched = s2.Match("hello", &matches);
  EXPECT_TRUE(matched);
  EXPECT_FALSE(matches.empty());
}

// Test move assignment operator
TEST_F(RE2SetTest_231, MoveAssignment_231) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  s1.Add("world", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(options, RE2::UNANCHORED);
  s2 = std::move(s1);

  std::vector<int> matches;
  bool matched = s2.Match("hello", &matches);
  EXPECT_TRUE(matched);
  EXPECT_FALSE(matches.empty());
}

// Test regex patterns
TEST_F(RE2SetTest_231, RegexPatternMatch_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("\\d+", &error);   // matches digits
  s.Add("[a-z]+", &error);  // matches lowercase letters
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool matched = s.Match("abc123", &matches);
  EXPECT_TRUE(matched);
  EXPECT_GE(matches.size(), 2u);
}

// Test case-insensitive matching
TEST_F(RE2SetTest_231, CaseInsensitiveMatch_231) {
  RE2::Options options;
  options.set_case_sensitive(false);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool matched = s.Match("HELLO", &matches);
  EXPECT_TRUE(matched);
  EXPECT_FALSE(matches.empty());
}

// Test Add after Compile should fail
TEST_F(RE2SetTest_231, AddAfterCompile_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  // Adding after Compile should return -1
  int index = s.Add("world", &error);
  EXPECT_EQ(index, -1);
}

// Test Match before Compile
TEST_F(RE2SetTest_231, MatchBeforeCompile_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);

  std::vector<int> matches;
  // Matching before compile should return false
  bool matched = s.Match("hello", &matches);
  EXPECT_FALSE(matched);
}

// Test with ANCHOR_START
TEST_F(RE2SetTest_231, MatchAnchorStart_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_START);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  EXPECT_FALSE(s.Match("say hello", &matches));
}

// Test with many patterns
TEST_F(RE2SetTest_231, ManyPatterns_231) {
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
  bool matched = s.Match("this contains pattern42 in it", &matches);
  EXPECT_TRUE(matched);

  bool found42 = false;
  for (int idx : matches) {
    if (idx == 42) found42 = true;
  }
  EXPECT_TRUE(found42);
}

// Test Add with null error string
TEST_F(RE2SetTest_231, AddWithNullError_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  int index = s.Add("hello", nullptr);
  EXPECT_EQ(index, 0);
}

// Test alternation pattern
TEST_F(RE2SetTest_231, AlternationPattern_231) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("cat|dog", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("I have a cat", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  EXPECT_TRUE(s.Match("I have a dog", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  EXPECT_FALSE(s.Match("I have a fish", &matches));
}

}  // namespace re2
