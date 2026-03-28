#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"

#include <set>
#include <vector>
#include <algorithm>

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

class SkipListTest_99 : public ::testing::Test {
 protected:
  IntComparator cmp_;
  Arena arena_;
};

// Test that an empty skip list does not contain any key
TEST_F(SkipListTest_99, EmptyListContainsNothing_99) {
  IntSkipList list(cmp_, &arena_);
  EXPECT_FALSE(list.Contains(0));
  EXPECT_FALSE(list.Contains(1));
  EXPECT_FALSE(list.Contains(-1));
  EXPECT_FALSE(list.Contains(100));
}

// Test inserting a single element and checking Contains
TEST_F(SkipListTest_99, InsertSingleElement_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  EXPECT_TRUE(list.Contains(10));
  EXPECT_FALSE(list.Contains(9));
  EXPECT_FALSE(list.Contains(11));
}

// Test inserting multiple elements
TEST_F(SkipListTest_99, InsertMultipleElements_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(5);
  list.Insert(10);
  list.Insert(15);
  list.Insert(20);

  EXPECT_TRUE(list.Contains(5));
  EXPECT_TRUE(list.Contains(10));
  EXPECT_TRUE(list.Contains(15));
  EXPECT_TRUE(list.Contains(20));
  EXPECT_FALSE(list.Contains(0));
  EXPECT_FALSE(list.Contains(7));
  EXPECT_FALSE(list.Contains(25));
}

// Test inserting elements in reverse order
TEST_F(SkipListTest_99, InsertReverseOrder_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(100);
  list.Insert(75);
  list.Insert(50);
  list.Insert(25);
  list.Insert(0);

  EXPECT_TRUE(list.Contains(0));
  EXPECT_TRUE(list.Contains(25));
  EXPECT_TRUE(list.Contains(50));
  EXPECT_TRUE(list.Contains(75));
  EXPECT_TRUE(list.Contains(100));
  EXPECT_FALSE(list.Contains(1));
  EXPECT_FALSE(list.Contains(99));
}

// Test iterator on empty list
TEST_F(SkipListTest_99, IteratorEmptyList_99) {
  IntSkipList list(cmp_, &arena_);
  IntSkipList::Iterator iter(&list);

  EXPECT_FALSE(iter.Valid());

  iter.SeekToFirst();
  EXPECT_FALSE(iter.Valid());

  iter.SeekToLast();
  EXPECT_FALSE(iter.Valid());
}

// Test iterator SeekToFirst on non-empty list
TEST_F(SkipListTest_99, IteratorSeekToFirst_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(3);
  list.Insert(1);
  list.Insert(2);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());
}

// Test iterator SeekToLast on non-empty list
TEST_F(SkipListTest_99, IteratorSeekToLast_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(3);
  list.Insert(1);
  list.Insert(2);

  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(3, iter.key());
}

// Test forward iteration through all elements
TEST_F(SkipListTest_99, IteratorForwardTraversal_99) {
  IntSkipList list(cmp_, &arena_);
  std::vector<int> keys = {5, 3, 7, 1, 9, 2, 8, 4, 6};
  for (int k : keys) {
    list.Insert(k);
  }

  std::sort(keys.begin(), keys.end());

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  int idx = 0;
  while (iter.Valid()) {
    ASSERT_LT(idx, static_cast<int>(keys.size()));
    EXPECT_EQ(keys[idx], iter.key());
    iter.Next();
    idx++;
  }
  EXPECT_EQ(static_cast<int>(keys.size()), idx);
}

// Test backward iteration using Prev
TEST_F(SkipListTest_99, IteratorBackwardTraversal_99) {
  IntSkipList list(cmp_, &arena_);
  std::vector<int> keys = {5, 3, 7, 1, 9};
  for (int k : keys) {
    list.Insert(k);
  }

  std::sort(keys.begin(), keys.end());

  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  int idx = static_cast<int>(keys.size()) - 1;
  while (iter.Valid()) {
    ASSERT_GE(idx, 0);
    EXPECT_EQ(keys[idx], iter.key());
    iter.Prev();
    idx--;
  }
  EXPECT_EQ(-1, idx);
}

// Test Seek finds exact key
TEST_F(SkipListTest_99, IteratorSeekExactKey_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test Seek finds first key >= target when target is not present
TEST_F(SkipListTest_99, IteratorSeekNonExistentKey_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test Seek past all elements
TEST_F(SkipListTest_99, IteratorSeekPastEnd_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(31);
  EXPECT_FALSE(iter.Valid());
}

// Test Seek to value before first element
TEST_F(SkipListTest_99, IteratorSeekBeforeFirst_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test Prev from the first element makes iterator invalid
TEST_F(SkipListTest_99, IteratorPrevFromFirst_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());

  iter.Prev();
  EXPECT_FALSE(iter.Valid());
}

// Test Next from last element makes iterator invalid
TEST_F(SkipListTest_99, IteratorNextFromLast_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(10);

  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());

  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

// Test with a single element - all iterator operations
TEST_F(SkipListTest_99, SingleElementIteratorOperations_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(42);

  IntSkipList::Iterator iter(&list);

  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(42, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(42, iter.key());

  iter.Seek(42);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(42, iter.key());

  iter.Seek(41);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(42, iter.key());

  iter.Seek(43);
  EXPECT_FALSE(iter.Valid());
}

// Test inserting negative numbers
TEST_F(SkipListTest_99, NegativeNumbers_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(-5);
  list.Insert(-10);
  list.Insert(0);
  list.Insert(5);
  list.Insert(10);

  EXPECT_TRUE(list.Contains(-10));
  EXPECT_TRUE(list.Contains(-5));
  EXPECT_TRUE(list.Contains(0));
  EXPECT_TRUE(list.Contains(5));
  EXPECT_TRUE(list.Contains(10));
  EXPECT_FALSE(list.Contains(-1));

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(-10, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test with larger number of insertions
TEST_F(SkipListTest_99, LargeNumberOfInsertions_99) {
  IntSkipList list(cmp_, &arena_);
  const int N = 1000;
  for (int i = N; i > 0; i--) {
    list.Insert(i);
  }

  for (int i = 1; i <= N; i++) {
    EXPECT_TRUE(list.Contains(i));
  }
  EXPECT_FALSE(list.Contains(0));
  EXPECT_FALSE(list.Contains(N + 1));

  // Verify sorted order
  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  int expected = 1;
  while (iter.Valid()) {
    EXPECT_EQ(expected, iter.key());
    expected++;
    iter.Next();
  }
  EXPECT_EQ(N + 1, expected);
}

// Test iterator constructed initially is not valid
TEST_F(SkipListTest_99, IteratorInitialState_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);

  IntSkipList::Iterator iter(&list);
  // According to typical skiplist implementations, newly constructed iterator
  // points to head_->Next(0), but let's test SeekToFirst for correctness
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());
}

// Test Seek to minimum int value
TEST_F(SkipListTest_99, SeekToMinimumValue_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(100);
  list.Insert(200);

  IntSkipList::Iterator iter(&list);
  iter.Seek(std::numeric_limits<int>::min());
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(100, iter.key());
}

// Test Seek to maximum int value when it's larger than all elements
TEST_F(SkipListTest_99, SeekToMaximumValue_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(100);
  list.Insert(200);

  IntSkipList::Iterator iter(&list);
  iter.Seek(std::numeric_limits<int>::max());
  // Should be invalid since no element >= max int (assuming max int is not inserted)
  EXPECT_FALSE(iter.Valid());
}

// Test mixed forward and backward iteration
TEST_F(SkipListTest_99, MixedForwardBackwardIteration_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);
  list.Insert(4);
  list.Insert(5);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());

  iter.Next();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(2, iter.key());

  iter.Next();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(3, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(2, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());

  iter.Prev();
  EXPECT_FALSE(iter.Valid());
}

// Test Contains returns false for keys not inserted
TEST_F(SkipListTest_99, ContainsReturnsFalseForMissingKeys_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(2);
  list.Insert(4);
  list.Insert(6);

  EXPECT_FALSE(list.Contains(1));
  EXPECT_FALSE(list.Contains(3));
  EXPECT_FALSE(list.Contains(5));
  EXPECT_FALSE(list.Contains(7));
}

// Test that two iterators can coexist on the same list
TEST_F(SkipListTest_99, MultipleIterators_99) {
  IntSkipList list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);

  IntSkipList::Iterator iter1(&list);
  IntSkipList::Iterator iter2(&list);

  iter1.SeekToFirst();
  iter2.SeekToLast();

  ASSERT_TRUE(iter1.Valid());
  ASSERT_TRUE(iter2.Valid());
  EXPECT_EQ(1, iter1.key());
  EXPECT_EQ(3, iter2.key());

  iter1.Next();
  iter2.Prev();

  ASSERT_TRUE(iter1.Valid());
  ASSERT_TRUE(iter2.Valid());
  EXPECT_EQ(2, iter1.key());
  EXPECT_EQ(2, iter2.key());
}

// Test inserting elements and verifying order via iteration
TEST_F(SkipListTest_99, InsertionMaintainsSortedOrder_99) {
  IntSkipList list(cmp_, &arena_);
  // Insert in random-ish order
  list.Insert(50);
  list.Insert(10);
  list.Insert(90);
  list.Insert(30);
  list.Insert(70);

  std::vector<int> expected = {10, 30, 50, 70, 90};

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  for (int i = 0; i < static_cast<int>(expected.size()); i++) {
    ASSERT_TRUE(iter.Valid());
    EXPECT_EQ(expected[i], iter.key());
    iter.Next();
  }
  EXPECT_FALSE(iter.Valid());
}

}  // namespace leveldb
