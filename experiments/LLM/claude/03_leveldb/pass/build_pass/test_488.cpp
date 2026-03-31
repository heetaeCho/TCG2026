#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "table/filter_block.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <string>
#include <vector>

namespace leveldb {

// Mock FilterPolicy for testing
class MockFilterPolicy : public FilterPolicy {
 public:
  ~MockFilterPolicy() override {}
  const char* Name() const override { return "MockFilterPolicy"; }
  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {
    // Simple filter: just store all keys concatenated
    for (int i = 0; i < n; i++) {
      dst->append(keys[i].data(), keys[i].size());
    }
  }
  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    // Simple match: check if key appears in filter
    std::string k = key.ToString();
    std::string f = filter.ToString();
    return f.find(k) != std::string::npos;
  }
};

// A filter policy that always returns true for KeyMayMatch
class AlwaysMatchFilterPolicy : public FilterPolicy {
 public:
  ~AlwaysMatchFilterPolicy() override {}
  const char* Name() const override { return "AlwaysMatch"; }
  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {}
  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    return true;
  }
};

// A filter policy that always returns false for KeyMayMatch
class NeverMatchFilterPolicy : public FilterPolicy {
 public:
  ~NeverMatchFilterPolicy() override {}
  const char* Name() const override { return "NeverMatch"; }
  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {}
  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    return false;
  }
};

class FilterBlockReaderTest_488 : public ::testing::Test {
 protected:
  MockFilterPolicy policy_;
  AlwaysMatchFilterPolicy always_match_policy_;
  NeverMatchFilterPolicy never_match_policy_;
};

// Test construction with empty contents (less than 5 bytes)
TEST_F(FilterBlockReaderTest_488, EmptyContents_488) {
  Slice contents("", 0);
  FilterBlockReader reader(&policy_, contents);
  // With empty contents, reader should not crash and KeyMayMatch should
  // handle gracefully
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("key")));
}

// Test construction with contents too small (1 byte)
TEST_F(FilterBlockReaderTest_488, ContentsTooSmall1Byte_488) {
  std::string data(1, '\0');
  Slice contents(data);
  FilterBlockReader reader(&policy_, contents);
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("key")));
}

// Test construction with contents too small (4 bytes)
TEST_F(FilterBlockReaderTest_488, ContentsTooSmall4Bytes_488) {
  std::string data(4, '\0');
  Slice contents(data.data(), 4);
  FilterBlockReader reader(&policy_, contents);
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("key")));
}

// Test construction with exactly 5 bytes but offset points beyond data
TEST_F(FilterBlockReaderTest_488, ExactlyMinSizeInvalidOffset_488) {
  std::string data;
  // 4 bytes for offset array start (pointing beyond valid range)
  uint32_t offset_start = 10;  // > n - 5 = 0, so invalid
  data.resize(4);
  EncodeFixed32(&data[0], offset_start);
  data.push_back(0);  // base_lg_
  Slice contents(data.data(), data.size());
  FilterBlockReader reader(&policy_, contents);
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("key")));
}

// Test construction with exactly 5 bytes and valid offset
TEST_F(FilterBlockReaderTest_488, ExactlyMinSizeValidOffset_488) {
  std::string data;
  // offset_start = 0, which is <= n - 5 = 0
  uint32_t offset_start = 0;
  data.resize(4);
  EncodeFixed32(&data[0], offset_start);
  data.push_back(0);  // base_lg_
  Slice contents(data.data(), data.size());
  FilterBlockReader reader(&policy_, contents);
  // num_ = (5 - 5 - 0) / 4 = 0, so no filters
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("key")));
}

// Test with a properly constructed filter block using FilterBlockBuilder
// We'll manually construct a valid filter block
TEST_F(FilterBlockReaderTest_488, ValidFilterBlockSingleFilter_488) {
  // Build a simple filter block manually
  // Layout: [filter data][offset of filter 0][offset of end of filter 0][offset array start][base_lg_]
  
  // Filter data: "hello" (5 bytes)
  std::string filter_data = "hello";
  
  // Offset array: offset[0] = 0, offset[1] = 5 (end of filter 0)
  std::string result;
  result.append(filter_data);
  
  // Offset entries (each 4 bytes)
  std::string offset_entry;
  offset_entry.resize(4);
  EncodeFixed32(&offset_entry[0], 0);  // filter 0 starts at 0
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 5);  // filter 0 ends at 5
  result.append(offset_entry);
  
  // Offset array start position
  uint32_t array_offset = static_cast<uint32_t>(filter_data.size());  // 5
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  // base_lg_ = 11 (default in leveldb)
  result.push_back(static_cast<char>(11));
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&policy_, contents);
  
  // "hello" is in the filter, so KeyMayMatch should return true for substrings
  // that the mock policy finds
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("hello")));
}

// Test KeyMayMatch returns false when key is not in filter
TEST_F(FilterBlockReaderTest_488, KeyNotInFilter_488) {
  std::string filter_data = "hello";
  
  std::string result;
  result.append(filter_data);
  
  std::string offset_entry;
  offset_entry.resize(4);
  EncodeFixed32(&offset_entry[0], 0);
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 5);
  result.append(offset_entry);
  
  uint32_t array_offset = static_cast<uint32_t>(filter_data.size());
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  result.push_back(static_cast<char>(11));
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&policy_, contents);
  
  // "world" is not in "hello" filter
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("world")));
}

// Test with AlwaysMatchFilterPolicy
TEST_F(FilterBlockReaderTest_488, AlwaysMatchPolicy_488) {
  std::string filter_data = "test";
  
  std::string result;
  result.append(filter_data);
  
  std::string offset_entry;
  offset_entry.resize(4);
  EncodeFixed32(&offset_entry[0], 0);
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 4);
  result.append(offset_entry);
  
  uint32_t array_offset = static_cast<uint32_t>(filter_data.size());
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  result.push_back(static_cast<char>(11));
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&always_match_policy_, contents);
  
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("anything")));
}

// Test with NeverMatchFilterPolicy
TEST_F(FilterBlockReaderTest_488, NeverMatchPolicy_488) {
  std::string filter_data = "test";
  
  std::string result;
  result.append(filter_data);
  
  std::string offset_entry;
  offset_entry.resize(4);
  EncodeFixed32(&offset_entry[0], 0);
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 4);
  result.append(offset_entry);
  
  uint32_t array_offset = static_cast<uint32_t>(filter_data.size());
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  result.push_back(static_cast<char>(11));
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&never_match_policy_, contents);
  
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("test")));
}

// Test with block_offset that maps to a non-existent filter index
TEST_F(FilterBlockReaderTest_488, BlockOffsetBeyondFilters_488) {
  std::string filter_data = "hello";
  
  std::string result;
  result.append(filter_data);
  
  std::string offset_entry;
  offset_entry.resize(4);
  EncodeFixed32(&offset_entry[0], 0);
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 5);
  result.append(offset_entry);
  
  uint32_t array_offset = static_cast<uint32_t>(filter_data.size());
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  // base_lg_ = 11, so filter index = block_offset >> 11
  result.push_back(static_cast<char>(11));
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&policy_, contents);
  
  // With base_lg_ = 11, block_offset >> 11 gives the filter index
  // We have only 1 filter (num_ = 1), so a large block_offset should
  // map to an index >= num_ and return true (missing filter = may match)
  uint64_t large_offset = static_cast<uint64_t>(2048) * 100;  // >> 11 gives 100
  EXPECT_TRUE(reader.KeyMayMatch(large_offset, Slice("hello")));
}

// Test with last_word exactly equal to n - 5 (boundary)
TEST_F(FilterBlockReaderTest_488, LastWordExactlyAtBoundary_488) {
  // No filter data, no offset entries, last_word = 0
  std::string result;
  
  uint32_t array_offset = 0;  // last_word = 0, n - 5 = 0, so 0 <= 0
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  result.push_back(static_cast<char>(0));  // base_lg_
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&policy_, contents);
  
  // num_ = (5 - 5 - 0) / 4 = 0
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("key")));
}

// Test construction with 2 bytes (too small)
TEST_F(FilterBlockReaderTest_488, ContentsTooSmall2Bytes_488) {
  std::string data(2, '\0');
  Slice contents(data.data(), 2);
  FilterBlockReader reader(&policy_, contents);
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("key")));
}

// Test construction with 3 bytes (too small)
TEST_F(FilterBlockReaderTest_488, ContentsTooSmall3Bytes_488) {
  std::string data(3, '\0');
  Slice contents(data.data(), 3);
  FilterBlockReader reader(&policy_, contents);
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("key")));
}

// Test with multiple filters
TEST_F(FilterBlockReaderTest_488, MultipleFilters_488) {
  // Two filters: "abc" and "xyz"
  std::string result;
  result.append("abc");  // filter 0: bytes 0-2
  result.append("xyz");  // filter 1: bytes 3-5
  
  // Offset array with 3 entries: [0, 3, 6]
  std::string offset_entry;
  offset_entry.resize(4);
  
  EncodeFixed32(&offset_entry[0], 0);  // filter 0 starts at 0
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 3);  // filter 1 starts at 3
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 6);  // end of filter 1
  result.append(offset_entry);
  
  // Offset array starts at position 6
  uint32_t array_offset = 6;
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  // base_lg_ = 11
  result.push_back(static_cast<char>(11));
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&policy_, contents);
  
  // Filter index 0 (block_offset 0 >> 11 = 0): filter is "abc"
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("abc")));
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("xyz")));
  
  // Filter index 1 (block_offset 2048 >> 11 = 1): filter is "xyz"
  EXPECT_TRUE(reader.KeyMayMatch(2048, Slice("xyz")));
  EXPECT_FALSE(reader.KeyMayMatch(2048, Slice("abc")));
}

// Test with base_lg_ = 0
TEST_F(FilterBlockReaderTest_488, BaseLgZero_488) {
  std::string filter_data = "hello";
  
  std::string result;
  result.append(filter_data);
  
  std::string offset_entry;
  offset_entry.resize(4);
  EncodeFixed32(&offset_entry[0], 0);
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 5);
  result.append(offset_entry);
  
  uint32_t array_offset = static_cast<uint32_t>(filter_data.size());
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  // base_lg_ = 0, so filter index = block_offset >> 0 = block_offset
  result.push_back(static_cast<char>(0));
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&policy_, contents);
  
  // block_offset = 0 >> 0 = 0, which is filter 0
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("hello")));
  
  // block_offset = 1 >> 0 = 1, which is >= num_ (1), so should return true
  EXPECT_TRUE(reader.KeyMayMatch(1, Slice("anything")));
}

// Test using FilterBlockBuilder and FilterBlockReader together
// This is an integration-style test
TEST_F(FilterBlockReaderTest_488, BuilderAndReaderIntegration_488) {
  FilterBlockBuilder builder(&policy_);
  
  builder.StartBlock(0);
  builder.AddKey(Slice("foo"));
  builder.AddKey(Slice("bar"));
  
  builder.StartBlock(2048);
  builder.AddKey(Slice("box"));
  
  builder.StartBlock(3100);
  builder.AddKey(Slice("hello"));
  
  Slice block = builder.Finish();
  
  FilterBlockReader reader(&policy_, block);
  
  // Check that keys added to their respective blocks are found
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("foo")));
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("bar")));
  EXPECT_TRUE(reader.KeyMayMatch(2048, Slice("box")));
  EXPECT_TRUE(reader.KeyMayMatch(3100, Slice("hello")));
  
  // Check that keys not added are (most likely) not found
  // Note: depends on mock policy behavior
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("missing")));
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("box")));
}

// Test with empty key
TEST_F(FilterBlockReaderTest_488, EmptyKey_488) {
  std::string filter_data = "hello";
  
  std::string result;
  result.append(filter_data);
  
  std::string offset_entry;
  offset_entry.resize(4);
  EncodeFixed32(&offset_entry[0], 0);
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 5);
  result.append(offset_entry);
  
  uint32_t array_offset = static_cast<uint32_t>(filter_data.size());
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  result.push_back(static_cast<char>(11));
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&policy_, contents);
  
  // Empty key - mock policy will check if "" is in "hello"
  // std::string::find("") returns 0 (found), so this should be true
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("")));
}

// Test with empty filter (filter has 0 bytes)
TEST_F(FilterBlockReaderTest_488, EmptyFilter_488) {
  std::string result;
  // No filter data
  
  // Offset array: [0, 0] (empty filter)
  std::string offset_entry;
  offset_entry.resize(4);
  EncodeFixed32(&offset_entry[0], 0);
  result.append(offset_entry);
  
  EncodeFixed32(&offset_entry[0], 0);
  result.append(offset_entry);
  
  uint32_t array_offset = 0;
  std::string last_word;
  last_word.resize(4);
  EncodeFixed32(&last_word[0], array_offset);
  result.append(last_word);
  
  result.push_back(static_cast<char>(11));
  
  Slice contents(result.data(), result.size());
  FilterBlockReader reader(&policy_, contents);
  
  // The filter is empty, so KeyMayMatch behavior depends on policy
  // With mock policy, find of any key in "" should return npos for non-empty keys
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("key")));
}

}  // namespace leveldb
