#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include "leveldb/env.h"
#include "db/db_impl.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class DBImplTest_310 : public testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "dbimpl_test_310";
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
};

// Test: GetSnapshot returns a non-null snapshot
TEST_F(DBImplTest_310, GetSnapshotReturnsNonNull_310) {
  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);
  db_->ReleaseSnapshot(snap);
}

// Test: ReleaseSnapshot does not crash when releasing a valid snapshot
TEST_F(DBImplTest_310, ReleaseSnapshotValidSnapshot_310) {
  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);
  EXPECT_NO_FATAL_FAILURE(db_->ReleaseSnapshot(snap));
}

// Test: Multiple snapshots can be obtained and released
TEST_F(DBImplTest_310, MultipleSnapshotsGetAndRelease_310) {
  const Snapshot* snap1 = db_->GetSnapshot();
  const Snapshot* snap2 = db_->GetSnapshot();
  const Snapshot* snap3 = db_->GetSnapshot();
  ASSERT_NE(snap1, nullptr);
  ASSERT_NE(snap2, nullptr);
  ASSERT_NE(snap3, nullptr);

  db_->ReleaseSnapshot(snap2);
  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap3);
}

// Test: Snapshot preserves data state at time of creation
TEST_F(DBImplTest_310, SnapshotPreservesDataState_310) {
  // Write initial data
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value1").ok());

  // Take snapshot
  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  // Modify data after snapshot
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "value2").ok());

  // Read with snapshot should see old value
  ReadOptions read_opts;
  read_opts.snapshot = snap;
  std::string value;
  Status s = db_->Get(read_opts, "key1", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "value1");

  // Read without snapshot should see new value
  s = db_->Get(ReadOptions(), "key1", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "value2");

  db_->ReleaseSnapshot(snap);
}

// Test: Put and Get basic functionality
TEST_F(DBImplTest_310, PutAndGetBasic_310) {
  Status s = db_->Put(WriteOptions(), "hello", "world");
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(ReadOptions(), "hello", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "world");
}

// Test: Delete removes a key
TEST_F(DBImplTest_310, DeleteRemovesKey_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "val").ok());
  ASSERT_TRUE(db_->Delete(WriteOptions(), "key").ok());

  std::string value;
  Status s = db_->Get(ReadOptions(), "key", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Get on non-existent key returns NotFound
TEST_F(DBImplTest_310, GetNonExistentKeyReturnsNotFound_310) {
  std::string value;
  Status s = db_->Get(ReadOptions(), "nonexistent", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Write with WriteBatch
TEST_F(DBImplTest_310, WriteBatchMultipleOperations_310) {
  WriteBatch batch;
  batch.Put("key1", "val1");
  batch.Put("key2", "val2");
  batch.Delete("key1");

  Status s = db_->Write(WriteOptions(), &batch);
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(ReadOptions(), "key1", &value);
  EXPECT_TRUE(s.IsNotFound());

  s = db_->Get(ReadOptions(), "key2", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "val2");
}

// Test: Write with null batch
TEST_F(DBImplTest_310, WriteNullBatch_310) {
  Status s = db_->Write(WriteOptions(), nullptr);
  EXPECT_TRUE(s.ok());
}

// Test: NewIterator returns valid iterator
TEST_F(DBImplTest_310, NewIteratorBasic_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());

  Iterator* iter = db_->NewIterator(ReadOptions());
  ASSERT_NE(iter, nullptr);

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(count, 3);
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test: NewIterator on empty DB
TEST_F(DBImplTest_310, NewIteratorEmptyDB_310) {
  Iterator* iter = db_->NewIterator(ReadOptions());
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Iterator with snapshot
TEST_F(DBImplTest_310, NewIteratorWithSnapshot_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "val1").ok());
  const Snapshot* snap = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(WriteOptions(), "key2", "val2").ok());

  ReadOptions read_opts;
  read_opts.snapshot = snap;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(count, 1);

  delete iter;
  db_->ReleaseSnapshot(snap);
}

// Test: Overwrite existing key
TEST_F(DBImplTest_310, OverwriteExistingKey_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "first").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "second").ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "key", &value).ok());
  EXPECT_EQ(value, "second");
}

// Test: GetProperty with valid property
TEST_F(DBImplTest_310, GetPropertyNumFilesAtLevel_310) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  EXPECT_TRUE(result);
}

// Test: GetProperty with invalid property
TEST_F(DBImplTest_310, GetPropertyInvalidProperty_310) {
  std::string value;
  bool result = db_->GetProperty("leveldb.nonexistent-property", &value);
  EXPECT_FALSE(result);
}

// Test: GetProperty stats
TEST_F(DBImplTest_310, GetPropertyStats_310) {
  std::string value;
  bool result = db_->GetProperty("leveldb.stats", &value);
  EXPECT_TRUE(result);
  EXPECT_FALSE(value.empty());
}

// Test: GetApproximateSizes
TEST_F(DBImplTest_310, GetApproximateSizesBasic_310) {
  // Write some data
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = std::string(100, 'x');
    ASSERT_TRUE(db_->Put(WriteOptions(), key, val).ok());
  }

  Range range("key0", "key99");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // Size should be non-negative (could be 0 if not flushed)
  EXPECT_GE(size, 0u);
}

// Test: CompactRange does not crash
TEST_F(DBImplTest_310, CompactRangeFullDB_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "z", "2").ok());

  EXPECT_NO_FATAL_FAILURE(db_->CompactRange(nullptr, nullptr));
}

// Test: CompactRange with specific range
TEST_F(DBImplTest_310, CompactRangeWithBounds_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "m", "2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "z", "3").ok());

  Slice begin("a");
  Slice end("m");
  EXPECT_NO_FATAL_FAILURE(db_->CompactRange(&begin, &end));
}

// Test: Snapshot after delete shows deleted key
TEST_F(DBImplTest_310, SnapshotAfterDelete_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "value").ok());
  const Snapshot* snap = db_->GetSnapshot();

  ASSERT_TRUE(db_->Delete(WriteOptions(), "key").ok());

  // Snapshot should still see the key
  ReadOptions ro;
  ro.snapshot = snap;
  std::string value;
  Status s = db_->Get(ro, "key", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "value");

  // Without snapshot, key should be gone
  s = db_->Get(ReadOptions(), "key", &value);
  EXPECT_TRUE(s.IsNotFound());

  db_->ReleaseSnapshot(snap);
}

// Test: Put with sync write option
TEST_F(DBImplTest_310, PutWithSyncOption_310) {
  WriteOptions wo;
  wo.sync = true;
  Status s = db_->Put(wo, "synckey", "syncval");
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(ReadOptions(), "synckey", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "syncval");
}

// Test: Large number of puts
TEST_F(DBImplTest_310, ManyPuts_310) {
  const int kNumEntries = 1000;
  for (int i = 0; i < kNumEntries; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, val).ok());
  }

  for (int i = 0; i < kNumEntries; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected = "val" + std::to_string(i);
    std::string value;
    ASSERT_TRUE(db_->Get(ReadOptions(), key, &value).ok());
    EXPECT_EQ(value, expected);
  }
}

// Test: Empty key and value
TEST_F(DBImplTest_310, EmptyKeyAndValue_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "", "").ok());
  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "", &value).ok());
  EXPECT_EQ(value, "");
}

// Test: Large value
TEST_F(DBImplTest_310, LargeValue_310) {
  std::string large_val(100000, 'A');
  ASSERT_TRUE(db_->Put(WriteOptions(), "bigkey", large_val).ok());

  std::string value;
  ASSERT_TRUE(db_->Get(ReadOptions(), "bigkey", &value).ok());
  EXPECT_EQ(value, large_val);
}

// Test: Delete non-existent key is ok
TEST_F(DBImplTest_310, DeleteNonExistentKey_310) {
  Status s = db_->Delete(WriteOptions(), "nonexistent");
  EXPECT_TRUE(s.ok());
}

// Test: Snapshot ordering - multiple snapshots see correct data
TEST_F(DBImplTest_310, MultipleSnapshotsOrdering_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "v1").ok());
  const Snapshot* snap1 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "v2").ok());
  const Snapshot* snap2 = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "v3").ok());

  ReadOptions ro1, ro2;
  ro1.snapshot = snap1;
  ro2.snapshot = snap2;

  std::string value;
  ASSERT_TRUE(db_->Get(ro1, "key", &value).ok());
  EXPECT_EQ(value, "v1");

  ASSERT_TRUE(db_->Get(ro2, "key", &value).ok());
  EXPECT_EQ(value, "v2");

  ASSERT_TRUE(db_->Get(ReadOptions(), "key", &value).ok());
  EXPECT_EQ(value, "v3");

  db_->ReleaseSnapshot(snap1);
  db_->ReleaseSnapshot(snap2);
}

// Test: Iterator SeekToLast
TEST_F(DBImplTest_310, IteratorSeekToLast_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");
  EXPECT_EQ(iter->value().ToString(), "3");

  delete iter;
}

// Test: Iterator Seek
TEST_F(DBImplTest_310, IteratorSeek_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "e", "5").ok());

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  iter->Seek("d");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "e");

  iter->Seek("f");
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Reopen database preserves data
TEST_F(DBImplTest_310, ReopenPreservesData_310) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "persist", "data").ok());
  delete db_;
  db_ = nullptr;

  Status s = DB::Open(options_, dbname_, &db_);
  ASSERT_TRUE(s.ok());

  std::string value;
  s = db_->Get(ReadOptions(), "persist", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "data");
}

// Test: GetApproximateSizes with multiple ranges
TEST_F(DBImplTest_310, GetApproximateSizesMultipleRanges_310) {
  Range ranges[2];
  ranges[0] = Range("a", "m");
  ranges[1] = Range("m", "z");
  uint64_t sizes[2];
  db_->GetApproximateSizes(ranges, 2, sizes);
  // Just verify it doesn't crash and returns non-negative values
  EXPECT_GE(sizes[0], 0u);
  EXPECT_GE(sizes[1], 0u);
}

}  // namespace leveldb
