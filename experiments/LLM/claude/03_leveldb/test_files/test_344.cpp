#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/log_writer.h"
#include "db/log_reader.h"
#include "db/log_format.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "util/crc32c.h"

#include <string>
#include <vector>
#include <cstdint>

namespace leveldb {
namespace log {

// A simple in-memory writable file for testing
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

// A simple in-memory sequential file for reading back
class StringSequentialFile : public SequentialFile {
 public:
  std::string contents_;
  size_t offset_;

  explicit StringSequentialFile(const std::string& contents)
      : contents_(contents), offset_(0) {}

  Status Read(size_t n, Slice* result, char* scratch) override {
    size_t available = contents_.size() - offset_;
    if (n > available) n = available;
    std::memcpy(scratch, contents_.data() + offset_, n);
    *result = Slice(scratch, n);
    offset_ += n;
    return Status::OK();
  }

  Status Skip(uint64_t n) override {
    if (offset_ + n > contents_.size()) {
      offset_ = contents_.size();
      return Status::NotFound("skip past end");
    }
    offset_ += n;
    return Status::OK();
  }
};

// An error-injecting writable file
class ErrorWritableFile : public WritableFile {
 public:
  int append_count_;
  int error_after_;  // Return error after this many successful appends

  ErrorWritableFile(int error_after)
      : append_count_(0), error_after_(error_after) {}

  Status Append(const Slice& data) override {
    if (append_count_ >= error_after_) {
      return Status::IOError("injected error");
    }
    append_count_++;
    return Status::OK();
  }

  Status Close() override { return Status::OK(); }
  Status Flush() override { return Status::OK(); }
  Status Sync() override { return Status::OK(); }
};

// Mock reporter for Reader
class MockReporter : public Reader::Reporter {
 public:
  std::vector<size_t> dropped_bytes_;
  std::vector<Status> statuses_;

  void Corruption(size_t bytes, const Status& status) override {
    dropped_bytes_.push_back(bytes);
    statuses_.push_back(status);
  }
};

class LogWriterTest_344 : public ::testing::Test {
 protected:
  StringWritableFile* dest_file_;
  Writer* writer_;

  void SetUp() override {
    dest_file_ = new StringWritableFile();
    writer_ = new Writer(dest_file_);
  }

  void TearDown() override {
    delete writer_;
    delete dest_file_;
  }

  // Helper to read back records from the written data
  std::vector<std::string> ReadRecords(const std::string& data) {
    std::vector<std::string> records;
    StringSequentialFile* source = new StringSequentialFile(data);
    MockReporter reporter;
    Reader reader(source, &reporter, true, 0);
    std::string scratch;
    Slice record;
    while (reader.ReadRecord(&record, &scratch)) {
      records.push_back(record.ToString());
    }
    delete source;
    return records;
  }
};

TEST_F(LogWriterTest_344, WriteEmptyRecord_344) {
  Status s = writer_->AddRecord(Slice(""));
  ASSERT_TRUE(s.ok());
  ASSERT_FALSE(dest_file_->contents_.empty());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], "");
}

TEST_F(LogWriterTest_344, WriteSingleSmallRecord_344) {
  std::string data = "hello world";
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], data);
}

TEST_F(LogWriterTest_344, WriteMultipleRecords_344) {
  std::vector<std::string> inputs = {"first", "second", "third"};
  for (const auto& input : inputs) {
    Status s = writer_->AddRecord(Slice(input));
    ASSERT_TRUE(s.ok());
  }

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), inputs.size());
  for (size_t i = 0; i < inputs.size(); i++) {
    EXPECT_EQ(records[i], inputs[i]);
  }
}

TEST_F(LogWriterTest_344, WriteLargeRecord_344) {
  // Write a record larger than a single block (32KB)
  std::string large_data(100000, 'x');
  Status s = writer_->AddRecord(Slice(large_data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], large_data);
}

TEST_F(LogWriterTest_344, WriteRecordExactlyBlockSize_344) {
  // kBlockSize is 32768, header is 7 bytes
  // A record that fills exactly one block: data size = 32768 - 7 = 32761
  std::string data(32761, 'a');
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], data);
}

TEST_F(LogWriterTest_344, WriteRecordOneByteOverBlock_344) {
  // Data that is one byte more than fits in a single block
  std::string data(32762, 'b');
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], data);
}

TEST_F(LogWriterTest_344, WriteManySmallRecords_344) {
  const int kNumRecords = 1000;
  for (int i = 0; i < kNumRecords; i++) {
    std::string data = "record_" + std::to_string(i);
    Status s = writer_->AddRecord(Slice(data));
    ASSERT_TRUE(s.ok());
  }

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), static_cast<size_t>(kNumRecords));
  for (int i = 0; i < kNumRecords; i++) {
    EXPECT_EQ(records[i], "record_" + std::to_string(i));
  }
}

TEST_F(LogWriterTest_344, WriteVeryLargeRecord_344) {
  // Multiple blocks worth of data
  std::string data(1000000, 'z');
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], data);
}

TEST_F(LogWriterTest_344, WriteWithInitialOffset_344) {
  // Test Writer with a dest_length (pre-existing data offset)
  delete writer_;
  delete dest_file_;

  dest_file_ = new StringWritableFile();
  // Simulate writing some initial data before constructing writer with offset
  writer_ = new Writer(dest_file_, 0);

  std::string data = "test with offset constructor";
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], data);
}

TEST_F(LogWriterTest_344, WriteRecordBinaryData_344) {
  // Test with binary data including null bytes
  std::string data;
  data.resize(256);
  for (int i = 0; i < 256; i++) {
    data[i] = static_cast<char>(i);
  }
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], data);
}

TEST_F(LogWriterTest_344, WriteSingleByteRecord_344) {
  std::string data(1, 'A');
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], data);
}

TEST_F(LogWriterTest_344, WriteRecordThatSpansThreeBlocks_344) {
  // 3 * 32768 = 98304, minus headers. Use something that clearly spans 3+ blocks
  std::string data(70000, 'c');
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], data);
}

TEST_F(LogWriterTest_344, ErrorOnWrite_344) {
  // Test that IO errors are propagated
  ErrorWritableFile* error_file = new ErrorWritableFile(0);  // fail immediately
  Writer error_writer(error_file);

  Status s = error_writer.AddRecord(Slice("data"));
  EXPECT_FALSE(s.ok());

  delete error_file;
}

TEST_F(LogWriterTest_344, ErrorOnWriteLargeRecord_344) {
  // Allow first append but fail on second (for multi-fragment records)
  ErrorWritableFile* error_file = new ErrorWritableFile(1);
  Writer error_writer(error_file);

  // Large enough to require multiple fragments
  std::string large_data(100000, 'y');
  Status s = error_writer.AddRecord(Slice(large_data));
  EXPECT_FALSE(s.ok());

  delete error_file;
}

TEST_F(LogWriterTest_344, WriteRecordHeaderBoundary_344) {
  // Fill up a block so that exactly kHeaderSize (7) bytes remain,
  // which should cause a trailer of zeros
  // First record: 32761 bytes of data fills exactly one block (32761 + 7 = 32768)
  std::string first_record(32761, 'f');
  Status s = writer_->AddRecord(Slice(first_record));
  ASSERT_TRUE(s.ok());

  // Second record should start at the beginning of a new block
  std::string second_record = "next block";
  s = writer_->AddRecord(Slice(second_record));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 2u);
  EXPECT_EQ(records[0], first_record);
  EXPECT_EQ(records[1], second_record);
}

TEST_F(LogWriterTest_344, WriteRecordLeavingSixBytesInBlock_344) {
  // Leave exactly 6 bytes (less than header size) at end of block
  // Record data size: 32768 - 7 - 1 = 32760, leaving 1 byte for next.
  // Actually we want to leave 6 bytes: data = 32768 - 7 - 6 = 32755
  std::string first_record(32755, 'g');
  Status s = writer_->AddRecord(Slice(first_record));
  ASSERT_TRUE(s.ok());

  // The remaining 6 bytes < kHeaderSize, so they should be zero-padded
  std::string second_record = "after padding";
  s = writer_->AddRecord(Slice(second_record));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 2u);
  EXPECT_EQ(records[0], first_record);
  EXPECT_EQ(records[1], second_record);
}

TEST_F(LogWriterTest_344, DestLengthAlignedToBlockBoundary_344) {
  delete writer_;
  delete dest_file_;

  dest_file_ = new StringWritableFile();
  // dest_length at a block boundary
  writer_ = new Writer(dest_file_, 32768);

  std::string data = "aligned start";
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), 1u);
  EXPECT_EQ(records[0], data);
}

TEST_F(LogWriterTest_344, DestLengthMidBlock_344) {
  delete writer_;
  delete dest_file_;

  dest_file_ = new StringWritableFile();
  // dest_length mid-block
  writer_ = new Writer(dest_file_, 1000);

  std::string data = "mid block record";
  Status s = writer_->AddRecord(Slice(data));
  ASSERT_TRUE(s.ok());
  // We can't easily read this back without the preceding data,
  // but at least verify the write succeeded
  EXPECT_FALSE(dest_file_->contents_.empty());
}

TEST_F(LogWriterTest_344, MultipleRecordsFillingMultipleBlocks_344) {
  // Write records of varying sizes
  std::vector<std::string> inputs;
  inputs.push_back(std::string(10, 'a'));
  inputs.push_back(std::string(32000, 'b'));
  inputs.push_back(std::string(50000, 'c'));
  inputs.push_back(std::string(1, 'd'));
  inputs.push_back(std::string(100000, 'e'));

  for (const auto& input : inputs) {
    Status s = writer_->AddRecord(Slice(input));
    ASSERT_TRUE(s.ok());
  }

  auto records = ReadRecords(dest_file_->contents_);
  ASSERT_EQ(records.size(), inputs.size());
  for (size_t i = 0; i < inputs.size(); i++) {
    EXPECT_EQ(records[i], inputs[i]);
  }
}

}  // namespace log
}  // namespace leveldb
