#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "leveldb/write_batch.h"
#include "db/db_impl.h"
#include "db/dbformat.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class DBImplTest_302 : public testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "dbimpl_test_302";
    options_.create_if_missing = true;
    // Use a fresh environment for each test
    DestroyDB(dbname_, options_);
    Status s = DB::Open(options_, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }

  DBImpl* impl() { return reinterpret_cast<DBImpl*>(db_); }

  void Put(const std::string& key, const std::string& value) {
    WriteOptions wo;
    Status s = db_->Put(wo, key, value);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  std::string Get(const std::string& key) {
    ReadOptions ro;
    std::string value;
    Status s = db_->Get(ro, key, &value);
    if (s.IsNotFound()) return "NOT_FOUND";
    EXPECT_TRUE(s.ok()) << s.ToString();
    return value;
  }

  void Delete(const std::string& key) {
    WriteOptions wo;
    Status s = db_->Delete(wo, key);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }
};

// Test basic put and get operations
TEST_F(DBImplTest_302, BasicPutGet_302) {
  Put("key1", "value1");
  ASSERT_EQ("value1", Get("key1"));
}

// Test that getting a non-existent key returns not found
TEST_F(DBImplTest_302, GetNonExistentKey_302) {
  ASSERT_EQ("NOT_FOUND", Get("nonexistent"));
}

// Test basic delete operation
TEST_F(DBImplTest_302, BasicDelete_302) {
  Put("key1", "value1");
  ASSERT_EQ("value1", Get("key1"));
  Delete("key1");
  ASSERT_EQ("NOT_FOUND", Get("key1"));
}

// Test overwriting a key
TEST_F(DBImplTest_302, OverwriteKey_302) {
  Put("key1", "value1");
  ASSERT_EQ("value1", Get("key1"));
  Put("key1", "value2");
  ASSERT_EQ("value2", Get("key1"));
}

// Test TEST_CompactRange with nullptr begin and end (compact entire level)
TEST_F(DBImplTest_302, CompactRangeNullBeginAndEnd_302) {
  // Insert some data
  for (int i = 0; i < 100; i++) {
    Put("key" + std::to_string(i), "value" + std::to_string(i));
  }
  // Flush memtable
  impl()->TEST_CompactMemTable();

  // Compact level 0 with null range (entire level)
  impl()->TEST_CompactRange(0, nullptr, nullptr);

  // Verify data is still accessible
  for (int i = 0; i < 100; i++) {
    ASSERT_EQ("value" + std::to_string(i), Get("key" + std::to_string(i)));
  }
}

// Test TEST_CompactRange with specific begin and end
TEST_F(DBImplTest_302, CompactRangeWithBeginAndEnd_302) {
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    Put(key, "value" + std::to_string(i));
  }
  impl()->TEST_CompactMemTable();

  Slice begin("key000020");
  Slice end("key000080");
  impl()->TEST_CompactRange(0, &begin, &end);

  // Verify data is still accessible
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_EQ("value" + std::to_string(i), Get(key));
  }
}

// Test TEST_CompactRange with only begin specified
TEST_F(DBImplTest_302, CompactRangeWithOnlyBegin_302) {
  for (int i = 0; i < 50; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    Put(key, "value" + std::to_string(i));
  }
  impl()->TEST_CompactMemTable();

  Slice begin("key000010");
  impl()->TEST_CompactRange(0, &begin, nullptr);

  for (int i = 0; i < 50; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_EQ("value" + std::to_string(i), Get(key));
  }
}

// Test TEST_CompactRange with only end specified
TEST_F(DBImplTest_302, CompactRangeWithOnlyEnd_302) {
  for (int i = 0; i < 50; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    Put(key, "value" + std::to_string(i));
  }
  impl()->TEST_CompactMemTable();

  Slice end("key000040");
  impl()->TEST_CompactRange(0, nullptr, &end);

  for (int i = 0; i < 50; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_EQ("value" + std::to_string(i), Get(key));
  }
}

// Test compacting at different levels
TEST_F(DBImplTest_302, CompactRangeMultipleLevels_302) {
  for (int i = 0; i < 200; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    Put(key, "value" + std::to_string(i));
  }
  impl()->TEST_CompactMemTable();

  // Compact through multiple levels
  for (int level = 0; level < config::kNumLevels - 1; level++) {
    impl()->TEST_CompactRange(level, nullptr, nullptr);
  }

  // Verify data integrity after multi-level compaction
  for (int i = 0; i < 200; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_EQ("value" + std::to_string(i), Get(key));
  }
}

// Test TEST_CompactMemTable
TEST_F(DBImplTest_302, CompactMemTable_302) {
  Put("memkey1", "memval1");
  Put("memkey2", "memval2");

  Status s = impl()->TEST_CompactMemTable();
  ASSERT_TRUE(s.ok()) << s.ToString();

  ASSERT_EQ("memval1", Get("memkey1"));
  ASSERT_EQ("memval2", Get("memkey2"));
}

// Test CompactRange public API
TEST_F(DBImplTest_302, PublicCompactRange_302) {
  for (int i = 0; i < 100; i++) {
    Put("key" + std::to_string(i), "value" + std::to_string(i));
  }

  Slice begin("key0");
  Slice end("key99");
  db_->CompactRange(&begin, &end);

  for (int i = 0; i < 100; i++) {
    ASSERT_EQ("value" + std::to_string(i), Get("key" + std::to_string(i)));
  }
}

// Test PublicCompactRange with null range
TEST_F(DBImplTest_302, PublicCompactRangeNull_302) {
  for (int i = 0; i < 50; i++) {
    Put("key" + std::to_string(i), "value" + std::to_string(i));
  }

  db_->CompactRange(nullptr, nullptr);

  for (int i = 0; i < 50; i++) {
    ASSERT_EQ("value" + std::to_string(i), Get("key" + std::to_string(i)));
  }
}

// Test Write with WriteBatch
TEST_F(DBImplTest_302, WriteBatch_302) {
  WriteBatch batch;
  batch.Put("bkey1", "bval1");
  batch.Put("bkey2", "bval2");
  batch.Delete("bkey1");

  WriteOptions wo;
  Status s = db_->Write(wo, &batch);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ASSERT_EQ("NOT_FOUND", Get("bkey1"));
  ASSERT_EQ("bval2", Get("bkey2"));
}

// Test Write with nullptr batch (should handle gracefully)
TEST_F(DBImplTest_302, WriteNullBatch_302) {
  WriteOptions wo;
  Status s = db_->Write(wo, nullptr);
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test GetSnapshot and ReleaseSnapshot
TEST_F(DBImplTest_302, SnapshotOperations_302) {
  Put("snapkey", "val1");
  const Snapshot* snap = db_->GetSnapshot();
  ASSERT_NE(snap, nullptr);

  Put("snapkey", "val2");

  // Read with snapshot should see old value
  ReadOptions ro;
  ro.snapshot = snap;
  std::string value;
  Status s = db_->Get(ro, "snapkey", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("val1", value);

  // Read without snapshot should see new value
  ASSERT_EQ("val2", Get("snapkey"));

  db_->ReleaseSnapshot(snap);
}

// Test GetProperty
TEST_F(DBImplTest_302, GetPropertyStats_302) {
  std::string stats;
  bool result = db_->GetProperty("leveldb.stats", &stats);
  ASSERT_TRUE(result);
  ASSERT_FALSE(stats.empty());
}

// Test GetProperty with num-files-at-level
TEST_F(DBImplTest_302, GetPropertyNumFiles_302) {
  std::string value;
  bool result = db_->GetProperty("leveldb.num-files-at-level0", &value);
  ASSERT_TRUE(result);
}

// Test GetProperty with invalid property
TEST_F(DBImplTest_302, GetPropertyInvalid_302) {
  std::string value;
  bool result = db_->GetProperty("leveldb.nonexistent", &value);
  ASSERT_FALSE(result);
}

// Test GetApproximateSizes
TEST_F(DBImplTest_302, GetApproximateSizes_302) {
  // Insert enough data to get meaningful sizes
  for (int i = 0; i < 1000; i++) {
    char key[100];
    snprintf(key, sizeof(key), "sizekey%06d", i);
    Put(key, std::string(100, 'v'));
  }
  impl()->TEST_CompactMemTable();

  Range range("sizekey000000", "sizekey001000");
  uint64_t size;
  db_->GetApproximateSizes(&range, 1, &size);
  // We just verify the call doesn't crash; size depends on implementation
  ASSERT_GE(size, 0u);
}

// Test NewIterator
TEST_F(DBImplTest_302, NewIterator_302) {
  Put("iter1", "val1");
  Put("iter2", "val2");
  Put("iter3", "val3");

  ReadOptions ro;
  Iterator* iter = db_->NewIterator(ro);
  ASSERT_NE(iter, nullptr);

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  ASSERT_EQ(3, count);
  ASSERT_TRUE(iter->status().ok());

  delete iter;
}

// Test iterator seeking
TEST_F(DBImplTest_302, IteratorSeek_302) {
  Put("a", "va");
  Put("b", "vb");
  Put("c", "vc");

  ReadOptions ro;
  Iterator* iter = db_->NewIterator(ro);

  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ("b", iter->key().ToString());
  ASSERT_EQ("vb", iter->value().ToString());

  delete iter;
}

// Test empty database iterator
TEST_F(DBImplTest_302, EmptyIterator_302) {
  ReadOptions ro;
  Iterator* iter = db_->NewIterator(ro);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test TEST_MaxNextLevelOverlappingBytes
TEST_F(DBImplTest_302, MaxNextLevelOverlappingBytes_302) {
  int64_t result = impl()->TEST_MaxNextLevelOverlappingBytes();
  ASSERT_GE(result, 0);
}

// Test compacting after deletes
TEST_F(DBImplTest_302, CompactAfterDeletes_302) {
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "delkey%06d", i);
    Put(key, "value");
  }
  impl()->TEST_CompactMemTable();

  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "delkey%06d", i);
    Delete(key);
  }
  impl()->TEST_CompactMemTable();

  impl()->TEST_CompactRange(0, nullptr, nullptr);
  impl()->TEST_CompactRange(1, nullptr, nullptr);

  // All keys should be deleted
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "delkey%06d", i);
    ASSERT_EQ("NOT_FOUND", Get(key));
  }
}

// Test compacting at the highest valid level
TEST_F(DBImplTest_302, CompactRangeHighestLevel_302) {
  Put("highkey", "highval");
  impl()->TEST_CompactMemTable();

  // config::kNumLevels is 7, so max level for TEST_CompactRange is 5 (level + 1 < 7)
  impl()->TEST_CompactRange(config::kNumLevels - 2, nullptr, nullptr);

  ASSERT_EQ("highval", Get("highkey"));
}

// Test compacting level 0
TEST_F(DBImplTest_302, CompactRangeLevel0_302) {
  for (int i = 0; i < 50; i++) {
    Put("l0key" + std::to_string(i), "val" + std::to_string(i));
  }
  impl()->TEST_CompactMemTable();

  impl()->TEST_CompactRange(0, nullptr, nullptr);

  for (int i = 0; i < 50; i++) {
    ASSERT_EQ("val" + std::to_string(i), Get("l0key" + std::to_string(i)));
  }
}

// Test with sync write option
TEST_F(DBImplTest_302, SyncWrite_302) {
  WriteOptions wo;
  wo.sync = true;
  Status s = db_->Put(wo, "synckey", "syncval");
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_EQ("syncval", Get("synckey"));
}

// Test with large values
TEST_F(DBImplTest_302, LargeValues_302) {
  std::string large_value(100000, 'x');
  Put("largekey", large_value);
  ASSERT_EQ(large_value, Get("largekey"));
}

// Test with empty key and value
TEST_F(DBImplTest_302, EmptyKeyValue_302) {
  Put("", "emptykey_value");
  ASSERT_EQ("emptykey_value", Get(""));

  Put("emptyval_key", "");
  ASSERT_EQ("", Get("emptyval_key"));
}

// Test reopening the database preserves data
TEST_F(DBImplTest_302, ReopenPreservesData_302) {
  Put("persist1", "pval1");
  Put("persist2", "pval2");

  delete db_;
  db_ = nullptr;

  Status s = DB::Open(options_, dbname_, &db_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ASSERT_EQ("pval1", Get("persist1"));
  ASSERT_EQ("pval2", Get("persist2"));
}

// Test TEST_NewInternalIterator
TEST_F(DBImplTest_302, TestNewInternalIterator_302) {
  Put("ikey1", "ival1");
  Put("ikey2", "ival2");

  Iterator* iter = impl()->TEST_NewInternalIterator();
  ASSERT_NE(iter, nullptr);

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  ASSERT_GT(count, 0);

  delete iter;
}

// Test multiple snapshots
TEST_F(DBImplTest_302, MultipleSnapshots_302) {
  Put("mkey", "v1");
  const Snapshot* s1 = db_->GetSnapshot();

  Put("mkey", "v2");
  const Snapshot* s2 = db_->GetSnapshot();

  Put("mkey", "v3");

  ReadOptions ro;
  std::string value;

  ro.snapshot = s1;
  ASSERT_TRUE(db_->Get(ro, "mkey", &value).ok());
  ASSERT_EQ("v1", value);

  ro.snapshot = s2;
  ASSERT_TRUE(db_->Get(ro, "mkey", &value).ok());
  ASSERT_EQ("v2", value);

  ro.snapshot = nullptr;
  ASSERT_TRUE(db_->Get(ro, "mkey", &value).ok());
  ASSERT_EQ("v3", value);

  db_->ReleaseSnapshot(s1);
  db_->ReleaseSnapshot(s2);
}

}  // namespace leveldb
