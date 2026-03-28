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

class SkipListTest_102 : public ::testing::Test {
 protected:
  void SetUp() override {
    arena_ = new Arena();
  }

  void TearDown() override {
    delete arena_;
  }

  Arena* arena_;
  IntComparator cmp_;
};

// Test that a newly created SkipList does not contain any key
TEST_F(SkipListTest_102, EmptyListContainsNothing_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  EXPECT_FALSE(list.Contains(0));
  EXPECT_FALSE(list.Contains(1));
  EXPECT_FALSE(list.Contains(-1));
  EXPECT_FALSE(list.Contains(100));
}

// Test inserting a single element and finding it
TEST_F(SkipListTest_102, InsertSingleElement_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(10);
  EXPECT_TRUE(list.Contains(10));
}

// Test that Contains returns false for keys not inserted
TEST_F(SkipListTest_102, ContainsReturnsFalseForMissingKeys_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(10);
  EXPECT_FALSE(list.Contains(5));
  EXPECT_FALSE(list.Contains(15));
  EXPECT_FALSE(list.Contains(0));
  EXPECT_FALSE(list.Contains(-10));
}

// Test inserting multiple elements and verifying all are present
TEST_F(SkipListTest_102, InsertMultipleElements_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
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
  EXPECT_FALSE(list.Contains(12));
  EXPECT_FALSE(list.Contains(25));
}

// Test inserting elements in reverse order
TEST_F(SkipListTest_102, InsertInReverseOrder_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
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
}

// Test inserting negative keys
TEST_F(SkipListTest_102, InsertNegativeKeys_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(-10);
  list.Insert(-5);
  list.Insert(0);
  list.Insert(5);
  list.Insert(10);
  
  EXPECT_TRUE(list.Contains(-10));
  EXPECT_TRUE(list.Contains(-5));
  EXPECT_TRUE(list.Contains(0));
  EXPECT_TRUE(list.Contains(5));
  EXPECT_TRUE(list.Contains(10));
  
  EXPECT_FALSE(list.Contains(-15));
  EXPECT_FALSE(list.Contains(-1));
  EXPECT_FALSE(list.Contains(1));
  EXPECT_FALSE(list.Contains(15));
}

// Test with a large number of sequential inserts
TEST_F(SkipListTest_102, LargeNumberOfInserts_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  const int N = 1000;
  
  for (int i = 0; i < N; i++) {
    list.Insert(i);
  }
  
  for (int i = 0; i < N; i++) {
    EXPECT_TRUE(list.Contains(i));
  }
  
  // Check keys outside the range
  EXPECT_FALSE(list.Contains(-1));
  EXPECT_FALSE(list.Contains(N));
  EXPECT_FALSE(list.Contains(N + 1));
}

// Test boundary: inserting INT_MIN and INT_MAX-like values
TEST_F(SkipListTest_102, BoundaryValues_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(INT_MIN);
  list.Insert(INT_MAX);
  
  EXPECT_TRUE(list.Contains(INT_MIN));
  EXPECT_TRUE(list.Contains(INT_MAX));
  EXPECT_FALSE(list.Contains(0));
}

// Test inserting elements in random-ish order
TEST_F(SkipListTest_102, InsertRandomOrder_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  
  // Insert in a scrambled order
  int keys[] = {50, 10, 90, 30, 70, 20, 80, 40, 60, 100};
  for (int key : keys) {
    list.Insert(key);
  }
  
  for (int key : keys) {
    EXPECT_TRUE(list.Contains(key));
  }
  
  EXPECT_FALSE(list.Contains(0));
  EXPECT_FALSE(list.Contains(15));
  EXPECT_FALSE(list.Contains(55));
  EXPECT_FALSE(list.Contains(101));
}

// Test Contains on empty list with zero key
TEST_F(SkipListTest_102, EmptyListContainsZero_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  EXPECT_FALSE(list.Contains(0));
}

// Test inserting zero
TEST_F(SkipListTest_102, InsertZero_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(0);
  EXPECT_TRUE(list.Contains(0));
  EXPECT_FALSE(list.Contains(1));
  EXPECT_FALSE(list.Contains(-1));
}

// Test inserting many elements and checking neighbors
TEST_F(SkipListTest_102, CheckNeighborKeys_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  
  // Insert only even numbers
  for (int i = 0; i < 100; i += 2) {
    list.Insert(i);
  }
  
  // Even numbers should be found
  for (int i = 0; i < 100; i += 2) {
    EXPECT_TRUE(list.Contains(i));
  }
  
  // Odd numbers should not be found
  for (int i = 1; i < 100; i += 2) {
    EXPECT_FALSE(list.Contains(i));
  }
}

// Test the Iterator on an empty skip list
TEST_F(SkipListTest_102, IteratorOnEmptyList_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  SkipList<int, IntComparator>::Iterator iter(&list);
  
  EXPECT_FALSE(iter.Valid());
}

// Test Iterator SeekToFirst on non-empty list
TEST_F(SkipListTest_102, IteratorSeekToFirst_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(30);
  list.Insert(10);
  list.Insert(20);
  
  SkipList<int, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test Iterator SeekToLast on non-empty list
TEST_F(SkipListTest_102, IteratorSeekToLast_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(30);
  list.Insert(10);
  list.Insert(20);
  
  SkipList<int, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
  
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());
}

// Test Iterator Next traversal in order
TEST_F(SkipListTest_102, IteratorForwardTraversal_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(3);
  list.Insert(1);
  list.Insert(2);
  
  SkipList<int, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());
  
  iter.Next();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(2, iter.key());
  
  iter.Next();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(3, iter.key());
  
  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

// Test Iterator Prev traversal in reverse order
TEST_F(SkipListTest_102, IteratorBackwardTraversal_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(3);
  list.Insert(1);
  list.Insert(2);
  
  SkipList<int, IntComparator>::Iterator iter(&list);
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

// Test Iterator Seek finds the target or next greater key
TEST_F(SkipListTest_102, IteratorSeekExactKey_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);
  
  SkipList<int, IntComparator>::Iterator iter(&list);
  iter.Seek(20);
  
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test Iterator Seek when key is between existing keys
TEST_F(SkipListTest_102, IteratorSeekBetweenKeys_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);
  
  SkipList<int, IntComparator>::Iterator iter(&list);
  iter.Seek(15);
  
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Test Iterator Seek past all keys
TEST_F(SkipListTest_102, IteratorSeekPastEnd_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);
  
  SkipList<int, IntComparator>::Iterator iter(&list);
  iter.Seek(35);
  
  EXPECT_FALSE(iter.Valid());
}

// Test Iterator Seek before all keys
TEST_F(SkipListTest_102, IteratorSeekBeforeAll_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);
  
  SkipList<int, IntComparator>::Iterator iter(&list);
  iter.Seek(5);
  
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test Iterator on single element list
TEST_F(SkipListTest_102, IteratorSingleElement_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  list.Insert(42);
  
  SkipList<int, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(42, iter.key());
  
  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

// Test full forward traversal with many elements
TEST_F(SkipListTest_102, IteratorFullForwardTraversal_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  const int N = 100;
  
  for (int i = N - 1; i >= 0; i--) {
    list.Insert(i);
  }
  
  SkipList<int, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  
  int expected = 0;
  while (iter.Valid()) {
    EXPECT_EQ(expected, iter.key());
    expected++;
    iter.Next();
  }
  EXPECT_EQ(N, expected);
}

// Test SeekToFirst and SeekToLast on empty list
TEST_F(SkipListTest_102, IteratorSeekOnEmptyList_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  SkipList<int, IntComparator>::Iterator iter(&list);
  
  iter.SeekToFirst();
  EXPECT_FALSE(iter.Valid());
  
  iter.SeekToLast();
  EXPECT_FALSE(iter.Valid());
}

// Test Seek on empty list
TEST_F(SkipListTest_102, IteratorSeekOnEmptyListWithKey_102) {
  SkipList<int, IntComparator> list(cmp_, arena_);
  SkipList<int, IntComparator>::Iterator iter(&list);
  
  iter.Seek(42);
  EXPECT_FALSE(iter.Valid());
}

}  // namespace leveldb
