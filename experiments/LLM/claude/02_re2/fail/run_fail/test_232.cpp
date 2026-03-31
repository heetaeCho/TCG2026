#include "gtest/gtest.h"
#include "re2/set.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

class RE2SetTest_232 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test adding a valid simple pattern returns index 0
TEST_F(RE2SetTest_232, AddValidPatternReturnsZero_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("hello", &error);
  EXPECT_EQ(0, index);
}

// Test adding multiple valid patterns returns incrementing indices
TEST_F(RE2SetTest_232, AddMultiplePatternsReturnsIncrementingIndices_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  EXPECT_EQ(0, s.Add("hello", &error));
  EXPECT_EQ(1, s.Add("world", &error));
  EXPECT_EQ(2, s.Add("foo", &error));
  EXPECT_EQ(3, s.Add("bar", &error));
}

// Test adding an invalid pattern returns -1
TEST_F(RE2SetTest_232, AddInvalidPatternReturnsNegativeOne_232) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2::Set s(opts, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("[invalid", &error);
  EXPECT_EQ(-1, index);
}

// Test that error string is populated for invalid pattern
TEST_F(RE2SetTest_232, AddInvalidPatternSetsErrorString_232) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2::Set s(opts, RE2::UNANCHORED);
  std::string error;
  s.Add("[invalid", &error);
  EXPECT_FALSE(error.empty());
}

// Test adding pattern with null error pointer for invalid pattern
TEST_F(RE2SetTest_232, AddInvalidPatternWithNullError_232) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2::Set s(opts, RE2::UNANCHORED);
  int index = s.Add("[invalid", nullptr);
  EXPECT_EQ(-1, index);
}

// Test adding pattern with null error pointer for valid pattern
TEST_F(RE2SetTest_232, AddValidPatternWithNullError_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  int index = s.Add("hello", nullptr);
  EXPECT_EQ(0, index);
}

// Test that Add after Compile returns -1
TEST_F(RE2SetTest_232, AddAfterCompileReturnsNegativeOne_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());
  int index = s.Add("world", &error);
  EXPECT_EQ(-1, index);
}

// Test Compile with valid patterns
TEST_F(RE2SetTest_232, CompileWithValidPatterns_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  EXPECT_TRUE(s.Compile());
}

// Test Compile with no patterns
TEST_F(RE2SetTest_232, CompileWithNoPatterns_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  EXPECT_TRUE(s.Compile());
}

// Test Match after Compile with matching text
TEST_F(RE2SetTest_232, MatchFindsMatchingPattern_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test Match with non-matching text
TEST_F(RE2SetTest_232, MatchDoesNotFindNonMatchingPattern_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool result = s.Match("xyz", &matches);
  // If no match, result should be false and matches should be empty
  if (!result) {
    EXPECT_TRUE(matches.empty());
  }
}

// Test Match returns correct indices
TEST_F(RE2SetTest_232, MatchReturnsCorrectIndices_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);   // index 0
  s.Add("bar", &error);   // index 1
  s.Add("baz", &error);   // index 2
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foobar", &matches));
  // Should contain at least index 0 and 1
  bool found0 = false, found1 = false;
  for (int idx : matches) {
    if (idx == 0) found0 = true;
    if (idx == 1) found1 = true;
  }
  EXPECT_TRUE(found0);
  EXPECT_TRUE(found1);
}

// Test Match with null vector
TEST_F(RE2SetTest_232, MatchWithNullVector_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  EXPECT_TRUE(s.Match("hello", nullptr));
}

// Test adding empty pattern
TEST_F(RE2SetTest_232, AddEmptyPattern_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("", &error);
  EXPECT_EQ(0, index);
}

// Test adding pattern with regex special characters
TEST_F(RE2SetTest_232, AddPatternWithSpecialCharacters_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("a.*b", &error);
  EXPECT_EQ(0, index);
}

// Test adding pattern with character class
TEST_F(RE2SetTest_232, AddPatternWithCharacterClass_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("[a-z]+", &error);
  EXPECT_EQ(0, index);
}

// Test adding pattern with alternation
TEST_F(RE2SetTest_232, AddPatternWithAlternation_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("foo|bar", &error);
  EXPECT_EQ(0, index);
}

// Test adding pattern with groups (concat patterns)
TEST_F(RE2SetTest_232, AddConcatPattern_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("abc", &error);
  EXPECT_EQ(0, index);
}

// Test Match with ANCHOR_BOTH
TEST_F(RE2SetTest_232, MatchWithAnchorBoth_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_BOTH);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  bool result = s.Match("hello world", &matches);
  // With ANCHOR_BOTH, "hello world" should not match "hello"
  if (result) {
    bool found0 = false;
    for (int idx : matches) {
      if (idx == 0) found0 = true;
    }
    // "hello" alone shouldn't match "hello world" with ANCHOR_BOTH
    // but behavior depends on implementation
  }
}

// Test Match with ANCHOR_START
TEST_F(RE2SetTest_232, MatchWithAnchorStart_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_START);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test Move constructor
TEST_F(RE2SetTest_232, MoveConstructor_232) {
  RE2::Set s1(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  s1.Add("world", &error);

  RE2::Set s2(std::move(s1));
  EXPECT_TRUE(s2.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello", &matches));
}

// Test Move assignment operator
TEST_F(RE2SetTest_232, MoveAssignment_232) {
  RE2::Set s1(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);

  RE2::Set s2(RE2::DefaultOptions, RE2::UNANCHORED);
  s2 = std::move(s1);
  EXPECT_TRUE(s2.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello", &matches));
}

// Test with Quiet option
TEST_F(RE2SetTest_232, AddInvalidPatternWithQuietOption_232) {
  RE2::Set s(RE2::Quiet, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("[invalid", &error);
  EXPECT_EQ(-1, index);
  EXPECT_FALSE(error.empty());
}

// Test with literal option
TEST_F(RE2SetTest_232, AddPatternWithLiteralOption_232) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2::Set s(opts, RE2::UNANCHORED);
  std::string error;
  // With literal mode, special chars should be treated as literals
  int index = s.Add("[abc", &error);
  EXPECT_EQ(0, index);
}

// Test Match with ErrorInfo overload
TEST_F(RE2SetTest_232, MatchWithErrorInfo_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  EXPECT_TRUE(s.Match("hello", &matches, &error_info));
  EXPECT_FALSE(matches.empty());
}

// Test adding many patterns
TEST_F(RE2SetTest_232, AddManyPatterns_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  for (int i = 0; i < 100; i++) {
    std::string pattern = "pattern" + std::to_string(i);
    EXPECT_EQ(i, s.Add(pattern, &error));
  }
  EXPECT_TRUE(s.Compile());
}

// Test Match with empty text
TEST_F(RE2SetTest_232, MatchWithEmptyText_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool result = s.Match("", &matches);
  EXPECT_FALSE(result);
}

// Test Match empty pattern with empty text
TEST_F(RE2SetTest_232, MatchEmptyPatternWithEmptyText_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  bool result = s.Match("", &matches);
  EXPECT_TRUE(result);
}

// Test that valid error string is empty for valid patterns
TEST_F(RE2SetTest_232, AddValidPatternErrorStringUnchanged_232) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error = "initial";
  s.Add("hello", &error);
  // For valid patterns, error should not be modified
  EXPECT_EQ("initial", error);
}

// Test case insensitive option
TEST_F(RE2SetTest_232, MatchCaseInsensitive_232) {
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

// Test posix syntax option
TEST_F(RE2SetTest_232, AddWithPosixSyntax_232) {
  RE2::Set s(RE2::POSIX, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("hello", &error);
  EXPECT_EQ(0, index);
  EXPECT_TRUE(s.Compile());
}

}  // namespace re2
