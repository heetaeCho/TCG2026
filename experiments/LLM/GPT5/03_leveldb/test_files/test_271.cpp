// db_filterpolicy_bloom_test_271.cc
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

// Forward declarations to avoid relying on internal implementation details.
struct leveldb_filterpolicy_t : public leveldb::FilterPolicy;  // incomplete type is fine for upcast

// Factory under test (provided by the codebase).
leveldb_filterpolicy_t* leveldb_filterpolicy_create_bloom(int bits_per_key);

using leveldb::FilterPolicy;
using leveldb::Slice;

namespace {

// Small helper to convert std::string to Slice (by copy lifetime is managed by std::string).
inline Slice S(const std::string& s) { return Slice(s); }

// Test fixture to manage policy lifetime safely.
class BloomFilterPolicyTest_271 : public ::testing::Test {
protected:
  // We keep a base-class pointer to ensure we only use the public interface.
  const FilterPolicy* policy_ = nullptr;
  // Also keep the raw returned pointer for explicit delete in TearDown (virtual dtor).
  leveldb_filterpolicy_t* raw_ = nullptr;

  void SetUp() override {
    raw_ = leveldb_filterpolicy_create_bloom(/*bits_per_key=*/10);
    ASSERT_NE(raw_, nullptr);
    policy_ = static_cast<const FilterPolicy*>(raw_);
    ASSERT_NE(policy_, nullptr);
  }

  void TearDown() override {
    delete raw_;
    raw_ = nullptr;
    policy_ = nullptr;
  }
};

// --- Normal operation --------------------------------------------------------

TEST_F(BloomFilterPolicyTest_271, NameIsNonEmptyAndStable_271) {
  // Name should be a valid, non-empty C-string and stable across calls.
  const char* n1 = policy_->Name();
  const char* n2 = policy_->Name();
  ASSERT_NE(n1, nullptr);
  EXPECT_STRNE(n1, "");   // non-empty
  // Stability: the returned string content should be the same across calls.
  // We compare strings rather than pointers to avoid assumptions about storage.
  EXPECT_STREQ(n1, n2);
}

TEST_F(BloomFilterPolicyTest_271, InsertedKeysAlwaysMatch_271) {
  // Build a filter for a set of keys and verify each inserted key "may match".
  std::vector<std::string> keys_str = {"alpha", "beta", "gamma", "delta", "epsilon"};
  std::vector<Slice> keys;
  keys.reserve(keys_str.size());
  for (const auto& s : keys_str) keys.push_back(S(s));

  std::string filter_blob;
  policy_->CreateFilter(keys.data(), static_cast<int>(keys.size()), &filter_blob);
  ASSERT_FALSE(filter_blob.empty());  // observable effect: produced some filter bytes

  const Slice filter(filter_blob);
  for (const auto& s : keys_str) {
    EXPECT_TRUE(policy_->KeyMayMatch(S(s), filter))
        << "Expected inserted key to match: " << s;
  }
}

// --- Boundary conditions -----------------------------------------------------

TEST_F(BloomFilterPolicyTest_271, WorksWithZeroBitsPerKey_271) {
  // Create a brand-new policy with an extreme/edge bits_per_key and ensure basic behavior works.
  leveldb_filterpolicy_t* raw2 = leveldb_filterpolicy_create_bloom(/*bits_per_key=*/0);
  ASSERT_NE(raw2, nullptr);
  const FilterPolicy* p2 = static_cast<const FilterPolicy*>(raw2);

  std::vector<Slice> keys = {S("x"), S("y")};
  std::string filter_blob;
  p2->CreateFilter(keys.data(), static_cast<int>(keys.size()), &filter_blob);
  ASSERT_FALSE(filter_blob.empty());

  const Slice filter(filter_blob);
  EXPECT_TRUE(p2->KeyMayMatch(S("x"), filter));
  EXPECT_TRUE(p2->KeyMayMatch(S("y"), filter));

  delete raw2;  // ensure no crash/leak on destruction path
}

TEST_F(BloomFilterPolicyTest_271, HandlesDuplicateKeys_271) {
  // Duplicate entries should not break correctness for inserted keys.
  std::vector<Slice> keys = {S("dup"), S("dup"), S("unique")};

  std::string filter_blob;
  policy_->CreateFilter(keys.data(), static_cast<int>(keys.size()), &filter_blob);
  ASSERT_FALSE(filter_blob.empty());

  const Slice filter(filter_blob);
  EXPECT_TRUE(policy_->KeyMayMatch(S("dup"), filter));
  EXPECT_TRUE(policy_->KeyMayMatch(S("unique"), filter));
}

TEST_F(BloomFilterPolicyTest_271, HandlesEmptyKeySet_271) {
  // Creating a filter with zero keys should be safe and produce a usable filter blob (possibly empty).
  std::string filter_blob = "prefix";  // ensure function is free to modify/append/clear as per its contract
  policy_->CreateFilter(/*keys=*/nullptr, /*n=*/0, &filter_blob);

  // We only assert that KeyMayMatch is callable and does not crash.
  // Behavior for non-inserted keys is intentionally not asserted (black-box; Bloom filters can have false positives).
  Slice filter(filter_blob);
  (void)policy_->KeyMayMatch(S("anything"), filter);
}

// --- Exceptional/robustness (observable) ------------------------------------

TEST(BloomFilterPolicyStandalone_271, DeletionViaBasePointerIsSafe_271) {
  // Ensure the object can be deleted via the public base class pointer (virtual destructor).
  leveldb_filterpolicy_t* raw = leveldb_filterpolicy_create_bloom(5);
  ASSERT_NE(raw, nullptr);
  const FilterPolicy* base = static_cast<const FilterPolicy*>(raw);
  // Use it briefly:
  std::string filter_blob;
  std::vector<Slice> keys = {Slice("k1"), Slice("k2")};
  base->CreateFilter(keys.data(), static_cast<int>(keys.size()), &filter_blob);
  ASSERT_FALSE(filter_blob.empty());
  // Now delete via base pointer; should call the correct destructor chain without crashing.
  delete base;
}

}  // namespace
