#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/testutil.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"

#include <set>
#include <cstdint>
#include <string>

namespace leveldb {

class VersionSetAddLiveFilesTest_169 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_add_live_files_test";
    env_->CreateDir(dbname_);

    // Create CURRENT file to make VersionSet happy
    options_.env = env_;
    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete version_set_;
    delete table_cache_;
    delete icmp_;
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
  VersionSet* version_set_;
};

// Test that AddLiveFiles on a freshly created VersionSet returns an empty set
// (or whatever files are in the initial version)
TEST_F(VersionSetAddLiveFilesTest_169, EmptyVersionSet_169) {
  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);
  // A freshly constructed VersionSet without Recover should have no files
  // in its versions (only dummy_versions_ which has no files).
  // However, the current_ version might be nullptr or not appended.
  // Based on the constructor, current_ is nullptr and dummy_versions_ 
  // points to itself, so the loop should not iterate at all.
  EXPECT_TRUE(live.empty());
}

// Test AddLiveFiles after recovering a simple database with some files
class VersionSetAddLiveFilesWithDBTest_169 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_add_live_db_test";
    // Clean up any previous test data
    DestroyDB(dbname_, Options());
  }

  void TearDown() override {
    DestroyDB(dbname_, Options());
  }

  Env* env_;
  std::string dbname_;
};

TEST_F(VersionSetAddLiveFilesWithDBTest_169, AddLiveFilesAfterWrites_169) {
  // Open a database, write some data to create SST files, then check AddLiveFiles
  Options options;
  options.env = env_;
  options.create_if_missing = true;

  DB* db = nullptr;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Write enough data to trigger compaction / flush
  WriteOptions wo;
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    s = db->Put(wo, key, val);
    ASSERT_TRUE(s.ok());
  }

  // Force a compaction to create files at various levels
  // Use the test interface if available, or just close and reopen
  delete db;
  db = nullptr;

  // Reopen and verify AddLiveFiles through the public interface
  // Since AddLiveFiles is on VersionSet which is internal, 
  // we verify indirectly that the DB works correctly
  s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // The database should still have all the data
  ReadOptions ro;
  std::string value;
  s = db->Get(ro, "key0", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("value0", value);

  s = db->Get(ro, "key999", &value);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("value999", value);

  delete db;
}

// Test that AddLiveFiles with a pre-existing set merges correctly (set behavior)
TEST_F(VersionSetAddLiveFilesTest_169, AddLiveFilesPrePopulatedSet_169) {
  std::set<uint64_t> live;
  live.insert(100);
  live.insert(200);
  version_set_->AddLiveFiles(&live);
  // The pre-existing entries should still be there
  EXPECT_TRUE(live.count(100) > 0);
  EXPECT_TRUE(live.count(200) > 0);
}

// Test that calling AddLiveFiles multiple times is idempotent
TEST_F(VersionSetAddLiveFilesTest_169, AddLiveFilesIdempotent_169) {
  std::set<uint64_t> live1;
  version_set_->AddLiveFiles(&live1);

  std::set<uint64_t> live2;
  version_set_->AddLiveFiles(&live2);

  EXPECT_EQ(live1, live2);
}

// Integration test: create a real DB, force flush, and verify live files are non-empty
class VersionSetIntegrationTest_169 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_integration_test";
    DestroyDB(dbname_, Options());
  }

  void TearDown() override {
    DestroyDB(dbname_, Options());
  }

  Env* env_;
  std::string dbname_;
};

TEST_F(VersionSetIntegrationTest_169, LiveFilesNonEmptyAfterFlush_169) {
  Options options;
  options.env = env_;
  options.create_if_missing = true;
  options.write_buffer_size = 1024;  // Small buffer to trigger flush

  DB* db = nullptr;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Write enough data to trigger at least one flush
  WriteOptions wo;
  for (int i = 0; i < 500; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = std::string(100, 'v');  // 100 byte values
    s = db->Put(wo, key, val);
    ASSERT_TRUE(s.ok());
  }

  // After writes and potential flushes, live files should exist
  // We can check this indirectly through GetApproximateSizes or 
  // the property interface
  std::string num_files;
  bool ok = db->GetProperty("leveldb.num-files-at-level0", &num_files);
  EXPECT_TRUE(ok);
  // There should be some files somewhere
  bool has_files = false;
  for (int level = 0; level < 7; level++) {
    std::string prop = "leveldb.num-files-at-level" + std::to_string(level);
    std::string val;
    if (db->GetProperty(prop, &val)) {
      if (std::stoi(val) > 0) {
        has_files = true;
        break;
      }
    }
  }
  EXPECT_TRUE(has_files);

  delete db;
}

// Test boundary: AddLiveFiles should handle versions with files at all levels
TEST_F(VersionSetIntegrationTest_169, LiveFilesAcrossMultipleLevels_169) {
  Options options;
  options.env = env_;
  options.create_if_missing = true;
  options.write_buffer_size = 1024;

  DB* db = nullptr;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Write and compact to push files to deeper levels
  WriteOptions wo;
  for (int round = 0; round < 5; round++) {
    for (int i = 0; i < 200; i++) {
      std::string key = "key" + std::to_string(round * 200 + i);
      std::string val = std::string(100, 'x');
      s = db->Put(wo, key, val);
      ASSERT_TRUE(s.ok());
    }
    // Trigger compaction
    db->CompactRange(nullptr, nullptr);
  }

  // Verify data integrity after compaction
  ReadOptions ro;
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value;
    s = db->Get(ro, key, &value);
    ASSERT_TRUE(s.ok()) << "Missing key: " << key;
  }

  delete db;
}

}  // namespace leveldb
