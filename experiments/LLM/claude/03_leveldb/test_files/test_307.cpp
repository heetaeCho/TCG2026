#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/iterator.h"
#include "leveldb/write_batch.h"
#include "db/db_impl.h"
#include "db/snapshot.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class DBImplTest_307 : public ::testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "dbimpl_test_307";
    options_.create_if_missing = true;
    DestroyDB(dbname_, options_);
    Status s = DB::Open(options_, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }
};

// Test: NewIterator returns a non-null iterator on an empty database
TEST_F(DBImplTest_307, NewIteratorOnEmptyDB_307) {
  ReadOptions read_opts;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);
  EXPECT_TRUE(iter->status().ok());
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test: NewIterator can iterate over inserted data
TEST_F(DBImplTest_307, NewIteratorSeesInsertedData_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "key1", "value1").ok());
  ASSERT_TRUE(db_->Put(write_opts, "key2", "value2").ok());
  ASSERT_TRUE(db_->Put(write_opts, "key3", "value3").ok());

  ReadOptions read_opts;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "value1");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().ToString(), "value2");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key3");
  EXPECT_EQ(iter->value().ToString(), "value3");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: NewIterator with snapshot sees only data at the snapshot point
TEST_F(DBImplTest_307, NewIteratorWithSnapshot_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "key1", "value1").ok());

  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  // Write more data after the snapshot
  ASSERT_TRUE(db_->Put(write_opts, "key2", "value2").ok());

  // Iterator with snapshot should only see key1
  ReadOptions read_opts;
  read_opts.snapshot = snap;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "value1");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;

  // Iterator without snapshot should see both keys
  ReadOptions read_opts2;
  Iterator* iter2 = db_->NewIterator(read_opts2);
  ASSERT_NE(iter2, nullptr);

  int count = 0;
  for (iter2->SeekToFirst(); iter2->Valid(); iter2->Next()) {
    count++;
  }
  EXPECT_EQ(count, 2);

  delete iter2;
  db_->ReleaseSnapshot(snap);
}

// Test: NewIterator reflects deleted keys
TEST_F(DBImplTest_307, NewIteratorAfterDelete_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "key1", "value1").ok());
  ASSERT_TRUE(db_->Put(write_opts, "key2", "value2").ok());
  ASSERT_TRUE(db_->Delete(write_opts, "key1").ok());

  ReadOptions read_opts;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().ToString(), "value2");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: NewIterator reflects overwritten values
TEST_F(DBImplTest_307, NewIteratorSeesLatestValue_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "key1", "old_value").ok());
  ASSERT_TRUE(db_->Put(write_opts, "key1", "new_value").ok());

  ReadOptions read_opts;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "new_value");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: NewIterator supports SeekToLast and reverse iteration
TEST_F(DBImplTest_307, NewIteratorReverseIteration_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "a", "1").ok());
  ASSERT_TRUE(db_->Put(write_opts, "b", "2").ok());
  ASSERT_TRUE(db_->Put(write_opts, "c", "3").ok());

  ReadOptions read_opts;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: NewIterator Seek to a specific key
TEST_F(DBImplTest_307, NewIteratorSeek_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "apple", "1").ok());
  ASSERT_TRUE(db_->Put(write_opts, "banana", "2").ok());
  ASSERT_TRUE(db_->Put(write_opts, "cherry", "3").ok());

  ReadOptions read_opts;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->Seek("banana");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "banana");
  EXPECT_EQ(iter->value().ToString(), "2");

  delete iter;
}

// Test: NewIterator Seek past all keys returns invalid
TEST_F(DBImplTest_307, NewIteratorSeekPastEnd_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "a", "1").ok());
  ASSERT_TRUE(db_->Put(write_opts, "b", "2").ok());

  ReadOptions read_opts;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->Seek("z");
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Snapshot-based iterator does not see deleted keys after snapshot
TEST_F(DBImplTest_307, NewIteratorSnapshotDoesNotSeeDeletes_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "key1", "value1").ok());
  ASSERT_TRUE(db_->Put(write_opts, "key2", "value2").ok());

  const Snapshot* snap = db_->GetSnapshot();

  ASSERT_TRUE(db_->Delete(write_opts, "key1").ok());

  // With snapshot, key1 should still be visible
  ReadOptions read_opts;
  read_opts.snapshot = snap;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "value1");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  db_->ReleaseSnapshot(snap);
}

// Test: Multiple iterators can coexist
TEST_F(DBImplTest_307, MultipleIterators_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "key1", "value1").ok());

  ReadOptions read_opts;
  Iterator* iter1 = db_->NewIterator(read_opts);
  Iterator* iter2 = db_->NewIterator(read_opts);

  ASSERT_NE(iter1, nullptr);
  ASSERT_NE(iter2, nullptr);

  iter1->SeekToFirst();
  iter2->SeekToFirst();

  ASSERT_TRUE(iter1->Valid());
  ASSERT_TRUE(iter2->Valid());
  EXPECT_EQ(iter1->key().ToString(), "key1");
  EXPECT_EQ(iter2->key().ToString(), "key1");

  delete iter1;
  delete iter2;
}

// Test: Put, Get, Delete basic operations
TEST_F(DBImplTest_307, BasicPutGetDelete_307) {
  WriteOptions write_opts;
  ReadOptions read_opts;
  std::string value;

  ASSERT_TRUE(db_->Put(write_opts, "testkey", "testvalue").ok());

  Status s = db_->Get(read_opts, "testkey", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "testvalue");

  ASSERT_TRUE(db_->Delete(write_opts, "testkey").ok());

  s = db_->Get(read_opts, "testkey", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Get on non-existent key returns NotFound
TEST_F(DBImplTest_307, GetNonExistentKey_307) {
  ReadOptions read_opts;
  std::string value;
  Status s = db_->Get(read_opts, "nonexistent", &value);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: GetSnapshot and ReleaseSnapshot
TEST_F(DBImplTest_307, SnapshotGetRelease_307) {
  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);
  db_->ReleaseSnapshot(snap);
}

// Test: WriteBatch atomicity
TEST_F(DBImplTest_307, WriteBatchAtomicity_307) {
  WriteBatch batch;
  batch.Put("bk1", "bv1");
  batch.Put("bk2", "bv2");
  batch.Delete("bk1");

  WriteOptions write_opts;
  ASSERT_TRUE(db_->Write(write_opts, &batch).ok());

  ReadOptions read_opts;
  std::string value;
  Status s = db_->Get(read_opts, "bk1", &value);
  EXPECT_TRUE(s.IsNotFound());

  s = db_->Get(read_opts, "bk2", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(value, "bv2");
}

// Test: Iterator with many keys
TEST_F(DBImplTest_307, NewIteratorManyKeys_307) {
  WriteOptions write_opts;
  const int kNumKeys = 100;
  for (int i = 0; i < kNumKeys; i++) {
    char key[32];
    char val[32];
    std::snprintf(key, sizeof(key), "key%06d", i);
    std::snprintf(val, sizeof(val), "val%06d", i);
    ASSERT_TRUE(db_->Put(write_opts, key, val).ok());
  }

  ReadOptions read_opts;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(count, kNumKeys);
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test: GetProperty for known properties
TEST_F(DBImplTest_307, GetPropertyNumFilesAtLevel_307) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  EXPECT_TRUE(result);
}

// Test: GetProperty for unknown property returns false
TEST_F(DBImplTest_307, GetPropertyUnknown_307) {
  std::string value;
  bool result = db_->GetProperty("leveldb.unknown-property", &value);
  EXPECT_FALSE(result);
}

// Test: GetApproximateSizes
TEST_F(DBImplTest_307, GetApproximateSizes_307) {
  WriteOptions write_opts;
  for (int i = 0; i < 100; i++) {
    char key[32];
    std::snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(write_opts, key, std::string(100, 'x')).ok());
  }

  Range range("key000000", "key000099");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // Size should be non-negative (could be 0 if not flushed)
  EXPECT_GE(size, 0u);
}

// Test: Iterator status is ok after normal iteration
TEST_F(DBImplTest_307, NewIteratorStatusOk_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "k", "v").ok());

  ReadOptions read_opts;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
  }
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test: Snapshot-based iterator with overwritten values
TEST_F(DBImplTest_307, NewIteratorSnapshotOverwrite_307) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "key1", "old_value").ok());

  const Snapshot* snap = db_->GetSnapshot();

  ASSERT_TRUE(db_->Put(write_opts, "key1", "new_value").ok());

  // With snapshot, should see old value
  ReadOptions read_opts;
  read_opts.snapshot = snap;
  Iterator* iter = db_->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "old_value");

  delete iter;

  // Without snapshot, should see new value
  ReadOptions read_opts2;
  Iterator* iter2 = db_->NewIterator(read_opts2);
  iter2->SeekToFirst();
  ASSERT_TRUE(iter2->Valid());
  EXPECT_EQ(iter2->key().ToString(), "key1");
  EXPECT_EQ(iter2->value().ToString(), "new_value");

  delete iter2;
  db_->ReleaseSnapshot(snap);
}

}  // namespace leveldb
