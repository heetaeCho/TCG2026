#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/write_batch.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

namespace leveldb {

// Mock Handler for testing Iterate
class MockHandler : public WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));
  MOCK_METHOD(void, Delete, (const Slice& key), (override));
};

class WriteBatchTest_198 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

TEST_F(WriteBatchTest_198, DefaultConstructorCreatesEmptyBatch_198) {
  // A newly constructed WriteBatch should have a small approximate size (header only)
  EXPECT_GT(batch_.ApproximateSize(), 0u);
}

TEST_F(WriteBatchTest_198, ClearResetsToEmpty_198) {
  batch_.Put("key1", "value1");
  size_t size_after_put = batch_.ApproximateSize();
  batch_.Clear();
  size_t size_after_clear = batch_.ApproximateSize();
  EXPECT_LT(size_after_clear, size_after_put);
}

TEST_F(WriteBatchTest_198, PutIncreasesApproximateSize_198) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Put("key", "value");
  EXPECT_GT(batch_.ApproximateSize(), initial_size);
}

TEST_F(WriteBatchTest_198, DeleteIncreasesApproximateSize_198) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Delete("key");
  EXPECT_GT(batch_.ApproximateSize(), initial_size);
}

TEST_F(WriteBatchTest_198, IterateOnEmptyBatch_198) {
  MockHandler handler;
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);
  EXPECT_CALL(handler, Delete(::testing::_)).Times(0);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, IterateWithSinglePut_198) {
  batch_.Put("key1", "value1");
  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("key1"), Slice("value1"))).Times(1);
  EXPECT_CALL(handler, Delete(::testing::_)).Times(0);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, IterateWithSingleDelete_198) {
  batch_.Delete("key1");
  MockHandler handler;
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);
  EXPECT_CALL(handler, Delete(Slice("key1"))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, IterateWithMultipleOperations_198) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Delete("key3");
  batch_.Put("key4", "value4");

  MockHandler handler;
  {
    ::testing::InSequence seq;
    EXPECT_CALL(handler, Put(Slice("key1"), Slice("value1"))).Times(1);
    EXPECT_CALL(handler, Put(Slice("key2"), Slice("value2"))).Times(1);
    EXPECT_CALL(handler, Delete(Slice("key3"))).Times(1);
    EXPECT_CALL(handler, Put(Slice("key4"), Slice("value4"))).Times(1);
  }
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, ClearThenIterate_198) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Clear();

  MockHandler handler;
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);
  EXPECT_CALL(handler, Delete(::testing::_)).Times(0);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, ApproximateSizeAfterClear_198) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key", "value");
  batch_.Clear();
  EXPECT_EQ(batch_.ApproximateSize(), empty_size);
}

TEST_F(WriteBatchTest_198, AppendCombinesBatches_198) {
  WriteBatch batch2;
  batch_.Put("key1", "value1");
  batch2.Put("key2", "value2");
  batch2.Delete("key3");

  batch_.Append(batch2);

  MockHandler handler;
  {
    ::testing::InSequence seq;
    EXPECT_CALL(handler, Put(Slice("key1"), Slice("value1"))).Times(1);
    EXPECT_CALL(handler, Put(Slice("key2"), Slice("value2"))).Times(1);
    EXPECT_CALL(handler, Delete(Slice("key3"))).Times(1);
  }
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, AppendEmptyBatch_198) {
  batch_.Put("key1", "value1");
  WriteBatch empty_batch;
  size_t size_before = batch_.ApproximateSize();
  batch_.Append(empty_batch);
  // Appending an empty batch should not significantly change the size
  // (at most it should remain the same or very close)
  EXPECT_GE(batch_.ApproximateSize(), size_before);
}

TEST_F(WriteBatchTest_198, AppendToEmptyBatch_198) {
  WriteBatch batch2;
  batch2.Put("key1", "value1");
  batch_.Append(batch2);

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("key1"), Slice("value1"))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, CopyConstructor_198) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");

  WriteBatch copy(batch_);

  MockHandler handler;
  {
    ::testing::InSequence seq;
    EXPECT_CALL(handler, Put(Slice("key1"), Slice("value1"))).Times(1);
    EXPECT_CALL(handler, Delete(Slice("key2"))).Times(1);
  }
  Status s = copy.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, AssignmentOperator_198) {
  batch_.Put("key1", "value1");
  WriteBatch other;
  other = batch_;

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("key1"), Slice("value1"))).Times(1);
  Status s = other.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, PutEmptyKeyAndValue_198) {
  batch_.Put("", "");
  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice(""), Slice(""))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, DeleteEmptyKey_198) {
  batch_.Delete("");
  MockHandler handler;
  EXPECT_CALL(handler, Delete(Slice(""))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, PutLargeKeyAndValue_198) {
  std::string large_key(10000, 'k');
  std::string large_value(100000, 'v');
  batch_.Put(large_key, large_value);

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice(large_key), Slice(large_value))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, MultiplePutsToSameKey_198) {
  batch_.Put("key", "value1");
  batch_.Put("key", "value2");
  batch_.Put("key", "value3");

  MockHandler handler;
  {
    ::testing::InSequence seq;
    EXPECT_CALL(handler, Put(Slice("key"), Slice("value1"))).Times(1);
    EXPECT_CALL(handler, Put(Slice("key"), Slice("value2"))).Times(1);
    EXPECT_CALL(handler, Put(Slice("key"), Slice("value3"))).Times(1);
  }
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, ApproximateSizeGrowsWithOperations_198) {
  size_t s0 = batch_.ApproximateSize();
  batch_.Put("k1", "v1");
  size_t s1 = batch_.ApproximateSize();
  batch_.Put("k2", "v2");
  size_t s2 = batch_.ApproximateSize();
  batch_.Delete("k3");
  size_t s3 = batch_.ApproximateSize();

  EXPECT_LT(s0, s1);
  EXPECT_LT(s1, s2);
  EXPECT_LT(s2, s3);
}

TEST_F(WriteBatchTest_198, ClearAndReuse_198) {
  batch_.Put("key1", "value1");
  batch_.Clear();
  batch_.Put("key2", "value2");

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("key2"), Slice("value2"))).Times(1);
  EXPECT_CALL(handler, Put(Slice("key1"), ::testing::_)).Times(0);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

TEST_F(WriteBatchTest_198, AppendSelfDoublesEntries_198) {
  batch_.Put("key1", "value1");
  batch_.Append(batch_);

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("key1"), Slice("value1"))).Times(2);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
