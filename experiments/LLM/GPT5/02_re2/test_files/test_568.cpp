// File: onepass_addq_test_568.cc
#include <gtest/gtest.h>

// Include the container type and the function under test.
// AddQ is defined as 'static' in the TU, so we include the .cc directly.
#include "re2/sparse_set.h"
#include "re2/onepass.cc"

namespace {

using re2::SparseSet;

class AddQTest_568 : public ::testing::Test {
 protected:
  static constexpr int kCap = 64;
  AddQTest_568() : q_(kCap) {}
  SparseSet q_;
};

// Normal operation: inserting a non-zero id that isn't present.
TEST_F(AddQTest_568, InsertNonZero_NewId_InsertsAndReturnsTrue_568) {
  const int id = 5;
  ASSERT_FALSE(q_.contains(id));
  const int before = q_.size();

  EXPECT_TRUE(re2::AddQ(&q_, id));
  EXPECT_TRUE(q_.contains(id));
  EXPECT_EQ(before + 1, q_.size());
}

// Boundary: id == 0 should be a no-op that returns true.
TEST_F(AddQTest_568, InsertZeroId_NoInsert_ReturnsTrue_568) {
  const int before = q_.size();

  EXPECT_TRUE(re2::AddQ(&q_, 0));
  EXPECT_EQ(before, q_.size());
  EXPECT_FALSE(q_.contains(0));  // 0 should not have been inserted.
}

// Exceptional/duplicate observable case: adding an existing non-zero id.
TEST_F(AddQTest_568, InsertExistingId_ReturnsFalse_NoDuplicate_568) {
  const int id = 7;
  q_.insert(id);
  ASSERT_TRUE(q_.contains(id));
  const int before = q_.size();

  EXPECT_FALSE(re2::AddQ(&q_, id));
  EXPECT_TRUE(q_.contains(id));      // Still present
  EXPECT_EQ(before, q_.size());      // No duplicate inserted
}

// Normal operation with multiple unique ids: each should return true and be present.
TEST_F(AddQTest_568, InsertMultipleUniqueIds_AllTrue_AllPresent_568) {
  const int before = q_.size();

  EXPECT_TRUE(re2::AddQ(&q_, 1));
  EXPECT_TRUE(re2::AddQ(&q_, 2));
  EXPECT_TRUE(re2::AddQ(&q_, 3));

  EXPECT_TRUE(q_.contains(1));
  EXPECT_TRUE(q_.contains(2));
  EXPECT_TRUE(q_.contains(3));
  EXPECT_EQ(before + 3, q_.size());
}

// Boundary nuance: id == 0 returns true even if 0 was already inserted externally.
// Observable behavior: no size change (no duplicate insert via AddQ).
TEST_F(AddQTest_568, ZeroIdAlreadyPresent_ReturnsTrue_NoChange_568) {
  // Explicitly insert 0 through the public API (allowed by SparseSet capacity).
  q_.insert(0);
  ASSERT_TRUE(q_.contains(0));
  const int before = q_.size();

  EXPECT_TRUE(re2::AddQ(&q_, 0));    // Should NOT attempt to insert again
  EXPECT_TRUE(q_.contains(0));       // Still present
  EXPECT_EQ(before, q_.size());      // No change in size
}

}  // namespace
