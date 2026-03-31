#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/testutil.h"
#include "util/testharness.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"
#include "leveldb/table.h"
#include "leveldb/db.h"

#include <memory>
#include <string>
#include <vector>

namespace leveldb {

class CompactRangeTest_177 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "compactrange_test_177";
    
    // Clean up any previous state
    DestroyDB(dbname_, Options());
    
    // Create the database directory
    env_->CreateDir(dbname_);
    
    options_.env = env_;
    options_.comparator = BytewiseComparator();
    
    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(options_.comparator);
    versions_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
    
    // We need to recover or initialize the version set
    bool save_manifest = false;
    Status s = versions_->Recover(&save_manifest);
    // If recover fails because no CURRENT file, we create a fresh DB
    if (!s.ok()) {
      // Create a fresh database
      DestroyDB(dbname_, options_);
      DB* db = nullptr;
      Options opts;
      opts.create_if_missing = true;
      opts.env = env_;
      s = DB::Open(opts, dbname_, &db);
      if (db) {
        delete db;
        db = nullptr;
      }
      // Re-create version set
      delete versions_;
      delete table_cache_;
      table_cache_ = new TableCache(dbname_, &options_, 100);
      versions_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
      s = versions_->Recover(&save_manifest);
    }
  }

  void TearDown() override {
    delete versions_;
    delete table_cache_;
    delete icmp_;
    DestroyDB(dbname_, Options());
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
  VersionSet* versions_;
};

// Test that CompactRange returns nullptr when there are no overlapping files
TEST_F(CompactRangeTest_177, ReturnsNullWhenNoOverlappingFiles_177) {
  InternalKey begin("a", 100, kTypeValue);
  InternalKey end("z", 100, kTypeValue);
  
  // On a fresh database, there should be no files at any level
  Compaction* c = versions_->CompactRange(0, &begin, &end);
  // With no files, should return nullptr
  EXPECT_EQ(c, nullptr);
}

// Test CompactRange with nullptr begin and end (full range)
TEST_F(CompactRangeTest_177, ReturnsNullWithNullRangeAndNoFiles_177) {
  Compaction* c = versions_->CompactRange(0, nullptr, nullptr);
  EXPECT_EQ(c, nullptr);
}

// Test CompactRange at different levels with no files
TEST_F(CompactRangeTest_177, ReturnsNullAtVariousLevelsWithNoFiles_177) {
  InternalKey begin("a", 100, kTypeValue);
  InternalKey end("z", 100, kTypeValue);
  
  for (int level = 0; level < config::kNumLevels - 1; level++) {
    Compaction* c = versions_->CompactRange(level, &begin, &end);
    EXPECT_EQ(c, nullptr) << "Expected nullptr at level " << level;
  }
}

// Test CompactRange with nullptr begin
TEST_F(CompactRangeTest_177, ReturnsNullWithNullBeginAndNoFiles_177) {
  InternalKey end("z", 100, kTypeValue);
  Compaction* c = versions_->CompactRange(0, nullptr, &end);
  EXPECT_EQ(c, nullptr);
}

// Test CompactRange with nullptr end
TEST_F(CompactRangeTest_177, ReturnsNullWithNullEndAndNoFiles_177) {
  InternalKey begin("a", 100, kTypeValue);
  Compaction* c = versions_->CompactRange(0, &begin, nullptr);
  EXPECT_EQ(c, nullptr);
}

// Integration test: create a DB with data, then test CompactRange
class CompactRangeWithDataTest_177 : public ::testing::Test {
 protected:
  void SetUp() override {
    dbname_ = testing::TempDir() + "compactrange_data_test_177";
    DestroyDB(dbname_, Options());
    
    Options opts;
    opts.create_if_missing = true;
    Status s = DB::Open(opts, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, Options());
  }

  std::string dbname_;
  DB* db_;
};

// Test that after writing data and compacting, the database is still consistent
TEST_F(CompactRangeWithDataTest_177, CompactRangeViaDBInterface_177) {
  // Write some data
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    ASSERT_TRUE(db_->Put(wo, key, val).ok());
  }
  
  // Use DB::CompactRange which internally uses VersionSet::CompactRange
  Slice begin("key0");
  Slice end("key99");
  db_->CompactRange(&begin, &end);
  
  // Verify data is still accessible
  ReadOptions ro;
  std::string value;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    Status s = db_->Get(ro, key, &value);
    ASSERT_TRUE(s.ok()) << "Failed to get " << key << ": " << s.ToString();
    EXPECT_EQ(value, "value" + std::to_string(i));
  }
}

// Test full range compaction
TEST_F(CompactRangeWithDataTest_177, FullRangeCompaction_177) {
  WriteOptions wo;
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(wo, key, "val" + std::to_string(i)).ok());
  }
  
  // nullptr means compact everything
  db_->CompactRange(nullptr, nullptr);
  
  // Verify data integrity
  ReadOptions ro;
  std::string value;
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    Status s = db_->Get(ro, key, &value);
    ASSERT_TRUE(s.ok());
    EXPECT_EQ(value, "val" + std::to_string(i));
  }
}

// Test compaction on empty range
TEST_F(CompactRangeWithDataTest_177, CompactEmptyRange_177) {
  WriteOptions wo;
  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(db_->Put(wo, "aaa" + std::to_string(i), "val").ok());
  }
  
  // Compact a range that doesn't overlap with any data
  Slice begin("zzz0");
  Slice end("zzz9");
  db_->CompactRange(&begin, &end);
  
  // Original data should still be intact
  ReadOptions ro;
  std::string value;
  for (int i = 0; i < 10; i++) {
    Status s = db_->Get(ro, "aaa" + std::to_string(i), &value);
    ASSERT_TRUE(s.ok());
    EXPECT_EQ(value, "val");
  }
}

// Test compaction with large amount of data to potentially trigger file size limits
TEST_F(CompactRangeWithDataTest_177, CompactRangeWithLargeData_177) {
  WriteOptions wo;
  std::string large_value(10000, 'x');
  
  for (int i = 0; i < 200; i++) {
    char key[32];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(wo, key, large_value).ok());
  }
  
  // Force compaction
  db_->CompactRange(nullptr, nullptr);
  
  // Verify data
  ReadOptions ro;
  std::string value;
  for (int i = 0; i < 200; i++) {
    char key[32];
    snprintf(key, sizeof(key), "key%06d", i);
    Status s = db_->Get(ro, key, &value);
    ASSERT_TRUE(s.ok()) << "Failed for key: " << key;
    EXPECT_EQ(value, large_value);
  }
}

// Test partial range compaction
TEST_F(CompactRangeWithDataTest_177, PartialRangeCompaction_177) {
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    char key[32];
    snprintf(key, sizeof(key), "key%06d", i);
    ASSERT_TRUE(db_->Put(wo, key, "value" + std::to_string(i)).ok());
  }
  
  // Compact only a subset
  Slice begin("key000010");
  Slice end("key000050");
  db_->CompactRange(&begin, &end);
  
  // Verify all data still accessible
  ReadOptions ro;
  std::string value;
  for (int i = 0; i < 100; i++) {
    char key[32];
    snprintf(key, sizeof(key), "key%06d", i);
    Status s = db_->Get(ro, key, &value);
    ASSERT_TRUE(s.ok()) << "Failed for key: " << key;
  }
}

// Test multiple compactions in sequence
TEST_F(CompactRangeWithDataTest_177, MultipleSequentialCompactions_177) {
  WriteOptions wo;
  for (int i = 0; i < 50; i++) {
    ASSERT_TRUE(db_->Put(wo, "key" + std::to_string(i), "val" + std::to_string(i)).ok());
  }
  
  // Multiple compactions
  db_->CompactRange(nullptr, nullptr);
  db_->CompactRange(nullptr, nullptr);
  
  // Verify data
  ReadOptions ro;
  std::string value;
  for (int i = 0; i < 50; i++) {
    Status s = db_->Get(ro, "key" + std::to_string(i), &value);
    ASSERT_TRUE(s.ok());
    EXPECT_EQ(value, "val" + std::to_string(i));
  }
}

// Test that Compaction object properties are correct when obtained
TEST_F(CompactRangeWithDataTest_177, CompactionObjectProperties_177) {
  // This test just ensures that after writes and compaction, data remains consistent
  // and implicitly tests that any Compaction objects created have valid properties
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    char key[32];
    snprintf(key, sizeof(key), "key%06d", i);
    std::string val(1000, 'a' + (i % 26));
    ASSERT_TRUE(db_->Put(wo, key, val).ok());
  }
  
  Slice begin("key000000");
  Slice end("key000099");
  db_->CompactRange(&begin, &end);
  
  // Verify
  ReadOptions ro;
  std::string value;
  for (int i = 0; i < 100; i++) {
    char key[32];
    snprintf(key, sizeof(key), "key%06d", i);
    Status s = db_->Get(ro, key, &value);
    ASSERT_TRUE(s.ok());
    std::string expected(1000, 'a' + (i % 26));
    EXPECT_EQ(value, expected);
  }
}

// Test CompactRange after deletions
TEST_F(CompactRangeWithDataTest_177, CompactRangeAfterDeletions_177) {
  WriteOptions wo;
  for (int i = 0; i < 50; i++) {
    ASSERT_TRUE(db_->Put(wo, "key" + std::to_string(i), "val" + std::to_string(i)).ok());
  }
  
  // Delete some keys
  for (int i = 0; i < 25; i++) {
    ASSERT_TRUE(db_->Delete(wo, "key" + std::to_string(i)).ok());
  }
  
  // Compact
  db_->CompactRange(nullptr, nullptr);
  
  // Verify deleted keys are gone
  ReadOptions ro;
  std::string value;
  for (int i = 0; i < 25; i++) {
    Status s = db_->Get(ro, "key" + std::to_string(i), &value);
    EXPECT_TRUE(s.IsNotFound()) << "Key should be deleted: key" << i;
  }
  
  // Verify remaining keys
  for (int i = 25; i < 50; i++) {
    Status s = db_->Get(ro, "key" + std::to_string(i), &value);
    ASSERT_TRUE(s.ok());
    EXPECT_EQ(value, "val" + std::to_string(i));
  }
}

}  // namespace leveldb
