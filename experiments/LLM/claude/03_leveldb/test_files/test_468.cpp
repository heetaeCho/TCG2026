#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgPointee;
using ::testing::Invoke;

namespace leveldb {

// Forward declare the function under test
static Status DoWriteStringToFile(Env* env, const Slice& data,
                                  const std::string& fname, bool should_sync);

// Mock WritableFile
class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

// Mock Env
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewWritableFile,
              (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(Status, NewSequentialFile,
              (const std::string& fname, SequentialFile** result), (override));
  MOCK_METHOD(Status, NewRandomAccessFile,
              (const std::string& fname, RandomAccessFile** result), (override));
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

// We need to access the static function. Since it's defined as static in env.cc,
// we need to either include it or use a wrapper. For testing purposes, we'll
// use the public wrappers WriteStringToFile / WriteStringToFileSync if available,
// or we'll test via the public API.
// 
// Actually, leveldb provides WriteStringToFile and WriteStringToFileSync as
// public helper functions in env.h that call DoWriteStringToFile internally.
// Let's test through those.

class DoWriteStringToFileTest_468 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
};

// Test: NewWritableFile fails => returns error, no further calls
TEST_F(DoWriteStringToFileTest_468, NewWritableFileFailsReturnsError_468) {
  EXPECT_CALL(mock_env_, NewWritableFile("/test/file", _))
      .WillOnce(Return(Status::IOError("cannot create file")));

  // RemoveFile should NOT be called since NewWritableFile failed
  // (the file pointer is never obtained)
  EXPECT_CALL(mock_env_, RemoveFile(_)).Times(0);

  Status s = WriteStringToFile(&mock_env_, "hello", "/test/file");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// Test: Successful write without sync
TEST_F(DoWriteStringToFileTest_468, SuccessfulWriteNoSync_468) {
  auto* mock_file = new MockWritableFile();

  EXPECT_CALL(mock_env_, NewWritableFile("/test/file", _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(Slice("hello")))
      .WillOnce(Return(Status::OK()));
  // should_sync = false, so Sync should NOT be called
  EXPECT_CALL(*mock_file, Sync()).Times(0);
  EXPECT_CALL(*mock_file, Close()).WillOnce(Return(Status::OK()));

  EXPECT_CALL(mock_env_, RemoveFile(_)).Times(0);

  Status s = WriteStringToFile(&mock_env_, "hello", "/test/file");
  EXPECT_TRUE(s.ok());
}

// Test: Successful write with sync
TEST_F(DoWriteStringToFileTest_468, SuccessfulWriteWithSync_468) {
  auto* mock_file = new MockWritableFile();

  EXPECT_CALL(mock_env_, NewWritableFile("/test/file", _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(Slice("data")))
      .WillOnce(Return(Status::OK()));
  EXPECT_CALL(*mock_file, Sync()).WillOnce(Return(Status::OK()));
  EXPECT_CALL(*mock_file, Close()).WillOnce(Return(Status::OK()));

  EXPECT_CALL(mock_env_, RemoveFile(_)).Times(0);

  Status s = WriteStringToFileSync(&mock_env_, "data", "/test/file");
  EXPECT_TRUE(s.ok());
}

// Test: Append fails => file removed, Sync and Close not called
TEST_F(DoWriteStringToFileTest_468, AppendFailsCleansUp_468) {
  auto* mock_file = new MockWritableFile();

  EXPECT_CALL(mock_env_, NewWritableFile("/test/file", _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(_))
      .WillOnce(Return(Status::IOError("write error")));
  // Since Append failed, Sync and Close should not be called
  EXPECT_CALL(*mock_file, Sync()).Times(0);
  EXPECT_CALL(*mock_file, Close()).Times(0);

  // File should be removed on error
  EXPECT_CALL(mock_env_, RemoveFile("/test/file"))
      .WillOnce(Return(Status::OK()));

  Status s = WriteStringToFile(&mock_env_, "hello", "/test/file");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// Test: Sync fails => file removed
TEST_F(DoWriteStringToFileTest_468, SyncFailsCleansUp_468) {
  auto* mock_file = new MockWritableFile();

  EXPECT_CALL(mock_env_, NewWritableFile("/test/file", _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(_)).WillOnce(Return(Status::OK()));
  EXPECT_CALL(*mock_file, Sync())
      .WillOnce(Return(Status::IOError("sync error")));
  // Close should not be called since Sync failed (s is not ok)
  EXPECT_CALL(*mock_file, Close()).Times(0);

  EXPECT_CALL(mock_env_, RemoveFile("/test/file"))
      .WillOnce(Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, "data", "/test/file");
  EXPECT_FALSE(s.ok());
}

// Test: Close fails => file removed
TEST_F(DoWriteStringToFileTest_468, CloseFailsCleansUp_468) {
  auto* mock_file = new MockWritableFile();

  EXPECT_CALL(mock_env_, NewWritableFile("/test/file", _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(_)).WillOnce(Return(Status::OK()));
  EXPECT_CALL(*mock_file, Close())
      .WillOnce(Return(Status::IOError("close error")));

  EXPECT_CALL(mock_env_, RemoveFile("/test/file"))
      .WillOnce(Return(Status::OK()));

  Status s = WriteStringToFile(&mock_env_, "data", "/test/file");
  EXPECT_FALSE(s.ok());
}

// Test: Empty data write succeeds
TEST_F(DoWriteStringToFileTest_468, EmptyDataWriteSucceeds_468) {
  auto* mock_file = new MockWritableFile();

  EXPECT_CALL(mock_env_, NewWritableFile("/test/empty", _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(Slice("")))
      .WillOnce(Return(Status::OK()));
  EXPECT_CALL(*mock_file, Close()).WillOnce(Return(Status::OK()));

  EXPECT_CALL(mock_env_, RemoveFile(_)).Times(0);

  Status s = WriteStringToFile(&mock_env_, "", "/test/empty");
  EXPECT_TRUE(s.ok());
}

// Test: Large data write succeeds
TEST_F(DoWriteStringToFileTest_468, LargeDataWriteSucceeds_468) {
  auto* mock_file = new MockWritableFile();
  std::string large_data(1024 * 1024, 'x');  // 1MB

  EXPECT_CALL(mock_env_, NewWritableFile("/test/large", _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(_)).WillOnce(Return(Status::OK()));
  EXPECT_CALL(*mock_file, Close()).WillOnce(Return(Status::OK()));

  EXPECT_CALL(mock_env_, RemoveFile(_)).Times(0);

  Status s = WriteStringToFile(&mock_env_, large_data, "/test/large");
  EXPECT_TRUE(s.ok());
}

// Test: Append succeeds, no sync requested, Close fails => RemoveFile called
TEST_F(DoWriteStringToFileTest_468, NoSyncCloseFailRemovesFile_468) {
  auto* mock_file = new MockWritableFile();

  EXPECT_CALL(mock_env_, NewWritableFile("/test/f", _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(_)).WillOnce(Return(Status::OK()));
  EXPECT_CALL(*mock_file, Sync()).Times(0);  // no sync requested
  EXPECT_CALL(*mock_file, Close())
      .WillOnce(Return(Status::IOError("close fail")));

  EXPECT_CALL(mock_env_, RemoveFile("/test/f"))
      .WillOnce(Return(Status::OK()));

  Status s = WriteStringToFile(&mock_env_, "test", "/test/f");
  EXPECT_FALSE(s.ok());
}

// Test: Verify that the correct filename is passed throughout
TEST_F(DoWriteStringToFileTest_468, CorrectFilenamePassedThrough_468) {
  auto* mock_file = new MockWritableFile();
  const std::string fname = "/some/path/myfile.dat";

  EXPECT_CALL(mock_env_, NewWritableFile(fname, _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(_))
      .WillOnce(Return(Status::IOError("fail")));

  // Verify RemoveFile is called with the same filename
  EXPECT_CALL(mock_env_, RemoveFile(fname))
      .WillOnce(Return(Status::OK()));

  Status s = WriteStringToFile(&mock_env_, "data", fname);
  EXPECT_FALSE(s.ok());
}

// Test: Append fails with sync requested => Sync not called, file removed
TEST_F(DoWriteStringToFileTest_468, AppendFailsWithSyncRequested_468) {
  auto* mock_file = new MockWritableFile();

  EXPECT_CALL(mock_env_, NewWritableFile("/test/sync", _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Append(_))
      .WillOnce(Return(Status::Corruption("corrupt")));
  EXPECT_CALL(*mock_file, Sync()).Times(0);
  EXPECT_CALL(*mock_file, Close()).Times(0);

  EXPECT_CALL(mock_env_, RemoveFile("/test/sync"))
      .WillOnce(Return(Status::OK()));

  Status s = WriteStringToFileSync(&mock_env_, "data", "/test/sync");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

}  // namespace leveldb
