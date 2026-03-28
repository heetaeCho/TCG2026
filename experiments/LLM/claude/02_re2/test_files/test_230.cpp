#include "gtest/gtest.h"
#include "re2/set.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {
namespace {

// Test fixture for RE2::Set tests
class RE2SetTest_230 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic construction and destruction
TEST_F(RE2SetTest_230, ConstructAndDestruct_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  // Should not crash
}

// Test construction with ANCHOR_BOTH
TEST_F(RE2SetTest_230, ConstructWithAnchorBoth_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_BOTH);
  // Should not crash
}

// Test construction with ANCHOR_START
TEST_F(RE2SetTest_230, ConstructWithAnchorStart_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_START);
  // Should not crash
}

// Test Add returns non-negative index for valid pattern
TEST_F(RE2SetTest_230, AddValidPattern_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("hello", &error);
  EXPECT_GE(index, 0);
}

// Test Add returns -1 for invalid pattern
TEST_F(RE2SetTest_230, AddInvalidPattern_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("(invalid", &error);
  EXPECT_EQ(index, -1);
  EXPECT_FALSE(error.empty());
}

// Test Add multiple patterns returns increasing indices
TEST_F(RE2SetTest_230, AddMultiplePatterns_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int idx0 = s.Add("foo", &error);
  int idx1 = s.Add("bar", &error);
  int idx2 = s.Add("baz", &error);
  EXPECT_EQ(idx0, 0);
  EXPECT_EQ(idx1, 1);
  EXPECT_EQ(idx2, 2);
}

// Test Compile succeeds with valid patterns
TEST_F(RE2SetTest_230, CompileSucceeds_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  EXPECT_TRUE(s.Compile());
}

// Test Compile succeeds with no patterns
TEST_F(RE2SetTest_230, CompileWithNoPatterns_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  EXPECT_TRUE(s.Compile());
}

// Test Match finds matching patterns (unanchored)
TEST_F(RE2SetTest_230, MatchFindsPatterns_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  s.Add("bar", &error);
  s.Add("baz", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foo", &matches));
  ASSERT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 0);
}

// Test Match returns false when no patterns match
TEST_F(RE2SetTest_230, MatchNoMatch_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  s.Add("bar", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("qux", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test Match with multiple matching patterns
TEST_F(RE2SetTest_230, MatchMultiplePatterns_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("fo.", &error);
  s.Add("foo", &error);
  s.Add("bar", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foo", &matches));
  EXPECT_GE(matches.size(), 2u);
  // Both pattern 0 (fo.) and pattern 1 (foo) should match
  bool found0 = false, found1 = false;
  for (int m : matches) {
    if (m == 0) found0 = true;
    if (m == 1) found1 = true;
  }
  EXPECT_TRUE(found0);
  EXPECT_TRUE(found1);
}

// Test Match with ANCHOR_BOTH
TEST_F(RE2SetTest_230, MatchAnchorBoth_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_BOTH);
  std::string error;
  s.Add("foo", &error);
  s.Add("bar", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  // "foobar" should not match when anchored both
  EXPECT_FALSE(s.Match("foobar", &matches));

  matches.clear();
  EXPECT_TRUE(s.Match("foo", &matches));
  ASSERT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 0);
}

// Test Match with null vector
TEST_F(RE2SetTest_230, MatchWithNullVector_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  // Passing nullptr for matches vector - should just return whether there is a match
  EXPECT_TRUE(s.Match("foo", static_cast<std::vector<int>*>(nullptr)));
  EXPECT_FALSE(s.Match("bar", static_cast<std::vector<int>*>(nullptr)));
}

// Test Match with ErrorInfo overload
TEST_F(RE2SetTest_230, MatchWithErrorInfo_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  EXPECT_TRUE(s.Match("hello world", &matches, &error_info));
  EXPECT_FALSE(matches.empty());
}

// Test Match before Compile should fail
TEST_F(RE2SetTest_230, MatchBeforeCompile_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  // Not compiled yet
  std::vector<int> matches;
  EXPECT_FALSE(s.Match("foo", &matches));
}

// Test Add after Compile should fail
TEST_F(RE2SetTest_230, AddAfterCompile_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());
  int index = s.Add("bar", &error);
  EXPECT_EQ(index, -1);
}

// Test Move constructor
TEST_F(RE2SetTest_230, MoveConstructor_230) {
  RE2::Set s1(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s1.Add("foo", &error);
  s1.Add("bar", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(std::move(s1));

  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("foo", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test Move assignment
TEST_F(RE2SetTest_230, MoveAssignment_230) {
  RE2::Set s1(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s1.Add("foo", &error);
  s1.Add("bar", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(RE2::DefaultOptions, RE2::UNANCHORED);
  s2 = std::move(s1);

  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("foo", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test empty string pattern
TEST_F(RE2SetTest_230, EmptyPattern_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("", &error);
  EXPECT_GE(index, 0);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  // Empty pattern matches anything
  EXPECT_TRUE(s.Match("anything", &matches));
}

// Test matching against empty text
TEST_F(RE2SetTest_230, EmptyTextMatch_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("", &matches));
}

// Test empty text with empty pattern
TEST_F(RE2SetTest_230, EmptyTextEmptyPattern_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("", &matches));
}

// Test with regex special characters
TEST_F(RE2SetTest_230, RegexSpecialChars_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("a.*b", &error);
  s.Add("[0-9]+", &error);
  s.Add("(x|y|z)", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;

  EXPECT_TRUE(s.Match("aXXXb", &matches));
  bool found0 = false;
  for (int m : matches) {
    if (m == 0) found0 = true;
  }
  EXPECT_TRUE(found0);

  matches.clear();
  EXPECT_TRUE(s.Match("12345", &matches));
  bool found1 = false;
  for (int m : matches) {
    if (m == 1) found1 = true;
  }
  EXPECT_TRUE(found1);

  matches.clear();
  EXPECT_TRUE(s.Match("x", &matches));
  bool found2 = false;
  for (int m : matches) {
    if (m == 2) found2 = true;
  }
  EXPECT_TRUE(found2);
}

// Test with no patterns compiled, match returns false
TEST_F(RE2SetTest_230, CompileEmptySetNoMatch_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("anything", &matches));
}

// Test Add with null error string
TEST_F(RE2SetTest_230, AddWithNullError_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  int index = s.Add("foo", nullptr);
  EXPECT_GE(index, 0);
}

// Test Add invalid pattern with null error
TEST_F(RE2SetTest_230, AddInvalidPatternNullError_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  int index = s.Add("(unclosed", nullptr);
  EXPECT_EQ(index, -1);
}

// Test Match with ANCHOR_START
TEST_F(RE2SetTest_230, MatchAnchorStart_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_START);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foobar", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  EXPECT_FALSE(s.Match("barfoo", &matches));
}

// Test case insensitive matching via options
TEST_F(RE2SetTest_230, CaseInsensitive_230) {
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

// Test single pattern match with large text
TEST_F(RE2SetTest_230, LargeText_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("needle", &error);
  ASSERT_TRUE(s.Compile());

  std::string large_text(100000, 'x');
  large_text += "needle";
  large_text += std::string(100000, 'y');

  std::vector<int> matches;
  EXPECT_TRUE(s.Match(large_text, &matches));
  ASSERT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 0);
}

// Test many patterns
TEST_F(RE2SetTest_230, ManyPatterns_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  for (int i = 0; i < 100; i++) {
    std::string pattern = "pattern" + std::to_string(i);
    int idx = s.Add(pattern, &error);
    EXPECT_EQ(idx, i);
  }
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("pattern42", &matches));
  bool found42 = false;
  for (int m : matches) {
    if (m == 42) found42 = true;
  }
  EXPECT_TRUE(found42);
}

// Test ErrorInfo on no match
TEST_F(RE2SetTest_230, ErrorInfoOnNoMatch_230) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  std::string error;
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  RE2::Set::ErrorInfo error_info;
  EXPECT_FALSE(s.Match("bar", &matches, &error_info));
}

}  // namespace
}  // namespace re2
