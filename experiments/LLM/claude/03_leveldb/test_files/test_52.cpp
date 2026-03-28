#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

class InternalKeyTest_52 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates an empty key
TEST_F(InternalKeyTest_52, DefaultConstructorCreatesEmptyKey_52) {
  InternalKey key;
  Slice encoded = key.Encode();
  EXPECT_TRUE(encoded.empty());
}

// Test constructing an InternalKey with user_key, sequence number, and value type
TEST_F(InternalKeyTest_52, ConstructWithParameters_52) {
  InternalKey key(Slice("testkey"), 100, kTypeValue);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "testkey");
}

// Test that Encode returns a non-empty slice for a valid key
TEST_F(InternalKeyTest_52, EncodeReturnsNonEmptySlice_52) {
  InternalKey key(Slice("hello"), 42, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  // user_key (5 bytes) + 8 bytes for sequence+type
  EXPECT_EQ(encoded.size(), 5 + 8);
}

// Test DecodeFrom with a valid encoded key
TEST_F(InternalKeyTest_52, DecodeFromValidEncoding_52) {
  InternalKey original(Slice("mykey"), 200, kTypeValue);
  Slice encoded = original.Encode();

  InternalKey decoded;
  EXPECT_TRUE(decoded.DecodeFrom(encoded));
  EXPECT_EQ(decoded.user_key().ToString(), "mykey");
}

// Test DecodeFrom with an empty slice should fail
TEST_F(InternalKeyTest_52, DecodeFromEmptySliceFails_52) {
  InternalKey key;
  EXPECT_FALSE(key.DecodeFrom(Slice()));
}

// Test DecodeFrom with too short data (less than 8 bytes)
TEST_F(InternalKeyTest_52, DecodeFromTooShortDataFails_52) {
  InternalKey key;
  // Less than 8 bytes means no room for sequence+type tag
  EXPECT_FALSE(key.DecodeFrom(Slice("short")));
}

// Test that Clear empties the internal representation
TEST_F(InternalKeyTest_52, ClearEmptiesKey_52) {
  InternalKey key(Slice("somekey"), 50, kTypeValue);
  EXPECT_FALSE(key.Encode().empty());
  key.Clear();
  Slice encoded = key.Encode();
  EXPECT_TRUE(encoded.empty());
}

// Test SetFrom with a ParsedInternalKey
TEST_F(InternalKeyTest_52, SetFromParsedInternalKey_52) {
  ParsedInternalKey parsed("userkey", 300, kTypeValue);
  InternalKey key;
  key.SetFrom(parsed);
  EXPECT_EQ(key.user_key().ToString(), "userkey");
}

// Test user_key with kTypeDeletion
TEST_F(InternalKeyTest_52, UserKeyWithDeletionType_52) {
  InternalKey key(Slice("delkey"), 500, kTypeDeletion);
  EXPECT_EQ(key.user_key().ToString(), "delkey");
}

// Test that encoding and decoding round-trips correctly
TEST_F(InternalKeyTest_52, EncodeDecodeRoundTrip_52) {
  InternalKey original(Slice("roundtrip"), 12345, kTypeValue);
  Slice encoded = original.Encode();

  InternalKey restored;
  ASSERT_TRUE(restored.DecodeFrom(encoded));
  EXPECT_EQ(restored.user_key().ToString(), original.user_key().ToString());
  EXPECT_EQ(restored.Encode().ToString(), original.Encode().ToString());
}

// Test with empty user key
TEST_F(InternalKeyTest_52, EmptyUserKey_52) {
  InternalKey key(Slice(""), 1, kTypeValue);
  Slice encoded = key.Encode();
  // Should have exactly 8 bytes (just the sequence+type tag)
  EXPECT_EQ(encoded.size(), 8u);
  EXPECT_EQ(key.user_key().ToString(), "");
}

// Test with large sequence number
TEST_F(InternalKeyTest_52, LargeSequenceNumber_52) {
  SequenceNumber large_seq = (1ull << 56) - 1;  // max sequence number
  InternalKey key(Slice("bigseq"), large_seq, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), "bigseq");

  Slice encoded = key.Encode();
  InternalKey decoded;
  ASSERT_TRUE(decoded.DecodeFrom(encoded));
  EXPECT_EQ(decoded.user_key().ToString(), "bigseq");
}

// Test with sequence number 0
TEST_F(InternalKeyTest_52, ZeroSequenceNumber_52) {
  InternalKey key(Slice("zeroseq"), 0, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), "zeroseq");
}

// Test DebugString returns non-empty for valid key
TEST_F(InternalKeyTest_52, DebugStringNonEmpty_52) {
  InternalKey key(Slice("debugkey"), 77, kTypeValue);
  std::string debug = key.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString for default constructed key
TEST_F(InternalKeyTest_52, DebugStringDefaultConstructed_52) {
  InternalKey key;
  std::string debug = key.DebugString();
  // Should return something (possibly indicating invalid/empty)
  // Just ensure it doesn't crash
  EXPECT_TRUE(true);
}

// Test SetFrom overwrites previous content
TEST_F(InternalKeyTest_52, SetFromOverwritesPrevious_52) {
  InternalKey key(Slice("first"), 1, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), "first");

  ParsedInternalKey parsed("second", 2, kTypeDeletion);
  key.SetFrom(parsed);
  EXPECT_EQ(key.user_key().ToString(), "second");
}

// Test with a long user key
TEST_F(InternalKeyTest_52, LongUserKey_52) {
  std::string long_key(1000, 'x');
  InternalKey key(Slice(long_key), 999, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), long_key);

  Slice encoded = key.Encode();
  EXPECT_EQ(encoded.size(), 1000 + 8);

  InternalKey decoded;
  ASSERT_TRUE(decoded.DecodeFrom(encoded));
  EXPECT_EQ(decoded.user_key().ToString(), long_key);
}

// Test DecodeFrom with exactly 8 bytes (empty user key)
TEST_F(InternalKeyTest_52, DecodeFromExactly8Bytes_52) {
  InternalKey original(Slice(""), 42, kTypeValue);
  Slice encoded = original.Encode();
  ASSERT_EQ(encoded.size(), 8u);

  InternalKey decoded;
  EXPECT_TRUE(decoded.DecodeFrom(encoded));
  EXPECT_EQ(decoded.user_key().ToString(), "");
}

}  // namespace leveldb
