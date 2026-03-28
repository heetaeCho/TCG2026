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

class SkipListTest_98 : public ::testing::Test {
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
TEST_F(SkipListTest_98, EmptyListContainsNothing_98) {
  EXPECT_FALSE(list_->Contains(0));
  EXPECT_FALSE(list_->Contains(1));
  EXPECT_FALSE(list_->Contains(-1));
  EXPECT_FALSE(list_->Contains(100));
}

// Test inserting a single element and verifying Contains
TEST_F(SkipListTest_98, InsertSingleElement_98) {
  list_->Insert(10);
  EXPECT_TRUE(list_->Contains(10));
  EXPECT_FALSE(list_->Contains(9));
  EXPECT_FALSE(list_->Contains(11));
}

// Test inserting multiple elements
TEST_F(SkipListTest_98, InsertMultipleElements_98) {
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
TEST_F(SkipListTest_98, InsertReverseOrder_98) {
  list_->Insert(50);
  list_->Insert(40);
  list_->Insert(30);
  list_->Insert(20);
  list_->Insert(10);

  EXPECT_TRUE(list_->Contains(10));
  EXPECT_TRUE(list_->Contains(20));
  EXPECT_TRUE(list_->Contains(30));
  EXPECT_TRUE(list_->Contains(40));
  EXPECT_TRUE(list_->Contains(50));
}

// Test inserting negative keys
TEST_F(SkipListTest_98, InsertNegativeKeys_98) {
  list_->Insert(-10);
  list_->Insert(-5);
  list_->Insert(0);
  list_->Insert(5);

  EXPECT_TRUE(list_->Contains(-10));
  EXPECT_TRUE(list_->Contains(-5));
  EXPECT_TRUE(list_->Contains(0));
  EXPECT_TRUE(list_->Contains(5));
  EXPECT_FALSE(list_->Contains(-1));
}

// Iterator on empty list should not be valid
TEST_F(SkipListTest_98, IteratorEmptyList_98) {
  IntSkipList::Iterator iter(list_);
  EXPECT_FALSE(iter.Valid());
}

// Iterator SeekToFirst on empty list
TEST_F(SkipListTest_98, IteratorSeekToFirstEmpty_98) {
  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  EXPECT_FALSE(iter.Valid());
}

// Iterator SeekToLast on empty list
TEST_F(SkipListTest_98, IteratorSeekToLastEmpty_98) {
  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  EXPECT_FALSE(iter.Valid());
}

// Iterator Seek on empty list
TEST_F(SkipListTest_98, IteratorSeekEmpty_98) {
  IntSkipList::Iterator iter(list_);
  iter.Seek(10);
  EXPECT_FALSE(iter.Valid());
}

// Iterator SeekToFirst should point to smallest element
TEST_F(SkipListTest_98, IteratorSeekToFirst_98) {
  list_->Insert(30);
  list_->Insert(10);
  list_->Insert(20);

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Iterator SeekToLast should point to largest element
TEST_F(SkipListTest_98, IteratorSeekToLast_98) {
  list_->Insert(30);
  list_->Insert(10);
  list_->Insert(20);

  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());
}

// Iterator forward traversal
TEST_F(SkipListTest_98, IteratorForwardTraversal_98) {
  list_->Insert(3);
  list_->Insert(1);
  list_->Insert(2);

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
  iter.Next();

  EXPECT_FALSE(iter.Valid());
}

// Iterator backward traversal
TEST_F(SkipListTest_98, IteratorBackwardTraversal_98) {
  list_->Insert(3);
  list_->Insert(1);
  list_->Insert(2);

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

// Iterator Seek finds exact key
TEST_F(SkipListTest_98, IteratorSeekExactKey_98) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Iterator Seek finds next greater key when target is not present
TEST_F(SkipListTest_98, IteratorSeekGreaterOrEqual_98) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(20, iter.key());
}

// Iterator Seek past all elements
TEST_F(SkipListTest_98, IteratorSeekPastEnd_98) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(100);
  EXPECT_FALSE(iter.Valid());
}

// Iterator Seek to value less than minimum
TEST_F(SkipListTest_98, IteratorSeekBeforeFirst_98) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test with a single element: iterator operations
TEST_F(SkipListTest_98, SingleElementIterator_98) {
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
}

// Test inserting many elements and iterating in order
TEST_F(SkipListTest_98, ManyElementsInOrder_98) {
  const int N = 1000;
  for (int i = N - 1; i >= 0; i--) {
    list_->Insert(i);
  }

  // Verify all elements exist
  for (int i = 0; i < N; i++) {
    EXPECT_TRUE(list_->Contains(i));
  }

  // Verify forward iteration is in order
  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  for (int i = 0; i < N; i++) {
    ASSERT_TRUE(iter.Valid());
    EXPECT_EQ(i, iter.key());
    iter.Next();
  }
  EXPECT_FALSE(iter.Valid());
}

// Test that elements not inserted are not contained
TEST_F(SkipListTest_98, ContainsNonExistentElements_98) {
  for (int i = 0; i < 100; i += 2) {
    list_->Insert(i);
  }

  for (int i = 0; i < 100; i++) {
    if (i % 2 == 0) {
      EXPECT_TRUE(list_->Contains(i));
    } else {
      EXPECT_FALSE(list_->Contains(i));
    }
  }
}

// Test Prev from SeekToFirst makes iterator invalid
TEST_F(SkipListTest_98, PrevFromFirst_98) {
  list_->Insert(1);
  list_->Insert(2);
  list_->Insert(3);

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  iter.Prev();
  EXPECT_FALSE(iter.Valid());
}

// Test Next from SeekToLast makes iterator invalid
TEST_F(SkipListTest_98, NextFromLast_98) {
  list_->Insert(1);
  list_->Insert(2);
  list_->Insert(3);

  IntSkipList::Iterator iter(list_);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

// Test Seek to the first element
TEST_F(SkipListTest_98, SeekToExactFirst_98) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(10);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(10, iter.key());
}

// Test Seek to the last element
TEST_F(SkipListTest_98, SeekToExactLast_98) {
  list_->Insert(10);
  list_->Insert(20);
  list_->Insert(30);

  IntSkipList::Iterator iter(list_);
  iter.Seek(30);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(30, iter.key());
  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

// Test forward then backward traversal
TEST_F(SkipListTest_98, ForwardThenBackward_98) {
  list_->Insert(1);
  list_->Insert(2);
  list_->Insert(3);
  list_->Insert(4);
  list_->Insert(5);

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  // Move forward to 3
  iter.Next();  // 2
  iter.Next();  // 3
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(3, iter.key());

  // Move backward to 2
  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(2, iter.key());

  // Move backward to 1
  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());
}

// Test large number of elements for Contains performance/correctness
TEST_F(SkipListTest_98, LargeInsertAndContains_98) {
  const int N = 5000;
  for (int i = 0; i < N; i++) {
    list_->Insert(i * 2);  // Insert even numbers
  }

  for (int i = 0; i < N; i++) {
    EXPECT_TRUE(list_->Contains(i * 2));
    EXPECT_FALSE(list_->Contains(i * 2 + 1));
  }
}

// Test that iterator can be reused after SeekToFirst and SeekToLast
TEST_F(SkipListTest_98, IteratorReuse_98) {
  list_->Insert(1);
  list_->Insert(2);
  list_->Insert(3);

  IntSkipList::Iterator iter(list_);

  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(3, iter.key());

  iter.Seek(2);
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(2, iter.key());

  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(1, iter.key());
}

// Test boundary: inserting INT_MIN and INT_MAX-like values
TEST_F(SkipListTest_98, BoundaryValues_98) {
  list_->Insert(-2147483647);
  list_->Insert(2147483647);
  list_->Insert(0);

  EXPECT_TRUE(list_->Contains(-2147483647));
  EXPECT_TRUE(list_->Contains(0));
  EXPECT_TRUE(list_->Contains(2147483647));

  IntSkipList::Iterator iter(list_);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(-2147483647, iter.key());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  EXPECT_EQ(2147483647, iter.key());
}

}  // namespace leveldb
