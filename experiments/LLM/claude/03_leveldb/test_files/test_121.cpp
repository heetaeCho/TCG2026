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

class EnvWrapperTest_121 : public ::testing::Test {
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
TEST_F(EnvWrapperTest_121, TargetReturnsWrappedEnv_121) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_121, GetTestDirectoryDelegatesToTarget_121) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"), 
                                  ::testing::Return(Status::OK())));
  
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test GetTestDirectory propagates error from target
TEST_F(EnvWrapperTest_121, GetTestDirectoryPropagatesError_121) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(::testing::_))
      .WillOnce(::testing::Return(Status::IOError("test error")));
  
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_121, NewSequentialFileDelegatesToTarget_121) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("testfile", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewSequentialFile("testfile", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile propagates error
TEST_F(EnvWrapperTest_121, NewSequentialFilePropagatesError_121) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("nonexistent", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));
  
  Status s = wrapper_->NewSequentialFile("nonexistent", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_121, NewRandomAccessFileDelegatesToTarget_121) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("testfile", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewRandomAccessFile("testfile", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_121, NewWritableFileDelegatesToTarget_121) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("testfile", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewWritableFile("testfile", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_121, NewAppendableFileDelegatesToTarget_121) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("testfile", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewAppendableFile("testfile", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target - true case
TEST_F(EnvWrapperTest_121, FileExistsDelegatesToTargetTrue_121) {
  EXPECT_CALL(*mock_env_, FileExists("existing_file"))
      .WillOnce(::testing::Return(true));
  
  EXPECT_TRUE(wrapper_->FileExists("existing_file"));
}

// Test FileExists delegates to target - false case
TEST_F(EnvWrapperTest_121, FileExistsDelegatesToTargetFalse_121) {
  EXPECT_CALL(*mock_env_, FileExists("nonexistent"))
      .WillOnce(::testing::Return(false));
  
  EXPECT_FALSE(wrapper_->FileExists("nonexistent"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_121, GetChildrenDelegatesToTarget_121) {
  std::vector<std::string> children;
  std::vector<std::string> expected_children = {"file1", "file2", "file3"};
  
  EXPECT_CALL(*mock_env_, GetChildren("/testdir", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(expected_children),
          ::testing::Return(Status::OK())));
  
  Status s = wrapper_->GetChildren("/testdir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(children.size(), 3u);
  EXPECT_EQ(children[0], "file1");
  EXPECT_EQ(children[1], "file2");
  EXPECT_EQ(children[2], "file3");
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_121, GetChildrenEmptyDirectory_121) {
  std::vector<std::string> children;
  
  EXPECT_CALL(*mock_env_, GetChildren("/emptydir", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));
  
  Status s = wrapper_->GetChildren("/emptydir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_121, RemoveFileDelegatesToTarget_121) {
  EXPECT_CALL(*mock_env_, RemoveFile("testfile"))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->RemoveFile("testfile");
  EXPECT_TRUE(s.ok());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_121, CreateDirDelegatesToTarget_121) {
  EXPECT_CALL(*mock_env_, CreateDir("/newdir"))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->CreateDir("/newdir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_121, RemoveDirDelegatesToTarget_121) {
  EXPECT_CALL(*mock_env_, RemoveDir("/olddir"))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->RemoveDir("/olddir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_121, GetFileSizeDelegatesToTarget_121) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("testfile", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(12345u),
          ::testing::Return(Status::OK())));
  
  Status s = wrapper_->GetFileSize("testfile", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 12345u);
}

// Test GetFileSize with zero size
TEST_F(EnvWrapperTest_121, GetFileSizeZero_121) {
  uint64_t size = 999;
  EXPECT_CALL(*mock_env_, GetFileSize("emptyfile", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(0u),
          ::testing::Return(Status::OK())));
  
  Status s = wrapper_->GetFileSize("emptyfile", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_121, RenameFileDelegatesToTarget_121) {
  EXPECT_CALL(*mock_env_, RenameFile("src", "dst"))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->RenameFile("src", "dst");
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_121, LockFileDelegatesToTarget_121) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lockfile", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->LockFile("lockfile", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_121, UnlockFileDelegatesToTarget_121) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyFunction(void* arg) {}

TEST_F(EnvWrapperTest_121, ScheduleDelegatesToTarget_121) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyFunction, &dummy_arg))
      .Times(1);
  
  wrapper_->Schedule(DummyFunction, &dummy_arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_121, StartThreadDelegatesToTarget_121) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, StartThread(DummyFunction, &dummy_arg))
      .Times(1);
  
  wrapper_->StartThread(DummyFunction, &dummy_arg);
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_121, NewLoggerDelegatesToTarget_121) {
  Logger* result = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("logfile", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewLogger("logfile", &result);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_121, NowMicrosDelegatesToTarget_121) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890u));
  
  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890u);
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_121, NowMicrosReturnsZero_121) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0u));
  
  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 0u);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_121, SleepForMicrosecondsDelegatesToTarget_121) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000))
      .Times(1);
  
  wrapper_->SleepForMicroseconds(1000);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_121, SleepForMicrosecondsZero_121) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);
  
  wrapper_->SleepForMicroseconds(0);
}

// Test that empty filename is passed correctly
TEST_F(EnvWrapperTest_121, EmptyFilenameDelegation_121) {
  EXPECT_CALL(*mock_env_, FileExists(""))
      .WillOnce(::testing::Return(false));
  
  EXPECT_FALSE(wrapper_->FileExists(""));
}

// Test RenameFile error propagation
TEST_F(EnvWrapperTest_121, RenameFileErrorPropagation_121) {
  EXPECT_CALL(*mock_env_, RenameFile("src", "dst"))
      .WillOnce(::testing::Return(Status::IOError("rename failed")));
  
  Status s = wrapper_->RenameFile("src", "dst");
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir error propagation
TEST_F(EnvWrapperTest_121, CreateDirErrorPropagation_121) {
  EXPECT_CALL(*mock_env_, CreateDir("/existing"))
      .WillOnce(::testing::Return(Status::IOError("already exists")));
  
  Status s = wrapper_->CreateDir("/existing");
  EXPECT_TRUE(s.IsIOError());
}

// Test RemoveDir error propagation
TEST_F(EnvWrapperTest_121, RemoveDirErrorPropagation_121) {
  EXPECT_CALL(*mock_env_, RemoveDir("/nonexistent"))
      .WillOnce(::testing::Return(Status::IOError("not found")));
  
  Status s = wrapper_->RemoveDir("/nonexistent");
  EXPECT_TRUE(s.IsIOError());
}

// Test multiple sequential calls to same method
TEST_F(EnvWrapperTest_121, MultipleCallsToSameMethod_121) {
  EXPECT_CALL(*mock_env_, FileExists(::testing::_))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true));
  
  EXPECT_TRUE(wrapper_->FileExists("file1"));
  EXPECT_FALSE(wrapper_->FileExists("file2"));
  EXPECT_TRUE(wrapper_->FileExists("file3"));
}

// Test GetFileSize with large file size
TEST_F(EnvWrapperTest_121, GetFileSizeLargeFile_121) {
  uint64_t size = 0;
  uint64_t expected = UINT64_MAX;
  EXPECT_CALL(*mock_env_, GetFileSize("largefile", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(expected),
          ::testing::Return(Status::OK())));
  
  Status s = wrapper_->GetFileSize("largefile", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, expected);
}

// Test Schedule with nullptr argument
TEST_F(EnvWrapperTest_121, ScheduleWithNullArg_121) {
  EXPECT_CALL(*mock_env_, Schedule(DummyFunction, nullptr))
      .Times(1);
  
  wrapper_->Schedule(DummyFunction, nullptr);
}

// Test NewWritableFile error propagation
TEST_F(EnvWrapperTest_121, NewWritableFileErrorPropagation_121) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("/readonly/file", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  
  Status s = wrapper_->NewWritableFile("/readonly/file", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test using Default Env with EnvWrapper
TEST_F(EnvWrapperTest_121, DefaultEnvIntegration_121) {
  Env* default_env = Env::Default();
  ASSERT_NE(default_env, nullptr);
  
  EnvWrapper default_wrapper(default_env);
  EXPECT_EQ(default_wrapper.target(), default_env);
  
  std::string test_dir;
  Status s = default_wrapper.GetTestDirectory(&test_dir);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(test_dir.empty());
}

// Test NowMicros returns large value
TEST_F(EnvWrapperTest_121, NowMicrosLargeValue_121) {
  uint64_t large_val = 1700000000000000ULL;  // representative microsecond timestamp
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(large_val));
  
  EXPECT_EQ(wrapper_->NowMicros(), large_val);
}

// Test LockFile error propagation
TEST_F(EnvWrapperTest_121, LockFileErrorPropagation_121) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("already_locked", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("already locked")));
  
  Status s = wrapper_->LockFile("already_locked", &lock);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewLogger error propagation
TEST_F(EnvWrapperTest_121, NewLoggerErrorPropagation_121) {
  Logger* result = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("/invalid/path", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("cannot create logger")));
  
  Status s = wrapper_->NewLogger("/invalid/path", &result);
  EXPECT_TRUE(s.IsIOError());
}

}  // namespace leveldb
