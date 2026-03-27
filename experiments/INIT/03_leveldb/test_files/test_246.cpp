// File: db/c_clear_test_246.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Match the C linkage used by LevelDB's C wrapper.
extern "C" {
  // Forward declarations from db/c.cc (partial code provided)
  struct leveldb_writebatch_t { leveldb::WriteBatch rep; };
  void leveldb_writebatch_clear(leveldb_writebatch_t* b);
}

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Exactly;
using ::testing::Times;

namespace {

// A mock Handler to observe external interactions during Iterate.
class MockHandler : public leveldb::WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put,
              (const leveldb::Slice& key, const leveldb::Slice& value),
              (override));
  MOCK_METHOD(void, Delete, (const leveldb::Slice& key), (override));
};

struct WriteBatchClearTest_246 : public ::testing::Test {
  leveldb_writebatch_t b{};  // Construct with default-inited WriteBatch
};

}  // namespace

// Normal operation: clear removes all recorded operations (no handler calls).
TEST_F(WriteBatchClearTest_246, Clear_EmptiesBatch_246) {
  // Arrange: add a few operations using only public WriteBatch API.
  b.rep.Put(leveldb::Slice("k1"), leveldb::Slice("v1"));
  b.rep.Put(leveldb::Slice("k2"), leveldb::Slice("v2"));
  b.rep.Delete(leveldb::Slice("k3"));

  // Act: clear via the C API wrapper.
  leveldb_writebatch_clear(&b);

  // Assert: iterating invokes no Put/Delete on the handler.
  StrictMock<MockHandler> h;
  EXPECT_CALL(h, Put(_, _)).Times(0);
  EXPECT_CALL(h, Delete(_)).Times(0);
  leveldb::Status s = b.rep.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

// Boundary: clearing an already empty batch is a no-op and remains iterable.
TEST_F(WriteBatchClearTest_246, Clear_IdempotentOnEmpty_246) {
  // Batch starts empty; call clear twice.
  leveldb_writebatch_clear(&b);
  leveldb_writebatch_clear(&b);

  // No operations should be observed.
  StrictMock<MockHandler> h;
  EXPECT_CALL(h, Put(_, _)).Times(0);
  EXPECT_CALL(h, Delete(_)).Times(0);
  leveldb::Status s = b.rep.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

// Post-condition & reuse: after clear, new operations can be added and observed.
TEST_F(WriteBatchClearTest_246, Clear_AllowsReuse_246) {
  // Arrange: add and then clear.
  b.rep.Put(leveldb::Slice("a"), leveldb::Slice("1"));
  b.rep.Delete(leveldb::Slice("b"));
  leveldb_writebatch_clear(&b);

  // Reuse the batch with fresh ops.
  b.rep.Put(leveldb::Slice("x"), leveldb::Slice("y"));

  // Expect exactly one Put, no Delete.
  StrictMock<MockHandler> h;
  EXPECT_CALL(h, Put(_, _)).Times(Exactly(1));
  EXPECT_CALL(h, Delete(_)).Times(0);
  leveldb::Status s = b.rep.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

// Observable size behavior: ApproximateSize should not increase after clear.
TEST_F(WriteBatchClearTest_246, ApproximateSize_NonIncreasingAfterClear_246) {
  // Arrange: make the batch non-empty.
  b.rep.Put(leveldb::Slice("k"), leveldb::Slice("v"));
  b.rep.Put(leveldb::Slice("k2"), leveldb::Slice("v2"));

  const size_t size_before = b.rep.ApproximateSize();

  // Act: clear via the C API.
  leveldb_writebatch_clear(&b);

  const size_t size_after = b.rep.ApproximateSize();

  // Assert: clearing should not increase the reported size.
  EXPECT_LE(size_after, size_before);

  // And the cleared batch should iterate with no calls.
  StrictMock<MockHandler> h;
  EXPECT_CALL(h, Put(_, _)).Times(0);
  EXPECT_CALL(h, Delete(_)).Times(0);
  leveldb::Status s = b.rep.Iterate(&h);
  EXPECT_TRUE(s.ok());
}
