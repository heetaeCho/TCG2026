// File: db/skiplist_iterator_valid_test.cc

#include "db/skiplist.h"
#include "util/arena.h"
#include "gtest/gtest.h"

namespace leveldb {

// Minimal comparator for integral keys, consistent with SkipList's expectations.
struct IntComparator {
  int operator()(const int& a, const int& b) const {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
  }
};

class SkipListIteratorValidTest_94 : public ::testing::Test {
 protected:
  SkipListIteratorValidTest_94()
      : list_(cmp_, &arena_) {}

  void SetUp() override {
    // Insert a few elements for non-empty scenarios.
    list_.Insert(10);
    list_.Insert(20);
    list_.Insert(30);
  }

  Arena arena_;
  IntComparator cmp_;
  SkipList<int, IntComparator> list_;
};

// [Normal] Iterator is invalid before any positioning operations.
TEST_F(SkipListIteratorValidTest_94, InitiallyInvalidBeforePositioning_94) {
  SkipList<int, IntComparator>::Iterator it(&list_);
  // No positioning yet.
  EXPECT_FALSE(it.Valid());
}

// [Boundary] Empty list => SeekToFirst() should make iterator invalid.
TEST_F(SkipListIteratorValidTest_94, InvalidOnEmpty_94) {
  Arena arena;
  IntComparator cmp;
  SkipList<int, IntComparator> empty_list(cmp, &arena);

  SkipList<int, IntComparator>::Iterator it(&empty_list);
  it.SeekToFirst();
  EXPECT_FALSE(it.Valid());

  it.SeekToLast();
  EXPECT_FALSE(it.Valid());

  it.Seek(123);
  EXPECT_FALSE(it.Valid());
}

// [Normal] On non-empty list, SeekToFirst() produces a valid iterator.
TEST_F(SkipListIteratorValidTest_94, ValidAfterSeekToFirstWhenNotEmpty_94) {
  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToFirst();
  EXPECT_TRUE(it.Valid());
}

// [Boundary] Seek to last then Next() should make the iterator invalid (past end).
TEST_F(SkipListIteratorValidTest_94, BecomesInvalidAfterNextPastLast_94) {
  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());   // at last (30)
  it.Next();                 // move past end
  EXPECT_FALSE(it.Valid());  // now invalid
}

// [Boundary] Seek to first then Prev() should make the iterator invalid (before begin).
TEST_F(SkipListIteratorValidTest_94, BecomesInvalidAfterPrevBeforeFirst_94) {
  SkipList<int, IntComparator>::Iterator it(&list_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());   // at first (10)
  it.Prev();                 // move before begin
  EXPECT_FALSE(it.Valid());  // now invalid
}

// [Boundary] Seek to a target greater than the maximum key => invalid.
TEST_F(SkipListIteratorValidTest_94, InvalidAfterSeekBeyondLast_94) {
  SkipList<int, IntComparator>::Iterator it(&list_);
  it.Seek(1000);             // target larger than any element
  EXPECT_FALSE(it.Valid());
}

// [Normal] Seek within range stays valid while moving inside bounds.
TEST_F(SkipListIteratorValidTest_94, RemainsValidWithinRange_94) {
  SkipList<int, IntComparator>::Iterator it(&list_);

  it.Seek(15);               // should land on 20 (first >= 15)
  EXPECT_TRUE(it.Valid());

  it.Next();                 // should go to 30
  EXPECT_TRUE(it.Valid());

  it.Prev();                 // back to 20
  EXPECT_TRUE(it.Valid());
}

}  // namespace leveldb
