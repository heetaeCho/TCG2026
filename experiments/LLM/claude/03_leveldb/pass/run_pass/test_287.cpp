#include "gtest/gtest.h"
#include "db/snapshot.h"

namespace leveldb {

// We need to access the SnapshotList to properly test SnapshotImpl creation and behavior.
// Based on the known dependencies, SnapshotImpl takes a SequenceNumber in its constructor.

class SnapshotImplTest_287 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that sequence_number() returns the value passed to the constructor
TEST_F(SnapshotImplTest_287, SequenceNumberReturnsCorrectValue_287) {
  SnapshotImpl snapshot(100);
  EXPECT_EQ(100, snapshot.sequence_number());
}

// Test with sequence number of zero (boundary)
TEST_F(SnapshotImplTest_287, SequenceNumberZero_287) {
  SnapshotImpl snapshot(0);
  EXPECT_EQ(0, snapshot.sequence_number());
}

// Test with a large sequence number
TEST_F(SnapshotImplTest_287, SequenceNumberLargeValue_287) {
  SequenceNumber large_seq = static_cast<SequenceNumber>(0xFFFFFFFFFFFFFFULL);
  SnapshotImpl snapshot(large_seq);
  EXPECT_EQ(large_seq, snapshot.sequence_number());
}

// Test with sequence number of 1 (boundary near zero)
TEST_F(SnapshotImplTest_287, SequenceNumberOne_287) {
  SnapshotImpl snapshot(1);
  EXPECT_EQ(1, snapshot.sequence_number());
}

// Test that multiple snapshots maintain independent sequence numbers
TEST_F(SnapshotImplTest_287, MultipleSnapshotsIndependent_287) {
  SnapshotImpl snapshot1(10);
  SnapshotImpl snapshot2(20);
  SnapshotImpl snapshot3(30);
  
  EXPECT_EQ(10, snapshot1.sequence_number());
  EXPECT_EQ(20, snapshot2.sequence_number());
  EXPECT_EQ(30, snapshot3.sequence_number());
}

// Test that sequence_number() is const and can be called multiple times
TEST_F(SnapshotImplTest_287, SequenceNumberIsIdempotent_287) {
  SnapshotImpl snapshot(42);
  EXPECT_EQ(42, snapshot.sequence_number());
  EXPECT_EQ(42, snapshot.sequence_number());
  EXPECT_EQ(42, snapshot.sequence_number());
}

// Test with max uint64 value as sequence number
TEST_F(SnapshotImplTest_287, SequenceNumberMaxValue_287) {
  SequenceNumber max_seq = std::numeric_limits<uint64_t>::max();
  SnapshotImpl snapshot(max_seq);
  EXPECT_EQ(max_seq, snapshot.sequence_number());
}

// Test SnapshotList basic operations
class SnapshotListTest_287 : public ::testing::Test {
 protected:
  SnapshotList list_;
};

// Test that a new SnapshotList is empty
TEST_F(SnapshotListTest_287, NewListIsEmpty_287) {
  EXPECT_TRUE(list_.empty());
}

// Test inserting a snapshot into the list
TEST_F(SnapshotListTest_287, InsertMakesListNonEmpty_287) {
  SnapshotImpl* s = list_.New(100);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(100, s->sequence_number());
  list_.Delete(s);
}

// Test that after deleting the only snapshot, list is empty again
TEST_F(SnapshotListTest_287, DeleteMakesListEmpty_287) {
  SnapshotImpl* s = list_.New(100);
  EXPECT_FALSE(list_.empty());
  list_.Delete(s);
  EXPECT_TRUE(list_.empty());
}

// Test newest() returns the most recently inserted snapshot
TEST_F(SnapshotListTest_287, NewestReturnsLastInserted_287) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  
  EXPECT_EQ(s3, list_.newest());
  EXPECT_EQ(30, list_.newest()->sequence_number());
  
  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
}

// Test oldest() returns the first inserted snapshot
TEST_F(SnapshotListTest_287, OldestReturnsFirstInserted_287) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(10, list_.oldest()->sequence_number());
  
  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
}

// Test deleting oldest updates oldest pointer
TEST_F(SnapshotListTest_287, DeleteOldestUpdatesOldest_287) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  
  list_.Delete(s1);
  EXPECT_EQ(s2, list_.oldest());
  EXPECT_EQ(20, list_.oldest()->sequence_number());
  
  list_.Delete(s2);
  EXPECT_EQ(s3, list_.oldest());
  
  list_.Delete(s3);
  EXPECT_TRUE(list_.empty());
}

// Test deleting newest updates newest pointer
TEST_F(SnapshotListTest_287, DeleteNewestUpdatesNewest_287) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  
  list_.Delete(s3);
  EXPECT_EQ(s2, list_.newest());
  EXPECT_EQ(20, list_.newest()->sequence_number());
  
  list_.Delete(s2);
  list_.Delete(s1);
}

// Test deleting middle element
TEST_F(SnapshotListTest_287, DeleteMiddleElement_287) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  
  list_.Delete(s2);
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s3, list_.newest());
  EXPECT_FALSE(list_.empty());
  
  list_.Delete(s1);
  list_.Delete(s3);
}

// Test single element list oldest and newest are the same
TEST_F(SnapshotListTest_287, SingleElementOldestEqualsNewest_287) {
  SnapshotImpl* s = list_.New(42);
  EXPECT_EQ(s, list_.oldest());
  EXPECT_EQ(s, list_.newest());
  list_.Delete(s);
}

}  // namespace leveldb
