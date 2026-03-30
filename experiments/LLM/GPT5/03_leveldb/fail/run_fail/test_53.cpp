// File: db/internal_key_setfrom_test.cc

#include "db/dbformat.h"
#include <gtest/gtest.h>
#include <limits>
#include <string>

namespace {

using leveldb::InternalKey;
using leveldb::ParsedInternalKey;
using leveldb::SequenceNumber;
using leveldb::Slice;
using leveldb::ValueType;

// Test fixture (kept minimal; no internal state access)
class InternalKeyTest_53 : public ::testing::Test {
protected:
  static std::string SliceToString(const Slice& s) {
    return std::string(s.data(), s.size());
  }
};

TEST_F(InternalKeyTest_53, SetFromMatchesConstructor_53) {
  const std::string uk = "abc";
  const SequenceNumber seq = 100;
  const ValueType type = static_cast<ValueType>(1); // Typically kTypeValue

  ParsedInternalKey pik(Slice(uk), seq, type);

  InternalKey from_ctor(uk, seq, type);
  InternalKey from_set;
  from_set.SetFrom(pik);

  // Encoded forms must match when built via ctor vs SetFrom
  EXPECT_EQ(SliceToString(from_ctor.Encode()), SliceToString(from_set.Encode()));
  // user_key() should reflect what we set
  EXPECT_EQ(uk, SliceToString(from_set.user_key()));
}

TEST_F(InternalKeyTest_53, SetFromOverwritesPreviousState_53) {
  const std::string first_key = "first";
  const std::string second_key = "x";
  const SequenceNumber first_seq = 7;
  const SequenceNumber second_seq = 9999;

  // Types chosen just to differ; values come from the public enum in real code.
  const ValueType first_type = static_cast<ValueType>(1);
  const ValueType second_type = static_cast<ValueType>(0);

  ParsedInternalKey first_pik(Slice(first_key), first_seq, first_type);
  ParsedInternalKey second_pik(Slice(second_key), second_seq, second_type);

  InternalKey ik;
  ik.SetFrom(first_pik);
  const std::string encoded_first = SliceToString(ik.Encode());

  // Overwrite with a different key/seq/type
  ik.SetFrom(second_pik);
  const std::string encoded_second = SliceToString(ik.Encode());

  // Compare with a freshly constructed key for the second values
  InternalKey expected_second(second_key, second_seq, second_type);
  EXPECT_EQ(SliceToString(expected_second.Encode()), encoded_second);

  // Ensure it's not the old encoding anymore
  EXPECT_NE(encoded_first, encoded_second);
}

TEST_F(InternalKeyTest_53, SetFromEmptyUserKey_53) {
  const std::string empty_key;
  const SequenceNumber seq = 1;
  const ValueType type = static_cast<ValueType>(1); // Typically kTypeValue

  ParsedInternalKey pik(Slice(empty_key), seq, type);
  InternalKey ik;
  ik.SetFrom(pik);

  // Round-trip via DecodeFrom should succeed and preserve user key
  InternalKey decoded;
  ASSERT_TRUE(decoded.DecodeFrom(ik.Encode()));
  EXPECT_EQ(empty_key, SliceToString(decoded.user_key()));

  // Constructor path should match SetFrom path
  InternalKey via_ctor(empty_key, seq, type);
  EXPECT_EQ(SliceToString(via_ctor.Encode()), SliceToString(ik.Encode()));
}

TEST_F(InternalKeyTest_53, SetFromRoundTripDecode_53) {
  const std::string uk = "user/key/with/slashes";
  const SequenceNumber seq = 123456789ULL;
  const ValueType type = static_cast<ValueType>(1); // Typically kTypeValue

  ParsedInternalKey pik(Slice(uk), seq, type);

  InternalKey ik;
  ik.SetFrom(pik);

  InternalKey decoded;
  ASSERT_TRUE(decoded.DecodeFrom(ik.Encode()));
  EXPECT_EQ(uk, SliceToString(decoded.user_key()));
  // Encoded bytes of decoded should match original
  EXPECT_EQ(SliceToString(ik.Encode()), SliceToString(decoded.Encode()));
}

TEST_F(InternalKeyTest_53, SetFromDifferentValueTypesProduceDifferentEncodings_53) {
  const std::string uk = "same-user-key";
  const SequenceNumber seq = 42;

  const ValueType type_value = static_cast<ValueType>(1);    // e.g., kTypeValue
  const ValueType type_delete = static_cast<ValueType>(0);   // e.g., kTypeDeletion

  InternalKey a(uk, seq, type_value);

  ParsedInternalKey pik_del(Slice(uk), seq, type_delete);
  InternalKey b;
  b.SetFrom(pik_del);

  // With same user key & seq but different ValueType, encodings should differ
  EXPECT_NE(SliceToString(a.Encode()), SliceToString(b.Encode()));
}

TEST_F(InternalKeyTest_53, SetFromWithLargeSequenceNumber_53) {
  // We don't assume internal constraints; treat SequenceNumber as typedef'd uint64_t
  const std::string uk = "big-seq";
  const SequenceNumber big = std::numeric_limits<SequenceNumber>::max();
  const ValueType type = static_cast<ValueType>(1);

  ParsedInternalKey pik(Slice(uk), big, type);
  InternalKey ik;
  ik.SetFrom(pik);

  // It should round-trip via DecodeFrom and preserve the user key.
  InternalKey decoded;
  ASSERT_TRUE(decoded.DecodeFrom(ik.Encode()));
  EXPECT_EQ(uk, SliceToString(decoded.user_key()));

  // A ctor-built key with the same inputs should produce the same encoding.
  InternalKey via_ctor(uk, big, type);
  EXPECT_EQ(SliceToString(via_ctor.Encode()), SliceToString(ik.Encode()));
}

}  // namespace
