#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/status.h"
#include "db/write_batch_internal.h"
#include "leveldb/slice.h"
#include <string>

namespace leveldb {

// A simple handler for testing Iterate
class TestHandler : public WriteBatch::Handler {
 public:
  std::string log_;

  void Put(const Slice& key, const Slice& value) override {
    log_ += "PUT(" + key.ToString() + "," + value.ToString() + ")";
  }

  void Delete(const Slice& key) override {
    log_ += "DELETE(" + key.ToString() + ")";
  }
};

class WriteBatchTest_209 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

TEST_F(WriteBatchTest_209, EmptyBatch_209) {
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_209, PutIncreasesCount_209) {
  batch_.Put("key1", "value1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_209, MultiplePuts_209) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Put("key3", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_209, DeleteIncreasesCount_209) {
  batch_.Delete("key1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_209, PutAndDelete_209) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_209, ClearResetsBatch_209) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Clear();
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_209, IterateEmpty_209) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("", handler.log_);
}

TEST_F(WriteBatchTest_209, IteratePut_209) {
  batch_.Put("key1", "value1");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("PUT(key1,value1)", handler.log_);
}

TEST_F(WriteBatchTest_209, IterateDelete_209) {
  batch_.Delete("key1");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("DELETE(key1)", handler.log_);
}

TEST_F(WriteBatchTest_209, IterateMultipleOperations_209) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("PUT(key1,value1)DELETE(key2)PUT(key3,value3)", handler.log_);
}

TEST_F(WriteBatchTest_209, ApproximateSizeEmpty_209) {
  // Empty batch should have at least the header size
  size_t empty_size = batch_.ApproximateSize();
  ASSERT_GT(empty_size, 0u);
}

TEST_F(WriteBatchTest_209, ApproximateSizeGrowsWithPut_209) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  size_t one_put_size = batch_.ApproximateSize();
  ASSERT_GT(one_put_size, empty_size);
}

TEST_F(WriteBatchTest_209, ApproximateSizeGrowsWithDelete_209) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Delete("key1");
  size_t one_delete_size = batch_.ApproximateSize();
  ASSERT_GT(one_delete_size, empty_size);
}

TEST_F(WriteBatchTest_209, AppendEmptyToEmpty_209) {
  WriteBatch source;
  batch_.Append(source);
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_209, AppendNonEmptyToEmpty_209) {
  WriteBatch source;
  source.Put("key1", "value1");
  source.Delete("key2");
  batch_.Append(source);
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("PUT(key1,value1)DELETE(key2)", handler.log_);
}

TEST_F(WriteBatchTest_209, AppendToNonEmpty_209) {
  batch_.Put("key1", "value1");
  WriteBatch source;
  source.Put("key2", "value2");
  batch_.Append(source);
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("PUT(key1,value1)PUT(key2,value2)", handler.log_);
}

TEST_F(WriteBatchTest_209, AppendEmptyToNonEmpty_209) {
  batch_.Put("key1", "value1");
  WriteBatch source;
  batch_.Append(source);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_209, SetCount_209) {
  WriteBatchInternal::SetCount(&batch_, 42);
  ASSERT_EQ(42, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_209, SetSequence_209) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  ASSERT_EQ(100u, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_209, SequenceDefaultIsZero_209) {
  ASSERT_EQ(0u, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_209, ByteSize_209) {
  size_t header_size = WriteBatchInternal::ByteSize(&batch_);
  batch_.Put("key", "value");
  size_t new_size = WriteBatchInternal::ByteSize(&batch_);
  ASSERT_GT(new_size, header_size);
}

TEST_F(WriteBatchTest_209, Contents_209) {
  batch_.Put("key", "value");
  Slice contents = WriteBatchInternal::Contents(&batch_);
  ASSERT_GE(contents.size(), 12u);  // At least the header
}

TEST_F(WriteBatchTest_209, SetContents_209) {
  batch_.Put("key1", "value1");
  Slice contents = WriteBatchInternal::Contents(&batch_);
  std::string saved(contents.data(), contents.size());

  WriteBatch batch2;
  WriteBatchInternal::SetContents(&batch2, Slice(saved));
  ASSERT_EQ(WriteBatchInternal::Count(&batch2), WriteBatchInternal::Count(&batch_));

  TestHandler handler1, handler2;
  batch_.Iterate(&handler1);
  batch2.Iterate(&handler2);
  ASSERT_EQ(handler1.log_, handler2.log_);
}

TEST_F(WriteBatchTest_209, CopyConstructor_209) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  WriteBatch batch2(batch_);
  ASSERT_EQ(WriteBatchInternal::Count(&batch2), WriteBatchInternal::Count(&batch_));

  TestHandler handler1, handler2;
  batch_.Iterate(&handler1);
  batch2.Iterate(&handler2);
  ASSERT_EQ(handler1.log_, handler2.log_);
}

TEST_F(WriteBatchTest_209, AssignmentOperator_209) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  WriteBatch batch2;
  batch2 = batch_;
  ASSERT_EQ(WriteBatchInternal::Count(&batch2), WriteBatchInternal::Count(&batch_));

  TestHandler handler1, handler2;
  batch_.Iterate(&handler1);
  batch2.Iterate(&handler2);
  ASSERT_EQ(handler1.log_, handler2.log_);
}

TEST_F(WriteBatchTest_209, PutEmptyKeyAndValue_209) {
  batch_.Put("", "");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("PUT(,)", handler.log_);
}

TEST_F(WriteBatchTest_209, DeleteEmptyKey_209) {
  batch_.Delete("");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("DELETE()", handler.log_);
}

TEST_F(WriteBatchTest_209, PutLargeKeyValue_209) {
  std::string large_key(10000, 'k');
  std::string large_value(10000, 'v');
  batch_.Put(large_key, large_value);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("PUT(" + large_key + "," + large_value + ")", handler.log_);
}

TEST_F(WriteBatchTest_209, ClearThenReuse_209) {
  batch_.Put("key1", "value1");
  batch_.Clear();
  batch_.Put("key2", "value2");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("PUT(key2,value2)", handler.log_);
}

TEST_F(WriteBatchTest_209, WriteBatchInternalAppend_209) {
  batch_.Put("key1", "value1");
  WriteBatch src;
  src.Put("key2", "value2");
  src.Delete("key3");
  WriteBatchInternal::Append(&batch_, &src);
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("PUT(key1,value1)PUT(key2,value2)DELETE(key3)", handler.log_);
}

TEST_F(WriteBatchTest_209, ApproximateSizeAfterClear_209) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  batch_.Clear();
  size_t cleared_size = batch_.ApproximateSize();
  ASSERT_EQ(empty_size, cleared_size);
}

TEST_F(WriteBatchTest_209, MultipleAppends_209) {
  WriteBatch src1, src2;
  src1.Put("a", "1");
  src2.Put("b", "2");
  batch_.Append(src1);
  batch_.Append(src2);
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));
  TestHandler handler;
  batch_.Iterate(&handler);
  ASSERT_EQ("PUT(a,1)PUT(b,2)", handler.log_);
}

TEST_F(WriteBatchTest_209, SetSequencePersistsThroughOperations_209) {
  WriteBatchInternal::SetSequence(&batch_, 500);
  batch_.Put("key", "value");
  ASSERT_EQ(500u, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_209, CountAfterSetCount_209) {
  WriteBatchInternal::SetCount(&batch_, 0);
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
  WriteBatchInternal::SetCount(&batch_, 1000);
  ASSERT_EQ(1000, WriteBatchInternal::Count(&batch_));
}

}  // namespace leveldb
