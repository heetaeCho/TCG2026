#include "gtest/gtest.h"
#include "db/snapshot.h"

namespace leveldb {

class SnapshotListTest_288 : public ::testing::Test {
 protected:
  SnapshotList list_;
};

TEST_F(SnapshotListTest_288, InitiallyEmpty_288) {
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_288, NotEmptyAfterNew_288) {
  SnapshotImpl* s = list_.New(1);
  EXPECT_FALSE(list_.empty());
  list_.Delete(s);
}

TEST_F(SnapshotListTest_288, EmptyAfterDeleteOnly_288) {
  SnapshotImpl* s = list_.New(1);
  EXPECT_FALSE(list_.empty());
  list_.Delete(s);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_288, NewReturnsNonNull_288) {
  SnapshotImpl* s = list_.New(100);
  EXPECT_NE(nullptr, s);
  list_.Delete(s);
}

TEST_F(SnapshotListTest_288, SequenceNumberPreserved_288) {
  SnapshotImpl* s = list_.New(42);
  EXPECT_EQ(42, s->sequence_number());
  list_.Delete(s);
}

TEST_F(SnapshotListTest_288, OldestReturnFirstInserted_288) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  EXPECT_EQ(s1, list_.oldest());
  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
}

TEST_F(SnapshotListTest_288, NewestReturnLastInserted_288) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  EXPECT_EQ(s3, list_.newest());
  list_.Delete(s1);
  list_.Delete(s2);
  list_.Delete(s3);
}

TEST_F(SnapshotListTest_288, SingleElementOldestAndNewestSame_288) {
  SnapshotImpl* s = list_.New(10);
  EXPECT_EQ(s, list_.oldest());
  EXPECT_EQ(s, list_.newest());
  list_.Delete(s);
}

TEST_F(SnapshotListTest_288, DeleteOldestUpdatesOldest_288) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  list_.Delete(s1);
  EXPECT_EQ(s2, list_.oldest());
  EXPECT_EQ(s3, list_.newest());
  list_.Delete(s2);
  list_.Delete(s3);
}

TEST_F(SnapshotListTest_288, DeleteNewestUpdatesNewest_288) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  list_.Delete(s3);
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s2, list_.newest());
  list_.Delete(s1);
  list_.Delete(s2);
}

TEST_F(SnapshotListTest_288, DeleteMiddleElement_288) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);
  list_.Delete(s2);
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s3, list_.newest());
  EXPECT_FALSE(list_.empty());
  list_.Delete(s1);
  list_.Delete(s3);
}

TEST_F(SnapshotListTest_288, MultipleInsertAndDeleteAll_288) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  SnapshotImpl* s4 = list_.New(40);
  SnapshotImpl* s5 = list_.New(50);

  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s5, list_.newest());

  list_.Delete(s3);
  list_.Delete(s1);
  EXPECT_EQ(s2, list_.oldest());

  list_.Delete(s5);
  EXPECT_EQ(s4, list_.newest());

  list_.Delete(s2);
  list_.Delete(s4);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_288, SequenceNumberZero_288) {
  SnapshotImpl* s = list_.New(0);
  EXPECT_EQ(0, s->sequence_number());
  EXPECT_FALSE(list_.empty());
  list_.Delete(s);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_288, LargeSequenceNumber_288) {
  SequenceNumber large_seq = UINT64_MAX;
  SnapshotImpl* s = list_.New(large_seq);
  EXPECT_EQ(large_seq, s->sequence_number());
  list_.Delete(s);
}

TEST_F(SnapshotListTest_288, ReinsertAfterEmpty_288) {
  SnapshotImpl* s1 = list_.New(1);
  list_.Delete(s1);
  EXPECT_TRUE(list_.empty());

  SnapshotImpl* s2 = list_.New(2);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s2, list_.oldest());
  EXPECT_EQ(s2, list_.newest());
  EXPECT_EQ(2, s2->sequence_number());
  list_.Delete(s2);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_288, ManySnapshots_288) {
  const int kCount = 100;
  std::vector<SnapshotImpl*> snapshots;
  for (int i = 0; i < kCount; i++) {
    snapshots.push_back(list_.New(static_cast<SequenceNumber>(i)));
  }
  EXPECT_EQ(snapshots.front(), list_.oldest());
  EXPECT_EQ(snapshots.back(), list_.newest());

  for (int i = 0; i < kCount; i++) {
    EXPECT_EQ(static_cast<SequenceNumber>(i), snapshots[i]->sequence_number());
  }

  // Delete in reverse order
  for (int i = kCount - 1; i >= 0; i--) {
    list_.Delete(snapshots[i]);
  }
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_288, DuplicateSequenceNumbers_288) {
  SnapshotImpl* s1 = list_.New(5);
  SnapshotImpl* s2 = list_.New(5);
  EXPECT_NE(s1, s2);
  EXPECT_EQ(5, s1->sequence_number());
  EXPECT_EQ(5, s2->sequence_number());
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s2, list_.newest());
  list_.Delete(s1);
  list_.Delete(s2);
  EXPECT_TRUE(list_.empty());
}

}  // namespace leveldb
