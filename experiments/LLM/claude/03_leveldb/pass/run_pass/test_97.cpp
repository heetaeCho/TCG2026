#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"

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

class SkipListTest_97 : public ::testing::Test {
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
TEST_F(SkipListTest_97, EmptyListContainsNothing_97) {
  EXPECT_FALSE(list_->Contains(0));
  EXPECT_FALSE(list_->Contains(1));
  EXPECT_FALSE(list_->Contains(-1));
  EXPECT_FALSE(list_->Contains(100));
}

// Test basic insert and contains
TEST_F(SkipListTest_97, InsertAndContains_97) {
  list_->Insert(10);
  EXPECT_TRUE(list_->Contains(10));
  EXPECT_FALSE(list_->Contains(5));
  EXPECT_FALSE(list_->Contains(15));
}

// Test inserting multiple elements
TEST_F(SkipListTest_97, InsertMultipleElements_97) {
  list_->Insert(1);
  list_->Insert(3);
  list_->Insert(5);
  list_->Insert(7);
  list_->Insert(9);

  EXPECT_TRUE(list_->Contains(1));
  EXPECT_TRUE(list_->Contains(3));
  EXPECT_TRUE(list_->Contains(5));
  EXPECT_TRUE(list_->Contains(7));
  EXPECT_TRUE(list_->Contains(9));

  EXPECT_FALSE(list_->Contains(0));
  EXPECT_FALSE(list_->Contains(2));
  EXPECT_FALSE(list_->Contains(4));
  EXPECT_FALSE(list_->Contains(6));
  EXPECT_FALSE(list_->Contains(8));
  EXPECT_FALSE(list_->Contains(10));
}

// Test inserting elements in reverse order
TEST_F(SkipListTest_97, InsertReverseOrder_97) {
  list_->Insert(5);
  list_->Insert(4);
  list_->Insert(3);
  list_->Insert(2);
  list_->Insert(1);

  for (int i = 1; i <= 5; i++) {
    EXPECT_TRUE(list_->Contains(i));
  }
}

// Test iterator on empty list is not valid
TEST_F(SkipListTest_97, IteratorOnEmptyList_97) {
  IntSkipList::Iterator iter(list_);
  EXPECT_FALSE(iter.Valid());
}

// Test SeekToFirst on empty list
TEST_F(SkipListTest_97, SeekToFirstOnEmptyList_97) {
  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  EXPECT_FALSE(iter.Valid());
}

// Test SeekToLast on empty list
TEST_F(SkipListTest_97, SeekToLastOnEmptyList_97) {
  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  EXPECT_FALSE(iter.Valid());
}

// Test Seek on empty list
TEST_F(SkipListTest_97, SeekOnEmptyList_97) {
  IntSkipList::Iterator iter(list_);
  iter.Seek(10);
  EXPECT_FALSE(iter.Valid());
}

// Test SeekToFirst returns the smallest element
TEST_F(SkipListTest_97, SeekToFirstReturnsSmallest_97) {
  list_->Insert(3);
  list_->Insert(1);
  list_->Insert(2);

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());
}

// Test SeekToLast returns the largest element
TEST_F(SkipListTest_97, SeekToLastReturnsLargest_97) {
  list_->Insert(3);
  list_->Insert(1);
  list_->Insert(2);

  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(3, iter.key());
}

// Test forward iteration traverses in order
TEST_F(SkipListTest_97, ForwardIteration_97) {
  list_->Insert(5);
  list_->Insert(1);
  list_->Insert(3);
  list_->Insert(7);
  list_->Insert(9);

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();

  int expected[] = {1, 3, 5, 7, 9};
  for (int i = 0; i < 5; i++) {
    ASSERT_TRUE(iter.Valid());
    EXPECT_EQ(expected[i], iter.key());
    iter.Next();
  }
  EXPECT_FALSE(iter.Valid());
}

// Test backward iteration (Prev) traverses in reverse order
TEST_F(SkipListTest_97, BackwardIteration_97) {
  list_->Insert(5);
  list_->Insert(1);
  list_->Insert(3);
  list_->Insert(7);
  list_->Insert(9);

  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();

  int expected[] = {9, 7, 5, 3, 1};
  for (int i = 0; i < 5; i++) {
    ASSERT_TRUE(iter.Valid());
    EXPECT_EQ(expected[i], iter.key());
    iter.Prev();
  }
  EXPECT_FALSE(iter.Valid());
}

// Test Seek finds the exact key
TEST_F(SkipListTest_97, SeekExactKey_97) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test Seek finds the next key when exact key doesn't exist
TEST_F(SkipListTest_97, SeekToNextWhenKeyMissing_97) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test Seek past all keys returns invalid
TEST_F(SkipListTest_97, SeekPastAllKeys_97) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(31);
  EXPECT_FALSE(iter.Valid());
}

// Test Seek to a key before first returns first
TEST_F(SkipListTest_97, SeekBeforeFirstKey_97) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test Prev on the first element makes iterator invalid
TEST_F(SkipListTest_97, PrevOnFirstElementBecomesInvalid_97) {
  list_->Insert(10);
  list_->Insert(20);

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());

  iter.Prev();
  EXPECT_FALSE(iter.Valid());
}

// Test Next on the last element makes iterator invalid
TEST_F(SkipListTest_97, NextOnLastElementBecomesInvalid_97) {
  list_->Insert(10);
  list_->Insert(20);

  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());

  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

// Test with a single element
TEST_F(SkipListTest_97, SingleElement_97) {
  list_->Insert(42);

  EXPECT_TRUE(list_->Contains(42));
  EXPECT_FALSE(list_->Contains(41));
  EXPECT_FALSE(list_->Contains(43));

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
}

// Test with negative keys
TEST_F(SkipListTest_97, NegativeKeys_97) {
  list_->Insert(-5);
  list_->Insert(-3);
  list_->Insert(-1);
  list_->Insert(0);
  list_->Insert(2);

  EXPECT_TRUE(list_->Contains(-5));
  EXPECT_TRUE(list_->Contains(-3));
  EXPECT_TRUE(list_->Contains(-1));
  EXPECT_TRUE(list_->Contains(0));
  EXPECT_TRUE(list_->Contains(2));
  EXPECT_FALSE(list_->Contains(-4));
  EXPECT_FALSE(list_->Contains(1));

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(-5, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(2, iter.key());
}

// Test large number of insertions
TEST_F(SkipListTest_97, LargeNumberOfInsertions_97) {
  const int N = 1000;
  for (int i = 0; i < N; i++) {
    list_->Insert(i * 2);  // Insert even numbers 0, 2, 4, ..., 1998
  }

  for (int i = 0; i < N; i++) {
    EXPECT_TRUE(list_->Contains(i * 2));
    EXPECT_FALSE(list_->Contains(i * 2 + 1));
  }

  // Verify forward iteration is sorted
  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  int prev = iter.key();
  iter.Next();
  int count = 1;
  while (iter.Valid()) {
    EXPECT_LT(prev, iter.key());
    prev = iter.key();
    iter.Next();
    count++;
  }
  EXPECT_EQ(N, count);
}

// Test that Seek followed by Prev gives the previous element
TEST_F(SkipListTest_97, SeekThenPrev_97) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);
  list_->Insert(40);
  list_->Insert(50);

  IntSkipList::Iterator iter(list_);
  iter.Seek(30);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());

  iter.Prev();
  EXPECT_FALSE(iter.Valid());
}

// Test that Seek followed by Next gives the next element
TEST_F(SkipListTest_97, SeekThenNext_97) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);
  list_->Insert(40);
  list_->Insert(50);

  IntSkipList::Iterator iter(list_);
  iter.Seek(30);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());

  iter.Next();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(40, iter.key());

  iter.Next();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(50, iter.key());

  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

// Test mixed forward and backward iteration
TEST_F(SkipListTest_97, MixedForwardBackwardIteration_97) {
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
  EXPECT_EQ(2, iter.key());

  iter.Next();
  EXPECT_EQ(3, iter.key());

  iter.Prev();
  EXPECT_EQ(2, iter.key());

  iter.Next();
  EXPECT_EQ(3, iter.key());

  iter.Next();
  EXPECT_EQ(4, iter.key());
}

// Test inserting elements in reverse order and iterating
TEST_F(SkipListTest_97, InsertReverseOrderAndIterate_97) {
  for (int i = 100; i >= 1; i--) {
    list_->Insert(i);
  }

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  for (int i = 1; i <= 100; i++) {
    ASSERT_TRUE(iter.Valid());
    EXPECT_EQ(i, iter.key());
    iter.Next();
  }
  EXPECT_FALSE(iter.Valid());
}

// Test SeekToLast then backward iteration
TEST_F(SkipListTest_97, SeekToLastThenBackward_97) {
  for (int i = 1; i <= 10; i++) {
    list_->Insert(i * 10);
  }

  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  for (int i = 10; i >= 1; i--) {
    ASSERT_TRUE(iter.Valid());
    EXPECT_EQ(i * 10, iter.key());
    iter.Prev();
  }
  EXPECT_FALSE(iter.Valid());
}

// Test Contains does not find non-existent keys
TEST_F(SkipListTest_97, ContainsNonExistentKeys_97) {
  list_->Insert(100);
  list_->Insert(200);
  list_->Insert(300);

  EXPECT_FALSE(list_->Contains(50));
  EXPECT_FALSE(list_->Contains(150));
  EXPECT_FALSE(list_->Contains(250));
  EXPECT_FALSE(list_->Contains(350));
}

// Test iterator creation does not start in valid state
TEST_F(SkipListTest_97, IteratorInitiallyInvalid_97) {
  list_->Insert(1);
  list_->Insert(2);
  list_->Insert(3);

  IntSkipList::Iterator iter(list_);
  EXPECT_FALSE(iter.Valid());
}

// Test Seek to the minimum key
TEST_F(SkipListTest_97, SeekToMinimumKey_97) {
  list_->Insert(5);
  list_->Insert(10);
  list_->Insert(15);

  IntSkipList::Iterator iter(list_);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(5, iter.key());
}

// Test Seek to the maximum key
TEST_F(SkipListTest_97, SeekToMaximumKey_97) {
  list_->Insert(5);
  list_->Insert(10);
  list_->Insert(15);

  IntSkipList::Iterator iter(list_);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(15, iter.key());
}

}  // namespace leveldb
