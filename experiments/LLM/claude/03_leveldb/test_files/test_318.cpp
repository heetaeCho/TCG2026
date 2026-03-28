#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

namespace leveldb {

// Helper to get a unique temporary directory for each test
static std::string TempDir() {
  std::string dir;
  Env::Default()->GetTestDirectory(&dir);
  return dir;
}

static std::string RandomDBName(const std::string& prefix) {
  static int counter = 0;
  return TempDir() + "/" + prefix + "_" + std::to_string(counter++);
}

// Helper to destroy a database directory
static void DestroyDB(const std::string& dbname) {
  Options opts;
  leveldb::DestroyDB(dbname, opts);
}

class DBImplTest_318 : public ::testing::Test {
 protected:
  std::string dbname_;
  DB* db_;

  void SetUp() override {
    dbname_ = RandomDBName("dbimpl_test_318");
    db_ = nullptr;
  }

  void TearDown() override {
    delete db_;
    db_ = nullptr;
    DestroyDB(dbname_);
  }

  Status OpenDB(const Options& options) {
    return DB::Open(options, dbname_, &db_);
  }

  Status OpenDB() {
    Options options;
    options.create_if_missing = true;
    return OpenDB(options);
  }
};

// Test: Open a new database with create_if_missing = true succeeds
TEST_F(DBImplTest_318, OpenNewDB_318) {
  Options options;
  options.create_if_missing = true;
  Status s = OpenDB(options);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_NE(db_, nullptr);
}

// Test: Open a non-existent database without create_if_missing fails
TEST_F(DBImplTest_318, OpenNonExistentDBWithoutCreate_318) {
  Options options;
  options.create_if_missing = false;
  Status s = OpenDB(options);
  ASSERT_FALSE(s.ok());
  ASSERT_EQ(db_, nullptr);
}

// Test: Open with error_if_exists on existing database fails
TEST_F(DBImplTest_318, OpenExistingDBWithErrorIfExists_318) {
  Options options;
  options.create_if_missing = true;
  Status s = OpenDB(options);
  ASSERT_TRUE(s.ok());
  delete db_;
  db_ = nullptr;

  options.error_if_exists = true;
  s = OpenDB(options);
  ASSERT_FALSE(s.ok());
  ASSERT_EQ(db_, nullptr);
}

// Test: Basic Put and Get
TEST_F(DBImplTest_318, PutAndGet_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  Status s = db_->Put(wo, "key1", "value1");
  ASSERT_TRUE(s.ok());

  ReadOptions ro;
  std::string value;
  s = db_->Get(ro, "key1", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value1");
}

// Test: Get for non-existent key returns NotFound
TEST_F(DBImplTest_318, GetNonExistentKey_318) {
  ASSERT_TRUE(OpenDB().ok());

  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "nonexistent", &value);
  ASSERT_TRUE(s.IsNotFound());
}

// Test: Delete removes a key
TEST_F(DBImplTest_318, DeleteKey_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "key1", "value1").ok());

  ASSERT_TRUE(db_->Delete(wo, "key1").ok());

  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "key1", &value);
  ASSERT_TRUE(s.IsNotFound());
}

// Test: Delete non-existent key succeeds (no error)
TEST_F(DBImplTest_318, DeleteNonExistentKey_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  Status s = db_->Delete(wo, "nonexistent");
  ASSERT_TRUE(s.ok());
}

// Test: WriteBatch with multiple operations
TEST_F(DBImplTest_318, WriteBatch_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteBatch batch;
  batch.Put("key1", "value1");
  batch.Put("key2", "value2");
  batch.Put("key3", "value3");
  batch.Delete("key2");

  WriteOptions wo;
  Status s = db_->Write(wo, &batch);
  ASSERT_TRUE(s.ok());

  ReadOptions ro;
  std::string value;

  s = db_->Get(ro, "key1", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value1");

  s = db_->Get(ro, "key2", &value);
  ASSERT_TRUE(s.IsNotFound());

  s = db_->Get(ro, "key3", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value3");
}

// Test: Overwrite existing key
TEST_F(DBImplTest_318, OverwriteKey_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "key1", "value1").ok());
  ASSERT_TRUE(db_->Put(wo, "key1", "value2").ok());

  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "key1", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value2");
}

// Test: Iterator basic functionality
TEST_F(DBImplTest_318, IteratorBasic_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "a", "1").ok());
  ASSERT_TRUE(db_->Put(wo, "b", "2").ok());
  ASSERT_TRUE(db_->Put(wo, "c", "3").ok());

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
  ASSERT_NE(it, nullptr);

  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());
  ASSERT_EQ(it->key().ToString(), "a");
  ASSERT_EQ(it->value().ToString(), "1");

  it->Next();
  ASSERT_TRUE(it->Valid());
  ASSERT_EQ(it->key().ToString(), "b");
  ASSERT_EQ(it->value().ToString(), "2");

  it->Next();
  ASSERT_TRUE(it->Valid());
  ASSERT_EQ(it->key().ToString(), "c");
  ASSERT_EQ(it->value().ToString(), "3");

  it->Next();
  ASSERT_FALSE(it->Valid());

  delete it;
}

// Test: Iterator on empty database
TEST_F(DBImplTest_318, IteratorEmpty_318) {
  ASSERT_TRUE(OpenDB().ok());

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
  ASSERT_NE(it, nullptr);

  it->SeekToFirst();
  ASSERT_FALSE(it->Valid());

  it->SeekToLast();
  ASSERT_FALSE(it->Valid());

  delete it;
}

// Test: Iterator SeekToLast and reverse iteration
TEST_F(DBImplTest_318, IteratorReverse_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "a", "1").ok());
  ASSERT_TRUE(db_->Put(wo, "b", "2").ok());
  ASSERT_TRUE(db_->Put(wo, "c", "3").ok());

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);

  it->SeekToLast();
  ASSERT_TRUE(it->Valid());
  ASSERT_EQ(it->key().ToString(), "c");

  it->Prev();
  ASSERT_TRUE(it->Valid());
  ASSERT_EQ(it->key().ToString(), "b");

  it->Prev();
  ASSERT_TRUE(it->Valid());
  ASSERT_EQ(it->key().ToString(), "a");

  it->Prev();
  ASSERT_FALSE(it->Valid());

  delete it;
}

// Test: Snapshot isolation
TEST_F(DBImplTest_318, SnapshotIsolation_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "key1", "value1").ok());

  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  ASSERT_TRUE(db_->Put(wo, "key1", "value2").ok());

  ReadOptions ro;
  ro.snapshot = snap;
  std::string value;
  Status s = db_->Get(ro, "key1", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value1");

  // Without snapshot, should see latest value
  ReadOptions ro2;
  s = db_->Get(ro2, "key1", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value2");

  db_->ReleaseSnapshot(snap);
}

// Test: GetProperty for valid properties
TEST_F(DBImplTest_318, GetPropertyNumFilesAtLevel_318) {
  ASSERT_TRUE(OpenDB().ok());

  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  ASSERT_TRUE(result);

  result = db_->GetProperty("leveldb.stats", &value);
  ASSERT_TRUE(result);
}

// Test: GetProperty for invalid property returns false
TEST_F(DBImplTest_318, GetPropertyInvalid_318) {
  ASSERT_TRUE(OpenDB().ok());

  std::string value;
  bool result = db_->GetProperty("invalid.property", &value);
  ASSERT_FALSE(result);
}

// Test: GetApproximateSizes
TEST_F(DBImplTest_318, GetApproximateSizes_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  // Write some data
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val(1000, 'v');
    ASSERT_TRUE(db_->Put(wo, key, val).ok());
  }

  Range range("key0", "key99");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // We just check it doesn't crash; size can be 0 if data is in memtable
  ASSERT_GE(size, 0u);
}

// Test: Reopen database preserves data
TEST_F(DBImplTest_318, ReopenPreservesData_318) {
  {
    Options options;
    options.create_if_missing = true;
    ASSERT_TRUE(OpenDB(options).ok());

    WriteOptions wo;
    ASSERT_TRUE(db_->Put(wo, "persist_key", "persist_value").ok());

    delete db_;
    db_ = nullptr;
  }

  {
    Options options;
    ASSERT_TRUE(OpenDB(options).ok());

    ReadOptions ro;
    std::string value;
    Status s = db_->Get(ro, "persist_key", &value);
    ASSERT_TRUE(s.ok());
    ASSERT_EQ(value, "persist_value");
  }
}

// Test: Write with nullptr WriteBatch (null updates)
TEST_F(DBImplTest_318, WriteNullBatch_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  Status s = db_->Write(wo, nullptr);
  ASSERT_TRUE(s.ok());
}

// Test: Empty key and value
TEST_F(DBImplTest_318, EmptyKeyAndValue_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "", "").ok());

  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "");
}

// Test: Large value
TEST_F(DBImplTest_318, LargeValue_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  std::string large_value(100000, 'x');
  ASSERT_TRUE(db_->Put(wo, "large_key", large_value).ok());

  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "large_key", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, large_value);
}

// Test: Many keys
TEST_F(DBImplTest_318, ManyKeys_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ReadOptions ro;
  const int kNumKeys = 1000;

  for (int i = 0; i < kNumKeys; i++) {
    char key[100], val[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    ASSERT_TRUE(db_->Put(wo, key, val).ok());
  }

  for (int i = 0; i < kNumKeys; i++) {
    char key[100], expected_val[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(expected_val, sizeof(expected_val), "val%06d", i);
    std::string value;
    Status s = db_->Get(ro, key, &value);
    ASSERT_TRUE(s.ok()) << "Failed to get " << key;
    ASSERT_EQ(value, expected_val);
  }
}

// Test: Iterator Seek
TEST_F(DBImplTest_318, IteratorSeek_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "a", "1").ok());
  ASSERT_TRUE(db_->Put(wo, "c", "3").ok());
  ASSERT_TRUE(db_->Put(wo, "e", "5").ok());

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);

  it->Seek("b");
  ASSERT_TRUE(it->Valid());
  ASSERT_EQ(it->key().ToString(), "c");

  it->Seek("d");
  ASSERT_TRUE(it->Valid());
  ASSERT_EQ(it->key().ToString(), "e");

  it->Seek("f");
  ASSERT_FALSE(it->Valid());

  delete it;
}

// Test: CompactRange doesn't crash
TEST_F(DBImplTest_318, CompactRange_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(wo, key, std::string(100, 'v')).ok());
  }

  // Compact entire range
  db_->CompactRange(nullptr, nullptr);

  // Verify data still accessible
  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "key50", &value);
  ASSERT_TRUE(s.ok());
}

// Test: Multiple snapshots
TEST_F(DBImplTest_318, MultipleSnapshots_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "key", "v1").ok());
  const Snapshot* snap1 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(wo, "key", "v2").ok());
  const Snapshot* snap2 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(wo, "key", "v3").ok());

  ReadOptions ro1;
  ro1.snapshot = snap1;
  std::string value;
  ASSERT_TRUE(db_->Get(ro1, "key", &value).ok());
  ASSERT_EQ(value, "v1");

  ReadOptions ro2;
  ro2.snapshot = snap2;
  ASSERT_TRUE(db_->Get(ro2, "key", &value).ok());
  ASSERT_EQ(value, "v2");

  ReadOptions ro3;
  ASSERT_TRUE(db_->Get(ro3, "key", &value).ok());
  ASSERT_EQ(value, "v3");

  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap2);
}

// Test: Sync write option
TEST_F(DBImplTest_318, SyncWrite_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  wo.sync = true;
  Status s = db_->Put(wo, "sync_key", "sync_value");
  ASSERT_TRUE(s.ok());

  ReadOptions ro;
  std::string value;
  s = db_->Get(ro, "sync_key", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "sync_value");
}

// Test: dbptr is set to nullptr on failure
TEST_F(DBImplTest_318, DbPtrNullOnFailure_318) {
  DB* dbptr = reinterpret_cast<DB*>(0x1234);  // non-null sentinel
  Options options;
  options.create_if_missing = false;
  std::string nonexistent = TempDir() + "/nonexistent_db_318_xyz";
  Status s = DB::Open(options, nonexistent, &dbptr);
  ASSERT_FALSE(s.ok());
  ASSERT_EQ(dbptr, nullptr);
}

// Test: Put after delete returns the new value
TEST_F(DBImplTest_318, PutAfterDelete_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "key", "v1").ok());
  ASSERT_TRUE(db_->Delete(wo, "key").ok());
  ASSERT_TRUE(db_->Put(wo, "key", "v2").ok());

  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "key", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "v2");
}

// Test: Iterator counts correct number of entries
TEST_F(DBImplTest_318, IteratorCount_318) {
  ASSERT_TRUE(OpenDB().ok());

  WriteOptions wo;
  const int kCount = 50;
  for (int i = 0; i < kCount; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%04d", i);
    ASSERT_TRUE(db_->Put(wo, key, "val").ok());
  }

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
  int count = 0;
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    count++;
  }
  ASSERT_EQ(count, kCount);
  ASSERT_TRUE(it->status().ok());
  delete it;
}

}  // namespace leveldb
