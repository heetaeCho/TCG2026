// File: util/bloom_test.cc

#include "gtest/gtest.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

#include <memory>
#include <string>
#include <vector>

using leveldb::FilterPolicy;
using leveldb::NewBloomFilterPolicy;
using leveldb::Slice;

namespace {

class BloomFilterPolicyTest_461 : public ::testing::Test {
protected:
  static std::vector<Slice> MakeKeySlices(const std::vector<std::string>& keys,
                                          std::vector<std::string>& backing) {
    // Keep a backing copy alive so the Slice data remains valid.
    backing = keys;
    std::vector<Slice> slices;
    slices.reserve(backing.size());
    for (const auto& k : backing) {
      slices.emplace_back(k);
    }
    return slices;
  }
};

// Basic construction: non-null return and deletable.
TEST(BloomFilterPolicyTest_461, ReturnsNonNull_461) {
  const FilterPolicy* policy = NewBloomFilterPolicy(10);
  ASSERT_NE(policy, nullptr);
  delete policy;  // ensure no crash/leak on destruction
}

// Name() should be non-empty and stable across instances.
TEST(BloomFilterPolicyTest_461, NameIsStableAndNonEmpty_461) {
  std::unique_ptr<const FilterPolicy> p1(NewBloomFilterPolicy(5));
  std::unique_ptr<const FilterPolicy> p2(NewBloomFilterPolicy(12));

  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);

  ASSERT_FALSE(std::string(p1->Name()).empty());
  // The builtin Bloom filter policy name should not depend on bits_per_key.
  EXPECT_STREQ(p1->Name(), p2->Name());
}

// A filter must (by Bloom filter property) report true for inserted keys.
TEST(BloomFilterPolicyTest_461, InsertedKeysMayMatch_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(10));
  ASSERT_NE(policy, nullptr);

  std::vector<std::string> backing;
  std::vector<Slice> keys = MakeKeySlices({"a", "b", "c", "hello", "world"}, backing);

  std::string filter;
  policy->CreateFilter(&keys[0], static_cast<int>(keys.size()), &filter);

  for (const auto& k : keys) {
    EXPECT_TRUE(policy->KeyMayMatch(k, filter)) << "Expected inserted key to match: " << k.ToString();
  }
}

// Works for a very small bits_per_key (boundary-ish), still no false negatives.
TEST(BloomFilterPolicyTest_461, SmallBitsPerKeyStillMatchesInserted_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(1));  // very small filter
  ASSERT_NE(policy, nullptr);

  std::vector<std::string> backing;
  std::vector<Slice> keys = MakeKeySlices({"x", "y", "z"}, backing);

  std::string filter;
  policy->CreateFilter(&keys[0], static_cast<int>(keys.size()), &filter);

  for (const auto& k : keys) {
    EXPECT_TRUE(policy->KeyMayMatch(k, filter)) << "Expected inserted key to match with small bits_per_key";
  }
}

// bits_per_key = 0 should still create a usable policy (constructor clamps internally).
TEST(BloomFilterPolicyTest_461, ZeroBitsPerKeyStillUsable_461) {
  std::unique_ptr<const FilterPolicy> policy(NewBloomFilterPolicy(0));
  ASSERT_NE(policy, nullptr);

  // Include duplicates and binary data to ensure robustness of the public API.
  const std::string with_nulls = std::string("bin\0ary", 7);
  std::vector<std::string> backing;
  std::vector<Slice> keys = MakeKeySlices({"dup", "dup", with_nulls}, backing);

  std::string filter;
  policy->CreateFilter(&keys[0], static_cast<int>(keys.size()), &filter);

  for (const auto& k : keys) {
    EXPECT_TRUE(policy->KeyMayMatch(k, filter)) << "Expected inserted (incl. duplicates/binary) key to match";
  }
}

// Independent policies with different bits_per_key both preserve no-false-negative guarantee.
TEST(BloomFilterPolicyTest_461, DifferentBitsPerKeyNoFalseNegatives_461) {
  std::unique_ptr<const FilterPolicy> p_small(NewBloomFilterPolicy(4));
  std::unique_ptr<const FilterPolicy> p_large(NewBloomFilterPolicy(16));
  ASSERT_NE(p_small, nullptr);
  ASSERT_NE(p_large, nullptr);

  std::vector<std::string> backing;
  std::vector<Slice> keys = MakeKeySlices({"k1", "k2", "k3", "longer-key"}, backing);

  std::string filter_small;
  std::string filter_large;

  p_small->CreateFilter(&keys[0], static_cast<int>(keys.size()), &filter_small);
  p_large->CreateFilter(&keys[0], static_cast<int>(keys.size()), &filter_large);

  for (const auto& k : keys) {
    EXPECT_TRUE(p_small->KeyMayMatch(k, filter_small)) << "Inserted key should match (small bits_per_key).";
    EXPECT_TRUE(p_large->KeyMayMatch(k, filter_large)) << "Inserted key should match (large bits_per_key).";
  }
}

}  // namespace
