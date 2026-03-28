#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"

#include <set>
#include <vector>
#include <algorithm>
#include <random>

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

class SkipListTest_101 : public ::testing::Test {
 protected:
  void SetUp() override {
    arena_ = new Arena();
    cmp_ = IntComparator();
  }

  void TearDown() override {
    delete arena_;
  }

  Arena* arena_;
  IntComparator cmp_;
};

// Test that a newly created skip list does not contain any key
TEST_F(SkipListTest_101, EmptySkipListContainsNothing_101) {
  IntSkipList list(cmp_, arena_);
  EXPECT_FALSE(list.Contains(0));
  EXPECT_FALSE(list.Contains(1));
  EXPECT_FALSE(list.Contains(-1));
  EXPECT_FALSE(list.Contains(100));
}

// Test inserting a single element and verifying it exists
TEST_F(SkipListTest_101, InsertSingleElement_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(42);
  EXPECT_TRUE(list.Contains(42));
  EXPECT_FALSE(list.Contains(41));
  EXPECT_FALSE(list.Contains(43));
}

// Test inserting multiple elements and verifying all exist
TEST_F(SkipListTest_101, InsertMultipleElements_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  EXPECT_TRUE(list.Contains(10));
  EXPECT_TRUE(list.Contains(20));
  EXPECT_TRUE(list.Contains(30));
  EXPECT_FALSE(list.Contains(15));
  EXPECT_FALSE(list.Contains(25));
  EXPECT_FALSE(list.Contains(5));
  EXPECT_FALSE(list.Contains(35));
}

// Test inserting elements in reverse order
TEST_F(SkipListTest_101, InsertReverseOrder_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(30);
  list.Insert(20);
  list.Insert(10);

  EXPECT_TRUE(list.Contains(10));
  EXPECT_TRUE(list.Contains(20));
  EXPECT_TRUE(list.Contains(30));
}

// Test inserting elements in random order
TEST_F(SkipListTest_101, InsertRandomOrder_101) {
  IntSkipList list(cmp_, arena_);
  std::vector<int> keys = {5, 3, 8, 1, 9, 2, 7, 4, 6, 10};
  for (int k : keys) {
    list.Insert(k);
  }
  for (int k : keys) {
    EXPECT_TRUE(list.Contains(k));
  }
  EXPECT_FALSE(list.Contains(0));
  EXPECT_FALSE(list.Contains(11));
}

// Test boundary: inserting zero
TEST_F(SkipListTest_101, InsertZero_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(0);
  EXPECT_TRUE(list.Contains(0));
  EXPECT_FALSE(list.Contains(1));
  EXPECT_FALSE(list.Contains(-1));
}

// Test inserting negative numbers
TEST_F(SkipListTest_101, InsertNegativeNumbers_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(-5);
  list.Insert(-3);
  list.Insert(-1);
  list.Insert(0);
  list.Insert(2);

  EXPECT_TRUE(list.Contains(-5));
  EXPECT_TRUE(list.Contains(-3));
  EXPECT_TRUE(list.Contains(-1));
  EXPECT_TRUE(list.Contains(0));
  EXPECT_TRUE(list.Contains(2));
  EXPECT_FALSE(list.Contains(-4));
  EXPECT_FALSE(list.Contains(-2));
  EXPECT_FALSE(list.Contains(1));
}

// Test inserting a large number of elements
TEST_F(SkipListTest_101, InsertLargeNumberOfElements_101) {
  IntSkipList list(cmp_, arena_);
  const int N = 1000;
  std::set<int> inserted;

  // Insert odd numbers in some shuffled order
  std::vector<int> keys;
  for (int i = 1; i <= 2 * N; i += 2) {
    keys.push_back(i);
  }
  std::mt19937 rng(12345);
  std::shuffle(keys.begin(), keys.end(), rng);

  for (int k : keys) {
    list.Insert(k);
    inserted.insert(k);
  }

  // Verify all inserted keys exist
  for (int k : inserted) {
    EXPECT_TRUE(list.Contains(k));
  }

  // Verify even numbers don't exist
  for (int i = 0; i <= 2 * N; i += 2) {
    EXPECT_FALSE(list.Contains(i));
  }
}

// Test Contains on an element not in the list
TEST_F(SkipListTest_101, ContainsReturnsFalseForMissingKey_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(1);
  list.Insert(3);
  list.Insert(5);

  EXPECT_FALSE(list.Contains(2));
  EXPECT_FALSE(list.Contains(4));
  EXPECT_FALSE(list.Contains(6));
  EXPECT_FALSE(list.Contains(0));
  EXPECT_FALSE(list.Contains(-1));
}

// Test inserting INT_MAX and INT_MIN boundary values
TEST_F(SkipListTest_101, InsertBoundaryIntValues_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(INT_MAX);
  list.Insert(INT_MIN);

  EXPECT_TRUE(list.Contains(INT_MAX));
  EXPECT_TRUE(list.Contains(INT_MIN));
  EXPECT_FALSE(list.Contains(0));
}

// Test inserting sequential ascending elements
TEST_F(SkipListTest_101, InsertSequentialAscending_101) {
  IntSkipList list(cmp_, arena_);
  for (int i = 0; i < 100; i++) {
    list.Insert(i);
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(list.Contains(i));
  }
  EXPECT_FALSE(list.Contains(-1));
  EXPECT_FALSE(list.Contains(100));
}

// Test inserting sequential descending elements
TEST_F(SkipListTest_101, InsertSequentialDescending_101) {
  IntSkipList list(cmp_, arena_);
  for (int i = 99; i >= 0; i--) {
    list.Insert(i);
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(list.Contains(i));
  }
  EXPECT_FALSE(list.Contains(-1));
  EXPECT_FALSE(list.Contains(100));
}

// Test with only one element inserted, checking boundary neighbors
TEST_F(SkipListTest_101, SingleElementBoundaryCheck_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(50);

  EXPECT_TRUE(list.Contains(50));
  EXPECT_FALSE(list.Contains(49));
  EXPECT_FALSE(list.Contains(51));
}

// Test the Iterator: SeekToFirst on empty list should not be valid
TEST_F(SkipListTest_101, IteratorEmptyList_101) {
  IntSkipList list(cmp_, arena_);
  IntSkipList::Iterator iter(&list);

  iter.SeekToFirst();
  EXPECT_FALSE(iter.Valid());
}

// Test the Iterator: SeekToFirst on non-empty list
TEST_F(SkipListTest_101, IteratorSeekToFirst_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(30);
  list.Insert(10);
  list.Insert(20);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test the Iterator: iterating through all elements in order
TEST_F(SkipListTest_101, IteratorTraversalInOrder_101) {
  IntSkipList list(cmp_, arena_);
  std::vector<int> keys = {50, 30, 70, 10, 40, 60, 80, 20};
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

// Test the Iterator: SeekToLast
TEST_F(SkipListTest_101, IteratorSeekToLast_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());
}

// Test the Iterator: Seek to an existing key
TEST_F(SkipListTest_101, IteratorSeekExistingKey_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(20);
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test the Iterator: Seek to a non-existing key (should land on next greater)
TEST_F(SkipListTest_101, IteratorSeekNonExistingKey_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(15);
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test the Iterator: Seek past all elements
TEST_F(SkipListTest_101, IteratorSeekPastEnd_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(31);
  EXPECT_FALSE(iter.Valid());
}

// Test the Iterator: Prev
TEST_F(SkipListTest_101, IteratorPrev_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());

  iter.Prev();
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());

  iter.Prev();
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());

  iter.Prev();
  EXPECT_FALSE(iter.Valid());
}

// Test the Iterator: reverse traversal
TEST_F(SkipListTest_101, IteratorReverseTraversal_101) {
  IntSkipList list(cmp_, arena_);
  std::vector<int> keys = {5, 3, 8, 1, 9, 2, 7, 4, 6, 10};
  for (int k : keys) {
    list.Insert(k);
  }

  std::sort(keys.begin(), keys.end(), std::greater<int>());

  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  int idx = 0;
  while (iter.Valid()) {
    ASSERT_LT(idx, static_cast<int>(keys.size()));
    EXPECT_EQ(keys[idx], iter.key());
    iter.Prev();
    idx++;
  }
  EXPECT_EQ(static_cast<int>(keys.size()), idx);
}

// Test the Iterator: SeekToFirst then Next through all, then check invalid
TEST_F(SkipListTest_101, IteratorNextPastEnd_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(1);
  list.Insert(2);

  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());

  iter.Next();
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(2, iter.key());

  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

// Test the Iterator: SeekToLast on empty list
TEST_F(SkipListTest_101, IteratorSeekToLastEmpty_101) {
  IntSkipList list(cmp_, arena_);
  IntSkipList::Iterator iter(&list);
  iter.SeekToLast();
  EXPECT_FALSE(iter.Valid());
}

// Test inserting a larger scale and iterating
TEST_F(SkipListTest_101, LargeScaleInsertAndIterate_101) {
  IntSkipList list(cmp_, arena_);
  const int N = 500;
  std::vector<int> keys;
  for (int i = 0; i < N; i++) {
    keys.push_back(i * 2 + 1);  // odd numbers: 1, 3, 5, ..., 999
  }

  // Shuffle and insert
  std::mt19937 rng(42);
  std::vector<int> shuffled = keys;
  std::shuffle(shuffled.begin(), shuffled.end(), rng);
  for (int k : shuffled) {
    list.Insert(k);
  }

  // Forward iteration should produce sorted order
  std::sort(keys.begin(), keys.end());
  IntSkipList::Iterator iter(&list);
  iter.SeekToFirst();
  int idx = 0;
  while (iter.Valid()) {
    ASSERT_LT(idx, N);
    EXPECT_EQ(keys[idx], iter.key());
    iter.Next();
    idx++;
  }
  EXPECT_EQ(N, idx);
}

// Test Seek to the smallest key
TEST_F(SkipListTest_101, IteratorSeekToSmallestKey_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(10);
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test Seek to a key smaller than all elements
TEST_F(SkipListTest_101, IteratorSeekBeforeAll_101) {
  IntSkipList list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  IntSkipList::Iterator iter(&list);
  iter.Seek(5);
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

}  // namespace leveldb
