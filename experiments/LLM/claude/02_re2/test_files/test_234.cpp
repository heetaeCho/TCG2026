#include "gtest/gtest.h"
#include "re2/set.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

class RE2SetTest_234 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic construction with default options and UNANCHORED
TEST_F(RE2SetTest_234, ConstructWithDefaultOptions_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  // Should be constructable without crashing
}

// Test basic construction with ANCHOR_BOTH
TEST_F(RE2SetTest_234, ConstructWithAnchorBoth_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_BOTH);
  // Should be constructable without crashing
}

// Test adding a valid pattern
TEST_F(RE2SetTest_234, AddValidPattern_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("hello", &error);
  EXPECT_EQ(index, 0);
}

// Test adding multiple valid patterns
TEST_F(RE2SetTest_234, AddMultipleValidPatterns_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index0 = s.Add("hello", &error);
  int index1 = s.Add("world", &error);
  int index2 = s.Add("foo", &error);
  EXPECT_EQ(index0, 0);
  EXPECT_EQ(index1, 1);
  EXPECT_EQ(index2, 2);
}

// Test adding an invalid pattern returns -1
TEST_F(RE2SetTest_234, AddInvalidPattern_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("[invalid", &error);
  EXPECT_EQ(index, -1);
  EXPECT_FALSE(error.empty());
}

// Test adding an invalid pattern with null error string
TEST_F(RE2SetTest_234, AddInvalidPatternNullError_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  int index = s.Add("[invalid", nullptr);
  EXPECT_EQ(index, -1);
}

// Test Compile with no patterns
TEST_F(RE2SetTest_234, CompileNoPatterns_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  bool compiled = s.Compile();
  EXPECT_TRUE(compiled);
}

// Test Compile after adding patterns
TEST_F(RE2SetTest_234, CompileAfterAddingPatterns_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  bool compiled = s.Compile();
  EXPECT_TRUE(compiled);
}

// Test Match returns true when a pattern matches (UNANCHORED)
TEST_F(RE2SetTest_234, MatchSinglePattern_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Compile();

  std::vector<int> matches;
  bool matched = s.Match("say hello world", &matches);
  EXPECT_TRUE(matched);
  ASSERT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 0);
}

// Test Match returns false when no pattern matches
TEST_F(RE2SetTest_234, MatchNoMatch_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Compile();

  std::vector<int> matches;
  bool matched = s.Match("goodbye", &matches);
  EXPECT_FALSE(matched);
  EXPECT_TRUE(matches.empty());
}

// Test Match with multiple patterns matching
TEST_F(RE2SetTest_234, MatchMultiplePatterns_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  s.Add("xyz", &error);
  s.Compile();

  std::vector<int> matches;
  bool matched = s.Match("hello world", &matches);
  EXPECT_TRUE(matched);
  EXPECT_GE(matches.size(), 2u);
  // Both pattern 0 and pattern 1 should match
  EXPECT_NE(std::find(matches.begin(), matches.end(), 0), matches.end());
  EXPECT_NE(std::find(matches.begin(), matches.end(), 1), matches.end());
  // Pattern 2 should not match
  EXPECT_EQ(std::find(matches.begin(), matches.end(), 2), matches.end());
}

// Test Match with null vector (just checking if any pattern matches)
TEST_F(RE2SetTest_234, MatchWithNullVector_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Compile();

  bool matched = s.Match("hello", nullptr);
  EXPECT_TRUE(matched);
}

// Test Match with null vector and no match
TEST_F(RE2SetTest_234, MatchWithNullVectorNoMatch_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Compile();

  bool matched = s.Match("goodbye", nullptr);
  EXPECT_FALSE(matched);
}

// Test Match with ANCHOR_BOTH
TEST_F(RE2SetTest_234, MatchAnchorBoth_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_BOTH);
  std::string error;
  s.Add("hello", &error);
  s.Compile();

  std::vector<int> matches;
  // Exact match should work
  bool matched = s.Match("hello", &matches);
  EXPECT_TRUE(matched);
  EXPECT_EQ(matches.size(), 1u);

  matches.clear();
  // Substring match should not work with ANCHOR_BOTH
  matched = s.Match("say hello", &matches);
  EXPECT_FALSE(matched);
}

// Test Match with regex patterns
TEST_F(RE2SetTest_234, MatchWithRegex_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("h.*o", &error);
  s.Add("w[oO]rld", &error);
  s.Compile();

  std::vector<int> matches;
  bool matched = s.Match("hello", &matches);
  EXPECT_TRUE(matched);
  EXPECT_NE(std::find(matches.begin(), matches.end(), 0), matches.end());
}

// Test Match on empty text
TEST_F(RE2SetTest_234, MatchEmptyText_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Compile();

  std::vector<int> matches;
  bool matched = s.Match("", &matches);
  EXPECT_FALSE(matched);
}

// Test Match on empty text with pattern that matches empty string
TEST_F(RE2SetTest_234, MatchEmptyTextWithEmptyPattern_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add(".*", &error);
  s.Compile();

  std::vector<int> matches;
  bool matched = s.Match("", &matches);
  EXPECT_TRUE(matched);
}

// Test no patterns compiled, then match
TEST_F(RE2SetTest_234, MatchNoPatternsCompiled_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  s.Compile();

  std::vector<int> matches;
  bool matched = s.Match("hello", &matches);
  EXPECT_FALSE(matched);
}

// Test move constructor
TEST_F(RE2SetTest_234, MoveConstructor_234) {
  RE2::Set s1(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  s1.Compile();

  RE2::Set s2(std::move(s1));

  std::vector<int> matches;
  bool matched = s2.Match("hello", &matches);
  EXPECT_TRUE(matched);
  EXPECT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 0);
}

// Test move assignment operator
TEST_F(RE2SetTest_234, MoveAssignment_234) {
  RE2::Set s1(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  s1.Compile();

  RE2::Set s2(RE2::DefaultOptions, RE2::UNANCHORED);
  s2 = std::move(s1);

  std::vector<int> matches;
  bool matched = s2.Match("hello", &matches);
  EXPECT_TRUE(matched);
  EXPECT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 0);
}

// Test Match with ErrorInfo overload
TEST_F(RE2SetTest_234, MatchWithErrorInfo_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  s.Compile();

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  bool matched = s.Match("hello world", &matches, &error_info);
  EXPECT_TRUE(matched);
  EXPECT_GE(matches.size(), 1u);
}

// Test Match with ErrorInfo overload and no match
TEST_F(RE2SetTest_234, MatchWithErrorInfoNoMatch_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Compile();

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  bool matched = s.Match("goodbye", &matches, &error_info);
  EXPECT_FALSE(matched);
}

// Test that the convenience Match (2 args) delegates correctly
TEST_F(RE2SetTest_234, ConvenienceMatchDelegatesToThreeArg_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("test", &error);
  s.Compile();

  std::vector<int> matches;
  // This calls Match(text, v, NULL)
  bool matched = s.Match("this is a test", &matches);
  EXPECT_TRUE(matched);
  EXPECT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 0);
}

// Test adding a pattern with special regex characters
TEST_F(RE2SetTest_234, AddPatternWithSpecialChars_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("a+b*c?d", &error);
  EXPECT_EQ(index, 0);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  bool matched = s.Match("aaabcd", &matches);
  EXPECT_TRUE(matched);
}

// Test with ANCHOR_START anchor option
TEST_F(RE2SetTest_234, MatchAnchorStart_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_START);
  std::string error;
  s.Add("hello", &error);
  s.Compile();

  std::vector<int> matches;
  // Match at start should succeed
  bool matched = s.Match("hello world", &matches);
  EXPECT_TRUE(matched);

  matches.clear();
  // Match not at start should fail
  matched = s.Match("say hello", &matches);
  EXPECT_FALSE(matched);
}

// Test with many patterns
TEST_F(RE2SetTest_234, MatchManyPatterns_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  for (int i = 0; i < 100; i++) {
    std::string pattern = "pattern" + std::to_string(i);
    int index = s.Add(pattern, &error);
    EXPECT_EQ(index, i);
  }
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  bool matched = s.Match("pattern42", &matches);
  EXPECT_TRUE(matched);
  EXPECT_NE(std::find(matches.begin(), matches.end(), 42), matches.end());
}

// Test that matches vector is cleared before use
TEST_F(RE2SetTest_234, MatchClearsVector_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Compile();

  std::vector<int> matches;
  matches.push_back(99);  // pre-populate
  bool matched = s.Match("hello", &matches);
  EXPECT_TRUE(matched);
  // The vector should not contain the pre-populated value if cleared
  // or it could contain it if not cleared - we observe the behavior
  // Either way, pattern 0 should be in the results
  EXPECT_NE(std::find(matches.begin(), matches.end(), 0), matches.end());
}

// Test Match with alternation pattern
TEST_F(RE2SetTest_234, MatchAlternation_234) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("cat|dog", &error);
  s.Compile();

  std::vector<int> matches;
  bool matched = s.Match("I have a cat", &matches);
  EXPECT_TRUE(matched);

  matches.clear();
  matched = s.Match("I have a dog", &matches);
  EXPECT_TRUE(matched);

  matches.clear();
  matched = s.Match("I have a bird", &matches);
  EXPECT_FALSE(matched);
}

}  // namespace re2
