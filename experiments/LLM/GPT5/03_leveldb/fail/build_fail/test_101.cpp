// File: db/skiplist_insert_test_101.cc
#include <gtest/gtest.h>
#include "db/skiplist.h"
#include "db/arena.h"

namespace leveldb {
namespace {

struct IntLess {
  bool operator()(const int& a, const int& b) const { return a < b; }
};

class SkipListInsertTest_101 : public ::testing::Test {
 protected:
  SkipListInsertTest_101()
      : cmp_(),
        arena_(),
        list_(cmp_, &arena_) {}

  void InsertAll(const std::vector<int>& keys) {
    for (int k : keys) list_.Insert(k);
  }

  IntLess cmp_;
  Arena arena_;
  SkipList<int, IntLess> list_;
};

// --- Normal operation ---

TEST_F(SkipListInsertTest_101, ContainsOnEmptyReturnsFalse_101) {
  EXPECT_FALSE(list_.Contains(0));
  EXPECT_FALSE(list_.Contains(42));
}

TEST_F(SkipListInsertTest_101, InsertSingleKeyThenContainsTrue_101) {
  list_.Insert(10);
  EXPECT_TRUE(list_.Contains(10));
  EXPECT_FALSE(list_.Contains(9));
  EXPECT_FALSE(list_.Contains(11));
}

TEST_F(SkipListInsertTest_101, InsertMultipleKeysThenContainsEach_101) {
  std::vector<int> keys = {1, 3, 5, 7, 9};
  InsertAll(keys);

  for (int k : keys) {
    EXPECT_TRUE(list_.Contains(k)) << "Expected to find key " << k;
  }
  // A few miss checks around inserted values
  EXPECT_FALSE(list_.Contains(0));
  EXPECT_FALSE(list_.Contains(2));
  EXPECT_FALSE(list_.Contains(10));
}

TEST_F(SkipListInsertTest_101, InsertOutOfOrderKeysThenContainsEach_101) {
  std::vector<int> keys = {50, 10, 40, 20, 30};
  InsertAll(keys);

  for (int k : keys) {
    EXPECT_TRUE(list_.Contains(k)) << "Expected to find key " << k;
  }
  EXPECT_FALSE(list_.Contains(15));
  EXPECT_FALSE(list_.Contains(60));
}

// --- Boundary conditions ---

TEST_F(SkipListInsertTest_101, InsertBoundaryValuesIntMinMax_101) {
  const int kMin = std::numeric_limits<int>::min();
  const int kMax = std::numeric_limits<int>::max();
  InsertAll({kMin, 0, kMax});

  EXPECT_TRUE(list_.Contains(kMin));
  EXPECT_TRUE(list_.Contains(0));
  EXPECT_TRUE(list_.Contains(kMax));
  EXPECT_FALSE(list_.Contains(kMax - 1)); // Nearby non-inserted
}

TEST_F(SkipListInsertTest_101, InsertNegativeAndZeroAndPositive_101) {
  InsertAll({-5, 0, 5});
  EXPECT_TRUE(list_.Contains(-5));
  EXPECT_TRUE(list_.Contains(0));
  EXPECT_TRUE(list_.Contains(5));
  EXPECT_FALSE(list_.Contains(1));
}

// --- Exceptional / error cases as observable ---

// The Insert implementation includes an assertion that rejects duplicate keys.
// In debug builds (asserts enabled), inserting a duplicate should terminate.
// In release builds, asserts are typically disabled, so we only check non-crash behavior.
#if !defined(NDEBUG)
TEST_F(SkipListInsertTest_101, InsertDuplicateKeyTriggersAssertionInDebug_101) {
  ASSERT_DEATH(
      {
        SkipList<int, IntLess> local_list(cmp_, &arena_);
        local_list.Insert(42);
        local_list.Insert(42);  // Expect assertion failure in debug.
      },
      "");  // Match any assertion message.
}
#else
TEST_F(SkipListInsertTest_101, InsertDuplicateKeyIsSafeInRelease_101) {
  // In release builds, behavior on duplicate is not specified by the interface,
  // but we can at least verify it doesn't throw/crash and that Contains remains true.
  list_.Insert(42);
  list_.Insert(42);
  EXPECT_TRUE(list_.Contains(42));
}
#endif

// --- Light stress / broader coverage without relying on internals ---

TEST_F(SkipListInsertTest_101, InsertManySequentialThenSpotCheckContains_101) {
  for (int i = 0; i < 1000; ++i) list_.Insert(i);
  // Spot checks
  EXPECT_TRUE(list_.Contains(0));
  EXPECT_TRUE(list_.Contains(123));
  EXPECT_TRUE(list_.Contains(999));
  EXPECT_FALSE(list_.Contains(-1));
  EXPECT_FALSE(list_.Contains(1000));
}

}  // namespace
}  // namespace leveldb
