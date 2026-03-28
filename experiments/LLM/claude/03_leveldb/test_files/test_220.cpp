#include "gtest/gtest.h"
#include "leveldb/c.h"
#include "leveldb/db.h"
#include "leveldb/options.h"

#include <cstdlib>
#include <cstring>
#include <string>

// Helper to get a temporary directory for test databases
static std::string GetTestDir() {
    std::string dir;
    const char* env = std::getenv("TEST_TMPDIR");
    if (env && env[0] != '\0') {
        dir = env;
    } else {
        dir = "/tmp/leveldb_c_test";
    }
    return dir;
}

class LevelDBCTest_220 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = leveldb_options_create();
    leveldb_options_set_create_if_missing(options_, 1);
    leveldb_options_set_error_if_exists(options_, 1);
    dbname_ = GetTestDir() + "/c_test_db_220";
    // Destroy any pre-existing database
    char* err = nullptr;
    leveldb_destroy_db(options_, dbname_.c_str(), &err);
    if (err) {
      leveldb_free(err);
    }
  }

  void TearDown() override {
    if (db_) {
      leveldb_close(db_);
      db_ = nullptr;
    }
    char* err = nullptr;
    leveldb_destroy_db(options_, dbname_.c_str(), &err);
    if (err) {
      leveldb_free(err);
    }
    leveldb_options_destroy(options_);
  }

  leveldb_options_t* options_ = nullptr;
  leveldb_t* db_ = nullptr;
  std::string dbname_;
};

// Test: Successfully open a new database
TEST_F(LevelDBCTest_220, OpenNewDatabase_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);
}

// Test: Opening a database with error_if_exists on an existing DB should fail
TEST_F(LevelDBCTest_220, OpenExistingDatabaseWithErrorIfExists_220) {
  char* err = nullptr;
  // First open should succeed
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);
  leveldb_close(db_);
  db_ = nullptr;

  // Second open with error_if_exists should fail
  err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_NE(err, nullptr);
  ASSERT_EQ(db_, nullptr);
  leveldb_free(err);
}

// Test: Opening a non-existent database without create_if_missing should fail
TEST_F(LevelDBCTest_220, OpenNonExistentWithoutCreateIfMissing_220) {
  leveldb_options_set_create_if_missing(options_, 0);
  leveldb_options_set_error_if_exists(options_, 0);

  std::string nonexistent = dbname_ + "_nonexistent";
  char* err = nullptr;
  leveldb_t* db = leveldb_open(options_, nonexistent.c_str(), &err);
  ASSERT_NE(err, nullptr);
  ASSERT_EQ(db, nullptr);
  leveldb_free(err);
}

// Test: Open, put, get, delete operations
TEST_F(LevelDBCTest_220, PutGetDelete_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();

  // Put a key-value pair
  const char* key = "testkey";
  const char* val = "testvalue";
  err = nullptr;
  leveldb_put(db_, woptions, key, strlen(key), val, strlen(val), &err);
  ASSERT_EQ(err, nullptr);

  // Get the value back
  size_t vallen = 0;
  err = nullptr;
  char* result = leveldb_get(db_, roptions, key, strlen(key), &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(vallen, strlen(val));
  ASSERT_EQ(std::string(result, vallen), std::string(val));
  leveldb_free(result);

  // Delete the key
  err = nullptr;
  leveldb_delete(db_, woptions, key, strlen(key), &err);
  ASSERT_EQ(err, nullptr);

  // Get should return null after delete
  err = nullptr;
  result = leveldb_get(db_, roptions, key, strlen(key), &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_EQ(result, nullptr);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
}

// Test: Open with empty database name (should fail or handle gracefully)
TEST_F(LevelDBCTest_220, OpenWithEmptyName_220) {
  char* err = nullptr;
  leveldb_t* db = leveldb_open(options_, "", &err);
  // Empty name is generally an error, but behavior may vary
  // We check that if there's an error, db is nullptr
  if (err != nullptr) {
    ASSERT_EQ(db, nullptr);
    leveldb_free(err);
  } else {
    // If it somehow succeeds, clean up
    ASSERT_NE(db, nullptr);
    leveldb_close(db);
    leveldb_destroy_db(options_, "", &err);
    if (err) leveldb_free(err);
  }
}

// Test: Reopen existing database without error_if_exists
TEST_F(LevelDBCTest_220, ReopenExistingDatabase_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  // Put data
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db_, woptions, "key1", 4, "value1", 6, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_writeoptions_destroy(woptions);

  leveldb_close(db_);
  db_ = nullptr;

  // Reopen without error_if_exists
  leveldb_options_set_error_if_exists(options_, 0);
  err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  // Verify data persists
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  err = nullptr;
  char* result = leveldb_get(db_, roptions, "key1", 4, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(vallen, 6u);
  ASSERT_EQ(std::string(result, vallen), "value1");
  leveldb_free(result);
  leveldb_readoptions_destroy(roptions);
}

// Test: Close and ensure db handle is released properly
TEST_F(LevelDBCTest_220, CloseDatabase_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_close(db_);
  db_ = nullptr;
  // No crash means success - handle was properly released
}

// Test: Write batch operations
TEST_F(LevelDBCTest_220, WriteBatch_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();

  // Create a write batch with puts and a delete
  leveldb_writebatch_t* wb = leveldb_writebatch_create();
  leveldb_writebatch_put(wb, "batch_key1", 10, "batch_val1", 10);
  leveldb_writebatch_put(wb, "batch_key2", 10, "batch_val2", 10);

  err = nullptr;
  leveldb_write(db_, woptions, wb, &err);
  ASSERT_EQ(err, nullptr);

  // Verify both keys exist
  size_t vallen = 0;
  err = nullptr;
  char* result = leveldb_get(db_, roptions, "batch_key1", 10, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(std::string(result, vallen), "batch_val1");
  leveldb_free(result);

  result = leveldb_get(db_, roptions, "batch_key2", 10, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(std::string(result, vallen), "batch_val2");
  leveldb_free(result);

  // Delete via batch
  leveldb_writebatch_t* wb2 = leveldb_writebatch_create();
  leveldb_writebatch_delete(wb2, "batch_key1", 10);
  err = nullptr;
  leveldb_write(db_, woptions, wb2, &err);
  ASSERT_EQ(err, nullptr);

  result = leveldb_get(db_, roptions, "batch_key1", 10, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_EQ(result, nullptr);

  leveldb_writebatch_destroy(wb);
  leveldb_writebatch_destroy(wb2);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
}

// Test: Iterator operations
TEST_F(LevelDBCTest_220, Iterator_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();

  // Insert some data
  leveldb_put(db_, woptions, "a", 1, "1", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db_, woptions, "b", 1, "2", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db_, woptions, "c", 1, "3", 1, &err);
  ASSERT_EQ(err, nullptr);

  // Create iterator and iterate
  leveldb_iterator_t* iter = leveldb_create_iterator(db_, roptions);
  ASSERT_NE(iter, nullptr);

  leveldb_iter_seek_to_first(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));

  size_t klen;
  const char* key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(klen, 1u);
  ASSERT_EQ(key[0], 'a');

  leveldb_iter_next(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(klen, 1u);
  ASSERT_EQ(key[0], 'b');

  leveldb_iter_next(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(klen, 1u);
  ASSERT_EQ(key[0], 'c');

  leveldb_iter_next(iter);
  ASSERT_FALSE(leveldb_iter_valid(iter));

  leveldb_iter_destroy(iter);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
}

// Test: Get non-existent key returns nullptr
TEST_F(LevelDBCTest_220, GetNonExistentKey_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  err = nullptr;
  char* result = leveldb_get(db_, roptions, "nokey", 5, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_EQ(result, nullptr);

  leveldb_readoptions_destroy(roptions);
}

// Test: Snapshot isolation
TEST_F(LevelDBCTest_220, SnapshotIsolation_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();

  // Put initial value
  leveldb_put(db_, woptions, "snap_key", 8, "old_val", 7, &err);
  ASSERT_EQ(err, nullptr);

  // Take snapshot
  const leveldb_snapshot_t* snap = leveldb_create_snapshot(db_);
  ASSERT_NE(snap, nullptr);

  // Update value after snapshot
  leveldb_put(db_, woptions, "snap_key", 8, "new_val", 7, &err);
  ASSERT_EQ(err, nullptr);

  // Read with snapshot should return old value
  leveldb_readoptions_set_snapshot(roptions, snap);
  size_t vallen = 0;
  err = nullptr;
  char* result = leveldb_get(db_, roptions, "snap_key", 8, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(std::string(result, vallen), "old_val");
  leveldb_free(result);

  // Read without snapshot should return new value
  leveldb_readoptions_set_snapshot(roptions, nullptr);
  result = leveldb_get(db_, roptions, "snap_key", 8, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(std::string(result, vallen), "new_val");
  leveldb_free(result);

  leveldb_release_snapshot(db_, snap);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
}

// Test: Multiple put/overwrite same key
TEST_F(LevelDBCTest_220, OverwriteKey_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();

  leveldb_put(db_, woptions, "key", 3, "val1", 4, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_put(db_, woptions, "key", 3, "val2", 4, &err);
  ASSERT_EQ(err, nullptr);

  size_t vallen = 0;
  char* result = leveldb_get(db_, roptions, "key", 3, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(std::string(result, vallen), "val2");
  leveldb_free(result);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
}

// Test: Property retrieval
TEST_F(LevelDBCTest_220, GetProperty_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  char* prop = leveldb_property_value(db_, "leveldb.stats");
  // stats property should be available
  ASSERT_NE(prop, nullptr);
  leveldb_free(prop);

  // Non-existent property should return nullptr
  char* bad_prop = leveldb_property_value(db_, "nonexistent.property");
  ASSERT_EQ(bad_prop, nullptr);
}

// Test: Compact range
TEST_F(LevelDBCTest_220, CompactRange_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();

  // Insert some data
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    leveldb_put(db_, woptions, key.c_str(), key.size(), val.c_str(), val.size(), &err);
    ASSERT_EQ(err, nullptr);
  }

  // Compact full range (nullptr means open-ended)
  leveldb_compact_range(db_, nullptr, 0, nullptr, 0);
  // No crash means success

  leveldb_writeoptions_destroy(woptions);
}

// Test: Empty key and value
TEST_F(LevelDBCTest_220, EmptyKeyAndValue_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();

  // Put empty key with empty value
  leveldb_put(db_, woptions, "", 0, "", 0, &err);
  ASSERT_EQ(err, nullptr);

  size_t vallen = 0;
  char* result = leveldb_get(db_, roptions, "", 0, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(vallen, 0u);
  leveldb_free(result);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
}

// Test: Large key and value
TEST_F(LevelDBCTest_220, LargeKeyValue_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();

  std::string large_key(1024, 'K');
  std::string large_val(1024 * 100, 'V');

  leveldb_put(db_, woptions, large_key.c_str(), large_key.size(),
              large_val.c_str(), large_val.size(), &err);
  ASSERT_EQ(err, nullptr);

  size_t vallen = 0;
  char* result = leveldb_get(db_, roptions, large_key.c_str(), large_key.size(),
                             &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(vallen, large_val.size());
  ASSERT_EQ(std::string(result, vallen), large_val);
  leveldb_free(result);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
}

// Test: Destroy database
TEST_F(LevelDBCTest_220, DestroyDatabase_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db_, woptions, "key", 3, "val", 3, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_writeoptions_destroy(woptions);

  leveldb_close(db_);
  db_ = nullptr;

  // Destroy the database
  err = nullptr;
  leveldb_destroy_db(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  // Trying to open without create_if_missing should fail now
  leveldb_options_set_create_if_missing(options_, 0);
  leveldb_options_set_error_if_exists(options_, 0);
  err = nullptr;
  leveldb_t* db2 = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_NE(err, nullptr);
  ASSERT_EQ(db2, nullptr);
  leveldb_free(err);
}

// Test: Repair database
TEST_F(LevelDBCTest_220, RepairDatabase_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_close(db_);
  db_ = nullptr;

  err = nullptr;
  leveldb_repair_db(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  // Should be able to reopen after repair
  leveldb_options_set_error_if_exists(options_, 0);
  err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);
}

// Test: Approximate sizes
TEST_F(LevelDBCTest_220, ApproximateSizes_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();

  // Insert data to have some size
  for (int i = 0; i < 100; i++) {
    char key[32], val[256];
    snprintf(key, sizeof(key), "key%06d", i);
    memset(val, 'x', sizeof(val));
    leveldb_put(db_, woptions, key, strlen(key), val, sizeof(val), &err);
    ASSERT_EQ(err, nullptr);
  }

  const char* start_key = "key000000";
  size_t start_key_len = strlen(start_key);
  const char* end_key = "key999999";
  size_t end_key_len = strlen(end_key);

  uint64_t size;
  leveldb_approximate_sizes(db_, 1, &start_key, &start_key_len,
                            &end_key, &end_key_len, &size);
  // Size should be non-negative (it's uint64_t so always >= 0)
  // Just verify it doesn't crash
  SUCCEED();

  leveldb_writeoptions_destroy(woptions);
}

// Test: WriteBatch clear
TEST_F(LevelDBCTest_220, WriteBatchClear_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();

  leveldb_writebatch_t* wb = leveldb_writebatch_create();
  leveldb_writebatch_put(wb, "cleared_key", 11, "cleared_val", 11);
  leveldb_writebatch_clear(wb);

  // After clear, writing the batch should be a no-op
  err = nullptr;
  leveldb_write(db_, woptions, wb, &err);
  ASSERT_EQ(err, nullptr);

  size_t vallen = 0;
  char* result = leveldb_get(db_, roptions, "cleared_key", 11, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_EQ(result, nullptr);

  leveldb_writebatch_destroy(wb);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
}

// Test: Options creation and destruction don't crash
TEST_F(LevelDBCTest_220, OptionsLifecycle_220) {
  leveldb_options_t* opts = leveldb_options_create();
  ASSERT_NE(opts, nullptr);
  
  leveldb_options_set_create_if_missing(opts, 1);
  leveldb_options_set_error_if_exists(opts, 0);
  leveldb_options_set_paranoid_checks(opts, 1);
  leveldb_options_set_write_buffer_size(opts, 4 * 1024 * 1024);
  leveldb_options_set_max_open_files(opts, 100);
  leveldb_options_set_block_size(opts, 4096);
  leveldb_options_set_block_restart_interval(opts, 16);
  leveldb_options_set_max_file_size(opts, 2 * 1024 * 1024);
  leveldb_options_set_compression(opts, leveldb_snappy_compression);
  
  leveldb_options_destroy(opts);
  SUCCEED();
}

// Test: Sync write option
TEST_F(LevelDBCTest_220, SyncWrite_220) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_writeoptions_set_sync(woptions, 1);
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();

  leveldb_put(db_, woptions, "sync_key", 8, "sync_val", 8, &err);
  ASSERT_EQ(err, nullptr);

  size_t vallen = 0;
  char* result = leveldb_get(db_, roptions, "sync_key", 8, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(std::string(result, vallen), "sync_val");
  leveldb_free(result);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
}
