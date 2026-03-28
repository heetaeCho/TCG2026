#include "re2/set.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <gtest/gtest.h>

namespace re2 {

// Test fixture for RE2::Set tests
class RE2SetTest_594 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic construction with default options
TEST_F(RE2SetTest_594, ConstructWithDefaultOptions_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  // Should be constructible without issues
}

// Test construction with ANCHOR_BOTH
TEST_F(RE2SetTest_594, ConstructWithAnchorBoth_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_BOTH);
}

// Test Add a single valid pattern
TEST_F(RE2SetTest_594, AddSingleValidPattern_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("hello", &error);
  EXPECT_EQ(index, 0);
}

// Test Add multiple valid patterns
TEST_F(RE2SetTest_594, AddMultipleValidPatterns_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  EXPECT_EQ(s.Add("hello", &error), 0);
  EXPECT_EQ(s.Add("world", &error), 1);
  EXPECT_EQ(s.Add("foo", &error), 2);
}

// Test Add an invalid pattern returns -1
TEST_F(RE2SetTest_594, AddInvalidPatternReturnsNegative_594) {
  RE2::Options options;
  options.set_log_errors(false);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("[invalid", &error);
  EXPECT_EQ(index, -1);
  EXPECT_FALSE(error.empty());
}

// Test Compile with no patterns
TEST_F(RE2SetTest_594, CompileWithNoPatterns_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  EXPECT_TRUE(s.Compile());
}

// Test Compile with valid patterns
TEST_F(RE2SetTest_594, CompileWithValidPatterns_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  EXPECT_TRUE(s.Compile());
}

// Test Match finds matching patterns
TEST_F(RE2SetTest_594, MatchFindsPatterns_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  s.Add("foo", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello", &matches));
  ASSERT_EQ(matches.size(), 1);
  EXPECT_EQ(matches[0], 0);
}

// Test Match finds multiple matching patterns
TEST_F(RE2SetTest_594, MatchFindsMultiplePatterns_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("he", &error);
  s.Add("hell", &error);
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  EXPECT_GE(matches.size(), 1u);
}

// Test Match returns false when no pattern matches
TEST_F(RE2SetTest_594, MatchReturnsFalseWhenNoMatch_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("xyz", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test Match with null vector
TEST_F(RE2SetTest_594, MatchWithNullVector_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  EXPECT_TRUE(s.Match("hello", nullptr));
}

// Test Match with no match and null vector
TEST_F(RE2SetTest_594, MatchNoMatchWithNullVector_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  EXPECT_FALSE(s.Match("xyz", nullptr));
}

// Test Match on empty text
TEST_F(RE2SetTest_594, MatchEmptyText_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("", &matches));
}

// Test Match with empty pattern matches everything
TEST_F(RE2SetTest_594, MatchEmptyPatternMatchesEmptyText_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("", &matches));
  EXPECT_GE(matches.size(), 1u);
}

// Test Match with ANCHOR_BOTH
TEST_F(RE2SetTest_594, MatchWithAnchorBoth_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_BOTH);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  // Exact match should succeed
  EXPECT_TRUE(s.Match("hello", &matches));
  EXPECT_EQ(matches.size(), 1u);

  matches.clear();
  // Partial match should fail with ANCHOR_BOTH
  EXPECT_FALSE(s.Match("hello world", &matches));
}

// Test Match with ANCHOR_START
TEST_F(RE2SetTest_594, MatchWithAnchorStart_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_START);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  EXPECT_GE(matches.size(), 1u);

  matches.clear();
  EXPECT_FALSE(s.Match("say hello", &matches));
}

// Test Move Constructor
TEST_F(RE2SetTest_594, MoveConstructor_594) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  s1.Add("world", &error);
  EXPECT_TRUE(s1.Compile());

  // Move construct s2 from s1
  RE2::Set s2(std::move(s1));

  // s2 should be functional
  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello", &matches));
  EXPECT_GE(matches.size(), 1u);
}

// Test Move Constructor - moved-from object state
TEST_F(RE2SetTest_594, MoveConstructorMovedFromState_594) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  EXPECT_TRUE(s1.Compile());

  RE2::Set s2(std::move(s1));
  // After move, s2 should work. s1 is in a valid but unspecified state.
  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello", &matches));
}

// Test Move Assignment Operator
TEST_F(RE2SetTest_594, MoveAssignment_594) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  s1.Add("world", &error);
  EXPECT_TRUE(s1.Compile());

  RE2::Set s2(options, RE2::UNANCHORED);
  s2 = std::move(s1);

  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello", &matches));
  EXPECT_GE(matches.size(), 1u);
}

// Test Match with ErrorInfo overload
TEST_F(RE2SetTest_594, MatchWithErrorInfo_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  EXPECT_TRUE(s.Match("hello", &matches, &error_info));
  EXPECT_GE(matches.size(), 1u);
}

// Test Match with ErrorInfo and no match
TEST_F(RE2SetTest_594, MatchWithErrorInfoNoMatch_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  EXPECT_FALSE(s.Match("xyz", &matches, &error_info));
}

// Test compiling empty set and matching
TEST_F(RE2SetTest_594, CompileEmptySetAndMatch_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("hello", &matches));
}

// Test Add after Compile should fail (Add returns -1)
TEST_F(RE2SetTest_594, AddAfterCompile_594) {
  RE2::Options options;
  options.set_log_errors(false);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  // Adding after compile should return -1
  int index = s.Add("world", &error);
  EXPECT_EQ(index, -1);
}

// Test with regex patterns
TEST_F(RE2SetTest_594, MatchWithRegexPatterns_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hel+o", &error);
  s.Add("wor.d", &error);
  s.Add("[0-9]+", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("helllllo", &matches));
  EXPECT_GE(matches.size(), 1u);

  matches.clear();
  EXPECT_TRUE(s.Match("42", &matches));
  // Should match the [0-9]+ pattern
  bool found = false;
  for (int m : matches) {
    if (m == 2) found = true;
  }
  EXPECT_TRUE(found);
}

// Test case-insensitive matching
TEST_F(RE2SetTest_594, CaseInsensitiveMatch_594) {
  RE2::Options options;
  options.set_case_sensitive(false);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("HELLO", &matches));
  EXPECT_GE(matches.size(), 1u);
}

// Test large number of patterns
TEST_F(RE2SetTest_594, ManyPatterns_594) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  const int kNumPatterns = 100;
  for (int i = 0; i < kNumPatterns; i++) {
    std::string pattern = "pattern" + std::to_string(i);
    int index = s.Add(pattern, &error);
    EXPECT_EQ(index, i);
  }
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("pattern50", &matches));
  bool found50 = false;
  for (int m : matches) {
    if (m == 50) found50 = true;
  }
  EXPECT_TRUE(found50);
}

// Test that copy construction is deleted (compile-time check, just verifying Set is movable)
TEST_F(RE2SetTest_594, MoveIsValid_594) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("test", &error);
  EXPECT_TRUE(s1.Compile());

  // Move should work
  RE2::Set s2 = std::move(s1);
  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("test", &matches));
}

// Test Match before Compile returns false
TEST_F(RE2SetTest_594, MatchBeforeCompile_594) {
  RE2::Options options;
  options.set_log_errors(false);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);

  std::vector<int> matches;
  // Should return false since not compiled
  EXPECT_FALSE(s.Match("hello", &matches));
}

}  // namespace re2
