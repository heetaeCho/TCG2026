#include "gtest/gtest.h"
#include "re2/dfa.cc"
#include "re2/sparse_set.h"

// Since Workq is a private inner class of DFA, and we need to test it,
// we need to access it. The class is defined in dfa.cc.
// We'll use a workaround by including the source file or using friend declarations.
// Given the constraints, we'll work with what's available.

// Since Workq is nested inside DFA and may be private, we need a way to instantiate it.
// Looking at the code, Workq inherits from SparseSet publicly.
// We'll try to access it via re2::DFA::Workq if possible.

// For testing purposes, we create a test fixture that can access the Workq class.
// If Workq is not directly accessible, we may need to use a helper or the actual
// DFA interface. Based on the partial code, Workq appears to be a public nested class
// within DFA (as shown in the code snippet).

namespace re2 {

class WorkqTest_443 : public ::testing::Test {
 protected:
  // Helper to create a Workq with given parameters
  // n = number of states, maxmark = max number of marks
};

// Test basic construction and initial state
TEST_F(WorkqTest_443, ConstructionBasic_443) {
  DFA::Workq wq(10, 5);
  // After construction, the workq should be empty (inherited from SparseSet behavior)
  // size() should return 0 after clear or initial state
  wq.clear();
  EXPECT_EQ(wq.size(), 0);
}

// Test clear resets the workq
TEST_F(WorkqTest_443, ClearResetsWorkq_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(3);
  EXPECT_GT(wq.size(), 0);
  wq.clear();
  EXPECT_EQ(wq.size(), 0);
}

// Test insert and size
TEST_F(WorkqTest_443, InsertIncreasesSize_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(0);
  EXPECT_EQ(wq.size(), 1);
  wq.insert(1);
  EXPECT_EQ(wq.size(), 2);
}

// Test insert_new
TEST_F(WorkqTest_443, InsertNew_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert_new(5);
  EXPECT_EQ(wq.size(), 1);
}

// Test is_mark identifies mark values correctly
TEST_F(WorkqTest_443, IsMarkReturnsTrueForMarkValues_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  // Values >= n_ are marks
  EXPECT_TRUE(wq.is_mark(10));
  EXPECT_TRUE(wq.is_mark(11));
  EXPECT_TRUE(wq.is_mark(14));
}

// Test is_mark returns false for non-mark values
TEST_F(WorkqTest_443, IsMarkReturnsFalseForNonMarkValues_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  EXPECT_FALSE(wq.is_mark(0));
  EXPECT_FALSE(wq.is_mark(5));
  EXPECT_FALSE(wq.is_mark(9));
}

// Test maxmark returns the correct value
TEST_F(WorkqTest_443, MaxmarkReturnsCorrectValue_443) {
  DFA::Workq wq(10, 5);
  EXPECT_EQ(wq.maxmark(), 5);
}

// Test maxmark with different value
TEST_F(WorkqTest_443, MaxmarkDifferentValue_443) {
  DFA::Workq wq(20, 10);
  EXPECT_EQ(wq.maxmark(), 10);
}

// Test mark inserts a mark separator
TEST_F(WorkqTest_443, MarkInsertsMarkSeparator_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(1);
  wq.mark();
  wq.insert(2);
  // After inserting elements and a mark, size should include the mark
  EXPECT_GE(wq.size(), 2);
}

// Test multiple marks
TEST_F(WorkqTest_443, MultipleMarks_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(0);
  wq.mark();
  wq.insert(1);
  wq.mark();
  wq.insert(2);
  EXPECT_GE(wq.size(), 3);
}

// Test clear after marks
TEST_F(WorkqTest_443, ClearAfterMarks_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(0);
  wq.mark();
  wq.insert(1);
  wq.clear();
  EXPECT_EQ(wq.size(), 0);
}

// Test duplicate insert (same id inserted twice)
TEST_F(WorkqTest_443, DuplicateInsert_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(3);
  int size_after_first = wq.size();
  wq.insert(3);
  // Duplicate insert should not increase size (SparseSet behavior)
  EXPECT_EQ(wq.size(), size_after_first);
}

// Test boundary: insert id = 0
TEST_F(WorkqTest_443, InsertZeroId_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(0);
  EXPECT_EQ(wq.size(), 1);
}

// Test boundary: insert id = n-1 (maximum valid non-mark id)
TEST_F(WorkqTest_443, InsertMaxNonMarkId_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.insert(9);
  EXPECT_EQ(wq.size(), 1);
  EXPECT_FALSE(wq.is_mark(9));
}

// Test construction with n=1, maxmark=1
TEST_F(WorkqTest_443, SmallConstruction_443) {
  DFA::Workq wq(1, 1);
  wq.clear();
  EXPECT_EQ(wq.maxmark(), 1);
  wq.insert(0);
  EXPECT_EQ(wq.size(), 1);
  EXPECT_FALSE(wq.is_mark(0));
  EXPECT_TRUE(wq.is_mark(1));
}

// Test mark followed by mark (consecutive marks)
TEST_F(WorkqTest_443, ConsecutiveMarks_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.mark();
  wq.mark();
  // Consecutive marks should still work without crashing
  EXPECT_GE(wq.size(), 0);
}

// Test size after clear is zero
TEST_F(WorkqTest_443, SizeAfterClearIsZero_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  EXPECT_EQ(wq.size(), 0);
}

// Test insert multiple distinct ids
TEST_F(WorkqTest_443, InsertMultipleDistinctIds_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  for (int i = 0; i < 10; i++) {
    wq.insert(i);
  }
  EXPECT_EQ(wq.size(), 10);
}

// Test mark then insert
TEST_F(WorkqTest_443, MarkThenInsert_443) {
  DFA::Workq wq(10, 5);
  wq.clear();
  wq.mark();
  wq.insert(5);
  EXPECT_GE(wq.size(), 1);
}

// Test is_mark boundary at exactly n
TEST_F(WorkqTest_443, IsMarkBoundaryAtN_443) {
  DFA::Workq wq(10, 5);
  EXPECT_FALSE(wq.is_mark(9));  // n-1 is not a mark
  EXPECT_TRUE(wq.is_mark(10));  // n is a mark
}

}  // namespace re2
