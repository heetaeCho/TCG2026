// File: db/internalkey_clear_test.cc
#include "db/dbformat.h"
#include "gtest/gtest.h"
#include "leveldb/slice.h"

using leveldb::InternalKey;
using leveldb::SequenceNumber;
using leveldb::Slice;
using leveldb::ValueType;

namespace {

// Small helper that builds a valid encoded InternalKey using only public APIs.
// We avoid relying on any internal details.
static std::string MakeEncodedIK(const Slice& user_key,
                                 SequenceNumber seq,
                                 ValueType type) {
  InternalKey k(user_key, seq, type);
  Slice enc = k.Encode();
  return std::string(enc.data(), enc.size());  // own the bytes
}

}  // namespace

// 1) Normal: Clear on a freshly constructed object keeps it empty.
TEST(InternalKeyClearTest_54, ClearOnDefaultConstructedKeepsEmpty_54) {
  InternalKey k;
  // Before Clear: default-constructed key is allowed to be empty; verify via Encode size.
  EXPECT_EQ(0u, k.Encode().size());
  EXPECT_EQ(0u, k.user_key().size());

  // After Clear: still empty.
  k.Clear();
  EXPECT_EQ(0u, k.Encode().size());
  EXPECT_EQ(0u, k.user_key().size());
}

// 2) Normal: Clear after DecodeFrom makes representation empty and safe to query.
TEST(InternalKeyClearTest_54, ClearAfterDecodeFromEmptiesState_54) {
  // Build a valid encoded key via the public constructor + Encode.
  const std::string encoded = MakeEncodedIK(Slice("abc"), /*seq=*/123, /*type=*/static_cast<ValueType>(1));
  Slice enc_slice(encoded);

  InternalKey k;
  ASSERT_TRUE(k.DecodeFrom(enc_slice));  // Observable success via bool return

  // Sanity: now it shouldn't be empty.
  EXPECT_GT(k.Encode().size(), 0u);
  EXPECT_GT(k.user_key().size(), 0u);

  // Clear should empty it.
  k.Clear();
  EXPECT_EQ(0u, k.Encode().size());
  EXPECT_EQ(0u, k.user_key().size());
}

// 3) Boundary: Calling Clear multiple times is idempotent.
TEST(InternalKeyClearTest_54, ClearIsIdempotent_54) {
  InternalKey k;
  // Seed with something first so we know it had content.
  const std::string encoded = MakeEncodedIK(Slice("xyz"), /*seq=*/1, /*type=*/static_cast<ValueType>(1));
  ASSERT_TRUE(k.DecodeFrom(Slice(encoded)));
  EXPECT_GT(k.Encode().size(), 0u);

  // First Clear
  k.Clear();
  EXPECT_EQ(0u, k.Encode().size());
  EXPECT_EQ(0u, k.user_key().size());

  // Second Clear should be a no-op and remain empty.
  k.Clear();
  EXPECT_EQ(0u, k.Encode().size());
  EXPECT_EQ(0u, k.user_key().size());
}

// 4) Isolation: Clearing one instance does not affect another.
TEST(InternalKeyClearTest_54, ClearDoesNotAffectOtherInstances_54) {
  const std::string encodedA = MakeEncodedIK(Slice("keyA"), /*seq=*/5, /*type=*/static_cast<ValueType>(1));
  const std::string encodedB = MakeEncodedIK(Slice("keyB"), /*seq=*/6, /*type=*/static_cast<ValueType>(1));

  InternalKey a, b;
  ASSERT_TRUE(a.DecodeFrom(Slice(encodedA)));
  ASSERT_TRUE(b.DecodeFrom(Slice(encodedB)));

  // Clear only 'a'
  a.Clear();

  // 'a' is empty
  EXPECT_EQ(0u, a.Encode().size());
  EXPECT_EQ(0u, a.user_key().size());

  // 'b' should be unaffected and remain non-empty
  EXPECT_GT(b.Encode().size(), 0u);
  EXPECT_GT(b.user_key().size(), 0u);
}

// 5) Reuse: After Clear, the object can be reused and DecodeFrom works again.
TEST(InternalKeyClearTest_54, ReuseAfterClearWithDecodeFrom_54) {
  InternalKey k;

  // Seed with first value and then clear.
  const std::string first = MakeEncodedIK(Slice("first"), /*seq=*/10, /*type=*/static_cast<ValueType>(1));
  ASSERT_TRUE(k.DecodeFrom(Slice(first)));
  k.Clear();
  EXPECT_EQ(0u, k.Encode().size());
  EXPECT_EQ(0u, k.user_key().size());

  // Reuse the same object with a different key via DecodeFrom.
  const std::string second = MakeEncodedIK(Slice("second"), /*seq=*/11, /*type=*/static_cast<ValueType>(1));
  ASSERT_TRUE(k.DecodeFrom(Slice(second)));

  // Should now be non-empty again.
  EXPECT_GT(k.Encode().size(), 0u);
  EXPECT_GT(k.user_key().size(), 0u);
}

