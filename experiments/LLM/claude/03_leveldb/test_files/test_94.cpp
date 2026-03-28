#include "db/skiplist.h"
#include "util/arena.h"
#include "util/random.h"

#include "gtest/gtest.h"

#include <set>
#include <vector>
#include <algorithm>

namespace leveldb {

typedef uint64_t Key;

struct IntComparator {
  int operator()(const Key& a, const Key& b) const {
    if (a < b) {
      return -1;
    } else if (a > b) {
      return +1;
    } else {
      return 0;
    }
  }
};

class SkipListTest_94 : public ::testing::Test {
 protected:
  Arena arena_;
  IntComparator cmp_;
};

// Test that an iterator on an empty skip list is not valid
TEST_F(SkipListTest_94, EmptyIteratorNotValid_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  ASSERT_FALSE(iter.Valid());
}

// Test SeekToFirst on empty list yields invalid iterator
TEST_F(SkipListTest_94, SeekToFirstOnEmptyList_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_FALSE(iter.Valid());
}

// Test SeekToLast on empty list yields invalid iterator
TEST_F(SkipListTest_94, SeekToLastOnEmptyList_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_FALSE(iter.Valid());
}

// Test Seek on empty list yields invalid iterator
TEST_F(SkipListTest_94, SeekOnEmptyList_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(100);
  ASSERT_FALSE(iter.Valid());
}

// Test inserting a single element and iterating
TEST_F(SkipListTest_94, InsertSingleElement_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(42);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42, iter.key());
  iter.Next();
  ASSERT_FALSE(iter.Valid());
}

// Test SeekToLast with a single element
TEST_F(SkipListTest_94, SeekToLastSingleElement_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(42);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42, iter.key());
}

// Test Prev from last element with single element
TEST_F(SkipListTest_94, PrevFromLastSingleElement_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(42);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42, iter.key());
  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

// Test inserting multiple elements and forward iteration
TEST_F(SkipListTest_94, InsertMultipleForwardIteration_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  std::vector<Key> keys = {5, 3, 7, 1, 9, 2, 8, 4, 6, 10};
  for (Key k : keys) {
    list.Insert(k);
  }

  std::sort(keys.begin(), keys.end());

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  for (size_t i = 0; i < keys.size(); i++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(keys[i], iter.key());
    iter.Next();
  }
  ASSERT_FALSE(iter.Valid());
}

// Test inserting multiple elements and reverse iteration
TEST_F(SkipListTest_94, InsertMultipleReverseIteration_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  std::vector<Key> keys = {5, 3, 7, 1, 9, 2, 8, 4, 6, 10};
  for (Key k : keys) {
    list.Insert(k);
  }

  std::sort(keys.begin(), keys.end());

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
  for (int i = static_cast<int>(keys.size()) - 1; i >= 0; i--) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(keys[i], iter.key());
    iter.Prev();
  }
  ASSERT_FALSE(iter.Valid());
}

// Test Seek finds exact key
TEST_F(SkipListTest_94, SeekExactKey_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  for (Key k = 1; k <= 10; k++) {
    list.Insert(k * 10);
  }

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(50);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(50, iter.key());
}

// Test Seek finds next key when exact key is missing
TEST_F(SkipListTest_94, SeekNonExistentKey_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  for (Key k = 1; k <= 5; k++) {
    list.Insert(k * 10);
  }

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(25);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30, iter.key());
}

// Test Seek past all elements yields invalid
TEST_F(SkipListTest_94, SeekPastEnd_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  for (Key k = 1; k <= 5; k++) {
    list.Insert(k * 10);
  }

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(100);
  ASSERT_FALSE(iter.Valid());
}

// Test Seek to value before all elements returns first element
TEST_F(SkipListTest_94, SeekBeforeFirst_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  for (Key k = 10; k <= 50; k += 10) {
    list.Insert(k);
  }

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(1);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

// Test Contains on existing and non-existing keys
TEST_F(SkipListTest_94, ContainsExistingAndNonExisting_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  ASSERT_TRUE(list.Contains(10));
  ASSERT_TRUE(list.Contains(20));
  ASSERT_TRUE(list.Contains(30));
  ASSERT_FALSE(list.Contains(5));
  ASSERT_FALSE(list.Contains(15));
  ASSERT_FALSE(list.Contains(25));
  ASSERT_FALSE(list.Contains(35));
}

// Test Contains on empty list
TEST_F(SkipListTest_94, ContainsOnEmptyList_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  ASSERT_FALSE(list.Contains(0));
  ASSERT_FALSE(list.Contains(1));
}

// Test inserting many elements preserves sorted order
TEST_F(SkipListTest_94, LargeInsertionOrder_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  Random rnd(301);
  std::set<Key> inserted;
  for (int i = 0; i < 1000; i++) {
    Key k = rnd.Next() % 5000;
    if (inserted.count(k) == 0) {
      inserted.insert(k);
      list.Insert(k);
    }
  }

  // Verify forward order
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  Key prev = 0;
  bool first = true;
  int count = 0;
  while (iter.Valid()) {
    if (!first) {
      ASSERT_LT(prev, iter.key());
    }
    prev = iter.key();
    first = false;
    count++;
    iter.Next();
  }
  ASSERT_EQ(static_cast<int>(inserted.size()), count);
}

// Test Next and Prev are consistent
TEST_F(SkipListTest_94, NextPrevConsistency_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  for (Key k = 1; k <= 5; k++) {
    list.Insert(k);
  }

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(1, iter.key());

  iter.Next();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(2, iter.key());

  iter.Next();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(3, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(2, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(1, iter.key());

  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

// Test boundary: Seek to exact first element
TEST_F(SkipListTest_94, SeekToExactFirst_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(10);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

// Test boundary: Seek to exact last element
TEST_F(SkipListTest_94, SeekToExactLast_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(30);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30, iter.key());
  iter.Next();
  ASSERT_FALSE(iter.Valid());
}

// Test SeekToFirst then SeekToLast
TEST_F(SkipListTest_94, SeekToFirstThenSeekToLast_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(1, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(3, iter.key());
}

// Test that Contains works for boundary values (0 and large)
TEST_F(SkipListTest_94, ContainsBoundaryValues_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(0);
  list.Insert(UINT64_MAX);

  ASSERT_TRUE(list.Contains(0));
  ASSERT_TRUE(list.Contains(UINT64_MAX));
  ASSERT_FALSE(list.Contains(1));
}

// Test Seek with key 0
TEST_F(SkipListTest_94, SeekKeyZero_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(0);
  list.Insert(5);
  list.Insert(10);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(0);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(0, iter.key());
}

// Test that iterating forward collects all elements
TEST_F(SkipListTest_94, ForwardIterationCollectsAll_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  std::set<Key> expected = {3, 7, 1, 15, 9};
  for (Key k : expected) {
    list.Insert(k);
  }

  std::set<Key> collected;
  SkipList<Key, IntComparator>::Iterator iter(&list);
  for (iter.SeekToFirst(); iter.Valid(); iter.Next()) {
    collected.insert(iter.key());
  }
  ASSERT_EQ(expected, collected);
}

// Test that iterating backward collects all elements
TEST_F(SkipListTest_94, BackwardIterationCollectsAll_94) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  std::set<Key> expected = {3, 7, 1, 15, 9};
  for (Key k : expected) {
    list.Insert(k);
  }

  std::set<Key> collected;
  SkipList<Key, IntComparator>::Iterator iter(&list);
  for (iter.SeekToLast(); iter.Valid(); iter.Prev()) {
    collected.insert(iter.key());
  }
  ASSERT_EQ(expected, collected);
}

}  // namespace leveldb
