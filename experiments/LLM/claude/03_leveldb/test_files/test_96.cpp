#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"
#include "util/random.h"

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

class SkipListTest_96 : public ::testing::Test {
 protected:
  Arena arena_;
  IntComparator cmp_;
};

TEST_F(SkipListTest_96, EmptyListIteratorNotValid_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_96, EmptyListSeekToFirst_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_96, EmptyListSeekToLast_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_96, EmptyListSeek_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(100);
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_96, InsertAndLookup_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(10);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());

  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());

  iter.Seek(30);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30, iter.key());
}

TEST_F(SkipListTest_96, InsertSingleElement_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(42);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42, iter.key());

  iter.Next();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_96, SeekToFirstReturnsSmallest_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(30);
  list.Insert(10);
  list.Insert(20);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

TEST_F(SkipListTest_96, SeekToLastReturnsLargest_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(30);
  list.Insert(10);
  list.Insert(20);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30, iter.key());
}

TEST_F(SkipListTest_96, NextTraversesInOrder_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(3);
  list.Insert(1);
  list.Insert(2);

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

  iter.Next();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_96, PrevTraversesInReverseOrder_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(3);
  list.Insert(1);
  list.Insert(2);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
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

TEST_F(SkipListTest_96, SeekToNonExistentKeyGoesToNext_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());
}

TEST_F(SkipListTest_96, SeekBeyondLastElement_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(31);
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_96, SeekBeforeFirstElement_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

TEST_F(SkipListTest_96, ContainsExistingKey_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  ASSERT_TRUE(list.Contains(10));
  ASSERT_TRUE(list.Contains(20));
  ASSERT_TRUE(list.Contains(30));
}

TEST_F(SkipListTest_96, ContainsNonExistingKey_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  ASSERT_FALSE(list.Contains(5));
  ASSERT_FALSE(list.Contains(15));
  ASSERT_FALSE(list.Contains(25));
  ASSERT_FALSE(list.Contains(35));
}

TEST_F(SkipListTest_96, ContainsOnEmptyList_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  ASSERT_FALSE(list.Contains(1));
}

TEST_F(SkipListTest_96, InsertManyElements_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  const int N = 1000;
  for (int i = N; i > 0; i--) {
    list.Insert(static_cast<Key>(i));
  }

  // Verify all elements are present
  for (int i = 1; i <= N; i++) {
    ASSERT_TRUE(list.Contains(static_cast<Key>(i)));
  }

  // Verify ordering via iteration
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  Key prev = 0;
  int count = 0;
  while (iter.Valid()) {
    ASSERT_GT(iter.key(), prev);
    prev = iter.key();
    iter.Next();
    count++;
  }
  ASSERT_EQ(N, count);
}

TEST_F(SkipListTest_96, PrevFromFirstIsNotValid_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());

  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_96, SeekToExactKey_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20, iter.key());
}

TEST_F(SkipListTest_96, IteratorNextThenPrev_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);
  list.Insert(4);
  list.Insert(5);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_EQ(1, iter.key());

  iter.Next();
  ASSERT_EQ(2, iter.key());

  iter.Next();
  ASSERT_EQ(3, iter.key());

  iter.Prev();
  ASSERT_EQ(2, iter.key());

  iter.Prev();
  ASSERT_EQ(1, iter.key());
}

TEST_F(SkipListTest_96, MultipleIteratorsOnSameList_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter1(&list);
  SkipList<Key, IntComparator>::Iterator iter2(&list);

  iter1.SeekToFirst();
  iter2.SeekToLast();

  ASSERT_TRUE(iter1.Valid());
  ASSERT_TRUE(iter2.Valid());
  ASSERT_EQ(10, iter1.key());
  ASSERT_EQ(30, iter2.key());

  // They should be independent
  iter1.Next();
  ASSERT_EQ(20, iter1.key());
  ASSERT_EQ(30, iter2.key());  // iter2 unchanged
}

TEST_F(SkipListTest_96, SeekToZeroKey_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(0);
  list.Insert(1);
  list.Insert(2);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(0);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(0, iter.key());
}

TEST_F(SkipListTest_96, LargeKeyValues_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  Key large1 = 1000000000ULL;
  Key large2 = 2000000000ULL;
  Key large3 = 3000000000ULL;

  list.Insert(large2);
  list.Insert(large1);
  list.Insert(large3);

  ASSERT_TRUE(list.Contains(large1));
  ASSERT_TRUE(list.Contains(large2));
  ASSERT_TRUE(list.Contains(large3));

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_EQ(large1, iter.key());
  iter.Next();
  ASSERT_EQ(large2, iter.key());
  iter.Next();
  ASSERT_EQ(large3, iter.key());
  iter.Next();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_96, FullForwardAndBackwardTraversal_96) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  for (int i = 1; i <= 10; i++) {
    list.Insert(static_cast<Key>(i));
  }

  // Forward
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  for (int i = 1; i <= 10; i++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(static_cast<Key>(i), iter.key());
    if (i < 10) iter.Next();
  }

  // Now go backward from last
  for (int i = 10; i >= 1; i--) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(static_cast<Key>(i), iter.key());
    if (i > 1) iter.Prev();
  }

  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

}  // namespace leveldb
