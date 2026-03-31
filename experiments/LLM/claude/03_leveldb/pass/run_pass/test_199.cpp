#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/db.h"
#include "leveldb/status.h"

namespace leveldb {

// A simple handler that records operations for verification
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

class WriteBatchTest_199 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

TEST_F(WriteBatchTest_199, EmptyBatchHasSmallSize_199) {
  // An empty batch should have a small but non-zero approximate size
  // (due to the header in the internal representation).
  size_t size = batch_.ApproximateSize();
  EXPECT_GT(size, 0u);
}

TEST_F(WriteBatchTest_199, PutIncreasesSize_199) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Put("key", "value");
  size_t after_put_size = batch_.ApproximateSize();
  EXPECT_GT(after_put_size, initial_size);
}

TEST_F(WriteBatchTest_199, DeleteIncreasesSize_199) {
  size_t initial_size = batch_.ApproximateSize();
  batch_.Delete("key");
  size_t after_delete_size = batch_.ApproximateSize();
  EXPECT_GT(after_delete_size, initial_size);
}

TEST_F(WriteBatchTest_199, ClearResetsSize_199) {
  batch_.Put("key1", "value1");
  batch_.Put("key2", "value2");
  batch_.Delete("key3");
  batch_.Clear();
  WriteBatch empty_batch;
  EXPECT_EQ(batch_.ApproximateSize(), empty_batch.ApproximateSize());
}

TEST_F(WriteBatchTest_199, MultiplePutsIncreaseSize_199) {
  size_t size_before = batch_.ApproximateSize();
  batch_.Put("key1", "value1");
  size_t size_after_one = batch_.ApproximateSize();
  batch_.Put("key2", "value2");
  size_t size_after_two = batch_.ApproximateSize();
  EXPECT_GT(size_after_one, size_before);
  EXPECT_GT(size_after_two, size_after_one);
}

TEST_F(WriteBatchTest_199, IterateEmptyBatch_199) {
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(handler.puts_.size(), 0u);
  EXPECT_EQ(handler.deletes_.size(), 0u);
}

TEST_F(WriteBatchTest_199, IterateSinglePut_199) {
  batch_.Put("hello", "world");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "hello");
  EXPECT_EQ(handler.puts_[0].second, "world");
  EXPECT_EQ(handler.deletes_.size(), 0u);
}

TEST_F(WriteBatchTest_199, IterateSingleDelete_199) {
  batch_.Delete("hello");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(handler.puts_.size(), 0u);
  ASSERT_EQ(handler.deletes_.size(), 1u);
  EXPECT_EQ(handler.deletes_[0], "hello");
}

TEST_F(WriteBatchTest_199, IterateMultipleOperations_199) {
  batch_.Put("key1", "val1");
  batch_.Delete("key2");
  batch_.Put("key3", "val3");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 2u);
  EXPECT_EQ(handler.puts_[0].first, "key1");
  EXPECT_EQ(handler.puts_[0].second, "val1");
  EXPECT_EQ(handler.puts_[1].first, "key3");
  EXPECT_EQ(handler.puts_[1].second, "val3");
  ASSERT_EQ(handler.deletes_.size(), 1u);
  EXPECT_EQ(handler.deletes_[0], "key2");
}

TEST_F(WriteBatchTest_199, AppendIncreasesSize_199) {
  WriteBatch other;
  other.Put("key1", "value1");
  other.Delete("key2");
  size_t initial_size = batch_.ApproximateSize();
  batch_.Append(other);
  EXPECT_GT(batch_.ApproximateSize(), initial_size);
}

TEST_F(WriteBatchTest_199, AppendCombinesOperations_199) {
  batch_.Put("key1", "val1");
  WriteBatch other;
  other.Put("key2", "val2");
  other.Delete("key3");
  batch_.Append(other);

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 2u);
  EXPECT_EQ(handler.puts_[0].first, "key1");
  EXPECT_EQ(handler.puts_[0].second, "val1");
  EXPECT_EQ(handler.puts_[1].first, "key2");
  EXPECT_EQ(handler.puts_[1].second, "val2");
  ASSERT_EQ(handler.deletes_.size(), 1u);
  EXPECT_EQ(handler.deletes_[0], "key3");
}

TEST_F(WriteBatchTest_199, AppendEmptyBatch_199) {
  batch_.Put("key1", "val1");
  size_t size_before = batch_.ApproximateSize();
  WriteBatch empty;
  batch_.Append(empty);
  // Appending an empty batch should not change content significantly
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "key1");
}

TEST_F(WriteBatchTest_199, CopyConstructor_199) {
  batch_.Put("key1", "val1");
  batch_.Delete("key2");
  WriteBatch copy(batch_);

  TestHandler handler;
  Status s = copy.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "key1");
  EXPECT_EQ(handler.puts_[0].second, "val1");
  ASSERT_EQ(handler.deletes_.size(), 1u);
  EXPECT_EQ(handler.deletes_[0], "key2");
}

TEST_F(WriteBatchTest_199, AssignmentOperator_199) {
  batch_.Put("key1", "val1");
  WriteBatch other;
  other = batch_;

  TestHandler handler;
  Status s = other.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "key1");
  EXPECT_EQ(handler.puts_[0].second, "val1");
}

TEST_F(WriteBatchTest_199, PutEmptyKeyAndValue_199) {
  batch_.Put("", "");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "");
  EXPECT_EQ(handler.puts_[0].second, "");
}

TEST_F(WriteBatchTest_199, DeleteEmptyKey_199) {
  batch_.Delete("");
  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.deletes_.size(), 1u);
  EXPECT_EQ(handler.deletes_[0], "");
}

TEST_F(WriteBatchTest_199, LargeKeyAndValue_199) {
  std::string large_key(10000, 'k');
  std::string large_value(100000, 'v');
  batch_.Put(large_key, large_value);

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, large_key);
  EXPECT_EQ(handler.puts_[0].second, large_value);
}

TEST_F(WriteBatchTest_199, SizeGrowsWithLargerData_199) {
  batch_.Put("a", "b");
  size_t small_size = batch_.ApproximateSize();

  WriteBatch big_batch;
  big_batch.Put(std::string(1000, 'x'), std::string(1000, 'y'));
  size_t big_size = big_batch.ApproximateSize();

  EXPECT_GT(big_size, small_size);
}

TEST_F(WriteBatchTest_199, ClearThenReuse_199) {
  batch_.Put("key1", "val1");
  batch_.Clear();
  batch_.Put("key2", "val2");

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "key2");
  EXPECT_EQ(handler.puts_[0].second, "val2");
}

TEST_F(WriteBatchTest_199, ManyOperations_199) {
  const int kNumOps = 1000;
  for (int i = 0; i < kNumOps; ++i) {
    batch_.Put("key" + std::to_string(i), "val" + std::to_string(i));
  }
  for (int i = 0; i < kNumOps; ++i) {
    batch_.Delete("del" + std::to_string(i));
  }

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(handler.puts_.size(), static_cast<size_t>(kNumOps));
  EXPECT_EQ(handler.deletes_.size(), static_cast<size_t>(kNumOps));
}

TEST_F(WriteBatchTest_199, ApproximateSizeConsistentAcrossCopies_199) {
  batch_.Put("key", "value");
  batch_.Delete("other");
  WriteBatch copy(batch_);
  EXPECT_EQ(batch_.ApproximateSize(), copy.ApproximateSize());
}

TEST_F(WriteBatchTest_199, AppendToSelf_199) {
  // This tests appending a batch to itself - behavior should be defined
  batch_.Put("key1", "val1");
  size_t size_before = batch_.ApproximateSize();
  batch_.Append(batch_);
  EXPECT_GT(batch_.ApproximateSize(), size_before);

  TestHandler handler;
  Status s = batch_.Iterate(&handler);
  EXPECT_TRUE(s.ok());
  // After appending to self, should have duplicated entries
  EXPECT_EQ(handler.puts_.size(), 2u);
}

}  // namespace leveldb
