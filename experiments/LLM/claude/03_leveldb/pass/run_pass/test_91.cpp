#include "gtest/gtest.h"

#include <atomic>
#include <cstdlib>
#include <set>
#include <utility>

#include "db/skiplist.h"
#include "util/arena.h"
#include "util/random.h"

namespace leveldb {

typedef uint64_t Key;

struct Comparator {
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

class SkipListTest_91 : public ::testing::Test {
 protected:
  Arena arena_;
  Comparator cmp_;
};

TEST_F(SkipListTest_91, Empty_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  ASSERT_TRUE(!list.Contains(10));

  SkipList<Key, Comparator>::Iterator iter(&list);
  ASSERT_TRUE(!iter.Valid());
  iter.SeekToFirst();
  ASSERT_TRUE(!iter.Valid());
  iter.Seek(100);
  ASSERT_TRUE(!iter.Valid());
  iter.SeekToLast();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_91, InsertAndLookup_91) {
  const int N = 2000;
  const int R = 5000;
  Random rnd(1000);
  std::set<Key> keys;
  SkipList<Key, Comparator> list(cmp_, &arena_);
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
    SkipList<Key, Comparator>::Iterator iter(&list);
    ASSERT_TRUE(!iter.Valid());

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
  for (int i = 0; i < R; i++) {
    SkipList<Key, Comparator>::Iterator iter(&list);
    iter.Seek(i);

    // Compare against model iterator
    std::set<Key>::iterator model_iter = keys.lower_bound(i);
    for (int j = 0; j < 3; j++) {
      if (model_iter == keys.end()) {
        ASSERT_TRUE(!iter.Valid());
        break;
      } else {
        ASSERT_TRUE(iter.Valid());
        ASSERT_EQ(*model_iter, iter.key());
        ++model_iter;
        iter.Next();
      }
    }
  }

  // Backward iteration test
  {
    SkipList<Key, Comparator>::Iterator iter(&list);
    iter.SeekToLast();

    // Compare against model iterator
    for (auto model_iter = keys.rbegin(); model_iter != keys.rend();
         ++model_iter) {
      ASSERT_TRUE(iter.Valid());
      ASSERT_EQ(*model_iter, iter.key());
      iter.Prev();
    }
    ASSERT_TRUE(!iter.Valid());
  }
}

TEST_F(SkipListTest_91, InsertSingleElement_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(42);
  ASSERT_TRUE(list.Contains(42));
  ASSERT_TRUE(!list.Contains(41));
  ASSERT_TRUE(!list.Contains(43));
}

TEST_F(SkipListTest_91, IteratorSeekToFirstOnSingle_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(100);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(100u, iter.key());
  iter.Next();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_91, IteratorSeekToLastOnSingle_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(100);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(100u, iter.key());
  iter.Prev();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_91, InsertInOrder_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  for (int i = 1; i <= 100; i++) {
    list.Insert(i);
  }

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  for (int i = 1; i <= 100; i++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(static_cast<Key>(i), iter.key());
    iter.Next();
  }
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_91, InsertReverseOrder_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  for (int i = 100; i >= 1; i--) {
    list.Insert(i);
  }

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  for (int i = 1; i <= 100; i++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(static_cast<Key>(i), iter.key());
    iter.Next();
  }
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_91, ContainsNonExistent_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  ASSERT_TRUE(!list.Contains(5));
  ASSERT_TRUE(!list.Contains(15));
  ASSERT_TRUE(!list.Contains(25));
  ASSERT_TRUE(!list.Contains(35));
}

TEST_F(SkipListTest_91, SeekPastEnd_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(30);
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_91, SeekBeforeFirst_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10u, iter.key());
}

TEST_F(SkipListTest_91, SeekExact_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20u, iter.key());
}

TEST_F(SkipListTest_91, PrevFromFirst_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  iter.Prev();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_91, ForwardAndBackward_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);
  list.Insert(4);
  list.Insert(5);

  SkipList<Key, Comparator>::Iterator iter(&list);
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
  iter.Next();
  ASSERT_EQ(2u, iter.key());
}

TEST_F(SkipListTest_91, LargeInsert_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  const int N = 10000;
  Random rnd(42);
  std::set<Key> keys;

  for (int i = 0; i < N; i++) {
    Key key = rnd.Next();
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  // Verify all keys are present
  for (const auto& k : keys) {
    ASSERT_TRUE(list.Contains(k));
  }

  // Verify forward iteration gives correct count and order
  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  auto model_iter = keys.begin();
  size_t count = 0;
  while (iter.Valid()) {
    ASSERT_TRUE(model_iter != keys.end());
    ASSERT_EQ(*model_iter, iter.key());
    ++model_iter;
    iter.Next();
    count++;
  }
  ASSERT_EQ(keys.size(), count);
}

TEST_F(SkipListTest_91, BoundaryKeyZero_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(0);
  ASSERT_TRUE(list.Contains(0));

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(0u, iter.key());
}

TEST_F(SkipListTest_91, BoundaryKeyMax_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  Key max_key = std::numeric_limits<Key>::max();
  list.Insert(max_key);
  ASSERT_TRUE(list.Contains(max_key));

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(max_key, iter.key());
}

TEST_F(SkipListTest_91, SeekBetweenElements_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(30);
  list.Insert(50);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(30u, iter.key());

  iter.Seek(40);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(50u, iter.key());
}

TEST_F(SkipListTest_91, IteratorCopyConstructor_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(2);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(2u, iter.key());

  // Test that we can create another iterator independently
  SkipList<Key, Comparator>::Iterator iter2(&list);
  iter2.SeekToFirst();
  ASSERT_EQ(1u, iter2.key());

  // Original iterator should still be at 2
  ASSERT_EQ(2u, iter.key());
}

TEST_F(SkipListTest_91, MultipleIteratorsIndependent_91) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  for (int i = 1; i <= 5; i++) {
    list.Insert(i);
  }

  SkipList<Key, Comparator>::Iterator iter1(&list);
  SkipList<Key, Comparator>::Iterator iter2(&list);

  iter1.SeekToFirst();
  iter2.SeekToLast();

  ASSERT_EQ(1u, iter1.key());
  ASSERT_EQ(5u, iter2.key());

  iter1.Next();
  iter2.Prev();

  ASSERT_EQ(2u, iter1.key());
  ASSERT_EQ(4u, iter2.key());
}

}  // namespace leveldb
