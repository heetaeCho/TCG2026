// File: dfa_workq_size_test_445.cc

#include <gtest/gtest.h>

// We rely on the provided interface in the project.
// Including the implementation unit here to access the public API
// presented in the prompt. If there is a header, prefer including that instead.
#include "re2/dfa.cc"

namespace re2 {

using ::testing::Test;

// Simple sanity checks for size() based on observable behavior.

// TEST_ID: 445
TEST(WorkqSizeTest_445, Size_ReturnsSumForTypicalInputs_445) {
  // Arrange
  DFA::Workq w(3, 2);  // interface shows ctor Workq(int n, int maxmark)

  // Act
  int sz = w.size();

  // Assert
  EXPECT_EQ(sz, 3 + 2);
}

// TEST_ID: 445
TEST(WorkqSizeTest_445, Size_ZeroBoth_445) {
  DFA::Workq w(0, 0);
  EXPECT_EQ(w.size(), 0);
}

// TEST_ID: 445
TEST(WorkqSizeTest_445, Size_ZeroN_NonZeroMaxmark_445) {
  DFA::Workq w(0, 5);
  EXPECT_EQ(w.size(), 5);
}

// TEST_ID: 445
TEST(WorkqSizeTest_445, Size_NonZeroN_ZeroMaxmark_445) {
  DFA::Workq w(7, 0);
  EXPECT_EQ(w.size(), 7);
}

// TEST_ID: 445
TEST(WorkqSizeTest_445, Size_LargeButSafeValues_445) {
  // Use values well within int range to avoid overflow in the test itself.
  const int n = 1'000'000;
  const int maxmark = 2'000'000;
  DFA::Workq w(n, maxmark);
  EXPECT_EQ(w.size(), n + maxmark);
}

// TEST_ID: 445
TEST(WorkqSizeTest_445, Size_IsIndependentOfOperations_445) {
  // This test exercises other *public* methods only to verify that calling
  // them does not change the observable return value of size().
  // We do not assert anything about their internal effects.
  DFA::Workq w(10, 4);

  // Baseline
  const int expected = 10 + 4;
  EXPECT_EQ(w.size(), expected);

  // Call other public methods with safe inputs (interface-based only).
  // We intentionally do not depend on any undocumented side effects.
  w.clear();              // should not affect size() contract
  w.mark();               // add a mark (per interface name)
  w.insert(0);            // insert a valid id within [0, n)
  w.insert_new(1);        // insert_new with another valid id
  (void)w.is_mark(0);     // just invoke to ensure no crashes
  (void)w.maxmark();      // query maxmark; no assertions about its value here

  // size() should remain based solely on constructor parameters.
  EXPECT_EQ(w.size(), expected);
}

}  // namespace re2
