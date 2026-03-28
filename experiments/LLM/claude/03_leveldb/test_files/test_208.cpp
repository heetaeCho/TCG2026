#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/db.h"
#include "db/write_batch_internal.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/env.h"
#include "util/logging.h"

namespace leveldb {

class WriteBatchTest_208 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a newly created WriteBatch has zero count
TEST_F(WriteBatchTest_208, EmptyBatchHasZeroCount_208) {
  WriteBatch batch;
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch));
}

// Test that Put increases the count
TEST_F(WriteBatchTest_208, PutIncreasesCount_208) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch));
}

// Test that Delete increases the count
TEST_F(WriteBatchTest_208, DeleteIncreasesCount_208) {
  WriteBatch batch;
  batch.Delete("key1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch));
}

// Test multiple puts increase count correctly
TEST_F(WriteBatchTest_208, MultiplePutsIncreaseCount_208) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Put("key2", "value2");
  batch.Put("key3", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch));
}

// Test mixed puts and deletes increase count correctly
TEST_F(WriteBatchTest_208, MixedPutsAndDeletesIncreaseCount_208) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Delete("key2");
  batch.Put("key3", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch));
}

// Test Clear resets the batch
TEST_F(WriteBatchTest_208, ClearResetsBatch_208) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Delete("key2");
  batch.Clear();
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch));
}

// Test that SetSequence and Sequence work correctly
TEST_F(WriteBatchTest_208, SetAndGetSequence_208) {
  WriteBatch batch;
  WriteBatchInternal::SetSequence(&batch, 100);
  ASSERT_EQ(100, WriteBatchInternal::Sequence(&batch));
}

// Test that SetSequence works with zero
TEST_F(WriteBatchTest_208, SetSequenceToZero_208) {
  WriteBatch batch;
  WriteBatchInternal::SetSequence(&batch, 0);
  ASSERT_EQ(0, WriteBatchInternal::Sequence(&batch));
}

// Test that SetCount and Count work correctly
TEST_F(WriteBatchTest_208, SetAndGetCount_208) {
  WriteBatch batch;
  WriteBatchInternal::SetCount(&batch, 5);
  ASSERT_EQ(5, WriteBatchInternal::Count(&batch));
}

// Test Append combines two batches
TEST_F(WriteBatchTest_208, AppendCombinesBatches_208) {
  WriteBatch batch1;
  batch1.Put("key1", "value1");
  batch1.Put("key2", "value2");

  WriteBatch batch2;
  batch2.Put("key3", "value3");
  batch2.Delete("key4");

  batch1.Append(batch2);
  ASSERT_EQ(4, WriteBatchInternal::Count(&batch1));
}

// Test Append with empty source batch
TEST_F(WriteBatchTest_208, AppendEmptyBatch_208) {
  WriteBatch batch1;
  batch1.Put("key1", "value1");

  WriteBatch batch2;
  batch1.Append(batch2);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch1));
}

// Test Append to empty destination batch
TEST_F(WriteBatchTest_208, AppendToEmptyBatch_208) {
  WriteBatch batch1;

  WriteBatch batch2;
  batch2.Put("key1", "value1");
  batch2.Put("key2", "value2");

  batch1.Append(batch2);
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch1));
}

// Test ApproximateSize increases with puts
TEST_F(WriteBatchTest_208, ApproximateSizeIncreasesWithPuts_208) {
  WriteBatch batch;
  size_t empty_size = batch.ApproximateSize();
  batch.Put("key1", "value1");
  size_t one_put_size = batch.ApproximateSize();
  ASSERT_GT(one_put_size, empty_size);

  batch.Put("key2", "value2");
  size_t two_put_size = batch.ApproximateSize();
  ASSERT_GT(two_put_size, one_put_size);
}

// Test ApproximateSize increases with deletes
TEST_F(WriteBatchTest_208, ApproximateSizeIncreasesWithDeletes_208) {
  WriteBatch batch;
  size_t empty_size = batch.ApproximateSize();
  batch.Delete("key1");
  ASSERT_GT(batch.ApproximateSize(), empty_size);
}

// Test ApproximateSize resets after Clear
TEST_F(WriteBatchTest_208, ApproximateSizeResetsAfterClear_208) {
  WriteBatch batch;
  size_t empty_size = batch.ApproximateSize();
  batch.Put("key1", "value1");
  batch.Clear();
  ASSERT_EQ(empty_size, batch.ApproximateSize());
}

// Test InsertInto puts data into MemTable
TEST_F(WriteBatchTest_208, InsertIntoMemTable_208) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  WriteBatch batch;
  batch.Put("key1", "value1");
  WriteBatchInternal::SetSequence(&batch, 100);

  Status s = WriteBatchInternal::InsertInto(&batch, mem);
  ASSERT_TRUE(s.ok());

  // Verify the data was inserted by reading it back
  std::string value;
  Status get_status;
  LookupKey lkey("key1", 200);
  bool found = mem->Get(lkey, &value, &get_status);
  ASSERT_TRUE(found);
  ASSERT_TRUE(get_status.ok());
  ASSERT_EQ("value1", value);

  mem->Unref();
}

// Test InsertInto with multiple entries
TEST_F(WriteBatchTest_208, InsertIntoMemTableMultipleEntries_208) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Put("key2", "value2");
  batch.Put("key3", "value3");
  WriteBatchInternal::SetSequence(&batch, 100);

  Status s = WriteBatchInternal::InsertInto(&batch, mem);
  ASSERT_TRUE(s.ok());

  // Verify all entries were inserted
  for (int i = 1; i <= 3; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    std::string value;
    Status get_status;
    LookupKey lkey(key, 200);
    bool found = mem->Get(lkey, &value, &get_status);
    ASSERT_TRUE(found);
    ASSERT_TRUE(get_status.ok());
    ASSERT_EQ(expected_value, value);
  }

  mem->Unref();
}

// Test InsertInto with delete entries
TEST_F(WriteBatchTest_208, InsertIntoMemTableWithDelete_208) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Delete("key1");
  WriteBatchInternal::SetSequence(&batch, 100);

  Status s = WriteBatchInternal::InsertInto(&batch, mem);
  ASSERT_TRUE(s.ok());

  // The delete should be visible with a higher sequence number
  std::string value;
  Status get_status;
  LookupKey lkey("key1", 200);
  bool found = mem->Get(lkey, &value, &get_status);
  // After delete, Get should return found=true but with NotFound status
  ASSERT_TRUE(found);
  ASSERT_TRUE(get_status.IsNotFound());

  mem->Unref();
}

// Test InsertInto with empty batch
TEST_F(WriteBatchTest_208, InsertIntoMemTableEmptyBatch_208) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  WriteBatch batch;
  WriteBatchInternal::SetSequence(&batch, 100);

  Status s = WriteBatchInternal::InsertInto(&batch, mem);
  ASSERT_TRUE(s.ok());

  mem->Unref();
}

// Test WriteBatchInternal::Append
TEST_F(WriteBatchTest_208, WriteBatchInternalAppend_208) {
  WriteBatch dst;
  dst.Put("key1", "value1");

  WriteBatch src;
  src.Put("key2", "value2");
  src.Delete("key3");

  WriteBatchInternal::Append(&dst, &src);
  ASSERT_EQ(3, WriteBatchInternal::Count(&dst));
}

// Test copy constructor
TEST_F(WriteBatchTest_208, CopyConstructor_208) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Put("key2", "value2");
  WriteBatchInternal::SetSequence(&batch, 42);

  WriteBatch copy(batch);
  ASSERT_EQ(WriteBatchInternal::Count(&batch), WriteBatchInternal::Count(&copy));
  ASSERT_EQ(WriteBatchInternal::Sequence(&batch), WriteBatchInternal::Sequence(&copy));
}

// Test assignment operator
TEST_F(WriteBatchTest_208, AssignmentOperator_208) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  WriteBatchInternal::SetSequence(&batch, 42);

  WriteBatch assigned;
  assigned = batch;
  ASSERT_EQ(WriteBatchInternal::Count(&batch), WriteBatchInternal::Count(&assigned));
  ASSERT_EQ(WriteBatchInternal::Sequence(&batch), WriteBatchInternal::Sequence(&assigned));
}

// Test Put with empty key and value
TEST_F(WriteBatchTest_208, PutWithEmptyKeyAndValue_208) {
  WriteBatch batch;
  batch.Put("", "");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch));
}

// Test Delete with empty key
TEST_F(WriteBatchTest_208, DeleteWithEmptyKey_208) {
  WriteBatch batch;
  batch.Delete("");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch));
}

// Test Put with large key and value
TEST_F(WriteBatchTest_208, PutWithLargeKeyAndValue_208) {
  WriteBatch batch;
  std::string large_key(10000, 'k');
  std::string large_value(100000, 'v');
  batch.Put(large_key, large_value);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch));
}

// Test Contents and ByteSize
TEST_F(WriteBatchTest_208, ContentsAndByteSize_208) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  Slice contents = WriteBatchInternal::Contents(&batch);
  size_t byte_size = WriteBatchInternal::ByteSize(&batch);
  ASSERT_EQ(contents.size(), byte_size);
  ASSERT_GT(byte_size, 0u);
}

// Test SetContents restores batch state
TEST_F(WriteBatchTest_208, SetContentsRestoresBatchState_208) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Put("key2", "value2");
  WriteBatchInternal::SetSequence(&batch, 50);

  Slice contents = WriteBatchInternal::Contents(&batch);
  std::string saved(contents.data(), contents.size());

  WriteBatch restored;
  WriteBatchInternal::SetContents(&restored, Slice(saved));

  ASSERT_EQ(WriteBatchInternal::Count(&batch), WriteBatchInternal::Count(&restored));
  ASSERT_EQ(WriteBatchInternal::Sequence(&batch), WriteBatchInternal::Sequence(&restored));
}

// Test sequence numbers increment correctly during InsertInto
TEST_F(WriteBatchTest_208, SequenceNumbersIncrementDuringInsert_208) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Put("key2", "value2");
  WriteBatchInternal::SetSequence(&batch, 100);

  Status s = WriteBatchInternal::InsertInto(&batch, mem);
  ASSERT_TRUE(s.ok());

  // key1 should be at sequence 100, key2 at sequence 101
  // We can verify by looking up with specific sequence numbers
  {
    std::string value;
    Status get_status;
    LookupKey lkey("key1", 100);
    bool found = mem->Get(lkey, &value, &get_status);
    ASSERT_TRUE(found);
    ASSERT_EQ("value1", value);
  }
  {
    std::string value;
    Status get_status;
    LookupKey lkey("key2", 101);
    bool found = mem->Get(lkey, &value, &get_status);
    ASSERT_TRUE(found);
    ASSERT_EQ("value2", value);
  }

  mem->Unref();
}

// Test that a key not in memtable is not found
TEST_F(WriteBatchTest_208, KeyNotFoundInMemTable_208) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  WriteBatch batch;
  batch.Put("key1", "value1");
  WriteBatchInternal::SetSequence(&batch, 100);

  WriteBatchInternal::InsertInto(&batch, mem);

  std::string value;
  Status get_status;
  LookupKey lkey("nonexistent", 200);
  bool found = mem->Get(lkey, &value, &get_status);
  ASSERT_FALSE(found);

  mem->Unref();
}

// Test using Iterate with a custom handler
class TestHandler_208 : public WriteBatch::Handler {
 public:
  void Put(const Slice& key, const Slice& value) override {
    puts_.push_back({key.ToString(), value.ToString()});
  }
  void Delete(const Slice& key) override {
    deletes_.push_back(key.ToString());
  }
  std::vector<std::pair<std::string, std::string>> puts_;
  std::vector<std::string> deletes_;
};

TEST_F(WriteBatchTest_208, IterateCallsHandler_208) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Put("key2", "value2");
  batch.Delete("key3");

  TestHandler_208 handler;
  Status s = batch.Iterate(&handler);
  ASSERT_TRUE(s.ok());

  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
  ASSERT_EQ("key2", handler.puts_[1].first);
  ASSERT_EQ("value2", handler.puts_[1].second);

  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("key3", handler.deletes_[0]);
}

// Test Iterate on empty batch
TEST_F(WriteBatchTest_208, IterateOnEmptyBatch_208) {
  WriteBatch batch;
  TestHandler_208 handler;
  Status s = batch.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, handler.puts_.size());
  ASSERT_EQ(0u, handler.deletes_.size());
}

// Test Append two empty batches
TEST_F(WriteBatchTest_208, AppendTwoEmptyBatches_208) {
  WriteBatch batch1;
  WriteBatch batch2;
  batch1.Append(batch2);
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch1));
}

// Test large number of operations
TEST_F(WriteBatchTest_208, LargeNumberOfOperations_208) {
  WriteBatch batch;
  const int kNumOps = 1000;
  for (int i = 0; i < kNumOps; i++) {
    batch.Put("key" + std::to_string(i), "value" + std::to_string(i));
  }
  ASSERT_EQ(kNumOps, WriteBatchInternal::Count(&batch));
}

// Test overwriting a key
TEST_F(WriteBatchTest_208, OverwriteKey_208) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Put("key1", "value2");
  WriteBatchInternal::SetSequence(&batch, 100);

  Status s = WriteBatchInternal::InsertInto(&batch, mem);
  ASSERT_TRUE(s.ok());

  // Should get the latest value
  std::string value;
  Status get_status;
  LookupKey lkey("key1", 200);
  bool found = mem->Get(lkey, &value, &get_status);
  ASSERT_TRUE(found);
  ASSERT_TRUE(get_status.ok());
  ASSERT_EQ("value2", value);

  mem->Unref();
}

}  // namespace leveldb
