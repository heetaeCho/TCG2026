#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

#include <string>
#include <cstring>

namespace leveldb {

// Mock SequentialFile
class MockSequentialFile : public SequentialFile {
 public:
  MOCK_METHOD(Status, Read, (size_t n, Slice* result, char* scratch), (override));
  MOCK_METHOD(Status, Skip, (uint64_t n), (override));
};

// Mock Env
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

// Forward declaration
Status ReadFileToString(Env* env, const std::string& fname, std::string* data);

class ReadFileToStringTest_471 : public ::testing::Test {
 protected:
  MockEnv mock_env_;
  std::string data_;
};

// Test: NewSequentialFile fails, should return error status and data should be empty
TEST_F(ReadFileToStringTest_471, NewSequentialFileFailsReturnsError_471) {
  EXPECT_CALL(mock_env_, NewSequentialFile("nonexistent.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("file not found")));

  Status s = ReadFileToString(&mock_env_, "nonexistent.txt", &data_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_TRUE(data_.empty());
}

// Test: File exists but is empty (Read returns empty slice immediately)
TEST_F(ReadFileToStringTest_471, EmptyFileReturnsEmptyString_471) {
  // We need a MockSequentialFile allocated on the heap since ReadFileToString deletes it
  MockSequentialFile* mock_file = new MockSequentialFile();

  EXPECT_CALL(mock_env_, NewSequentialFile("empty.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](size_t, Slice* result, char*) {
            *result = Slice("", 0);
          }),
          ::testing::Return(Status::OK())));

  Status s = ReadFileToString(&mock_env_, "empty.txt", &data_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data_, "");
}

// Test: File with small content that fits in one read
TEST_F(ReadFileToStringTest_471, SmallFileReadSuccessfully_471) {
  MockSequentialFile* mock_file = new MockSequentialFile();
  const std::string content = "Hello, World!";

  EXPECT_CALL(mock_env_, NewSequentialFile("small.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  ::testing::InSequence seq;

  // First read returns the content
  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([&content](size_t, Slice* result, char* scratch) {
            std::memcpy(scratch, content.data(), content.size());
            *result = Slice(scratch, content.size());
          }),
          ::testing::Return(Status::OK())));

  // Second read returns empty (EOF)
  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](size_t, Slice* result, char*) {
            *result = Slice("", 0);
          }),
          ::testing::Return(Status::OK())));

  Status s = ReadFileToString(&mock_env_, "small.txt", &data_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data_, content);
}

// Test: File requiring multiple reads
TEST_F(ReadFileToStringTest_471, LargeFileMultipleReads_471) {
  MockSequentialFile* mock_file = new MockSequentialFile();

  std::string chunk1(8192, 'A');
  std::string chunk2(4096, 'B');

  EXPECT_CALL(mock_env_, NewSequentialFile("large.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  ::testing::InSequence seq;

  // First read returns full buffer
  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([&chunk1](size_t, Slice* result, char* scratch) {
            std::memcpy(scratch, chunk1.data(), chunk1.size());
            *result = Slice(scratch, chunk1.size());
          }),
          ::testing::Return(Status::OK())));

  // Second read returns partial buffer
  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([&chunk2](size_t, Slice* result, char* scratch) {
            std::memcpy(scratch, chunk2.data(), chunk2.size());
            *result = Slice(scratch, chunk2.size());
          }),
          ::testing::Return(Status::OK())));

  // Third read returns empty (EOF)
  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](size_t, Slice* result, char*) {
            *result = Slice("", 0);
          }),
          ::testing::Return(Status::OK())));

  Status s = ReadFileToString(&mock_env_, "large.txt", &data_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data_.size(), 8192u + 4096u);
  EXPECT_EQ(data_.substr(0, 8192), chunk1);
  EXPECT_EQ(data_.substr(8192), chunk2);
}

// Test: Read returns an error on the first read
TEST_F(ReadFileToStringTest_471, ReadFailsOnFirstRead_471) {
  MockSequentialFile* mock_file = new MockSequentialFile();

  EXPECT_CALL(mock_env_, NewSequentialFile("error.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("read error")));

  Status s = ReadFileToString(&mock_env_, "error.txt", &data_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// Test: Read fails on a subsequent read (after first successful read)
TEST_F(ReadFileToStringTest_471, ReadFailsOnSecondRead_471) {
  MockSequentialFile* mock_file = new MockSequentialFile();
  const std::string content = "partial data";

  EXPECT_CALL(mock_env_, NewSequentialFile("partial_error.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  ::testing::InSequence seq;

  // First read succeeds with some data
  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([&content](size_t, Slice* result, char* scratch) {
            std::memcpy(scratch, content.data(), content.size());
            *result = Slice(scratch, content.size());
          }),
          ::testing::Return(Status::OK())));

  // Second read fails
  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::Return(Status::Corruption("corrupted")));

  Status s = ReadFileToString(&mock_env_, "partial_error.txt", &data_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test: Data is cleared before reading
TEST_F(ReadFileToStringTest_471, DataIsClearedBeforeReading_471) {
  MockSequentialFile* mock_file = new MockSequentialFile();

  data_ = "pre-existing data";

  EXPECT_CALL(mock_env_, NewSequentialFile("clear_test.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](size_t, Slice* result, char*) {
            *result = Slice("", 0);
          }),
          ::testing::Return(Status::OK())));

  Status s = ReadFileToString(&mock_env_, "clear_test.txt", &data_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data_, "");
}

// Test: Data is cleared even when NewSequentialFile fails
TEST_F(ReadFileToStringTest_471, DataIsClearedOnOpenFailure_471) {
  data_ = "old data that should be cleared";

  EXPECT_CALL(mock_env_, NewSequentialFile("no_file.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::NotFound("no such file")));

  Status s = ReadFileToString(&mock_env_, "no_file.txt", &data_);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(data_, "");
}

// Test: File with exactly one buffer size of data
TEST_F(ReadFileToStringTest_471, ExactlyOneBufferSize_471) {
  MockSequentialFile* mock_file = new MockSequentialFile();

  std::string chunk(8192, 'X');

  EXPECT_CALL(mock_env_, NewSequentialFile("exact.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  ::testing::InSequence seq;

  // First read returns exactly 8192 bytes
  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([&chunk](size_t, Slice* result, char* scratch) {
            std::memcpy(scratch, chunk.data(), chunk.size());
            *result = Slice(scratch, chunk.size());
          }),
          ::testing::Return(Status::OK())));

  // Second read returns empty (EOF)
  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](size_t, Slice* result, char*) {
            *result = Slice("", 0);
          }),
          ::testing::Return(Status::OK())));

  Status s = ReadFileToString(&mock_env_, "exact.txt", &data_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data_.size(), 8192u);
  EXPECT_EQ(data_, chunk);
}

// Test: Single byte file
TEST_F(ReadFileToStringTest_471, SingleByteFile_471) {
  MockSequentialFile* mock_file = new MockSequentialFile();

  EXPECT_CALL(mock_env_, NewSequentialFile("one_byte.txt", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  ::testing::InSequence seq;

  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](size_t, Slice* result, char* scratch) {
            scratch[0] = 'Z';
            *result = Slice(scratch, 1);
          }),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](size_t, Slice* result, char*) {
            *result = Slice("", 0);
          }),
          ::testing::Return(Status::OK())));

  Status s = ReadFileToString(&mock_env_, "one_byte.txt", &data_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data_, "Z");
}

// Test: IOError from NewSequentialFile
TEST_F(ReadFileToStringTest_471, IOErrorFromNewSequentialFile_471) {
  EXPECT_CALL(mock_env_, NewSequentialFile("io_error.txt", ::testing::_))
      .WillOnce(::testing::Return(Status::IOError("permission denied")));

  Status s = ReadFileToString(&mock_env_, "io_error.txt", &data_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
  EXPECT_TRUE(data_.empty());
}

// Test: Binary data with null bytes
TEST_F(ReadFileToStringTest_471, BinaryDataWithNullBytes_471) {
  MockSequentialFile* mock_file = new MockSequentialFile();

  EXPECT_CALL(mock_env_, NewSequentialFile("binary.dat", ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>(mock_file),
          ::testing::Return(Status::OK())));

  ::testing::InSequence seq;

  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](size_t, Slice* result, char* scratch) {
            scratch[0] = 'A';
            scratch[1] = '\0';
            scratch[2] = 'B';
            scratch[3] = '\0';
            scratch[4] = 'C';
            *result = Slice(scratch, 5);
          }),
          ::testing::Return(Status::OK())));

  EXPECT_CALL(*mock_file, Read(8192, ::testing::_, ::testing::_))
      .WillOnce(::testing::DoAll(
          ::testing::Invoke([](size_t, Slice* result, char*) {
            *result = Slice("", 0);
          }),
          ::testing::Return(Status::OK())));

  Status s = ReadFileToString(&mock_env_, "binary.dat", &data_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data_.size(), 5u);
  EXPECT_EQ(data_[0], 'A');
  EXPECT_EQ(data_[1], '\0');
  EXPECT_EQ(data_[2], 'B');
  EXPECT_EQ(data_[3], '\0');
  EXPECT_EQ(data_[4], 'C');
}

}  // namespace leveldb
