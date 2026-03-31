#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test that RuneRangeLess returns true when a.hi < b.lo (non-overlapping, a before b)
TEST(RuneRangeLessTest_142, ReturnsTrueWhenAHiLessThanBLo_142) {
  RuneRangeLess less;
  RuneRange a(1, 5);
  RuneRange b(10, 20);
  EXPECT_TRUE(less(a, b));
}

// Test that RuneRangeLess returns false when a.hi >= b.lo (overlapping ranges)
TEST(RuneRangeLessTest_142, ReturnsFalseWhenAHiEqualsBLo_142) {
  RuneRangeLess less;
  RuneRange a(1, 10);
  RuneRange b(10, 20);
  EXPECT_FALSE(less(a, b));
}

// Test that RuneRangeLess returns false when a.hi > b.lo (overlapping)
TEST(RuneRangeLessTest_142, ReturnsFalseWhenAHiGreaterThanBLo_142) {
  RuneRangeLess less;
  RuneRange a(1, 15);
  RuneRange b(10, 20);
  EXPECT_FALSE(less(a, b));
}

// Test that RuneRangeLess returns false when ranges are identical
TEST(RuneRangeLessTest_142, ReturnsFalseForIdenticalRanges_142) {
  RuneRangeLess less;
  RuneRange a(5, 10);
  RuneRange b(5, 10);
  EXPECT_FALSE(less(a, b));
}

// Test reversed order: b before a
TEST(RuneRangeLessTest_142, ReturnsFalseWhenBBeforeA_142) {
  RuneRangeLess less;
  RuneRange a(10, 20);
  RuneRange b(1, 5);
  EXPECT_FALSE(less(a, b));
}

// Test that b before a returns true from b's perspective
TEST(RuneRangeLessTest_142, ReturnsTrueWhenBHiLessThanALo_142) {
  RuneRangeLess less;
  RuneRange a(10, 20);
  RuneRange b(1, 5);
  EXPECT_TRUE(less(b, a));
}

// Test boundary: a.hi is exactly one less than b.lo
TEST(RuneRangeLessTest_142, ReturnsTrueWhenAHiOneLessThanBLo_142) {
  RuneRangeLess less;
  RuneRange a(1, 9);
  RuneRange b(10, 20);
  EXPECT_TRUE(less(a, b));
}

// Test with single-element ranges (lo == hi)
TEST(RuneRangeLessTest_142, SingleElementRangesNoOverlap_142) {
  RuneRangeLess less;
  RuneRange a(5, 5);
  RuneRange b(10, 10);
  EXPECT_TRUE(less(a, b));
  EXPECT_FALSE(less(b, a));
}

// Test with single-element ranges that are the same
TEST(RuneRangeLessTest_142, SingleElementRangesSameValue_142) {
  RuneRangeLess less;
  RuneRange a(5, 5);
  RuneRange b(5, 5);
  EXPECT_FALSE(less(a, b));
  EXPECT_FALSE(less(b, a));
}

// Test with zero ranges
TEST(RuneRangeLessTest_142, ZeroRanges_142) {
  RuneRangeLess less;
  RuneRange a(0, 0);
  RuneRange b(0, 0);
  EXPECT_FALSE(less(a, b));
}

// Test with zero range and positive range
TEST(RuneRangeLessTest_142, ZeroRangeBeforePositiveRange_142) {
  RuneRangeLess less;
  RuneRange a(0, 0);
  RuneRange b(1, 5);
  EXPECT_TRUE(less(a, b));
  EXPECT_FALSE(less(b, a));
}

// Test that it works correctly as a comparator in std::set
TEST(RuneRangeLessTest_142, WorksAsSetComparator_142) {
  std::set<RuneRange, RuneRangeLess> s;
  s.insert(RuneRange(1, 5));
  s.insert(RuneRange(10, 20));
  s.insert(RuneRange(30, 40));
  EXPECT_EQ(s.size(), 3u);
}

// Test that overlapping ranges are considered equivalent in the set
TEST(RuneRangeLessTest_142, OverlappingRangesAreEquivalentInSet_142) {
  std::set<RuneRange, RuneRangeLess> s;
  s.insert(RuneRange(1, 10));
  s.insert(RuneRange(5, 15));  // overlaps with (1,10) since 10 >= 5
  // Since neither less(a,b) nor less(b,a) is true, they are equivalent
  EXPECT_EQ(s.size(), 1u);
}

// Test adjacent ranges (a.hi + 1 == b.lo) are distinct
TEST(RuneRangeLessTest_142, AdjacentRangesAreDistinctInSet_142) {
  std::set<RuneRange, RuneRangeLess> s;
  s.insert(RuneRange(1, 9));
  s.insert(RuneRange(10, 20));
  EXPECT_EQ(s.size(), 2u);
}

// Test with large rune values
TEST(RuneRangeLessTest_142, LargeRuneValues_142) {
  RuneRangeLess less;
  RuneRange a(0, 0x10000);
  RuneRange b(0x20000, 0x10FFFF);
  EXPECT_TRUE(less(a, b));
  EXPECT_FALSE(less(b, a));
}

// Test strict weak ordering: irreflexivity
TEST(RuneRangeLessTest_142, Irreflexivity_142) {
  RuneRangeLess less;
  RuneRange a(3, 7);
  EXPECT_FALSE(less(a, a));
}

// Test asymmetry: if less(a,b) then !less(b,a)
TEST(RuneRangeLessTest_142, Asymmetry_142) {
  RuneRangeLess less;
  RuneRange a(1, 5);
  RuneRange b(10, 20);
  EXPECT_TRUE(less(a, b));
  EXPECT_FALSE(less(b, a));
}

}  // namespace re2
