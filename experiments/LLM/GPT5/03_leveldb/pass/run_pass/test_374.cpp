// File: filter_block_reader_keymaymatch_test_374.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "table/filter_block.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;
using ::testing::NiceMock;
using ::testing::Exactly;

namespace {

// --- Minimal mock for FilterPolicy (only what we need) ---
class MockFilterPolicy : public leveldb::FilterPolicy {
 public:
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, CreateFilter,
              (const leveldb::Slice* keys, int n, std::string* dst),
              (const, override));
  MOCK_METHOD(bool, KeyMayMatch,
              (const leveldb::Slice& key, const leveldb::Slice& filter),
              (const, override));
  ~MockFilterPolicy() override = default;
};

// --- Little-endian helper ---
static void PutFixed32LE(std::string& dst, uint32_t v) {
  char buf[4];
  buf[0] = static_cast<char>(v & 0xFF);
  buf[1] = static_cast<char>((v >> 8) & 0xFF);
  buf[2] = static_cast<char>((v >> 16) & 0xFF);
  buf[3] = static_cast<char>((v >> 24) & 0xFF);
  dst.append(buf, 4);
}

// Build a filter block contents as a single blob, following the public
// constructor signature (contents as a Slice). We do not rely on or
// inspect any private state; we only craft inputs and observe behavior.
static std::string BuildFilterBlockContents(const std::vector<std::string>& filters,
                                            uint8_t base_lg) {
  std::string contents;

  // 1) Concatenate raw filter payloads
  std::vector<uint32_t> offsets;
  offsets.reserve(filters.size() + 1);
  uint32_t cur = 0;
  for (const auto& f : filters) {
    offsets.push_back(cur);
    contents.append(f);
    cur += static_cast<uint32_t>(f.size());
  }
  // The terminal offset (end)
  offsets.push_back(cur);

  // 2) Append the 4-byte little-endian offset table (num_ + 1 entries)
  for (uint32_t off : offsets) {
    PutFixed32LE(contents, off);
  }

  // 3) Append the 4-byte little-endian start-of-offset-table (relative to data)
  // This is the boundary used by KeyMayMatch to validate (limit <= offset_-data_).
  const uint32_t offset_array_start = static_cast<uint32_t>(cur);
  PutFixed32LE(contents, offset_array_start);

  // 4) Append 1 byte base_lg
  contents.push_back(static_cast<char>(base_lg));

  return contents;
}

class FilterBlockReaderTest_374 : public ::testing::Test {
 protected:
  // Utility to create a reader from filters with chosen base_lg
  std::unique_ptr<leveldb::FilterBlockReader> MakeReader(
      const leveldb::FilterPolicy* policy,
      const std::vector<std::string>& filters,
      uint8_t base_lg) {
    std::string blob = BuildFilterBlockContents(filters, base_lg);
    leveldb::Slice contents(blob.data(), blob.size());
    return std::unique_ptr<leveldb::FilterBlockReader>(
        new leveldb::FilterBlockReader(policy, contents));
  }
};

}  // namespace

// Normal operation: valid index -> delegates to policy and returns its result.
TEST_F(FilterBlockReaderTest_374, DelegatesToPolicyOnValidRange_374) {
  StrictMock<MockFilterPolicy> policy;
  // Two simple filters; index 0 points to "AAA", index 1 points to "BBBB".
  auto reader = MakeReader(&policy, {"AAA", "BBBB"}, /*base_lg=*/1);

  // block_offset >> 1 -> index. Choose offset so index==1 (e.g., block_offset=2).
  const uint64_t block_offset = 2;
  const leveldb::Slice key("hello");

  // Expect delegation with some Slice pointing to "BBBB".
  EXPECT_CALL(policy, KeyMayMatch(_, _))
      .WillOnce([](const leveldb::Slice& k, const leveldb::Slice& filter) {
        // Basic observable checks on arguments
        EXPECT_EQ(std::string("hello"), std::string(k.data(), k.size()));
        EXPECT_EQ(std::string("BBBB"), std::string(filter.data(), filter.size()));
        return true;  // Reader should return this value
      });

  EXPECT_TRUE(reader->KeyMayMatch(block_offset, key));
}

// Empty filter region (start == limit) -> returns false and does NOT call policy.
TEST_F(FilterBlockReaderTest_374, ReturnsFalseOnEmptyFilter_374) {
  StrictMock<MockFilterPolicy> policy;
  // First filter is empty; second is non-empty.
  auto reader = MakeReader(&policy, {"", "X"}, /*base_lg=*/0);

  // base_lg=0 -> index = block_offset. Choose index 0 to hit the empty filter.
  const uint64_t block_offset = 0;
  const leveldb::Slice key("k");

  // No calls expected
  EXPECT_FALSE(reader->KeyMayMatch(block_offset, key));
}

// Index out of range (index >= num_) -> treated as "error": return true; no policy call.
TEST_F(FilterBlockReaderTest_374, ReturnsTrueOnIndexOutOfRange_374) {
  StrictMock<MockFilterPolicy> policy;
  auto reader = MakeReader(&policy, {"Z"}, /*base_lg=*/0);

  // Only 1 filter -> valid index is 0. Use index 1.
  const uint64_t block_offset = 1;
  const leveldb::Slice key("k");

  EXPECT_TRUE(reader->KeyMayMatch(block_offset, key));
}

// Corrupt range: start > limit -> treated as error -> return true; no policy call.
TEST_F(FilterBlockReaderTest_374, ReturnsTrueOnCorruptRangeStartGreaterThanLimit_374) {
  StrictMock<MockFilterPolicy> policy;

  // Build a valid block first, then tamper the offset table to make start>limit
  std::string blob = BuildFilterBlockContents({"AA", "BB"}, /*base_lg=*/0);

  // Locate the offset table inside the blob:
  // layout: [data | offsets( (num+1)*4 ) | 4B offset_array_start | 1B base_lg]
  // data size = end terminal offset = 4 * (num+1) entry at the end of data.
  // We'll flip the first two offsets to make start > limit for index 0.
  // For portability, read the offset_array_start we wrote:
  uint32_t offset_array_start =
      static_cast<uint8_t>(blob[blob.size() - 5]) |
      (static_cast<uint8_t>(blob[blob.size() - 4]) << 8) |
      (static_cast<uint8_t>(blob[blob.size() - 3]) << 16) |
      (static_cast<uint8_t>(blob[blob.size() - 2]) << 24);
  // Offsets are at blob.data() + offset_array_start
  // Swap the first two 32-bit entries to enforce start > limit for index 0
  std::swap(blob[offset_array_start + 0], blob[offset_array_start + 4]);
  std::swap(blob[offset_array_start + 1], blob[offset_array_start + 5]);
  std::swap(blob[offset_array_start + 2], blob[offset_array_start + 6]);
  std::swap(blob[offset_array_start + 3], blob[offset_array_start + 7]);

  leveldb::Slice contents(blob.data(), blob.size());
  leveldb::FilterBlockReader reader(&policy, contents);

  EXPECT_TRUE(reader.KeyMayMatch(/*block_offset=*/0, leveldb::Slice("k")));
}

// Corrupt range: limit beyond data boundary -> treated as error -> return true; no policy call.
TEST_F(FilterBlockReaderTest_374, ReturnsTrueOnCorruptRangeLimitBeyondData_374) {
  StrictMock<MockFilterPolicy> policy;

  // Start with one empty filter (valid), then tamper limit to exceed data boundary.
  std::string blob = BuildFilterBlockContents({""}, /*base_lg=*/0);

  // Read offset_array_start
  uint32_t offset_array_start =
      static_cast<uint8_t>(blob[blob.size() - 5]) |
      (static_cast<uint8_t>(blob[blob.size() - 4]) << 8) |
      (static_cast<uint8_t>(blob[blob.size() - 3]) << 16) |
      (static_cast<uint8_t>(blob[blob.size() - 2]) << 24);

  // Overwrite the "limit" entry (offset index 1) with something large
  // Write 0x7FFFFFFF into entry 1
  const uint32_t kTooLarge = 0x7FFFFFFF;
  blob[offset_array_start + 4] = static_cast<char>(kTooLarge & 0xFF);
  blob[offset_array_start + 5] = static_cast<char>((kTooLarge >> 8) & 0xFF);
  blob[offset_array_start + 6] = static_cast<char>((kTooLarge >> 16) & 0xFF);
  blob[offset_array_start + 7] = static_cast<char>((kTooLarge >> 24) & 0xFF);

  leveldb::Slice contents(blob.data(), blob.size());
  leveldb::FilterBlockReader reader(&policy, contents);

  EXPECT_TRUE(reader.KeyMayMatch(/*block_offset=*/0, leveldb::Slice("any")));
}

// base_lg affects index selection: block_offset >> base_lg.
// Build two filters and verify different offsets map to different filters.
TEST_F(FilterBlockReaderTest_374, UsesBlockOffsetShiftByBaseLg_374) {
  StrictMock<MockFilterPolicy> policy;
  // Two filters with distinct payloads so we can observe which is chosen
  auto reader = MakeReader(&policy, {"F0", "F1PAYLOAD"}, /*base_lg=*/2);

  // For base_lg=2, index = block_offset >> 2.
  // Use 3 (index 0) and 4 (index 1).
  const leveldb::Slice key("k");

  {
    testing::InSequence seq;
    EXPECT_CALL(policy, KeyMayMatch(_, _))
        .WillOnce([](const leveldb::Slice&, const leveldb::Slice& filter) {
          EXPECT_EQ(std::string("F0"), std::string(filter.data(), filter.size()));
          return false;
        });
    EXPECT_CALL(policy, KeyMayMatch(_, _))
        .WillOnce([](const leveldb::Slice&, const leveldb::Slice& filter) {
          EXPECT_EQ(std::string("F1PAYLOAD"), std::string(filter.data(), filter.size()));
          return true;
        });
  }

  EXPECT_FALSE(reader->KeyMayMatch(/*block_offset=*/3, key));  // index 0
  EXPECT_TRUE(reader->KeyMayMatch(/*block_offset=*/4, key));   // index 1
}
