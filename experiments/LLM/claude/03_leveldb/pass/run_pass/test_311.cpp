#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"
#include "leveldb/iterator.h"
#include "leveldb/env.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>

namespace leveldb {

class DBImplTest_311 : public ::testing::Test {
 protected:
  DB* db_ = nullptr;
  std::string dbname_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "dbimpl_test_311";
    DestroyDB(dbname_, Options());
    Options options;
    options.create_if_missing = true;
    Status s = DB::Open(options, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    db_ = nullptr;
    DestroyDB(dbname_, Options());
  }
};

// Test that opening a database succeeds
TEST_F(DBImplTest_311, OpenDatabase_311) {
  ASSERT_NE(db_, nullptr);
}

// Test basic Put and Get
TEST_F(DBImplTest_311, PutAndGet_311) {
  WriteOptions wo;
  Status s = db_->Put(wo, "key1", "value1");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions ro;
  std::string value;
  s = db_->Get(ro, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "value1");
}

// Test Put overwrites existing key
TEST_F(DBImplTest_311, PutOverwrite_311) {
  WriteOptions wo;
  db_->Put(wo, "key1", "value1");
  db_->Put(wo, "key1", "value2");

  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "value2");
}

// Test Get on non-existent key returns NotFound
TEST_F(DBImplTest_311, GetNonExistentKey_311) {
  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "nonexistent", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test Delete removes a key
TEST_F(DBImplTest_311, DeleteKey_311) {
  WriteOptions wo;
  db_->Put(wo, "key1", "value1");

  Status s = db_->Delete(wo, "key1");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions ro;
  std::string value;
  s = db_->Get(ro, "key1", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test Delete on non-existent key succeeds
TEST_F(DBImplTest_311, DeleteNonExistentKey_311) {
  WriteOptions wo;
  Status s = db_->Delete(wo, "nonexistent");
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test Write with WriteBatch
TEST_F(DBImplTest_311, WriteBatch_311) {
  WriteBatch batch;
  batch.Put("batch_key1", "batch_value1");
  batch.Put("batch_key2", "batch_value2");
  batch.Delete("batch_key1");

  WriteOptions wo;
  Status s = db_->Write(wo, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions ro;
  std::string value;

  s = db_->Get(ro, "batch_key1", &value);
  EXPECT_TRUE(s.IsNotFound());

  s = db_->Get(ro, "batch_key2", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "batch_value2");
}

// Test Write with nullptr WriteBatch (should handle gracefully or succeed)
TEST_F(DBImplTest_311, WriteNullBatch_311) {
  WriteOptions wo;
  Status s = db_->Write(wo, nullptr);
  // A null batch should still succeed (it's treated as a barrier/sync)
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test Put with sync option
TEST_F(DBImplTest_311, PutWithSync_311) {
  WriteOptions wo;
  wo.sync = true;
  Status s = db_->Put(wo, "sync_key", "sync_value");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions ro;
  std::string value;
  s = db_->Get(ro, "sync_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "sync_value");
}

// Test NewIterator basic functionality
TEST_F(DBImplTest_311, NewIterator_311) {
  WriteOptions wo;
  db_->Put(wo, "a", "1");
  db_->Put(wo, "b", "2");
  db_->Put(wo, "c", "3");

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
  ASSERT_NE(it, nullptr);

  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "a");
  EXPECT_EQ(it->value().ToString(), "1");

  it->Next();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "b");
  EXPECT_EQ(it->value().ToString(), "2");

  it->Next();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "c");
  EXPECT_EQ(it->value().ToString(), "3");

  it->Next();
  EXPECT_FALSE(it->Valid());

  delete it;
}

// Test NewIterator SeekToLast
TEST_F(DBImplTest_311, NewIteratorSeekToLast_311) {
  WriteOptions wo;
  db_->Put(wo, "a", "1");
  db_->Put(wo, "b", "2");
  db_->Put(wo, "c", "3");

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
  it->SeekToLast();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "c");
  EXPECT_EQ(it->value().ToString(), "3");

  delete it;
}

// Test NewIterator Seek
TEST_F(DBImplTest_311, NewIteratorSeek_311) {
  WriteOptions wo;
  db_->Put(wo, "a", "1");
  db_->Put(wo, "c", "3");
  db_->Put(wo, "e", "5");

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
  it->Seek("b");
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "c");

  it->Seek("d");
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "e");

  it->Seek("f");
  EXPECT_FALSE(it->Valid());

  delete it;
}

// Test empty iterator
TEST_F(DBImplTest_311, EmptyIterator_311) {
  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
  ASSERT_NE(it, nullptr);
  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());
  delete it;
}

// Test GetSnapshot and ReleaseSnapshot
TEST_F(DBImplTest_311, SnapshotBasic_311) {
  WriteOptions wo;
  db_->Put(wo, "key1", "value1");

  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  db_->Put(wo, "key1", "value2");

  ReadOptions ro;
  ro.snapshot = snap;
  std::string value;
  Status s = db_->Get(ro, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "value1");

  // Without snapshot should see new value
  ReadOptions ro2;
  s = db_->Get(ro2, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "value2");

  db_->ReleaseSnapshot(snap);
}

// Test GetProperty with valid property
TEST_F(DBImplTest_311, GetPropertyNumFilesAtLevel_311) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  EXPECT_TRUE(result);
}

// Test GetProperty with invalid property
TEST_F(DBImplTest_311, GetPropertyInvalid_311) {
  std::string value;
  bool result = db_->GetProperty("leveldb.invalid-property", &value);
  EXPECT_FALSE(result);
}

// Test GetProperty stats
TEST_F(DBImplTest_311, GetPropertyStats_311) {
  std::string value;
  bool result = db_->GetProperty("leveldb.stats", &value);
  EXPECT_TRUE(result);
}

// Test GetApproximateSizes
TEST_F(DBImplTest_311, GetApproximateSizes_311) {
  WriteOptions wo;
  // Insert some data
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    db_->Put(wo, key, val);
  }

  Range range("key0", "key99");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // Size should be non-negative (could be 0 if data hasn't been flushed)
  EXPECT_GE(size, 0u);
}

// Test CompactRange
TEST_F(DBImplTest_311, CompactRange_311) {
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = std::string(1000, 'v');
    db_->Put(wo, key, val);
  }

  db_->CompactRange(nullptr, nullptr);

  // Verify data is still accessible after compaction
  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "key0", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test Put with empty key
TEST_F(DBImplTest_311, PutEmptyKey_311) {
  WriteOptions wo;
  Status s = db_->Put(wo, "", "empty_key_value");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions ro;
  std::string value;
  s = db_->Get(ro, "", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "empty_key_value");
}

// Test Put with empty value
TEST_F(DBImplTest_311, PutEmptyValue_311) {
  WriteOptions wo;
  Status s = db_->Put(wo, "key_empty_val", "");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions ro;
  std::string value;
  s = db_->Get(ro, "key_empty_val", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "");
}

// Test Put with large value
TEST_F(DBImplTest_311, PutLargeValue_311) {
  WriteOptions wo;
  std::string large_value(100000, 'x');
  Status s = db_->Put(wo, "large_key", large_value);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions ro;
  std::string value;
  s = db_->Get(ro, "large_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, large_value);
}

// Test multiple snapshots
TEST_F(DBImplTest_311, MultipleSnapshots_311) {
  WriteOptions wo;
  db_->Put(wo, "key", "v1");
  const Snapshot* snap1 = db_->GetSnapshot();

  db_->Put(wo, "key", "v2");
  const Snapshot* snap2 = db_->GetSnapshot();

  db_->Put(wo, "key", "v3");

  ReadOptions ro1;
  ro1.snapshot = snap1;
  std::string value;
  db_->Get(ro1, "key", &value);
  EXPECT_EQ(value, "v1");

  ReadOptions ro2;
  ro2.snapshot = snap2;
  db_->Get(ro2, "key", &value);
  EXPECT_EQ(value, "v2");

  ReadOptions ro3;
  db_->Get(ro3, "key", &value);
  EXPECT_EQ(value, "v3");

  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap2);
}

// Test opening a database without create_if_missing on non-existent path
TEST_F(DBImplTest_311, OpenWithoutCreateIfMissing_311) {
  // Use a different path
  std::string new_dbname = testing::TempDir() + "dbimpl_test_311_no_create";
  DestroyDB(new_dbname, Options());

  Options options;
  options.create_if_missing = false;
  DB* db = nullptr;
  Status s = DB::Open(options, new_dbname, &db);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(db, nullptr);
}

// Test opening with error_if_exists on existing db
TEST_F(DBImplTest_311, OpenWithErrorIfExists_311) {
  // db_ is already open, close it first
  delete db_;
  db_ = nullptr;

  Options options;
  options.create_if_missing = true;
  options.error_if_exists = true;
  DB* db = nullptr;
  Status s = DB::Open(options, dbname_, &db);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(db, nullptr);

  // Reopen normally for TearDown
  options.error_if_exists = false;
  s = DB::Open(options, dbname_, &db_);
  ASSERT_TRUE(s.ok());
}

// Test iterator Prev
TEST_F(DBImplTest_311, IteratorPrev_311) {
  WriteOptions wo;
  db_->Put(wo, "a", "1");
  db_->Put(wo, "b", "2");
  db_->Put(wo, "c", "3");

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
  it->SeekToLast();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "c");

  it->Prev();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "b");

  it->Prev();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "a");

  it->Prev();
  EXPECT_FALSE(it->Valid());

  delete it;
}

// Test many puts
TEST_F(DBImplTest_311, ManyPuts_311) {
  WriteOptions wo;
  const int kNumEntries = 1000;
  for (int i = 0; i < kNumEntries; i++) {
    char key[100];
    char val[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    Status s = db_->Put(wo, key, val);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  ReadOptions ro;
  for (int i = 0; i < kNumEntries; i++) {
    char key[100];
    char expected_val[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(expected_val, sizeof(expected_val), "val%06d", i);
    std::string value;
    Status s = db_->Get(ro, key, &value);
    ASSERT_TRUE(s.ok()) << s.ToString();
    EXPECT_EQ(value, expected_val);
  }
}

// Test CompactRange with specific range
TEST_F(DBImplTest_311, CompactRangeWithBounds_311) {
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    db_->Put(wo, key, std::string(500, 'v'));
  }

  Slice begin("key000020");
  Slice end("key000080");
  db_->CompactRange(&begin, &end);

  // Verify data integrity after partial compaction
  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "key000050", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test reopen database retains data
TEST_F(DBImplTest_311, ReopenRetainsData_311) {
  WriteOptions wo;
  db_->Put(wo, "persist_key", "persist_value");

  delete db_;
  db_ = nullptr;

  Options options;
  options.create_if_missing = false;
  Status s = DB::Open(options, dbname_, &db_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions ro;
  std::string value;
  s = db_->Get(ro, "persist_key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "persist_value");
}

// Test GetProperty for approximate-memory-usage
TEST_F(DBImplTest_311, GetPropertyApproximateMemoryUsage_311) {
  std::string value;
  bool result = db_->GetProperty("leveldb.approximate-memory-usage", &value);
  EXPECT_TRUE(result);
}

// Test GetApproximateSizes with empty range
TEST_F(DBImplTest_311, GetApproximateSizesEmptyRange_311) {
  Range range("z", "zz");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  EXPECT_EQ(size, 0u);
}

// Test WriteBatch with multiple operations
TEST_F(DBImplTest_311, WriteBatchMultipleOps_311) {
  WriteBatch batch;
  batch.Put("k1", "v1");
  batch.Put("k2", "v2");
  batch.Put("k3", "v3");
  batch.Delete("k2");
  batch.Put("k4", "v4");

  WriteOptions wo;
  Status s = db_->Write(wo, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ReadOptions ro;
  std::string value;

  s = db_->Get(ro, "k1", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "v1");

  s = db_->Get(ro, "k2", &value);
  EXPECT_TRUE(s.IsNotFound());

  s = db_->Get(ro, "k3", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "v3");

  s = db_->Get(ro, "k4", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "v4");
}

// Test that deleting and re-adding a key works correctly
TEST_F(DBImplTest_311, DeleteThenReAdd_311) {
  WriteOptions wo;
  db_->Put(wo, "key", "val1");
  db_->Delete(wo, "key");
  db_->Put(wo, "key", "val2");

  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "key", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "val2");
}

// Test GetProperty for num-files-at-level with different levels
TEST_F(DBImplTest_311, GetPropertyAllLevels_311) {
  for (int level = 0; level < 7; level++) {
    std::string prop = "leveldb.num-files-at-level" + std::to_string(level);
    std::string value;
    bool result = db_->GetProperty(prop, &value);
    EXPECT_TRUE(result) << "Failed for " << prop;
  }
}

}  // namespace leveldb
