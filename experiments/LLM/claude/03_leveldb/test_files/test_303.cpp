#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/env.h"
#include "db/db_impl.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class DBImplTest_303 : public testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "dbimpl_test_303";
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

// Test that TEST_CompactMemTable returns OK on an empty database
TEST_F(DBImplTest_303, CompactMemTableEmpty_303) {
  Status s = impl()->TEST_CompactMemTable();
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test that TEST_CompactMemTable succeeds after writing some data
TEST_F(DBImplTest_303, CompactMemTableAfterPut_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "key2", "value2").ok());

  Status s = impl()->TEST_CompactMemTable();
  EXPECT_TRUE(s.ok()) << s.ToString();

  // Verify data is still readable after compaction
  std::string value;
  EXPECT_TRUE(db_->Get(ReadOptions(), "key1", &value).ok());
  EXPECT_EQ("value1", value);
  EXPECT_TRUE(db_->Get(ReadOptions(), "key2", &value).ok());
  EXPECT_EQ("value2", value);
}

// Test Put and Get basic operations
TEST_F(DBImplTest_303, PutAndGet_303) {
  WriteOptions wo;
  Status s = db_->Put(wo, "hello", "world");
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string value;
  s = db_->Get(ReadOptions(), "hello", &value);
  ASSERT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ("world", value);
}

// Test Delete operation
TEST_F(DBImplTest_303, DeleteKey_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "val").ok());
  ASSERT_TRUE(db_->Delete(WriteOptions(), "key").ok());

  std::string value;
  Status s = db_->Get(ReadOptions(), "key", &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test Get for non-existent key
TEST_F(DBImplTest_303, GetNonExistentKey_303) {
  std::string value;
  Status s = db_->Get(ReadOptions(), "nonexistent", &value);
  EXPECT_TRUE(s.IsNotFound()) << s.ToString();
}

// Test Write with a WriteBatch
TEST_F(DBImplTest_303, WriteBatch_303) {
  WriteBatch batch;
  batch.Put("batch_key1", "batch_val1");
  batch.Put("batch_key2", "batch_val2");
  batch.Delete("batch_key1");

  Status s = db_->Write(WriteOptions(), &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string value;
  s = db_->Get(ReadOptions(), "batch_key1", &value);
  EXPECT_TRUE(s.IsNotFound());

  s = db_->Get(ReadOptions(), "batch_key2", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("batch_val2", value);
}

// Test Write with nullptr (used internally by TEST_CompactMemTable)
TEST_F(DBImplTest_303, WriteWithNullBatch_303) {
  Status s = db_->Write(WriteOptions(), nullptr);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test NewIterator on empty DB
TEST_F(DBImplTest_303, NewIteratorEmpty_303) {
  Iterator* iter = db_->NewIterator(ReadOptions());
  ASSERT_NE(iter, nullptr);
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test NewIterator with data
TEST_F(DBImplTest_303, NewIteratorWithData_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());

  Iterator* iter = db_->NewIterator(ReadOptions());
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  EXPECT_EQ("1", iter->value().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test GetSnapshot and ReleaseSnapshot
TEST_F(DBImplTest_303, SnapshotIsolation_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "v1").ok());

  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "v2").ok());

  // Read with snapshot should see old value
  ReadOptions ro;
  ro.snapshot = snap;
  std::string value;
  ASSERT_TRUE(db_->Get(ro, "key", &value).ok());
  EXPECT_EQ("v1", value);

  // Read without snapshot should see new value
  ASSERT_TRUE(db_->Get(ReadOptions(), "key", &value).ok());
  EXPECT_EQ("v2", value);

  db_->ReleaseSnapshot(snap);
}

// Test GetProperty with valid property
TEST_F(DBImplTest_303, GetPropertyNumFilesAtLevel_303) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  EXPECT_TRUE(result);
}

// Test GetProperty with invalid property
TEST_F(DBImplTest_303, GetPropertyInvalid_303) {
  std::string value;
  bool result = db_->GetProperty("leveldb.nonexistent-property", &value);
  EXPECT_FALSE(result);
}

// Test GetProperty for stats
TEST_F(DBImplTest_303, GetPropertyStats_303) {
  std::string value;
  bool result = db_->GetProperty("leveldb.stats", &value);
  EXPECT_TRUE(result);
}

// Test GetApproximateSizes
TEST_F(DBImplTest_303, GetApproximateSizes_303) {
  // Write some data and compact
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val(1000, 'x');
    ASSERT_TRUE(db_->Put(WriteOptions(), key, val).ok());
  }
  impl()->TEST_CompactMemTable();

  Range range("key0", "key99");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // Size should be non-negative (can be 0 or more)
  EXPECT_GE(size, 0u);
}

// Test CompactRange
TEST_F(DBImplTest_303, CompactRange_303) {
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(100, 'v')).ok());
  }

  // Compact the entire range
  db_->CompactRange(nullptr, nullptr);

  // Data should still be readable
  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key0", &value).ok());
}

// Test TEST_CompactRange
TEST_F(DBImplTest_303, TestCompactRange_303) {
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(100, 'v')).ok());
  }
  impl()->TEST_CompactMemTable();

  Slice begin("key0");
  Slice end("key9");
  impl()->TEST_CompactRange(0, &begin, &end);

  // Verify data is still there
  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key0", &value).ok());
}

// Test TEST_MaxNextLevelOverlappingBytes
TEST_F(DBImplTest_303, TestMaxNextLevelOverlappingBytes_303) {
  int64_t result = impl()->TEST_MaxNextLevelOverlappingBytes();
  EXPECT_GE(result, 0);
}

// Test TEST_NewInternalIterator
TEST_F(DBImplTest_303, TestNewInternalIterator_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "ikey", "ival").ok());

  Iterator* iter = impl()->TEST_NewInternalIterator();
  ASSERT_NE(iter, nullptr);
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  delete iter;
}

// Test multiple compact memtable calls in succession
TEST_F(DBImplTest_303, MultipleCompactMemTable_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "k1", "v1").ok());
  EXPECT_TRUE(impl()->TEST_CompactMemTable().ok());

  ASSERT_TRUE(db_->Put(WriteOptions(), "k2", "v2").ok());
  EXPECT_TRUE(impl()->TEST_CompactMemTable().ok());

  ASSERT_TRUE(db_->Put(WriteOptions(), "k3", "v3").ok());
  EXPECT_TRUE(impl()->TEST_CompactMemTable().ok());

  std::string value;
  EXPECT_TRUE(db_->Get(ReadOptions(), "k1", &value).ok());
  EXPECT_EQ("v1", value);
  EXPECT_TRUE(db_->Get(ReadOptions(), "k2", &value).ok());
  EXPECT_EQ("v2", value);
  EXPECT_TRUE(db_->Get(ReadOptions(), "k3", &value).ok());
  EXPECT_EQ("v3", value);
}

// Test overwriting a key and compacting
TEST_F(DBImplTest_303, OverwriteAndCompact_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "old_value").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "new_value").ok());

  EXPECT_TRUE(impl()->TEST_CompactMemTable().ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key", &value).ok());
  EXPECT_EQ("new_value", value);
}

// Test large number of keys with compact
TEST_F(DBImplTest_303, LargeNumberOfKeysCompact_303) {
  const int kNumKeys = 1000;
  for (int i = 0; i < kNumKeys; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, std::string(100, 'x')).ok());
  }

  EXPECT_TRUE(impl()->TEST_CompactMemTable().ok());

  // Verify some keys
  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key000000", &value).ok());
  ASSERT_TRUE(db_->Get(ReadOptions(), "key000999", &value).ok());
}

// Test empty key and empty value
TEST_F(DBImplTest_303, EmptyKeyAndValue_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "", "").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "", &value).ok());
  EXPECT_EQ("", value);

  EXPECT_TRUE(impl()->TEST_CompactMemTable().ok());

  ASSERT_TRUE(db_->Get(ReadOptions(), "", &value).ok());
  EXPECT_EQ("", value);
}

// Test sync write option
TEST_F(DBImplTest_303, SyncWrite_303) {
  WriteOptions wo;
  wo.sync = true;
  Status s = db_->Put(wo, "sync_key", "sync_val");
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "sync_key", &value).ok());
  EXPECT_EQ("sync_val", value);
}

// Test reopening the database preserves data after compact
TEST_F(DBImplTest_303, ReopenAfterCompact_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "persist_key", "persist_val").ok());
  EXPECT_TRUE(impl()->TEST_CompactMemTable().ok());

  delete db_;
  db_ = nullptr;

  Status s = DB::Open(options_, dbname_, &db_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "persist_key", &value).ok());
  EXPECT_EQ("persist_val", value);
}

// Test iterator SeekToLast
TEST_F(DBImplTest_303, IteratorSeekToLast_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "z", "26").ok());

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("z", iter->key().ToString());
  EXPECT_EQ("26", iter->value().ToString());
  delete iter;
}

// Test iterator Seek
TEST_F(DBImplTest_303, IteratorSeek_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "e", "5").ok());

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());
  delete iter;
}

// Test delete then compact
TEST_F(DBImplTest_303, DeleteThenCompact_303) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "del_key", "del_val").ok());
  ASSERT_TRUE(db_->Delete(WriteOptions(), "del_key").ok());
  EXPECT_TRUE(impl()->TEST_CompactMemTable().ok());

  std::string value;
  Status s = db_->Get(ReadOptions(), "del_key", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test GetApproximateSizes with empty range
TEST_F(DBImplTest_303, GetApproximateSizesEmptyRange_303) {
  Range range("a", "a");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  EXPECT_EQ(0u, size);
}

}  // namespace leveldb
