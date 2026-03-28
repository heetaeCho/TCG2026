// File: sparse_array_set_existing_test_78.cc
#include <gtest/gtest.h>
#include "re2/sparse_array.h"

using namespace re2;

namespace {

// A simple fixture to create a SparseArray<int> with a reasonable capacity.
class SparseArraySetExistingTest_78 : public ::testing::Test {
protected:
  static constexpr int kMax = 32;
  SparseArray<int> arr_{kMax};
};

TEST_F(SparseArraySetExistingTest_78, UpdateExistingValue_78) {
  // Arrange: create an index with an initial value.
  int idx = 5;
  arr_.set_new(idx, 10);
  ASSERT_TRUE(arr_.has_index(idx));
  ASSERT_EQ(arr_.size(), 1);

  // Act: update the existing index.
  auto it = arr_.set_existing(idx, 20);

  // Assert: value updated; size unchanged; iterator is valid (not end()).
  EXPECT_TRUE(arr_.has_index(idx));
  EXPECT_EQ(arr_.get_existing(idx), 20);
  EXPECT_EQ(arr_.size(), 1);
  EXPECT_NE(it, arr_.end());
}

TEST_F(SparseArraySetExistingTest_78, DoesNotInsertWhenMissing_78) {
  // Arrange: pick an index that does not exist yet.
  int idx = 3;
  ASSERT_FALSE(arr_.has_index(idx));
  int size_before = arr_.size();

  // Act: call set_existing on a non-existent index.
  auto it = arr_.set_existing(idx, 7);

  // Assert: no insertion happened; size unchanged; still no such index.
  EXPECT_FALSE(arr_.has_index(idx));
  EXPECT_EQ(arr_.size(), size_before);

  // Note: We do NOT assert what iterator is returned for the "missing" case,
  // since behavior is unspecified by the given interface. We only assert
  // observable state via public methods per the constraints.
  (void)it;  // avoid unused-variable warning while keeping the check minimal.
}

TEST_F(SparseArraySetExistingTest_78, PreservesOtherIndices_78) {
  // Arrange: create two distinct indices.
  int a = 1, b = 4;
  arr_.set_new(a, 111);
  arr_.set_new(b, 222);
  ASSERT_TRUE(arr_.has_index(a));
  ASSERT_TRUE(arr_.has_index(b));
  ASSERT_EQ(arr_.size(), 2);

  // Act: update only 'a'.
  arr_.set_existing(a, 777);

  // Assert: 'a' is updated; 'b' remains unchanged; size unchanged.
  EXPECT_TRUE(arr_.has_index(a));
  EXPECT_TRUE(arr_.has_index(b));
  EXPECT_EQ(arr_.get_existing(a), 777);
  EXPECT_EQ(arr_.get_existing(b), 222);
  EXPECT_EQ(arr_.size(), 2);
}

TEST_F(SparseArraySetExistingTest_78, MultipleUpdatesOnSameIndex_78) {
  // Arrange
  int idx = 8;
  arr_.set_new(idx, 1);
  ASSERT_TRUE(arr_.has_index(idx));
  ASSERT_EQ(arr_.get_existing(idx), 1);

  // Act: perform multiple updates.
  arr_.set_existing(idx, 2);
  arr_.set_existing(idx, 3);
  auto it = arr_.set_existing(idx, 4);

  // Assert: latest value is visible; index remains present; iterator is valid.
  EXPECT_TRUE(arr_.has_index(idx));
  EXPECT_EQ(arr_.get_existing(idx), 4);
  EXPECT_NE(it, arr_.end());
  EXPECT_EQ(arr_.size(), 1);
}

TEST_F(SparseArraySetExistingTest_78, IteratorValidityWhenUpdatingExisting_78) {
  // Arrange
  int idx = 12;
  arr_.set_new(idx, 100);
  ASSERT_TRUE(arr_.has_index(idx));

  // Act
  auto it = arr_.set_existing(idx, 200);

  // Assert: we can only assert non-end() since IndexValue internals are opaque.
  EXPECT_NE(it, arr_.end());
  EXPECT_TRUE(arr_.has_index(idx));
  EXPECT_EQ(arr_.get_existing(idx), 200);
}

}  // namespace
