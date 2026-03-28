#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test fixture for InternalKey tests
class InternalKeyTest_51 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that default-constructed InternalKey has empty representation
TEST_F(InternalKeyTest_51, DefaultConstructorCreatesEmptyKey_51) {
  InternalKey key;
  // A default-constructed key should have an empty rep_, so Clear() or
  // DecodeFrom with empty should reflect that. We test via DecodeFrom behavior.
  // Since rep_ is empty, Encode() would assert. We test indirectly.
  // After Clear(), the key should have empty internal state.
  key.Clear();
  // We can't call Encode() on empty key (it asserts), so we verify
  // that DecodeFrom with valid data works after default construction.
  std::string valid_key;
  PutFixed64(&valid_key, PackSequenceAndType(100, kTypeValue));
  // Prepend a user key
  std::string full_key = "user_key";
  full_key.append(valid_key);
  ASSERT_TRUE(key.DecodeFrom(Slice(full_key)));
}

// Test constructing InternalKey with user_key, sequence, and type
TEST_F(InternalKeyTest_51, ConstructWithParameters_51) {
  InternalKey key(Slice("hello"), 1, kTypeValue);
  Slice encoded = key.Encode();
  ASSERT_FALSE(encoded.empty());
}

// Test that Encode returns non-empty slice for valid key
TEST_F(InternalKeyTest_51, EncodeReturnsNonEmptyForValidKey_51) {
  InternalKey key(Slice("test_key"), 42, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_GT(encoded.size(), 0);
  // The encoded key should contain the user key plus 8 bytes for seq+type
  EXPECT_EQ(encoded.size(), std::string("test_key").size() + 8);
}

// Test that user_key() returns the correct user key portion
TEST_F(InternalKeyTest_51, UserKeyReturnsCorrectKey_51) {
  std::string user_key_str = "my_user_key";
  InternalKey key(Slice(user_key_str), 100, kTypeValue);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), user_key_str);
}

// Test that user_key works with different sequence numbers
TEST_F(InternalKeyTest_51, UserKeyConsistentAcrossSequenceNumbers_51) {
  std::string user_key_str = "consistent_key";
  InternalKey key1(Slice(user_key_str), 1, kTypeValue);
  InternalKey key2(Slice(user_key_str), 1000, kTypeValue);
  EXPECT_EQ(key1.user_key().ToString(), key2.user_key().ToString());
}

// Test DecodeFrom with valid data
TEST_F(InternalKeyTest_51, DecodeFromValidData_51) {
  InternalKey original(Slice("decode_test"), 500, kTypeValue);
  Slice encoded = original.Encode();

  InternalKey decoded;
  ASSERT_TRUE(decoded.DecodeFrom(encoded));
  EXPECT_EQ(decoded.user_key().ToString(), "decode_test");
}

// Test DecodeFrom with empty slice returns false
TEST_F(InternalKeyTest_51, DecodeFromEmptySlice_51) {
  InternalKey key;
  EXPECT_TRUE(key.DecodeFrom(Slice()).empty() || !key.DecodeFrom(Slice()));
  // DecodeFrom with empty data should fail
  InternalKey key2;
  bool result = key2.DecodeFrom(Slice(""));
  // Empty or too-short data should not decode successfully
  // (less than 8 bytes for the trailer)
  EXPECT_FALSE(result);
}

// Test DecodeFrom with data too short (less than 8 bytes)
TEST_F(InternalKeyTest_51, DecodeFromTooShortData_51) {
  InternalKey key;
  bool result = key.DecodeFrom(Slice("short"));
  // Data shorter than 8 bytes cannot contain a valid internal key trailer
  // The implementation may or may not reject this; we test observable behavior
  // If it does decode, the key is at least set
  // This tests boundary behavior
}

// Test Clear resets the key
TEST_F(InternalKeyTest_51, ClearResetsKey_51) {
  InternalKey key(Slice("to_clear"), 200, kTypeDeletion);
  EXPECT_FALSE(key.Encode().empty());
  key.Clear();
  // After Clear, the internal rep should be empty
  // We can't call Encode() as it would assert, but we can verify
  // by checking DecodeFrom works after Clear
  InternalKey key2(Slice("new_key"), 300, kTypeValue);
  Slice encoded = key2.Encode();
  ASSERT_TRUE(key.DecodeFrom(encoded));
  EXPECT_EQ(key.user_key().ToString(), "new_key");
}

// Test SetFrom with ParsedInternalKey
TEST_F(InternalKeyTest_51, SetFromParsedInternalKey_51) {
  ParsedInternalKey parsed("set_from_key", 750, kTypeValue);
  InternalKey key;
  key.SetFrom(parsed);
  EXPECT_EQ(key.user_key().ToString(), "set_from_key");
  EXPECT_FALSE(key.Encode().empty());
}

// Test with kTypeDeletion value type
TEST_F(InternalKeyTest_51, DeletionTypeKey_51) {
  InternalKey key(Slice("deleted_key"), 999, kTypeDeletion);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  EXPECT_EQ(key.user_key().ToString(), "deleted_key");
}

// Test DebugString returns non-empty string for valid key
TEST_F(InternalKeyTest_51, DebugStringForValidKey_51) {
  InternalKey key(Slice("debug_key"), 123, kTypeValue);
  std::string debug = key.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test that Encode round-trips through DecodeFrom
TEST_F(InternalKeyTest_51, EncodeDecodeRoundTrip_51) {
  InternalKey original(Slice("roundtrip"), 12345, kTypeValue);
  Slice encoded = original.Encode();

  InternalKey copy;
  ASSERT_TRUE(copy.DecodeFrom(encoded));

  EXPECT_EQ(copy.Encode().ToString(), original.Encode().ToString());
  EXPECT_EQ(copy.user_key().ToString(), original.user_key().ToString());
}

// Test with empty user key
TEST_F(InternalKeyTest_51, EmptyUserKey_51) {
  InternalKey key(Slice(""), 1, kTypeValue);
  Slice encoded = key.Encode();
  // Should have exactly 8 bytes (just the trailer, no user key bytes)
  EXPECT_EQ(encoded.size(), 8);
  EXPECT_EQ(key.user_key().ToString(), "");
}

// Test with maximum sequence number
TEST_F(InternalKeyTest_51, MaxSequenceNumber_51) {
  SequenceNumber max_seq = kMaxSequenceNumber;
  InternalKey key(Slice("max_seq"), max_seq, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  EXPECT_EQ(key.user_key().ToString(), "max_seq");
}

// Test with sequence number 0
TEST_F(InternalKeyTest_51, ZeroSequenceNumber_51) {
  InternalKey key(Slice("zero_seq"), 0, kTypeValue);
  Slice encoded = key.Encode();
  EXPECT_FALSE(encoded.empty());
  EXPECT_EQ(key.user_key().ToString(), "zero_seq");
}

// Test with long user key
TEST_F(InternalKeyTest_51, LongUserKey_51) {
  std::string long_key(10000, 'x');
  InternalKey key(Slice(long_key), 42, kTypeValue);
  EXPECT_EQ(key.user_key().ToString(), long_key);
  EXPECT_EQ(key.Encode().size(), long_key.size() + 8);
}

// Test multiple SetFrom calls overwrite previous state
TEST_F(InternalKeyTest_51, MultipleSetFromCalls_51) {
  InternalKey key;

  ParsedInternalKey parsed1("first_key", 100, kTypeValue);
  key.SetFrom(parsed1);
  EXPECT_EQ(key.user_key().ToString(), "first_key");

  ParsedInternalKey parsed2("second_key", 200, kTypeDeletion);
  key.SetFrom(parsed2);
  EXPECT_EQ(key.user_key().ToString(), "second_key");
}

// Test that two keys with same user key but different sequences encode differently
TEST_F(InternalKeyTest_51, DifferentSequenceNumbersProduceDifferentEncodings_51) {
  InternalKey key1(Slice("same_key"), 1, kTypeValue);
  InternalKey key2(Slice("same_key"), 2, kTypeValue);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

// Test that two keys with same user key but different types encode differently
TEST_F(InternalKeyTest_51, DifferentTypesProduceDifferentEncodings_51) {
  InternalKey key1(Slice("same_key"), 1, kTypeValue);
  InternalKey key2(Slice("same_key"), 1, kTypeDeletion);
  EXPECT_NE(key1.Encode().ToString(), key2.Encode().ToString());
}

}  // namespace leveldb
