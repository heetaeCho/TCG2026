// dbformat_lookupkey_test.cc
#include <gtest/gtest.h>
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace {

using leveldb::LookupKey;
using leveldb::SequenceNumber;
using leveldb::Slice;

class LookupKeyTest_482 : public ::testing::Test {
 protected:
  // Helper to build a Slice from std::string literal without trailing '\0'
  static Slice S(const std::string& s) { return Slice(s.data(), s.size()); }
};

// Normal operation: memtable_key() and internal_key() are non-empty and contain the user key prefix
TEST_F(LookupKeyTest_482, ConstructsAndExposesSlices_482) {
  const std::string user = "abc";
  const SequenceNumber seq = 12345;

  LookupKey lk(S(user), seq);

  // Public API: returned slices must be non-empty and user_key() must start with the original user key
  Slice uk = lk.user_key();
  EXPECT_FALSE(uk.empty());
  EXPECT_EQ(0, uk.compare(S(user)));

  Slice ik = lk.internal_key();
  EXPECT_FALSE(ik.empty());
  // internal_key() should begin with the user key per interface documentation in LevelDB
  ASSERT_GE(ik.size(), user.size());
  EXPECT_EQ(0, Slice(ik.data(), user.size()).compare(S(user)));

  Slice mk = lk.memtable_key();
  EXPECT_FALSE(mk.empty());
  // memtable_key() is a length-prefixed varint key; it must at least contain the internal key bytes.
  ASSERT_GE(mk.size(), ik.size());
  // The internal key bytes must appear as a suffix of memtable_key() (after a length prefix).
  EXPECT_EQ(0, Slice(mk.data() + (mk.size() - ik.size()), ik.size()).compare(ik));
}

// Boundary: empty user key
TEST_F(LookupKeyTest_482, EmptyUserKey_482) {
  const std::string user = "";
  const SequenceNumber seq = 7;

  LookupKey lk(S(user), seq);

  Slice uk = lk.user_key();
  EXPECT_TRUE(uk.empty());

  Slice ik = lk.internal_key();
  EXPECT_FALSE(ik.empty());  // still contains sequence/type trailer

  Slice mk = lk.memtable_key();
  EXPECT_FALSE(mk.empty());
  ASSERT_GE(mk.size(), ik.size());
  EXPECT_EQ(0, Slice(mk.data() + (mk.size() - ik.size()), ik.size()).compare(ik));
}

// Boundary: long key that exceeds inline buffer to exercise heap path (observable only via successful behavior)
TEST_F(LookupKeyTest_482, LongUserKey_HeapPathBehaviorallyOk_482) {
  std::string user(500, 'x');  // longer than any likely small inline buffer
  const SequenceNumber seq = 1;

  LookupKey lk(S(user), seq);

  // Observable behavior: APIs work and preserve user key bytes at the start of internal_key()
  Slice uk = lk.user_key();
  EXPECT_EQ(user.size(), uk.size());
  EXPECT_EQ(0, uk.compare(S(user)));

  Slice ik = lk.internal_key();
  ASSERT_GE(ik.size(), user.size());
  EXPECT_EQ(0, Slice(ik.data(), user.size()).compare(S(user)));

  Slice mk = lk.memtable_key();
  ASSERT_GE(mk.size(), ik.size());
  EXPECT_EQ(0, Slice(mk.data() + (mk.size() - ik.size()), ik.size()).compare(ik));
}

// Exceptional/edge: very large sequence number preserves prefix relationship (no overflow observable via API)
TEST_F(LookupKeyTest_482, LargeSequenceNumber_DoesNotCorruptLayout_482) {
  const std::string user = "k";
  const SequenceNumber seq = std::numeric_limits<SequenceNumber>::max();

  LookupKey lk(S(user), seq);

  // We cannot inspect encoded sequence/type; just ensure returned slices remain consistent.
  Slice uk = lk.user_key();
  EXPECT_EQ(0, uk.compare(S(user)));

  Slice ik = lk.internal_key();
  ASSERT_GE(ik.size(), user.size());
  EXPECT_EQ(0, Slice(ik.data(), user.size()).compare(S(user)));

  Slice mk = lk.memtable_key();
  ASSERT_GE(mk.size(), ik.size());
  EXPECT_EQ(0, Slice(mk.data() + (mk.size() - ik.size()), ik.size()).compare(ik));
}

// Lifetime: returned slices must remain valid while LookupKey is alive (basic observable check)
TEST_F(LookupKeyTest_482, SliceStabilityWhileAlive_482) {
  Slice uk_copy, ik_copy, mk_copy;
  {
    std::string user = "persist";
    LookupKey lk(S(user), 100);
    uk_copy = lk.user_key();
    ik_copy = lk.internal_key();
    mk_copy = lk.memtable_key();

    // Within lifetime, repeated calls should be identical by value.
    EXPECT_EQ(0, lk.user_key().compare(uk_copy));
    EXPECT_EQ(0, lk.internal_key().compare(ik_copy));
    EXPECT_EQ(0, lk.memtable_key().compare(mk_copy));
  }
  // We do NOT dereference slices after destruction (would be UB).
  SUCCEED();
}

}  // namespace
