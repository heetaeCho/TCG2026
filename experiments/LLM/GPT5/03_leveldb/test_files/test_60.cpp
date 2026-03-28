// File: lookupkey_destructor_test_60.cc
#include "gtest/gtest.h"

#include "leveldb/dbformat.h"  // LookupKey
#include "leveldb/slice.h"     // Slice

using leveldb::LookupKey;
using leveldb::SequenceNumber;
using leveldb::Slice;

class LookupKeyTest_60 : public ::testing::Test {
protected:
  static SequenceNumber Seq() { return static_cast<SequenceNumber>(1); }
};

// Verifies that user_key() returns the original user key for a typical small key.
TEST_F(LookupKeyTest_60, UserKeyRoundTrip_Small_60) {
  const std::string input = "abc";
  LookupKey key(Slice(input), Seq());

  // Observable behavior via public API
  EXPECT_EQ(key.user_key().ToString(), input);
  // Other exposed slices should be available (non-empty) during lifetime.
  EXPECT_FALSE(key.internal_key().empty());
  EXPECT_FALSE(key.memtable_key().empty());
}

// Verifies behavior with an empty user key (boundary).
TEST_F(LookupKeyTest_60, UserKeyRoundTrip_Empty_60) {
  const std::string input;  // empty
  LookupKey key(Slice(input), Seq());

  EXPECT_EQ(key.user_key().ToString(), input);
  EXPECT_FALSE(key.internal_key().empty());
  EXPECT_FALSE(key.memtable_key().empty());
}

// Verifies behavior with a large user key (likely to exercise different storage paths internally).
TEST_F(LookupKeyTest_60, UserKeyRoundTrip_Large_60) {
  std::string input(4096, 'X');  // large input
  LookupKey key(Slice(input), Seq());

  EXPECT_EQ(key.user_key().ToString(), input);
  EXPECT_FALSE(key.internal_key().empty());
  EXPECT_FALSE(key.memtable_key().empty());
}

// Destructor safety test for small key: object goes out of scope without crashing.
TEST_F(LookupKeyTest_60, DestructorSafety_Small_60) {
  {
    const std::string input = "small";
    LookupKey key(Slice(input), Seq());
    // Access the slices to ensure they are realizable during lifetime.
    auto u = key.user_key();
    auto i = key.internal_key();
    auto m = key.memtable_key();
    EXPECT_FALSE(i.empty());
    EXPECT_FALSE(m.empty());
    EXPECT_EQ(u.ToString(), input);
  }
  SUCCEED() << "LookupKey with small key destroyed without error.";
}

// Destructor safety test for large key: object goes out of scope without crashing.
TEST_F(LookupKeyTest_60, DestructorSafety_Large_60) {
  {
    std::string input(1 << 15, 'Y');  // 32 KiB
    LookupKey key(Slice(input), Seq());
    auto u = key.user_key();
    auto i = key.internal_key();
    auto m = key.memtable_key();
    EXPECT_FALSE(i.empty());
    EXPECT_FALSE(m.empty());
    EXPECT_EQ(u.ToString(), input);
  }
  SUCCEED() << "LookupKey with large key destroyed without error.";
}

// Interface conformance: copy/assignment are deleted per the header.
TEST_F(LookupKeyTest_60, DeletedCopyAndAssign_60) {
  static_assert(!std::is_copy_constructible<LookupKey>::value,
                "LookupKey must not be copy-constructible");
  static_assert(!std::is_copy_assignable<LookupKey>::value,
                "LookupKey must not be copy-assignable");
  SUCCEED();
}
