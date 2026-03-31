#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "db/write_batch_internal.h"
#include "db/dbformat.h"

#include <string>
#include <vector>

namespace leveldb {

// A simple handler to collect operations from Iterate
class TestHandler : public WriteBatch::Handler {
 public:
  void Put(const Slice& key, const Slice& value) override {
    ops_.push_back("PUT(" + key.ToString() + "," + value.ToString() + ")");
  }
  void Delete(const Slice& key) override {
    ops_.push_back("DELETE(" + key.ToString() + ")");
  }
  std::vector<std::string> ops_;
};

class WriteBatchTest_206 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// Test that a newly created WriteBatch has count 0
TEST_F(WriteBatchTest_206, EmptyBatchHasZeroCount_206) {
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that Put increases the count by 1
TEST_F(WriteBatchTest_206, PutIncreasesCount_206) {
  batch_.Put("key1", "value1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test that Delete increases the count by 1
TEST_F(WriteBatchTest_206, DeleteIncreasesCount_206) {
  batch_.Delete("key1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test that multiple Puts increase count correctly
TEST_F(WriteBatchTest_206, MultiplePutsIncreaseCount_206) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Put("key3", "value3");
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test that multiple Deletes increase count correctly
TEST_F(WriteBatchTest_206, MultipleDeletesIncreaseCount_206) {
  batch_.Delete("key1");
  batch_.Delete("key2");
  batch_.Delete("key3");
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test mixed Put and Delete operations
TEST_F(WriteBatchTest_206, MixedPutAndDeleteCount_206) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test that Clear resets the batch
TEST_F(WriteBatchTest_206, ClearResetsBatch_206) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Clear();
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that Iterate with a handler produces correct Put operations
TEST_F(WriteBatchTest_206, IterateProducesPutOperations_206) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("PUT(key2,value2)", handler.ops_[1]);
}

// Test that Iterate with a handler produces correct Delete operations
TEST_F(WriteBatchTest_206, IterateProducesDeleteOperations_206) {
  batch_.Delete("key1");
  batch_.Delete("key2");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.ops_.size());
  EXPECT_EQ("DELETE(key1)", handler.ops_[0]);
  EXPECT_EQ("DELETE(key2)", handler.ops_[1]);
}

// Test that Iterate with mixed operations preserves order
TEST_F(WriteBatchTest_206, IterateMixedOperationsPreservesOrder_206) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  batch_.Delete("key4");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(4u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("DELETE(key2)", handler.ops_[1]);
  EXPECT_EQ("PUT(key3,value3)", handler.ops_[2]);
  EXPECT_EQ("DELETE(key4)", handler.ops_[3]);
}

// Test Iterate on empty batch
TEST_F(WriteBatchTest_206, IterateOnEmptyBatch_206) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(0u, handler.ops_.size());
}

// Test ApproximateSize on empty batch
TEST_F(WriteBatchTest_206, ApproximateSizeEmpty_206) {
  size_t empty_size = batch_.ApproximateSize();
  // A new batch has a header (sequence number + count = 12 bytes)
  EXPECT_GT(empty_size, 0u);
}

// Test ApproximateSize increases after Put
TEST_F(WriteBatchTest_206, ApproximateSizeIncreasesAfterPut_206) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  size_t after_put_size = batch_.ApproximateSize();
  EXPECT_GT(after_put_size, initial_size);
}

// Test ApproximateSize increases after Delete
TEST_F(WriteBatchTest_206, ApproximateSizeIncreasesAfterDelete_206) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Delete("key1");
  size_t after_delete_size = batch_.ApproximateSize();
  EXPECT_GT(after_delete_size, initial_size);
}

// Test Append merges two batches
TEST_F(WriteBatchTest_206, AppendMergesBatches_206) {
  batch_.Put("key1", "value1");

  WriteBatch batch2;
  batch2.Delete("key2");
  batch2.Put("key3", "value3");

  batch_.Append(batch2);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("DELETE(key2)", handler.ops_[1]);
  EXPECT_EQ("PUT(key3,value3)", handler.ops_[2]);
}

// Test Append with empty source batch
TEST_F(WriteBatchTest_206, AppendEmptySourceBatch_206) {
  batch_.Put("key1", "value1");
  WriteBatch empty_batch;
  batch_.Append(empty_batch);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test Append to empty batch
TEST_F(WriteBatchTest_206, AppendToEmptyBatch_206) {
  WriteBatch source;
  source.Put("key1", "value1");
  batch_.Append(source);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
}

// Test that Delete works with an empty key
TEST_F(WriteBatchTest_206, DeleteEmptyKey_206) {
  batch_.Delete("");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("DELETE()", handler.ops_[0]);
}

// Test that Put works with empty key and value
TEST_F(WriteBatchTest_206, PutEmptyKeyAndValue_206) {
  batch_.Put("", "");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("PUT(,)", handler.ops_[0]);
}

// Test that Put works with large key and value
TEST_F(WriteBatchTest_206, PutLargeKeyAndValue_206) {
  std::string large_key(10000, 'k');
  std::string large_value(10000, 'v');
  batch_.Put(large_key, large_value);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("PUT(" + large_key + "," + large_value + ")", handler.ops_[0]);
}

// Test Delete with large key
TEST_F(WriteBatchTest_206, DeleteLargeKey_206) {
  std::string large_key(10000, 'k');
  batch_.Delete(large_key);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("DELETE(" + large_key + ")", handler.ops_[0]);
}

// Test copy constructor preserves operations
TEST_F(WriteBatchTest_206, CopyConstructorPreservesOperations_206) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");

  WriteBatch copy(batch_);
  EXPECT_EQ(2, WriteBatchInternal::Count(&copy));

  TestHandler handler;
  Status s = copy.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("DELETE(key2)", handler.ops_[1]);
}

// Test assignment operator preserves operations
TEST_F(WriteBatchTest_206, AssignmentOperatorPreservesOperations_206) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");

  WriteBatch assigned;
  assigned = batch_;
  EXPECT_EQ(2, WriteBatchInternal::Count(&assigned));

  TestHandler handler;
  Status s = assigned.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("DELETE(key2)", handler.ops_[1]);
}

// Test SetSequence and Sequence
TEST_F(WriteBatchTest_206, SetAndGetSequence_206) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  EXPECT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

// Test that Clear resets approximate size
TEST_F(WriteBatchTest_206, ClearResetsApproximateSize_206) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Clear();
  EXPECT_EQ(empty_size, batch_.ApproximateSize());
}

// Test many operations
TEST_F(WriteBatchTest_206, ManyOperations_206) {
  const int kNumOps = 1000;
  for (int i = 0; i < kNumOps; i++) {
    if (i % 2 == 0) {
      batch_.Put("key" + std::to_string(i), "val" + std::to_string(i));
    } else {
      batch_.Delete("key" + std::to_string(i));
    }
  }
  EXPECT_EQ(kNumOps, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(static_cast<size_t>(kNumOps), handler.ops_.size());
}

// Test that ByteSize returns the internal rep size
TEST_F(WriteBatchTest_206, ByteSizeMatchesRepSize_206) {
  size_t initial_byte_size = WriteBatchInternal::ByteSize(&batch_);
  batch_.Put("key", "value");
  size_t after_put_byte_size = WriteBatchInternal::ByteSize(&batch_);
  EXPECT_GT(after_put_byte_size, initial_byte_size);
}

// Test Append with both batches non-empty
TEST_F(WriteBatchTest_206, AppendBothNonEmpty_206) {
  batch_.Put("a", "1");
  batch_.Put("b", "2");

  WriteBatch other;
  other.Put("c", "3");
  other.Delete("d");

  batch_.Append(other);
  EXPECT_EQ(4, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(4u, handler.ops_.size());
  EXPECT_EQ("PUT(a,1)", handler.ops_[0]);
  EXPECT_EQ("PUT(b,2)", handler.ops_[1]);
  EXPECT_EQ("PUT(c,3)", handler.ops_[2]);
  EXPECT_EQ("DELETE(d)", handler.ops_[3]);
}

// Test that Delete followed by Put on the same key records both
TEST_F(WriteBatchTest_206, DeleteThenPutSameKey_206) {
  batch_.Delete("key1");
  batch_.Put("key1", "new_value");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.ops_.size());
  EXPECT_EQ("DELETE(key1)", handler.ops_[0]);
  EXPECT_EQ("PUT(key1,new_value)", handler.ops_[1]);
}

// Test that Put followed by Delete on the same key records both
TEST_F(WriteBatchTest_206, PutThenDeleteSameKey_206) {
  batch_.Put("key1", "value1");
  batch_.Delete("key1");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("DELETE(key1)", handler.ops_[1]);
}

// Test that Contents returns a non-empty slice even for empty batch (header exists)
TEST_F(WriteBatchTest_206, ContentsNonEmptyForNewBatch_206) {
  Slice contents = WriteBatchInternal::Contents(&batch_);
  EXPECT_GT(contents.size(), 0u);
}

}  // namespace leveldb
