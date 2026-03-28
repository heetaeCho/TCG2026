// File: sparse_set_test_585.cc
// Purpose: Black-box tests for re2::SparseSetT / re2::SparseSet
// Notes:
//  - Tests only observable behavior via the public interface (size, empty,
//    max_size, begin/end iteration, insert/insert_new, contains, clear, resize, less).
//  - No assumptions about internal layout/order; iteration checks only set
//    membership and counts.
//  - No out-of-range insertions (behavior may be undefined/assert-dependent).

#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
#include "re2/sparse_set.h"

namespace {

using re2::SparseSet;           // typedef SparseSetT<void>
using re2::SparseSetT;

class SparseSetTest_585 : public ::testing::Test {};

TEST_F(SparseSetTest_585, ConstructWithMaxSizeBasics_585) {
  const int kMax = 8;
  SparseSet set(kMax);

  EXPECT_EQ(set.size(), 0);
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.max_size(), kMax);
  EXPECT_EQ(set.begin(), set.end()); // no elements → empty iteration range
}

TEST_F(SparseSetTest_585, InsertAndContains_585) {
  SparseSet set(10);

  auto it = set.insert(3);
  ASSERT_NE(it, set.end());
  EXPECT_EQ(*it, 3);
  EXPECT_TRUE(set.contains(3));
  EXPECT_EQ(set.size(), 1);
  EXPECT_FALSE(set.empty());

  // Another distinct element
  auto it2 = set.insert(7);
  ASSERT_NE(it2, set.end());
  EXPECT_EQ(*it2, 7);
  EXPECT_TRUE(set.contains(7));
  EXPECT_EQ(set.size(), 2);
}

TEST_F(SparseSetTest_585, InsertDuplicateDoesNotIncreaseSize_585) {
  SparseSet set(10);

  set.insert(4);
  const int before = set.size();

  auto it_dup = set.insert(4);
  ASSERT_NE(it_dup, set.end());
  EXPECT_EQ(*it_dup, 4);
  EXPECT_TRUE(set.contains(4));
  EXPECT_EQ(set.size(), before);  // set semantics: no growth on duplicate
}

TEST_F(SparseSetTest_585, InsertNewReturnsIteratorAndGrows_585) {
  SparseSet set(10);
  EXPECT_EQ(set.size(), 0);

  auto it = set.insert_new(2);
  ASSERT_NE(it, set.end());
  EXPECT_EQ(*it, 2);
  EXPECT_TRUE(set.contains(2));
  EXPECT_EQ(set.size(), 1);
}

TEST_F(SparseSetTest_585, IterationYieldsAllInsertedElements_585) {
  SparseSet set(16);
  const int elems[] = {1, 3, 5, 9};

  for (int v : elems) {
    set.insert_new(v);
  }
  EXPECT_EQ(set.size(), static_cast<int>(std::size(elems)));

  std::vector<int> seen;
  for (auto it = set.begin(); it != set.end(); ++it) {
    seen.push_back(*it);
  }
  EXPECT_EQ(static_cast<int>(seen.size()), set.size());

  for (int v : elems) {
    EXPECT_TRUE(std::find(seen.begin(), seen.end(), v) != seen.end());
  }
}

TEST_F(SparseSetTest_585, ClearResetsState_585) {
  SparseSet set(12);
  set.insert(3);
  set.insert(6);
  ASSERT_EQ(set.size(), 2);

  set.clear();
  EXPECT_EQ(set.size(), 0);
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.begin(), set.end());
  EXPECT_FALSE(set.contains(3));
  EXPECT_FALSE(set.contains(6));
}

TEST_F(SparseSetTest_585, ResizeGrowPreservesElementsAndAllowsNewRange_585) {
  SparseSet set(8);
  set.insert_new(1);
  set.insert_new(6);
  ASSERT_TRUE(set.contains(1));
  ASSERT_TRUE(set.contains(6));
  const int old_size = set.size();

  // Grow capacity
  set.resize(20);
  EXPECT_EQ(set.max_size(), 20);
  // Existing elements remain observable
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(6));
  EXPECT_EQ(set.size(), old_size);

  // New insertion in the extended range
  auto it = set.insert_new(17);
  ASSERT_NE(it, set.end());
  EXPECT_EQ(*it, 17);
  EXPECT_TRUE(set.contains(17));
  EXPECT_EQ(set.size(), old_size + 1);
}

TEST_F(SparseSetTest_585, ContainsReturnsFalseForMissing_585) {
  SparseSet set(10);
  set.insert(2);
  EXPECT_FALSE(set.contains(0));
  EXPECT_FALSE(set.contains(1));
  EXPECT_FALSE(set.contains(3));
  EXPECT_FALSE(set.contains(9));
}

TEST_F(SparseSetTest_585, StaticLessIsStrictOrderingForInts_585) {
  // Using the static comparator as advertised by the interface.
  EXPECT_TRUE(SparseSetT<void>::less(1, 2));
  EXPECT_FALSE(SparseSetT<void>::less(2, 1));
  EXPECT_FALSE(SparseSetT<void>::less(3, 3)); // strict: not less when equal
}

}  // namespace
