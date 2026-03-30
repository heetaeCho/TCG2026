// File: internal_key_comparator_user_comparator_test.cc

#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

#include <gtest/gtest.h>

namespace {

// A simple external collaborator to pass into InternalKeyComparator.
// Implements the Comparator interface without relying on any internal state.
class DummyComparator final : public leveldb::Comparator {
 public:
  const char* Name() const override { return "DummyComparator"; }

  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {
    const std::string as = a.ToString();
    const std::string bs = b.ToString();
    if (as < bs) return -1;
    if (as > bs) return 1;
    return 0;
  }

  void FindShortestSeparator(std::string* start,
                             const leveldb::Slice& limit) const override {
    // No-op: sufficient for tests that only pass this as a dependency.
    (void)limit;
  }

  void FindShortSuccessor(std::string* key) const override {
    // No-op: sufficient for tests that only pass this as a dependency.
    (void)key;
  }
};

}  // namespace

// Fixture (kept minimal since we only verify the accessor behavior).
class InternalKeyComparatorTest_49 : public ::testing::Test {};

// [Normal] Returns the same pointer that was provided at construction.
TEST_F(InternalKeyComparatorTest_49, UserComparatorReturnsSameInstance_49) {
  DummyComparator user_cmp;
  leveldb::InternalKeyComparator ikc(&user_cmp);

  // Observable behavior: accessor should return the exact pointer passed in.
  EXPECT_EQ(&user_cmp, ikc.user_comparator());
}

// [Normal] Different instances passed to different comparators yield different pointers.
TEST_F(InternalKeyComparatorTest_49, UserComparatorDifferentInstances_49) {
  DummyComparator user_cmp_1;
  DummyComparator user_cmp_2;

  leveldb::InternalKeyComparator ikc1(&user_cmp_1);
  leveldb::InternalKeyComparator ikc2(&user_cmp_2);

  EXPECT_EQ(&user_cmp_1, ikc1.user_comparator());
  EXPECT_EQ(&user_cmp_2, ikc2.user_comparator());
  EXPECT_NE(ikc1.user_comparator(), ikc2.user_comparator());
}

// [Const-correctness] Access via const reference returns the same pointer.
TEST_F(InternalKeyComparatorTest_49, UserComparatorConstAccess_49) {
  DummyComparator user_cmp;
  leveldb::InternalKeyComparator ikc(&user_cmp);

  const leveldb::InternalKeyComparator& const_ref = ikc;
  EXPECT_EQ(&user_cmp, const_ref.user_comparator());
}
