#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/iterator.h"
#include "leveldb/write_batch.h"
#include "leveldb/env.h"
#include "db/db_impl.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class DBImplTest_304 : public ::testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "/db_impl_test_304";
    options_.create_if_missing = true;
    options_.error_if_exists = false;
    DestroyDB(dbname_, options_);
    Status s = DB::Open(options_, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }

  DBImpl* impl() { return reinterpret_cast<DBImpl*>(db_); }
};

// ============ Put / Get Tests ============

TEST_F(DBImplTest_304, PutAndGetSingleKey_304) {
  Status s = db_->Put(WriteOptions(), "key1", "value1");
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string value;
  s = db_->Get(ReadOptions(), "key1", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("value1", value);
}

TEST_F(DBImplTest_304, PutOverwriteKey_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value2").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key1", &value).ok());
  EXPECT_EQ("value2", value);
}

TEST_F(DBImplTest_304, GetNonExistentKey_304) {
  std::string value;
  Status s = db_->Get(ReadOptions(), "nonexistent", &value);
  EXPECT_TRUE(s.IsNotFound());
}

TEST_F(DBImplTest_304, PutEmptyKey_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "", "emptykey").ok());
  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "", &value).ok());
  EXPECT_EQ("emptykey", value);
}

TEST_F(DBImplTest_304, PutEmptyValue_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key_empty_val", "").ok());
  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key_empty_val", &value).ok());
  EXPECT_EQ("", value);
}

// ============ Delete Tests ============

TEST_F(DBImplTest_304, DeleteExistingKey_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value1").ok());
  ASSERT_TRUE(db_->Delete(WriteOptions(), "key1").ok());

  std::string value;
  Status s = db_->Get(ReadOptions(), "key1", &value);
  EXPECT_TRUE(s.IsNotFound());
}

TEST_F(DBImplTest_304, DeleteNonExistentKey_304) {
  Status s = db_->Delete(WriteOptions(), "nonexistent");
  EXPECT_TRUE(s.ok());
}

// ============ Write (WriteBatch) Tests ============

TEST_F(DBImplTest_304, WriteBatchMultipleOps_304) {
  WriteBatch batch;
  batch.Put("bkey1", "bval1");
  batch.Put("bkey2", "bval2");
  batch.Delete("bkey1");

  ASSERT_TRUE(db_->Write(WriteOptions(), &batch).ok());

  std::string value;
  Status s = db_->Get(ReadOptions(), "bkey1", &value);
  EXPECT_TRUE(s.IsNotFound());

  s = db_->Get(ReadOptions(), "bkey2", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("bval2", value);
}

TEST_F(DBImplTest_304, WriteNullBatch_304) {
  Status s = db_->Write(WriteOptions(), nullptr);
  EXPECT_TRUE(s.ok());
}

// ============ Iterator Tests ============

TEST_F(DBImplTest_304, NewIteratorEmpty_304) {
  Iterator* it = db_->NewIterator(ReadOptions());
  ASSERT_NE(it, nullptr);
  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());
  delete it;
}

TEST_F(DBImplTest_304, NewIteratorWithData_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());

  Iterator* it = db_->NewIterator(ReadOptions());
  ASSERT_NE(it, nullptr);

  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("a", it->key().ToString());
  EXPECT_EQ("1", it->value().ToString());

  it->Next();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("b", it->key().ToString());

  it->Next();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("c", it->key().ToString());

  it->Next();
  EXPECT_FALSE(it->Valid());

  delete it;
}

TEST_F(DBImplTest_304, NewIteratorSeekToLast_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());

  Iterator* it = db_->NewIterator(ReadOptions());
  it->SeekToLast();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("b", it->key().ToString());
  EXPECT_EQ("2", it->value().ToString());
  delete it;
}

TEST_F(DBImplTest_304, NewIteratorSeek_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "e", "5").ok());

  Iterator* it = db_->NewIterator(ReadOptions());
  it->Seek("b");
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("c", it->key().ToString());

  it->Seek("d");
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("e", it->key().ToString());

  it->Seek("f");
  EXPECT_FALSE(it->Valid());

  delete it;
}

// ============ Snapshot Tests ============

TEST_F(DBImplTest_304, SnapshotReadOldValue_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "old_value").ok());

  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "new_value").ok());

  // Read with snapshot should see old value
  ReadOptions ro;
  ro.snapshot = snap;
  std::string value;
  ASSERT_TRUE(db_->Get(ro, "key1", &value).ok());
  EXPECT_EQ("old_value", value);

  // Read without snapshot should see new value
  ASSERT_TRUE(db_->Get(ReadOptions(), "key1", &value).ok());
  EXPECT_EQ("new_value", value);

  db_->ReleaseSnapshot(snap);
}

TEST_F(DBImplTest_304, MultipleSnapshots_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "v1").ok());
  const Snapshot* snap1 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "v2").ok());
  const Snapshot* snap2 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "v3").ok());

  ReadOptions ro1, ro2;
  ro1.snapshot = snap1;
  ro2.snapshot = snap2;

  std::string value;
  ASSERT_TRUE(db_->Get(ro1, "key1", &value).ok());
  EXPECT_EQ("v1", value);

  ASSERT_TRUE(db_->Get(ro2, "key1", &value).ok());
  EXPECT_EQ("v2", value);

  ASSERT_TRUE(db_->Get(ReadOptions(), "key1", &value).ok());
  EXPECT_EQ("v3", value);

  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap2);
}

// ============ GetProperty Tests ============

TEST_F(DBImplTest_304, GetPropertyNumFilesAtLevel_304) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  EXPECT_TRUE(result);
  // Value should be a non-negative number
  EXPECT_GE(std::stoi(value), 0);
}

TEST_F(DBImplTest_304, GetPropertyStats_304) {
  std::string value;
  bool result = db_->GetProperty("leveldb.stats", &value);
  EXPECT_TRUE(result);
  EXPECT_FALSE(value.empty());
}

TEST_F(DBImplTest_304, GetPropertyInvalid_304) {
  std::string value;
  bool result = db_->GetProperty("leveldb.nonexistent-property", &value);
  EXPECT_FALSE(result);
}

TEST_F(DBImplTest_304, GetPropertySSTables_304) {
  std::string value;
  bool result = db_->GetProperty("leveldb.sstables", &value);
  EXPECT_TRUE(result);
}

TEST_F(DBImplTest_304, GetPropertyApproximateMemoryUsage_304) {
  std::string value;
  bool result = db_->GetProperty("leveldb.approximate-memory-usage", &value);
  EXPECT_TRUE(result);
  EXPECT_GE(std::stoll(value), 0);
}

// ============ GetApproximateSizes Tests ============

TEST_F(DBImplTest_304, GetApproximateSizesEmpty_304) {
  Range range("a", "z");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  EXPECT_EQ(0u, size);
}

TEST_F(DBImplTest_304, GetApproximateSizesWithData_304) {
  // Insert enough data to potentially create files
  for (int i = 0; i < 1000; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(1000, 'v')).ok());
  }

  // Flush to SST
  impl()->TEST_CompactMemTable();

  Range range("key000000", "key999999");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // We have data, so size should be > 0
  EXPECT_GT(size, 0u);
}

TEST_F(DBImplTest_304, GetApproximateSizesMultipleRanges_304) {
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(100, 'x')).ok());
  }

  Range ranges[2];
  ranges[0] = Range("key000000", "key000050");
  ranges[1] = Range("key000050", "key000100");
  uint64_t sizes[2];
  db_->GetApproximateSizes(ranges, 2, sizes);
  // Both ranges should have non-negative sizes
  EXPECT_GE(sizes[0], 0u);
  EXPECT_GE(sizes[1], 0u);
}

// ============ CompactRange Tests ============

TEST_F(DBImplTest_304, CompactRangeFullDatabase_304) {
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(100, 'v')).ok());
  }
  // Compact entire range
  db_->CompactRange(nullptr, nullptr);

  // Verify data is still accessible
  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key000050", &value).ok());
  EXPECT_EQ(std::string(100, 'v'), value);
}

TEST_F(DBImplTest_304, CompactRangePartial_304) {
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(100, 'v')).ok());
  }
  Slice begin("key000020");
  Slice end("key000080");
  db_->CompactRange(&begin, &end);

  // Verify data is still accessible
  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key000050", &value).ok());
}

// ============ TEST_CompactMemTable Tests ============

TEST_F(DBImplTest_304, TestCompactMemTable_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "memkey", "memval").ok());
  Status s = impl()->TEST_CompactMemTable();
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "memkey", &value).ok());
  EXPECT_EQ("memval", value);
}

// ============ TEST_NewInternalIterator Tests ============

TEST_F(DBImplTest_304, TestNewInternalIteratorEmpty_304) {
  Iterator* it = impl()->TEST_NewInternalIterator();
  ASSERT_NE(it, nullptr);
  it->SeekToFirst();
  // Internal iterator may or may not have entries; just check it doesn't crash
  EXPECT_TRUE(it->status().ok());
  delete it;
}

TEST_F(DBImplTest_304, TestNewInternalIteratorWithData_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "ikey", "ival").ok());

  Iterator* it = impl()->TEST_NewInternalIterator();
  ASSERT_NE(it, nullptr);
  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());
  EXPECT_TRUE(it->status().ok());
  delete it;
}

// ============ TEST_MaxNextLevelOverlappingBytes Tests ============

TEST_F(DBImplTest_304, TestMaxNextLevelOverlappingBytesEmpty_304) {
  int64_t result = impl()->TEST_MaxNextLevelOverlappingBytes();
  EXPECT_GE(result, 0);
}

TEST_F(DBImplTest_304, TestMaxNextLevelOverlappingBytesWithData_304) {
  for (int i = 0; i < 500; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(100, 'v')).ok());
  }
  impl()->TEST_CompactMemTable();

  int64_t result = impl()->TEST_MaxNextLevelOverlappingBytes();
  EXPECT_GE(result, 0);
}

// ============ TEST_CompactRange Tests ============

TEST_F(DBImplTest_304, TestCompactRangeLevel0_304) {
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(100, 'v')).ok());
  }
  impl()->TEST_CompactMemTable();

  Slice begin("key000000");
  Slice end("key000099");
  impl()->TEST_CompactRange(0, &begin, &end);

  // Data should still be accessible
  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key000050", &value).ok());
}

TEST_F(DBImplTest_304, TestCompactRangeWithNullBounds_304) {
  for (int i = 0; i < 50; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(100, 'v')).ok());
  }
  impl()->TEST_CompactMemTable();

  impl()->TEST_CompactRange(0, nullptr, nullptr);

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key000025", &value).ok());
}

// ============ Multiple Put/Delete Sequence Tests ============

TEST_F(DBImplTest_304, PutDeletePutSequence_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "v1").ok());
  ASSERT_TRUE(db_->Delete(WriteOptions(), "key1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "v2").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key1", &value).ok());
  EXPECT_EQ("v2", value);
}

// ============ Large Value Tests ============

TEST_F(DBImplTest_304, LargeValuePutGet_304) {
  std::string large_value(100000, 'x');
  ASSERT_TRUE(db_->Put(WriteOptions(), "large_key", large_value).ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "large_key", &value).ok());
  EXPECT_EQ(large_value, value);
}

// ============ Many Keys Tests ============

TEST_F(DBImplTest_304, ManyKeysPutGet_304) {
  const int kCount = 1000;
  for (int i = 0; i < kCount; i++) {
    char key[100], val[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, val).ok());
  }

  for (int i = 0; i < kCount; i++) {
    char key[100], expected_val[100];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(expected_val, sizeof(expected_val), "val%06d", i);
    std::string value;
    ASSERT_TRUE(db_->Get(ReadOptions(), key, &value).ok());
    EXPECT_EQ(expected_val, value);
  }
}

// ============ Reopen Database Tests ============

TEST_F(DBImplTest_304, ReopenDatabasePersistence_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "persist_key", "persist_val").ok());
  delete db_;
  db_ = nullptr;

  Status s = DB::Open(options_, dbname_, &db_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "persist_key", &value).ok());
  EXPECT_EQ("persist_val", value);
}

// ============ Sync Write Tests ============

TEST_F(DBImplTest_304, SyncWrite_304) {
  WriteOptions wo;
  wo.sync = true;
  ASSERT_TRUE(db_->Put(wo, "sync_key", "sync_val").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "sync_key", &value).ok());
  EXPECT_EQ("sync_val", value);
}

// ============ Iterator Prev Tests ============

TEST_F(DBImplTest_304, IteratorPrev_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());

  Iterator* it = db_->NewIterator(ReadOptions());
  it->SeekToLast();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("c", it->key().ToString());

  it->Prev();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("b", it->key().ToString());

  it->Prev();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("a", it->key().ToString());

  it->Prev();
  EXPECT_FALSE(it->Valid());

  delete it;
}

// ============ Open non-existent without create_if_missing ============

TEST_F(DBImplTest_304, OpenNonExistentWithoutCreate_304) {
  Options opts;
  opts.create_if_missing = false;
  DB* db2 = nullptr;
  std::string path = testing::TempDir() + "/db_impl_test_304_noexist";
  DestroyDB(path, opts);
  Status s = DB::Open(opts, path, &db2);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(db2, nullptr);
}

// ============ Open existing with error_if_exists ============

TEST_F(DBImplTest_304, OpenExistingWithErrorIfExists_304) {
  // db_ is already open; close it and reopen with error_if_exists
  delete db_;
  db_ = nullptr;

  Options opts;
  opts.create_if_missing = true;
  opts.error_if_exists = true;
  DB* db2 = nullptr;
  Status s = DB::Open(opts, dbname_, &db2);
  EXPECT_FALSE(s.ok());
  if (db2) {
    delete db2;
  }

  // Reopen normally for teardown
  options_.error_if_exists = false;
  s = DB::Open(options_, dbname_, &db_);
  ASSERT_TRUE(s.ok());
}

// ============ GetProperty with invalid level number ============

TEST_F(DBImplTest_304, GetPropertyInvalidLevel_304) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level99", &value);
  EXPECT_FALSE(result);
}

// ============ Snapshot with deleted key ============

TEST_F(DBImplTest_304, SnapshotSeesDeletedKey_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "snap_del_key", "snap_del_val").ok());
  const Snapshot* snap = db_->GetSnapshot();

  ASSERT_TRUE(db_->Delete(WriteOptions(), "snap_del_key").ok());

  // Current view should not find the key
  std::string value;
  Status s = db_->Get(ReadOptions(), "snap_del_key", &value);
  EXPECT_TRUE(s.IsNotFound());

  // Snapshot view should still find it
  ReadOptions ro;
  ro.snapshot = snap;
  s = db_->Get(ro, "snap_del_key", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("snap_del_val", value);

  db_->ReleaseSnapshot(snap);
}

// ============ Iterator with snapshot ============

TEST_F(DBImplTest_304, IteratorWithSnapshot_304) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());

  const Snapshot* snap = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());

  ReadOptions ro;
  ro.snapshot = snap;
  Iterator* it = db_->NewIterator(ro);
  int count = 0;
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    count++;
  }
  EXPECT_EQ(2, count);

  delete it;
  db_->ReleaseSnapshot(snap);
}

}  // namespace leveldb
