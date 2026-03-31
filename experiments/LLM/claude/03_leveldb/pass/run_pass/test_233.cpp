#include "gtest/gtest.h"
#include "leveldb/c.h"

#include <cstdlib>
#include <cstring>
#include <string>

class LevelDBRepairTest_233 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = leveldb_options_create();
    leveldb_options_set_create_if_missing(options_, 1);
  }

  void TearDown() override {
    leveldb_options_destroy(options_);
  }

  leveldb_options_t* options_;
};

TEST_F(LevelDBRepairTest_233, RepairNonExistentDB_233) {
  char* err = nullptr;
  // Attempt to repair a database that doesn't exist at a non-existent path
  leveldb_repair_db(options_, "/tmp/leveldb_repair_test_nonexistent_233", &err);
  // The result depends on whether the path exists or not.
  // If error occurs, err will be non-null.
  // We just verify the function doesn't crash and we clean up properly.
  if (err) {
    leveldb_free(err);
  }
}

TEST_F(LevelDBRepairTest_233, RepairValidDB_233) {
  const char* dbname = "/tmp/leveldb_repair_test_valid_233";
  char* err = nullptr;

  // First create a database
  leveldb_t* db = leveldb_open(options_, dbname, &err);
  ASSERT_EQ(err, nullptr) << "Failed to open DB: " << err;

  // Write some data
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "key1", 4, "value1", 6, &err);
  ASSERT_EQ(err, nullptr) << "Failed to put: " << err;
  leveldb_writeoptions_destroy(woptions);

  // Close the database
  leveldb_close(db);

  // Now repair the database
  leveldb_repair_db(options_, dbname, &err);
  EXPECT_EQ(err, nullptr) << "Repair failed: " << err;
  if (err) {
    leveldb_free(err);
    err = nullptr;
  }

  // Verify database is still accessible after repair
  db = leveldb_open(options_, dbname, &err);
  ASSERT_EQ(err, nullptr) << "Failed to open DB after repair: " << err;

  // Verify data is still there
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t val_len = 0;
  char* val = leveldb_get(db, roptions, "key1", 4, &val_len, &err);
  EXPECT_EQ(err, nullptr);
  if (val) {
    EXPECT_EQ(val_len, 6u);
    EXPECT_EQ(std::string(val, val_len), "value1");
    leveldb_free(val);
  }

  leveldb_readoptions_destroy(roptions);
  leveldb_close(db);

  // Clean up
  leveldb_destroy_db(options_, dbname, &err);
  if (err) {
    leveldb_free(err);
  }
}

TEST_F(LevelDBRepairTest_233, RepairEmptyDB_233) {
  const char* dbname = "/tmp/leveldb_repair_test_empty_233";
  char* err = nullptr;

  // Create an empty database
  leveldb_t* db = leveldb_open(options_, dbname, &err);
  ASSERT_EQ(err, nullptr) << "Failed to open DB: " << err;
  leveldb_close(db);

  // Repair the empty database
  leveldb_repair_db(options_, dbname, &err);
  EXPECT_EQ(err, nullptr) << "Repair of empty DB failed: " << err;
  if (err) {
    leveldb_free(err);
    err = nullptr;
  }

  // Verify we can still open it
  db = leveldb_open(options_, dbname, &err);
  EXPECT_EQ(err, nullptr) << "Failed to open empty DB after repair: " << err;
  if (err) {
    leveldb_free(err);
    err = nullptr;
  }
  if (db) {
    leveldb_close(db);
  }

  // Clean up
  leveldb_destroy_db(options_, dbname, &err);
  if (err) {
    leveldb_free(err);
  }
}

TEST_F(LevelDBRepairTest_233, RepairEmptyPathString_233) {
  char* err = nullptr;
  leveldb_repair_db(options_, "", &err);
  // An empty path is likely an error
  // Just ensure no crash; if error, clean up
  if (err) {
    EXPECT_NE(std::string(err), "");
    leveldb_free(err);
  }
}

TEST_F(LevelDBRepairTest_233, RepairDBWithMultipleEntries_233) {
  const char* dbname = "/tmp/leveldb_repair_test_multi_233";
  char* err = nullptr;

  leveldb_t* db = leveldb_open(options_, dbname, &err);
  ASSERT_EQ(err, nullptr) << "Failed to open DB: " << err;

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value = "value" + std::to_string(i);
    leveldb_put(db, woptions, key.c_str(), key.size(), value.c_str(),
                value.size(), &err);
    ASSERT_EQ(err, nullptr) << "Failed to put key " << i << ": " << err;
  }
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);

  // Repair
  leveldb_repair_db(options_, dbname, &err);
  EXPECT_EQ(err, nullptr) << "Repair failed: " << err;
  if (err) {
    leveldb_free(err);
    err = nullptr;
  }

  // Verify data
  db = leveldb_open(options_, dbname, &err);
  ASSERT_EQ(err, nullptr) << "Failed to open after repair: " << err;

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    size_t val_len = 0;
    char* val = leveldb_get(db, roptions, key.c_str(), key.size(), &val_len, &err);
    EXPECT_EQ(err, nullptr);
    if (val) {
      EXPECT_EQ(std::string(val, val_len), expected_value);
      leveldb_free(val);
    }
  }

  leveldb_readoptions_destroy(roptions);
  leveldb_close(db);

  leveldb_destroy_db(options_, dbname, &err);
  if (err) {
    leveldb_free(err);
  }
}
