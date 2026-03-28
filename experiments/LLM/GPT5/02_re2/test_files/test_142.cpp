// File: rune_range_less_test_142.cc
#include <gtest/gtest.h>
#include <set>
#include "./TestProjects/re2/re2/regexp.h"

using re2::RuneRange;
using re2::RuneRangeLess;
using re2::RuneRangeSet;

class RuneRangeLessTest_142 : public ::testing::Test {
protected:
  RuneRangeLess comp_;
};

// Normal operation: a strictly before b
TEST_F(RuneRangeLessTest_142, StrictlyBefore_ReturnsTrue_142) {
  RuneRange a(/*lo=*/0, /*hi=*/5);
  RuneRange b(/*lo=*/6, /*hi=*/10);

  EXPECT_TRUE(comp_(a, b));
  EXPECT_FALSE(comp_(b, a));
}

// Boundary condition: touching ranges (a.hi == b.lo) are NOT considered a<b
TEST_F(RuneRangeLessTest_142, TouchingRanges_NotLessEitherWay_142) {
  RuneRange a(0, 5);
  RuneRange b(5, 10);

  EXPECT_FALSE(comp_(a, b));
  EXPECT_FALSE(comp_(b, a));
}

// Overlap condition: overlapping ranges are NOT less either way
TEST_F(RuneRangeLessTest_142, OverlappingRanges_NotLessEitherWay_142) {
  RuneRange a(0, 7);
  RuneRange b(3, 10);

  EXPECT_FALSE(comp_(a, b));
  EXPECT_FALSE(comp_(b, a));
}

// Set interaction: overlapping/touching ranges are considered equivalent keys; second insert fails
TEST_F(RuneRangeLessTest_142, SetInsertion_EquivalentWhenOverlapOrTouch_142) {
  RuneRangeSet s;

  // Insert first range
  auto [it1, inserted1] = s.insert(RuneRange(0, 5));
  ASSERT_TRUE(inserted1);
  ASSERT_EQ(s.size(), 1u);

  // Insert overlapping range -> should NOT insert (equivalent under comparator)
  auto [it2, inserted2] = s.insert(RuneRange(3, 4));
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(s.size(), 1u);

  // Insert touching range -> should also NOT insert
  auto [it3, inserted3] = s.insert(RuneRange(5, 9));
  EXPECT_FALSE(inserted3);
  EXPECT_EQ(s.size(), 1u);

  // The set still contains exactly one equivalent element
  (void)it1; (void)it2; (void)it3; // silence unused warnings
}

// Set ordering with disjoint ranges: earlier range compares less; order is consistent
TEST_F(RuneRangeLessTest_142, SetOrdering_WithDisjointRanges_142) {
  RuneRangeSet s;
  RuneRange r1(0, 1);
  RuneRange r2(2, 3);
  RuneRange r3(5, 8);

  // All are pairwise disjoint and strictly ordered by the comparator
  auto i1 = s.insert(r2);  // insert out of order to ensure comparator governs placement
  auto i2 = s.insert(r3);
  auto i3 = s.insert(r1);
  ASSERT_TRUE(i1.second);
  ASSERT_TRUE(i2.second);
  ASSERT_TRUE(i3.second);
  ASSERT_EQ(s.size(), 3u);

  // Verify comparator relationships using the elements as stored
  auto it = s.begin();
  auto first = *it; ++it;
  auto second = *it; ++it;
  auto third = *it;

  // first < second and second < third under the comparator
  EXPECT_TRUE(RuneRangeLess()(first, second));
  EXPECT_TRUE(RuneRangeLess()(second, third));
  EXPECT_FALSE(RuneRangeLess()(second, first));
  EXPECT_FALSE(RuneRangeLess()(third, second));
}

// Asymmetry check: if a<b is false because a is after b, then b<a should be true
TEST_F(RuneRangeLessTest_142, AfterVsBefore_Asymmetry_142) {
  RuneRange a(10, 20); // after
  RuneRange b(0, 5);   // before

  EXPECT_FALSE(comp_(a, b)); // a.hi < b.lo ? 20 < 0 -> false
  EXPECT_TRUE(comp_(b, a));  // b.hi < a.lo ? 5 < 10 -> true
}
