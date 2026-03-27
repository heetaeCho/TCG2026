// File: db/c_repair_db_test.cc

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "leveldb/c.h"

// Utility: unique temp directory name per test run.
static std::string TempDir(const std::string& suffix) {
  // Very basic per-process uniquifier.
  return std::string("repairdb_test_") + suffix + "_" + std::to_string(::getpid());
}

// Helper: create a minimal, valid DB at path using C API.
static void CreateMinimalDB(const std::string& path) {
  char* err = nullptr;

  leveldb_options_t* opts = leveldb_options_create();
  leveldb_options_set_create_if_missing(opts, 1);

  leveldb_t* db = leveldb_open(opts, path.c_str(), &err);
  ASSERT_EQ(nullptr, err) << "leveldb_open failed: " << err;
  ASSERT_NE(nullptr, db);

  leveldb_close(db);
  leveldb_options_destroy(opts);
  if (err) leveldb_free(err);
}

// Helper: destroy DB directory if it exists (best-effort cleanup).
static void DestroyDBIfExists(const std::string& path) {
  char* err = nullptr;
  leveldb_options_t* opts = leveldb_options_create();
  leveldb_destroy_db(opts, path.c_str(), &err);
  if (err) leveldb_free(err);
  leveldb_options_destroy(opts);
}

// =============== Tests ===============

TEST(LevelDBRepairDB_233, Repair_OnValidDB_PathLeavesErrNull_233) {
  // Arrange
  const std::string dbpath = TempDir("ok");
  DestroyDBIfExists(dbpath);         // clean slate
  CreateMinimalDB(dbpath);           // ensure a valid DB exists

  leveldb_options_t* opts = leveldb_options_create();
  char* err = nullptr;

  // Act
  leveldb_repair_db(opts, dbpath.c_str(), &err);

  // Assert
  EXPECT_EQ(nullptr, err) << "Expected no error for repairing a valid DB";
  if (err) leveldb_free(err);

  // Cleanup
  DestroyDBIfExists(dbpath);
  leveldb_options_destroy(opts);
}

TEST(LevelDBRepairDB_233, Repair_WithNonexistentPath_SetsErrptr_233) {
  // Arrange
  const std::string dbpath = TempDir("missing");  // do NOT create it
  DestroyDBIfExists(dbpath);                      // ensure it does not exist

  leveldb_options_t* opts = leveldb_options_create();
  char* err = nullptr;

  // Act
  leveldb_repair_db(opts, dbpath.c_str(), &err);

  // Assert
  // Observable behavior: on failure, errptr should be set to a non-null message.
  EXPECT_NE(nullptr, err) << "Expected error for repairing a non-existent DB path";
  if (err) leveldb_free(err);

  // Cleanup
  leveldb_options_destroy(opts);
}

TEST(LevelDBRepairDB_233, Repair_WithEmptyName_SetsErrptr_233) {
  // Arrange
  leveldb_options_t* opts = leveldb_options_create();
  char* err = nullptr;

  // Act
  leveldb_repair_db(opts, /*name=*/"", &err);

  // Assert
  EXPECT_NE(nullptr, err) << "Expected error when DB name/path is empty";
  if (err) leveldb_free(err);

  // Cleanup
  leveldb_options_destroy(opts);
}
