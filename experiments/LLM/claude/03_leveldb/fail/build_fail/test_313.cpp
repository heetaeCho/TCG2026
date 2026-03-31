#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/status.h"
#include "db/db_impl.h"
#include "util/testutil.h"

#include <string>
#include <thread>
#include <vector>
#include <atomic>

namespace leveldb {

class DBImplWriteTest_313 : public testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "db_impl_write_test_313";
    options_.create_if_missing = true;
    // Use default env
    Status s = DB::Open(options_, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }
};

// Test: Writing a single key-value pair succeeds
TEST_F(DBImplWriteTest_313, WriteSinglePut_313) {
  WriteBatch batch;
  batch.Put("key1", "value1");
  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify the write by reading
  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("value1", value);
}

// Test: Writing with nullptr batch (compaction trigger path)
TEST_F(DBImplWriteTest_313, WriteNullBatch_313) {
  WriteOptions write_options;
  Status s = db_->Write(write_options, nullptr);
  // nullptr batch should still return ok (it's used for compaction triggers)
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test: Writing an empty batch succeeds
TEST_F(DBImplWriteTest_313, WriteEmptyBatch_313) {
  WriteBatch batch;
  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test: Writing with sync option enabled
TEST_F(DBImplWriteTest_313, WriteWithSync_313) {
  WriteBatch batch;
  batch.Put("sync_key", "sync_value");
  WriteOptions write_options;
  write_options.sync = true;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "sync_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("sync_value", value);
}

// Test: Multiple writes in sequence
TEST_F(DBImplWriteTest_313, WriteMultipleSequential_313) {
  WriteOptions write_options;
  for (int i = 0; i < 100; i++) {
    WriteBatch batch;
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    batch.Put(key, val);
    Status s = db_->Write(write_options, &batch);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  ReadOptions read_options;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected = "val" + std::to_string(i);
    std::string value;
    Status s = db_->Get(read_options, key, &value);
    ASSERT_TRUE(s.ok()) << s.ToString();
    EXPECT_EQ(expected, value);
  }
}

// Test: WriteBatch with multiple operations
TEST_F(DBImplWriteTest_313, WriteBatchWithMultipleOperations_313) {
  WriteBatch batch;
  batch.Put("k1", "v1");
  batch.Put("k2", "v2");
  batch.Put("k3", "v3");
  batch.Delete("k2");

  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;

  s = db_->Get(read_options, "k1", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("v1", value);

  s = db_->Get(read_options, "k2", &value);
  ASSERT_TRUE(s.IsNotFound());

  s = db_->Get(read_options, "k3", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("v3", value);
}

// Test: Concurrent writes from multiple threads
TEST_F(DBImplWriteTest_313, WriteConcurrent_313) {
  const int kNumThreads = 10;
  const int kWritesPerThread = 100;
  std::vector<std::thread> threads;
  std::atomic<int> errors(0);

  for (int t = 0; t < kNumThreads; t++) {
    threads.emplace_back([this, t, &errors, kWritesPerThread]() {
      WriteOptions write_options;
      for (int i = 0; i < kWritesPerThread; i++) {
        WriteBatch batch;
        std::string key = "t" + std::to_string(t) + "_k" + std::to_string(i);
        std::string val = "t" + std::to_string(t) + "_v" + std::to_string(i);
        batch.Put(key, val);
        Status s = db_->Write(write_options, &batch);
        if (!s.ok()) {
          errors.fetch_add(1);
        }
      }
    });
  }

  for (auto& th : threads) {
    th.join();
  }

  ASSERT_EQ(0, errors.load());

  // Verify all writes
  ReadOptions read_options;
  for (int t = 0; t < kNumThreads; t++) {
    for (int i = 0; i < kWritesPerThread; i++) {
      std::string key = "t" + std::to_string(t) + "_k" + std::to_string(i);
      std::string expected = "t" + std::to_string(t) + "_v" + std::to_string(i);
      std::string value;
      Status s = db_->Get(read_options, key, &value);
      ASSERT_TRUE(s.ok()) << "Failed to read key: " << key << " " << s.ToString();
      EXPECT_EQ(expected, value);
    }
  }
}

// Test: Write overwriting an existing key
TEST_F(DBImplWriteTest_313, WriteOverwriteKey_313) {
  WriteOptions write_options;
  WriteBatch batch1;
  batch1.Put("overwrite_key", "original_value");
  Status s = db_->Write(write_options, &batch1);
  ASSERT_TRUE(s.ok());

  WriteBatch batch2;
  batch2.Put("overwrite_key", "new_value");
  s = db_->Write(write_options, &batch2);
  ASSERT_TRUE(s.ok());

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "overwrite_key", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("new_value", value);
}

// Test: Write a delete for a non-existent key (should not error)
TEST_F(DBImplWriteTest_313, WriteDeleteNonExistentKey_313) {
  WriteBatch batch;
  batch.Delete("nonexistent_key");
  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test: Write large values
TEST_F(DBImplWriteTest_313, WriteLargeValue_313) {
  std::string large_value(100000, 'x');
  WriteBatch batch;
  batch.Put("large_key", large_value);
  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "large_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(large_value, value);
}

// Test: Write with empty key
TEST_F(DBImplWriteTest_313, WriteEmptyKey_313) {
  WriteBatch batch;
  batch.Put("", "empty_key_value");
  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("empty_key_value", value);
}

// Test: Write with empty value
TEST_F(DBImplWriteTest_313, WriteEmptyValue_313) {
  WriteBatch batch;
  batch.Put("empty_val_key", "");
  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "empty_val_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("", value);
}

// Test: Batch with many operations
TEST_F(DBImplWriteTest_313, WriteLargeBatch_313) {
  WriteBatch batch;
  const int kCount = 1000;
  for (int i = 0; i < kCount; i++) {
    batch.Put("batch_key_" + std::to_string(i), "batch_val_" + std::to_string(i));
  }
  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  for (int i = 0; i < kCount; i++) {
    std::string value;
    s = db_->Get(read_options, "batch_key_" + std::to_string(i), &value);
    ASSERT_TRUE(s.ok()) << s.ToString();
    EXPECT_EQ("batch_val_" + std::to_string(i), value);
  }
}

// Test: Put and Delete in same batch, then write
TEST_F(DBImplWriteTest_313, WritePutThenDeleteSameKey_313) {
  WriteBatch batch;
  batch.Put("pd_key", "pd_value");
  batch.Delete("pd_key");
  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "pd_key", &value);
  ASSERT_TRUE(s.IsNotFound());
}

// Test: Delete then Put in same batch (should end up with the Put value)
TEST_F(DBImplWriteTest_313, WriteDeleteThenPutSameKey_313) {
  // First, write an initial value
  {
    WriteBatch batch;
    batch.Put("dp_key", "initial");
    WriteOptions wo;
    ASSERT_TRUE(db_->Write(wo, &batch).ok());
  }

  WriteBatch batch;
  batch.Delete("dp_key");
  batch.Put("dp_key", "restored");
  WriteOptions write_options;
  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "dp_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("restored", value);
}

// Test: Write after DB reopen persists data
TEST_F(DBImplWriteTest_313, WritePersistsAfterReopen_313) {
  {
    WriteBatch batch;
    batch.Put("persist_key", "persist_value");
    WriteOptions write_options;
    write_options.sync = true;
    Status s = db_->Write(write_options, &batch);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  // Close and reopen
  delete db_;
  db_ = nullptr;
  Status s = DB::Open(options_, dbname_, &db_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "persist_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("persist_value", value);
}

// Test: Write uses Put interface which delegates to Write
TEST_F(DBImplWriteTest_313, PutDelegatesToWrite_313) {
  WriteOptions write_options;
  Status s = db_->Put(write_options, "put_key", "put_value");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "put_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("put_value", value);
}

// Test: Delete interface delegates to Write
TEST_F(DBImplWriteTest_313, DeleteDelegatesToWrite_313) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "del_key", "del_value").ok());

  Status s = db_->Delete(write_options, "del_key");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_options;
  std::string value;
  s = db_->Get(read_options, "del_key", &value);
  ASSERT_TRUE(s.IsNotFound());
}

}  // namespace leveldb
