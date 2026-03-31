#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

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

class EnvWrapperTest_114 : public ::testing::Test {
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

// Test that target() returns the correct underlying Env
TEST_F(EnvWrapperTest_114, TargetReturnsUnderlyingEnv_114) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test RemoveDir delegates to target and returns OK
TEST_F(EnvWrapperTest_114, RemoveDirDelegatesToTarget_114) {
  EXPECT_CALL(*mock_env_, RemoveDir("/test/dir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir("/test/dir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target and returns error
TEST_F(EnvWrapperTest_114, RemoveDirReturnsErrorFromTarget_114) {
  EXPECT_CALL(*mock_env_, RemoveDir("/nonexistent"))
      .WillOnce(
          ::testing::Return(Status::IOError("/nonexistent", "No such file")));
  Status s = wrapper_->RemoveDir("/nonexistent");
  EXPECT_TRUE(s.IsIOError());
}

// Test RemoveDir with empty string
TEST_F(EnvWrapperTest_114, RemoveDirEmptyString_114) {
  EXPECT_CALL(*mock_env_, RemoveDir(""))
      .WillOnce(::testing::Return(Status::InvalidArgument("empty dir")));
  Status s = wrapper_->RemoveDir("");
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test RemoveDir passes exact argument
TEST_F(EnvWrapperTest_114, RemoveDirPassesExactArgument_114) {
  std::string dir_name = "/some/deep/nested/directory/path";
  EXPECT_CALL(*mock_env_, RemoveDir(dir_name))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir(dir_name);
  EXPECT_TRUE(s.ok());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_114, CreateDirDelegatesToTarget_114) {
  EXPECT_CALL(*mock_env_, CreateDir("/new/dir"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->CreateDir("/new/dir");
  EXPECT_TRUE(s.ok());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_114, NewSequentialFileDelegatesToTarget_114) {
  SequentialFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewSequentialFile("/test/file", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewSequentialFile("/test/file", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_114, NewRandomAccessFileDelegatesToTarget_114) {
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("/test/file", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewRandomAccessFile("/test/file", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_114, NewWritableFileDelegatesToTarget_114) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewWritableFile("/test/file", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewWritableFile("/test/file", &result);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_114, NewAppendableFileDelegatesToTarget_114) {
  WritableFile* result = nullptr;
  EXPECT_CALL(*mock_env_, NewAppendableFile("/test/file", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewAppendableFile("/test/file", &result);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target returning true
TEST_F(EnvWrapperTest_114, FileExistsDelegatesToTargetTrue_114) {
  EXPECT_CALL(*mock_env_, FileExists("/test/file"))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(wrapper_->FileExists("/test/file"));
}

// Test FileExists delegates to target returning false
TEST_F(EnvWrapperTest_114, FileExistsDelegatesToTargetFalse_114) {
  EXPECT_CALL(*mock_env_, FileExists("/nonexistent"))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(wrapper_->FileExists("/nonexistent"));
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_114, GetChildrenDelegatesToTarget_114) {
  std::vector<std::string> children;
  EXPECT_CALL(*mock_env_, GetChildren("/test/dir", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(
              std::vector<std::string>{"a.txt", "b.txt"}),
          ::testing::Return(Status::OK())));
  Status s = wrapper_->GetChildren("/test/dir", &children);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(children.size(), 2u);
  EXPECT_EQ(children[0], "a.txt");
  EXPECT_EQ(children[1], "b.txt");
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_114, RemoveFileDelegatesToTarget_114) {
  EXPECT_CALL(*mock_env_, RemoveFile("/test/file"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveFile("/test/file");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_114, GetFileSizeDelegatesToTarget_114) {
  uint64_t size = 0;
  EXPECT_CALL(*mock_env_, GetFileSize("/test/file", ::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(1024),
                                  ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("/test/file", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 1024u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_114, RenameFileDelegatesToTarget_114) {
  EXPECT_CALL(*mock_env_, RenameFile("/src", "/dst"))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RenameFile("/src", "/dst");
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_114, LockFileDelegatesToTarget_114) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, LockFile("/test/lock", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->LockFile("/test/lock", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_114, UnlockFileDelegatesToTarget_114) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
TEST_F(EnvWrapperTest_114, ScheduleDelegatesToTarget_114) {
  void (*func)(void*) = [](void*) {};
  int arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(func, &arg)).Times(1);
  wrapper_->Schedule(func, &arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_114, StartThreadDelegatesToTarget_114) {
  void (*func)(void*) = [](void*) {};
  int arg = 42;
  EXPECT_CALL(*mock_env_, StartThread(func, &arg)).Times(1);
  wrapper_->StartThread(func, &arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_114, GetTestDirectoryDelegatesToTarget_114) {
  std::string path;
  EXPECT_CALL(*mock_env_, GetTestDirectory(::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"),
                                  ::testing::Return(Status::OK())));
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_114, NewLoggerDelegatesToTarget_114) {
  Logger* logger = nullptr;
  EXPECT_CALL(*mock_env_, NewLogger("/test/log", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->NewLogger("/test/log", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_114, NowMicrosDelegatesToTarget_114) {
  EXPECT_CALL(*mock_env_, NowMicros()).WillOnce(::testing::Return(123456789));
  uint64_t result = wrapper_->NowMicros();
  EXPECT_EQ(result, 123456789u);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_114, SleepForMicrosecondsDelegatesToTarget_114) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000)).Times(1);
  wrapper_->SleepForMicroseconds(1000);
}

// Test RemoveDir with special characters in path
TEST_F(EnvWrapperTest_114, RemoveDirSpecialCharactersInPath_114) {
  std::string special_path = "/test/dir with spaces/and-dashes/and_underscores";
  EXPECT_CALL(*mock_env_, RemoveDir(special_path))
      .WillOnce(::testing::Return(Status::OK()));
  Status s = wrapper_->RemoveDir(special_path);
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir called multiple times
TEST_F(EnvWrapperTest_114, RemoveDirCalledMultipleTimes_114) {
  EXPECT_CALL(*mock_env_, RemoveDir("/dir1"))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(*mock_env_, RemoveDir("/dir2"))
      .WillOnce(::testing::Return(Status::IOError("error")));

  Status s1 = wrapper_->RemoveDir("/dir1");
  Status s2 = wrapper_->RemoveDir("/dir2");

  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.IsIOError());
}

// Test NowMicros returns zero (boundary)
TEST_F(EnvWrapperTest_114, NowMicrosReturnsZero_114) {
  EXPECT_CALL(*mock_env_, NowMicros()).WillOnce(::testing::Return(0));
  EXPECT_EQ(wrapper_->NowMicros(), 0u);
}

// Test NowMicros returns max uint64
TEST_F(EnvWrapperTest_114, NowMicrosReturnsMaxValue_114) {
  uint64_t max_val = std::numeric_limits<uint64_t>::max();
  EXPECT_CALL(*mock_env_, NowMicros()).WillOnce(::testing::Return(max_val));
  EXPECT_EQ(wrapper_->NowMicros(), max_val);
}

// Test GetFileSize with zero size file (boundary)
TEST_F(EnvWrapperTest_114, GetFileSizeZeroBytes_114) {
  uint64_t size = 999;
  EXPECT_CALL(*mock_env_, GetFileSize("/empty", ::testing::_))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(0),
                                  ::testing::Return(Status::OK())));
  Status s = wrapper_->GetFileSize("/empty", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0u);
}

// Test SleepForMicroseconds with zero (boundary)
TEST_F(EnvWrapperTest_114, SleepForMicrosecondsZero_114) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(0)).Times(1);
  wrapper_->SleepForMicroseconds(0);
}

// Test RemoveFile returns NotFound error
TEST_F(EnvWrapperTest_114, RemoveFileReturnsNotFound_114) {
  EXPECT_CALL(*mock_env_, RemoveFile("/nonexistent"))
      .WillOnce(::testing::Return(Status::NotFound("/nonexistent")));
  Status s = wrapper_->RemoveFile("/nonexistent");
  EXPECT_TRUE(s.IsNotFound());
}

// Test RenameFile returns error
TEST_F(EnvWrapperTest_114, RenameFileReturnsError_114) {
  EXPECT_CALL(*mock_env_, RenameFile("/src", "/dst"))
      .WillOnce(::testing::Return(Status::IOError("rename failed")));
  Status s = wrapper_->RenameFile("/src", "/dst");
  EXPECT_TRUE(s.IsIOError());
}

// Test that wrapper uses Default env
TEST(EnvWrapperDefaultEnvTest_114, WrapDefaultEnv_114) {
  Env* default_env = Env::Default();
  ASSERT_NE(default_env, nullptr);
  EnvWrapper wrapper(default_env);
  EXPECT_EQ(wrapper.target(), default_env);
}

}  // namespace leveldb
