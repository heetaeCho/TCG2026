#include "gtest/gtest.h"
#include "re2/set.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

// Test fixture for RE2::Set tests
class RE2SetTest_235 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Adding valid patterns returns non-negative index
TEST_F(RE2SetTest_235, AddValidPattern_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int idx = s.Add("hello", &error);
  EXPECT_GE(idx, 0);
}

// Test: Adding multiple valid patterns returns sequential indices
TEST_F(RE2SetTest_235, AddMultiplePatterns_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int idx0 = s.Add("hello", &error);
  int idx1 = s.Add("world", &error);
  int idx2 = s.Add("foo", &error);
  EXPECT_EQ(idx0, 0);
  EXPECT_EQ(idx1, 1);
  EXPECT_EQ(idx2, 2);
}

// Test: Adding an invalid pattern returns -1
TEST_F(RE2SetTest_235, AddInvalidPattern_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int idx = s.Add("[invalid", &error);
  EXPECT_EQ(idx, -1);
  EXPECT_FALSE(error.empty());
}

// Test: Compile succeeds after adding patterns
TEST_F(RE2SetTest_235, CompileSucceeds_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  EXPECT_TRUE(s.Compile());
}

// Test: Compile succeeds with no patterns added
TEST_F(RE2SetTest_235, CompileWithNoPatterns_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  EXPECT_TRUE(s.Compile());
}

// Test: Match before Compile returns false with kNotCompiled error
TEST_F(RE2SetTest_235, MatchBeforeCompile_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  EXPECT_FALSE(s.Match("hello", &matches, &error_info));
  EXPECT_EQ(error_info.kind, RE2::Set::kNotCompiled);
}

// Test: Simple match returns true and correct indices
TEST_F(RE2SetTest_235, SimpleMatch_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello", &matches));
  ASSERT_FALSE(matches.empty());
  EXPECT_NE(std::find(matches.begin(), matches.end(), 0), matches.end());
}

// Test: Match with no matching patterns returns false
TEST_F(RE2SetTest_235, NoMatch_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("xyz", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test: Match with multiple matching patterns
TEST_F(RE2SetTest_235, MultipleMatches_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("\\w+", &error);
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello", &matches));
  EXPECT_GE(matches.size(), 1u);
}

// Test: Match with null vector still returns correct bool
TEST_F(RE2SetTest_235, MatchWithNullVector_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  EXPECT_TRUE(s.Match("hello", static_cast<std::vector<int>*>(nullptr)));
}

// Test: Match with null vector and no match returns false
TEST_F(RE2SetTest_235, NoMatchWithNullVector_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  EXPECT_FALSE(s.Match("xyz", static_cast<std::vector<int>*>(nullptr)));
}

// Test: Match with ErrorInfo and no error
TEST_F(RE2SetTest_235, MatchWithErrorInfoNoError_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  bool result = s.Match("hello", &matches, &error_info);
  EXPECT_TRUE(result);
  EXPECT_EQ(error_info.kind, RE2::Set::kNoError);
}

// Test: Match returns kNoError when no match
TEST_F(RE2SetTest_235, MatchNoMatchErrorInfo_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  bool result = s.Match("xyz", &matches, &error_info);
  EXPECT_FALSE(result);
  EXPECT_EQ(error_info.kind, RE2::Set::kNoError);
}

// Test: Empty string match
TEST_F(RE2SetTest_235, EmptyStringMatch_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add(".*", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test: Empty string with no matching pattern
TEST_F(RE2SetTest_235, EmptyStringNoMatch_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("", &matches));
}

// Test: Anchored match
TEST_F(RE2SetTest_235, AnchoredMatch_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_BOTH);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  EXPECT_FALSE(s.Match("hello world", &matches));
}

// Test: ANCHOR_START match
TEST_F(RE2SetTest_235, AnchorStartMatch_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_START);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  EXPECT_FALSE(s.Match("say hello", &matches));
}

// Test: Move constructor
TEST_F(RE2SetTest_235, MoveConstructor_235) {
  RE2::Set s1(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(std::move(s1));
  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test: Move assignment
TEST_F(RE2SetTest_235, MoveAssignment_235) {
  RE2::Set s1(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(RE2::DefaultOptions, RE2::UNANCHORED);
  s2 = std::move(s1);
  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test: Adding pattern with error string set to nullptr
TEST_F(RE2SetTest_235, AddWithNullError_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  int idx = s.Add("hello", nullptr);
  EXPECT_GE(idx, 0);
}

// Test: Adding invalid pattern with null error
TEST_F(RE2SetTest_235, AddInvalidWithNullError_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  int idx = s.Add("[invalid", nullptr);
  EXPECT_EQ(idx, -1);
}

// Test: Compile with no patterns and match returns false
TEST_F(RE2SetTest_235, CompileEmptySetMatch_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("anything", &matches));
}

// Test: Match with ErrorInfo null pointer
TEST_F(RE2SetTest_235, MatchWithNullErrorInfo_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello", &matches, nullptr));
  EXPECT_FALSE(matches.empty());
}

// Test: Regex patterns with special characters
TEST_F(RE2SetTest_235, SpecialCharacterPatterns_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  EXPECT_GE(s.Add("\\d+", &error), 0);
  EXPECT_GE(s.Add("[a-z]+", &error), 0);
  EXPECT_GE(s.Add("foo|bar", &error), 0);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("123", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test: Case insensitive matching with options
TEST_F(RE2SetTest_235, CaseInsensitiveMatch_235) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2::Set s(opts, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("HELLO", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test: Large number of patterns
TEST_F(RE2SetTest_235, LargeNumberOfPatterns_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  for (int i = 0; i < 100; i++) {
    std::string pattern = "pattern" + std::to_string(i);
    EXPECT_EQ(s.Add(pattern, &error), i);
  }
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("pattern50", &matches));
  EXPECT_FALSE(matches.empty());
  EXPECT_NE(std::find(matches.begin(), matches.end(), 50), matches.end());
}

// Test: Match clears the vector before populating
TEST_F(RE2SetTest_235, MatchClearsVector_235) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  matches.push_back(999);  // Pre-populate with garbage
  EXPECT_TRUE(s.Match("hello", &matches));
  // The vector should not contain the pre-populated value if match clears it
  EXPECT_EQ(std::find(matches.begin(), matches.end(), 999), matches.end());
}

// Test: Literal option
TEST_F(RE2SetTest_235, LiteralOption_235) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2::Set s(opts, RE2::UNANCHORED);
  std::string error;
  // With literal mode, "\\d+" should match literal string "\\d+"
  s.Add("\\d+", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  // Should NOT match "123" because it's literal
  EXPECT_FALSE(s.Match("123", &matches));
  // Should match the literal string
  EXPECT_TRUE(s.Match("\\d+", &matches));
}

}  // namespace re2
