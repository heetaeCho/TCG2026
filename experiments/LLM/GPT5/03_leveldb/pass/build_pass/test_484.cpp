// snapshot_list_test_484.cc
#include "db/snapshot.h"
#include <gtest/gtest.h>

namespace leveldb {

class SnapshotListTest_484 : public ::testing::Test {
protected:
  SnapshotList list_;
};

// ------------------------------------------------------------------
// Construction / empty state
// ------------------------------------------------------------------

TEST_F(SnapshotListTest_484, InitiallyEmpty_484) {
  EXPECT_TRUE(list_.empty());
  EXPECT_EQ(nullptr, list_.oldest());
  EXPECT_EQ(nullptr, list_.newest());
}

// ------------------------------------------------------------------
// Single element behavior
// ------------------------------------------------------------------

TEST_F(SnapshotListTest_484, NewCreatesSingleSnapshotAndUpdatesState_484) {
  const SequenceNumber kSeq = 10;
  SnapshotImpl* s = list_.New(kSeq);

  ASSERT_NE(nullptr, s);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s, list_.oldest());
  EXPECT_EQ(s, list_.newest());
  EXPECT_EQ(kSeq, s->sequence_number());
}

TEST_F(SnapshotListTest_484, DeleteSingleSnapshotMakesListEmpty_484) {
  SnapshotImpl* s = list_.New(1);
  ASSERT_NE(nullptr, s);

  list_.Delete(s);

  EXPECT_TRUE(list_.empty());
  EXPECT_EQ(nullptr, list_.oldest());
  EXPECT_EQ(nullptr, list_.newest());
}

// ------------------------------------------------------------------
// Multi-element ordering (observable via oldest/newest)
// ------------------------------------------------------------------

TEST_F(SnapshotListTest_484, OldestAndNewestReflectInsertionOrder_484) {
  SnapshotImpl* s1 = list_.New(100);
  SnapshotImpl* s2 = list_.New(200);

  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);
  ASSERT_NE(s1, s2);

  // With monotonically increasing sequence numbers, oldest should be first inserted, newest last.
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s2, list_.newest());

  // Adding another larger sequence keeps oldest and updates newest.
  SnapshotImpl* s3 = list_.New(300);
  ASSERT_NE(nullptr, s3);
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s3, list_.newest());

  // Basic sanity: sequence numbers preserved
  EXPECT_EQ(100u, s1->sequence_number());
  EXPECT_EQ(200u, s2->sequence_number());
  EXPECT_EQ(300u, s3->sequence_number());
}

// ------------------------------------------------------------------
// Deleting ends (oldest / newest) rebinds endpoints correctly
// ------------------------------------------------------------------

TEST_F(SnapshotListTest_484, DeleteOldestRebindsOldest_484) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);

  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);
  ASSERT_NE(nullptr, s3);

  // Remove oldest (s1). Oldest should become s2, newest unchanged.
  list_.Delete(s1);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s2, list_.oldest());
  EXPECT_EQ(s3, list_.newest());
}

TEST_F(SnapshotListTest_484, DeleteNewestRebindsNewest_484) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);

  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);
  ASSERT_NE(nullptr, s3);

  // Remove newest (s3). Newest should become s2, oldest unchanged.
  list_.Delete(s3);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s2, list_.newest());
}

// ------------------------------------------------------------------
// Deleting a middle element preserves endpoints and non-deleted elements
// ------------------------------------------------------------------

TEST_F(SnapshotListTest_484, DeleteMiddlePreservesOldestAndNewest_484) {
  SnapshotImpl* s1 = list_.New(1);
  SnapshotImpl* s2 = list_.New(2);
  SnapshotImpl* s3 = list_.New(3);

  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);
  ASSERT_NE(nullptr, s3);

  // Remove middle (s2). Oldest/newest should remain s1/s3.
  list_.Delete(s2);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s3, list_.newest());
}

// ------------------------------------------------------------------
// Deleting all elements (from either end) results in empty list
// ------------------------------------------------------------------

TEST_F(SnapshotListTest_484, DeleteAllFromEndsResultsInEmpty_484) {
  SnapshotImpl* s1 = list_.New(11);
  SnapshotImpl* s2 = list_.New(22);

  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);

  // Delete newest first, then oldest.
  list_.Delete(s2);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s1, list_.newest());

  list_.Delete(s1);
  EXPECT_TRUE(list_.empty());
  EXPECT_EQ(nullptr, list_.oldest());
  EXPECT_EQ(nullptr, list_.newest());
}

} // namespace leveldb
