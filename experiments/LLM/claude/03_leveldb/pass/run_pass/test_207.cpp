#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "leveldb/status.h"
#include <string>

namespace leveldb {

// A simple Handler implementation to observe Iterate calls
class TestHandler : public WriteBatch::Handler {
 public:
  void Put(const Slice& key, const Slice& value) override {
    entries_.push_back("PUT(" + key.ToString() + "," + value.ToString() + ")");
  }
  void Delete(const Slice& key) override {
    entries_.push_back("DELETE(" + key.ToString() + ")");
  }
  std::vector<std::string> entries_;
};

class WriteBatchTest_207 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// Test that a newly constructed WriteBatch has zero count
TEST_F(WriteBatchTest_207, EmptyBatchHasZeroCount_207) {
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that Put increases the count
TEST_F(WriteBatchTest_207, PutIncreasesCount_207) {
  batch_.Put("key1", "value1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Put("key2", "value2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test that Delete increases the count
TEST_F(WriteBatchTest_207, DeleteIncreasesCount_207) {
  batch_.Delete("key1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test that mixed Put and Delete operations increase count correctly
TEST_F(WriteBatchTest_207, MixedPutAndDeleteCount_207) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test that Clear resets the batch
TEST_F(WriteBatchTest_207, ClearResetsBatch_207) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
  batch_.Clear();
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that ApproximateSize increases after Put
TEST_F(WriteBatchTest_207, ApproximateSizeIncreasesAfterPut_207) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  EXPECT_GT(batch_.ApproximateSize(), empty_size);
}

// Test that ApproximateSize increases after Delete
TEST_F(WriteBatchTest_207, ApproximateSizeIncreasesAfterDelete_207) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Delete("key1");
  EXPECT_GT(batch_.ApproximateSize(), empty_size);
}

// Test that ApproximateSize resets after Clear
TEST_F(WriteBatchTest_207, ApproximateSizeResetsAfterClear_207) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  batch_.Clear();
  EXPECT_EQ(batch_.ApproximateSize(), empty_size);
}

// Test Iterate with Put entries
TEST_F(WriteBatchTest_207, IterateWithPutEntries_207) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.entries_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.entries_[0]);
  EXPECT_EQ("PUT(key2,value2)", handler.entries_[1]);
}

// Test Iterate with Delete entries
TEST_F(WriteBatchTest_207, IterateWithDeleteEntries_207) {
  batch_.Delete("key1");
  batch_.Delete("key2");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.entries_.size());
  EXPECT_EQ("DELETE(key1)", handler.entries_[0]);
  EXPECT_EQ("DELETE(key2)", handler.entries_[1]);
}

// Test Iterate with mixed Put and Delete
TEST_F(WriteBatchTest_207, IterateWithMixedEntries_207) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.entries_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.entries_[0]);
  EXPECT_EQ("DELETE(key2)", handler.entries_[1]);
  EXPECT_EQ("PUT(key3,value3)", handler.entries_[2]);
}

// Test Iterate on empty batch
TEST_F(WriteBatchTest_207, IterateOnEmptyBatch_207) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(0u, handler.entries_.size());
}

// Test Append combines two batches
TEST_F(WriteBatchTest_207, AppendCombinesBatches_207) {
  batch_.Put("key1", "value1");
  WriteBatch batch2;
  batch2.Put("key2", "value2");
  batch2.Delete("key3");
  batch_.Append(batch2);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.entries_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.entries_[0]);
  EXPECT_EQ("PUT(key2,value2)", handler.entries_[1]);
  EXPECT_EQ("DELETE(key3)", handler.entries_[2]);
}

// Test Append with empty source batch
TEST_F(WriteBatchTest_207, AppendEmptySourceBatch_207) {
  batch_.Put("key1", "value1");
  WriteBatch empty_batch;
  batch_.Append(empty_batch);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.entries_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.entries_[0]);
}

// Test Append to empty destination batch
TEST_F(WriteBatchTest_207, AppendToEmptyDestBatch_207) {
  WriteBatch source;
  source.Put("key1", "value1");
  batch_.Append(source);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.entries_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.entries_[0]);
}

// Test Append both empty
TEST_F(WriteBatchTest_207, AppendBothEmpty_207) {
  WriteBatch empty_batch;
  batch_.Append(empty_batch);
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test SetCount and Count
TEST_F(WriteBatchTest_207, SetCountAndCount_207) {
  WriteBatchInternal::SetCount(&batch_, 42);
  EXPECT_EQ(42, WriteBatchInternal::Count(&batch_));
}

// Test SetSequence and Sequence
TEST_F(WriteBatchTest_207, SetSequenceAndSequence_207) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  EXPECT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

// Test copy constructor
TEST_F(WriteBatchTest_207, CopyConstructor_207) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  WriteBatch copy(batch_);
  EXPECT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&copy));
  TestHandler handler;
  Status s = copy.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.entries_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.entries_[0]);
  EXPECT_EQ("DELETE(key2)", handler.entries_[1]);
}

// Test assignment operator
TEST_F(WriteBatchTest_207, AssignmentOperator_207) {
  batch_.Put("key1", "value1");
  WriteBatch other;
  other = batch_;
  EXPECT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&other));
  TestHandler handler;
  Status s = other.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.entries_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.entries_[0]);
}

// Test Put with empty key and value
TEST_F(WriteBatchTest_207, PutEmptyKeyAndValue_207) {
  batch_.Put("", "");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.entries_.size());
  EXPECT_EQ("PUT(,)", handler.entries_[0]);
}

// Test Delete with empty key
TEST_F(WriteBatchTest_207, DeleteEmptyKey_207) {
  batch_.Delete("");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.entries_.size());
  EXPECT_EQ("DELETE()", handler.entries_[0]);
}

// Test Put with large key and value
TEST_F(WriteBatchTest_207, PutLargeKeyAndValue_207) {
  std::string large_key(10000, 'k');
  std::string large_value(10000, 'v');
  batch_.Put(large_key, large_value);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.entries_.size());
  EXPECT_EQ("PUT(" + large_key + "," + large_value + ")", handler.entries_[0]);
}

// Test that ByteSize returns a reasonable value
TEST_F(WriteBatchTest_207, ByteSizeGrowsWithEntries_207) {
  size_t initial_size = WriteBatchInternal::ByteSize(&batch_);
  batch_.Put("key", "value");
  size_t after_put = WriteBatchInternal::ByteSize(&batch_);
  EXPECT_GT(after_put, initial_size);
}

// Test multiple Appends
TEST_F(WriteBatchTest_207, MultipleAppends_207) {
  WriteBatch b1, b2, b3;
  b1.Put("k1", "v1");
  b2.Put("k2", "v2");
  b3.Delete("k3");
  batch_.Append(b1);
  batch_.Append(b2);
  batch_.Append(b3);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.entries_.size());
  EXPECT_EQ("PUT(k1,v1)", handler.entries_[0]);
  EXPECT_EQ("PUT(k2,v2)", handler.entries_[1]);
  EXPECT_EQ("DELETE(k3)", handler.entries_[2]);
}

// Test Clear followed by new operations
TEST_F(WriteBatchTest_207, ClearThenAddNewEntries_207) {
  batch_.Put("old_key", "old_value");
  batch_.Clear();
  batch_.Put("new_key", "new_value");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.entries_.size());
  EXPECT_EQ("PUT(new_key,new_value)", handler.entries_[0]);
}

// Test Contents returns valid slice
TEST_F(WriteBatchTest_207, ContentsIsNotEmpty_207) {
  batch_.Put("key", "value");
  Slice contents = WriteBatchInternal::Contents(&batch_);
  EXPECT_GT(contents.size(), 0u);
}

// Test SetContents
TEST_F(WriteBatchTest_207, SetContentsFromAnotherBatch_207) {
  WriteBatch source;
  source.Put("key1", "value1");
  source.Delete("key2");
  Slice contents = WriteBatchInternal::Contents(&source);
  WriteBatchInternal::SetContents(&batch_, contents);
  EXPECT_EQ(WriteBatchInternal::Count(&source), WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.entries_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.entries_[0]);
  EXPECT_EQ("DELETE(key2)", handler.entries_[1]);
}

// Test sequence number is initially zero or consistent
TEST_F(WriteBatchTest_207, InitialSequenceNumber_207) {
  SequenceNumber seq = WriteBatchInternal::Sequence(&batch_);
  EXPECT_EQ(0u, seq);
}

// Test overwriting sequence number
TEST_F(WriteBatchTest_207, SetSequenceMultipleTimes_207) {
  WriteBatchInternal::SetSequence(&batch_, 10);
  EXPECT_EQ(10u, WriteBatchInternal::Sequence(&batch_));
  WriteBatchInternal::SetSequence(&batch_, 20);
  EXPECT_EQ(20u, WriteBatchInternal::Sequence(&batch_));
}

// Test that ApproximateSize grows proportionally
TEST_F(WriteBatchTest_207, ApproximateSizeGrowsWithMultiplePuts_207) {
  size_t size_after_0 = batch_.ApproximateSize();
  batch_.Put("k", "v");
  size_t size_after_1 = batch_.ApproximateSize();
  batch_.Put("k", "v");
  size_t size_after_2 = batch_.ApproximateSize();
  EXPECT_GT(size_after_1, size_after_0);
  EXPECT_GT(size_after_2, size_after_1);
}

}  // namespace leveldb
