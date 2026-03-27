// File: sparse_array_has_index_test_85.cc
#include <gtest/gtest.h>
#include "re2/sparse_array.h"

using re2::SparseArray;

// NOTE: These tests treat SparseArray as a black box and verify only observable
// behavior via its public API. We assume assertions are enabled in the test build
// so out-of-range indices trigger death tests.

namespace {

// Helper: construct an array of a given max size for int values.
static SparseArray<int> MakeArray(int max_size) {
  return SparseArray<int>(max_size);
}

// ---------- Normal & Boundary Behavior ----------

TEST(SparseArrayHasIndexTest_85, InitiallyFalseForAllValidIndices_85) {
  auto arr = MakeArray(4);
  for (int i = 0; i < 4; ++i) {
    EXPECT_FALSE(arr.has_index(i)) << "Expected no index to be set initially at " << i;
  }
}

TEST(SparseArrayHasIndexTest_85, TrueAfterSetNewForThatIndexOnly_85) {
  auto arr = MakeArray(5);

  // Before: all false
  EXPECT_FALSE(arr.has_index(2));
  EXPECT_FALSE(arr.has_index(3));

  // Act: set a value at index 3 (observable via has_index)
  arr.set_new(3, 123);

  // Only index 3 becomes present
  EXPECT_TRUE(arr.has_index(3));
  EXPECT_FALSE(arr.has_index(2));
  EXPECT_FALSE(arr.has_index(4));
}

TEST(SparseArrayHasIndexTest_85, RemainsTrueAfterSetExisting_85) {
  auto arr = MakeArray(3);
  arr.set_new(1, 10);
  ASSERT_TRUE(arr.has_index(1));

  // Update existing (still observable as present)
  arr.set_existing(1, 20);
  EXPECT_TRUE(arr.has_index(1));
}

TEST(SparseArrayHasIndexTest_85, BecomesFalseAfterClear_85) {
  auto arr = MakeArray(3);
  arr.set_new(0, 7);
  ASSERT_TRUE(arr.has_index(0));

  arr.clear();
  EXPECT_FALSE(arr.has_index(0));
  EXPECT_FALSE(arr.has_index(1));
  EXPECT_FALSE(arr.has_index(2));
}

TEST(SparseArrayHasIndexTest_85, AfterResizeWithinBoundsQueryIsAllowed_85) {
  auto arr = MakeArray(2);
  // Valid queries for 0..1 before resize
  EXPECT_FALSE(arr.has_index(0));
  EXPECT_FALSE(arr.has_index(1));

  // Increase capacity; newly valid indices should be queryable and initially absent
  arr.resize(5);
  EXPECT_FALSE(arr.has_index(2));
  EXPECT_FALSE(arr.has_index(4));

  // And setting within new range should reflect in has_index
  arr.set_new(4, 99);
  EXPECT_TRUE(arr.has_index(4));
  EXPECT_FALSE(arr.has_index(3));
}

// ---------- Exceptional / Error (assert) Behavior ----------

#if GTEST_HAS_DEATH_TEST
TEST(SparseArrayHasIndexTest_85, DeathOnNegativeIndex_85) {
  auto arr = MakeArray(3);
  ASSERT_DEATH({ (void)arr.has_index(-1); }, ".*");
}

TEST(SparseArrayHasIndexTest_85, DeathOnIndexEqualToMaxSize_85) {
  auto arr = MakeArray(3);
  // Valid: 0,1,2; Index 3 is out of range.
  ASSERT_DEATH({ (void)arr.has_index(3); }, ".*");
}

TEST(SparseArrayHasIndexTest_85, DeathOnIndexGreaterThanMaxSize_85) {
  auto arr = MakeArray(3);
  ASSERT_DEATH({ (void)arr.has_index(100); }, ".*");
}

TEST(SparseArrayHasIndexTest_85, DeathAfterResizeForNowOutOfRangeIndex_85) {
  auto arr = MakeArray(5);
  // Querying in range is fine
  EXPECT_FALSE(arr.has_index(4));

  // Shrink and then querying an index >= new max_size should assert
  arr.resize(2);
  ASSERT_DEATH({ (void)arr.has_index(2); }, ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
