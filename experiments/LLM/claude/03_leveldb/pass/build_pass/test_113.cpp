#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

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
  MOCK_METHOD(Status, DeleteFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, DeleteDir, (const std::string& dirname), (override));
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

class EnvWrapperTest_113 : public ::testing::Test {
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

// Test that target() returns the correct Env pointer
TEST_F(EnvWrapperTest_113, TargetReturnsCorrectEnv_113) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_113, CreateDirDelegatesToTarget_113) {
  EXPECT_CALL(*mock_env_, CreateDir("test_dir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->CreateDir("test_dir");
  EXPECT_TRUE(s.ok());
}

// Test CreateDir with error status
TEST_F(EnvWrapperTest_113, CreateDirReturnsError_113) {
  EXPECT_CALL(*mock_env_, CreateDir("bad_dir"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  Status s = wrapper_->CreateDir("bad_dir");
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir with empty string
TEST_F(EnvWrapperTest_113, CreateDirEmptyString_113) {
  EXPECT_CALL(*mock_env_, CreateDir(""))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty dir name")));
  Status s = wrapper_->CreateDir("");
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_113, NewSequentialFileDelegatesToTarget_113) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("file.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewSequentialFile("file.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_113, NewRandomAccessFileDelegatesToTarget_113) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("file.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewRandomAccessFile("file.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_113, NewWritableFileDelegatesToTarget_113) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("file.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewWritableFile("file.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_113, NewAppendableFileDelegatesToTarget_113) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("file.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewAppendableFile("file.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_113, FileExistsDelegatesToTarget_113) {
  EXPECT_CALL(*mock_env_, FileExists("file.txt"))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists("file.txt"));
}

// Test FileExists returns false
TEST_F(EnvWrapperTest_113, FileExistsReturnsFalse_113) {
  EXPECT_CALL(*mock_env_, FileExists("nonexistent.txt"))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists("nonexistent.txt"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_113, GetChildrenDelegatesToTarget_113) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("dir", &children))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->GetChildren("dir", &children);
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_113, RemoveFileDelegatesToTarget_113) {
  EXPECT_CALL(*mock_env_, RemoveFile("file.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveFile("file.txt");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_113, RemoveDirDelegatesToTarget_113) {
  EXPECT_CALL(*mock_env_, RemoveDir("dir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir("dir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_113, GetFileSizeDelegatesToTarget_113) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("file.txt", &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(1024),
                                  ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("file.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 1024);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_113, RenameFileDelegatesToTarget_113) {
  EXPECT_CALL(*mock_env_, RenameFile("old.txt", "new.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile("old.txt", "new.txt");
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_113, LockFileDelegatesToTarget_113) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lock.txt", &lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->LockFile("lock.txt", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_113, UnlockFileDelegatesToTarget_113) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyFunction(void* arg) {}

TEST_F(EnvWrapperTest_113, ScheduleDelegatesToTarget_113) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyFunction, &dummy_arg))
      .Times(1);
  wrapper_->Schedule(DummyFunction, &dummy_arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_113, StartThreadDelegatesToTarget_113) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, StartThread(DummyFunction, &dummy_arg))
      .Times(1);
  wrapper_->StartThread(DummyFunction, &dummy_arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_113, GetTestDirectoryDelegatesToTarget_113) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(&path))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"),
                                  ::testing::Return(Status::OK())));
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_113, NewLoggerDelegatesToTarget_113) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log.txt", &logger))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewLogger("log.txt", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_113, NowMicrosDelegatesToTarget_113) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(123456789ULL));
  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 123456789ULL);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_113, SleepForMicrosecondsDelegatesToTarget_113) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000))
      .Times(1);
  wrapper_->SleepForMicroseconds(1000);
}

// Test CreateDir with long path
TEST_F(EnvWrapperTest_113, CreateDirLongPath_113) {
  std::string long_path(4096, 'a');
  EXPECT_CALL(*mock_env_, CreateDir(long_path))
      .WillOnce(::testing::Return(Status::IOError("path too long")));
  Status s = wrapper_->CreateDir(long_path);
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir with special characters
TEST_F(EnvWrapperTest_113, CreateDirSpecialChars_113) {
  std::string special_dir = "/tmp/test dir/with spaces/and\ttabs";
  EXPECT_CALL(*mock_env_, CreateDir(special_dir))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->CreateDir(special_dir);
  EXPECT_TRUE(s.ok());
}

// Test multiple calls to CreateDir
TEST_F(EnvWrapperTest_113, CreateDirMultipleCalls_113) {
  EXPECT_CALL(*mock_env_, CreateDir("dir1"))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock_env_, CreateDir("dir2"))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock_env_, CreateDir("dir3"))
      .WillOnce(::testing::Return(Status::IOError("error")));

  EXPECT_TRUE(wrapper_->CreateDir("dir1").ok());
  EXPECT_TRUE(wrapper_->CreateDir("dir2").ok());
  EXPECT_TRUE(wrapper_->CreateDir("dir3").IsIOError());
}

// Test NewSequentialFile with error
TEST_F(EnvWrapperTest_113, NewSequentialFileError_113) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("nonexistent.txt", &result))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));
  Status s = wrapper_->NewSequentialFile("nonexistent.txt", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_113, NowMicrosReturnsZero_113) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0ULL));
  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 0ULL);
}

// Test NowMicros returns max value
TEST_F(EnvWrapperTest_113, NowMicrosReturnsMax_113) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(UINT64_MAX));
  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, UINT64_MAX);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_113, SleepForMicrosecondsZero_113) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);
  wrapper_->SleepForMicroseconds(0);
}

// Test Schedule with nullptr function and arg
TEST_F(EnvWrapperTest_113, ScheduleWithNullArgs_113) {
  EXPECT_CALL(*mock_env_, Schedule(nullptr, nullptr))
      .Times(1);
  wrapper_->Schedule(nullptr, nullptr);
}

// Test GetFileSize with error
TEST_F(EnvWrapperTest_113, GetFileSizeError_113) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("nonexistent.txt", &size))
      .WillOnce(::testing::Return(Status::NotFound("not found")));
  Status s = wrapper_->GetFileSize("nonexistent.txt", &size);
  EXPECT_TRUE(s.IsNotFound());
}

// Test RenameFile with error
TEST_F(EnvWrapperTest_113, RenameFileError_113) {
  EXPECT_CALL(*mock_env_, RenameFile("src.txt", "dst.txt"))
      .WillOnce(::testing::Return(Status::IOError("rename failed")));
  Status s = wrapper_->RenameFile("src.txt", "dst.txt");
  EXPECT_TRUE(s.IsIOError());
}

}  // namespace leveldb
