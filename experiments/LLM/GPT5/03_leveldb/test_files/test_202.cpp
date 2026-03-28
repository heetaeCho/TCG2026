// write_batch_setcount_test.cc
#include "db/write_batch_internal.h"
#include "leveldb/write_batch.h"

#include <gtest/gtest.h>

namespace leveldb {

class WriteBatchInternalSetCountTest_202 : public ::testing::Test {};

// Normal operation: SetCount updates Count on a fresh batch.
TEST_F(WriteBatchInternalSetCountTest_202, SetCount_UpdatesCountOnFreshBatch_202) {
  WriteBatch b;
  EXPECT_GE(WriteBatchInternal::Count(&b), 0);  // sanity check via public API
  WriteBatchInternal::SetCount(&b, 5);
  EXPECT_EQ(WriteBatchInternal::Count(&b), 5);
}

// Boundary: SetCount to zero should be observable via Count.
TEST_F(WriteBatchInternalSetCountTest_202, SetCount_ToZero_202) {
  WriteBatch b;
  // Bump to a non-zero first to ensure we're actually changing something
  WriteBatchInternal::SetCount(&b, 7);
  EXPECT_EQ(WriteBatchInternal::Count(&b), 7);

  WriteBatchInternal::SetCount(&b, 0);
  EXPECT_EQ(WriteBatchInternal::Count(&b), 0);
}

// Interaction with existing operations: after adding entries, SetCount overrides Count.
TEST_F(WriteBatchInternalSetCountTest_202, SetCount_OverridesExistingCount_202) {
  WriteBatch b;
  b.Put(Slice("k1"), Slice("v1"));
  b.Put(Slice("k2"), Slice("v2"));

  // Observe current count through the public internal API
  const int before = WriteBatchInternal::Count(&b);
  EXPECT_GE(before, 1);  // Do not assume exact internal behavior; just ensure it's non-negative

  // Now override the count explicitly and verify it takes effect
  WriteBatchInternal::SetCount(&b, 1);
  EXPECT_EQ(WriteBatchInternal::Count(&b), 1);
}

// Large value: SetCount with a large positive 32-bit value is reflected by Count.
TEST_F(WriteBatchInternalSetCountTest_202, SetCount_LargePositive_202) {
  WriteBatch b;
  const int large = 1 << 30; // A large, but valid positive int
  WriteBatchInternal::SetCount(&b, large);
  EXPECT_EQ(WriteBatchInternal::Count(&b), large);
}

}  // namespace leveldb
