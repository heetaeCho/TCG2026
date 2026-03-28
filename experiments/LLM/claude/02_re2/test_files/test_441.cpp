#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "gtest/gtest.h"

// Since Workq is a private nested class inside DFA (defined in dfa.cc),
// we need to include the implementation file to access it for testing.
// In practice, this would require a friend declaration or test helper.
// For this test, we include the cc file directly.
#include "re2/dfa.cc"

namespace re2 {

class WorkqTest_441 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test is_mark returns false for values less than n_
TEST_F(WorkqTest_441, IsMarkReturnsFalseForValuesLessThanN_441) {
  DFA::Workq wq(10, 5);
  EXPECT_FALSE(wq.is_mark(0));
  EXPECT_FALSE(wq.is_mark(5));
  EXPECT_FALSE(wq.is_mark(9));
}

// Test is_mark returns true for values equal to n_
TEST_F(WorkqTest_441, IsMarkReturnsTrueForValueEqualToN_441) {
  DFA::Workq wq(10, 5);
  EXPECT_TRUE(wq.is_mark(10));
}

// Test is_mark returns true for values greater than n_
TEST_F(WorkqTest_441, IsMarkReturnsTrueForValuesGreaterThanN_441) {
  DFA::Workq wq(10, 5);
  EXPECT_TRUE(wq.is_mark(11));
  EXPECT_TRUE(wq.is_mark(14));
  EXPECT_TRUE(wq.is_mark(100));
}

// Test is_mark boundary: n_ - 1 should return false
TEST_F(WorkqTest_441, IsMarkBoundaryJustBelowN_441) {
  DFA::Workq wq(10, 5);
  EXPECT_FALSE(wq.is_mark(9));
}

// Test with n_ = 0, every non-negative value should be a mark
TEST_F(WorkqTest_441, IsMarkWithNZero_441) {
  DFA::Workq wq(0, 5);
  EXPECT_TRUE(wq.is_mark(0));
  EXPECT_TRUE(wq.is_mark(1));
}

// Test with n_ = 1
TEST_F(WorkqTest_441, IsMarkWithNOne_441) {
  DFA::Workq wq(1, 5);
  EXPECT_FALSE(wq.is_mark(0));
  EXPECT_TRUE(wq.is_mark(1));
  EXPECT_TRUE(wq.is_mark(2));
}

// Test maxmark returns the correct value
TEST_F(WorkqTest_441, MaxmarkReturnsCorrectValue_441) {
  DFA::Workq wq(10, 5);
  EXPECT_EQ(wq.maxmark(), 5);
}

// Test maxmark with zero
TEST_F(WorkqTest_441, MaxmarkWithZero_441) {
  DFA::Workq wq(10, 0);
  EXPECT_EQ(wq.maxmark(), 0);
}

// Test clear resets size
TEST_F(WorkqTest_441, ClearResetsWorkq_441) {
  DFA::Workq wq(10, 5);
  wq.insert(3);
  wq.clear();
  EXPECT_EQ(wq.size(), 0);
}

// Test size after insert
TEST_F(WorkqTest_441, SizeAfterInsert_441) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(3);
  EXPECT_GE(wq.size(), 1);
}

// Test insert_new
TEST_F(WorkqTest_441, InsertNew_441) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert_new(3);
  EXPECT_GE(wq.size(), 1);
}

// Test mark increases size
TEST_F(WorkqTest_441, MarkIncreasesSize_441) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(1);
  int size_before = wq.size();
  wq.mark();
  EXPECT_GE(wq.size(), size_before);
}

// Test large n_ value for is_mark
TEST_F(WorkqTest_441, IsMarkLargeN_441) {
  DFA::Workq wq(1000, 10);
  EXPECT_FALSE(wq.is_mark(999));
  EXPECT_TRUE(wq.is_mark(1000));
  EXPECT_TRUE(wq.is_mark(1009));
}

}  // namespace re2
