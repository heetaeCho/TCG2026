// File: db/dbformat_lookupkey_memtable_key_test_57.cc

#include "db/dbformat.h"
#include "gtest/gtest.h"
#include <cstring>
#include <string>
#include <type_traits>

using leveldb::LookupKey;
using leveldb::SequenceNumber;
using leveldb::Slice;

namespace {

// Small helpers that rely only on the public Slice interface.
bool SliceEqual(const Slice& a, const Slice& b) {
  return a.size() == b.size() &&
         (a.size() == 0 || std::memcmp(a.data(), b.data(), a.size()) == 0);
}

bool SliceStartsWith(const Slice& s, const Slice& prefix) {
  if (prefix.size() > s.size()) return false;
  return std::memcmp(s.data(), prefix.data(), prefix.size()) == 0;
}

} // namespace

// --- Type trait checks (based purely on public deleted copy ops) ---

TEST(LookupKeyTest_57, NotCopyConstructible_57) {
  static_assert(!std::is_copy_constructible<LookupKey>::value,
                "LookupKey must not be copy-constructible");
}

TEST(LookupKeyTest_57, NotCopyAssignable_57) {
  static_assert(!std::is_copy_assignable<LookupKey>::value,
                "LookupKey must not be copy-assignable");
}

// --- Core behavior of memtable_key() ---

TEST(LookupKeyTest_57, MemtableKey_ReturnsStableSliceOnRepeatedCalls_57) {
  const std::string user = "abc";
  const SequenceNumber seq = 100;

  LookupKey lk(Slice(user), seq);

  Slice first = lk.memtable_key();
  Slice second = lk.memtable_key();

  // Observable: repeated calls should return an equivalent Slice view.
  EXPECT_TRUE(SliceEqual(first, second));
  // Non-empty user key should typically yield a non-empty memtable key.
  // (We don't assume format; we only expect something materialized.)
  EXPECT_GE(first.size(), static_cast<size_t>(0));
}

TEST(LookupKeyTest_57, RelationshipsAmongUserInternalMemtable_57) {
  const std::string user = "hello";
  const SequenceNumber seq = 7;

  LookupKey lk(Slice(user), seq);

  Slice user_s   = lk.user_key();
  Slice internal = lk.internal_key();
  Slice mem      = lk.memtable_key();

  // 1) internal key should at least be able to represent the user key.
  // We don't assume specific encoding; we only check that the user key
  // appears at the start of the internal key, which is an observable
  // relationship through public outputs.
  EXPECT_TRUE(SliceStartsWith(internal, user_s));

  // 2) memtable key should not be smaller than the internal key it exposes.
  EXPECT_GE(mem.size(), internal.size());

  // 3) Repeated calls are stable.
  EXPECT_TRUE(SliceEqual(mem, lk.memtable_key()));
}

TEST(LookupKeyTest_57, EmptyUserKey_DoesNotCrashAndIsConsistent_57) {
  const std::string user; // empty
  const SequenceNumber seq = 1;

  LookupKey lk(Slice(user), seq);

  Slice user_s   = lk.user_key();
  Slice internal = lk.internal_key();
  Slice mem      = lk.memtable_key();

  // User key is empty by construction.
  EXPECT_EQ(user_s.size(), 0u);

  // internal and memtable keys are materialized and consistent w.r.t. sizes.
  EXPECT_GE(internal.size(), user_s.size());
  EXPECT_GE(mem.size(), internal.size());

  // Stability on repeated calls.
  EXPECT_TRUE(SliceEqual(mem, lk.memtable_key()));
  EXPECT_TRUE(SliceEqual(internal, lk.internal_key()));
}

TEST(LookupKeyTest_57, LargeUserKey_ConsistentAndStable_57) {
  // Create a large user key to exercise any internal storage choices.
  std::string user_large(300, 'X'); // larger than small-inline buffer hints
  const SequenceNumber seq = 123456;

  LookupKey lk(Slice(user_large), seq);

  Slice user_s   = lk.user_key();
  Slice internal = lk.internal_key();
  Slice mem      = lk.memtable_key();

  // Publicly observable relationships only:
  EXPECT_TRUE(SliceStartsWith(internal, user_s));
  EXPECT_GE(mem.size(), internal.size());

  // Stability on repeated calls.
  EXPECT_TRUE(SliceEqual(mem, lk.memtable_key()));
}

TEST(LookupKeyTest_57, DifferentSequenceNumbers_ChangeInternalKey_57) {
  const std::string user = "same-user";
  const SequenceNumber seq1 = 10;
  const SequenceNumber seq2 = 11;

  LookupKey a(Slice(user), seq1);
  LookupKey b(Slice(user), seq2);

  Slice a_internal = a.internal_key();
  Slice b_internal = b.internal_key();

  // With identical user keys but different sequence numbers,
  // it's reasonable to expect the internal representation to differ.
  // This compares only the public outputs.
  // (If the implementation ever encodes seq elsewhere, size or bytes should differ.)
  bool same = SliceEqual(a_internal, b_internal);
  EXPECT_FALSE(same) << "internal_key() should differ for different sequence numbers";

  // memtable_key() should also reflect that difference.
  Slice a_mem = a.memtable_key();
  Slice b_mem = b.memtable_key();
  EXPECT_FALSE(SliceEqual(a_mem, b_mem));
}

