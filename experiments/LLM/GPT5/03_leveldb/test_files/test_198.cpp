// File: write_batch_clear_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

using ::testing::_;
using ::testing::StrictMock;
using ::testing::Exactly;

namespace leveldb {

// A mock Handler to observe Iterate() effects without peeking into internals.
class MockHandler : public WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));
  MOCK_METHOD(void, Delete, (const Slice& key), (override));
  ~MockHandler() override = default;
};

class WriteBatchTest_198 : public ::testing::Test {};

// [Behavior] Clear() on a fresh batch keeps the size at the initial baseline.
TEST_F(WriteBatchTest_198, ClearOnEmpty_KeepsInitialSize_198) {
  WriteBatch b;
  const size_t initial = b.ApproximateSize();

  // Sanity: initial should be stable across a no-op Clear().
  b.Clear();
  EXPECT_EQ(b.ApproximateSize(), initial);

  // Empty Iterate should produce no handler calls and OK status.
  StrictMock<MockHandler> h;
  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

// [Behavior] Clear() resets the size back to the initial baseline after writes.
TEST_F(WriteBatchTest_198, ClearResetsToInitialSizeAfterWrites_198) {
  WriteBatch b;
  const size_t initial = b.ApproximateSize();

  // Add some operations to increase size (observable via ApproximateSize()).
  b.Put(Slice("k1"), Slice("v1"));
  b.Put(Slice("k2"), Slice("v2"));
  b.Delete(Slice("k1"));

  const size_t grown = b.ApproximateSize();
  ASSERT_GT(grown, initial);

  // Clear should bring it back to the initial baseline.
  b.Clear();
  EXPECT_EQ(b.ApproximateSize(), initial);
}

// [Behavior] After Clear(), Iterate() should yield no callbacks.
TEST_F(WriteBatchTest_198, ClearMakesIterateNoOp_198) {
  WriteBatch b;
  b.Put(Slice("a"), Slice("1"));
  b.Delete(Slice("a"));

  b.Clear();

  StrictMock<MockHandler> h;
  // No Put/Delete should be invoked on an empty batch.
  EXPECT_CALL(h, Put(_, _)).Times(0);
  EXPECT_CALL(h, Delete(_)).Times(0);

  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

// [Behavior] Batch can be reused after Clear(): new ops are visible, old ones are gone.
TEST_F(WriteBatchTest_198, ReuseAfterClear_ShowsOnlyNewOps_198) {
  WriteBatch b;

  // Stage 1: add some entries, then clear them.
  b.Put(Slice("x"), Slice("1"));
  b.Put(Slice("y"), Slice("2"));
  b.Delete(Slice("x"));
  b.Clear();

  // Stage 2: add new entries and verify Iterate() only sees these.
  b.Put(Slice("z"), Slice("9"));
  b.Delete(Slice("y"));

  StrictMock<MockHandler> h;
  // Expect exactly the new operations in whatever order the public interface documents.
  // Since we must not assume internal ordering beyond what Iterate() guarantees,
  // we only assert that each expected callback occurs once.
  EXPECT_CALL(h, Put(Slice("z"), Slice("9"))).Times(Exactly(1));
  EXPECT_CALL(h, Delete(Slice("y"))).Times(Exactly(1));

  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
