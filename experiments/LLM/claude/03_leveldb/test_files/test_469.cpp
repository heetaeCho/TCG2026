#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <string>
#include <vector>

namespace leveldb {

// Forward declaration of the function under test
Status WriteStringToFile(Env* env, const Slice& data, const std::string& fname);

// Mock WritableFile for testing
class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

// Mock Env to control file creation behavior
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

class WriteStringToFileTest_469 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
};

// Test: WriteStringToFile with normal data succeeds when env operations succeed
TEST_F(WriteStringToFileTest_469, NormalWrite_469) {
  MockWritableFile* mock_file = new MockWritableFile();
  
  EXPECT_CALL(mock_env_, NewWritableFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));
  
  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  std::string data = "hello world";
  Status s = WriteStringToFile(&mock_env_, Slice(data), "/tmp/test_file");
  EXPECT_TRUE(s.ok());
}

// Test: WriteStringToFile fails when NewWritableFile fails
TEST_F(WriteStringToFileTest_469, FailOnFileCreation_469) {
  EXPECT_CALL(mock_env_, NewWritableFile(::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("cannot create file")));

  std::string data = "hello world";
  Status s = WriteStringToFile(&mock_env_, Slice(data), "/tmp/test_file");
  EXPECT_FALSE(s.ok());
}

// Test: WriteStringToFile fails when Append fails
TEST_F(WriteStringToFileTest_469, FailOnAppend_469) {
  MockWritableFile* mock_file = new MockWritableFile();
  
  EXPECT_CALL(mock_env_, NewWritableFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));
  
  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::IOError("write error")));
  
  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));
  
  // When Append fails, the file might still need to be cleaned up
  EXPECT_CALL(mock_env_, RemoveFile(::testing::_))
      .Times(::testing::AnyNumber())
      .WillRepeatedly(::testing::Return(Status::OK()));

  std::string data = "hello world";
  Status s = WriteStringToFile(&mock_env_, Slice(data), "/tmp/test_file");
  EXPECT_FALSE(s.ok());
}

// Test: WriteStringToFile fails when Close fails
TEST_F(WriteStringToFileTest_469, FailOnClose_469) {
  MockWritableFile* mock_file = new MockWritableFile();
  
  EXPECT_CALL(mock_env_, NewWritableFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));
  
  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::IOError("close error")));
  
  EXPECT_CALL(mock_env_, RemoveFile(::testing::_))
      .Times(::testing::AnyNumber())
      .WillRepeatedly(::testing::Return(Status::OK()));

  std::string data = "hello world";
  Status s = WriteStringToFile(&mock_env_, Slice(data), "/tmp/test_file");
  EXPECT_FALSE(s.ok());
}

// Test: WriteStringToFile with empty data
TEST_F(WriteStringToFileTest_469, EmptyData_469) {
  MockWritableFile* mock_file = new MockWritableFile();
  
  EXPECT_CALL(mock_env_, NewWritableFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));
  
  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  Status s = WriteStringToFile(&mock_env_, Slice(""), "/tmp/test_file");
  EXPECT_TRUE(s.ok());
}

// Test: WriteStringToFile with large data
TEST_F(WriteStringToFileTest_469, LargeData_469) {
  MockWritableFile* mock_file = new MockWritableFile();
  
  EXPECT_CALL(mock_env_, NewWritableFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));
  
  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  std::string large_data(1024 * 1024, 'x');  // 1MB of data
  Status s = WriteStringToFile(&mock_env_, Slice(large_data), "/tmp/test_large_file");
  EXPECT_TRUE(s.ok());
}

// Test: WriteStringToFile verifies the filename is passed correctly
TEST_F(WriteStringToFileTest_469, CorrectFilenamePassedToEnv_469) {
  MockWritableFile* mock_file = new MockWritableFile();
  std::string expected_fname = "/specific/path/to/file.txt";
  
  EXPECT_CALL(mock_env_, NewWritableFile(expected_fname, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));
  
  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  Status s = WriteStringToFile(&mock_env_, Slice("data"), expected_fname);
  EXPECT_TRUE(s.ok());
}

// Test: WriteStringToFile with data containing null bytes
TEST_F(WriteStringToFileTest_469, DataWithNullBytes_469) {
  MockWritableFile* mock_file = new MockWritableFile();
  
  EXPECT_CALL(mock_env_, NewWritableFile(::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));
  
  EXPECT_CALL(*mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  
  EXPECT_CALL(*mock_file, Close())
      .WillOnce(::testing::Return(Status::OK()));

  std::string data_with_nulls("hello\0world", 11);
  Status s = WriteStringToFile(&mock_env_, Slice(data_with_nulls), "/tmp/null_file");
  EXPECT_TRUE(s.ok());
}

// Integration test: Use the default Env to write and then read back
TEST_F(WriteStringToFileTest_469, IntegrationWithDefaultEnv_469) {
  Env* env = Env::Default();
  std::string test_dir;
  ASSERT_TRUE(env->GetTestDirectory(&test_dir).ok());
  
  std::string fname = test_dir + "/write_string_test_469";
  std::string data = "test data for integration test 469";
  
  Status s = WriteStringToFile(env, Slice(data), fname);
  ASSERT_TRUE(s.ok());
  
  // Verify by reading back
  SequentialFile* seq_file = nullptr;
  s = env->NewSequentialFile(fname, &seq_file);
  ASSERT_TRUE(s.ok());
  
  char buf[256];
  Slice result;
  s = seq_file->Read(data.size(), &result, buf);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(result.ToString(), data);
  
  delete seq_file;
  env->RemoveFile(fname);
}

// Integration test: Empty string with default Env
TEST_F(WriteStringToFileTest_469, IntegrationEmptyString_469) {
  Env* env = Env::Default();
  std::string test_dir;
  ASSERT_TRUE(env->GetTestDirectory(&test_dir).ok());
  
  std::string fname = test_dir + "/write_empty_string_test_469";
  
  Status s = WriteStringToFile(env, Slice(""), fname);
  ASSERT_TRUE(s.ok());
  
  uint64_t file_size;
  s = env->GetFileSize(fname, &file_size);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(file_size, 0u);
  
  env->RemoveFile(fname);
}

}  // namespace leveldb
