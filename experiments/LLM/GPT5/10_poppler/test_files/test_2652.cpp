// pdftoppm_needToRotate_test_2652.cc
#include <gtest/gtest.h>

// The production code declares this function as `static` inside pdftoppm.cc,
// so it has internal linkage and cannot be linked from a separate test TU.
// To test it as a black box without re-implementing logic, we include the
// .cc file directly to make the function visible within this translation unit.
#include "TestProjects/poppler/utils/pdftoppm.cc"

class NeedToRotateTest_2652 : public ::testing::Test {};

// Normal operation: angles that should require rotation.
TEST_F(NeedToRotateTest_2652, ReturnsTrueFor90_2652) {
  EXPECT_TRUE(needToRotate(90));
}

TEST_F(NeedToRotateTest_2652, ReturnsTrueFor270_2652) {
  EXPECT_TRUE(needToRotate(270));
}

// Normal operation: common angles that should not require rotation.
TEST_F(NeedToRotateTest_2652, ReturnsFalseFor0_2652) {
  EXPECT_FALSE(needToRotate(0));
}

TEST_F(NeedToRotateTest_2652, ReturnsFalseFor180_2652) {
  EXPECT_FALSE(needToRotate(180));
}

TEST_F(NeedToRotateTest_2652, ReturnsFalseFor360_2652) {
  EXPECT_FALSE(needToRotate(360));
}

// Boundary / edge-ish: nearby values should not trigger rotation.
TEST_F(NeedToRotateTest_2652, ReturnsFalseFor89_2652) {
  EXPECT_FALSE(needToRotate(89));
}

TEST_F(NeedToRotateTest_2652, ReturnsFalseFor91_2652) {
  EXPECT_FALSE(needToRotate(91));
}

TEST_F(NeedToRotateTest_2652, ReturnsFalseFor269_2652) {
  EXPECT_FALSE(needToRotate(269));
}

TEST_F(NeedToRotateTest_2652, ReturnsFalseFor271_2652) {
  EXPECT_FALSE(needToRotate(271));
}

// Error/exceptional: function takes int; verify it behaves (returns a bool)
// for unexpected inputs (no crash is the main observable behavior here).
TEST_F(NeedToRotateTest_2652, ReturnsFalseForNegativeAngles_2652) {
  EXPECT_FALSE(needToRotate(-90));
  EXPECT_FALSE(needToRotate(-270));
  EXPECT_FALSE(needToRotate(-1));
}

TEST_F(NeedToRotateTest_2652, ReturnsFalseForLargeAngles_2652) {
  EXPECT_FALSE(needToRotate(450));
  EXPECT_FALSE(needToRotate(630));
  EXPECT_FALSE(needToRotate(1000000));
}

TEST_F(NeedToRotateTest_2652, ReturnsFalseForIntLimits_2652) {
  EXPECT_FALSE(needToRotate(std::numeric_limits<int>::min()));
  EXPECT_FALSE(needToRotate(std::numeric_limits<int>::max()));
}