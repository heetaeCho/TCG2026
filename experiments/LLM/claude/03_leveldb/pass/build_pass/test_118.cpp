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

class EnvWrapperTest_118 : public ::testing::Test {
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

// Test that target() returns the correct target env
TEST_F(EnvWrapperTest_118, TargetReturnsCorrectEnv_118) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_118, UnlockFileDelegatesToTarget_118) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile propagates error from target
TEST_F(EnvWrapperTest_118, UnlockFilePropagatesToError_118) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::IOError("unlock failed")));
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.IsIOError());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_118, LockFileDelegatesToTarget_118) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("test_lock", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->LockFile("test_lock", &lock);
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_118, NewSequentialFileDelegatesToTarget_118) {
  SequentialFile* file = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("test.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewSequentialFile("test.txt", &file);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_118, NewRandomAccessFileDelegatesToTarget_118) {
  RandomAccessFile* file = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("test.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewRandomAccessFile("test.txt", &file);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_118, NewWritableFileDelegatesToTarget_118) {
  WritableFile* file = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("test.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewWritableFile("test.txt", &file);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_118, NewAppendableFileDelegatesToTarget_118) {
  WritableFile* file = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("test.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewAppendableFile("test.txt", &file);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target - file exists
TEST_F(EnvWrapperTest_118, FileExistsReturnsTrueWhenTargetReturnsTrue_118) {
  EXPECT_CALL(*mock_env_, FileExists("existing.txt"))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists("existing.txt"));
}

// Test FileExists delegates to target - file does not exist
TEST_F(EnvWrapperTest_118, FileExistsReturnsFalseWhenTargetReturnsFalse_118) {
  EXPECT_CALL(*mock_env_, FileExists("nonexistent.txt"))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists("nonexistent.txt"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_118, GetChildrenDelegatesToTarget_118) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/dir", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{"a", "b", "c"}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren("/dir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(children.size(), 3u);
  EXPECT_EQ(children[0], "a");
  EXPECT_EQ(children[1], "b");
  EXPECT_EQ(children[2], "c");
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_118, RemoveFileDelegatesToTarget_118) {
  EXPECT_CALL(*mock_env_, RemoveFile("test.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveFile("test.txt");
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile error propagation
TEST_F(EnvWrapperTest_118, RemoveFilePropagatesToError_118) {
  EXPECT_CALL(*mock_env_, RemoveFile("nonexistent.txt"))
      .WillOnce(::testing::Return(Status::IOError("file not found")));
  Status s = wrapper_->RemoveFile("nonexistent.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_118, CreateDirDelegatesToTarget_118) {
  EXPECT_CALL(*mock_env_, CreateDir("/newdir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->CreateDir("/newdir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_118, RemoveDirDelegatesToTarget_118) {
  EXPECT_CALL(*mock_env_, RemoveDir("/olddir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir("/olddir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_118, GetFileSizeDelegatesToTarget_118) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("test.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(12345u),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("test.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 12345u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_118, RenameFileDelegatesToTarget_118) {
  EXPECT_CALL(*mock_env_, RenameFile("old.txt", "new.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile("old.txt", "new.txt");
  EXPECT_TRUE(s.ok());
}

// Test RenameFile error propagation
TEST_F(EnvWrapperTest_118, RenameFilePropagatesToError_118) {
  EXPECT_CALL(*mock_env_, RenameFile("old.txt", "new.txt"))
      .WillOnce(::testing::Return(Status::IOError("rename failed")));
  Status s = wrapper_->RenameFile("old.txt", "new.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test LockFile error propagation
TEST_F(EnvWrapperTest_118, LockFilePropagatesToError_118) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("test_lock", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("lock failed")));
  Status s = wrapper_->LockFile("test_lock", &lock);
  EXPECT_TRUE(s.IsIOError());
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_118, GetTestDirectoryDelegatesToTarget_118) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<0>("/tmp/test"),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_118, NewLoggerDelegatesToTarget_118) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewLogger("log.txt", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_118, NowMicrosDelegatesToTarget_118) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890u));
  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890u);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_118, SleepForMicrosecondsDelegatesToTarget_118) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000))
      .Times(1);
  wrapper_->SleepForMicroseconds(1000);
}

// Test Schedule delegates to target
static void DummyScheduleFunc(void* arg) {}

TEST_F(EnvWrapperTest_118, ScheduleDelegatesToTarget_118) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, &dummy_arg))
      .Times(1);
  wrapper_->Schedule(DummyScheduleFunc, &dummy_arg);
}

// Test StartThread delegates to target
static void DummyThreadFunc(void* arg) {}

TEST_F(EnvWrapperTest_118, StartThreadDelegatesToTarget_118) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, StartThread(DummyThreadFunc, &dummy_arg))
      .Times(1);
  wrapper_->StartThread(DummyThreadFunc, &dummy_arg);
}

// Test with empty filename strings
TEST_F(EnvWrapperTest_118, EmptyFilenameDelegatesToTarget_118) {
  EXPECT_CALL(*mock_env_, FileExists(""))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists(""));
}

// Test GetFileSize with zero size
TEST_F(EnvWrapperTest_118, GetFileSizeZeroDelegatesToTarget_118) {
  uint64_t size = 999;
  EXPECT_CALL(*mock_env_, GetFileSize("empty.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(0u),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("empty.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0u);
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_118, NowMicrosReturnsZero_118) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0u));
  EXPECT_EQ(wrapper_->NowMicros(), 0u);
}

// Test NowMicros returns max value
TEST_F(EnvWrapperTest_118, NowMicrosReturnsMaxValue_118) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(std::numeric_limits<uint64_t>::max()));
  EXPECT_EQ(wrapper_->NowMicros(), std::numeric_limits<uint64_t>::max());
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_118, SleepForMicrosecondsZero_118) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);
  wrapper_->SleepForMicroseconds(0);
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_118, GetChildrenEmptyDir_118) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren("", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test Schedule with nullptr arg
TEST_F(EnvWrapperTest_118, ScheduleWithNullArg_118) {
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, nullptr))
      .Times(1);
  wrapper_->Schedule(DummyScheduleFunc, nullptr);
}

// Test NewWritableFile error
TEST_F(EnvWrapperTest_118, NewWritableFileError_118) {
  WritableFile* file = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("readonly.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  Status s = wrapper_->NewWritableFile("readonly.txt", &file);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewSequentialFile error
TEST_F(EnvWrapperTest_118, NewSequentialFileError_118) {
  SequentialFile* file = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("noexist.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));
  Status s = wrapper_->NewSequentialFile("noexist.txt", &file);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewRandomAccessFile error
TEST_F(EnvWrapperTest_118, NewRandomAccessFileError_118) {
  RandomAccessFile* file = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("noexist.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));
  Status s = wrapper_->NewRandomAccessFile("noexist.txt", &file);
  EXPECT_TRUE(s.IsNotFound());
}

// Test CreateDir error
TEST_F(EnvWrapperTest_118, CreateDirError_118) {
  EXPECT_CALL(*mock_env_, CreateDir("/no_permission"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  Status s = wrapper_->CreateDir("/no_permission");
  EXPECT_TRUE(s.IsIOError());
}

// Test RemoveDir error
TEST_F(EnvWrapperTest_118, RemoveDirError_118) {
  EXPECT_CALL(*mock_env_, RemoveDir("/nonexistent"))
      .WillOnce(::testing::Return(Status::IOError("dir not found")));
  Status s = wrapper_->RemoveDir("/nonexistent");
  EXPECT_TRUE(s.IsIOError());
}

// Test GetFileSize error
TEST_F(EnvWrapperTest_118, GetFileSizeError_118) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("noexist.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("not found")));
  Status s = wrapper_->GetFileSize("noexist.txt", &size);
  EXPECT_TRUE(s.IsNotFound());
}

// Test multiple calls are properly delegated
TEST_F(EnvWrapperTest_118, MultipleDelegationCalls_118) {
  EXPECT_CALL(*mock_env_, FileExists("file1.txt"))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, FileExists("file2.txt"))
      .WillOnce(::testing::Return(false));
  EXPECT_CALL(*mock_env_, FileExists("file3.txt"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("file1.txt"));
  EXPECT_FALSE(wrapper_->FileExists("file2.txt"));
  EXPECT_TRUE(wrapper_->FileExists("file3.txt"));
}

// Test using Default Env with EnvWrapper
TEST_F(EnvWrapperTest_118, WrapDefaultEnv_118) {
  Env* default_env = Env::Default();
  EnvWrapper default_wrapper(default_env);
  EXPECT_EQ(default_wrapper.target(), default_env);

  std::string test_dir;
  Status s = default_wrapper.GetTestDirectory(&test_dir);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(test_dir.empty());
}

// Test NowMicros via Default env wrapper gives reasonable value
TEST_F(EnvWrapperTest_118, WrapDefaultEnvNowMicros_118) {
  Env* default_env = Env::Default();
  EnvWrapper default_wrapper(default_env);
  uint64_t micros = default_wrapper.NowMicros();
  EXPECT_GT(micros, 0u);
}

}  // namespace leveldb
