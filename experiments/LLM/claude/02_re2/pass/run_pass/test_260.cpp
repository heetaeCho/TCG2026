#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

class RE2PossibleMatchRangeTest_260 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic literal pattern returns correct range
TEST_F(RE2PossibleMatchRangeTest_260, BasicLiteralPattern_260) {
  RE2 re("hello");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  EXPECT_EQ(min, "hello");
  EXPECT_EQ(max, "hello");
}

// Test pattern with wildcard character class
TEST_F(RE2PossibleMatchRangeTest_260, PatternWithWildcard_260) {
  RE2 re("abc.*");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  // min should start with "abc"
  EXPECT_GE(min.size(), 3u);
  EXPECT_EQ(min.substr(0, 3), "abc");
}

// Test empty pattern
TEST_F(RE2PossibleMatchRangeTest_260, EmptyPattern_260) {
  RE2 re("");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
}

// Test maxlen of 0
TEST_F(RE2PossibleMatchRangeTest_260, MaxlenZero_260) {
  RE2 re("hello");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 0);
  // With maxlen 0, we can't really get much range info
  // The function should still return without crashing
  // It may return true or false depending on implementation
  (void)result;
}

// Test maxlen of 1
TEST_F(RE2PossibleMatchRangeTest_260, MaxlenOne_260) {
  RE2 re("hello");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 1);
  EXPECT_TRUE(result);
  EXPECT_LE(min.size(), 1u);
  EXPECT_LE(max.size(), 1u);
}

// Test case-insensitive pattern
TEST_F(RE2PossibleMatchRangeTest_260, CaseInsensitivePattern_260) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
}

// Test invalid regex pattern
TEST_F(RE2PossibleMatchRangeTest_260, InvalidPattern_260) {
  RE2 re("(unclosed");
  std::string min, max;
  // If the pattern is invalid, ok() should be false
  // and PossibleMatchRange should return false (prog_ == NULL)
  if (!re.ok()) {
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_FALSE(result);
  }
}

// Test pattern that matches everything
TEST_F(RE2PossibleMatchRangeTest_260, MatchEverything_260) {
  RE2 re(".*");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
}

// Test min <= max relationship
TEST_F(RE2PossibleMatchRangeTest_260, MinLessOrEqualMax_260) {
  RE2 re("abc[d-f]ghi");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min, max);
}

// Test with large maxlen
TEST_F(RE2PossibleMatchRangeTest_260, LargeMaxlen_260) {
  RE2 re("hello");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 1000);
  EXPECT_TRUE(result);
  EXPECT_EQ(min, "hello");
  EXPECT_EQ(max, "hello");
}

// Test pattern with character class
TEST_F(RE2PossibleMatchRangeTest_260, CharacterClassPattern_260) {
  RE2 re("[a-z]+");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min, max);
}

// Test pattern with prefix and alternation
TEST_F(RE2PossibleMatchRangeTest_260, PrefixWithAlternation_260) {
  RE2 re("abc(def|ghi)");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min, max);
}

// Test single character pattern
TEST_F(RE2PossibleMatchRangeTest_260, SingleCharPattern_260) {
  RE2 re("x");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  EXPECT_EQ(min, "x");
  EXPECT_EQ(max, "x");
}

// Test that the range is useful for filtering
TEST_F(RE2PossibleMatchRangeTest_260, RangeIsUsefulForFiltering_260) {
  RE2 re("prefix.*suffix");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 20);
  EXPECT_TRUE(result);
  // Any string matching the pattern should be >= min and < max
  EXPECT_LE(min, max);
}

// Test pattern with dot
TEST_F(RE2PossibleMatchRangeTest_260, PatternWithDot_260) {
  RE2 re("a.c");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min, max);
}

// Test maxlen smaller than prefix
TEST_F(RE2PossibleMatchRangeTest_260, MaxlenSmallerThanPrefix_260) {
  RE2 re("abcdefghij");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 3);
  EXPECT_TRUE(result);
  EXPECT_LE(min.size(), 3u);
  EXPECT_LE(max.size(), 4u);  // max might get a successor appended
}

// Test with numeric pattern
TEST_F(RE2PossibleMatchRangeTest_260, NumericPattern_260) {
  RE2 re("[0-9]+");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min, max);
}

// Test with anchored pattern
TEST_F(RE2PossibleMatchRangeTest_260, AnchoredPattern_260) {
  RE2 re("^hello$");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
}

// Test result strings are non-empty for valid patterns
TEST_F(RE2PossibleMatchRangeTest_260, NonEmptyResults_260) {
  RE2 re("test");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min.empty());
  EXPECT_FALSE(max.empty());
}

// Test with optional group
TEST_F(RE2PossibleMatchRangeTest_260, OptionalGroup_260) {
  RE2 re("abc(def)?ghi");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 20);
  EXPECT_TRUE(result);
  EXPECT_LE(min, max);
}

// Test with repetition
TEST_F(RE2PossibleMatchRangeTest_260, RepetitionPattern_260) {
  RE2 re("a{3,5}");
  std::string min, max;
  ASSERT_TRUE(re.ok());
  bool result = re.PossibleMatchRange(&min, &max, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min, max);
}

}  // namespace re2
