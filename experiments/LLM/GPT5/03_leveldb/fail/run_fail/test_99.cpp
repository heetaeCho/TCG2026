// File: db/skiplist_iterator_seektofirst_test_99.cc
#include "db/skiplist.h"
#include "util/arena.h"
#include <gtest/gtest.h>

namespace leveldb {

// Simple total-order comparator for integers matching SkipList's Comparator contract.
struct IntComparator {
  int operator()(int a, int b) const {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
  }
};

class SkipListIteratorTest_99 : public ::testing::Test {
protected:
  Arena arena_;
  IntComparator cmp_;
  SkipList<int, IntComparator> list_;

  SkipListIteratorTest_99()
      : arena_(),
        cmp_(),
        list_(cmp_, &arena_) {}
};

// [Empty] SeekToFirst on an empty list should make iterator invalid.
TEST_F(SkipListIteratorTest_99, SeekToFirst_EmptyList_IsInvalid_99) {
  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToFirst();
  EXPECT_FALSE(it.Valid());
}

// [Single element] SeekToFirst should point to the only element and be valid.
TEST_F(SkipListIteratorTest_99, SeekToFirst_SingleElement_PointsToOnlyKey_99) {
  list_.Insert(10);

  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToFirst();

  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(10, it.key());
}

// [Multiple elements] SeekToFirst should position at the smallest key.
TEST_F(SkipListIteratorTest_99, SeekToFirst_Multiple_PointsToSmallest_99) {
  // Insert in unsorted order
  list_.Insert(5);
  list_.Insert(1);
  list_.Insert(7);
  list_.Insert(3);

  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToFirst();

  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(1, it.key());  // observable: first key encountered is the minimum
}

// [Rewind behavior] After moving elsewhere, SeekToFirst should rewind to first.
TEST_F(SkipListIteratorTest_99, SeekToFirst_RewindsFromOtherPositions_99) {
  list_.Insert(2);
  list_.Insert(4);
  list_.Insert(6);

  SkipList<int, IntComparator>::Iterator it(&list_);

  // Move away from the beginning using public API, then rewind.
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(6, it.key());

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(2, it.key());
}

// [Boundary ordering check] After SeekToFirst, advancing should yield non-decreasing order.
// This asserts the starting point is indeed the beginning of in-order traversal.
TEST_F(SkipListIteratorTest_99, SeekToFirst_StartsInOrderTraversal_99) {
  const int keys[] = {9, 0, 4, -1, 4, 8, 2};  // includes boundary-ish values and a duplicate
  for (int k : keys) list_.Insert(k);

  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToFirst();

  // If the list is non-empty, the first position must be valid.
  ASSERT_TRUE(it.Valid());

  // Verify non-decreasing order starting from the first element.
  int prev = it.key();
  it.Next();
  while (it.Valid()) {
    int cur = it.key();
    // Non-decreasing with our comparator
    EXPECT_LE(prev, cur);
    prev = cur;
    it.Next();
  }
}

}  // namespace leveldb
