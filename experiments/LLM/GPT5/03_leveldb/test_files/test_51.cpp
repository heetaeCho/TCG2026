// File: db/internal_key_encode_test_51.cc

#include "db/dbformat.h"
#include <gtest/gtest.h>

namespace leveldb {

static InternalKey MakeKey(const Slice& user_key,
                           SequenceNumber seq = 1,
                           ValueType type = kTypeValue) {
  return InternalKey(user_key, seq, type);
}

// Normal operation: Encode returns a non-empty Slice after construction.
TEST(InternalKeyEncodeTest_51, EncodeReturnsNonEmptyAfterConstruction_51) {
  InternalKey ik = MakeKey(Slice("user"));
  Slice enc = ik.Encode();
  EXPECT_GT(enc.size(), 0u);
}

// Normal operation: Encode/Decode round-trip preserves the byte representation.
TEST(InternalKeyEncodeTest_51, EncodeThenDecodeRoundTrip_51) {
  InternalKey original = MakeKey(Slice("alpha"));
  std::string bytes = original.Encode().ToString();

  InternalKey parsed;
  ASSERT_TRUE(parsed.DecodeFrom(Slice(bytes)));
  EXPECT_EQ(parsed.Encode().ToString(), bytes);
}

// Boundary: very long user key still produces a valid (non-empty) encoding and round-trips.
TEST(InternalKeyEncodeTest_51, VeryLongUserKeyRoundTrip_51) {
  std::string long_key(1024 * 1024, 'x');  // 1MB
  InternalKey original = MakeKey(Slice(long_key), 123456789, kTypeValue);
  std::string bytes = original.Encode().ToString();

  ASSERT_FALSE(bytes.empty());

  InternalKey parsed;
  ASSERT_TRUE(parsed.DecodeFrom(Slice(bytes)));
  EXPECT_EQ(parsed.Encode().ToString(), bytes);
}

// Exceptional/error case (observable): DecodeFrom with empty Slice should fail.
TEST(InternalKeyEncodeTest_51, DecodeFromEmptySliceFails_51) {
  InternalKey ik;
  EXPECT_FALSE(ik.DecodeFrom(Slice()));
}

// State-dependent behavior: after Clear(), calling Encode() should fail via debug assertion.
// Guard with death-test support and non-NDEBUG builds.
#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG
TEST(InternalKeyEncodeTest_51, EncodeDiesAfterClear_51) {
  InternalKey ik = MakeKey(Slice("z"));
  ik.Clear();
  EXPECT_DEATH_IF_SUPPORTED(ik.Encode(), "");  // message ignored/empty: platform-specific
}
#endif  // !NDEBUG
#endif  // GTEST_HAS_DEATH_TEST

// Sanity: user_key() reflects the user key provided at construction (observable contract).
TEST(InternalKeyEncodeTest_51, UserKeyIsAccessible_51) {
  Slice user("hello");
  InternalKey ik = MakeKey(user, 42, kTypeValue);
  EXPECT_EQ(ik.user_key().ToString(), user.ToString());
}

}  // namespace leveldb
