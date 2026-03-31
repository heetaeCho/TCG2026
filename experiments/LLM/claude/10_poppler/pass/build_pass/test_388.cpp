#include <gtest/gtest.h>

// Include necessary headers
#include "GfxState.h"

class DblToColTest_388 : public ::testing::Test {
protected:
};

// Test normal operation: converting 0.0 should yield 0
TEST_F(DblToColTest_388, ZeroInput_388) {
    GfxColorComp result = dblToCol(0.0);
    EXPECT_EQ(result, 0);
}

// Test normal operation: converting 1.0 should yield gfxColorComp1 (65536)
TEST_F(DblToColTest_388, OneInput_388) {
    GfxColorComp result = dblToCol(1.0);
    EXPECT_EQ(result, 65536);
}

// Test normal operation: converting 0.5 should yield half of gfxColorComp1
TEST_F(DblToColTest_388, HalfInput_388) {
    GfxColorComp result = dblToCol(0.5);
    EXPECT_EQ(result, (GfxColorComp)(0.5 * 65536));
}

// Test normal operation: converting 0.25
TEST_F(DblToColTest_388, QuarterInput_388) {
    GfxColorComp result = dblToCol(0.25);
    EXPECT_EQ(result, (GfxColorComp)(0.25 * 65536));
}

// Test normal operation: converting 0.75
TEST_F(DblToColTest_388, ThreeQuarterInput_388) {
    GfxColorComp result = dblToCol(0.75);
    EXPECT_EQ(result, (GfxColorComp)(0.75 * 65536));
}

// Test boundary: very small positive value
TEST_F(DblToColTest_388, VerySmallPositive_388) {
    double small = 1.0 / 65536.0;
    GfxColorComp result = dblToCol(small);
    EXPECT_EQ(result, (GfxColorComp)(small * 65536));
}

// Test boundary: negative input
TEST_F(DblToColTest_388, NegativeInput_388) {
    GfxColorComp result = dblToCol(-1.0);
    EXPECT_EQ(result, (GfxColorComp)(-1.0 * 65536));
}

// Test boundary: negative small value
TEST_F(DblToColTest_388, NegativeSmallInput_388) {
    GfxColorComp result = dblToCol(-0.5);
    EXPECT_EQ(result, (GfxColorComp)(-0.5 * 65536));
}

// Test with value greater than 1.0
TEST_F(DblToColTest_388, GreaterThanOne_388) {
    GfxColorComp result = dblToCol(2.0);
    EXPECT_EQ(result, (GfxColorComp)(2.0 * 65536));
}

// Test with value slightly less than 1.0
TEST_F(DblToColTest_388, SlightlyLessThanOne_388) {
    double val = 1.0 - 1e-10;
    GfxColorComp result = dblToCol(val);
    EXPECT_EQ(result, (GfxColorComp)(val * 65536));
}

// Test that constexpr evaluation works at compile time
TEST_F(DblToColTest_388, ConstexprEvaluation_388) {
    constexpr GfxColorComp result = dblToCol(0.0);
    EXPECT_EQ(result, 0);
    
    constexpr GfxColorComp result1 = dblToCol(1.0);
    EXPECT_EQ(result1, 65536);
}

// Test with 1/3 (non-exact binary fraction)
TEST_F(DblToColTest_388, OneThirdInput_388) {
    double val = 1.0 / 3.0;
    GfxColorComp result = dblToCol(val);
    EXPECT_EQ(result, (GfxColorComp)(val * 65536));
}

// Test with very small epsilon near zero
TEST_F(DblToColTest_388, EpsilonNearZero_388) {
    double val = 1e-15;
    GfxColorComp result = dblToCol(val);
    EXPECT_EQ(result, (GfxColorComp)(val * 65536));
}

// Test with 0.1 (non-exact binary fraction)
TEST_F(DblToColTest_388, TenthInput_388) {
    GfxColorComp result = dblToCol(0.1);
    EXPECT_EQ(result, (GfxColorComp)(0.1 * 65536));
}

// Test with 0.9
TEST_F(DblToColTest_388, NinetyPercentInput_388) {
    GfxColorComp result = dblToCol(0.9);
    EXPECT_EQ(result, (GfxColorComp)(0.9 * 65536));
}
