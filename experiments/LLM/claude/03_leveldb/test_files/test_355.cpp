#include "gtest/gtest.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "util/coding.h"
#include <cstring>
#include <string>
#include <vector>

namespace leveldb {

// Helper function to encode a length-prefixed slice into a buffer
// This matches the format expected by GetLengthPrefixedSlice
static std::string EncodeLengthPrefixedSlice(const Slice& s) {
  std::string result;
  // Encode varint32 length followed by data
  char buf[5];
  char* p = buf;
  p = EncodeVarint32(p, s.size());
  result.append(buf, p - buf);
  result.append(s.data(), s.size());
  return result;
}

// Helper to create an internal key in the format used by memtable
static std::string MakeInternalKey(const std::string& user_key,
                                    SequenceNumber seq,
                                    ValueType type) {
  std::string encoded;
  encoded.append(user_key);
  PutFixed64(&encoded, PackSequenceAndType(seq, type));
  return encoded;
}

static std::string MakeLengthPrefixedInternalKey(const std::string& user_key,
                                                   SequenceNumber seq,
                                                   ValueType type) {
  std::string internal_key = MakeInternalKey(user_key, seq, type);
  return EncodeLengthPrefixedSlice(Slice(internal_key));
}

class KeyComparatorTest_355 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Use the default bytewise comparator
    icmp_ = new InternalKeyComparator(BytewiseComparator());
  }

  void TearDown() override {
    delete icmp_;
  }

  InternalKeyComparator* icmp_;
};

// Test that equal keys with the same sequence number return 0
TEST_F(KeyComparatorTest_355, EqualKeysReturnZero_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("key1", 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("key1", 100, kTypeValue);

  int result = cmp(a.data(), b.data());
  EXPECT_EQ(0, result);
}

// Test that comparing different user keys gives correct ordering
TEST_F(KeyComparatorTest_355, DifferentUserKeysOrdering_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("aaa", 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("bbb", 100, kTypeValue);

  EXPECT_LT(cmp(a.data(), b.data()), 0);
  EXPECT_GT(cmp(b.data(), a.data()), 0);
}

// Test that same user key with different sequence numbers orders by decreasing sequence
TEST_F(KeyComparatorTest_355, SameKeyDifferentSequenceNumbers_355) {
  MemTable::KeyComparator cmp(*icmp_);

  // InternalKeyComparator orders by user_key ascending, then by sequence descending
  std::string a = MakeLengthPrefixedInternalKey("key1", 200, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("key1", 100, kTypeValue);

  // Higher sequence number should come first (be "less than")
  EXPECT_LT(cmp(a.data(), b.data()), 0);
  EXPECT_GT(cmp(b.data(), a.data()), 0);
}

// Test comparison with empty user keys
TEST_F(KeyComparatorTest_355, EmptyUserKeys_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("", 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("", 100, kTypeValue);

  EXPECT_EQ(0, cmp(a.data(), b.data()));
}

// Test empty key vs non-empty key
TEST_F(KeyComparatorTest_355, EmptyVsNonEmptyKey_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("", 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("key1", 100, kTypeValue);

  EXPECT_LT(cmp(a.data(), b.data()), 0);
  EXPECT_GT(cmp(b.data(), a.data()), 0);
}

// Test that same key with different types orders correctly
TEST_F(KeyComparatorTest_355, SameKeyDifferentTypes_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("key1", 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("key1", 100, kTypeDeletion);

  // kTypeValue (1) > kTypeDeletion (0), and type is packed with sequence
  // so (100 << 8 | 1) vs (100 << 8 | 0) -- higher packed value sorts first
  EXPECT_LT(cmp(a.data(), b.data()), 0);
}

// Test comparison with longer keys
TEST_F(KeyComparatorTest_355, LongKeys_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string long_key_a(1000, 'a');
  std::string long_key_b(1000, 'b');

  std::string a = MakeLengthPrefixedInternalKey(long_key_a, 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey(long_key_b, 100, kTypeValue);

  EXPECT_LT(cmp(a.data(), b.data()), 0);
  EXPECT_GT(cmp(b.data(), a.data()), 0);
}

// Test comparison with keys that are prefixes of each other
TEST_F(KeyComparatorTest_355, PrefixKeys_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("key", 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("key1", 100, kTypeValue);

  EXPECT_LT(cmp(a.data(), b.data()), 0);
  EXPECT_GT(cmp(b.data(), a.data()), 0);
}

// Test reflexivity: comparing a key with itself returns 0
TEST_F(KeyComparatorTest_355, Reflexive_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("testkey", 50, kTypeValue);

  EXPECT_EQ(0, cmp(a.data(), a.data()));
}

// Test transitivity of ordering
TEST_F(KeyComparatorTest_355, TransitiveOrdering_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("aaa", 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("bbb", 100, kTypeValue);
  std::string c = MakeLengthPrefixedInternalKey("ccc", 100, kTypeValue);

  EXPECT_LT(cmp(a.data(), b.data()), 0);
  EXPECT_LT(cmp(b.data(), c.data()), 0);
  EXPECT_LT(cmp(a.data(), c.data()), 0);
}

// Test with sequence number boundaries
TEST_F(KeyComparatorTest_355, SequenceNumberBoundary_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("key1", 0, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("key1", 1, kTypeValue);

  // Higher sequence number comes first
  EXPECT_GT(cmp(a.data(), b.data()), 0);
  EXPECT_LT(cmp(b.data(), a.data()), 0);
}

// Test with very large sequence numbers
TEST_F(KeyComparatorTest_355, LargeSequenceNumber_355) {
  MemTable::KeyComparator cmp(*icmp_);

  SequenceNumber max_seq = kMaxSequenceNumber;
  std::string a = MakeLengthPrefixedInternalKey("key1", max_seq, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("key1", 1, kTypeValue);

  // max_seq should come before seq 1
  EXPECT_LT(cmp(a.data(), b.data()), 0);
  EXPECT_GT(cmp(b.data(), a.data()), 0);
}

// Test keys with binary data
TEST_F(KeyComparatorTest_355, BinaryDataKeys_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string key_a = std::string("\x00\x01\x02", 3);
  std::string key_b = std::string("\x00\x01\x03", 3);

  std::string a = MakeLengthPrefixedInternalKey(key_a, 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey(key_b, 100, kTypeValue);

  EXPECT_LT(cmp(a.data(), b.data()), 0);
  EXPECT_GT(cmp(b.data(), a.data()), 0);
}

// Test single character keys
TEST_F(KeyComparatorTest_355, SingleCharKeys_355) {
  MemTable::KeyComparator cmp(*icmp_);

  std::string a = MakeLengthPrefixedInternalKey("a", 100, kTypeValue);
  std::string b = MakeLengthPrefixedInternalKey("z", 100, kTypeValue);

  EXPECT_LT(cmp(a.data(), b.data()), 0);
  EXPECT_GT(cmp(b.data(), a.data()), 0);
}

}  // namespace leveldb
