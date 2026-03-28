// File: write_batch_sequence_test_203.cc

#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"

#include <limits>

namespace leveldb {

class WriteBatchInternalTest_203 : public ::testing::Test {
 protected:
  WriteBatchInternalTest_203() = default;
};

// [Normal] Setting a sequence number to 0 should round-trip via Sequence().
TEST_F(WriteBatchInternalTest_203, SetSequenceAndGet_RoundTripZero_203) {
  WriteBatch b;
  WriteBatchInternal::SetSequence(&b, static_cast<SequenceNumber>(0));
  SequenceNumber got = WriteBatchInternal::Sequence(&b);
  EXPECT_EQ(got, static_cast<SequenceNumber>(0));
}

// [Normal] Setting a small non-zero sequence number should round-trip.
TEST_F(WriteBatchInternalTest_203, SetSequenceAndGet_RoundTripSmall_203) {
  WriteBatch b;
  const SequenceNumber expected = static_cast<SequenceNumber>(12345);
  WriteBatchInternal::SetSequence(&b, expected);
  EXPECT_EQ(WriteBatchInternal::Sequence(&b), expected);
}

// [Boundary] Setting the maximum representable sequence number should round-trip.
TEST_F(WriteBatchInternalTest_203, SetSequenceAndGet_RoundTripMax_203) {
  WriteBatch b;
  const SequenceNumber expected =
      static_cast<SequenceNumber>(std::numeric_limits<uint64_t>::max());
  WriteBatchInternal::SetSequence(&b, expected);
  EXPECT_EQ(WriteBatchInternal::Sequence(&b), expected);
}

// [Non-mutating behavior] Calling Sequence() must not modify observable batch state.
TEST_F(WriteBatchInternalTest_203, SequenceDoesNotMutateBatchState_203) {
  WriteBatch b;

  // Populate the batch to make Count/ByteSize observable.
  b.Put(Slice("k1"), Slice("v1"));
  b.Delete(Slice("k2"));

  // Capture observable state.
  const int count_before = WriteBatchInternal::Count(&b);
  const size_t size_before = WriteBatchInternal::ByteSize(&b);

  // Set an arbitrary sequence number, then read it back multiple times.
  const SequenceNumber expected = static_cast<SequenceNumber>(9876543210ULL);
  WriteBatchInternal::SetSequence(&b, expected);

  // Invoke Sequence() and ensure it returns the set value.
  EXPECT_EQ(WriteBatchInternal::Sequence(&b), expected);
  // Invoke again to help catch any hidden mutations on read.
  EXPECT_EQ(WriteBatchInternal::Sequence(&b), expected);

  // Verify no observable mutation to Count/ByteSize occurred.
  EXPECT_EQ(WriteBatchInternal::Count(&b), count_before);
  EXPECT_EQ(WriteBatchInternal::ByteSize(&b), size_before);
}

}  // namespace leveldb
