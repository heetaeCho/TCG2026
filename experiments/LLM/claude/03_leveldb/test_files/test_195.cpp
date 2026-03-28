#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "leveldb/db.h"
#include "leveldb/status.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "util/logging.h"

namespace leveldb {

class WriteBatchTest_195 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// Test that a newly created WriteBatch has count 0
TEST_F(WriteBatchTest_195, EmptyBatchHasZeroCount_195) {
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that Put increases count
TEST_F(WriteBatchTest_195, PutIncreasesCount_195) {
  batch_.Put("key1", "value1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Put("key2", "value2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test that Delete increases count
TEST_F(WriteBatchTest_195, DeleteIncreasesCount_195) {
  batch_.Delete("key1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test that mixed Put and Delete operations increase count correctly
TEST_F(WriteBatchTest_195, MixedPutDeleteCount_195) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test Clear resets count to 0
TEST_F(WriteBatchTest_195, ClearResetsCount_195) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
  batch_.Clear();
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test SetCount and Count round-trip
TEST_F(WriteBatchTest_195, SetCountAndCount_195) {
  WriteBatchInternal::SetCount(&batch_, 42);
  EXPECT_EQ(42, WriteBatchInternal::Count(&batch_));
}

// Test SetSequence and Sequence round-trip
TEST_F(WriteBatchTest_195, SetSequenceAndSequence_195) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  EXPECT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

// Test that default sequence is 0
TEST_F(WriteBatchTest_195, DefaultSequenceIsZero_195) {
  EXPECT_EQ(0u, WriteBatchInternal::Sequence(&batch_));
}

// Test Contents returns non-empty slice even for empty batch (header exists)
TEST_F(WriteBatchTest_195, ContentsOfEmptyBatch_195) {
  Slice contents = WriteBatchInternal::Contents(&batch_);
  // Header is 12 bytes: 8 bytes sequence + 4 bytes count
  EXPECT_EQ(12u, contents.size());
}

// Test ByteSize matches Contents size
TEST_F(WriteBatchTest_195, ByteSizeMatchesContents_195) {
  batch_.Put("key", "value");
  EXPECT_EQ(WriteBatchInternal::Contents(&batch_).size(),
            WriteBatchInternal::ByteSize(&batch_));
}

// Test ByteSize increases after Put
TEST_F(WriteBatchTest_195, ByteSizeIncreasesAfterPut_195) {
  size_t initial = WriteBatchInternal::ByteSize(&batch_);
  batch_.Put("key", "value");
  EXPECT_GT(WriteBatchInternal::ByteSize(&batch_), initial);
}

// Test ApproximateSize
TEST_F(WriteBatchTest_195, ApproximateSizeEmptyBatch_195) {
  EXPECT_GT(batch_.ApproximateSize(), 0u);
}

TEST_F(WriteBatchTest_195, ApproximateSizeIncreasesWithPut_195) {
  size_t size1 = batch_.ApproximateSize();
  batch_.Put("key", "value");
  size_t size2 = batch_.ApproximateSize();
  EXPECT_GT(size2, size1);
}

// Test Append combines two batches
TEST_F(WriteBatchTest_195, AppendCombinesBatches_195) {
  batch_.Put("key1", "value1");
  WriteBatch batch2;
  batch2.Put("key2", "value2");
  batch2.Delete("key3");

  WriteBatchInternal::Append(&batch_, &batch2);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

// Test Append with empty source
TEST_F(WriteBatchTest_195, AppendEmptySource_195) {
  batch_.Put("key1", "value1");
  WriteBatch empty;
  WriteBatchInternal::Append(&batch_, &empty);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test Append with empty destination
TEST_F(WriteBatchTest_195, AppendToEmptyDest_195) {
  WriteBatch source;
  source.Put("key1", "value1");
  WriteBatchInternal::Append(&batch_, &source);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// Test WriteBatch::Append member function
TEST_F(WriteBatchTest_195, WriteBatchAppendMember_195) {
  batch_.Put("key1", "value1");
  WriteBatch batch2;
  batch2.Put("key2", "value2");
  batch_.Append(batch2);
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test SetContents
TEST_F(WriteBatchTest_195, SetContentsRestoresBatch_195) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  Slice contents = WriteBatchInternal::Contents(&batch_);
  std::string saved(contents.data(), contents.size());

  WriteBatch restored;
  WriteBatchInternal::SetContents(&restored, Slice(saved));
  EXPECT_EQ(WriteBatchInternal::Count(&batch_),
            WriteBatchInternal::Count(&restored));
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_),
            WriteBatchInternal::ByteSize(&restored));
}

// Test Iterate with a handler
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

TEST_F(WriteBatchTest_195, IterateCallsPutHandler_195) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  EXPECT_EQ("key1", handler.puts_[0].first);
  EXPECT_EQ("value1", handler.puts_[0].second);
  EXPECT_EQ("key2", handler.puts_[1].first);
  EXPECT_EQ("value2", handler.puts_[1].second);
}

TEST_F(WriteBatchTest_195, IterateCallsDeleteHandler_195) {
  batch_.Delete("key1");
  batch_.Delete("key2");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.deletes_.size());
  EXPECT_EQ("key1", handler.deletes_[0]);
  EXPECT_EQ("key2", handler.deletes_[1]);
}

TEST_F(WriteBatchTest_195, IterateMixedOperations_195) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.puts_.size());
  ASSERT_EQ(1u, handler.deletes_.size());
  EXPECT_EQ("key1", handler.puts_[0].first);
  EXPECT_EQ("value1", handler.puts_[0].second);
  EXPECT_EQ("key2", handler.deletes_[0]);
  EXPECT_EQ("key3", handler.puts_[1].first);
  EXPECT_EQ("value3", handler.puts_[1].second);
}

TEST_F(WriteBatchTest_195, IterateEmptyBatch_195) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(0u, handler.puts_.size());
  EXPECT_EQ(0u, handler.deletes_.size());
}

// Test InsertInto with a MemTable
TEST_F(WriteBatchTest_195, InsertIntoMemTable_195) {
  batch_.Put("key1", "value1");
  WriteBatchInternal::SetSequence(&batch_, 100);

  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  Status s = WriteBatchInternal::InsertInto(&batch_, mem);
  EXPECT_TRUE(s.ok());

  // Verify the data was inserted by looking it up
  LookupKey lk("key1", 100);
  std::string value;
  Status lookup_status;
  bool found = mem->Get(lk, &value, &lookup_status);
  EXPECT_TRUE(found);
  EXPECT_TRUE(lookup_status.ok());
  EXPECT_EQ("value1", value);

  mem->Unref();
}

// Test InsertInto with Delete
TEST_F(WriteBatchTest_195, InsertIntoMemTableWithDelete_195) {
  batch_.Put("key1", "value1");
  batch_.Delete("key1");
  WriteBatchInternal::SetSequence(&batch_, 100);

  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mem = new MemTable(cmp);
  mem->Ref();

  Status s = WriteBatchInternal::InsertInto(&batch_, mem);
  EXPECT_TRUE(s.ok());

  // The delete should be at sequence 101, put at 100
  // Looking up at sequence 101 should find the deletion marker
  LookupKey lk("key1", 101);
  std::string value;
  Status lookup_status;
  bool found = mem->Get(lk, &value, &lookup_status);
  EXPECT_TRUE(found);
  EXPECT_TRUE(lookup_status.IsNotFound());

  mem->Unref();
}

// Test copy constructor
TEST_F(WriteBatchTest_195, CopyConstructor_195) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");

  WriteBatch copy(batch_);
  EXPECT_EQ(WriteBatchInternal::Count(&batch_),
            WriteBatchInternal::Count(&copy));
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_),
            WriteBatchInternal::ByteSize(&copy));
}

// Test copy assignment
TEST_F(WriteBatchTest_195, CopyAssignment_195) {
  batch_.Put("key1", "value1");
  WriteBatch other;
  other.Put("key2", "value2");
  other.Put("key3", "value3");

  other = batch_;
  EXPECT_EQ(WriteBatchInternal::Count(&batch_),
            WriteBatchInternal::Count(&other));
  EXPECT_EQ(WriteBatchInternal::ByteSize(&batch_),
            WriteBatchInternal::ByteSize(&other));
}

// Test with empty key and value
TEST_F(WriteBatchTest_195, EmptyKeyAndValue_195) {
  batch_.Put("", "");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  EXPECT_EQ("", handler.puts_[0].first);
  EXPECT_EQ("", handler.puts_[0].second);
}

// Test with large key and value
TEST_F(WriteBatchTest_195, LargeKeyAndValue_195) {
  std::string large_key(10000, 'k');
  std::string large_value(10000, 'v');
  batch_.Put(large_key, large_value);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.puts_.size());
  EXPECT_EQ(large_key, handler.puts_[0].first);
  EXPECT_EQ(large_value, handler.puts_[0].second);
}

// Test SetCount to zero
TEST_F(WriteBatchTest_195, SetCountToZero_195) {
  batch_.Put("key", "value");
  WriteBatchInternal::SetCount(&batch_, 0);
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test sequence number boundary
TEST_F(WriteBatchTest_195, LargeSequenceNumber_195) {
  SequenceNumber large_seq = (1ULL << 56) - 1;
  WriteBatchInternal::SetSequence(&batch_, large_seq);
  EXPECT_EQ(large_seq, WriteBatchInternal::Sequence(&batch_));
}

// Test multiple clears
TEST_F(WriteBatchTest_195, MultipleClearsAreIdempotent_195) {
  batch_.Put("key", "value");
  batch_.Clear();
  batch_.Clear();
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
  EXPECT_EQ(12u, WriteBatchInternal::ByteSize(&batch_));
}

// Test that Clear resets sequence too (sequence is stored in header)
TEST_F(WriteBatchTest_195, ClearResetsSequence_195) {
  WriteBatchInternal::SetSequence(&batch_, 42);
  batch_.Put("key", "value");
  batch_.Clear();
  EXPECT_EQ(0u, WriteBatchInternal::Sequence(&batch_));
}

// Test delete with empty key
TEST_F(WriteBatchTest_195, DeleteEmptyKey_195) {
  batch_.Delete("");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.deletes_.size());
  EXPECT_EQ("", handler.deletes_[0]);
}

// Test Append both empty
TEST_F(WriteBatchTest_195, AppendBothEmpty_195) {
  WriteBatch empty;
  WriteBatchInternal::Append(&batch_, &empty);
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test many operations
TEST_F(WriteBatchTest_195, ManyOperations_195) {
  const int N = 1000;
  for (int i = 0; i < N; i++) {
    batch_.Put("key" + std::to_string(i), "value" + std::to_string(i));
  }
  EXPECT_EQ(N, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(static_cast<size_t>(N), handler.puts_.size());
}

}  // namespace leveldb
