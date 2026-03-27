// File: log_reader_readrecord_test_324.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

using ::testing::_;
using ::testing::Invoke;
using ::testing::StrictMock;

namespace leveldb {

// ---- Minimal stubs to satisfy the Reader interface ----
class Status {
 public:
  Status() : msg_("") {}
  explicit Status(const std::string& m) : msg_(m) {}
  static Status Corruption(const std::string& m) { return Status(m); }
  std::string ToString() const { return msg_; }
 private:
  std::string msg_;
};

class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }
  void clear() { data_ = ""; size_ = 0; }
  std::string ToString() const { return std::string(data_, size_); }
 private:
  const char* data_;
  size_t size_;
};

class SequentialFile {
 public:
  virtual ~SequentialFile() = default;
  // Matches LevelDB’s typical signature.
  virtual Status Read(size_t n, Slice* result, char* scratch) = 0;
};

// Reporter interface used by Reader via ReportCorruption/ReportDrop.
struct Reporter {
  virtual ~Reporter() = default;
  virtual void Corruption(size_t bytes, const Status& status) = 0;
};

namespace log {
constexpr int kHeaderSize = 4 + 2 + 1;
constexpr size_t kBlockSize = 32768;

enum RecordType {
  kZeroType  = 0,
  kFullType  = 1,
  kFirstType = 2,
  kMiddleType= 3,
  kLastType  = 4,
};

class Reader {
 public:
  Reader(SequentialFile* file, Reporter* reporter, bool checksum, uint64_t initial_offset);
  Reader(const Reader&) = delete;
  Reader& operator=(const Reader&) = delete;
  ~Reader();

  bool ReadRecord(Slice* record, std::string* scratch);
  uint64_t LastRecordOffset();

 private:
  bool SkipToInitialBlock();
  unsigned int ReadPhysicalRecord(Slice* result);
  void ReportCorruption(uint64_t bytes, const char* reason);
  void ReportDrop(uint64_t bytes, const Status& reason);

  // … real members exist in production (not needed here)
};

}  // namespace log
}  // namespace leveldb

// ---- Test doubles (external collaborators) ----
namespace {

using namespace leveldb;
using namespace leveldb::log;

// A tiny in-memory sequential file feeding the Reader.
class StringSequentialFile : public SequentialFile {
 public:
  explicit StringSequentialFile(std::string data) : data_(std::move(data)), pos_(0) {}

  Status Read(size_t n, Slice* result, char* scratch) override {
    // Return up to n bytes from current position.
    const size_t rem = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t to_read = (n < rem) ? n : rem;
    if (to_read > 0) {
      std::memcpy(scratch, data_.data() + pos_, to_read);
      *result = Slice(scratch, to_read);
      pos_ += to_read;
      return Status();
    } else {
      // EOF -> empty slice
      *result = Slice();
      return Status();
    }
  }

 private:
  std::string data_;
  size_t pos_;
};

class MockReporter : public Reporter {
 public:
  MOCK_METHOD(void, Corruption, (size_t bytes, const Status& status), (override));
};

// Helper: append one physical record (crc=0 when checksum disabled).
static void EmitPhysicalRecord(std::string& dst, uint8_t type, const std::string& payload) {
  uint32_t crc = 0;  // ignored when checksum=false
  uint16_t len = static_cast<uint16_t>(payload.size());
  // Write little-endian header: crc(4), len(2), type(1)
  dst.append(reinterpret_cast<const char*>(&crc), 4);
  dst.push_back(static_cast<char>(len & 0xff));
  dst.push_back(static_cast<char>((len >> 8) & 0xff));
  dst.push_back(static_cast<char>(type));
  dst.append(payload);
}

// Build a single FULL record stream.
static std::string MakeFull(const std::string& payload) {
  std::string s;
  EmitPhysicalRecord(s, kFullType, payload);
  return s;
}

// Build a fragmented record stream: FIRST + MIDDLE... + LAST
static std::string MakeFragmented(const std::vector<std::string>& parts) {
  std::string s;
  if (parts.empty()) return s;
  EmitPhysicalRecord(s, kFirstType, parts.front());
  for (size_t i = 1; i + 1 < parts.size(); ++i) {
    EmitPhysicalRecord(s, kMiddleType, parts[i]);
  }
  EmitPhysicalRecord(s, kLastType, parts.back());
  return s;
}

// Build arbitrary sequence of physical records (for resync/tests).
static std::string MakeSeq(const std::vector<std::pair<uint8_t, std::string>>& seq) {
  std::string s;
  for (auto& [t, p] : seq) EmitPhysicalRecord(s, t, p);
  return s;
}

// ---- Fixture ----
class ReaderTest_324 : public ::testing::Test {
 protected:
  // Helper to construct a Reader with given stream & initial_offset
  std::unique_ptr<log::Reader> MakeReader(const std::string& data,
                                          Reporter* reporter,
                                          uint64_t initial_offset = 0) {
    file_.reset(new StringSequentialFile(data));
    // checksum=false for simpler headers
    return std::unique_ptr<log::Reader>(new log::Reader(file_.get(), reporter, /*checksum=*/false, initial_offset));
  }

  std::unique_ptr<StringSequentialFile> file_;
};

} // namespace

// ------------ TESTS ------------

// Normal path: a single FULL record should return true with the payload.
// Also verifies scratch is cleared on success, and last offset becomes non-zero.
TEST_F(ReaderTest_324, FullRecord_SucceedsAndSetsRecord_324) {
  StrictMock<MockReporter> reporter;
  auto reader = MakeReader(MakeFull("hello"), &reporter);

  leveldb::Slice out;
  std::string scratch = "will be cleared";

  ASSERT_TRUE(reader->ReadRecord(&out, &scratch));
  EXPECT_EQ(out.ToString(), "hello");
  EXPECT_TRUE(scratch.empty());

  const uint64_t last1 = reader->LastRecordOffset();
  EXPECT_GT(last1, 0u);

  // Second read should hit EOF and return false.
  out = leveldb::Slice();  // reset
  scratch = "x";
  EXPECT_FALSE(reader->ReadRecord(&out, &scratch));
  EXPECT_TRUE(out.empty());
  // scratch may be cleared by EOF path; observable value is not strictly guaranteed,
  // so we don’t assert it here beyond not crashing / returning false.
}

// Fragmented record: FIRST+MIDDLE+LAST are reassembled and returned as one logical record.
TEST_F(ReaderTest_324, FragmentedRecord_ReassemblesIntoSingleLogicalRecord_324) {
  StrictMock<MockReporter> reporter;
  std::vector<std::string> parts = {"abc", "DEF", "12345"};
  const std::string stream = MakeFragmented(parts);

  auto reader = MakeReader(stream, &reporter);

  leveldb::Slice out;
  std::string scratch;
  ASSERT_TRUE(reader->ReadRecord(&out, &scratch));
  EXPECT_EQ(out.ToString(), "abcDEF12345");
  EXPECT_TRUE(scratch.empty());

  // After consuming it, subsequent read should be EOF.
  EXPECT_FALSE(reader->ReadRecord(&out, &scratch));
}

// Boundary/erroneous observable case: MIDDLE without a prior FIRST.
// Reader reports corruption internally and continues; with immediate EOF it returns false,
// and scratch must be cleared per implementation path.
TEST_F(ReaderTest_324, MiddleWithoutStart_ClearsScratchAndReturnsFalse_324) {
  StrictMock<MockReporter> reporter;
  // Stream: MIDDLE("zzz") then nothing (EOF)
  auto reader = MakeReader(MakeSeq({{kMiddleType, "zzz"}}), &reporter);

  leveldb::Slice out;
  std::string scratch = "temp";
  EXPECT_FALSE(reader->ReadRecord(&out, &scratch));
  EXPECT_TRUE(out.empty());
  EXPECT_TRUE(scratch.empty());  // implementation clears scratch when EOF during fragmented
}

// Error in the middle of a fragmented record: FIRST then BAD -> (clears) -> EOF -> false.
// We can’t assert reporter interactions strictly, but we can assert observable scratch clearing.
TEST_F(ReaderTest_324, BadRecordDuringFragmentation_AbortsAndClearsScratch_324) {
  StrictMock<MockReporter> reporter;
  // Stream: FIRST("A"), BAD("junk"), then EOF
  auto reader = MakeReader(MakeSeq({{kFirstType, "A"}, {static_cast<uint8_t>(6), "junk"}}), &reporter);
  // ^ 6 is kBadRecord per header in prompt

  leveldb::Slice out;
  std::string scratch;
  EXPECT_FALSE(reader->ReadRecord(&out, &scratch));
  EXPECT_TRUE(out.empty());
  EXPECT_TRUE(scratch.empty());
}

// Resync behavior when initial_offset_ > 0:
// If the first physical type seen is MIDDLE, Reader should skip until a FULL or FIRST/LAST completes.
// Here: MIDDLE("xx") then FULL("OK") -> should return "OK".
TEST_F(ReaderTest_324, Resyncing_SkipsMiddleThenReadsNextFull_324) {
  StrictMock<MockReporter> reporter;
  const std::string stream = MakeSeq({
      {kMiddleType, "xx"},
      {kFullType,   "OK"}
  });

  // initial_offset > 0 triggers resyncing_ path.
  auto reader = MakeReader(stream, &reporter, /*initial_offset=*/1234);

  leveldb::Slice out;
  std::string scratch;
  ASSERT_TRUE(reader->ReadRecord(&out, &scratch));
  EXPECT_EQ(out.ToString(), "OK");
  EXPECT_TRUE(scratch.empty());

  // Offset should be set (monotonic); we don’t assume exact math.
  EXPECT_GT(reader->LastRecordOffset(), 0u);

  // Then EOF.
  EXPECT_FALSE(reader->ReadRecord(&out, &scratch));
}

