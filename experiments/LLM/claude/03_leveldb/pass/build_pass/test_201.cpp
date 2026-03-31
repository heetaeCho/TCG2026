#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "leveldb/db.h"
#include "leveldb/status.h"
#include "util/logging.h"

#include <string>

namespace leveldb {

// A simple handler that records all operations for verification
class TestHandler : public WriteBatch::Handler {
 public:
  std::string record_;

  void Put(const Slice& key, const Slice& value) override {
    record_ += "Put(" + key.ToString() + ", " + value.ToString() + ")";
  }

  void Delete(const Slice& key) override {
    record_ += "Delete(" + key.ToString() + ")";
  }
};

class WriteBatchTest_201 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

TEST_F(WriteBatchTest_201, Empty_201) {
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
  ASSERT_EQ(0, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_201, PutIncreasesCount_201) {
  batch_.Put("key1", "value1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_201, MultiplePuts_201) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Put("key3", "value3");
  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_201, DeleteIncreasesCount_201) {
  batch_.Delete("key1");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_201, PutAndDelete_201) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_201, IteratePut_201) {
  batch_.Put("foo", "bar");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Put(foo, bar)", handler.record_);
}

TEST_F(WriteBatchTest_201, IterateDelete_201) {
  batch_.Delete("foo");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Delete(foo)", handler.record_);
}

TEST_F(WriteBatchTest_201, IterateMultipleOperations_201) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Put("key3", "value3");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Put(key1, value1)Delete(key2)Put(key3, value3)", handler.record_);
}

TEST_F(WriteBatchTest_201, Clear_201) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  batch_.Clear();
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("", handler.record_);
}

TEST_F(WriteBatchTest_201, ApproximateSizeEmpty_201) {
  // An empty batch has a header of 12 bytes (8 for sequence + 4 for count)
  size_t empty_size = batch_.ApproximateSize();
  ASSERT_GT(empty_size, 0u);
}

TEST_F(WriteBatchTest_201, ApproximateSizeGrowsWithPut_201) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  size_t size_after_put = batch_.ApproximateSize();
  ASSERT_GT(size_after_put, empty_size);
}

TEST_F(WriteBatchTest_201, ApproximateSizeGrowsWithDelete_201) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Delete("key1");
  size_t size_after_delete = batch_.ApproximateSize();
  ASSERT_GT(size_after_delete, empty_size);
}

TEST_F(WriteBatchTest_201, Append_201) {
  WriteBatch source;
  source.Put("key1", "value1");
  source.Delete("key2");

  batch_.Put("key0", "value0");
  batch_.Append(source);

  ASSERT_EQ(3, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Put(key0, value0)Put(key1, value1)Delete(key2)", handler.record_);
}

TEST_F(WriteBatchTest_201, AppendEmptyToEmpty_201) {
  WriteBatch source;
  batch_.Append(source);
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_201, AppendEmptyToNonEmpty_201) {
  batch_.Put("key1", "value1");
  WriteBatch source;
  batch_.Append(source);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_201, AppendNonEmptyToEmpty_201) {
  WriteBatch source;
  source.Put("key1", "value1");
  batch_.Append(source);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Put(key1, value1)", handler.record_);
}

TEST_F(WriteBatchTest_201, SetSequence_201) {
  WriteBatchInternal::SetSequence(&batch_, 100);
  ASSERT_EQ(100, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_201, SetCount_201) {
  WriteBatchInternal::SetCount(&batch_, 42);
  ASSERT_EQ(42, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_201, CopyConstructor_201) {
  batch_.Put("key1", "value1");
  batch_.Delete("key2");
  WriteBatchInternal::SetSequence(&batch_, 200);

  WriteBatch copy(batch_);
  ASSERT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&copy));
  ASSERT_EQ(WriteBatchInternal::Sequence(&batch_), WriteBatchInternal::Sequence(&copy));

  TestHandler handler;
  Status s = copy.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Put(key1, value1)Delete(key2)", handler.record_);
}

TEST_F(WriteBatchTest_201, AssignmentOperator_201) {
  batch_.Put("key1", "value1");
  WriteBatchInternal::SetSequence(&batch_, 300);

  WriteBatch assigned;
  assigned = batch_;
  ASSERT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&assigned));
  ASSERT_EQ(WriteBatchInternal::Sequence(&batch_), WriteBatchInternal::Sequence(&assigned));

  TestHandler handler;
  Status s = assigned.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Put(key1, value1)", handler.record_);
}

TEST_F(WriteBatchTest_201, PutEmptyKeyAndValue_201) {
  batch_.Put("", "");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Put(, )", handler.record_);
}

TEST_F(WriteBatchTest_201, DeleteEmptyKey_201) {
  batch_.Delete("");
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Delete()", handler.record_);
}

TEST_F(WriteBatchTest_201, PutLargeKeyAndValue_201) {
  std::string large_key(10000, 'k');
  std::string large_value(100000, 'v');
  batch_.Put(large_key, large_value);
  ASSERT_EQ(1, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  std::string expected = "Put(" + large_key + ", " + large_value + ")";
  ASSERT_EQ(expected, handler.record_);
}

TEST_F(WriteBatchTest_201, SequenceDefaultZero_201) {
  ASSERT_EQ(0, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_201, ClearResetsSequence_201) {
  WriteBatchInternal::SetSequence(&batch_, 500);
  batch_.Put("key", "val");
  batch_.Clear();
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));
  // After clear, sequence should be reset
  ASSERT_EQ(0, WriteBatchInternal::Sequence(&batch_));
}

TEST_F(WriteBatchTest_201, ByteSize_201) {
  size_t initial_size = WriteBatchInternal::ByteSize(&batch_);
  batch_.Put("key", "value");
  size_t size_after = WriteBatchInternal::ByteSize(&batch_);
  ASSERT_GT(size_after, initial_size);
}

TEST_F(WriteBatchTest_201, Contents_201) {
  batch_.Put("hello", "world");
  Slice contents = WriteBatchInternal::Contents(&batch_);
  ASSERT_GT(contents.size(), 12u);  // At least header size
}

TEST_F(WriteBatchTest_201, SetContents_201) {
  // Build a batch, get its contents, then set those contents on a new batch
  batch_.Put("key1", "value1");
  WriteBatchInternal::SetSequence(&batch_, 42);
  Slice contents = WriteBatchInternal::Contents(&batch_);

  WriteBatch new_batch;
  WriteBatchInternal::SetContents(&new_batch, contents);

  ASSERT_EQ(WriteBatchInternal::Count(&batch_), WriteBatchInternal::Count(&new_batch));
  ASSERT_EQ(WriteBatchInternal::Sequence(&batch_), WriteBatchInternal::Sequence(&new_batch));

  TestHandler handler;
  Status s = new_batch.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Put(key1, value1)", handler.record_);
}

TEST_F(WriteBatchTest_201, WriteBatchInternalAppend_201) {
  WriteBatch src;
  src.Put("src_key", "src_value");

  batch_.Put("dst_key", "dst_value");
  WriteBatchInternal::Append(&batch_, &src);

  ASSERT_EQ(2, WriteBatchInternal::Count(&batch_));

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("Put(dst_key, dst_value)Put(src_key, src_value)", handler.record_);
}

TEST_F(WriteBatchTest_201, ManyOperations_201) {
  const int kCount = 1000;
  for (int i = 0; i < kCount; i++) {
    batch_.Put("key" + std::to_string(i), "value" + std::to_string(i));
  }
  ASSERT_EQ(kCount, WriteBatchInternal::Count(&batch_));
}

TEST_F(WriteBatchTest_201, IterateEmptyBatch_201) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("", handler.record_);
}

TEST_F(WriteBatchTest_201, ApproximateSizeAfterClear_201) {
  size_t empty_size = batch_.ApproximateSize();
  batch_.Put("key", "value");
  batch_.Clear();
  size_t size_after_clear = batch_.ApproximateSize();
  ASSERT_EQ(empty_size, size_after_clear);
}

}  // namespace leveldb
