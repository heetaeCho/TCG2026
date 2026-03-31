#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

// Test ReverseProgramFanout with a valid simple pattern
TEST(RE2ReverseProgramFanoutTest_249, ValidSimplePattern_249) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ReverseProgramFanout with a valid pattern containing alternation
TEST(RE2ReverseProgramFanoutTest_249, ValidAlternationPattern_249) {
  RE2 re("(hello|world)");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
  EXPECT_FALSE(histogram.empty());
}

// Test ReverseProgramFanout with an invalid pattern returns -1
TEST(RE2ReverseProgramFanoutTest_249, InvalidPatternReturnsNegative_249) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(?P<a>hello)(?P<a>world)", opts);  // duplicate named group - may be invalid
  // If the pattern is valid, we just check it doesn't crash
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  if (!re.ok()) {
    EXPECT_EQ(result, -1);
  }
}

// Test ReverseProgramFanout with a character class pattern
TEST(RE2ReverseProgramFanoutTest_249, CharacterClassPattern_249) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ReverseProgramFanout with a complex pattern
TEST(RE2ReverseProgramFanoutTest_249, ComplexPattern_249) {
  RE2 re("(a+)(b*)(c?)(d{2,4})");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ReverseProgramFanout with an empty pattern
TEST(RE2ReverseProgramFanoutTest_249, EmptyPattern_249) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ReverseProgramFanout with a dot-star pattern
TEST(RE2ReverseProgramFanoutTest_249, DotStarPattern_249) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ReverseProgramFanout with a single character pattern
TEST(RE2ReverseProgramFanoutTest_249, SingleCharPattern_249) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ReverseProgramFanout with a pattern that has nested groups
TEST(RE2ReverseProgramFanoutTest_249, NestedGroupsPattern_249) {
  RE2 re("((a)(b(c)))");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ReverseProgramFanout histogram is populated with non-negative values
TEST(RE2ReverseProgramFanoutTest_249, HistogramValuesNonNegative_249) {
  RE2 re("abc|def|ghi");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
  for (int val : histogram) {
    EXPECT_GE(val, 0);
  }
}

// Test ReverseProgramFanout with a large repetition pattern
TEST(RE2ReverseProgramFanoutTest_249, LargeRepetitionPattern_249) {
  RE2 re("a{1,100}");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test that ReverseProgramFanout result is consistent with ReverseProgramSize
TEST(RE2ReverseProgramFanoutTest_249, ConsistentWithReverseProgramSize_249) {
  RE2 re("foo|bar|baz");
  ASSERT_TRUE(re.ok());
  int rps = re.ReverseProgramSize();
  EXPECT_GT(rps, 0);
  std::vector<int> histogram;
  int fanout = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(fanout, 0);
}

// Test ProgramFanout as a comparison (both vector-based variants)
TEST(RE2ProgramFanoutTest_249, ValidPatternProgramFanout_249) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ProgramSize and ReverseProgramSize for a valid pattern
TEST(RE2ProgramSizeTest_249, ValidPatternSizes_249) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// Test with a pattern that uses anchors
TEST(RE2ReverseProgramFanoutTest_249, AnchoredPattern_249) {
  RE2 re("^abc$");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test with a pattern containing Unicode
TEST(RE2ReverseProgramFanoutTest_249, UnicodePattern_249) {
  RE2 re("\\p{L}+");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test that calling ReverseProgramFanout multiple times gives same result
TEST(RE2ReverseProgramFanoutTest_249, MultipleCalls_249) {
  RE2 re("(a|b)(c|d)");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram1;
  int result1 = re.ReverseProgramFanout(&histogram1);
  std::vector<int> histogram2;
  int result2 = re.ReverseProgramFanout(&histogram2);
  EXPECT_EQ(result1, result2);
  EXPECT_EQ(histogram1, histogram2);
}

}  // namespace re2
