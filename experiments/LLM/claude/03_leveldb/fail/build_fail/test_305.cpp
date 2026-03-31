#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include "db/db_impl.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <cstdio>

namespace leveldb {

class DBImplTest_305 : public testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "dbimpl_test_305";
    options_.create_if_missing = true;
    // Destroy any previous database
    DestroyDB(dbname_, options_);
    Status s = DB::Open(options_, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }

  DBImpl* impl() {
    return reinterpret_cast<DBImpl*>(db_);
  }
};

// Test that on an empty database, MaxNextLevelOverlappingBytes returns a non-negative value
TEST_F(DBImplTest_305, MaxNextLevelOverlappingBytesEmptyDB_305) {
  int64_t result = impl()->TEST_MaxNextLevelOverlappingBytes();
  EXPECT_GE(result, 0);
}

// Test that MaxNextLevelOverlappingBytes returns a value after inserting some data
TEST_F(DBImplTest_305, MaxNextLevelOverlappingBytesAfterInserts_305) {
  // Insert some data
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    ASSERT_TRUE(db_->Put(wo, key, val).ok());
  }

  int64_t result = impl()->TEST_MaxNextLevelOverlappingBytes();
  EXPECT_GE(result, 0);
}

// Test that after compaction, MaxNextLevelOverlappingBytes is still valid
TEST_F(DBImplTest_305, MaxNextLevelOverlappingBytesAfterCompaction_305) {
  WriteOptions wo;
  // Write enough data to trigger compactions
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = std::string(100, 'v');
    ASSERT_TRUE(db_->Put(wo, key, val).ok());
  }

  // Force compaction of memtable
  ASSERT_TRUE(impl()->TEST_CompactMemTable().ok());

  int64_t result = impl()->TEST_MaxNextLevelOverlappingBytes();
  EXPECT_GE(result, 0);
}

// Test basic Put and Get
TEST_F(DBImplTest_305, PutAndGet_305) {
  WriteOptions wo;
  ReadOptions ro;

  ASSERT_TRUE(db_->Put(wo, "testkey", "testvalue").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ro, "testkey", &value).ok());
  EXPECT_EQ("testvalue", value);
}

// Test Delete
TEST_F(DBImplTest_305, DeleteKey_305) {
  WriteOptions wo;
  ReadOptions ro;

  ASSERT_TRUE(db_->Put(wo, "delkey", "delvalue").ok());
  ASSERT_TRUE(db_->Delete(wo, "delkey").ok());

  std::string value;
  Status s = db_->Get(ro, "delkey", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test Get on non-existent key
TEST_F(DBImplTest_305, GetNonExistentKey_305) {
  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "nonexistent", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test Write with WriteBatch
TEST_F(DBImplTest_305, WriteBatchOperations_305) {
  WriteBatch batch;
  batch.Put("batchkey1", "batchval1");
  batch.Put("batchkey2", "batchval2");
  batch.Delete("batchkey1");

  WriteOptions wo;
  ASSERT_TRUE(db_->Write(wo, &batch).ok());

  ReadOptions ro;
  std::string value;
  Status s = db_->Get(ro, "batchkey1", &value);
  EXPECT_TRUE(s.IsNotFound());

  ASSERT_TRUE(db_->Get(ro, "batchkey2", &value).ok());
  EXPECT_EQ("batchval2", value);
}

// Test Write with nullptr batch (should handle gracefully)
TEST_F(DBImplTest_305, WriteNullBatch_305) {
  WriteOptions wo;
  Status s = db_->Write(wo, nullptr);
  // The behavior with nullptr batch: it should succeed (acts as a barrier)
  EXPECT_TRUE(s.ok());
}

// Test NewIterator
TEST_F(DBImplTest_305, NewIteratorEmpty_305) {
  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
  ASSERT_NE(it, nullptr);
  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());
  delete it;
}

// Test NewIterator with data
TEST_F(DBImplTest_305, NewIteratorWithData_305) {
  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "a", "1").ok());
  ASSERT_TRUE(db_->Put(wo, "b", "2").ok());
  ASSERT_TRUE(db_->Put(wo, "c", "3").ok());

  ReadOptions ro;
  Iterator* it = db_->NewIterator(ro);
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

// Test Snapshot
TEST_F(DBImplTest_305, SnapshotIsolation_305) {
  WriteOptions wo;
  ReadOptions ro;

  ASSERT_TRUE(db_->Put(wo, "snapkey", "val1").ok());

  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  ASSERT_TRUE(db_->Put(wo, "snapkey", "val2").ok());

  // Read with snapshot should see old value
  ro.snapshot = snap;
  std::string value;
  ASSERT_TRUE(db_->Get(ro, "snapkey", &value).ok());
  EXPECT_EQ("val1", value);

  // Read without snapshot should see new value
  ro.snapshot = nullptr;
  ASSERT_TRUE(db_->Get(ro, "snapkey", &value).ok());
  EXPECT_EQ("val2", value);

  db_->ReleaseSnapshot(snap);
}

// Test GetProperty
TEST_F(DBImplTest_305, GetPropertyNumFilesAtLevel_305) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  EXPECT_TRUE(result);
  // On empty DB, level 0 should have 0 files
  EXPECT_EQ("0", value);
}

// Test GetProperty with invalid property name
TEST_F(DBImplTest_305, GetPropertyInvalid_305) {
  std::string value;
  bool result = db_->GetProperty("leveldb.nonexistent-property", &value);
  EXPECT_FALSE(result);
}

// Test GetProperty stats
TEST_F(DBImplTest_305, GetPropertyStats_305) {
  std::string value;
  bool result = db_->GetProperty("leveldb.stats", &value);
  EXPECT_TRUE(result);
  EXPECT_FALSE(value.empty());
}

// Test GetApproximateSizes
TEST_F(DBImplTest_305, GetApproximateSizesEmpty_305) {
  Range range("a", "z");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  EXPECT_EQ(0, size);
}

// Test GetApproximateSizes with data
TEST_F(DBImplTest_305, GetApproximateSizesWithData_305) {
  WriteOptions wo;
  // Insert enough data
  for (int i = 0; i < 1000; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(wo, key, std::string(1000, 'v')).ok());
  }

  // Flush to disk
  ASSERT_TRUE(impl()->TEST_CompactMemTable().ok());

  Range range("key000000", "key999999");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // Should be non-zero after inserting data and flushing
  EXPECT_GT(size, 0);
}

// Test CompactRange
TEST_F(DBImplTest_305, CompactRangeFull_305) {
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(wo, key, std::string(100, 'x')).ok());
  }

  // Compact all
  db_->CompactRange(nullptr, nullptr);

  // Verify data is still accessible
  ReadOptions ro;
  std::string value;
  ASSERT_TRUE(db_->Get(ro, "key0", &value).ok());
  EXPECT_EQ(std::string(100, 'x'), value);
}

// Test TEST_CompactMemTable
TEST_F(DBImplTest_305, CompactMemTable_305) {
  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "memkey", "memval").ok());

  Status s = impl()->TEST_CompactMemTable();
  EXPECT_TRUE(s.ok());

  ReadOptions ro;
  std::string value;
  ASSERT_TRUE(db_->Get(ro, "memkey", &value).ok());
  EXPECT_EQ("memval", value);
}

// Test TEST_NewInternalIterator
TEST_F(DBImplTest_305, NewInternalIterator_305) {
  WriteOptions wo;
  ASSERT_TRUE(db_->Put(wo, "ikey", "ival").ok());

  Iterator* it = impl()->TEST_NewInternalIterator();
  ASSERT_NE(it, nullptr);
  it->SeekToFirst();
  EXPECT_TRUE(it->Valid());
  delete it;
}

// Test TEST_CompactRange
TEST_F(DBImplTest_305, TestCompactRange_305) {
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "cr%06d", i);
    ASSERT_TRUE(db_->Put(wo, key, std::string(100, 'a')).ok());
  }
  ASSERT_TRUE(impl()->TEST_CompactMemTable().ok());

  Slice begin("cr000000");
  Slice end("cr000099");
  impl()->TEST_CompactRange(0, &begin, &end);

  // Data should still be accessible
  ReadOptions ro;
  std::string value;
  ASSERT_TRUE(db_->Get(ro, "cr000050", &value).ok());
}

// Test MaxNextLevelOverlappingBytes with multiple levels of compaction
TEST_F(DBImplTest_305, MaxNextLevelOverlappingBytesWithMultipleLevels_305) {
  WriteOptions wo;
  // Write and compact multiple times to populate different levels
  for (int round = 0; round < 5; round++) {
    for (int i = 0; i < 200; i++) {
      char key[100];
      snprintf(key, sizeof(key), "mlkey%06d", i);
      ASSERT_TRUE(db_->Put(wo, key, std::string(100, 'v')).ok());
    }
    ASSERT_TRUE(impl()->TEST_CompactMemTable().ok());
  }

  int64_t result = impl()->TEST_MaxNextLevelOverlappingBytes();
  EXPECT_GE(result, 0);
}

// Test that MaxNextLevelOverlappingBytes is consistent across calls
TEST_F(DBImplTest_305, MaxNextLevelOverlappingBytesConsistency_305) {
  WriteOptions wo;
  for (int i = 0; i < 50; i++) {
    ASSERT_TRUE(db_->Put(wo, "ckey" + std::to_string(i), "cval").ok());
  }
  ASSERT_TRUE(impl()->TEST_CompactMemTable().ok());

  int64_t result1 = impl()->TEST_MaxNextLevelOverlappingBytes();
  int64_t result2 = impl()->TEST_MaxNextLevelOverlappingBytes();
  // Without any writes in between, the result should be the same
  EXPECT_EQ(result1, result2);
}

// Test overwriting values
TEST_F(DBImplTest_305, OverwriteValue_305) {
  WriteOptions wo;
  ReadOptions ro;

  ASSERT_TRUE(db_->Put(wo, "owkey", "first").ok());
  ASSERT_TRUE(db_->Put(wo, "owkey", "second").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ro, "owkey", &value).ok());
  EXPECT_EQ("second", value);
}

// Test empty key and value
TEST_F(DBImplTest_305, EmptyKeyAndValue_305) {
  WriteOptions wo;
  ReadOptions ro;

  ASSERT_TRUE(db_->Put(wo, "", "").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ro, "", &value).ok());
  EXPECT_EQ("", value);
}

// Test large value
TEST_F(DBImplTest_305, LargeValue_305) {
  WriteOptions wo;
  ReadOptions ro;

  std::string large_val(100000, 'L');
  ASSERT_TRUE(db_->Put(wo, "largekey", large_val).ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ro, "largekey", &value).ok());
  EXPECT_EQ(large_val, value);
}

// Test GetProperty for sstables
TEST_F(DBImplTest_305, GetPropertySSTables_305) {
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    ASSERT_TRUE(db_->Put(wo, "sstkey" + std::to_string(i), "val").ok());
  }
  ASSERT_TRUE(impl()->TEST_CompactMemTable().ok());

  std::string value;
  bool result = db_->GetProperty("leveldb.sstables", &value);
  EXPECT_TRUE(result);
}

// Test GetProperty approximate-memory-usage
TEST_F(DBImplTest_305, GetPropertyApproxMemUsage_305) {
  std::string value;
  bool result = db_->GetProperty("leveldb.approximate-memory-usage", &value);
  EXPECT_TRUE(result);
  // Memory usage should be positive
  EXPECT_GT(std::stol(value), 0);
}

// Test multiple snapshots
TEST_F(DBImplTest_305, MultipleSnapshots_305) {
  WriteOptions wo;
  ReadOptions ro;

  ASSERT_TRUE(db_->Put(wo, "mskey", "v1").ok());
  const Snapshot* s1 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(wo, "mskey", "v2").ok());
  const Snapshot* s2 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(wo, "mskey", "v3").ok());

  std::string value;

  ro.snapshot = s1;
  ASSERT_TRUE(db_->Get(ro, "mskey", &value).ok());
  EXPECT_EQ("v1", value);

  ro.snapshot = s2;
  ASSERT_TRUE(db_->Get(ro, "mskey", &value).ok());
  EXPECT_EQ("v2", value);

  ro.snapshot = nullptr;
  ASSERT_TRUE(db_->Get(ro, "mskey", &value).ok());
  EXPECT_EQ("v3", value);

  db_->ReleaseSnapshot(s1);
  db_->ReleaseSnapshot(s2);
}

}  // namespace leveldb
