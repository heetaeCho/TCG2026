#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "leveldb/db.h"
#include "leveldb/status.h"
#include "db/memtable.h"
#include "leveldb/comparator.h"
#include "util/logging.h"

namespace leveldb {

class WriteBatchTest_196 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// Test that a newly created WriteBatch has count 0
TEST_F(WriteBatchTest_196, EmptyBatchHasZeroCount_196) {
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that Put increases the count
TEST_F(WriteBatchTest_196, PutIncreasesCount_196) {
  batch_.Put("key1", "value1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Put("key2", "value2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test that Delete increases the count
TEST_F(WriteBatchTest_196, DeleteIncreasesCount_196) {
  batch_.Delete("key1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test mixed Put and Delete
TEST_F(WriteBatchTest_196, MixedPutAndDelete_196) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test Clear resets the batch
TEST_F(WriteBatchTest_196, ClearResetsBatch_196) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
  batch_.Clear();
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test SetCount and Count
TEST_F(WriteBatchTest_196, SetCountAndCount_196) {
  WriteBatchInternal::SetCount(&batch_, 42);
  EXPECT_EQ(42, WriteBatchInternal::Count(&batch_));
}

// Test SetSequence and Sequence
TEST_F(WriteBatchTest_196, SetSequenceAndSequence_196) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  EXPECT_EQ(100, WriteBatchInternal::Sequence(&batch_));
}

// Test that initial sequence is 0
TEST_F(WriteBatchTest_196, InitialSequenceIsZero_196) {
  EXPECT_EQ(0, WriteBatchInternal::Sequence(&batch_));
}

// Test ByteSize on empty batch
TEST_F(WriteBatchTest_196, ByteSizeOnEmptyBatch_196) {
  // A new WriteBatch has a 12-byte header (8 bytes sequence + 4 bytes count)
  EXPECT_EQ(12u, WriteBatchInternal::ByteSize(&batch_));
}

// Test ByteSize increases after Put
TEST_F(WriteBatchTest_196, ByteSizeIncreasesAfterPut_196) {
  size_t initial_size = WriteBatchInternal::ByteSize(&batch_);
  batch_.Put("key", "value");
  EXPECT_GT(WriteBatchInternal::ByteSize(&batch_), initial_size);
}

// Test ByteSize increases after Delete
TEST_F(WriteBatchTest_196, ByteSizeIncreasesAfterDelete_196) {
  size_t initial_size = WriteBatchInternal::ByteSize(&batch_);
  batch_.Delete("key");
  EXPECT_GT(WriteBatchInternal::ByteSize(&batch_), initial_size);
}

// Test ApproximateSize
TEST_F(WriteBatchTest_196, ApproximateSizeOnEmptyBatch_196) {
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_), batch_.ApproximateSize());
}

// Test ApproximateSize after Put
TEST_F(WriteBatchTest_196, ApproximateSizeAfterPut_196) {
  batch_.Put("key", "value");
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_), batch_.ApproximateSize());
}

// Test Append combines batches
TEST_F(WriteBatchTest_196, AppendCombinesBatches_196) {
  batch_.Put("key1", "value1");
  WriteBatch batch2;
  batch2.Put("key2", "value2");
  batch2.Delete("key3");
  batch_.Append(batch2);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test WriteBatchInternal::Append
TEST_F(WriteBatchTest_196, InternalAppendCombinesBatches_196) {
  batch_.Put("key1", "value1");
  WriteBatch batch2;
  batch2.Put("key2", "value2");
  WriteBatchInternal::Append(&batch_, &batch2);
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test Append with empty source
TEST_F(WriteBatchTest_196, AppendEmptySource_196) {
  batch_.Put("key1", "value1");
  WriteBatch empty_batch;
  batch_.Append(empty_batch);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test Append to empty destination
TEST_F(WriteBatchTest_196, AppendToEmptyDestination_196) {
  WriteBatch source;
  source.Put("key1", "value1");
  source.Delete("key2");
  batch_.Append(source);
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test Contents returns the representation
TEST_F(WriteBatchTest_196, ContentsReturnsRepresentation_196) {
  Slice contents = WriteBatchInternal::Contents(&batch_);
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_), contents.size());
}

// Test SetContents
TEST_F(WriteBatchTest_196, SetContentsRestoresBatch_196) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  Slice saved = WriteBatchInternal::Contents(&batch_);
  std::string saved_str(saved.data(), saved.size());

  WriteBatch new_batch;
  WriteBatchInternal::SetContents(&new_batch, Slice(saved_str));
  EXPECT_EQ(WriteBatchInternal::Count(&batch_),
            WriteBatchInternal::Count(&new_batch));
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_),
            WriteBatchInternal::ByteSize(&new_batch));
}

// Test copy constructor
TEST_F(WriteBatchTest_196, CopyConstructor_196) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  WriteBatch copy(batch_);
  EXPECT_EQ(WriteBatchInternal::Count(&batch_),
            WriteBatchInternal::Count(&copy));
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_),
            WriteBatchInternal::ByteSize(&copy));
}

// Test assignment operator
TEST_F(WriteBatchTest_196, AssignmentOperator_196) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  WriteBatch assigned;
  assigned = batch_;
  EXPECT_EQ(WriteBatchInternal::Count(&batch_),
            WriteBatchInternal::Count(&assigned));
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_),
            WriteBatchInternal::ByteSize(&assigned));
}

// Test SetCount with zero
TEST_F(WriteBatchTest_196, SetCountToZero_196) {
  batch_.Put("key1", "value1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  WriteBatchInternal::SetCount(&batch_, 0);
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test sequence number boundaries
TEST_F(WriteBatchTest_196, LargeSequenceNumber_196) {
  SequenceNumber large_seq = 1ULL << 40;
  WriteBatchInternal::SetSequence(&batch_, large_seq);
  EXPECT_EQ(large_seq, WriteBatchInternal::Sequence(&batch_));
}

// Test Put with empty key and value
TEST_F(WriteBatchTest_196, PutEmptyKeyAndValue_196) {
  batch_.Put("", "");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test Delete with empty key
TEST_F(WriteBatchTest_196, DeleteEmptyKey_196) {
  batch_.Delete("");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test Put with large key and value
TEST_F(WriteBatchTest_196, PutLargeKeyAndValue_196) {
  std::string large_key(10000, 'k');
  std::string large_value(100000, 'v');
  batch_.Put(large_key, large_value);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  EXPECT_GT(WriteBatchInternal::ByteSize(&batch_), 110000u);
}

// Test Iterate with a handler
class TestHandler_196 : public WriteBatch::Handler {
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

TEST_F(WriteBatchTest_196, IterateCallsHandler_196) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Delete("key3");

  TestHandler_196 handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(2u, handler.puts_.size());
  EXPECT_EQ(1u, handler.deletes_.size());
  EXPECT_EQ("key1", handler.puts_[0].first);
  EXPECT_EQ("value1", handler.puts_[0].second);
  EXPECT_EQ("key2", handler.puts_[1].first);
  EXPECT_EQ("value2", handler.puts_[1].second);
  EXPECT_EQ("key3", handler.deletes_[0]);
}

// Test Iterate on empty batch
TEST_F(WriteBatchTest_196, IterateOnEmptyBatch_196) {
  TestHandler_196 handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(0u, handler.puts_.size());
  EXPECT_EQ(0u, handler.deletes_.size());
}

// Test Clear then reuse
TEST_F(WriteBatchTest_196, ClearThenReuse_196) {
  batch_.Put("key1", "value1");
  batch_.Clear();
  batch_.Put("key2", "value2");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler_196 handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(1u, handler.puts_.size());
  EXPECT_EQ("key2", handler.puts_[0].first);
  EXPECT_EQ("value2", handler.puts_[0].second);
}

// Test multiple appends
TEST_F(WriteBatchTest_196, MultipleAppends_196) {
  WriteBatch b1, b2, b3;
  b1.Put("a", "1");
  b2.Put("b", "2");
  b3.Delete("c");

  batch_.Append(b1);
  batch_.Append(b2);
  batch_.Append(b3);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test InsertInto with MemTable
TEST_F(WriteBatchTest_196, InsertIntoMemTable_196) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Delete("key3");
  WriteBatchInternal::SetSequence(&batch_, 100);

  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();
  Status s = WriteBatchInternal::InsertInto(&batch_, mem);
  EXPECT_TRUE(s.ok());

  // Verify we can look up inserted keys
  std::string value;
  LookupKey lk1("key1", 102);
  Status found_status;
  EXPECT_TRUE(mem->Get(lk1, &value, &found_status));
  EXPECT_EQ("value1", value);

  LookupKey lk2("key2", 102);
  EXPECT_TRUE(mem->Get(lk2, &value, &found_status));
  EXPECT_EQ("value2", value);

  mem->Unref();
}

// Test ByteSize equals Contents size
TEST_F(WriteBatchTest_196, ByteSizeEqualsContentsSize_196) {
  batch_.Put("hello", "world");
  batch_.Delete("foo");
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_),
            WriteBatchInternal::Contents(&batch_).size());
}

}  // namespace leveldb
