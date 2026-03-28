#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>

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

class EnvWrapperTest_120 : public ::testing::Test {
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
TEST_F(EnvWrapperTest_120, TargetReturnsWrappedEnv_120) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_120, StartThreadDelegatesToTarget_120) {
  auto func = [](void* arg) { };
  int dummy = 42;
  EXPECT_CALL(*mock_env_, StartThread(func, &dummy)).Times(1);
  wrapper_->StartThread(func, &dummy);
}

// Test StartThread with nullptr function pointer and arg
TEST_F(EnvWrapperTest_120, StartThreadWithNullArgs_120) {
  EXPECT_CALL(*mock_env_, StartThread(nullptr, nullptr)).Times(1);
  wrapper_->StartThread(nullptr, nullptr);
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_120, NewSequentialFileDelegatesToTarget_120) {
  SequentialFile* result = nullptr;
  std::string fname = "/test/file.txt";
  EXPECT_CALL(*mock_env_, NewSequentialFile(fname, &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewSequentialFile(fname, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile returns error from target
TEST_F(EnvWrapperTest_120, NewSequentialFileReturnsError_120) {
  SequentialFile* result = nullptr;
  std::string fname = "/nonexistent/file.txt";
  EXPECT_CALL(*mock_env_, NewSequentialFile(fname, &result))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));
  Status s = wrapper_->NewSequentialFile(fname, &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_120, NewRandomAccessFileDelegatesToTarget_120) {
  RandomAccessFile* result = nullptr;
  std::string fname = "/test/random.txt";
  EXPECT_CALL(*mock_env_, NewRandomAccessFile(fname, &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewRandomAccessFile(fname, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_120, NewWritableFileDelegatesToTarget_120) {
  WritableFile* result = nullptr;
  std::string fname = "/test/writable.txt";
  EXPECT_CALL(*mock_env_, NewWritableFile(fname, &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewWritableFile(fname, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_120, NewAppendableFileDelegatesToTarget_120) {
  WritableFile* result = nullptr;
  std::string fname = "/test/appendable.txt";
  EXPECT_CALL(*mock_env_, NewAppendableFile(fname, &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewAppendableFile(fname, &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target and returns true
TEST_F(EnvWrapperTest_120, FileExistsReturnsTrue_120) {
  std::string fname = "/test/existing.txt";
  EXPECT_CALL(*mock_env_, FileExists(fname))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists(fname));
}

// Test FileExists delegates to target and returns false
TEST_F(EnvWrapperTest_120, FileExistsReturnsFalse_120) {
  std::string fname = "/test/nonexistent.txt";
  EXPECT_CALL(*mock_env_, FileExists(fname))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists(fname));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_120, GetChildrenDelegatesToTarget_120) {
  std::vector<std::string> children;
  std::string dir = "/test/dir";
  EXPECT_CALL(*mock_env_, GetChildren(dir, &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{"a", "b", "c"}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren(dir, &children);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(children.size(), 3u);
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_120, GetChildrenEmptyDir_120) {
  std::vector<std::string> children;
  std::string dir = "/test/empty";
  EXPECT_CALL(*mock_env_, GetChildren(dir, &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren(dir, &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_120, RemoveFileDelegatesToTarget_120) {
  std::string fname = "/test/remove.txt";
  EXPECT_CALL(*mock_env_, RemoveFile(fname))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveFile(fname);
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile returns error
TEST_F(EnvWrapperTest_120, RemoveFileReturnsError_120) {
  std::string fname = "/test/remove_fail.txt";
  EXPECT_CALL(*mock_env_, RemoveFile(fname))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  Status s = wrapper_->RemoveFile(fname);
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_120, CreateDirDelegatesToTarget_120) {
  std::string dirname = "/test/newdir";
  EXPECT_CALL(*mock_env_, CreateDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->CreateDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_120, RemoveDirDelegatesToTarget_120) {
  std::string dirname = "/test/removedir";
  EXPECT_CALL(*mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_120, GetFileSizeDelegatesToTarget_120) {
  uint64_t size = 0;
  std::string fname = "/test/filesize.txt";
  EXPECT_CALL(*mock_env_, GetFileSize(fname, &size))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(1024u),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize(fname, &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 1024u);
}

// Test GetFileSize with zero size
TEST_F(EnvWrapperTest_120, GetFileSizeZero_120) {
  uint64_t size = 999;
  std::string fname = "/test/empty_file.txt";
  EXPECT_CALL(*mock_env_, GetFileSize(fname, &size))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(0u),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize(fname, &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_120, RenameFileDelegatesToTarget_120) {
  std::string src = "/test/src.txt";
  std::string target = "/test/dst.txt";
  EXPECT_CALL(*mock_env_, RenameFile(src, target))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile(src, target);
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_120, LockFileDelegatesToTarget_120) {
  FileLock* lock = nullptr;
  std::string fname = "/test/lock";
  EXPECT_CALL(*mock_env_, LockFile(fname, &lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->LockFile(fname, &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_120, UnlockFileDelegatesToTarget_120) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
TEST_F(EnvWrapperTest_120, ScheduleDelegatesToTarget_120) {
  auto func = [](void* arg) { };
  int dummy = 10;
  EXPECT_CALL(*mock_env_, Schedule(func, &dummy)).Times(1);
  wrapper_->Schedule(func, &dummy);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_120, GetTestDirectoryDelegatesToTarget_120) {
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
TEST_F(EnvWrapperTest_120, NewLoggerDelegatesToTarget_120) {
  Logger* logger = nullptr;
  std::string fname = "/test/log";
  EXPECT_CALL(*mock_env_, NewLogger(fname, &logger))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewLogger(fname, &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_120, NowMicrosDelegatesToTarget_120) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890u));
  uint64_t now = wrapper_->NowMicros();
  EXPECT_EQ(now, 1234567890u);
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_120, NowMicrosReturnsZero_120) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0u));
  uint64_t now = wrapper_->NowMicros();
  EXPECT_EQ(now, 0u);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_120, SleepForMicrosecondsDelegatesToTarget_120) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000)).Times(1);
  wrapper_->SleepForMicroseconds(1000);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_120, SleepForMicrosecondsZero_120) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0)).Times(1);
  wrapper_->SleepForMicroseconds(0);
}

// Test that multiple operations delegate correctly
TEST_F(EnvWrapperTest_120, MultipleDelegations_120) {
  std::string fname = "/test/multi.txt";
  
  EXPECT_CALL(*mock_env_, FileExists(fname))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists(fname));

  WritableFile* wf = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile(fname, &wf))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewWritableFile(fname, &wf);
  EXPECT_TRUE(s.ok());

  EXPECT_CALL(*mock_env_, FileExists(fname))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists(fname));
}

// Test with empty string filename
TEST_F(EnvWrapperTest_120, EmptyFilenameNewSequentialFile_120) {
  SequentialFile* result = nullptr;
  std::string fname = "";
  EXPECT_CALL(*mock_env_, NewSequentialFile(fname, &result))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty filename")));
  Status s = wrapper_->NewSequentialFile(fname, &result);
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test RenameFile with same source and target
TEST_F(EnvWrapperTest_120, RenameFileSameName_120) {
  std::string name = "/test/same.txt";
  EXPECT_CALL(*mock_env_, RenameFile(name, name))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile(name, name);
  EXPECT_TRUE(s.ok());
}

// Test with Env::Default() as a real integration test
TEST(EnvWrapperDefaultTest_120, WrapDefaultEnv_120) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);
  EXPECT_EQ(wrapper.target(), default_env);
  
  // NowMicros should return a positive value
  uint64_t now = wrapper.NowMicros();
  EXPECT_GT(now, 0u);
}

TEST(EnvWrapperDefaultTest_120, GetTestDirectoryFromDefault_120) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);
  
  std::string path;
  Status s = wrapper.GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(path.empty());
}

TEST(EnvWrapperDefaultTest_120, FileExistsOnNonExistentFile_120) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);
  
  bool exists = wrapper.FileExists("/this/path/should/not/exist/ever_120");
  EXPECT_FALSE(exists);
}

TEST(EnvWrapperDefaultTest_120, StartThreadCallsFunction_120) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);
  
  std::atomic<bool> called(false);
  auto func = [](void* arg) {
    std::atomic<bool>* flag = reinterpret_cast<std::atomic<bool>*>(arg);
    flag->store(true);
  };
  
  wrapper.StartThread(func, &called);
  
  // Wait for thread to complete
  for (int i = 0; i < 100 && !called.load(); ++i) {
    default_env->SleepForMicroseconds(10000);  // 10ms
  }
  EXPECT_TRUE(called.load());
}

}  // namespace leveldb
