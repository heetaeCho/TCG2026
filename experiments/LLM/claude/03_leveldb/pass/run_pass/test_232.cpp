#include "gtest/gtest.h"
#include "leveldb/c.h"

#include <cstdlib>
#include <cstring>
#include <string>

// Helper to create a temporary directory path
static std::string GetTempDir() {
  std::string dir;
#ifdef _WIN32
  char tmp[MAX_PATH];
  GetTempPathA(MAX_PATH, tmp);
  dir = std::string(tmp) + "leveldb_c_test_232";
#else
  dir = "/tmp/leveldb_c_test_232";
#endif
  return dir;
}

class LevelDBDestroyTest_232 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = leveldb_options_create();
    leveldb_options_set_create_if_missing(options_, 1);
    db_path_ = GetTempDir();
  }

  void TearDown() override {
    if (options_) {
      leveldb_options_destroy(options_);
      options_ = nullptr;
    }
  }

  leveldb_options_t* options_ = nullptr;
  std::string db_path_;
};

// Test that destroying a non-existent database does not produce an error
// (DestroyDB on a path that doesn't exist should succeed or at least not crash)
TEST_F(LevelDBDestroyTest_232, DestroyNonExistentDB_232) {
  char* err = nullptr;
  leveldb_destroy_db(options_, "/tmp/leveldb_nonexistent_db_232_xyz", &err);
  // DestroyDB on a non-existent path typically succeeds (no files to remove)
  if (err) {
    free(err);
    err = nullptr;
  }
  // Test passes if no crash occurs
}

// Test that destroying a freshly created database succeeds
TEST_F(LevelDBDestroyTest_232, DestroyExistingDB_232) {
  char* err = nullptr;

  // First create a database
  leveldb_t* db = leveldb_open(options_, db_path_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to open DB: " << err;
  ASSERT_NE(db, nullptr);

  // Close it
  leveldb_close(db);
  db = nullptr;

  // Now destroy it
  err = nullptr;
  leveldb_destroy_db(options_, db_path_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to destroy DB: " << err;

  // Verify the database is destroyed by trying to open without create_if_missing
  leveldb_options_t* open_opts = leveldb_options_create();
  leveldb_options_set_create_if_missing(open_opts, 0);

  err = nullptr;
  db = leveldb_open(open_opts, db_path_.c_str(), &err);
  // Should fail because DB was destroyed and we're not creating a new one
  EXPECT_NE(err, nullptr);
  if (err) {
    free(err);
    err = nullptr;
  }
  if (db) {
    leveldb_close(db);
  }
  leveldb_options_destroy(open_opts);
}

// Test that destroying a database with data works correctly
TEST_F(LevelDBDestroyTest_232, DestroyDBWithData_232) {
  char* err = nullptr;

  // Create and populate a database
  leveldb_t* db = leveldb_open(options_, db_path_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to open DB: " << err;
  ASSERT_NE(db, nullptr);

  // Write some data
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  const char* key = "testkey";
  const char* val = "testvalue";
  leveldb_put(db, woptions, key, strlen(key), val, strlen(val), &err);
  ASSERT_EQ(err, nullptr) << "Failed to put: " << err;
  leveldb_writeoptions_destroy(woptions);

  // Close the database
  leveldb_close(db);
  db = nullptr;

  // Destroy it
  err = nullptr;
  leveldb_destroy_db(options_, db_path_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to destroy DB: " << err;
}

// Test that errptr is set to nullptr on successful destroy
TEST_F(LevelDBDestroyTest_232, ErrptrNullOnSuccess_232) {
  char* err = nullptr;

  // Create DB first
  leveldb_t* db = leveldb_open(options_, db_path_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db, nullptr);
  leveldb_close(db);

  // Destroy
  err = nullptr;
  leveldb_destroy_db(options_, db_path_.c_str(), &err);
  EXPECT_EQ(err, nullptr);
}

// Test destroying the same path twice
TEST_F(LevelDBDestroyTest_232, DestroyTwice_232) {
  char* err = nullptr;

  // Create a database
  leveldb_t* db = leveldb_open(options_, db_path_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db, nullptr);
  leveldb_close(db);

  // Destroy first time
  err = nullptr;
  leveldb_destroy_db(options_, db_path_.c_str(), &err);
  if (err) {
    free(err);
    err = nullptr;
  }

  // Destroy second time — should not crash, may or may not error
  err = nullptr;
  leveldb_destroy_db(options_, db_path_.c_str(), &err);
  if (err) {
    free(err);
    err = nullptr;
  }
  // Test passes if no crash
}

// Test with default options (no special configuration)
TEST_F(LevelDBDestroyTest_232, DestroyWithDefaultOptions_232) {
  char* err = nullptr;
  leveldb_options_t* default_opts = leveldb_options_create();

  // Just ensure calling destroy with default options doesn't crash
  leveldb_destroy_db(default_opts, "/tmp/leveldb_default_opts_test_232", &err);
  if (err) {
    free(err);
    err = nullptr;
  }
  leveldb_options_destroy(default_opts);
}

// Test that after destroying, reopening with create_if_missing gives a fresh DB
TEST_F(LevelDBDestroyTest_232, ReopenAfterDestroy_232) {
  char* err = nullptr;

  // Create and populate
  leveldb_t* db = leveldb_open(options_, db_path_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  const char* key = "mykey";
  const char* val = "myvalue";
  leveldb_put(db, woptions, key, strlen(key), val, strlen(val), &err);
  ASSERT_EQ(err, nullptr);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  db = nullptr;

  // Destroy
  err = nullptr;
  leveldb_destroy_db(options_, db_path_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  // Reopen with create_if_missing
  err = nullptr;
  db = leveldb_open(options_, db_path_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db, nullptr);

  // The old data should be gone
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  err = nullptr;
  char* result = leveldb_get(db, roptions, key, strlen(key), &vallen, &err);
  EXPECT_EQ(err, nullptr);
  EXPECT_EQ(result, nullptr);  // Key should not exist in fresh DB

  if (result) {
    free(result);
  }
  if (err) {
    free(err);
  }

  leveldb_readoptions_destroy(roptions);
  leveldb_close(db);

  // Clean up
  err = nullptr;
  leveldb_destroy_db(options_, db_path_.c_str(), &err);
  if (err) free(err);
}
