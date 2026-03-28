// File: re2_reverse_program_fanout_test_249.cc
#include <gtest/gtest.h>
#include <vector>
#include "re2/re2.h"

using re2::RE2;

class RE2ReverseProgramFanoutTest_249 : public ::testing::Test {};

// [Behavior] If the regex cannot be compiled (invalid), reverse program fanout is unavailable.
// Expect: returns -1.
TEST_F(RE2ReverseProgramFanoutTest_249, InvalidPatternReturnsMinusOne_249) {
  RE2 re("(");  // syntactically invalid regex
  std::vector<int> histogram;
  const int rc = re.ReverseProgramFanout(&histogram);
  EXPECT_EQ(rc, -1);
  // Histogram content is undefined in error cases; only assert we didn't crash.
}

// [Behavior] For a valid pattern, ReverseProgramFanout should succeed (non-negative),
// and any provided histogram should remain in a valid state (e.g., non-negative counts).
TEST_F(RE2ReverseProgramFanoutTest_249, ValidPatternProducesNonNegativeResultAndCounts_249) {
  RE2 re("(ab|cd)+e");
  std::vector<int> histogram;  // start empty
  const int rc = re.ReverseProgramFanout(&histogram);

  ASSERT_GE(rc, 0) << "Expected non-negative fanout for a valid compiled pattern.";

  // If the implementation chose to populate buckets, ensure no negative bucket counts appear.
  for (size_t i = 0; i < histogram.size(); ++i) {
    EXPECT_GE(histogram[i], 0) << "Bucket " << i << " should not be negative.";
  }
}

// [Behavior] Some fanout-style APIs allow a null histogram pointer to request only the count.
// Treating the class as a black box, verify that passing nullptr either succeeds with a
// non-negative return (if supported) or at least does not crash the program under a valid pattern.
TEST_F(RE2ReverseProgramFanoutTest_249, ValidPatternWithNullHistogramPointer_249) {
  RE2 re("a.*b");
  // Call with nullptr; black-box expectation is that it returns a non-negative number if supported.
  // (If the underlying implementation does not support nullptr, this test will surface that contract.)
  const int rc = re.ReverseProgramFanout(static_cast<std::vector<int>*>(nullptr));
  EXPECT_GE(rc, 0);
}

// [Behavior] Calling multiple times should be consistent for the same compiled pattern.
// We don't assume specific values; just that successive calls both succeed and keep histogram valid.
TEST_F(RE2ReverseProgramFanoutTest_249, IdempotentSuccessOnRepeatedCalls_249) {
  RE2 re("^(foo|bar)?baz$");
  std::vector<int> h1, h2;

  const int rc1 = re.ReverseProgramFanout(&h1);
  const int rc2 = re.ReverseProgramFanout(&h2);

  ASSERT_GE(rc1, 0);
  ASSERT_GE(rc2, 0);

  // Buckets, if present, must be non-negative.
  for (int v : h1) EXPECT_GE(v, 0);
  for (int v : h2) EXPECT_GE(v, 0);
}
