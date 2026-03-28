#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "leveldb/write_batch.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <filesystem>

namespace leveldb {

class DBImplGetTest_306 : public ::testing::Test {
 protected:
  DB* db_;
  std::string dbname_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "/db_impl_get_test_306";
    DestroyDB(dbname_, Options());
    options_.create_if_missing = true;
    ASSERT_TRUE(DB::Open(options_, dbname_, &db_).ok());
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, Options());
  }
};

// Test: Get on a key that does not exist should return NotFound
TEST_F(DBImplGetTest_306, GetNonExistentKeyReturnsNotFound_306) {
  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, "nonexistent_key", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Get a key that was previously Put
TEST_F(DBImplGetTest_306, GetExistingKeyReturnsValue_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "key1", "value1").ok());

  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, "key1", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);
}

// Test: Get returns the latest value after multiple Puts to the same key
TEST_F(DBImplGetTest_306, GetReturnsLatestValueAfterUpdate_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "key1", "value1").ok());
  ASSERT_TRUE(db_->Put(write_options, "key1", "value2").ok());
  ASSERT_TRUE(db_->Put(write_options, "key1", "value3").ok());

  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, "key1", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value3", value);
}

// Test: Get returns NotFound after a key is deleted
TEST_F(DBImplGetTest_306, GetAfterDeleteReturnsNotFound_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "key1", "value1").ok());

  ASSERT_TRUE(db_->Delete(write_options, "key1").ok());

  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, "key1", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Get with snapshot reads old value
TEST_F(DBImplGetTest_306, GetWithSnapshotReadsOldValue_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "key1", "value1").ok());

  const Snapshot* snapshot = db_->GetSnapshot();
  ASSERT_NE(snapshot, nullptr);

  ASSERT_TRUE(db_->Put(write_options, "key1", "value2").ok());

  ReadOptions read_options;
  read_options.snapshot = snapshot;
  std::string value;
  Status s = db_->Get(read_options, "key1", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);

  // Without snapshot, should see the new value
  ReadOptions read_options_no_snap;
  s = db_->Get(read_options_no_snap, "key1", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value2", value);

  db_->ReleaseSnapshot(snapshot);
}

// Test: Get with snapshot where key was deleted after snapshot
TEST_F(DBImplGetTest_306, GetWithSnapshotAfterDelete_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "key1", "value1").ok());

  const Snapshot* snapshot = db_->GetSnapshot();
  ASSERT_NE(snapshot, nullptr);

  ASSERT_TRUE(db_->Delete(write_options, "key1").ok());

  ReadOptions read_options;
  read_options.snapshot = snapshot;
  std::string value;
  Status s = db_->Get(read_options, "key1", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);

  // Without snapshot, key should be gone
  ReadOptions read_options_no_snap;
  s = db_->Get(read_options_no_snap, "key1", &value);
  EXPECT_TRUE(s.IsNotFound());

  db_->ReleaseSnapshot(snapshot);
}

// Test: Get with empty key
TEST_F(DBImplGetTest_306, GetWithEmptyKey_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "", "empty_key_value").ok());

  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, "", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("empty_key_value", value);
}

// Test: Get with empty value
TEST_F(DBImplGetTest_306, GetWithEmptyValue_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "key_empty_val", "").ok());

  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, "key_empty_val", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("", value);
}

// Test: Get with large key and value
TEST_F(DBImplGetTest_306, GetWithLargeKeyAndValue_306) {
  WriteOptions write_options;
  std::string large_key(1000, 'k');
  std::string large_value(100000, 'v');
  ASSERT_TRUE(db_->Put(write_options, large_key, large_value).ok());

  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, large_key, &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(large_value, value);
}

// Test: Get multiple distinct keys
TEST_F(DBImplGetTest_306, GetMultipleDistinctKeys_306) {
  WriteOptions write_options;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_options, key, val).ok());
  }

  ReadOptions read_options;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_val = "val" + std::to_string(i);
    std::string value;
    Status s = db_->Get(read_options, key, &value);
    EXPECT_TRUE(s.ok());
    EXPECT_EQ(expected_val, value);
  }
}

// Test: Get after compaction still returns correct value
TEST_F(DBImplGetTest_306, GetAfterCompactionReturnsCorrectValue_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "compact_key", "compact_value").ok());

  // Force compaction
  db_->CompactRange(nullptr, nullptr);

  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, "compact_key", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("compact_value", value);
}

// Test: Get with snapshot that doesn't have the key
TEST_F(DBImplGetTest_306, GetWithSnapshotBeforeKeyInsert_306) {
  const Snapshot* snapshot = db_->GetSnapshot();
  ASSERT_NE(snapshot, nullptr);

  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "new_key", "new_value").ok());

  ReadOptions read_options;
  read_options.snapshot = snapshot;
  std::string value;
  Status s = db_->Get(read_options, "new_key", &value);
  EXPECT_TRUE(s.IsNotFound());

  db_->ReleaseSnapshot(snapshot);
}

// Test: Get after WriteBatch with multiple operations
TEST_F(DBImplGetTest_306, GetAfterWriteBatch_306) {
  WriteBatch batch;
  batch.Put("batch_key1", "batch_value1");
  batch.Put("batch_key2", "batch_value2");
  batch.Delete("batch_key1");

  WriteOptions write_options;
  ASSERT_TRUE(db_->Write(write_options, &batch).ok());

  ReadOptions read_options;
  std::string value;

  Status s = db_->Get(read_options, "batch_key1", &value);
  EXPECT_TRUE(s.IsNotFound());

  s = db_->Get(read_options, "batch_key2", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("batch_value2", value);
}

// Test: Get with verify_checksums option
TEST_F(DBImplGetTest_306, GetWithVerifyChecksums_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "check_key", "check_value").ok());

  // Force data to SST files
  db_->CompactRange(nullptr, nullptr);

  ReadOptions read_options;
  read_options.verify_checksums = true;
  std::string value;
  Status s = db_->Get(read_options, "check_key", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("check_value", value);
}

// Test: Get with fill_cache = false
TEST_F(DBImplGetTest_306, GetWithFillCacheFalse_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "cache_key", "cache_value").ok());

  // Force data to SST files
  db_->CompactRange(nullptr, nullptr);

  ReadOptions read_options;
  read_options.fill_cache = false;
  std::string value;
  Status s = db_->Get(read_options, "cache_key", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("cache_value", value);
}

// Test: Get after DB reopen returns persisted data
TEST_F(DBImplGetTest_306, GetAfterReopenReturnsPersisted_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "persist_key", "persist_value").ok());

  delete db_;
  db_ = nullptr;

  Options options;
  options.create_if_missing = false;
  ASSERT_TRUE(DB::Open(options, dbname_, &db_).ok());

  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, "persist_key", &value);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("persist_value", value);
}

// Test: Overwrite a key, take snapshot, overwrite again, verify snapshot reads middle value
TEST_F(DBImplGetTest_306, GetSnapshotMiddleVersion_306) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "skey", "v1").ok());
  ASSERT_TRUE(db_->Put(write_options, "skey", "v2").ok());

  const Snapshot* snap = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(write_options, "skey", "v3").ok());

  ReadOptions ro;
  ro.snapshot = snap;
  std::string value;
  EXPECT_TRUE(db_->Get(ro, "skey", &value).ok());
  EXPECT_EQ("v2", value);

  ReadOptions ro2;
  EXPECT_TRUE(db_->Get(ro2, "skey", &value).ok());
  EXPECT_EQ("v3", value);

  db_->ReleaseSnapshot(snap);
}

}  // namespace leveldb
