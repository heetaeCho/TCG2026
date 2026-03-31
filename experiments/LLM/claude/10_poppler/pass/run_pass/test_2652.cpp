#include <gtest/gtest.h>

// Declare the function under test (defined in pdftoppm.cc)
static bool needToRotate(int angle) { return (angle == 90) || (angle == 270); }

// Test that angle 90 needs rotation
TEST(NeedToRotateTest_2652, Angle90ReturnsTrue_2652) {
    EXPECT_TRUE(needToRotate(90));
}

// Test that angle 270 needs rotation
TEST(NeedToRotateTest_2652, Angle270ReturnsTrue_2652) {
    EXPECT_TRUE(needToRotate(270));
}

// Test that angle 0 does not need rotation
TEST(NeedToRotateTest_2652, Angle0ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(0));
}

// Test that angle 180 does not need rotation
TEST(NeedToRotateTest_2652, Angle180ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(180));
}

// Test that angle 360 does not need rotation
TEST(NeedToRotateTest_2652, Angle360ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(360));
}

// Test that angle 45 does not need rotation
TEST(NeedToRotateTest_2652, Angle45ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(45));
}

// Test negative angle -90 does not need rotation (only positive 90 and 270 match)
TEST(NeedToRotateTest_2652, AngleNegative90ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(-90));
}

// Test negative angle -270 does not need rotation
TEST(NeedToRotateTest_2652, AngleNegative270ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(-270));
}

// Test that angle 1 does not need rotation
TEST(NeedToRotateTest_2652, Angle1ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(1));
}

// Test that angle 89 does not need rotation (boundary just below 90)
TEST(NeedToRotateTest_2652, Angle89ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(89));
}

// Test that angle 91 does not need rotation (boundary just above 90)
TEST(NeedToRotateTest_2652, Angle91ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(91));
}

// Test that angle 269 does not need rotation (boundary just below 270)
TEST(NeedToRotateTest_2652, Angle269ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(269));
}

// Test that angle 271 does not need rotation (boundary just above 270)
TEST(NeedToRotateTest_2652, Angle271ReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(271));
}

// Test large positive angle
TEST(NeedToRotateTest_2652, LargePositiveAngleReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(9999));
}

// Test large negative angle
TEST(NeedToRotateTest_2652, LargeNegativeAngleReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(-9999));
}

// Test INT_MAX boundary
TEST(NeedToRotateTest_2652, IntMaxReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(INT_MAX));
}

// Test INT_MIN boundary
TEST(NeedToRotateTest_2652, IntMinReturnsFalse_2652) {
    EXPECT_FALSE(needToRotate(INT_MIN));
}
