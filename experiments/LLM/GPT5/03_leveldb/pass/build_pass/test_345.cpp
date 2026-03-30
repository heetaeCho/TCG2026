// File: log_writer_addrecord_test_345.cc
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "db/log_writer.h"
#include "db/log_format.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

namespace leveldb {
namespace {

class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

// Helper: generate a string of a given length with deterministic content.
static std::string MakeData(size_t n) {
  std::string s;
  s.resize(n);
  for (size_t i = 0; i < n; ++i) s[i] = static_cast<char>(i % 251 + 1);
  return s;
}

// Custom matcher to verify the "padding" behavior triggered directly in AddRecord
// when leftover < kHeaderSize: Writer must Append a Slice of 'leftover' zero bytes.
MATCHER_P(IsZeroSliceOfSize, expected_size,
          "Slice is all-zero bytes of the given size") {
  const Slice& sl = arg;
  if (sl.size() != expected_size) return false;
  for (size_t i = 0; i < sl.size(); ++i) {
    if (sl.data()[i] != 0) return false;
  }
  return true;
}

}  // namespace

// -----------------------------------------------------------------------------
// Normal operation: small record from a fresh block returns OK.
// We do NOT assert on how many appends happen inside EmitPhysicalRecord;
// we only require AddRecord to succeed.
// -----------------------------------------------------------------------------
TEST(WriterAddRecord_345, AddRecord_ReturnsOk_ForSmallInput_345) {
  MockWritableFile file;
  // Any internal Append(s) performed by EmitPhysicalRecord should succeed.
  ON_CALL(file, Append(_)).WillByDefault(Return(Status::OK()));

  log::Writer writer(&file);  // fresh block (offset = 0)
  const std::string payload = "hello";
  Status s = writer.AddRecord(Slice(payload));
  EXPECT_TRUE(s.ok());
}

// -----------------------------------------------------------------------------
// Boundary: when the current block has fewer than kHeaderSize bytes left,
// AddRecord must pad the remainder of the block with zero bytes via dest_->Append.
// We verify that an Append is invoked with exactly 'leftover' zero bytes BEFORE
// writing any fragment(s).
// -----------------------------------------------------------------------------
TEST(WriterAddRecord_345, AddRecord_PadsTrailerWhenLeftoverLessThanHeader_345) {
  MockWritableFile file;
  ON_CALL(file, Append(_)).WillByDefault(Return(Status::OK()));

  // Set dest_length so that block_offset_ == kBlockSize - (kHeaderSize - 1),
  // i.e., leftover = kHeaderSize - 1 (< kHeaderSize) => padding is required.
  const int leftover = log::kHeaderSize - 1;
  const uint64_t dest_length = log::kBlockSize - leftover;

  log::Writer writer(&file, dest_length);

  // The first Append must be the zero padding of size 'leftover'.
  InSequence seq;
  EXPECT_CALL(file, Append(IsZeroSliceOfSize(leftover)))
      .WillOnce(Return(Status::OK()));
  // Subsequent appends (from emitting the physical record) are allowed and OK.

  const std::string payload = "A";  // any non-empty slice
  Status s = writer.AddRecord(Slice(payload));
  EXPECT_TRUE(s.ok());
}

// -----------------------------------------------------------------------------
// Error propagation: if the underlying file Append used by emitting a fragment
// fails, AddRecord should return a non-OK Status (we simulate an IOError).
// We do not assert on internal formatting—only that failure is surfaced.
// -----------------------------------------------------------------------------
TEST(WriterAddRecord_345, AddRecord_PropagatesFailureFromUnderlyingAppend_345) {
  MockWritableFile file;

  // The very first Append attempted by EmitPhysicalRecord will fail.
  // (No padding occurs here since we start at a fresh block.)
  EXPECT_CALL(file, Append(_))
      .WillOnce(Return(Status::IOError("disk full")));

  log::Writer writer(&file);  // fresh block
  const std::string payload = MakeData(100);  // arbitrary size
  Status s = writer.AddRecord(Slice(payload));

  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// -----------------------------------------------------------------------------
// Padding happens only when leftover < kHeaderSize. If we start exactly at the
// beginning of a block (or any offset with sufficient space), no zero-padding
// Append should precede the record write. We ensure the first Append is NOT a
// small all-zero slice by placing the writer at offset 0.
// (We cannot assert exact sizes or counts of internal appends.)
// -----------------------------------------------------------------------------
TEST(WriterAddRecord_345, AddRecord_NoPaddingWhenFreshBlock_345) {
  MockWritableFile file;
  // On a fresh block, the first Append must not be a tiny zero-padding slice.
  // We accept any OK return for subsequent calls.
  ON_CALL(file, Append(_)).WillByDefault(Return(Status::OK()));

  // Capture the very first Append argument to ensure it isn't a padding slice
  // smaller than kHeaderSize-1 of all zeros (which would indicate unintended padding).
  bool first_call_checked = false;
  EXPECT_CALL(file, Append(_))
      .WillOnce([&first_call_checked](const Slice& s) {
        // If padding were happening spuriously, it would be a tiny (<= kHeaderSize-1)
        // all-zero Slice. Disallow that here.
        if (s.size() > 0 && s.size() < static_cast<size_t>(log::kHeaderSize)) {
          // Verify not all zeros (would imply padding). We accept any non-padding.
          bool all_zero = true;
          for (size_t i = 0; i < s.size(); ++i) {
            if (s.data()[i] != 0) { all_zero = false; break; }
          }
          EXPECT_FALSE(all_zero) << "Unexpected zero-padding on fresh block";
        }
        first_call_checked = true;
        return Status::OK();
      });

  log::Writer writer(&file);  // offset = 0
  const std::string payload = MakeData(32);
  Status s = writer.AddRecord(Slice(payload));
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(first_call_checked);
}

}  // namespace leveldb
