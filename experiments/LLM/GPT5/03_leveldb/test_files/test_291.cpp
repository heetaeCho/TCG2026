// File: snapshot_list_new_test_291.cc
#include <gtest/gtest.h>
#include <limits>
#include "db/snapshot.h"

namespace leveldb {

class SnapshotListTest_291 : public ::testing::Test {
protected:
  SnapshotList list_;

  // Helper to safely delete a snapshot if created.
  void DeleteIfNotNull(const SnapshotImpl* s) {
    if (s) list_.Delete(s);
  }
};

TEST_F(SnapshotListTest_291, NewOnEmptyList_291) {
  // Given a fresh list
  EXPECT_TRUE(list_.empty());

  // When creating the first snapshot
  SnapshotImpl* s = list_.New(static_cast<SequenceNumber>(5));

  // Then the list reflects one element and oldest/newest are that element
  EXPECT_FALSE(list_.empty());
  ASSERT_NE(nullptr, list_.oldest());
  ASSERT_NE(nullptr, list_.newest());
  EXPECT_EQ(static_cast<SequenceNumber>(5), list_.oldest()->sequence_number());
  EXPECT_EQ(static_cast<SequenceNumber>(5), list_.newest()->sequence_number());

  // Cleanup
  DeleteIfNotNull(s);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_291, NewAppendsAndUpdatesNewest_291) {
  // When adding snapshots with increasing sequence numbers
  SnapshotImpl* s1 = list_.New(static_cast<SequenceNumber>(10));
  SnapshotImpl* s2 = list_.New(static_cast<SequenceNumber>(20));

  // Then oldest remains the first, newest becomes the last
  ASSERT_NE(nullptr, list_.oldest());
  ASSERT_NE(nullptr, list_.newest());
  EXPECT_EQ(static_cast<SequenceNumber>(10), list_.oldest()->sequence_number());
  EXPECT_EQ(static_cast<SequenceNumber>(20), list_.newest()->sequence_number());

  // Cleanup (delete newest first or any order, using public Delete)
  DeleteIfNotNull(s2);
  DeleteIfNotNull(s1);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_291, NewAllowsEqualSequence_291) {
  // Given an element with a sequence number
  SnapshotImpl* s1 = list_.New(static_cast<SequenceNumber>(30));

  // When adding another snapshot with the SAME sequence number
  SnapshotImpl* s2 = list_.New(static_cast<SequenceNumber>(30));

  // Then both ends report that same sequence number (non-decreasing is allowed)
  ASSERT_NE(nullptr, list_.oldest());
  ASSERT_NE(nullptr, list_.newest());
  EXPECT_EQ(static_cast<SequenceNumber>(30), list_.oldest()->sequence_number());
  EXPECT_EQ(static_cast<SequenceNumber>(30), list_.newest()->sequence_number());

  // Cleanup
  DeleteIfNotNull(s2);
  DeleteIfNotNull(s1);
  EXPECT_TRUE(list_.empty());
}

TEST_F(SnapshotListTest_291, NewHandlesVeryLargeSequence_291) {
  // When adding a snapshot at a very large sequence number boundary
  const uint64_t kMax = std::numeric_limits<uint64_t>::max();
  SnapshotImpl* s = list_.New(static_cast<SequenceNumber>(kMax));

  // Then oldest/newest reflect that number
  ASSERT_NE(nullptr, list_.oldest());
  ASSERT_NE(nullptr, list_.newest());
  EXPECT_EQ(static_cast<SequenceNumber>(kMax), list_.oldest()->sequence_number());
  EXPECT_EQ(static_cast<SequenceNumber>(kMax), list_.newest()->sequence_number());

  // Cleanup
  DeleteIfNotNull(s);
  EXPECT_TRUE(list_.empty());
}

#ifndef NDEBUG
TEST_F(SnapshotListTest_291, NewRejectsDecreasingSequenceInDebug_291) {
  // Given a snapshot with higher (newest) sequence number
  SnapshotImpl* s1 = list_.New(static_cast<SequenceNumber>(100));

  // When attempting to add a strictly smaller sequence number
  // Then the debug-mode assertion in New should fail (process death)
  EXPECT_DEATH(
      {
        // The call under test: should trigger the assert
        list_.New(static_cast<SequenceNumber>(99));
      },
      ".*");

  // Cleanup the original
  DeleteIfNotNull(s1);
  EXPECT_TRUE(list_.empty());
}
#endif  // NDEBUG

}  // namespace leveldb
