// db/snapshot_list_test_288.cc
#include <gtest/gtest.h>
#include "db/snapshot.h"

namespace leveldb {

class SnapshotListTest_288 : public ::testing::Test {
protected:
  SnapshotList list_;
};

TEST_F(SnapshotListTest_288, InitiallyEmpty_288) {
  // A fresh list should report empty.
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_288, NewSingleSnapshot_BasicProperties_288) {
  // Creating one snapshot makes the list non-empty and both ends point to it.
  SnapshotImpl* s = list_.New(/*sequence_number=*/100);
  ASSERT_NE(s, nullptr);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(list_.oldest(), s);
  EXPECT_EQ(list_.newest(), s);
  EXPECT_EQ(s->sequence_number(), 100u);
}

TEST_F(SnapshotListTest_288, NewTwoSnapshots_OrderOldestNewest_288) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);

  // With two snapshots, oldest/newest should be well-defined.
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(list_.oldest(), s1);
  EXPECT_EQ(list_.newest(), s2);

  // Sequence numbers should match what was requested.
  EXPECT_EQ(s1->sequence_number(), 1u);
  EXPECT_EQ(s2->sequence_number(), 2u);
}

TEST_F(SnapshotListTest_288, DeleteOnlySnapshot_MakesEmpty_288) {
  SnapshotImpl* s = list_.New(10);
  ASSERT_NE(s, nullptr);
  EXPECT_FALSE(list_.empty());

  list_.Delete(s);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_288, DeleteOldest_UpdatesOldestAndNewest_288) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);

  // Precondition checks
  ASSERT_EQ(list_.oldest(), s1);
  ASSERT_EQ(list_.newest(), s2);

  list_.Delete(s1);

  // After removing the oldest, list remains non-empty and both ends are s2.
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(list_.oldest(), s2);
  EXPECT_EQ(list_.newest(), s2);
  EXPECT_EQ(s2->sequence_number(), 2u);
}

TEST_F(SnapshotListTest_288, DeleteNewest_UpdatesNewest_288) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);

  list_.Delete(s2);

  // After removing newest, list remains non-empty and both ends are s1.
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(list_.oldest(), s1);
  EXPECT_EQ(list_.newest(), s1);
  EXPECT_EQ(s1->sequence_number(), 1u);
}

TEST_F(SnapshotListTest_288, DeleteMiddle_KeepsEndsIntact_288) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);
  ASSERT_NE(s3, nullptr);

  // Sanity: oldest/newest reflect the ends before deletion.
  ASSERT_EQ(list_.oldest(), s1);
  ASSERT_EQ(list_.newest(), s3);

  // Remove the middle snapshot.
  list_.Delete(s2);

  // Ends should remain the same; list still non-empty.
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(list_.oldest(), s1);
  EXPECT_EQ(list_.newest(), s3);
  EXPECT_EQ(s1->sequence_number(), 1u);
  EXPECT_EQ(s3->sequence_number(), 3u);
}

TEST_F(SnapshotListTest_288, DeleteAllInVariousOrder_EndsEmpty_288) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);
  ASSERT_NE(s3, nullptr);
  EXPECT_FALSE(list_.empty());

  // Delete in non-creation order to ensure robust handling.
  list_.Delete(s2);
  EXPECT_FALSE(list_.empty());
  list_.Delete(s1);
  EXPECT_FALSE(list_.empty());
  list_.Delete(s3);
  EXPECT_TRUE(list_.empty());
}

}  // namespace leveldb
