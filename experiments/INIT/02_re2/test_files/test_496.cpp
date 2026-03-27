// File: ./TestProjects/re2/tests/repetition_walker_previsit_test_496.cc

#include "gtest/gtest.h"
#include "re2/regexp.h"

// Pull in the RepetitionWalker definition used by the build.
#include "re2/parse.cc"

namespace {

class RepetitionWalkerTest_496 : public ::testing::Test {
protected:
  using PF = re2::Regexp::ParseFlags;

  static PF NoFlags() {
    return static_cast<PF>(0);
  }

  static re2::Regexp* MakeLiteral() {
    return re2::Regexp::NewLiteral('x', NoFlags());
  }

  static re2::Regexp* MakeRepeat(int min, int max) {
    re2::Regexp* sub = MakeLiteral();
    // Treating implementation as a black box: use the public factory.
    re2::Regexp* rep = re2::Regexp::Repeat(sub, NoFlags(), min, max);
    return rep;
  }
};

// Normal operation: repeat with finite max divides parent_arg by max.
TEST_F(RepetitionWalkerTest_496, RepeatWithFiniteMax_DividesParentArg_496) {
  re2::RepetitionWalker w;
  bool stop = false;

  re2::Regexp* re = MakeRepeat(2, 5);  // finite max = 5
  ASSERT_NE(re, nullptr);

  int result = w.PreVisit(re, /*parent_arg=*/100, &stop);
  EXPECT_EQ(result, 20);  // 100 / 5

  re->Decref();
}

// Normal operation: repeat with "infinite" max (negative) uses min.
TEST_F(RepetitionWalkerTest_496, RepeatWithInfiniteMax_UsesMin_496) {
  re2::RepetitionWalker w;
  bool stop = false;

  re2::Regexp* re = MakeRepeat(3, -1);  // max < 0 => use min (=3)
  ASSERT_NE(re, nullptr);

  int result = w.PreVisit(re, /*parent_arg=*/100, &stop);
  EXPECT_EQ(result, 33);  // integer division: 100 / 3 => 33

  re->Decref();
}

// Boundary: max == 0 -> no division (returns parent_arg unchanged).
TEST_F(RepetitionWalkerTest_496, RepeatWithZeroMax_NoDivision_496) {
  re2::RepetitionWalker w;
  bool stop = false;

  re2::Regexp* re = MakeRepeat(0, 0);
  ASSERT_NE(re, nullptr);

  int result = w.PreVisit(re, /*parent_arg=*/100, &stop);
  EXPECT_EQ(result, 100);

  re->Decref();
}

// Boundary: max < 0 but min == 0 -> no division (m = min = 0, not > 0).
TEST_F(RepetitionWalkerTest_496, RepeatWithInfiniteMaxAndZeroMin_NoDivision_496) {
  re2::RepetitionWalker w;
  bool stop = false;

  re2::Regexp* re = MakeRepeat(0, -1);
  ASSERT_NE(re, nullptr);

  int result = w.PreVisit(re, /*parent_arg=*/100, &stop);
  EXPECT_EQ(result, 100);

  re->Decref();
}

// Boundary: finite max greater than parent_arg -> integer division yields 0.
TEST_F(RepetitionWalkerTest_496, RepeatWithFiniteMaxGreaterThanParentArg_YieldsZero_496) {
  re2::RepetitionWalker w;
  bool stop = false;

  re2::Regexp* re = MakeRepeat(1, 5);  // use max = 5
  ASSERT_NE(re, nullptr);

  int result = w.PreVisit(re, /*parent_arg=*/3, &stop);
  EXPECT_EQ(result, 0);  // 3 / 5 -> 0 with integer division

  re->Decref();
}

// Non-repeat op: returns parent_arg unchanged.
TEST_F(RepetitionWalkerTest_496, NonRepeatOp_ReturnsParentArgUnchanged_496) {
  re2::RepetitionWalker w;
  bool stop = false;

  re2::Regexp* lit = MakeLiteral();  // op != kRegexpRepeat
  ASSERT_NE(lit, nullptr);

  int result = w.PreVisit(lit, /*parent_arg=*/123, &stop);
  EXPECT_EQ(result, 123);

  lit->Decref();
}

}  // namespace
