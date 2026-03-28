#include "gtest/gtest.h"
#include "db/snapshot.h"

namespace leveldb {

class SnapshotListTest_291 : public ::testing::Test {
 protected:
  SnapshotList list_;
};

TEST_F(SnapshotListTest_291, InitiallyEmpty_291) {
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_291, NewSnapshotMakesListNonEmpty_291) {
  SnapshotImpl* snap = list_.New(1);
  EXPECT_FALSE(list_.empty());
  list_.Delete(snap);
}

TEST_F(SnapshotListTest_291, NewSnapshotReturnsCorrectSequenceNumber_291) {
  SnapshotImpl* snap = list_.New(42);
  EXPECT_EQ(42, snap->sequence_number());
  list_.Delete(snap);
}

TEST_F(SnapshotListTest_291, SingleSnapshotIsOldestAndNewest_291) {
  SnapshotImpl* snap = list_.New(10);
  EXPECT_EQ(snap, list_.oldest());
  EXPECT_EQ(snap, list_.newest());
  list_.Delete(snap);
}

TEST_F(SnapshotListTest_291, MultipleSnapshotsOldestAndNewest_291) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);
  EXPECT_EQ(snap1, list_.oldest());
  EXPECT_EQ(snap3, list_.newest());
  list_.Delete(snap1);
  list_.Delete(snap2);
  list_.Delete(snap3);
}

TEST_F(SnapshotListTest_291, DeleteOldestUpdatesOldest_291) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);
  list_.Delete(snap1);
  EXPECT_EQ(snap2, list_.oldest());
  EXPECT_EQ(snap3, list_.newest());
  list_.Delete(snap2);
  list_.Delete(snap3);
}

TEST_F(SnapshotListTest_291, DeleteNewestUpdatesNewest_291) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);
  list_.Delete(snap3);
  EXPECT_EQ(snap1, list_.oldest());
  EXPECT_EQ(snap2, list_.newest());
  list_.Delete(snap1);
  list_.Delete(snap2);
}

TEST_F(SnapshotListTest_291, DeleteMiddlePreservesOldestAndNewest_291) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);
  list_.Delete(snap2);
  EXPECT_EQ(snap1, list_.oldest());
  EXPECT_EQ(snap3, list_.newest());
  list_.Delete(snap1);
  list_.Delete(snap3);
}

TEST_F(SnapshotListTest_291, DeleteAllMakesEmpty_291) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  list_.Delete(snap1);
  list_.Delete(snap2);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_291, DeleteSingleSnapshotMakesEmpty_291) {
  SnapshotImpl* snap = list_.New(5);
  EXPECT_FALSE(list_.empty());
  list_.Delete(snap);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_291, NewWithSameSequenceNumber_291) {
  SnapshotImpl* snap1 = list_.New(5);
  SnapshotImpl* snap2 = list_.New(5);
  EXPECT_EQ(5, snap1->sequence_number());
  EXPECT_EQ(5, snap2->sequence_number());
  EXPECT_EQ(snap1, list_.oldest());
  EXPECT_EQ(snap2, list_.newest());
  list_.Delete(snap1);
  list_.Delete(snap2);
}

TEST_F(SnapshotListTest_291, NewWithIncreasingSequenceNumbers_291) {
  SnapshotImpl* snap1 = list_.New(100);
  SnapshotImpl* snap2 = list_.New(200);
  SnapshotImpl* snap3 = list_.New(300);
  EXPECT_EQ(100, list_.oldest()->sequence_number());
  EXPECT_EQ(300, list_.newest()->sequence_number());
  list_.Delete(snap1);
  list_.Delete(snap2);
  list_.Delete(snap3);
}

TEST_F(SnapshotListTest_291, NewWithZeroSequenceNumber_291) {
  SnapshotImpl* snap = list_.New(0);
  EXPECT_EQ(0, snap->sequence_number());
  EXPECT_FALSE(list_.empty());
  list_.Delete(snap);
}

TEST_F(SnapshotListTest_291, NewWithLargeSequenceNumber_291) {
  SnapshotImpl* snap = list_.New(UINT64_MAX);
  EXPECT_EQ(UINT64_MAX, snap->sequence_number());
  list_.Delete(snap);
}

TEST_F(SnapshotListTest_291, ManySnapshotsOrdering_291) {
  const int kCount = 100;
  std::vector<SnapshotImpl*> snapshots;
  for (int i = 0; i < kCount; i++) {
    snapshots.push_back(list_.New(static_cast<SequenceNumber>(i)));
  }
  EXPECT_EQ(snapshots.front(), list_.oldest());
  EXPECT_EQ(snapshots.back(), list_.newest());
  EXPECT_EQ(0, list_.oldest()->sequence_number());
  EXPECT_EQ(kCount - 1, list_.newest()->sequence_number());

  // Delete from the front
  for (int i = 0; i < kCount; i++) {
    list_.Delete(snapshots[i]);
  }
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_291, DeleteInReverseOrder_291) {
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

TEST_F(SnapshotListTest_291, AddAfterDeleteAll_291) {
  SnapshotImpl* snap1 = list_.New(1);
  list_.Delete(snap1);
  EXPECT_TRUE(list_.empty());

  SnapshotImpl* snap2 = list_.New(2);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(snap2, list_.oldest());
  EXPECT_EQ(snap2, list_.newest());
  EXPECT_EQ(2, snap2->sequence_number());
  list_.Delete(snap2);
}

TEST_F(SnapshotListTest_291, DeleteFromMiddleMultipleTimes_291) {
  SnapshotImpl* snap1 = list_.New(1);
  SnapshotImpl* snap2 = list_.New(2);
  SnapshotImpl* snap3 = list_.New(3);
  SnapshotImpl* snap4 = list_.New(4);
  SnapshotImpl* snap5 = list_.New(5);

  list_.Delete(snap2);
  list_.Delete(snap4);

  EXPECT_EQ(snap1, list_.oldest());
  EXPECT_EQ(snap5, list_.newest());

  list_.Delete(snap3);
  EXPECT_EQ(snap1, list_.oldest());
  EXPECT_EQ(snap5, list_.newest());

  list_.Delete(snap1);
  list_.Delete(snap5);
  EXPECT_TRUE(list_.empty());
}

}  // namespace leveldb
