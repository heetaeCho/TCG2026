// File: sparse_array_set_new_test_77.cc
#include <gtest/gtest.h>
#include "re2/sparse_array.h"

using re2::SparseArray;

class SparseArraySetNewTest_77 : public ::testing::Test {
protected:
  // Helper to create a reasonably sized container for tests
  static SparseArray<int> Make(int max = 16) { return SparseArray<int>(max); }
};

// Normal operation: inserting a brand-new index
TEST_F(SparseArraySetNewTest_77, SetNew_InsertsAndIsRetrievable_77) {
  auto sa = Make(8);
  EXPECT_EQ(sa.size(), 0);

  auto it = sa.set_new(3, 42);
  ASSERT_NE(it, nullptr) << "set_new should succeed for a new index";
  EXPECT_TRUE(sa.has_index(3));
  EXPECT_EQ(sa.get_existing(3), 42);
  EXPECT_EQ(sa.size(), 1);

  // Sanity: other indices remain absent
  EXPECT_FALSE(sa.has_index(0));
  EXPECT_FALSE(sa.has_index(7));
}

// Normal operation with multiple distinct indices
TEST_F(SparseArraySetNewTest_77, SetNew_MultipleDistinctIndices_77) {
  auto sa = Make(10);

  ASSERT_NE(sa.set_new(7, 70), nullptr);
  ASSERT_NE(sa.set_new(2, 20), nullptr);
  ASSERT_NE(sa.set_new(5, 50), nullptr);

  EXPECT_EQ(sa.size(), 3);
  EXPECT_TRUE(sa.has_index(2));
  EXPECT_TRUE(sa.has_index(5));
  EXPECT_TRUE(sa.has_index(7));
  EXPECT_EQ(sa.get_existing(2), 20);
  EXPECT_EQ(sa.get_existing(5), 50);
  EXPECT_EQ(sa.get_existing(7), 70);

  // Iteration span equals size (without assuming iteration order)
  EXPECT_EQ(sa.end() - sa.begin(), sa.size());
}

// Boundary conditions: lowest and highest valid indices
TEST_F(SparseArraySetNewTest_77, SetNew_BoundaryIndices_77) {
  auto sa = Make(6);
  const int lo = 0;
  const int hi = sa.max_size() - 1;

  ASSERT_NE(sa.set_new(lo, 111), nullptr);
  ASSERT_NE(sa.set_new(hi, 999), nullptr);

  EXPECT_TRUE(sa.has_index(lo));
  EXPECT_TRUE(sa.has_index(hi));
  EXPECT_EQ(sa.get_existing(lo), 111);
  EXPECT_EQ(sa.get_existing(hi), 999);
  EXPECT_EQ(sa.size(), 2);
}

// Exceptional/edge (observable via interface): inserting at an existing index
// Expectation: set_new should not create a second entry; it should fail in an
// observable way (e.g., return nullptr) and leave the stored value intact.
TEST_F(SparseArraySetNewTest_77, SetNew_FailsOnExistingIndex_77) {
  auto sa = Make(8);

  ASSERT_NE(sa.set_new(4, 123), nullptr);
  EXPECT_EQ(sa.size(), 1);

  auto dup = sa.set_new(4, 456);  // same index, different value
  EXPECT_EQ(dup, nullptr) << "set_new should indicate failure for existing index";
  EXPECT_EQ(sa.size(), 1) << "size should not increase on failed insertion";
  EXPECT_EQ(sa.get_existing(4), 123) << "existing value should remain unchanged";
}

// Safety: inserting at one index does not affect neighbors
TEST_F(SparseArraySetNewTest_77, SetNew_DoesNotAffectOtherIndices_77) {
  auto sa = Make(9);
  ASSERT_NE(sa.set_new(6, 600), nullptr);

  EXPECT_TRUE(sa.has_index(6));
  EXPECT_EQ(sa.get_existing(6), 600);

  // Adjacent indices remain unset (no accidental side effects)
  EXPECT_FALSE(sa.has_index(5));
  EXPECT_FALSE(sa.has_index(7));
}
