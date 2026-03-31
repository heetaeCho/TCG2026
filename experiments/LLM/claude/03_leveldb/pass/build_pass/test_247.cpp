#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <cstring>
#include <string>
#include <vector>

// Replicate the C wrapper struct as defined in db/c.cc
struct leveldb_writebatch_t {
  leveldb::WriteBatch rep;
};

// Replicate the C function under test
void leveldb_writebatch_put(leveldb_writebatch_t* b, const char* key,
                            size_t klen, const char* val, size_t vlen) {
  b->rep.Put(leveldb::Slice(key, klen), leveldb::Slice(val, vlen));
}

// A simple Handler to inspect what was put into the WriteBatch
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

class WriteBatchCTest_247 : public ::testing::Test {
 protected:
  void SetUp() override {
    batch_ = new leveldb_writebatch_t;
  }
  void TearDown() override {
    delete batch_;
  }
  leveldb_writebatch_t* batch_;
};

// Test that a single Put is recorded correctly
TEST_F(WriteBatchCTest_247, SinglePut_247) {
  const char* key = "hello";
  const char* val = "world";
  leveldb_writebatch_put(batch_, key, 5, val, 5);

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "hello");
  EXPECT_EQ(handler.puts_[0].second, "world");
  EXPECT_EQ(handler.deletes_.size(), 0u);
}

// Test that multiple Puts are all recorded in order
TEST_F(WriteBatchCTest_247, MultiplePuts_247) {
  leveldb_writebatch_put(batch_, "k1", 2, "v1", 2);
  leveldb_writebatch_put(batch_, "k2", 2, "v2", 2);
  leveldb_writebatch_put(batch_, "k3", 2, "v3", 2);

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 3u);
  EXPECT_EQ(handler.puts_[0].first, "k1");
  EXPECT_EQ(handler.puts_[0].second, "v1");
  EXPECT_EQ(handler.puts_[1].first, "k2");
  EXPECT_EQ(handler.puts_[1].second, "v2");
  EXPECT_EQ(handler.puts_[2].first, "k3");
  EXPECT_EQ(handler.puts_[2].second, "v3");
}

// Test putting empty key and empty value
TEST_F(WriteBatchCTest_247, EmptyKeyAndValue_247) {
  leveldb_writebatch_put(batch_, "", 0, "", 0);

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "");
  EXPECT_EQ(handler.puts_[0].second, "");
}

// Test putting empty key with non-empty value
TEST_F(WriteBatchCTest_247, EmptyKeyNonEmptyValue_247) {
  leveldb_writebatch_put(batch_, "", 0, "value", 5);

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "");
  EXPECT_EQ(handler.puts_[0].second, "value");
}

// Test putting non-empty key with empty value
TEST_F(WriteBatchCTest_247, NonEmptyKeyEmptyValue_247) {
  leveldb_writebatch_put(batch_, "key", 3, "", 0);

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "key");
  EXPECT_EQ(handler.puts_[0].second, "");
}

// Test that partial key length is respected (only klen bytes used)
TEST_F(WriteBatchCTest_247, PartialKeyLength_247) {
  const char* key = "hello_world";
  leveldb_writebatch_put(batch_, key, 5, "v", 1);

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "hello");
  EXPECT_EQ(handler.puts_[0].second, "v");
}

// Test that partial value length is respected
TEST_F(WriteBatchCTest_247, PartialValueLength_247) {
  const char* val = "long_value_string";
  leveldb_writebatch_put(batch_, "k", 1, val, 4);

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, "k");
  EXPECT_EQ(handler.puts_[0].second, "long");
}

// Test that ApproximateSize increases after a put
TEST_F(WriteBatchCTest_247, ApproximateSizeIncreases_247) {
  size_t initial_size = batch_->rep.ApproximateSize();
  leveldb_writebatch_put(batch_, "key", 3, "value", 5);
  size_t after_put_size = batch_->rep.ApproximateSize();
  EXPECT_GT(after_put_size, initial_size);
}

// Test that Clear removes entries added via the C wrapper
TEST_F(WriteBatchCTest_247, ClearAfterPut_247) {
  leveldb_writebatch_put(batch_, "key", 3, "val", 3);
  batch_->rep.Clear();

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(handler.puts_.size(), 0u);
}

// Test binary data with embedded null bytes in key and value
TEST_F(WriteBatchCTest_247, BinaryDataWithNulls_247) {
  const char key[] = {'k', '\0', 'e', 'y'};
  const char val[] = {'v', '\0', 'a', 'l'};
  leveldb_writebatch_put(batch_, key, 4, val, 4);

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, std::string(key, 4));
  EXPECT_EQ(handler.puts_[0].second, std::string(val, 4));
}

// Test a large key and value
TEST_F(WriteBatchCTest_247, LargeKeyAndValue_247) {
  std::string large_key(10000, 'K');
  std::string large_val(10000, 'V');
  leveldb_writebatch_put(batch_, large_key.data(), large_key.size(),
                         large_val.data(), large_val.size());

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 1u);
  EXPECT_EQ(handler.puts_[0].first, large_key);
  EXPECT_EQ(handler.puts_[0].second, large_val);
}

// Test that the batch is initially empty before any put
TEST_F(WriteBatchCTest_247, InitiallyEmpty_247) {
  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(handler.puts_.size(), 0u);
  EXPECT_EQ(handler.deletes_.size(), 0u);
}

// Test that ApproximateSize grows proportionally with more puts
TEST_F(WriteBatchCTest_247, ApproximateSizeGrowsWithMultiplePuts_247) {
  size_t size_before = batch_->rep.ApproximateSize();

  leveldb_writebatch_put(batch_, "key1", 4, "val1", 4);
  size_t size_after_one = batch_->rep.ApproximateSize();

  leveldb_writebatch_put(batch_, "key2", 4, "val2", 4);
  size_t size_after_two = batch_->rep.ApproximateSize();

  EXPECT_GT(size_after_one, size_before);
  EXPECT_GT(size_after_two, size_after_one);
}

// Test duplicate keys — both should be recorded
TEST_F(WriteBatchCTest_247, DuplicateKeys_247) {
  leveldb_writebatch_put(batch_, "dup", 3, "val1", 4);
  leveldb_writebatch_put(batch_, "dup", 3, "val2", 4);

  TestHandler handler;
  leveldb::Status s = batch_->rep.Iterate(&handler);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(handler.puts_.size(), 2u);
  EXPECT_EQ(handler.puts_[0].first, "dup");
  EXPECT_EQ(handler.puts_[0].second, "val1");
  EXPECT_EQ(handler.puts_[1].first, "dup");
  EXPECT_EQ(handler.puts_[1].second, "val2");
}
