#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

namespace leveldb {

// ===========================================================================
// InternalKey Tests
// ===========================================================================

class InternalKeyTest_55 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(InternalKeyTest_55, DefaultConstructorCreatesEmptyKey_55) {
  InternalKey key;
  // Default constructed key should have empty encoding
  Slice encoded = key.Encode();
  EXPECT_TRUE(encoded.empty());
}

TEST_F(InternalKeyTest_55, ConstructorWithParametersCreatesValidKey_55) {
  InternalKey key("user_key", 100, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
}

TEST_F(InternalKeyTest_55, UserKeyExtraction_55) {
  InternalKey key("hello", 42, kTypeValue);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "hello");
}

TEST_F(InternalKeyTest_55, EncodeAndDecodeRoundTrip_55) {
  InternalKey original("test_key", 200, kTypeValue);
  Slice encoded = original.Encode();

  InternalKey decoded;
  EXPECT_TRUE(decoded.DecodeFrom(encoded));
  EXPECT_EQ(decoded.Encode().ToString(), original.Encode().ToString());
}

TEST_F(InternalKeyTest_55, DecodeFromInvalidData_55) {
  InternalKey key;
  // Too short to contain the 8-byte trailer
  Slice short_data("short");
  EXPECT_FALSE(key.DecodeFrom(short_data));
}

TEST_F(InternalKeyTest_55, DecodeFromEmptySlice_55) {
  InternalKey key;
  Slice empty_data;
  EXPECT_FALSE(key.DecodeFrom(empty_data));
}

TEST_F(InternalKeyTest_55, ClearResetsKey_55) {
  InternalKey key("user_key", 100, kTypeValue);
  EXPECT_FALSE(key.Encode().empty());
  key.Clear();
  Slice encoded = key.Encode();
  EXPECT_TRUE(encoded.empty());
}

TEST_F(InternalKeyTest_55, SetFromParsedInternalKey_55) {
  ParsedInternalKey parsed;
  parsed.user_key = Slice("my_key");
  parsed.sequence = 500;
  parsed.type = kTypeValue;

  InternalKey key;
  key.SetFrom(parsed);

  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "my_key");
}

TEST_F(InternalKeyTest_55, DebugStringIsNotEmpty_55) {
  InternalKey key("debug_key", 77, kTypeValue);
  std::string debug = key.DebugString();
  EXPECT_FALSE(debug.empty());
}

TEST_F(InternalKeyTest_55, DifferentSequenceNumbersProduceDifferentKeys_55) {
  InternalKey key1("same_key", 100, kTypeValue);
  InternalKey key2("same_key", 200, kTypeValue);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

TEST_F(InternalKeyTest_55, DifferentValueTypesProduceDifferentKeys_55) {
  InternalKey key1("same_key", 100, kTypeValue);
  InternalKey key2("same_key", 100, kTypeDeletion);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

TEST_F(InternalKeyTest_55, DifferentUserKeysProduceDifferentKeys_55) {
  InternalKey key1("key_a", 100, kTypeValue);
  InternalKey key2("key_b", 100, kTypeValue);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

TEST_F(InternalKeyTest_55, EmptyUserKey_55) {
  InternalKey key("", 1, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "");
}

TEST_F(InternalKeyTest_55, MaxSequenceNumber_55) {
  // Max sequence number is (1 << 56) - 1 based on leveldb's format
  SequenceNumber max_seq = (1ull << 56) - 1;
  InternalKey key("key", max_seq, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  EXPECT_EQ(key.user_key().ToString(), "key");
}

TEST_F(InternalKeyTest_55, ZeroSequenceNumber_55) {
  InternalKey key("key", 0, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  EXPECT_EQ(key.user_key().ToString(), "key");
}

// ===========================================================================
// InternalKeyComparator Tests
// ===========================================================================

class InternalKeyComparatorTest_55 : public ::testing::Test {
 protected:
  InternalKeyComparatorTest_55()
      : cmp_(BytewiseComparator()) {}

  InternalKeyComparator cmp_;
};

TEST_F(InternalKeyComparatorTest_55, EqualKeysCompareEqual_55) {
  InternalKey a("same_key", 100, kTypeValue);
  InternalKey b("same_key", 100, kTypeValue);
  EXPECT_EQ(cmp_.Compare(a, b), 0);
}

TEST_F(InternalKeyComparatorTest_55, DifferentUserKeysOrdering_55) {
  InternalKey a("aaa", 100, kTypeValue);
  InternalKey b("bbb", 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(a, b), 0);
  EXPECT_GT(cmp_.Compare(b, a), 0);
}

TEST_F(InternalKeyComparatorTest_55, SameUserKeyHigherSequenceComesFirst_55) {
  // In InternalKeyComparator, for the same user key,
  // the key with a higher sequence number should come first (be "less")
  InternalKey a("key", 200, kTypeValue);
  InternalKey b("key", 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(a, b), 0);
  EXPECT_GT(cmp_.Compare(b, a), 0);
}

TEST_F(InternalKeyComparatorTest_55, SameUserKeySameSeqDifferentType_55) {
  // kTypeValue = 1, kTypeDeletion = 0
  // Higher type value should come first
  InternalKey a("key", 100, kTypeValue);       // type = 1
  InternalKey b("key", 100, kTypeDeletion);    // type = 0
  // Since tag = (seq << 8) | type, higher type means higher tag value,
  // but the comparator uses decreasing order for the tag
  EXPECT_LT(cmp_.Compare(a, b), 0);
}

TEST_F(InternalKeyComparatorTest_55, CompareWithSliceInterface_55) {
  InternalKey a("aaa", 100, kTypeValue);
  InternalKey b("bbb", 100, kTypeValue);
  int result = cmp_.Compare(a.Encode(), b.Encode());
  EXPECT_LT(result, 0);
}

TEST_F(InternalKeyComparatorTest_55, NameIsNotNull_55) {
  const char* name = cmp_.Name();
  EXPECT_NE(name, nullptr);
  EXPECT_GT(strlen(name), 0u);
}

TEST_F(InternalKeyComparatorTest_55, UserComparatorAccessor_55) {
  const Comparator* uc = cmp_.user_comparator();
  EXPECT_EQ(uc, BytewiseComparator());
}

TEST_F(InternalKeyComparatorTest_55, FindShortestSeparatorDoesNotCrash_55) {
  InternalKey a("abc", 100, kTypeValue);
  InternalKey b("xyz", 100, kTypeValue);
  std::string start = a.Encode().ToString();
  Slice limit = b.Encode();
  // Should not crash or throw
  cmp_.FindShortestSeparator(&start, limit);
  // Result should be <= limit according to comparator contract
  EXPECT_LE(cmp_.Compare(start, limit), 0);
}

TEST_F(InternalKeyComparatorTest_55, FindShortSuccessorDoesNotCrash_55) {
  InternalKey a("test", 100, kTypeValue);
  std::string key = a.Encode().ToString();
  std::string original_key = key;
  // Should not crash or throw
  cmp_.FindShortSuccessor(&key);
  // The result should be >= original
  EXPECT_GE(cmp_.Compare(key, original_key), 0);
}

TEST_F(InternalKeyComparatorTest_55, CompareReflexive_55) {
  InternalKey a("reflexive", 50, kTypeValue);
  EXPECT_EQ(cmp_.Compare(a, a), 0);
}

TEST_F(InternalKeyComparatorTest_55, CompareTransitive_55) {
  InternalKey a("aaa", 100, kTypeValue);
  InternalKey b("bbb", 100, kTypeValue);
  InternalKey c("ccc", 100, kTypeValue);
  EXPECT_LT(cmp_.Compare(a, b), 0);
  EXPECT_LT(cmp_.Compare(b, c), 0);
  EXPECT_LT(cmp_.Compare(a, c), 0);
}

TEST_F(InternalKeyComparatorTest_55, CompareAntiSymmetric_55) {
  InternalKey a("key_a", 100, kTypeValue);
  InternalKey b("key_b", 100, kTypeValue);
  int ab = cmp_.Compare(a, b);
  int ba = cmp_.Compare(b, a);
  EXPECT_EQ(ab, -ba);
}

TEST_F(InternalKeyComparatorTest_55, LongUserKey_55) {
  std::string long_key(1000, 'x');
  InternalKey a(long_key, 100, kTypeValue);
  InternalKey b(long_key, 99, kTypeValue);
  // Same user key, higher sequence comes first
  EXPECT_LT(cmp_.Compare(a, b), 0);
}

TEST_F(InternalKeyComparatorTest_55, SingleCharUserKeys_55) {
  InternalKey a("a", 1, kTypeValue);
  InternalKey b("b", 1, kTypeValue);
  EXPECT_LT(cmp_.Compare(a, b), 0);
}

}  // namespace leveldb
