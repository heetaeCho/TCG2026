#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "gtest/gtest.h"

// Since DFA::Workq is an internal class defined in dfa.cc, we need to
// include or access it. The test relies on the actual implementation file.
// We include the dfa.cc directly to access internal classes for testing.
#include "re2/dfa.cc"

namespace re2 {

class WorkqTest_442 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that maxmark returns the value passed to constructor
TEST_F(WorkqTest_442, MaxmarkReturnsConstructorValue_442) {
  DFA::Workq wq(10, 5);
  EXPECT_EQ(wq.maxmark(), 5);
}

TEST_F(WorkqTest_442, MaxmarkReturnsZero_442) {
  DFA::Workq wq(10, 0);
  EXPECT_EQ(wq.maxmark(), 0);
}

TEST_F(WorkqTest_442, MaxmarkReturnsOne_442) {
  DFA::Workq wq(10, 1);
  EXPECT_EQ(wq.maxmark(), 1);
}

// Test initial size after construction
TEST_F(WorkqTest_442, InitialSizeIsZero_442) {
  DFA::Workq wq(10, 5);
  EXPECT_EQ(wq.size(), 0);
}

// Test clear resets the queue
TEST_F(WorkqTest_442, ClearResetsSize_442) {
  DFA::Workq wq(10, 5);
  wq.insert(0);
  wq.insert(1);
  wq.clear();
  EXPECT_EQ(wq.size(), 0);
}

// Test insert increases size
TEST_F(WorkqTest_442, InsertIncreasesSize_442) {
  DFA::Workq wq(10, 5);
  wq.insert(0);
  EXPECT_GE(wq.size(), 1);
}

// Test insert_new increases size
TEST_F(WorkqTest_442, InsertNewIncreasesSize_442) {
  DFA::Workq wq(10, 5);
  wq.insert_new(0);
  EXPECT_GE(wq.size(), 1);
}

// Test mark functionality
TEST_F(WorkqTest_442, MarkIncreasesSize_442) {
  DFA::Workq wq(10, 5);
  wq.mark();
  // After a mark, size should reflect the mark entry
  EXPECT_GE(wq.size(), 1);
}

// Test is_mark with Mark constant
TEST_F(WorkqTest_442, IsMarkReturnsTrueForMark_442) {
  DFA::Workq wq(10, 5);
  EXPECT_TRUE(wq.is_mark(Mark));
}

// Test is_mark with non-mark values
TEST_F(WorkqTest_442, IsMarkReturnsFalseForNonMark_442) {
  DFA::Workq wq(10, 5);
  EXPECT_FALSE(wq.is_mark(0));
  EXPECT_FALSE(wq.is_mark(1));
  EXPECT_FALSE(wq.is_mark(5));
}

// Test inserting duplicate via insert doesn't increase size
TEST_F(WorkqTest_442, InsertDuplicateDoesNotIncreaseSize_442) {
  DFA::Workq wq(10, 5);
  wq.insert(3);
  int size_after_first = wq.size();
  wq.insert(3);
  EXPECT_EQ(wq.size(), size_after_first);
}

// Test inserting multiple different elements
TEST_F(WorkqTest_442, InsertMultipleElements_442) {
  DFA::Workq wq(10, 5);
  wq.insert(0);
  wq.insert(1);
  wq.insert(2);
  EXPECT_GE(wq.size(), 3);
}

// Test large n with maxmark
TEST_F(WorkqTest_442, LargeNAndMaxmark_442) {
  DFA::Workq wq(100, 50);
  EXPECT_EQ(wq.maxmark(), 50);
  EXPECT_EQ(wq.size(), 0);
}

// Test clear after mark
TEST_F(WorkqTest_442, ClearAfterMark_442) {
  DFA::Workq wq(10, 5);
  wq.insert(1);
  wq.mark();
  wq.insert(2);
  wq.clear();
  EXPECT_EQ(wq.size(), 0);
}

}  // namespace re2
