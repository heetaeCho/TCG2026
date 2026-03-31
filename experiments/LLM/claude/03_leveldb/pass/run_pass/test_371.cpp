#include "gtest/gtest.h"
#include "table/filter_block.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

#include <string>
#include <memory>

namespace leveldb {

// A simple test filter policy for testing purposes
class TestFilterPolicy : public FilterPolicy {
 public:
  const char* Name() const override { return "TestFilterPolicy"; }

  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {
    for (int i = 0; i < n; i++) {
      dst->append(keys[i].data(), keys[i].size());
    }
  }

  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    // Simple check: if the filter contains the key
    return filter.ToString().find(key.ToString()) != std::string::npos;
  }
};

class FilterBlockBuilderTest_371 : public ::testing::Test {
 protected:
  void SetUp() override {
    policy_ = std::make_unique<TestFilterPolicy>();
    builder_ = std::make_unique<FilterBlockBuilder>(policy_.get());
  }

  std::unique_ptr<TestFilterPolicy> policy_;
  std::unique_ptr<FilterBlockBuilder> builder_;
};

// Test that creating a FilterBlockBuilder with a valid policy doesn't crash
TEST_F(FilterBlockBuilderTest_371, ConstructionWithValidPolicy_371) {
  FilterBlockBuilder builder(policy_.get());
  // If we get here without crashing, construction succeeded
}

// Test StartBlock with offset 0 (should not generate any filters)
TEST_F(FilterBlockBuilderTest_371, StartBlockAtZeroOffset_371) {
  builder_->StartBlock(0);
  // Should succeed without issues; filter_index = 0 / kFilterBase = 0
}

// Test StartBlock with a small offset within the first filter base
TEST_F(FilterBlockBuilderTest_371, StartBlockSmallOffset_371) {
  builder_->StartBlock(1);
  // offset 1 / kFilterBase (2048) = 0, so no filters generated
}

// Test StartBlock with offset exactly at kFilterBase boundary
TEST_F(FilterBlockBuilderTest_371, StartBlockAtFilterBaseBoundary_371) {
  // kFilterBase = 1 << 11 = 2048
  builder_->StartBlock(2048);
  // filter_index = 2048 / 2048 = 1, should generate one filter
}

// Test StartBlock with offset that creates multiple filter gaps
TEST_F(FilterBlockBuilderTest_371, StartBlockMultipleFilterGaps_371) {
  // kFilterBase = 2048
  // offset = 2048 * 5 = 10240, filter_index = 5
  builder_->StartBlock(10240);
  // Should generate 5 filters (indices 0 through 4)
}

// Test StartBlock called multiple times with increasing offsets
TEST_F(FilterBlockBuilderTest_371, StartBlockIncreasingOffsets_371) {
  builder_->StartBlock(0);
  builder_->StartBlock(2048);
  builder_->StartBlock(4096);
  builder_->StartBlock(6144);
  // Should work fine with increasing offsets
}

// Test AddKey then StartBlock
TEST_F(FilterBlockBuilderTest_371, AddKeyThenStartBlock_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice("key1"));
  builder_->AddKey(Slice("key2"));
  builder_->StartBlock(2048);
  // Keys added to first block should be included in first filter
}

// Test Finish with no keys added
TEST_F(FilterBlockBuilderTest_371, FinishWithNoKeys_371) {
  Slice result = builder_->Finish();
  // Result should be non-empty (at least contains the offset array and metadata)
  EXPECT_TRUE(result.size() > 0);
}

// Test Finish after adding some keys
TEST_F(FilterBlockBuilderTest_371, FinishAfterAddingKeys_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice("hello"));
  builder_->AddKey(Slice("world"));
  Slice result = builder_->Finish();
  EXPECT_TRUE(result.size() > 0);
}

// Test Finish after StartBlock with large offset
TEST_F(FilterBlockBuilderTest_371, FinishAfterLargeOffset_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice("key1"));
  builder_->StartBlock(2048 * 3);
  builder_->AddKey(Slice("key2"));
  Slice result = builder_->Finish();
  EXPECT_TRUE(result.size() > 0);
}

// Test adding empty key
TEST_F(FilterBlockBuilderTest_371, AddEmptyKey_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice(""));
  Slice result = builder_->Finish();
  EXPECT_TRUE(result.size() > 0);
}

// Test adding many keys
TEST_F(FilterBlockBuilderTest_371, AddManyKeys_371) {
  builder_->StartBlock(0);
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    builder_->AddKey(Slice(key));
  }
  Slice result = builder_->Finish();
  EXPECT_TRUE(result.size() > 0);
}

// Test StartBlock at offset just below kFilterBase
TEST_F(FilterBlockBuilderTest_371, StartBlockJustBelowFilterBase_371) {
  // kFilterBase = 2048, so offset 2047 -> filter_index = 0
  builder_->StartBlock(2047);
  // No filters should be generated since filter_index = 0
}

// Test StartBlock at offset just above kFilterBase
TEST_F(FilterBlockBuilderTest_371, StartBlockJustAboveFilterBase_371) {
  // kFilterBase = 2048, so offset 2049 -> filter_index = 1
  builder_->StartBlock(2049);
  // One filter should be generated
}

// Test multiple blocks with keys and then finish
TEST_F(FilterBlockBuilderTest_371, MultipleBlocksWithKeysAndFinish_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice("a"));
  builder_->AddKey(Slice("b"));

  builder_->StartBlock(2048);
  builder_->AddKey(Slice("c"));
  builder_->AddKey(Slice("d"));

  builder_->StartBlock(4096);
  builder_->AddKey(Slice("e"));

  Slice result = builder_->Finish();
  EXPECT_TRUE(result.size() > 0);
}

// Test FilterBlockReader with builder output
TEST_F(FilterBlockBuilderTest_371, FilterBlockReaderKeyMayMatch_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice("hello"));
  builder_->AddKey(Slice("world"));

  Slice block = builder_->Finish();

  FilterBlockReader reader(policy_.get(), block);
  // Block offset 0 should potentially match "hello"
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("hello")));
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("world")));
}

// Test FilterBlockReader with key that was not added
TEST_F(FilterBlockBuilderTest_371, FilterBlockReaderKeyNotAdded_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice("hello"));

  Slice block = builder_->Finish();

  FilterBlockReader reader(policy_.get(), block);
  // "missing" was not added - may or may not match depending on filter policy
  // With our test policy, it should not match
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("missing")));
}

// Test FilterBlockReader with multiple blocks
TEST_F(FilterBlockBuilderTest_371, FilterBlockReaderMultipleBlocks_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice("foo"));

  builder_->StartBlock(2048);
  builder_->AddKey(Slice("bar"));

  builder_->StartBlock(4096);
  builder_->AddKey(Slice("baz"));

  Slice block = builder_->Finish();

  FilterBlockReader reader(policy_.get(), block);
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("foo")));
  EXPECT_TRUE(reader.KeyMayMatch(2048, Slice("bar")));
  EXPECT_TRUE(reader.KeyMayMatch(4096, Slice("baz")));
}

// Test FilterBlockReader with very large block offset
TEST_F(FilterBlockBuilderTest_371, FilterBlockReaderLargeBlockOffset_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice("test"));

  Slice block = builder_->Finish();

  FilterBlockReader reader(policy_.get(), block);
  // Very large offset - should return true (safe default) since no filter exists for that range
  EXPECT_TRUE(reader.KeyMayMatch(100000, Slice("test")));
}

// Test Finish can only be called once (result is valid)
TEST_F(FilterBlockBuilderTest_371, FinishProducesValidResult_371) {
  builder_->StartBlock(0);
  builder_->AddKey(Slice("key"));
  Slice result = builder_->Finish();

  // The result should have at least 5 bytes (4 for offset array offset + 1 for base lg)
  EXPECT_GE(result.size(), 5u);
}

// Test StartBlock with very large offset
TEST_F(FilterBlockBuilderTest_371, StartBlockVeryLargeOffset_371) {
  // This would create many filters but should work
  // Use a moderately large offset to avoid excessive memory usage
  builder_->StartBlock(2048 * 10);
  builder_->AddKey(Slice("key"));
  Slice result = builder_->Finish();
  EXPECT_TRUE(result.size() > 0);
}

}  // namespace leveldb
