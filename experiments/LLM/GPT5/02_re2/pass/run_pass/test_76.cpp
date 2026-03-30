// File: sparse_array_set_test_76.cc
#include <gtest/gtest.h>
#include "re2/sparse_array.h"

namespace re2 {

class SparseArraySetTest_76 : public ::testing::Test {
protected:
  // Use a small explicit capacity to exercise boundary indices cleanly.
  static constexpr int kMax = 10;
  SparseArray<int> arr_{kMax};
};

// Normal operation: inserting a new index returns a valid iterator,
// makes the index present, sets the value, and increases size by 1.
TEST_F(SparseArraySetTest_76, SetNewIndex_InsertsAndVisibleViaQueries_76) {
  EXPECT_EQ(arr_.size(), 0);
  EXPECT_FALSE(arr_.has_index(3));

  auto it = arr_.set(3, 42);

  // Iterator should be valid (i.e., not end()).
  EXPECT_NE(it, arr_.end());

  // Observable effects via public API.
  EXPECT_TRUE(arr_.has_index(3));
  EXPECT_EQ(arr_.get_existing(3), 42);
  EXPECT_EQ(arr_.size(), 1);
}

// Normal + idempotency boundary: setting the same index twice should not
// increase the size, and the value should reflect the latest set().
TEST_F(SparseArraySetTest_76, SetSameIndexTwice_UpdatesValue_SizeUnchanged_76) {
  arr_.set(3, 10);
  EXPECT_EQ(arr_.size(), 1);
  EXPECT_EQ(arr_.get_existing(3), 10);

  auto it2 = arr_.set(3, 99);

  EXPECT_NE(it2, arr_.end());        // Still returns a valid iterator.
  EXPECT_TRUE(arr_.has_index(3));    // Index remains present.
  EXPECT_EQ(arr_.get_existing(3), 99);
  EXPECT_EQ(arr_.size(), 1);          // Size did not grow.
}

// Boundary indices within declared capacity: 0 and max_size()-1 are valid
// if the container was constructed with that capacity.
TEST_F(SparseArraySetTest_76, SetAtBoundaryIndices_0_And_MaxMinusOne_76) {
  ASSERT_EQ(arr_.max_size(), kMax);

  // Lowest valid index.
  auto it0 = arr_.set(0, 111);
  EXPECT_NE(it0, arr_.end());
  EXPECT_TRUE(arr_.has_index(0));
  EXPECT_EQ(arr_.get_existing(0), 111);

  // Highest valid index (max_size()-1).
  auto it_last = arr_.set(kMax - 1, 222);
  EXPECT_NE(it_last, arr_.end());
  EXPECT_TRUE(arr_.has_index(kMax - 1));
  EXPECT_EQ(arr_.get_existing(kMax - 1), 222);

  // Size reflects two distinct indices.
  EXPECT_EQ(arr_.size(), 2);
}

// Multiple inserts at different indices: ensures presence and size
// reflect all unique indices set().
TEST_F(SparseArraySetTest_76, SetMultipleDistinctIndices_IncreasesSize_76) {
  EXPECT_EQ(arr_.size(), 0);

  arr_.set(2, 1);
  arr_.set(5, 2);
  arr_.set(7, 3);

  EXPECT_TRUE(arr_.has_index(2));
  EXPECT_TRUE(arr_.has_index(5));
  EXPECT_TRUE(arr_.has_index(7));

  EXPECT_EQ(arr_.get_existing(2), 1);
  EXPECT_EQ(arr_.get_existing(5), 2);
  EXPECT_EQ(arr_.get_existing(7), 3);

  EXPECT_EQ(arr_.size(), 3);
}

}  // namespace re2
