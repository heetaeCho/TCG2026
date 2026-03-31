#include "gtest/gtest.h"

#include <atomic>
#include <cstdlib>
#include <cstring>

// We need to include the actual skiplist header
#include "db/skiplist.h"
#include "util/arena.h"
#include "util/random.h"

namespace leveldb {

// A simple comparator for uint64_t keys
struct Uint64Comparator {
  int operator()(const uint64_t& a, const uint64_t& b) const {
    if (a < b) return -1;
    if (a > b) return +1;
    return 0;
  }
};

class SkipListTest_93 : public ::testing::Test {
 protected:
  Arena arena_;
  Uint64Comparator cmp_;
};

// Test: An empty skip list should not contain any elements
TEST_F(SkipListTest_93, EmptyListContainsNothing_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  ASSERT_FALSE(list.Contains(10));
  ASSERT_FALSE(list.Contains(0));
  ASSERT_FALSE(list.Contains(100));
}

// Test: Iterator on empty list is not valid
TEST_F(SkipListTest_93, EmptyListIteratorNotValid_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  ASSERT_FALSE(iter.Valid());
}

// Test: Insert a single element and verify Contains
TEST_F(SkipListTest_93, InsertSingleElement_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(42);
  ASSERT_TRUE(list.Contains(42));
  ASSERT_FALSE(list.Contains(41));
  ASSERT_FALSE(list.Contains(43));
}

// Test: Insert multiple elements and verify all are contained
TEST_F(SkipListTest_93, InsertMultipleElements_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);
  list.Insert(5);
  list.Insert(15);

  ASSERT_TRUE(list.Contains(5));
  ASSERT_TRUE(list.Contains(10));
  ASSERT_TRUE(list.Contains(15));
  ASSERT_TRUE(list.Contains(20));
  ASSERT_TRUE(list.Contains(30));
  ASSERT_FALSE(list.Contains(0));
  ASSERT_FALSE(list.Contains(25));
  ASSERT_FALSE(list.Contains(35));
}

// Test: Iterator SeekToFirst on non-empty list
TEST_F(SkipListTest_93, IteratorSeekToFirst_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(30);
  list.Insert(10);
  list.Insert(20);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

// Test: Iterator SeekToLast on non-empty list
TEST_F(SkipListTest_93, IteratorSeekToLast_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(30);
  list.Insert(10);
  list.Insert(20);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30, iter.key());
}

// Test: Iterator Next traverses in sorted order
TEST_F(SkipListTest_93, IteratorNextTraversal_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(50);
  list.Insert(10);
  list.Insert(30);
  list.Insert(20);
  list.Insert(40);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToFirst();

  std::vector<uint64_t> result;
  while (iter.Valid()) {
    result.push_back(iter.key());
    iter.Next();
  }

  std::vector<uint64_t> expected = {10, 20, 30, 40, 50};
  ASSERT_EQ(expected, result);
}

// Test: Iterator Prev traverses in reverse sorted order
TEST_F(SkipListTest_93, IteratorPrevTraversal_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(50);
  list.Insert(10);
  list.Insert(30);
  list.Insert(20);
  list.Insert(40);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToLast();

  std::vector<uint64_t> result;
  while (iter.Valid()) {
    result.push_back(iter.key());
    iter.Prev();
  }

  std::vector<uint64_t> expected = {50, 40, 30, 20, 10};
  ASSERT_EQ(expected, result);
}

// Test: Iterator Seek finds the correct position (exact match)
TEST_F(SkipListTest_93, IteratorSeekExactMatch_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());
}

// Test: Iterator Seek lands on next element when key not present
TEST_F(SkipListTest_93, IteratorSeekNoExactMatch_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());
}

// Test: Iterator Seek past all elements is not valid
TEST_F(SkipListTest_93, IteratorSeekPastEnd_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.Seek(40);
  ASSERT_FALSE(iter.Valid());
}

// Test: Iterator Seek to value before first element returns first
TEST_F(SkipListTest_93, IteratorSeekBeforeFirst_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

// Test: SeekToFirst on empty list leaves iterator invalid
TEST_F(SkipListTest_93, IteratorSeekToFirstEmpty_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_FALSE(iter.Valid());
}

// Test: SeekToLast on empty list leaves iterator invalid
TEST_F(SkipListTest_93, IteratorSeekToLastEmpty_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_FALSE(iter.Valid());
}

// Test: Insert boundary values (0 and large value)
TEST_F(SkipListTest_93, InsertBoundaryValues_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(0);
  list.Insert(UINT64_MAX);

  ASSERT_TRUE(list.Contains(0));
  ASSERT_TRUE(list.Contains(UINT64_MAX));
  ASSERT_FALSE(list.Contains(1));

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(0, iter.key());
  iter.Next();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(UINT64_MAX, iter.key());
  iter.Next();
  ASSERT_FALSE(iter.Valid());
}

// Test: Insert many elements and verify sorted order
TEST_F(SkipListTest_93, InsertManyElements_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  const int N = 1000;
  Random rnd(301);

  std::set<uint64_t> keys;
  for (int i = 0; i < N; i++) {
    uint64_t key = rnd.Next() % 10000;
    if (keys.count(key) == 0) {
      keys.insert(key);
      list.Insert(key);
    }
  }

  // Verify all inserted keys are found
  for (uint64_t k : keys) {
    ASSERT_TRUE(list.Contains(k));
  }

  // Verify iteration order matches sorted set
  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  auto set_iter = keys.begin();
  while (iter.Valid()) {
    ASSERT_NE(set_iter, keys.end());
    ASSERT_EQ(*set_iter, iter.key());
    iter.Next();
    ++set_iter;
  }
  ASSERT_EQ(set_iter, keys.end());
}

// Test: Single element - SeekToFirst and SeekToLast return the same
TEST_F(SkipListTest_93, SingleElementFirstAndLastSame_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(100);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(100, iter.key());

  SkipList<uint64_t, Uint64Comparator>::Iterator iter2(&list);
  iter2.SeekToLast();
  ASSERT_TRUE(iter2.Valid());
  ASSERT_EQ(100, iter2.key());
}

// Test: Prev from first element makes iterator invalid
TEST_F(SkipListTest_93, PrevFromFirstBecomesInvalid_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

// Test: Next from last element makes iterator invalid
TEST_F(SkipListTest_93, NextFromLastBecomesInvalid_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());
  iter.Next();
  ASSERT_FALSE(iter.Valid());
}

// Test: Contains returns false for non-existent elements in populated list
TEST_F(SkipListTest_93, ContainsNonExistentElements_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  for (uint64_t i = 0; i < 100; i += 2) {
    list.Insert(i);
  }
  // Odd numbers should not be found
  for (uint64_t i = 1; i < 100; i += 2) {
    ASSERT_FALSE(list.Contains(i));
  }
  // Even numbers should be found
  for (uint64_t i = 0; i < 100; i += 2) {
    ASSERT_TRUE(list.Contains(i));
  }
}

// Test: Seek on each element in a sequence
TEST_F(SkipListTest_93, SeekOnEachElement_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  std::vector<uint64_t> vals = {5, 15, 25, 35, 45};
  for (auto v : vals) {
    list.Insert(v);
  }

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);
  for (auto v : vals) {
    iter.Seek(v);
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(v, iter.key());
  }
}

// Test: Seek between elements lands on next higher element
TEST_F(SkipListTest_93, SeekBetweenElements_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);
  list.Insert(40);
  list.Insert(50);

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);

  iter.Seek(11);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());

  iter.Seek(25);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30, iter.key());

  iter.Seek(45);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(50, iter.key());

  iter.Seek(51);
  ASSERT_FALSE(iter.Valid());
}

// Test: Forward and backward iteration consistency
TEST_F(SkipListTest_93, ForwardBackwardConsistency_93) {
  SkipList<uint64_t, Uint64Comparator> list(cmp_, &arena_);
  for (uint64_t i = 1; i <= 10; i++) {
    list.Insert(i * 10);
  }

  SkipList<uint64_t, Uint64Comparator>::Iterator iter(&list);

  // Go forward to element 50
  iter.Seek(50);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(50, iter.key());

  // Go backward
  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(40, iter.key());

  // Go forward again
  iter.Next();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(50, iter.key());

  iter.Next();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(60, iter.key());
}

}  // namespace leveldb
