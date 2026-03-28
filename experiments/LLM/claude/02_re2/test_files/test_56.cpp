#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "re2/re2.h"

// Include the shim function declaration
namespace re2_python {
std::vector<int> RE2ProgramFanoutShim(const RE2& self);
}

using re2::RE2;
using re2_python::RE2ProgramFanoutShim;

class RE2ProgramFanoutShimTest_56 : public ::testing::Test {
 protected:
};

// Test that a simple literal pattern returns a non-empty fanout histogram
TEST_F(RE2ProgramFanoutShimTest_56, SimpleLiteralPattern_56) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  // A valid compiled pattern should produce some histogram data
  // We just verify it doesn't crash and returns something
  EXPECT_FALSE(histogram.empty());
}

// Test that the shim returns the same result as calling ProgramFanout directly
TEST_F(RE2ProgramFanoutShimTest_56, ConsistentWithDirectCall_56) {
  RE2 re("a(b+)c");
  ASSERT_TRUE(re.ok());
  
  std::vector<int> shimResult = RE2ProgramFanoutShim(re);
  
  std::vector<int> directResult;
  re.ProgramFanout(&directResult);
  
  EXPECT_EQ(shimResult, directResult);
}

// Test with an alternation pattern which typically creates more fanout
TEST_F(RE2ProgramFanoutShimTest_56, AlternationPattern_56) {
  RE2 re("abc|def|ghi");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  EXPECT_FALSE(histogram.empty());
}

// Test with a character class pattern
TEST_F(RE2ProgramFanoutShimTest_56, CharacterClassPattern_56) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  EXPECT_FALSE(histogram.empty());
}

// Test with a complex pattern with quantifiers
TEST_F(RE2ProgramFanoutShimTest_56, ComplexPatternWithQuantifiers_56) {
  RE2 re("(a+)(b*)(c?)(d{2,5})");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  EXPECT_FALSE(histogram.empty());
}

// Test with a single character pattern
TEST_F(RE2ProgramFanoutShimTest_56, SingleCharPattern_56) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  EXPECT_FALSE(histogram.empty());
}

// Test with a dot-star pattern
TEST_F(RE2ProgramFanoutShimTest_56, DotStarPattern_56) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  EXPECT_FALSE(histogram.empty());
}

// Test with an empty pattern
TEST_F(RE2ProgramFanoutShimTest_56, EmptyPattern_56) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  // Even an empty pattern compiles to a program; histogram may or may not be empty
  // Just ensure no crash
}

// Test that calling the shim multiple times yields the same result
TEST_F(RE2ProgramFanoutShimTest_56, Idempotency_56) {
  RE2 re("foo(bar|baz)+qux");
  ASSERT_TRUE(re.ok());
  
  std::vector<int> result1 = RE2ProgramFanoutShim(re);
  std::vector<int> result2 = RE2ProgramFanoutShim(re);
  
  EXPECT_EQ(result1, result2);
}

// Test with nested groups
TEST_F(RE2ProgramFanoutShimTest_56, NestedGroups_56) {
  RE2 re("((a|b)(c|d))+");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  EXPECT_FALSE(histogram.empty());
}

// Test with a pattern involving anchors
TEST_F(RE2ProgramFanoutShimTest_56, AnchoredPattern_56) {
  RE2 re("^start.*end$");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  EXPECT_FALSE(histogram.empty());
}

// Test that histogram values are non-negative
TEST_F(RE2ProgramFanoutShimTest_56, HistogramValuesNonNegative_56) {
  RE2 re("(a|b|c|d|e)(f|g|h)");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  for (size_t i = 0; i < histogram.size(); ++i) {
    EXPECT_GE(histogram[i], 0) << "Histogram entry at index " << i << " is negative";
  }
}

// Test with a large alternation
TEST_F(RE2ProgramFanoutShimTest_56, LargeAlternation_56) {
  RE2 re("a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  EXPECT_FALSE(histogram.empty());
}

// Test that the histogram size relates to ProgramSize
TEST_F(RE2ProgramFanoutShimTest_56, HistogramSizeRelation_56) {
  RE2 re("(abc)+(def)*");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram = RE2ProgramFanoutShim(re);
  int programSize = re.ProgramSize();
  // The histogram should have as many entries as there are instructions in the program
  // (each entry corresponds to one instruction's fanout bucket)
  EXPECT_EQ(static_cast<int>(histogram.size()), programSize);
}
