#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

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

class EnvWrapperTest_124 : public ::testing::Test {
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

// Test that target() returns the env passed in the constructor
TEST_F(EnvWrapperTest_124, TargetReturnsWrappedEnv_124) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_124, SleepForMicrosecondsDelegatesToTarget_124) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000)).Times(1);
  wrapper_->SleepForMicroseconds(1000);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_124, SleepForMicrosecondsBoundaryZero_124) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0)).Times(1);
  wrapper_->SleepForMicroseconds(0);
}

// Test NowMicros delegates and returns correct value
TEST_F(EnvWrapperTest_124, NowMicrosDelegatesToTarget_124) {
  EXPECT_CALL(*mock_env_, NowMicros()).WillOnce(::testing::Return(123456789ULL));
  EXPECT_EQ(wrapper_->NowMicros(), 123456789ULL);
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_124, NewSequentialFileDelegatesToTarget_124) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("test.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewSequentialFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile returns error from target
TEST_F(EnvWrapperTest_124, NewSequentialFileReturnsError_124) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("nonexistent.txt", &result))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));
  Status s = wrapper_->NewSequentialFile("nonexistent.txt", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_124, NewRandomAccessFileDelegatesToTarget_124) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("test.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewRandomAccessFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_124, NewWritableFileDelegatesToTarget_124) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("output.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewWritableFile("output.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_124, NewAppendableFileDelegatesToTarget_124) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("append.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewAppendableFile("append.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target - file exists
TEST_F(EnvWrapperTest_124, FileExistsDelegatesToTargetTrue_124) {
  EXPECT_CALL(*mock_env_, FileExists("existing.txt"))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists("existing.txt"));
}

// Test FileExists delegates to target - file does not exist
TEST_F(EnvWrapperTest_124, FileExistsDelegatesToTargetFalse_124) {
  EXPECT_CALL(*mock_env_, FileExists("nonexistent.txt"))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists("nonexistent.txt"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_124, GetChildrenDelegatesToTarget_124) {
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
TEST_F(EnvWrapperTest_124, GetChildrenEmptyDirectory_124) {
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
TEST_F(EnvWrapperTest_124, RemoveFileDelegatesToTarget_124) {
  EXPECT_CALL(*mock_env_, RemoveFile("delete_me.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveFile("delete_me.txt");
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile with error
TEST_F(EnvWrapperTest_124, RemoveFileReturnsError_124) {
  EXPECT_CALL(*mock_env_, RemoveFile("protected.txt"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  Status s = wrapper_->RemoveFile("protected.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_124, CreateDirDelegatesToTarget_124) {
  EXPECT_CALL(*mock_env_, CreateDir("/new/dir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->CreateDir("/new/dir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_124, RemoveDirDelegatesToTarget_124) {
  EXPECT_CALL(*mock_env_, RemoveDir("/old/dir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir("/old/dir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_124, GetFileSizeDelegatesToTarget_124) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("file.txt", &size))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(42ULL),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("file.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 42ULL);
}

// Test GetFileSize with zero size
TEST_F(EnvWrapperTest_124, GetFileSizeZero_124) {
  uint64_t size = 999;
  EXPECT_CALL(*mock_env_, GetFileSize("empty.txt", &size))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(0ULL),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("empty.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0ULL);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_124, RenameFileDelegatesToTarget_124) {
  EXPECT_CALL(*mock_env_, RenameFile("old.txt", "new.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile("old.txt", "new.txt");
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_124, LockFileDelegatesToTarget_124) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lock.lck", &lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->LockFile("lock.lck", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_124, UnlockFileDelegatesToTarget_124) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyFunction(void* arg) {
  // No-op for testing delegation
}

TEST_F(EnvWrapperTest_124, ScheduleDelegatesToTarget_124) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyFunction, &dummy_arg)).Times(1);
  wrapper_->Schedule(DummyFunction, &dummy_arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_124, StartThreadDelegatesToTarget_124) {
  int dummy_arg = 99;
  EXPECT_CALL(*mock_env_, StartThread(DummyFunction, &dummy_arg)).Times(1);
  wrapper_->StartThread(DummyFunction, &dummy_arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_124, GetTestDirectoryDelegatesToTarget_124) {
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
TEST_F(EnvWrapperTest_124, NewLoggerDelegatesToTarget_124) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log.txt", &logger))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewLogger("log.txt", &logger);
  EXPECT_TRUE(s.ok());
}

// Test Schedule with nullptr argument
TEST_F(EnvWrapperTest_124, ScheduleWithNullArg_124) {
  EXPECT_CALL(*mock_env_, Schedule(DummyFunction, nullptr)).Times(1);
  wrapper_->Schedule(DummyFunction, nullptr);
}

// Test multiple delegations in sequence
TEST_F(EnvWrapperTest_124, MultipleDelegationsInSequence_124) {
  EXPECT_CALL(*mock_env_, FileExists("a.txt")).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, FileExists("b.txt")).WillOnce(::testing::Return(false));
  EXPECT_CALL(*mock_env_, NowMicros()).WillOnce(::testing::Return(100ULL));

  EXPECT_TRUE(wrapper_->FileExists("a.txt"));
  EXPECT_FALSE(wrapper_->FileExists("b.txt"));
  EXPECT_EQ(wrapper_->NowMicros(), 100ULL);
}

// Test with empty string filename
TEST_F(EnvWrapperTest_124, EmptyFilenameDelegatesToTarget_124) {
  EXPECT_CALL(*mock_env_, FileExists("")).WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists(""));
}

// Test SleepForMicroseconds with large value
TEST_F(EnvWrapperTest_124, SleepForMicrosecondsBoundaryLargeValue_124) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(INT_MAX)).Times(1);
  wrapper_->SleepForMicroseconds(INT_MAX);
}

// Test NowMicros returns large value
TEST_F(EnvWrapperTest_124, NowMicrosLargeValue_124) {
  EXPECT_CALL(*mock_env_, NowMicros()).WillOnce(::testing::Return(UINT64_MAX));
  EXPECT_EQ(wrapper_->NowMicros(), UINT64_MAX);
}

// Test that RenameFile with same source and target delegates correctly
TEST_F(EnvWrapperTest_124, RenameFileSameSourceAndTarget_124) {
  EXPECT_CALL(*mock_env_, RenameFile("same.txt", "same.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile("same.txt", "same.txt");
  EXPECT_TRUE(s.ok());
}

// Test using Default Env through EnvWrapper
TEST(EnvWrapperDefaultTest_124, WrapDefaultEnv_124) {
  Env* default_env = Env::Default();
  ASSERT_NE(default_env, nullptr);
  EnvWrapper wrapper(default_env);
  EXPECT_EQ(wrapper.target(), default_env);

  // Verify basic delegation works with real env
  std::string test_dir;
  Status s = wrapper.GetTestDirectory(&test_dir);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(test_dir.empty());
}

// Test NowMicros returns reasonable value via default env
TEST(EnvWrapperDefaultTest_124, NowMicrosReturnsNonZero_124) {
  Env* default_env = Env::Default();
  EnvWrapper wrapper(default_env);
  uint64_t time = wrapper.NowMicros();
  EXPECT_GT(time, 0ULL);
}

}  // namespace leveldb
