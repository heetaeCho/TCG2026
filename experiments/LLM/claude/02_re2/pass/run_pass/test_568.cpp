#include "gtest/gtest.h"
#include "re2/sparse_set.h"

// We need to access the AddQ function from the re2 namespace.
// Since it's a static function in onepass.cc, we need to either include the file
// or redeclare/test it indirectly. However, since AddQ is static, it's only
// visible within its translation unit. We'll need to test it by including the
// source file or by creating a test helper.

// Since AddQ is a static function in onepass.cc, we include it to get access.
// This is a common technique for testing static (file-scope) functions.

typedef re2::SparseSet Instq;

namespace re2 {
// Forward declare the static function - we need to access it for testing.
// Since it's static, we include the source to bring it into scope.
static bool AddQ(Instq *q, int id);
}

// Include the implementation file to get the static function
#include "re2/onepass.cc"

namespace {

class AddQTest_568 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that adding id 0 always returns true without modifying the set
TEST_F(AddQTest_568, AddZeroReturnsTrue_568) {
  Instq q(10);
  q.clear();
  EXPECT_TRUE(re2::AddQ(&q, 0));
  // id 0 should not be inserted into the set
  EXPECT_FALSE(q.contains(0));
  EXPECT_EQ(q.size(), 0);
}

// Test that adding a valid id to an empty set returns true
TEST_F(AddQTest_568, AddValidIdToEmptySet_568) {
  Instq q(10);
  q.clear();
  EXPECT_TRUE(re2::AddQ(&q, 1));
  EXPECT_TRUE(q.contains(1));
  EXPECT_EQ(q.size(), 1);
}

// Test that adding a duplicate id returns false
TEST_F(AddQTest_568, AddDuplicateIdReturnsFalse_568) {
  Instq q(10);
  q.clear();
  EXPECT_TRUE(re2::AddQ(&q, 5));
  EXPECT_FALSE(re2::AddQ(&q, 5));
  EXPECT_EQ(q.size(), 1);
}

// Test adding multiple distinct ids
TEST_F(AddQTest_568, AddMultipleDistinctIds_568) {
  Instq q(10);
  q.clear();
  EXPECT_TRUE(re2::AddQ(&q, 1));
  EXPECT_TRUE(re2::AddQ(&q, 2));
  EXPECT_TRUE(re2::AddQ(&q, 3));
  EXPECT_EQ(q.size(), 3);
  EXPECT_TRUE(q.contains(1));
  EXPECT_TRUE(q.contains(2));
  EXPECT_TRUE(q.contains(3));
}

// Test that adding id 0 multiple times always returns true and doesn't insert
TEST_F(AddQTest_568, AddZeroMultipleTimes_568) {
  Instq q(10);
  q.clear();
  EXPECT_TRUE(re2::AddQ(&q, 0));
  EXPECT_TRUE(re2::AddQ(&q, 0));
  EXPECT_TRUE(re2::AddQ(&q, 0));
  EXPECT_EQ(q.size(), 0);
}

// Test adding id 0 mixed with other ids
TEST_F(AddQTest_568, AddZeroMixedWithOtherIds_568) {
  Instq q(10);
  q.clear();
  EXPECT_TRUE(re2::AddQ(&q, 0));
  EXPECT_TRUE(re2::AddQ(&q, 1));
  EXPECT_TRUE(re2::AddQ(&q, 0));
  EXPECT_TRUE(re2::AddQ(&q, 2));
  EXPECT_EQ(q.size(), 2);
  EXPECT_FALSE(q.contains(0));
  EXPECT_TRUE(q.contains(1));
  EXPECT_TRUE(q.contains(2));
}

// Test adding an id at the boundary of max_size
TEST_F(AddQTest_568, AddIdAtMaxSizeBoundary_568) {
  Instq q(100);
  q.clear();
  EXPECT_TRUE(re2::AddQ(&q, 99));
  EXPECT_TRUE(q.contains(99));
  EXPECT_EQ(q.size(), 1);
}

// Test adding id 1 (smallest valid non-zero id)
TEST_F(AddQTest_568, AddSmallestValidId_568) {
  Instq q(10);
  q.clear();
  EXPECT_TRUE(re2::AddQ(&q, 1));
  EXPECT_TRUE(q.contains(1));
}

// Test adding and then trying duplicate for multiple ids
TEST_F(AddQTest_568, AddAndDuplicateMultiple_568) {
  Instq q(20);
  q.clear();
  for (int i = 1; i < 10; i++) {
    EXPECT_TRUE(re2::AddQ(&q, i));
  }
  EXPECT_EQ(q.size(), 9);
  for (int i = 1; i < 10; i++) {
    EXPECT_FALSE(re2::AddQ(&q, i));
  }
  EXPECT_EQ(q.size(), 9);
}

// Test that the set correctly reflects all additions
TEST_F(AddQTest_568, VerifyContainsAfterMultipleAdds_568) {
  Instq q(50);
  q.clear();
  re2::AddQ(&q, 5);
  re2::AddQ(&q, 10);
  re2::AddQ(&q, 15);
  re2::AddQ(&q, 20);
  
  EXPECT_TRUE(q.contains(5));
  EXPECT_TRUE(q.contains(10));
  EXPECT_TRUE(q.contains(15));
  EXPECT_TRUE(q.contains(20));
  EXPECT_FALSE(q.contains(1));
  EXPECT_FALSE(q.contains(25));
}

}  // namespace
