#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/db.h"
#include "leveldb/status.h"
#include "db/write_batch_internal.h"
#include "db/memtable.h"
#include "leveldb/options.h"
#include "util/logging.h"

namespace leveldb {

// A simple Handler that records calls for verification
class TestHandler : public WriteBatch::Handler {
 public:
  std::vector<std::pair<std::string, std::string>> puts_;
  std::vector<std::string> deletes_;

  void Put(const Slice& key, const Slice& value) override {
    puts_.emplace_back(key.ToString(), value.ToString());
  }

  void Delete(const Slice& key) override {
    deletes_.push_back(key.ToString());
  }
};

class WriteBatchTest_203 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

TEST_F(WriteBatchTest_203, EmptyBatchHasZeroCount_203) {
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_203, PutIncreasesCount_203) {
  batch_.Put("key1", "value1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  batch_.Put("key2", "value2");
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_203, DeleteIncreasesCount_203) {
  batch_.Delete("key1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  batch_.Delete("key2");
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_203, MixedPutAndDeleteCount_203) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_203, ClearResetsBatch_203) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));

  batch_.Clear();
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_203, ApproximateSizeEmptyBatch_203) {
  // An empty batch should have a header size
  size_t empty_size = batch_.ApproximateSize();
  ASSERT_GT(empty_size, 0u);
}

TEST_F(WriteBatchTest_203, ApproximateSizeIncreasesWithPut_203) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  size_t after_put = batch_.ApproximateSize();
  ASSERT_GT(after_put, initial_size);
}

TEST_F(WriteBatchTest_203, ApproximateSizeIncreasesWithDelete_203) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Delete("key1");
  size_t after_delete = batch_.ApproximateSize();
  ASSERT_GT(after_delete, initial_size);
}

TEST_F(WriteBatchTest_203, IterateEmptyBatch_203) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, handler.puts_.size());
  ASSERT_EQ(0u, handler.deletes_.size());
}

TEST_F(WriteBatchTest_203, IterateWithPuts_203) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
  ASSERT_EQ("key2", handler.puts_[1].first);
  ASSERT_EQ("value2", handler.puts_[1].second);
}

TEST_F(WriteBatchTest_203, IterateWithDeletes_203) {
  batch_.Delete("key1");
  batch_.Delete("key2");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, handler.puts_.size());
  ASSERT_EQ(2u, handler.deletes_.size());
  ASSERT_EQ("key1", handler.deletes_[0]);
  ASSERT_EQ("key2", handler.deletes_[1]);
}

TEST_F(WriteBatchTest_203, IterateMixedOperations_203) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");

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

TEST_F(WriteBatchTest_203, SetAndGetSequence_203) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  ASSERT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_203, SetAndGetCount_203) {
  WriteBatchInternal::SetCount(&batch_, 5);
  ASSERT_EQ(5, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_203, AppendBatches_203) {
  WriteBatch batch2;
  batch_.Put("key1", "value1");
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

TEST_F(WriteBatchTest_203, AppendEmptyBatch_203) {
  WriteBatch batch2;
  batch_.Put("key1", "value1");
  batch_.Append(batch2);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_203, AppendToEmptyBatch_203) {
  WriteBatch batch2;
  batch2.Put("key1", "value1");
  batch_.Append(batch2);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
}

TEST_F(WriteBatchTest_203, CopyConstructor_203) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");

  WriteBatch copy(batch_);
  ASSERT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&copy));

  TestHandler handler;
  Status s = copy.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
  ASSERT_EQ("key2", handler.deletes_[0]);
}

TEST_F(WriteBatchTest_203, AssignmentOperator_203) {
  batch_.Put("key1", "value1");

  WriteBatch other;
  other = batch_;
  ASSERT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&other));

  TestHandler handler;
  Status s = other.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
}

TEST_F(WriteBatchTest_203, ClearAndReuse_203) {
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

TEST_F(WriteBatchTest_203, PutEmptyKeyAndValue_203) {
  batch_.Put("", "");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("", handler.puts_[0].first);
  ASSERT_EQ("", handler.puts_[0].second);
}

TEST_F(WriteBatchTest_203, DeleteEmptyKey_203) {
  batch_.Delete("");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ("", handler.deletes_[0]);
}

TEST_F(WriteBatchTest_203, PutLargeKeyValue_203) {
  std::string large_key(10000, 'k');
  std::string large_value(100000, 'v');
  batch_.Put(large_key, large_value);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ(large_key, handler.puts_[0].first);
  ASSERT_EQ(large_value, handler.puts_[0].second);
}

TEST_F(WriteBatchTest_203, SequenceDefaultIsZero_203) {
  ASSERT_EQ(0u, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_203, SetSequenceLargeValue_203) {
  WriteBatchInternal::SetSequence(&batch_, 1ULL << 50);
  ASSERT_EQ(1ULL << 50, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_203, ByteSizeMatchesRepSize_203) {
  size_t byte_size = WriteBatchInternal::ByteSize(&batch_);
  ASSERT_GT(byte_size, 0u);

  batch_.Put("key", "value");
  size_t byte_size_after = WriteBatchInternal::ByteSize(&batch_);
  ASSERT_GT(byte_size_after, byte_size);
}

TEST_F(WriteBatchTest_203, ContentsAndSetContents_203) {
  batch_.Put("key1", "value1");
  Slice contents = WriteBatchInternal::Contents(&batch_);

  WriteBatch batch2;
  WriteBatchInternal::SetContents(&batch2, contents);

  ASSERT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&batch2));

  TestHandler handler;
  Status s = batch2.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key1", handler.puts_[0].first);
  ASSERT_EQ("value1", handler.puts_[0].second);
}

TEST_F(WriteBatchTest_203, WriteBatchInternalAppend_203) {
  WriteBatch src;
  batch_.Put("key1", "value1");
  src.Put("key2", "value2");
  src.Delete("key3");

  WriteBatchInternal::Append(&batch_, &src);
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
}

TEST_F(WriteBatchTest_203, MultiplePutsWithSameKey_203) {
  batch_.Put("key1", "value1");
  batch_.Put("key1", "value2");
  batch_.Put("key1", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.puts_.size());
  ASSERT_EQ("value1", handler.puts_[0].second);
  ASSERT_EQ("value2", handler.puts_[1].second);
  ASSERT_EQ("value3", handler.puts_[2].second);
}

TEST_F(WriteBatchTest_203, DeleteAndPutSameKey_203) {
  batch_.Delete("key1");
  batch_.Put("key1", "value1");
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.deletes_.size());
  ASSERT_EQ(1u, handler.puts_.size());
  ASSERT_EQ("key1", handler.deletes_[0]);
  ASSERT_EQ("key1", handler.puts_[0].first);
}

TEST_F(WriteBatchTest_203, ApproximateSizeAfterClear_203) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  batch_.Clear();
  ASSERT_EQ(empty_size, batch_.ApproximateSize());
}

TEST_F(WriteBatchTest_203, ManyOperations_203) {
  const int kNumOps = 1000;
  for (int i = 0; i < kNumOps; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value = "value" + std::to_string(i);
    batch_.Put(key, value);
  }
  ASSERT_EQ(kNumOps, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(static_cast<size_t>(kNumOps), handler.puts_.size());
}

TEST_F(WriteBatchTest_203, AppendMultipleBatches_203) {
  WriteBatch b1, b2, b3;
  b1.Put("k1", "v1");
  b2.Put("k2", "v2");
  b3.Delete("k3");

  batch_.Append(b1);
  batch_.Append(b2);
  batch_.Append(b3);

  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
}

}  // namespace leveldb
