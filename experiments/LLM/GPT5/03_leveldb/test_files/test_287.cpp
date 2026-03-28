// File: snapshot_impl_test_287.cc
#include <gtest/gtest.h>
#include <limits>

#include "db/snapshot.h"  // Uses the production header

namespace leveldb {

TEST(SnapshotImplTest_287, ReturnsExactSequenceNumber_287) {
  const SequenceNumber input = static_cast<SequenceNumber>(12345);
  SnapshotImpl snap(input);

  EXPECT_EQ(snap.sequence_number(), input);
}

TEST(SnapshotImplTest_287, HandlesZeroSequenceNumber_287) {
  const SequenceNumber input = static_cast<SequenceNumber>(0);
  SnapshotImpl snap(input);

  EXPECT_EQ(snap.sequence_number(), input);
}

TEST(SnapshotImplTest_287, HandlesLargeSequenceNumber_287) {
  const SequenceNumber input = std::numeric_limits<SequenceNumber>::max();
  SnapshotImpl snap(input);

  EXPECT_EQ(snap.sequence_number(), input);
}

TEST(SnapshotImplTest_287, MultipleInstancesMaintainOwnValues_287) {
  const SequenceNumber a = static_cast<SequenceNumber>(1);
  const SequenceNumber b = static_cast<SequenceNumber>(999999);

  SnapshotImpl snap_a(a);
  SnapshotImpl snap_b(b);

  EXPECT_EQ(snap_a.sequence_number(), a);
  EXPECT_EQ(snap_b.sequence_number(), b);
}

TEST(SnapshotImplTest_287, RepeatedCallsAreStable_287) {
  const SequenceNumber input = static_cast<SequenceNumber>(424242);
  SnapshotImpl snap(input);

  EXPECT_EQ(snap.sequence_number(), input);
  EXPECT_EQ(snap.sequence_number(), input);
  EXPECT_EQ(snap.sequence_number(), input);
}

TEST(SnapshotImplTest_287, ConstCorrectness_AllowsCallOnConstObject_287) {
  const SequenceNumber input = static_cast<SequenceNumber>(101);
  const SnapshotImpl snap(input);  // const object

  // Verifies the method is callable on a const instance and returns the same value.
  EXPECT_EQ(snap.sequence_number(), input);
}

}  // namespace leveldb
