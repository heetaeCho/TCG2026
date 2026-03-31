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

class EnvWrapperTest_117 : public ::testing::Test {
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
TEST_F(EnvWrapperTest_117, TargetReturnsWrappedEnv_117) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_117, LockFileDelegatesToTarget_117) {
  FileLock* lock = nullptr;
  std::string fname = "/tmp/test.lock";

  EXPECT_CALL(*mock_env_, LockFile(fname, &lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->LockFile(fname, &lock);
  EXPECT_TRUE(s.ok());
}

// Test LockFile propagates error from target
TEST_F(EnvWrapperTest_117, LockFileReturnsErrorFromTarget_117) {
  FileLock* lock = nullptr;
  std::string fname = "/tmp/nonexistent.lock";

  EXPECT_CALL(*mock_env_, LockFile(fname, &lock))
      .WillOnce(::testing::Return(Status::IOError("lock failed")));

  Status s = wrapper_->LockFile(fname, &lock);
  EXPECT_TRUE(s.IsIOError());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_117, UnlockFileDelegatesToTarget_117) {
  FileLock* lock = nullptr;

  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_117, NewSequentialFileDelegatesToTarget_117) {
  SequentialFile* result = nullptr;
  std::string fname = "/tmp/seq_file";

  EXPECT_CALL(*mock_env_, NewSequentialFile(fname, &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewSequentialFile(fname, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_117, NewRandomAccessFileDelegatesToTarget_117) {
  RandomAccessFile* result = nullptr;
  std::string fname = "/tmp/rand_file";

  EXPECT_CALL(*mock_env_, NewRandomAccessFile(fname, &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewRandomAccessFile(fname, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_117, NewWritableFileDelegatesToTarget_117) {
  WritableFile* result = nullptr;
  std::string fname = "/tmp/writable_file";

  EXPECT_CALL(*mock_env_, NewWritableFile(fname, &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewWritableFile(fname, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_117, NewAppendableFileDelegatesToTarget_117) {
  WritableFile* result = nullptr;
  std::string fname = "/tmp/appendable_file";

  EXPECT_CALL(*mock_env_, NewAppendableFile(fname, &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewAppendableFile(fname, &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_117, FileExistsDelegatesToTarget_117) {
  std::string fname = "/tmp/existing_file";

  EXPECT_CALL(*mock_env_, FileExists(fname))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists(fname));
}

// Test FileExists returns false when target returns false
TEST_F(EnvWrapperTest_117, FileExistsReturnsFalse_117) {
  std::string fname = "/tmp/nonexistent_file";

  EXPECT_CALL(*mock_env_, FileExists(fname))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper_->FileExists(fname));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_117, GetChildrenDelegatesToTarget_117) {
  std::string dir = "/tmp/test_dir";
  std::vector<std::string> children;

  EXPECT_CALL(*mock_env_, GetChildren(dir, &children))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->GetChildren(dir, &children);
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_117, RemoveFileDelegatesToTarget_117) {
  std::string fname = "/tmp/remove_me";

  EXPECT_CALL(*mock_env_, RemoveFile(fname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveFile(fname);
  EXPECT_TRUE(s.ok());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_117, CreateDirDelegatesToTarget_117) {
  std::string dirname = "/tmp/new_dir";

  EXPECT_CALL(*mock_env_, CreateDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->CreateDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_117, RemoveDirDelegatesToTarget_117) {
  std::string dirname = "/tmp/remove_dir";

  EXPECT_CALL(*mock_env_, RemoveDir(dirname))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveDir(dirname);
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_117, GetFileSizeDelegatesToTarget_117) {
  std::string fname = "/tmp/sized_file";
  uint64_t size = 0;

  EXPECT_CALL(*mock_env_, GetFileSize(fname, &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(12345),
                                 ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize(fname, &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 12345u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_117, RenameFileDelegatesToTarget_117) {
  std::string src = "/tmp/old_name";
  std::string target = "/tmp/new_name";

  EXPECT_CALL(*mock_env_, RenameFile(src, target))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile(src, target);
  EXPECT_TRUE(s.ok());
}

// Test RenameFile propagates error
TEST_F(EnvWrapperTest_117, RenameFileReturnsErrorFromTarget_117) {
  std::string src = "/tmp/old";
  std::string target = "/tmp/new";

  EXPECT_CALL(*mock_env_, RenameFile(src, target))
      .WillOnce(::testing::Return(Status::IOError("rename failed")));

  Status s = wrapper_->RenameFile(src, target);
  EXPECT_TRUE(s.IsIOError());
}

// Test Schedule delegates to target
TEST_F(EnvWrapperTest_117, ScheduleDelegatesToTarget_117) {
  void (*func)(void*) = [](void*) {};
  void* arg = nullptr;

  EXPECT_CALL(*mock_env_, Schedule(func, arg)).Times(1);

  wrapper_->Schedule(func, arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_117, StartThreadDelegatesToTarget_117) {
  void (*func)(void*) = [](void*) {};
  void* arg = nullptr;

  EXPECT_CALL(*mock_env_, StartThread(func, arg)).Times(1);

  wrapper_->StartThread(func, arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_117, GetTestDirectoryDelegatesToTarget_117) {
  std::string path;

  EXPECT_CALL(*mock_env_, GetTestDirectory(&path))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"),
                                 ::testing::Return(Status::OK())));

  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_117, NewLoggerDelegatesToTarget_117) {
  Logger* logger = nullptr;
  std::string fname = "/tmp/log";

  EXPECT_CALL(*mock_env_, NewLogger(fname, &logger))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewLogger(fname, &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_117, NowMicrosDelegatesToTarget_117) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890ULL));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890ULL);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_117, SleepForMicrosecondsDelegatesToTarget_117) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000)).Times(1);

  wrapper_->SleepForMicroseconds(1000);
}

// Test LockFile with empty filename
TEST_F(EnvWrapperTest_117, LockFileEmptyFilename_117) {
  FileLock* lock = nullptr;
  std::string fname = "";

  EXPECT_CALL(*mock_env_, LockFile(fname, &lock))
      .WillOnce(::testing::Return(Status::IOError("empty filename")));

  Status s = wrapper_->LockFile(fname, &lock);
  EXPECT_TRUE(s.IsIOError());
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_117, NowMicrosReturnsZero_117) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0ULL));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 0ULL);
}

// Test NowMicros returns max value
TEST_F(EnvWrapperTest_117, NowMicrosReturnsMaxValue_117) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(UINT64_MAX));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, UINT64_MAX);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_117, SleepForMicrosecondsZero_117) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0)).Times(1);

  wrapper_->SleepForMicroseconds(0);
}

// Test GetFileSize with error
TEST_F(EnvWrapperTest_117, GetFileSizeReturnsError_117) {
  std::string fname = "/tmp/no_file";
  uint64_t size = 0;

  EXPECT_CALL(*mock_env_, GetFileSize(fname, &size))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));

  Status s = wrapper_->GetFileSize(fname, &size);
  EXPECT_TRUE(s.IsNotFound());
}

// Test multiple sequential calls delegate properly
TEST_F(EnvWrapperTest_117, MultipleLockUnlockCalls_117) {
  FileLock* lock = nullptr;
  std::string fname = "/tmp/multi.lock";

  EXPECT_CALL(*mock_env_, LockFile(fname, &lock))
      .Times(2)
      .WillRepeatedly(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .Times(2)
      .WillRepeatedly(::testing::Return(Status::OK()));

  EXPECT_TRUE(wrapper_->LockFile(fname, &lock).ok());
  EXPECT_TRUE(wrapper_->UnlockFile(lock).ok());
  EXPECT_TRUE(wrapper_->LockFile(fname, &lock).ok());
  EXPECT_TRUE(wrapper_->UnlockFile(lock).ok());
}

// Test that arguments are passed through correctly for GetChildren
TEST_F(EnvWrapperTest_117, GetChildrenPopulatesResults_117) {
  std::string dir = "/tmp/children_dir";
  std::vector<std::string> children;

  EXPECT_CALL(*mock_env_, GetChildren(dir, &children))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](const std::string&, std::vector<std::string>* r) {
            r->push_back("file1");
            r->push_back("file2");
            r->push_back("file3");
          }),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren(dir, &children);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(children.size(), 3u);
  EXPECT_EQ(children[0], "file1");
  EXPECT_EQ(children[1], "file2");
  EXPECT_EQ(children[2], "file3");
}

// Test with Default Env (integration-style, non-mock)
TEST(EnvWrapperDefaultTest_117, WrapDefaultEnv_117) {
  Env* default_env = Env::Default();
  ASSERT_NE(default_env, nullptr);

  EnvWrapper wrapper(default_env);
  EXPECT_EQ(wrapper.target(), default_env);

  // Verify NowMicros returns a reasonable value
  uint64_t micros = wrapper.NowMicros();
  EXPECT_GT(micros, 0u);
}

// Test GetTestDirectory with Default Env through wrapper
TEST(EnvWrapperDefaultTest_117, GetTestDirectoryWorks_117) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);

  std::string path;
  Status s = wrapper.GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(path.empty());
}

// Test CreateDir and RemoveDir through wrapper with default env
TEST(EnvWrapperDefaultTest_117, CreateAndRemoveDir_117) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);

  std::string test_path;
  ASSERT_TRUE(wrapper.GetTestDirectory(&test_path).ok());

  std::string dir = test_path + "/env_wrapper_test_117_dir";
  // Clean up first in case it exists
  wrapper.RemoveDir(dir);

  Status s = wrapper.CreateDir(dir);
  EXPECT_TRUE(s.ok());

  s = wrapper.RemoveDir(dir);
  EXPECT_TRUE(s.ok());
}

// Test FileExists through wrapper with default env
TEST(EnvWrapperDefaultTest_117, FileExistsCheck_117) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);

  EXPECT_FALSE(wrapper.FileExists("/tmp/definitely_nonexistent_file_117_xyz"));
}

}  // namespace leveldb
