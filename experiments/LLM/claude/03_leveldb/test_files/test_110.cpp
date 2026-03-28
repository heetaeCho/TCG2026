#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

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

class EnvWrapperTest_110 : public ::testing::Test {
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

// Test that target() returns the wrapped environment
TEST_F(EnvWrapperTest_110, TargetReturnsWrappedEnv_110) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_110, FileExistsDelegatesToTarget_110) {
  EXPECT_CALL(*mock_env_, FileExists("/tmp/testfile"))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists("/tmp/testfile"));
}

TEST_F(EnvWrapperTest_110, FileExistsReturnsFalse_110) {
  EXPECT_CALL(*mock_env_, FileExists("/nonexistent"))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists("/nonexistent"));
}

// Test FileExists with empty string
TEST_F(EnvWrapperTest_110, FileExistsEmptyString_110) {
  EXPECT_CALL(*mock_env_, FileExists(""))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists(""));
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_110, NewSequentialFileDelegatesToTarget_110) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("/tmp/seq", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewSequentialFile("/tmp/seq", &result);
  EXPECT_TRUE(s.ok());
}

TEST_F(EnvWrapperTest_110, NewSequentialFileError_110) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("/nonexistent", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));
  Status s = wrapper_->NewSequentialFile("/nonexistent", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_110, NewRandomAccessFileDelegatesToTarget_110) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("/tmp/rand", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewRandomAccessFile("/tmp/rand", &result);
  EXPECT_TRUE(s.ok());
}

TEST_F(EnvWrapperTest_110, NewRandomAccessFileError_110) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("/missing", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("not found")));
  Status s = wrapper_->NewRandomAccessFile("/missing", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_110, NewWritableFileDelegatesToTarget_110) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("/tmp/writable", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewWritableFile("/tmp/writable", &result);
  EXPECT_TRUE(s.ok());
}

TEST_F(EnvWrapperTest_110, NewWritableFileError_110) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("/readonly/file", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  Status s = wrapper_->NewWritableFile("/readonly/file", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_110, NewAppendableFileDelegatesToTarget_110) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("/tmp/append", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewAppendableFile("/tmp/append", &result);
  EXPECT_TRUE(s.ok());
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_110, GetChildrenDelegatesToTarget_110) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/tmp", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(
              std::vector<std::string>{"a.txt", "b.txt"}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren("/tmp", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(children.size(), 2u);
  EXPECT_EQ(children[0], "a.txt");
  EXPECT_EQ(children[1], "b.txt");
}

TEST_F(EnvWrapperTest_110, GetChildrenEmpty_110) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/empty", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren("/empty", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_110, RemoveFileDelegatesToTarget_110) {
  EXPECT_CALL(*mock_env_, RemoveFile("/tmp/file"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveFile("/tmp/file");
  EXPECT_TRUE(s.ok());
}

TEST_F(EnvWrapperTest_110, RemoveFileError_110) {
  EXPECT_CALL(*mock_env_, RemoveFile("/nonexistent"))
      .WillOnce(::testing::Return(Status::NotFound("not found")));
  Status s = wrapper_->RemoveFile("/nonexistent");
  EXPECT_TRUE(s.IsNotFound());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_110, CreateDirDelegatesToTarget_110) {
  EXPECT_CALL(*mock_env_, CreateDir("/tmp/newdir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->CreateDir("/tmp/newdir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_110, RemoveDirDelegatesToTarget_110) {
  EXPECT_CALL(*mock_env_, RemoveDir("/tmp/dir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir("/tmp/dir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_110, GetFileSizeDelegatesToTarget_110) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("/tmp/file", ::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(1024u),
                                 ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("/tmp/file", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 1024u);
}

TEST_F(EnvWrapperTest_110, GetFileSizeZero_110) {
  uint64_t size = 999;
  EXPECT_CALL(*mock_env_, GetFileSize("/tmp/empty", ::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(0u),
                                 ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("/tmp/empty", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0u);
}

TEST_F(EnvWrapperTest_110, GetFileSizeLargeFile_110) {
  uint64_t size = 0;
  uint64_t large_size = static_cast<uint64_t>(1) << 40;  // 1TB
  EXPECT_CALL(*mock_env_, GetFileSize("/tmp/large", ::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(large_size),
                                 ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("/tmp/large", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, large_size);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_110, RenameFileDelegatesToTarget_110) {
  EXPECT_CALL(*mock_env_, RenameFile("/tmp/old", "/tmp/new"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile("/tmp/old", "/tmp/new");
  EXPECT_TRUE(s.ok());
}

TEST_F(EnvWrapperTest_110, RenameFileError_110) {
  EXPECT_CALL(*mock_env_, RenameFile("/missing", "/tmp/new"))
      .WillOnce(::testing::Return(Status::NotFound("source not found")));
  Status s = wrapper_->RenameFile("/missing", "/tmp/new");
  EXPECT_TRUE(s.IsNotFound());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_110, LockFileDelegatesToTarget_110) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("/tmp/lockfile", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->LockFile("/tmp/lockfile", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_110, UnlockFileDelegatesToTarget_110) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
TEST_F(EnvWrapperTest_110, ScheduleDelegatesToTarget_110) {
  void (*fn)(void*) = [](void*) {};
  void* arg = nullptr;
  EXPECT_CALL(*mock_env_, Schedule(fn, arg)).Times(1);
  wrapper_->Schedule(fn, arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_110, StartThreadDelegatesToTarget_110) {
  void (*fn)(void*) = [](void*) {};
  void* arg = nullptr;
  EXPECT_CALL(*mock_env_, StartThread(fn, arg)).Times(1);
  wrapper_->StartThread(fn, arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_110, GetTestDirectoryDelegatesToTarget_110) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"),
                                 ::testing::Return(Status::OK())));
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_110, NewLoggerDelegatesToTarget_110) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("/tmp/log", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewLogger("/tmp/log", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_110, NowMicrosDelegatesToTarget_110) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890u));
  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890u);
}

TEST_F(EnvWrapperTest_110, NowMicrosZero_110) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0u));
  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 0u);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_110, SleepForMicrosecondsDelegatesToTarget_110) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000)).Times(1);
  wrapper_->SleepForMicroseconds(1000);
}

TEST_F(EnvWrapperTest_110, SleepForMicrosecondsZero_110) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0)).Times(1);
  wrapper_->SleepForMicroseconds(0);
}

// Test that multiple calls are properly delegated
TEST_F(EnvWrapperTest_110, MultipleDelegationCalls_110) {
  EXPECT_CALL(*mock_env_, FileExists("/a"))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, FileExists("/b"))
      .WillOnce(::testing::Return(false));
  EXPECT_CALL(*mock_env_, FileExists("/c"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("/a"));
  EXPECT_FALSE(wrapper_->FileExists("/b"));
  EXPECT_TRUE(wrapper_->FileExists("/c"));
}

// Test Schedule with non-null argument
TEST_F(EnvWrapperTest_110, ScheduleWithArg_110) {
  int value = 42;
  void (*fn)(void*) = [](void* arg) { *static_cast<int*>(arg) += 1; };
  EXPECT_CALL(*mock_env_, Schedule(fn, &value)).Times(1);
  wrapper_->Schedule(fn, &value);
}

// Test that wrapper correctly passes exact string arguments
TEST_F(EnvWrapperTest_110, ExactStringArgumentPassing_110) {
  std::string long_path(1000, 'a');
  EXPECT_CALL(*mock_env_, FileExists(long_path))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists(long_path));
}

// Test with special characters in filenames
TEST_F(EnvWrapperTest_110, SpecialCharactersInFilename_110) {
  std::string special = "/tmp/file with spaces & (parens)!";
  EXPECT_CALL(*mock_env_, FileExists(special))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists(special));
}

}  // namespace leveldb
