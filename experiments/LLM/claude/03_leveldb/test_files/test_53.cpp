#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test fixture for InternalKey tests
class InternalKeyTest_53 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that SetFrom correctly sets the internal key from a ParsedInternalKey
TEST_F(InternalKeyTest_53, SetFromBasic_53) {
  ParsedInternalKey parsed("user_key", 100, kTypeValue);
  InternalKey internal_key;
  internal_key.SetFrom(parsed);

  // After SetFrom, Encode() should return a non-empty slice
  Slice encoded = internal_key.Encode();
  ASSERT_FALSE(encoded.empty());

  // The user_key should be recoverable
  Slice extracted_user_key = internal_key.user_key();
  EXPECT_EQ(extracted_user_key.ToString(), "user_key");
}

// Test SetFrom with kTypeDeletion
TEST_F(InternalKeyTest_53, SetFromDeletion_53) {
  ParsedInternalKey parsed("delete_key", 200, kTypeDeletion);
  InternalKey internal_key;
  internal_key.SetFrom(parsed);

  Slice encoded = internal_key.Encode();
  ASSERT_FALSE(encoded.empty());

  Slice extracted_user_key = internal_key.user_key();
  EXPECT_EQ(extracted_user_key.ToString(), "delete_key");
}

// Test that SetFrom overwrites previous content
TEST_F(InternalKeyTest_53, SetFromOverwritesPrevious_53) {
  InternalKey internal_key("first_key", 50, kTypeValue);

  Slice first_user_key = internal_key.user_key();
  EXPECT_EQ(first_user_key.ToString(), "first_key");

  ParsedInternalKey parsed("second_key", 100, kTypeValue);
  internal_key.SetFrom(parsed);

  Slice second_user_key = internal_key.user_key();
  EXPECT_EQ(second_user_key.ToString(), "second_key");
}

// Test SetFrom with empty user key
TEST_F(InternalKeyTest_53, SetFromEmptyUserKey_53) {
  ParsedInternalKey parsed("", 0, kTypeValue);
  InternalKey internal_key;
  internal_key.SetFrom(parsed);

  Slice encoded = internal_key.Encode();
  ASSERT_FALSE(encoded.empty());

  Slice extracted_user_key = internal_key.user_key();
  EXPECT_EQ(extracted_user_key.ToString(), "");
}

// Test SetFrom with max sequence number
TEST_F(InternalKeyTest_53, SetFromMaxSequence_53) {
  ParsedInternalKey parsed("max_seq_key", kMaxSequenceNumber, kTypeValue);
  InternalKey internal_key;
  internal_key.SetFrom(parsed);

  Slice encoded = internal_key.Encode();
  ASSERT_FALSE(encoded.empty());

  Slice extracted_user_key = internal_key.user_key();
  EXPECT_EQ(extracted_user_key.ToString(), "max_seq_key");
}

// Test SetFrom with zero sequence number
TEST_F(InternalKeyTest_53, SetFromZeroSequence_53) {
  ParsedInternalKey parsed("zero_seq", 0, kTypeValue);
  InternalKey internal_key;
  internal_key.SetFrom(parsed);

  Slice extracted_user_key = internal_key.user_key();
  EXPECT_EQ(extracted_user_key.ToString(), "zero_seq");
}

// Test that SetFrom result can be decoded back
TEST_F(InternalKeyTest_53, SetFromRoundTrip_53) {
  ParsedInternalKey original("roundtrip_key", 42, kTypeValue);
  InternalKey internal_key;
  internal_key.SetFrom(original);

  Slice encoded = internal_key.Encode();

  // Parse the encoded internal key back
  ParsedInternalKey decoded;
  ASSERT_TRUE(ParseInternalKey(encoded, &decoded));
  EXPECT_EQ(decoded.user_key.ToString(), "roundtrip_key");
  EXPECT_EQ(decoded.sequence, 42u);
  EXPECT_EQ(decoded.type, kTypeValue);
}

// Test SetFrom round trip with deletion type
TEST_F(InternalKeyTest_53, SetFromRoundTripDeletion_53) {
  ParsedInternalKey original("del_key", 999, kTypeDeletion);
  InternalKey internal_key;
  internal_key.SetFrom(original);

  Slice encoded = internal_key.Encode();

  ParsedInternalKey decoded;
  ASSERT_TRUE(ParseInternalKey(encoded, &decoded));
  EXPECT_EQ(decoded.user_key.ToString(), "del_key");
  EXPECT_EQ(decoded.sequence, 999u);
  EXPECT_EQ(decoded.type, kTypeDeletion);
}

// Test constructor-based initialization matches SetFrom
TEST_F(InternalKeyTest_53, ConstructorMatchesSetFrom_53) {
  InternalKey from_constructor("test_key", 100, kTypeValue);

  ParsedInternalKey parsed("test_key", 100, kTypeValue);
  InternalKey from_set;
  from_set.SetFrom(parsed);

  EXPECT_EQ(from_constructor.Encode().ToString(),
            from_set.Encode().ToString());
}

// Test Clear after SetFrom
TEST_F(InternalKeyTest_53, ClearAfterSetFrom_53) {
  ParsedInternalKey parsed("some_key", 50, kTypeValue);
  InternalKey internal_key;
  internal_key.SetFrom(parsed);

  ASSERT_FALSE(internal_key.Encode().empty());

  internal_key.Clear();
  EXPECT_TRUE(internal_key.Encode().empty());
}

// Test SetFrom with a long user key
TEST_F(InternalKeyTest_53, SetFromLongUserKey_53) {
  std::string long_key(10000, 'x');
  ParsedInternalKey parsed(long_key, 1, kTypeValue);
  InternalKey internal_key;
  internal_key.SetFrom(parsed);

  Slice extracted_user_key = internal_key.user_key();
  EXPECT_EQ(extracted_user_key.ToString(), long_key);
}

// Test multiple SetFrom calls
TEST_F(InternalKeyTest_53, MultipleSetFrom_53) {
  InternalKey internal_key;

  for (int i = 0; i < 100; i++) {
    std::string key = "key_" + std::to_string(i);
    ParsedInternalKey parsed(key, static_cast<SequenceNumber>(i), kTypeValue);
    internal_key.SetFrom(parsed);

    Slice extracted = internal_key.user_key();
    EXPECT_EQ(extracted.ToString(), key);
  }
}

// Test DecodeFrom with encoded data from SetFrom
TEST_F(InternalKeyTest_53, DecodeFromEncodedSetFrom_53) {
  ParsedInternalKey parsed("decode_test", 77, kTypeDeletion);
  InternalKey original;
  original.SetFrom(parsed);

  std::string encoded_str = original.Encode().ToString();

  InternalKey decoded;
  ASSERT_TRUE(decoded.DecodeFrom(Slice(encoded_str)));
  EXPECT_EQ(decoded.user_key().ToString(), "decode_test");
}

// Test DebugString after SetFrom (just ensure it doesn't crash and returns something)
TEST_F(InternalKeyTest_53, DebugStringAfterSetFrom_53) {
  ParsedInternalKey parsed("debug_key", 10, kTypeValue);
  InternalKey internal_key;
  internal_key.SetFrom(parsed);

  std::string debug = internal_key.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test default constructor produces empty encode
TEST_F(InternalKeyTest_53, DefaultConstructorEmpty_53) {
  InternalKey internal_key;
  EXPECT_TRUE(internal_key.Encode().empty());
}

}  // namespace leveldb
