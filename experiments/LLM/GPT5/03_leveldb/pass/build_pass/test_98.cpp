// File: skiplist_iterator_seek_test_98.cc

#include "db/skiplist.h"
#include "util/arena.h"
#include <gtest/gtest.h>

namespace leveldb {
namespace {

struct IntComparator {
  // LevelDB-style comparator: negative if a < b, 0 if equal, positive if a > b
  int operator()(const int& a, const int& b) const {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
  }
};

class SkipListIteratorSeekTest_98 : public ::testing::Test {
protected:
  Arena arena_;
  IntComparator cmp_;
  SkipList<int, IntComparator> list_;

  SkipListIteratorSeekTest_98()
      : arena_(),
        cmp_(),
        list_(cmp_, &arena_) {}

  void InsertAll(const std::vector<int>& keys) {
    for (int k : keys) list_.Insert(k);
  }
};

// Normal operation: Seek to an existing key should point to that key.
TEST_F(SkipListIteratorSeekTest_98, Seek_ExactMatchPointsToKey_98) {
  InsertAll({10, 20, 30, 40});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.Seek(20);
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(20, it.key());

  it.Seek(40);
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(40, it.key());
}

// Normal operation: Seek to a value between keys positions to the smallest key >= target.
TEST_F(SkipListIteratorSeekTest_98, Seek_BetweenKeysPointsToNextGreater_98) {
  InsertAll({10, 20, 30, 40});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.Seek(25);
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(30, it.key());

  it.Seek(11);
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(20, it.key());
}

// Boundary: Seek smaller than the smallest element should land on the first element.
TEST_F(SkipListIteratorSeekTest_98, Seek_SmallerThanMinPointsToFirst_98) {
  InsertAll({5, 10, 15});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.Seek(-100);
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(5, it.key());
}

// Boundary: Seek greater than the largest element should be invalid.
TEST_F(SkipListIteratorSeekTest_98, Seek_GreaterThanMaxIsInvalid_98) {
  InsertAll({1, 2, 3});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.Seek(100);
  EXPECT_FALSE(it.Valid());
}

// Exceptional/edge: Seek on an empty list should be invalid.
TEST_F(SkipListIteratorSeekTest_98, Seek_OnEmptyListIsInvalid_98) {
  typename SkipList<int, IntComparator>::Iterator it(&list_);
  it.Seek(10);
  EXPECT_FALSE(it.Valid());
}

// Interaction with iteration: After Seek to middle, Next should advance to the immediate successor.
TEST_F(SkipListIteratorSeekTest_98, Seek_ThenNextAdvancesSequentially_98) {
  InsertAll({10, 20, 30, 40});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.Seek(25);                // should position at 30
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(30, it.key());

  it.Next();                  // expect 40
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(40, it.key());
}

// Stability: Multiple seeks should reposition correctly each time.
TEST_F(SkipListIteratorSeekTest_98, Seek_MultipleSequentialSeeksReposition_98) {
  InsertAll({10, 20, 30, 40});
  typename SkipList<int, IntComparator>::Iterator it(&list_);

  it.Seek(35);
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(40, it.key());

  it.Seek(0);
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(10, it.key());

  it.Seek(20);
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(20, it.key());

  it.Seek(100);  // beyond max
  EXPECT_FALSE(it.Valid());
}

}  // namespace
}  // namespace leveldb
