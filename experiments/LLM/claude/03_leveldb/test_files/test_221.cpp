#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "leveldb/c.h"
}

#include <cstdlib>
#include <cstring>
#include <string>

// Test fixture for leveldb_close tests
class LeveldbCloseTest_221 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temporary directory for the database
    db_ = nullptr;
    options_ = leveldb_options_create();
    leveldb_options_set_create_if_missing(options_, 1);
    
    // Use a unique path for each test
    dbpath_ = testing::TempDir() + "leveldb_close_test_221";
    
    // Clean up any existing database
    char* err = nullptr;
    leveldb_destroy_db(options_, dbpath_.c_str(), &err);
    if (err) {
      leveldb_free(err);
      err = nullptr;
    }
  }

  void TearDown() override {
    if (options_) {
      // Clean up the database directory
      char* err = nullptr;
      leveldb_destroy_db(options_, dbpath_.c_str(), &err);
      if (err) {
        leveldb_free(err);
      }
      leveldb_options_destroy(options_);
    }
  }

  leveldb_t* db_;
  leveldb_options_t* options_;
  std::string dbpath_;
};

// Test that leveldb_close successfully closes a newly opened database
TEST_F(LeveldbCloseTest_221, CloseAfterOpen_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to open database: " << err;
  ASSERT_NE(db_, nullptr);
  
  // Close should not crash
  leveldb_close(db_);
  db_ = nullptr;  // Prevent double close
}

// Test that leveldb_close works after performing write operations
TEST_F(LeveldbCloseTest_221, CloseAfterWrites_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to open database: " << err;
  ASSERT_NE(db_, nullptr);
  
  // Perform some writes
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    leveldb_put(db_, woptions, key.c_str(), key.size(),
                val.c_str(), val.size(), &err);
    ASSERT_EQ(err, nullptr);
  }
  leveldb_writeoptions_destroy(woptions);
  
  // Close should not crash after writes
  leveldb_close(db_);
  db_ = nullptr;
}

// Test that leveldb_close works after performing read operations
TEST_F(LeveldbCloseTest_221, CloseAfterReads_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to open database: " << err;
  ASSERT_NE(db_, nullptr);
  
  // Write a value
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  const char* key = "testkey";
  const char* val = "testval";
  leveldb_put(db_, woptions, key, strlen(key), val, strlen(val), &err);
  ASSERT_EQ(err, nullptr);
  leveldb_writeoptions_destroy(woptions);
  
  // Read the value
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen;
  char* result = leveldb_get(db_, roptions, key, strlen(key), &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(vallen, strlen(val));
  ASSERT_EQ(std::string(result, vallen), std::string(val));
  leveldb_free(result);
  leveldb_readoptions_destroy(roptions);
  
  // Close should not crash after reads
  leveldb_close(db_);
  db_ = nullptr;
}

// Test that the database can be reopened after being closed
TEST_F(LeveldbCloseTest_221, ReopenAfterClose_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to open database: " << err;
  ASSERT_NE(db_, nullptr);
  
  // Write a value before closing
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  const char* key = "persistkey";
  const char* val = "persistval";
  leveldb_put(db_, woptions, key, strlen(key), val, strlen(val), &err);
  ASSERT_EQ(err, nullptr);
  leveldb_writeoptions_destroy(woptions);
  
  // Close the database
  leveldb_close(db_);
  db_ = nullptr;
  
  // Reopen the database
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to reopen database: " << err;
  ASSERT_NE(db_, nullptr);
  
  // Verify the previously written value persists
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen;
  char* result = leveldb_get(db_, roptions, key, strlen(key), &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(result, nullptr);
  ASSERT_EQ(std::string(result, vallen), std::string(val));
  leveldb_free(result);
  leveldb_readoptions_destroy(roptions);
  
  leveldb_close(db_);
  db_ = nullptr;
}

// Test that closing a database releases the lock so another open can succeed
TEST_F(LeveldbCloseTest_221, CloseReleasesLock_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to open database: " << err;
  ASSERT_NE(db_, nullptr);
  
  // Close the database
  leveldb_close(db_);
  db_ = nullptr;
  
  // Opening again should succeed (lock should be released)
  leveldb_t* db2 = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Failed to reopen after close: " << err;
  ASSERT_NE(db2, nullptr);
  
  leveldb_close(db2);
}

// Test close after delete operations
TEST_F(LeveldbCloseTest_221, CloseAfterDeletes_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);
  
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  
  // Write then delete
  const char* key = "delkey";
  const char* val = "delval";
  leveldb_put(db_, woptions, key, strlen(key), val, strlen(val), &err);
  ASSERT_EQ(err, nullptr);
  
  leveldb_delete(db_, woptions, key, strlen(key), &err);
  ASSERT_EQ(err, nullptr);
  
  leveldb_writeoptions_destroy(woptions);
  
  // Close should work fine after deletes
  leveldb_close(db_);
  db_ = nullptr;
}

// Test close after iterator usage
TEST_F(LeveldbCloseTest_221, CloseAfterIteratorDestroyed_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);
  
  // Write some data
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  for (int i = 0; i < 10; i++) {
    std::string key = "iter_key_" + std::to_string(i);
    std::string val = "iter_val_" + std::to_string(i);
    leveldb_put(db_, woptions, key.c_str(), key.size(),
                val.c_str(), val.size(), &err);
    ASSERT_EQ(err, nullptr);
  }
  leveldb_writeoptions_destroy(woptions);
  
  // Create and use an iterator
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_iterator_t* iter = leveldb_create_iterator(db_, roptions);
  ASSERT_NE(iter, nullptr);
  
  leveldb_iter_seek_to_first(iter);
  int count = 0;
  while (leveldb_iter_valid(iter)) {
    count++;
    leveldb_iter_next(iter);
  }
  ASSERT_EQ(count, 10);
  
  // Destroy iterator before closing
  leveldb_iter_destroy(iter);
  leveldb_readoptions_destroy(roptions);
  
  // Close should not crash
  leveldb_close(db_);
  db_ = nullptr;
}

// Test close with an empty database (no writes)
TEST_F(LeveldbCloseTest_221, CloseEmptyDatabase_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);
  
  // Immediately close without any operations
  leveldb_close(db_);
  db_ = nullptr;
}

// Test close after snapshot creation and release
TEST_F(LeveldbCloseTest_221, CloseAfterSnapshotRelease_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);
  
  // Create a snapshot
  const leveldb_snapshot_t* snap = leveldb_create_snapshot(db_);
  ASSERT_NE(snap, nullptr);
  
  // Release the snapshot
  leveldb_release_snapshot(db_, snap);
  
  // Close should not crash
  leveldb_close(db_);
  db_ = nullptr;
}

// Test close after batch write operations
TEST_F(LeveldbCloseTest_221, CloseAfterBatchWrite_221) {
  char* err = nullptr;
  db_ = leveldb_open(options_, dbpath_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db_, nullptr);
  
  // Create a write batch
  leveldb_writebatch_t* wb = leveldb_writebatch_create();
  for (int i = 0; i < 50; i++) {
    std::string key = "batch_key_" + std::to_string(i);
    std::string val = "batch_val_" + std::to_string(i);
    leveldb_writebatch_put(wb, key.c_str(), key.size(),
                           val.c_str(), val.size());
  }
  
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_write(db_, woptions, wb, &err);
  ASSERT_EQ(err, nullptr);
  
  leveldb_writebatch_destroy(wb);
  leveldb_writeoptions_destroy(woptions);
  
  // Close should work fine after batch write
  leveldb_close(db_);
  db_ = nullptr;
}
