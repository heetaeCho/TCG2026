#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/filename.h"
#include "leveldb/env.h"
#include "leveldb/status.h"
#include "util/env_posix_test_helper.h"

#include <string>
#include <cstdint>

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::DoAll;
using ::testing::SetArgPointee;
using ::testing::HasSubstr;

namespace leveldb {

// Mock Env for testing
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewSequentialFile, (const std::string& fname, SequentialFile** result), (override));
  MOCK_METHOD(Status, NewRandomAccessFile, (const std::string& fname, RandomAccessFile** result), (override));
  MOCK_METHOD(Status, NewWritableFile, (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(Status, NewAppendableFile, (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(bool, FileExists, (const std::string& fname), (override));
  MOCK_METHOD(Status, GetChildren, (const std::string& dir, std::vector<std::string>* result), (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, DeleteFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, DeleteDir, (const std::string& dirname), (override));
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

// A helper writable file that captures written content
class StringWritableFile : public WritableFile {
 public:
  std::string contents_;
  Status Append(const Slice& data) override {
    contents_.append(data.data(), data.size());
    return Status::OK();
  }
  Status Close() override { return Status::OK(); }
  Status Flush() override { return Status::OK(); }
  Status Sync() override { return Status::OK(); }
};

class SetCurrentFileTest_337 : public ::testing::Test {
 protected:
  MockEnv env_;
  std::string dbname_ = "/test/db";
};

// Test that SetCurrentFile succeeds when both WriteStringToFileSync and RenameFile succeed
TEST_F(SetCurrentFileTest_337, SuccessfulSetCurrentFile_337) {
  uint64_t descriptor_number = 42;

  // We need to handle the write (NewWritableFile for the temp file) and rename
  // Since WriteStringToFileSync internally calls NewWritableFile, we mock that
  StringWritableFile* writable_file = new StringWritableFile();
  
  EXPECT_CALL(env_, NewWritableFile(_, _))
      .WillOnce(DoAll(SetArgPointee<1>(writable_file), Return(Status::OK())));
  
  std::string current_file = dbname_ + "/CURRENT";
  EXPECT_CALL(env_, RenameFile(_, current_file))
      .WillOnce(Return(Status::OK()));
  
  // RemoveFile should NOT be called on success
  EXPECT_CALL(env_, RemoveFile(_)).Times(0);

  Status s = SetCurrentFile(&env_, dbname_, descriptor_number);
  EXPECT_TRUE(s.ok());
}

// Test that SetCurrentFile cleans up temp file when RenameFile fails
TEST_F(SetCurrentFileTest_337, RenameFailsCleansUpTempFile_337) {
  uint64_t descriptor_number = 7;
  
  StringWritableFile* writable_file = new StringWritableFile();
  
  EXPECT_CALL(env_, NewWritableFile(_, _))
      .WillOnce(DoAll(SetArgPointee<1>(writable_file), Return(Status::OK())));
  
  EXPECT_CALL(env_, RenameFile(_, _))
      .WillOnce(Return(Status::IOError("rename failed")));
  
  // Should attempt to remove the temp file on failure
  std::string tmp_file = TempFileName(dbname_, descriptor_number);
  EXPECT_CALL(env_, RemoveFile(tmp_file))
      .WillOnce(Return(Status::OK()));

  Status s = SetCurrentFile(&env_, dbname_, descriptor_number);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// Test that SetCurrentFile cleans up temp file when WriteStringToFileSync fails
TEST_F(SetCurrentFileTest_337, WriteFailsCleansUpTempFile_337) {
  uint64_t descriptor_number = 100;
  
  EXPECT_CALL(env_, NewWritableFile(_, _))
      .WillOnce(Return(Status::IOError("write failed")));
  
  // RenameFile should not be called
  EXPECT_CALL(env_, RenameFile(_, _)).Times(0);
  
  // Should attempt to remove the temp file
  std::string tmp_file = TempFileName(dbname_, descriptor_number);
  EXPECT_CALL(env_, RemoveFile(tmp_file))
      .WillOnce(Return(Status::OK()));

  Status s = SetCurrentFile(&env_, dbname_, descriptor_number);
  EXPECT_FALSE(s.ok());
}

// Test with descriptor number 1 (boundary: small descriptor number)
TEST_F(SetCurrentFileTest_337, SmallDescriptorNumber_337) {
  uint64_t descriptor_number = 1;
  
  StringWritableFile* writable_file = new StringWritableFile();
  
  EXPECT_CALL(env_, NewWritableFile(_, _))
      .WillOnce(DoAll(SetArgPointee<1>(writable_file), Return(Status::OK())));
  
  EXPECT_CALL(env_, RenameFile(_, _))
      .WillOnce(Return(Status::OK()));

  Status s = SetCurrentFile(&env_, dbname_, descriptor_number);
  EXPECT_TRUE(s.ok());
}

// Test with large descriptor number
TEST_F(SetCurrentFileTest_337, LargeDescriptorNumber_337) {
  uint64_t descriptor_number = 999999999;
  
  StringWritableFile* writable_file = new StringWritableFile();
  
  EXPECT_CALL(env_, NewWritableFile(_, _))
      .WillOnce(DoAll(SetArgPointee<1>(writable_file), Return(Status::OK())));
  
  EXPECT_CALL(env_, RenameFile(_, _))
      .WillOnce(Return(Status::OK()));

  Status s = SetCurrentFile(&env_, dbname_, descriptor_number);
  EXPECT_TRUE(s.ok());
}

// Test that the correct temp file name is used
TEST_F(SetCurrentFileTest_337, CorrectTempFileName_337) {
  uint64_t descriptor_number = 5;
  std::string expected_tmp = TempFileName(dbname_, descriptor_number);
  
  StringWritableFile* writable_file = new StringWritableFile();
  
  // Verify the temp file name passed to NewWritableFile
  EXPECT_CALL(env_, NewWritableFile(expected_tmp, _))
      .WillOnce(DoAll(SetArgPointee<1>(writable_file), Return(Status::OK())));
  
  std::string expected_current = CurrentFileName(dbname_);
  EXPECT_CALL(env_, RenameFile(expected_tmp, expected_current))
      .WillOnce(Return(Status::OK()));

  Status s = SetCurrentFile(&env_, dbname_, descriptor_number);
  EXPECT_TRUE(s.ok());
}

// Test that the correct CURRENT file path is used as rename target
TEST_F(SetCurrentFileTest_337, CorrectCurrentFileName_337) {
  uint64_t descriptor_number = 10;
  std::string expected_current = CurrentFileName(dbname_);
  
  StringWritableFile* writable_file = new StringWritableFile();
  
  EXPECT_CALL(env_, NewWritableFile(_, _))
      .WillOnce(DoAll(SetArgPointee<1>(writable_file), Return(Status::OK())));
  
  EXPECT_CALL(env_, RenameFile(_, expected_current))
      .WillOnce(Return(Status::OK()));

  Status s = SetCurrentFile(&env_, dbname_, descriptor_number);
  EXPECT_TRUE(s.ok());
}

// Test with a different dbname
TEST_F(SetCurrentFileTest_337, DifferentDbName_337) {
  std::string other_dbname = "/another/path/mydb";
  uint64_t descriptor_number = 3;
  
  std::string expected_tmp = TempFileName(other_dbname, descriptor_number);
  std::string expected_current = CurrentFileName(other_dbname);
  
  StringWritableFile* writable_file = new StringWritableFile();
  
  EXPECT_CALL(env_, NewWritableFile(expected_tmp, _))
      .WillOnce(DoAll(SetArgPointee<1>(writable_file), Return(Status::OK())));
  
  EXPECT_CALL(env_, RenameFile(expected_tmp, expected_current))
      .WillOnce(Return(Status::OK()));

  Status s = SetCurrentFile(&env_, other_dbname, descriptor_number);
  EXPECT_TRUE(s.ok());
}

// Test that RemoveFile is called even if it also fails (when rename fails)
TEST_F(SetCurrentFileTest_337, RemoveFileFailsAfterRenameFails_337) {
  uint64_t descriptor_number = 20;
  
  StringWritableFile* writable_file = new StringWritableFile();
  
  EXPECT_CALL(env_, NewWritableFile(_, _))
      .WillOnce(DoAll(SetArgPointee<1>(writable_file), Return(Status::OK())));
  
  EXPECT_CALL(env_, RenameFile(_, _))
      .WillOnce(Return(Status::IOError("rename error")));
  
  // RemoveFile also fails, but the original error should be returned
  EXPECT_CALL(env_, RemoveFile(_))
      .WillOnce(Return(Status::IOError("remove error")));

  Status s = SetCurrentFile(&env_, dbname_, descriptor_number);
  EXPECT_FALSE(s.ok());
}

}  // namespace leveldb
