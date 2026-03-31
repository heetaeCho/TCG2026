#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include <string>
#include <vector>

namespace leveldb {

// A simple Handler implementation for testing Iterate
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

// Test fixture
class WriteBatchTest_210 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

TEST_F(WriteBatchTest_210, EmptyBatchHasZeroCount_210) {
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, PutIncreasesCount_210) {
  batch_.Put("key1", "value1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, MultiplePutsIncreaseCount_210) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Put("key3", "value3");
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, DeleteIncreasesCount_210) {
  batch_.Delete("key1");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, MultipleDeletesIncreaseCount_210) {
  batch_.Delete("key1");
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, MixedPutAndDeleteCount_210) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, ClearResetsCount_210) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Clear();
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, ClearResetsSizeToHeader_210) {
  batch_.Put("key1", "value1");
  batch_.Clear();
  // After clear, ApproximateSize should be the header size
  size_t empty_size = WriteBatch().ApproximateSize();
  EXPECT_EQ(empty_size, batch_.ApproximateSize());
}

TEST_F(WriteBatchTest_210, ApproximateSizeEmptyBatch_210) {
  // An empty batch should have a size equal to the header
  EXPECT_EQ(12u, batch_.ApproximateSize());  // kHeader == 12
}

TEST_F(WriteBatchTest_210, ApproximateSizeIncreasesWithPut_210) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Put("key", "value");
  EXPECT_GT(batch_.ApproximateSize(), initial_size);
}

TEST_F(WriteBatchTest_210, ApproximateSizeIncreasesWithDelete_210) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Delete("key");
  EXPECT_GT(batch_.ApproximateSize(), initial_size);
}

TEST_F(WriteBatchTest_210, IterateEmptyBatch_210) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(handler.ops_.empty());
}

TEST_F(WriteBatchTest_210, IteratePutOperations_210) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("PUT(key2,value2)", handler.ops_[1]);
}

TEST_F(WriteBatchTest_210, IterateDeleteOperations_210) {
  batch_.Delete("key1");
  batch_.Delete("key2");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.ops_.size());
  EXPECT_EQ("DELETE(key1)", handler.ops_[0]);
  EXPECT_EQ("DELETE(key2)", handler.ops_[1]);
}

TEST_F(WriteBatchTest_210, IterateMixedOperations_210) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("DELETE(key2)", handler.ops_[1]);
  EXPECT_EQ("PUT(key3,value3)", handler.ops_[2]);
}

TEST_F(WriteBatchTest_210, AppendEmptyToEmpty_210) {
  WriteBatch source;
  batch_.Append(source);
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, AppendNonEmptyToEmpty_210) {
  WriteBatch source;
  source.Put("key1", "value1");
  source.Delete("key2");
  batch_.Append(source);
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
  
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("DELETE(key2)", handler.ops_[1]);
}

TEST_F(WriteBatchTest_210, AppendEmptyToNonEmpty_210) {
  batch_.Put("key1", "value1");
  WriteBatch source;
  batch_.Append(source);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
}

TEST_F(WriteBatchTest_210, AppendNonEmptyToNonEmpty_210) {
  batch_.Put("key1", "value1");
  WriteBatch source;
  source.Put("key2", "value2");
  source.Delete("key3");
  batch_.Append(source);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
  
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.ops_.size());
  EXPECT_EQ("PUT(key1,value1)", handler.ops_[0]);
  EXPECT_EQ("PUT(key2,value2)", handler.ops_[1]);
  EXPECT_EQ("DELETE(key3)", handler.ops_[2]);
}

TEST_F(WriteBatchTest_210, WriteBatchInternalAppend_210) {
  batch_.Put("a", "1");
  WriteBatch src;
  src.Put("b", "2");
  src.Delete("c");
  WriteBatchInternal::Append(&batch_, &src);
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
  
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.ops_.size());
  EXPECT_EQ("PUT(a,1)", handler.ops_[0]);
  EXPECT_EQ("PUT(b,2)", handler.ops_[1]);
  EXPECT_EQ("DELETE(c)", handler.ops_[2]);
}

TEST_F(WriteBatchTest_210, SetCountAndCount_210) {
  WriteBatchInternal::SetCount(&batch_, 42);
  EXPECT_EQ(42, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, SetSequenceAndSequence_210) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  EXPECT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_210, SequenceDefaultIsZero_210) {
  EXPECT_EQ(0u, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_210, ByteSizeEmptyBatch_210) {
  EXPECT_EQ(batch_.ApproximateSize(), WriteBatchInternal::ByteSize(&batch_));
}

TEST_F(WriteBatchTest_210, ByteSizeNonEmptyBatch_210) {
  batch_.Put("key", "value");
  EXPECT_EQ(batch_.ApproximateSize(), WriteBatchInternal::ByteSize(&batch_));
}

TEST_F(WriteBatchTest_210, ContentsOfEmptyBatch_210) {
  Slice contents = WriteBatchInternal::Contents(&batch_);
  EXPECT_EQ(12u, contents.size());  // kHeader size
}

TEST_F(WriteBatchTest_210, SetContentsReplacesBatch_210) {
  batch_.Put("key1", "value1");
  Slice original = WriteBatchInternal::Contents(&batch_);
  std::string saved(original.data(), original.size());
  
  WriteBatch batch2;
  WriteBatchInternal::SetContents(&batch2, Slice(saved));
  
  EXPECT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&batch2));
  
  TestHandler handler1, handler2;
  batch_.Iterate(&handler1);
  batch2.Iterate(&handler2);
  EXPECT_EQ(handler1.ops_, handler2.ops_);
}

TEST_F(WriteBatchTest_210, CopyConstructor_210) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  
  WriteBatch copy(batch_);
  EXPECT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&copy));
  
  TestHandler handler1, handler2;
  batch_.Iterate(&handler1);
  copy.Iterate(&handler2);
  EXPECT_EQ(handler1.ops_, handler2.ops_);
}

TEST_F(WriteBatchTest_210, AssignmentOperator_210) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  
  WriteBatch assigned;
  assigned = batch_;
  EXPECT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&assigned));
  
  TestHandler handler1, handler2;
  batch_.Iterate(&handler1);
  assigned.Iterate(&handler2);
  EXPECT_EQ(handler1.ops_, handler2.ops_);
}

TEST_F(WriteBatchTest_210, PutEmptyKeyAndValue_210) {
  batch_.Put("", "");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("PUT(,)", handler.ops_[0]);
}

TEST_F(WriteBatchTest_210, DeleteEmptyKey_210) {
  batch_.Delete("");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("DELETE()", handler.ops_[0]);
}

TEST_F(WriteBatchTest_210, PutLargeKeyValue_210) {
  std::string large_key(10000, 'k');
  std::string large_value(10000, 'v');
  batch_.Put(large_key, large_value);
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("PUT(" + large_key + "," + large_value + ")", handler.ops_[0]);
}

TEST_F(WriteBatchTest_210, MultipleAppends_210) {
  WriteBatch s1, s2, s3;
  s1.Put("a", "1");
  s2.Put("b", "2");
  s3.Delete("c");
  
  batch_.Append(s1);
  batch_.Append(s2);
  batch_.Append(s3);
  
  EXPECT_EQ(3, WriteBatchInternal::Count(&batch_));
  
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(3u, handler.ops_.size());
  EXPECT_EQ("PUT(a,1)", handler.ops_[0]);
  EXPECT_EQ("PUT(b,2)", handler.ops_[1]);
  EXPECT_EQ("DELETE(c)", handler.ops_[2]);
}

TEST_F(WriteBatchTest_210, ApproximateSizeGrowsWithEachPut_210) {
  size_t prev_size = batch_.ApproximateSize();
  for (int i = 0; i < 10; i++) {
    batch_.Put("key" + std::to_string(i), "value" + std::to_string(i));
    size_t cur_size = batch_.ApproximateSize();
    EXPECT_GT(cur_size, prev_size);
    prev_size = cur_size;
  }
}

TEST_F(WriteBatchTest_210, ClearAndReuse_210) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));
  
  batch_.Clear();
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
  
  batch_.Put("key3", "value3");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(1u, handler.ops_.size());
  EXPECT_EQ("PUT(key3,value3)", handler.ops_[0]);
}

TEST_F(WriteBatchTest_210, AppendToSelf_210) {
  batch_.Put("key1", "value1");
  int original_count = WriteBatchInternal::Count(&batch_);
  batch_.Append(batch_);
  // After appending to self, count should double
  EXPECT_EQ(original_count * 2, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_210, SetSequenceLargeValue_210) {
  WriteBatchInternal::SetSequence(&batch_, 0xFFFFFFFFFFULL);
  EXPECT_EQ(0xFFFFFFFFFFULL, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_210, SetCountZero_210) {
  batch_.Put("key", "value");
  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
  WriteBatchInternal::SetCount(&batch_, 0);
  EXPECT_EQ(0, WriteBatchInternal::Count(&batch_));
}

}  // namespace leveldb
