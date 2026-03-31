#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"
#include "leveldb/iterator.h"
#include "db/db_impl.h"

#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <filesystem>

namespace leveldb {

class DBImplTest_312 : public ::testing::Test {
 protected:
  DB* db_ = nullptr;
  std::string dbname_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "/dbimpl_test_312";
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

// Test: Delete a key that was previously Put
TEST_F(DBImplTest_312, DeleteExistingKey_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  // Put a key
  Status s = db_->Put(write_opts, "key1", "value1");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify key exists
  std::string value;
  s = db_->Get(read_opts, "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("value1", value);

  // Delete the key
  s = db_->Delete(write_opts, "key1");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify key no longer exists
  s = db_->Get(read_opts, "key1", &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test: Delete a key that does not exist (should still succeed)
TEST_F(DBImplTest_312, DeleteNonExistingKey_312) {
  WriteOptions write_opts;
  Status s = db_->Delete(write_opts, "nonexistent_key");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify it's not found
  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "nonexistent_key", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Delete with sync option
TEST_F(DBImplTest_312, DeleteWithSyncOption_312) {
  WriteOptions write_opts;
  write_opts.sync = true;

  // Put a key first
  Status s = db_->Put(WriteOptions(), "synckey", "syncvalue");
  ASSERT_TRUE(s.ok());

  // Delete with sync
  s = db_->Delete(write_opts, "synckey");
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify deletion
  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "synckey", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Delete an empty key
TEST_F(DBImplTest_312, DeleteEmptyKey_312) {
  WriteOptions write_opts;

  // Put with empty key
  Status s = db_->Put(write_opts, "", "emptyvalue");
  ASSERT_TRUE(s.ok());

  // Delete empty key
  s = db_->Delete(write_opts, "");
  ASSERT_TRUE(s.ok());

  // Verify
  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Delete same key multiple times
TEST_F(DBImplTest_312, DeleteSameKeyMultipleTimes_312) {
  WriteOptions write_opts;

  Status s = db_->Put(write_opts, "multikey", "value");
  ASSERT_TRUE(s.ok());

  // Delete multiple times
  s = db_->Delete(write_opts, "multikey");
  ASSERT_TRUE(s.ok());

  s = db_->Delete(write_opts, "multikey");
  ASSERT_TRUE(s.ok());

  s = db_->Delete(write_opts, "multikey");
  ASSERT_TRUE(s.ok());

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "multikey", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Put after Delete restores the key
TEST_F(DBImplTest_312, PutAfterDelete_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  Status s = db_->Put(write_opts, "key2", "value2");
  ASSERT_TRUE(s.ok());

  s = db_->Delete(write_opts, "key2");
  ASSERT_TRUE(s.ok());

  s = db_->Put(write_opts, "key2", "newvalue2");
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(read_opts, "key2", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("newvalue2", value);
}

// Test: Delete does not affect other keys
TEST_F(DBImplTest_312, DeleteDoesNotAffectOtherKeys_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  Status s = db_->Put(write_opts, "keyA", "valueA");
  ASSERT_TRUE(s.ok());
  s = db_->Put(write_opts, "keyB", "valueB");
  ASSERT_TRUE(s.ok());
  s = db_->Put(write_opts, "keyC", "valueC");
  ASSERT_TRUE(s.ok());

  // Delete only keyB
  s = db_->Delete(write_opts, "keyB");
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(read_opts, "keyA", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("valueA", value);

  s = db_->Get(read_opts, "keyB", &value);
  EXPECT_TRUE(s.IsNotFound());

  s = db_->Get(read_opts, "keyC", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("valueC", value);
}

// Test: Delete with a large key
TEST_F(DBImplTest_312, DeleteLargeKey_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  std::string large_key(1000, 'x');
  Status s = db_->Put(write_opts, large_key, "largevalue");
  ASSERT_TRUE(s.ok());

  s = db_->Delete(write_opts, large_key);
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(read_opts, large_key, &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Delete is visible through iterator
TEST_F(DBImplTest_312, DeleteVisibleThroughIterator_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  Status s = db_->Put(write_opts, "iter1", "val1");
  ASSERT_TRUE(s.ok());
  s = db_->Put(write_opts, "iter2", "val2");
  ASSERT_TRUE(s.ok());
  s = db_->Put(write_opts, "iter3", "val3");
  ASSERT_TRUE(s.ok());

  // Delete iter2
  s = db_->Delete(write_opts, "iter2");
  ASSERT_TRUE(s.ok());

  // Iterate and verify iter2 is gone
  Iterator* it = db_->NewIterator(read_opts);
  std::vector<std::string> keys;
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    keys.push_back(it->key().ToString());
  }
  ASSERT_TRUE(it->status().ok());
  delete it;

  EXPECT_EQ(2u, keys.size());
  EXPECT_EQ("iter1", keys[0]);
  EXPECT_EQ("iter3", keys[1]);
}

// Test: Delete is visible in snapshot taken after delete
TEST_F(DBImplTest_312, DeleteVisibleAfterSnapshot_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  Status s = db_->Put(write_opts, "snapkey", "snapval");
  ASSERT_TRUE(s.ok());

  // Take snapshot before delete
  const Snapshot* snap = db_->GetSnapshot();

  s = db_->Delete(write_opts, "snapkey");
  ASSERT_TRUE(s.ok());

  // Reading at snapshot should still see the key
  ReadOptions snap_read_opts;
  snap_read_opts.snapshot = snap;
  std::string value;
  s = db_->Get(snap_read_opts, "snapkey", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("snapval", value);

  // Reading without snapshot should not see the key
  s = db_->Get(read_opts, "snapkey", &value);
  EXPECT_TRUE(s.IsNotFound());

  db_->ReleaseSnapshot(snap);
}

// Test: Multiple deletes of different keys
TEST_F(DBImplTest_312, DeleteMultipleDifferentKeys_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    Status s = db_->Put(write_opts, key, val);
    ASSERT_TRUE(s.ok());
  }

  // Delete even keys
  for (int i = 0; i < 100; i += 2) {
    std::string key = "key" + std::to_string(i);
    Status s = db_->Delete(write_opts, key);
    ASSERT_TRUE(s.ok());
  }

  // Verify even keys are gone, odd keys remain
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value;
    Status s = db_->Get(read_opts, key, &value);
    if (i % 2 == 0) {
      EXPECT_TRUE(s.IsNotFound()) << "Key " << key << " should be deleted";
    } else {
      ASSERT_TRUE(s.ok()) << "Key " << key << " should exist";
      EXPECT_EQ("val" + std::to_string(i), value);
    }
  }
}

// Test: Delete with key containing special characters
TEST_F(DBImplTest_312, DeleteKeyWithSpecialChars_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  std::string special_key = std::string("\x00\x01\x02\xff", 4);
  Status s = db_->Put(write_opts, special_key, "special_value");
  ASSERT_TRUE(s.ok());

  s = db_->Delete(write_opts, special_key);
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(read_opts, special_key, &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Put method works correctly
TEST_F(DBImplTest_312, PutBasic_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  Status s = db_->Put(write_opts, "hello", "world");
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(read_opts, "hello", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("world", value);
}

// Test: Put overwrites existing value
TEST_F(DBImplTest_312, PutOverwrite_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  Status s = db_->Put(write_opts, "overkey", "first");
  ASSERT_TRUE(s.ok());

  s = db_->Put(write_opts, "overkey", "second");
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(read_opts, "overkey", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("second", value);
}

// Test: Get on non-existing key returns NotFound
TEST_F(DBImplTest_312, GetNonExisting_312) {
  ReadOptions read_opts;
  std::string value;
  Status s = db_->Get(read_opts, "no_such_key", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: GetProperty returns something for known properties
TEST_F(DBImplTest_312, GetPropertyNumFilesAtLevel_312) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  EXPECT_TRUE(result);
}

// Test: GetProperty returns false for unknown property
TEST_F(DBImplTest_312, GetPropertyUnknown_312) {
  std::string value;
  bool result = db_->GetProperty("leveldb.unknown-property", &value);
  EXPECT_FALSE(result);
}

// Test: GetApproximateSizes returns zero for empty range
TEST_F(DBImplTest_312, GetApproximateSizesEmpty_312) {
  Range range("a", "z");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // Empty database should have approximately 0 size
  EXPECT_EQ(0u, size);
}

// Test: Snapshot lifecycle
TEST_F(DBImplTest_312, SnapshotLifecycle_312) {
  const Snapshot* snap1 = db_->GetSnapshot();
  ASSERT_NE(nullptr, snap1);

  const Snapshot* snap2 = db_->GetSnapshot();
  ASSERT_NE(nullptr, snap2);

  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap2);
}

// Test: NewIterator on empty database
TEST_F(DBImplTest_312, NewIteratorEmptyDB_312) {
  ReadOptions read_opts;
  Iterator* it = db_->NewIterator(read_opts);
  ASSERT_NE(nullptr, it);

  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());

  it->SeekToLast();
  EXPECT_FALSE(it->Valid());

  delete it;
}

// Test: Write with WriteBatch
TEST_F(DBImplTest_312, WriteBatchPutAndDelete_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  WriteBatch batch;
  batch.Put("batchkey1", "batchval1");
  batch.Put("batchkey2", "batchval2");
  batch.Delete("batchkey1");

  Status s = db_->Write(write_opts, &batch);
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(read_opts, "batchkey1", &value);
  EXPECT_TRUE(s.IsNotFound());

  s = db_->Get(read_opts, "batchkey2", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("batchval2", value);
}

// Test: Write with nullptr batch
TEST_F(DBImplTest_312, WriteNullBatch_312) {
  WriteOptions write_opts;
  Status s = db_->Write(write_opts, nullptr);
  // Writing a null batch should succeed (it's treated as an empty write)
  ASSERT_TRUE(s.ok());
}

// Test: CompactRange on full range
TEST_F(DBImplTest_312, CompactRangeFull_312) {
  WriteOptions write_opts;

  for (int i = 0; i < 100; i++) {
    std::string key = "compact_key" + std::to_string(i);
    std::string val = "compact_val" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_opts, key, val).ok());
  }

  // Compact full range
  db_->CompactRange(nullptr, nullptr);

  // Verify data still intact
  ReadOptions read_opts;
  std::string value;
  Status s = db_->Get(read_opts, "compact_key50", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("compact_val50", value);
}

// Test: Open DB that already exists
TEST_F(DBImplTest_312, ReopenDB_312) {
  WriteOptions write_opts;
  Status s = db_->Put(write_opts, "persist_key", "persist_val");
  ASSERT_TRUE(s.ok());

  // Close current DB
  delete db_;
  db_ = nullptr;

  // Reopen
  Options options;
  s = DB::Open(options, dbname_, &db_);
  ASSERT_TRUE(s.ok());

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "persist_key", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("persist_val", value);
}

// Test: Delete persists across reopen
TEST_F(DBImplTest_312, DeletePersistsAcrossReopen_312) {
  WriteOptions write_opts;
  Status s = db_->Put(write_opts, "delkey", "delval");
  ASSERT_TRUE(s.ok());

  s = db_->Delete(write_opts, "delkey");
  ASSERT_TRUE(s.ok());

  // Close and reopen
  delete db_;
  db_ = nullptr;

  Options options;
  s = DB::Open(options, dbname_, &db_);
  ASSERT_TRUE(s.ok());

  ReadOptions read_opts;
  std::string value;
  s = db_->Get(read_opts, "delkey", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Open with create_if_missing=false on non-existing DB fails
TEST_F(DBImplTest_312, OpenNonExistingWithoutCreate_312) {
  std::string new_dbname = testing::TempDir() + "/dbimpl_test_312_noexist";
  DestroyDB(new_dbname, Options());

  Options options;
  options.create_if_missing = false;
  DB* new_db = nullptr;
  Status s = DB::Open(options, new_dbname, &new_db);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(nullptr, new_db);
}

// Test: Open with error_if_exists=true on existing DB fails
TEST_F(DBImplTest_312, OpenExistingWithErrorIfExists_312) {
  // db_ is already open; close it
  delete db_;
  db_ = nullptr;

  Options options;
  options.create_if_missing = true;
  options.error_if_exists = true;
  DB* new_db = nullptr;
  Status s = DB::Open(options, dbname_, &new_db);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(nullptr, new_db);

  // Reopen without error_if_exists for teardown
  options.error_if_exists = false;
  s = DB::Open(options, dbname_, &db_);
  ASSERT_TRUE(s.ok());
}

// Test: GetProperty for stats
TEST_F(DBImplTest_312, GetPropertyStats_312) {
  std::string value;
  bool result = db_->GetProperty("leveldb.stats", &value);
  EXPECT_TRUE(result);
  EXPECT_FALSE(value.empty());
}

// Test: GetProperty for sstables
TEST_F(DBImplTest_312, GetPropertySSTables_312) {
  std::string value;
  bool result = db_->GetProperty("leveldb.sstables", &value);
  EXPECT_TRUE(result);
}

// Test: Large value put and delete
TEST_F(DBImplTest_312, DeleteLargeValue_312) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  std::string large_value(100000, 'v');
  Status s = db_->Put(write_opts, "largevalkey", large_value);
  ASSERT_TRUE(s.ok());

  s = db_->Delete(write_opts, "largevalkey");
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(read_opts, "largevalkey", &value);
  EXPECT_TRUE(s.IsNotFound());
}

}  // namespace leveldb
