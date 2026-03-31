#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

class InternalKeyTest_475 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that constructing an InternalKey with valid parameters produces a non-empty encoding
TEST_F(InternalKeyTest_475, ConstructorProducesNonEmptyEncoding_475) {
  InternalKey key("testkey", 100, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
}

// Test that user_key() returns the original user key
TEST_F(InternalKeyTest_475, UserKeyReturnsCorrectKey_475) {
  InternalKey key("mykey", 200, kTypeValue);
  Slice uk = key.user_key();
  EXPECT_EQ(uk.ToString(), "mykey");
}

// Test that user_key() works with kTypeDeletion
TEST_F(InternalKeyTest_475, UserKeyWithDeletionType_475) {
  InternalKey key("delkey", 300, kTypeDeletion);
  Slice uk = key.user_key();
  EXPECT_EQ(uk.ToString(), "delkey");
}

// Test that Encode() followed by DecodeFrom() roundtrips correctly
TEST_F(InternalKeyTest_475, EncodeDecodeRoundTrip_475) {
  InternalKey key1("roundtrip", 500, kTypeValue);
  Slice encoded = key1.Encode();

  InternalKey key2;
  EXPECT_TRUE(key2.DecodeFrom(encoded));
  EXPECT_EQ(key2.user_key().ToString(), "roundtrip");
}

// Test default constructor creates an empty/invalid key
TEST_F(InternalKeyTest_475, DefaultConstructorCreatesEmptyKey_475) {
  InternalKey key;
  Slice encoded = key.Encode();
  EXPECT_TRUE(encoded.empty());
}

// Test Clear() makes the key empty
TEST_F(InternalKeyTest_475, ClearMakesKeyEmpty_475) {
  InternalKey key("clearme", 100, kTypeValue);
  EXPECT_FALSE(key.Encode().empty());
  key.Clear();
  EXPECT_TRUE(key.Encode().empty());
}

// Test SetFrom correctly sets the internal key
TEST_F(InternalKeyTest_475, SetFromSetsCorrectly_475) {
  InternalKey key;
  ParsedInternalKey parsed("setfrom", 777, kTypeValue);
  key.SetFrom(parsed);
  EXPECT_EQ(key.user_key().ToString(), "setfrom");
}

// Test that two keys with different sequence numbers produce different encodings
TEST_F(InternalKeyTest_475, DifferentSequenceNumbersDifferentEncodings_475) {
  InternalKey key1("samekey", 1, kTypeValue);
  InternalKey key2("samekey", 2, kTypeValue);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

// Test that two keys with different value types produce different encodings
TEST_F(InternalKeyTest_475, DifferentValueTypesDifferentEncodings_475) {
  InternalKey key1("samekey", 100, kTypeValue);
  InternalKey key2("samekey", 100, kTypeDeletion);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

// Test that two keys with different user keys produce different encodings
TEST_F(InternalKeyTest_475, DifferentUserKeysDifferentEncodings_475) {
  InternalKey key1("alpha", 100, kTypeValue);
  InternalKey key2("beta", 100, kTypeValue);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

// Test DebugString returns a non-empty string for a valid key
TEST_F(InternalKeyTest_475, DebugStringNonEmpty_475) {
  InternalKey key("debugkey", 42, kTypeValue);
  std::string debug = key.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test with empty user key
TEST_F(InternalKeyTest_475, EmptyUserKey_475) {
  InternalKey key("", 1, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  EXPECT_EQ(key.user_key().ToString(), "");
}

// Test with maximum sequence number
TEST_F(InternalKeyTest_475, MaxSequenceNumber_475) {
  InternalKey key("maxseq", kMaxSequenceNumber, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  EXPECT_EQ(key.user_key().ToString(), "maxseq");
}

// Test with sequence number 0
TEST_F(InternalKeyTest_475, ZeroSequenceNumber_475) {
  InternalKey key("zeroseq", 0, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  EXPECT_EQ(key.user_key().ToString(), "zeroseq");
}

// Test DecodeFrom with invalid/short data returns false
TEST_F(InternalKeyTest_475, DecodeFromInvalidData_475) {
  InternalKey key;
  // A slice shorter than 8 bytes should not decode properly
  // (internal key = user_key + 8 bytes of tag)
  Slice too_short("short");
  // The behavior may vary, but we test it doesn't crash
  // An empty slice should definitely fail
  Slice empty_slice("");
  EXPECT_FALSE(key.DecodeFrom(empty_slice));
}

// Test that encoding size is user_key size + 8 bytes (for sequence + type tag)
TEST_F(InternalKeyTest_475, EncodingSizeIsCorrect_475) {
  std::string user_key = "hello";
  InternalKey key(user_key, 100, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_EQ(encoded.size(), user_key.size() + 8);
}

// Test SetFrom after Clear
TEST_F(InternalKeyTest_475, SetFromAfterClear_475) {
  InternalKey key("original", 1, kTypeValue);
  key.Clear();
  EXPECT_TRUE(key.Encode().empty());

  ParsedInternalKey parsed("renewed", 2, kTypeDeletion);
  key.SetFrom(parsed);
  EXPECT_EQ(key.user_key().ToString(), "renewed");
}

// Test multiple DecodeFrom calls on same key object
TEST_F(InternalKeyTest_475, MultipleDecodeFrom_475) {
  InternalKey key1("first", 10, kTypeValue);
  InternalKey key2("second", 20, kTypeDeletion);

  InternalKey target;
  EXPECT_TRUE(target.DecodeFrom(key1.Encode()));
  EXPECT_EQ(target.user_key().ToString(), "first");

  EXPECT_TRUE(target.DecodeFrom(key2.Encode()));
  EXPECT_EQ(target.user_key().ToString(), "second");
}

// Test with a long user key
TEST_F(InternalKeyTest_475, LongUserKey_475) {
  std::string long_key(1000, 'x');
  InternalKey key(long_key, 999, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), long_key);
  EXPECT_EQ(key.Encode().size(), long_key.size() + 8);
}

}  // namespace leveldb
