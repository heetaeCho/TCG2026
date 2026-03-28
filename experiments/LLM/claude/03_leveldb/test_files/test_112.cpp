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

class EnvWrapperTest_112 : public ::testing::Test {
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

// Test that target() returns the underlying Env pointer
TEST_F(EnvWrapperTest_112, TargetReturnsUnderlyingEnv_112) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_112, RemoveFileDelegatesToTarget_112) {
  EXPECT_CALL(*mock_env_, RemoveFile("testfile.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveFile("testfile.txt");
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile propagates error from target
TEST_F(EnvWrapperTest_112, RemoveFileReturnsErrorFromTarget_112) {
  EXPECT_CALL(*mock_env_, RemoveFile("nonexistent.txt"))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));
  Status s = wrapper_->RemoveFile("nonexistent.txt");
  EXPECT_TRUE(s.IsNotFound());
}

// Test RemoveFile with empty string
TEST_F(EnvWrapperTest_112, RemoveFileEmptyString_112) {
  EXPECT_CALL(*mock_env_, RemoveFile(""))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty filename")));
  Status s = wrapper_->RemoveFile("");
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_112, NewSequentialFileDelegatesToTarget_112) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("seq.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewSequentialFile("seq.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_112, NewRandomAccessFileDelegatesToTarget_112) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("rand.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewRandomAccessFile("rand.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_112, NewWritableFileDelegatesToTarget_112) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("write.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewWritableFile("write.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_112, NewAppendableFileDelegatesToTarget_112) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("append.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewAppendableFile("append.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target and returns true
TEST_F(EnvWrapperTest_112, FileExistsReturnsTrueFromTarget_112) {
  EXPECT_CALL(*mock_env_, FileExists("existing.txt"))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists("existing.txt"));
}

// Test FileExists delegates to target and returns false
TEST_F(EnvWrapperTest_112, FileExistsReturnsFalseFromTarget_112) {
  EXPECT_CALL(*mock_env_, FileExists("missing.txt"))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists("missing.txt"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_112, GetChildrenDelegatesToTarget_112) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/dir", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(
              std::vector<std::string>{"a.txt", "b.txt"}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren("/dir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(children.size(), 2u);
  EXPECT_EQ(children[0], "a.txt");
  EXPECT_EQ(children[1], "b.txt");
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_112, GetChildrenEmptyDirectory_112) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/empty", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren("/empty", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_112, CreateDirDelegatesToTarget_112) {
  EXPECT_CALL(*mock_env_, CreateDir("/newdir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->CreateDir("/newdir");
  EXPECT_TRUE(s.ok());
}

// Test CreateDir propagates error
TEST_F(EnvWrapperTest_112, CreateDirReturnsErrorFromTarget_112) {
  EXPECT_CALL(*mock_env_, CreateDir("/forbidden"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  Status s = wrapper_->CreateDir("/forbidden");
  EXPECT_TRUE(s.IsIOError());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_112, RemoveDirDelegatesToTarget_112) {
  EXPECT_CALL(*mock_env_, RemoveDir("/olddir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir("/olddir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_112, GetFileSizeDelegatesToTarget_112) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("data.bin", ::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(1024u),
                                  ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("data.bin", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 1024u);
}

// Test GetFileSize with zero-size file
TEST_F(EnvWrapperTest_112, GetFileSizeZero_112) {
  uint64_t size = 999;
  EXPECT_CALL(*mock_env_, GetFileSize("empty.bin", ::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(0u),
                                  ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("empty.bin", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_112, RenameFileDelegatesToTarget_112) {
  EXPECT_CALL(*mock_env_, RenameFile("old.txt", "new.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile("old.txt", "new.txt");
  EXPECT_TRUE(s.ok());
}

// Test RenameFile propagates error
TEST_F(EnvWrapperTest_112, RenameFileReturnsErrorFromTarget_112) {
  EXPECT_CALL(*mock_env_, RenameFile("old.txt", "new.txt"))
      .WillOnce(::testing::Return(Status::IOError("disk full")));
  Status s = wrapper_->RenameFile("old.txt", "new.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_112, LockFileDelegatesToTarget_112) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lock.lck", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->LockFile("lock.lck", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_112, UnlockFileDelegatesToTarget_112) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
TEST_F(EnvWrapperTest_112, ScheduleDelegatesToTarget_112) {
  void (*func)(void*) = [](void*) {};
  int arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(func, &arg)).Times(1);
  wrapper_->Schedule(func, &arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_112, StartThreadDelegatesToTarget_112) {
  void (*func)(void*) = [](void*) {};
  int arg = 99;
  EXPECT_CALL(*mock_env_, StartThread(func, &arg)).Times(1);
  wrapper_->StartThread(func, &arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_112, GetTestDirectoryDelegatesToTarget_112) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"),
                                  ::testing::Return(Status::OK())));
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_112, NewLoggerDelegatesToTarget_112) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewLogger("log.txt", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_112, NowMicrosDelegatesToTarget_112) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890ULL));
  uint64_t time = wrapper_->NowMicros();
  EXPECT_EQ(time, 1234567890ULL);
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_112, NowMicrosReturnsZero_112) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0ULL));
  uint64_t time = wrapper_->NowMicros();
  EXPECT_EQ(time, 0ULL);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_112, SleepForMicrosecondsDelegatesToTarget_112) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(500)).Times(1);
  wrapper_->SleepForMicroseconds(500);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_112, SleepForMicrosecondsZero_112) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0)).Times(1);
  wrapper_->SleepForMicroseconds(0);
}

// Test RemoveFile with path containing special characters
TEST_F(EnvWrapperTest_112, RemoveFileSpecialCharacters_112) {
  std::string specialPath = "/path/to/file with spaces & (special).txt";
  EXPECT_CALL(*mock_env_, RemoveFile(specialPath))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveFile(specialPath);
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile with very long path
TEST_F(EnvWrapperTest_112, RemoveFileLongPath_112) {
  std::string longPath(4096, 'a');
  EXPECT_CALL(*mock_env_, RemoveFile(longPath))
      .WillOnce(::testing::Return(Status::IOError("path too long")));
  Status s = wrapper_->RemoveFile(longPath);
  EXPECT_TRUE(s.IsIOError());
}

// Test multiple sequential calls delegate correctly
TEST_F(EnvWrapperTest_112, MultipleCallsDelegate_112) {
  EXPECT_CALL(*mock_env_, RemoveFile("file1.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock_env_, RemoveFile("file2.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock_env_, RemoveFile("file3.txt"))
      .WillOnce(::testing::Return(Status::NotFound("not found")));

  EXPECT_TRUE(wrapper_->RemoveFile("file1.txt").ok());
  EXPECT_TRUE(wrapper_->RemoveFile("file2.txt").ok());
  EXPECT_TRUE(wrapper_->RemoveFile("file3.txt").IsNotFound());
}

// Test Schedule with nullptr arg
TEST_F(EnvWrapperTest_112, ScheduleWithNullArg_112) {
  void (*func)(void*) = [](void*) {};
  EXPECT_CALL(*mock_env_, Schedule(func, nullptr)).Times(1);
  wrapper_->Schedule(func, nullptr);
}

// Test GetFileSize propagates error
TEST_F(EnvWrapperTest_112, GetFileSizeError_112) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("missing.bin", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("not found")));
  Status s = wrapper_->GetFileSize("missing.bin", &size);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewSequentialFile propagates error
TEST_F(EnvWrapperTest_112, NewSequentialFileError_112) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("missing.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("no such file")));
  Status s = wrapper_->NewSequentialFile("missing.txt", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewRandomAccessFile propagates error
TEST_F(EnvWrapperTest_112, NewRandomAccessFileError_112) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("missing.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("no such file")));
  Status s = wrapper_->NewRandomAccessFile("missing.txt", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewWritableFile propagates error
TEST_F(EnvWrapperTest_112, NewWritableFileError_112) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("/readonly/file.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("read only fs")));
  Status s = wrapper_->NewWritableFile("/readonly/file.txt", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewAppendableFile propagates error
TEST_F(EnvWrapperTest_112, NewAppendableFileError_112) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("/readonly/file.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("read only fs")));
  Status s = wrapper_->NewAppendableFile("/readonly/file.txt", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test that NowMicros can return large values
TEST_F(EnvWrapperTest_112, NowMicrosLargeValue_112) {
  uint64_t largeTime = UINT64_MAX;
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(largeTime));
  uint64_t time = wrapper_->NowMicros();
  EXPECT_EQ(time, largeTime);
}

// Test LockFile error
TEST_F(EnvWrapperTest_112, LockFileError_112) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("locked.lck", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("already locked")));
  Status s = wrapper_->LockFile("locked.lck", &lock);
  EXPECT_TRUE(s.IsIOError());
}

// Test RemoveDir error
TEST_F(EnvWrapperTest_112, RemoveDirError_112) {
  EXPECT_CALL(*mock_env_, RemoveDir("/nonempty"))
      .WillOnce(::testing::Return(Status::IOError("directory not empty")));
  Status s = wrapper_->RemoveDir("/nonempty");
  EXPECT_TRUE(s.IsIOError());
}

}  // namespace leveldb
