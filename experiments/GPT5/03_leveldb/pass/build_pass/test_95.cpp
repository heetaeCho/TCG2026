// File: skiplist_iterator_key_test_95.cc

#include "db/skiplist.h"
#include <gtest/gtest.h>

namespace {

// Minimal comparator compatible with leveldb::SkipList expectations.
struct IntComparator {
  int operator()(const int& a, const int& b) const {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
  }
};

}  // namespace

namespace leveldb {

class SkipListIteratorKeyTest_95 : public ::testing::Test {
protected:
  SkipListIteratorKeyTest_95() : list_(cmp_, &arena_) {}

  IntComparator cmp_;
  Arena arena_;
  SkipList<int, IntComparator> list_;
};

// --- Normal operation ---

TEST_F(SkipListIteratorKeyTest_95, KeyAfterSeekToFirst_95) {
  list_.Insert(10);
  list_.Insert(20);
  list_.Insert(30);

  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(10, it.key());
}

TEST_F(SkipListIteratorKeyTest_95, KeyAfterSeekToLast_95) {
  list_.Insert(5);
  list_.Insert(15);
  list_.Insert(25);

  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(25, it.key());
}

TEST_F(SkipListIteratorKeyTest_95, KeyUpdatesWithNextTraversal_95) {
  list_.Insert(1);
  list_.Insert(3);
  list_.Insert(2);  // Insertion order should not matter; iteration is sorted.

  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(1, it.key());

  it.Next();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(2, it.key());

  it.Next();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(3, it.key());
}

// --- Boundary & search behavior ---

TEST_F(SkipListIteratorKeyTest_95, KeyAfterSeekGE_95) {
  list_.Insert(10);
  list_.Insert(20);
  list_.Insert(30);

  SkipList<int, IntComparator>::Iterator it(&list_);
  it.Seek(15);  // Seek to first key >= 15
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(20, it.key());

  it.Seek(30);  // Exact match
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(30, it.key());
}

// --- Exceptional / error cases (observable via assert/DEATH in debug) ---

#if GTEST_HAS_DEATH_TEST
TEST_F(SkipListIteratorKeyTest_95, KeyOnInvalidIteratorTriggersAssert_95) {
  // Empty list ⇒ iterator starts invalid; calling key() should assert.
  SkipList<int, IntComparator>::Iterator it(&list_);
  ASSERT_FALSE(it.Valid());
  ASSERT_DEATH({ (void)it.key(); }, ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace leveldb
