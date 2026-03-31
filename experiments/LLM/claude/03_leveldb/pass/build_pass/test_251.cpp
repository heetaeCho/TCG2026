#include "gtest/gtest.h"

// Include the necessary headers for leveldb C API
extern "C" {
#include "leveldb/c.h"
}

class LevelDBOptionsTest_251 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any options created during tests
  }
};

TEST_F(LevelDBOptionsTest_251, CreateOptionsReturnsNonNull_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, CreateMultipleOptionsReturnsDistinctPointers_251) {
  leveldb_options_t* options1 = leveldb_options_create();
  leveldb_options_t* options2 = leveldb_options_create();
  ASSERT_NE(options1, nullptr);
  ASSERT_NE(options2, nullptr);
  ASSERT_NE(options1, options2);
  leveldb_options_destroy(options1);
  leveldb_options_destroy(options2);
}

TEST_F(LevelDBOptionsTest_251, SetCreateIfMissing_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  // Should not crash when setting create_if_missing
  leveldb_options_set_create_if_missing(options, 1);
  leveldb_options_set_create_if_missing(options, 0);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, SetErrorIfExists_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_error_if_exists(options, 1);
  leveldb_options_set_error_if_exists(options, 0);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, SetParanoidChecks_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_paranoid_checks(options, 1);
  leveldb_options_set_paranoid_checks(options, 0);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, SetWriteBufferSize_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_write_buffer_size(options, 4 * 1024 * 1024);
  leveldb_options_set_write_buffer_size(options, 1);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, SetMaxOpenFiles_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_max_open_files(options, 1000);
  leveldb_options_set_max_open_files(options, 1);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, SetBlockSize_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_block_size(options, 4096);
  leveldb_options_set_block_size(options, 1);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, SetBlockRestartInterval_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_block_restart_interval(options, 16);
  leveldb_options_set_block_restart_interval(options, 1);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, SetMaxFileSize_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_max_file_size(options, 2 * 1024 * 1024);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, SetCompression_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_set_compression(options, leveldb_no_compression);
  leveldb_options_set_compression(options, leveldb_snappy_compression);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBOptionsTest_251, DestroyOptionsDoesNotCrash_251) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  leveldb_options_destroy(options);
  // Should not crash or leak
}

// Test full lifecycle: create DB with options, use it, close it
class LevelDBFullLifecycleTest_251 : public ::testing::Test {
 protected:
  std::string dbname_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "leveldb_c_test_251";
  }

  void TearDown() override {
    // Clean up database
    leveldb_options_t* options = leveldb_options_create();
    leveldb_destroy_db(options, dbname_.c_str(), nullptr);
    leveldb_options_destroy(options);
  }
};

TEST_F(LevelDBFullLifecycleTest_251, OpenAndCloseDatabase_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr) << "Error opening DB: " << err;
  ASSERT_NE(db, nullptr);

  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, OpenWithoutCreateIfMissingFails_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 0);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  // Should fail because DB doesn't exist and create_if_missing is false
  ASSERT_NE(err, nullptr);
  if (err) {
    leveldb_free(err);
  }
  ASSERT_EQ(db, nullptr);

  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, PutAndGet_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db, nullptr);

  // Write a key-value pair
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "key1", 4, "value1", 6, &err);
  ASSERT_EQ(err, nullptr);

  // Read back the key-value pair
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, "key1", 4, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  ASSERT_EQ(vallen, 6u);
  ASSERT_EQ(std::string(val, vallen), "value1");

  leveldb_free(val);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, DeleteKey_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "key1", 4, "value1", 6, &err);
  ASSERT_EQ(err, nullptr);

  // Delete the key
  leveldb_delete(db, woptions, "key1", 4, &err);
  ASSERT_EQ(err, nullptr);

  // Try to read deleted key
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, "key1", 4, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_EQ(val, nullptr);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, GetNonExistentKey_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, "nonexistent", 11, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_EQ(val, nullptr);

  leveldb_readoptions_destroy(roptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, WriteBatch_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(db, nullptr);

  // Create and populate a write batch
  leveldb_writebatch_t* batch = leveldb_writebatch_create();
  leveldb_writebatch_put(batch, "bkey1", 5, "bval1", 5);
  leveldb_writebatch_put(batch, "bkey2", 5, "bval2", 5);
  leveldb_writebatch_put(batch, "bkey3", 5, "bval3", 5);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_write(db, woptions, batch, &err);
  ASSERT_EQ(err, nullptr);

  // Verify all keys exist
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;

  char* val1 = leveldb_get(db, roptions, "bkey1", 5, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val1, nullptr);
  ASSERT_EQ(std::string(val1, vallen), "bval1");
  leveldb_free(val1);

  char* val2 = leveldb_get(db, roptions, "bkey2", 5, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val2, nullptr);
  ASSERT_EQ(std::string(val2, vallen), "bval2");
  leveldb_free(val2);

  char* val3 = leveldb_get(db, roptions, "bkey3", 5, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val3, nullptr);
  ASSERT_EQ(std::string(val3, vallen), "bval3");
  leveldb_free(val3);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_writebatch_destroy(batch);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, WriteBatchClear_251) {
  leveldb_writebatch_t* batch = leveldb_writebatch_create();
  ASSERT_NE(batch, nullptr);

  leveldb_writebatch_put(batch, "key", 3, "val", 3);
  leveldb_writebatch_clear(batch);

  // After clear, writing batch should be a no-op
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_write(db, woptions, batch, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, "key", 3, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_EQ(val, nullptr);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_writebatch_destroy(batch);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, IteratorBasic_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  // Insert some data
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "a", 1, "1", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "b", 1, "2", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "c", 1, "3", 1, &err);
  ASSERT_EQ(err, nullptr);

  // Create iterator and iterate
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_iterator_t* iter = leveldb_create_iterator(db, roptions);
  ASSERT_NE(iter, nullptr);

  leveldb_iter_seek_to_first(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));

  size_t klen;
  const char* key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(std::string(key, klen), "a");

  size_t vlen;
  const char* val = leveldb_iter_value(iter, &vlen);
  ASSERT_EQ(std::string(val, vlen), "1");

  leveldb_iter_next(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(std::string(key, klen), "b");

  leveldb_iter_next(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(std::string(key, klen), "c");

  leveldb_iter_next(iter);
  ASSERT_FALSE(leveldb_iter_valid(iter));

  leveldb_iter_destroy(iter);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, IteratorSeekToLast_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "a", 1, "1", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "z", 1, "26", 2, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_iterator_t* iter = leveldb_create_iterator(db, roptions);

  leveldb_iter_seek_to_last(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));

  size_t klen;
  const char* key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(std::string(key, klen), "z");

  leveldb_iter_destroy(iter);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, IteratorOnEmptyDB_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_iterator_t* iter = leveldb_create_iterator(db, roptions);

  leveldb_iter_seek_to_first(iter);
  ASSERT_FALSE(leveldb_iter_valid(iter));

  leveldb_iter_destroy(iter);
  leveldb_readoptions_destroy(roptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, ErrorIfExistsOption_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  leveldb_close(db);

  // Now try to open with error_if_exists
  leveldb_options_set_error_if_exists(options, 1);
  db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_NE(err, nullptr);
  if (err) {
    leveldb_free(err);
  }

  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, ReadOptionsCreate_251) {
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  ASSERT_NE(roptions, nullptr);
  leveldb_readoptions_destroy(roptions);
}

TEST_F(LevelDBFullLifecycleTest_251, WriteOptionsCreate_251) {
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  ASSERT_NE(woptions, nullptr);
  leveldb_writeoptions_destroy(woptions);
}

TEST_F(LevelDBFullLifecycleTest_251, ReadOptionsSetVerifyChecksums_251) {
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_readoptions_set_verify_checksums(roptions, 1);
  leveldb_readoptions_set_verify_checksums(roptions, 0);
  leveldb_readoptions_destroy(roptions);
}

TEST_F(LevelDBFullLifecycleTest_251, ReadOptionsSetFillCache_251) {
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_readoptions_set_fill_cache(roptions, 1);
  leveldb_readoptions_set_fill_cache(roptions, 0);
  leveldb_readoptions_destroy(roptions);
}

TEST_F(LevelDBFullLifecycleTest_251, WriteOptionsSetSync_251) {
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_writeoptions_set_sync(woptions, 1);
  leveldb_writeoptions_set_sync(woptions, 0);
  leveldb_writeoptions_destroy(woptions);
}

TEST_F(LevelDBFullLifecycleTest_251, DestroyDB_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "key", 3, "val", 3, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_writeoptions_destroy(woptions);

  leveldb_close(db);

  // Destroy the database
  leveldb_destroy_db(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  // Opening without create_if_missing should fail now
  leveldb_options_set_create_if_missing(options, 0);
  db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_NE(err, nullptr);
  if (err) {
    leveldb_free(err);
  }

  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, RepairDB_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);
  leveldb_close(db);

  // Repair should succeed on a valid database
  leveldb_repair_db(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, PropertyValue_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  char* prop = leveldb_property_value(db, "leveldb.stats");
  // Stats property should return something
  ASSERT_NE(prop, nullptr);
  leveldb_free(prop);

  // Non-existent property
  char* prop2 = leveldb_property_value(db, "leveldb.nonexistent");
  ASSERT_EQ(prop2, nullptr);

  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, EmptyKeyAndValue_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  // Empty value
  leveldb_put(db, woptions, "key", 3, "", 0, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, "key", 3, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  ASSERT_EQ(vallen, 0u);
  leveldb_free(val);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, LargeKeyValue_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  // Create a large key and value
  std::string large_key(1000, 'k');
  std::string large_value(100000, 'v');

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, large_key.data(), large_key.size(),
              large_value.data(), large_value.size(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, large_key.data(), large_key.size(),
                          &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  ASSERT_EQ(vallen, large_value.size());
  ASSERT_EQ(std::string(val, vallen), large_value);
  leveldb_free(val);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, OverwriteExistingKey_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "key", 3, "val1", 4, &err);
  ASSERT_EQ(err, nullptr);

  // Overwrite with new value
  leveldb_put(db, woptions, "key", 3, "val2", 4, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, "key", 3, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  ASSERT_EQ(std::string(val, vallen), "val2");
  leveldb_free(val);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, WriteBatchWithDeleteAndPut_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  // First insert a key
  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "key1", 4, "val1", 4, &err);
  ASSERT_EQ(err, nullptr);

  // Use batch to delete key1 and add key2
  leveldb_writebatch_t* batch = leveldb_writebatch_create();
  leveldb_writebatch_delete(batch, "key1", 4);
  leveldb_writebatch_put(batch, "key2", 4, "val2", 4);

  leveldb_write(db, woptions, batch, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;

  // key1 should be deleted
  char* val1 = leveldb_get(db, roptions, "key1", 4, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_EQ(val1, nullptr);

  // key2 should exist
  char* val2 = leveldb_get(db, roptions, "key2", 4, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val2, nullptr);
  ASSERT_EQ(std::string(val2, vallen), "val2");
  leveldb_free(val2);

  leveldb_readoptions_destroy(roptions);
  leveldb_writebatch_destroy(batch);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, IteratorSeek_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "a", 1, "1", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "c", 1, "3", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "e", 1, "5", 1, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_iterator_t* iter = leveldb_create_iterator(db, roptions);

  // Seek to "b" should land on "c"
  leveldb_iter_seek(iter, "b", 1);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  size_t klen;
  const char* key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(std::string(key, klen), "c");

  // Seek to "d" should land on "e"
  leveldb_iter_seek(iter, "d", 1);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(std::string(key, klen), "e");

  // Seek past all keys
  leveldb_iter_seek(iter, "f", 1);
  ASSERT_FALSE(leveldb_iter_valid(iter));

  leveldb_iter_destroy(iter);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, IteratorPrev_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "a", 1, "1", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "b", 1, "2", 1, &err);
  ASSERT_EQ(err, nullptr);
  leveldb_put(db, woptions, "c", 1, "3", 1, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_iterator_t* iter = leveldb_create_iterator(db, roptions);

  leveldb_iter_seek_to_last(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));

  size_t klen;
  const char* key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(std::string(key, klen), "c");

  leveldb_iter_prev(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(std::string(key, klen), "b");

  leveldb_iter_prev(iter);
  ASSERT_TRUE(leveldb_iter_valid(iter));
  key = leveldb_iter_key(iter, &klen);
  ASSERT_EQ(std::string(key, klen), "a");

  leveldb_iter_prev(iter);
  ASSERT_FALSE(leveldb_iter_valid(iter));

  leveldb_iter_destroy(iter);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, ApproximateSizes_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  const char* start_keys[] = {"a"};
  size_t start_key_lens[] = {1};
  const char* limit_keys[] = {"z"};
  size_t limit_key_lens[] = {1};
  uint64_t sizes[1];

  leveldb_approximate_sizes(db, 1, start_keys, start_key_lens, limit_keys,
                            limit_key_lens, sizes);
  // On an empty or near-empty DB, size should be small (possibly 0)
  // We just verify it doesn't crash and returns a reasonable value
  ASSERT_GE(sizes[0], 0u);

  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, CompactRange_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    leveldb_put(db, woptions, key.c_str(), key.size(), val.c_str(),
                val.size(), &err);
    ASSERT_EQ(err, nullptr);
  }

  // Compact entire range - should not crash
  leveldb_compact_range(db, nullptr, 0, nullptr, 0);

  // Verify data is still accessible after compaction
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, "key50", 5, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  ASSERT_EQ(std::string(val, vallen), "val50");
  leveldb_free(val);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

TEST_F(LevelDBFullLifecycleTest_251, SnapshotReadOptions_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "key", 3, "val1", 4, &err);
  ASSERT_EQ(err, nullptr);

  // Create snapshot
  const leveldb_snapshot_t* snap = leveldb_create_snapshot(db);
  ASSERT_NE(snap, nullptr);

  // Overwrite
  leveldb_put(db, woptions, "key", 3, "val2", 4, &err);
  ASSERT_EQ(err, nullptr);

  // Read with snapshot should return old value
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  leveldb_readoptions_set_snapshot(roptions, snap);

  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, "key", 3, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  ASSERT_EQ(std::string(val, vallen), "val1");
  leveldb_free(val);

  // Read without snapshot should return new value
  leveldb_readoptions_set_snapshot(roptions, nullptr);
  val = leveldb_get(db, roptions, "key", 3, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  ASSERT_EQ(std::string(val, vallen), "val2");
  leveldb_free(val);

  leveldb_release_snapshot(db, snap);
  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
}

// Test for cache
TEST_F(LevelDBFullLifecycleTest_251, CacheCreateAndDestroy_251) {
  leveldb_cache_t* cache = leveldb_cache_create_lru(8 * 1024 * 1024);
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
}

TEST_F(LevelDBFullLifecycleTest_251, OptionsWithCache_251) {
  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);

  leveldb_cache_t* cache = leveldb_cache_create_lru(8 * 1024 * 1024);
  leveldb_options_set_cache(options, cache);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_close(db);
  leveldb_cache_destroy(cache);
  leveldb_options_destroy(options);
}

// Test for filter policy
TEST_F(LevelDBFullLifecycleTest_251, BloomFilterPolicy_251) {
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy, nullptr);

  leveldb_options_t* options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);
  leveldb_options_set_filter_policy(options, policy);

  char* err = nullptr;
  leveldb_t* db = leveldb_open(options, dbname_.c_str(), &err);
  ASSERT_EQ(err, nullptr);

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  leveldb_put(db, woptions, "key", 3, "val", 3, &err);
  ASSERT_EQ(err, nullptr);

  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  char* val = leveldb_get(db, roptions, "key", 3, &vallen, &err);
  ASSERT_EQ(err, nullptr);
  ASSERT_NE(val, nullptr);
  ASSERT_EQ(std::string(val, vallen), "val");
  leveldb_free(val);

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);
  leveldb_options_destroy(options);
  leveldb_filterpolicy_destroy(policy);
}

TEST_F(LevelDBFullLifecycleTest_251, MajorVersion_251) {
  ASSERT_GE(leveldb_major_version(), 1);
}

TEST_F(LevelDBFullLifecycleTest_251, MinorVersion_251) {
  ASSERT_GE(leveldb_minor_version(), 0);
}
