#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "re2/re2.h"

// Include the shim function declaration
namespace re2_python {
std::vector<int> RE2ReverseProgramFanoutShim(const RE2& self);
}

class RE2ReverseProgramFanoutShimTest_57 : public ::testing::Test {
protected:
};

// Test that a simple literal pattern returns a non-empty histogram
TEST_F(RE2ReverseProgramFanoutShimTest_57, SimpleLiteralPattern_57) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  // A valid compiled pattern should produce some fanout histogram
  // We just verify it doesn't crash and returns something
  EXPECT_FALSE(result.empty());
}

// Test with an empty pattern
TEST_F(RE2ReverseProgramFanoutShimTest_57, EmptyPattern_57) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  // Even an empty pattern compiles to a program; just verify no crash
  // Result may or may not be empty depending on implementation
}

// Test with a single character pattern
TEST_F(RE2ReverseProgramFanoutShimTest_57, SingleCharPattern_57) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test with a character class pattern
TEST_F(RE2ReverseProgramFanoutShimTest_57, CharacterClassPattern_57) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test with alternation pattern
TEST_F(RE2ReverseProgramFanoutShimTest_57, AlternationPattern_57) {
  RE2 re("abc|def|ghi");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test with a complex pattern containing groups
TEST_F(RE2ReverseProgramFanoutShimTest_57, ComplexPatternWithGroups_57) {
  RE2 re("(a+)(b+)(c+)");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test with a repetition/quantifier pattern
TEST_F(RE2ReverseProgramFanoutShimTest_57, RepetitionPattern_57) {
  RE2 re("a{2,5}b{3,7}");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test with a dot-star pattern
TEST_F(RE2ReverseProgramFanoutShimTest_57, DotStarPattern_57) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test consistency: calling twice on the same RE2 should give the same result
TEST_F(RE2ReverseProgramFanoutShimTest_57, ConsistentResults_57) {
  RE2 re("foo(bar|baz)+qux");
  ASSERT_TRUE(re.ok());
  std::vector<int> result1 = re2_python::RE2ReverseProgramFanoutShim(re);
  std::vector<int> result2 = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_EQ(result1, result2);
}

// Test that shim result matches direct ReverseProgramFanout call
TEST_F(RE2ReverseProgramFanoutShimTest_57, MatchesDirectCall_57) {
  RE2 re("(abc)|(def)");
  ASSERT_TRUE(re.ok());
  
  std::vector<int> shim_result = re2_python::RE2ReverseProgramFanoutShim(re);
  
  std::vector<int> direct_result;
  re.ReverseProgramFanout(&direct_result);
  
  EXPECT_EQ(shim_result, direct_result);
}

// Test with nested groups
TEST_F(RE2ReverseProgramFanoutShimTest_57, NestedGroups_57) {
  RE2 re("((a)(b(c)))");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test with anchored pattern
TEST_F(RE2ReverseProgramFanoutShimTest_57, AnchoredPattern_57) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test that histogram size matches ReverseProgramSize
TEST_F(RE2ReverseProgramFanoutShimTest_57, HistogramSizeMatchesReverseProgramSize_57) {
  RE2 re("a(b|c)d");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  int rps = re.ReverseProgramSize();
  // The histogram vector should have size equal to ReverseProgramSize
  EXPECT_EQ(static_cast<int>(result.size()), rps);
}

// Test with a long alternation pattern
TEST_F(RE2ReverseProgramFanoutShimTest_57, LongAlternation_57) {
  RE2 re("a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test with optional elements
TEST_F(RE2ReverseProgramFanoutShimTest_57, OptionalElements_57) {
  RE2 re("a?b?c?d?");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  EXPECT_FALSE(result.empty());
}

// Test all histogram values are non-negative
TEST_F(RE2ReverseProgramFanoutShimTest_57, AllValuesNonNegative_57) {
  RE2 re("(foo)|(bar)|(baz)");
  ASSERT_TRUE(re.ok());
  std::vector<int> result = re2_python::RE2ReverseProgramFanoutShim(re);
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_GE(result[i], 0) << "Negative value at index " << i;
  }
}
