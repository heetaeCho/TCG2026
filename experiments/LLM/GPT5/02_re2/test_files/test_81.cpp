// File: sparse_array_move_assign_test_81.cc
#include <gtest/gtest.h>
#include <utility>
#include <vector>

#include "re2/sparse_array.h"

using re2::SparseArray;

namespace {

// Helpers (only use public API)
static void Fill(SparseArray<int>& arr,
                 const std::vector<std::pair<int,int>>& items) {
  for (const auto& kv : items) arr.set(kv.first, kv.second);
}

static void ExpectHasKV(SparseArray<int>& arr, int idx, int val) {
  ASSERT_TRUE(arr.has_index(idx)) << "Expected index " << idx << " to exist";
  EXPECT_EQ(arr.get_existing(idx), val);
}

static void ExpectNotHas(SparseArray<int>& arr, int idx) {
  EXPECT_FALSE(arr.has_index(idx)) << "Did not expect index " << idx << " to exist";
}

}  // namespace

// Normal operation: move from non-empty into empty.
TEST(SparseArrayMoveAssignTest_81, MoveNonEmptyIntoEmpty_81) {
  SparseArray<int> src(/*max_size=*/10);
  Fill(src, {{2, 42}, {7, 99}});
  const int src_size_before = src.size();

  SparseArray<int> dst(/*max_size=*/10);
  ASSERT_EQ(dst.size(), 0);

  dst = std::move(src);

  // Destination takes over source contents (observable via public API).
  EXPECT_EQ(dst.size(), src_size_before);
  ExpectHasKV(dst, 2, 42);
  ExpectHasKV(dst, 7, 99);

  // Moved-from source becomes empty (observable).
  EXPECT_EQ(src.size(), 0);
}

// Boundary: move into a previously non-empty destination; old contents are replaced.
TEST(SparseArrayMoveAssignTest_81, MoveIntoNonEmpty_ReplacesContent_81) {
  SparseArray<int> dst(/*max_size=*/10);
  Fill(dst, {{1, 11}, {3, 33}});

  SparseArray<int> src(/*max_size=*/15);
  Fill(src, {{4, 44}, {9, 99}});
  const int src_size_before = src.size();
  const int src_max_before  = src.max_size();

  dst = std::move(src);

  // Destination reflects the previous source state.
  EXPECT_EQ(dst.size(), src_size_before);
  EXPECT_EQ(dst.max_size(), src_max_before);
  ExpectHasKV(dst, 4, 44);
  ExpectHasKV(dst, 9, 99);

  // Old destination entries are no longer observed.
  ExpectNotHas(dst, 1);
  ExpectNotHas(dst, 3);

  // Source is now empty.
  EXPECT_EQ(src.size(), 0);
}

// Boundary: move-assign from an empty source into a non-empty destination.
TEST(SparseArrayMoveAssignTest_81, MoveFromEmptyIntoNonEmpty_YieldsEmptyDest_81) {
  SparseArray<int> src;  // default-constructed, empty (observable via size()).
  ASSERT_EQ(src.size(), 0);

  SparseArray<int> dst(/*max_size=*/8);
  Fill(dst, {{0, 1}, {5, 50}});
  ASSERT_EQ(dst.size(), 2);

  dst = std::move(src);

  // Destination becomes empty (observable).
  EXPECT_EQ(dst.size(), 0);

  // Source remains a valid, empty container.
  EXPECT_EQ(src.size(), 0);
}

// Exceptional/edge-like: self move-assignment should leave the object usable.
TEST(SparseArrayMoveAssignTest_81, SelfMoveAssignment_LeavesObjectUsable_81) {
  SparseArray<int> a(/*max_size=*/8);
  Fill(a, {{2, 77}});

  // Self move-assignment. We don't assert exact post-state (unspecified),
  // but we require the object to remain valid and usable via public API.
  a = std::move(a);

  // Perform subsequent operations to confirm usability.
  a.set(5, 123);
  ASSERT_TRUE(a.has_index(5));
  EXPECT_EQ(a.get_existing(5), 123);

  // Size should be consistent with observable inserts (at least 1 now).
  EXPECT_GE(a.size(), 1);
}
