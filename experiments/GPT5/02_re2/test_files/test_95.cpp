// File: sparse_set_contains_test_95.cc
#include <gtest/gtest.h>
#include "re2/sparse_set.h"

using re2::SparseSet;

// Test fixture for reuse.
class SparseSetTest_95 : public ::testing::Test {
protected:
  static constexpr int kMax = 8;
  SparseSetTest_95() : set_(kMax) {}
  SparseSet set_;
};

// --- Normal operation ---

// Empty set should not contain any index within range.
TEST_F(SparseSetTest_95, EmptyDoesNotContain_95) {
  for (int i = 0; i < set_.max_size(); ++i) {
    EXPECT_FALSE(set_.contains(i)) << "Index " << i << " unexpectedly present in empty set";
  }
}

// After inserting an element, contains(i) should be true for that element.
TEST_F(SparseSetTest_95, ContainsAfterInsert_95) {
  ASSERT_EQ(set_.size(), 0);
  (void)set_.insert(3);
  EXPECT_TRUE(set_.contains(3));
  // Non-inserted neighbors should remain false.
  EXPECT_FALSE(set_.contains(2));
  EXPECT_FALSE(set_.contains(4));
  // Size is observable; insertion should increase size by 1.
  EXPECT_EQ(set_.size(), 1);
}

// Boundary elements within range (0 and max_size()-1) behave correctly.
TEST_F(SparseSetTest_95, ContainsBoundaryIndices_95) {
  const int last = set_.max_size() - 1;
  (void)set_.insert(0);
  (void)set_.insert(last);
  EXPECT_TRUE(set_.contains(0));
  EXPECT_TRUE(set_.contains(last));
  // A middle value not inserted should be false.
  EXPECT_FALSE(set_.contains(last / 2));
}

// Clearing the set should make previously inserted elements absent.
TEST_F(SparseSetTest_95, ContainsAfterClearIsFalse_95) {
  (void)set_.insert(5);
  ASSERT_TRUE(set_.contains(5));
  set_.clear();
  EXPECT_EQ(set_.size(), 0);
  EXPECT_FALSE(set_.contains(5));
}

// --- Boundary & exceptional (observable via interface) ---

// Indices >= max_size() should not be contained.
// In debug builds, the asserts may fire; in release, contains() should safely return false.
// We allow either behavior via death-test when available.
TEST_F(SparseSetTest_95, OutOfRangeHighIndex_95) {
  const int hi = set_.max_size(); // first out-of-range index
#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
  EXPECT_DEATH({ (void)set_.contains(hi); }, "");
#else
  EXPECT_FALSE(set_.contains(hi));
#endif
}

// Negative indices should not be contained; same handling as above.
TEST_F(SparseSetTest_95, OutOfRangeNegativeIndex_95) {
#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
  EXPECT_DEATH({ (void)set_.contains(-1); }, "");
#else
  EXPECT_FALSE(set_.contains(-1));
#endif
}

// Ensure contains() does not mutate the set (observable via size()).
TEST_F(SparseSetTest_95, ContainsIsNonMutating_95) {
  (void)set_.insert(1);
  const int before = set_.size();
  (void)set_.contains(1);
  (void)set_.contains(2);
  EXPECT_EQ(set_.size(), before);
}

// --- Resizing-related (interface-observable only) ---

// After increasing capacity, previously inserted elements are still reported by contains()
// and new valid indices remain queryable.
TEST_F(SparseSetTest_95, ContainsAfterIncreaseResize_95) {
  (void)set_.insert(2);
  ASSERT_TRUE(set_.contains(2));
  const int old_max = set_.max_size();
  set_.resize(old_max * 2);
  EXPECT_GE(set_.max_size(), old_max * 2); // Observable via interface
  EXPECT_TRUE(set_.contains(2));           // Previously inserted still recognized

  // Newly in-range index (was out-of-range before) should be false until inserted.
  const int new_idx = old_max + 1;
  ASSERT_LT(new_idx, set_.max_size());
#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
  // In debug builds, this is in range, so no assert expected; just check false.
  EXPECT_FALSE(set_.contains(new_idx));
#else
  EXPECT_FALSE(set_.contains(new_idx));
#endif
}

// Decreasing capacity: querying an index that is now out-of-range should either
// death-assert (debug) or safely return false (release), but in-range ones still work.
TEST_F(SparseSetTest_95, ContainsAfterDecreaseResize_95) {
  (void)set_.insert(6);
  ASSERT_TRUE(set_.contains(6));
  set_.resize(4);
  // 6 is now out-of-range; allow death or false depending on build.
#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
  EXPECT_DEATH({ (void)set_.contains(6); }, "");
#else
  EXPECT_FALSE(set_.contains(6));
#endif

  // In-range query still works.
  if (set_.max_size() > 0) {
    EXPECT_FALSE(set_.contains(0)); // not inserted after resize
  }
}
