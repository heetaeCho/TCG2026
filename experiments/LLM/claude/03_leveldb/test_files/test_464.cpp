#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <cstdint>

namespace leveldb {

// Mock Env to test the DeleteDir -> RemoveDir delegation
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewSequentialFile,
              (const std::string& fname, SequentialFile** result), (override));
  MOCK_METHOD(Status, NewRandomAccessFile,
              (const std::string& fname, RandomAccessFile** result), (override));
  MOCK_METHOD(Status, NewWritableFile,
              (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(Status, NewAppendableFile,
              (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(bool, FileExists, (const std::string& fname), (override));
  MOCK_METHOD(Status, GetChildren,
              (const std::string& dir, std::vector<std::string>* result),
              (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, GetFileSize,
              (const std::string& fname, uint64_t* file_size), (override));
  MOCK_METHOD(Status, RenameFile,
              (const std::string& src, const std::string& target), (override));
  MOCK_METHOD(Status, LockFile,
              (const std::string& fname, FileLock** lock), (override));
  MOCK_METHOD(Status, UnlockFile, (FileLock* lock), (override));
  MOCK_METHOD(void, Schedule, (void (*function)(void*), void* arg), (override));
  MOCK_METHOD(void, StartThread, (void (*function)(void*), void* arg),
              (override));
  MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));
  MOCK_METHOD(Status, NewLogger,
              (const std::string& fname, Logger** result), (override));
  MOCK_METHOD(uint64_t, NowMicros, (), (override));
  MOCK_METHOD(void, SleepForMicroseconds, (int micros), (override));
};

class EnvDeleteDirTest_464 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
};

// Test that DeleteDir delegates to RemoveDir with the same directory name
TEST_F(EnvDeleteDirTest_464, DeleteDirDelegatesToRemoveDir_464) {
  std::string dirname = "/tmp/testdir";
  EXPECT_CALL(mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = mock_env_.DeleteDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test that DeleteDir returns the same error status as RemoveDir
TEST_F(EnvDeleteDirTest_464, DeleteDirReturnsRemoveDirError_464) {
  std::string dirname = "/nonexistent/dir";
  EXPECT_CALL(mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::IOError("No such directory")));

  Status s = mock_env_.DeleteDir(dirname);
  EXPECT_TRUE(s.IsIOError());
}

// Test DeleteDir with an empty string dirname
TEST_F(EnvDeleteDirTest_464, DeleteDirEmptyString_464) {
  std::string dirname = "";
  EXPECT_CALL(mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::IOError("Invalid argument")));

  Status s = mock_env_.DeleteDir(dirname);
  EXPECT_TRUE(s.IsIOError());
}

// Test DeleteDir with a root directory
TEST_F(EnvDeleteDirTest_464, DeleteDirRootDirectory_464) {
  std::string dirname = "/";
  EXPECT_CALL(mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::IOError("Permission denied")));

  Status s = mock_env_.DeleteDir(dirname);
  EXPECT_FALSE(s.ok());
}

// Test DeleteDir passes the exact string to RemoveDir
TEST_F(EnvDeleteDirTest_464, DeleteDirPassesExactString_464) {
  std::string dirname = "/some/path/with spaces/and-dashes";
  EXPECT_CALL(mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = mock_env_.DeleteDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test DeleteDir with a long path
TEST_F(EnvDeleteDirTest_464, DeleteDirLongPath_464) {
  std::string dirname(4096, 'a');
  EXPECT_CALL(mock_env_, RemoveDir(dirname))
      .WillOnce(
          ::testing::Return(Status::IOError("File name too long")));

  Status s = mock_env_.DeleteDir(dirname);
  EXPECT_TRUE(s.IsIOError());
}

// Test that DeleteDir calls RemoveDir exactly once
TEST_F(EnvDeleteDirTest_464, DeleteDirCallsRemoveDirOnce_464) {
  std::string dirname = "/tmp/somedir";
  EXPECT_CALL(mock_env_, RemoveDir(dirname))
      .Times(1)
      .WillOnce(::testing::Return(Status::OK()));

  mock_env_.DeleteDir(dirname);
}

// Integration-style test with the default environment
class EnvDefaultTest_464 : public ::testing::Test {
 protected:
  Env* env_;
  std::string test_dir_;

  void SetUp() override {
    env_ = Env::Default();
    ASSERT_TRUE(env_->GetTestDirectory(&test_dir_).ok());
  }
};

// Test that CreateDir and then DeleteDir works on real environment
TEST_F(EnvDefaultTest_464, CreateAndDeleteDir_464) {
  std::string dirname = test_dir_ + "/delete_dir_test_464";

  // Clean up first if it exists
  env_->RemoveDir(dirname);

  Status s = env_->CreateDir(dirname);
  ASSERT_TRUE(s.ok()) << s.ToString();

  s = env_->DeleteDir(dirname);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test DeleteDir on a non-existent directory returns error
TEST_F(EnvDefaultTest_464, DeleteNonExistentDir_464) {
  std::string dirname = test_dir_ + "/this_dir_should_not_exist_464";
  Status s = env_->DeleteDir(dirname);
  EXPECT_FALSE(s.ok());
}

// Test that DeleteDir and RemoveDir have the same behavior
TEST_F(EnvDefaultTest_464, DeleteDirAndRemoveDirConsistency_464) {
  std::string dirname1 = test_dir_ + "/consistency_test1_464";
  std::string dirname2 = test_dir_ + "/consistency_test2_464";

  // Clean up
  env_->RemoveDir(dirname1);
  env_->RemoveDir(dirname2);

  // Create both directories
  ASSERT_TRUE(env_->CreateDir(dirname1).ok());
  ASSERT_TRUE(env_->CreateDir(dirname2).ok());

  // Delete using different methods
  Status s1 = env_->DeleteDir(dirname1);
  Status s2 = env_->RemoveDir(dirname2);

  EXPECT_EQ(s1.ok(), s2.ok());
}

}  // namespace leveldb
