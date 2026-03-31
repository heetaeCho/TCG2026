#include "gtest/gtest.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

// Forward declaration of the C API function we're testing
struct leveldb_filterpolicy_t;
extern "C" {
leveldb_filterpolicy_t* leveldb_filterpolicy_create_bloom(int bits_per_key);
}

// We need access to FilterPolicy since leveldb_filterpolicy_t inherits from it
using leveldb::FilterPolicy;
using leveldb::Slice;

class BloomFilterPolicyTest_271 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (policy_ != nullptr) {
      delete policy_;
      policy_ = nullptr;
    }
  }

  FilterPolicy* policy_ = nullptr;
};

TEST_F(BloomFilterPolicyTest_271, CreateBloomReturnsNonNull_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);
}

TEST_F(BloomFilterPolicyTest_271, NameReturnsBloomFilterName_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);
  const char* name = policy_->Name();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "leveldb.BuiltinBloomFilter2");
}

TEST_F(BloomFilterPolicyTest_271, CreateFilterProducesNonEmptyOutput_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);

  Slice keys[] = {Slice("hello"), Slice("world"), Slice("foo")};
  std::string dst;
  policy_->CreateFilter(keys, 3, &dst);
  EXPECT_FALSE(dst.empty());
}

TEST_F(BloomFilterPolicyTest_271, KeyMayMatchReturnsTrueForInsertedKeys_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);

  Slice keys[] = {Slice("hello"), Slice("world"), Slice("foo")};
  std::string filter;
  policy_->CreateFilter(keys, 3, &filter);

  // All inserted keys should match
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("hello"), Slice(filter)));
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("world"), Slice(filter)));
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("foo"), Slice(filter)));
}

TEST_F(BloomFilterPolicyTest_271, KeyMayMatchMayReturnFalseForNonInsertedKeys_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);

  Slice keys[] = {Slice("hello"), Slice("world"), Slice("foo")};
  std::string filter;
  policy_->CreateFilter(keys, 3, &filter);

  // Non-inserted keys might return false (bloom filter allows false positives but not false negatives)
  // We test multiple keys; statistically, at least some should return false
  int false_count = 0;
  const int num_tests = 100;
  for (int i = 0; i < num_tests; i++) {
    std::string key = "nonexistent_key_" + std::to_string(i);
    if (!policy_->KeyMayMatch(Slice(key), Slice(filter))) {
      false_count++;
    }
  }
  // With 10 bits per key and only 3 keys, false positive rate should be low
  // Expect at least some keys to not match
  EXPECT_GT(false_count, 0);
}

TEST_F(BloomFilterPolicyTest_271, CreateFilterWithSingleKey_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);

  Slice keys[] = {Slice("single")};
  std::string filter;
  policy_->CreateFilter(keys, 1, &filter);
  EXPECT_FALSE(filter.empty());
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("single"), Slice(filter)));
}

TEST_F(BloomFilterPolicyTest_271, CreateFilterWithZeroKeys_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);

  std::string filter;
  policy_->CreateFilter(nullptr, 0, &filter);
  // Even with zero keys, the filter should be created (may have minimal content)
  // A non-existent key should ideally not match
}

TEST_F(BloomFilterPolicyTest_271, DifferentBitsPerKeyValues_271) {
  // Test with small bits_per_key
  policy_ = leveldb_filterpolicy_create_bloom(1);
  ASSERT_NE(policy_, nullptr);

  Slice keys[] = {Slice("a"), Slice("b"), Slice("c")};
  std::string filter1;
  policy_->CreateFilter(keys, 3, &filter1);
  EXPECT_FALSE(filter1.empty());
  
  // Inserted keys should still match
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("a"), Slice(filter1)));
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("b"), Slice(filter1)));
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("c"), Slice(filter1)));

  delete policy_;

  // Test with larger bits_per_key
  policy_ = leveldb_filterpolicy_create_bloom(100);
  ASSERT_NE(policy_, nullptr);

  std::string filter2;
  policy_->CreateFilter(keys, 3, &filter2);
  EXPECT_FALSE(filter2.empty());

  EXPECT_TRUE(policy_->KeyMayMatch(Slice("a"), Slice(filter2)));
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("b"), Slice(filter2)));
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("c"), Slice(filter2)));
}

TEST_F(BloomFilterPolicyTest_271, LargerBitsPerKeyReducesFalsePositiveRate_271) {
  Slice keys[] = {Slice("key1"), Slice("key2"), Slice("key3"),
                  Slice("key4"), Slice("key5")};

  // Create filter with low bits_per_key
  auto* low_policy = leveldb_filterpolicy_create_bloom(2);
  std::string low_filter;
  low_policy->CreateFilter(keys, 5, &low_filter);

  // Create filter with high bits_per_key
  auto* high_policy = leveldb_filterpolicy_create_bloom(20);
  std::string high_filter;
  high_policy->CreateFilter(keys, 5, &high_filter);

  int low_false_positives = 0;
  int high_false_positives = 0;
  const int num_tests = 1000;

  for (int i = 0; i < num_tests; i++) {
    std::string test_key = "test_nonexistent_" + std::to_string(i);
    if (low_policy->KeyMayMatch(Slice(test_key), Slice(low_filter))) {
      low_false_positives++;
    }
    if (high_policy->KeyMayMatch(Slice(test_key), Slice(high_filter))) {
      high_false_positives++;
    }
  }

  // Higher bits per key should give fewer or equal false positives
  EXPECT_LE(high_false_positives, low_false_positives);

  delete low_policy;
  delete high_policy;
  policy_ = nullptr;  // Prevent double-delete in TearDown
}

TEST_F(BloomFilterPolicyTest_271, EmptyKeyFilter_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);

  Slice keys[] = {Slice("", 0)};
  std::string filter;
  policy_->CreateFilter(keys, 1, &filter);
  EXPECT_FALSE(filter.empty());
  EXPECT_TRUE(policy_->KeyMayMatch(Slice("", 0), Slice(filter)));
}

TEST_F(BloomFilterPolicyTest_271, BinaryKeyData_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);

  std::string key1("\x00\x01\x02", 3);
  std::string key2("\xff\xfe\xfd", 3);
  Slice keys[] = {Slice(key1), Slice(key2)};
  std::string filter;
  policy_->CreateFilter(keys, 2, &filter);
  EXPECT_FALSE(filter.empty());
  EXPECT_TRUE(policy_->KeyMayMatch(Slice(key1), Slice(filter)));
  EXPECT_TRUE(policy_->KeyMayMatch(Slice(key2), Slice(filter)));
}

TEST_F(BloomFilterPolicyTest_271, ManyKeysFilter_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);

  const int num_keys = 10000;
  std::vector<std::string> key_strings;
  key_strings.reserve(num_keys);
  for (int i = 0; i < num_keys; i++) {
    key_strings.push_back("key_" + std::to_string(i));
  }

  std::vector<Slice> keys;
  keys.reserve(num_keys);
  for (const auto& s : key_strings) {
    keys.push_back(Slice(s));
  }

  std::string filter;
  policy_->CreateFilter(keys.data(), num_keys, &filter);
  EXPECT_FALSE(filter.empty());

  // All inserted keys should match
  for (int i = 0; i < num_keys; i++) {
    EXPECT_TRUE(policy_->KeyMayMatch(keys[i], Slice(filter)))
        << "Key " << key_strings[i] << " should match";
  }
}

TEST_F(BloomFilterPolicyTest_271, DeleteDoesNotCrash_271) {
  // Simply create and delete to ensure destructor works properly
  FilterPolicy* p = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(p, nullptr);
  delete p;
  // If we reach here without crash, the test passes
  policy_ = nullptr;  // Don't double delete in TearDown
}

TEST_F(BloomFilterPolicyTest_271, KeyMayMatchWithEmptyFilter_271) {
  policy_ = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy_, nullptr);

  std::string empty_filter;
  // KeyMayMatch with empty filter - behavior depends on implementation
  // but it should not crash
  bool result = policy_->KeyMayMatch(Slice("test"), Slice(empty_filter));
  // We just verify it doesn't crash; result can be true or false
  (void)result;
}
