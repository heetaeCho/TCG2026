// File: write_batch_put_test_205.cc

#include <gtest/gtest.h>
#include <string>
#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "db/dbformat.h"

using namespace leveldb;

class WriteBatchTest_205 : public ::testing::Test {
protected:
  // Utility to create a big string without relying on any internals.
  static std::string BigString(size_t n, char ch = 'x') {
    return std::string(n, ch);
  }
};

// [205] Normal operation: Put increments logical record count by exactly 1.
TEST_F(WriteBatchTest_205, PutIncrementsCount_205) {
  WriteBatch batch;

  const int before = WriteBatchInternal::Count(&batch);
  batch.Put(Slice("key"), Slice("value"));
  const int after = WriteBatchInternal::Count(&batch);

  EXPECT_EQ(after, before + 1);
}

// [205] Normal operation: Multiple Put calls accumulate count and grow size.
TEST_F(WriteBatchTest_205, MultiplePutsAccumulateAndGrowSize_205) {
  WriteBatch batch;

  const int c0 = WriteBatchInternal::Count(&batch);
  const size_t sz0 = WriteBatchInternal::ByteSize(&batch);

  batch.Put(Slice("k1"), Slice("v1"));
  const int c1 = WriteBatchInternal::Count(&batch);
  const size_t sz1 = WriteBatchInternal::ByteSize(&batch);

  batch.Put(Slice("k2"), Slice("v2"));
  const int c2 = WriteBatchInternal::Count(&batch);
  const size_t sz2 = WriteBatchInternal::ByteSize(&batch);

  EXPECT_EQ(c1, c0 + 1);
  EXPECT_EQ(c2, c0 + 2);

  // We do not assert an exact encoding/size—only that size grows monotonically.
  EXPECT_LT(sz0, sz1);
  EXPECT_LT(sz1, sz2);
}

// [205] Boundary: Empty key and/or value are accepted and reflected in count and size growth.
TEST_F(WriteBatchTest_205, PutAcceptsEmptyKeyAndValue_205) {
  WriteBatch batch;

  const int before = WriteBatchInternal::Count(&batch);
  const size_t sz_before = WriteBatchInternal::ByteSize(&batch);

  // Empty key and value
  batch.Put(Slice(), Slice());

  const int after = WriteBatchInternal::Count(&batch);
  const size_t sz_after = WriteBatchInternal::ByteSize(&batch);

  EXPECT_EQ(after, before + 1);
  EXPECT_GT(sz_after, sz_before);  // representation grows, but we don't rely on exact bytes
}

// [205] Stress/Boundary: Large key/value are handled without errors; count increases and size grows.
TEST_F(WriteBatchTest_205, PutHandlesLargeInputs_205) {
  WriteBatch batch;

  const std::string big_key = BigString(1 << 20, 'K');   // ~1MB key
  const std::string big_val = BigString(1 << 20, 'V');   // ~1MB value

  const int before = WriteBatchInternal::Count(&batch);
  const size_t sz_before = WriteBatchInternal::ByteSize(&batch);

  batch.Put(Slice(big_key), Slice(big_val));

  const int after = WriteBatchInternal::Count(&batch);
  const size_t sz_after = WriteBatchInternal::ByteSize(&batch);

  EXPECT_EQ(after, before + 1);
  EXPECT_GT(sz_after, sz_before);
}

// [205] Idempotent check on sequential empty/non-empty mixes to ensure consistent monotonic size increase.
TEST_F(WriteBatchTest_205, MixedEmptyAndNonEmptyPutsMonotonicSizeIncrease_205) {
  WriteBatch batch;

  const size_t s0 = WriteBatchInternal::ByteSize(&batch);
  batch.Put(Slice(), Slice());
  const size_t s1 = WriteBatchInternal::ByteSize(&batch);
  batch.Put(Slice("a"), Slice("b"));
  const size_t s2 = WriteBatchInternal::ByteSize(&batch);
  batch.Put(Slice("longer_key"), Slice("longer_value"));
  const size_t s3 = WriteBatchInternal::ByteSize(&batch);

  EXPECT_LT(s0, s1);
  EXPECT_LT(s1, s2);
  EXPECT_LT(s2, s3);

  const int cnt = WriteBatchInternal::Count(&batch);
  EXPECT_EQ(cnt, 3);  // three Put calls in this test
}
