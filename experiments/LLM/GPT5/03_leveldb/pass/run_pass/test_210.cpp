// File: write_batch_append_test_210.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/write_batch.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

using ::testing::InSequence;
using ::testing::StrictMock;

namespace leveldb {

// Minimal mock of WriteBatch::Handler to verify observable interactions.
class MockHandler : public WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));
  MOCK_METHOD(void, Delete, (const Slice& key), (override));
};

// Helper to add a few ops without asserting on internal details.
static void FillBatch(WriteBatch* b,
                      std::initializer_list<std::pair<std::string, std::string>> puts,
                      std::initializer_list<std::string> deletes = {}) {
  for (const auto& kv : puts) {
    b->Put(Slice(kv.first), Slice(kv.second));
  }
  for (const auto& k : deletes) {
    b->Delete(Slice(k));
  }
}

class WriteBatchAppendTest_210 : public ::testing::Test {};

TEST_F(WriteBatchAppendTest_210, Append_NonEmptyToNonEmpty_PreservesOrder_210) {
  WriteBatch dst;
  WriteBatch src;

  FillBatch(&dst, {{"k1","v1"}}, {"k2"});
  FillBatch(&src, {{"k3","v3"}, {"k4","v4"}});

  // Act
  dst.Append(src);

  // Assert order: all dst ops, then all src ops, in-sequence.
  StrictMock<MockHandler> h;
  {
    InSequence seq;
    EXPECT_CALL(h, Put(Slice("k1"), Slice("v1")));
    EXPECT_CALL(h, Delete(Slice("k2")));
    EXPECT_CALL(h, Put(Slice("k3"), Slice("v3")));
    EXPECT_CALL(h, Put(Slice("k4"), Slice("v4")));
  }
  Status s = dst.Iterate(&h);
  ASSERT_TRUE(s.ok());
}

TEST_F(WriteBatchAppendTest_210, Append_EmptySrc_NoChange_210) {
  WriteBatch dst;
  WriteBatch src;  // empty

  FillBatch(&dst, {{"a","1"}}, {"b"});

  // Snapshot observable size before (best-effort, monotonic expectation).
  const size_t before = dst.ApproximateSize();

  // Act
  dst.Append(src);

  // Assert: sequence unchanged
  StrictMock<MockHandler> h;
  {
    InSequence seq;
    EXPECT_CALL(h, Put(Slice("a"), Slice("1")));
    EXPECT_CALL(h, Delete(Slice("b")));
  }
  Status s = dst.Iterate(&h);
  ASSERT_TRUE(s.ok());

  // And size should not shrink.
  const size_t after = dst.ApproximateSize();
  EXPECT_GE(after, before);
}

TEST_F(WriteBatchAppendTest_210, Append_ToEmpty_CopiesAll_210) {
  WriteBatch dst;  // empty
  WriteBatch src;

  FillBatch(&src, {{"x","X"}, {"y","Y"}}, {"z"});

  // Act
  dst.Append(src);

  // Assert: dst now yields exactly src's operations, in order
  StrictMock<MockHandler> h;
  {
    InSequence seq;
    EXPECT_CALL(h, Put(Slice("x"), Slice("X")));
    EXPECT_CALL(h, Put(Slice("y"), Slice("Y")));
    EXPECT_CALL(h, Delete(Slice("z")));
  }
  Status s = dst.Iterate(&h);
  ASSERT_TRUE(s.ok());
}

TEST_F(WriteBatchAppendTest_210, Append_EmptyToEmpty_YieldsNoOps_210) {
  WriteBatch dst;
  WriteBatch src;

  // Act
  dst.Append(src);

  // Assert: Iterate should succeed and invoke no callbacks.
  StrictMock<MockHandler> h;
  // No EXPECT_CALLs: any unexpected call would fail the test.
  Status s = dst.Iterate(&h);
  ASSERT_TRUE(s.ok());
}

TEST_F(WriteBatchAppendTest_210, Append_IncreasesApproximateSize_WhenAddingOps_210) {
  WriteBatch dst;
  WriteBatch src;

  FillBatch(&dst, {{"p","1"}});
  const size_t before = dst.ApproximateSize();

  FillBatch(&src, {{"q","2"}, {"r","3"}});

  // Act
  dst.Append(src);

  // Assert: size should grow (monotonic check; we don't assert exact bytes)
  const size_t after = dst.ApproximateSize();
  EXPECT_GT(after, before);

  // And all operations are present and in order.
  StrictMock<MockHandler> h;
  {
    InSequence seq;
    EXPECT_CALL(h, Put(Slice("p"), Slice("1")));
    EXPECT_CALL(h, Put(Slice("q"), Slice("2")));
    EXPECT_CALL(h, Put(Slice("r"), Slice("3")));
  }
  Status s = dst.Iterate(&h);
  ASSERT_TRUE(s.ok());
}

}  // namespace leveldb
