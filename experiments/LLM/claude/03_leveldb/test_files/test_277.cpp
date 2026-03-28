#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

TEST(LevelDBWriteOptionsCreateTest_277, CreateReturnsNonNull_277) {
  leveldb_writeoptions_t* options = leveldb_writeoptions_create();
  ASSERT_NE(options, nullptr);
  leveldb_writeoptions_destroy(options);
}

TEST(LevelDBWriteOptionsCreateTest_277, MultipleCreatesReturnDistinctPointers_277) {
  leveldb_writeoptions_t* options1 = leveldb_writeoptions_create();
  leveldb_writeoptions_t* options2 = leveldb_writeoptions_create();
  ASSERT_NE(options1, nullptr);
  ASSERT_NE(options2, nullptr);
  ASSERT_NE(options1, options2);
  leveldb_writeoptions_destroy(options1);
  leveldb_writeoptions_destroy(options2);
}

TEST(LevelDBWriteOptionsCreateTest_277, SetSyncDoesNotCrash_277) {
  leveldb_writeoptions_t* options = leveldb_writeoptions_create();
  ASSERT_NE(options, nullptr);
  leveldb_writeoptions_set_sync(options, 0);
  leveldb_writeoptions_set_sync(options, 1);
  leveldb_writeoptions_destroy(options);
}

TEST(LevelDBWriteOptionsCreateTest_277, DestroyAfterCreateDoesNotCrash_277) {
  leveldb_writeoptions_t* options = leveldb_writeoptions_create();
  ASSERT_NE(options, nullptr);
  leveldb_writeoptions_destroy(options);
  // No crash expected
}

TEST(LevelDBWriteOptionsCreateTest_277, UsedInWriteOperation_277) {
  // Test that the write options can be used in a basic DB write workflow
  leveldb_options_t* db_options = leveldb_options_create();
  leveldb_options_set_create_if_missing(db_options, 1);

  char* err = nullptr;
  // Use a temporary directory for the test database
  const char* dbname = "/tmp/leveldb_test_writeoptions_277";
  
  // Clean up any previous test database
  leveldb_destroy_db(db_options, dbname, &err);
  if (err) {
    leveldb_free(err);
    err = nullptr;
  }

  leveldb_t* db = leveldb_open(db_options, dbname, &err);
  if (err != nullptr) {
    // If we can't open the DB, skip the write test but don't fail
    leveldb_free(err);
    leveldb_options_destroy(db_options);
    GTEST_SKIP() << "Could not open test database";
    return;
  }

  leveldb_writeoptions_t* woptions = leveldb_writeoptions_create();
  ASSERT_NE(woptions, nullptr);

  // Write with sync = 0
  leveldb_writeoptions_set_sync(woptions, 0);
  err = nullptr;
  leveldb_put(db, woptions, "key1", 4, "val1", 4, &err);
  EXPECT_EQ(err, nullptr);
  if (err) {
    leveldb_free(err);
    err = nullptr;
  }

  // Write with sync = 1
  leveldb_writeoptions_set_sync(woptions, 1);
  err = nullptr;
  leveldb_put(db, woptions, "key2", 4, "val2", 4, &err);
  EXPECT_EQ(err, nullptr);
  if (err) {
    leveldb_free(err);
    err = nullptr;
  }

  // Verify the writes
  leveldb_readoptions_t* roptions = leveldb_readoptions_create();
  size_t vallen = 0;
  err = nullptr;
  char* val = leveldb_get(db, roptions, "key1", 4, &vallen, &err);
  EXPECT_EQ(err, nullptr);
  if (val) {
    EXPECT_EQ(vallen, 4u);
    EXPECT_EQ(std::string(val, vallen), "val1");
    leveldb_free(val);
  }

  val = leveldb_get(db, roptions, "key2", 4, &vallen, &err);
  EXPECT_EQ(err, nullptr);
  if (val) {
    EXPECT_EQ(vallen, 4u);
    EXPECT_EQ(std::string(val, vallen), "val2");
    leveldb_free(val);
  }

  leveldb_readoptions_destroy(roptions);
  leveldb_writeoptions_destroy(woptions);
  leveldb_close(db);

  // Cleanup
  err = nullptr;
  leveldb_destroy_db(db_options, dbname, &err);
  if (err) leveldb_free(err);
  leveldb_options_destroy(db_options);
}

TEST(LevelDBWriteOptionsCreateTest_277, CreateManyAndDestroyAll_277) {
  // Boundary: creating many write options objects
  const int count = 100;
  std::vector<leveldb_writeoptions_t*> options_list;
  options_list.reserve(count);

  for (int i = 0; i < count; i++) {
    leveldb_writeoptions_t* opt = leveldb_writeoptions_create();
    ASSERT_NE(opt, nullptr);
    options_list.push_back(opt);
  }

  // Destroy all
  for (auto* opt : options_list) {
    leveldb_writeoptions_destroy(opt);
  }
}

TEST(LevelDBWriteOptionsCreateTest_277, SetSyncMultipleTimes_277) {
  leveldb_writeoptions_t* options = leveldb_writeoptions_create();
  ASSERT_NE(options, nullptr);

  // Toggle sync multiple times - should not crash
  for (int i = 0; i < 10; i++) {
    leveldb_writeoptions_set_sync(options, i % 2);
  }

  leveldb_writeoptions_destroy(options);
}
