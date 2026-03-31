#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include <string>
#include <vector>

namespace leveldb {

// Mock class for Env to serve as the target for EnvWrapper
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewSequentialFile, (const std::string& f, SequentialFile** r), (override));
  MOCK_METHOD(Status, NewRandomAccessFile, (const std::string& f, RandomAccessFile** r), (override));
  MOCK_METHOD(Status, NewWritableFile, (const std::string& f, WritableFile** r), (override));
  MOCK_METHOD(Status, NewAppendableFile, (const std::string& f, WritableFile** r), (override));
  MOCK_METHOD(bool, FileExists, (const std::string& f), (override));
  MOCK_METHOD(Status, GetChildren, (const std::string& dir, std::vector<std::string>* r), (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& f), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& d), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& d), (override));
  MOCK_METHOD(Status, GetFileSize, (const std::string& f, uint64_t* s), (override));
  MOCK_METHOD(Status, RenameFile, (const std::string& s, const std::string& t), (override));
  MOCK_METHOD(Status, LockFile, (const std::string& f, FileLock** l), (override));
  MOCK_METHOD(Status, UnlockFile, (FileLock* l), (override));
  MOCK_METHOD(void, Schedule, (void (*f)(void*), void* a), (override));
  MOCK_METHOD(void, StartThread, (void (*f)(void*), void* a), (override));
  MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));
  MOCK_METHOD(Status, NewLogger, (const std::string& fname, Logger** result), (override));
  MOCK_METHOD(uint64_t, NowMicros, (), (override));
  MOCK_METHOD(void, SleepForMicroseconds, (int micros), (override));
};

class EnvWrapperTest_451 : public ::testing::Test {
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

// Test that target() returns the Env pointer passed in the constructor
TEST_F(EnvWrapperTest_451, TargetReturnsCorrectEnv_451) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test GetChildren delegates to target and returns OK status
TEST_F(EnvWrapperTest_451, GetChildrenDelegatesToTarget_451) {
  std::vector<std::string> expected_children = {"file1.txt", "file2.txt", "subdir"};
  EXPECT_CALL(*mock_env_, GetChildren("/test/dir", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(expected_children),
          ::testing::Return(Status::OK())));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("/test/dir", &result);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result, expected_children);
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_451, GetChildrenEmptyDirectory_451) {
  std::vector<std::string> empty;
  EXPECT_CALL(*mock_env_, GetChildren("/empty/dir", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(empty),
          ::testing::Return(Status::OK())));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("/empty/dir", &result);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(result.empty());
}

// Test GetChildren when target returns error
TEST_F(EnvWrapperTest_451, GetChildrenReturnsError_451) {
  EXPECT_CALL(*mock_env_, GetChildren("/nonexistent", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("directory not found")));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("/nonexistent", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test GetChildren with empty string path
TEST_F(EnvWrapperTest_451, GetChildrenEmptyPath_451) {
  std::vector<std::string> children = {"a"};
  EXPECT_CALL(*mock_env_, GetChildren("", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(children),
          ::testing::Return(Status::OK())));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("", &result);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result.size(), 1u);
  EXPECT_EQ(result[0], "a");
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_451, NewSequentialFileDelegates_451) {
  EXPECT_CALL(*mock_env_, NewSequentialFile("/test/file", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  SequentialFile* file = nullptr;
  Status s = wrapper_->NewSequentialFile("/test/file", &file);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_451, NewRandomAccessFileDelegates_451) {
  EXPECT_CALL(*mock_env_, NewRandomAccessFile("/test/file", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  RandomAccessFile* file = nullptr;
  Status s = wrapper_->NewRandomAccessFile("/test/file", &file);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_451, NewWritableFileDelegates_451) {
  EXPECT_CALL(*mock_env_, NewWritableFile("/test/file", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  WritableFile* file = nullptr;
  Status s = wrapper_->NewWritableFile("/test/file", &file);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_451, NewAppendableFileDelegates_451) {
  EXPECT_CALL(*mock_env_, NewAppendableFile("/test/file", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  WritableFile* file = nullptr;
  Status s = wrapper_->NewAppendableFile("/test/file", &file);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target - true case
TEST_F(EnvWrapperTest_451, FileExistsReturnsTrue_451) {
  EXPECT_CALL(*mock_env_, FileExists("/existing/file"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("/existing/file"));
}

// Test FileExists delegates to target - false case
TEST_F(EnvWrapperTest_451, FileExistsReturnsFalse_451) {
  EXPECT_CALL(*mock_env_, FileExists("/nonexistent/file"))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper_->FileExists("/nonexistent/file"));
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_451, RemoveFileDelegates_451) {
  EXPECT_CALL(*mock_env_, RemoveFile("/test/file"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveFile("/test/file");
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile error case
TEST_F(EnvWrapperTest_451, RemoveFileError_451) {
  EXPECT_CALL(*mock_env_, RemoveFile("/protected/file"))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->RemoveFile("/protected/file");
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_451, CreateDirDelegates_451) {
  EXPECT_CALL(*mock_env_, CreateDir("/new/dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->CreateDir("/new/dir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_451, RemoveDirDelegates_451) {
  EXPECT_CALL(*mock_env_, RemoveDir("/empty/dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveDir("/empty/dir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_451, GetFileSizeDelegates_451) {
  EXPECT_CALL(*mock_env_, GetFileSize("/test/file", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(1024),
          ::testing::Return(Status::OK())));

  uint64_t size = 0;
  Status s = wrapper_->GetFileSize("/test/file", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 1024u);
}

// Test GetFileSize with zero size file
TEST_F(EnvWrapperTest_451, GetFileSizeZero_451) {
  EXPECT_CALL(*mock_env_, GetFileSize("/empty/file", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(0),
          ::testing::Return(Status::OK())));

  uint64_t size = 999;
  Status s = wrapper_->GetFileSize("/empty/file", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0u);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_451, RenameFileDelegates_451) {
  EXPECT_CALL(*mock_env_, RenameFile("/old/name", "/new/name"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile("/old/name", "/new/name");
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_451, LockFileDelegates_451) {
  EXPECT_CALL(*mock_env_, LockFile("/test/lock", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  FileLock* lock = nullptr;
  Status s = wrapper_->LockFile("/test/lock", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_451, UnlockFileDelegates_451) {
  FileLock* lock = nullptr;
  EXPECT_CALL(*mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
TEST_F(EnvWrapperTest_451, ScheduleDelegates_451) {
  auto func = [](void* arg) {};
  int arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(::testing::_, ::testing::_))
      .Times(1);

  wrapper_->Schedule(func, &arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_451, StartThreadDelegates_451) {
  auto func = [](void* arg) {};
  int arg = 42;
  EXPECT_CALL(*mock_env_, StartThread(::testing::_, ::testing::_))
      .Times(1);

  wrapper_->StartThread(func, &arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_451, GetTestDirectoryDelegates_451) {
  EXPECT_CALL(*mock_env_, GetTestDirectory(::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<0>("/tmp/test"),
          ::testing::Return(Status::OK())));

  std::string path;
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_451, NewLoggerDelegates_451) {
  EXPECT_CALL(*mock_env_, NewLogger("/test/log", ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Logger* logger = nullptr;
  Status s = wrapper_->NewLogger("/test/log", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_451, NowMicrosDelegates_451) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890u));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890u);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_451, SleepForMicrosecondsDelegates_451) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(1000))
      .Times(1);

  wrapper_->SleepForMicroseconds(1000);
}

// Test GetChildren with many files
TEST_F(EnvWrapperTest_451, GetChildrenManyFiles_451) {
  std::vector<std::string> many_files;
  for (int i = 0; i < 1000; ++i) {
    many_files.push_back("file_" + std::to_string(i));
  }
  EXPECT_CALL(*mock_env_, GetChildren("/large/dir", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(many_files),
          ::testing::Return(Status::OK())));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("/large/dir", &result);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result.size(), 1000u);
}

// Test NewSequentialFile error case
TEST_F(EnvWrapperTest_451, NewSequentialFileError_451) {
  EXPECT_CALL(*mock_env_, NewSequentialFile("/nonexistent", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("file not found")));

  SequentialFile* file = nullptr;
  Status s = wrapper_->NewSequentialFile("/nonexistent", &file);
  EXPECT_TRUE(s.IsIOError());
}

// Test NowMicros returns zero
TEST_F(EnvWrapperTest_451, NowMicrosZero_451) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0u));

  EXPECT_EQ(wrapper_->NowMicros(), 0u);
}

// Test GetChildren called multiple times
TEST_F(EnvWrapperTest_451, GetChildrenMultipleCalls_451) {
  std::vector<std::string> children1 = {"a", "b"};
  std::vector<std::string> children2 = {"c", "d", "e"};

  EXPECT_CALL(*mock_env_, GetChildren("/dir1", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(children1),
          ::testing::Return(Status::OK())));
  EXPECT_CALL(*mock_env_, GetChildren("/dir2", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(children2),
          ::testing::Return(Status::OK())));

  std::vector<std::string> result1;
  Status s1 = wrapper_->GetChildren("/dir1", &result1);
  EXPECT_TRUE(s1.ok());
  EXPECT_EQ(result1.size(), 2u);

  std::vector<std::string> result2;
  Status s2 = wrapper_->GetChildren("/dir2", &result2);
  EXPECT_TRUE(s2.ok());
  EXPECT_EQ(result2.size(), 3u);
}

// Test RenameFile error case
TEST_F(EnvWrapperTest_451, RenameFileError_451) {
  EXPECT_CALL(*mock_env_, RenameFile("/src", "/dst"))
      .WillOnce(::testing::Return(Status::IOError("rename failed")));

  Status s = wrapper_->RenameFile("/src", "/dst");
  EXPECT_TRUE(s.IsIOError());
}

// Test GetFileSize with large file
TEST_F(EnvWrapperTest_451, GetFileSizeLargeFile_451) {
  uint64_t large_size = static_cast<uint64_t>(1) << 40;  // 1 TB
  EXPECT_CALL(*mock_env_, GetFileSize("/large/file", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(large_size),
          ::testing::Return(Status::OK())));

  uint64_t size = 0;
  Status s = wrapper_->GetFileSize("/large/file", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, large_size);
}

}  // namespace leveldb
