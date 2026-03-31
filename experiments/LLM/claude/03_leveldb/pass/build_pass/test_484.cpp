#include "gtest/gtest.h"
#include "db/snapshot.h"

namespace leveldb {

class SnapshotListTest_484 : public ::testing::Test {
 protected:
  SnapshotList list_;
};

// Test that a newly created SnapshotList is empty
TEST_F(SnapshotListTest_484, NewListIsEmpty_484) {
  EXPECT_TRUE(list_.empty());
}

// Test that adding a snapshot makes the list non-empty
TEST_F(SnapshotListTest_484, NewSnapshotMakesListNonEmpty_484) {
  SnapshotImpl* s = list_.New(1);
  EXPECT_FALSE(list_.empty());
  list_.Delete(s);
}

// Test that after deleting all snapshots, the list is empty again
TEST_F(SnapshotListTest_484, DeleteAllMakesListEmpty_484) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  list_.Delete(s1);
  list_.Delete(s2);
  EXPECT_TRUE(list_.empty());
}

// Test that a single snapshot is both oldest and newest
TEST_F(SnapshotListTest_484, SingleSnapshotIsOldestAndNewest_484) {
  SnapshotImpl* s = list_.New(100);
  EXPECT_EQ(s, list_.oldest());
  EXPECT_EQ(s, list_.newest());
  list_.Delete(s);
}

// Test that oldest returns the first inserted snapshot
TEST_F(SnapshotListTest_484, OldestReturnsFirstInserted_484) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  EXPECT_EQ(s1, list_.oldest());
  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
}

// Test that newest returns the last inserted snapshot
TEST_F(SnapshotListTest_484, NewestReturnsLastInserted_484) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  EXPECT_EQ(s3, list_.newest());
  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
}

// Test that the sequence number is correctly stored
TEST_F(SnapshotListTest_484, SequenceNumberIsCorrect_484) {
  SnapshotImpl* s = list_.New(42);
  EXPECT_EQ(42u, s->sequence_number());
  list_.Delete(s);
}

// Test deleting the oldest snapshot updates oldest
TEST_F(SnapshotListTest_484, DeleteOldestUpdatesOldest_484) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  list_.Delete(s1);
  EXPECT_EQ(s2, list_.oldest());
  list_.Delete(s2);
  EXPECT_EQ(s3, list_.oldest());
  list_.Delete(s3);
}

// Test deleting the newest snapshot updates newest
TEST_F(SnapshotListTest_484, DeleteNewestUpdatesNewest_484) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  list_.Delete(s3);
  EXPECT_EQ(s2, list_.newest());
  list_.Delete(s2);
  EXPECT_EQ(s1, list_.newest());
  list_.Delete(s1);
}

// Test deleting a middle snapshot doesn't affect oldest/newest
TEST_F(SnapshotListTest_484, DeleteMiddleDoesNotAffectEnds_484) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  list_.Delete(s2);
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s3, list_.newest());
  list_.Delete(s1);
  list_.Delete(s3);
}

// Test with sequence number zero
TEST_F(SnapshotListTest_484, SequenceNumberZero_484) {
  SnapshotImpl* s = list_.New(0);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(0u, s->sequence_number());
  EXPECT_EQ(s, list_.oldest());
  EXPECT_EQ(s, list_.newest());
  list_.Delete(s);
}

// Test adding many snapshots
TEST_F(SnapshotListTest_484, ManySnapshots_484) {
  const int kCount = 100;
  std::vector<SnapshotImpl*> snapshots;
  for (int i = 0; i < kCount; i++) {
    snapshots.push_back(list_.New(static_cast<SequenceNumber>(i)));
  }
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(snapshots.front(), list_.oldest());
  EXPECT_EQ(snapshots.back(), list_.newest());
  
  for (int i = 0; i < kCount; i++) {
    EXPECT_EQ(static_cast<SequenceNumber>(i), snapshots[i]->sequence_number());
  }

  for (auto* s : snapshots) {
    list_.Delete(s);
  }
  EXPECT_TRUE(list_.empty());
}

// Test that each snapshot has a unique and correct sequence number
TEST_F(SnapshotListTest_484, MultipleSequenceNumbers_484) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  EXPECT_EQ(10u, s1->sequence_number());
  EXPECT_EQ(20u, s2->sequence_number());
  EXPECT_EQ(30u, s3->sequence_number());
  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
}

// Test deleting snapshots in reverse order
TEST_F(SnapshotListTest_484, DeleteInReverseOrder_484) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  list_.Delete(s3);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s2, list_.newest());
  list_.Delete(s2);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s1, list_.newest());
  list_.Delete(s1);
  EXPECT_TRUE(list_.empty());
}

// Test with large sequence numbers
TEST_F(SnapshotListTest_484, LargeSequenceNumber_484) {
  SequenceNumber large_seq = static_cast<SequenceNumber>(0xFFFFFFFFFFFFFFULL);
  SnapshotImpl* s = list_.New(large_seq);
  EXPECT_EQ(large_seq, s->sequence_number());
  EXPECT_EQ(s, list_.oldest());
  EXPECT_EQ(s, list_.newest());
  list_.Delete(s);
  EXPECT_TRUE(list_.empty());
}

}  // namespace leveldb
