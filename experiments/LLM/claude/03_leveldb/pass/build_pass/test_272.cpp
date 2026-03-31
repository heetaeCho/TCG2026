#include "gtest/gtest.h"

// Include the necessary headers for the C API
#include "leveldb/c.h"

#include <cstdlib>
#include <cstring>

class LevelDBCReadOptionsTest_272 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that leveldb_readoptions_create returns a non-null pointer
TEST_F(LevelDBCReadOptionsTest_272, CreateReturnsNonNull_272) {
  leveldb_readoptions_t* options = leveldb_readoptions_create();
  ASSERT_NE(options, nullptr);
  leveldb_readoptions_destroy(options);
}

// Test that multiple creates return distinct pointers
TEST_F(LevelDBCReadOptionsTest_272, MultipleCreatesReturnDistinctPointers_272) {
  leveldb_readoptions_t* options1 = leveldb_readoptions_create();
  leveldb_readoptions_t* options2 = leveldb_readoptions_create();
  ASSERT_NE(options1, nullptr);
  ASSERT_NE(options2, nullptr);
  ASSERT_NE(options1, options2);
  leveldb_readoptions_destroy(options1);
  leveldb_readoptions_destroy(options2);
}

// Test that destroy does not crash on a valid pointer
TEST_F(LevelDBCReadOptionsTest_272, DestroyDoesNotCrash_272) {
  leveldb_readoptions_t* options = leveldb_readoptions_create();
  ASSERT_NE(options, nullptr);
  // Should not crash
  leveldb_readoptions_destroy(options);
}

// Test setting verify_checksums option
TEST_F(LevelDBCReadOptionsTest_272, SetVerifyChecksums_272) {
  leveldb_readoptions_t* options = leveldb_readoptions_create();
  ASSERT_NE(options, nullptr);
  // Should not crash when setting verify checksums to true or false
  leveldb_readoptions_set_verify_checksums(options, 1);
  leveldb_readoptions_set_verify_checksums(options, 0);
  leveldb_readoptions_destroy(options);
}

// Test setting fill_cache option
TEST_F(LevelDBCReadOptionsTest_272, SetFillCache_272) {
  leveldb_readoptions_t* options = leveldb_readoptions_create();
  ASSERT_NE(options, nullptr);
  // Should not crash when setting fill cache to true or false
  leveldb_readoptions_set_fill_cache(options, 1);
  leveldb_readoptions_set_fill_cache(options, 0);
  leveldb_readoptions_destroy(options);
}

// Test setting snapshot to nullptr (no snapshot)
TEST_F(LevelDBCReadOptionsTest_272, SetSnapshotNull_272) {
  leveldb_readoptions_t* options = leveldb_readoptions_create();
  ASSERT_NE(options, nullptr);
  // Setting snapshot to nullptr should be valid (means read from current state)
  leveldb_readoptions_set_snapshot(options, nullptr);
  leveldb_readoptions_destroy(options);
}

// Integration test: create readoptions, configure, and use with a database
TEST_F(LevelDBCReadOptionsTest_272, UseWithDatabase_272) {
  // Create a temporary database
  leveldb_options_t* db_options = leveldb_options_create();
  leveldb_options_set_create_if_missing(db_options, 1);

  // Use a unique temporary directory
  std::string dbname = testing::TempDir() + "leveldb_c_test_readoptions_272";

  char* err = nullptr;
  leveldb_t* db = leveldb_open(db_options, dbname.c_str(), &err);
  if (err != nullptr) {
    // If we can't open the database, clean up and skip
    leveldb_free(err);
    leveldb_options_destroy(db_options);
    GTEST_SKIP() << "Could not open test database";
  }

  // Write a key-value pair
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  const char* key = "test_key";
  const char* value = "test_value";
  leveldb_put(db, woptions, key, strlen(key), value, strlen(value), &err);
  ASSERT_EQ(err, nullptr);

  // Read with the read options
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  ASSERT_NE(roptions, nullptr);
  leveldb_readoptions_set_verify_checksums(roptions, 1);
  leveldb_readoptions_set_fill_cache(roptions, 1);

  size_t vallen = 0;
  char* result = leveldb_get(db, roptions, key, strlen(key), &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(vallen, strlen(value));
  ASSERT_EQ(memcmp(result, value, vallen), 0);

  leveldb_free(result);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_destroy_db(db_options, dbname.c_str(), &err);
  leveldb_free(err);
  leveldb_options_destroy(db_options);
}

// Test reading a non-existent key with readoptions
TEST_F(LevelDBCReadOptionsTest_272, ReadNonExistentKey_272) {
  leveldb_options_t* db_options = leveldb_options_create();
  leveldb_options_set_create_if_missing(db_options, 1);

  std::string dbname = testing::TempDir() + "leveldb_c_test_readoptions_nonexist_272";

  char* err = nullptr;
  leveldb_t* db = leveldb_open(db_options, dbname.c_str(), &err);
  if (err != nullptr) {
    leveldb_free(err);
    leveldb_options_destroy(db_options);
    GTEST_SKIP() << "Could not open test database";
  }

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  ASSERT_NE(roptions, nullptr);

  size_t vallen = 0;
  const char* key = "nonexistent_key";
  char* result = leveldb_get(db, roptions, key, strlen(key), &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_EQ(result, nullptr);

  leveldb_readoptions_destroy(roptions);
  leveldb_close(db);
  leveldb_destroy_db(db_options, dbname.c_str(), &err);
  leveldb_free(err);
  leveldb_options_destroy(db_options);
}

// Test with snapshot
TEST_F(LevelDBCReadOptionsTest_272, ReadWithSnapshot_272) {
  leveldb_options_t* db_options = leveldb_options_create();
  leveldb_options_set_create_if_missing(db_options, 1);

  std::string dbname = testing::TempDir() + "leveldb_c_test_snapshot_272";

  char* err = nullptr;
  leveldb_t* db = leveldb_open(db_options, dbname.c_str(), &err);
  if (err != nullptr) {
    leveldb_free(err);
    leveldb_options_destroy(db_options);
    GTEST_SKIP() << "Could not open test database";
  }

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();

  // Write initial value
  const char* key = "snap_key";
  const char* value1 = "value1";
  leveldb_put(db, woptions, key, strlen(key), value1, strlen(value1), &err);
  ASSERT_EQ(err, nullptr);

  // Create a snapshot
  const leveldb_snapshot_t* snapshot = leveldb_create_snapshot(db);
  ASSERT_NE(snapshot, nullptr);

  // Write a new value after snapshot
  const char* value2 = "value2";
  leveldb_put(db, woptions, key, strlen(key), value2, strlen(value2), &err);
  ASSERT_EQ(err, nullptr);

  // Read with snapshot - should see old value
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_readoptions_set_snapshot(roptions, snapshot);

  size_t vallen = 0;
  char* result = leveldb_get(db, roptions, key, strlen(key), &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(vallen, strlen(value1));
  ASSERT_EQ(memcmp(result, value1, vallen), 0);
  leveldb_free(result);

  // Read without snapshot - should see new value
  leveldb_readoptions_set_snapshot(roptions, nullptr);
  result = leveldb_get(db, roptions, key, strlen(key), &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(vallen, strlen(value2));
  ASSERT_EQ(memcmp(result, value2, vallen), 0);
  leveldb_free(result);

  leveldb_release_snapshot(db, snapshot);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_destroy_db(db_options, dbname.c_str(), &err);
  leveldb_free(err);
  leveldb_options_destroy(db_options);
}

// Boundary: create and immediately destroy
TEST_F(LevelDBCReadOptionsTest_272, CreateAndImmediatelyDestroy_272) {
  leveldb_readoptions_t* options = leveldb_readoptions_create();
  ASSERT_NE(options, nullptr);
  leveldb_readoptions_destroy(options);
  // No crash means success
}

// Boundary: set options with boundary values
TEST_F(LevelDBCReadOptionsTest_272, SetOptionsWithBoundaryValues_272) {
  leveldb_readoptions_t* options = leveldb_readoptions_create();
  ASSERT_NE(options, nullptr);

  // Test with various boolean-like values
  leveldb_readoptions_set_verify_checksums(options, 0);
  leveldb_readoptions_set_fill_cache(options, 0);

  leveldb_readoptions_set_verify_checksums(options, 1);
  leveldb_readoptions_set_fill_cache(options, 1);

  // Non-zero values should also work as true
  leveldb_readoptions_set_verify_checksums(options, 255);
  leveldb_readoptions_set_fill_cache(options, 255);

  leveldb_readoptions_destroy(options);
}
