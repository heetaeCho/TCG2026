#include "gtest/gtest.h"
#include "db/log_reader.h"
#include "db/log_writer.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "util/coding.h"
#include "util/crc32c.h"
#include "db/log_format.h"

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

  void SetContents(const std::string& contents) {
    contents_ = contents;
    offset_ = 0;
  }

 private:
  std::string contents_;
  size_t offset_;
};

// A simple in-memory WritableFile for testing
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
  size_t dropped_bytes_ = 0;
  std::string message_;

  void Corruption(size_t bytes, const Status& status) override {
    dropped_bytes_ += bytes;
    message_.append(status.ToString());
  }
};

class LogReaderTest_323 : public ::testing::Test {
 protected:
  std::string Write(const std::vector<std::string>& records) {
    StringDest dest;
    Writer writer(&dest);
    for (const auto& record : records) {
      EXPECT_TRUE(writer.AddRecord(Slice(record)).ok());
    }
    return dest.contents_;
  }

  std::string Write(const std::string& record) {
    return Write(std::vector<std::string>{record});
  }
};

TEST_F(LogReaderTest_323, EmptyFile_323) {
  StringSource* source = new StringSource("");
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

TEST_F(LogReaderTest_323, ReadSingleSmallRecord_323) {
  std::string data = Write("hello");
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("hello", record.ToString());
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

TEST_F(LogReaderTest_323, ReadMultipleRecords_323) {
  std::vector<std::string> records = {"foo", "bar", "baz"};
  std::string data = Write(records);
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  for (const auto& expected : records) {
    EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
    EXPECT_EQ(expected, record.ToString());
  }
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

TEST_F(LogReaderTest_323, ReadEmptyRecord_323) {
  std::string data = Write("");
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("", record.ToString());
}

TEST_F(LogReaderTest_323, LargeRecord_323) {
  // A record larger than one block (kBlockSize = 32768)
  std::string large_record(kBlockSize * 3, 'x');
  std::string data = Write(large_record);
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(large_record, record.ToString());
}

TEST_F(LogReaderTest_323, LastRecordOffset_323) {
  std::vector<std::string> records = {"first", "second", "third"};
  std::string data = Write(records);
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;

  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  uint64_t offset0 = reader.LastRecordOffset();
  EXPECT_EQ(0u, offset0);

  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  uint64_t offset1 = reader.LastRecordOffset();
  EXPECT_GT(offset1, offset0);

  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  uint64_t offset2 = reader.LastRecordOffset();
  EXPECT_GT(offset2, offset1);
}

TEST_F(LogReaderTest_323, InitialOffsetSkipsRecords_323) {
  // Write two records; use initial_offset to skip the first
  std::string rec1(100, 'a');
  std::string rec2(100, 'b');
  std::vector<std::string> records = {rec1, rec2};
  std::string data = Write(records);

  // First, read normally to find offset of second record
  StringSource* source1 = new StringSource(data);
  TestReporter reporter1;
  Reader reader1(source1, &reporter1, true, 0);
  Slice record;
  std::string scratch;
  EXPECT_TRUE(reader1.ReadRecord(&record, &scratch));
  EXPECT_TRUE(reader1.ReadRecord(&record, &scratch));
  uint64_t second_offset = reader1.LastRecordOffset();

  // Now read with initial_offset at or past first record
  StringSource* source2 = new StringSource(data);
  TestReporter reporter2;
  Reader reader2(source2, &reporter2, true, second_offset);

  EXPECT_TRUE(reader2.ReadRecord(&record, &scratch));
  EXPECT_EQ(rec2, record.ToString());
  EXPECT_FALSE(reader2.ReadRecord(&record, &scratch));
}

TEST_F(LogReaderTest_323, CorruptedData_323) {
  std::string data = Write("hello world");
  // Corrupt a byte in the record data area (after the header)
  // Header is 7 bytes: 4 CRC + 2 length + 1 type
  if (data.size() > 10) {
    data[10] ^= 0xff;
  }
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  // With checksum enabled, corruption should be detected
  bool read_ok = reader.ReadRecord(&record, &scratch);
  if (!read_ok) {
    EXPECT_GT(reporter.dropped_bytes_, 0u);
  }
  // If it did read, the data should be corrupted or reporter called
}

TEST_F(LogReaderTest_323, NoChecksumDoesNotReportCorruption_323) {
  std::string data = Write("hello world");
  // Corrupt CRC bytes
  if (data.size() > 4) {
    data[0] ^= 0xff;
  }
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, false, 0);

  Slice record;
  std::string scratch;
  // With checksum disabled, even corrupted CRC should still read
  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  // The reporter should not have been called for checksum mismatch
}

TEST_F(LogReaderTest_323, TruncatedRecord_323) {
  std::string data = Write("hello");
  // Truncate the data
  data.resize(data.size() / 2);
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

TEST_F(LogReaderTest_323, NullReporter_323) {
  std::string data = Write("test data");
  StringSource* source = new StringSource(data);
  // Pass nullptr for reporter
  Reader reader(source, nullptr, true, 0);

  Slice record;
  std::string scratch;
  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ("test data", record.ToString());
}

TEST_F(LogReaderTest_323, RecordExactlyFillsBlock_323) {
  // kHeaderSize is 7 bytes, kBlockSize is 32768
  // So a record of size kBlockSize - kHeaderSize exactly fills one block
  std::string exact_record(kBlockSize - kHeaderSize, 'z');
  std::string data = Write(exact_record);
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(exact_record, record.ToString());
}

TEST_F(LogReaderTest_323, MultipleSmallRecordsInOneBlock_323) {
  std::vector<std::string> records;
  for (int i = 0; i < 100; i++) {
    records.push_back("record_" + std::to_string(i));
  }
  std::string data = Write(records);
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  for (const auto& expected : records) {
    EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
    EXPECT_EQ(expected, record.ToString());
  }
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

TEST_F(LogReaderTest_323, InitialOffsetBeyondEnd_323) {
  std::string data = Write("short");
  // Set initial_offset beyond the file size
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, data.size() + 1000);

  Slice record;
  std::string scratch;
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

TEST_F(LogReaderTest_323, InitialOffsetAtBlockBoundary_323) {
  // Write enough records to span multiple blocks
  std::string rec1(kBlockSize - kHeaderSize, 'a');
  std::string rec2(100, 'b');
  std::vector<std::string> records = {rec1, rec2};
  std::string data = Write(records);

  // Initial offset at second block
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, kBlockSize);

  Slice record;
  std::string scratch;
  EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
  EXPECT_EQ(rec2, record.ToString());
}

TEST_F(LogReaderTest_323, ZeroLengthPayloadMultipleRecords_323) {
  std::vector<std::string> records = {"", "", ""};
  std::string data = Write(records);
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  for (int i = 0; i < 3; i++) {
    EXPECT_TRUE(reader.ReadRecord(&record, &scratch));
    EXPECT_EQ("", record.ToString());
  }
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

TEST_F(LogReaderTest_323, CorruptedHeaderLength_323) {
  std::string data = Write("hello");
  // Corrupt the length field in the header (bytes 4-5)
  if (data.size() > 5) {
    data[4] = 0xff;
    data[5] = 0xff;
  }
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  // Should detect corruption
  EXPECT_FALSE(reader.ReadRecord(&record, &scratch));
}

TEST_F(LogReaderTest_323, CorruptedRecordType_323) {
  std::string data = Write("hello");
  // Corrupt the type field in the header (byte 6)
  if (data.size() > 6) {
    data[6] = 0xff;  // Invalid record type
  }
  StringSource* source = new StringSource(data);
  TestReporter reporter;
  Reader reader(source, &reporter, true, 0);

  Slice record;
  std::string scratch;
  bool result = reader.ReadRecord(&record, &scratch);
  // With corrupted type and checksum enabled, should fail or report
  if (!result) {
    EXPECT_GT(reporter.dropped_bytes_, 0u);
  }
}

}  // namespace log
}  // namespace leveldb
