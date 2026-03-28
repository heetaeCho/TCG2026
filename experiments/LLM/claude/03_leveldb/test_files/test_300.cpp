#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include "db/db_impl.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class DBImplTest_300 : public testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "/dbimpl_test_300";
    options_.create_if_missing = true;
    options_.error_if_exists = false;
    // Use default env
    DestroyDB(dbname_, options_);
    ASSERT_TRUE(DB::Open(options_, dbname_, &db_).ok());
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }
};

// Test basic Put and Get
TEST_F(DBImplTest_300, PutAndGet_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  Status s = db_->Put(write_options, "key1", "value1");
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(read_options, "key1", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("value1", value);
}

// Test Get for non-existent key
TEST_F(DBImplTest_300, GetNonExistentKey_300) {
  ReadOptions read_options;
  std::string value;
  Status s = db_->Get(read_options, "nonexistent", &value);
  ASSERT_TRUE(s.IsNotFound());
}

// Test Delete operation
TEST_F(DBImplTest_300, DeleteKey_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "key1", "value1").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "key1", &value).ok());
  EXPECT_EQ("value1", value);

  ASSERT_TRUE(db_->Delete(write_options, "key1").ok());

  Status s = db_->Get(read_options, "key1", &value);
  ASSERT_TRUE(s.IsNotFound());
}

// Test Write with WriteBatch
TEST_F(DBImplTest_300, WriteBatchOperations_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  WriteBatch batch;
  batch.Put("batch_key1", "batch_value1");
  batch.Put("batch_key2", "batch_value2");
  batch.Put("batch_key3", "batch_value3");

  Status s = db_->Write(write_options, &batch);
  ASSERT_TRUE(s.ok());

  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "batch_key1", &value).ok());
  EXPECT_EQ("batch_value1", value);

  ASSERT_TRUE(db_->Get(read_options, "batch_key2", &value).ok());
  EXPECT_EQ("batch_value2", value);

  ASSERT_TRUE(db_->Get(read_options, "batch_key3", &value).ok());
  EXPECT_EQ("batch_value3", value);
}

// Test WriteBatch with delete in batch
TEST_F(DBImplTest_300, WriteBatchWithDelete_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "key_to_delete", "value").ok());

  WriteBatch batch;
  batch.Put("new_key", "new_value");
  batch.Delete("key_to_delete");

  ASSERT_TRUE(db_->Write(write_options, &batch).ok());

  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "new_key", &value).ok());
  EXPECT_EQ("new_value", value);

  Status s = db_->Get(read_options, "key_to_delete", &value);
  ASSERT_TRUE(s.IsNotFound());
}

// Test Write with nullptr batch (empty write)
TEST_F(DBImplTest_300, WriteWithNullBatch_300) {
  WriteOptions write_options;
  Status s = db_->Write(write_options, nullptr);
  ASSERT_TRUE(s.ok());
}

// Test overwriting a key
TEST_F(DBImplTest_300, OverwriteKey_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "key1", "value1").ok());
  ASSERT_TRUE(db_->Put(write_options, "key1", "value2").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "key1", &value).ok());
  EXPECT_EQ("value2", value);
}

// Test NewIterator basic functionality
TEST_F(DBImplTest_300, IteratorBasic_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "a", "1").ok());
  ASSERT_TRUE(db_->Put(write_options, "b", "2").ok());
  ASSERT_TRUE(db_->Put(write_options, "c", "3").ok());

  Iterator* iter = db_->NewIterator(read_options);
  ASSERT_TRUE(iter != nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  EXPECT_EQ("1", iter->value().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());
  EXPECT_EQ("2", iter->value().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());
  EXPECT_EQ("3", iter->value().ToString());

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test Iterator SeekToLast
TEST_F(DBImplTest_300, IteratorSeekToLast_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "a", "1").ok());
  ASSERT_TRUE(db_->Put(write_options, "b", "2").ok());
  ASSERT_TRUE(db_->Put(write_options, "c", "3").ok());

  Iterator* iter = db_->NewIterator(read_options);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());
  EXPECT_EQ("3", iter->value().ToString());

  delete iter;
}

// Test Iterator Seek
TEST_F(DBImplTest_300, IteratorSeek_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "a", "1").ok());
  ASSERT_TRUE(db_->Put(write_options, "c", "3").ok());
  ASSERT_TRUE(db_->Put(write_options, "e", "5").ok());

  Iterator* iter = db_->NewIterator(read_options);
  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  iter->Seek("d");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("e", iter->key().ToString());

  iter->Seek("f");
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test empty iterator
TEST_F(DBImplTest_300, EmptyIterator_300) {
  ReadOptions read_options;
  Iterator* iter = db_->NewIterator(read_options);
  ASSERT_TRUE(iter != nullptr);

  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());

  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test Snapshot functionality
TEST_F(DBImplTest_300, SnapshotBasic_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "key1", "value1").ok());

  const Snapshot* snapshot = db_->GetSnapshot();
  ASSERT_TRUE(snapshot != nullptr);

  ASSERT_TRUE(db_->Put(write_options, "key1", "value2").ok());

  // Read with snapshot should see old value
  read_options.snapshot = snapshot;
  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "key1", &value).ok());
  EXPECT_EQ("value1", value);

  // Read without snapshot should see new value
  ReadOptions read_options_no_snap;
  ASSERT_TRUE(db_->Get(read_options_no_snap, "key1", &value).ok());
  EXPECT_EQ("value2", value);

  db_->ReleaseSnapshot(snapshot);
}

// Test Snapshot sees consistent state
TEST_F(DBImplTest_300, SnapshotConsistency_300) {
  WriteOptions write_options;

  ASSERT_TRUE(db_->Put(write_options, "k1", "v1").ok());
  ASSERT_TRUE(db_->Put(write_options, "k2", "v2").ok());

  const Snapshot* snap = db_->GetSnapshot();

  ASSERT_TRUE(db_->Delete(write_options, "k1").ok());
  ASSERT_TRUE(db_->Put(write_options, "k2", "v2_updated").ok());
  ASSERT_TRUE(db_->Put(write_options, "k3", "v3").ok());

  ReadOptions read_with_snap;
  read_with_snap.snapshot = snap;
  std::string value;

  // k1 should still exist in snapshot
  ASSERT_TRUE(db_->Get(read_with_snap, "k1", &value).ok());
  EXPECT_EQ("v1", value);

  // k2 should have old value
  ASSERT_TRUE(db_->Get(read_with_snap, "k2", &value).ok());
  EXPECT_EQ("v2", value);

  // k3 should not exist in snapshot
  ASSERT_TRUE(db_->Get(read_with_snap, "k3", &value).IsNotFound());

  db_->ReleaseSnapshot(snap);
}

// Test GetProperty for stats
TEST_F(DBImplTest_300, GetPropertyStats_300) {
  std::string value;
  bool result = db_->GetProperty("leveldb.stats", &value);
  EXPECT_TRUE(result);
  EXPECT_FALSE(value.empty());
}

// Test GetProperty for num-files-at-level
TEST_F(DBImplTest_300, GetPropertyNumFiles_300) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  EXPECT_TRUE(result);
}

// Test GetProperty with invalid property
TEST_F(DBImplTest_300, GetPropertyInvalid_300) {
  std::string value;
  bool result = db_->GetProperty("leveldb.nonexistent-property", &value);
  EXPECT_FALSE(result);
}

// Test GetApproximateSizes
TEST_F(DBImplTest_300, GetApproximateSizes_300) {
  WriteOptions write_options;

  // Write some data
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = std::string(1000, 'x');
    ASSERT_TRUE(db_->Put(write_options, key, val).ok());
  }

  Range range;
  range.start = "key0";
  range.limit = "key99";
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // Size should be non-negative (could be 0 if all in memtable)
  EXPECT_GE(size, 0u);
}

// Test CompactRange
TEST_F(DBImplTest_300, CompactRange_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_options, key, std::string(100, 'v')).ok());
  }

  // Compact entire range
  db_->CompactRange(nullptr, nullptr);

  // Data should still be accessible
  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "key0", &value).ok());
}

// Test CompactRange with specific range
TEST_F(DBImplTest_300, CompactRangeSpecific_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_options, key, std::string(100, 'v')).ok());
  }

  Slice begin("key0");
  Slice end("key25");
  db_->CompactRange(&begin, &end);

  // Data should still be accessible
  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "key10", &value).ok());
}

// Test multiple Put and Delete in sequence
TEST_F(DBImplTest_300, MultiplePutDelete_300) {
  WriteOptions write_options;
  ReadOptions read_options;
  std::string value;

  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_options, key, "value" + std::to_string(i)).ok());
  }

  // Delete even keys
  for (int i = 0; i < 50; i += 2) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Delete(write_options, key).ok());
  }

  // Even keys should be gone
  for (int i = 0; i < 50; i += 2) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Get(read_options, key, &value).IsNotFound());
  }

  // Odd keys should remain
  for (int i = 1; i < 50; i += 2) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Get(read_options, key, &value).ok());
    EXPECT_EQ("value" + std::to_string(i), value);
  }
}

// Test empty key and value
TEST_F(DBImplTest_300, EmptyKeyAndValue_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "", "").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "", &value).ok());
  EXPECT_EQ("", value);
}

// Test large value
TEST_F(DBImplTest_300, LargeValue_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  std::string large_value(100000, 'x');
  ASSERT_TRUE(db_->Put(write_options, "large_key", large_value).ok());

  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "large_key", &value).ok());
  EXPECT_EQ(large_value, value);
}

// Test DB open with error_if_exists
TEST_F(DBImplTest_300, ErrorIfExists_300) {
  // The db already exists from SetUp
  Options opts;
  opts.create_if_missing = false;
  opts.error_if_exists = true;
  DB* db2 = nullptr;
  Status s = DB::Open(opts, dbname_, &db2);
  ASSERT_TRUE(s.IsInvalidArgument()) << s.ToString();
  EXPECT_EQ(nullptr, db2);
}

// Test DB open with create_if_missing = false on non-existent db
TEST_F(DBImplTest_300, OpenNonExistentNoCreate_300) {
  std::string nonexistent = testing::TempDir() + "/nonexistent_db_300";
  DestroyDB(nonexistent, Options());

  Options opts;
  opts.create_if_missing = false;
  DB* db2 = nullptr;
  Status s = DB::Open(opts, nonexistent, &db2);
  ASSERT_FALSE(s.ok());
  EXPECT_EQ(nullptr, db2);
}

// Test reopen database preserves data
TEST_F(DBImplTest_300, ReopenPreservesData_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "persist_key", "persist_value").ok());

  // Close
  delete db_;
  db_ = nullptr;

  // Reopen
  Status s = DB::Open(options_, dbname_, &db_);
  ASSERT_TRUE(s.ok());

  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "persist_key", &value).ok());
  EXPECT_EQ("persist_value", value);
}

// Test Iterator Prev
TEST_F(DBImplTest_300, IteratorPrev_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "a", "1").ok());
  ASSERT_TRUE(db_->Put(write_options, "b", "2").ok());
  ASSERT_TRUE(db_->Put(write_options, "c", "3").ok());

  Iterator* iter = db_->NewIterator(read_options);
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());

  iter->Prev();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test delete non-existent key
TEST_F(DBImplTest_300, DeleteNonExistentKey_300) {
  WriteOptions write_options;
  Status s = db_->Delete(write_options, "does_not_exist");
  ASSERT_TRUE(s.ok());
}

// Test sync write option
TEST_F(DBImplTest_300, SyncWrite_300) {
  WriteOptions write_options;
  write_options.sync = true;

  ASSERT_TRUE(db_->Put(write_options, "sync_key", "sync_value").ok());

  ReadOptions read_options;
  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "sync_key", &value).ok());
  EXPECT_EQ("sync_value", value);
}

// Test multiple snapshots
TEST_F(DBImplTest_300, MultipleSnapshots_300) {
  WriteOptions write_options;

  ASSERT_TRUE(db_->Put(write_options, "k", "v1").ok());
  const Snapshot* snap1 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(write_options, "k", "v2").ok());
  const Snapshot* snap2 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(write_options, "k", "v3").ok());

  ReadOptions ro1, ro2, ro3;
  ro1.snapshot = snap1;
  ro2.snapshot = snap2;
  std::string value;

  ASSERT_TRUE(db_->Get(ro1, "k", &value).ok());
  EXPECT_EQ("v1", value);

  ASSERT_TRUE(db_->Get(ro2, "k", &value).ok());
  EXPECT_EQ("v2", value);

  ASSERT_TRUE(db_->Get(ro3, "k", &value).ok());
  EXPECT_EQ("v3", value);

  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap2);
}

// Test GetApproximateSizes with multiple ranges
TEST_F(DBImplTest_300, GetApproximateSizesMultipleRanges_300) {
  WriteOptions write_options;

  for (int i = 0; i < 200; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(write_options, key, std::string(1000, 'v')).ok());
  }

  // Force compaction to have data on disk
  static_cast<DBImpl*>(db_)->TEST_CompactMemTable();

  Range ranges[3];
  ranges[0].start = "key000000";
  ranges[0].limit = "key000050";
  ranges[1].start = "key000050";
  ranges[1].limit = "key000100";
  ranges[2].start = "key000100";
  ranges[2].limit = "key000200";

  uint64_t sizes[3];
  db_->GetApproximateSizes(ranges, 3, sizes);

  // All sizes should be non-negative
  for (int i = 0; i < 3; i++) {
    EXPECT_GE(sizes[i], 0u);
  }
}

// Test TEST_CompactMemTable
TEST_F(DBImplTest_300, CompactMemTable_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  for (int i = 0; i < 100; i++) {
    std::string key = "memtable_key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_options, key, std::string(100, 'v')).ok());
  }

  DBImpl* dbimpl = static_cast<DBImpl*>(db_);
  Status s = dbimpl->TEST_CompactMemTable();
  ASSERT_TRUE(s.ok());

  // Data should still be accessible after compaction
  std::string value;
  ASSERT_TRUE(db_->Get(read_options, "memtable_key0", &value).ok());
}

// Test many writes and reads
TEST_F(DBImplTest_300, ManyWritesAndReads_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  const int kCount = 1000;
  for (int i = 0; i < kCount; i++) {
    char key[100], val[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    ASSERT_TRUE(db_->Put(write_options, key, val).ok());
  }

  for (int i = 0; i < kCount; i++) {
    char key[100], expected_val[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(expected_val, sizeof(expected_val), "val%06d", i);
    std::string value;
    ASSERT_TRUE(db_->Get(read_options, key, &value).ok());
    EXPECT_EQ(std::string(expected_val), value);
  }
}

// Test GetProperty for sstables
TEST_F(DBImplTest_300, GetPropertySSTables_300) {
  WriteOptions write_options;
  for (int i = 0; i < 100; i++) {
    ASSERT_TRUE(db_->Put(write_options, "k" + std::to_string(i),
                          std::string(100, 'v')).ok());
  }
  static_cast<DBImpl*>(db_)->TEST_CompactMemTable();

  std::string value;
  bool result = db_->GetProperty("leveldb.sstables", &value);
  EXPECT_TRUE(result);
}

// Test GetProperty for approximate memory usage
TEST_F(DBImplTest_300, GetPropertyApproxMemUsage_300) {
  std::string value;
  bool result = db_->GetProperty("leveldb.approximate-memory-usage", &value);
  EXPECT_TRUE(result);
}

// Test Iterator on database with single element
TEST_F(DBImplTest_300, IteratorSingleElement_300) {
  WriteOptions write_options;
  ReadOptions read_options;

  ASSERT_TRUE(db_->Put(write_options, "only_key", "only_value").ok());

  Iterator* iter = db_->NewIterator(read_options);
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("only_key", iter->key().ToString());
  EXPECT_EQ("only_value", iter->value().ToString());

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test DestroyDB
TEST_F(DBImplTest_300, DestroyDB_300) {
  WriteOptions write_options;
  ASSERT_TRUE(db_->Put(write_options, "key1", "value1").ok());

  delete db_;
  db_ = nullptr;

  ASSERT_TRUE(DestroyDB(dbname_, options_).ok());

  // Opening without create_if_missing should fail
  Options opts;
  opts.create_if_missing = false;
  DB* db2 = nullptr;
  Status s = DB::Open(opts, dbname_, &db2);
  ASSERT_FALSE(s.ok());
  EXPECT_EQ(nullptr, db2);

  // Recreate for TearDown
  options_.create_if_missing = true;
  ASSERT_TRUE(DB::Open(options_, dbname_, &db_).ok());
}

}  // namespace leveldb
