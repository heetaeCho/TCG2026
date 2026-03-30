// after_file_test_132.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "db/version_edit.h"   // For FileMetaData
#include "db/dbformat.h"       // For InternalKey

// If AfterFile is not available via a header (it's 'static' in the .cc),
// include the implementation unit directly so the symbol is visible to the test.
// This is a common tactic to test TU-local helpers.
#include "db/version_set.cc"

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SaveArg;

namespace {

class MockComparator : public leveldb::Comparator {
public:
  // Only the Compare behavior is relevant/observable for AfterFile.
  MOCK_METHOD(int, Compare,
              (const leveldb::Slice& a, const leveldb::Slice& b),
              (override));
};

} // namespace

// TEST_ID: 132
TEST(AfterFileTest_132, NullUserKeyReturnsFalse_132) {
  MockComparator cmp;
  leveldb::FileMetaData f; // largest is default-constructed; we do not depend on internals.

  // When user_key is nullptr, Compare must not be called at all.
  EXPECT_CALL(cmp, Compare(_, _)).Times(0);

  const bool result = leveldb::AfterFile(&cmp, /*user_key=*/nullptr, &f);
  EXPECT_FALSE(result);
}

// TEST_ID: 132
TEST(AfterFileTest_132, ReturnsTrueWhenComparatorIsGreaterThanZero_132) {
  MockComparator cmp;
  leveldb::FileMetaData f;
  leveldb::Slice user_key("user");

  EXPECT_CALL(cmp, Compare(_, _)).WillOnce(Return(1));

  const bool result = leveldb::AfterFile(&cmp, &user_key, &f);
  EXPECT_TRUE(result);
}

// TEST_ID: 132
TEST(AfterFileTest_132, ReturnsFalseWhenComparatorIsZero_132) {
  MockComparator cmp;
  leveldb::FileMetaData f;
  leveldb::Slice user_key("same");

  EXPECT_CALL(cmp, Compare(_, _)).WillOnce(Return(0));

  const bool result = leveldb::AfterFile(&cmp, &user_key, &f);
  EXPECT_FALSE(result);
}

// TEST_ID: 132
TEST(AfterFileTest_132, ReturnsFalseWhenComparatorIsLessThanZero_132) {
  MockComparator cmp;
  leveldb::FileMetaData f;
  leveldb::Slice user_key("less");

  EXPECT_CALL(cmp, Compare(_, _)).WillOnce(Return(-5));

  const bool result = leveldb::AfterFile(&cmp, &user_key, &f);
  EXPECT_FALSE(result);
}

// TEST_ID: 132
TEST(AfterFileTest_132, PassesExpectedArgumentsToComparator_132) {
  MockComparator cmp;
  leveldb::FileMetaData f;
  leveldb::Slice user_key("arg-check");

  // Capture arguments passed to Compare to verify that:
  //  - first arg equals *user_key
  //  - second arg equals f.largest.user_key() as observed via its public accessor
  leveldb::Slice captured_a;
  leveldb::Slice captured_b;
  EXPECT_CALL(cmp, Compare(_, _))
      .WillOnce(DoAll(SaveArg<0>(&captured_a), SaveArg<1>(&captured_b), Return(0)));

  // Observe the current public largest.user_key() to compare later (no assumptions about internals).
  leveldb::Slice expected_b = f.largest.user_key();

  (void)leveldb::AfterFile(&cmp, &user_key, &f);

  // Verify first argument equals the provided user_key slice (by content).
  EXPECT_EQ(0, captured_a.compare(user_key));

  // Verify second argument equals the publicly observed largest.user_key() of f.
  EXPECT_EQ(0, captured_b.compare(expected_b));
}
