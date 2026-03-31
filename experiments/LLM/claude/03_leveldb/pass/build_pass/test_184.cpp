#include "gtest/gtest.h"
#include "db/dbformat.h"

namespace leveldb {

// We need to test PackSequenceAndType indirectly through public interfaces
// that use it. The primary public interfaces are:
// - InternalKey::Encode()
// - AppendInternalKey()
// - ParseInternalKey()
// - InternalKeyEncodingLength()

// Test normal construction and encoding of InternalKey
TEST(InternalKeyTest_184, NormalConstruction_184) {
  InternalKey key("hello", 100, kTypeValue);
  ASSERT_FALSE(key.Encode().empty());
}

TEST(InternalKeyTest_184, EncodeDecodeRoundTrip_184) {
  InternalKey key("testkey", 500, kTypeValue);
  Slice encoded = key.Encode();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(encoded, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "testkey");
  EXPECT_EQ(parsed.sequence, 500u);
  EXPECT_EQ(parsed.type, kTypeValue);
}

TEST(InternalKeyTest_184, EncodeDecodeWithDeletion_184) {
  InternalKey key("deletekey", 42, kTypeDeletion);
  Slice encoded = key.Encode();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(encoded, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "deletekey");
  EXPECT_EQ(parsed.sequence, 42u);
  EXPECT_EQ(parsed.type, kTypeDeletion);
}

TEST(InternalKeyTest_184, SequenceNumberZero_184) {
  InternalKey key("zerokey", 0, kTypeValue);
  Slice encoded = key.Encode();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(encoded, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "zerokey");
  EXPECT_EQ(parsed.sequence, 0u);
  EXPECT_EQ(parsed.type, kTypeValue);
}

TEST(InternalKeyTest_184, MaxSequenceNumber_184) {
  InternalKey key("maxseqkey", kMaxSequenceNumber, kTypeValue);
  Slice encoded = key.Encode();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(encoded, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "maxseqkey");
  EXPECT_EQ(parsed.sequence, kMaxSequenceNumber);
  EXPECT_EQ(parsed.type, kTypeValue);
}

TEST(InternalKeyTest_184, EmptyUserKey_184) {
  InternalKey key("", 1, kTypeValue);
  Slice encoded = key.Encode();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(encoded, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "");
  EXPECT_EQ(parsed.sequence, 1u);
  EXPECT_EQ(parsed.type, kTypeValue);
}

TEST(InternalKeyTest_184, DeletionTypeZeroSequence_184) {
  InternalKey key("delzero", 0, kTypeDeletion);
  Slice encoded = key.Encode();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(encoded, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "delzero");
  EXPECT_EQ(parsed.sequence, 0u);
  EXPECT_EQ(parsed.type, kTypeDeletion);
}

TEST(InternalKeyTest_184, ParseInternalKeyTooShort_184) {
  // An internal key must be at least 8 bytes (for the packed seq+type)
  Slice too_short("short");
  ParsedInternalKey parsed;
  EXPECT_FALSE(ParseInternalKey(too_short, &parsed));
}

TEST(InternalKeyTest_184, ParseInternalKeyEmptySlice_184) {
  Slice empty;
  ParsedInternalKey parsed;
  EXPECT_FALSE(ParseInternalKey(empty, &parsed));
}

TEST(InternalKeyTest_184, SetFromAndDecodeBack_184) {
  InternalKey key;
  ParsedInternalKey pkey("userdata", 999, kTypeDeletion);
  key.SetFrom(pkey);
  
  Slice encoded = key.Encode();
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(encoded, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "userdata");
  EXPECT_EQ(parsed.sequence, 999u);
  EXPECT_EQ(parsed.type, kTypeDeletion);
}

TEST(InternalKeyTest_184, ClearMakesEmpty_184) {
  InternalKey key("hello", 100, kTypeValue);
  ASSERT_FALSE(key.Encode().empty());
  key.Clear();
  EXPECT_TRUE(key.Encode().empty());
}

TEST(InternalKeyTest_184, UserKeyExtraction_184) {
  InternalKey key("myuserkey", 77, kTypeValue);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "myuserkey");
}

TEST(InternalKeyTest_184, AppendInternalKey_184) {
  std::string result;
  ParsedInternalKey pkey("appendtest", 256, kTypeValue);
  AppendInternalKey(&result, pkey);
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(Slice(result), &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "appendtest");
  EXPECT_EQ(parsed.sequence, 256u);
  EXPECT_EQ(parsed.type, kTypeValue);
}

TEST(InternalKeyTest_184, SequenceNumberOne_184) {
  InternalKey key("oneseq", 1, kTypeValue);
  Slice encoded = key.Encode();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(encoded, &parsed));
  EXPECT_EQ(parsed.sequence, 1u);
  EXPECT_EQ(parsed.type, kTypeValue);
}

TEST(InternalKeyTest_184, LargeSequenceNumber_184) {
  // Test with a large but valid sequence number
  SequenceNumber large_seq = (1ULL << 48) - 1;
  InternalKey key("largeseq", large_seq, kTypeValue);
  Slice encoded = key.Encode();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(encoded, &parsed));
  EXPECT_EQ(parsed.sequence, large_seq);
  EXPECT_EQ(parsed.type, kTypeValue);
}

// Test InternalKeyComparator
TEST(InternalKeyComparatorTest_184, SameUserKeyDifferentSequence_184) {
  InternalKeyComparator cmp(BytewiseComparator());
  
  // Higher sequence number should come first (be "less")
  InternalKey key1("samekey", 200, kTypeValue);
  InternalKey key2("samekey", 100, kTypeValue);
  
  EXPECT_LT(cmp.Compare(key1.Encode(), key2.Encode()), 0);
  EXPECT_GT(cmp.Compare(key2.Encode(), key1.Encode()), 0);
}

TEST(InternalKeyComparatorTest_184, DifferentUserKeys_184) {
  InternalKeyComparator cmp(BytewiseComparator());
  
  InternalKey key1("aaa", 100, kTypeValue);
  InternalKey key2("bbb", 100, kTypeValue);
  
  EXPECT_LT(cmp.Compare(key1.Encode(), key2.Encode()), 0);
  EXPECT_GT(cmp.Compare(key2.Encode(), key1.Encode()), 0);
}

TEST(InternalKeyComparatorTest_184, SameKeysSameSequence_184) {
  InternalKeyComparator cmp(BytewiseComparator());
  
  InternalKey key1("samekey", 100, kTypeValue);
  InternalKey key2("samekey", 100, kTypeValue);
  
  EXPECT_EQ(cmp.Compare(key1.Encode(), key2.Encode()), 0);
}

TEST(InternalKeyComparatorTest_184, SameUserKeySameSeqDifferentType_184) {
  InternalKeyComparator cmp(BytewiseComparator());
  
  // kTypeValue (1) > kTypeDeletion (0), so kTypeValue should come first (be "less")
  InternalKey key1("samekey", 100, kTypeValue);
  InternalKey key2("samekey", 100, kTypeDeletion);
  
  EXPECT_LT(cmp.Compare(key1.Encode(), key2.Encode()), 0);
  EXPECT_GT(cmp.Compare(key2.Encode(), key1.Encode()), 0);
}

TEST(InternalKeyComparatorTest_184, ComparatorName_184) {
  InternalKeyComparator cmp(BytewiseComparator());
  EXPECT_NE(cmp.Name(), nullptr);
  // The name should contain "leveldb.InternalKeyComparator"
  std::string name(cmp.Name());
  EXPECT_FALSE(name.empty());
}

// Test LookupKey
TEST(LookupKeyTest_184, BasicConstruction_184) {
  LookupKey lk(Slice("hello"), 100);
  
  Slice memtable_key = lk.memtable_key();
  Slice internal_key = lk.internal_key();
  Slice user_key = lk.user_key();
  
  EXPECT_FALSE(memtable_key.empty());
  EXPECT_FALSE(internal_key.empty());
  EXPECT_EQ(user_key.ToString(), "hello");
}

TEST(LookupKeyTest_184, InternalKeyParsable_184) {
  LookupKey lk(Slice("lookuptest"), 555);
  Slice internal_key = lk.internal_key();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_key, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "lookuptest");
  EXPECT_EQ(parsed.sequence, 555u);
  EXPECT_EQ(parsed.type, kValueTypeForSeek);
}

TEST(LookupKeyTest_184, ZeroSequence_184) {
  LookupKey lk(Slice("zerotest"), 0);
  Slice internal_key = lk.internal_key();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_key, &parsed));
  EXPECT_EQ(parsed.sequence, 0u);
  EXPECT_EQ(parsed.type, kValueTypeForSeek);
}

TEST(LookupKeyTest_184, MaxSequence_184) {
  LookupKey lk(Slice("maxtest"), kMaxSequenceNumber);
  Slice internal_key = lk.internal_key();
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_key, &parsed));
  EXPECT_EQ(parsed.sequence, kMaxSequenceNumber);
}

TEST(LookupKeyTest_184, EmptyUserKey_184) {
  LookupKey lk(Slice(""), 50);
  Slice user_key = lk.user_key();
  EXPECT_EQ(user_key.ToString(), "");
  
  Slice internal_key = lk.internal_key();
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_key, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "");
  EXPECT_EQ(parsed.sequence, 50u);
}

// Test InternalFilterPolicy
TEST(InternalFilterPolicyTest_184, Name_184) {
  const FilterPolicy* bloom = NewBloomFilterPolicy(10);
  InternalFilterPolicy ifp(bloom);
  EXPECT_NE(ifp.Name(), nullptr);
  delete bloom;
}

// Test ParsedInternalKey debug string
TEST(ParsedInternalKeyTest_184, DebugString_184) {
  ParsedInternalKey pkey("mykey", 42, kTypeValue);
  std::string debug = pkey.DebugString();
  EXPECT_FALSE(debug.empty());
  // Should contain user key info
  EXPECT_NE(debug.find("mykey"), std::string::npos);
}

// Encoding length
TEST(InternalKeyTest_184, EncodingLength_184) {
  ParsedInternalKey pkey("testkey", 100, kTypeValue);
  size_t len = InternalKeyEncodingLength(pkey);
  // user_key length + 8 bytes for packed sequence and type
  EXPECT_EQ(len, 7u + 8u);
}

TEST(InternalKeyTest_184, EncodingLengthEmptyKey_184) {
  ParsedInternalKey pkey("", 100, kTypeValue);
  size_t len = InternalKeyEncodingLength(pkey);
  EXPECT_EQ(len, 0u + 8u);
}

}  // namespace leveldb
