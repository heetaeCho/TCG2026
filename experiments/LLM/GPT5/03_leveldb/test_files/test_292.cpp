// File: db/snapshot_delete_test.cc
#include "db/snapshot.h"
#include <gtest/gtest.h>

namespace leveldb {

class SnapshotListDeleteTest_292 : public ::testing::Test {
protected:
  SnapshotList list_;
};

//
// Normal operation: create one snapshot and delete it
//
TEST_F(SnapshotListDeleteTest_292, NewThenDelete_Single_292) {
  // Precondition: new list is empty
  EXPECT_TRUE(list_.empty());
  EXPECT_EQ(nullptr, list_.oldest());
  EXPECT_EQ(nullptr, list_.newest());

  // Create one snapshot
  SnapshotImpl* s1 = list_.New(/*sequence_number=*/1);
  ASSERT_NE(nullptr, s1);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s1, list_.newest());
  EXPECT_EQ(1u, s1->sequence_number());

  // Delete it
  list_.Delete(s1);

  // Postcondition: list is empty again
  EXPECT_TRUE(list_.empty());
  EXPECT_EQ(nullptr, list_.oldest());
  EXPECT_EQ(nullptr, list_.newest());
}

//
// Boundary: delete the oldest when there are exactly two elements
//
TEST_F(SnapshotListDeleteTest_292, DeleteOldestOfTwo_292) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);
  ASSERT_EQ(s1, list_.oldest());
  ASSERT_EQ(s2, list_.newest());

  list_.Delete(s1);

  // s2 should now be both oldest and newest
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s2, list_.oldest());
  EXPECT_EQ(s2, list_.newest());
  EXPECT_EQ(20u, s2->sequence_number());
}

//
// Boundary: delete the newest when there are exactly two elements
//
TEST_F(SnapshotListDeleteTest_292, DeleteNewestOfTwo_292) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);
  ASSERT_EQ(s1, list_.oldest());
  ASSERT_EQ(s2, list_.newest());

  list_.Delete(s2);

  // s1 should now be both oldest and newest
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s1, list_.newest());
  EXPECT_EQ(10u, s1->sequence_number());
}

//
// Normal operation: delete the middle element in a 3-element list
// Verifies the remaining order (via oldest/newest) is preserved.
//
TEST_F(SnapshotListDeleteTest_292, DeleteMiddleOfThree_292) {
  SnapshotImpl* s1 = list_.New(10);
  SnapshotImpl* s2 = list_.New(20);
  SnapshotImpl* s3 = list_.New(30);
  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);
  ASSERT_NE(nullptr, s3);
  ASSERT_EQ(s1, list_.oldest());
  ASSERT_EQ(s3, list_.newest());

  list_.Delete(s2);

  // Oldest should still be s1, newest should still be s3
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s1, list_.oldest());
  EXPECT_EQ(s3, list_.newest());
  EXPECT_EQ(10u, s1->sequence_number());
  EXPECT_EQ(30u, s3->sequence_number());
}

//
// Exceptional-ish (observable) pattern: delete all, one by one,
// ensuring stable behavior as the list transitions through sizes 3->2->1->0.
//
TEST_F(SnapshotListDeleteTest_292, DeleteAllProgressively_292) {
  SnapshotImpl* s1 = list_.New(100);
  SnapshotImpl* s2 = list_.New(200);
  SnapshotImpl* s3 = list_.New(300);
  ASSERT_NE(nullptr, s1);
  ASSERT_NE(nullptr, s2);
  ASSERT_NE(nullptr, s3);

  // Initial sanity
  ASSERT_FALSE(list_.empty());
  ASSERT_EQ(s1, list_.oldest());
  ASSERT_EQ(s3, list_.newest());

  // Remove oldest (s1)
  list_.Delete(s1);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s2, list_.oldest());
  EXPECT_EQ(s3, list_.newest());

  // Remove newest (s3)
  list_.Delete(s3);
  EXPECT_FALSE(list_.empty());
  EXPECT_EQ(s2, list_.oldest());
  EXPECT_EQ(s2, list_.newest());

  // Remove the last remaining
  list_.Delete(s2);
  EXPECT_TRUE(list_.empty());
  EXPECT_EQ(nullptr, list_.oldest());
  EXPECT_EQ(nullptr, list_.newest());
}

}  // namespace leveldb
