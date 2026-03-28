#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/log_writer.h"
#include "db/log_format.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <cstring>

namespace leveldb {
namespace log {

// Mock WritableFile for testing
class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

// A StringWritableFile that captures all written data
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

class LogWriterTest_345 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that writing an empty record succeeds
TEST_F(LogWriterTest_345, AddEmptyRecord_345) {
  StringWritableFile file;
  Writer writer(&file);
  Status s = writer.AddRecord(Slice("", 0));
  EXPECT_TRUE(s.ok());
  // Should have written a header (7 bytes) even for empty record
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kHeaderSize));
}

// Test that writing a small record succeeds
TEST_F(LogWriterTest_345, AddSmallRecord_345) {
  StringWritableFile file;
  Writer writer(&file);
  std::string data = "hello";
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kHeaderSize + data.size()));
}

// Test that the record type for a small record is kFullType
TEST_F(LogWriterTest_345, SmallRecordIsFullType_345) {
  StringWritableFile file;
  Writer writer(&file);
  std::string data = "hello";
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  // The type byte is at offset 6 in the header
  ASSERT_GE(file.contents_.size(), static_cast<size_t>(kHeaderSize));
  unsigned char type_byte = static_cast<unsigned char>(file.contents_[6]);
  EXPECT_EQ(type_byte, kFullType);
}

// Test writing a record that exactly fills a block (minus header)
TEST_F(LogWriterTest_345, RecordExactlyFillsBlock_345) {
  StringWritableFile file;
  Writer writer(&file);
  size_t data_size = kBlockSize - kHeaderSize;
  std::string data(data_size, 'x');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kBlockSize));
}

// Test writing a record that spans two blocks
TEST_F(LogWriterTest_345, RecordSpansTwoBlocks_345) {
  StringWritableFile file;
  Writer writer(&file);
  size_t data_size = kBlockSize - kHeaderSize + 1;  // one byte more than fits in a single block
  std::string data(data_size, 'y');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  // Should have first fragment header + data + second fragment header + remaining data
  // First block: kHeaderSize + (kBlockSize - kHeaderSize) = kBlockSize
  // Second block: kHeaderSize + 1
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kBlockSize + kHeaderSize + 1));
}

// Test that first fragment has kFirstType and last has kLastType
TEST_F(LogWriterTest_345, TwoBlockRecordTypes_345) {
  StringWritableFile file;
  Writer writer(&file);
  size_t data_size = kBlockSize - kHeaderSize + 1;
  std::string data(data_size, 'z');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());

  // First record type at offset 6
  unsigned char first_type = static_cast<unsigned char>(file.contents_[6]);
  EXPECT_EQ(first_type, kFirstType);

  // Second record starts at offset kBlockSize, type at kBlockSize + 6
  unsigned char second_type = static_cast<unsigned char>(file.contents_[kBlockSize + 6]);
  EXPECT_EQ(second_type, kLastType);
}

// Test writing a record that spans three blocks (has a middle fragment)
TEST_F(LogWriterTest_345, RecordSpansThreeBlocks_345) {
  StringWritableFile file;
  Writer writer(&file);
  size_t data_size = 2 * (kBlockSize - kHeaderSize) + 1;
  std::string data(data_size, 'a');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());

  // First type
  unsigned char first_type = static_cast<unsigned char>(file.contents_[6]);
  EXPECT_EQ(first_type, kFirstType);

  // Middle type at second block
  unsigned char middle_type = static_cast<unsigned char>(file.contents_[kBlockSize + 6]);
  EXPECT_EQ(middle_type, kMiddleType);

  // Last type at third block
  unsigned char last_type = static_cast<unsigned char>(file.contents_[2 * kBlockSize + 6]);
  EXPECT_EQ(last_type, kLastType);
}

// Test writing multiple records
TEST_F(LogWriterTest_345, MultipleSmallRecords_345) {
  StringWritableFile file;
  Writer writer(&file);

  Status s1 = writer.AddRecord(Slice("first"));
  EXPECT_TRUE(s1.ok());

  Status s2 = writer.AddRecord(Slice("second"));
  EXPECT_TRUE(s2.ok());

  Status s3 = writer.AddRecord(Slice("third"));
  EXPECT_TRUE(s3.ok());

  size_t expected_size = 3 * kHeaderSize + 5 + 6 + 5;
  EXPECT_EQ(file.contents_.size(), expected_size);
}

// Test that Append failure is propagated
TEST_F(LogWriterTest_345, AppendFailurePropagated_345) {
  MockWritableFile mock_file;
  Writer writer(&mock_file);

  EXPECT_CALL(mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::IOError("disk full")));

  // We also need to handle Flush potentially being called
  EXPECT_CALL(mock_file, Flush())
      .Times(::testing::AnyNumber())
      .WillRepeatedly(::testing::Return(Status::OK()));

  Status s = writer.AddRecord(Slice("data"));
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// Test the Writer constructor with dest_length (resuming at an offset)
TEST_F(LogWriterTest_345, ConstructorWithOffset_345) {
  StringWritableFile file;
  // Start at an offset that simulates partial block usage
  Writer writer(&file, 100);
  std::string data = "test";
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kHeaderSize + data.size()));
}

// Test when block_offset leaves less than kHeaderSize remaining
// This should trigger padding of the remaining space and starting a new block
TEST_F(LogWriterTest_345, PaddingWhenLessThanHeaderSizeRemains_345) {
  StringWritableFile file;
  // Set offset so only 6 bytes remain (less than kHeaderSize = 7)
  uint64_t offset = kBlockSize - 6;
  Writer writer(&file, offset);

  std::string data = "test";
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());

  // Should have 6 bytes of padding + kHeaderSize + data.size()
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(6 + kHeaderSize + data.size()));
}

// Test when block_offset leaves exactly kHeaderSize remaining
// A record with no data should fit exactly
TEST_F(LogWriterTest_345, ExactlyHeaderSizeRemaining_345) {
  StringWritableFile file;
  uint64_t offset = kBlockSize - kHeaderSize;
  Writer writer(&file, offset);

  // Empty record should fit in the remaining header space
  Status s = writer.AddRecord(Slice("", 0));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kHeaderSize));
}

// Test writing a very large record
TEST_F(LogWriterTest_345, VeryLargeRecord_345) {
  StringWritableFile file;
  Writer writer(&file);
  // 100KB record - spans multiple blocks
  std::string data(100000, 'b');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  // Verify data was written (exact size depends on fragmentation)
  EXPECT_GT(file.contents_.size(), data.size());
}

// Test that failure during multi-fragment write stops further writes
TEST_F(LogWriterTest_345, FailureDuringMultiFragmentWrite_345) {
  MockWritableFile mock_file;
  Writer writer(&mock_file);

  // First Append succeeds (for first fragment header+data), 
  // then Flush succeeds, then second Append fails
  ::testing::InSequence seq;
  EXPECT_CALL(mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(mock_file, Flush())
      .WillOnce(::testing::Return(Status::OK()));
  EXPECT_CALL(mock_file, Append(::testing::_))
      .WillOnce(::testing::Return(Status::IOError("write error")));

  // Record large enough to span two blocks
  size_t data_size = kBlockSize - kHeaderSize + 1;
  std::string data(data_size, 'c');
  Status s = writer.AddRecord(Slice(data));
  EXPECT_FALSE(s.ok());
}

// Test writing exactly one byte
TEST_F(LogWriterTest_345, SingleByteRecord_345) {
  StringWritableFile file;
  Writer writer(&file);
  Status s = writer.AddRecord(Slice("x"));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kHeaderSize + 1));
  unsigned char type_byte = static_cast<unsigned char>(file.contents_[6]);
  EXPECT_EQ(type_byte, kFullType);
}

// Test block boundary: exactly zero leftover after a record
TEST_F(LogWriterTest_345, ZeroLeftoverAfterRecord_345) {
  StringWritableFile file;
  Writer writer(&file);

  // First fill an entire block
  size_t first_data_size = kBlockSize - kHeaderSize;
  std::string data1(first_data_size, 'a');
  Status s1 = writer.AddRecord(Slice(data1));
  EXPECT_TRUE(s1.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kBlockSize));

  // Next record should start at the beginning of next block
  std::string data2 = "next";
  Status s2 = writer.AddRecord(Slice(data2));
  EXPECT_TRUE(s2.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kBlockSize + kHeaderSize + data2.size()));
}

// Test that when leftover is exactly 1, padding is added
TEST_F(LogWriterTest_345, OneByteLeftoverPadding_345) {
  StringWritableFile file;
  Writer writer(&file);

  // Write a record that leaves exactly 1 byte in the block
  // 1 byte leftover means we need data of size: kBlockSize - kHeaderSize - 1
  // After this record: block_offset = kHeaderSize + (kBlockSize - kHeaderSize - 1) = kBlockSize - 1
  // Leftover = kBlockSize - (kBlockSize - 1) = 1, which is < kHeaderSize
  size_t first_data_size = kBlockSize - kHeaderSize - 1;
  std::string data1(first_data_size, 'p');
  Status s1 = writer.AddRecord(Slice(data1));
  EXPECT_TRUE(s1.ok());

  // Now write another record - should pad the 1 byte and start new block
  std::string data2 = "after_pad";
  Status s2 = writer.AddRecord(Slice(data2));
  EXPECT_TRUE(s2.ok());

  // Total: first block data (kBlockSize - 1) + 1 byte padding + kHeaderSize + data2.size()
  size_t expected = (kBlockSize - 1) + 1 + kHeaderSize + data2.size();
  EXPECT_EQ(file.contents_.size(), expected);
}

// Test Writer with dest_length that is exact multiple of kBlockSize
TEST_F(LogWriterTest_345, DestLengthMultipleOfBlockSize_345) {
  StringWritableFile file;
  Writer writer(&file, 3 * kBlockSize);  // block_offset_ should be 0
  std::string data = "aligned";
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kHeaderSize + data.size()));
}

// Test Writer with dest_length = 0
TEST_F(LogWriterTest_345, DestLengthZero_345) {
  StringWritableFile file;
  Writer writer(&file, 0);
  std::string data = "from_zero";
  Status s = writer.AddRecord(Slice(data));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(file.contents_.size(), static_cast<size_t>(kHeaderSize + data.size()));
}

}  // namespace log
}  // namespace leveldb
