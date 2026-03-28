// File: internalkey_user_key_test_52.cc

#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>

using namespace leveldb;

class InternalKeyUserKeyTest_52 : public ::testing::Test {
protected:
  static SequenceNumber Seq(std::uint64_t s) { return static_cast<SequenceNumber>(s); }
};

// Normal operation: constructor preserves user key
TEST_F(InternalKeyUserKeyTest_52, ConstructorPreservesUserKey_52) {
  std::string uk = "hello";
  InternalKey ik(Slice(uk), Seq(1), kTypeValue);

  EXPECT_EQ(uk, ik.user_key().ToString());
}

// Normal operation: Encode -> DecodeFrom round trip preserves user key
TEST_F(InternalKeyUserKeyTest_52, EncodeDecodeRoundTripPreservesUserKey_52) {
  std::string uk = "user-key-xyz";
  InternalKey a(Slice(uk), Seq(123), kTypeValue);

  Slice encoded = a.Encode();

  InternalKey b;
  ASSERT_TRUE(b.DecodeFrom(encoded));  // observable success path
  EXPECT_EQ(uk, b.user_key().ToString());
}

// Boundary: empty user key should be observable as empty
TEST_F(InternalKeyUserKeyTest_52, EmptyUserKey_52) {
  std::string uk; // empty
  InternalKey ik(Slice(uk), Seq(0), kTypeValue);

  EXPECT_TRUE(ik.user_key().empty());
  EXPECT_EQ(0u, ik.user_key().size());
  EXPECT_EQ("", ik.user_key().ToString());
}

// Boundary: user key containing embedded nulls should round-trip intact
TEST_F(InternalKeyUserKeyTest_52, UserKeyWithEmbeddedNulls_52) {
  std::string uk("a\0b\0c", 5); // includes two NUL bytes
  InternalKey a(Slice(uk), Seq(42), kTypeValue);

  // Direct from constructor
  EXPECT_EQ(uk, a.user_key().ToString());
  EXPECT_EQ(5u, a.user_key().size());

  // Encode/Decode path
  InternalKey b;
  ASSERT_TRUE(b.DecodeFrom(a.Encode()));
  EXPECT_EQ(uk, b.user_key().ToString());
  EXPECT_EQ(5u, b.user_key().size());
}

// Boundary: long user key (size stress) still returned intact
TEST_F(InternalKeyUserKeyTest_52, LongUserKey_52) {
  const size_t N = 1 << 20; // 1 MiB
  std::string uk;
  uk.reserve(N);
  for (size_t i = 0; i < N; ++i) uk.push_back(static_cast<char>(i & 0xFF));

  InternalKey a(Slice(uk), Seq(777), kTypeValue);
  EXPECT_EQ(N, a.user_key().size());
  EXPECT_EQ(uk, a.user_key().ToString());

  InternalKey b;
  ASSERT_TRUE(b.DecodeFrom(a.Encode()));
  EXPECT_EQ(N, b.user_key().size());
  EXPECT_EQ(uk, b.user_key().ToString());
}

// Observable effect: Clear() results in an empty user key (no assumptions beyond emptiness)
TEST_F(InternalKeyUserKeyTest_52, ClearMakesUserKeyEmpty_52) {
  InternalKey ik(Slice("data"), Seq(9), kTypeValue);
  ik.Clear();

  // Only check observable emptiness; do not assume anything else
  EXPECT_TRUE(ik.user_key().empty());
  EXPECT_EQ(0u, ik.user_key().size());
}

// Normal operation via public mutator: SetFrom updates the user key
TEST_F(InternalKeyUserKeyTest_52, SetFromUpdatesUserKey_52) {
  ParsedInternalKey pik;
  pik.user_key = Slice("new-user");
  pik.sequence = Seq(555);
  pik.type = kTypeValue;

  InternalKey ik;
  ik.SetFrom(pik);

  EXPECT_EQ("new-user", ik.user_key().ToString());
}

// Error case (observable): DecodeFrom failure does not crash; user_key can be observed
// without relying on specific content after failure.
TEST_F(InternalKeyUserKeyTest_52, DecodeFromInvalidInputIsHandled_52) {
  // Provide an obviously invalid slice (e.g., empty)
  InternalKey ik;
  Slice bad; // empty slice
  bool ok = ik.DecodeFrom(bad);

  EXPECT_FALSE(ok); // Only observable output we assert on
  // We avoid asserting the specific value of user_key() after failure
  // (behavior unspecified), but we ensure it is safe to call.
  (void)ik.user_key(); // call to ensure no crash / UB in observable sense
}
