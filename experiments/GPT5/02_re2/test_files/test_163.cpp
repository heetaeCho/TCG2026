// File: charclassbuilder_begin_test_163.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::CharClassBuilder;

class CharClassBuilderBeginTest_163 : public ::testing::Test {
protected:
  // Utility to count elements using only public begin()/end()
  static int CountByIteration(CharClassBuilder& cc) {
    int count = 0;
    for (auto it = cc.begin(); it != cc.end(); ++it) {
      ++count;
    }
    return count;
  }
};

// [Empty] begin() == end() when the set is empty.
TEST_F(CharClassBuilderBeginTest_163, BeginOnEmptyReturnsEnd_163) {
  CharClassBuilder cc;
  EXPECT_TRUE(cc.empty());
  EXPECT_EQ(cc.begin(), cc.end());
  EXPECT_EQ(0, cc.size());
  EXPECT_EQ(0, CountByIteration(cc));
}

// [Non-empty] After adding a range, begin() != end().
TEST_F(CharClassBuilderBeginTest_163, BeginAfterAddRange_NotEnd_163) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange('a', 'c'));  // Use only public AddRange interface
  EXPECT_FALSE(cc.empty());
  EXPECT_NE(cc.begin(), cc.end());
  EXPECT_GE(cc.size(), 1);
  EXPECT_EQ(cc.size(), CountByIteration(cc));
}

// [Iteration] Iteration from begin() to end() visits exactly size() elements.
TEST_F(CharClassBuilderBeginTest_163, BeginIteratesAllElementsEqualsSize_163) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange('a', 'a'));
  ASSERT_TRUE(cc.AddRange('d', 'f'));
  ASSERT_TRUE(cc.AddRange('m', 'p'));

  // We don't assume ordering or contents; we only compare counts.
  const int iter_count = CountByIteration(cc);
  EXPECT_EQ(cc.size(), iter_count);
  EXPECT_NE(cc.begin(), cc.end());
}

// [Stability w/o mutation] Multiple calls to begin() (no intervening changes) yield equal iterators.
TEST_F(CharClassBuilderBeginTest_163, BeginMultipleCallsConsistent_163) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange('x', 'z'));

  auto it1 = cc.begin();
  auto it2 = cc.begin();
  EXPECT_EQ(it1, it2);

  // Verify the container remains iterable and counts match size().
  EXPECT_EQ(cc.size(), CountByIteration(cc));
}

// [Mutation leading to empty] After removing above a threshold that excludes all ranges,
// begin() should equal end() again.
TEST_F(CharClassBuilderBeginTest_163, BeginReflectsEmptyAfterRemoveAbove_163) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange('b', 'b'));  // single-point range above 'a'

  EXPECT_NE(cc.begin(), cc.end());
  EXPECT_FALSE(cc.empty());
  EXPECT_EQ(cc.size(), CountByIteration(cc));

  // Remove everything above 'a' — this should eliminate the 'b'..'b' range
  cc.RemoveAbove('a');

  // Observe only via public API:
  EXPECT_TRUE(cc.empty());
  EXPECT_EQ(0, cc.size());
  EXPECT_EQ(cc.begin(), cc.end());
  EXPECT_EQ(0, CountByIteration(cc));
}
