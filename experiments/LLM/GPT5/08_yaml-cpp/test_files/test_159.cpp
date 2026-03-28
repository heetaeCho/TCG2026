// File: ./TestProjects/yaml-cpp/test/regex_and_operator_test_159.cpp

#include <gtest/gtest.h>

#include "regex_yaml.h"

namespace {

class RegExAndOperatorTest_159 : public ::testing::Test {
 protected:
  static void ExpectAndMatchesAgreeForChars(const YAML::RegEx& ex1,
                                           const YAML::RegEx& ex2,
                                           const std::string& charsToTest) {
    const YAML::RegEx combined = ex1 & ex2;

    for (char ch : charsToTest) {
      const bool expected = ex1.Matches(ch) && ex2.Matches(ch);
      EXPECT_EQ(combined.Matches(ch), expected) << "ch=" << static_cast<int>(ch);
    }
  }
};

TEST_F(RegExAndOperatorTest_159, AndAgreesWithBothOperandsForSingleCharMatches_159) {
  const YAML::RegEx isLowerAtoZ('a', 'z');
  const YAML::RegEx isM('m');

  // Basic sanity set including match / non-match.
  ExpectAndMatchesAgreeForChars(isLowerAtoZ, isM, "amzA0");
}

TEST_F(RegExAndOperatorTest_159, AndWithOverlappingRangesBehavesLikeIntersectionOnSamples_159) {
  const YAML::RegEx aToF('a', 'f');
  const YAML::RegEx dToZ('d', 'z');

  // Sample around boundaries and inside/outside overlap.
  ExpectAndMatchesAgreeForChars(aToF, dToZ, "abcdefgxyz");
}

TEST_F(RegExAndOperatorTest_159, AndWithNonOverlappingRangesMatchesNothingOnSamples_159) {
  const YAML::RegEx aToC('a', 'c');
  const YAML::RegEx xToZ('x', 'z');

  // Sample across alphabet segments.
  ExpectAndMatchesAgreeForChars(aToC, xToZ, "abcwxyz");
}

TEST_F(RegExAndOperatorTest_159, AndDoesNotMutateOperands_159) {
  const YAML::RegEx range('a', 'z');
  const YAML::RegEx exact('q');

  const bool beforeRangeQ = range.Matches('q');
  const bool beforeExactQ = exact.Matches('q');

  (void)(range & exact);  // Construct combined; should not change operands.

  EXPECT_EQ(range.Matches('q'), beforeRangeQ);
  EXPECT_EQ(exact.Matches('q'), beforeExactQ);

  // Also re-check a non-matching char to catch accidental broad mutation.
  const bool beforeRangeBang = range.Matches('!');
  const bool beforeExactBang = exact.Matches('!');
  EXPECT_EQ(range.Matches('!'), beforeRangeBang);
  EXPECT_EQ(exact.Matches('!'), beforeExactBang);
}

TEST_F(RegExAndOperatorTest_159, AndIsCommutativeForCharMatchesOnSamples_159) {
  const YAML::RegEx aToZ('a', 'z');
  const YAML::RegEx bToY('b', 'y');

  const YAML::RegEx left = aToZ & bToY;
  const YAML::RegEx right = bToY & aToZ;

  for (char ch : std::string("aabyzA0")) {
    EXPECT_EQ(left.Matches(ch), right.Matches(ch)) << "ch=" << static_cast<int>(ch);
  }
}

TEST_F(RegExAndOperatorTest_159, AndChainingAgreesWithRepeatedConjunctionOnSamples_159) {
  const YAML::RegEx aToZ('a', 'z');
  const YAML::RegEx aToF('a', 'f');
  const YAML::RegEx dToZ('d', 'z');

  const YAML::RegEx chained = (aToZ & aToF) & dToZ;

  for (char ch : std::string("abcdefgxyzA0")) {
    const bool expected = aToZ.Matches(ch) && aToF.Matches(ch) && dToZ.Matches(ch);
    EXPECT_EQ(chained.Matches(ch), expected) << "ch=" << static_cast<int>(ch);
  }
}

}  // namespace
