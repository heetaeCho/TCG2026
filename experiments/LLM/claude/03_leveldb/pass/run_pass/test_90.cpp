#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"
#include "util/random.h"

#include <set>
#include <thread>
#include <vector>

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

class SkipListTest_90 : public ::testing::Test {
 protected:
  Arena arena_;
  Comparator cmp_;
};

TEST_F(SkipListTest_90, Empty_90) {
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

TEST_F(SkipListTest_90, InsertAndLookup_90) {
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

TEST_F(SkipListTest_90, InsertSingleElement_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(42);
  ASSERT_TRUE(list.Contains(42));
  ASSERT_TRUE(!list.Contains(41));
  ASSERT_TRUE(!list.Contains(43));
}

TEST_F(SkipListTest_90, InsertMultipleElementsInOrder_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  for (int i = 0; i < 100; i++) {
    list.Insert(i);
  }
  for (int i = 0; i < 100; i++) {
    ASSERT_TRUE(list.Contains(i));
  }
  ASSERT_TRUE(!list.Contains(100));
}

TEST_F(SkipListTest_90, InsertMultipleElementsReverseOrder_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  for (int i = 99; i >= 0; i--) {
    list.Insert(i);
  }
  for (int i = 0; i < 100; i++) {
    ASSERT_TRUE(list.Contains(i));
  }
}

TEST_F(SkipListTest_90, IteratorSeekToFirst_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(3);
  list.Insert(1);
  list.Insert(2);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(1u, iter.key());
}

TEST_F(SkipListTest_90, IteratorSeekToLast_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(3);
  list.Insert(1);
  list.Insert(2);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(3u, iter.key());
}

TEST_F(SkipListTest_90, IteratorNext_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(1u, iter.key());
  iter.Next();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(2u, iter.key());
  iter.Next();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(3u, iter.key());
  iter.Next();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_90, IteratorPrev_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(3u, iter.key());
  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(2u, iter.key());
  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(1u, iter.key());
  iter.Prev();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_90, IteratorSeekExact_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(20);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20u, iter.key());
}

TEST_F(SkipListTest_90, IteratorSeekBetween_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(15);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(20u, iter.key());
}

TEST_F(SkipListTest_90, IteratorSeekPastEnd_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);
  list.Insert(30);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(31);
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_90, ContainsNotPresent_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(5);
  list.Insert(15);
  list.Insert(25);

  ASSERT_TRUE(!list.Contains(0));
  ASSERT_TRUE(!list.Contains(10));
  ASSERT_TRUE(!list.Contains(20));
  ASSERT_TRUE(!list.Contains(30));
}

TEST_F(SkipListTest_90, LargeInsert_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  const int N = 10000;
  Random rnd(42);
  std::set<Key> keys;
  for (int i = 0; i < N; i++) {
    Key key = rnd.Next() % 100000;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  // Verify all inserted keys are present
  for (Key k : keys) {
    ASSERT_TRUE(list.Contains(k));
  }

  // Verify forward iteration produces sorted order
  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  auto model_it = keys.begin();
  while (model_it != keys.end()) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(*model_it, iter.key());
    ++model_it;
    iter.Next();
  }
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_90, ConcurrentRead_90) {
  // Test concurrent reads with a single writer (writer inserts first, then
  // readers verify).
  SkipList<Key, Comparator> list(cmp_, &arena_);
  const int N = 1000;
  for (int i = 0; i < N; i++) {
    list.Insert(i);
  }

  auto reader = [&list](int start, int end) {
    for (int i = start; i < end; i++) {
      ASSERT_TRUE(list.Contains(i));
    }
  };

  std::vector<std::thread> threads;
  for (int t = 0; t < 4; t++) {
    threads.emplace_back(reader, 0, N);
  }
  for (auto& t : threads) {
    t.join();
  }
}

TEST_F(SkipListTest_90, IteratorSeekBeforeFirst_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(10);
  list.Insert(20);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(0);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(10u, iter.key());
}

TEST_F(SkipListTest_90, SingleElementPrevFromFirst_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(42);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42u, iter.key());
  iter.Prev();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_90, SingleElementNextFromLast_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(42);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(42u, iter.key());
  iter.Next();
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_90, SeekToLastThenPrev_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(1);
  list.Insert(2);
  list.Insert(3);
  list.Insert(4);
  list.Insert(5);

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToLast();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(5u, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(4u, iter.key());

  iter.Prev();
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(3u, iter.key());
}

TEST_F(SkipListTest_90, ConsecutiveKeys_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  for (Key k = 0; k < 50; k++) {
    list.Insert(k);
  }

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.SeekToFirst();
  for (Key k = 0; k < 50; k++) {
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(k, iter.key());
    iter.Next();
  }
  ASSERT_TRUE(!iter.Valid());
}

TEST_F(SkipListTest_90, SparseKeys_90) {
  SkipList<Key, Comparator> list(cmp_, &arena_);
  list.Insert(0);
  list.Insert(1000);
  list.Insert(2000);
  list.Insert(3000);

  ASSERT_TRUE(list.Contains(0));
  ASSERT_TRUE(list.Contains(1000));
  ASSERT_TRUE(!list.Contains(500));
  ASSERT_TRUE(!list.Contains(1500));

  SkipList<Key, Comparator>::Iterator iter(&list);
  iter.Seek(500);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(1000u, iter.key());

  iter.Seek(1500);
  ASSERT_TRUE(iter.Valid());
  ASSERT_EQ(2000u, iter.key());

  iter.Seek(3001);
  ASSERT_TRUE(!iter.Valid());
}

}  // namespace leveldb
