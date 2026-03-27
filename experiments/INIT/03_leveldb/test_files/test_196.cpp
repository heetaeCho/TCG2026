// File: write_batch_internal_bytesize_test_196.cc

#include "gtest/gtest.h"

#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "leveldb/slice.h"

using leveldb::Slice;
using leveldb::WriteBatch;
using leveldb::WriteBatchInternal;

class WriteBatchInternalTest_196 : public ::testing::Test {
 protected:
  // Helper to make small slices without depending on std::string lifetime.
  static Slice S(const char* s) { return Slice(s); }
};

// 1) Baseline: empty batch has a well-defined (implementation-defined) size.
// We don't assert the exact value; only that it's a valid non-negative size.
TEST_F(WriteBatchInternalTest_196, EmptyBatchBaseline_196) {
  WriteBatch b;
  const size_t baseline = WriteBatchInternal::ByteSize(&b);
  // Just sanity: size_t is unsigned; check it's "reasonable" (no UB).
  EXPECT_GE(baseline, static_cast<size_t>(0));
}

// 2) Normal operation: Put increases the byte size relative to an empty batch.
TEST_F(WriteBatchInternalTest_196, PutIncreasesByteSize_196) {
  WriteBatch b;
  const size_t baseline = WriteBatchInternal::ByteSize(&b);

  b.Put(S("key"), S("value"));
  const size_t after_put = WriteBatchInternal::ByteSize(&b);

  EXPECT_GT(after_put, baseline);
}

// 3) Normal operation: Delete also increases the byte size relative to empty.
TEST_F(WriteBatchInternalTest_196, DeleteIncreasesByteSize_196) {
  WriteBatch b;
  const size_t baseline = WriteBatchInternal::ByteSize(&b);

  b.Delete(S("key"));
  const size_t after_delete = WriteBatchInternal::ByteSize(&b);

  EXPECT_GT(after_delete, baseline);
}

// 4) Boundary / state reset: Clear returns the batch to its baseline size.
TEST_F(WriteBatchInternalTest_196, ClearResetsToBaseline_196) {
  WriteBatch b;
  const size_t baseline = WriteBatchInternal::ByteSize(&b);

  b.Put(S("k1"), S("v1"));
  b.Put(S("k2"), S("v2"));
  ASSERT_GT(WriteBatchInternal::ByteSize(&b), baseline) << "Precondition";

  b.Clear();
  const size_t after_clear = WriteBatchInternal::ByteSize(&b);

  EXPECT_EQ(after_clear, baseline);
}

// 5) Append behavior:
//   - Appending a non-empty batch increases destination size.
//   - Appending an empty batch does not change the size.
TEST_F(WriteBatchInternalTest_196, AppendBehavior_196) {
  WriteBatch dst;
  dst.Put(S("a"), S("1"));
  const size_t before = WriteBatchInternal::ByteSize(&dst);

  WriteBatch src_non_empty;
  src_non_empty.Put(S("b"), S("2"));

  WriteBatchInternal::Append(&dst, &src_non_empty);
  const size_t after_non_empty = WriteBatchInternal::ByteSize(&dst);
  EXPECT_GT(after_non_empty, before);

  // Appending an empty batch should not change size.
  WriteBatch src_empty;
  const size_t before_empty_append = WriteBatchInternal::ByteSize(&dst);
  WriteBatchInternal::Append(&dst, &src_empty);
  const size_t after_empty_append = WriteBatchInternal::ByteSize(&dst);
  EXPECT_EQ(after_empty_append, before_empty_append);
}

// 6) Copy semantics: copy-constructed and copy-assigned batches preserve size.
TEST_F(WriteBatchInternalTest_196, CopySemanticsPreserveByteSize_196) {
  WriteBatch original;
  original.Put(S("x"), S("100"));
  original.Delete(S("y"));
  const size_t original_size = WriteBatchInternal::ByteSize(&original);

  // Copy constructor
  WriteBatch copy_constructed(original);
  EXPECT_EQ(WriteBatchInternal::ByteSize(&copy_constructed), original_size);

  // Copy assignment
  WriteBatch copy_assigned;
  copy_assigned = original;
  EXPECT_EQ(WriteBatchInternal::ByteSize(&copy_assigned), original_size);
}

// 7) Cross-check: ByteSize should equal Contents(...).size() if available.
TEST_F(WriteBatchInternalTest_196, ByteSizeMatchesContentsSize_196) {
  WriteBatch b;
  b.Put(S("k"), S("v"));
  b.Delete(S("k2"));

  const size_t byte_size = WriteBatchInternal::ByteSize(&b);
  const leveldb::Slice contents = WriteBatchInternal::Contents(&b);

  EXPECT_EQ(byte_size, contents.size());
}
