#include "gtest/gtest.h"
#include "db/snapshot.h"

namespace leveldb {

class SnapshotListTest_292 : public ::testing::Test {
 protected:
  SnapshotList list_;
};

// Test that a newly created SnapshotList is empty
TEST_F(SnapshotListTest_292, NewListIsEmpty_292) {
  EXPECT_TRUE(list_.empty());
}

// Test that adding a snapshot makes the list non-empty
TEST_F(SnapshotListTest_292, NewSnapshotMakesListNonEmpty_292) {
  SnapshotImpl* s = list_.New(1);
  EXPECT_FALSE(list_.empty());
  list_.Delete(s);
}

// Test that after adding and deleting the only snapshot, list is empty again
TEST_F(SnapshotListTest_292, DeleteLastSnapshotMakesListEmpty_292) {
  SnapshotImpl* s = list_.New(1);
  EXPECT_FALSE(list_.empty());
  list_.Delete(s);
  EXPECT_TRUE(list_.empty());
}

// Test that New returns a snapshot with the correct sequence number
TEST_F(SnapshotListTest_292, NewReturnsCorrectSequenceNumber_292) {
  SnapshotImpl* s = list_.New(42);
  EXPECT_EQ(42, s->sequence_number());
  list_.Delete(s);
}

// Test oldest and newest with a single snapshot
TEST_F(SnapshotListTest_292, SingleSnapshotIsOldestAndNewest_292) {
  SnapshotImpl* s = list_.New(10);
  EXPECT_EQ(s, list_.oldest());
  EXPECT_EQ(s, list_.newest());
  list_.Delete(s);
}

// Test oldest and newest with multiple snapshots
TEST_F(SnapshotListTest_292, MultipleSnapshotsOldestAndNewest_292) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);

  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s3, list_.newest());

  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
}

// Test that deleting the oldest updates oldest correctly
TEST_F(SnapshotListTest_292, DeleteOldestUpdatesOldest_292) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);

  EXPECT_EQ(s1, list_.oldest());
  list_.Delete(s1);
  EXPECT_EQ(s2, list_.oldest());

  list_.Delete(s2);
  list_.Delete(s3);
}

// Test that deleting the newest updates newest correctly
TEST_F(SnapshotListTest_292, DeleteNewestUpdatesNewest_292) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);

  EXPECT_EQ(s3, list_.newest());
  list_.Delete(s3);
  EXPECT_EQ(s2, list_.newest());

  list_.Delete(s1);
  list_.Delete(s2);
}

// Test deleting a middle snapshot preserves oldest and newest
TEST_F(SnapshotListTest_292, DeleteMiddlePreservesOldestAndNewest_292) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);

  list_.Delete(s2);
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s3, list_.newest());

  list_.Delete(s1);
  list_.Delete(s3);
}

// Test adding many snapshots and deleting them all
TEST_F(SnapshotListTest_292, ManySnapshotsAddAndDeleteAll_292) {
  const int kCount = 100;
  std::vector<SnapshotImpl*> snapshots;
  for (int i = 0; i < kCount; i++) {
    snapshots.push_back(list_.New(i));
  }
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(snapshots.front(), list_.oldest());
  EXPECT_EQ(snapshots.back(), list_.newest());
  EXPECT_EQ(0, list_.oldest()->sequence_number());
  EXPECT_EQ(kCount - 1, list_.newest()->sequence_number());

  for (auto* s : snapshots) {
    list_.Delete(s);
  }
  EXPECT_TRUE(list_.empty());
}

// Test deleting snapshots in reverse order
TEST_F(SnapshotListTest_292, DeleteInReverseOrder_292) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);

  list_.Delete(s3);
  EXPECT_EQ(s2, list_.newest());
  list_.Delete(s2);
  EXPECT_EQ(s1, list_.newest());
  EXPECT_EQ(s1, list_.oldest());
  list_.Delete(s1);
  EXPECT_TRUE(list_.empty());
}

// Test sequence numbers are correctly stored for each snapshot
TEST_F(SnapshotListTest_292, SequenceNumbersAreCorrect_292) {
  SnapshotImpl* s1 = list_.New(100);
  SnapshotImpl* s2 = list_.New(200);
  SnapshotImpl* s3 = list_.New(300);

  EXPECT_EQ(100, s1->sequence_number());
  EXPECT_EQ(200, s2->sequence_number());
  EXPECT_EQ(300, s3->sequence_number());

  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
}

// Test with sequence number zero
TEST_F(SnapshotListTest_292, SequenceNumberZero_292) {
  SnapshotImpl* s = list_.New(0);
  EXPECT_EQ(0, s->sequence_number());
  EXPECT_FALSE(list_.empty());
  list_.Delete(s);
  EXPECT_TRUE(list_.empty());
}

// Test that deleting from the middle correctly links prev and next
TEST_F(SnapshotListTest_292, DeleteMiddleLinksCorrectly_292) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  SnapshotImpl* s4 = list_.New(4);
  SnapshotImpl* s5 = list_.New(5);

  // Delete middle ones
  list_.Delete(s2);
  list_.Delete(s4);

  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s5, list_.newest());

  // Now delete s3 (the new middle)
  list_.Delete(s3);
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s5, list_.newest());

  list_.Delete(s1);
  list_.Delete(s5);
  EXPECT_TRUE(list_.empty());
}

// Test adding snapshot after deleting all
TEST_F(SnapshotListTest_292, AddAfterDeleteAll_292) {
  SnapshotImpl* s1 = list_.New(1);
  list_.Delete(s1);
  EXPECT_TRUE(list_.empty());

  SnapshotImpl* s2 = list_.New(2);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s2, list_.oldest());
  EXPECT_EQ(s2, list_.newest());
  EXPECT_EQ(2, s2->sequence_number());
  list_.Delete(s2);
}

}  // namespace leveldb
