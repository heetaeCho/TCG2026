#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/write_batch.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include "db/write_batch_internal.h"

namespace leveldb {

// Mock Handler to capture calls from Iterate
class MockHandler : public WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));
  MOCK_METHOD(void, Delete, (const Slice& key), (override));
};

// A simple recording handler for verifying order and content
class RecordingHandler : public WriteBatch::Handler {
 public:
  struct Record {
    enum Type { kPut, kDelete };
    Type type;
    std::string key;
    std::string value;
  };

  void Put(const Slice& key, const Slice& value) override {
    records.push_back({Record::kPut, key.ToString(), value.ToString()});
  }

  void Delete(const Slice& key) override {
    records.push_back({Record::kDelete, key.ToString(), ""});
  }

  std::vector<Record> records;
};

class WriteBatchTest_200 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// Test that a newly created WriteBatch has count 0
TEST_F(WriteBatchTest_200, EmptyBatchHasZeroCount_200) {
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test that Put increases the count
TEST_F(WriteBatchTest_200, PutIncreasesCount_200) {
  batch_.Put("key1", "value1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Put("key2", "value2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test that Delete increases the count
TEST_F(WriteBatchTest_200, DeleteIncreasesCount_200) {
  batch_.Delete("key1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

// Test that Clear resets the batch
TEST_F(WriteBatchTest_200, ClearResetsBatch_200) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
  batch_.Clear();
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

// Test Iterate on empty batch calls no handler methods
TEST_F(WriteBatchTest_200, IterateOnEmptyBatch_200) {
  MockHandler handler;
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);
  EXPECT_CALL(handler, Delete(::testing::_)).Times(0);

  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Iterate with a single Put
TEST_F(WriteBatchTest_200, IterateWithSinglePut_200) {
  batch_.Put("mykey", "myvalue");

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.records.size());
  EXPECT_EQ(RecordingHandler::Record::kPut, handler.records[0].type);
  EXPECT_EQ("mykey", handler.records[0].key);
  EXPECT_EQ("myvalue", handler.records[0].value);
}

// Test Iterate with a single Delete
TEST_F(WriteBatchTest_200, IterateWithSingleDelete_200) {
  batch_.Delete("mykey");

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.records.size());
  EXPECT_EQ(RecordingHandler::Record::kDelete, handler.records[0].type);
  EXPECT_EQ("mykey", handler.records[0].key);
}

// Test Iterate with multiple Puts and Deletes in order
TEST_F(WriteBatchTest_200, IterateWithMultipleOperations_200) {
  batch_.Put("key1", "val1");
  batch_.Delete("key2");
  batch_.Put("key3", "val3");
  batch_.Delete("key4");

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(4u, handler.records.size());

  EXPECT_EQ(RecordingHandler::Record::kPut, handler.records[0].type);
  EXPECT_EQ("key1", handler.records[0].key);
  EXPECT_EQ("val1", handler.records[0].value);

  EXPECT_EQ(RecordingHandler::Record::kDelete, handler.records[1].type);
  EXPECT_EQ("key2", handler.records[1].key);

  EXPECT_EQ(RecordingHandler::Record::kPut, handler.records[2].type);
  EXPECT_EQ("key3", handler.records[2].key);
  EXPECT_EQ("val3", handler.records[2].value);

  EXPECT_EQ(RecordingHandler::Record::kDelete, handler.records[3].type);
  EXPECT_EQ("key4", handler.records[3].key);
}

// Test Iterate with empty key and value
TEST_F(WriteBatchTest_200, IterateWithEmptyKeyAndValue_200) {
  batch_.Put("", "");

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.records.size());
  EXPECT_EQ("", handler.records[0].key);
  EXPECT_EQ("", handler.records[0].value);
}

// Test Delete with empty key
TEST_F(WriteBatchTest_200, IterateWithEmptyKeyDelete_200) {
  batch_.Delete("");

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.records.size());
  EXPECT_EQ("", handler.records[0].key);
}

// Test Iterate on corrupted (too small) batch
TEST_F(WriteBatchTest_200, IterateOnCorruptedTooSmallBatch_200) {
  WriteBatch batch;
  // Manually set contents to something too small (less than 12 bytes header)
  WriteBatchInternal::SetContents(&batch, Slice("short"));

  RecordingHandler handler;
  Status s = batch.Iterate(&handler);
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_EQ(0u, handler.records.size());
}

// Test Iterate with wrong count (corrupted count field)
TEST_F(WriteBatchTest_200, IterateWithWrongCount_200) {
  batch_.Put("key1", "val1");
  // Set count to something wrong
  WriteBatchInternal::SetCount(&batch_, 5);

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.IsCorruption());
}

// Test Iterate detects unknown tag (corrupted data)
TEST_F(WriteBatchTest_200, IterateWithUnknownTag_200) {
  // Build a batch with valid header but unknown tag
  // Header is 12 bytes: 8 bytes sequence + 4 bytes count
  std::string contents(12, '\0');
  // Set count = 1
  contents[8] = 1;
  contents[9] = 0;
  contents[10] = 0;
  contents[11] = 0;
  // Add unknown tag (e.g., tag = 0xFF)
  contents.push_back(static_cast<char>(0xFF));

  WriteBatch batch;
  WriteBatchInternal::SetContents(&batch, contents);

  RecordingHandler handler;
  Status s = batch.Iterate(&handler);
  EXPECT_TRUE(s.IsCorruption());
}

// Test ApproximateSize grows with operations
TEST_F(WriteBatchTest_200, ApproximateSizeGrowsWithOperations_200) {
  size_t empty_size = batch_.ApproximateSize();
  EXPECT_GT(empty_size, 0u);  // At least the header

  batch_.Put("key1", "value1");
  size_t size_after_put = batch_.ApproximateSize();
  EXPECT_GT(size_after_put, empty_size);

  batch_.Delete("key2");
  size_t size_after_delete = batch_.ApproximateSize();
  EXPECT_GT(size_after_delete, size_after_put);
}

// Test Append combines two batches
TEST_F(WriteBatchTest_200, AppendCombinesBatches_200) {
  batch_.Put("key1", "val1");

  WriteBatch batch2;
  batch2.Put("key2", "val2");
  batch2.Delete("key3");

  batch_.Append(batch2);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.records.size());

  EXPECT_EQ("key1", handler.records[0].key);
  EXPECT_EQ("val1", handler.records[0].value);
  EXPECT_EQ("key2", handler.records[1].key);
  EXPECT_EQ("val2", handler.records[1].value);
  EXPECT_EQ("key3", handler.records[2].key);
  EXPECT_EQ(RecordingHandler::Record::kDelete, handler.records[2].type);
}

// Test Append with empty source
TEST_F(WriteBatchTest_200, AppendEmptySource_200) {
  batch_.Put("key1", "val1");
  WriteBatch empty_batch;
  batch_.Append(empty_batch);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.records.size());
}

// Test Append to empty destination
TEST_F(WriteBatchTest_200, AppendToEmptyDest_200) {
  WriteBatch source;
  source.Put("key1", "val1");
  batch_.Append(source);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.records.size());
  EXPECT_EQ("key1", handler.records[0].key);
}

// Test SetSequence and Sequence
TEST_F(WriteBatchTest_200, SetAndGetSequence_200) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  EXPECT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

// Test SetCount and Count
TEST_F(WriteBatchTest_200, SetAndGetCount_200) {
  WriteBatchInternal::SetCount(&batch_, 42);
  EXPECT_EQ(42, WriteBatchInternal::Count(&batch_));
}

// Test copy constructor preserves batch content
TEST_F(WriteBatchTest_200, CopyConstructor_200) {
  batch_.Put("key1", "val1");
  batch_.Delete("key2");

  WriteBatch copy(batch_);
  EXPECT_EQ(WriteBatchInternal::Count(&batch_),
            WriteBatchInternal::Count(&copy));

  RecordingHandler handler;
  Status s = copy.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.records.size());
  EXPECT_EQ("key1", handler.records[0].key);
  EXPECT_EQ("key2", handler.records[1].key);
}

// Test assignment operator preserves batch content
TEST_F(WriteBatchTest_200, AssignmentOperator_200) {
  batch_.Put("key1", "val1");

  WriteBatch other;
  other = batch_;
  EXPECT_EQ(WriteBatchInternal::Count(&batch_),
            WriteBatchInternal::Count(&other));

  RecordingHandler handler;
  Status s = other.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.records.size());
  EXPECT_EQ("key1", handler.records[0].key);
}

// Test large key and value
TEST_F(WriteBatchTest_200, LargeKeyAndValue_200) {
  std::string large_key(10000, 'k');
  std::string large_value(100000, 'v');
  batch_.Put(large_key, large_value);

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.records.size());
  EXPECT_EQ(large_key, handler.records[0].key);
  EXPECT_EQ(large_value, handler.records[0].value);
}

// Test many operations
TEST_F(WriteBatchTest_200, ManyOperations_200) {
  const int kNumOps = 1000;
  for (int i = 0; i < kNumOps; i++) {
    batch_.Put("key" + std::to_string(i), "val" + std::to_string(i));
  }
  EXPECT_EQ(kNumOps, WriteBatchInternal::Count(&batch_));

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(static_cast<size_t>(kNumOps), handler.records.size());
}

// Test that MockHandler receives correct parameters via Iterate
TEST_F(WriteBatchTest_200, MockHandlerReceivesCorrectParams_200) {
  batch_.Put("hello", "world");
  batch_.Delete("goodbye");

  MockHandler handler;
  {
    ::testing::InSequence seq;
    EXPECT_CALL(handler, Put(::testing::_, ::testing::_))
        .WillOnce([](const Slice& key, const Slice& value) {
          EXPECT_EQ("hello", key.ToString());
          EXPECT_EQ("world", value.ToString());
        });
    EXPECT_CALL(handler, Delete(::testing::_))
        .WillOnce([](const Slice& key) {
          EXPECT_EQ("goodbye", key.ToString());
        });
  }

  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test Contents and ByteSize internal helpers
TEST_F(WriteBatchTest_200, ContentsAndByteSize_200) {
  batch_.Put("k", "v");
  Slice contents = WriteBatchInternal::Contents(&batch_);
  EXPECT_FALSE(contents.empty());
  size_t byte_size = WriteBatchInternal::ByteSize(&batch_);
  EXPECT_EQ(contents.size(), byte_size);
}

// Test SetContents replaces batch content
TEST_F(WriteBatchTest_200, SetContentsReplacesContent_200) {
  batch_.Put("key1", "val1");
  batch_.Put("key2", "val2");

  // Save contents from another batch
  WriteBatch other;
  other.Put("other_key", "other_val");
  Slice other_contents = WriteBatchInternal::Contents(&other);
  std::string saved(other_contents.data(), other_contents.size());

  WriteBatchInternal::SetContents(&batch_, saved);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.records.size());
  EXPECT_EQ("other_key", handler.records[0].key);
  EXPECT_EQ("other_val", handler.records[0].value);
}

// Test that Clear and then adding operations works correctly
TEST_F(WriteBatchTest_200, ClearThenAddOperations_200) {
  batch_.Put("key1", "val1");
  batch_.Clear();
  batch_.Put("key2", "val2");
  batch_.Delete("key3");

  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));

  RecordingHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.records.size());
  EXPECT_EQ("key2", handler.records[0].key);
  EXPECT_EQ("key3", handler.records[1].key);
}

// Test corrupted Put (truncated data after kTypeValue tag)
TEST_F(WriteBatchTest_200, CorruptedPutTruncated_200) {
  // Build header with count=1 and a kTypeValue tag but no key/value data
  std::string contents(12, '\0');
  contents[8] = 1;  // count = 1
  contents.push_back(static_cast<char>(1));  // kTypeValue tag

  WriteBatch batch;
  WriteBatchInternal::SetContents(&batch, contents);

  RecordingHandler handler;
  Status s = batch.Iterate(&handler);
  EXPECT_TRUE(s.IsCorruption());
}

// Test corrupted Delete (truncated data after kTypeDeletion tag)
TEST_F(WriteBatchTest_200, CorruptedDeleteTruncated_200) {
  // Build header with count=1 and a kTypeDeletion tag but no key data
  std::string contents(12, '\0');
  contents[8] = 1;  // count = 1
  contents.push_back(static_cast<char>(0));  // kTypeDeletion tag

  WriteBatch batch;
  WriteBatchInternal::SetContents(&batch, contents);

  RecordingHandler handler;
  Status s = batch.Iterate(&handler);
  EXPECT_TRUE(s.IsCorruption());
}

}  // namespace leveldb
