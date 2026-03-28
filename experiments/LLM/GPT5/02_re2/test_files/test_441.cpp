// File: dfa_workq_is_mark_test_441.cc

#include <gtest/gtest.h>
#include <limits>

// Include the interface under test.
// If your project exposes a header, prefer that header instead.
// Using the .cc here to match the path given in the prompt.
#include "re2/dfa.cc"

namespace re2 {

// We only exercise the public interface and observable return values.
// No assumptions are made about internal state beyond what the constructor
// parameters make observable through is_mark(i).

// Normal behavior: values < n are not marks; values >= n are marks.
TEST(WorkqTest_441, IsMark_NormalRange_441) {
  // Arrange
  DFA::Workq w(5, 3);  // n = 5 (threshold), maxmark arbitrary for this test

  // Act & Assert
  EXPECT_FALSE(w.is_mark(0));
  EXPECT_FALSE(w.is_mark(1));
  EXPECT_FALSE(w.is_mark(2));
  EXPECT_FALSE(w.is_mark(3));
  EXPECT_FALSE(w.is_mark(4));

  EXPECT_TRUE(w.is_mark(5));  // first index considered a "mark"
  EXPECT_TRUE(w.is_mark(6));
  EXPECT_TRUE(w.is_mark(7));
}

// Boundary behavior: just below and at the threshold n.
TEST(WorkqTest_441, IsMark_BoundaryAtN_441) {
  DFA::Workq w(10, 4);  // n = 10

  EXPECT_FALSE(w.is_mark(9));   // n - 1 -> not a mark
  EXPECT_TRUE(w.is_mark(10));   // n     -> mark
}

// Larger inputs at/above the threshold should still be treated as marks
// (purely per the public predicate's return value).
TEST(WorkqTest_441, IsMark_LargeInputs_441) {
  DFA::Workq w(3, 2);  // n = 3

  EXPECT_TRUE(w.is_mark(1000));
  EXPECT_TRUE(w.is_mark(std::numeric_limits<int>::max()));
}

// Exceptional-ish/edge inputs: negative values should not be marks
// (since n is non-negative and the predicate checks i >= n).
TEST(WorkqTest_441, IsMark_NegativeInputs_441) {
  DFA::Workq w(0, 1);  // n = 0

  // For n = 0, any i >= 0 is a mark; negative should not be.
  EXPECT_FALSE(w.is_mark(-1));
  EXPECT_FALSE(w.is_mark(std::numeric_limits<int>::min()));
  EXPECT_TRUE(w.is_mark(0));
}

// Sanity across different constructor parameters: changing n changes the
// threshold where is_mark flips from false to true.
TEST(WorkqTest_441, IsMark_RespectsConstructorThreshold_441) {
  DFA::Workq w_n0(0, 5);  // threshold n = 0
  EXPECT_TRUE(w_n0.is_mark(0));   // everything >= 0 is a mark
  EXPECT_FALSE(w_n0.is_mark(-1));

  DFA::Workq w_n1(1, 5);  // threshold n = 1
  EXPECT_FALSE(w_n1.is_mark(0));
  EXPECT_TRUE(w_n1.is_mark(1));

  DFA::Workq w_n7(7, 1);  // threshold n = 7
  EXPECT_FALSE(w_n7.is_mark(6));
  EXPECT_TRUE(w_n7.is_mark(7));
}

}  // namespace re2
