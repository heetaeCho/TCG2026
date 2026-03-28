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
std::string TempDBPath(const std::string& suffix) {
  return testing::TempDir() + "/db_impl_test_317_" + suffix;
}

// Helper to recursively remove a directory (simple approach)
void DestroyDB(const std::string& dbname) {
  Options options;
  leveldb::DestroyDB(dbname, options);
}

class DBImplTest_317 : public ::testing::Test {
 protected:
  void SetUp() override {
    dbname_ = TempDBPath("main");
    DestroyDB(dbname_);
    Options options;
    options.create_if_missing = true;
    Status s = DB::Open(options, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_);
  }

  DB* db_ = nullptr;
  std::string dbname_;
};

// Test that Delete removes an existing key so that Get returns NotFound
TEST_F(DBImplTest_317, DeleteExistingKey_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  // Put a key first
  Status s = db_->Put(write_opts, "key1", "value1");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify the key exists
  std::string value;
  s = db_->Get(read_opts, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("value1", value);

  // Delete the key
  s = db_->Delete(write_opts, "key1");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify the key is gone
  s = db_->Get(read_opts, "key1", &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test that Delete on a non-existing key succeeds (no error)
TEST_F(DBImplTest_317, DeleteNonExistingKey_317) {
  WriteOptions write_opts;
  Status s = db_->Delete(write_opts, "nonexistent_key");
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test that Delete with sync option works correctly
TEST_F(DBImplTest_317, DeleteWithSyncOption_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  // Put a key first
  Status s = db_->Put(write_opts, "sync_key", "sync_value");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Delete with sync = true
  WriteOptions sync_opts;
  sync_opts.sync = true;
  s = db_->Delete(sync_opts, "sync_key");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify the key is deleted
  std::string value;
  s = db_->Get(read_opts, "sync_key", &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test deleting an empty string key
TEST_F(DBImplTest_317, DeleteEmptyKey_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  // Put an empty key
  Status s = db_->Put(write_opts, "", "empty_key_value");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify it exists
  std::string value;
  s = db_->Get(read_opts, "", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("empty_key_value", value);

  // Delete the empty key
  s = db_->Delete(write_opts, "");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify it's gone
  s = db_->Get(read_opts, "", &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test deleting the same key multiple times
TEST_F(DBImplTest_317, DeleteSameKeyMultipleTimes_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  // Put a key
  Status s = db_->Put(write_opts, "multi_del", "value");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Delete multiple times - all should succeed
  for (int i = 0; i < 5; i++) {
    s = db_->Delete(write_opts, "multi_del");
    EXPECT_TRUE(s.ok()) << "Delete iteration " << i << ": " << s.ToString();
  }

  // Verify key is deleted
  std::string value;
  s = db_->Get(read_opts, "multi_del", &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test that Delete only affects the specified key and not others
TEST_F(DBImplTest_317, DeleteDoesNotAffectOtherKeys_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  // Put multiple keys
  ASSERT_TRUE(db_->Put(write_opts, "key_a", "value_a").ok());
  ASSERT_TRUE(db_->Put(write_opts, "key_b", "value_b").ok());
  ASSERT_TRUE(db_->Put(write_opts, "key_c", "value_c").ok());

  // Delete only key_b
  Status s = db_->Delete(write_opts, "key_b");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify key_a and key_c still exist
  std::string value;
  s = db_->Get(read_opts, "key_a", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("value_a", value);

  s = db_->Get(read_opts, "key_c", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("value_c", value);

  // Verify key_b is gone
  s = db_->Get(read_opts, "key_b", &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test Put after Delete re-inserts the key
TEST_F(DBImplTest_317, PutAfterDelete_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  // Put, Delete, then Put again
  ASSERT_TRUE(db_->Put(write_opts, "reinsert", "first").ok());
  ASSERT_TRUE(db_->Delete(write_opts, "reinsert").ok());
  ASSERT_TRUE(db_->Put(write_opts, "reinsert", "second").ok());

  std::string value;
  Status s = db_->Get(read_opts, "reinsert", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("second", value);
}

// Test Delete with a large key
TEST_F(DBImplTest_317, DeleteLargeKey_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  std::string large_key(10000, 'x');
  ASSERT_TRUE(db_->Put(write_opts, large_key, "large_key_value").ok());

  // Verify the key exists
  std::string value;
  Status s = db_->Get(read_opts, large_key, &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("large_key_value", value);

  // Delete the large key
  s = db_->Delete(write_opts, large_key);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify the key is deleted
  s = db_->Get(read_opts, large_key, &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test that Delete is visible through an iterator
TEST_F(DBImplTest_317, DeleteVisibleThroughIterator_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  ASSERT_TRUE(db_->Put(write_opts, "iter_key1", "v1").ok());
  ASSERT_TRUE(db_->Put(write_opts, "iter_key2", "v2").ok());
  ASSERT_TRUE(db_->Put(write_opts, "iter_key3", "v3").ok());

  // Delete key2
  ASSERT_TRUE(db_->Delete(write_opts, "iter_key2").ok());

  // Iterate and collect keys
  std::vector<std::string> keys;
  Iterator* it = db_->NewIterator(read_opts);
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    keys.push_back(it->key().ToString());
  }
  ASSERT_TRUE(it->status().ok());
  delete it;

  // Should have key1 and key3 but not key2
  EXPECT_EQ(2u, keys.size());
  EXPECT_EQ("iter_key1", keys[0]);
  EXPECT_EQ("iter_key3", keys[1]);
}

// Test Delete with binary data in key
TEST_F(DBImplTest_317, DeleteBinaryKey_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  // Create a key with embedded null bytes
  std::string binary_key("key\0with\0nulls", 14);
  ASSERT_TRUE(db_->Put(write_opts, binary_key, "binary_value").ok());

  std::string value;
  Status s = db_->Get(read_opts, binary_key, &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("binary_value", value);

  s = db_->Delete(write_opts, binary_key);
  ASSERT_TRUE(s.ok()) << s.ToString();

  s = db_->Get(read_opts, binary_key, &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test that snapshot taken before delete still sees the key
TEST_F(DBImplTest_317, DeleteWithSnapshot_317) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  ASSERT_TRUE(db_->Put(write_opts, "snap_key", "snap_value").ok());

  // Take a snapshot before delete
  const Snapshot* snapshot = db_->GetSnapshot();
  ASSERT_NE(nullptr, snapshot);

  // Delete the key
  ASSERT_TRUE(db_->Delete(write_opts, "snap_key").ok());

  // Read with snapshot should still see the key
  ReadOptions snap_read_opts;
  snap_read_opts.snapshot = snapshot;
  std::string value;
  Status s = db_->Get(snap_read_opts, "snap_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("snap_value", value);

  // Read without snapshot should not see the key
  s = db_->Get(read_opts, "snap_key", &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();

  db_->ReleaseSnapshot(snapshot);
}

}  // namespace
}  // namespace leveldb
