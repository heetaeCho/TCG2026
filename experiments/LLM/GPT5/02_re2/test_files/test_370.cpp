// File: charclassbuilder_addrange_test_370.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/util/utf.h"

using re2::CharClassBuilder;
using re2::RuneRange;
using re2::Runemax;

namespace {

// Helper to materialize current merged ranges via the public begin()/end() API.
static std::vector<RuneRange> CollectRanges(CharClassBuilder& ccb) {
  std::vector<RuneRange> out;
  for (auto it = ccb.begin(); it != ccb.end(); ++it) {
    out.push_back(*it);
  }
  return out;
}

}  // namespace

// Normal: adding a simple, valid singleton range inserts it and returns true.
TEST(CharClassBuilderTest_370, AddSingletonRange_InsertsAndContains_370) {
  CharClassBuilder ccb;
  bool changed = ccb.AddRange(5, 5);
  EXPECT_TRUE(changed);

  auto ranges = CollectRanges(ccb);
  ASSERT_EQ(ranges.size(), 1u);
  EXPECT_EQ(ranges[0].lo, 5);
  EXPECT_EQ(ranges[0].hi, 5);

  EXPECT_TRUE(ccb.Contains(5));
  EXPECT_FALSE(ccb.Contains(4));
  EXPECT_FALSE(ccb.Contains(6));
}

// Boundary: hi < lo is invalid and must return false with no observable change.
TEST(CharClassBuilderTest_370, InvalidRange_HiLessThanLo_ReturnsFalse_370) {
  CharClassBuilder ccb;
  bool changed = ccb.AddRange(10, 9);
  EXPECT_FALSE(changed);

  auto ranges = CollectRanges(ccb);
  EXPECT_TRUE(ranges.empty());
}

// Idempotence: adding a range fully contained in an existing one returns false.
TEST(CharClassBuilderTest_370, AddingContainedRange_ReturnsFalse_NoChange_370) {
  CharClassBuilder ccb;
  ASSERT_TRUE(ccb.AddRange(10, 20));

  bool changed = ccb.AddRange(12, 15);
  EXPECT_FALSE(changed);

  auto ranges = CollectRanges(ccb);
  ASSERT_EQ(ranges.size(), 1u);
  EXPECT_EQ(ranges[0].lo, 10);
  EXPECT_EQ(ranges[0].hi, 20);

  EXPECT_TRUE(ccb.Contains(12));
  EXPECT_TRUE(ccb.Contains(19));
  EXPECT_FALSE(ccb.Contains(9));
  EXPECT_FALSE(ccb.Contains(21));
}

// Merge: overlapping second range should merge into a single combined range.
TEST(CharClassBuilderTest_370, OverlappingRanges_MergeIntoSingleRange_370) {
  CharClassBuilder ccb;
  ASSERT_TRUE(ccb.AddRange(10, 20));

  bool changed = ccb.AddRange(15, 25);
  EXPECT_TRUE(changed);

  auto ranges = CollectRanges(ccb);
  ASSERT_EQ(ranges.size(), 1u);
  EXPECT_EQ(ranges[0].lo, 10);
  EXPECT_EQ(ranges[0].hi, 25);

  EXPECT_TRUE(ccb.Contains(10));
  EXPECT_TRUE(ccb.Contains(25));
  EXPECT_FALSE(ccb.Contains(9));
  EXPECT_FALSE(ccb.Contains(26));
}

// Merge: adjacent ranges (end + 1 == start) should merge.
TEST(CharClassBuilderTest_370, AdjacentRanges_MergeIntoSingleRange_370) {
  CharClassBuilder ccb;
  ASSERT_TRUE(ccb.AddRange(10, 20));

  bool changed = ccb.AddRange(21, 30);  // adjacent to [10,20]
  EXPECT_TRUE(changed);

  auto ranges = CollectRanges(ccb);
  ASSERT_EQ(ranges.size(), 1u);
  EXPECT_EQ(ranges[0].lo, 10);
  EXPECT_EQ(ranges[0].hi, 30);

  EXPECT_TRUE(ccb.Contains(10));
  EXPECT_TRUE(ccb.Contains(30));
  EXPECT_FALSE(ccb.Contains(9));
  EXPECT_FALSE(ccb.Contains(31));
}

// Merge both sides: inserting a bridge range should coalesce neighboring ranges.
TEST(CharClassBuilderTest_370, BridgeRange_CoalescesNeighbors_370) {
  CharClassBuilder ccb;
  ASSERT_TRUE(ccb.AddRange(0, 5));
  ASSERT_TRUE(ccb.AddRange(10, 15));

  bool changed = ccb.AddRange(6, 9);  // bridges [0,5] and [10,15]
  EXPECT_TRUE(changed);

  auto ranges = CollectRanges(ccb);
  ASSERT_EQ(ranges.size(), 1u);
  EXPECT_EQ(ranges[0].lo, 0);
  EXPECT_EQ(ranges[0].hi, 15);

  EXPECT_TRUE(ccb.Contains(0));
  EXPECT_TRUE(ccb.Contains(15));
  EXPECT_FALSE(ccb.Contains(16));
}

// Boundary at 0: adding a range at 0 behaves correctly (no underflow checks).
TEST(CharClassBuilderTest_370, LowerBoundZero_NoUnderflow_370) {
  CharClassBuilder ccb;
  bool changed = ccb.AddRange(0, 0);
  EXPECT_TRUE(changed);

  auto ranges = CollectRanges(ccb);
  ASSERT_EQ(ranges.size(), 1u);
  EXPECT_EQ(ranges[0].lo, 0);
  EXPECT_EQ(ranges[0].hi, 0);

  EXPECT_TRUE(ccb.Contains(0));
  EXPECT_FALSE(ccb.Contains(1));
}

// Boundary at Runemax: adding at the maximum and then adjacent below merges.
TEST(CharClassBuilderTest_370, UpperBoundRunemax_MergeFromBelow_370) {
  CharClassBuilder ccb;

  ASSERT_TRUE(ccb.AddRange(Runemax, Runemax));
  auto r1 = CollectRanges(ccb);
  ASSERT_EQ(r1.size(), 1u);
  EXPECT_EQ(r1[0].lo, Runemax);
  EXPECT_EQ(r1[0].hi, Runemax);
  EXPECT_TRUE(ccb.Contains(Runemax));

  // Now add the adjacent lower rune and ensure merge occurs.
  bool changed = ccb.AddRange(Runemax - 1, Runemax - 1);
  EXPECT_TRUE(changed);

  auto ranges = CollectRanges(ccb);
  ASSERT_EQ(ranges.size(), 1u);
  EXPECT_EQ(ranges[0].lo, Runemax - 1);
  EXPECT_EQ(ranges[0].hi, Runemax);

  EXPECT_TRUE(ccb.Contains(Runemax - 1));
  EXPECT_TRUE(ccb.Contains(Runemax));
}

// ASCII coverage observable via Contains: adding 'A'-'Z' and 'a'-'z' should
// result in membership checks succeeding within and failing outside.
TEST(CharClassBuilderTest_370, AsciiLetterRanges_ContainChecks_370) {
  CharClassBuilder ccb;

  ASSERT_TRUE(ccb.AddRange('A', 'Z'));
  ASSERT_TRUE(ccb.AddRange('a', 'z'));

  // Inside the ranges
  EXPECT_TRUE(ccb.Contains('A'));
  EXPECT_TRUE(ccb.Contains('M'));
  EXPECT_TRUE(ccb.Contains('Z'));
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('m'));
  EXPECT_TRUE(ccb.Contains('z'));

  // Outside the ranges
  EXPECT_FALSE(ccb.Contains('A' - 1));
  EXPECT_FALSE(ccb.Contains('Z' + 1));
  EXPECT_FALSE(ccb.Contains('a' - 1));
  EXPECT_FALSE(ccb.Contains('z' + 1));
}

