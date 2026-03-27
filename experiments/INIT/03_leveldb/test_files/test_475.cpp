// TEST_ID: 475

#include "db/dbformat.h"
#include "leveldb/slice.h"

#include <gtest/gtest.h>
#include <limits>
#include <string>

namespace leveldb {

class InternalKeyTest_475 : public ::testing::Test {};

// Construct with a normal user key and verify observable properties.
TEST_F(InternalKeyTest_475, ConstructorStoresUserKey_475) {
  const std::string key_str = "user-key";
  const Slice user_key(key_str);
  const SequenceNumber seq = 42;
  const ValueType type = kTypeValue;  // use a public ValueType from the interface

  InternalKey ik(user_key, seq, type);

  // Observable via public API only
  EXPECT_EQ(ik.user_key().ToString(), key_str);
  EXPECT_FALSE(ik.Encode().empty());
  EXPECT_FALSE(ik.DebugString().empty());
  // Debug string should usually mention the user key (do not assert exact format)
  EXPECT_NE(ik.DebugString().find(key_str), std::string::npos);
}

// Encoding should round-trip through DecodeFrom on a default-constructed object.
TEST_F(InternalKeyTest_475, EncodeThenDecodeRoundTrip_475) {
  const std::string key_str = "k";
  const Slice user_key(key_str);
  const SequenceNumber seq = 7;
  const ValueType type = kTypeValue;

  InternalKey a(user_key, seq, type);
  Slice enc = a.Encode();

  InternalKey b;
  ASSERT_TRUE(b.DecodeFrom(enc));           // Observable success
  EXPECT_EQ(b.user_key().ToString(), key_str);
  EXPECT_FALSE(b.Encode().empty());
}

// Changing the sequence number should change the encoded bytes
// (without asserting any specific encoding format).
TEST_F(InternalKeyTest_475, DifferentSequenceNumbersAffectEncoding_475) {
  const std::string key_str = "same-key";
  const Slice user_key(key_str);

  InternalKey k1(user_key, 1, kTypeValue);
  InternalKey k2(user_key, 2, kTypeValue);

  EXPECT_NE(k1.Encode().ToString(), k2.Encode().ToString());
}

// Clear() should make the key appear empty through observable APIs.
TEST_F(InternalKeyTest_475, ClearMakesEncodeEmpty_475) {
  InternalKey ik(Slice("x"), 123, kTypeValue);
  ASSERT_FALSE(ik.Encode().empty());  // precondition

  ik.Clear();

  EXPECT_TRUE(ik.Encode().empty());
  // user_key() being empty is an observable, non-format-specific check.
  EXPECT_TRUE(ik.user_key().empty());
}

// Boundary: empty user key and maximum sequence number.
TEST_F(InternalKeyTest_475, EmptyUserKeyAndMaxSequence_475) {
  const std::string empty_key;
  const Slice user_key(empty_key);
  const SequenceNumber max_seq = std::numeric_limits<SequenceNumber>::max();

  InternalKey ik(user_key, max_seq, kTypeValue);

  EXPECT_TRUE(ik.user_key().empty());
  EXPECT_FALSE(ik.Encode().empty());   // still should produce an encoding
  EXPECT_FALSE(ik.DebugString().empty());
}

// SetFrom with a ParsedInternalKey should reflect through observable accessors.
TEST_F(InternalKeyTest_475, SetFromParsedInternalKey_475) {
  const std::string key_str = "pkey";
  ParsedInternalKey pik(Slice(key_str), 55, kTypeDeletion);

  InternalKey ik;
  ik.SetFrom(pik);

  EXPECT_EQ(ik.user_key().ToString(), key_str);
  EXPECT_FALSE(ik.Encode().empty());

  // Round-trip via Encode/Decode remains successful
  InternalKey decoded;
  ASSERT_TRUE(decoded.DecodeFrom(ik.Encode()));
  EXPECT_EQ(decoded.user_key().ToString(), key_str);
}

}  // namespace leveldb
