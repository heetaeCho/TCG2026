#include <string>
#include <memory>
#include <cstdio>
#include <vector>

#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"
#include "leveldb/status.h"

namespace leveldb {
namespace {

// Helper to create a temporary database directory name
std::string TempDBName(const std::string& suffix) {
  return testing::TempDir() + "/db_impl_test_" + suffix;
}

// Helper to remove directory contents (basic cleanup)
void DestroyDB(const std::string& dbname) {
  Options options;
  leveldb::DestroyDB(dbname, options);
}

class DBImplTest_316 : public ::testing::Test {
 protected:
  std::string dbname_;
  DB* db_;

  void SetUp() override {
    static int counter = 0;
    dbname_ = TempDBName(std::to_string(counter++));
    Options options;
    options.create_if_missing = true;
    Status s = DB::Open(options, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_);
  }
};

// Test that Put followed by Get retrieves the correct value
TEST_F(DBImplTest_316, PutAndGetBasic_316) {
  WriteOptions write_opts;
  Status s = db_->Put(write_opts, "key1", "value1");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("value1", value);
}

// Test that Put overwrites an existing key
TEST_F(DBImplTest_316, PutOverwritesExistingKey_316) {
  WriteOptions write_opts;
  Status s = db_->Put(write_opts, "key1", "value1");
  ASSERT_TRUE(s.ok());

  s = db_->Put(write_opts, "key1", "value2");
  ASSERT_TRUE(s.ok());

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "key1", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("value2", value);
}

// Test Put with empty key
TEST_F(DBImplTest_316, PutEmptyKey_316) {
  WriteOptions write_opts;
  Status s = db_->Put(write_opts, "", "value_empty_key");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("value_empty_key", value);
}

// Test Put with empty value
TEST_F(DBImplTest_316, PutEmptyValue_316) {
  WriteOptions write_opts;
  Status s = db_->Put(write_opts, "key_empty_val", "");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "key_empty_val", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("", value);
}

// Test Put with both empty key and empty value
TEST_F(DBImplTest_316, PutEmptyKeyAndValue_316) {
  WriteOptions write_opts;
  Status s = db_->Put(write_opts, "", "");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("", value);
}

// Test Put with sync option enabled
TEST_F(DBImplTest_316, PutWithSyncOption_316) {
  WriteOptions write_opts;
  write_opts.sync = true;
  Status s = db_->Put(write_opts, "sync_key", "sync_value");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "sync_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("sync_value", value);
}

// Test Put with a large key
TEST_F(DBImplTest_316, PutLargeKey_316) {
  WriteOptions write_opts;
  std::string large_key(1000, 'k');
  Status s = db_->Put(write_opts, large_key, "large_key_value");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, large_key, &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("large_key_value", value);
}

// Test Put with a large value
TEST_F(DBImplTest_316, PutLargeValue_316) {
  WriteOptions write_opts;
  std::string large_value(100000, 'v');
  Status s = db_->Put(write_opts, "large_val_key", large_value);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "large_val_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(large_value, value);
}

// Test multiple Puts with different keys
TEST_F(DBImplTest_316, PutMultipleKeys_316) {
  WriteOptions write_opts;
  const int num_entries = 100;
  for (int i = 0; i < num_entries; i++) {
    std::string key = "key_" + std::to_string(i);
    std::string val = "val_" + std::to_string(i);
    Status s = db_->Put(write_opts, key, val);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  ReadOptions read_opts;
  for (int i = 0; i < num_entries; i++) {
    std::string key = "key_" + std::to_string(i);
    std::string expected_val = "val_" + std::to_string(i);
    std::string value;
    Status s = db_->Get(read_opts, key, &value);
    ASSERT_TRUE(s.ok()) << "Failed to get " << key << ": " << s.ToString();
    EXPECT_EQ(expected_val, value);
  }
}

// Test that Get returns NotFound for a non-existent key
TEST_F(DBImplTest_316, GetNonExistentKey_316) {
  ReadOptions read_opts;
  std::string value;
  Status s = db_->Get(read_opts, "nonexistent_key", &value);
  ASSERT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test Put then Delete then Get returns NotFound
TEST_F(DBImplTest_316, PutThenDeleteThenGet_316) {
  WriteOptions write_opts;
  Status s = db_->Put(write_opts, "del_key", "del_value");
  ASSERT_TRUE(s.ok());

  s = db_->Delete(write_opts, "del_key");
  ASSERT_TRUE(s.ok());

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "del_key", &value);
  ASSERT_TRUE(s.IsNotFound());
}

// Test Put with binary data in key and value
TEST_F(DBImplTest_316, PutBinaryData_316) {
  WriteOptions write_opts;
  std::string binary_key("key\0with\0nulls", 14);
  std::string binary_value("val\0with\0nulls", 14);

  Status s = db_->Put(write_opts, binary_key, binary_value);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, binary_key, &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(binary_value, value);
}

// Test that Put result is visible via NewIterator
TEST_F(DBImplTest_316, PutVisibleViaIterator_316) {
  WriteOptions write_opts;
  Status s = db_->Put(write_opts, "iter_key", "iter_value");
  ASSERT_TRUE(s.ok());

  ReadOptions read_opts;
  Iterator* it = db_->NewIterator(read_opts);
  it->Seek("iter_key");
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("iter_key", it->key().ToString());
  EXPECT_EQ("iter_value", it->value().ToString());
  delete it;
}

// Test that Put with default WriteOptions works (sync = false by default)
TEST_F(DBImplTest_316, PutDefaultWriteOptions_316) {
  WriteOptions write_opts;  // sync defaults to false
  EXPECT_FALSE(write_opts.sync);

  Status s = db_->Put(write_opts, "default_key", "default_value");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "default_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("default_value", value);
}

// Test that Put persists across database close and reopen
TEST_F(DBImplTest_316, PutPersistsAcrossReopen_316) {
  WriteOptions write_opts;
  write_opts.sync = true;
  Status s = db_->Put(write_opts, "persist_key", "persist_value");
  ASSERT_TRUE(s.ok());

  // Close and reopen
  delete db_;
  db_ = nullptr;

  Options options;
  s = DB::Open(options, dbname_, &db_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "persist_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("persist_value", value);
}

// Test multiple overwrites of the same key
TEST_F(DBImplTest_316, PutMultipleOverwrites_316) {
  WriteOptions write_opts;
  std::string key = "overwrite_key";

  for (int i = 0; i < 50; i++) {
    std::string val = "value_" + std::to_string(i);
    Status s = db_->Put(write_opts, key, val);
    ASSERT_TRUE(s.ok());
  }

  ReadOptions read_opts;
  std::string value;
  Status s = db_->Get(read_opts, key, &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("value_49", value);
}

// Test that Write with a WriteBatch containing a single Put
// behaves the same as calling Put directly
TEST_F(DBImplTest_316, WriteWithSinglePutBatch_316) {
  WriteOptions write_opts;
  WriteBatch batch;
  batch.Put("batch_key", "batch_value");
  Status s = db_->Write(write_opts, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "batch_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("batch_value", value);
}

// Test Put with Slice constructed from const char*
TEST_F(DBImplTest_316, PutWithSliceFromCharPtr_316) {
  WriteOptions write_opts;
  const char* key = "char_ptr_key";
  const char* val = "char_ptr_val";
  Status s = db_->Put(write_opts, Slice(key), Slice(val));
  ASSERT_TRUE(s.ok());

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, Slice(key), &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("char_ptr_val", value);
}

// Test that opening a DB at a non-existent path without create_if_missing fails
TEST_F(DBImplTest_316, OpenWithoutCreateIfMissingFails_316) {
  std::string bad_path = TempDBName("nonexistent_open_test");
  DestroyDB(bad_path);

  Options options;
  options.create_if_missing = false;
  DB* db2 = nullptr;
  Status s = DB::Open(options, bad_path, &db2);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(nullptr, db2);
}

}  // namespace
}  // namespace leveldb
