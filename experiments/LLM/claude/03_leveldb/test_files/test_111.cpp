#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <cstdint>

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

class EnvWrapperTest_111 : public ::testing::Test {
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

// Test that target() returns the env passed to constructor
TEST_F(EnvWrapperTest_111, TargetReturnsWrappedEnv_111) {
  EXPECT_EQ(wrapper_->target(), mock_env_);
}

// Test GetChildren delegates to target
TEST_F(EnvWrapperTest_111, GetChildrenDelegatesToTarget_111) {
  std::vector<std::string> expected_children = {"file1.txt", "file2.txt", "subdir"};
  EXPECT_CALL(*mock_env_, GetChildren(::testing::Eq("/test/dir"), ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(expected_children),
          ::testing::Return(Status::OK())));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("/test/dir", &result);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result, expected_children);
}

// Test GetChildren propagates error from target
TEST_F(EnvWrapperTest_111, GetChildrenPropagatesError_111) {
  EXPECT_CALL(*mock_env_, GetChildren(::testing::Eq("/nonexistent"), ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("directory not found")));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("/nonexistent", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test GetChildren with empty directory
TEST_F(EnvWrapperTest_111, GetChildrenEmptyDirectory_111) {
  std::vector<std::string> empty;
  EXPECT_CALL(*mock_env_, GetChildren(::testing::Eq("/empty"), ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(empty),
          ::testing::Return(Status::OK())));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("/empty", &result);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(result.empty());
}

// Test GetChildren with empty string directory
TEST_F(EnvWrapperTest_111, GetChildrenEmptyStringDir_111) {
  EXPECT_CALL(*mock_env_, GetChildren(::testing::Eq(""), ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("invalid path")));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("", &result);
  EXPECT_TRUE(s.IsIOError());
}

// Test NewSequentialFile delegates to target
TEST_F(EnvWrapperTest_111, NewSequentialFileDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, NewSequentialFile(::testing::Eq("/test/file"), ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  SequentialFile* file = nullptr;
  Status s = wrapper_->NewSequentialFile("/test/file", &file);
  EXPECT_TRUE(s.ok());
}

// Test NewRandomAccessFile delegates to target
TEST_F(EnvWrapperTest_111, NewRandomAccessFileDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, NewRandomAccessFile(::testing::Eq("/test/file"), ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  RandomAccessFile* file = nullptr;
  Status s = wrapper_->NewRandomAccessFile("/test/file", &file);
  EXPECT_TRUE(s.ok());
}

// Test NewWritableFile delegates to target
TEST_F(EnvWrapperTest_111, NewWritableFileDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, NewWritableFile(::testing::Eq("/test/file"), ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  WritableFile* file = nullptr;
  Status s = wrapper_->NewWritableFile("/test/file", &file);
  EXPECT_TRUE(s.ok());
}

// Test NewAppendableFile delegates to target
TEST_F(EnvWrapperTest_111, NewAppendableFileDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, NewAppendableFile(::testing::Eq("/test/file"), ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  WritableFile* file = nullptr;
  Status s = wrapper_->NewAppendableFile("/test/file", &file);
  EXPECT_TRUE(s.ok());
}

// Test FileExists delegates to target
TEST_F(EnvWrapperTest_111, FileExistsDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, FileExists(::testing::Eq("/test/file")))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper_->FileExists("/test/file"));
}

// Test FileExists returns false when target returns false
TEST_F(EnvWrapperTest_111, FileExistsReturnsFalse_111) {
  EXPECT_CALL(*mock_env_, FileExists(::testing::Eq("/nonexistent")))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper_->FileExists("/nonexistent"));
}

// Test RemoveFile delegates to target
TEST_F(EnvWrapperTest_111, RemoveFileDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::Eq("/test/file")))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveFile("/test/file");
  EXPECT_TRUE(s.ok());
}

// Test RemoveFile propagates error
TEST_F(EnvWrapperTest_111, RemoveFilePropagatesError_111) {
  EXPECT_CALL(*mock_env_, RemoveFile(::testing::Eq("/test/file")))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper_->RemoveFile("/test/file");
  EXPECT_TRUE(s.IsIOError());
}

// Test CreateDir delegates to target
TEST_F(EnvWrapperTest_111, CreateDirDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, CreateDir(::testing::Eq("/test/newdir")))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->CreateDir("/test/newdir");
  EXPECT_TRUE(s.ok());
}

// Test RemoveDir delegates to target
TEST_F(EnvWrapperTest_111, RemoveDirDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, RemoveDir(::testing::Eq("/test/dir")))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RemoveDir("/test/dir");
  EXPECT_TRUE(s.ok());
}

// Test GetFileSize delegates to target
TEST_F(EnvWrapperTest_111, GetFileSizeDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, GetFileSize(::testing::Eq("/test/file"), ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(12345ULL),
          ::testing::Return(Status::OK())));

  uint64_t size = 0;
  Status s = wrapper_->GetFileSize("/test/file", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 12345ULL);
}

// Test GetFileSize with zero-size file
TEST_F(EnvWrapperTest_111, GetFileSizeZero_111) {
  EXPECT_CALL(*mock_env_, GetFileSize(::testing::Eq("/test/empty"), ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(0ULL),
          ::testing::Return(Status::OK())));

  uint64_t size = 999;
  Status s = wrapper_->GetFileSize("/test/empty", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(size, 0ULL);
}

// Test RenameFile delegates to target
TEST_F(EnvWrapperTest_111, RenameFileDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, RenameFile(::testing::Eq("/old"), ::testing::Eq("/new")))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->RenameFile("/old", "/new");
  EXPECT_TRUE(s.ok());
}

// Test LockFile delegates to target
TEST_F(EnvWrapperTest_111, LockFileDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, LockFile(::testing::Eq("/test/lock"), ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  FileLock* lock = nullptr;
  Status s = wrapper_->LockFile("/test/lock", &lock);
  EXPECT_TRUE(s.ok());
}

// Test UnlockFile delegates to target
TEST_F(EnvWrapperTest_111, UnlockFileDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, UnlockFile(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper_->UnlockFile(nullptr);
  EXPECT_TRUE(s.ok());
}

// Test Schedule delegates to target
static void DummyFunction(void* arg) {}

TEST_F(EnvWrapperTest_111, ScheduleDelegatesToTarget_111) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, Schedule(::testing::_, ::testing::_))
      .Times(1);

  wrapper_->Schedule(&DummyFunction, &dummy_arg);
}

// Test StartThread delegates to target
TEST_F(EnvWrapperTest_111, StartThreadDelegatesToTarget_111) {
  int dummy_arg = 42;
  EXPECT_CALL(*mock_env_, StartThread(::testing::_, ::testing::_))
      .Times(1);

  wrapper_->StartThread(&DummyFunction, &dummy_arg);
}

// Test GetTestDirectory delegates to target
TEST_F(EnvWrapperTest_111, GetTestDirectoryDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, GetTestDirectory(::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<0>(std::string("/tmp/test")),
          ::testing::Return(Status::OK())));

  std::string path;
  Status s = wrapper_->GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(path, "/tmp/test");
}

// Test NewLogger delegates to target
TEST_F(EnvWrapperTest_111, NewLoggerDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, NewLogger(::testing::Eq("/test/log"), ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  Logger* logger = nullptr;
  Status s = wrapper_->NewLogger("/test/log", &logger);
  EXPECT_TRUE(s.ok());
}

// Test NowMicros delegates to target
TEST_F(EnvWrapperTest_111, NowMicrosDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890ULL));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 1234567890ULL);
}

// Test SleepForMicroseconds delegates to target
TEST_F(EnvWrapperTest_111, SleepForMicrosecondsDelegatesToTarget_111) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(::testing::Eq(1000)))
      .Times(1);

  wrapper_->SleepForMicroseconds(1000);
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_111, SleepForMicrosecondsBoundaryZero_111) {
  EXPECT_CALL(*mock_env_, SleepForMicroseconds(::testing::Eq(0)))
      .Times(1);

  wrapper_->SleepForMicroseconds(0);
}

// Test NewSequentialFile propagates error from target
TEST_F(EnvWrapperTest_111, NewSequentialFilePropagatesError_111) {
  EXPECT_CALL(*mock_env_, NewSequentialFile(::testing::Eq("/nonexistent"), ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));

  SequentialFile* file = nullptr;
  Status s = wrapper_->NewSequentialFile("/nonexistent", &file);
  EXPECT_TRUE(s.IsNotFound());
}

// Test NewWritableFile propagates error from target
TEST_F(EnvWrapperTest_111, NewWritableFilePropagatesError_111) {
  EXPECT_CALL(*mock_env_, NewWritableFile(::testing::Eq("/readonly/file"), ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("read-only filesystem")));

  WritableFile* file = nullptr;
  Status s = wrapper_->NewWritableFile("/readonly/file", &file);
  EXPECT_TRUE(s.IsIOError());
}

// Test GetChildren with many children
TEST_F(EnvWrapperTest_111, GetChildrenManyFiles_111) {
  std::vector<std::string> many_files;
  for (int i = 0; i < 1000; ++i) {
    many_files.push_back("file_" + std::to_string(i));
  }
  EXPECT_CALL(*mock_env_, GetChildren(::testing::Eq("/large_dir"), ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(many_files),
          ::testing::Return(Status::OK())));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren("/large_dir", &result);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result.size(), 1000u);
}

// Test NowMicros returns zero boundary
TEST_F(EnvWrapperTest_111, NowMicrosReturnsZero_111) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(0ULL));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, 0ULL);
}

// Test NowMicros returns max uint64
TEST_F(EnvWrapperTest_111, NowMicrosReturnsMaxValue_111) {
  EXPECT_CALL(*mock_env_, NowMicros())
      .WillOnce(::testing::Return(UINT64_MAX));

  uint64_t micros = wrapper_->NowMicros();
  EXPECT_EQ(micros, UINT64_MAX);
}

// Test GetFileSize propagates error
TEST_F(EnvWrapperTest_111, GetFileSizePropagatesError_111) {
  EXPECT_CALL(*mock_env_, GetFileSize(::testing::Eq("/nonexistent"), ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("no such file")));

  uint64_t size = 0;
  Status s = wrapper_->GetFileSize("/nonexistent", &size);
  EXPECT_TRUE(s.IsNotFound());
}

// Test RenameFile propagates error
TEST_F(EnvWrapperTest_111, RenameFilePropagatesError_111) {
  EXPECT_CALL(*mock_env_, RenameFile(::testing::Eq("/src"), ::testing::Eq("/dst")))
      .WillOnce(::testing::Return(Status::IOError("rename failed")));

  Status s = wrapper_->RenameFile("/src", "/dst");
  EXPECT_TRUE(s.IsIOError());
}

// Test multiple calls delegate correctly
TEST_F(EnvWrapperTest_111, MultipleCallsDelegate_111) {
  EXPECT_CALL(*mock_env_, FileExists(::testing::Eq("/a")))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(*mock_env_, FileExists(::testing::Eq("/b")))
      .WillOnce(::testing::Return(false));

  EXPECT_TRUE(wrapper_->FileExists("/a"));
  EXPECT_FALSE(wrapper_->FileExists("/b"));
}

// Test that correct directory path is forwarded for GetChildren
TEST_F(EnvWrapperTest_111, GetChildrenForwardsExactPath_111) {
  std::string expected_path = "/some/specific/path/with spaces";
  EXPECT_CALL(*mock_env_, GetChildren(::testing::Eq(expected_path), ::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  std::vector<std::string> result;
  Status s = wrapper_->GetChildren(expected_path, &result);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
