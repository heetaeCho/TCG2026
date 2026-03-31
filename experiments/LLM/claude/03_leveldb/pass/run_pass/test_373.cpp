#include "gtest/gtest.h"
#include "table/filter_block.h"
#include "leveldb/filter_policy.h"
#include "util/coding.h"
#include "util/hash.h"

#include <string>
#include <cstring>

namespace leveldb {

// A simple test filter policy for testing purposes
class TestFilterPolicy : public FilterPolicy {
 public:
  const char* Name() const override { return "TestFilterPolicy"; }

  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {
    for (int i = 0; i < n; i++) {
      // Simple filter: just append the hash of each key
      PutFixed32(dst, Hash(keys[i].data(), keys[i].size(), 1));
    }
  }

  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    uint32_t h = Hash(key.data(), key.size(), 1);
    for (size_t i = 0; i + 4 <= filter.size(); i += 4) {
      if (h == DecodeFixed32(filter.data() + i)) {
        return true;
      }
    }
    return false;
  }
};

class FilterBlockBuilderTest_373 : public ::testing::Test {
 protected:
  TestFilterPolicy policy_;
};

// Test that Finish() works when no keys or blocks have been added
TEST_F(FilterBlockBuilderTest_373, FinishWithNoKeys_373) {
  FilterBlockBuilder builder(&policy_);
  Slice result = builder.Finish();
  // Result should contain at least the array_offset (4 bytes) and the encoding parameter (1 byte)
  ASSERT_GE(result.size(), 5u);
  // The last byte should be kFilterBaseLg (11)
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test that Finish() with a single key produces a non-empty result
TEST_F(FilterBlockBuilderTest_373, FinishWithSingleKey_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey("hello");
  Slice result = builder.Finish();
  // Should have filter data + at least one filter offset (4 bytes) + array_offset (4 bytes) + 1 byte for kFilterBaseLg
  ASSERT_GE(result.size(), 9u);
  // Last byte is kFilterBaseLg
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test that Finish() with multiple keys in same block
TEST_F(FilterBlockBuilderTest_373, FinishWithMultipleKeysInSameBlock_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey("key1");
  builder.AddKey("key2");
  builder.AddKey("key3");
  Slice result = builder.Finish();
  ASSERT_GE(result.size(), 5u);
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test that Finish() with keys in multiple blocks at different offsets
TEST_F(FilterBlockBuilderTest_373, FinishWithMultipleBlocks_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey("key1");
  // Start a new block at offset 2048 (which is at filter index 1 since kFilterBase = 2048)
  builder.StartBlock(2048);
  builder.AddKey("key2");
  Slice result = builder.Finish();
  ASSERT_GE(result.size(), 5u);
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test that Finish() with blocks at large offsets
TEST_F(FilterBlockBuilderTest_373, FinishWithLargeBlockOffset_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey("a");
  // Jump to a much larger offset, which should trigger multiple filter generations
  builder.StartBlock(100000);
  builder.AddKey("b");
  Slice result = builder.Finish();
  ASSERT_GE(result.size(), 5u);
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test that the array_offset is stored correctly
TEST_F(FilterBlockBuilderTest_373, ArrayOffsetStoredCorrectly_373) {
  FilterBlockBuilder builder(&policy_);
  Slice result = builder.Finish();
  // No filters generated, so array_offset should be 0
  // The result should be: array_offset (4 bytes) + kFilterBaseLg (1 byte) = 5 bytes
  ASSERT_EQ(result.size(), 5u);
  // Decode the array_offset (second to last 4 bytes before the kFilterBaseLg byte)
  uint32_t array_offset = DecodeFixed32(result.data());
  EXPECT_EQ(array_offset, 0u);
}

// Test that kFilterBaseLg encoding parameter is always the last byte
TEST_F(FilterBlockBuilderTest_373, EncodingParameterIsLastByte_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey("test_key");
  builder.StartBlock(5000);
  builder.AddKey("another_key");
  Slice result = builder.Finish();
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test adding keys without calling StartBlock first
TEST_F(FilterBlockBuilderTest_373, AddKeyWithoutStartBlock_373) {
  FilterBlockBuilder builder(&policy_);
  builder.AddKey("orphan_key");
  Slice result = builder.Finish();
  // Should still produce a valid result with the encoding parameter
  ASSERT_GE(result.size(), 5u);
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test calling StartBlock multiple times without adding keys
TEST_F(FilterBlockBuilderTest_373, StartBlockWithoutAddingKeys_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.StartBlock(2048);
  builder.StartBlock(4096);
  Slice result = builder.Finish();
  ASSERT_GE(result.size(), 5u);
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test with empty key
TEST_F(FilterBlockBuilderTest_373, EmptyKey_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey(Slice("", 0));
  Slice result = builder.Finish();
  ASSERT_GE(result.size(), 5u);
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test that result size grows with more filters
TEST_F(FilterBlockBuilderTest_373, ResultGrowsWithMoreFilters_373) {
  FilterBlockBuilder builder1(&policy_);
  builder1.StartBlock(0);
  builder1.AddKey("key");
  Slice result1 = builder1.Finish();

  FilterBlockBuilder builder2(&policy_);
  builder2.StartBlock(0);
  builder2.AddKey("key1");
  builder2.StartBlock(2048);
  builder2.AddKey("key2");
  builder2.StartBlock(4096);
  builder2.AddKey("key3");
  Slice result2 = builder2.Finish();

  // More blocks should produce a larger result
  EXPECT_GT(result2.size(), result1.size());
}

// Test with block offset 0
TEST_F(FilterBlockBuilderTest_373, BlockOffsetZero_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey("zero_offset_key");
  Slice result = builder.Finish();
  ASSERT_GE(result.size(), 5u);
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

// Test that the filter_offsets array and array_offset are consistent
TEST_F(FilterBlockBuilderTest_373, ConsistentFilterOffsetsAndArrayOffset_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey("key_a");
  Slice result = builder.Finish();
  
  // Parse the result: last byte is kFilterBaseLg
  ASSERT_GE(result.size(), 5u);
  uint8_t lg = static_cast<uint8_t>(result[result.size() - 1]);
  EXPECT_EQ(lg, 11);
  
  // Second to last 4 bytes (before lg) is array_offset
  uint32_t array_offset = DecodeFixed32(result.data() + result.size() - 5);
  
  // array_offset should be within the result
  EXPECT_LE(array_offset, result.size() - 5);
  
  // Number of filter offsets
  size_t num_offsets = (result.size() - 5 - array_offset) / 4;
  EXPECT_GE(num_offsets, 1u);
}

// Test adding many keys to ensure stability
TEST_F(FilterBlockBuilderTest_373, ManyKeys_373) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  for (int i = 0; i < 1000; i++) {
    std::string key = "key_" + std::to_string(i);
    builder.AddKey(key);
  }
  Slice result = builder.Finish();
  ASSERT_GE(result.size(), 5u);
  EXPECT_EQ(static_cast<uint8_t>(result[result.size() - 1]), 11);
}

}  // namespace leveldb
