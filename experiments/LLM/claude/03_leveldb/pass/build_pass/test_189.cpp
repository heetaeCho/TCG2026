#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <string>
#include <cstring>

namespace leveldb {

// Helper function to build an internal key from user key, sequence number, and value type
static std::string MakeInternalKey(const std::string& user_key, uint64_t seq, ValueType type) {
  std::string result = user_key;
  PutFixed64(&result, (seq << 8) | static_cast<uint64_t>(type));
  return result;
}

class InternalKeyComparatorTest_189 : public ::testing::Test {
 protected:
  InternalKeyComparatorTest_189()
      : cmp_(BytewiseComparator()) {}

  InternalKeyComparator cmp_;
};

// Test that two identical user keys with the same sequence number return 0
TEST_F(InternalKeyComparatorTest_189, SameKeysSameSequence_189) {
  std::string a = MakeInternalKey("hello", 100, kTypeValue);
  std::string b = MakeInternalKey("hello", 100, kTypeValue);
  EXPECT_EQ(0, cmp_.Compare(Slice(a), Slice(b)));
}

// Test that when user keys differ, the user key ordering takes precedence
TEST_F(InternalKeyComparatorTest_189, DifferentUserKeys_189) {
  std::string a = MakeInternalKey("abc", 100, kTypeValue);
  std::string b = MakeInternalKey("def", 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
  EXPECT_GT(cmp_.Compare(Slice(b), Slice(a)), 0);
}

// Test that for the same user key, a higher sequence number sorts first (earlier)
TEST_F(InternalKeyComparatorTest_189, SameUserKeyHigherSequenceFirst_189) {
  std::string a = MakeInternalKey("hello", 200, kTypeValue);
  std::string b = MakeInternalKey("hello", 100, kTypeValue);
  // Higher sequence number (200) should come before lower (100), so a < b
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test that for the same user key, a lower sequence number sorts later
TEST_F(InternalKeyComparatorTest_189, SameUserKeyLowerSequenceLater_189) {
  std::string a = MakeInternalKey("hello", 50, kTypeValue);
  std::string b = MakeInternalKey("hello", 200, kTypeValue);
  // Lower sequence number (50) should come after higher (200), so a > b
  EXPECT_GT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test with sequence number 0 vs 1
TEST_F(InternalKeyComparatorTest_189, SequenceNumberBoundary_189) {
  std::string a = MakeInternalKey("key", 1, kTypeValue);
  std::string b = MakeInternalKey("key", 0, kTypeValue);
  // seq 1 > seq 0, so a should come first
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test with different value types (kTypeValue vs kTypeDeletion) with same user key and seq
TEST_F(InternalKeyComparatorTest_189, SameKeyDifferentType_189) {
  std::string a = MakeInternalKey("key", 100, kTypeValue);
  std::string b = MakeInternalKey("key", 100, kTypeDeletion);
  // kTypeValue = 1, kTypeDeletion = 0
  // The packed number for a: (100 << 8) | 1
  // The packed number for b: (100 << 8) | 0
  // a has a larger packed number, so a should sort first (return -1)
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test with empty user keys
TEST_F(InternalKeyComparatorTest_189, EmptyUserKeys_189) {
  std::string a = MakeInternalKey("", 100, kTypeValue);
  std::string b = MakeInternalKey("", 50, kTypeValue);
  // Same user key (empty), seq 100 > 50, so a comes first
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test with very large sequence numbers
TEST_F(InternalKeyComparatorTest_189, LargeSequenceNumbers_189) {
  uint64_t max_seq = (1ULL << 56) - 1;  // Max sequence number
  std::string a = MakeInternalKey("key", max_seq, kTypeValue);
  std::string b = MakeInternalKey("key", max_seq - 1, kTypeValue);
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test that user key ordering dominates over sequence number ordering
TEST_F(InternalKeyComparatorTest_189, UserKeyDominatesOverSequence_189) {
  std::string a = MakeInternalKey("aaa", 1, kTypeValue);
  std::string b = MakeInternalKey("bbb", 1000000, kTypeValue);
  // "aaa" < "bbb" in user key, so a < b regardless of sequence number
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test reflexivity: Compare(a, a) == 0
TEST_F(InternalKeyComparatorTest_189, Reflexivity_189) {
  std::string a = MakeInternalKey("testkey", 42, kTypeValue);
  EXPECT_EQ(0, cmp_.Compare(Slice(a), Slice(a)));
}

// Test antisymmetry
TEST_F(InternalKeyComparatorTest_189, Antisymmetry_189) {
  std::string a = MakeInternalKey("alpha", 100, kTypeValue);
  std::string b = MakeInternalKey("beta", 100, kTypeValue);
  int ab = cmp_.Compare(Slice(a), Slice(b));
  int ba = cmp_.Compare(Slice(b), Slice(a));
  EXPECT_LT(ab, 0);
  EXPECT_GT(ba, 0);
}

// Test transitivity
TEST_F(InternalKeyComparatorTest_189, Transitivity_189) {
  std::string a = MakeInternalKey("key", 300, kTypeValue);
  std::string b = MakeInternalKey("key", 200, kTypeValue);
  std::string c = MakeInternalKey("key", 100, kTypeValue);
  // a < b < c (higher seq comes first)
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
  EXPECT_LT(cmp_.Compare(Slice(b), Slice(c)), 0);
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(c)), 0);
}

// Test Name() returns a non-null string
TEST_F(InternalKeyComparatorTest_189, NameNotNull_189) {
  const char* name = cmp_.Name();
  ASSERT_NE(name, nullptr);
  EXPECT_GT(strlen(name), 0u);
}

// Test user_comparator() returns the comparator passed in
TEST_F(InternalKeyComparatorTest_189, UserComparatorAccessor_189) {
  EXPECT_EQ(cmp_.user_comparator(), BytewiseComparator());
}

// Test with single character user keys
TEST_F(InternalKeyComparatorTest_189, SingleCharUserKeys_189) {
  std::string a = MakeInternalKey("a", 10, kTypeValue);
  std::string b = MakeInternalKey("b", 10, kTypeValue);
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test that sequence number 0 with kTypeDeletion (packed value = 0) sorts last among same user keys
TEST_F(InternalKeyComparatorTest_189, SequenceZeroDeletion_189) {
  std::string a = MakeInternalKey("key", 1, kTypeDeletion);
  std::string b = MakeInternalKey("key", 0, kTypeDeletion);
  // packed(a) = (1 << 8) | 0 > packed(b) = 0, so a comes first
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test with binary data in user keys
TEST_F(InternalKeyComparatorTest_189, BinaryUserKeys_189) {
  std::string user_a(4, '\0');
  user_a[3] = '\x01';
  std::string user_b(4, '\0');
  user_b[3] = '\x02';
  std::string a = MakeInternalKey(user_a, 100, kTypeValue);
  std::string b = MakeInternalKey(user_b, 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

}  // namespace leveldb
