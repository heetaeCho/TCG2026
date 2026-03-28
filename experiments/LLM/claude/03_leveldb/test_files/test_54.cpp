#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

class InternalKeyTest_54 : public ::testing::Test {
 protected:
  InternalKey key_;
};

// Test that a default-constructed InternalKey has an empty representation
TEST_F(InternalKeyTest_54, DefaultConstructorCreatesEmptyKey_54) {
  InternalKey key;
  // Encode() should return an empty slice for a default-constructed key
  Slice encoded = key.Encode();
  EXPECT_EQ(encoded.size(), 0u);
}

// Test Clear() resets the key to empty state
TEST_F(InternalKeyTest_54, ClearResetsKey_54) {
  // Construct a key with actual data
  InternalKey key(Slice("user_key"), 100, kTypeValue);
  EXPECT_GT(key.Encode().size(), 0u);

  key.Clear();
  EXPECT_EQ(key.Encode().size(), 0u);
}

// Test constructing an InternalKey with user_key, sequence, and type
TEST_F(InternalKeyTest_54, ConstructWithParameters_54) {
  InternalKey key(Slice("hello"), 42, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_GT(encoded.size(), 0u);

  // user_key() should return the original user key
  Slice uk = key.user_key();
  EXPECT_EQ(uk.ToString(), "hello");
}

// Test that user_key() returns correct user key
TEST_F(InternalKeyTest_54, UserKeyExtraction_54) {
  InternalKey key(Slice("test_key"), 500, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), "test_key");
}

// Test that user_key() works with kTypeDeletion
TEST_F(InternalKeyTest_54, UserKeyWithDeletionType_54) {
  InternalKey key(Slice("deleted_key"), 200, kTypeDeletion);
  EXPECT_EQ(key.user_key().ToString(), "deleted_key");
}

// Test Encode and DecodeFrom round-trip
TEST_F(InternalKeyTest_54, EncodeDecodeRoundTrip_54) {
  InternalKey original(Slice("roundtrip"), 999, kTypeValue);
  Slice encoded = original.Encode();

  InternalKey decoded;
  EXPECT_TRUE(decoded.DecodeFrom(encoded));
  EXPECT_EQ(decoded.user_key().ToString(), "roundtrip");
  EXPECT_EQ(decoded.Encode().ToString(), original.Encode().ToString());
}

// Test DecodeFrom with empty slice should fail or handle gracefully
TEST_F(InternalKeyTest_54, DecodeFromEmptySlice_54) {
  InternalKey key;
  Slice empty_slice;
  // Decoding an empty slice should fail since there's no tag
  EXPECT_FALSE(key.DecodeFrom(empty_slice));
}

// Test DecodeFrom with too-short data (less than 8 bytes for the tag)
TEST_F(InternalKeyTest_54, DecodeFromTooShortData_54) {
  InternalKey key;
  Slice short_slice("short");  // Only 5 bytes, need at least 8 for tag
  EXPECT_FALSE(key.DecodeFrom(short_slice));
}

// Test SetFrom with a ParsedInternalKey
TEST_F(InternalKeyTest_54, SetFromParsedInternalKey_54) {
  ParsedInternalKey parsed;
  parsed.user_key = Slice("set_from_key");
  parsed.sequence = 12345;
  parsed.type = kTypeValue;

  InternalKey key;
  key.SetFrom(parsed);

  EXPECT_EQ(key.user_key().ToString(), "set_from_key");
  EXPECT_GT(key.Encode().size(), 0u);
}

// Test SetFrom then Clear
TEST_F(InternalKeyTest_54, SetFromThenClear_54) {
  ParsedInternalKey parsed;
  parsed.user_key = Slice("to_clear");
  parsed.sequence = 1;
  parsed.type = kTypeValue;

  InternalKey key;
  key.SetFrom(parsed);
  EXPECT_GT(key.Encode().size(), 0u);

  key.Clear();
  EXPECT_EQ(key.Encode().size(), 0u);
}

// Test DebugString returns non-empty string for valid key
TEST_F(InternalKeyTest_54, DebugStringNonEmpty_54) {
  InternalKey key(Slice("debug_key"), 77, kTypeValue);
  std::string debug = key.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString for default-constructed key
TEST_F(InternalKeyTest_54, DebugStringForEmptyKey_54) {
  InternalKey key;
  std::string debug = key.DebugString();
  // Should return some string (possibly indicating invalid/empty state)
  // Just verify it doesn't crash
  EXPECT_TRUE(true);
}

// Test with sequence number 0
TEST_F(InternalKeyTest_54, SequenceNumberZero_54) {
  InternalKey key(Slice("seq_zero"), 0, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), "seq_zero");
}

// Test with maximum sequence number
TEST_F(InternalKeyTest_54, MaxSequenceNumber_54) {
  InternalKey key(Slice("max_seq"), kMaxSequenceNumber, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), "max_seq");

  // Verify round-trip
  Slice encoded = key.Encode();
  InternalKey decoded;
  EXPECT_TRUE(decoded.DecodeFrom(encoded));
  EXPECT_EQ(decoded.user_key().ToString(), "max_seq");
}

// Test with empty user key
TEST_F(InternalKeyTest_54, EmptyUserKey_54) {
  InternalKey key(Slice(""), 50, kTypeValue);
  Slice encoded = key.Encode();
  // Should have at least 8 bytes for the tag
  EXPECT_GE(encoded.size(), 8u);
  EXPECT_EQ(key.user_key().ToString(), "");
}

// Test that two keys with different sequences encode differently
TEST_F(InternalKeyTest_54, DifferentSequencesDifferentEncoding_54) {
  InternalKey key1(Slice("same_key"), 100, kTypeValue);
  InternalKey key2(Slice("same_key"), 200, kTypeValue);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

// Test that two keys with different types encode differently
TEST_F(InternalKeyTest_54, DifferentTypesDifferentEncoding_54) {
  InternalKey key1(Slice("same_key"), 100, kTypeValue);
  InternalKey key2(Slice("same_key"), 100, kTypeDeletion);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

// Test multiple Clear calls
TEST_F(InternalKeyTest_54, MultipleClearCalls_54) {
  InternalKey key(Slice("multi_clear"), 10, kTypeValue);
  key.Clear();
  key.Clear();  // Should not crash
  EXPECT_EQ(key.Encode().size(), 0u);
}

// Test SetFrom overwrites previous value
TEST_F(InternalKeyTest_54, SetFromOverwritesPrevious_54) {
  InternalKey key(Slice("original"), 1, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), "original");

  ParsedInternalKey parsed;
  parsed.user_key = Slice("overwritten");
  parsed.sequence = 2;
  parsed.type = kTypeDeletion;

  key.SetFrom(parsed);
  EXPECT_EQ(key.user_key().ToString(), "overwritten");
}

}  // namespace leveldb
