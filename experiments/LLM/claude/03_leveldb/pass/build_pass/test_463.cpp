#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <memory>

namespace leveldb {

// A mock Env that allows us to verify RemoveDir delegates to DeleteDir
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
  MOCK_METHOD(Status, DeleteFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, DeleteDir, (const std::string& dirname), (override));
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

class EnvTest_463 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
};

// Test that RemoveDir delegates to DeleteDir and returns OK status
TEST_F(EnvTest_463, RemoveDirDelegatesToDeleteDir_463) {
  std::string dirname = "/tmp/testdir";
  EXPECT_CALL(mock_env_, DeleteDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = mock_env_.RemoveDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test that RemoveDir returns the same error status that DeleteDir returns
TEST_F(EnvTest_463, RemoveDirReturnsErrorFromDeleteDir_463) {
  std::string dirname = "/tmp/nonexistent";
  EXPECT_CALL(mock_env_, DeleteDir(dirname))
      .WillOnce(::testing::Return(Status::IOError("directory not found")));

  Status s = mock_env_.RemoveDir(dirname);
  EXPECT_TRUE(s.IsIOError());
}

// Test RemoveDir with empty string dirname
TEST_F(EnvTest_463, RemoveDirWithEmptyString_463) {
  std::string dirname = "";
  EXPECT_CALL(mock_env_, DeleteDir(dirname))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty dirname")));

  Status s = mock_env_.RemoveDir(dirname);
  EXPECT_FALSE(s.ok());
}

// Test RemoveDir passes the exact dirname string to DeleteDir
TEST_F(EnvTest_463, RemoveDirPassesExactDirname_463) {
  std::string dirname = "/some/deeply/nested/directory/path";
  EXPECT_CALL(mock_env_, DeleteDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = mock_env_.RemoveDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir with a dirname containing special characters
TEST_F(EnvTest_463, RemoveDirWithSpecialCharacters_463) {
  std::string dirname = "/tmp/test dir with spaces/and-dashes_and.dots";
  EXPECT_CALL(mock_env_, DeleteDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = mock_env_.RemoveDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir when DeleteDir returns NotFound
TEST_F(EnvTest_463, RemoveDirReturnsNotFoundFromDeleteDir_463) {
  std::string dirname = "/tmp/doesnotexist";
  EXPECT_CALL(mock_env_, DeleteDir(dirname))
      .WillOnce(::testing::Return(Status::NotFound("no such directory")));

  Status s = mock_env_.RemoveDir(dirname);
  EXPECT_TRUE(s.IsNotFound());
}

// Test that RemoveDir can be called multiple times
TEST_F(EnvTest_463, RemoveDirCalledMultipleTimes_463) {
  std::string dirname1 = "/tmp/dir1";
  std::string dirname2 = "/tmp/dir2";

  EXPECT_CALL(mock_env_, DeleteDir(dirname1))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(mock_env_, DeleteDir(dirname2))
      .WillOnce(::testing::Return(Status::OK()));

  Status s1 = mock_env_.RemoveDir(dirname1);
  Status s2 = mock_env_.RemoveDir(dirname2);
  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.ok());
}

// Test using the default Env for basic directory operations
TEST_F(EnvTest_463, DefaultEnvCreateAndRemoveDir_463) {
  Env* env = Env::Default();
  std::string test_dir;
  ASSERT_TRUE(env->GetTestDirectory(&test_dir).ok());

  std::string dirname = test_dir + "/removedir_test_463";

  // Create directory
  Status create_status = env->CreateDir(dirname);
  ASSERT_TRUE(create_status.ok());

  // Remove using RemoveDir (which delegates to DeleteDir)
  Status remove_status = env->RemoveDir(dirname);
  EXPECT_TRUE(remove_status.ok());
}

// Test that RemoveDir on a non-existent directory returns an error on default env
TEST_F(EnvTest_463, DefaultEnvRemoveDirNonExistent_463) {
  Env* env = Env::Default();
  std::string test_dir;
  ASSERT_TRUE(env->GetTestDirectory(&test_dir).ok());

  std::string dirname = test_dir + "/this_dir_should_not_exist_463";

  Status s = env->RemoveDir(dirname);
  EXPECT_FALSE(s.ok());
}

// Test that RemoveDir with a trailing slash is correctly passed to DeleteDir
TEST_F(EnvTest_463, RemoveDirWithTrailingSlash_463) {
  std::string dirname = "/tmp/testdir/";
  EXPECT_CALL(mock_env_, DeleteDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = mock_env_.RemoveDir(dirname);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
