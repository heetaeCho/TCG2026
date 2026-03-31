#include "gtest/gtest.h"
#include "db/snapshot.h"

namespace leveldb {

class SnapshotListTest_290 : public ::testing::Test {
 protected:
  SnapshotList list_;
};

// Test that a newly created SnapshotList is empty
TEST_F(SnapshotListTest_290, NewListIsEmpty_290) {
  EXPECT_TRUE(list_.empty());
}

// Test that after adding one snapshot, the list is no longer empty
TEST_F(SnapshotListTest_290, NotEmptyAfterNew_290) {
  list_.New(1);
  EXPECT_FALSE(list_.empty());
}

// Test that newest() returns the single snapshot when only one exists
TEST_F(SnapshotListTest_290, NewestWithSingleElement_290) {
  SnapshotImpl* snap = list_.New(100);
  EXPECT_EQ(snap, list_.newest());
}

// Test that oldest() returns the single snapshot when only one exists
TEST_F(SnapshotListTest_290, OldestWithSingleElement_290) {
  SnapshotImpl* snap = list_.New(100);
  EXPECT_EQ(snap, list_.oldest());
}

// Test that newest() returns the last inserted snapshot
TEST_F(SnapshotListTest_290, NewestReturnsLastInserted_290) {
  list_.New(1);
  list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);
  EXPECT_EQ(snap3, list_.newest());
}

// Test that oldest() returns the first inserted snapshot
TEST_F(SnapshotListTest_290, OldestReturnsFirstInserted_290) {
  SnapshotImpl* snap1 = list_.New(1);
  list_.New(2);
  list_.New(3);
  EXPECT_EQ(snap1, list_.oldest());
}

// Test that the sequence number is correctly stored
TEST_F(SnapshotListTest_290, SequenceNumberIsCorrect_290) {
  SnapshotImpl* snap = list_.New(42);
  EXPECT_EQ(42u, snap->sequence_number());
}

// Test that deleting the only element makes the list empty
TEST_F(SnapshotListTest_290, DeleteMakesListEmpty_290) {
  SnapshotImpl* snap = list_.New(1);
  list_.Delete(snap);
  EXPECT_TRUE(list_.empty());
}

// Test deleting the oldest element updates oldest()
TEST_F(SnapshotListTest_290, DeleteOldestUpdatesOldest_290) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  list_.New(3);
  list_.Delete(snap1);
  EXPECT_EQ(snap2, list_.oldest());
}

// Test deleting the newest element updates newest()
TEST_F(SnapshotListTest_290, DeleteNewestUpdatesNewest_290) {
  list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);
  list_.Delete(snap3);
  EXPECT_EQ(snap2, list_.newest());
}

// Test deleting a middle element keeps oldest and newest intact
TEST_F(SnapshotListTest_290, DeleteMiddleKeepsOldestAndNewest_290) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);
  list_.Delete(snap2);
  EXPECT_EQ(snap1, list_.oldest());
  EXPECT_EQ(snap3, list_.newest());
}

// Test multiple inserts and that each has the correct sequence number
TEST_F(SnapshotListTest_290, MultipleInsertsCorrectSequenceNumbers_290) {
  SnapshotImpl* snap1 = list_.New(10);
  SnapshotImpl* snap2 = list_.New(20);
  SnapshotImpl* snap3 = list_.New(30);
  EXPECT_EQ(10u, snap1->sequence_number());
  EXPECT_EQ(20u, snap2->sequence_number());
  EXPECT_EQ(30u, snap3->sequence_number());
}

// Test deleting all elements one by one
TEST_F(SnapshotListTest_290, DeleteAllElements_290) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);

  list_.Delete(snap2);
  EXPECT_FALSE(list_.empty());

  list_.Delete(snap1);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(snap3, list_.oldest());
  EXPECT_EQ(snap3, list_.newest());

  list_.Delete(snap3);
  EXPECT_TRUE(list_.empty());
}

// Test creating a snapshot with sequence number 0
TEST_F(SnapshotListTest_290, SequenceNumberZero_290) {
  SnapshotImpl* snap = list_.New(0);
  EXPECT_EQ(0u, snap->sequence_number());
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(snap, list_.newest());
  EXPECT_EQ(snap, list_.oldest());
}

// Test with large sequence numbers
TEST_F(SnapshotListTest_290, LargeSequenceNumber_290) {
  SequenceNumber large_seq = static_cast<SequenceNumber>(0xFFFFFFFFFFFFFFULL);
  SnapshotImpl* snap = list_.New(large_seq);
  EXPECT_EQ(large_seq, snap->sequence_number());
}

// Test that newest and oldest are the same when only one element exists
TEST_F(SnapshotListTest_290, SingleElementNewestEqualsOldest_290) {
  SnapshotImpl* snap = list_.New(5);
  EXPECT_EQ(list_.newest(), list_.oldest());
  EXPECT_EQ(snap, list_.newest());
}

// Test adding many snapshots and verifying ordering
TEST_F(SnapshotListTest_290, ManySnapshots_290) {
  const int count = 100;
  SnapshotImpl* first = nullptr;
  SnapshotImpl* last = nullptr;
  for (int i = 0; i < count; i++) {
    SnapshotImpl* s = list_.New(static_cast<SequenceNumber>(i));
    if (i == 0) first = s;
    last = s;
  }
  EXPECT_EQ(first, list_.oldest());
  EXPECT_EQ(last, list_.newest());
  EXPECT_EQ(0u, list_.oldest()->sequence_number());
  EXPECT_EQ(99u, list_.newest()->sequence_number());
}

// Test deleting in reverse order
TEST_F(SnapshotListTest_290, DeleteInReverseOrder_290) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);

  list_.Delete(snap3);
  EXPECT_EQ(snap2, list_.newest());

  list_.Delete(snap2);
  EXPECT_EQ(snap1, list_.newest());
  EXPECT_EQ(snap1, list_.oldest());

  list_.Delete(snap1);
  EXPECT_TRUE(list_.empty());
}

}  // namespace leveldb
