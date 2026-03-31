#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Replicate the C wrapper struct as defined in db/c.cc
struct leveldb_writebatch_t {
  leveldb::WriteBatch rep;
};

// Forward declare the C function under test
extern "C" {
void leveldb_writebatch_append(leveldb_writebatch_t* destination,
                               const leveldb_writebatch_t* source);
}

// A simple handler to collect Put/Delete operations for verification
class TestHandler : public leveldb::WriteBatch::Handler {
 public:
  void Put(const leveldb::Slice& key, const leveldb::Slice& value) override {
    puts_.emplace_back(key.ToString(), value.ToString());
  }
  void Delete(const leveldb::Slice& key) override {
    deletes_.push_back(key.ToString());
  }

  std::vector<std::pair<std::string, std::string>> puts_;
  std::vector<std::string> deletes_;
};

class WriteBatchAppendTest_250 : public ::testing::Test {
 protected:
  leveldb_writebatch_t dest_;
  leveldb_writebatch_t src_;
};

TEST_F(WriteBatchAppendTest_250, AppendEmptyToEmpty_250) {
  // Appending an empty batch to an empty batch should result in an empty batch.
  leveldb_writebatch_append(&dest_, &src_);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(handler.puts_.size(), 0u);
  EXPECT_EQ(handler.deletes_.size(), 0u);
}

TEST_F(WriteBatchAppendTest_250, AppendNonEmptyToEmpty_250) {
  // Appending a non-empty source to an empty destination
  src_.rep.Put("key1", "value1");
  src_.rep.Put("key2", "value2");

  leveldb_writebatch_append(&dest_, &src_);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 2u);
  EXPECT_EQ(handler.puts_[0].first, "key1");
  EXPECT_EQ(handler.puts_[0].second, "value1");
  EXPECT_EQ(handler.puts_[1].first, "key2");
  EXPECT_EQ(handler.puts_[1].second, "value2");
}

TEST_F(WriteBatchAppendTest_250, AppendEmptyToNonEmpty_250) {
  // Appending an empty source to a non-empty destination shouldn't change dest
  dest_.rep.Put("existing_key", "existing_value");

  size_t size_before = dest_.rep.ApproximateSize();
  leveldb_writebatch_append(&dest_, &src_);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "existing_key");
  EXPECT_EQ(handler.puts_[0].second, "existing_value");
}

TEST_F(WriteBatchAppendTest_250, AppendNonEmptyToNonEmpty_250) {
  // Both destination and source have entries
  dest_.rep.Put("dest_key", "dest_value");
  src_.rep.Put("src_key", "src_value");

  leveldb_writebatch_append(&dest_, &src_);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 2u);
  EXPECT_EQ(handler.puts_[0].first, "dest_key");
  EXPECT_EQ(handler.puts_[0].second, "dest_value");
  EXPECT_EQ(handler.puts_[1].first, "src_key");
  EXPECT_EQ(handler.puts_[1].second, "src_value");
}

TEST_F(WriteBatchAppendTest_250, AppendPreservesSourceUnchanged_250) {
  // Verify that the source batch is not modified by the append operation
  src_.rep.Put("src_key", "src_value");

  size_t src_size_before = src_.rep.ApproximateSize();
  leveldb_writebatch_append(&dest_, &src_);
  size_t src_size_after = src_.rep.ApproximateSize();

  EXPECT_EQ(src_size_before, src_size_after);

  TestHandler handler;
  leveldb::Status s = src_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "src_key");
  EXPECT_EQ(handler.puts_[0].second, "src_value");
}

TEST_F(WriteBatchAppendTest_250, AppendWithDeleteOperations_250) {
  // Test appending a batch that contains Delete operations
  dest_.rep.Put("key1", "value1");
  src_.rep.Delete("key1");
  src_.rep.Put("key2", "value2");

  leveldb_writebatch_append(&dest_, &src_);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 2u);
  ASSERT_EQ(handler.deletes_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "key1");
  EXPECT_EQ(handler.puts_[0].second, "value1");
  EXPECT_EQ(handler.deletes_[0], "key1");
  EXPECT_EQ(handler.puts_[1].first, "key2");
  EXPECT_EQ(handler.puts_[1].second, "value2");
}

TEST_F(WriteBatchAppendTest_250, AppendIncreasesApproximateSize_250) {
  // Approximate size should increase after appending a non-empty batch
  src_.rep.Put("key", "value");

  size_t dest_size_before = dest_.rep.ApproximateSize();
  leveldb_writebatch_append(&dest_, &src_);
  size_t dest_size_after = dest_.rep.ApproximateSize();

  EXPECT_GT(dest_size_after, dest_size_before);
}

TEST_F(WriteBatchAppendTest_250, AppendMultipleTimes_250) {
  // Test appending multiple times
  leveldb_writebatch_t src2;

  src_.rep.Put("key1", "value1");
  src2.rep.Put("key2", "value2");

  leveldb_writebatch_append(&dest_, &src_);
  leveldb_writebatch_append(&dest_, &src2);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 2u);
  EXPECT_EQ(handler.puts_[0].first, "key1");
  EXPECT_EQ(handler.puts_[0].second, "value1");
  EXPECT_EQ(handler.puts_[1].first, "key2");
  EXPECT_EQ(handler.puts_[1].second, "value2");
}

TEST_F(WriteBatchAppendTest_250, AppendSelfToSelf_250) {
  // Self-append: appending a batch to itself
  dest_.rep.Put("key", "value");

  leveldb_writebatch_append(&dest_, &dest_);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  // After self-append, we expect the original entry duplicated
  EXPECT_GE(handler.puts_.size(), 2u);
  EXPECT_EQ(handler.puts_[0].first, "key");
  EXPECT_EQ(handler.puts_[0].second, "value");
  EXPECT_EQ(handler.puts_[1].first, "key");
  EXPECT_EQ(handler.puts_[1].second, "value");
}

TEST_F(WriteBatchAppendTest_250, AppendMixedOperations_250) {
  // Dest has deletes, source has puts - verify ordering is maintained
  dest_.rep.Delete("old_key");
  dest_.rep.Put("dest_key", "dest_val");
  src_.rep.Put("src_key1", "src_val1");
  src_.rep.Delete("src_key2");

  leveldb_writebatch_append(&dest_, &src_);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());

  // Puts: dest_key, src_key1
  ASSERT_EQ(handler.puts_.size(), 2u);
  EXPECT_EQ(handler.puts_[0].first, "dest_key");
  EXPECT_EQ(handler.puts_[1].first, "src_key1");

  // Deletes: old_key, src_key2
  ASSERT_EQ(handler.deletes_.size(), 2u);
  EXPECT_EQ(handler.deletes_[0], "old_key");
  EXPECT_EQ(handler.deletes_[1], "src_key2");
}

TEST_F(WriteBatchAppendTest_250, AppendLargeNumberOfEntries_250) {
  // Boundary: append a batch with many entries
  for (int i = 0; i < 1000; i++) {
    src_.rep.Put("key" + std::to_string(i), "value" + std::to_string(i));
  }

  leveldb_writebatch_append(&dest_, &src_);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(handler.puts_.size(), 1000u);
  EXPECT_EQ(handler.puts_[0].first, "key0");
  EXPECT_EQ(handler.puts_[999].first, "key999");
}

TEST_F(WriteBatchAppendTest_250, AppendAfterClear_250) {
  // After clearing the source, appending should not add anything
  src_.rep.Put("key", "value");
  src_.rep.Clear();

  dest_.rep.Put("existing", "data");
  leveldb_writebatch_append(&dest_, &src_);

  TestHandler handler;
  leveldb::Status s = dest_.rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "existing");
}
