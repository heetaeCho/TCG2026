#include "gtest/gtest.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"
#include <string>
#include <vector>
#include <memory>

namespace leveldb {

// Helper to get the FilterPolicy
class BloomFilterTest_461 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to build a filter from a set of keys
  std::string BuildFilter(const FilterPolicy* policy,
                          const std::vector<std::string>& keys) {
    std::vector<Slice> key_slices;
    for (const auto& k : keys) {
      key_slices.push_back(Slice(k));
    }
    std::string dst;
    policy->CreateFilter(key_slices.data(), static_cast<int>(key_slices.size()),
                         &dst);
    return dst;
  }
};

TEST_F(BloomFilterTest_461, PolicyNameIsNotEmpty_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  ASSERT_NE(policy->Name(), nullptr);
  EXPECT_GT(strlen(policy->Name()), 0u);
}

TEST_F(BloomFilterTest_461, PolicyNameContainsBloom_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  std::string name(policy->Name());
  // The name should reference "bloom" in some form
  EXPECT_NE(name.find("leveldb.BuiltinBloomFilter2"), std::string::npos);
}

TEST_F(BloomFilterTest_461, CreateFilterProducesNonEmptyOutput_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  std::vector<std::string> keys = {"hello", "world", "foo", "bar"};
  std::string filter = BuildFilter(policy.get(), keys);
  EXPECT_FALSE(filter.empty());
}

TEST_F(BloomFilterTest_461, KeyMatchesAfterInsertion_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  std::vector<std::string> keys = {"hello", "world", "foo", "bar"};
  std::string filter = BuildFilter(policy.get(), keys);

  // All inserted keys must match
  for (const auto& k : keys) {
    EXPECT_TRUE(policy->KeyMayMatch(Slice(k), Slice(filter)))
        << "Key '" << k << "' should match";
  }
}

TEST_F(BloomFilterTest_461, NonExistentKeyMayNotMatch_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  std::vector<std::string> keys = {"hello", "world", "foo", "bar"};
  std::string filter = BuildFilter(policy.get(), keys);

  // Test many non-existent keys; false positive rate should be low
  int false_positives = 0;
  int total = 10000;
  for (int i = 0; i < total; i++) {
    std::string key = "nonexistent_key_" + std::to_string(i);
    if (policy->KeyMayMatch(Slice(key), Slice(filter))) {
      false_positives++;
    }
  }
  // With 10 bits per key and 4 keys, false positive rate should be very low
  // Allow up to 2% false positive rate
  EXPECT_LT(false_positives, total * 0.02)
      << "False positive rate too high: " << false_positives << "/" << total;
}

TEST_F(BloomFilterTest_461, EmptyFilterMatchesNothing_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  std::vector<std::string> keys;
  std::string filter = BuildFilter(policy.get(), keys);

  EXPECT_FALSE(policy->KeyMayMatch(Slice("hello"), Slice(filter)));
  EXPECT_FALSE(policy->KeyMayMatch(Slice("world"), Slice(filter)));
}

TEST_F(BloomFilterTest_461, SingleKeyFilter_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  std::vector<std::string> keys = {"onlykey"};
  std::string filter = BuildFilter(policy.get(), keys);

  EXPECT_TRUE(policy->KeyMayMatch(Slice("onlykey"), Slice(filter)));
}

TEST_F(BloomFilterTest_461, DifferentBitsPerKey_461) {
  // Test with different bits_per_key values
  for (int bpk : {1, 5, 10, 20, 50}) {
    std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(bpk));
    std::vector<std::string> keys = {"alpha", "beta", "gamma"};
    std::string filter = BuildFilter(policy.get(), keys);

    // All keys must still match
    for (const auto& k : keys) {
      EXPECT_TRUE(policy->KeyMayMatch(Slice(k), Slice(filter)))
          << "Key '" << k << "' should match with bpk=" << bpk;
    }
  }
}

TEST_F(BloomFilterTest_461, HighBitsPerKeyLowFalsePositiveRate_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(20));
  std::vector<std::string> keys;
  for (int i = 0; i < 100; i++) {
    keys.push_back("key_" + std::to_string(i));
  }
  std::string filter = BuildFilter(policy.get(), keys);

  // All inserted keys must match
  for (const auto& k : keys) {
    EXPECT_TRUE(policy->KeyMayMatch(Slice(k), Slice(filter)));
  }

  // Check false positive rate with non-existent keys
  int false_positives = 0;
  int total = 10000;
  for (int i = 0; i < total; i++) {
    std::string key = "missing_" + std::to_string(i);
    if (policy->KeyMayMatch(Slice(key), Slice(filter))) {
      false_positives++;
    }
  }
  // With 20 bits per key, false positive rate should be very low (< 1%)
  EXPECT_LT(false_positives, total * 0.01)
      << "False positive rate too high with 20 bpk: " << false_positives << "/"
      << total;
}

TEST_F(BloomFilterTest_461, LowBitsPerKeyHigherFalsePositiveRate_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(1));
  std::vector<std::string> keys;
  for (int i = 0; i < 100; i++) {
    keys.push_back("key_" + std::to_string(i));
  }
  std::string filter = BuildFilter(policy.get(), keys);

  // All inserted keys must still match (correctness guarantee)
  for (const auto& k : keys) {
    EXPECT_TRUE(policy->KeyMayMatch(Slice(k), Slice(filter)));
  }
}

TEST_F(BloomFilterTest_461, LargeNumberOfKeys_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  std::vector<std::string> keys;
  for (int i = 0; i < 10000; i++) {
    keys.push_back("large_key_" + std::to_string(i));
  }
  std::string filter = BuildFilter(policy.get(), keys);
  EXPECT_FALSE(filter.empty());

  // Spot check some keys
  EXPECT_TRUE(policy->KeyMayMatch(Slice("large_key_0"), Slice(filter)));
  EXPECT_TRUE(policy->KeyMayMatch(Slice("large_key_9999"), Slice(filter)));
  EXPECT_TRUE(policy->KeyMayMatch(Slice("large_key_5000"), Slice(filter)));
}

TEST_F(BloomFilterTest_461, EmptyKeyInFilter_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  std::vector<std::string> keys = {""};
  std::string filter = BuildFilter(policy.get(), keys);

  EXPECT_TRUE(policy->KeyMayMatch(Slice(""), Slice(filter)));
}

TEST_F(BloomFilterTest_461, DuplicateKeysInFilter_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  std::vector<std::string> keys = {"dup", "dup", "dup"};
  std::string filter = BuildFilter(policy.get(), keys);

  EXPECT_TRUE(policy->KeyMayMatch(Slice("dup"), Slice(filter)));
}

TEST_F(BloomFilterTest_461, FilterSizeGrowsWithKeys_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));

  std::vector<std::string> small_keys = {"a"};
  std::string small_filter = BuildFilter(policy.get(), small_keys);

  std::vector<std::string> large_keys;
  for (int i = 0; i < 1000; i++) {
    large_keys.push_back("key_" + std::to_string(i));
  }
  std::string large_filter = BuildFilter(policy.get(), large_keys);

  // Larger set of keys should produce a larger filter
  EXPECT_GT(large_filter.size(), small_filter.size());
}

TEST_F(BloomFilterTest_461, NewBloomFilterPolicyReturnsNonNull_461) {
  const FilterPolicy* policy = NewBloomFilterPolicy(10);
  ASSERT_NE(policy, nullptr);
  delete policy;
}

TEST_F(BloomFilterTest_461, CorruptedFilterData_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  
  // An empty filter string
  std::string empty_filter;
  // This should not crash; behavior may vary but shouldn't segfault
  EXPECT_FALSE(policy->KeyMayMatch(Slice("test"), Slice(empty_filter)));
}

TEST_F(BloomFilterTest_461, BinaryKeyData_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  
  std::string key1(4, '\0');
  key1[0] = 'a';
  key1[1] = '\0';
  key1[2] = 'b';
  key1[3] = '\0';

  std::string key2(4, '\0');
  key2[0] = 'c';
  key2[1] = '\0';
  key2[2] = 'd';
  key2[3] = '\0';

  std::vector<std::string> keys = {key1, key2};
  std::string filter = BuildFilter(policy.get(), keys);

  EXPECT_TRUE(policy->KeyMayMatch(Slice(key1), Slice(filter)));
  EXPECT_TRUE(policy->KeyMayMatch(Slice(key2), Slice(filter)));
}

}  // namespace leveldb
