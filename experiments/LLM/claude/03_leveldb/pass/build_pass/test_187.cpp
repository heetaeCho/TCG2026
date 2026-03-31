#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include <string>

namespace leveldb {

// Test fixture for InternalKey tests
class InternalKeyTest_187 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a default-constructed InternalKey produces a debug string starting with "(bad)"
TEST_F(InternalKeyTest_187, DefaultConstructedDebugString_187) {
  InternalKey key;
  std::string debug = key.DebugString();
  // A default-constructed key has an empty rep_, which should fail to parse
  EXPECT_TRUE(debug.find("(bad)") != std::string::npos);
}

// Test that a properly constructed InternalKey produces a valid debug string
TEST_F(InternalKeyTest_187, ValidKeyDebugString_187) {
  InternalKey key(Slice("userkey"), 100, kTypeValue);
  std::string debug = key.DebugString();
  // Should not contain "(bad)" since the key is valid
  EXPECT_EQ(debug.find("(bad)"), std::string::npos);
  // Should contain the user key somewhere in the debug output
  EXPECT_TRUE(debug.find("userkey") != std::string::npos);
}

// Test DebugString with kTypeDeletion type
TEST_F(InternalKeyTest_187, DeletionKeyDebugString_187) {
  InternalKey key(Slice("deleted"), 42, kTypeDeletion);
  std::string debug = key.DebugString();
  EXPECT_EQ(debug.find("(bad)"), std::string::npos);
  EXPECT_TRUE(debug.find("deleted") != std::string::npos);
}

// Test that after Clear(), DebugString shows "(bad)"
TEST_F(InternalKeyTest_187, ClearedKeyDebugString_187) {
  InternalKey key(Slice("testkey"), 50, kTypeValue);
  key.Clear();
  std::string debug = key.DebugString();
  EXPECT_TRUE(debug.find("(bad)") != std::string::npos);
}

// Test Encode and DecodeFrom roundtrip
TEST_F(InternalKeyTest_187, EncodeDecodeRoundTrip_187) {
  InternalKey original(Slice("roundtrip"), 999, kTypeValue);
  Slice encoded = original.Encode();

  InternalKey decoded;
  EXPECT_TRUE(decoded.DecodeFrom(encoded));

  std::string orig_debug = original.DebugString();
  std::string dec_debug = decoded.DebugString();
  EXPECT_EQ(orig_debug, dec_debug);
}

// Test user_key() returns the correct user key
TEST_F(InternalKeyTest_187, UserKeyExtraction_187) {
  InternalKey key(Slice("myuserkey"), 200, kTypeValue);
  Slice ukey = key.user_key();
  EXPECT_EQ(ukey.ToString(), "myuserkey");
}

// Test SetFrom with a ParsedInternalKey
TEST_F(InternalKeyTest_187, SetFromParsedKey_187) {
  ParsedInternalKey parsed(Slice("setfrom"), 300, kTypeDeletion);
  InternalKey key;
  key.SetFrom(parsed);

  std::string debug = key.DebugString();
  EXPECT_EQ(debug.find("(bad)"), std::string::npos);
  EXPECT_TRUE(debug.find("setfrom") != std::string::npos);
}

// Test with sequence number 0
TEST_F(InternalKeyTest_187, ZeroSequenceNumber_187) {
  InternalKey key(Slice("zerokey"), 0, kTypeValue);
  std::string debug = key.DebugString();
  EXPECT_EQ(debug.find("(bad)"), std::string::npos);
  EXPECT_TRUE(debug.find("zerokey") != std::string::npos);
}

// Test with maximum sequence number
TEST_F(InternalKeyTest_187, MaxSequenceNumber_187) {
  InternalKey key(Slice("maxseq"), kMaxSequenceNumber, kTypeValue);
  std::string debug = key.DebugString();
  EXPECT_EQ(debug.find("(bad)"), std::string::npos);
  EXPECT_TRUE(debug.find("maxseq") != std::string::npos);
}

// Test with empty user key
TEST_F(InternalKeyTest_187, EmptyUserKey_187) {
  InternalKey key(Slice(""), 1, kTypeValue);
  std::string debug = key.DebugString();
  // Even with empty user key, the internal key should still parse correctly
  EXPECT_EQ(debug.find("(bad)"), std::string::npos);
}

// Test DecodeFrom with invalid (too short) data
TEST_F(InternalKeyTest_187, DecodeFromInvalidData_187) {
  InternalKey key;
  // A slice that's too short to be a valid internal key (needs at least 8 bytes for the trailer)
  EXPECT_TRUE(!key.DecodeFrom(Slice("short")));
}

// Test DecodeFrom with empty slice
TEST_F(InternalKeyTest_187, DecodeFromEmptySlice_187) {
  InternalKey key;
  EXPECT_TRUE(!key.DecodeFrom(Slice("")));
}

// Test that Encode returns non-empty for valid key
TEST_F(InternalKeyTest_187, EncodeNonEmpty_187) {
  InternalKey key(Slice("enctest"), 10, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  // The encoded form should be user_key + 8 bytes of trailer
  EXPECT_EQ(encoded.size(), 7 + 8);  // "enctest" is 7 chars
}

// Test that two keys with same data produce same debug strings
TEST_F(InternalKeyTest_187, ConsistentDebugString_187) {
  InternalKey key1(Slice("consistent"), 500, kTypeValue);
  InternalKey key2(Slice("consistent"), 500, kTypeValue);
  EXPECT_EQ(key1.DebugString(), key2.DebugString());
}

// Test that different keys produce different debug strings
TEST_F(InternalKeyTest_187, DifferentKeysDebugString_187) {
  InternalKey key1(Slice("alpha"), 100, kTypeValue);
  InternalKey key2(Slice("beta"), 200, kTypeDeletion);
  EXPECT_NE(key1.DebugString(), key2.DebugString());
}

// Test ParsedInternalKey DebugString
TEST_F(InternalKeyTest_187, ParsedInternalKeyDebugString_187) {
  ParsedInternalKey parsed(Slice("parsedkey"), 77, kTypeValue);
  std::string debug = parsed.DebugString();
  EXPECT_TRUE(debug.find("parsedkey") != std::string::npos);
}

}  // namespace leveldb
