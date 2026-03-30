// File: db/skiplist_iterator_prev_test.cc

#include "db/skiplist.h"
#include "util/arena.h"
#include <gtest/gtest.h>

namespace leveldb {
namespace {

struct IntComparator {
  int operator()(const int& a, const int& b) const {
    if (a < b) return -1;
    if (a > b) return +1;
    return 0;
  }
};

class SkipListIteratorPrevTest_97 : public ::testing::Test {
protected:
  Arena arena_;
  IntComparator cmp_;
  SkipList<int, IntComparator> list_;

  SkipListIteratorPrevTest_97()
      : arena_(),
        cmp_(),
        list_(cmp_, &arena_) {}

  void InsertMany(std::initializer_list<int> keys) {
    for (int k : keys) list_.Insert(k);
  }
};

TEST_F(SkipListIteratorPrevTest_97, Prev_FromMiddleMovesToImmediatePredecessor_97) {
  InsertMany({10, 20, 30, 40, 50});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.Seek(40);                // position at key >= 40
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(40, it.key());

  it.Prev();                  // should move to 30
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(30, it.key());
}

TEST_F(SkipListIteratorPrevTest_97, Prev_FromFirstInvalidates_97) {
  InsertMany({10, 20, 30});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(10, it.key());

  it.Prev();                  // stepping before the first should invalidate
  EXPECT_FALSE(it.Valid());
}

TEST_F(SkipListIteratorPrevTest_97, Prev_FromLastMovesToPrevious_97) {
  InsertMany({10, 20, 30});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(30, it.key());

  it.Prev();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(20, it.key());
}

TEST_F(SkipListIteratorPrevTest_97, Prev_MultipleStepsReachInvalid_97) {
  InsertMany({10, 20, 30});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.SeekToLast();            // 30
  ASSERT_TRUE(it.Valid());
  it.Prev();                  // 20
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(20, it.key());
  it.Prev();                  // 10
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(10, it.key());
  it.Prev();                  // before first -> invalid
  EXPECT_FALSE(it.Valid());
}

TEST_F(SkipListIteratorPrevTest_97, Prev_AfterSeekToNonExistingTarget_StepsBeforeCeil_97) {
  // Ensure there’s a gap so Seek goes to the ceiling (>= target).
  InsertMany({10, 20, 30, 40});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.Seek(25);                // expected to land at 30 (first >= 25)
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(30, it.key());

  it.Prev();                  // should move to predecessor (20)
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(20, it.key());
}

TEST_F(SkipListIteratorPrevTest_97, Prev_OnSingleElementListInvalidates_97) {
  InsertMany({42});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.SeekToFirst();           // 42
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(42, it.key());

  it.Prev();                  // before first -> invalid
  EXPECT_FALSE(it.Valid());
}

}  // namespace
}  // namespace leveldb
