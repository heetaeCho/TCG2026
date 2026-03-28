// File: db/lookupkey_internal_key_test_58.cc

#include "db/dbformat.h"
#include "util/slice.h"

#include <gtest/gtest.h>
#include <string>

using leveldb::LookupKey;
using leveldb::SequenceNumber;
using leveldb::Slice;

namespace {

// Small helpers that operate only on public Slice API
bool StartsWith(const Slice& s, const Slice& prefix) {
  if (prefix.size() > s.size()) return false;
  return std::memcmp(s.data(), prefix.data(), prefix.size()) == 0;
}

bool EndsWith(const Slice& s, const Slice& suffix) {
  if (suffix.size() > s.size()) return false;
  const size_t offset = s.size() - suffix.size();
  return std::memcmp(s.data() + offset, suffix.data(), suffix.size()) == 0;
}

class LookupKeyTest_58 : public ::testing::Test {};

}  // namespace

// Normal: internal_key() contains the user_key as a prefix,
// and its size is at least the user_key size.
TEST_F(LookupKeyTest_58, InternalKeyStartsWithUserKey_58) {
  const std::string uk = "user-key-abc";
  const SequenceNumber seq = 123u;

  LookupKey lk(Slice(uk), seq);

  Slice internal = lk.internal_key();
  Slice user = lk.user_key();

  ASSERT_TRUE(StartsWith(internal, user))
      << "internal_key should start with user_key";
  ASSERT_GE(internal.size(), user.size())
      << "internal_key size should be >= user_key size";
}

// Normal: memtable_key() should contain internal_key() contiguously.
// A minimally observable property (without parsing) is that
// memtable_key ends with internal_key and is not smaller than it.
TEST_F(LookupKeyTest_58, MemtableContainsInternalKeySuffix_58) {
  const std::string uk = "xyz";
  const SequenceNumber seq = 999u;

  LookupKey lk(Slice(uk), seq);

  Slice mem = lk.memtable_key();
  Slice internal = lk.internal_key();

  ASSERT_GE(mem.size(), internal.size())
      << "memtable_key should not be smaller than internal_key";
  ASSERT_TRUE(EndsWith(mem, internal))
      << "memtable_key should end with internal_key bytes";
}

// Variation: different sequence numbers for the same user key
// produce different internal_key() byte sequences (observable difference),
// while user_key() remains identical.
TEST_F(LookupKeyTest_58, DifferentSequenceYieldsDifferentInternalKey_58) {
  const std::string uk = "same-user-key";

  LookupKey a(Slice(uk), static_cast<SequenceNumber>(1));
  LookupKey b(Slice(uk), static_cast<SequenceNumber>(2));

  Slice internal_a = a.internal_key();
  Slice internal_b = b.internal_key();

  // User keys should match exactly.
  EXPECT_EQ(a.user_key().size(), b.user_key().size());
  EXPECT_EQ(0, std::memcmp(a.user_key().data(), b.user_key().data(), a.user_key().size()));

  // Internal keys should differ in content for different sequence numbers.
  // (We do not assume any specific encoding; we only assert observable inequality.)
  bool same_size = (internal_a.size() == internal_b.size());
  bool same_bytes = same_size &&
                    (std::memcmp(internal_a.data(), internal_b.data(), internal_a.size()) == 0);
  EXPECT_FALSE(same_bytes) << "internal_key should differ for different sequence numbers";
}

// Boundary: empty user key.
// We verify stable relationships only via public API without assuming encodings.
TEST_F(LookupKeyTest_58, EmptyUserKey_58) {
  const std::string uk;  // empty
  const SequenceNumber seq = 42u;

  LookupKey lk(Slice(uk), seq);

  Slice user = lk.user_key();
  Slice internal = lk.internal_key();
  Slice mem = lk.memtable_key();

  // internal_key should be at least as long as user_key (0),
  // and memtable_key should not be smaller than internal_key.
  EXPECT_EQ(user.size(), 0u);
  EXPECT_GE(internal.size(), user.size());
  EXPECT_GE(mem.size(), internal.size());
  EXPECT_TRUE(EndsWith(mem, internal));
  // StartsWith(internal, user) is trivially true for empty prefix.
  EXPECT_TRUE(StartsWith(internal, user));
}

// Boundary: large user key (stress size without relying on internals).
// We only assert the same public-interface relationships.
TEST_F(LookupKeyTest_58, LargeUserKey_58) {
  std::string uk(1000, 'A');  // large user key
  const SequenceNumber seq = 777u;

  LookupKey lk(Slice(uk), seq);

  Slice user = lk.user_key();
  Slice internal = lk.internal_key();
  Slice mem = lk.memtable_key();

  ASSERT_EQ(user.size(), uk.size());
  ASSERT_TRUE(StartsWith(internal, user));
  ASSERT_GE(internal.size(), user.size());
  ASSERT_GE(mem.size(), internal.size());
  ASSERT_TRUE(EndsWith(mem, internal));
}

// Sanity: repeated calls to internal_key() return the same slice view
// (address and size stable while the object is alive).
TEST_F(LookupKeyTest_58, InternalKeyViewIsStableAcrossCalls_58) {
  const std::string uk = "stable";
  const SequenceNumber seq = 555u;

  LookupKey lk(Slice(uk), seq);

  Slice a = lk.internal_key();
  Slice b = lk.internal_key();

  EXPECT_EQ(a.size(), b.size());
  // Compare the bytes directly for stability.
  ASSERT_EQ(0, std::memcmp(a.data(), b.data(), a.size()));
}
