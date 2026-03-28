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

class EnvWrapperTest_116 : public ::testing::Test {
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
TEST_F(EnvWrapperTest_116, TargetReturnsWrappedEnv_116) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test RenameFile delegates to target with correct arguments and returns OK
TEST_F(EnvWrapperTest_116, RenameFileDelegatesToTarget_116) {
  EXPECT_CALL(*mock_env_, RenameFile("source.txt", "target.txt"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile("source.txt", "target.txt");
  EXPECT_TRUE(s.ok());
}

// Test RenameFile propagates error status from target
TEST_F(EnvWrapperTest_116, RenameFileReturnsErrorFromTarget_116) {
  EXPECT_CALL(*mock_env_, RenameFile("nonexistent", "dest"))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));

  Status s = wrapper_->RenameFile("nonexistent", "dest");
  EXPECT_TRUE(s.IsNotFound());
}

// Test RenameFile with empty strings
TEST_F(EnvWrapperTest_116, RenameFileWithEmptyStrings_116) {
  EXPECT_CALL(*mock_env_, RenameFile("", ""))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty name")));

  Status s = wrapper_->RenameFile("", "");
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test RenameFile with same source and target
TEST_F(EnvWrapperTest_116, RenameFileSameSourceAndTarget_116) {
  EXPECT_CALL(*mock_env_, RenameFile("same.txt", "same.txt"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile("same.txt", "same.txt");
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_116, NewSequentialFileDelegates_116) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("test.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewSequentialFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_116, NewRandomAccessFileDelegates_116) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("test.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewRandomAccessFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_116, NewWritableFileDelegates_116) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("test.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewWritableFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_116, NewAppendableFileDelegates_116) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("test.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewAppendableFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target - returns true
TEST_F(EnvWrapperTest_116, FileExistsDelegatesTrue_116) {
  EXPECT_CALL(*mock_env_, FileExists("existing.txt"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("existing.txt"));
}

// Test FileExists delegates to target - returns false
TEST_F(EnvWrapperTest_116, FileExistsDelegatesFalse_116) {
  EXPECT_CALL(*mock_env_, FileExists("missing.txt"))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper_->FileExists("missing.txt"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_116, GetChildrenDelegates_116) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/testdir", &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{"a.txt", "b.txt"}),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren("/testdir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(children.size(), 2u);
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_116, RemoveFileDelegates_116) {
  EXPECT_CALL(*mock_env_, RemoveFile("delete_me.txt"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveFile("delete_me.txt");
  EXPECT_TRUE(s.ok());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_116, CreateDirDelegates_116) {
  EXPECT_CALL(*mock_env_, CreateDir("/newdir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->CreateDir("/newdir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_116, RemoveDirDelegates_116) {
  EXPECT_CALL(*mock_env_, RemoveDir("/olddir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveDir("/olddir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_116, GetFileSizeDelegates_116) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("file.txt", &size))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(12345u),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize("file.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 12345u);
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_116, LockFileDelegates_116) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lock.lk", &lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->LockFile("lock.lk", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_116, UnlockFileDelegates_116) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyFunction(void* arg) {}

TEST_F(EnvWrapperTest_116, ScheduleDelegates_116) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyFunction, &dummy_arg))
      .Times(1);

  wrapper_->Schedule(DummyFunction, &dummy_arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_116, StartThreadDelegates_116) {
  int dummy_arg = 99;
  EXPECT_CALL(*mock_env_, StartThread(DummyFunction, &dummy_arg))
      .Times(1);

  wrapper_->StartThread(DummyFunction, &dummy_arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_116, GetTestDirectoryDelegates_116) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(&path))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<0>(std::string("/tmp/test")),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_116, NewLoggerDelegates_116) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log.txt", &logger))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewLogger("log.txt", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_116, NowMicrosDelegates_116) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890u));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890u);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_116, SleepForMicrosecondsDelegates_116) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000))
      .Times(1);

  wrapper_->SleepForMicroseconds(1000);
}

// Test RenameFile with long file paths
TEST_F(EnvWrapperTest_116, RenameFileWithLongPaths_116) {
  std::string long_src(4096, 'a');
  std::string long_tgt(4096, 'b');
  EXPECT_CALL(*mock_env_, RenameFile(long_src, long_tgt))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile(long_src, long_tgt);
  EXPECT_TRUE(s.ok());
}

// Test RenameFile IOError propagation
TEST_F(EnvWrapperTest_116, RenameFileIOError_116) {
  EXPECT_CALL(*mock_env_, RenameFile("src", "dst"))
      .WillOnce(::testing::Return(Status::IOError("disk error")));

  Status s = wrapper_->RenameFile("src", "dst");
  EXPECT_TRUE(s.IsIOError());
}

// Test multiple calls to RenameFile
TEST_F(EnvWrapperTest_116, RenameFileMultipleCalls_116) {
  EXPECT_CALL(*mock_env_, RenameFile(::testing::_, ::testing::_))
      .Times(3)
      .WillRepeatedly(::testing::Return(Status::OK()));

  EXPECT_TRUE(wrapper_->RenameFile("a", "b").ok());
  EXPECT_TRUE(wrapper_->RenameFile("c", "d").ok());
  EXPECT_TRUE(wrapper_->RenameFile("e", "f").ok());
}

// Test RenameFile verifies exact argument forwarding
TEST_F(EnvWrapperTest_116, RenameFileExactArguments_116) {
  const std::string src = "/path/to/source";
  const std::string tgt = "/path/to/target";

  EXPECT_CALL(*mock_env_, RenameFile(src, tgt))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile(src, tgt);
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile with error
TEST_F(EnvWrapperTest_116, NewSequentialFileError_116) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("missing.txt", &result))
      .WillOnce(::testing::Return(Status::NotFound("no such file")));

  Status s = wrapper_->NewSequentialFile("missing.txt", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test GetFileSize with error
TEST_F(EnvWrapperTest_116, GetFileSizeError_116) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("nonexistent.txt", &size))
      .WillOnce(::testing::Return(Status::NotFound("not found")));

  Status s = wrapper_->GetFileSize("nonexistent.txt", &size);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_116, NowMicrosReturnsZero_116) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0u));

  EXPECT_EQ(wrapper_->NowMicros(), 0u);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_116, SleepForZeroMicroseconds_116) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);

  wrapper_->SleepForMicroseconds(0);
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_116, GetChildrenEmptyDir_116) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/emptydir", &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren("/emptydir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

}  // namespace leveldb
