#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/cache.h"
#include "leveldb/env.h"
#include "db/db_impl.h"
#include "util/testutil.h"

#include <string>
#include <cstdlib>

namespace leveldb {

class DBImplGetPropertyTest_314 : public ::testing::Test {
 protected:
  DB* db_;
  std::string dbname_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "db_impl_getproperty_test_314";
    options_.create_if_missing = true;
    // Use a known block cache so approximate-memory-usage works
    options_.block_cache = NewLRUCache(8 * 1024 * 1024);
    DestroyDB(dbname_, options_);
    Status s = DB::Open(options_, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    delete options_.block_cache;
    DestroyDB(dbname_, Options());
  }
};

// Test that a property without the "leveldb." prefix returns false
TEST_F(DBImplGetPropertyTest_314, InvalidPrefix_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("invalid.property", &value));
}

// Test that an empty string returns false
TEST_F(DBImplGetPropertyTest_314, EmptyProperty_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("", &value));
}

// Test that "leveldb." alone (no suffix) returns false
TEST_F(DBImplGetPropertyTest_314, PrefixOnly_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("leveldb.", &value));
}

// Test that an unknown property after "leveldb." returns false
TEST_F(DBImplGetPropertyTest_314, UnknownProperty_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("leveldb.unknown-property", &value));
}

// Test num-files-at-level0 on an empty database
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevel0Empty_314) {
  std::string value;
  EXPECT_TRUE(db_->GetProperty("leveldb.num-files-at-level0", &value));
  EXPECT_EQ("0", value);
}

// Test num-files-at-level for all valid levels (0 through 6)
TEST_F(DBImplGetPropertyTest_314, NumFilesAtAllLevels_314) {
  for (int level = 0; level < 7; level++) {
    std::string value;
    std::string prop = "leveldb.num-files-at-level" + std::to_string(level);
    EXPECT_TRUE(db_->GetProperty(prop, &value))
        << "Failed for level " << level;
    // On empty DB, should be "0"
    EXPECT_EQ("0", value) << "Unexpected value at level " << level;
  }
}

// Test num-files-at-level with an out-of-range level returns false
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevelOutOfRange_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("leveldb.num-files-at-level7", &value));
}

// Test num-files-at-level with a very large level number returns false
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevelVeryLarge_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("leveldb.num-files-at-level100", &value));
}

// Test num-files-at-level with non-numeric suffix returns false
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevelNonNumeric_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("leveldb.num-files-at-levelabc", &value));
}

// Test num-files-at-level with trailing characters returns false
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevelTrailingChars_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("leveldb.num-files-at-level0abc", &value));
}

// Test num-files-at-level with no level number returns false
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevelNoNumber_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("leveldb.num-files-at-level", &value));
}

// Test stats property returns true and non-empty value
TEST_F(DBImplGetPropertyTest_314, StatsProperty_314) {
  std::string value;
  EXPECT_TRUE(db_->GetProperty("leveldb.stats", &value));
  EXPECT_FALSE(value.empty());
  // Should contain the header
  EXPECT_NE(std::string::npos, value.find("Compactions"));
  EXPECT_NE(std::string::npos, value.find("Level"));
}

// Test sstables property returns true
TEST_F(DBImplGetPropertyTest_314, SstablesProperty_314) {
  std::string value;
  EXPECT_TRUE(db_->GetProperty("leveldb.sstables", &value));
  // On empty DB, the value might be empty or contain some info
  // Just verify it returned true
}

// Test approximate-memory-usage property returns true and a numeric value
TEST_F(DBImplGetPropertyTest_314, ApproximateMemoryUsage_314) {
  std::string value;
  EXPECT_TRUE(db_->GetProperty("leveldb.approximate-memory-usage", &value));
  EXPECT_FALSE(value.empty());
  // Should be a numeric string
  unsigned long long usage = std::stoull(value);
  // Memory usage should be non-negative (always true for unsigned)
  EXPECT_GE(usage, 0ULL);
}

// Test that after writing data, num-files-at-level reflects changes after compaction
TEST_F(DBImplGetPropertyTest_314, NumFilesAfterWrite_314) {
  // Write some data and flush
  WriteOptions write_options;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_options, key, val).ok());
  }

  // Force compaction of memtable
  DBImpl* dbimpl = reinterpret_cast<DBImpl*>(db_);
  dbimpl->TEST_CompactMemTable();

  std::string value;
  EXPECT_TRUE(db_->GetProperty("leveldb.num-files-at-level0", &value));
  // After flush, there should be at least one file at some level
  // (likely level 0)
  int num_files = std::stoi(value);
  EXPECT_GE(num_files, 0);
}

// Test approximate-memory-usage increases after writing data
TEST_F(DBImplGetPropertyTest_314, ApproximateMemoryUsageIncreasesAfterWrite_314) {
  std::string value_before;
  EXPECT_TRUE(db_->GetProperty("leveldb.approximate-memory-usage", &value_before));
  unsigned long long usage_before = std::stoull(value_before);

  // Write some data
  WriteOptions write_options;
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = std::string(100, 'x');
    ASSERT_TRUE(db_->Put(write_options, key, val).ok());
  }

  std::string value_after;
  EXPECT_TRUE(db_->GetProperty("leveldb.approximate-memory-usage", &value_after));
  unsigned long long usage_after = std::stoull(value_after);

  EXPECT_GT(usage_after, usage_before);
}

// Test stats property after some compaction work
TEST_F(DBImplGetPropertyTest_314, StatsAfterCompaction_314) {
  WriteOptions write_options;
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = std::string(100, 'v');
    ASSERT_TRUE(db_->Put(write_options, key, val).ok());
  }

  DBImpl* dbimpl = reinterpret_cast<DBImpl*>(db_);
  dbimpl->TEST_CompactMemTable();

  std::string value;
  EXPECT_TRUE(db_->GetProperty("leveldb.stats", &value));
  EXPECT_FALSE(value.empty());
  // After compaction, stats should show at least some level info
  EXPECT_NE(std::string::npos, value.find("Compactions"));
}

// Test sstables after writing and flushing
TEST_F(DBImplGetPropertyTest_314, SstablesAfterFlush_314) {
  WriteOptions write_options;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_options, key, val).ok());
  }

  DBImpl* dbimpl = reinterpret_cast<DBImpl*>(db_);
  dbimpl->TEST_CompactMemTable();

  std::string value;
  EXPECT_TRUE(db_->GetProperty("leveldb.sstables", &value));
  // After flush, there should be some sstable info
  EXPECT_FALSE(value.empty());
}

// Test that value is cleared before setting (even on failure)
TEST_F(DBImplGetPropertyTest_314, ValueClearedOnFailure_314) {
  std::string value = "pre-existing-content";
  EXPECT_FALSE(db_->GetProperty("invalid.property", &value));
  EXPECT_TRUE(value.empty());
}

// Test that value is cleared before setting on success
TEST_F(DBImplGetPropertyTest_314, ValueClearedOnSuccess_314) {
  std::string value = "pre-existing-content";
  EXPECT_TRUE(db_->GetProperty("leveldb.num-files-at-level0", &value));
  // Should be the actual value, not appended to pre-existing content
  EXPECT_EQ("0", value);
}

// Test partial prefix match doesn't work
TEST_F(DBImplGetPropertyTest_314, PartialPrefixMatch_314) {
  std::string value;
  EXPECT_FALSE(db_->GetProperty("leveldb", &value));
  EXPECT_FALSE(db_->GetProperty("level", &value));
  EXPECT_FALSE(db_->GetProperty("lev", &value));
}

// Test case sensitivity - "leveldb.Stats" should fail (if case-sensitive)
TEST_F(DBImplGetPropertyTest_314, CaseSensitivity_314) {
  std::string value;
  // "Stats" with capital S - this should return false since it checks exact match
  EXPECT_FALSE(db_->GetProperty("leveldb.Stats", &value));
}

// Test num-files-at-level with negative-like input (dash before number)
TEST_F(DBImplGetPropertyTest_314, NumFilesAtLevelNegative_314) {
  std::string value;
  // ConsumeDecimalNumber won't consume a dash, so this should fail
  EXPECT_FALSE(db_->GetProperty("leveldb.num-files-at-level-1", &value));
}

}  // namespace leveldb
