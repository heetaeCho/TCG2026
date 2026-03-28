#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/db.h"
#include "leveldb/status.h"
#include "db/write_batch_internal.h"
#include "db/memtable.h"
#include "leveldb/comparator.h"
#include "db/dbformat.h"

namespace leveldb {

// A simple Handler mock to capture Iterate calls
class TestHandler_202 : public WriteBatch::Handler {
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

class WriteBatchTest_202 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// Test that a newly created WriteBatch has count 0
TEST_F(WriteBatchTest_202, EmptyBatchHasZeroCount_202) {
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that a newly created WriteBatch has a certain approximate size (header only)
TEST_F(WriteBatchTest_202, EmptyBatchApproximateSize_202) {
  // Header is 12 bytes (8 byte sequence + 4 byte count)
  ASSERT_EQ(12u, batch_.ApproximateSize());
}

// Test that Put increases count by 1
TEST_F(WriteBatchTest_202, PutIncreasesCount_202) {
  batch_.Put("key1", "value1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test that Delete increases count by 1
TEST_F(WriteBatchTest_202, DeleteIncreasesCount_202) {
  batch_.Delete("key1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test that multiple Puts increase count correctly
TEST_F(WriteBatchTest_202, MultiplePutsIncreaseCount_202) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Put("key3", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test that mixed Put and Delete operations increase count correctly
TEST_F(WriteBatchTest_202, MixedPutDeleteCount_202) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test that Clear resets the batch
TEST_F(WriteBatchTest_202, ClearResetsBatch_202) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Clear();
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
  ASSERT_EQ(12u, batch_.ApproximateSize());
}

// Test that ApproximateSize increases after Put
TEST_F(WriteBatchTest_202, ApproximateSizeIncreasesAfterPut_202) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  ASSERT_GT(batch_.ApproximateSize(), initial_size);
}

// Test that ApproximateSize increases after Delete
TEST_F(WriteBatchTest_202, ApproximateSizeIncreasesAfterDelete_202) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Delete("key1");
  ASSERT_GT(batch_.ApproximateSize(), initial_size);
}

// Test Iterate with Put operations
TEST_F(WriteBatchTest_202, IterateWithPuts_202) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
  ASSERT_EQ("key2", handler.puts_[1].first);
  ASSERT_EQ("value2", handler.puts_[1].second);
}

// Test Iterate with Delete operations
TEST_F(WriteBatchTest_202, IterateWithDeletes_202) {
  batch_.Delete("key1");
  batch_.Delete("key2");

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.deletes_.size());
  ASSERT_EQ("key1", handler.deletes_[0]);
  ASSERT_EQ("key2", handler.deletes_[1]);
}

// Test Iterate with mixed operations preserves order
TEST_F(WriteBatchTest_202, IterateMixedOperationsOrder_202) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");

  TestHandler_202 handler;
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

// Test Iterate on empty batch
TEST_F(WriteBatchTest_202, IterateEmptyBatch_202) {
  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, handler.puts_.size());
  ASSERT_EQ(0u, handler.deletes_.size());
}

// Test SetCount and Count
TEST_F(WriteBatchTest_202, SetCountAndCount_202) {
  WriteBatchInternal::SetCount(&batch_, 42);
  ASSERT_EQ(42, WriteBatchInternal::Count(&batch_));
}

// Test SetSequence and Sequence
TEST_F(WriteBatchTest_202, SetSequenceAndSequence_202) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  ASSERT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

// Test Append combines two batches
TEST_F(WriteBatchTest_202, AppendCombinesBatches_202) {
  batch_.Put("key1", "value1");

  WriteBatch batch2;
  batch2.Put("key2", "value2");
  batch2.Delete("key3");

  batch_.Append(batch2);
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("key2", handler.puts_[1].first);
  ASSERT_EQ("key3", handler.deletes_[0]);
}

// Test Append with empty source
TEST_F(WriteBatchTest_202, AppendEmptySource_202) {
  batch_.Put("key1", "value1");
  WriteBatch empty;
  batch_.Append(empty);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test Append to empty destination
TEST_F(WriteBatchTest_202, AppendToEmptyDestination_202) {
  WriteBatch source;
  source.Put("key1", "value1");
  batch_.Append(source);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
}

// Test copy constructor
TEST_F(WriteBatchTest_202, CopyConstructor_202) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");

  WriteBatch copy(batch_);
  ASSERT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&copy));

  TestHandler_202 handler;
  Status s = copy.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("key2", handler.deletes_[0]);
}

// Test assignment operator
TEST_F(WriteBatchTest_202, AssignmentOperator_202) {
  batch_.Put("key1", "value1");

  WriteBatch other;
  other = batch_;
  ASSERT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&other));

  TestHandler_202 handler;
  Status s = other.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
}

// Test Put with empty key and value
TEST_F(WriteBatchTest_202, PutEmptyKeyAndValue_202) {
  batch_.Put("", "");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("", handler.puts_[0].first);
  ASSERT_EQ("", handler.puts_[0].second);
}

// Test Delete with empty key
TEST_F(WriteBatchTest_202, DeleteEmptyKey_202) {
  batch_.Delete("");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("", handler.deletes_[0]);
}

// Test Put with large key and value
TEST_F(WriteBatchTest_202, PutLargeKeyAndValue_202) {
  std::string large_key(10000, 'k');
  std::string large_value(10000, 'v');
  batch_.Put(large_key, large_value);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ(large_key, handler.puts_[0].first);
  ASSERT_EQ(large_value, handler.puts_[0].second);
}

// Test ByteSize through WriteBatchInternal
TEST_F(WriteBatchTest_202, ByteSize_202) {
  size_t empty_size = WriteBatchInternal::ByteSize(&batch_);
  ASSERT_EQ(12u, empty_size);  // header size

  batch_.Put("key", "val");
  ASSERT_GT(WriteBatchInternal::ByteSize(&batch_), empty_size);
}

// Test Contents through WriteBatchInternal
TEST_F(WriteBatchTest_202, Contents_202) {
  Slice contents = WriteBatchInternal::Contents(&batch_);
  // At minimum, the contents should be the 12-byte header for an empty batch
  ASSERT_EQ(12u, contents.size());
}

// Test SetContents
TEST_F(WriteBatchTest_202, SetContents_202) {
  batch_.Put("key1", "value1");
  Slice saved_contents = WriteBatchInternal::Contents(&batch_);
  std::string saved(saved_contents.data(), saved_contents.size());

  WriteBatch batch2;
  WriteBatchInternal::SetContents(&batch2, saved);

  ASSERT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&batch2));

  TestHandler_202 handler;
  Status s = batch2.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
}

// Test WriteBatchInternal::Append (static version)
TEST_F(WriteBatchTest_202, WriteBatchInternalAppend_202) {
  batch_.Put("key1", "value1");

  WriteBatch src;
  src.Put("key2", "value2");
  src.Delete("key3");

  WriteBatchInternal::Append(&batch_, &src);
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
}

// Test sequence number default
TEST_F(WriteBatchTest_202, DefaultSequenceNumber_202) {
  ASSERT_EQ(0u, WriteBatchInternal::Sequence(&batch_));
}

// Test SetCount to zero
TEST_F(WriteBatchTest_202, SetCountToZero_202) {
  batch_.Put("key1", "value1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
  WriteBatchInternal::SetCount(&batch_, 0);
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test multiple Clears
TEST_F(WriteBatchTest_202, MultipleClear_202) {
  batch_.Put("key1", "value1");
  batch_.Clear();
  batch_.Put("key2", "value2");
  batch_.Clear();
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, handler.puts_.size());
  ASSERT_EQ(0u, handler.deletes_.size());
}

// Test reuse after Clear
TEST_F(WriteBatchTest_202, ReuseAfterClear_202) {
  batch_.Put("key1", "value1");
  batch_.Clear();
  batch_.Put("key2", "value2");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler_202 handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key2", handler.puts_[0].first);
  ASSERT_EQ("value2", handler.puts_[0].second);
}

// Test InsertInto with MemTable
TEST_F(WriteBatchTest_202, InsertIntoMemTable_202) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Delete("key3");

  WriteBatchInternal::SetSequence(&batch_, 100);

  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  Status s = WriteBatchInternal::InsertInto(&batch_, mem);
  ASSERT_TRUE(s.ok());

  // Verify the data was inserted by looking up the keys
  LookupKey lk1(Slice("key1"), 102);
  std::string value;
  Status found_status;
  bool found = mem->Get(lk1, &value, &found_status);
  ASSERT_TRUE(found);
  ASSERT_TRUE(found_status.ok());
  ASSERT_EQ("value1", value);

  LookupKey lk2(Slice("key2"), 102);
  found = mem->Get(lk2, &value, &found_status);
  ASSERT_TRUE(found);
  ASSERT_TRUE(found_status.ok());
  ASSERT_EQ("value2", value);

  // key3 was deleted; lookup at seq 102 should find the deletion marker
  LookupKey lk3(Slice("key3"), 103);
  found = mem->Get(lk3, &value, &found_status);
  ASSERT_TRUE(found);
  ASSERT_TRUE(found_status.IsNotFound());

  mem->Unref();
}

}  // namespace leveldb
