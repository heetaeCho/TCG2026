#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"

#include <set>
#include <vector>
#include <algorithm>

namespace leveldb {

// A simple comparator for int keys
struct IntComparator {
  int operator()(const int& a, const int& b) const {
    if (a < b) return -1;
    if (a > b) return +1;
    return 0;
  }
};

typedef SkipList<int, IntComparator> IntSkipList;

class SkipListTest_478 : public ::testing::Test {
 protected:
  void SetUp() override {
    arena_ = new Arena();
    list_ = new IntSkipList(IntComparator(), arena_);
  }

  void TearDown() override {
    delete list_;
    delete arena_;
  }

  Arena* arena_;
  IntSkipList* list_;
};

// Test that an empty skip list does not contain any key
TEST_F(SkipListTest_478, EmptyListContainsNothing_478) {
  EXPECT_FALSE(list_->Contains(0));
  EXPECT_FALSE(list_->Contains(1));
  EXPECT_FALSE(list_->Contains(-1));
  EXPECT_FALSE(list_->Contains(100));
}

// Test inserting a single element and checking Contains
TEST_F(SkipListTest_478, InsertSingleElement_478) {
  list_->Insert(10);
  EXPECT_TRUE(list_->Contains(10));
  EXPECT_FALSE(list_->Contains(9));
  EXPECT_FALSE(list_->Contains(11));
}

// Test inserting multiple elements
TEST_F(SkipListTest_478, InsertMultipleElements_478) {
  list_->Insert(5);
  list_->Insert(10);
  list_->Insert(15);
  list_->Insert(20);

  EXPECT_TRUE(list_->Contains(5));
  EXPECT_TRUE(list_->Contains(10));
  EXPECT_TRUE(list_->Contains(15));
  EXPECT_TRUE(list_->Contains(20));
  EXPECT_FALSE(list_->Contains(0));
  EXPECT_FALSE(list_->Contains(7));
  EXPECT_FALSE(list_->Contains(25));
}

// Test inserting elements in reverse order
TEST_F(SkipListTest_478, InsertReverseOrder_478) {
  list_->Insert(100);
  list_->Insert(75);
  list_->Insert(50);
  list_->Insert(25);
  list_->Insert(0);

  EXPECT_TRUE(list_->Contains(0));
  EXPECT_TRUE(list_->Contains(25));
  EXPECT_TRUE(list_->Contains(50));
  EXPECT_TRUE(list_->Contains(75));
  EXPECT_TRUE(list_->Contains(100));
  EXPECT_FALSE(list_->Contains(1));
  EXPECT_FALSE(list_->Contains(99));
}

// Test iterator on empty list
TEST_F(SkipListTest_478, IteratorEmptyList_478) {
  IntSkipList::Iterator iter(list_);
  EXPECT_FALSE(iter.Valid());
}

// Test SeekToFirst on empty list
TEST_F(SkipListTest_478, SeekToFirstEmptyList_478) {
  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  EXPECT_FALSE(iter.Valid());
}

// Test SeekToLast on empty list
TEST_F(SkipListTest_478, SeekToLastEmptyList_478) {
  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  EXPECT_FALSE(iter.Valid());
}

// Test Seek on empty list
TEST_F(SkipListTest_478, SeekOnEmptyList_478) {
  IntSkipList::Iterator iter(list_);
  iter.Seek(10);
  EXPECT_FALSE(iter.Valid());
}

// Test iterator SeekToFirst with elements
TEST_F(SkipListTest_478, IteratorSeekToFirst_478) {
  list_->Insert(3);
  list_->Insert(1);
  list_->Insert(2);

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());
}

// Test iterator SeekToLast with elements
TEST_F(SkipListTest_478, IteratorSeekToLast_478) {
  list_->Insert(3);
  list_->Insert(1);
  list_->Insert(2);

  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(3, iter.key());
}

// Test forward iteration through all elements
TEST_F(SkipListTest_478, ForwardIteration_478) {
  std::vector<int> keys = {5, 3, 7, 1, 9, 2, 8, 4, 6};
  for (int k : keys) {
    list_->Insert(k);
  }

  std::sort(keys.begin(), keys.end());

  IntSkipList::Iterator iter(list_);
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

// Test backward iteration through all elements
TEST_F(SkipListTest_478, BackwardIteration_478) {
  std::vector<int> keys = {5, 3, 7, 1, 9};
  for (int k : keys) {
    list_->Insert(k);
  }

  std::sort(keys.begin(), keys.end());

  IntSkipList::Iterator iter(list_);
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

// Test Seek finds the target key exactly
TEST_F(SkipListTest_478, SeekExactKey_478) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test Seek finds the next key when target is not present
TEST_F(SkipListTest_478, SeekToNextGreaterOrEqual_478) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test Seek past all elements
TEST_F(SkipListTest_478, SeekPastAllElements_478) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(31);
  EXPECT_FALSE(iter.Valid());
}

// Test Seek to a key before all elements
TEST_F(SkipListTest_478, SeekBeforeAllElements_478) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test Prev from first element makes iterator invalid
TEST_F(SkipListTest_478, PrevFromFirstElementInvalid_478) {
  list_->Insert(10);
  list_->Insert(20);

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
  iter.Prev();
  EXPECT_FALSE(iter.Valid());
}

// Test Next from last element makes iterator invalid
TEST_F(SkipListTest_478, NextFromLastElementInvalid_478) {
  list_->Insert(10);
  list_->Insert(20);

  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

// Test with a single element - all iterator operations
TEST_F(SkipListTest_478, SingleElementIterator_478) {
  list_->Insert(42);

  IntSkipList::Iterator iter(list_);

  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(42, iter.key());

  iter.Next();
  EXPECT_FALSE(iter.Valid());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(42, iter.key());

  iter.Prev();
  EXPECT_FALSE(iter.Valid());

  iter.Seek(42);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(42, iter.key());

  iter.Seek(41);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(42, iter.key());

  iter.Seek(43);
  EXPECT_FALSE(iter.Valid());
}

// Test inserting many elements and verifying sorted order
TEST_F(SkipListTest_478, LargeInsertionSortedOrder_478) {
  const int N = 1000;
  std::set<int> keys;
  Random rnd(301);

  for (int i = 0; i < N; i++) {
    int key = rnd.Next() % 10000;
    if (keys.count(key) == 0) {
      keys.insert(key);
      list_->Insert(key);
    }
  }

  // Verify all inserted keys are found
  for (int k : keys) {
    EXPECT_TRUE(list_->Contains(k));
  }

  // Verify forward iteration produces sorted order
  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  auto it = keys.begin();
  while (iter.Valid()) {
    ASSERT_NE(it, keys.end());
    EXPECT_EQ(*it, iter.key());
    iter.Next();
    ++it;
  }
  EXPECT_EQ(it, keys.end());
}

// Test that Contains returns false for non-existent keys
TEST_F(SkipListTest_478, ContainsNonExistentKeys_478) {
  list_->Insert(2);
  list_->Insert(4);
  list_->Insert(6);
  list_->Insert(8);

  EXPECT_FALSE(list_->Contains(1));
  EXPECT_FALSE(list_->Contains(3));
  EXPECT_FALSE(list_->Contains(5));
  EXPECT_FALSE(list_->Contains(7));
  EXPECT_FALSE(list_->Contains(9));
}

// Test negative keys
TEST_F(SkipListTest_478, NegativeKeys_478) {
  list_->Insert(-5);
  list_->Insert(-3);
  list_->Insert(-1);
  list_->Insert(0);
  list_->Insert(1);

  EXPECT_TRUE(list_->Contains(-5));
  EXPECT_TRUE(list_->Contains(-3));
  EXPECT_TRUE(list_->Contains(-1));
  EXPECT_TRUE(list_->Contains(0));
  EXPECT_TRUE(list_->Contains(1));
  EXPECT_FALSE(list_->Contains(-4));
  EXPECT_FALSE(list_->Contains(-2));

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(-5, iter.key());
}

// Test iterator constructed from list starts as invalid
TEST_F(SkipListTest_478, IteratorInitiallyInvalid_478) {
  list_->Insert(1);
  list_->Insert(2);
  list_->Insert(3);

  IntSkipList::Iterator iter(list_);
  EXPECT_FALSE(iter.Valid());
}

// Test interleaving Next and Prev
TEST_F(SkipListTest_478, InterleavedNextPrev_478) {
  list_->Insert(1);
  list_->Insert(2);
  list_->Insert(3);
  list_->Insert(4);
  list_->Insert(5);

  IntSkipList::Iterator iter(list_);
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

  iter.Next();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(2, iter.key());
}

// Test Seek for first element
TEST_F(SkipListTest_478, SeekToFirstElement_478) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(10);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test Seek for last element
TEST_F(SkipListTest_478, SeekToLastElement_478) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(30);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());
}

// Test boundary: INT_MIN and INT_MAX
TEST_F(SkipListTest_478, BoundaryIntValues_478) {
  list_->Insert(INT_MIN);
  list_->Insert(INT_MAX);
  list_->Insert(0);

  EXPECT_TRUE(list_->Contains(INT_MIN));
  EXPECT_TRUE(list_->Contains(INT_MAX));
  EXPECT_TRUE(list_->Contains(0));

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(INT_MIN, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(INT_MAX, iter.key());
}

// Test multiple seeks on the same iterator
TEST_F(SkipListTest_478, MultipleSeeks_478) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);
  list_->Insert(40);
  list_->Insert(50);

  IntSkipList::Iterator iter(list_);

  iter.Seek(30);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());

  iter.Seek(10);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());

  iter.Seek(50);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(50, iter.key());

  iter.Seek(25);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());
}

// Test that after SeekToLast, Prev walks backward correctly
TEST_F(SkipListTest_478, SeekToLastThenPrevAll_478) {
  list_->Insert(1);
  list_->Insert(2);
  list_->Insert(3);

  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
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

}  // namespace leveldb
