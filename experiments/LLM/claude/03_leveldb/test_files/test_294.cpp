#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <cstdlib>

namespace leveldb {

// Forward declaration
Status RepairDB(const std::string& dbname, const Options& options);

class RepairDBTest_294 : public testing::Test {
 protected:
  std::string dbname_;
  Env* env_;
  Options options_;

  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/repair_test_294";
    options_.create_if_missing = true;
    options_.env = env_;
    // Clean up any previous test artifacts
    DestroyDB(dbname_, options_);
  }

  void TearDown() override {
    DestroyDB(dbname_, options_);
  }

  // Helper to create a database with some data
  void CreateDBWithData(int num_entries) {
    DB* db = nullptr;
    Status s = DB::Open(options_, dbname_, &db);
    ASSERT_TRUE(s.ok()) << s.ToString();
    WriteOptions write_options;
    for (int i = 0; i < num_entries; i++) {
      std::string key = "key" + std::to_string(i);
      std::string val = "value" + std::to_string(i);
      s = db->Put(write_options, key, val);
      ASSERT_TRUE(s.ok()) << s.ToString();
    }
    delete db;
  }

  // Helper to verify data after repair
  void VerifyDBData(int num_entries) {
    DB* db = nullptr;
    Options open_opts;
    open_opts.env = env_;
    Status s = DB::Open(open_opts, dbname_, &db);
    ASSERT_TRUE(s.ok()) << s.ToString();
    ReadOptions read_options;
    for (int i = 0; i < num_entries; i++) {
      std::string key = "key" + std::to_string(i);
      std::string expected_val = "value" + std::to_string(i);
      std::string actual_val;
      s = db->Get(read_options, key, &actual_val);
      ASSERT_TRUE(s.ok()) << "Key: " << key << " Status: " << s.ToString();
      ASSERT_EQ(expected_val, actual_val);
    }
    delete db;
  }
};

// Test repairing a non-existent database directory
TEST_F(RepairDBTest_294, RepairNonExistentDB_294) {
  std::string nonexistent = testing::TempDir() + "/nonexistent_repair_db_294";
  DestroyDB(nonexistent, options_);
  Options opts;
  // Repairing a non-existent database - behavior depends on implementation
  // but should not crash
  Status s = RepairDB(nonexistent, opts);
  // The status may or may not be ok depending on implementation,
  // but it should not crash
  (void)s;
}

// Test repairing an empty database
TEST_F(RepairDBTest_294, RepairEmptyDB_294) {
  CreateDBWithData(0);
  Status s = RepairDB(dbname_, options_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Should be able to open the repaired database
  DB* db = nullptr;
  Options open_opts;
  open_opts.env = env_;
  s = DB::Open(open_opts, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();
  delete db;
}

// Test repairing a database with some data
TEST_F(RepairDBTest_294, RepairDBWithData_294) {
  const int kNumEntries = 100;
  CreateDBWithData(kNumEntries);

  Status s = RepairDB(dbname_, options_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VerifyDBData(kNumEntries);
}

// Test repairing a database after deleting the MANIFEST file
TEST_F(RepairDBTest_294, RepairAfterManifestDeletion_294) {
  const int kNumEntries = 50;
  CreateDBWithData(kNumEntries);

  // Delete MANIFEST files
  std::vector<std::string> filenames;
  ASSERT_TRUE(env_->GetChildren(dbname_, &filenames).ok());
  for (const auto& f : filenames) {
    if (f.find("MANIFEST") != std::string::npos) {
      ASSERT_TRUE(env_->RemoveFile(dbname_ + "/" + f).ok());
    }
  }

  // Database should not be openable now
  {
    DB* db = nullptr;
    Options open_opts;
    open_opts.env = env_;
    Status s = DB::Open(open_opts, dbname_, &db);
    ASSERT_FALSE(s.ok());
    delete db;
  }

  // Repair should fix it
  Status s = RepairDB(dbname_, options_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VerifyDBData(kNumEntries);
}

// Test repairing a database with a single entry
TEST_F(RepairDBTest_294, RepairDBWithSingleEntry_294) {
  CreateDBWithData(1);

  Status s = RepairDB(dbname_, options_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VerifyDBData(1);
}

// Test repairing a database with large number of entries
TEST_F(RepairDBTest_294, RepairDBWithManyEntries_294) {
  const int kNumEntries = 1000;
  CreateDBWithData(kNumEntries);

  Status s = RepairDB(dbname_, options_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VerifyDBData(kNumEntries);
}

// Test repairing a database twice
TEST_F(RepairDBTest_294, RepairDBTwice_294) {
  const int kNumEntries = 50;
  CreateDBWithData(kNumEntries);

  Status s = RepairDB(dbname_, options_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Repair again
  s = RepairDB(dbname_, options_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VerifyDBData(kNumEntries);
}

// Test repair with paranoid_checks enabled
TEST_F(RepairDBTest_294, RepairWithParanoidChecks_294) {
  const int kNumEntries = 30;
  CreateDBWithData(kNumEntries);

  Options repair_opts = options_;
  repair_opts.paranoid_checks = true;

  Status s = RepairDB(dbname_, repair_opts);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VerifyDBData(kNumEntries);
}

// Test that repair works after database is closed uncleanly (simulated by
// deleting the CURRENT file)
TEST_F(RepairDBTest_294, RepairAfterCurrentFileDeletion_294) {
  const int kNumEntries = 20;
  CreateDBWithData(kNumEntries);

  // Delete CURRENT file
  ASSERT_TRUE(env_->RemoveFile(dbname_ + "/CURRENT").ok());

  // Database should not be openable
  {
    DB* db = nullptr;
    Options open_opts;
    open_opts.env = env_;
    Status s = DB::Open(open_opts, dbname_, &db);
    ASSERT_FALSE(s.ok());
    delete db;
  }

  // Repair should fix it
  Status s = RepairDB(dbname_, options_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  VerifyDBData(kNumEntries);
}

// Test repair with default options
TEST_F(RepairDBTest_294, RepairWithDefaultOptions_294) {
  const int kNumEntries = 10;
  {
    DB* db = nullptr;
    Options opts;
    opts.create_if_missing = true;
    Status s = DB::Open(opts, dbname_, &db);
    ASSERT_TRUE(s.ok()) << s.ToString();
    for (int i = 0; i < kNumEntries; i++) {
      s = db->Put(WriteOptions(), "key" + std::to_string(i),
                  "value" + std::to_string(i));
      ASSERT_TRUE(s.ok());
    }
    delete db;
  }

  Options default_opts;
  Status s = RepairDB(dbname_, default_opts);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify data is intact
  {
    DB* db = nullptr;
    Status s = DB::Open(Options(), dbname_, &db);
    ASSERT_TRUE(s.ok()) << s.ToString();
    for (int i = 0; i < kNumEntries; i++) {
      std::string val;
      s = db->Get(ReadOptions(), "key" + std::to_string(i), &val);
      ASSERT_TRUE(s.ok());
      ASSERT_EQ("value" + std::to_string(i), val);
    }
    delete db;
  }
}

// Test repair preserves data across multiple flushes
TEST_F(RepairDBTest_294, RepairAfterMultipleFlushes_294) {
  DB* db = nullptr;
  options_.write_buffer_size = 1024;  // Small buffer to force flushes
  Status s = DB::Open(options_, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();

  const int kNumEntries = 200;
  for (int i = 0; i < kNumEntries; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = std::string(100, 'a' + (i % 26));
    s = db->Put(WriteOptions(), key, val);
    ASSERT_TRUE(s.ok());
  }
  delete db;

  s = RepairDB(dbname_, options_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify
  db = nullptr;
  Options open_opts;
  open_opts.env = env_;
  s = DB::Open(open_opts, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();
  for (int i = 0; i < kNumEntries; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_val = std::string(100, 'a' + (i % 26));
    std::string actual_val;
    s = db->Get(ReadOptions(), key, &actual_val);
    ASSERT_TRUE(s.ok()) << "Key: " << key << " Status: " << s.ToString();
    ASSERT_EQ(expected_val, actual_val);
  }
  delete db;
}

}  // namespace leveldb
