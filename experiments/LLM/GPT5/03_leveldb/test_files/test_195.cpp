// write_batch_internal_contents_test_195.cc
#include "db/write_batch_internal.h"
#include "leveldb/write_batch.h"

#include <gtest/gtest.h>
#include <cstring>  // for std::memcmp

using leveldb::Slice;
using leveldb::Status;
using leveldb::WriteBatch;
using leveldb::WriteBatchInternal;

namespace {

// Helper: clone a batch using Contents/SetContents and return the clone.
static WriteBatch CloneViaContents(const WriteBatch& src) {
  Slice contents = WriteBatchInternal::Contents(&src);
  WriteBatch clone;
  WriteBatchInternal::SetContents(&clone, contents);
  return clone;
}

// Helper: byte-wise equality of Contents between two batches.
static void ExpectContentsEqual(const WriteBatch& a, const WriteBatch& b) {
  Slice ca = WriteBatchInternal::Contents(&a);
  Slice cb = WriteBatchInternal::Contents(&b);
  ASSERT_EQ(ca.size(), cb.size());
  ASSERT_EQ(0, std::memcmp(ca.data(), cb.data(), ca.size()));
}

}  // namespace

// Baseline: empty batch round-trips through Contents/SetContents unchanged.
TEST(WriteBatchInternalContentsTest_195, EmptyRoundTrip_195) {
  WriteBatch empty;

  // Clone via Contents -> SetContents.
  WriteBatch cloned = CloneViaContents(empty);

  // Exact byte-for-byte equality of the serialized representation.
  ExpectContentsEqual(empty, cloned);
}

// Normal operation: Put/Delete in a batch survive a Contents-based clone.
TEST(WriteBatchInternalContentsTest_195, NonEmptyRoundTrip_PutDelete_195) {
  WriteBatch b;
  std::string k1 = "k1", v1 = "v1";
  std::string k2 = "k2";
  b.Put(Slice(k1), Slice(v1));
  b.Delete(Slice(k2));

  WriteBatch cloned = CloneViaContents(b);

  // The serialized representation should be identical.
  ExpectContentsEqual(b, cloned);
}

// Boundary-ish case: empty keys/values should also round-trip.
TEST(WriteBatchInternalContentsTest_195, EmptyKeyValueRoundTrip_195) {
  WriteBatch b;
  std::string empty;
  b.Put(Slice(empty), Slice(empty));
  b.Delete(Slice(empty));

  WriteBatch cloned = CloneViaContents(b);
  ExpectContentsEqual(b, cloned);
}

// Clear(): Contents should revert to the same serialized form as a fresh batch.
TEST(WriteBatchInternalContentsTest_195, ClearResetsContents_195) {
  WriteBatch baseline_empty;
  WriteBatch b;

  // Make b non-empty first.
  std::string k = "k", v = "v";
  b.Put(Slice(k), Slice(v));
  ASSERT_NE(WriteBatchInternal::Contents(&baseline_empty).size(),
            WriteBatchInternal::Contents(&b).size());

  // After Clear, serialized form should match a fresh empty batch.
  b.Clear();
  ExpectContentsEqual(baseline_empty, b);
}

// Append(): destination Contents size should grow; clone still equals itself.
TEST(WriteBatchInternalContentsTest_195, AppendIncreasesSize_195) {
  WriteBatch dst;
  WriteBatch src;

  std::string k1 = "a", v1 = "1";
  std::string k2 = "b", v2 = "2";
  dst.Put(Slice(k1), Slice(v1));
  src.Put(Slice(k2), Slice(v2));
  src.Delete(Slice(k1));  // mix of ops in the source

  size_t before = WriteBatchInternal::Contents(&dst).size();

  // Append src into dst via the provided API.
  WriteBatchInternal::Append(&dst, &src);

  size_t after = WriteBatchInternal::Contents(&dst).size();
  EXPECT_GT(after, before);

  // A clone via SetContents must exactly match dst's serialized form.
  WriteBatch cloned = CloneViaContents(dst);
  ExpectContentsEqual(dst, cloned);
}

// Consistency: Contents size should match ByteSize for various states.
TEST(WriteBatchInternalContentsTest_195, ContentsSizeMatchesByteSize_195) {
  WriteBatch b;
  auto expect_match = [&](const WriteBatch& wb) {
    Slice s = WriteBatchInternal::Contents(&wb);
    size_t byte_size = WriteBatchInternal::ByteSize(&wb);
    EXPECT_EQ(s.size(), byte_size);
  };

  // Empty
  expect_match(b);

  // After some operations
  std::string k = "key", v = "value";
  b.Put(Slice(k), Slice(v));
  expect_match(b);

  b.Delete(Slice(k));
  expect_match(b);

  // After Clear
  b.Clear();
  expect_match(b);
}
