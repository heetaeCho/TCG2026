// File: sparse_array_assign_copy_tests_80.cc
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

// Headers under test
#include "re2/sparse_array.h"

// Convenience alias for readability in tests
using SA = re2::SparseArray<int>;

class SparseArrayAssignCopyTest_80 : public ::testing::Test {
protected:
  static SA MakeFilled(int max_size, const std::vector<std::pair<int,int>>& pairs) {
    SA sa(max_size);
    for (const auto& kv : pairs) {
      sa.set(kv.first, kv.second);
    }
    return sa;
  }

  // Verifies that all (index,value) pairs exist with exact values
  static void ExpectContainsExactly(const SA& sa,
                                    int expected_size,
                                    const std::vector<std::pair<int,int>>& pairs) {
    EXPECT_EQ(sa.size(), expected_size);
    for (const auto& kv : pairs) {
      EXPECT_TRUE(sa.has_index(kv.first)) << "missing index " << kv.first;
      EXPECT_EQ(sa.get_existing(kv.first), kv.second) << "value mismatch at index " << kv.first;
    }
  }
};

// Normal operation: copies size and values from source to destination.
TEST_F(SparseArrayAssignCopyTest_80, CopyAssign_CopiesSizeAndValues_80) {
  const int kMax = 10;
  SA src = MakeFilled(kMax, {{0, 11}, {5, 22}, {9, 33}});
  SA dst(kMax);                   // start empty

  // Exercise: copy-assign
  dst = src;

  // Verify: same size and same contents; indices not set in src should be absent in dst
  ExpectContainsExactly(dst, /*expected_size=*/src.size(), {{0,11}, {5,22}, {9,33}});
  EXPECT_FALSE(dst.has_index(1));
  EXPECT_FALSE(dst.has_index(8));
}

// Destination had content; after assignment it should mirror the source (not retain old data).
TEST_F(SparseArrayAssignCopyTest_80, CopyAssign_OverwritesPreviousContent_80) {
  SA src = MakeFilled(/*max_size=*/8, {{2, 100}, {7, 200}});
  SA dst = MakeFilled(/*max_size=*/8, {{0, 1}, {3, 2}, {6, 3}});
  ASSERT_EQ(dst.size(), 3);  // precondition

  dst = src;

  ExpectContainsExactly(dst, /*expected_size=*/src.size(), {{2,100}, {7,200}});
  EXPECT_FALSE(dst.has_index(0));
  EXPECT_FALSE(dst.has_index(3));
  EXPECT_FALSE(dst.has_index(6));
}

// Max size after copy-assignment should match the source's max size (observable via capacity-boundary behavior).
TEST_F(SparseArrayAssignCopyTest_80, CopyAssign_MaxSizeMatchesSource_80) {
  SA src(/*max_size=*/12);
  // Fill sentinel edges of the source to ensure boundary is usable.
  src.set(0, 1);
  src.set(11, 2);

  SA dst(/*max_size=*/3);
  dst = src;

  // We cannot access private capacity, but we can check boundary indices are usable post-assignment.
  EXPECT_TRUE(dst.has_index(0));
  EXPECT_TRUE(dst.has_index(11));
  EXPECT_EQ(dst.get_existing(0), 1);
  EXPECT_EQ(dst.get_existing(11), 2);

  // And indices outside the source’s boundary (like 12) should not be valid.
  EXPECT_FALSE(dst.has_index(12));
}

// Deep copy: modifying source after assignment does not change destination, and vice versa.
TEST_F(SparseArrayAssignCopyTest_80, CopyAssign_DeepCopyIndependence_80) {
  SA src = MakeFilled(/*max_size=*/6, {{1, 10}, {4, 40}});
  SA dst(/*max_size=*/2);
  dst = src;

  // Mutate source
  src.set(1, 999);   // change existing
  src.set(5, 555);   // add new

  // Destination should remain with original values
  ExpectContainsExactly(dst, /*expected_size=*/2, {{1,10}, {4,40}});
  EXPECT_FALSE(dst.has_index(5));

  // Mutate destination independently
  dst.set(4, 4444);
  dst.set(0, 7);

  // Source should remain unaffected by dst mutations
  ExpectContainsExactly(src, /*expected_size=*/3, {{1,999}, {4,40}, {5,555}});
  EXPECT_FALSE(src.has_index(0));
}

// Self-assignment: object remains unchanged and operation is safe.
TEST_F(SparseArrayAssignCopyTest_80, CopyAssign_SelfAssignment_NoChange_80) {
  SA sa = MakeFilled(/*max_size=*/5, {{0, 3}, {3, 9}});

  const int before_size = sa.size();
  const bool has0 = sa.has_index(0);
  const bool has3 = sa.has_index(3);
  const int v0 = sa.get_existing(0);
  const int v3 = sa.get_existing(3);

  // Exercise: self assign
  sa = sa;

  // Verify: unchanged
  EXPECT_EQ(sa.size(), before_size);
  EXPECT_EQ(sa.has_index(0), has0);
  EXPECT_EQ(sa.has_index(3), has3);
  EXPECT_EQ(sa.get_existing(0), v0);
  EXPECT_EQ(sa.get_existing(3), v3);
}

// Assigning from an empty source: destination becomes empty and indices disappear.
TEST_F(SparseArrayAssignCopyTest_80, CopyAssign_FromEmptySource_MakesDestEmpty_80) {
  SA src(/*max_size=*/8);  // empty
  SA dst = MakeFilled(/*max_size=*/8, {{2, 1}, {4, 2}});
  ASSERT_EQ(dst.size(), 2);  // precondition

  dst = src;

  EXPECT_EQ(dst.size(), 0);
  EXPECT_FALSE(dst.has_index(2));
  EXPECT_FALSE(dst.has_index(4));

  // Boundary behavior still matches source capacity (we can at least set within source's bounds after copy)
  dst.set(0, 123);
  dst.set(7, 456);
  EXPECT_EQ(dst.size(), 2);
  EXPECT_TRUE(dst.has_index(0));
  EXPECT_TRUE(dst.has_index(7));
  EXPECT_FALSE(dst.has_index(8));  // outside original source max_size
}

// Optional: iterator sanity—distance between begin/end should reflect size after copy-assignment.
TEST_F(SparseArrayAssignCopyTest_80, CopyAssign_IteratorDistanceReflectsSize_80) {
  SA src = MakeFilled(/*max_size=*/10, {{1, 5}, {3, 6}, {9, 7}});
  SA dst(/*max_size=*/4);

  dst = src;

  const auto it_dist = std::distance(dst.begin(), dst.end());
  EXPECT_EQ(it_dist, dst.size());
}
