// File: sparse_set_insert_test_92.cc
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "re2/sparse_set.h"

using namespace re2;

class SparseSetInsertTest_92 : public ::testing::Test {
protected:
  // Helper to collect current elements without making assumptions about order.
  static std::vector<int> Collect(const SparseSet& s) {
    std::vector<int> out;
    for (auto it = const_cast<SparseSet&>(s).begin(); it != const_cast<SparseSet&>(s).end(); ++it) {
      out.push_back(*it);
    }
    return out;
  }
};

// Normal operation: inserting into an empty set adds the element, updates size, and returns a valid iterator.
TEST_F(SparseSetInsertTest_92, InsertIntoEmptyAddsElement_92) {
  SparseSet s(10);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);

  auto it = s.insert(3);

  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(3));
  ASSERT_NE(it, s.end());
  EXPECT_EQ(*it, 3);  // iterator should dereference to the inserted index via public iterator API
}

// Normal operation: inserting multiple distinct elements results in presence of all, size increments appropriately.
TEST_F(SparseSetInsertTest_92, InsertMultipleDistinctElements_92) {
  SparseSet s(16);

  s.insert(1);
  s.insert(5);
  s.insert(7);

  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(5));
  EXPECT_TRUE(s.contains(7));

  // Validate the contents using iteration without assuming order.
  auto elems = Collect(s);
  std::sort(elems.begin(), elems.end());
  std::vector<int> expected{1,5,7};
  EXPECT_EQ(elems, expected);
}

// Idempotency for existing element (observable): calling insert() on an already present element should not duplicate it.
TEST_F(SparseSetInsertTest_92, InsertExistingDoesNotIncreaseSize_92) {
  SparseSet s(8);

  auto it1 = s.insert(2);
  ASSERT_NE(it1, s.end());
  EXPECT_EQ(*it1, 2);
  ASSERT_EQ(s.size(), 1);

  auto it2 = s.insert(2);  // allowed by insert(...) contract in the provided snippet
  EXPECT_EQ(s.size(), 1);  // still a set (no duplicates observable)
  ASSERT_NE(it2, s.end());
  EXPECT_EQ(*it2, 2);
  EXPECT_TRUE(s.contains(2));
}

// Boundary conditions: lowest and highest valid indices within the configured max_size can be inserted.
TEST_F(SparseSetInsertTest_92, InsertBoundaryIndices_92) {
  const int kMax = 5;
  SparseSet s(kMax);

  auto it_low  = s.insert(0);
  auto it_high = s.insert(kMax - 1);

  ASSERT_NE(it_low, s.end());
  ASSERT_NE(it_high, s.end());
  EXPECT_EQ(*it_low, 0);
  EXPECT_EQ(*it_high, kMax - 1);

  EXPECT_EQ(s.size(), 2);
  EXPECT_TRUE(s.contains(0));
  EXPECT_TRUE(s.contains(kMax - 1));
}

// State reset interaction: after clear(), insert should behave as if the set were empty.
TEST_F(SparseSetInsertTest_92, InsertAfterClearBehavesFresh_92) {
  SparseSet s(10);

  s.insert(4);
  s.insert(6);
  ASSERT_EQ(s.size(), 2);
  s.clear();

  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(4));
  EXPECT_FALSE(s.contains(6));

  auto it = s.insert(4);
  ASSERT_NE(it, s.end());
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(4));
}

// Interaction with resize: after enlarging capacity, insert new indices within the new range.
TEST_F(SparseSetInsertTest_92, InsertWorksAfterEnlargeResize_92) {
  SparseSet s(3);
  s.insert(0);
  s.insert(1);
  EXPECT_EQ(s.size(), 2);

  s.resize(6);  // enlarge capacity; behavior is observable via subsequent valid inserts
  auto it = s.insert(5);
  ASSERT_NE(it, s.end());
  EXPECT_EQ(*it, 5);
  EXPECT_TRUE(s.contains(5));
  EXPECT_EQ(s.size(), 3);
}
