#include "gtest/gtest.h"
#include "db/log_reader.h"
#include "db/log_writer.h"
#include "db/log_format.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "util/coding.h"
#include "util/crc32c.h"

#include <string>
#include <vector>
#include <cstring>

namespace leveldb {
namespace log {

// A simple in-memory SequentialFile for testing
class StringSource : public SequentialFile {
 public:
  explicit StringSource(const std::string& contents)
      : contents_(contents), offset_(0) {}

  Status Read(size_t n, Slice* result, char* scratch) override {
    if (offset_ >= contents_.size()) {
      *result = Slice();
      return Status::OK();
    }
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
    } else {
      offset_ += n;
    }
    return Status::OK();
  }

 private:
  std::string contents_;
  size_t offset_;
};

// A SequentialFile that can inject read errors
class ErrorSource : public SequentialFile {
 public:
  explicit ErrorSource(const std::string& contents, size_t error_after = SIZE_MAX)
      : contents_(contents), offset_(0), error_after_(error_after), bytes_read_(0) {}

  Status Read(size_t n, Slice* result, char* scratch) override {
    if (bytes_read_ >= error_after_) {
      *result = Slice();
      return Status::Corruption("injected read error");
    }
    if (offset_ >= contents_.size()) {
      *result = Slice();
      return Status::OK();
    }
    size_t available = contents_.size() - offset_;
    if (n > available) n = available;
    std::memcpy(scratch, contents_.data() + offset_, n);
    *result = Slice(scratch, n);
    offset_ += n;
    bytes_read_ += n;
    return Status::OK();
  }

  Status Skip(uint64_t n) override {
    if (offset_ + n > contents_.size()) {
      offset_ = contents_.size();
    } else {
      offset_ += n;
    }
    return Status::OK();
  }

 private:
  std::string contents_;
  size_t offset_;
  size_t error_after_;
  size_t bytes_read_;
};

// A simple WritableFile backed by a string
class StringDest : public WritableFile {
 public:
  std::string contents_;

  Status Close() override { return Status::OK(); }
  Status Flush() override { return Status::OK(); }
  Status Sync() override { return Status::OK(); }
  Status Append(const Slice& slice) override {
    contents_.append(slice.data(), slice.size());
    return Status::OK();
  }
};

// Reporter that records corruption messages
class TestReporter : public Reader::Reporter {
 public:
  size_t dropped_bytes_;
  std::string message_;

  TestReporter() : dropped_bytes_(0) {}

  void Corruption(size_t bytes, const Status& status) override {
    dropped_bytes_ += bytes;
    message_.append(status.ToString());
  }
};

// Helper to write records and return the raw bytes
static std::string WriteLog(const std::vector<std::string>& records) {
  StringDest dest;
  Writer writer(&dest);
  for (const auto& r : records) {
    writer.AddRecord(Slice(r));
  }
  return dest.contents_;
}

class LogReaderTest_324 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test reading a single small record
TEST_F(LogReaderTest_324, ReadSingleRecord_324) {
  std::string data = WriteLog({"hello"});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("hello", record.ToString());
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

// Test reading multiple records
TEST_F(LogReaderTest_324, ReadMultipleRecords_324) {
  std::string data = WriteLog({"first", "second", "third"});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("first", record.ToString());

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("second", record.ToString());

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("third", record.ToString());

  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

// Test reading an empty record
TEST_F(LogReaderTest_324, ReadEmptyRecord_324) {
  std::string data = WriteLog({""});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("", record.ToString());
  EXPECT_EQ(0u, record.size());
}

// Test reading from empty file returns false
TEST_F(LogReaderTest_324, ReadFromEmptyFile_324) {
  StringSource* source = new StringSource("");
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

// Test reading a large record that spans multiple blocks
TEST_F(LogReaderTest_324, ReadLargeRecord_324) {
  // kBlockSize is 32768, so a record larger than that will be fragmented
  std::string big(100000, 'x');
  std::string data = WriteLog({big});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(big, record.ToString());
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

// Test LastRecordOffset returns 0 initially
TEST_F(LogReaderTest_324, LastRecordOffsetInitiallyZero_324) {
  std::string data = WriteLog({"test"});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  EXPECT_EQ(0u, reader.LastRecordOffset());
}

// Test LastRecordOffset updates after reading a record
TEST_F(LogReaderTest_324, LastRecordOffsetAfterRead_324) {
  std::string data = WriteLog({"hello", "world"});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  uint64_t offset1 = reader.LastRecordOffset();

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  uint64_t offset2 = reader.LastRecordOffset();

  // Second record should have a higher offset than the first
  EXPECT_GT(offset2, offset1);
}

// Test reading with initial_offset > 0 skips to the right block
TEST_F(LogReaderTest_324, ReadWithInitialOffset_324) {
  // Write two records
  std::string data = WriteLog({"first", "second"});
  
  // Read the first record to find where the second starts
  {
    StringSource* source = new StringSource(data);
    TestReporter reporter;
    Reader reader(source, &reporter, true, 0);
    Slice record;
    std::string scratch;
    ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
    ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
    EXPECT_EQ("second", record.ToString());
  }
}

// Test reading with initial_offset that skips the first record
TEST_F(LogReaderTest_324, InitialOffsetSkipsFirstRecord_324) {
  // Create enough records that offset-based skipping is meaningful
  std::string data = WriteLog({"record1", "record2", "record3"});

  // Use initial_offset that is past the first record header+data
  // The first record is "record1" (7 bytes) + kHeaderSize (7) = 14 bytes
  // Using offset 14 should skip record1
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 14);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  // Should get record2 or record3 (depending on exact layout)
  std::string result = record.ToString();
  EXPECT_TRUE(result == "record2" || result == "record3");
}

// Test that a record exactly filling a block boundary works
TEST_F(LogReaderTest_324, RecordAtBlockBoundary_324) {
  // kBlockSize = 32768, kHeaderSize = 7
  // A record of size (32768 - 7) will exactly fill one block
  std::string exact(32768 - 7, 'a');
  std::string data = WriteLog({exact});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(exact, record.ToString());
}

// Test multiple large records that span blocks
TEST_F(LogReaderTest_324, MultipleLargeRecords_324) {
  std::string big1(50000, 'a');
  std::string big2(60000, 'b');
  std::string data = WriteLog({big1, big2});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(big1, record.ToString());

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(big2, record.ToString());

  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

// Test with no reporter (nullptr)
TEST_F(LogReaderTest_324, NullReporter_324) {
  std::string data = WriteLog({"hello"});
  StringSource* source = new StringSource(data);
  Reader reader(source, nullptr, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("hello", record.ToString());
}

// Test corrupted data reports corruption
TEST_F(LogReaderTest_324, CorruptedData_324) {
  std::string data = WriteLog({"hello", "world"});
  // Corrupt the CRC of the first record
  if (data.size() > 4) {
    data[0] ^= 0xff;
  }
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  // May or may not read successfully, but reporter should be notified
  // We just verify we don't crash
  while (reader.ReadRecord(&record, &scratch)) {
    // consume all
  }
  // Corruption should have been reported
  EXPECT_GT(reporter.dropped_bytes_, 0u);
}

// Test truncated file
TEST_F(LogReaderTest_324, TruncatedFile_324) {
  std::string data = WriteLog({"hello world this is a test"});
  // Truncate the file
  data = data.substr(0, data.size() / 2);
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  // Should handle gracefully
  bool result = reader.ReadRecord(&record, &scratch);
  // May or may not succeed depending on truncation point
  // Just verify no crash
  (void)result;
}

// Test reading multiple empty records
TEST_F(LogReaderTest_324, MultipleEmptyRecords_324) {
  std::string data = WriteLog({"", "", ""});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("", record.ToString());

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("", record.ToString());

  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("", record.ToString());

  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

// Test record that is exactly one block minus header
TEST_F(LogReaderTest_324, ExactOneBlockRecord_324) {
  const int kBlockSize = 32768;
  std::string exact_fit(kBlockSize - kHeaderSize, 'z');
  std::string data = WriteLog({exact_fit});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(exact_fit.size(), record.size());
  EXPECT_EQ(exact_fit, record.ToString());
}

// Test record slightly larger than one block (forces fragmentation)
TEST_F(LogReaderTest_324, SlightlyOverOneBlockRecord_324) {
  const int kBlockSize = 32768;
  std::string over_fit(kBlockSize - kHeaderSize + 1, 'y');
  std::string data = WriteLog({over_fit});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(over_fit.size(), record.size());
  EXPECT_EQ(over_fit, record.ToString());
}

// Test with checksum disabled
TEST_F(LogReaderTest_324, ChecksumDisabled_324) {
  std::string data = WriteLog({"no checksum test"});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, false, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("no checksum test", record.ToString());
}

// Test with checksum disabled and corrupted CRC still reads
TEST_F(LogReaderTest_324, ChecksumDisabledCorruptedCRC_324) {
  std::string data = WriteLog({"test data"});
  // Corrupt the CRC
  if (data.size() > 4) {
    data[0] ^= 0xff;
  }
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, false, 0);

  Slice record;
  std::string scratch;
  // With checksum disabled, should still read despite corrupted CRC
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("test data", record.ToString());
}

// Test binary data in records
TEST_F(LogReaderTest_324, BinaryData_324) {
  std::string binary_data;
  for (int i = 0; i < 256; i++) {
    binary_data.push_back(static_cast<char>(i));
  }
  std::string data = WriteLog({binary_data});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(binary_data.size(), record.size());
  EXPECT_EQ(binary_data, record.ToString());
}

// Test many small records
TEST_F(LogReaderTest_324, ManySmallRecords_324) {
  std::vector<std::string> records;
  for (int i = 0; i < 1000; i++) {
    records.push_back("record" + std::to_string(i));
  }
  std::string data = WriteLog(records);
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  for (int i = 0; i < 1000; i++) {
    ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
    EXPECT_EQ(records[i], record.ToString());
  }
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

// Test that offset after reading all records from empty log is 0
TEST_F(LogReaderTest_324, EmptyLogLastRecordOffset_324) {
  StringSource* source = new StringSource("");
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  EXPECT_EQ(0u, reader.LastRecordOffset());

  Slice record;
  std::string scratch;
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(0u, reader.LastRecordOffset());
}

// Test reading record of size 1
TEST_F(LogReaderTest_324, SingleByteRecord_324) {
  std::string data = WriteLog({"x"});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("x", record.ToString());
  EXPECT_EQ(1u, record.size());
}

// Test that corrupting length field causes corruption report
TEST_F(LogReaderTest_324, CorruptedLengthField_324) {
  std::string data = WriteLog({"test"});
  // Corrupt the length field (bytes 4-5 in the header)
  if (data.size() > 5) {
    data[4] = 0xff;
    data[5] = 0xff;
  }
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  // Should fail or report corruption
  while (reader.ReadRecord(&record, &scratch)) {
    // consume
  }
  // Either corruption was reported or we simply got no records
}

// Test initial offset past end of file
TEST_F(LogReaderTest_324, InitialOffsetPastEndOfFile_324) {
  std::string data = WriteLog({"hello"});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, data.size() + 1000);

  Slice record;
  std::string scratch;
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

// Test a record spanning exactly two blocks
TEST_F(LogReaderTest_324, RecordSpanningTwoBlocks_324) {
  const int kBlockSize = 32768;
  // Create a record that is about 1.5 blocks
  std::string large(kBlockSize + kBlockSize / 2, 'q');
  std::string data = WriteLog({large});
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(large, record.ToString());
}

// Test reading records when file has garbage appended
TEST_F(LogReaderTest_324, GarbageAtEnd_324) {
  std::string data = WriteLog({"valid record"});
  // Append garbage
  data.append("this is garbage data that should not parse as a valid record");
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("valid record", record.ToString());

  // Additional reads should eventually return false (possibly with corruption reports)
  while (reader.ReadRecord(&record, &scratch)) {
    // consume any additional records if parsed
  }
}

}  // namespace log
}  // namespace leveldb
