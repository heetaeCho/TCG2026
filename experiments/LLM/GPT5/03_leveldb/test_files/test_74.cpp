// File: version_set_last_sequence_test_74.cc

#include "db/version_set.h"
#include "db/dbformat.h"       // InternalKeyComparator
#include "util/comparator.h"   // BytewiseComparator
#include "gtest/gtest.h"

#include <limits>

namespace leveldb {

class VersionSetTest_74 : public ::testing::Test {
protected:
  Options options_;
  InternalKeyComparator* icmp_{nullptr};

  void SetUp() override {
    // For these tests, we don't need a working Env or TableCache.
    // We pass nullptr for TableCache and leave options_.env as-is.
    // InternalKeyComparator requires a user comparator; use the standard one.
    static InternalKeyComparator kIcmp(BytewiseComparator());
    icmp_ = &kIcmp;
  }

  VersionSet MakeVS() {
    // TableCache is not exercised by these tests; pass nullptr.
    return VersionSet("testdb", &options_, /*table_cache=*/nullptr, icmp_);
  }
};

// Verifies the observable default state via the public getter.
TEST_F(VersionSetTest_74, DefaultLastSequenceIsZero_74) {
  VersionSet vs = MakeVS();
  EXPECT_EQ(vs.LastSequence(), 0u);
}

// Setting to zero and reading back should work.
TEST_F(VersionSetTest_74, SetAndGetZero_74) {
  VersionSet vs = MakeVS();
  vs.SetLastSequence(0);
  EXPECT_EQ(vs.LastSequence(), 0u);
}

// Setting to a typical non-zero value should be observable through the getter.
TEST_F(VersionSetTest_74, SetAndGetNonZero_74) {
  VersionSet vs = MakeVS();
  const uint64_t kValue = 123456789ull;
  vs.SetLastSequence(kValue);
  EXPECT_EQ(vs.LastSequence(), kValue);
}

// Boundary: maximum uint64_t value should round-trip.
TEST_F(VersionSetTest_74, SetAndGetMaxUint64_74) {
  VersionSet vs = MakeVS();
  const uint64_t kMax = std::numeric_limits<uint64_t>::max();
  vs.SetLastSequence(kMax);
  EXPECT_EQ(vs.LastSequence(), kMax);
}

// Overwriting the value should reflect the latest write via the getter.
TEST_F(VersionSetTest_74, OverwriteLastSequence_74) {
  VersionSet vs = MakeVS();
  vs.SetLastSequence(1);
  EXPECT_EQ(vs.LastSequence(), 1u);
  vs.SetLastSequence(42);
  EXPECT_EQ(vs.LastSequence(), 42u);
}

// Calling the getter repeatedly should not change the value (idempotency).
TEST_F(VersionSetTest_74, GetterIsIdempotent_74) {
  VersionSet vs = MakeVS();
  const uint64_t kValue = 777ull;
  vs.SetLastSequence(kValue);

  const uint64_t first = vs.LastSequence();
  const uint64_t second = vs.LastSequence();
  const uint64_t third = vs.LastSequence();

  EXPECT_EQ(first, kValue);
  EXPECT_EQ(second, kValue);
  EXPECT_EQ(third, kValue);
}

}  // namespace leveldb
