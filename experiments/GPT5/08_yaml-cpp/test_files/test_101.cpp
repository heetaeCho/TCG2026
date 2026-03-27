// File: streamcharsource_test_101.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

// yaml-cpp internal headers (paths as used in the project tree)
#include "stream.h"
#include "streamcharsource.h"

namespace {

class StreamCharSourceTest_101 : public ::testing::Test {
 protected:
  StreamCharSourceTest_101()
      : input("abcdef"),
        iss(input),
        stream(iss),
        source(stream) {}

  const std::string input;
  std::stringstream iss;
  YAML::Stream stream;
  YAML::StreamCharSource source;
};

TEST_F(StreamCharSourceTest_101, PlusZeroReturnsEquivalentView_101) {
  const auto s0 = source;
  const auto s1 = source + 0;

  // Adding 0 should not change the visible character sequence at the front.
  EXPECT_EQ(s1[0], s0[0]);
  EXPECT_EQ(s1[1], s0[1]);
}

TEST_F(StreamCharSourceTest_101, PlusPositiveShiftsForward_101) {
  const auto s0 = source;
  const auto s2 = source + 2;

  // After shifting by 2, the new "front" should match the old [2].
  EXPECT_EQ(s2[0], s0[2]);
  EXPECT_EQ(s2[1], s0[3]);
}

TEST_F(StreamCharSourceTest_101, OperatorPlusDoesNotModifyOriginal_101) {
  const char before0 = source[0];
  const char before1 = source[1];

  (void)(source + 3);  // returned object intentionally ignored

  // Original view should remain unchanged (operator+ returns a new object).
  EXPECT_EQ(source[0], before0);
  EXPECT_EQ(source[1], before1);
}

TEST_F(StreamCharSourceTest_101, PlusNegativeFromZeroClampsAtStart_101) {
  const auto s0 = source;
  const auto sNeg = source + (-5);

  // If negative movement would go before start, it should clamp to start.
  EXPECT_EQ(sNeg[0], s0[0]);
  EXPECT_EQ(sNeg[1], s0[1]);
}

TEST_F(StreamCharSourceTest_101, PlusNegativeFromNonZeroMovesBackButNotPastStart_101) {
  const auto s3 = source + 3;
  const auto s1_via_back = s3 + (-2);
  const auto s1_direct = source + 1;

  // Moving back from a non-zero offset should match direct offset.
  EXPECT_EQ(s1_via_back[0], s1_direct[0]);
  EXPECT_EQ(s1_via_back[1], s1_direct[1]);

  // And it must never move before the start if over-decremented.
  const auto sClamped = s1_direct + (-1000);
  EXPECT_EQ(sClamped[0], source[0]);
  EXPECT_EQ(sClamped[1], source[1]);
}

TEST_F(StreamCharSourceTest_101, PlusBeyondEndBecomesInvalidOrFalsey_101) {
  // Shift well past the end of "abcdef".
  const auto sFar = source + 1000;

  // Observable error/exceptional behavior through the interface:
  // Most yaml-cpp stream sources become "false" / "!" once past end.
  // We accept either representation, but it must be observable as not-valid.
  const bool as_bool = static_cast<bool>(sFar);
  const bool as_not = static_cast<bool>(!sFar);
  EXPECT_TRUE(!as_bool || as_not);

  // Also check that repeated shifting stays falsey (no resurrection).
  const auto sFarther = sFar + 10;
  const bool as_bool2 = static_cast<bool>(sFarther);
  const bool as_not2 = static_cast<bool>(!sFarther);
  EXPECT_TRUE(!as_bool2 || as_not2);
}

TEST_F(StreamCharSourceTest_101, ChainedPlusMatchesSinglePlus_101) {
  const auto s_chain = (source + 1) + 2;
  const auto s_single = source + 3;

  // Chaining should be equivalent to the combined shift.
  EXPECT_EQ(s_chain[0], s_single[0]);
  EXPECT_EQ(s_chain[1], s_single[1]);
}

}  // namespace
