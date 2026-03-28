#include "db/skiplist.h"

#include <set>
#include <vector>

#include "gtest/gtest.h"
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

class SkipListTest_95 : public testing::Test {
 protected:
  Arena arena_;
  IntComparator cmp_;
};

TEST_F(SkipListTest_95, EmptyList_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  ASSERT_FALSE(list.Contains(10));

  SkipList<Key, IntComparator>::Iterator iter(&list);
  ASSERT_FALSE(iter.Valid());
  iter.SeekToFirst();
  ASSERT_FALSE(iter.Valid());
  iter.SeekToLast();
  ASSERT_FALSE(iter.Valid());
  iter.Seek(100);
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_95, InsertAndLookup_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);

  const int N = 2000;
  const int R = 5000;
  std::set<Key> keys;
  Random rnd(1000);
  for (int i = 0; i < N; i++) {
    Key key = rnd.Next() % R;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  for (int i = 0; i < R; i++) {
    if (list.Contains(i)) {
      ASSERT_EQ(keys.count(i), 1u);
    } else {
      ASSERT_EQ(keys.count(i), 0u);
    }
  }

  // Simple iterator tests
  {
    SkipList<Key, IntComparator>::Iterator iter(&list);
    ASSERT_FALSE(iter.Valid());

    iter.Seek(0);
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(*(keys.begin()), iter.key());

    iter.SeekToFirst();
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(*(keys.begin()), iter.key());

    iter.SeekToLast();
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(*(keys.rbegin()), iter.key());
  }

  // Forward iteration test
  {
    SkipList<Key, IntComparator>::Iterator iter(&list);
    iter.SeekToFirst();
    std::set<Key>::iterator model_iter = keys.begin();
    while (model_iter != keys.end()) {
      ASSERT_TRUE(iter.Valid());
      ASSERT_EQ(*model_iter, iter.key());
      iter.Next();
      ++model_iter;
    }
    ASSERT_FALSE(iter.Valid());
  }

  // Backward iteration test
  {
    SkipList<Key, IntComparator>::Iterator iter(&list);
    iter.SeekToLast();
    std::set<Key>::reverse_iterator model_riter = keys.rbegin();
    while (model_riter != keys.rend()) {
      ASSERT_TRUE(iter.Valid());
      ASSERT_EQ(*model_riter, iter.key());
      iter.Prev();
      ++model_riter;
    }
    ASSERT_FALSE(iter.Valid());
  }
}

TEST_F(SkipListTest_95, SeekExactKey_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20u, iter.key());
}

TEST_F(SkipListTest_95, SeekBetweenKeys_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20u, iter.key());
}

TEST_F(SkipListTest_95, SeekPastEnd_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(100);
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_95, SingleElement_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(42);

  ASSERT_TRUE(list.Contains(42));
  ASSERT_FALSE(list.Contains(41));
  ASSERT_FALSE(list.Contains(43));

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42u, iter.key());
  iter.Next();
  ASSERT_FALSE(iter.Valid());

  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42u, iter.key());
  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_95, ContainsNonExistent_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(5);
  list.Insert(15);
  list.Insert(25);

  ASSERT_FALSE(list.Contains(0));
  ASSERT_FALSE(list.Contains(10));
  ASSERT_FALSE(list.Contains(20));
  ASSERT_FALSE(list.Contains(30));
  ASSERT_TRUE(list.Contains(5));
  ASSERT_TRUE(list.Contains(15));
  ASSERT_TRUE(list.Contains(25));
}

TEST_F(SkipListTest_95, IteratorNextPrevInteraction_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);
  list.Insert(4);
  list.Insert(5);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_EQ(1u, iter.key());

  iter.Next();
  ASSERT_EQ(2u, iter.key());

  iter.Next();
  ASSERT_EQ(3u, iter.key());

  iter.Prev();
  ASSERT_EQ(2u, iter.key());

  iter.Prev();
  ASSERT_EQ(1u, iter.key());

  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_95, SeekToFirstOnEmptyList_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_95, SeekToLastOnEmptyList_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_95, InsertSequentialKeys_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  for (Key i = 0; i < 100; i++) {
    list.Insert(i);
  }

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  for (Key i = 0; i < 100; i++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(i, iter.key());
    iter.Next();
  }
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_95, InsertReverseSequentialKeys_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  for (int i = 99; i >= 0; i--) {
    list.Insert(static_cast<Key>(i));
  }

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToFirst();
  for (Key i = 0; i < 100; i++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(i, iter.key());
    iter.Next();
  }
  ASSERT_FALSE(iter.Valid());
}

TEST_F(SkipListTest_95, LargeNumberOfElements_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  const int N = 10000;
  for (int i = 0; i < N; i++) {
    list.Insert(static_cast<Key>(i * 2));  // Even numbers only
  }

  // Verify all even numbers are contained
  for (int i = 0; i < N; i++) {
    ASSERT_TRUE(list.Contains(static_cast<Key>(i * 2)));
  }

  // Verify odd numbers are not contained
  for (int i = 0; i < N; i++) {
    ASSERT_FALSE(list.Contains(static_cast<Key>(i * 2 + 1)));
  }

  // Seek to an odd number should land on the next even
  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(6u, iter.key());
}

TEST_F(SkipListTest_95, SeekBeforeAllKeys_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(100);
  list.Insert(200);
  list.Insert(300);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.Seek(0);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(100u, iter.key());
}

TEST_F(SkipListTest_95, IteratorCopyBehavior_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);

  SkipList<Key, IntComparator>::Iterator iter1(&list);
  iter1.SeekToFirst();
  ASSERT_EQ(1u, iter1.key());

  // Copy the iterator
  SkipList<Key, IntComparator>::Iterator iter2 = iter1;
  ASSERT_TRUE(iter2.Valid());
  ASSERT_EQ(1u, iter2.key());

  // Advance iter1, iter2 should remain at the same position
  iter1.Next();
  ASSERT_EQ(2u, iter1.key());
  ASSERT_EQ(1u, iter2.key());
}

TEST_F(SkipListTest_95, SeekToLastAndPrevTraversal_95) {
  SkipList<Key, IntComparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);
  list.Insert(40);
  list.Insert(50);

  SkipList<Key, IntComparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(50u, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(40u, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30u, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20u, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10u, iter.key());

  iter.Prev();
  ASSERT_FALSE(iter.Valid());
}

}  // namespace leveldb
