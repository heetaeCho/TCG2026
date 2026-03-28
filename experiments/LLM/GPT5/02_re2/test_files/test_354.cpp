// File: regexp_numcaptures_walker_test.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace re2 {

class NumCapturesWalkerTest_354 : public ::testing::Test {
 protected:
  // Helper: parse pattern -> return capture count. Treats Regexp as a black box.
  int Count(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, /*flags=*/0, &status);
    // Observable behavior check: successful parse should yield non-null Regexp*.
    // We do not assert on internal status details; just ensure we can proceed.
    EXPECT_NE(re, nullptr) << "Parse returned nullptr for pattern: " << pattern;
    if (!re) return -1;  // Make the test robust in case Parse fails.

    const int n = re->NumCaptures();
    re->Decref();  // Respect ownership per the public interface.
    return n;
  }
};

// Normal operation: plain text has zero captures.
TEST_F(NumCapturesWalkerTest_354, NoCapturesForPlainText_354) {
  EXPECT_EQ(Count("abc"), 0);
  EXPECT_EQ(Count(""), 0);              // empty pattern is allowed: no captures
  EXPECT_EQ(Count("a*b+c?"), 0);        // operators but no parentheses
}

// Normal operation: single simple capturing group.
TEST_F(NumCapturesWalkerTest_354, OneSimpleCapture_354) {
  EXPECT_EQ(Count("(abc)"), 1);
  EXPECT_EQ(Count("a(b)c"), 1);
  EXPECT_EQ(Count("(a)"), 1);
}

// Normal operation: multiple and nested capturing groups.
TEST_F(NumCapturesWalkerTest_354, NestedCaptures_354) {
  // ((a)(b(c))) -> captures: outer, (a), (b(c)), (c) => 4
  EXPECT_EQ(Count("((a)(b(c)))"), 4);
  // (a(b)c)(d(e(f))) -> (a(b)c), (b), (d(e(f))), (e(f)), (f) => 5
  EXPECT_EQ(Count("(a(b)c)(d(e(f)))"), 5);
}

// Boundary: many adjacent capturing groups.
TEST_F(NumCapturesWalkerTest_354, ManyAdjacentCaptures_354) {
  EXPECT_EQ(Count("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)"), 10);
}

// Boundary/behavioral: non-capturing groups should NOT increase the count.
TEST_F(NumCapturesWalkerTest_354, NonCapturingGroupsNotCounted_354) {
  EXPECT_EQ(Count("(?:abc)"), 0);
  EXPECT_EQ(Count("a(?:b)c"), 0);
  // Mixed capturing + non-capturing -> only capturing are counted.
  EXPECT_EQ(Count("(a)(?:b)(c)"), 2);
}

// Mixed constructs: alternation, repetition, etc., with captures.
TEST_F(NumCapturesWalkerTest_354, AlternationAndRepetitionWithCaptures_354) {
  EXPECT_EQ(Count("a(b|c)d"), 1);                 // alternation inside a capture
  EXPECT_EQ(Count("(ab)?(cd)+(?:ef)*(gh){2,3}"), 3);  // only (ab), (cd), (gh) count
}

// Error/robustness (observable): invalid patterns should not crash tests.
// We only check that if Parse fails (nullptr), helper returns -1; this keeps
// black-box behavior without asserting on internal error reporting.
TEST_F(NumCapturesWalkerTest_354, InvalidPatternDoesNotCrash_354) {
  // Unbalanced parentheses likely fail to parse.
  int result = Count("(");
  if (result != -1) {
    // If environment accepts it (impl-defined), it must have no captures counted here.
    EXPECT_GE(result, 0);
  }
}

}  // namespace re2
