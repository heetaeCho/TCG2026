#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <cstdint>

namespace leveldb {

// A mock Env that allows us to test the RemoveFile -> DeleteFile delegation
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

class EnvTest_465 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
};

// Test that RemoveFile delegates to DeleteFile with the same filename
TEST_F(EnvTest_465, RemoveFileDelegatesToDeleteFile_465) {
  std::string fname = "/tmp/testfile.txt";
  EXPECT_CALL(mock_env_, DeleteFile(fname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = mock_env_.RemoveFile(fname);
  EXPECT_TRUE(s.ok());
}

// Test that RemoveFile returns the error status from DeleteFile
TEST_F(EnvTest_465, RemoveFileReturnsDeleteFileError_465) {
  std::string fname = "/tmp/nonexistent.txt";
  EXPECT_CALL(mock_env_, DeleteFile(fname))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));

  Status s = mock_env_.RemoveFile(fname);
  EXPECT_TRUE(s.IsNotFound());
}

// Test RemoveFile with an empty filename
TEST_F(EnvTest_465, RemoveFileEmptyFilename_465) {
  std::string fname = "";
  EXPECT_CALL(mock_env_, DeleteFile(fname))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty filename")));

  Status s = mock_env_.RemoveFile(fname);
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test RemoveFile passes the exact string to DeleteFile
TEST_F(EnvTest_465, RemoveFilePassesExactFilename_465) {
  std::string fname = "/some/deep/nested/path/to/file.dat";
  EXPECT_CALL(mock_env_, DeleteFile(fname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = mock_env_.RemoveFile(fname);
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile with IOError from DeleteFile
TEST_F(EnvTest_465, RemoveFileReturnsIOError_465) {
  std::string fname = "/tmp/locked_file.txt";
  EXPECT_CALL(mock_env_, DeleteFile(fname))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = mock_env_.RemoveFile(fname);
  EXPECT_TRUE(s.IsIOError());
}

// Test that Default() returns a non-null Env
TEST_F(EnvTest_465, DefaultEnvIsNotNull_465) {
  Env* env = Env::Default();
  ASSERT_NE(env, nullptr);
}

// Test that Default() returns the same instance on multiple calls
TEST_F(EnvTest_465, DefaultEnvReturnsSameInstance_465) {
  Env* env1 = Env::Default();
  Env* env2 = Env::Default();
  EXPECT_EQ(env1, env2);
}

// Test basic file operations using the default Env
class EnvDefaultTest_465 : public ::testing::Test {
 protected:
  Env* env_;
  std::string test_dir_;

  void SetUp() override {
    env_ = Env::Default();
    ASSERT_TRUE(env_->GetTestDirectory(&test_dir_).ok());
  }
};

// Test creating and removing a file using the default Env
TEST_F(EnvDefaultTest_465, CreateAndRemoveFile_465) {
  std::string fname = test_dir_ + "/env_test_remove_file_465";

  // Create a file
  WritableFile* writable_file = nullptr;
  Status s = env_->NewWritableFile(fname, &writable_file);
  ASSERT_TRUE(s.ok());
  delete writable_file;

  // Verify it exists
  EXPECT_TRUE(env_->FileExists(fname));

  // Remove using RemoveFile
  s = env_->RemoveFile(fname);
  EXPECT_TRUE(s.ok());

  // Verify it no longer exists
  EXPECT_FALSE(env_->FileExists(fname));
}

// Test RemoveFile on a non-existent file using default env
TEST_F(EnvDefaultTest_465, RemoveNonExistentFile_465) {
  std::string fname = test_dir_ + "/non_existent_file_465";
  Status s = env_->RemoveFile(fname);
  EXPECT_FALSE(s.ok());
}

// Test RemoveFile with special characters in filename
TEST_F(EnvDefaultTest_465, RemoveFileSpecialCharacters_465) {
  std::string fname = test_dir_ + "/file_with-special.chars_465";

  // Create the file
  WritableFile* writable_file = nullptr;
  Status s = env_->NewWritableFile(fname, &writable_file);
  ASSERT_TRUE(s.ok());
  delete writable_file;

  // Remove it
  s = env_->RemoveFile(fname);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(env_->FileExists(fname));
}

// Test that RemoveFile and DeleteFile have the same effect
TEST_F(EnvDefaultTest_465, RemoveFileAndDeleteFileEquivalence_465) {
  std::string fname1 = test_dir_ + "/env_test_delete_465";
  std::string fname2 = test_dir_ + "/env_test_remove_465";

  // Create two files
  WritableFile* wf1 = nullptr;
  WritableFile* wf2 = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname1, &wf1).ok());
  ASSERT_TRUE(env_->NewWritableFile(fname2, &wf2).ok());
  delete wf1;
  delete wf2;

  // Delete one with DeleteFile, the other with RemoveFile
  Status s1 = env_->DeleteFile(fname1);
  Status s2 = env_->RemoveFile(fname2);

  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.ok());

  EXPECT_FALSE(env_->FileExists(fname1));
  EXPECT_FALSE(env_->FileExists(fname2));
}

}  // namespace leveldb
