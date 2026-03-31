#include "gtest/gtest.h"
#include "re2/set.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

class RE2SetTest_233 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Basic construction with default options and UNANCHORED
TEST_F(RE2SetTest_233, ConstructWithDefaultOptions_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  // Should compile successfully even with no patterns
  EXPECT_TRUE(s.Compile());
}

// Test: Add a single valid pattern and compile
TEST_F(RE2SetTest_233, AddSinglePatternAndCompile_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("hello", &error);
  EXPECT_EQ(index, 0);
  EXPECT_TRUE(s.Compile());
}

// Test: Add multiple valid patterns
TEST_F(RE2SetTest_233, AddMultiplePatternsAndCompile_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  EXPECT_EQ(s.Add("hello", &error), 0);
  EXPECT_EQ(s.Add("world", &error), 1);
  EXPECT_EQ(s.Add("foo", &error), 2);
  EXPECT_TRUE(s.Compile());
}

// Test: Add an invalid pattern returns -1
TEST_F(RE2SetTest_233, AddInvalidPatternReturnsNegative_233) {
  RE2::Options options;
  options.set_log_errors(false);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  int index = s.Add("(invalid[", &error);
  EXPECT_EQ(index, -1);
  EXPECT_FALSE(error.empty());
}

// Test: Match finds correct pattern indices (UNANCHORED)
TEST_F(RE2SetTest_233, MatchFindsCorrectPatterns_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  s.Add("foo", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  // Should find at least "hello" and "world"
  bool found_hello = false, found_world = false;
  for (int m : matches) {
    if (m == 0) found_hello = true;
    if (m == 1) found_world = true;
  }
  EXPECT_TRUE(found_hello);
  EXPECT_TRUE(found_world);
}

// Test: Match with no matching patterns
TEST_F(RE2SetTest_233, MatchNoMatch_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  s.Add("world", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("xyz", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test: Match with empty text
TEST_F(RE2SetTest_233, MatchEmptyText_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("", &matches));
}

// Test: Match with empty pattern matches empty text
TEST_F(RE2SetTest_233, EmptyPatternMatchesEmptyText_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("", &matches));
  ASSERT_EQ(matches.size(), 1);
  EXPECT_EQ(matches[0], 0);
}

// Test: Compile with no patterns added
TEST_F(RE2SetTest_233, CompileWithNoPatterns_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  // Compiling with no patterns should still succeed (or at least not crash)
  // The behavior may vary, but we test it doesn't crash
  bool compiled = s.Compile();
  // If compiled, matching should return false for any text
  if (compiled) {
    std::vector<int> matches;
    EXPECT_FALSE(s.Match("anything", &matches));
  }
}

// Test: Compile called twice returns false on second call
TEST_F(RE2SetTest_233, CompileCalledTwiceReturnsFalse_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  EXPECT_TRUE(s.Compile());
  // Second call to Compile should fail
  EXPECT_FALSE(s.Compile());
}

// Test: ANCHOR_BOTH mode - full match only
TEST_F(RE2SetTest_233, AnchorBothFullMatchOnly_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::ANCHOR_BOTH);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  EXPECT_FALSE(s.Match("hello world", &matches));
}

// Test: ANCHOR_START mode
TEST_F(RE2SetTest_233, AnchorStartMode_233) {
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

// Test: Match with nullptr vector (just boolean result)
TEST_F(RE2SetTest_233, MatchWithNullVector_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);
  ASSERT_TRUE(s.Compile());

  EXPECT_TRUE(s.Match("hello", nullptr));
  EXPECT_FALSE(s.Match("xyz", nullptr));
}

// Test: Match with regex special characters
TEST_F(RE2SetTest_233, MatchWithRegexSpecialChars_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("a+b", &error);
  s.Add("c*d", &error);
  s.Add("[0-9]+", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("aab", &matches));
  
  matches.clear();
  EXPECT_TRUE(s.Match("123", &matches));
}

// Test: Move constructor
TEST_F(RE2SetTest_233, MoveConstructor_233) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  s1.Add("world", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(std::move(s1));
  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test: Move assignment operator
TEST_F(RE2SetTest_233, MoveAssignment_233) {
  RE2::Options options;
  RE2::Set s1(options, RE2::UNANCHORED);
  std::string error;
  s1.Add("hello", &error);
  ASSERT_TRUE(s1.Compile());

  RE2::Set s2(options, RE2::UNANCHORED);
  s2 = std::move(s1);
  std::vector<int> matches;
  EXPECT_TRUE(s2.Match("hello", &matches));
}

// Test: Add pattern with error parameter as nullptr
TEST_F(RE2SetTest_233, AddPatternWithNullError_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  int index = s.Add("hello", nullptr);
  EXPECT_EQ(index, 0);
  EXPECT_TRUE(s.Compile());
}

// Test: Add invalid pattern with error parameter as nullptr
TEST_F(RE2SetTest_233, AddInvalidPatternWithNullError_233) {
  RE2::Options options;
  options.set_log_errors(false);
  RE2::Set s(options, RE2::UNANCHORED);
  int index = s.Add("(invalid[", nullptr);
  EXPECT_EQ(index, -1);
}

// Test: Multiple patterns all matching
TEST_F(RE2SetTest_233, AllPatternsMatch_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("a", &error);
  s.Add("b", &error);
  s.Add("c", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("abc", &matches));
  EXPECT_EQ(matches.size(), 3u);
}

// Test: Match with ErrorInfo overload
TEST_F(RE2SetTest_233, MatchWithErrorInfo_233) {
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

// Test: Match before Compile should fail or return false
TEST_F(RE2SetTest_233, MatchBeforeCompileFails_233) {
  RE2::Options options;
  options.set_log_errors(false);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("hello", &error);

  std::vector<int> matches;
  // Calling Match before Compile - should return false
  EXPECT_FALSE(s.Match("hello", &matches));
}

// Test: Literal mode
TEST_F(RE2SetTest_233, LiteralMode_233) {
  RE2::Options options;
  options.set_literal(true);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  // In literal mode, "a+b" should match literally "a+b" not regex
  s.Add("a+b", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("a+b", &matches));
  EXPECT_FALSE(matches.empty());

  matches.clear();
  // "aab" should NOT match because in literal mode "a+b" is literal
  EXPECT_FALSE(s.Match("aab", &matches));
}

// Test: Case insensitive matching
TEST_F(RE2SetTest_233, CaseInsensitive_233) {
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

// Test: Large number of patterns
TEST_F(RE2SetTest_233, LargeNumberOfPatterns_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  for (int i = 0; i < 100; i++) {
    std::string pattern = "pattern" + std::to_string(i);
    EXPECT_EQ(s.Add(pattern, &error), i);
  }
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("pattern50", &matches));
  bool found = false;
  for (int m : matches) {
    if (m == 50) found = true;
  }
  EXPECT_TRUE(found);
}

// Test: Dot matches newline option
TEST_F(RE2SetTest_233, DotMatchesNewline_233) {
  RE2::Options options;
  options.set_dot_nl(true);
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("a.b", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("a\nb", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test: Dot does not match newline by default
TEST_F(RE2SetTest_233, DotDoesNotMatchNewlineByDefault_233) {
  RE2::Options options;
  RE2::Set s(options, RE2::UNANCHORED);
  std::string error;
  s.Add("a.b", &error);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(s.Match("a\nb", &matches));
}

}  // namespace re2
