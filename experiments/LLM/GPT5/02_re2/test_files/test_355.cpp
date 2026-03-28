// File: num_captures_walker_shortvisit_test_355.cc

#include <climits>
#include "gtest/gtest.h"

// We only need the class/func signatures to call into the already-implemented code.
// The implementation lives in the production .cc; tests treat it as a black box.
namespace re2 {
class Regexp;                    // forward-declare; ShortVisit doesn't require full type
class NumCapturesWalker {
 public:
  using Ignored = int;
  virtual Ignored ShortVisit(Regexp* re, Ignored ignored);
  virtual ~NumCapturesWalker() = default;
};
}  // namespace re2

// Test fixture (name includes TEST_ID as requested)
class NumCapturesWalkerTest_355 : public ::testing::Test {};

// In non-fuzzing builds, ShortVisit logs DFATAL and should terminate.
// We verify this via a death test without asserting specific log contents.
#ifndef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
TEST_F(NumCapturesWalkerTest_355, ShortVisit_DFATALDeath_355) {
  re2::NumCapturesWalker w;
  // Pass a nullptr Regexp* since behavior under test does not require dereference.
  // Expect death due to DFATAL; don't rely on the exact log text.
  EXPECT_DEATH(
      {
        // The expression under test:
        (void)w.ShortVisit(/*re=*/nullptr, /*ignored=*/123);
      },
      ".*");
}
#else
// In fuzzing builds, DFATAL is disabled; ShortVisit should simply return the
// 'ignored' value unmodified. These tests assert that observable behavior.

TEST_F(NumCapturesWalkerTest_355, ShortVisit_ReturnsSameValue_Positive_355) {
  re2::NumCapturesWalker w;
  int in = 123;
  int out = w.ShortVisit(/*re=*/nullptr, in);
  EXPECT_EQ(out, in);
}

TEST_F(NumCapturesWalkerTest_355, ShortVisit_ReturnsSameValue_Zero_355) {
  re2::NumCapturesWalker w;
  int in = 0;
  int out = w.ShortVisit(/*re=*/nullptr, in);
  EXPECT_EQ(out, in);
}

TEST_F(NumCapturesWalkerTest_355, ShortVisit_ReturnsSameValue_Boundaries_355) {
  re2::NumCapturesWalker w;

  int in_min = INT_MIN;
  int out_min = w.ShortVisit(/*re=*/nullptr, in_min);
  EXPECT_EQ(out_min, in_min);

  int in_max = INT_MAX;
  int out_max = w.ShortVisit(/*re=*/nullptr, in_max);
  EXPECT_EQ(out_max, in_max);
}
#endif  // FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
