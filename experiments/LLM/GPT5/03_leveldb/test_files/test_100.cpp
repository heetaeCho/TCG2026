// TEST_ID: 100

#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"

namespace leveldb {

namespace {

// Simple ascending comparator for integers (black-box acceptable)
struct IntComparator {
  bool operator()(const int a, const int b) const { return a < b; }
};

using IntSkipList = SkipList<int, IntComparator>;

class SkipListIteratorSeekToLastTest_100 : public ::testing::Test {
 protected:
  Arena arena_;
  IntComparator cmp_;
  std::unique_ptr<IntSkipList> list_;

  void SetUp() override {
    list_ = std::make_unique<IntSkipList>(cmp_, &arena_);
  }

  // Helper: fill with provided keys
  void InsertAll(const std::vector<int>& keys) {
    for (int k : keys) list_->Insert(k);
  }
};

}  // namespace

// 1) Boundary: empty list -> iterator becomes invalid after SeekToLast
TEST_F(SkipListIteratorSeekToLastTest_100, EmptyList_YieldsInvalid_100) {
  IntSkipList::Iterator it(list_.get());
  it.SeekToLast();
  EXPECT_FALSE(it.Valid());
}

// 2) Single element: SeekToLast should land on that element and be valid
TEST_F(SkipListIteratorSeekToLastTest_100, SingleElement_PointsToOnlyKey_100) {
  InsertAll({42});

  IntSkipList::Iterator it(list_.get());
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 42);
}

// 3) Multiple elements (unsorted insertion): SeekToLast points to the maximum key
TEST_F(SkipListIteratorSeekToLastTest_100, MultipleElements_PointsToMaxKey_100) {
  InsertAll({5, 1, 9, 3, 7});

  IntSkipList::Iterator it(list_.get());
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 9);
}

// 4) Idempotence: Calling SeekToLast repeatedly should remain on the last element
TEST_F(SkipListIteratorSeekToLastTest_100, RepeatedCalls_RemainsAtLast_100) {
  InsertAll({10, 2, 8});

  IntSkipList::Iterator it(list_.get());
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 10);

  // Call again; should still be valid and at the same key
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 10);
}

// 5) After additional insertions that introduce a new maximum, SeekToLast should reach the new last
TEST_F(SkipListIteratorSeekToLastTest_100, AfterInsertNewMax_SeeksToNewLast_100) {
  InsertAll({4, 6, 9});

  IntSkipList::Iterator it(list_.get());
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 9);

  // Insert a new maximum and call SeekToLast again
  list_->Insert(15);
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 15);
}

// 6) With duplicates present, SeekToLast should still point to the maximum key value
TEST_F(SkipListIteratorSeekToLastTest_100, WithDuplicates_PointsToMaxValue_100) {
  InsertAll({3, 7, 7, 1, 3, 9, 9, 9});

  IntSkipList::Iterator it(list_.get());
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 9);
}

// 7) Sanity: After SeekToLast, moving Prev() should reach the next-lower key if it exists (observable behavior only)
TEST_F(SkipListIteratorSeekToLastTest_100, SeekToLast_ThenPrev_ReachesLowerKey_100) {
  InsertAll({2, 4, 6});

  IntSkipList::Iterator it(list_.get());
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 6);

  it.Prev();  // Should move to next-lower key (public behavior)
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 4);
}

}  // namespace leveldb
