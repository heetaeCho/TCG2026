// File: db/snapshotlist_oldest_test.cc

#include "db/snapshot.h"
#include <gtest/gtest.h>

namespace leveldb {

class SnapshotListTest_289 : public ::testing::Test {
protected:
  SnapshotList list_;
};

// [Normal] With a single snapshot, oldest() returns that snapshot.
TEST_F(SnapshotListTest_289, OldestReturnsOnlyElement_289) {
  SnapshotImpl* s1 = list_.New(/*sequence_number=*/123);
  ASSERT_FALSE(list_.empty());                  // observable precondition
  ASSERT_NE(nullptr, s1);

  SnapshotImpl* oldest = list_.oldest();
  ASSERT_NE(nullptr, oldest);
  EXPECT_EQ(s1, oldest);
  EXPECT_EQ(123u, oldest->sequence_number());   // observable property
}

// [Boundary] Calling oldest() on an empty list triggers the contract assert.
#if GTEST_HAS_DEATH_TEST
TEST_F(SnapshotListTest_289, OldestAssertsWhenEmpty_289) {
  ASSERT_TRUE(list_.empty());
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-deadcode.DeadStores)
        SnapshotImpl* p = list_.oldest();  // Should assert(!empty()) in debug.
        (void)p;
      },
      "");  // Accept any assert message.
}
#endif

// [Normal] With two snapshots, oldest() consistently returns the oldest.
TEST_F(SnapshotListTest_289, OldestAmongTwo_289) {
  SnapshotImpl* s1 = list_.New(/*sequence_number=*/100);
  SnapshotImpl* s2 = list_.New(/*sequence_number=*/200);
  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);

  SnapshotImpl* oldest = list_.oldest();
  ASSERT_NE(nullptr, oldest);
  // Treat as black box: verify it returns the first (older) one we added
  // and that sequence_number matches that snapshot.
  EXPECT_EQ(s1, oldest);
  EXPECT_EQ(100u, oldest->sequence_number());
}

// [Mutation] After deleting the current oldest, oldest() moves to the next one.
TEST_F(SnapshotListTest_289, OldestUpdatesAfterDeletingOldest_289) {
  SnapshotImpl* s1 = list_.New(/*sequence_number=*/10);
  SnapshotImpl* s2 = list_.New(/*sequence_number=*/20);
  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);

  ASSERT_EQ(s1, list_.oldest());  // initial check

  list_.Delete(s1);               // observable mutation through public API
  ASSERT_FALSE(list_.empty());

  SnapshotImpl* oldest_after = list_.oldest();
  ASSERT_NE(nullptr, oldest_after);
  EXPECT_EQ(s2, oldest_after);
  EXPECT_EQ(20u, oldest_after->sequence_number());
}

// [Mutation/Boundary] Deleting a non-oldest element does not change oldest().
TEST_F(SnapshotListTest_289, OldestUnaffectedWhenDeletingNewest_289) {
  SnapshotImpl* s1 = list_.New(/*sequence_number=*/1);
  SnapshotImpl* s2 = list_.New(/*sequence_number=*/2);
  SnapshotImpl* s3 = list_.New(/*sequence_number=*/3);
  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);
  ASSERT_NE(nullptr, s3);

  ASSERT_EQ(s1, list_.oldest());  // baseline

  list_.Delete(s3);               // delete a non-oldest snapshot
  ASSERT_FALSE(list_.empty());

  SnapshotImpl* oldest_after = list_.oldest();
  ASSERT_NE(nullptr, oldest_after);
  EXPECT_EQ(s1, oldest_after);    // oldest should remain the same
  EXPECT_EQ(1u, oldest_after->sequence_number());
}

}  // namespace leveldb
