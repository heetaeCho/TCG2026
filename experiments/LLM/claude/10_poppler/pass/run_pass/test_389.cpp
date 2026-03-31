#include <gtest/gtest.h>

// Include necessary headers
#include "GfxState.h"

class ColToDblTest_389 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: converting gfxColorComp1 should yield 1.0
TEST_F(ColToDblTest_389, MaxValueYieldsOne_389) {
    GfxColorComp maxVal = gfxColorComp1;
    double result = colToDbl(maxVal);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test normal operation: converting 0 should yield 0.0
TEST_F(ColToDblTest_389, ZeroValueYieldsZero_389) {
    GfxColorComp zeroVal = 0;
    double result = colToDbl(zeroVal);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test normal operation: converting half of gfxColorComp1 should yield ~0.5
TEST_F(ColToDblTest_389, HalfValueYieldsHalf_389) {
    GfxColorComp halfVal = gfxColorComp1 / 2;
    double result = colToDbl(halfVal);
    EXPECT_NEAR(result, 0.5, 1e-5);
}

// Test normal operation: converting a quarter of gfxColorComp1
TEST_F(ColToDblTest_389, QuarterValueYieldsQuarter_389) {
    GfxColorComp quarterVal = gfxColorComp1 / 4;
    double result = colToDbl(quarterVal);
    EXPECT_NEAR(result, 0.25, 1e-5);
}

// Test boundary: converting value 1
TEST_F(ColToDblTest_389, ValueOneYieldsSmallFraction_389) {
    GfxColorComp oneVal = 1;
    double result = colToDbl(oneVal);
    double expected = 1.0 / (double)gfxColorComp1;
    EXPECT_DOUBLE_EQ(result, expected);
}

// Test boundary: converting gfxColorComp1 - 1 should yield close to 1.0 but not exactly 1.0
TEST_F(ColToDblTest_389, MaxMinusOneYieldsNearOne_389) {
    GfxColorComp almostMax = gfxColorComp1 - 1;
    double result = colToDbl(almostMax);
    double expected = (double)(gfxColorComp1 - 1) / (double)gfxColorComp1;
    EXPECT_DOUBLE_EQ(result, expected);
    EXPECT_LT(result, 1.0);
}

// Test negative value (if GfxColorComp is signed)
TEST_F(ColToDblTest_389, NegativeValueYieldsNegativeResult_389) {
    GfxColorComp negVal = -gfxColorComp1;
    double result = colToDbl(negVal);
    EXPECT_DOUBLE_EQ(result, -1.0);
}

// Test that the result is proportional: double the input yields double the output
TEST_F(ColToDblTest_389, ProportionalScaling_389) {
    GfxColorComp val1 = gfxColorComp1 / 8;
    GfxColorComp val2 = gfxColorComp1 / 4;
    double result1 = colToDbl(val1);
    double result2 = colToDbl(val2);
    EXPECT_NEAR(result2, result1 * 2.0, 1e-10);
}

// Test three-quarters value
TEST_F(ColToDblTest_389, ThreeQuartersValue_389) {
    GfxColorComp threeQuarters = (gfxColorComp1 * 3) / 4;
    double result = colToDbl(threeQuarters);
    EXPECT_NEAR(result, 0.75, 1e-5);
}

// Test that result for gfxColorComp1 is exactly representable
TEST_F(ColToDblTest_389, ExactDivisionForKnownConstant_389) {
    // gfxColorComp1 = 65536, so x/65536 should be exact for many values
    GfxColorComp val = 32768; // 2^15
    double result = colToDbl(val);
    EXPECT_DOUBLE_EQ(result, 0.5);
}

// Test small positive value
TEST_F(ColToDblTest_389, SmallPositiveValue_389) {
    GfxColorComp val = 10;
    double result = colToDbl(val);
    double expected = 10.0 / 65536.0;
    EXPECT_DOUBLE_EQ(result, expected);
}

// Test negative small value
TEST_F(ColToDblTest_389, SmallNegativeValue_389) {
    GfxColorComp val = -1;
    double result = colToDbl(val);
    double expected = -1.0 / 65536.0;
    EXPECT_DOUBLE_EQ(result, expected);
}
