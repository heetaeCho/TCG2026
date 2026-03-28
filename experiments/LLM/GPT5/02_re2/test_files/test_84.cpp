// File: sparse_array_resize_test_84.cc
#include <gtest/gtest.h>
#include "re2/sparse_array.h"

using re2::SparseArray;

// Helper: count logical elements via public iteration only.
template <typename T>
static int CountElements(SparseArray<T>& arr) {
  int n = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) ++n;
  return n;
}

class SparseArrayResizeTest_84 : public ::testing::Test {
protected:
  using T = int;
};

// --- Normal operation: grow ---
// Growing max size should not change the number of set elements,
// should preserve existing indices/values, and should update max_size().
TEST_F(SparseArrayResizeTest_84, ResizeIncrease_PreservesContentsAndSize_84) {
  SparseArray<int> arr(10);
  arr.set(2, 20);
  arr.set(7, 70);
  ASSERT_EQ(arr.size(), 2);
  ASSERT_EQ(CountElements(arr), 2);

  arr.resize(20);

  // Size unchanged; capacity (max_size) increased.
  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(CountElements(arr), 2);
  EXPECT_EQ(arr.max_size(), 20);

  // Indices remain present and values retrievable.
  EXPECT_TRUE(arr.has_index(2));
  EXPECT_TRUE(arr.has_index(7));
  EXPECT_EQ(arr.get_existing(2), 20);
  EXPECT_EQ(arr.get_existing(7), 70);
}

// --- Normal operation: shrink ---
// Shrinking max size below some existing indices should drop those out-of-range
// entries and reduce size accordingly, while keeping valid in-range entries.
TEST_F(SparseArrayResizeTest_84, ResizeDecrease_DropsOutOfRangeEntries_84) {
  SparseArray<int> arr(10);
  arr.set(2, 20);
  arr.set(7, 70);
  ASSERT_EQ(arr.size(), 2);

  // After resize to 5, index 7 should no longer be valid.
  arr.resize(5);

  EXPECT_EQ(arr.max_size(), 5);
  EXPECT_TRUE(arr.has_index(2));
  EXPECT_FALSE(arr.has_index(7));

  // Only the in-range element remains.
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(CountElements(arr), 1);
  EXPECT_EQ(arr.get_existing(2), 20);
}

// --- Boundary: resize to zero ---
// Resizing to zero should clear all elements; begin == end, size == 0.
TEST_F(SparseArrayResizeTest_84, ResizeToZero_ClearsAll_84) {
  SparseArray<int> arr(4);
  arr.set(0, 1);
  arr.set(3, 9);
  ASSERT_EQ(arr.size(), 2);

  arr.resize(0);

  EXPECT_EQ(arr.max_size(), 0);
  EXPECT_EQ(arr.size(), 0);
  EXPECT_EQ(CountElements(arr), 0);
  EXPECT_EQ(arr.begin(), arr.end());
  // has_index on any previous index must be false (defensive spot-checks).
  EXPECT_FALSE(arr.has_index(0));
  EXPECT_FALSE(arr.has_index(3));
}

// --- No-op: same size ---
// Resizing to the current max size should be a no-op.
TEST_F(SparseArrayResizeTest_84, ResizeSameSize_NoOp_84) {
  SparseArray<int> arr(6);
  arr.set(1, 10);
  arr.set(5, 50);
  ASSERT_EQ(arr.size(), 2);
  const int old_max = arr.max_size();

  arr.resize(old_max);  // no-op

  EXPECT_EQ(arr.max_size(), old_max);
  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(CountElements(arr), 2);
  EXPECT_TRUE(arr.has_index(1));
  EXPECT_TRUE(arr.has_index(5));
  EXPECT_EQ(arr.get_existing(1), 10);
  EXPECT_EQ(arr.get_existing(5), 50);
}

// --- Grow then insert near new boundary ---
// After growing, we should be able to set a value at a newly valid high index.
TEST_F(SparseArrayResizeTest_84, ResizeIncreaseThenSet_NewHighIndexWorks_84) {
  SparseArray<int> arr(3);
  arr.set(0, 11);
  ASSERT_EQ(arr.size(), 1);

  arr.resize(8);
  EXPECT_EQ(arr.max_size(), 8);
  EXPECT_EQ(arr.size(), 1);

  // Now set near the new upper bound (index 7 is valid if max_size() == 8).
  arr.set(7, 77);
  EXPECT_TRUE(arr.has_index(7));
  EXPECT_EQ(arr.get_existing(7), 77);

  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(CountElements(arr), 2);
}

// --- Boundary across shrink/grow cycles ---
// Setting at the old upper boundary, shrinking below it should drop it,
// and re-growing should NOT magically restore dropped entries.
TEST_F(SparseArrayResizeTest_84, ShrinkThenGrow_DroppedEntriesDoNotReappear_84) {
  SparseArray<int> arr(5); // valid indices: 0..4
  arr.set(4, 44);
  ASSERT_TRUE(arr.has_index(4));
  ASSERT_EQ(arr.size(), 1);

  // Shrink so index 4 becomes out-of-range.
  arr.resize(3); // valid indices: 0..2
  EXPECT_EQ(arr.max_size(), 3);
  EXPECT_FALSE(arr.has_index(4));
  EXPECT_EQ(arr.size(), 0);
  EXPECT_EQ(CountElements(arr), 0);

  // Grow again; previously dropped index should NOT automatically reappear.
  arr.resize(6); // valid indices: 0..5
  EXPECT_EQ(arr.max_size(), 6);
  EXPECT_FALSE(arr.has_index(4));
  EXPECT_EQ(arr.size(), 0);

  // We can set it again now that it's in range.
  arr.set(4, 444);
  EXPECT_TRUE(arr.has_index(4));
  EXPECT_EQ(arr.get_existing(4), 444);
  EXPECT_EQ(arr.size(), 1);
}
