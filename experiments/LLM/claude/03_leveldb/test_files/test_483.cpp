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

class WriteBatchTest_483 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// Test that a newly constructed WriteBatch has a small approximate size (header only)
TEST_F(WriteBatchTest_483, DefaultConstructorApproximateSize_483) {
  // A fresh WriteBatch should have a small size (just the header)
  size_t initial_size = batch_.ApproximateSize();
  EXPECT_GT(initial_size, 0u);
}

// Test that Clear resets the batch
TEST_F(WriteBatchTest_483, ClearResetsBatch_483) {
  batch_.Put("key1", "value1");
  size_t size_after_put = batch_.ApproximateSize();
  batch_.Clear();
  size_t size_after_clear = batch_.ApproximateSize();
  EXPECT_LT(size_after_clear, size_after_put);
}

// Test that Put increases approximate size
TEST_F(WriteBatchTest_483, PutIncreasesSize_483) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Put("key", "value");
  EXPECT_GT(batch_.ApproximateSize(), initial_size);
}

// Test that Delete increases approximate size
TEST_F(WriteBatchTest_483, DeleteIncreasesSize_483) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Delete("key");
  EXPECT_GT(batch_.ApproximateSize(), initial_size);
}

// Test Iterate with a single Put
TEST_F(WriteBatchTest_483, IterateSinglePut_483) {
  batch_.Put("hello", "world");
  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("hello"), Slice("world"))).Times(1);
  EXPECT_CALL(handler, Delete(::testing::_)).Times(0);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Iterate with a single Delete
TEST_F(WriteBatchTest_483, IterateSingleDelete_483) {
  batch_.Delete("hello");
  MockHandler handler;
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);
  EXPECT_CALL(handler, Delete(Slice("hello"))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Iterate with multiple operations
TEST_F(WriteBatchTest_483, IterateMultipleOperations_483) {
  batch_.Put("key1", "val1");
  batch_.Delete("key2");
  batch_.Put("key3", "val3");

  MockHandler handler;
  {
    ::testing::InSequence seq;
    EXPECT_CALL(handler, Put(Slice("key1"), Slice("val1"))).Times(1);
    EXPECT_CALL(handler, Delete(Slice("key2"))).Times(1);
    EXPECT_CALL(handler, Put(Slice("key3"), Slice("val3"))).Times(1);
  }
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Iterate on empty batch
TEST_F(WriteBatchTest_483, IterateEmptyBatch_483) {
  MockHandler handler;
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);
  EXPECT_CALL(handler, Delete(::testing::_)).Times(0);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test copy constructor
TEST_F(WriteBatchTest_483, CopyConstructor_483) {
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

// Test copy assignment operator
TEST_F(WriteBatchTest_483, CopyAssignment_483) {
  batch_.Put("key1", "value1");

  WriteBatch other;
  other = batch_;

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("key1"), Slice("value1"))).Times(1);
  Status s = other.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Append combines two batches
TEST_F(WriteBatchTest_483, AppendCombinesBatches_483) {
  batch_.Put("key1", "val1");

  WriteBatch other;
  other.Put("key2", "val2");
  other.Delete("key3");

  batch_.Append(other);

  MockHandler handler;
  {
    ::testing::InSequence seq;
    EXPECT_CALL(handler, Put(Slice("key1"), Slice("val1"))).Times(1);
    EXPECT_CALL(handler, Put(Slice("key2"), Slice("val2"))).Times(1);
    EXPECT_CALL(handler, Delete(Slice("key3"))).Times(1);
  }
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Append with empty source
TEST_F(WriteBatchTest_483, AppendEmptySource_483) {
  batch_.Put("key1", "val1");
  size_t size_before = batch_.ApproximateSize();

  WriteBatch empty;
  batch_.Append(empty);

  // Should still have the original operation
  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("key1"), Slice("val1"))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Append to empty batch
TEST_F(WriteBatchTest_483, AppendToEmptyBatch_483) {
  WriteBatch source;
  source.Put("key1", "val1");

  batch_.Append(source);

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("key1"), Slice("val1"))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Put with empty key and value
TEST_F(WriteBatchTest_483, PutEmptyKeyAndValue_483) {
  batch_.Put("", "");

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice(""), Slice(""))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Delete with empty key
TEST_F(WriteBatchTest_483, DeleteEmptyKey_483) {
  batch_.Delete("");

  MockHandler handler;
  EXPECT_CALL(handler, Delete(Slice(""))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Put with large key and value
TEST_F(WriteBatchTest_483, PutLargeKeyAndValue_483) {
  std::string large_key(10000, 'k');
  std::string large_value(100000, 'v');
  batch_.Put(large_key, large_value);

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice(large_key), Slice(large_value))).Times(1);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test ApproximateSize grows with multiple puts
TEST_F(WriteBatchTest_483, ApproximateSizeGrowsWithMultiplePuts_483) {
  size_t prev_size = batch_.ApproximateSize();
  for (int i = 0; i < 10; i++) {
    batch_.Put("key" + std::to_string(i), "value" + std::to_string(i));
    size_t current_size = batch_.ApproximateSize();
    EXPECT_GT(current_size, prev_size);
    prev_size = current_size;
  }
}

// Test Clear after multiple operations
TEST_F(WriteBatchTest_483, ClearAfterMultipleOperations_483) {
  batch_.Put("k1", "v1");
  batch_.Put("k2", "v2");
  batch_.Delete("k3");
  batch_.Clear();

  MockHandler handler;
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);
  EXPECT_CALL(handler, Delete(::testing::_)).Times(0);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test multiple clears
TEST_F(WriteBatchTest_483, MultipleClearsAreIdempotent_483) {
  batch_.Put("key", "val");
  batch_.Clear();
  batch_.Clear();
  batch_.Clear();

  size_t size = batch_.ApproximateSize();
  WriteBatch fresh;
  EXPECT_EQ(size, fresh.ApproximateSize());
}

// Test reuse after clear
TEST_F(WriteBatchTest_483, ReuseAfterClear_483) {
  batch_.Put("old_key", "old_val");
  batch_.Clear();
  batch_.Put("new_key", "new_val");

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("new_key"), Slice("new_val"))).Times(1);
  EXPECT_CALL(handler, Put(Slice("old_key"), Slice("old_val"))).Times(0);
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test that Append does not modify the source
TEST_F(WriteBatchTest_483, AppendDoesNotModifySource_483) {
  WriteBatch source;
  source.Put("src_key", "src_val");
  size_t source_size_before = source.ApproximateSize();

  batch_.Append(source);

  EXPECT_EQ(source.ApproximateSize(), source_size_before);

  MockHandler handler;
  EXPECT_CALL(handler, Put(Slice("src_key"), Slice("src_val"))).Times(1);
  Status s = source.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
