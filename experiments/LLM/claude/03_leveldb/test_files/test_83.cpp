#include "db/version_set.h"
#include "db/version_edit.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table_builder.h"
#include "db/dbformat.h"
#include "util/testutil.h"

#include "gtest/gtest.h"

#include <memory>
#include <string>
#include <vector>

namespace leveldb {

// We need to access the Compaction constructor which is private.
// In the actual codebase, VersionSet is a friend of Compaction.
// We'll test through VersionSet's public interface.

class CompactionTest_83 : public ::testing::Test {
 protected:
  CompactionTest_83()
      : dbname_(testing::TempDir() + "compaction_test"),
        env_(Env::Default()) {
    // Clean up any previous state
    DestroyDB(dbname_, Options());
  }

  ~CompactionTest_83() override {
    DestroyDB(dbname_, Options());
  }

  std::string dbname_;
  Env* env_;
};

TEST_F(CompactionTest_83, OpenAndCompact_83) {
  // Test that we can create a DB and trigger compaction-related paths
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  options.write_buffer_size = 1024;  // Small to trigger compaction sooner

  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Write enough data to potentially trigger compaction
  WriteOptions write_options;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value = "value" + std::string(100, 'x');
    s = db->Put(write_options, key, value);
    ASSERT_TRUE(s.ok());
  }

  // Force compaction
  db->CompactRange(nullptr, nullptr);

  // Verify data still readable after compaction
  ReadOptions read_options;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string result;
    s = db->Get(read_options, key, &result);
    ASSERT_TRUE(s.ok()) << "Failed to read key: " << key;
  }

  delete db;
}

TEST_F(CompactionTest_83, MaxOutputFileSizeIsPositive_83) {
  // Indirectly test MaxOutputFileSize through DB compaction behavior
  // After compaction, output files should respect max file size
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  options.max_file_size = 1024;  // 1KB max file size
  options.write_buffer_size = 4096;

  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();

  WriteOptions write_options;
  for (int i = 0; i < 200; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value(200, 'v');
    s = db->Put(write_options, key, value);
    ASSERT_TRUE(s.ok());
  }

  db->CompactRange(nullptr, nullptr);

  // Verify all data still readable
  ReadOptions read_options;
  std::string result;
  for (int i = 0; i < 200; i++) {
    std::string key = "key" + std::to_string(i);
    s = db->Get(read_options, key, &result);
    ASSERT_TRUE(s.ok());
  }

  delete db;
}

TEST_F(CompactionTest_83, CompactionWithDeletions_83) {
  // Test compaction handles deletions (AddInputDeletions path)
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  options.write_buffer_size = 1024;

  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions write_options;
  // Write data
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    s = db->Put(write_options, key, "value");
    ASSERT_TRUE(s.ok());
  }

  // Delete half the keys
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    s = db->Delete(write_options, key);
    ASSERT_TRUE(s.ok());
  }

  // Compact to clean up
  db->CompactRange(nullptr, nullptr);

  // Deleted keys should not be found
  ReadOptions read_options;
  std::string result;
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    s = db->Get(read_options, key, &result);
    ASSERT_TRUE(s.IsNotFound()) << "Key should be deleted: " << key;
  }

  // Remaining keys should still be found
  for (int i = 50; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    s = db->Get(read_options, key, &result);
    ASSERT_TRUE(s.ok()) << "Key should exist: " << key;
    ASSERT_EQ(result, "value");
  }

  delete db;
}

TEST_F(CompactionTest_83, CompactionWithOverwrites_83) {
  // Test IsBaseLevelForKey behavior through overwrites
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  options.write_buffer_size = 1024;

  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions write_options;
  // Write and overwrite keys multiple times
  for (int round = 0; round < 5; round++) {
    for (int i = 0; i < 50; i++) {
      std::string key = "key" + std::to_string(i);
      std::string value = "value_round_" + std::to_string(round);
      s = db->Put(write_options, key, value);
      ASSERT_TRUE(s.ok());
    }
  }

  // Compact
  db->CompactRange(nullptr, nullptr);

  // Should get the latest values
  ReadOptions read_options;
  std::string result;
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    s = db->Get(read_options, key, &result);
    ASSERT_TRUE(s.ok());
    ASSERT_EQ(result, "value_round_4");
  }

  delete db;
}

TEST_F(CompactionTest_83, CompactRangePartial_83) {
  // Test partial range compaction
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  options.write_buffer_size = 1024;

  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions write_options;
  for (int i = 0; i < 100; i++) {
    char key[10];
    snprintf(key, sizeof(key), "key%05d", i);
    s = db->Put(write_options, key, std::string(100, 'v'));
    ASSERT_TRUE(s.ok());
  }

  // Compact a partial range
  Slice begin("key00020");
  Slice end("key00080");
  db->CompactRange(&begin, &end);

  // All data should still be readable
  ReadOptions read_options;
  std::string result;
  for (int i = 0; i < 100; i++) {
    char key[10];
    snprintf(key, sizeof(key), "key%05d", i);
    s = db->Get(read_options, key, &result);
    ASSERT_TRUE(s.ok()) << "Failed at key: " << key;
  }

  delete db;
}

TEST_F(CompactionTest_83, EmptyDatabaseCompaction_83) {
  // Test compaction on empty database
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;

  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  // Compact empty database - should not crash
  db->CompactRange(nullptr, nullptr);

  delete db;
}

TEST_F(CompactionTest_83, LargeValueCompaction_83) {
  // Test compaction with large values to exercise ShouldStopBefore
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  options.write_buffer_size = 4096;
  options.max_file_size = 2048;

  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions write_options;
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value(1000, 'a' + (i % 26));
    s = db->Put(write_options, key, value);
    ASSERT_TRUE(s.ok());
  }

  db->CompactRange(nullptr, nullptr);

  // Verify data integrity
  ReadOptions read_options;
  std::string result;
  for (int i = 0; i < 50; i++) {
    std::string key = "key" + std::to_string(i);
    s = db->Get(read_options, key, &result);
    ASSERT_TRUE(s.ok());
    ASSERT_EQ(result.size(), 1000u);
    ASSERT_EQ(result[0], 'a' + (i % 26));
  }

  delete db;
}

TEST_F(CompactionTest_83, MultipleCompactions_83) {
  // Test multiple rounds of compaction
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  options.write_buffer_size = 2048;

  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions write_options;
  ReadOptions read_options;

  for (int round = 0; round < 3; round++) {
    for (int i = 0; i < 100; i++) {
      std::string key = "key" + std::to_string(i);
      std::string value = "round" + std::to_string(round) + "_value";
      s = db->Put(write_options, key, value);
      ASSERT_TRUE(s.ok());
    }
    db->CompactRange(nullptr, nullptr);
  }

  // Verify latest values
  std::string result;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    s = db->Get(read_options, key, &result);
    ASSERT_TRUE(s.ok());
    ASSERT_EQ(result, "round2_value");
  }

  delete db;
}

TEST_F(CompactionTest_83, ReopenAfterCompaction_83) {
  // Test that compacted data survives reopen (ReleaseInputs properly handled)
  Options options;
  options.create_if_missing = true;
  options.write_buffer_size = 1024;

  {
    DB* db = nullptr;
    Status s = DB::Open(options, dbname_, &db);
    ASSERT_TRUE(s.ok());

    WriteOptions write_options;
    for (int i = 0; i < 100; i++) {
      std::string key = "key" + std::to_string(i);
      s = db->Put(write_options, key, "value" + std::to_string(i));
      ASSERT_TRUE(s.ok());
    }
    db->CompactRange(nullptr, nullptr);
    delete db;
  }

  {
    DB* db = nullptr;
    Status s = DB::Open(options, dbname_, &db);
    ASSERT_TRUE(s.ok());

    ReadOptions read_options;
    std::string result;
    for (int i = 0; i < 100; i++) {
      std::string key = "key" + std::to_string(i);
      s = db->Get(read_options, key, &result);
      ASSERT_TRUE(s.ok()) << "Key missing after reopen: " << key;
      ASSERT_EQ(result, "value" + std::to_string(i));
    }
    delete db;
  }
}

}  // namespace leveldb
