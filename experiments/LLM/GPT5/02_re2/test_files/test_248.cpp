// File: re2_programfanout_test_248.cc
#include <gtest/gtest.h>
#include <vector>
#include "re2/re2.h"

using re2::RE2;

class RE2_ProgramFanoutTest_248 : public ::testing::Test {};

// [Normal] Valid pattern should return a non-negative value and (observably) work with a non-null histogram.
TEST_F(RE2_ProgramFanoutTest_248, ValidPatternReturnsNonNegativeAndFillsHistogram_248) {
  RE2 re("a");  // Construct with a simple, valid pattern.
  ASSERT_TRUE(re.ok()) << "Precondition: valid pattern should construct successfully.";

  std::vector<int> hist;
  const int fanout = re.ProgramFanout(&hist);

  EXPECT_GE(fanout, 0);
  // We don't assert specific contents; just that the function provided observable output.
  // It's reasonable to expect at least one bucket for a compiled program.
  EXPECT_FALSE(hist.empty());
}

// [Exceptional/Error] Invalid pattern should not have a compiled program; expect -1.
// Also verifies it doesn't crash when a histogram vector is provided.
TEST_F(RE2_ProgramFanoutTest_248, InvalidPatternReturnsMinusOne_248) {
  RE2 re("(");  // Unbalanced parenthesis -> invalid regex.
  ASSERT_FALSE(re.ok()) << "Precondition: invalid pattern should fail to compile.";

  std::vector<int> hist;
  const int fanout = re.ProgramFanout(&hist);

  EXPECT_EQ(fanout, -1);
}

// [Boundary/Interaction] When there's no compiled program (invalid pattern),
// the function should not mutate the caller-provided histogram (since the fast-path returns -1).
TEST_F(RE2_ProgramFanoutTest_248, NoProgramDoesNotModifyProvidedHistogram_248) {
  RE2 re("(");  // Force construction failure.
  ASSERT_FALSE(re.ok());

  std::vector<int> hist = {42, 99, 7};  // Sentinel contents to detect mutation.
  const std::vector<int> before = hist;

  const int fanout = re.ProgramFanout(&hist);
  EXPECT_EQ(fanout, -1);
  EXPECT_EQ(hist, before) << "Histogram should remain unchanged when no program exists.";
}
