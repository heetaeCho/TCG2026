#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <cstdint>

namespace leveldb {

// Mock Env to act as the target_ for EnvWrapper
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

class EnvWrapperTest_109 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_env_ = new MockEnv();
    wrapper_ = new EnvWrapper(mock_env_);
  }

  void TearDown() override {
    delete wrapper_;
    // Note: mock_env_ is owned externally, not by EnvWrapper
    delete mock_env_;
  }

  MockEnv* mock_env_;
  EnvWrapper* wrapper_;
};

// Test that target() returns the correct Env pointer
TEST_F(EnvWrapperTest_109, TargetReturnsCorrectEnv_109) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_109, NewAppendableFileDelegatesToTarget_109) {
  WritableFile* result = nullptr;
  std::string filename = "/tmp/test_appendable";
  
  EXPECT_CALL(*mock_env_, NewAppendableFile(filename, &result))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewAppendableFile(filename, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile propagates error status from target
TEST_F(EnvWrapperTest_109, NewAppendableFilePropagatessError_109) {
  WritableFile* result = nullptr;
  std::string filename = "/nonexistent/path/file";
  
  EXPECT_CALL(*mock_env_, NewAppendableFile(filename, &result))
      .WillOnce(::testing::Return(Status::IOError("file not found")));
  
  Status s = wrapper_->NewAppendableFile(filename, &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_109, NewWritableFileDelegatesToTarget_109) {
  WritableFile* result = nullptr;
  std::string filename = "/tmp/test_writable";
  
  EXPECT_CALL(*mock_env_, NewWritableFile(filename, &result))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewWritableFile(filename, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_109, NewSequentialFileDelegatesToTarget_109) {
  SequentialFile* result = nullptr;
  std::string filename = "/tmp/test_sequential";
  
  EXPECT_CALL(*mock_env_, NewSequentialFile(filename, &result))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewSequentialFile(filename, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_109, NewRandomAccessFileDelegatesToTarget_109) {
  RandomAccessFile* result = nullptr;
  std::string filename = "/tmp/test_random";
  
  EXPECT_CALL(*mock_env_, NewRandomAccessFile(filename, &result))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewRandomAccessFile(filename, &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_109, FileExistsDelegatesToTarget_109) {
  std::string filename = "/tmp/existing_file";
  
  EXPECT_CALL(*mock_env_, FileExists(filename))
      .WillOnce(::testing::Return(true));
  
  EXPECT_TRUE(wrapper_->FileExists(filename));
}

// Test FileExists returns false when target says false
TEST_F(EnvWrapperTest_109, FileExistsReturnsFalse_109) {
  std::string filename = "/tmp/nonexistent_file";
  
  EXPECT_CALL(*mock_env_, FileExists(filename))
      .WillOnce(::testing::Return(false));
  
  EXPECT_FALSE(wrapper_->FileExists(filename));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_109, GetChildrenDelegatesToTarget_109) {
  std::string dir = "/tmp/testdir";
  std::vector<std::string> children;
  
  EXPECT_CALL(*mock_env_, GetChildren(dir, &children))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->GetChildren(dir, &children);
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_109, RemoveFileDelegatesToTarget_109) {
  std::string filename = "/tmp/file_to_remove";
  
  EXPECT_CALL(*mock_env_, RemoveFile(filename))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->RemoveFile(filename);
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile propagates error
TEST_F(EnvWrapperTest_109, RemoveFilePropagatesError_109) {
  std::string filename = "/tmp/nonexistent_file";
  
  EXPECT_CALL(*mock_env_, RemoveFile(filename))
      .WillOnce(::testing::Return(Status::IOError("file not found")));
  
  Status s = wrapper_->RemoveFile(filename);
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_109, CreateDirDelegatesToTarget_109) {
  std::string dirname = "/tmp/newdir";
  
  EXPECT_CALL(*mock_env_, CreateDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->CreateDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_109, RemoveDirDelegatesToTarget_109) {
  std::string dirname = "/tmp/dirtoremove";
  
  EXPECT_CALL(*mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->RemoveDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_109, GetFileSizeDelegatesToTarget_109) {
  std::string filename = "/tmp/somefile";
  uint64_t size = 0;
  
  EXPECT_CALL(*mock_env_, GetFileSize(filename, &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(1024),
                                  ::testing::Return(Status::OK())));
  
  Status s = wrapper_->GetFileSize(filename, &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 1024u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_109, RenameFileDelegatesToTarget_109) {
  std::string src = "/tmp/src";
  std::string tgt = "/tmp/tgt";
  
  EXPECT_CALL(*mock_env_, RenameFile(src, tgt))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->RenameFile(src, tgt);
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_109, LockFileDelegatesToTarget_109) {
  std::string filename = "/tmp/lockfile";
  FileLock* lock = nullptr;
  
  EXPECT_CALL(*mock_env_, LockFile(filename, &lock))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->LockFile(filename, &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_109, UnlockFileDelegatesToTarget_109) {
  FileLock* lock = nullptr;
  
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyScheduleFunc(void* arg) {}

TEST_F(EnvWrapperTest_109, ScheduleDelegatesToTarget_109) {
  int arg = 42;
  
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, &arg))
      .Times(1);
  
  wrapper_->Schedule(DummyScheduleFunc, &arg);
}

// Test StartThread delegates to target
static void DummyThreadFunc(void* arg) {}

TEST_F(EnvWrapperTest_109, StartThreadDelegatesToTarget_109) {
  int arg = 99;
  
  EXPECT_CALL(*mock_env_, StartThread(DummyThreadFunc, &arg))
      .Times(1);
  
  wrapper_->StartThread(DummyThreadFunc, &arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_109, GetTestDirectoryDelegatesToTarget_109) {
  std::string path;
  
  EXPECT_CALL(*mock_env_, GetTestDirectory(&path))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"),
                                  ::testing::Return(Status::OK())));
  
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_109, NewLoggerDelegatesToTarget_109) {
  std::string fname = "/tmp/logfile";
  Logger* logger = nullptr;
  
  EXPECT_CALL(*mock_env_, NewLogger(fname, &logger))
      .WillOnce(::testing::Return(Status::OK()));
  
  Status s = wrapper_->NewLogger(fname, &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_109, NowMicrosDelegatesToTarget_109) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(123456789ULL));
  
  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 123456789ULL);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_109, SleepForMicrosecondsDelegatesToTarget_109) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000))
      .Times(1);
  
  wrapper_->SleepForMicroseconds(1000);
}

// Test NewAppendableFile with empty filename
TEST_F(EnvWrapperTest_109, NewAppendableFileEmptyFilename_109) {
  WritableFile* result = nullptr;
  std::string filename = "";
  
  EXPECT_CALL(*mock_env_, NewAppendableFile(filename, &result))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty filename")));
  
  Status s = wrapper_->NewAppendableFile(filename, &result);
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test that multiple calls delegate correctly
TEST_F(EnvWrapperTest_109, MultipleDelegationCalls_109) {
  EXPECT_CALL(*mock_env_, FileExists("/tmp/a"))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, FileExists("/tmp/b"))
      .WillOnce(::testing::Return(false));
  
  EXPECT_TRUE(wrapper_->FileExists("/tmp/a"));
  EXPECT_FALSE(wrapper_->FileExists("/tmp/b"));
}

// Test GetFileSize with error
TEST_F(EnvWrapperTest_109, GetFileSizeError_109) {
  std::string filename = "/nonexistent";
  uint64_t size = 0;
  
  EXPECT_CALL(*mock_env_, GetFileSize(filename, &size))
      .WillOnce(::testing::Return(Status::IOError("no such file")));
  
  Status s = wrapper_->GetFileSize(filename, &size);
  EXPECT_TRUE(s.IsIOError());
}

// Test NowMicros returns zero (boundary)
TEST_F(EnvWrapperTest_109, NowMicrosZero_109) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0ULL));
  
  EXPECT_EQ(wrapper_->NowMicros(), 0ULL);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_109, SleepForZeroMicroseconds_109) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);
  
  wrapper_->SleepForMicroseconds(0);
}

// Test using the default Env (integration-style)
TEST(EnvDefaultTest_109, DefaultEnvNotNull_109) {
  Env* env = Env::Default();
  ASSERT_NE(env, nullptr);
}

TEST(EnvDefaultTest_109, DefaultEnvGetTestDirectory_109) {
  Env* env = Env::Default();
  std::string path;
  Status s = env->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(path.empty());
}

TEST(EnvDefaultTest_109, DefaultEnvNowMicrosReturnsNonZero_109) {
  Env* env = Env::Default();
  uint64_t micros = env->NowMicros();
  EXPECT_GT(micros, 0ULL);
}

// Test EnvWrapper with default env as target
TEST(EnvWrapperWithDefaultTest_109, WrapDefaultEnv_109) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);
  EXPECT_EQ(wrapper.target(), default_env);
  
  std::string path;
  Status s = wrapper.GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(path.empty());
}

// Test RenameFile propagates error
TEST_F(EnvWrapperTest_109, RenameFileError_109) {
  EXPECT_CALL(*mock_env_, RenameFile("/a", "/b"))
      .WillOnce(::testing::Return(Status::IOError("rename failed")));
  
  Status s = wrapper_->RenameFile("/a", "/b");
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir error
TEST_F(EnvWrapperTest_109, CreateDirError_109) {
  EXPECT_CALL(*mock_env_, CreateDir("/root/protected"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  
  Status s = wrapper_->CreateDir("/root/protected");
  EXPECT_TRUE(s.IsIOError());
}

// Test that Schedule with nullptr arg delegates correctly
TEST_F(EnvWrapperTest_109, ScheduleWithNullArg_109) {
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, nullptr))
      .Times(1);
  
  wrapper_->Schedule(DummyScheduleFunc, nullptr);
}

}  // namespace leveldb
