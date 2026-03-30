// File: db/skiplist_contains_test_102.cc

#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"

namespace leveldb {

namespace {

// Simple comparator for integers that matches the SkipList Comparator contract.
struct IntComparator {
  int operator()(int a, int b) const {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
  }
};

class SkipListContainsTest_102 : public ::testing::Test {
 protected:
  SkipListContainsTest_102() : cmp_(), list_(cmp_, &arena_) {}

  Arena arena_;
  IntComparator cmp_;
  SkipList<int, IntComparator> list_;
};

}  // namespace

// Empty skip list should not contain any key.
TEST_F(SkipListContainsTest_102, EmptyReturnsFalse_102) {
  EXPECT_FALSE(list_.Contains(0));
  EXPECT_FALSE(list_.Contains(-1));
  EXPECT_FALSE(list_.Contains(123));
}

// After inserting a single key, Contains should return true for that key.
TEST_F(SkipListContainsTest_102, SingleInsertFound_102) {
  list_.Insert(42);
  EXPECT_TRUE(list_.Contains(42));
  // Neighboring non-inserted keys should still return false.
  EXPECT_FALSE(list_.Contains(41));
  EXPECT_FALSE(list_.Contains(43));
}

// Multiple inserts (unsorted order): Contains must find exactly inserted keys.
TEST_F(SkipListContainsTest_102, MultipleInsertsFoundAndNotFound_102) {
  const int keys[] = {10, -5, 0, 7, 100, 3};
  for (int k : keys) list_.Insert(k);

  for (int k : keys) {
    EXPECT_TRUE(list_.Contains(k)) << "Expected to contain key " << k;
  }

  // Non-existent keys near existing ones
  EXPECT_FALSE(list_.Contains(9));
  EXPECT_FALSE(list_.Contains(11));
  EXPECT_FALSE(list_.Contains(-6));
  EXPECT_FALSE(list_.Contains(8));
  EXPECT_FALSE(list_.Contains(99));
  EXPECT_FALSE(list_.Contains(101));
}

// Boundary-style checks around min and max inserted keys.
TEST_F(SkipListContainsTest_102, BoundaryMinMax_102) {
  const int keys[] = {-100, -1, 0, 1, 2, 3, 50, 999};
  for (int k : keys) list_.Insert(k);

  // Contains must be true for actual min/max keys.
  EXPECT_TRUE(list_.Contains(-100));
  EXPECT_TRUE(list_.Contains(999));

  // Just outside the range should be false.
  EXPECT_FALSE(list_.Contains(-101));
  EXPECT_FALSE(list_.Contains(1000));
}

// Inserting duplicate keys should still result in Contains being true.
// (We do not assume anything about duplicate storage details.)
TEST_F(SkipListContainsTest_102, DuplicateInsertStillFound_102) {
  list_.Insert(5);
  list_.Insert(5);  // duplicate
  EXPECT_TRUE(list_.Contains(5));

  // Unrelated key should remain false.
  EXPECT_FALSE(list_.Contains(6));
}

// Probing several non-existent keys interleaved with existing ones.
TEST_F(SkipListContainsTest_102, NonExistentNearMatches_102) {
  const int existing[] = {2, 4, 6, 8, 10};
  for (int k : existing) list_.Insert(k);

  // Check evens exist
  for (int k : existing) EXPECT_TRUE(list_.Contains(k));

  // Check odds do not
  for (int k = 1; k <= 11; k += 2) EXPECT_FALSE(list_.Contains(k));
}

}  // namespace leveldb
