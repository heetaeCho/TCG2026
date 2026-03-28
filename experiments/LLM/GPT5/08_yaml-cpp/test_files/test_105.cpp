// File: ./TestProjects/yaml-cpp/test/stringsource_operator_plus_test_105.cpp

#include <gtest/gtest.h>

#include "stringsource.h"

namespace {

class StringCharSourceTest_105 : public ::testing::Test {
protected:
  static YAML::StringCharSource Make(const char* s) {
    // Size is explicitly provided by the interface; keep test data simple.
    // "abcd" -> 4, "abc" -> 3, etc.
    return YAML::StringCharSource(s, std::char_traits<char>::length(s));
  }
};

TEST_F(StringCharSourceTest_105, PlusZeroReturnsEquivalentSource_105) {
  auto s = Make("abcd");
  auto s0 = s + 0;

  // Compare observable behavior without assuming internal representation.
  EXPECT_EQ(static_cast<bool>(s), static_cast<bool>(s0));
  EXPECT_EQ(!s, !s0);

  // Compare a few reads (safe because within known length).
  EXPECT_EQ(s[0], s0[0]);
  EXPECT_EQ(s[1], s0[1]);
  EXPECT_EQ(s[2], s0[2]);
  EXPECT_EQ(s[3], s0[3]);
}

TEST_F(StringCharSourceTest_105, PlusPositiveMatchesRepeatedPreIncrement_105) {
  auto s = Make("abcd");

  auto s_plus2 = s + 2;

  auto s_inc2 = s;
  ++s_inc2;
  ++s_inc2;

  EXPECT_EQ(static_cast<bool>(s_plus2), static_cast<bool>(s_inc2));
  EXPECT_EQ(!s_plus2, !s_inc2);

  // Compare reads relative to the resulting sources (avoid assuming meaning of offset).
  EXPECT_EQ(s_plus2[0], s_inc2[0]);
  EXPECT_EQ(s_plus2[1], s_inc2[1]);
}

TEST_F(StringCharSourceTest_105, PlusDoesNotMutateOriginalSource_105) {
  auto s = Make("abcd");
  (void)(s + 1);  // create a shifted copy, ignore it

  // Original should behave the same as it did initially.
  EXPECT_TRUE(static_cast<bool>(s));
  EXPECT_FALSE(!s);
  EXPECT_EQ(s[0], 'a');
  EXPECT_EQ(s[1], 'b');
}

TEST_F(StringCharSourceTest_105, PlusNegativeFromStartClampsToStart_105) {
  auto s = Make("abcd");
  auto s_neg = s + (-1);

  // If clamped, behavior should match the original start state.
  EXPECT_EQ(static_cast<bool>(s), static_cast<bool>(s_neg));
  EXPECT_EQ(!s, !s_neg);
  EXPECT_EQ(s[0], s_neg[0]);
  EXPECT_EQ(s[1], s_neg[1]);
}

TEST_F(StringCharSourceTest_105, PlusNegativeCanMoveBackButNotBeforeStart_105) {
  auto s = Make("abcd");

  // Move forward, then move back.
  auto s_fwd3 = s + 3;
  auto s_back2 = s_fwd3 + (-2);

  // Equivalent to moving forward by 1 from the original.
  auto s_fwd1 = s + 1;

  EXPECT_EQ(static_cast<bool>(s_back2), static_cast<bool>(s_fwd1));
  EXPECT_EQ(!s_back2, !s_fwd1);
  EXPECT_EQ(s_back2[0], s_fwd1[0]);
  EXPECT_EQ(s_back2[1], s_fwd1[1]);
}

TEST_F(StringCharSourceTest_105, PlusNegativePastStartFromNonZeroClampsToStart_105) {
  auto s = Make("abcd");

  auto s_fwd1 = s + 1;
  auto s_clamped = s_fwd1 + (-5);  // attempt to go before start

  // Should clamp to the same observable state as the original.
  EXPECT_EQ(static_cast<bool>(s_clamped), static_cast<bool>(s));
  EXPECT_EQ(!s_clamped, !s);
  EXPECT_EQ(s_clamped[0], s[0]);
  EXPECT_EQ(s_clamped[1], s[1]);
}

TEST_F(StringCharSourceTest_105, LargePositivePlusMatchesPlusEqualsInObservables_105) {
  auto s = Make("abcd");

  // Avoid indexing after large shifts; just compare observable boolean state.
  auto s_plus_big = s + 100;

  auto s_pluseq_big = s;
  s_pluseq_big += 100;

  EXPECT_EQ(static_cast<bool>(s_plus_big), static_cast<bool>(s_pluseq_big));
  EXPECT_EQ(!s_plus_big, !s_pluseq_big);
}

TEST_F(StringCharSourceTest_105, PlusSizeMatchesPlusEqualsSizeInObservables_105) {
  auto s = Make("abcd");

  auto s_plus_size = s + 4;  // exactly length
  auto s_pluseq_size = s;
  s_pluseq_size += 4;

  EXPECT_EQ(static_cast<bool>(s_plus_size), static_cast<bool>(s_pluseq_size));
  EXPECT_EQ(!s_plus_size, !s_pluseq_size);
}

}  // namespace
