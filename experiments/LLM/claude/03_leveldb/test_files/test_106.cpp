#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

namespace leveldb {

// Mock Env class to act as the target for EnvWrapper
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

class EnvWrapperTest_106 : public ::testing::Test {
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

// Test that target() returns the correct underlying Env pointer
TEST_F(EnvWrapperTest_106, TargetReturnsUnderlyingEnv_106) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_106, NewSequentialFileDelegatesToTarget_106) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("test.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewSequentialFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile propagates errors from target
TEST_F(EnvWrapperTest_106, NewSequentialFilePropagatesToTargetError_106) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("nonexistent.txt", &result))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));

  Status s = wrapper_->NewSequentialFile("nonexistent.txt", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_106, NewRandomAccessFileDelegatesToTarget_106) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("rand.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewRandomAccessFile("rand.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_106, NewWritableFileDelegatesToTarget_106) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("writable.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewWritableFile("writable.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_106, NewAppendableFileDelegatesToTarget_106) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("appendable.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewAppendableFile("appendable.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_106, FileExistsDelegatesToTarget_106) {
  EXPECT_CALL(*mock_env_, FileExists("exists.txt"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("exists.txt"));
}

// Test FileExists returns false when target says false
TEST_F(EnvWrapperTest_106, FileExistsReturnsFalse_106) {
  EXPECT_CALL(*mock_env_, FileExists("notexists.txt"))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper_->FileExists("notexists.txt"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_106, GetChildrenDelegatesToTarget_106) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/dir", &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{"a", "b", "c"}),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren("/dir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(children.size(), 3u);
  EXPECT_EQ(children[0], "a");
  EXPECT_EQ(children[1], "b");
  EXPECT_EQ(children[2], "c");
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_106, RemoveFileDelegatesToTarget_106) {
  EXPECT_CALL(*mock_env_, RemoveFile("remove_me.txt"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveFile("remove_me.txt");
  EXPECT_TRUE(s.ok());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_106, CreateDirDelegatesToTarget_106) {
  EXPECT_CALL(*mock_env_, CreateDir("/newdir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->CreateDir("/newdir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_106, RemoveDirDelegatesToTarget_106) {
  EXPECT_CALL(*mock_env_, RemoveDir("/olddir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveDir("/olddir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_106, GetFileSizeDelegatesToTarget_106) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("file.txt", &size))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(12345),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize("file.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 12345u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_106, RenameFileDelegatesToTarget_106) {
  EXPECT_CALL(*mock_env_, RenameFile("old.txt", "new.txt"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile("old.txt", "new.txt");
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_106, LockFileDelegatesToTarget_106) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lock.txt", &lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->LockFile("lock.txt", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_106, UnlockFileDelegatesToTarget_106) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyScheduleFunc(void* arg) {}

TEST_F(EnvWrapperTest_106, ScheduleDelegatesToTarget_106) {
  int arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, &arg))
      .Times(1);

  wrapper_->Schedule(DummyScheduleFunc, &arg);
}

// Test StartThread delegates to target
static void DummyThreadFunc(void* arg) {}

TEST_F(EnvWrapperTest_106, StartThreadDelegatesToTarget_106) {
  int arg = 99;
  EXPECT_CALL(*mock_env_, StartThread(DummyThreadFunc, &arg))
      .Times(1);

  wrapper_->StartThread(DummyThreadFunc, &arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_106, GetTestDirectoryDelegatesToTarget_106) {
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
TEST_F(EnvWrapperTest_106, NewLoggerDelegatesToTarget_106) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log.txt", &logger))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewLogger("log.txt", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_106, NowMicrosDelegatesToTarget_106) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890ULL));

  uint64_t time = wrapper_->NowMicros();
  EXPECT_EQ(time, 1234567890ULL);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_106, SleepForMicrosecondsDelegatesToTarget_106) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(500))
      .Times(1);

  wrapper_->SleepForMicroseconds(500);
}

// Test with empty string filename
TEST_F(EnvWrapperTest_106, NewSequentialFileEmptyFilename_106) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("", &result))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty filename")));

  Status s = wrapper_->NewSequentialFile("", &result);
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test GetFileSize with error
TEST_F(EnvWrapperTest_106, GetFileSizeError_106) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("nonexistent.txt", &size))
      .WillOnce(::testing::Return(Status::NotFound("no such file")));

  Status s = wrapper_->GetFileSize("nonexistent.txt", &size);
  EXPECT_TRUE(s.IsNotFound());
}

// Test RenameFile with IOError
TEST_F(EnvWrapperTest_106, RenameFileIOError_106) {
  EXPECT_CALL(*mock_env_, RenameFile("src.txt", "dst.txt"))
      .WillOnce(::testing::Return(Status::IOError("disk full")));

  Status s = wrapper_->RenameFile("src.txt", "dst.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test NewWritableFile propagates error
TEST_F(EnvWrapperTest_106, NewWritableFileError_106) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("/readonly/file.txt", &result))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->NewWritableFile("/readonly/file.txt", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir with error
TEST_F(EnvWrapperTest_106, CreateDirError_106) {
  EXPECT_CALL(*mock_env_, CreateDir("/no/permission"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->CreateDir("/no/permission");
  EXPECT_TRUE(s.IsIOError());
}

// Test RemoveDir with error
TEST_F(EnvWrapperTest_106, RemoveDirError_106) {
  EXPECT_CALL(*mock_env_, RemoveDir("/nonexistent"))
      .WillOnce(::testing::Return(Status::NotFound("directory not found")));

  Status s = wrapper_->RemoveDir("/nonexistent");
  EXPECT_TRUE(s.IsNotFound());
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_106, NowMicrosZero_106) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0ULL));

  uint64_t time = wrapper_->NowMicros();
  EXPECT_EQ(time, 0ULL);
}

// Test NowMicros returns max value
TEST_F(EnvWrapperTest_106, NowMicrosMaxValue_106) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(std::numeric_limits<uint64_t>::max()));

  uint64_t time = wrapper_->NowMicros();
  EXPECT_EQ(time, std::numeric_limits<uint64_t>::max());
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_106, SleepForMicrosecondsZero_106) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);

  wrapper_->SleepForMicroseconds(0);
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_106, GetChildrenEmptyDir_106) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/emptydir", &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));

  Status s = wrapper_->GetChildren("/emptydir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test that multiple calls are properly delegated
TEST_F(EnvWrapperTest_106, MultipleCallsDelegated_106) {
  EXPECT_CALL(*mock_env_, FileExists("file1.txt"))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, FileExists("file2.txt"))
      .WillOnce(::testing::Return(false));
  EXPECT_CALL(*mock_env_, FileExists("file3.txt"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("file1.txt"));
  EXPECT_FALSE(wrapper_->FileExists("file2.txt"));
  EXPECT_TRUE(wrapper_->FileExists("file3.txt"));
}

// Test Default Env is not null
TEST(EnvDefaultTest_106, DefaultEnvNotNull_106) {
  Env* env = Env::Default();
  EXPECT_NE(env, nullptr);
}

// Test Default Env returns same instance
TEST(EnvDefaultTest_106, DefaultEnvSameInstance_106) {
  Env* env1 = Env::Default();
  Env* env2 = Env::Default();
  EXPECT_EQ(env1, env2);
}

// Test with Default Env - GetTestDirectory
TEST(EnvDefaultTest_106, GetTestDirectory_106) {
  Env* env = Env::Default();
  std::string path;
  Status s = env->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(path.empty());
}

// Test with Default Env - NowMicros returns reasonable value
TEST(EnvDefaultTest_106, NowMicrosReasonableValue_106) {
  Env* env = Env::Default();
  uint64_t time = env->NowMicros();
  EXPECT_GT(time, 0u);
}

// Test LockFile with error propagation
TEST_F(EnvWrapperTest_106, LockFileError_106) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("/nonexistent/lock", &lock))
      .WillOnce(::testing::Return(Status::IOError("cannot lock")));

  Status s = wrapper_->LockFile("/nonexistent/lock", &lock);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewAppendableFile with error
TEST_F(EnvWrapperTest_106, NewAppendableFileError_106) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("/no/access.txt", &result))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->NewAppendableFile("/no/access.txt", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewRandomAccessFile with error
TEST_F(EnvWrapperTest_106, NewRandomAccessFileError_106) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("missing.txt", &result))
      .WillOnce(::testing::Return(Status::NotFound("not found")));

  Status s = wrapper_->NewRandomAccessFile("missing.txt", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test RemoveFile with error
TEST_F(EnvWrapperTest_106, RemoveFileError_106) {
  EXPECT_CALL(*mock_env_, RemoveFile("protected.txt"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->RemoveFile("protected.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test NewLogger with error
TEST_F(EnvWrapperTest_106, NewLoggerError_106) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("/readonly/log.txt", &logger))
      .WillOnce(::testing::Return(Status::IOError("cannot create")));

  Status s = wrapper_->NewLogger("/readonly/log.txt", &logger);
  EXPECT_TRUE(s.IsIOError());
}

// Test Schedule with nullptr arg
TEST_F(EnvWrapperTest_106, ScheduleWithNullArg_106) {
  EXPECT_CALL(*mock_env_, Schedule(DummyScheduleFunc, nullptr))
      .Times(1);

  wrapper_->Schedule(DummyScheduleFunc, nullptr);
}

// Test StartThread with nullptr arg
TEST_F(EnvWrapperTest_106, StartThreadWithNullArg_106) {
  EXPECT_CALL(*mock_env_, StartThread(DummyThreadFunc, nullptr))
      .Times(1);

  wrapper_->StartThread(DummyThreadFunc, nullptr);
}

}  // namespace leveldb
