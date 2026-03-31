#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <cstdint>

namespace leveldb {

// Mock Env to serve as the target_ for EnvWrapper
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

class EnvWrapperTest_108 : public ::testing::Test {
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

// Test that target() returns the wrapped env
TEST_F(EnvWrapperTest_108, TargetReturnsWrappedEnv_108) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_108, NewWritableFileDelegatesToTarget_108) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("test.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewWritableFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile propagates error from target
TEST_F(EnvWrapperTest_108, NewWritableFilePropagatesToTargetError_108) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("nonexistent.txt", &result))
      .WillOnce(::testing::Return(Status::IOError("No such file")));

  Status s = wrapper_->NewWritableFile("nonexistent.txt", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_108, NewSequentialFileDelegatesToTarget_108) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("seq.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewSequentialFile("seq.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_108, NewRandomAccessFileDelegatesToTarget_108) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("rand.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewRandomAccessFile("rand.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_108, NewAppendableFileDelegatesToTarget_108) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("append.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewAppendableFile("append.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_108, FileExistsDelegatesToTarget_108) {
  EXPECT_CALL(*mock_env_, FileExists("existing.txt"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("existing.txt"));
}

// Test FileExists returns false when target returns false
TEST_F(EnvWrapperTest_108, FileExistsReturnsFalseWhenTargetReturnsFalse_108) {
  EXPECT_CALL(*mock_env_, FileExists("missing.txt"))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper_->FileExists("missing.txt"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_108, GetChildrenDelegatesToTarget_108) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/dir", &children))
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

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_108, RemoveFileDelegatesToTarget_108) {
  EXPECT_CALL(*mock_env_, RemoveFile("to_remove.txt"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveFile("to_remove.txt");
  EXPECT_TRUE(s.ok());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_108, CreateDirDelegatesToTarget_108) {
  EXPECT_CALL(*mock_env_, CreateDir("/new_dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->CreateDir("/new_dir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_108, RemoveDirDelegatesToTarget_108) {
  EXPECT_CALL(*mock_env_, RemoveDir("/old_dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveDir("/old_dir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_108, GetFileSizeDelegatesToTarget_108) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("file.txt", &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(1024u),
                                  ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize("file.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 1024u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_108, RenameFileDelegatesToTarget_108) {
  EXPECT_CALL(*mock_env_, RenameFile("old.txt", "new.txt"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile("old.txt", "new.txt");
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_108, LockFileDelegatesToTarget_108) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lock_file", &lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->LockFile("lock_file", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_108, UnlockFileDelegatesToTarget_108) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyScheduleFunc(void* arg) {}

TEST_F(EnvWrapperTest_108, ScheduleDelegatesToTarget_108) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, &dummy_arg))
      .Times(1);

  wrapper_->Schedule(DummyScheduleFunc, &dummy_arg);
}

// Test StartThread delegates to target
static void DummyThreadFunc(void* arg) {}

TEST_F(EnvWrapperTest_108, StartThreadDelegatesToTarget_108) {
  int dummy_arg = 99;
  EXPECT_CALL(*mock_env_, StartThread(DummyThreadFunc, &dummy_arg))
      .Times(1);

  wrapper_->StartThread(DummyThreadFunc, &dummy_arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_108, GetTestDirectoryDelegatesToTarget_108) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(&path))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"),
                                  ::testing::Return(Status::OK())));

  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_108, NewLoggerDelegatesToTarget_108) {
  Logger* result = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewLogger("log.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_108, NowMicrosDelegatesToTarget_108) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890u));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890u);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_108, SleepForMicrosecondsDelegatesToTarget_108) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(500))
      .Times(1);

  wrapper_->SleepForMicroseconds(500);
}

// Test NewWritableFile with empty filename
TEST_F(EnvWrapperTest_108, NewWritableFileWithEmptyFilename_108) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("", &result))
      .WillOnce(::testing::Return(Status::IOError("empty filename")));

  Status s = wrapper_->NewWritableFile("", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_108, GetChildrenEmptyDirectory_108) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("", &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren("", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test GetFileSize returns zero for empty file
TEST_F(EnvWrapperTest_108, GetFileSizeZero_108) {
  uint64_t size = 999;
  EXPECT_CALL(*mock_env_, GetFileSize("empty.txt", &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(0u),
                                  ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize("empty.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0u);
}

// Test RenameFile error propagation
TEST_F(EnvWrapperTest_108, RenameFileErrorPropagation_108) {
  EXPECT_CALL(*mock_env_, RenameFile("src.txt", "dst.txt"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->RenameFile("src.txt", "dst.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_108, NowMicrosReturnsZero_108) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0u));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 0u);
}

// Test multiple delegations in sequence
TEST_F(EnvWrapperTest_108, MultipleCallsDelegateCorrectly_108) {
  EXPECT_CALL(*mock_env_, FileExists("a.txt"))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, FileExists("b.txt"))
      .WillOnce(::testing::Return(false));

  EXPECT_TRUE(wrapper_->FileExists("a.txt"));
  EXPECT_FALSE(wrapper_->FileExists("b.txt"));
}

// Test that SleepForMicroseconds with zero is valid
TEST_F(EnvWrapperTest_108, SleepForZeroMicroseconds_108) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);

  wrapper_->SleepForMicroseconds(0);
}

// Test default Env is not null
TEST(EnvDefaultTest_108, DefaultEnvIsNotNull_108) {
  Env* env = Env::Default();
  EXPECT_NE(env, nullptr);
}

// Test default Env GetTestDirectory works
TEST(EnvDefaultTest_108, DefaultEnvGetTestDirectory_108) {
  Env* env = Env::Default();
  std::string path;
  Status s = env->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(path.empty());
}

// Test default Env NowMicros returns non-zero (time should have advanced)
TEST(EnvDefaultTest_108, DefaultEnvNowMicros_108) {
  Env* env = Env::Default();
  uint64_t micros = env->NowMicros();
  EXPECT_GT(micros, 0u);
}

// Test EnvWrapper with default Env as target
TEST(EnvWrapperWithDefaultTest_108, WrapDefaultEnv_108) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);
  EXPECT_EQ(wrapper.target(), default_env);

  std::string path;
  Status s = wrapper.GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(path.empty());
}

// Test CreateDir and RemoveDir error cases via delegation
TEST_F(EnvWrapperTest_108, CreateDirError_108) {
  EXPECT_CALL(*mock_env_, CreateDir("/bad_dir"))
      .WillOnce(::testing::Return(Status::IOError("cannot create")));

  Status s = wrapper_->CreateDir("/bad_dir");
  EXPECT_TRUE(s.IsIOError());
}

TEST_F(EnvWrapperTest_108, RemoveDirError_108) {
  EXPECT_CALL(*mock_env_, RemoveDir("/nonexistent"))
      .WillOnce(::testing::Return(Status::IOError("not found")));

  Status s = wrapper_->RemoveDir("/nonexistent");
  EXPECT_TRUE(s.IsIOError());
}

// Test LockFile error
TEST_F(EnvWrapperTest_108, LockFileError_108) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("locked", &lock))
      .WillOnce(::testing::Return(Status::IOError("already locked")));

  Status s = wrapper_->LockFile("locked", &lock);
  EXPECT_TRUE(s.IsIOError());
}

// Test Schedule with nullptr arg
TEST_F(EnvWrapperTest_108, ScheduleWithNullArg_108) {
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, nullptr))
      .Times(1);

  wrapper_->Schedule(DummyScheduleFunc, nullptr);
}

}  // namespace leveldb
