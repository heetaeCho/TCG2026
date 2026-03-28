// filter_block_reader_test_488.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <string>
#include <vector>

// ---- Minimal headers to satisfy compilation (interfaces only) ----
namespace leveldb {

class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
 private:
  const char* data_;
  size_t size_;
};

class FilterPolicy {
 public:
  virtual ~FilterPolicy() = default;
  virtual const char* Name() const = 0;
  virtual void CreateFilter(const Slice* /*keys*/, int /*n*/, std::string* /*dst*/) const = 0;
  virtual bool KeyMayMatch(const Slice& /*key*/, const Slice& /*filter*/) const = 0;
};

class FilterBlockReader {
 public:
  // Constructor under test (implementation provided elsewhere)
  FilterBlockReader(const FilterPolicy* policy, const Slice& contents);

  // Observable behavior we can exercise
  bool KeyMayMatch(uint64_t block_offset, const Slice& key);
};

} // namespace leveldb

// ---- GMock for FilterPolicy ----
class MockFilterPolicy : public leveldb::FilterPolicy {
 public:
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, CreateFilter, (const leveldb::Slice* keys, int n, std::string* dst), (const, override));
  MOCK_METHOD(bool, KeyMayMatch, (const leveldb::Slice& key, const leveldb::Slice& filter), (const, override));
};

// ---- Test helpers ----
namespace {

inline void AppendFixed32(std::string& dst, uint32_t v) {
  // little-endian encoding as used by DecodeFixed32
  char buf[4];
  buf[0] = static_cast<char>(v & 0xFF);
  buf[1] = static_cast<char>((v >> 8) & 0xFF);
  buf[2] = static_cast<char>((v >> 16) & 0xFF);
  buf[3] = static_cast<char>((v >> 24) & 0xFF);
  dst.append(buf, 4);
}

// Build a filter block byte-sequence matching the constructor layout:
// [filters bytes][offset array (4 * num entries)][last_word (4 bytes)][base_lg (1 byte)]
// where last_word = start offset of the offset array (i.e., filters.size()).
inline std::string BuildFilterBlock(const std::string& filters,
                                    const std::vector<uint32_t>& offsets,
                                    uint8_t base_lg) {
  std::string contents;
  contents.reserve(filters.size() + offsets.size() * 4 + 5);

  // Filters region
  contents.append(filters);

  // Offset array begins here
  const uint32_t last_word = static_cast<uint32_t>(filters.size());
  for (uint32_t x : offsets) {
    AppendFixed32(contents, x);
  }

  // Trailer: last_word (LE32) then base_lg (1 byte)
  AppendFixed32(contents, last_word);
  contents.push_back(static_cast<char>(base_lg));
  return contents;
}

} // namespace

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

// ------------------ Tests ------------------

// Boundary: contents shorter than 5 bytes should be treated as having no usable filters.
// Expect: construction succeeds; KeyMayMatch is safe to call and does NOT delegate to policy.
TEST(FilterBlockReaderTest_488, ConstructWithTooShortContents_NoPolicyCall_488) {
  StrictMock<MockFilterPolicy> policy;

  // Too short: fewer than 5 bytes
  const std::string tiny = "\x01\x02\x03\x04",  // 4 bytes
                    key   = "k";
  leveldb::FilterBlockReader reader(&policy, leveldb::Slice(tiny));

  // No calls into policy->KeyMayMatch should occur for malformed/empty contents.
  // We only assert it returns a bool without crashing; conservative behavior is acceptable.
  bool result = reader.KeyMayMatch(/*block_offset=*/0, leveldb::Slice(key));
  (void)result; // We don't assert the value to avoid inferring internal semantics.
}

// Error case: invalid last_word (greater than n-5) should result in "no usable filters".
// Expect: safe to call; no delegation to policy.
TEST(FilterBlockReaderTest_488, ConstructWithBadLastWord_NoPolicyCall_488) {
  StrictMock<MockFilterPolicy> policy;

  // Build 5 bytes so that last 5 form: [bad last_word (4 bytes)] [base_lg (1 byte)]
  // Let n=5; n-5=0; choose last_word=1 (>0) -> invalid.
  std::string contents;
  contents.reserve(5);
  AppendFixed32(contents, /*last_word=*/1);
  contents.push_back(static_cast<char>(/*base_lg=*/0));

  leveldb::FilterBlockReader reader(&policy, leveldb::Slice(contents));

  bool result = reader.KeyMayMatch(/*block_offset=*/0, leveldb::Slice("x"));
  (void)result; // Only checking for safety and no policy interaction.
}

// Normal operation: well-formed block should delegate to FilterPolicy::KeyMayMatch.
// We verify the external interaction and that the result is propagated.
TEST(FilterBlockReaderTest_488, ValidBlock_DelegatesToPolicyAndPropagatesResult_488) {
  StrictMock<MockFilterPolicy> policy;

  // Construct a minimal valid block:
  // filters: "abc" (3 bytes)
  // offsets: [0, 3]  -> two entries (so reader has num_ = 2)
  // base_lg: 0       -> block_offset >> 0 = block_offset; choose 0 to index first filter.
  const std::string filters = "abc";
  const std::vector<uint32_t> offsets = {0u, 3u};
  const uint8_t base_lg = 0;

  const std::string block = BuildFilterBlock(filters, offsets, base_lg);
  leveldb::FilterBlockReader reader(&policy, leveldb::Slice(block));

  // First: policy returns false; expect reader to return false.
  EXPECT_CALL(policy, KeyMayMatch(_, _)).WillOnce(Return(false));
  EXPECT_FALSE(reader.KeyMayMatch(/*block_offset=*/0, leveldb::Slice("k")));

  // Second: policy returns true; expect reader to return true.
  // (We set another expectation for a second call.)
  EXPECT_CALL(policy, KeyMayMatch(_, _)).WillOnce(Return(true));
  EXPECT_TRUE(reader.KeyMayMatch(/*block_offset=*/0, leveldb::Slice("k")));
}

// Additional interaction check: for a different block_offset that still maps to a valid index
// (given base_lg=0), we still expect a single policy call.
TEST(FilterBlockReaderTest_488, ValidBlock_DifferentBlockOffset_StillDelegatesOnce_488) {
  StrictMock<MockFilterPolicy> policy;

  const std::string filters = "hello_world";
  // Two filters demarcated at 0 and filters.size()
  const std::vector<uint32_t> offsets = {0u, static_cast<uint32_t>(filters.size())};
  const uint8_t base_lg = 0;

  const std::string block = BuildFilterBlock(filters, offsets, base_lg);
  leveldb::FilterBlockReader reader(&policy, leveldb::Slice(block));

  // block_offset = 1 with base_lg=0 maps to index 1; we still expect a delegation.
  EXPECT_CALL(policy, KeyMayMatch(_, _)).WillOnce(Return(true));
  EXPECT_TRUE(reader.KeyMayMatch(/*block_offset=*/1, leveldb::Slice("q")));
}
