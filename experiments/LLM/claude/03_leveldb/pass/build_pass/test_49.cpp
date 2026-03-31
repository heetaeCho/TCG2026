#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "util/coding.h"

namespace leveldb {

// Helper to construct an internal key from user key, sequence number, and value type
static std::string MakeInternalKey(const std::string& user_key, SequenceNumber seq, ValueType type) {
  std::string result = user_key;
  PutFixed64(&result, (seq << 8) | static_cast<uint64_t>(type));
  return result;
}

class InternalKeyComparatorTest_49 : public ::testing::Test {
 protected:
  InternalKeyComparatorTest_49()
      : cmp_(BytewiseComparator()) {}

  InternalKeyComparator cmp_;
};

// Test that user_comparator() returns the comparator passed during construction
TEST_F(InternalKeyComparatorTest_49, UserComparatorReturnsCorrectComparator_49) {
  EXPECT_EQ(cmp_.user_comparator(), BytewiseComparator());
}

// Test that Name() returns a non-null, non-empty string
TEST_F(InternalKeyComparatorTest_49, NameReturnsNonNull_49) {
  const char* name = cmp_.Name();
  ASSERT_NE(name, nullptr);
  EXPECT_GT(strlen(name), 0u);
}

// Test Compare with identical internal keys returns 0
TEST_F(InternalKeyComparatorTest_49, CompareIdenticalKeys_49) {
  std::string key = MakeInternalKey("foo", 100, kTypeValue);
  EXPECT_EQ(cmp_.Compare(Slice(key), Slice(key)), 0);
}

// Test Compare: different user keys, ordering follows user key order
TEST_F(InternalKeyComparatorTest_49, CompareDifferentUserKeys_49) {
  std::string key_a = MakeInternalKey("aaa", 100, kTypeValue);
  std::string key_b = MakeInternalKey("bbb", 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(Slice(key_a), Slice(key_b)), 0);
  EXPECT_GT(cmp_.Compare(Slice(key_b), Slice(key_a)), 0);
}

// Test Compare: same user key, higher sequence number comes first (smaller in order)
TEST_F(InternalKeyComparatorTest_49, CompareSameUserKeyDifferentSequence_49) {
  std::string key_high_seq = MakeInternalKey("foo", 200, kTypeValue);
  std::string key_low_seq = MakeInternalKey("foo", 100, kTypeValue);
  // Higher sequence number should sort before (be "less than") lower sequence number
  EXPECT_LT(cmp_.Compare(Slice(key_high_seq), Slice(key_low_seq)), 0);
  EXPECT_GT(cmp_.Compare(Slice(key_low_seq), Slice(key_high_seq)), 0);
}

// Test Compare: same user key, same sequence, different type
TEST_F(InternalKeyComparatorTest_49, CompareSameUserKeySameSeqDifferentType_49) {
  std::string key_value = MakeInternalKey("foo", 100, kTypeValue);
  std::string key_deletion = MakeInternalKey("foo", 100, kTypeDeletion);
  // kTypeValue (1) > kTypeDeletion (0), so kTypeValue should sort first (smaller)
  EXPECT_LT(cmp_.Compare(Slice(key_value), Slice(key_deletion)), 0);
  EXPECT_GT(cmp_.Compare(Slice(key_deletion), Slice(key_value)), 0);
}

// Test Compare using InternalKey objects
TEST_F(InternalKeyComparatorTest_49, CompareInternalKeyObjects_49) {
  InternalKey a("aaa", 100, kTypeValue);
  InternalKey b("bbb", 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(a, b), 0);
  EXPECT_GT(cmp_.Compare(b, a), 0);
  EXPECT_EQ(cmp_.Compare(a, a), 0);
}

// Test Compare using InternalKey objects with same user key different sequence
TEST_F(InternalKeyComparatorTest_49, CompareInternalKeyObjectsSameUserKey_49) {
  InternalKey a("foo", 200, kTypeValue);
  InternalKey b("foo", 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(a, b), 0);  // higher seq sorts first
}

// Test FindShortestSeparator modifies start
TEST_F(InternalKeyComparatorTest_49, FindShortestSeparator_49) {
  std::string start = MakeInternalKey("foo", 100, kTypeValue);
  std::string limit = MakeInternalKey("goo", 100, kTypeValue);
  std::string original_start = start;
  cmp_.FindShortestSeparator(&start, Slice(limit));
  // The result should be >= original start and <= limit
  EXPECT_LE(cmp_.Compare(Slice(original_start), Slice(start)), 0);
  EXPECT_LE(cmp_.Compare(Slice(start), Slice(limit)), 0);
}

// Test FindShortestSeparator with identical keys should not change start to be > limit
TEST_F(InternalKeyComparatorTest_49, FindShortestSeparatorIdenticalKeys_49) {
  std::string start = MakeInternalKey("foo", 100, kTypeValue);
  std::string limit = start;
  std::string original_start = start;
  cmp_.FindShortestSeparator(&start, Slice(limit));
  // start should still be <= limit
  EXPECT_LE(cmp_.Compare(Slice(original_start), Slice(start)), 0);
}

// Test FindShortSuccessor modifies key to be >= original
TEST_F(InternalKeyComparatorTest_49, FindShortSuccessor_49) {
  std::string key = MakeInternalKey("foo", 100, kTypeValue);
  std::string original_key = key;
  cmp_.FindShortSuccessor(&key);
  // Result should be >= original key
  EXPECT_LE(cmp_.Compare(Slice(original_key), Slice(key)), 0);
}

// Test boundary: empty user key
TEST_F(InternalKeyComparatorTest_49, CompareEmptyUserKey_49) {
  std::string key_a = MakeInternalKey("", 100, kTypeValue);
  std::string key_b = MakeInternalKey("a", 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(Slice(key_a), Slice(key_b)), 0);
}

// Test boundary: sequence number 0
TEST_F(InternalKeyComparatorTest_49, CompareSequenceNumberZero_49) {
  std::string key_a = MakeInternalKey("foo", 0, kTypeValue);
  std::string key_b = MakeInternalKey("foo", 1, kTypeValue);
  // Higher seq comes first
  EXPECT_GT(cmp_.Compare(Slice(key_a), Slice(key_b)), 0);
}

// Test boundary: very large sequence numbers
TEST_F(InternalKeyComparatorTest_49, CompareLargeSequenceNumbers_49) {
  SequenceNumber large_seq = (1ull << 56) - 1;  // max sequence number
  std::string key_a = MakeInternalKey("foo", large_seq, kTypeValue);
  std::string key_b = MakeInternalKey("foo", large_seq - 1, kTypeValue);
  EXPECT_LT(cmp_.Compare(Slice(key_a), Slice(key_b)), 0);
}

// Test that constructing with a different comparator stores it correctly
TEST_F(InternalKeyComparatorTest_49, ConstructorStoresUserComparator_49) {
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator ikc(bytewise);
  EXPECT_EQ(ikc.user_comparator(), bytewise);
}

// Test FindShortestSeparator when start > limit (no change expected or at least valid result)
TEST_F(InternalKeyComparatorTest_49, FindShortestSeparatorStartAfterLimit_49) {
  std::string start = MakeInternalKey("zoo", 100, kTypeValue);
  std::string limit = MakeInternalKey("aaa", 100, kTypeValue);
  std::string original_start = start;
  cmp_.FindShortestSeparator(&start, Slice(limit));
  // When start > limit, start should remain unchanged
  EXPECT_EQ(start, original_start);
}

}  // namespace leveldb
