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

class EnvWrapperTest_115 : public ::testing::Test {
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
TEST_F(EnvWrapperTest_115, TargetReturnsWrappedEnv_115) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_115, GetFileSizeDelegatesToTarget_115) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("test_file.txt", &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(42), ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize("test_file.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 42);
}

// Test GetFileSize with error from target
TEST_F(EnvWrapperTest_115, GetFileSizeReturnsErrorFromTarget_115) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("nonexistent.txt", &size))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));

  Status s = wrapper_->GetFileSize("nonexistent.txt", &size);
  EXPECT_TRUE(s.IsNotFound());
}

// Test GetFileSize with empty filename
TEST_F(EnvWrapperTest_115, GetFileSizeEmptyFilename_115) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("", &size))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty filename")));

  Status s = wrapper_->GetFileSize("", &size);
  EXPECT_FALSE(s.ok());
}

// Test GetFileSize with large file size
TEST_F(EnvWrapperTest_115, GetFileSizeLargeFile_115) {
  uint64_t size = 0;
  uint64_t large_size = UINT64_MAX;
  EXPECT_CALL(*mock_env_, GetFileSize("large_file.dat", &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(large_size), ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize("large_file.dat", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, large_size);
}

// Test GetFileSize with zero-byte file
TEST_F(EnvWrapperTest_115, GetFileSizeZeroByteFile_115) {
  uint64_t size = 999;
  EXPECT_CALL(*mock_env_, GetFileSize("empty_file.txt", &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(0), ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize("empty_file.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0);
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_115, NewSequentialFileDelegatesToTarget_115) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("seq_file.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewSequentialFile("seq_file.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_115, NewRandomAccessFileDelegatesToTarget_115) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("rand_file.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewRandomAccessFile("rand_file.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_115, NewWritableFileDelegatesToTarget_115) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("writable.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewWritableFile("writable.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_115, NewAppendableFileDelegatesToTarget_115) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("appendable.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewAppendableFile("appendable.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_115, FileExistsDelegatesToTarget_115) {
  EXPECT_CALL(*mock_env_, FileExists("exists.txt"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("exists.txt"));
}

// Test FileExists returns false
TEST_F(EnvWrapperTest_115, FileExistsReturnsFalse_115) {
  EXPECT_CALL(*mock_env_, FileExists("nonexistent.txt"))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper_->FileExists("nonexistent.txt"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_115, GetChildrenDelegatesToTarget_115) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/some/dir", &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{"a.txt", "b.txt"}),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren("/some/dir", &children);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(children.size(), 2);
  EXPECT_EQ(children[0], "a.txt");
  EXPECT_EQ(children[1], "b.txt");
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_115, GetChildrenEmptyDirectory_115) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/empty/dir", &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren("/empty/dir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_115, RemoveFileDelegatesToTarget_115) {
  EXPECT_CALL(*mock_env_, RemoveFile("to_remove.txt"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveFile("to_remove.txt");
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile with error
TEST_F(EnvWrapperTest_115, RemoveFileError_115) {
  EXPECT_CALL(*mock_env_, RemoveFile("locked.txt"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->RemoveFile("locked.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_115, CreateDirDelegatesToTarget_115) {
  EXPECT_CALL(*mock_env_, CreateDir("/new/dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->CreateDir("/new/dir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_115, RemoveDirDelegatesToTarget_115) {
  EXPECT_CALL(*mock_env_, RemoveDir("/old/dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveDir("/old/dir");
  EXPECT_TRUE(s.ok());
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_115, RenameFileDelegatesToTarget_115) {
  EXPECT_CALL(*mock_env_, RenameFile("old_name.txt", "new_name.txt"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile("old_name.txt", "new_name.txt");
  EXPECT_TRUE(s.ok());
}

// Test RenameFile with error
TEST_F(EnvWrapperTest_115, RenameFileError_115) {
  EXPECT_CALL(*mock_env_, RenameFile("nonexistent.txt", "target.txt"))
      .WillOnce(::testing::Return(Status::NotFound("source not found")));

  Status s = wrapper_->RenameFile("nonexistent.txt", "target.txt");
  EXPECT_TRUE(s.IsNotFound());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_115, LockFileDelegatesToTarget_115) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lock_file", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->LockFile("lock_file", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_115, UnlockFileDelegatesToTarget_115) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
TEST_F(EnvWrapperTest_115, ScheduleDelegatesToTarget_115) {
  auto func = [](void* arg) {};
  int arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(::testing::_, ::testing::_))
      .Times(1);

  wrapper_->Schedule(func, &arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_115, StartThreadDelegatesToTarget_115) {
  auto func = [](void* arg) {};
  int arg = 42;
  EXPECT_CALL(*mock_env_, StartThread(::testing::_, ::testing::_))
      .Times(1);

  wrapper_->StartThread(func, &arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_115, GetTestDirectoryDelegatesToTarget_115) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(&path))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<0>("/tmp/test"),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_115, NewLoggerDelegatesToTarget_115) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log_file.log", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewLogger("log_file.log", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_115, NowMicrosDelegatesToTarget_115) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890ULL));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890ULL);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_115, SleepForMicrosecondsDelegatesToTarget_115) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000))
      .Times(1);

  wrapper_->SleepForMicroseconds(1000);
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_115, NowMicrosReturnsZero_115) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0ULL));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 0ULL);
}

// Test NowMicros returns max value
TEST_F(EnvWrapperTest_115, NowMicrosReturnsMaxValue_115) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(UINT64_MAX));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, UINT64_MAX);
}

// Test multiple calls are all delegated
TEST_F(EnvWrapperTest_115, MultipleCallsDelegatedCorrectly_115) {
  EXPECT_CALL(*mock_env_, FileExists("file1.txt"))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, FileExists("file2.txt"))
      .WillOnce(::testing::Return(false));

  EXPECT_TRUE(wrapper_->FileExists("file1.txt"));
  EXPECT_FALSE(wrapper_->FileExists("file2.txt"));
}

// Test GetFileSize called with correct filename parameter
TEST_F(EnvWrapperTest_115, GetFileSizeCorrectFilenamePassedToTarget_115) {
  uint64_t size = 0;
  std::string expected_name = "/path/to/specific/file.dat";
  EXPECT_CALL(*mock_env_, GetFileSize(expected_name, ::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(100), ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize(expected_name, &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 100);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_115, SleepForMicrosecondsZero_115) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);

  wrapper_->SleepForMicroseconds(0);
}

}  // namespace leveldb
