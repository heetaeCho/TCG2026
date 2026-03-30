// File: db/skiplist_iterator_next_test.cc

#include "gtest/gtest.h"
#include "db/skiplist.h"
#include "util/arena.h"

namespace {

struct IntComparator {
  int operator()(const int& a, const int& b) const {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
  }
};

using leveldb::SkipList;

class SkipListIteratorTest_96 : public ::testing::Test {
protected:
  IntComparator cmp_;
  leveldb::Arena arena_;
  std::unique_ptr<SkipList<int, IntComparator>> list_;

  void SetUp() override {
    // Construct an empty list for each test; tests will populate as needed.
    list_ = std::make_unique<SkipList<int, IntComparator>>(cmp_, &arena_);
  }

  // Helper to insert a set of keys.
  void InsertKeys(const std::vector<int>& keys) {
    for (int k : keys) {
      list_->Insert(k);
    }
  }
};

// --- Normal operation ---

// After SeekToFirst(), Next() should move to the second element.
TEST_F(SkipListIteratorTest_96, NextMovesToFollowingKey_96) {
  InsertKeys({10, 20, 30});
  typename SkipList<int, IntComparator>::Iterator it(list_.get());

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 10);

  it.Next();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 20);
}

// Using Seek(target) to land on an existing key, Next() should move to the next greater key.
TEST_F(SkipListIteratorTest_96, NextAfterSeekOnExactHit_96) {
  InsertKeys({5, 15, 25, 35});
  typename SkipList<int, IntComparator>::Iterator it(list_.get());

  it.Seek(15);
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 15);

  it.Next();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 25);
}

// Using Seek(target) to land on the first >= target (non-exact), Next() should advance correctly.
TEST_F(SkipListIteratorTest_96, NextAfterSeekToCeilKey_96) {
  InsertKeys({1, 4, 7, 10});
  typename SkipList<int, IntComparator>::Iterator it(list_.get());

  it.Seek(6); // should land on 7 (first >= 6)
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 7);

  it.Next();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 10);
}

// --- Boundary conditions ---

// Calling Next() on the last element should make the iterator invalid.
TEST_F(SkipListIteratorTest_96, NextFromLastMakesIteratorInvalid_96) {
  InsertKeys({2, 4});
  typename SkipList<int, IntComparator>::Iterator it(list_.get());

  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 4);

  it.Next(); // move past last
  EXPECT_FALSE(it.Valid());
}

// On a single-element list, SeekToFirst() then Next() should invalidate the iterator.
TEST_F(SkipListIteratorTest_96, NextInvalidatesOnSingleElementList_96) {
  InsertKeys({42});
  typename SkipList<int, IntComparator>::Iterator it(list_.get());

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 42);

  it.Next();
  EXPECT_FALSE(it.Valid());
}

// --- Exceptional / error-observable behavior ---

// Next() requires Valid(); calling Next() when invalid should hit the debug assertion.
// Use a death test to capture the assertion behavior (when supported).
#if GTEST_HAS_DEATH_TEST
TEST_F(SkipListIteratorTest_96, NextOnInvalidIteratorTriggersAssert_96) {
  // Empty list => iterator is invalid before any Seek/SeekToFirst.
  typename SkipList<int, IntComparator>::Iterator it(list_.get());

  // Expect a death/assert due to the "assert(Valid())" precondition in Next().
  EXPECT_DEATH_IF_SUPPORTED(it.Next(), ".*");
}
#endif

// --- Additional observable traversal correctness ---

// Full forward traversal using Next() should visit sorted order and then become invalid.
TEST_F(SkipListIteratorTest_96, FullForwardTraversalBecomesInvalidAtEnd_96) {
  InsertKeys({8, 1, 5, 3}); // insertion order shouldn't matter to traversal order
  typename SkipList<int, IntComparator>::Iterator it(list_.get());

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 1);

  it.Next();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 3);

  it.Next();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 5);

  it.Next();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key(), 8);

  it.Next();
  EXPECT_FALSE(it.Valid());
}

} // namespace
