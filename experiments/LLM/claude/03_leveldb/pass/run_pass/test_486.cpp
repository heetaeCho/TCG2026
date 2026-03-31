#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/log_writer.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "db/log_format.h"

#include <string>
#include <vector>
#include <cstring>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

namespace leveldb {

class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

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

class LogWriterTest_486 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Writer can be constructed with a WritableFile
TEST_F(LogWriterTest_486, ConstructWriter_486) {
  StringWritableFile file;
  log::Writer writer(&file);
  // Construction should succeed without crashing
}

// Test that Writer can be constructed with a dest_length parameter
TEST_F(LogWriterTest_486, ConstructWriterWithDestLength_486) {
  StringWritableFile file;
  log::Writer writer(&file, 0);
  // Construction should succeed without crashing
}

// Test that Writer with non-zero dest_length can be constructed
TEST_F(LogWriterTest_486, ConstructWriterWithNonZeroDestLength_486) {
  StringWritableFile file;
  log::Writer writer(&file, 12345);
  // Construction should succeed
}

// Test AddRecord with an empty slice
TEST_F(LogWriterTest_486, AddRecordEmptySlice_486) {
  StringWritableFile file;
  log::Writer writer(&file);
  Status s = writer.AddRecord(Slice());
  EXPECT_TRUE(s.ok());
  // Even an empty record should produce a header
  EXPECT_GT(file.contents_.size(), 0u);
}

// Test AddRecord with a small record
TEST_F(LogWriterTest_486, AddRecordSmallRecord_486) {
  StringWritableFile file;
  log::Writer writer(&file);
  Status s = writer.AddRecord(Slice("hello"));
  EXPECT_TRUE(s.ok());
  // Header is 7 bytes, data is 5 bytes
  EXPECT_GE(file.contents_.size(), 12u);
}

// Test AddRecord with multiple small records
TEST_F(LogWriterTest_486, AddRecordMultipleSmallRecords_486) {
  StringWritableFile file;
  log::Writer writer(&file);

  Status s1 = writer.AddRecord(Slice("first"));
  EXPECT_TRUE(s1.ok());

  Status s2 = writer.AddRecord(Slice("second"));
  EXPECT_TRUE(s2.ok());

  Status s3 = writer.AddRecord(Slice("third"));
  EXPECT_TRUE(s3.ok());

  // All records should have been written
  EXPECT_GT(file.contents_.size(), 0u);
}

// Test AddRecord with a record that is exactly the block size minus header
TEST_F(LogWriterTest_486, AddRecordExactlyOneBlock_486) {
  StringWritableFile file;
  log::Writer writer(&file);

  // kBlockSize is 32768, header is 7 bytes
  // So max data in one block is 32768 - 7 = 32761
  const int kHeaderSize = 7;
  const int kBlockSize = 32768;
  std::string data(kBlockSize - kHeaderSize, 'x');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kBlockSize));
}

// Test AddRecord with a large record that spans multiple blocks
TEST_F(LogWriterTest_486, AddRecordLargeRecordSpansBlocks_486) {
  StringWritableFile file;
  log::Writer writer(&file);

  // Create a record larger than one block
  const int kBlockSize = 32768;
  std::string data(kBlockSize * 3, 'y');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  // The output should span multiple blocks
  EXPECT_GT(file.contents_.size(), static_cast<size_t>(kBlockSize));
}

// Test AddRecord returns error when Append fails
TEST_F(LogWriterTest_486, AddRecordAppendFails_486) {
  MockWritableFile mock_file;
  log::Writer writer(&mock_file);

  EXPECT_CALL(mock_file, Append(_))
      .WillRepeatedly(Return(Status::IOError("write failed")));
  EXPECT_CALL(mock_file, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Status s = writer.AddRecord(Slice("test data"));
  EXPECT_FALSE(s.ok());
}

// Test AddRecord returns error when Flush fails
TEST_F(LogWriterTest_486, AddRecordFlushFails_486) {
  MockWritableFile mock_file;
  log::Writer writer(&mock_file);

  EXPECT_CALL(mock_file, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file, Flush())
      .WillRepeatedly(Return(Status::IOError("flush failed")));

  Status s = writer.AddRecord(Slice("test data"));
  EXPECT_FALSE(s.ok());
}

// Test that Append is called with correct data for a simple record
TEST_F(LogWriterTest_486, AddRecordCallsAppendAndFlush_486) {
  MockWritableFile mock_file;
  log::Writer writer(&mock_file);

  EXPECT_CALL(mock_file, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Status s = writer.AddRecord(Slice("hello world"));
  EXPECT_TRUE(s.ok());
}

// Test Writer with dest_length that causes block_offset to be non-zero
TEST_F(LogWriterTest_486, WriterWithOffsetInBlock_486) {
  StringWritableFile file;
  // dest_length of 100 means block_offset_ = 100 % 32768 = 100
  log::Writer writer(&file, 100);
  Status s = writer.AddRecord(Slice("data"));
  EXPECT_TRUE(s.ok());
  EXPECT_GT(file.contents_.size(), 0u);
}

// Test Writer with dest_length that is exactly a block boundary
TEST_F(LogWriterTest_486, WriterAtBlockBoundary_486) {
  StringWritableFile file;
  const int kBlockSize = 32768;
  log::Writer writer(&file, kBlockSize);
  Status s = writer.AddRecord(Slice("data at boundary"));
  EXPECT_TRUE(s.ok());
}

// Test Writer when there are only 6 bytes left in block (less than header size)
TEST_F(LogWriterTest_486, WriterNearEndOfBlock_486) {
  StringWritableFile file;
  const int kBlockSize = 32768;
  const int kHeaderSize = 7;
  // Set offset so only 6 bytes remain (less than header)
  uint64_t dest_length = kBlockSize - 6;
  log::Writer writer(&file, dest_length);
  Status s = writer.AddRecord(Slice("test"));
  EXPECT_TRUE(s.ok());
  // Should have padded the remaining 6 bytes and started on a new block
  EXPECT_GE(file.contents_.size(), static_cast<size_t>(6 + kHeaderSize + 4));
}

// Test Writer when there are exactly 7 bytes left (exactly header size)
TEST_F(LogWriterTest_486, WriterExactlyHeaderBytesLeft_486) {
  StringWritableFile file;
  const int kBlockSize = 32768;
  const int kHeaderSize = 7;
  uint64_t dest_length = kBlockSize - kHeaderSize;
  log::Writer writer(&file, dest_length);
  Status s = writer.AddRecord(Slice("data"));
  EXPECT_TRUE(s.ok());
}

// Test AddRecord with a single byte
TEST_F(LogWriterTest_486, AddRecordSingleByte_486) {
  StringWritableFile file;
  log::Writer writer(&file);
  Status s = writer.AddRecord(Slice("a"));
  EXPECT_TRUE(s.ok());
  // Header (7) + data (1) = 8 bytes
  EXPECT_GE(file.contents_.size(), 8u);
}

// Test many small records to fill multiple blocks
TEST_F(LogWriterTest_486, AddManySmallRecords_486) {
  StringWritableFile file;
  log::Writer writer(&file);

  for (int i = 0; i < 10000; i++) {
    Status s = writer.AddRecord(Slice("rec"));
    EXPECT_TRUE(s.ok());
  }
  // Each record is 7 (header) + 3 (data) = 10 bytes
  // 10000 records should produce significant output
  EXPECT_GT(file.contents_.size(), 100000u);
}

// Test record that is exactly two blocks minus two headers
TEST_F(LogWriterTest_486, AddRecordExactlyTwoBlocks_486) {
  StringWritableFile file;
  log::Writer writer(&file);

  const int kBlockSize = 32768;
  const int kHeaderSize = 7;
  // A record that spans exactly two blocks
  std::string data(2 * (kBlockSize - kHeaderSize), 'z');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
}

// Test that after a failed write, subsequent writes also report errors
TEST_F(LogWriterTest_486, SubsequentWritesAfterFailure_486) {
  MockWritableFile mock_file;
  log::Writer writer(&mock_file);

  // First call to Append fails
  EXPECT_CALL(mock_file, Append(_))
      .WillOnce(Return(Status::IOError("disk full")))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Status s1 = writer.AddRecord(Slice("first"));
  EXPECT_FALSE(s1.ok());

  // Second write - behavior may vary, but test it
  Status s2 = writer.AddRecord(Slice("second"));
  // After an error, the writer might continue to fail
  // We just verify it doesn't crash
}

// Test AddRecord with a very large record (1MB)
TEST_F(LogWriterTest_486, AddRecordVeryLarge_486) {
  StringWritableFile file;
  log::Writer writer(&file);

  std::string data(1024 * 1024, 'A');  // 1MB
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  EXPECT_GT(file.contents_.size(), 1024u * 1024u);
}

// Test dest_length that is a large multiple of block size
TEST_F(LogWriterTest_486, WriterWithLargeDestLength_486) {
  StringWritableFile file;
  const int kBlockSize = 32768;
  log::Writer writer(&file, static_cast<uint64_t>(kBlockSize) * 1000);
  // block_offset_ should be 0 since it's an exact multiple
  Status s = writer.AddRecord(Slice("after many blocks"));
  EXPECT_TRUE(s.ok());
}

// Test dest_length with remainder
TEST_F(LogWriterTest_486, WriterWithDestLengthRemainder_486) {
  StringWritableFile file;
  const int kBlockSize = 32768;
  log::Writer writer(&file, static_cast<uint64_t>(kBlockSize) * 5 + 500);
  Status s = writer.AddRecord(Slice("with offset 500"));
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
