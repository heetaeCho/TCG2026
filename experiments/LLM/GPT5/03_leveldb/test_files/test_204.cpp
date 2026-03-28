// File: write_batch_setsequence_test_204.cc

#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"

#include <gtest/gtest.h>
#include <limits>

namespace {

using leveldb::WriteBatch;
using leveldb::WriteBatchInternal;
using leveldb::SequenceNumber;

class WriteBatchInternalTest_204 : public ::testing::Test {
protected:
  WriteBatch b1_;
  WriteBatch b2_;
};

// Normal operation: value roundtrip
TEST_F(WriteBatchInternalTest_204, SetSequence_StoresAndRetrievesSameValue_204) {
  const SequenceNumber seq = static_cast<SequenceNumber>(123456789ull);
  WriteBatchInternal::SetSequence(&b1_, seq);

  EXPECT_EQ(seq, WriteBatchInternal::Sequence(&b1_));
}

// Boundary: minimum value (usually 0 for unsigned)
TEST_F(WriteBatchInternalTest_204, SetSequence_ZeroIsHandled_204) {
  const SequenceNumber seq_min = static_cast<SequenceNumber>(0ull);
  WriteBatchInternal::SetSequence(&b1_, seq_min);

  EXPECT_EQ(seq_min, WriteBatchInternal::Sequence(&b1_));
}

// Boundary: maximum value for the type
TEST_F(WriteBatchInternalTest_204, SetSequence_MaxValueIsHandled_204) {
  const SequenceNumber seq_max = std::numeric_limits<SequenceNumber>::max();
  WriteBatchInternal::SetSequence(&b1_, seq_max);

  EXPECT_EQ(seq_max, WriteBatchInternal::Sequence(&b1_));
}

// Idempotence / overwrite behavior: last write wins
TEST_F(WriteBatchInternalTest_204, SetSequence_OverwriteUpdatesObservedValue_204) {
  const SequenceNumber first = static_cast<SequenceNumber>(1ull);
  const SequenceNumber second = static_cast<SequenceNumber>(999999999999ull);

  WriteBatchInternal::SetSequence(&b1_, first);
  ASSERT_EQ(first, WriteBatchInternal::Sequence(&b1_));

  WriteBatchInternal::SetSequence(&b1_, second);
  EXPECT_EQ(second, WriteBatchInternal::Sequence(&b1_));
}

// Independence: setting on one batch does not affect another
TEST_F(WriteBatchInternalTest_204, SetSequence_DoesNotLeakAcrossBatches_204) {
  const SequenceNumber seq1 = static_cast<SequenceNumber>(42ull);
  const SequenceNumber seq2 = static_cast<SequenceNumber>(84ull);

  WriteBatchInternal::SetSequence(&b1_, seq1);
  WriteBatchInternal::SetSequence(&b2_, seq2);

  EXPECT_EQ(seq1, WriteBatchInternal::Sequence(&b1_));
  EXPECT_EQ(seq2, WriteBatchInternal::Sequence(&b2_));
}

// Non-functional effect check: does not change Count() on an empty batch
TEST_F(WriteBatchInternalTest_204, SetSequence_DoesNotChangeCountOnEmptyBatch_204) {
  // Capture initial operation count via public interface
  const int initial_count = WriteBatchInternal::Count(&b1_);

  WriteBatchInternal::SetSequence(&b1_, static_cast<SequenceNumber>(123ull));

  EXPECT_EQ(initial_count, WriteBatchInternal::Count(&b1_));
}

// Non-functional effect check: does not change Count() on a non-empty batch
TEST_F(WriteBatchInternalTest_204, SetSequence_DoesNotChangeCountOnNonEmptyBatch_204) {
  // Add some observable operations using public API
  b1_.Put("k1", "v1");
  b1_.Delete("k2");

  const int count_before = WriteBatchInternal::Count(&b1_);

  WriteBatchInternal::SetSequence(&b1_, static_cast<SequenceNumber>(321ull));

  const int count_after = WriteBatchInternal::Count(&b1_);
  EXPECT_EQ(count_before, count_after);
}

} // namespace
