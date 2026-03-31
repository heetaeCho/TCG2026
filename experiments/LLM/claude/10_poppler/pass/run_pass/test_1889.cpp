#include <gtest/gtest.h>
#include <cmath>
#include <cfloat>

// We need access to the inline function. Since it's defined in GfxState.cc,
// we include it or replicate the necessary context.
// The function depends on RADIAL_EPSILON and radialExtendRange.

#define RADIAL_EPSILON 1e-7

static bool radialExtendRange(double *range, double value, bool valid) {
    if (!valid) {
        range[0] = value;
        range[1] = value;
    } else {
        if (value < range[0]) range[0] = value;
        if (value > range[1]) range[1] = value;
    }
    return true;
}

inline void radialEdge(double num, double den, double delta, double lower, double upper, double dr, double mindr, bool &valid, double *range) {
    if (fabs(den) >= RADIAL_EPSILON) {
        double t_edge, v;
        t_edge = (num) / (den);
        v = t_edge * (delta);
        if (t_edge * dr >= mindr && (lower) <= v && v <= (upper)) {
            valid = radialExtendRange(range, t_edge, valid);
        }
    }
}

class RadialEdgeTest_1889 : public ::testing::Test {
protected:
    void SetUp() override {
        valid = false;
        range[0] = 0.0;
        range[1] = 0.0;
    }

    bool valid;
    double range[2];
};

// Test that when den is zero (below RADIAL_EPSILON), nothing happens
TEST_F(RadialEdgeTest_1889, DenZero_NoEffect_1889) {
    valid = false;
    range[0] = 42.0;
    range[1] = 42.0;
    radialEdge(1.0, 0.0, 1.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_FALSE(valid);
    EXPECT_DOUBLE_EQ(range[0], 42.0);
    EXPECT_DOUBLE_EQ(range[1], 42.0);
}

// Test that when den is very small but below epsilon, nothing happens
TEST_F(RadialEdgeTest_1889, DenBelowEpsilon_NoEffect_1889) {
    valid = false;
    radialEdge(1.0, 1e-8, 1.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_FALSE(valid);
}

// Test that when den is exactly at epsilon, the function proceeds
TEST_F(RadialEdgeTest_1889, DenAtEpsilon_Proceeds_1889) {
    // den = 1e-7, num = 1e-7 => t_edge = 1.0
    // delta = 5.0 => v = 5.0, lower=0.0, upper=10.0 => in range
    // dr = 1.0, mindr = 0.0 => t_edge*dr=1.0 >= 0.0
    radialEdge(1e-7, 1e-7, 5.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 1.0);
    EXPECT_DOUBLE_EQ(range[1], 1.0);
}

// Test normal case where all conditions are satisfied
TEST_F(RadialEdgeTest_1889, NormalCase_AllConditionsMet_1889) {
    // num=2.0, den=1.0 => t_edge=2.0
    // delta=3.0 => v=6.0, lower=0.0, upper=10.0 => OK
    // dr=1.0, mindr=0.0 => 2.0>=0.0 => OK
    radialEdge(2.0, 1.0, 3.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 2.0);
    EXPECT_DOUBLE_EQ(range[1], 2.0);
}

// Test that v below lower causes no update
TEST_F(RadialEdgeTest_1889, VBelowLower_NoUpdate_1889) {
    // num=1.0, den=1.0 => t_edge=1.0
    // delta=2.0 => v=2.0, lower=3.0, upper=10.0 => v < lower
    radialEdge(1.0, 1.0, 2.0, 3.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_FALSE(valid);
}

// Test that v above upper causes no update
TEST_F(RadialEdgeTest_1889, VAboveUpper_NoUpdate_1889) {
    // num=5.0, den=1.0 => t_edge=5.0
    // delta=3.0 => v=15.0, lower=0.0, upper=10.0 => v > upper
    radialEdge(5.0, 1.0, 3.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_FALSE(valid);
}

// Test that t_edge*dr < mindr causes no update
TEST_F(RadialEdgeTest_1889, DrConditionFails_NoUpdate_1889) {
    // num=1.0, den=1.0 => t_edge=1.0
    // delta=5.0 => v=5.0, lower=0.0, upper=10.0 => OK
    // dr=1.0, mindr=2.0 => t_edge*dr=1.0 < 2.0 => fail
    radialEdge(1.0, 1.0, 5.0, 0.0, 10.0, 1.0, 2.0, valid, range);
    EXPECT_FALSE(valid);
}

// Test negative den (abs(den) >= epsilon)
TEST_F(RadialEdgeTest_1889, NegativeDen_Proceeds_1889) {
    // num=-2.0, den=-1.0 => t_edge=2.0
    // delta=3.0 => v=6.0, lower=0.0, upper=10.0 => OK
    // dr=1.0, mindr=0.0 => 2.0>=0.0 => OK
    radialEdge(-2.0, -1.0, 3.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 2.0);
    EXPECT_DOUBLE_EQ(range[1], 2.0);
}

// Test that negative t_edge with negative dr can satisfy the dr condition
TEST_F(RadialEdgeTest_1889, NegativeTedgeNegativeDr_1889) {
    // num=-2.0, den=1.0 => t_edge=-2.0
    // delta=-3.0 => v=6.0, lower=0.0, upper=10.0 => OK
    // dr=-1.0 => t_edge*dr = (-2.0)*(-1.0) = 2.0, mindr=0.0 => OK
    radialEdge(-2.0, 1.0, -3.0, 0.0, 10.0, -1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], -2.0);
    EXPECT_DOUBLE_EQ(range[1], -2.0);
}

// Test multiple calls extending range
TEST_F(RadialEdgeTest_1889, MultipleCalls_ExtendRange_1889) {
    // First call: t_edge=2.0
    radialEdge(2.0, 1.0, 3.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 2.0);
    EXPECT_DOUBLE_EQ(range[1], 2.0);

    // Second call: t_edge=5.0
    // delta=1.0 => v=5.0, lower=0.0, upper=10.0
    radialEdge(5.0, 1.0, 1.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 2.0);
    EXPECT_DOUBLE_EQ(range[1], 5.0);

    // Third call: t_edge=1.0
    radialEdge(1.0, 1.0, 5.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 1.0);
    EXPECT_DOUBLE_EQ(range[1], 5.0);
}

// Test v exactly at lower boundary
TEST_F(RadialEdgeTest_1889, VAtLowerBoundary_1889) {
    // num=3.0, den=1.0 => t_edge=3.0
    // delta=1.0 => v=3.0, lower=3.0, upper=10.0 => v == lower => OK
    radialEdge(3.0, 1.0, 1.0, 3.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 3.0);
    EXPECT_DOUBLE_EQ(range[1], 3.0);
}

// Test v exactly at upper boundary
TEST_F(RadialEdgeTest_1889, VAtUpperBoundary_1889) {
    // num=5.0, den=1.0 => t_edge=5.0
    // delta=2.0 => v=10.0, lower=0.0, upper=10.0 => v == upper => OK
    radialEdge(5.0, 1.0, 2.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 5.0);
    EXPECT_DOUBLE_EQ(range[1], 5.0);
}

// Test t_edge*dr exactly equals mindr
TEST_F(RadialEdgeTest_1889, DrExactlyAtMindr_1889) {
    // num=2.0, den=1.0 => t_edge=2.0
    // dr=1.0, mindr=2.0 => t_edge*dr=2.0 >= 2.0 => OK
    // delta=3.0 => v=6.0, lower=0.0, upper=10.0 => OK
    radialEdge(2.0, 1.0, 3.0, 0.0, 10.0, 1.0, 2.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 2.0);
}

// Test with zero num
TEST_F(RadialEdgeTest_1889, ZeroNum_1889) {
    // num=0.0, den=1.0 => t_edge=0.0
    // delta=5.0 => v=0.0, lower=0.0, upper=10.0 => OK
    // dr=1.0, mindr=0.0 => 0.0>=0.0 => OK
    radialEdge(0.0, 1.0, 5.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.0);
    EXPECT_DOUBLE_EQ(range[1], 0.0);
}

// Test with zero delta => v=0 always
TEST_F(RadialEdgeTest_1889, ZeroDelta_1889) {
    // num=3.0, den=1.0 => t_edge=3.0
    // delta=0.0 => v=0.0, lower=-1.0, upper=1.0 => OK
    // dr=1.0, mindr=0.0 => 3.0>=0.0 => OK
    radialEdge(3.0, 1.0, 0.0, -1.0, 1.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 3.0);
    EXPECT_DOUBLE_EQ(range[1], 3.0);
}

// Test with large values
TEST_F(RadialEdgeTest_1889, LargeValues_1889) {
    double big = 1e15;
    // num=big, den=1.0 => t_edge=big
    // delta=1.0 => v=big, lower=0.0, upper=2e15 => OK
    // dr=1.0, mindr=0.0 => big>=0.0 => OK
    radialEdge(big, 1.0, 1.0, 0.0, 2e15, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], big);
    EXPECT_DOUBLE_EQ(range[1], big);
}

// Test valid already true, range doesn't get reset
TEST_F(RadialEdgeTest_1889, ValidAlreadyTrue_RangeExtended_1889) {
    valid = true;
    range[0] = 1.0;
    range[1] = 3.0;
    // t_edge = 5.0, v = 5.0*2.0 = 10.0, lower=0.0, upper=10.0
    radialEdge(5.0, 1.0, 2.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 1.0);
    EXPECT_DOUBLE_EQ(range[1], 5.0);
}

// Test that when conditions fail, previously valid range is preserved
TEST_F(RadialEdgeTest_1889, FailedCondition_PreservesExistingRange_1889) {
    valid = true;
    range[0] = 1.0;
    range[1] = 3.0;
    // den = 0 => skip
    radialEdge(5.0, 0.0, 2.0, 0.0, 10.0, 1.0, 0.0, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 1.0);
    EXPECT_DOUBLE_EQ(range[1], 3.0);
}
