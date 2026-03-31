#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "db/write_batch_internal.h"

namespace leveldb {

// A simple handler to collect operations from Iterate
class TestHandler : public WriteBatch::Handler {
 public:
  void Put(const Slice& key, const Slice& value) override {
    puts_.emplace_back(key.ToString(), value.ToString());
  }
  void Delete(const Slice& key) override {
    deletes_.push_back(key.ToString());
  }

  std::vector<std::pair<std::string, std::string>> puts_;
  std::vector<std::string> deletes_;
};

class WriteBatchTest_205 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// Test that a newly created WriteBatch has zero count
TEST_F(WriteBatchTest_205, EmptyBatchHasZeroCount_205) {
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that Put increases the count by 1
TEST_F(WriteBatchTest_205, PutIncreasesCount_205) {
  batch_.Put("key1", "value1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test that multiple Puts increase count accordingly
TEST_F(WriteBatchTest_205, MultiplePutsIncreaseCount_205) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Put("key3", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test that Put followed by Iterate produces the correct key-value pair
TEST_F(WriteBatchTest_205, PutIterateProducesCorrectKeyValue_205) {
  batch_.Put("hello", "world");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("hello", handler.puts_[0].first);
  ASSERT_EQ("world", handler.puts_[0].second);
  ASSERT_EQ(0u, handler.deletes_.size());
}

// Test multiple Puts iterated in order
TEST_F(WriteBatchTest_205, MultiplePutsIterateInOrder_205) {
  batch_.Put("a", "1");
  batch_.Put("b", "2");
  batch_.Put("c", "3");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.puts_.size());
  ASSERT_EQ("a", handler.puts_[0].first);
  ASSERT_EQ("1", handler.puts_[0].second);
  ASSERT_EQ("b", handler.puts_[1].first);
  ASSERT_EQ("2", handler.puts_[1].second);
  ASSERT_EQ("c", handler.puts_[2].first);
  ASSERT_EQ("3", handler.puts_[2].second);
}

// Test that Put with empty key and value works
TEST_F(WriteBatchTest_205, PutEmptyKeyAndValue_205) {
  batch_.Put("", "");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("", handler.puts_[0].first);
  ASSERT_EQ("", handler.puts_[0].second);
}

// Test that Put with empty key and non-empty value works
TEST_F(WriteBatchTest_205, PutEmptyKeyNonEmptyValue_205) {
  batch_.Put("", "value");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("", handler.puts_[0].first);
  ASSERT_EQ("value", handler.puts_[0].second);
}

// Test that Put with non-empty key and empty value works
TEST_F(WriteBatchTest_205, PutNonEmptyKeyEmptyValue_205) {
  batch_.Put("key", "");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key", handler.puts_[0].first);
  ASSERT_EQ("", handler.puts_[0].second);
}

// Test Delete increases count
TEST_F(WriteBatchTest_205, DeleteIncreasesCount_205) {
  batch_.Delete("key1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test Delete followed by Iterate produces correct delete operation
TEST_F(WriteBatchTest_205, DeleteIterateProducesCorrectKey_205) {
  batch_.Delete("key1");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("key1", handler.deletes_[0]);
}

// Test mixed Put and Delete operations
TEST_F(WriteBatchTest_205, MixedPutAndDelete_205) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
  ASSERT_EQ("key2", handler.deletes_[0]);
  ASSERT_EQ("key3", handler.puts_[1].first);
  ASSERT_EQ("value3", handler.puts_[1].second);
}

// Test Clear resets the batch
TEST_F(WriteBatchTest_205, ClearResetsBatch_205) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));
  batch_.Clear();
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, handler.puts_.size());
  ASSERT_EQ(0u, handler.deletes_.size());
}

// Test ApproximateSize grows with Put
TEST_F(WriteBatchTest_205, ApproximateSizeGrowsWithPut_205) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  size_t one_put_size = batch_.ApproximateSize();
  ASSERT_GT(one_put_size, empty_size);
  batch_.Put("key2", "value2");
  size_t two_put_size = batch_.ApproximateSize();
  ASSERT_GT(two_put_size, one_put_size);
}

// Test ApproximateSize grows with Delete
TEST_F(WriteBatchTest_205, ApproximateSizeGrowsWithDelete_205) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Delete("key1");
  size_t one_delete_size = batch_.ApproximateSize();
  ASSERT_GT(one_delete_size, empty_size);
}

// Test Append merges two batches
TEST_F(WriteBatchTest_205, AppendMergesBatches_205) {
  batch_.Put("key1", "value1");

  WriteBatch batch2;
  batch2.Put("key2", "value2");
  batch2.Delete("key3");

  batch_.Append(batch2);
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
  ASSERT_EQ("key2", handler.puts_[1].first);
  ASSERT_EQ("value2", handler.puts_[1].second);
  ASSERT_EQ("key3", handler.deletes_[0]);
}

// Test Append with empty source batch
TEST_F(WriteBatchTest_205, AppendEmptySourceBatch_205) {
  batch_.Put("key1", "value1");
  WriteBatch empty_batch;
  batch_.Append(empty_batch);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test Append to empty batch
TEST_F(WriteBatchTest_205, AppendToEmptyBatch_205) {
  WriteBatch source;
  source.Put("key1", "value1");
  batch_.Append(source);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
}

// Test copy constructor preserves batch contents
TEST_F(WriteBatchTest_205, CopyConstructorPreservesContents_205) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");

  WriteBatch copy(batch_);
  ASSERT_EQ(2, WriteBatchInternal::Count(&copy));

  TestHandler handler;
  Status s = copy.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
  ASSERT_EQ("key2", handler.deletes_[0]);
}

// Test assignment operator preserves batch contents
TEST_F(WriteBatchTest_205, AssignmentOperatorPreservesContents_205) {
  batch_.Put("key1", "value1");

  WriteBatch assigned;
  assigned = batch_;
  ASSERT_EQ(1, WriteBatchInternal::Count(&assigned));

  TestHandler handler;
  Status s = assigned.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
}

// Test Put with large key and value
TEST_F(WriteBatchTest_205, PutLargeKeyAndValue_205) {
  std::string large_key(10000, 'k');
  std::string large_value(10000, 'v');
  batch_.Put(large_key, large_value);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ(large_key, handler.puts_[0].first);
  ASSERT_EQ(large_value, handler.puts_[0].second);
}

// Test Put with binary data (including null bytes)
TEST_F(WriteBatchTest_205, PutBinaryData_205) {
  std::string binary_key("key\0with\0nulls", 14);
  std::string binary_value("val\0with\0nulls", 14);
  batch_.Put(Slice(binary_key), Slice(binary_value));
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ(binary_key, handler.puts_[0].first);
  ASSERT_EQ(binary_value, handler.puts_[0].second);
}

// Test that iterating an empty batch produces no operations
TEST_F(WriteBatchTest_205, IterateEmptyBatch_205) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, handler.puts_.size());
  ASSERT_EQ(0u, handler.deletes_.size());
}

// Test SetSequence and Sequence
TEST_F(WriteBatchTest_205, SetAndGetSequence_205) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  ASSERT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

// Test that Put with duplicate keys produces two entries
TEST_F(WriteBatchTest_205, PutDuplicateKeys_205) {
  batch_.Put("key1", "value1");
  batch_.Put("key1", "value2");
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
  ASSERT_EQ("key1", handler.puts_[1].first);
  ASSERT_EQ("value2", handler.puts_[1].second);
}

// Test that Clear followed by new operations works correctly
TEST_F(WriteBatchTest_205, ClearThenAddOperations_205) {
  batch_.Put("key1", "value1");
  batch_.Clear();
  batch_.Put("key2", "value2");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key2", handler.puts_[0].first);
  ASSERT_EQ("value2", handler.puts_[0].second);
}

// Test ByteSize via WriteBatchInternal
TEST_F(WriteBatchTest_205, ByteSizeIncreasesWithOperations_205) {
  size_t initial_size = WriteBatchInternal::ByteSize(&batch_);
  batch_.Put("key", "value");
  size_t after_put = WriteBatchInternal::ByteSize(&batch_);
  ASSERT_GT(after_put, initial_size);
}

// Test many operations
TEST_F(WriteBatchTest_205, ManyOperations_205) {
  const int num_ops = 1000;
  for (int i = 0; i < num_ops; i++) {
    batch_.Put("key" + std::to_string(i), "value" + std::to_string(i));
  }
  ASSERT_EQ(num_ops, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(static_cast<size_t>(num_ops), handler.puts_.size());
  for (int i = 0; i < num_ops; i++) {
    ASSERT_EQ("key" + std::to_string(i), handler.puts_[i].first);
    ASSERT_EQ("value" + std::to_string(i), handler.puts_[i].second);
  }
}

}  // namespace leveldb
