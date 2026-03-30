// snapshot_list_newest_test_290.cc
#include <gtest/gtest.h>
#include "db/snapshot.h"

namespace leveldb {

class SnapshotListTest_290 : public ::testing::Test {
protected:
  SnapshotList list_;
};

// Normal: newest() on a single-element list returns that element
TEST_F(SnapshotListTest_290, NewestOnSingleSnapshot_ReturnsThatSnapshot_290) {
  SnapshotImpl* s1 = list_.New(/*sequence_number=*/1);
  ASSERT_FALSE(list_.empty());

  SnapshotImpl* newest = list_.newest();
  ASSERT_NE(nullptr, newest);
  EXPECT_EQ(s1, newest);
  EXPECT_EQ(1u, newest->sequence_number());

  list_.Delete(s1);
  EXPECT_TRUE(list_.empty());
}

// Normal: when two snapshots are created, newest() returns the most recently created one
TEST_F(SnapshotListTest_290, NewestOnMultipleSnapshots_ReturnsLastInserted_290) {
  SnapshotImpl* s1 = list_.New(/*sequence_number=*/10);
  SnapshotImpl* s2 = list_.New(/*sequence_number=*/20);

  ASSERT_FALSE(list_.empty());
  SnapshotImpl* newest = list_.newest();
  ASSERT_NE(nullptr, newest);
  EXPECT_EQ(s2, newest);
  EXPECT_EQ(20u, newest->sequence_number());

  // Cleanup
  list_.Delete(s2);
  list_.Delete(s1);
  EXPECT_TRUE(list_.empty());
}

// Boundary/Update: after deleting the newest snapshot, newest() moves to the previous one
TEST_F(SnapshotListTest_290, NewestUpdatesAfterDeletingNewest_290) {
  SnapshotImpl* s1 = list_.New(/*sequence_number=*/100);
  SnapshotImpl* s2 = list_.New(/*sequence_number=*/200);
  SnapshotImpl* s3 = list_.New(/*sequence_number=*/300);

  ASSERT_EQ(s3, list_.newest());
  list_.Delete(s3);

  ASSERT_FALSE(list_.empty());
  SnapshotImpl* newest_after_delete = list_.newest();
  ASSERT_NE(nullptr, newest_after_delete);
  EXPECT_EQ(s2, newest_after_delete);
  EXPECT_EQ(200u, newest_after_delete->sequence_number());

  // Cleanup the rest
  list_.Delete(s2);
  list_.Delete(s1);
  EXPECT_TRUE(list_.empty());
}

// Error case: calling newest() on an empty list should trigger the internal assert
// Use death test to validate the contract that newest() is undefined on empty()
TEST_F(SnapshotListTest_290, NewestOnEmptyList_TriggersAssert_290) {
#if GTEST_HAS_DEATH_TEST
  EXPECT_TRUE(list_.empty());
  // assert(!empty()) should fail; expect process death (abort)
  EXPECT_DEATH_IF_SUPPORTED({ list_.newest(); }, "");
#else
  GTEST_SKIP() << "Death tests not supported on this platform/toolchain.";
#endif
}

}  // namespace leveldb
