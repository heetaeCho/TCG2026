// File: sparse_array_end_test_73.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "re2/sparse_array.h"  // Adjust include path if needed

using ::testing::Eq;
using ::testing::Le;
using ::testing::Ge;

namespace {

template <typename T>
ptrdiff_t IterDistance(typename re2::SparseArray<T>::iterator b,
                       typename re2::SparseArray<T>::iterator e) {
  // Only uses public iterator type and std::distance semantics.
  return std::distance(b, e);
}

class SparseArrayEndTest_73 : public ::testing::Test {
 protected:
  // Use an int payload to avoid any destructor/ownership complexities.
  re2::SparseArray<int> arr_;
};

TEST_F(SparseArrayEndTest_73, EndEqualsBeginWhenEmpty_73) {
  // Preconditions for an empty container.
  EXPECT_EQ(arr_.size(), 0);
  EXPECT_EQ(arr_.begin(), arr_.end());
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), 0);
}

TEST_F(SparseArrayEndTest_73, EndUnaffectedByMaxSizeOnConstruction_73) {
  // Construct with explicit max size; size is still zero, so end==begin.
  re2::SparseArray<int> a_with_cap(128);
  EXPECT_EQ(a_with_cap.size(), 0);
  EXPECT_EQ(a_with_cap.begin(), a_with_cap.end());
  EXPECT_EQ(IterDistance<int>(a_with_cap.begin(), a_with_cap.end()), 0);
}

TEST_F(SparseArrayEndTest_73, EndAdvancesAsElementsAreAdded_73) {
  // Add elements at sparse indices; only rely on observable size/iterators.
  arr_.set(0, 10);
  EXPECT_EQ(arr_.size(), 1);
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), 1);

  arr_.set(5, 50);  // Add at non-contiguous index.
  EXPECT_EQ(arr_.size(), 2);
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), 2);

  arr_.set(2, 20);
  EXPECT_EQ(arr_.size(), 3);
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), 3);
}

TEST_F(SparseArrayEndTest_73, EndDoesNotMoveWhenUpdatingExistingIndex_73) {
  // Setting the same index again should not increase observable size,
  // so end() should remain at the same position relative to begin().
  arr_.set(3, 30);
  ASSERT_EQ(arr_.size(), 1);
  const auto dist_before = IterDistance<int>(arr_.begin(), arr_.end());

  // Update existing key using the same public API (no assumptions about internals).
  arr_.set(3, 300);

  EXPECT_EQ(arr_.size(), 1);
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), dist_before);
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), 1);
}

TEST_F(SparseArrayEndTest_73, EndResetsAfterClear_73) {
  arr_.set(1, 1);
  arr_.set(2, 2);
  ASSERT_EQ(arr_.size(), 2);
  ASSERT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), 2);

  arr_.clear();

  EXPECT_EQ(arr_.size(), 0);
  EXPECT_EQ(arr_.begin(), arr_.end());
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), 0);
}

TEST_F(SparseArrayEndTest_73, EndRemainsConsistentAfterGrowingResize_73) {
  // Populate some entries then grow capacity; size and end distance should match.
  arr_.set(10, 100);
  arr_.set(20, 200);
  arr_.set(30, 300);
  ASSERT_EQ(arr_.size(), 3);
  const auto dist_before = IterDistance<int>(arr_.begin(), arr_.end());

  // Grow max size; not asserting on capacity, only on observable invariants.
  arr_.resize(1024);

  EXPECT_EQ(arr_.size(), 3);
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), dist_before);
}

TEST_F(SparseArrayEndTest_73, EndMatchesSizeInvariant_73) {
  // General invariant: distance(begin,end) == size() for a valid container state.
  // Fill with several unique indices.
  for (int i : {0, 2, 4, 8, 16}) {
    arr_.set(i, i * 10);
  }
  EXPECT_EQ(arr_.size(), 5);
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), arr_.size());

  // Update some existing indices; size should not grow and end should stay consistent.
  arr_.set(2, 999);
  arr_.set(8, 888);
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), arr_.size());

  // Insert a new one; both size and end distance should increase by one.
  const auto size_before = arr_.size();
  const auto dist_before = IterDistance<int>(arr_.begin(), arr_.end());
  arr_.set(32, 320);
  EXPECT_EQ(arr_.size(), size_before + 1);
  EXPECT_EQ(IterDistance<int>(arr_.begin(), arr_.end()), dist_before + 1);
}

}  // namespace
