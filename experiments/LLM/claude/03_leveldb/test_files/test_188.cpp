#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <string>
#include <cstring>

namespace leveldb {

// Helper to construct an internal key from user key, sequence number, and value type
static std::string MakeInternalKey(const std::string& user_key, SequenceNumber seq, ValueType type) {
  std::string result = user_key;
  PutFixed64(&result, PackSequenceAndType(seq, type));
  return result;
}

class InternalKeyComparatorTest_188 : public ::testing::Test {
 protected:
  InternalKeyComparatorTest_188()
      : cmp_(BytewiseComparator()) {}

  InternalKeyComparator cmp_;
};

// Test that Name() returns the expected comparator name
TEST_F(InternalKeyComparatorTest_188, Name_188) {
  EXPECT_STREQ("leveldb.InternalKeyComparator", cmp_.Name());
}

// Test that user_comparator() returns the comparator passed at construction
TEST_F(InternalKeyComparatorTest_188, UserComparator_188) {
  EXPECT_EQ(BytewiseComparator(), cmp_.user_comparator());
}

// Test comparing two internal keys with different user keys
TEST_F(InternalKeyComparatorTest_188, CompareSliceDifferentUserKeys_188) {
  std::string a = MakeInternalKey("abc", 100, kTypeValue);
  std::string b = MakeInternalKey("abd", 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
  EXPECT_GT(cmp_.Compare(Slice(b), Slice(a)), 0);
}

// Test comparing two internal keys with same user key but different sequence numbers
// Higher sequence number should come first (i.e., compare as less)
TEST_F(InternalKeyComparatorTest_188, CompareSliceSameUserKeyDifferentSeq_188) {
  std::string a = MakeInternalKey("abc", 200, kTypeValue);
  std::string b = MakeInternalKey("abc", 100, kTypeValue);
  // a has higher sequence, so a < b in internal key ordering
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
  EXPECT_GT(cmp_.Compare(Slice(b), Slice(a)), 0);
}

// Test comparing two internal keys with same user key, same sequence, different type
TEST_F(InternalKeyComparatorTest_188, CompareSliceSameKeySeqDifferentType_188) {
  std::string a = MakeInternalKey("abc", 100, kTypeValue);
  std::string b = MakeInternalKey("abc", 100, kTypeDeletion);
  // kTypeValue (1) > kTypeDeletion (0), so in the tag comparison (seq<<8|type),
  // same seq but higher type means smaller tag numeric... actually the tag is
  // (seq << 8) | type, and we compare descending. So higher type value means
  // the packed number is larger, which in descending order means it comes first.
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test that comparing identical internal keys returns 0
TEST_F(InternalKeyComparatorTest_188, CompareSliceEqualKeys_188) {
  std::string a = MakeInternalKey("abc", 100, kTypeValue);
  std::string b = MakeInternalKey("abc", 100, kTypeValue);
  EXPECT_EQ(0, cmp_.Compare(Slice(a), Slice(b)));
}

// Test Compare with InternalKey objects
TEST_F(InternalKeyComparatorTest_188, CompareInternalKeyObjects_188) {
  InternalKey a(Slice("abc"), 100, kTypeValue);
  InternalKey b(Slice("abd"), 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(a, b), 0);
  EXPECT_GT(cmp_.Compare(b, a), 0);
}

TEST_F(InternalKeyComparatorTest_188, CompareInternalKeyObjectsEqual_188) {
  InternalKey a(Slice("abc"), 100, kTypeValue);
  InternalKey b(Slice("abc"), 100, kTypeValue);
  EXPECT_EQ(0, cmp_.Compare(a, b));
}

TEST_F(InternalKeyComparatorTest_188, CompareInternalKeyObjectsSameKeyDiffSeq_188) {
  InternalKey a(Slice("abc"), 200, kTypeValue);
  InternalKey b(Slice("abc"), 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(a, b), 0);
}

// Test FindShortestSeparator
TEST_F(InternalKeyComparatorTest_188, FindShortestSeparator_188) {
  std::string start = MakeInternalKey("abc", 100, kTypeValue);
  std::string limit = MakeInternalKey("abd", 100, kTypeValue);
  std::string original_start = start;
  cmp_.FindShortestSeparator(&start, Slice(limit));
  // After FindShortestSeparator, start should be >= original start
  EXPECT_LE(cmp_.Compare(Slice(original_start), Slice(start)), 0);
  // and start should be <= limit
  EXPECT_LE(cmp_.Compare(Slice(start), Slice(limit)), 0);
}

// Test FindShortestSeparator when start == limit (no change expected)
TEST_F(InternalKeyComparatorTest_188, FindShortestSeparatorSameKey_188) {
  std::string start = MakeInternalKey("abc", 100, kTypeValue);
  std::string limit = start;
  std::string original_start = start;
  cmp_.FindShortestSeparator(&start, Slice(limit));
  // start should still be valid and >= original_start and <= limit
  EXPECT_LE(cmp_.Compare(Slice(original_start), Slice(start)), 0);
}

// Test FindShortSuccessor
TEST_F(InternalKeyComparatorTest_188, FindShortSuccessor_188) {
  std::string key = MakeInternalKey("abc", 100, kTypeValue);
  std::string original_key = key;
  cmp_.FindShortSuccessor(&key);
  // The result should be >= the original key
  EXPECT_LE(cmp_.Compare(Slice(original_key), Slice(key)), 0);
}

// Test with empty user key
TEST_F(InternalKeyComparatorTest_188, CompareEmptyUserKey_188) {
  std::string a = MakeInternalKey("", 100, kTypeValue);
  std::string b = MakeInternalKey("", 50, kTypeValue);
  // Same user key (empty), higher seq comes first
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test with long user keys
TEST_F(InternalKeyComparatorTest_188, CompareLongUserKeys_188) {
  std::string long_key_a(1000, 'a');
  std::string long_key_b(1000, 'b');
  std::string a = MakeInternalKey(long_key_a, 100, kTypeValue);
  std::string b = MakeInternalKey(long_key_b, 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test sequence number boundary: max sequence number
TEST_F(InternalKeyComparatorTest_188, CompareMaxSequenceNumber_188) {
  SequenceNumber max_seq = kMaxSequenceNumber;
  std::string a = MakeInternalKey("abc", max_seq, kTypeValue);
  std::string b = MakeInternalKey("abc", 1, kTypeValue);
  // Higher sequence comes first
  EXPECT_LT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test sequence number 0
TEST_F(InternalKeyComparatorTest_188, CompareSequenceZero_188) {
  std::string a = MakeInternalKey("abc", 0, kTypeValue);
  std::string b = MakeInternalKey("abc", 1, kTypeValue);
  EXPECT_GT(cmp_.Compare(Slice(a), Slice(b)), 0);
}

// Test FindShortestSeparator with widely separated keys
TEST_F(InternalKeyComparatorTest_188, FindShortestSeparatorWidelySeparated_188) {
  std::string start = MakeInternalKey("a", 100, kTypeValue);
  std::string limit = MakeInternalKey("z", 100, kTypeValue);
  std::string original_start = start;
  cmp_.FindShortestSeparator(&start, Slice(limit));
  EXPECT_LE(cmp_.Compare(Slice(original_start), Slice(start)), 0);
  EXPECT_LE(cmp_.Compare(Slice(start), Slice(limit)), 0);
}

// Test FindShortSuccessor with single character key
TEST_F(InternalKeyComparatorTest_188, FindShortSuccessorSingleChar_188) {
  std::string key = MakeInternalKey("a", 100, kTypeValue);
  std::string original_key = key;
  cmp_.FindShortSuccessor(&key);
  EXPECT_LE(cmp_.Compare(Slice(original_key), Slice(key)), 0);
}

}  // namespace leveldb
