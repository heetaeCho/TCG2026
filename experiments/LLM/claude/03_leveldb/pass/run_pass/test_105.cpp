#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"

#include <string>
#include <vector>

namespace leveldb {
namespace {

// Mock class for Env to use as the target for EnvWrapper
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewSequentialFile,
              (const std::string& f, SequentialFile** r), (override));
  MOCK_METHOD(Status, NewRandomAccessFile,
              (const std::string& f, RandomAccessFile** r), (override));
  MOCK_METHOD(Status, NewWritableFile,
              (const std::string& f, WritableFile** r), (override));
  MOCK_METHOD(Status, NewAppendableFile,
              (const std::string& f, WritableFile** r), (override));
  MOCK_METHOD(bool, FileExists, (const std::string& f), (override));
  MOCK_METHOD(Status, GetChildren,
              (const std::string& dir, std::vector<std::string>* r),
              (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& f), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& d), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& d), (override));
  MOCK_METHOD(Status, GetFileSize, (const std::string& f, uint64_t* s),
              (override));
  MOCK_METHOD(Status, RenameFile,
              (const std::string& s, const std::string& t), (override));
  MOCK_METHOD(Status, LockFile, (const std::string& f, FileLock** l),
              (override));
  MOCK_METHOD(Status, UnlockFile, (FileLock* l), (override));
  MOCK_METHOD(void, Schedule, (void (*f)(void*), void* a), (override));
  MOCK_METHOD(void, StartThread, (void (*f)(void*), void* a), (override));
  MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));
  MOCK_METHOD(Status, NewLogger, (const std::string& fname, Logger** result),
              (override));
  MOCK_METHOD(uint64_t, NowMicros, (), (override));
  MOCK_METHOD(void, SleepForMicroseconds, (int micros), (override));
};

class EnvWrapperTest_105 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
};

// Test that target() returns the Env pointer passed in the constructor
TEST_F(EnvWrapperTest_105, TargetReturnsWrappedEnv_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_EQ(&mock_env_, wrapper.target());
}

// Test that NewSequentialFile delegates to the target env
TEST_F(EnvWrapperTest_105, NewSequentialFileDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  SequentialFile* result = nullptr;
  EXPECT_CALL(mock_env_, NewSequentialFile("test_file", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.NewSequentialFile("test_file", &result);
  EXPECT_TRUE(s.ok());
}

// Test that NewRandomAccessFile delegates to the target env
TEST_F(EnvWrapperTest_105, NewRandomAccessFileDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  RandomAccessFile* result = nullptr;
  EXPECT_CALL(mock_env_, NewRandomAccessFile("random_file", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.NewRandomAccessFile("random_file", &result);
  EXPECT_TRUE(s.ok());
}

// Test that NewWritableFile delegates to the target env
TEST_F(EnvWrapperTest_105, NewWritableFileDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  WritableFile* result = nullptr;
  EXPECT_CALL(mock_env_, NewWritableFile("writable_file", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.NewWritableFile("writable_file", &result);
  EXPECT_TRUE(s.ok());
}

// Test that NewAppendableFile delegates to the target env
TEST_F(EnvWrapperTest_105, NewAppendableFileDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  WritableFile* result = nullptr;
  EXPECT_CALL(mock_env_, NewAppendableFile("appendable_file", &result))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.NewAppendableFile("appendable_file", &result);
  EXPECT_TRUE(s.ok());
}

// Test that FileExists delegates to the target env
TEST_F(EnvWrapperTest_105, FileExistsDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, FileExists("existing_file"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper.FileExists("existing_file"));
}

// Test that FileExists returns false when target returns false
TEST_F(EnvWrapperTest_105, FileExistsReturnsFalse_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, FileExists("nonexistent_file"))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper.FileExists("nonexistent_file"));
}

// Test that GetChildren delegates to the target env
TEST_F(EnvWrapperTest_105, GetChildrenDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  std::vector<std::string> children;
  EXPECT_CALL(mock_env_, GetChildren("test_dir", &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(
              std::vector<std::string>{"file1", "file2"}),
          ::testing::Return(Status::OK())));

  Status s = wrapper.GetChildren("test_dir", &children);
  EXPECT_TRUE(s.ok());
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ("file1", children[0]);
  EXPECT_EQ("file2", children[1]);
}

// Test that RemoveFile delegates to the target env
TEST_F(EnvWrapperTest_105, RemoveFileDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, RemoveFile("file_to_remove"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.RemoveFile("file_to_remove");
  EXPECT_TRUE(s.ok());
}

// Test that CreateDir delegates to the target env
TEST_F(EnvWrapperTest_105, CreateDirDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, CreateDir("new_dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.CreateDir("new_dir");
  EXPECT_TRUE(s.ok());
}

// Test that RemoveDir delegates to the target env
TEST_F(EnvWrapperTest_105, RemoveDirDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, RemoveDir("old_dir"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.RemoveDir("old_dir");
  EXPECT_TRUE(s.ok());
}

// Test that GetFileSize delegates to the target env
TEST_F(EnvWrapperTest_105, GetFileSizeDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  uint64_t size = 0;
  EXPECT_CALL(mock_env_, GetFileSize("sized_file", &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(1024u),
                                  ::testing::Return(Status::OK())));

  Status s = wrapper.GetFileSize("sized_file", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(1024u, size);
}

// Test that RenameFile delegates to the target env
TEST_F(EnvWrapperTest_105, RenameFileDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, RenameFile("old_name", "new_name"))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.RenameFile("old_name", "new_name");
  EXPECT_TRUE(s.ok());
}

// Test that LockFile delegates to the target env
TEST_F(EnvWrapperTest_105, LockFileDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  FileLock* lock = nullptr;
  EXPECT_CALL(mock_env_, LockFile("lock_file", &lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.LockFile("lock_file", &lock);
  EXPECT_TRUE(s.ok());
}

// Test that UnlockFile delegates to the target env
TEST_F(EnvWrapperTest_105, UnlockFileDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  FileLock* lock = nullptr;
  EXPECT_CALL(mock_env_, UnlockFile(lock))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.UnlockFile(lock);
  EXPECT_TRUE(s.ok());
}

// Test that Schedule delegates to the target env
void DummyScheduleFunc(void* arg) {}

TEST_F(EnvWrapperTest_105, ScheduleDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  int dummy_arg = 42;
  EXPECT_CALL(mock_env_,
              Schedule(DummyScheduleFunc, static_cast<void*>(&dummy_arg)))
      .Times(1);

  wrapper.Schedule(DummyScheduleFunc, &dummy_arg);
}

// Test that StartThread delegates to the target env
void DummyThreadFunc(void* arg) {}

TEST_F(EnvWrapperTest_105, StartThreadDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  int dummy_arg = 99;
  EXPECT_CALL(mock_env_,
              StartThread(DummyThreadFunc, static_cast<void*>(&dummy_arg)))
      .Times(1);

  wrapper.StartThread(DummyThreadFunc, &dummy_arg);
}

// Test that GetTestDirectory delegates to the target env
TEST_F(EnvWrapperTest_105, GetTestDirectoryDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  std::string path;
  EXPECT_CALL(mock_env_, GetTestDirectory(&path))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<0>("/tmp/test"),
                                  ::testing::Return(Status::OK())));

  Status s = wrapper.GetTestDirectory(&path);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("/tmp/test", path);
}

// Test that NewLogger delegates to the target env
TEST_F(EnvWrapperTest_105, NewLoggerDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  Logger* logger = nullptr;
  EXPECT_CALL(mock_env_, NewLogger("log_file", &logger))
      .WillOnce(::testing::Return(Status::OK()));

  Status s = wrapper.NewLogger("log_file", &logger);
  EXPECT_TRUE(s.ok());
}

// Test that NowMicros delegates to the target env
TEST_F(EnvWrapperTest_105, NowMicrosDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, NowMicros())
      .WillOnce(::testing::Return(1234567890u));

  uint64_t micros = wrapper.NowMicros();
  EXPECT_EQ(1234567890u, micros);
}

// Test that SleepForMicroseconds delegates to the target env
TEST_F(EnvWrapperTest_105, SleepForMicrosecondsDelegatesToTarget_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, SleepForMicroseconds(500)).Times(1);

  wrapper.SleepForMicroseconds(500);
}

// Test error propagation: NewSequentialFile returns error
TEST_F(EnvWrapperTest_105, NewSequentialFileErrorPropagation_105) {
  EnvWrapper wrapper(&mock_env_);
  SequentialFile* result = nullptr;
  EXPECT_CALL(mock_env_, NewSequentialFile("bad_file", &result))
      .WillOnce(
          ::testing::Return(Status::NotFound("file not found")));

  Status s = wrapper.NewSequentialFile("bad_file", &result);
  EXPECT_TRUE(s.IsNotFound());
}

// Test error propagation: RemoveFile returns error
TEST_F(EnvWrapperTest_105, RemoveFileErrorPropagation_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, RemoveFile("protected_file"))
      .WillOnce(
          ::testing::Return(Status::IOError("permission denied")));

  Status s = wrapper.RemoveFile("protected_file");
  EXPECT_TRUE(s.IsIOError());
}

// Test with empty string filename
TEST_F(EnvWrapperTest_105, EmptyFilenameHandled_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, FileExists(""))
      .WillOnce(::testing::Return(false));

  EXPECT_FALSE(wrapper.FileExists(""));
}

// Test that GetFileSize with zero size
TEST_F(EnvWrapperTest_105, GetFileSizeZero_105) {
  EnvWrapper wrapper(&mock_env_);
  uint64_t size = 999;
  EXPECT_CALL(mock_env_, GetFileSize("empty_file", &size))
      .WillOnce(::testing::DoAll(::testing::SetArgPointee<1>(0u),
                                  ::testing::Return(Status::OK())));

  Status s = wrapper.GetFileSize("empty_file", &size);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(0u, size);
}

// Test NowMicros returns zero (boundary)
TEST_F(EnvWrapperTest_105, NowMicrosZero_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, NowMicros()).WillOnce(::testing::Return(0u));

  EXPECT_EQ(0u, wrapper.NowMicros());
}

// Test NowMicros returns max value (boundary)
TEST_F(EnvWrapperTest_105, NowMicrosMaxValue_105) {
  EnvWrapper wrapper(&mock_env_);
  uint64_t max_val = std::numeric_limits<uint64_t>::max();
  EXPECT_CALL(mock_env_, NowMicros()).WillOnce(::testing::Return(max_val));

  EXPECT_EQ(max_val, wrapper.NowMicros());
}

// Test SleepForMicroseconds with zero
TEST_F(EnvWrapperTest_105, SleepForZeroMicroseconds_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, SleepForMicroseconds(0)).Times(1);

  wrapper.SleepForMicroseconds(0);
}

// Test that GetChildren with empty directory returns empty list
TEST_F(EnvWrapperTest_105, GetChildrenEmptyDir_105) {
  EnvWrapper wrapper(&mock_env_);
  std::vector<std::string> children;
  EXPECT_CALL(mock_env_, GetChildren("empty_dir", &children))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(std::vector<std::string>{}),
          ::testing::Return(Status::OK())));

  Status s = wrapper.GetChildren("empty_dir", &children);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(children.empty());
}

// Test multiple calls to the same method
TEST_F(EnvWrapperTest_105, MultipleCallsToFileExists_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_CALL(mock_env_, FileExists("file_a"))
      .WillOnce(::testing::Return(true));
  EXPECT_CALL(mock_env_, FileExists("file_b"))
      .WillOnce(::testing::Return(false));
  EXPECT_CALL(mock_env_, FileExists("file_c"))
      .WillOnce(::testing::Return(true));

  EXPECT_TRUE(wrapper.FileExists("file_a"));
  EXPECT_FALSE(wrapper.FileExists("file_b"));
  EXPECT_TRUE(wrapper.FileExists("file_c"));
}

// Test that target() is consistent across calls
TEST_F(EnvWrapperTest_105, TargetConsistentAcrossCalls_105) {
  EnvWrapper wrapper(&mock_env_);
  EXPECT_EQ(wrapper.target(), wrapper.target());
  EXPECT_EQ(&mock_env_, wrapper.target());
}

}  // namespace
}  // namespace leveldb
