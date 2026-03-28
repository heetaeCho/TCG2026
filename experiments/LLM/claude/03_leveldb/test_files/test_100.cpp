#include "db/skiplist.h"
#include "util/arena.h"
#include "gtest/gtest.h"

namespace leveldb {

// Simple comparator for int keys
struct IntComparator {
  int operator()(const int& a, const int& b) const {
    if (a < b) return -1;
    if (a > b) return +1;
    return 0;
  }
};

typedef SkipList<int, IntComparator> IntSkipList;

class SkipListTest_100 : public ::testing::Test {
 protected:
  IntComparator cmp_;
  Arena arena_;
};

// Test: Empty skip list should not contain any key
TEST_F(SkipListTest_100, EmptyListContainsNothing_100) {
  IntSkipList list(cmp_, &arena_);
  ASSERT_FALSE(list.Contains(0));
  ASSERT_FALSE(list.Contains(1));
  ASSERT_FALSE(list.Contains(-1));
  ASSERT_FALSE(list.Contains(100));
}

// Test: Insert a single element and verify Contains
TEST_F(SkipListTest_100, InsertSingleElement_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  ASSERT_TRUE(list.Contains(10));
  ASSERT_FALSE(list.Contains(5));
  ASSERT_FALSE(list.Contains(15));
}

// Test: Insert multiple elements and verify Contains for each
TEST_F(SkipListTest_100, InsertMultipleElements_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(5);
  list.Insert(10);
  list.Insert(15);
  list.Insert(20);

  ASSERT_TRUE(list.Contains(5));
  ASSERT_TRUE(list.Contains(10));
  ASSERT_TRUE(list.Contains(15));
  ASSERT_TRUE(list.Contains(20));
  ASSERT_FALSE(list.Contains(0));
  ASSERT_FALSE(list.Contains(7));
  ASSERT_FALSE(list.Contains(25));
}

// Test: Insert elements in reverse order
TEST_F(SkipListTest_100, InsertReverseOrder_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(100);
  list.Insert(75);
  list.Insert(50);
  list.Insert(25);
  list.Insert(0);

  ASSERT_TRUE(list.Contains(0));
  ASSERT_TRUE(list.Contains(25));
  ASSERT_TRUE(list.Contains(50));
  ASSERT_TRUE(list.Contains(75));
  ASSERT_TRUE(list.Contains(100));
}

// Test: Iterator on empty list should not be valid
TEST_F(SkipListTest_100, IteratorOnEmptyList_100) {
  IntSkipList list(cmp_, &arena_);
  IntSkipList::Iterator iter(&list);
  ASSERT_FALSE(iter.Valid());
}

// Test: SeekToFirst on empty list
TEST_F(SkipListTest_100, SeekToFirstOnEmptyList_100) {
  IntSkipList list(cmp_, &arena_);
  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_FALSE(iter.Valid());
}

// Test: SeekToLast on empty list
TEST_F(SkipListTest_100, SeekToLastOnEmptyList_100) {
  IntSkipList list(cmp_, &arena_);
  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_FALSE(iter.Valid());
}

// Test: SeekToFirst on non-empty list returns smallest element
TEST_F(SkipListTest_100, SeekToFirstReturnsSmallest_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(30);
  list.Insert(10);
  list.Insert(20);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

// Test: SeekToLast on non-empty list returns largest element
TEST_F(SkipListTest_100, SeekToLastReturnsLargest_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(30);
  list.Insert(10);
  list.Insert(20);

  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30, iter.key());
}

// Test: Forward iteration visits all elements in order
TEST_F(SkipListTest_100, ForwardIteration_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(3);
  list.Insert(1);
  list.Insert(4);
  list.Insert(1);  // duplicate
  list.Insert(5);
  list.Insert(9);
  list.Insert(2);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());

  int prev = iter.key();
  iter.Next();
  while (iter.Valid()) {
    ASSERT_GE(iter.key(), prev);
    prev = iter.key();
    iter.Next();
  }
}

// Test: Backward iteration from last visits elements in reverse order
TEST_F(SkipListTest_100, BackwardIteration_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);
  list.Insert(40);
  list.Insert(50);

  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(50, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(40, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());

  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

// Test: Seek to an existing key
TEST_F(SkipListTest_100, SeekToExistingKey_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());
}

// Test: Seek to a non-existing key should land on the next greater key
TEST_F(SkipListTest_100, SeekToNonExistingKey_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());
}

// Test: Seek to a key larger than all elements
TEST_F(SkipListTest_100, SeekBeyondLast_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(100);
  ASSERT_FALSE(iter.Valid());
}

// Test: Seek to a key smaller than all elements should return the first
TEST_F(SkipListTest_100, SeekBeforeFirst_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(1);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

// Test: Next from the last element makes iterator invalid
TEST_F(SkipListTest_100, NextFromLastElementInvalidates_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(42);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42, iter.key());

  iter.Next();
  ASSERT_FALSE(iter.Valid());
}

// Test: Prev from the first element makes iterator invalid
TEST_F(SkipListTest_100, PrevFromFirstElementInvalidates_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(42);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42, iter.key());

  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

// Test: Single element list - SeekToFirst and SeekToLast return same element
TEST_F(SkipListTest_100, SingleElementSeekFirstAndLast_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(99);

  IntSkipList::Iterator iter(&list);

  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(99, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(99, iter.key());
}

// Test: Contains returns false for a key not in a non-empty list
TEST_F(SkipListTest_100, ContainsReturnsFalseForMissingKey_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(3);
  list.Insert(5);

  ASSERT_FALSE(list.Contains(0));
  ASSERT_FALSE(list.Contains(2));
  ASSERT_FALSE(list.Contains(4));
  ASSERT_FALSE(list.Contains(6));
}

// Test: Insert duplicate keys and verify iteration count
TEST_F(SkipListTest_100, InsertDuplicateKeys_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(5);
  list.Insert(5);
  list.Insert(5);

  ASSERT_TRUE(list.Contains(5));

  int count = 0;
  IntSkipList::Iterator iter(&list);
  for (iter.SeekToFirst(); iter.Valid(); iter.Next()) {
    ASSERT_EQ(5, iter.key());
    count++;
  }
  ASSERT_EQ(3, count);
}

// Test: Insert negative keys
TEST_F(SkipListTest_100, InsertNegativeKeys_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(-10);
  list.Insert(-5);
  list.Insert(0);
  list.Insert(5);
  list.Insert(10);

  ASSERT_TRUE(list.Contains(-10));
  ASSERT_TRUE(list.Contains(-5));
  ASSERT_TRUE(list.Contains(0));
  ASSERT_TRUE(list.Contains(5));
  ASSERT_TRUE(list.Contains(10));

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(-10, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

// Test: Large number of insertions and ordered iteration
TEST_F(SkipListTest_100, LargeInsertionAndIteration_100) {
  IntSkipList list(cmp_, &arena_);
  const int N = 1000;

  // Insert in reverse order
  for (int i = N - 1; i >= 0; i--) {
    list.Insert(i);
  }

  // Verify all are contained
  for (int i = 0; i < N; i++) {
    ASSERT_TRUE(list.Contains(i));
  }

  // Verify forward iteration is in order
  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  for (int i = 0; i < N; i++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(i, iter.key());
    iter.Next();
  }
  ASSERT_FALSE(iter.Valid());
}

// Test: Seek to the exact first element
TEST_F(SkipListTest_100, SeekToExactFirst_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(10);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

// Test: Seek to the exact last element
TEST_F(SkipListTest_100, SeekToExactLast_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(30);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30, iter.key());
}

// Test: Forward then backward navigation
TEST_F(SkipListTest_100, ForwardThenBackward_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);
  list.Insert(4);
  list.Insert(5);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_EQ(1, iter.key());

  iter.Next();
  ASSERT_EQ(2, iter.key());

  iter.Next();
  ASSERT_EQ(3, iter.key());

  // Now go backward
  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(2, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(1, iter.key());

  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

// Test: SeekToLast then iterate backward through all elements
TEST_F(SkipListTest_100, SeekToLastFullBackwardIteration_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(100);
  list.Insert(200);
  list.Insert(300);

  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(300, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(200, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(100, iter.key());

  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

// Test: Seek on empty list
TEST_F(SkipListTest_100, SeekOnEmptyList_100) {
  IntSkipList list(cmp_, &arena_);
  IntSkipList::Iterator iter(&list);
  iter.Seek(42);
  ASSERT_FALSE(iter.Valid());
}

// Test: Iterator starts invalid
TEST_F(SkipListTest_100, IteratorStartsInvalid_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);

  IntSkipList::Iterator iter(&list);
  ASSERT_FALSE(iter.Valid());
}

// Test: Insert and seek with boundary integer values
TEST_F(SkipListTest_100, BoundaryIntegerValues_100) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(INT32_MIN);
  list.Insert(INT32_MAX);
  list.Insert(0);

  ASSERT_TRUE(list.Contains(INT32_MIN));
  ASSERT_TRUE(list.Contains(INT32_MAX));
  ASSERT_TRUE(list.Contains(0));

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(INT32_MIN, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(INT32_MAX, iter.key());
}

}  // namespace leveldb
