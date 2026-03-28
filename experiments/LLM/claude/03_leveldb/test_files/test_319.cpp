#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/status.h"
#include "db/filename.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

// Mock Env for testing DestroyDB
class MockEnv : public EnvWrapper {
 public:
  explicit MockEnv(Env* base) : EnvWrapper(base) {}

  MOCK_METHOD(Status, GetChildren, (const std::string& dir, std::vector<std::string>* result), (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, LockFile, (const std::string& fname, FileLock** lock), (override));
  MOCK_METHOD(Status, UnlockFile, (FileLock* lock), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& dirname), (override));
};

class DestroyDBTest_319 : public ::testing::Test {
 protected:
  void SetUp() override {
    base_env_ = Env::Default();
    mock_env_ = new MockEnv(base_env_);
  }

  void TearDown() override {
    delete mock_env_;
  }

  Env* base_env_;
  MockEnv* mock_env_;
};

// Test: When GetChildren fails, DestroyDB should return OK
TEST_F(DestroyDBTest_319, GetChildrenFails_ReturnsOK_319) {
  Options options;
  options.env = mock_env_;

  EXPECT_CALL(*mock_env_, GetChildren(::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("dir not found")));

  Status s = DestroyDB("/tmp/testdb_319_nonexistent", options);
  EXPECT_TRUE(s.ok());
}

// Test: When GetChildren succeeds but LockFile fails, DestroyDB returns the lock error
TEST_F(DestroyDBTest_319, LockFileFails_ReturnsError_319) {
  Options options;
  options.env = mock_env_;

  std::vector<std::string> children = {"000001.log", "LOCK"};
  EXPECT_CALL(*mock_env_, GetChildren(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(children),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_env_, LockFile(::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("cannot lock")));

  Status s = DestroyDB("/tmp/testdb_319_lockfail", options);
  EXPECT_TRUE(s.IsIOError());
}

// Test: Normal operation - all files are removed successfully
TEST_F(DestroyDBTest_319, NormalOperation_AllFilesRemoved_319) {
  Options options;
  options.env = mock_env_;

  std::vector<std::string> children = {"000001.log", "000002.ldb", "MANIFEST-000003", "CURRENT", "LOCK"};
  EXPECT_CALL(*mock_env_, GetChildren(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(children),
          ::testing::Return(Status::OK())));

  FileLock* fake_lock = reinterpret_cast<FileLock*>(0x12345);
  EXPECT_CALL(*mock_env_, LockFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(fake_lock),
          ::testing::Return(Status::OK())));

  // LOCK file should NOT be removed by the loop (type == kDBLockFile)
  // Other files should be removed
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::HasSubstr("000001.log")))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::HasSubstr("000002.ldb")))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::HasSubstr("MANIFEST-000003")))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::HasSubstr("CURRENT")))
      .WillOnce(::testing::Return(Status::OK()));
  // The lock file name (LOCK) is removed after UnlockFile
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::EndsWith("LOCK")))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_env_, UnlockFile(fake_lock))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_env_, RemoveDir(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = DestroyDB("/tmp/testdb_319_normal", options);
  EXPECT_TRUE(s.ok());
}

// Test: When one file removal fails, the error status is propagated
TEST_F(DestroyDBTest_319, FileRemovalFails_ReturnsError_319) {
  Options options;
  options.env = mock_env_;

  std::vector<std::string> children = {"000001.log", "LOCK"};
  EXPECT_CALL(*mock_env_, GetChildren(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(children),
          ::testing::Return(Status::OK())));

  FileLock* fake_lock = reinterpret_cast<FileLock*>(0x12345);
  EXPECT_CALL(*mock_env_, LockFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(fake_lock),
          ::testing::Return(Status::OK())));

  // The log file removal fails
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::HasSubstr("000001.log")))
      .WillOnce(::testing::Return(Status::IOError("remove failed")));
  // Lock file removal at the end
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::EndsWith("LOCK")))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_env_, UnlockFile(fake_lock))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_env_, RemoveDir(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = DestroyDB("/tmp/testdb_319_removefail", options);
  EXPECT_TRUE(s.IsIOError());
}

// Test: Empty directory - no files to remove, should succeed
TEST_F(DestroyDBTest_319, EmptyDirectory_ReturnsOK_319) {
  Options options;
  options.env = mock_env_;

  std::vector<std::string> children;  // empty
  EXPECT_CALL(*mock_env_, GetChildren(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(children),
          ::testing::Return(Status::OK())));

  FileLock* fake_lock = reinterpret_cast<FileLock*>(0x12345);
  EXPECT_CALL(*mock_env_, LockFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(fake_lock),
          ::testing::Return(Status::OK())));

  // No file removals in the loop
  // Lock file removal at the end
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::EndsWith("LOCK")))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_env_, UnlockFile(fake_lock))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_env_, RemoveDir(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = DestroyDB("/tmp/testdb_319_empty", options);
  EXPECT_TRUE(s.ok());
}

// Test: Files that don't parse as valid leveldb filenames are skipped
TEST_F(DestroyDBTest_319, UnrecognizedFilesAreSkipped_319) {
  Options options;
  options.env = mock_env_;

  std::vector<std::string> children = {"random_file.txt", "not_a_db_file", "LOCK"};
  EXPECT_CALL(*mock_env_, GetChildren(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(children),
          ::testing::Return(Status::OK())));

  FileLock* fake_lock = reinterpret_cast<FileLock*>(0x12345);
  EXPECT_CALL(*mock_env_, LockFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(fake_lock),
          ::testing::Return(Status::OK())));

  // Only the LOCK file removal at end; no other RemoveFile calls for unrecognized files
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::EndsWith("LOCK")))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_env_, UnlockFile(fake_lock))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_env_, RemoveDir(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = DestroyDB("/tmp/testdb_319_unrecognized", options);
  EXPECT_TRUE(s.ok());
}

// Integration test: DestroyDB on an actual (real env) database
class DestroyDBIntegrationTest_319 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/destroydb_test_319";
  }

  void TearDown() override {
    // Clean up in case test fails
    DestroyDB(dbname_, Options());
  }

  Env* env_;
  std::string dbname_;
};

// Test: Create a DB, then destroy it, the directory should be cleaned
TEST_F(DestroyDBIntegrationTest_319, CreateThenDestroy_319) {
  Options options;
  options.create_if_missing = true;

  DB* db = nullptr;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Write some data
  s = db->Put(WriteOptions(), "key1", "value1");
  ASSERT_TRUE(s.ok());

  delete db;
  db = nullptr;

  // Destroy the database
  s = DestroyDB(dbname_, options);
  EXPECT_TRUE(s.ok()) << s.ToString();

  // Verify that the database files are gone (trying to open without create should fail or dir empty)
  Options no_create_options;
  no_create_options.create_if_missing = false;
  s = DB::Open(no_create_options, dbname_, &db);
  EXPECT_FALSE(s.ok());
  // db should be nullptr on failure, but just in case
  if (db != nullptr) {
    delete db;
  }
}

// Test: DestroyDB on a non-existent path should return OK
TEST_F(DestroyDBIntegrationTest_319, NonExistentPath_ReturnsOK_319) {
  std::string non_existent = testing::TempDir() + "/no_such_db_319_xyz";
  Status s = DestroyDB(non_existent, Options());
  EXPECT_TRUE(s.ok());
}

// Test: DestroyDB with default options
TEST_F(DestroyDBIntegrationTest_319, DefaultOptions_319) {
  Options options;
  options.create_if_missing = true;

  DB* db = nullptr;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());
  delete db;

  // Use default options for destroy
  s = DestroyDB(dbname_, Options());
  EXPECT_TRUE(s.ok());
}

// Test: DestroyDB called twice should succeed both times
TEST_F(DestroyDBIntegrationTest_319, DoubleDestroy_319) {
  Options options;
  options.create_if_missing = true;

  DB* db = nullptr;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());
  delete db;

  s = DestroyDB(dbname_, options);
  EXPECT_TRUE(s.ok());

  // Second destroy on already destroyed DB
  s = DestroyDB(dbname_, options);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
