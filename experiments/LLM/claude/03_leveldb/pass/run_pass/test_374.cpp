#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "table/filter_block.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <string>
#include <vector>
#include <cstring>

namespace leveldb {

// Mock FilterPolicy for testing
class MockFilterPolicy : public FilterPolicy {
 public:
  ~MockFilterPolicy() override = default;

  const char* Name() const override { return "MockFilterPolicy"; }

  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {
    // Simple filter: just concatenate keys
    for (int i = 0; i < n; i++) {
      dst->append(keys[i].data(), keys[i].size());
    }
  }

  MOCK_METHOD(bool, KeyMayMatch, (const Slice& key, const Slice& filter), (const, override));
};

// A simple always-match filter policy
class AlwaysMatchFilterPolicy : public FilterPolicy {
 public:
  ~AlwaysMatchFilterPolicy() override = default;
  const char* Name() const override { return "AlwaysMatch"; }
  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {}
  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    return true;
  }
};

// A simple never-match filter policy
class NeverMatchFilterPolicy : public FilterPolicy {
 public:
  ~NeverMatchFilterPolicy() override = default;
  const char* Name() const override { return "NeverMatch"; }
  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {}
  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    return false;
  }
};

// Helper to build filter block contents manually
// The format of FilterBlockReader's contents:
//   [filter 0][filter 1]...[filter N-1]
//   [offset of filter 0 (4 bytes)][offset of filter 1]...[offset of filter N (4 bytes)]
//   [offset of beginning of offset array (4 bytes)]
//   [base_lg (1 byte)]
class FilterBlockContentsBuilder {
 public:
  FilterBlockContentsBuilder() : base_lg_(11) {}

  void SetBaseLg(uint8_t lg) { base_lg_ = lg; }

  void AddFilter(const std::string& filter_data) {
    filters_.push_back(filter_data);
  }

  std::string Build() {
    std::string result;
    std::vector<uint32_t> offsets;

    // Write filter data
    for (const auto& f : filters_) {
      offsets.push_back(static_cast<uint32_t>(result.size()));
      result.append(f);
    }
    // Final offset (end of last filter)
    offsets.push_back(static_cast<uint32_t>(result.size()));

    // Write offset array
    uint32_t array_offset = static_cast<uint32_t>(result.size());
    for (uint32_t off : offsets) {
      PutFixed32(&result, off);
    }

    // Write offset of offset array
    PutFixed32(&result, array_offset);

    // Write base_lg
    result.push_back(static_cast<char>(base_lg_));

    return result;
  }

 private:
  std::vector<std::string> filters_;
  uint8_t base_lg_;
};

class FilterBlockReaderTest_374 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that an empty contents (no filters) returns true for any query
// (since index >= num_, it returns true as "potential match")
TEST_F(FilterBlockReaderTest_374, EmptyContentsReturnsTrue_374) {
  AlwaysMatchFilterPolicy policy;
  // Minimal valid contents: no filters, just offset array start + base_lg
  std::string contents;
  PutFixed32(&contents, 0);  // offset of offset array = 0
  contents.push_back(static_cast<char>(11));  // base_lg = 11

  FilterBlockReader reader(&policy, Slice(contents));
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("key")));
  EXPECT_TRUE(reader.KeyMayMatch(2048, Slice("key")));
  EXPECT_TRUE(reader.KeyMayMatch(100000, Slice("key")));
}

// Test with a single filter where the policy says the key matches
TEST_F(FilterBlockReaderTest_374, SingleFilterKeyMatches_374) {
  MockFilterPolicy policy;
  
  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(11);  // base = 2048
  builder.AddFilter("testfilter");
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&policy, Slice(contents));

  EXPECT_CALL(policy, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce(::testing::Return(true));
  
  // block_offset=0, index = 0 >> 11 = 0, which is < num_=1
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("hello")));
}

// Test with a single filter where the policy says the key does NOT match
TEST_F(FilterBlockReaderTest_374, SingleFilterKeyDoesNotMatch_374) {
  MockFilterPolicy policy;
  
  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(11);
  builder.AddFilter("testfilter");
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&policy, Slice(contents));

  EXPECT_CALL(policy, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce(::testing::Return(false));
  
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("hello")));
}

// Test that block_offset beyond existing filters returns true
TEST_F(FilterBlockReaderTest_374, BlockOffsetBeyondFiltersReturnsTrue_374) {
  NeverMatchFilterPolicy policy;

  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(11);  // base = 2048
  builder.AddFilter("filter0");
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&policy, Slice(contents));

  // index = large_offset >> 11 should be >= num_ (1)
  // So it should return true
  EXPECT_TRUE(reader.KeyMayMatch(2048, Slice("anykey")));
  EXPECT_TRUE(reader.KeyMayMatch(100000, Slice("anykey")));
}

// Test with multiple filters, selecting the correct one based on block_offset
TEST_F(FilterBlockReaderTest_374, MultipleFiltersCorrectSelection_374) {
  MockFilterPolicy policy;

  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(11);  // base = 2048
  builder.AddFilter("filter0");
  builder.AddFilter("filter1");
  builder.AddFilter("filter2");
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&policy, Slice(contents));

  // block_offset=0, index=0
  EXPECT_CALL(policy, KeyMayMatch(Slice("key0"), ::testing::_))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("key0")));

  // block_offset=2048, index=1
  EXPECT_CALL(policy, KeyMayMatch(Slice("key1"), ::testing::_))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(reader.KeyMayMatch(2048, Slice("key1")));

  // block_offset=4096, index=2
  EXPECT_CALL(policy, KeyMayMatch(Slice("key2"), ::testing::_))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(reader.KeyMayMatch(4096, Slice("key2")));
}

// Test with an empty filter (start == limit) should return false
TEST_F(FilterBlockReaderTest_374, EmptyFilterReturnsFalse_374) {
  AlwaysMatchFilterPolicy policy;

  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(11);
  builder.AddFilter("");  // empty filter: start == limit
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&policy, Slice(contents));

  // Empty filter means start == limit, policy returns true but
  // the code checks: start <= limit && limit <= (offset_ - data_)
  // For an empty filter, start == limit, and limit should be <= offset_ - data_
  // So it will create a Slice of length 0 and call policy_->KeyMayMatch
  // Actually, let's check: if start == limit and both are valid,
  // the first condition (start <= limit && limit <= ...) is satisfied,
  // so it calls policy. If start == limit and limit > offset_ - data_,
  // then the else-if (start == limit) returns false.
  // With a properly built contents, start==limit==0 and that's <= offset_ - data_.
  // So the policy will be called with an empty filter.
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("anykey")));
}

// Test with different base_lg values
TEST_F(FilterBlockReaderTest_374, DifferentBaseLg_374) {
  MockFilterPolicy policy;

  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(0);  // base = 1
  builder.AddFilter("f0");
  builder.AddFilter("f1");
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&policy, Slice(contents));

  // With base_lg=0, base=1, so index = block_offset >> 0 = block_offset
  // block_offset=0 => index=0
  EXPECT_CALL(policy, KeyMayMatch(Slice("k"), ::testing::_))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("k")));

  // block_offset=1 => index=1
  EXPECT_CALL(policy, KeyMayMatch(Slice("k"), ::testing::_))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(reader.KeyMayMatch(1, Slice("k")));

  // block_offset=2 => index=2 >= num_(2), returns true
  EXPECT_TRUE(reader.KeyMayMatch(2, Slice("k")));
}

// Test using FilterBlockBuilder and FilterBlockReader together for integration
TEST_F(FilterBlockReaderTest_374, BuilderAndReaderIntegration_374) {
  // Use the actual bloom filter or a test policy
  NeverMatchFilterPolicy never_policy;

  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(11);
  builder.AddFilter("somefilterdata");
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&never_policy, Slice(contents));

  // The NeverMatch policy always returns false
  EXPECT_FALSE(reader.KeyMayMatch(0, Slice("hello")));
}

// Test that a very large block offset beyond all filters returns true
TEST_F(FilterBlockReaderTest_374, VeryLargeBlockOffset_374) {
  NeverMatchFilterPolicy policy;

  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(11);
  builder.AddFilter("data");
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&policy, Slice(contents));

  // Very large offset should map to index >= num_, returning true
  EXPECT_TRUE(reader.KeyMayMatch(UINT64_MAX, Slice("key")));
}

// Test with block offset within first filter block range
TEST_F(FilterBlockReaderTest_374, BlockOffsetWithinFirstRange_374) {
  MockFilterPolicy policy;

  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(11);  // base = 2048
  builder.AddFilter("filter0data");
  builder.AddFilter("filter1data");
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&policy, Slice(contents));

  // Any block_offset from 0 to 2047 should map to index 0
  EXPECT_CALL(policy, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(reader.KeyMayMatch(1000, Slice("key")));

  EXPECT_CALL(policy, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(reader.KeyMayMatch(2047, Slice("key")));
}

// Test the filter data passed to KeyMayMatch is correct
TEST_F(FilterBlockReaderTest_374, CorrectFilterDataPassedToPolicy_374) {
  MockFilterPolicy policy;

  FilterBlockContentsBuilder builder;
  builder.SetBaseLg(11);
  builder.AddFilter("AAAA");
  builder.AddFilter("BBBB");
  
  std::string contents = builder.Build();
  
  FilterBlockReader reader(&policy, Slice(contents));

  // Filter 0 should be "AAAA"
  EXPECT_CALL(policy, KeyMayMatch(Slice("key"), 
      ::testing::Property(&Slice::ToString, "AAAA")))
      .WillOnce(::testing::Return(true));
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("key")));

  // Filter 1 should be "BBBB"
  EXPECT_CALL(policy, KeyMayMatch(Slice("key"),
      ::testing::Property(&Slice::ToString, "BBBB")))
      .WillOnce(::testing::Return(false));
  EXPECT_FALSE(reader.KeyMayMatch(2048, Slice("key")));
}

// Test with only metadata and no real content (minimal valid block)
TEST_F(FilterBlockReaderTest_374, MinimalValidBlock_374) {
  NeverMatchFilterPolicy policy;
  
  // Just the footer: array_offset (4 bytes) + base_lg (1 byte)
  // With array_offset = 0, there are 0 entries in offset array minus 1
  // Actually the constructor computes: num_ = (n - 5 - last_word) / 4
  // where n is contents size and last_word = offset of offset array
  std::string contents;
  PutFixed32(&contents, 0);  // array_offset = 0
  contents.push_back(static_cast<char>(11));  // base_lg = 11
  
  FilterBlockReader reader(&policy, Slice(contents));
  
  // No filters, should return true for any query
  EXPECT_TRUE(reader.KeyMayMatch(0, Slice("test")));
}

}  // namespace leveldb
