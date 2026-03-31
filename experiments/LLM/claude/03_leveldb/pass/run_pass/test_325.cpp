#include "gtest/gtest.h"
#include "db/log_reader.h"
#include "db/log_writer.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "util/coding.h"

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

// A simple in-memory WritableFile for the Writer
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

// Helper: write records using Writer, return the resulting string
static std::string WriteRecords(const std::vector<std::string>& records) {
  StringDest dest;
  Writer writer(&dest);
  for (const auto& r : records) {
    writer.AddRecord(Slice(r));
  }
  return dest.contents_;
}

class LogReaderTest_325 : public ::testing::Test {
 protected:
  std::string written_data_;
  TestReporter reporter_;

  void Write(const std::vector<std::string>& records) {
    written_data_ = WriteRecords(records);
  }

  Reader* NewReader(uint64_t initial_offset = 0) {
    auto* source = new StringSource(written_data_);
    return new Reader(source, &reporter_, true, initial_offset);
  }
};

TEST_F(LogReaderTest_325, LastRecordOffsetInitiallyZero_325) {
  // With no records written or read, LastRecordOffset should be 0
  written_data_ = "";
  // Need at least an empty source
  Reader* reader = NewReader();
  EXPECT_EQ(0u, reader->LastRecordOffset());
  delete reader;
}

TEST_F(LogReaderTest_325, ReadSingleRecord_325) {
  Write({"hello"});
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  EXPECT_EQ("hello", record.ToString());
  delete reader;
}

TEST_F(LogReaderTest_325, ReadMultipleRecords_325) {
  Write({"first", "second", "third"});
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;

  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  EXPECT_EQ("first", record.ToString());

  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  EXPECT_EQ("second", record.ToString());

  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  EXPECT_EQ("third", record.ToString());

  // No more records
  EXPECT_FALSE(reader->ReadRecord(&record, &scratch));
  delete reader;
}

TEST_F(LogReaderTest_325, ReadRecordReturnsFalseOnEmpty_325) {
  written_data_ = "";
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  EXPECT_FALSE(reader->ReadRecord(&record, &scratch));
  delete reader;
}

TEST_F(LogReaderTest_325, LastRecordOffsetAfterReadingSingleRecord_325) {
  Write({"hello"});
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  // The first record should start at offset 0
  EXPECT_EQ(0u, reader->LastRecordOffset());
  delete reader;
}

TEST_F(LogReaderTest_325, LastRecordOffsetAfterMultipleRecords_325) {
  Write({"a", "b"});
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;

  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  uint64_t first_offset = reader->LastRecordOffset();

  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  uint64_t second_offset = reader->LastRecordOffset();

  // Second record should be at a higher offset than first
  EXPECT_GT(second_offset, first_offset);
  delete reader;
}

TEST_F(LogReaderTest_325, EmptyRecord_325) {
  Write({""});
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  EXPECT_EQ("", record.ToString());
  EXPECT_EQ(0u, record.size());
  delete reader;
}

TEST_F(LogReaderTest_325, LargeRecord_325) {
  // A record larger than the block size (32KB)
  std::string big(100000, 'x');
  Write({big});
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  EXPECT_EQ(big, record.ToString());
  delete reader;
}

TEST_F(LogReaderTest_325, ManySmallRecords_325) {
  std::vector<std::string> records;
  for (int i = 0; i < 100; i++) {
    records.push_back("record_" + std::to_string(i));
  }
  Write(records);
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  for (int i = 0; i < 100; i++) {
    ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
    EXPECT_EQ("record_" + std::to_string(i), record.ToString());
  }
  EXPECT_FALSE(reader->ReadRecord(&record, &scratch));
  delete reader;
}

TEST_F(LogReaderTest_325, ReadWithInitialOffset_325) {
  // Write two records and then read starting from an offset that
  // should skip the first record
  Write({"first_record", "second_record"});
  Reader* reader_all = NewReader(0);
  Slice record;
  std::string scratch;

  ASSERT_TRUE(reader_all->ReadRecord(&record, &scratch));
  EXPECT_EQ("first_record", record.ToString());

  ASSERT_TRUE(reader_all->ReadRecord(&record, &scratch));
  uint64_t second_offset = reader_all->LastRecordOffset();
  delete reader_all;

  // Now read with initial_offset set to the second record's offset
  Reader* reader_skip = NewReader(second_offset);
  ASSERT_TRUE(reader_skip->ReadRecord(&record, &scratch));
  EXPECT_EQ("second_record", record.ToString());
  delete reader_skip;
}

TEST_F(LogReaderTest_325, CorruptedDataReported_325) {
  Write({"good_record"});
  // Corrupt part of the data
  if (written_data_.size() > 10) {
    written_data_[6] = 0xff;  // corrupt the type or length field
    written_data_[7] = 0xff;
  }
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  // May or may not read successfully, but we check it doesn't crash
  reader->ReadRecord(&record, &scratch);
  // Reporter may have been called due to corruption
  delete reader;
}

TEST_F(LogReaderTest_325, TruncatedDataHandledGracefully_325) {
  Write({"some_data"});
  // Truncate the data
  if (written_data_.size() > 5) {
    written_data_.resize(5);
  }
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  // Should not crash; should return false or report corruption
  bool result = reader->ReadRecord(&record, &scratch);
  EXPECT_FALSE(result);
  delete reader;
}

TEST_F(LogReaderTest_325, MultipleEmptyRecords_325) {
  Write({"", "", ""});
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  for (int i = 0; i < 3; i++) {
    ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
    EXPECT_EQ("", record.ToString());
  }
  EXPECT_FALSE(reader->ReadRecord(&record, &scratch));
  delete reader;
}

TEST_F(LogReaderTest_325, RecordExactlyBlockSize_325) {
  // kBlockSize is 32768, header is 7 bytes, so max payload in one block is 32761
  // Write a record that exactly fills one block's payload
  std::string exact(32768 - 7, 'y');
  Write({exact});
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;
  ASSERT_TRUE(reader->ReadRecord(&record, &scratch));
  EXPECT_EQ(exact, record.ToString());
  delete reader;
}

TEST_F(LogReaderTest_325, LastRecordOffsetConsistency_325) {
  Write({"alpha", "beta", "gamma"});
  Reader* reader = NewReader();
  Slice record;
  std::string scratch;

  std::vector<uint64_t> offsets;
  while (reader->ReadRecord(&record, &scratch)) {
    offsets.push_back(reader->LastRecordOffset());
  }

  ASSERT_EQ(3u, offsets.size());
  // Offsets should be monotonically increasing
  for (size_t i = 1; i < offsets.size(); i++) {
    EXPECT_GT(offsets[i], offsets[i - 1]);
  }
  delete reader;
}

}  // namespace log
}  // namespace leveldb
