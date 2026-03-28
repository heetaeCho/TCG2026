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

class EnvWrapperTest_107 : public ::testing::Test {
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

// Test that target() returns the correct Env pointer
TEST_F(EnvWrapperTest_107, TargetReturnsCorrectEnv_107) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_107, NewRandomAccessFileDelegatesToTarget_107) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("testfile.dat", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewRandomAccessFile("testfile.dat", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile returns error from target
TEST_F(EnvWrapperTest_107, NewRandomAccessFileReturnsError_107) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("nonexistent.dat", &result))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));

  Status s = wrapper_->NewRandomAccessFile("nonexistent.dat", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewRandomAccessFile with empty filename
TEST_F(EnvWrapperTest_107, NewRandomAccessFileEmptyFilename_107) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("", &result))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty filename")));

  Status s = wrapper_->NewRandomAccessFile("", &result);
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_107, NewSequentialFileDelegatesToTarget_107) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("seqfile.dat", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewSequentialFile("seqfile.dat", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_107, NewWritableFileDelegatesToTarget_107) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("writable.dat", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewWritableFile("writable.dat", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_107, NewAppendableFileDelegatesToTarget_107) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("appendable.dat", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewAppendableFile("appendable.dat", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_107, FileExistsDelegatesToTarget_107) {
  EXPECT_CALL(*mock_env_, FileExists("exists.dat"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("exists.dat"));
}

// Test FileExists returns false
TEST_F(EnvWrapperTest_107, FileExistsReturnsFalse_107) {
  EXPECT_CALL(*mock_env_, FileExists("noexist.dat"))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper_->FileExists("noexist.dat"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_107, GetChildrenDelegatesToTarget_107) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/some/dir", &children))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->GetChildren("/some/dir", &children);
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_107, RemoveFileDelegatesToTarget_107) {
  EXPECT_CALL(*mock_env_, RemoveFile("remove_me.dat"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveFile("remove_me.dat");
  EXPECT_TRUE(s.ok());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_107, CreateDirDelegatesToTarget_107) {
  EXPECT_CALL(*mock_env_, CreateDir("/new/dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->CreateDir("/new/dir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_107, RemoveDirDelegatesToTarget_107) {
  EXPECT_CALL(*mock_env_, RemoveDir("/old/dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveDir("/old/dir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_107, GetFileSizeDelegatesToTarget_107) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("file.dat", &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(1024),
                                 ::testing::Return(Status::OK())));

  Status s = wrapper_->GetFileSize("file.dat", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 1024u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_107, RenameFileDelegatesToTarget_107) {
  EXPECT_CALL(*mock_env_, RenameFile("old.dat", "new.dat"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile("old.dat", "new.dat");
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_107, LockFileDelegatesToTarget_107) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("lock.lck", &lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->LockFile("lock.lck", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_107, UnlockFileDelegatesToTarget_107) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyFunction(void* arg) {}

TEST_F(EnvWrapperTest_107, ScheduleDelegatesToTarget_107) {
  int arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(DummyFunction, &arg))
      .Times(1);

  wrapper_->Schedule(DummyFunction, &arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_107, StartThreadDelegatesToTarget_107) {
  int arg = 99;
  EXPECT_CALL(*mock_env_, StartThread(DummyFunction, &arg))
      .Times(1);

  wrapper_->StartThread(DummyFunction, &arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_107, GetTestDirectoryDelegatesToTarget_107) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(&path))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"),
                                 ::testing::Return(Status::OK())));

  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_107, NewLoggerDelegatesToTarget_107) {
  Logger* result = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("log.txt", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewLogger("log.txt", &result);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_107, NowMicrosDelegatesToTarget_107) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890ULL));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890ULL);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_107, SleepForMicrosecondsDelegatesToTarget_107) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(500))
      .Times(1);

  wrapper_->SleepForMicroseconds(500);
}

// Test NewRandomAccessFile with special characters in filename
TEST_F(EnvWrapperTest_107, NewRandomAccessFileSpecialCharsFilename_107) {
  RandomAccessFile* result = nullptr;
  std::string special_name = "/path/to/file with spaces & (special).dat";
  EXPECT_CALL(*mock_env_, NewRandomAccessFile(special_name, &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->NewRandomAccessFile(special_name, &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile IOError from target
TEST_F(EnvWrapperTest_107, NewRandomAccessFileIOError_107) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("ioerr.dat", &result))
      .WillOnce(::testing::Return(Status::IOError("disk failure")));

  Status s = wrapper_->NewRandomAccessFile("ioerr.dat", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test multiple calls delegate correctly
TEST_F(EnvWrapperTest_107, MultipleCallsDelegate_107) {
  EXPECT_CALL(*mock_env_, FileExists("a.dat")).WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, FileExists("b.dat")).WillOnce(::testing::Return(false));
  EXPECT_CALL(*mock_env_, FileExists("c.dat")).WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("a.dat"));
  EXPECT_FALSE(wrapper_->FileExists("b.dat"));
  EXPECT_TRUE(wrapper_->FileExists("c.dat"));
}

// Test NowMicros returns zero (boundary)
TEST_F(EnvWrapperTest_107, NowMicrosReturnsZero_107) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0ULL));

  EXPECT_EQ(wrapper_->NowMicros(), 0ULL);
}

// Test NowMicros returns max value (boundary)
TEST_F(EnvWrapperTest_107, NowMicrosReturnsMax_107) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(UINT64_MAX));

  EXPECT_EQ(wrapper_->NowMicros(), UINT64_MAX);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_107, SleepForMicrosecondsZero_107) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0))
      .Times(1);

  wrapper_->SleepForMicroseconds(0);
}

// Test GetFileSize with error
TEST_F(EnvWrapperTest_107, GetFileSizeError_107) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("missing.dat", &size))
      .WillOnce(::testing::Return(Status::NotFound("no such file")));

  Status s = wrapper_->GetFileSize("missing.dat", &size);
  EXPECT_TRUE(s.IsNotFound());
}

// Test that the default Env can be obtained
TEST(EnvDefaultTest_107, DefaultEnvIsNotNull_107) {
  Env* env = Env::Default();
  EXPECT_NE(env, nullptr);
}

// Test that the default Env returns the same instance
TEST(EnvDefaultTest_107, DefaultEnvIsSingleton_107) {
  Env* env1 = Env::Default();
  Env* env2 = Env::Default();
  EXPECT_EQ(env1, env2);
}

}  // namespace leveldb
