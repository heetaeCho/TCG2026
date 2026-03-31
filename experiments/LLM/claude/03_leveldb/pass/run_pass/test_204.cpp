#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "leveldb/db.h"
#include "leveldb/status.h"
#include "util/coding.h"

#include <string>
#include <vector>

namespace leveldb {

// A simple Handler that records the operations for verification
class TestHandler : public WriteBatch::Handler {
 public:
  void Put(const Slice& key, const Slice& value) override {
    operations_.push_back("PUT(" + key.ToString() + "," + value.ToString() + ")");
  }
  void Delete(const Slice& key) override {
    operations_.push_back("DELETE(" + key.ToString() + ")");
  }
  std::vector<std::string> operations_;
};

class WriteBatchTest_204 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// Test that a newly created WriteBatch has count 0
TEST_F(WriteBatchTest_204, EmptyBatchHasZeroCount_204) {
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that a newly created WriteBatch has a defined sequence number
TEST_F(WriteBatchTest_204, EmptyBatchHasSequenceZero_204) {
  EXPECT_EQ(0, WriteBatchInternal::Sequence(&batch_));
}

// Test that Put increases the count
TEST_F(WriteBatchTest_204, PutIncreasesCount_204) {
  batch_.Put("key1", "value1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Put("key2", "value2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test that Delete increases the count
TEST_F(WriteBatchTest_204, DeleteIncreasesCount_204) {
  batch_.Delete("key1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test mixed Put and Delete
TEST_F(WriteBatchTest_204, MixedPutAndDelete_204) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test that Iterate calls handler with correct operations
TEST_F(WriteBatchTest_204, IterateCallsPutHandler_204) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.operations_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.operations_[0]);
  EXPECT_EQ("PUT(key2,value2)", handler.operations_[1]);
}

// Test that Iterate calls handler with correct delete operations
TEST_F(WriteBatchTest_204, IterateCallsDeleteHandler_204) {
  batch_.Delete("key1");
  batch_.Delete("key2");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.operations_.size());
  EXPECT_EQ("DELETE(key1)", handler.operations_[0]);
  EXPECT_EQ("DELETE(key2)", handler.operations_[1]);
}

// Test that Iterate handles mixed operations in order
TEST_F(WriteBatchTest_204, IterateMixedOperationsInOrder_204) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.operations_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.operations_[0]);
  EXPECT_EQ("DELETE(key2)", handler.operations_[1]);
  EXPECT_EQ("PUT(key3,value3)", handler.operations_[2]);
}

// Test that Clear resets the batch
TEST_F(WriteBatchTest_204, ClearResetsBatch_204) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));

  batch_.Clear();
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(0u, handler.operations_.size());
}

// Test ApproximateSize increases with operations
TEST_F(WriteBatchTest_204, ApproximateSizeIncreasesWithPut_204) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  size_t one_put_size = batch_.ApproximateSize();
  EXPECT_GT(one_put_size, empty_size);

  batch_.Put("key2", "value2");
  size_t two_put_size = batch_.ApproximateSize();
  EXPECT_GT(two_put_size, one_put_size);
}

// Test ApproximateSize increases with delete
TEST_F(WriteBatchTest_204, ApproximateSizeIncreasesWithDelete_204) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Delete("key1");
  EXPECT_GT(batch_.ApproximateSize(), empty_size);
}

// Test ApproximateSize after Clear
TEST_F(WriteBatchTest_204, ApproximateSizeAfterClear_204) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  batch_.Clear();
  EXPECT_EQ(empty_size, batch_.ApproximateSize());
}

// Test Append combines two batches
TEST_F(WriteBatchTest_204, AppendCombinesBatches_204) {
  batch_.Put("key1", "value1");

  WriteBatch batch2;
  batch2.Put("key2", "value2");
  batch2.Delete("key3");

  batch_.Append(batch2);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.operations_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.operations_[0]);
  EXPECT_EQ("PUT(key2,value2)", handler.operations_[1]);
  EXPECT_EQ("DELETE(key3)", handler.operations_[2]);
}

// Test Append with empty source
TEST_F(WriteBatchTest_204, AppendEmptySource_204) {
  batch_.Put("key1", "value1");
  WriteBatch empty_batch;
  batch_.Append(empty_batch);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test Append to empty destination
TEST_F(WriteBatchTest_204, AppendToEmptyDest_204) {
  WriteBatch source;
  source.Put("key1", "value1");
  batch_.Append(source);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  batch_.Iterate(&handler);
  ASSERT_EQ(1u, handler.operations_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.operations_[0]);
}

// Test SetSequence and Sequence
TEST_F(WriteBatchTest_204, SetAndGetSequence_204) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  EXPECT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

// Test SetCount and Count
TEST_F(WriteBatchTest_204, SetAndGetCount_204) {
  WriteBatchInternal::SetCount(&batch_, 42);
  EXPECT_EQ(42, WriteBatchInternal::Count(&batch_));
}

// Test that Iterate on empty batch returns ok
TEST_F(WriteBatchTest_204, IterateOnEmptyBatch_204) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(0u, handler.operations_.size());
}

// Test copy constructor
TEST_F(WriteBatchTest_204, CopyConstructor_204) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  WriteBatchInternal::SetSequence(&batch_, 50);

  WriteBatch copy(batch_);
  EXPECT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&copy));
  EXPECT_EQ(WriteBatchInternal::Sequence(&batch_), WriteBatchInternal::Sequence(&copy));

  TestHandler handler;
  copy.Iterate(&handler);
  ASSERT_EQ(2u, handler.operations_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.operations_[0]);
  EXPECT_EQ("DELETE(key2)", handler.operations_[1]);
}

// Test assignment operator
TEST_F(WriteBatchTest_204, AssignmentOperator_204) {
  batch_.Put("key1", "value1");
  WriteBatchInternal::SetSequence(&batch_, 75);

  WriteBatch other;
  other = batch_;
  EXPECT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&other));
  EXPECT_EQ(WriteBatchInternal::Sequence(&batch_), WriteBatchInternal::Sequence(&other));

  TestHandler handler;
  other.Iterate(&handler);
  ASSERT_EQ(1u, handler.operations_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.operations_[0]);
}

// Test with empty key and value
TEST_F(WriteBatchTest_204, PutEmptyKeyAndValue_204) {
  batch_.Put("", "");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  batch_.Iterate(&handler);
  ASSERT_EQ(1u, handler.operations_.size());
  EXPECT_EQ("PUT(,)", handler.operations_[0]);
}

// Test Delete with empty key
TEST_F(WriteBatchTest_204, DeleteEmptyKey_204) {
  batch_.Delete("");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  batch_.Iterate(&handler);
  ASSERT_EQ(1u, handler.operations_.size());
  EXPECT_EQ("DELETE()", handler.operations_[0]);
}

// Test with large values
TEST_F(WriteBatchTest_204, PutLargeValue_204) {
  std::string large_key(1000, 'k');
  std::string large_value(10000, 'v');
  batch_.Put(large_key, large_value);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.operations_.size());
  EXPECT_EQ("PUT(" + large_key + "," + large_value + ")", handler.operations_[0]);
}

// Test ByteSize
TEST_F(WriteBatchTest_204, ByteSizeOfEmptyBatch_204) {
  size_t byte_size = WriteBatchInternal::ByteSize(&batch_);
  EXPECT_GT(byte_size, 0u);
}

// Test ByteSize grows with operations
TEST_F(WriteBatchTest_204, ByteSizeGrowsWithOperations_204) {
  size_t initial_size = WriteBatchInternal::ByteSize(&batch_);
  batch_.Put("key", "value");
  size_t after_put_size = WriteBatchInternal::ByteSize(&batch_);
  EXPECT_GT(after_put_size, initial_size);
}

// Test Contents returns non-empty for non-empty batch
TEST_F(WriteBatchTest_204, ContentsNonEmptyBatch_204) {
  batch_.Put("key1", "value1");
  Slice contents = WriteBatchInternal::Contents(&batch_);
  EXPECT_GT(contents.size(), 0u);
}

// Test SetContents
TEST_F(WriteBatchTest_204, SetContentsRestoresBatch_204) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  WriteBatchInternal::SetSequence(&batch_, 200);

  Slice contents = WriteBatchInternal::Contents(&batch_);
  std::string saved_contents = contents.ToString();

  WriteBatch restored;
  WriteBatchInternal::SetContents(&restored, saved_contents);

  EXPECT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&restored));
  EXPECT_EQ(WriteBatchInternal::Sequence(&batch_), WriteBatchInternal::Sequence(&restored));

  TestHandler handler;
  restored.Iterate(&handler);
  ASSERT_EQ(2u, handler.operations_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.operations_[0]);
  EXPECT_EQ("DELETE(key2)", handler.operations_[1]);
}

// Test WriteBatchInternal::Append static method
TEST_F(WriteBatchTest_204, InternalAppend_204) {
  batch_.Put("key1", "value1");

  WriteBatch source;
  source.Put("key2", "value2");

  WriteBatchInternal::Append(&batch_, &source);
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  batch_.Iterate(&handler);
  ASSERT_EQ(2u, handler.operations_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.operations_[0]);
  EXPECT_EQ("PUT(key2,value2)", handler.operations_[1]);
}

// Test multiple clears and reuse
TEST_F(WriteBatchTest_204, MultipleClearAndReuse_204) {
  batch_.Put("key1", "value1");
  batch_.Clear();
  batch_.Delete("key2");
  batch_.Clear();
  batch_.Put("key3", "value3");

  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  batch_.Iterate(&handler);
  ASSERT_EQ(1u, handler.operations_.size());
  EXPECT_EQ("PUT(key3,value3)", handler.operations_[0]);
}

// Test sequence number boundary: 0
TEST_F(WriteBatchTest_204, SequenceNumberZero_204) {
  WriteBatchInternal::SetSequence(&batch_, 0);
  EXPECT_EQ(0u, WriteBatchInternal::Sequence(&batch_));
}

// Test sequence number large value
TEST_F(WriteBatchTest_204, SequenceNumberLarge_204) {
  SequenceNumber large_seq = (1ULL << 56) - 1;  // Max sequence number in leveldb
  WriteBatchInternal::SetSequence(&batch_, large_seq);
  EXPECT_EQ(large_seq, WriteBatchInternal::Sequence(&batch_));
}

// Test many operations
TEST_F(WriteBatchTest_204, ManyOperations_204) {
  const int kNumOps = 1000;
  for (int i = 0; i < kNumOps; ++i) {
    batch_.Put("key" + std::to_string(i), "value" + std::to_string(i));
  }
  EXPECT_EQ(kNumOps, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(static_cast<size_t>(kNumOps), handler.operations_.size());
}

// Test Append does not modify source
TEST_F(WriteBatchTest_204, AppendDoesNotModifySource_204) {
  WriteBatch source;
  source.Put("key1", "value1");
  int source_count_before = WriteBatchInternal::Count(&source);

  batch_.Append(source);

  EXPECT_EQ(source_count_before, WriteBatchInternal::Count(&source));
}

}  // namespace leveldb
