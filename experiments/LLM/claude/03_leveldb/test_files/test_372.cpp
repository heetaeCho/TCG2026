#include "gtest/gtest.h"
#include "table/filter_block.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

#include <string>
#include <vector>

namespace leveldb {

// A simple test filter policy for testing purposes
class TestFilterPolicy : public FilterPolicy {
 public:
  const char* Name() const override { return "TestFilterPolicy"; }

  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {
    for (int i = 0; i < n; i++) {
      dst->append(keys[i].data(), keys[i].size());
      dst->push_back(',');
    }
  }

  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    std::string filter_str = filter.ToString();
    std::string search = key.ToString() + ",";
    return filter_str.find(search) != std::string::npos;
  }
};

class FilterBlockBuilderTest_372 : public ::testing::Test {
 protected:
  TestFilterPolicy policy_;
};

// Test that creating a FilterBlockBuilder with a policy does not crash
TEST_F(FilterBlockBuilderTest_372, ConstructionDoesNotCrash_372) {
  FilterBlockBuilder builder(&policy_);
  // Simply constructing should not crash
}

// Test adding a single key
TEST_F(FilterBlockBuilderTest_372, AddSingleKey_372) {
  FilterBlockBuilder builder(&policy_);
  builder.AddKey(Slice("hello"));
  // Should not crash; key is stored internally
}

// Test adding multiple keys
TEST_F(FilterBlockBuilderTest_372, AddMultipleKeys_372) {
  FilterBlockBuilder builder(&policy_);
  builder.AddKey(Slice("key1"));
  builder.AddKey(Slice("key2"));
  builder.AddKey(Slice("key3"));
  // Should not crash
}

// Test adding an empty key
TEST_F(FilterBlockBuilderTest_372, AddEmptyKey_372) {
  FilterBlockBuilder builder(&policy_);
  builder.AddKey(Slice(""));
  // Should not crash; empty key is valid
}

// Test Finish without adding any keys or starting any blocks
TEST_F(FilterBlockBuilderTest_372, FinishWithNoKeysOrBlocks_372) {
  FilterBlockBuilder builder(&policy_);
  Slice result = builder.Finish();
  // Result should be non-empty (at least contains metadata)
  EXPECT_FALSE(result.empty());
}

// Test Finish after adding keys
TEST_F(FilterBlockBuilderTest_372, FinishAfterAddingKeys_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey(Slice("key1"));
  builder.AddKey(Slice("key2"));
  Slice result = builder.Finish();
  EXPECT_FALSE(result.empty());
}

// Test StartBlock with offset 0
TEST_F(FilterBlockBuilderTest_372, StartBlockAtOffsetZero_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey(Slice("testkey"));
  Slice result = builder.Finish();
  EXPECT_FALSE(result.empty());
}

// Test StartBlock with a large offset that triggers filter generation
TEST_F(FilterBlockBuilderTest_372, StartBlockWithLargeOffset_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey(Slice("key1"));
  // Offset large enough to trigger a new filter block (filters are generated per 2KB)
  builder.StartBlock(4096);
  builder.AddKey(Slice("key2"));
  Slice result = builder.Finish();
  EXPECT_FALSE(result.empty());
}

// Test multiple StartBlock calls with increasing offsets
TEST_F(FilterBlockBuilderTest_372, MultipleStartBlockCalls_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey(Slice("a"));
  builder.StartBlock(2048);
  builder.AddKey(Slice("b"));
  builder.StartBlock(4096);
  builder.AddKey(Slice("c"));
  builder.StartBlock(8192);
  builder.AddKey(Slice("d"));
  Slice result = builder.Finish();
  EXPECT_FALSE(result.empty());
}

// Test adding key with special characters
TEST_F(FilterBlockBuilderTest_372, AddKeyWithSpecialChars_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  std::string key_with_nulls("key\0value", 9);
  builder.AddKey(Slice(key_with_nulls.data(), key_with_nulls.size()));
  Slice result = builder.Finish();
  EXPECT_FALSE(result.empty());
}

// Test adding a very long key
TEST_F(FilterBlockBuilderTest_372, AddVeryLongKey_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  std::string long_key(10000, 'x');
  builder.AddKey(Slice(long_key));
  Slice result = builder.Finish();
  EXPECT_FALSE(result.empty());
}

// Test that Finish produces a result that can be used with FilterBlockReader
TEST_F(FilterBlockBuilderTest_372, FinishResultUsableWithReader_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey(Slice("hello"));
  builder.AddKey(Slice("world"));
  Slice result = builder.Finish();

  FilterBlockReader reader(&policy_, result);
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("hello")));
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("world")));
}

// Test that FilterBlockReader returns false for keys not added
TEST_F(FilterBlockBuilderTest_372, ReaderDoesNotMatchMissingKey_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey(Slice("hello"));
  Slice result = builder.Finish();

  FilterBlockReader reader(&policy_, result);
  // "missing" was never added, so it should not match
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("missing")));
}

// Test StartBlock without adding any keys and then Finish
TEST_F(FilterBlockBuilderTest_372, StartBlockNoKeysFinish_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  Slice result = builder.Finish();
  EXPECT_FALSE(result.empty());
}

// Test multiple blocks with reader checking different offsets
TEST_F(FilterBlockBuilderTest_372, MultipleBlocksReaderCheck_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey(Slice("alpha"));
  builder.StartBlock(4096);
  builder.AddKey(Slice("beta"));
  Slice result = builder.Finish();

  FilterBlockReader reader(&policy_, result);
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("alpha")));
  EXPECT_TRUE(reader.KeyMayMatch(4096, Slice("beta")));
}

// Test reader with offset beyond any filter
TEST_F(FilterBlockBuilderTest_372, ReaderWithVeryLargeOffset_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.AddKey(Slice("key"));
  Slice result = builder.Finish();

  FilterBlockReader reader(&policy_, result);
  // Very large offset - should return true (safe default) since there's no filter for it
  EXPECT_TRUE(reader.KeyMayMatch(1000000, Slice("key")));
}

// Test adding many keys to a single block
TEST_F(FilterBlockBuilderTest_372, ManyKeysInSingleBlock_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    builder.AddKey(Slice(key));
  }
  Slice result = builder.Finish();
  EXPECT_FALSE(result.empty());

  FilterBlockReader reader(&policy_, result);
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("key0")));
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("key999")));
}

// Test building with consecutive StartBlock calls without adding keys in between
TEST_F(FilterBlockBuilderTest_372, ConsecutiveStartBlocksNoKeys_372) {
  FilterBlockBuilder builder(&policy_);
  builder.StartBlock(0);
  builder.StartBlock(2048);
  builder.StartBlock(4096);
  builder.StartBlock(8192);
  Slice result = builder.Finish();
  EXPECT_FALSE(result.empty());
}

}  // namespace leveldb
