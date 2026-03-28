#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <cstdint>

namespace leveldb {

// Mock Env to serve as the target for EnvWrapper
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewSequentialFile, (const std::string& fname, SequentialFile** result), (override));
  MOCK_METHOD(Status, NewRandomAccessFile, (const std::string& fname, RandomAccessFile** result), (override));
  MOCK_METHOD(Status, NewWritableFile, (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(Status, NewAppendableFile, (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(bool, FileExists, (const std::string& fname), (override));
  MOCK_METHOD(Status, GetChildren, (const std::string& dir, std::vector<std::string>* result), (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, GetFileSize, (const std::string& fname, uint64_t* file_size), (override));
  MOCK_METHOD(Status, RenameFile, (const std::string& src, const std::string& target), (override));
  MOCK_METHOD(Status, LockFile, (const std::string& fname, FileLock** lock), (override));
  MOCK_METHOD(Status, UnlockFile, (FileLock* lock), (override));
  MOCK_METHOD(void, Schedule, (void (*function)(void*), void* arg), (override));
  MOCK_METHOD(void, StartThread, (void (*function)(void*), void* arg), (override));
  MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));
  MOCK_METHOD(Status, NewLogger, (const std::string& fname, Logger** result), (override));
  MOCK_METHOD(uint64_t, NowMicros, (), (override));
  MOCK_METHOD(void, SleepForMicroseconds, (int micros), (override));
};

class EnvWrapperTest_122 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_env_ = new MockEnv();
    wrapper_ = new EnvWrapper(mock_env_);
  }

  void TearDown() override {
    delete wrapper_;
    delete mock_env_;
  }

  MockEnv* mock_env_;
  EnvWrapper* wrapper_;
};

// Test that target() returns the wrapped Env
TEST_F(EnvWrapperTest_122, TargetReturnsWrappedEnv_122) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_122, NewLoggerDelegatesToTarget_122) {
  Logger* logger = nullptr;
  std::string fname = "/tmp/test.log";
  EXPECT_CALL(*mock_env_, NewLogger(fname, &logger))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewLogger(fname, &logger);
  EXPECT_TRUE(s.ok());
}

// Test NewLogger with error from target
TEST_F(EnvWrapperTest_122, NewLoggerReturnsErrorFromTarget_122) {
  Logger* logger = nullptr;
  std::string fname = "/nonexistent/path/test.log";
  EXPECT_CALL(*mock_env_, NewLogger(fname, &logger))
      .WillOnce(::testing::Return(Status::IOError("No such directory")));

  Status s = wrapper_->NewLogger(fname, &logger);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_122, NewSequentialFileDelegatesToTarget_122) {
  SequentialFile* file = nullptr;
  std::string fname = "/tmp/seq_file";
  EXPECT_CALL(*mock_env_, NewSequentialFile(fname, &file))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewSequentialFile(fname, &file);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_122, NewRandomAccessFileDelegatesToTarget_122) {
  RandomAccessFile* file = nullptr;
  std::string fname = "/tmp/rand_file";
  EXPECT_CALL(*mock_env_, NewRandomAccessFile(fname, &file))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewRandomAccessFile(fname, &file);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_122, NewWritableFileDelegatesToTarget_122) {
  WritableFile* file = nullptr;
  std::string fname = "/tmp/writable_file";
  EXPECT_CALL(*mock_env_, NewWritableFile(fname, &file))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewWritableFile(fname, &file);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_122, NewAppendableFileDelegatesToTarget_122) {
  WritableFile* file = nullptr;
  std::string fname = "/tmp/appendable_file";
  EXPECT_CALL(*mock_env_, NewAppendableFile(fname, &file))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewAppendableFile(fname, &file);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_122, FileExistsDelegatesToTarget_122) {
  std::string fname = "/tmp/existing_file";
  EXPECT_CALL(*mock_env_, FileExists(fname))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists(fname));
}

// Test FileExists returns false
TEST_F(EnvWrapperTest_122, FileExistsReturnsFalse_122) {
  std::string fname = "/tmp/nonexistent_file";
  EXPECT_CALL(*mock_env_, FileExists(fname))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper_->FileExists(fname));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_122, GetChildrenDelegatesToTarget_122) {
  std::string dir = "/tmp";
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren(dir, &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{"a", "b", "c"}),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren(dir, &children);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(children.size(), 3u);
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_122, RemoveFileDelegatesToTarget_122) {
  std::string fname = "/tmp/file_to_remove";
  EXPECT_CALL(*mock_env_, RemoveFile(fname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveFile(fname);
  EXPECT_TRUE(s.ok());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_122, CreateDirDelegatesToTarget_122) {
  std::string dirname = "/tmp/new_dir";
  EXPECT_CALL(*mock_env_, CreateDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->CreateDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_122, RemoveDirDelegatesToTarget_122) {
  std::string dirname = "/tmp/dir_to_remove";
  EXPECT_CALL(*mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_122, GetFileSizeDelegatesToTarget_122) {
  std::string fname = "/tmp/file_with_size";
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize(fname, &size))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(12345u),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize(fname, &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 12345u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_122, RenameFileDelegatesToTarget_122) {
  std::string src = "/tmp/old_name";
  std::string target = "/tmp/new_name";
  EXPECT_CALL(*mock_env_, RenameFile(src, target))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile(src, target);
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_122, LockFileDelegatesToTarget_122) {
  std::string fname = "/tmp/lock_file";
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile(fname, &lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->LockFile(fname, &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_122, UnlockFileDelegatesToTarget_122) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyScheduleFunc(void* arg) {}

TEST_F(EnvWrapperTest_122, ScheduleDelegatesToTarget_122) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, &dummy_arg))
      .Times(1);

  wrapper_->Schedule(DummyScheduleFunc, &dummy_arg);
}

// Test StartThread delegates to target
static void DummyThreadFunc(void* arg) {}

TEST_F(EnvWrapperTest_122, StartThreadDelegatesToTarget_122) {
  int dummy_arg = 99;
  EXPECT_CALL(*mock_env_, StartThread(DummyThreadFunc, &dummy_arg))
      .Times(1);

  wrapper_->StartThread(DummyThreadFunc, &dummy_arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_122, GetTestDirectoryDelegatesToTarget_122) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(&path))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<0>(std::string("/tmp/test_dir")),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test_dir");
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_122, NowMicrosDelegatesToTarget_122) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890u));

  uint64_t result = wrapper_->NowMicros();
  EXPECT_EQ(result, 1234567890u);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_122, SleepForMicrosecondsDelegatesToTarget_122) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000))
      .Times(1);

  wrapper_->SleepForMicroseconds(1000);
}

// Test NewLogger with empty filename
TEST_F(EnvWrapperTest_122, NewLoggerWithEmptyFilename_122) {
  Logger* logger = nullptr;
  std::string fname = "";
  EXPECT_CALL(*mock_env_, NewLogger(fname, &logger))
      .WillOnce(::testing::Return(Status::IOError("empty filename")));

  Status s = wrapper_->NewLogger(fname, &logger);
  EXPECT_TRUE(s.IsIOError());
}

// Test that wrapper correctly forwards arguments for NewWritableFile error case
TEST_F(EnvWrapperTest_122, NewWritableFileError_122) {
  WritableFile* file = nullptr;
  std::string fname = "/invalid/path/file";
  EXPECT_CALL(*mock_env_, NewWritableFile(fname, &file))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->NewWritableFile(fname, &file);
  EXPECT_TRUE(s.IsIOError());
}

// Test RemoveFile with error
TEST_F(EnvWrapperTest_122, RemoveFileError_122) {
  std::string fname = "/nonexistent/file";
  EXPECT_CALL(*mock_env_, RemoveFile(fname))
      .WillOnce(::testing::Return(Status::IOError("file not found")));

  Status s = wrapper_->RemoveFile(fname);
  EXPECT_TRUE(s.IsIOError());
}

// Test GetFileSize with error
TEST_F(EnvWrapperTest_122, GetFileSizeError_122) {
  std::string fname = "/nonexistent/file";
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize(fname, &size))
      .WillOnce(::testing::Return(Status::IOError("not found")));

  Status s = wrapper_->GetFileSize(fname, &size);
  EXPECT_TRUE(s.IsIOError());
}

// Test RenameFile with error
TEST_F(EnvWrapperTest_122, RenameFileError_122) {
  std::string src = "/tmp/nonexistent";
  std::string target = "/tmp/new_name";
  EXPECT_CALL(*mock_env_, RenameFile(src, target))
      .WillOnce(::testing::Return(Status::IOError("source not found")));

  Status s = wrapper_->RenameFile(src, target);
  EXPECT_TRUE(s.IsIOError());
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_122, SleepForMicrosecondsZero_122) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);

  wrapper_->SleepForMicroseconds(0);
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_122, NowMicrosReturnsZero_122) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0u));

  uint64_t result = wrapper_->NowMicros();
  EXPECT_EQ(result, 0u);
}

// Test using Default Env with EnvWrapper
TEST_F(EnvWrapperTest_122, DefaultEnvIsNotNull_122) {
  Env* default_env = Env::Default();
  ASSERT_NE(default_env, nullptr);

  EnvWrapper default_wrapper(default_env);
  EXPECT_EQ(default_wrapper.target(), default_env);
}

// Test NewLogger with Default Env (integration-style)
TEST_F(EnvWrapperTest_122, NewLoggerWithDefaultEnv_122) {
  Env* default_env = Env::Default();
  EnvWrapper default_wrapper(default_env);

  std::string test_dir;
  Status s = default_wrapper.GetTestDirectory(&test_dir);
  EXPECT_TRUE(s.ok());

  Logger* logger = nullptr;
  std::string log_path = test_dir + "/env_wrapper_test_122.log";
  s = default_wrapper.NewLogger(log_path, &logger);
  EXPECT_TRUE(s.ok());
  if (logger != nullptr) {
    delete logger;
  }

  // Cleanup
  default_wrapper.RemoveFile(log_path);
}

// Test GetChildren with empty directory result
TEST_F(EnvWrapperTest_122, GetChildrenEmptyResult_122) {
  std::string dir = "/tmp/empty_dir";
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren(dir, &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren(dir, &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test Schedule with null arg
TEST_F(EnvWrapperTest_122, ScheduleWithNullArg_122) {
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, nullptr))
      .Times(1);

  wrapper_->Schedule(DummyScheduleFunc, nullptr);
}

// Test multiple NewLogger calls
TEST_F(EnvWrapperTest_122, MultipleNewLoggerCalls_122) {
  Logger* logger1 = nullptr;
  Logger* logger2 = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger(::testing::_, ::testing::_))
      .Times(2)
      .WillRepeatedly(::testing::Return(Status::OK()));

  Status s1 = wrapper_->NewLogger("/tmp/log1", &logger1);
  Status s2 = wrapper_->NewLogger("/tmp/log2", &logger2);
  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.ok());
}

// Test LockFile error
TEST_F(EnvWrapperTest_122, LockFileError_122) {
  std::string fname = "/tmp/lock";
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile(fname, &lock))
      .WillOnce(::testing::Return(Status::IOError("lock failed")));

  Status s = wrapper_->LockFile(fname, &lock);
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir error
TEST_F(EnvWrapperTest_122, CreateDirError_122) {
  std::string dirname = "/root/protected_dir";
  EXPECT_CALL(*mock_env_, CreateDir(dirname))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->CreateDir(dirname);
  EXPECT_TRUE(s.IsIOError());
}

// Test RemoveDir error
TEST_F(EnvWrapperTest_122, RemoveDirError_122) {
  std::string dirname = "/nonexistent_dir";
  EXPECT_CALL(*mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::IOError("not found")));

  Status s = wrapper_->RemoveDir(dirname);
  EXPECT_TRUE(s.IsIOError());
}

}  // namespace leveldb
