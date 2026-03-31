#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <string>
#include <vector>

namespace leveldb {

// Forward declaration of the function under test
Status WriteStringToFileSync(Env* env, const Slice& data, const std::string& fname);

// Mock WritableFile
class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

// Mock Env to control behavior of NewWritableFile and other methods
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

class WriteStringToFileSyncTest_470 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
};

// Test normal operation: writing data to a file successfully
TEST_F(WriteStringToFileSyncTest_470, WritesDataSuccessfully_470) {
  MockWritableFile* mock_file = new MockWritableFile();
  std::string filename = "/tmp/test_file.txt";
  std::string data = "Hello, World!";

  EXPECT_CALL(mock_env_, NewWritableFile(filename, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Sync())
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, Slice(data), filename);
  EXPECT_TRUE(s.ok());
}

// Test when NewWritableFile fails
TEST_F(WriteStringToFileSyncTest_470, FailsWhenNewWritableFileFails_470) {
  std::string filename = "/tmp/nonexistent_dir/test_file.txt";
  std::string data = "Hello";

  EXPECT_CALL(mock_env_, NewWritableFile(filename, ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("Cannot create file")));

  // RemoveFile might be called on failure
  EXPECT_CALL(mock_env_, RemoveFile(filename))
      .Times(::testing::AnyNumber())
      .WillRepeatedly(::testing::Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, Slice(data), filename);
  EXPECT_FALSE(s.ok());
}

// Test when Append fails
TEST_F(WriteStringToFileSyncTest_470, FailsWhenAppendFails_470) {
  MockWritableFile* mock_file = new MockWritableFile();
  std::string filename = "/tmp/test_file.txt";
  std::string data = "Hello, World!";

  EXPECT_CALL(mock_env_, NewWritableFile(filename, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::IOError("Write error")));

  // Sync might still be called or might not, depending on implementation
  EXPECT_CALL(*mock_file, Sync())
      .Times(::testing::AnyNumber())
      .WillRepeatedly(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  // RemoveFile might be called on failure
  EXPECT_CALL(mock_env_, RemoveFile(filename))
      .Times(::testing::AnyNumber())
      .WillRepeatedly(::testing::Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, Slice(data), filename);
  EXPECT_FALSE(s.ok());
}

// Test when Sync fails
TEST_F(WriteStringToFileSyncTest_470, FailsWhenSyncFails_470) {
  MockWritableFile* mock_file = new MockWritableFile();
  std::string filename = "/tmp/test_file.txt";
  std::string data = "Hello, World!";

  EXPECT_CALL(mock_env_, NewWritableFile(filename, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Sync())
      .WillOnce(::testing::Return(Status::IOError("Sync error")));

  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  // RemoveFile might be called on failure
  EXPECT_CALL(mock_env_, RemoveFile(filename))
      .Times(::testing::AnyNumber())
      .WillRepeatedly(::testing::Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, Slice(data), filename);
  EXPECT_FALSE(s.ok());
}

// Test when Close fails
TEST_F(WriteStringToFileSyncTest_470, FailsWhenCloseFails_470) {
  MockWritableFile* mock_file = new MockWritableFile();
  std::string filename = "/tmp/test_file.txt";
  std::string data = "Hello, World!";

  EXPECT_CALL(mock_env_, NewWritableFile(filename, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Sync())
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::IOError("Close error")));

  // RemoveFile might be called on failure
  EXPECT_CALL(mock_env_, RemoveFile(filename))
      .Times(::testing::AnyNumber())
      .WillRepeatedly(::testing::Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, Slice(data), filename);
  EXPECT_FALSE(s.ok());
}

// Test with empty data
TEST_F(WriteStringToFileSyncTest_470, WritesEmptyDataSuccessfully_470) {
  MockWritableFile* mock_file = new MockWritableFile();
  std::string filename = "/tmp/empty_file.txt";
  std::string data = "";

  EXPECT_CALL(mock_env_, NewWritableFile(filename, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Sync())
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, Slice(data), filename);
  EXPECT_TRUE(s.ok());
}

// Test with large data
TEST_F(WriteStringToFileSyncTest_470, WritesLargeDataSuccessfully_470) {
  MockWritableFile* mock_file = new MockWritableFile();
  std::string filename = "/tmp/large_file.txt";
  std::string data(1024 * 1024, 'A');  // 1 MB of data

  EXPECT_CALL(mock_env_, NewWritableFile(filename, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Sync())
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, Slice(data), filename);
  EXPECT_TRUE(s.ok());
}

// Test using real Env with actual file system
class WriteStringToFileSyncRealEnvTest_470 : public ::testing::Test {
 protected:
  Env* env_;
  std::string test_dir_;

  void SetUp() override {
    env_ = Env::Default();
    ASSERT_TRUE(env_->GetTestDirectory(&test_dir_).ok());
  }
};

TEST_F(WriteStringToFileSyncRealEnvTest_470, RealEnvWriteAndVerify_470) {
  std::string fname = test_dir_ + "/write_sync_test_470.txt";
  std::string data = "test data for sync write";

  Status s = WriteStringToFileSync(env_, Slice(data), fname);
  ASSERT_TRUE(s.ok());

  // Verify by reading the file back
  SequentialFile* file = nullptr;
  s = env_->NewSequentialFile(fname, &file);
  ASSERT_TRUE(s.ok());

  char buf[256];
  Slice result;
  s = file->Read(data.size(), &result, buf);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(data, result.ToString());

  delete file;

  // Clean up
  env_->RemoveFile(fname);
}

TEST_F(WriteStringToFileSyncRealEnvTest_470, RealEnvWriteEmptyFile_470) {
  std::string fname = test_dir_ + "/write_sync_empty_470.txt";
  std::string data = "";

  Status s = WriteStringToFileSync(env_, Slice(data), fname);
  ASSERT_TRUE(s.ok());

  uint64_t file_size = 0;
  s = env_->GetFileSize(fname, &file_size);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(0u, file_size);

  // Clean up
  env_->RemoveFile(fname);
}

// Verify that Sync is actually called (distinguishing from non-sync write)
TEST_F(WriteStringToFileSyncTest_470, SyncIsCalled_470) {
  MockWritableFile* mock_file = new MockWritableFile();
  std::string filename = "/tmp/sync_verify.txt";
  std::string data = "sync me";

  EXPECT_CALL(mock_env_, NewWritableFile(filename, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));

  // Sync MUST be called exactly once for WriteStringToFileSync
  EXPECT_CALL(*mock_file, Sync())
      .Times(1)
      .WillOnce(::testing::Return(Status::OK()));

  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, Slice(data), filename);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
