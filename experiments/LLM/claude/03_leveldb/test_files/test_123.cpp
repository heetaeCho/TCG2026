#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"

namespace leveldb {

// Mock Env to act as the target for EnvWrapper
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

class EnvWrapperTest_123 : public ::testing::Test {
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
TEST_F(EnvWrapperTest_123, TargetReturnsWrappedEnv_123) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_123, NowMicrosDelegatesToTarget_123) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890ULL));
  EXPECT_EQ(wrapper_->NowMicros(), 1234567890ULL);
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_123, NowMicrosReturnsZero_123) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0ULL));
  EXPECT_EQ(wrapper_->NowMicros(), 0ULL);
}

// Test NowMicros returns max uint64
TEST_F(EnvWrapperTest_123, NowMicrosReturnsMaxValue_123) {
  uint64_t max_val = std::numeric_limits<uint64_t>::max();
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(max_val));
  EXPECT_EQ(wrapper_->NowMicros(), max_val);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_123, SleepForMicrosecondsDelegatesToTarget_123) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000))
      .Times(1);
  wrapper_->SleepForMicroseconds(1000);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_123, SleepForMicrosecondsZero_123) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);
  wrapper_->SleepForMicroseconds(0);
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_123, NewSequentialFileDelegatesToTarget_123) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("test.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewSequentialFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile with error
TEST_F(EnvWrapperTest_123, NewSequentialFileReturnsError_123) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("nonexistent.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));
  Status s = wrapper_->NewSequentialFile("nonexistent.txt", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_123, NewRandomAccessFileDelegatesToTarget_123) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("test.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewRandomAccessFile("test.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile with error
TEST_F(EnvWrapperTest_123, NewRandomAccessFileReturnsError_123) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("missing.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("not found")));
  Status s = wrapper_->NewRandomAccessFile("missing.txt", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_123, NewWritableFileDelegatesToTarget_123) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("output.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewWritableFile("output.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile with IO error
TEST_F(EnvWrapperTest_123, NewWritableFileReturnsIOError_123) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("readonly.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));
  Status s = wrapper_->NewWritableFile("readonly.txt", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_123, NewAppendableFileDelegatesToTarget_123) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("append.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewAppendableFile("append.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target - file exists
TEST_F(EnvWrapperTest_123, FileExistsReturnsTrue_123) {
  EXPECT_CALL(*mock_env_, FileExists("existing.txt"))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists("existing.txt"));
}

// Test FileExists delegates to target - file does not exist
TEST_F(EnvWrapperTest_123, FileExistsReturnsFalse_123) {
  EXPECT_CALL(*mock_env_, FileExists("missing.txt"))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists("missing.txt"));
}

// Test FileExists with empty filename
TEST_F(EnvWrapperTest_123, FileExistsEmptyFilename_123) {
  EXPECT_CALL(*mock_env_, FileExists(""))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists(""));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_123, GetChildrenDelegatesToTarget_123) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/tmp", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{"a.txt", "b.txt"}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren("/tmp", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(children.size(), 2u);
  EXPECT_EQ(children[0], "a.txt");
  EXPECT_EQ(children[1], "b.txt");
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_123, GetChildrenEmptyDirectory_123) {
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
TEST_F(EnvWrapperTest_123, RemoveFileDelegatesToTarget_123) {
  EXPECT_CALL(*mock_env_, RemoveFile("delete_me.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveFile("delete_me.txt");
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile with error
TEST_F(EnvWrapperTest_123, RemoveFileReturnsError_123) {
  EXPECT_CALL(*mock_env_, RemoveFile("protected.txt"))
      .WillOnce(::testing::Return(Status::IOError("cannot delete")));
  Status s = wrapper_->RemoveFile("protected.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_123, CreateDirDelegatesToTarget_123) {
  EXPECT_CALL(*mock_env_, CreateDir("/tmp/newdir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->CreateDir("/tmp/newdir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_123, RemoveDirDelegatesToTarget_123) {
  EXPECT_CALL(*mock_env_, RemoveDir("/tmp/olddir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir("/tmp/olddir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_123, GetFileSizeDelegatesToTarget_123) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("big.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(42ULL),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("big.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 42ULL);
}

// Test GetFileSize with zero size
TEST_F(EnvWrapperTest_123, GetFileSizeZero_123) {
  uint64_t size = 999;
  EXPECT_CALL(*mock_env_, GetFileSize("empty.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(0ULL),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("empty.txt", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0ULL);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_123, RenameFileDelegatesToTarget_123) {
  EXPECT_CALL(*mock_env_, RenameFile("old.txt", "new.txt"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile("old.txt", "new.txt");
  EXPECT_TRUE(s.ok());
}

// Test RenameFile with error
TEST_F(EnvWrapperTest_123, RenameFileReturnsError_123) {
  EXPECT_CALL(*mock_env_, RenameFile("src.txt", "dst.txt"))
      .WillOnce(::testing::Return(Status::IOError("rename failed")));
  Status s = wrapper_->RenameFile("src.txt", "dst.txt");
  EXPECT_TRUE(s.IsIOError());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_123, LockFileDelegatesToTarget_123) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lock.lk", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->LockFile("lock.lk", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_123, UnlockFileDelegatesToTarget_123) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyFunction(void* arg) {}

TEST_F(EnvWrapperTest_123, ScheduleDelegatesToTarget_123) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyFunction, &dummy_arg))
      .Times(1);
  wrapper_->Schedule(DummyFunction, &dummy_arg);
}

// Test Schedule with null arg
TEST_F(EnvWrapperTest_123, ScheduleWithNullArg_123) {
  EXPECT_CALL(*mock_env_, Schedule(DummyFunction, nullptr))
      .Times(1);
  wrapper_->Schedule(DummyFunction, nullptr);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_123, StartThreadDelegatesToTarget_123) {
  int dummy_arg = 99;
  EXPECT_CALL(*mock_env_, StartThread(DummyFunction, &dummy_arg))
      .Times(1);
  wrapper_->StartThread(DummyFunction, &dummy_arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_123, GetTestDirectoryDelegatesToTarget_123) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<0>("/tmp/test"),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_123, NewLoggerDelegatesToTarget_123) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewLogger("log.txt", &logger);
  EXPECT_TRUE(s.ok());
}

// Test multiple NowMicros calls return different values
TEST_F(EnvWrapperTest_123, NowMicrosMultipleCalls_123) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(100ULL))
      .WillOnce(::testing::Return(200ULL))
      .WillOnce(::testing::Return(300ULL));
  EXPECT_EQ(wrapper_->NowMicros(), 100ULL);
  EXPECT_EQ(wrapper_->NowMicros(), 200ULL);
  EXPECT_EQ(wrapper_->NowMicros(), 300ULL);
}

// Test NewSequentialFile with empty filename
TEST_F(EnvWrapperTest_123, NewSequentialFileEmptyFilename_123) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("", ::testing::_))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty filename")));
  Status s = wrapper_->NewSequentialFile("", &result);
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test that wrapper properly delegates all calls (comprehensive delegation test)
TEST_F(EnvWrapperTest_123, AllDelegationCalls_123) {
  // This test ensures that multiple different calls can be made in sequence
  EXPECT_CALL(*mock_env_, FileExists("a.txt")).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, NowMicros()).WillOnce(::testing::Return(500ULL));
  EXPECT_CALL(*mock_env_, CreateDir("/newdir")).WillOnce(::testing::Return(Status::OK()));

  EXPECT_TRUE(wrapper_->FileExists("a.txt"));
  EXPECT_EQ(wrapper_->NowMicros(), 500ULL);
  EXPECT_TRUE(wrapper_->CreateDir("/newdir").ok());
}

// Test using default env through wrapper
TEST_F(EnvWrapperTest_123, WrapperWithDefaultEnv_123) {
  Env* default_env = Env::Default();
  EnvWrapper default_wrapper(default_env);
  EXPECT_EQ(default_wrapper.target(), default_env);
  
  // NowMicros should return a positive value
  uint64_t time = default_wrapper.NowMicros();
  EXPECT_GT(time, 0ULL);
}

// Test that NowMicros is monotonically non-decreasing with default env
TEST_F(EnvWrapperTest_123, NowMicrosMonotonicity_123) {
  Env* default_env = Env::Default();
  EnvWrapper default_wrapper(default_env);
  
  uint64_t t1 = default_wrapper.NowMicros();
  uint64_t t2 = default_wrapper.NowMicros();
  EXPECT_GE(t2, t1);
}

}  // namespace leveldb
