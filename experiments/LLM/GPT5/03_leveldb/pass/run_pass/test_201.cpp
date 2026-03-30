// File: write_batch_count_test_201.cc

#include "gtest/gtest.h"

#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "leveldb/slice.h"

using leveldb::Slice;
using leveldb::WriteBatch;
using leveldb::WriteBatchInternal;

namespace {

// (Optional) simple fixture for shared helpers
class WriteBatchCountTest_201 : public ::testing::Test {
 protected:
  // Helper to read count via the provided interface
  static int GetCount(const WriteBatch* b) {
    // The partial code exposes a non-static Count method; use an instance call.
    WriteBatchInternal helper;
    return helper.Count(b);
  }
};

}  // namespace

// --- Normal operation ---

TEST_F(WriteBatchCountTest_201, EmptyBatch_HasZeroCount_201) {
  WriteBatch b;
  EXPECT_EQ(0, WriteBatchCountTest_201::GetCount(&b))
      << "A freshly constructed WriteBatch should have a count of 0.";
}

TEST_F(WriteBatchCountTest_201, Put_IncreasesCountByOne_201) {
  WriteBatch b;
  b.Put(Slice("k1"), Slice("v1"));
  EXPECT_EQ(1, WriteBatchCountTest_201::GetCount(&b))
      << "One Put operation should increase the count to 1.";
}

TEST_F(WriteBatchCountTest_201, Delete_IncreasesCountByOne_201) {
  WriteBatch b;
  b.Delete(Slice("k1"));
  EXPECT_EQ(1, WriteBatchCountTest_201::GetCount(&b))
      << "One Delete operation should increase the count to 1.";
}

TEST_F(WriteBatchCountTest_201, MultipleOps_CountAccumulates_201) {
  WriteBatch b;
  b.Put(Slice("a"), Slice("1"));
  b.Put(Slice("b"), Slice("2"));
  b.Delete(Slice("c"));
  b.Put(Slice("d"), Slice("3"));
  EXPECT_EQ(4, WriteBatchCountTest_201::GetCount(&b))
      << "Count should equal the total number of recorded operations.";
}

// --- Boundary conditions ---

TEST_F(WriteBatchCountTest_201, Clear_ResetsCountToZero_201) {
  WriteBatch b;
  b.Put(Slice("x"), Slice("y"));
  b.Delete(Slice("z"));
  ASSERT_EQ(2, WriteBatchCountTest_201::GetCount(&b))
      << "Sanity check before Clear().";
  b.Clear();
  EXPECT_EQ(0, WriteBatchCountTest_201::GetCount(&b))
      << "Clear() should reset the operation count to 0.";
}

TEST_F(WriteBatchCountTest_201, Append_AddsSourceOpsToDestination_201) {
  WriteBatch dst;
  dst.Put(Slice("d1"), Slice("v1"));
  dst.Delete(Slice("d2"));  // dst has 2 ops

  WriteBatch src;
  src.Put(Slice("s1"), Slice("v1"));
  src.Put(Slice("s2"), Slice("v2"));
  src.Delete(Slice("s3"));  // src has 3 ops

  // Use the public interface to append; then observe via Count.
  dst.Append(src);

  EXPECT_EQ(5, WriteBatchCountTest_201::GetCount(&dst))
      << "After Append, destination's count should equal sum of both batches.";
  EXPECT_EQ(3, WriteBatchCountTest_201::GetCount(&src))
      << "Append should not modify the source batch's count.";
}

// --- Exceptional / edge observables (where exposed) ---

TEST_F(WriteBatchCountTest_201, Append_EmptySource_DoesNotChangeDestination_201) {
  WriteBatch dst;
  dst.Put(Slice("only"), Slice("once"));
  WriteBatch src;  // empty
  dst.Append(src);
  EXPECT_EQ(1, WriteBatchCountTest_201::GetCount(&dst))
      << "Appending an empty batch should not change the destination count.";
  EXPECT_EQ(0, WriteBatchCountTest_201::GetCount(&src))
      << "Empty source remains empty.";
}

