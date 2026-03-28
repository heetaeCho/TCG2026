#include "gtest/gtest.h"
#include "db/snapshot.h"

namespace leveldb {

class SnapshotListTest_289 : public ::testing::Test {
 protected:
  SnapshotList list_;
};

// Test that a newly created SnapshotList is empty
TEST_F(SnapshotListTest_289, NewListIsEmpty_289) {
  EXPECT_TRUE(list_.empty());
}

// Test that after adding one snapshot, the list is no longer empty
TEST_F(SnapshotListTest_289, NotEmptyAfterNew_289) {
  list_.New(1);
  EXPECT_FALSE(list_.empty());
}

// Test that oldest() returns the first inserted snapshot when multiple exist
TEST_F(SnapshotListTest_289, OldestReturnFirstInserted_289) {
  SnapshotImpl* s1 = list_.New(100);
  list_.New(200);
  list_.New(300);
  EXPECT_EQ(list_.oldest(), s1);
  EXPECT_EQ(list_.oldest()->sequence_number(), 100);
}

// Test that newest() returns the last inserted snapshot when multiple exist
TEST_F(SnapshotListTest_289, NewestReturnLastInserted_289) {
  list_.New(100);
  list_.New(200);
  SnapshotImpl* s3 = list_.New(300);
  EXPECT_EQ(list_.newest(), s3);
  EXPECT_EQ(list_.newest()->sequence_number(), 300);
}

// Test that when only one snapshot exists, oldest and newest are the same
TEST_F(SnapshotListTest_289, SingleSnapshotOldestEqualsNewest_289) {
  SnapshotImpl* s = list_.New(42);
  EXPECT_EQ(list_.oldest(), s);
  EXPECT_EQ(list_.newest(), s);
}

// Test that sequence_number is correctly stored
TEST_F(SnapshotListTest_289, SequenceNumberIsCorrect_289) {
  SnapshotImpl* s = list_.New(12345);
  EXPECT_EQ(s->sequence_number(), 12345);
}

// Test deleting the oldest snapshot updates oldest
TEST_F(SnapshotListTest_289, DeleteOldestUpdatesOldest_289) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  list_.New(30);
  list_.Delete(s1);
  EXPECT_EQ(list_.oldest(), s2);
  EXPECT_EQ(list_.oldest()->sequence_number(), 20);
}

// Test deleting the newest snapshot updates newest
TEST_F(SnapshotListTest_289, DeleteNewestUpdatesNewest_289) {
  list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  list_.Delete(s3);
  EXPECT_EQ(list_.newest(), s2);
  EXPECT_EQ(list_.newest()->sequence_number(), 20);
}

// Test deleting a middle snapshot doesn't affect oldest or newest
TEST_F(SnapshotListTest_289, DeleteMiddleSnapshotPreservesEndpoints_289) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  list_.Delete(s2);
  EXPECT_EQ(list_.oldest(), s1);
  EXPECT_EQ(list_.newest(), s3);
}

// Test deleting the only snapshot makes the list empty
TEST_F(SnapshotListTest_289, DeleteOnlySnapshotMakesEmpty_289) {
  SnapshotImpl* s = list_.New(50);
  list_.Delete(s);
  EXPECT_TRUE(list_.empty());
}

// Test deleting all snapshots makes the list empty
TEST_F(SnapshotListTest_289, DeleteAllSnapshotsMakesEmpty_289) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
  EXPECT_TRUE(list_.empty());
}

// Test adding snapshots with sequence number 0
TEST_F(SnapshotListTest_289, SequenceNumberZero_289) {
  SnapshotImpl* s = list_.New(0);
  EXPECT_EQ(s->sequence_number(), 0);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(list_.oldest(), s);
  EXPECT_EQ(list_.newest(), s);
}

// Test adding many snapshots and verifying oldest/newest
TEST_F(SnapshotListTest_289, ManySnapshots_289) {
  SnapshotImpl* first = list_.New(1);
  SnapshotImpl* last = nullptr;
  for (int i = 2; i <= 100; i++) {
    last = list_.New(i);
  }
  EXPECT_EQ(list_.oldest(), first);
  EXPECT_EQ(list_.oldest()->sequence_number(), 1);
  EXPECT_EQ(list_.newest(), last);
  EXPECT_EQ(list_.newest()->sequence_number(), 100);
}

// Test that deleting snapshots in reverse order works correctly
TEST_F(SnapshotListTest_289, DeleteInReverseOrder_289) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  list_.Delete(s3);
  EXPECT_EQ(list_.newest(), s2);
  list_.Delete(s2);
  EXPECT_EQ(list_.newest(), s1);
  EXPECT_EQ(list_.oldest(), s1);
  list_.Delete(s1);
  EXPECT_TRUE(list_.empty());
}

// Test that New returns a non-null pointer
TEST_F(SnapshotListTest_289, NewReturnsNonNull_289) {
  SnapshotImpl* s = list_.New(999);
  EXPECT_NE(s, nullptr);
}

// Test large sequence number
TEST_F(SnapshotListTest_289, LargeSequenceNumber_289) {
  uint64_t large_seq = (1ULL << 56) - 1;  // Large but valid sequence number
  SnapshotImpl* s = list_.New(large_seq);
  EXPECT_EQ(s->sequence_number(), large_seq);
}

}  // namespace leveldb
