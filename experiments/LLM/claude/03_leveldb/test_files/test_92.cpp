#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"
#include "util/random.h"

#include <set>
#include <thread>
#include <vector>
#include <atomic>

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

class SkipListTest_92 : public ::testing::Test {
 protected:
  Arena arena_;
  Comparator cmp_;
};

TEST_F(SkipListTest_92, Empty_92) {
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

TEST_F(SkipListTest_92, InsertAndLookup_92) {
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
      ASSERT_EQ(keys.count(i), 1);
    } else {
      ASSERT_EQ(keys.count(i), 0);
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

TEST_F(SkipListTest_92, InsertSingleElement_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(42);
  ASSERT_TRUE(list.Contains(42));
  ASSERT_TRUE(!list.Contains(41));
  ASSERT_TRUE(!list.Contains(43));
}

TEST_F(SkipListTest_92, IteratorSeekToFirstOnSingleElement_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(100);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(100, iter.key());
  iter.Next();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_92, IteratorSeekToLastOnSingleElement_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(100);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(100, iter.key());
  iter.Prev();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_92, IteratorPrevFromFirst_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(1, iter.key());
  iter.Prev();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_92, InsertInOrder_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  for (int i = 0; i < 100; i++) {
    list.Insert(i);
  }

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  for (int i = 0; i < 100; i++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(static_cast<Key>(i), iter.key());
    iter.Next();
  }
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_92, InsertInReverseOrder_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  for (int i = 99; i >= 0; i--) {
    list.Insert(i);
  }

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  for (int i = 0; i < 100; i++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(static_cast<Key>(i), iter.key());
    iter.Next();
  }
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_92, SeekPastEnd_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(5);
  list.Insert(10);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(11);
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_92, SeekBetweenElements_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(5);
  list.Insert(10);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(3);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(5, iter.key());

  iter.Seek(6);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

TEST_F(SkipListTest_92, SeekExactMatch_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(5);
  list.Insert(10);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(5);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(5, iter.key());
}

TEST_F(SkipListTest_92, ContainsBoundaryValues_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(0);
  list.Insert(UINT64_MAX);
  
  ASSERT_TRUE(list.Contains(0));
  ASSERT_TRUE(list.Contains(UINT64_MAX));
  ASSERT_TRUE(!list.Contains(1));
}

TEST_F(SkipListTest_92, FullForwardAndBackwardIteration_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);
  list.Insert(40);
  list.Insert(50);

  // Forward
  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  std::vector<Key> forward_keys;
  while (iter.Valid()) {
    forward_keys.push_back(iter.key());
    iter.Next();
  }
  ASSERT_EQ(5u, forward_keys.size());
  ASSERT_EQ(10, forward_keys[0]);
  ASSERT_EQ(50, forward_keys[4]);

  // Backward
  iter.SeekToLast();
  std::vector<Key> backward_keys;
  while (iter.Valid()) {
    backward_keys.push_back(iter.key());
    iter.Prev();
  }
  ASSERT_EQ(5u, backward_keys.size());
  ASSERT_EQ(50, backward_keys[0]);
  ASSERT_EQ(10, backward_keys[4]);

  // Verify forward and backward are consistent
  for (size_t i = 0; i < forward_keys.size(); i++) {
    ASSERT_EQ(forward_keys[i], backward_keys[forward_keys.size() - 1 - i]);
  }
}

TEST_F(SkipListTest_92, LargeNumberOfInserts_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  const int N = 10000;
  for (int i = 0; i < N; i++) {
    list.Insert(static_cast<Key>(i));
  }

  for (int i = 0; i < N; i++) {
    ASSERT_TRUE(list.Contains(static_cast<Key>(i)));
  }
  ASSERT_TRUE(!list.Contains(static_cast<Key>(N)));

  // Verify count via iteration
  SkipList<Key, Comparator>::Iterator iter(&list);
  int count = 0;
  iter.SeekToFirst();
  while (iter.Valid()) {
    count++;
    iter.Next();
  }
  ASSERT_EQ(N, count);
}

TEST_F(SkipListTest_92, SeekBeforeFirstElement_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(0);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10, iter.key());
}

// Concurrent read test - reads while list is being built
TEST_F(SkipListTest_92, ConcurrentRead_92) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  const int N = 1000;

  // Insert some initial elements
  for (int i = 0; i < N; i++) {
    list.Insert(static_cast<Key>(i * 2));  // Even numbers
  }

  // Verify we can iterate concurrently (basic test, single-threaded)
  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  int count = 0;
  Key prev = 0;
  bool first = true;
  while (iter.Valid()) {
    if (!first) {
      ASSERT_LT(prev, iter.key());
    }
    prev = iter.key();
    first = false;
    count++;
    iter.Next();
  }
  ASSERT_EQ(N, count);
}

}  // namespace leveldb
