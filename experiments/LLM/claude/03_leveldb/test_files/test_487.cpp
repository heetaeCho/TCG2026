#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/log_writer.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "db/log_format.h"

#include <string>
#include <vector>

using namespace leveldb;
using namespace leveldb::log;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::DoAll;

class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

class LogWriterTest_487 : public ::testing::Test {
 protected:
  MockWritableFile mock_file_;
};

// Test basic construction with single argument
TEST_F(LogWriterTest_487, ConstructWithDest_487) {
  Writer writer(&mock_file_);
  // Writer should be constructable without issues
}

// Test construction with dest_length
TEST_F(LogWriterTest_487, ConstructWithDestAndLength_487) {
  Writer writer(&mock_file_, 0);
  // Writer should be constructable with length 0
}

// Test construction with non-zero dest_length
TEST_F(LogWriterTest_487, ConstructWithNonZeroDestLength_487) {
  Writer writer(&mock_file_, 1024);
  // Should handle non-zero offset
}

// Test construction with dest_length that is exactly kBlockSize
TEST_F(LogWriterTest_487, ConstructWithBlockSizeLength_487) {
  Writer writer(&mock_file_, kBlockSize);
  // block_offset_ should be 0 since kBlockSize % kBlockSize == 0
}

// Test construction with dest_length larger than kBlockSize
TEST_F(LogWriterTest_487, ConstructWithLargerThanBlockSize_487) {
  Writer writer(&mock_file_, kBlockSize + 100);
  // block_offset_ should be 100
}

// Test AddRecord with empty slice
TEST_F(LogWriterTest_487, AddRecordEmptySlice_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  Slice empty_slice("");
  Status s = writer.AddRecord(empty_slice);
  EXPECT_TRUE(s.ok());
}

// Test AddRecord with a small record
TEST_F(LogWriterTest_487, AddRecordSmallRecord_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  std::string data = "hello world";
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test AddRecord when Append fails
TEST_F(LogWriterTest_487, AddRecordAppendFails_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::IOError("write error")));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  std::string data = "test data";
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_FALSE(s.ok());
}

// Test AddRecord when Flush fails
TEST_F(LogWriterTest_487, AddRecordFlushFails_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::IOError("flush error")));

  Writer writer(&mock_file_);
  std::string data = "test data";
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_FALSE(s.ok());
}

// Test AddRecord with large record that spans multiple blocks
TEST_F(LogWriterTest_487, AddRecordLargeRecord_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  // Create a record larger than kBlockSize to force fragmentation
  std::string data(kBlockSize * 3, 'x');
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test multiple AddRecord calls
TEST_F(LogWriterTest_487, AddRecordMultipleCalls_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  for (int i = 0; i < 10; i++) {
    std::string data = "record " + std::to_string(i);
    Slice slice(data);
    Status s = writer.AddRecord(slice);
    EXPECT_TRUE(s.ok());
  }
}

// Test AddRecord with record that exactly fills one block (minus header)
TEST_F(LogWriterTest_487, AddRecordExactBlockSize_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  // kHeaderSize is 7 bytes (4 checksum + 2 length + 1 type)
  // A record of size kBlockSize - kHeaderSize should fit exactly in one block
  const int kHeaderSize = 7;
  std::string data(kBlockSize - kHeaderSize, 'a');
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test AddRecord with writer starting at non-zero block offset
TEST_F(LogWriterTest_487, AddRecordWithNonZeroOffset_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_, 100);
  std::string data = "test after offset";
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test AddRecord where the remaining space in the block is less than header size
TEST_F(LogWriterTest_487, AddRecordNearBlockBoundary_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  // Set offset so there's less than kHeaderSize (7 bytes) remaining
  uint64_t offset = kBlockSize - 3;
  Writer writer(&mock_file_, offset);
  std::string data = "near boundary";
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test AddRecord with exactly kHeaderSize remaining in block
TEST_F(LogWriterTest_487, AddRecordExactlyHeaderSizeRemaining_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  const int kHeaderSize = 7;
  uint64_t offset = kBlockSize - kHeaderSize;
  Writer writer(&mock_file_, offset);
  std::string data = "exactly header remaining";
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test that Append is actually called (verifying external interaction)
TEST_F(LogWriterTest_487, AddRecordCallsAppend_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .Times(::testing::AtLeast(1))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  std::string data = "verify append called";
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test that Flush is called
TEST_F(LogWriterTest_487, AddRecordCallsFlush_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .Times(::testing::AtLeast(1))
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  std::string data = "verify flush called";
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test that after a failed write, subsequent writes also fail
TEST_F(LogWriterTest_487, AddRecordSubsequentWriteAfterFailure_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillOnce(Return(Status::IOError("disk full")))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  std::string data1 = "first";
  Status s1 = writer.AddRecord(Slice(data1));
  EXPECT_FALSE(s1.ok());

  // Subsequent record - behavior depends on implementation
  // but we can at least call it
  std::string data2 = "second";
  Status s2 = writer.AddRecord(Slice(data2));
  // Not asserting s2 since behavior after failure is implementation-dependent
}

// Test with a very large record
TEST_F(LogWriterTest_487, AddRecordVeryLargeRecord_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  std::string data(1000000, 'z');  // 1MB record
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test with single byte record
TEST_F(LogWriterTest_487, AddRecordSingleByte_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  std::string data = "x";
  Slice slice(data);
  Status s = writer.AddRecord(slice);
  EXPECT_TRUE(s.ok());
}

// Test that the data written via Append contains the record data
TEST_F(LogWriterTest_487, AddRecordDataIntegrity_487) {
  std::string written_data;
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(DoAll(
          Invoke([&written_data](const Slice& data) {
            written_data.append(data.data(), data.size());
          }),
          Return(Status::OK())));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  std::string record_data = "test record data";
  Status s = writer.AddRecord(Slice(record_data));
  EXPECT_TRUE(s.ok());
  
  // The written data should contain the record data somewhere (after the header)
  EXPECT_NE(written_data.find(record_data), std::string::npos);
}

// Test constructing writer at block boundary
TEST_F(LogWriterTest_487, ConstructAtBlockBoundary_487) {
  Writer writer(&mock_file_, kBlockSize * 5);
  // block_offset_ should be 0
  // Verify by writing a record
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Status s = writer.AddRecord(Slice("at boundary"));
  EXPECT_TRUE(s.ok());
}

// Test record that requires exactly two blocks
TEST_F(LogWriterTest_487, AddRecordSpansTwoBlocks_487) {
  EXPECT_CALL(mock_file_, Append(_))
      .WillRepeatedly(Return(Status::OK()));
  EXPECT_CALL(mock_file_, Flush())
      .WillRepeatedly(Return(Status::OK()));

  Writer writer(&mock_file_);
  // Record slightly larger than one block
  std::string data(kBlockSize, 'b');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
}
