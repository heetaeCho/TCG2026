// File: write_batch_approx_size_test.cc

#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>

using leveldb::Slice;
using leveldb::WriteBatch;

class WriteBatchTest_199 : public ::testing::Test {
protected:
  static std::string Repeated(char ch, size_t n) {
    return std::string(n, ch);
  }
};

// --- Normal operation ---

TEST_F(WriteBatchTest_199, EmptyBatchHasNonNegativeSize_199) {
  WriteBatch wb;
  size_t size = wb.ApproximateSize();
  // Non-negative and stable across multiple queries
  EXPECT_GE(size, 0u);
  EXPECT_EQ(size, wb.ApproximateSize());
}

TEST_F(WriteBatchTest_199, PutIncreasesSize_199) {
  WriteBatch wb;
  const size_t before = wb.ApproximateSize();
  wb.Put(Slice("k1"), Slice("v1"));
  const size_t after = wb.ApproximateSize();

  // Adding a record should not reduce the size
  EXPECT_GE(after, before);
  // A second put should not reduce the size either (monotonic)
  wb.Put(Slice("k2"), Slice("v2"));
  EXPECT_GE(wb.ApproximateSize(), after);
}

TEST_F(WriteBatchTest_199, DeleteIncreasesSizeOrAtLeastNotSmaller_199) {
  WriteBatch wb;
  const size_t before = wb.ApproximateSize();
  wb.Delete(Slice("gone"));
  const size_t after = wb.ApproximateSize();

  // Deletions are encoded as records too; size should not go down
  EXPECT_GE(after, before);
}

// --- Boundary conditions ---

TEST_F(WriteBatchTest_199, PutEmptyKeyAndValueStillAffectsSize_199) {
  WriteBatch wb;
  const size_t before = wb.ApproximateSize();
  wb.Put(Slice(""), Slice(""));
  const size_t after = wb.ApproximateSize();

  // Even empty key/value should be represented (e.g., headers), so size should not decrease.
  EXPECT_GE(after, before);
}

TEST_F(WriteBatchTest_199, SizeReflectsPayloadLengths_199) {
  WriteBatch small;
  small.Put(Slice("k"), Slice("v"));

  WriteBatch large;
  // Same number of operations, but much larger payload
  std::string bigKey = Repeated('k', 1024);
  std::string bigVal = Repeated('v', 4096);
  large.Put(Slice(bigKey), Slice(bigVal));

  // Larger payload should lead to a larger (or at least not smaller) approximate size
  EXPECT_GT(large.ApproximateSize(), small.ApproximateSize());
}

// --- Exceptional / reset-like behavior via public API ---

TEST_F(WriteBatchTest_199, ClearReducesSizeToAtMostInitial_199) {
  WriteBatch wb;
  const size_t initial = wb.ApproximateSize();

  wb.Put(Slice("k1"), Slice("v1"));
  wb.Put(Slice("k2"), Slice("v2"));
  ASSERT_GE(wb.ApproximateSize(), initial);

  wb.Clear();
  const size_t cleared = wb.ApproximateSize();

  // After Clear(), size should not exceed the initial empty-batch size.
  EXPECT_LE(cleared, initial);

  // Adding again after Clear() should grow (or stay non-decreasing)
  wb.Put(Slice("k3"), Slice("v3"));
  EXPECT_GE(wb.ApproximateSize(), cleared);
}

// --- External interactions through other public methods ---

TEST_F(WriteBatchTest_199, AppendIncreasesOrMaintainsSize_199) {
  WriteBatch dst;
  dst.Put(Slice("a"), Slice("1"));
  const size_t dst_before = dst.ApproximateSize();

  WriteBatch src;
  src.Put(Slice("b"), Slice("2"));
  src.Put(Slice("c"), Slice("3"));
  const size_t src_size = src.ApproximateSize();

  dst.Append(src);
  const size_t dst_after = dst.ApproximateSize();

  // Appending should not reduce size; result should be at least as large
  // as either participant individually (not asserting exact sum).
  EXPECT_GE(dst_after, dst_before);
  EXPECT_GE(dst_after, src_size);
}

TEST_F(WriteBatchTest_199, CopyConstructKeepsApproxSize_199) {
  WriteBatch original;
  original.Put(Slice("x"), Slice("y"));
  const size_t original_size = original.ApproximateSize();

  WriteBatch copy = original;  // copy-construct
  EXPECT_EQ(copy.ApproximateSize(), original_size);

  // Modifying the copy should not imply anything about original size,
  // but both should remain individually non-decreasing.
  const size_t copy_before = copy.ApproximateSize();
  copy.Put(Slice("x2"), Slice("y2"));
  EXPECT_GE(copy.ApproximateSize(), copy_before);
  EXPECT_EQ(original.ApproximateSize(), original_size);
}

