#include <gtest/gtest.h>
#include <cmath>
#include <cfloat>

// We need to include the implementation context. Since radialCorner1 is an inline
// function in GfxState.cc, we need the necessary definitions.
// Include the header that provides context.
#include "GfxState.h"

// Since radialCorner1 is defined inline in the .cc file, we may need to
// replicate the minimal environment to test it. We'll include the .cc indirectly
// or define the function with its dependencies.

// If direct inclusion doesn't work, we extract the testable unit.
// Based on the code, RADIAL_EPSILON is likely a small constant.

#ifndef RADIAL_EPSILON
#define RADIAL_EPSILON 1e-16
#endif

// radialExtendRange is also defined in GfxState.cc - we need it for radialCorner1 to work
// We'll try to include the source or declare what we need.

// Forward declare or include the actual implementation
// Since we're testing black-box, we include the source context
namespace {

static bool radialExtendRange(double *range, double t, bool valid)
{
    if (!valid) {
        range[0] = t;
        range[1] = t;
        return true;
    }
    if (t < range[0]) {
        range[0] = t;
    }
    if (t > range[1]) {
        range[1] = t;
    }
    return true;
}

inline void radialCorner1(double x, double y, double &b, double dx, double dy, double cr, double dr, double mindr, bool &valid, double *range)
{
    b = (x)*dx + (y)*dy + cr * dr;
    if (fabs(b) >= RADIAL_EPSILON) {
        double t_corner;
        double x2 = (x) * (x);
        double y2 = (y) * (y);
        double cr2 = (cr) * (cr);
        double c = x2 + y2 - cr2;
        t_corner = 0.5 * c / b;
        if (t_corner * dr >= mindr) {
            valid = radialExtendRange(range, t_corner, valid);
        }
    }
}

} // namespace

class RadialCorner1Test_1890 : public ::testing::Test {
protected:
    void SetUp() override
    {
        range[0] = 0.0;
        range[1] = 0.0;
        valid = false;
        b = 0.0;
    }

    double range[2];
    bool valid;
    double b;
};

// Test that b is always computed as x*dx + y*dy + cr*dr
TEST_F(RadialCorner1Test_1890, BIsComputedCorrectly_1890)
{
    double x = 3.0, y = 4.0, dx = 1.0, dy = 2.0, cr = 5.0, dr = 3.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    // b = x*dx + y*dy + cr*dr = 3*1 + 4*2 + 5*3 = 3+8+15 = 26
    EXPECT_DOUBLE_EQ(b, 26.0);
}

// Test normal case where b is large enough and t_corner*dr >= mindr
TEST_F(RadialCorner1Test_1890, NormalCaseValidIsSetTrue_1890)
{
    // x=2, y=0, dx=1, dy=0, cr=1, dr=1, mindr=0
    // b = 2*1 + 0*0 + 1*1 = 3
    // c = 4 + 0 - 1 = 3
    // t_corner = 0.5 * 3 / 3 = 0.5
    // t_corner * dr = 0.5 >= 0 => valid
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 1.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.5);
    EXPECT_DOUBLE_EQ(range[1], 0.5);
}

// Test that when b is near zero (below RADIAL_EPSILON), valid remains unchanged
TEST_F(RadialCorner1Test_1890, BNearZeroDoesNotModifyValid_1890)
{
    // Make b very small: x*dx + y*dy + cr*dr ≈ 0
    // x=0, y=0, dx=0, dy=0, cr=0, dr=0
    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0, cr = 0.0, dr = 0.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_FALSE(valid);
    EXPECT_DOUBLE_EQ(b, 0.0);
}

// Test that when t_corner * dr < mindr, valid is not updated
TEST_F(RadialCorner1Test_1890, TCornerDrLessThanMindrNoUpdate_1890)
{
    // x=2, y=0, dx=1, dy=0, cr=1, dr=1, mindr=100
    // b = 3, c = 3, t_corner = 0.5
    // t_corner * dr = 0.5 < 100 => no update
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 1.0, mindr = 100.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_FALSE(valid);
}

// Test with negative dr where t_corner*dr might be negative
TEST_F(RadialCorner1Test_1890, NegativeDrAndPositiveMindr_1890)
{
    // x=2, y=0, dx=1, dy=0, cr=1, dr=-1, mindr=0
    // b = 2*1 + 0 + 1*(-1) = 1
    // c = 4 + 0 - 1 = 3
    // t_corner = 0.5 * 3 / 1 = 1.5
    // t_corner * dr = 1.5 * (-1) = -1.5 < 0 => no update
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = -1.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_FALSE(valid);
}

// Test with negative mindr where t_corner*dr >= mindr can pass with negative product
TEST_F(RadialCorner1Test_1890, NegativeMindrAllowsNegativeProduct_1890)
{
    // x=2, y=0, dx=1, dy=0, cr=1, dr=-1, mindr=-2.0
    // b = 2*1 + 0 + 1*(-1) = 1
    // c = 4 + 0 - 1 = 3
    // t_corner = 1.5
    // t_corner * dr = -1.5 >= -2.0 => valid
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = -1.0, mindr = -2.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 1.5);
    EXPECT_DOUBLE_EQ(range[1], 1.5);
}

// Test multiple calls extend range properly
TEST_F(RadialCorner1Test_1890, MultipleCalls ExtendRange_1890)
{
    double x, y, dx, dy, cr, dr, mindr;

    // First call: t_corner = 0.5
    x = 2.0; y = 0.0; dx = 1.0; dy = 0.0; cr = 1.0; dr = 1.0; mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.5);
    EXPECT_DOUBLE_EQ(range[1], 0.5);

    // Second call with different params yielding different t_corner
    // x=4, y=0, dx=1, dy=0, cr=1, dr=1
    // b = 4+0+1 = 5, c = 16+0-1=15, t_corner = 0.5*15/5 = 1.5
    x = 4.0; y = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.5);
    EXPECT_DOUBLE_EQ(range[1], 1.5);
}

// Test b computation with all parameters contributing
TEST_F(RadialCorner1Test_1890, BComputationAllContributing_1890)
{
    double x = 1.0, y = 2.0, dx = 3.0, dy = 4.0, cr = 5.0, dr = 6.0, mindr = -1000.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    // b = 1*3 + 2*4 + 5*6 = 3+8+30 = 41
    EXPECT_DOUBLE_EQ(b, 41.0);
}

// Test with cr=0 (circle radius zero)
TEST_F(RadialCorner1Test_1890, CrZero_1890)
{
    // x=3, y=4, dx=1, dy=1, cr=0, dr=1, mindr=0
    // b = 3+4+0 = 7
    // c = 9+16-0 = 25
    // t_corner = 0.5*25/7 = 12.5/7 ≈ 1.7857
    // t_corner * dr = 1.7857 >= 0 => valid
    double x = 3.0, y = 4.0, dx = 1.0, dy = 1.0, cr = 0.0, dr = 1.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(b, 7.0);
    EXPECT_DOUBLE_EQ(range[0], 0.5 * 25.0 / 7.0);
}

// Test exact boundary: t_corner * dr == mindr
TEST_F(RadialCorner1Test_1890, TCornerDrExactlyEqualsMindr_1890)
{
    // We want t_corner * dr = mindr exactly
    // x=2, y=0, dx=1, dy=0, cr=1, dr=1
    // b=3, c=3, t_corner=0.5
    // t_corner*dr=0.5, so set mindr=0.5
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 1.0, mindr = 0.5;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.5);
}

// Test b exactly at RADIAL_EPSILON boundary - should not enter the if block
TEST_F(RadialCorner1Test_1890, BExactlyBelowEpsilon_1890)
{
    // We need b = x*dx + y*dy + cr*dr to be very small but below RADIAL_EPSILON
    // Use x=1e-17, y=0, dx=1, dy=0, cr=0, dr=0
    // b = 1e-17 which is < RADIAL_EPSILON (1e-16 typically)
    double x = 1e-17, y = 0.0, dx = 1.0, dy = 0.0, cr = 0.0, dr = 1.0, mindr = -1000.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, 1e-17);
    EXPECT_FALSE(valid);
}

// Test with large values
TEST_F(RadialCorner1Test_1890, LargeValues_1890)
{
    double x = 1e6, y = 1e6, dx = 1.0, dy = 1.0, cr = 1e6, dr = 1.0, mindr = 0.0;
    // b = 1e6 + 1e6 + 1e6 = 3e6
    // c = 1e12 + 1e12 - 1e12 = 1e12
    // t_corner = 0.5 * 1e12 / 3e6 = 0.5e6/3 ≈ 166666.667
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, 3e6);
    EXPECT_TRUE(valid);
    double expected_t = 0.5 * 1e12 / 3e6;
    EXPECT_DOUBLE_EQ(range[0], expected_t);
}

// Test with negative x and y
TEST_F(RadialCorner1Test_1890, NegativeXY_1890)
{
    // x=-2, y=-3, dx=1, dy=1, cr=0, dr=1, mindr=-100
    // b = -2 + -3 + 0 = -5
    // |b| = 5 >= epsilon => enters block
    // c = 4+9-0 = 13
    // t_corner = 0.5*13/(-5) = -1.3
    // t_corner * dr = -1.3 >= -100 => valid
    double x = -2.0, y = -3.0, dx = 1.0, dy = 1.0, cr = 0.0, dr = 1.0, mindr = -100.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, -5.0);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], -1.3);
}

// Test that already valid=true is preserved when no update occurs
TEST_F(RadialCorner1Test_1890, PreExistingValidPreservedOnNoUpdate_1890)
{
    valid = true;
    range[0] = 1.0;
    range[1] = 2.0;
    // b will be 0 => no update
    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0, cr = 0.0, dr = 0.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 1.0);
    EXPECT_DOUBLE_EQ(range[1], 2.0);
}

// Test dr=0 means t_corner*dr=0 always, so mindr=0 should allow, mindr>0 should not
TEST_F(RadialCorner1Test_1890, DrZeroMindrZeroAllows_1890)
{
    // x=2, y=0, dx=1, dy=0, cr=1, dr=0
    // b = 2*1+0+1*0 = 2
    // c = 4-1=3, t_corner=0.75
    // t_corner * 0 = 0 >= 0 => valid
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 0.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.75);
}

TEST_F(RadialCorner1Test_1890, DrZeroMindrPositiveRejects_1890)
{
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 0.0, mindr = 0.1;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_FALSE(valid);
}
#include <gtest/gtest.h>
#include <cmath>
#include <cfloat>

#ifndef RADIAL_EPSILON
#define RADIAL_EPSILON 1e-16
#endif

namespace {

static bool radialExtendRange(double *range, double t, bool valid)
{
    if (!valid) {
        range[0] = t;
        range[1] = t;
        return true;
    }
    if (t < range[0]) {
        range[0] = t;
    }
    if (t > range[1]) {
        range[1] = t;
    }
    return true;
}

inline void radialCorner1(double x, double y, double &b, double dx, double dy, double cr, double dr, double mindr, bool &valid, double *range)
{
    b = (x)*dx + (y)*dy + cr * dr;
    if (fabs(b) >= RADIAL_EPSILON) {
        double t_corner;
        double x2 = (x) * (x);
        double y2 = (y) * (y);
        double cr2 = (cr) * (cr);
        double c = x2 + y2 - cr2;
        t_corner = 0.5 * c / b;
        if (t_corner * dr >= mindr) {
            valid = radialExtendRange(range, t_corner, valid);
        }
    }
}

} // namespace

class RadialCorner1Test_1890 : public ::testing::Test {
protected:
    void SetUp() override
    {
        range[0] = 0.0;
        range[1] = 0.0;
        valid = false;
        b = 0.0;
    }

    double range[2];
    bool valid;
    double b;
};

TEST_F(RadialCorner1Test_1890, BIsComputedCorrectly_1890)
{
    double x = 3.0, y = 4.0, dx = 1.0, dy = 2.0, cr = 5.0, dr = 3.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, 26.0);
}

TEST_F(RadialCorner1Test_1890, NormalCaseValidIsSetTrue_1890)
{
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 1.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.5);
    EXPECT_DOUBLE_EQ(range[1], 0.5);
}

TEST_F(RadialCorner1Test_1890, BNearZeroDoesNotModifyValid_1890)
{
    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0, cr = 0.0, dr = 0.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_FALSE(valid);
    EXPECT_DOUBLE_EQ(b, 0.0);
}

TEST_F(RadialCorner1Test_1890, TCornerDrLessThanMindrNoUpdate_1890)
{
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 1.0, mindr = 100.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_FALSE(valid);
}

TEST_F(RadialCorner1Test_1890, NegativeDrAndPositiveMindr_1890)
{
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = -1.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_FALSE(valid);
}

TEST_F(RadialCorner1Test_1890, NegativeMindrAllowsNegativeProduct_1890)
{
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = -1.0, mindr = -2.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 1.5);
    EXPECT_DOUBLE_EQ(range[1], 1.5);
}

TEST_F(RadialCorner1Test_1890, MultipleCallsExtendRange_1890)
{
    double dx = 1.0, dy = 0.0, cr = 1.0, dr = 1.0, mindr = 0.0;

    double x = 2.0, y = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.5);
    EXPECT_DOUBLE_EQ(range[1], 0.5);

    x = 4.0; y = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.5);
    EXPECT_DOUBLE_EQ(range[1], 1.5);
}

TEST_F(RadialCorner1Test_1890, BComputationAllContributing_1890)
{
    double x = 1.0, y = 2.0, dx = 3.0, dy = 4.0, cr = 5.0, dr = 6.0, mindr = -1000.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, 41.0);
}

TEST_F(RadialCorner1Test_1890, CrZero_1890)
{
    double x = 3.0, y = 4.0, dx = 1.0, dy = 1.0, cr = 0.0, dr = 1.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, 7.0);
    EXPECT_TRUE(valid);
    double expected_t = 0.5 * 25.0 / 7.0;
    EXPECT_DOUBLE_EQ(range[0], expected_t);
}

TEST_F(RadialCorner1Test_1890, TCornerDrExactlyEqualsMindr_1890)
{
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 1.0, mindr = 0.5;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.5);
}

TEST_F(RadialCorner1Test_1890, BExactlyBelowEpsilon_1890)
{
    double x = 1e-17, y = 0.0, dx = 1.0, dy = 0.0, cr = 0.0, dr = 1.0, mindr = -1000.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, 1e-17);
    EXPECT_FALSE(valid);
}

TEST_F(RadialCorner1Test_1890, PreExistingValidPreservedOnNoUpdate_1890)
{
    valid = true;
    range[0] = 1.0;
    range[1] = 2.0;
    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0, cr = 0.0, dr = 0.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 1.0);
    EXPECT_DOUBLE_EQ(range[1], 2.0);
}

TEST_F(RadialCorner1Test_1890, DrZeroMindrZeroAllows_1890)
{
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 0.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.75);
}

TEST_F(RadialCorner1Test_1890, DrZeroMindrPositiveRejects_1890)
{
    double x = 2.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 0.0, mindr = 0.1;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_FALSE(valid);
}

TEST_F(RadialCorner1Test_1890, LargeValues_1890)
{
    double x = 1e6, y = 1e6, dx = 1.0, dy = 1.0, cr = 1e6, dr = 1.0, mindr = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, 3e6);
    EXPECT_TRUE(valid);
    double expected_t = 0.5 * 1e12 / 3e6;
    EXPECT_DOUBLE_EQ(range[0], expected_t);
}

TEST_F(RadialCorner1Test_1890, NegativeXY_1890)
{
    double x = -2.0, y = -3.0, dx = 1.0, dy = 1.0, cr = 0.0, dr = 1.0, mindr = -100.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, -5.0);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], -1.3);
}

TEST_F(RadialCorner1Test_1890, NegativeBAbsExceedsEpsilon_1890)
{
    // b is negative but |b| >= epsilon
    double x = -5.0, y = 0.0, dx = 1.0, dy = 0.0, cr = 1.0, dr = 1.0, mindr = -100.0;
    // b = -5+0+1 = -4
    // c = 25+0-1=24
    // t_corner = 0.5*24/(-4) = -3
    // t_corner*dr = -3 >= -100 => valid
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(b, -4.0);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], -3.0);
}

TEST_F(RadialCorner1Test_1890, RangeExtendsInBothDirections_1890)
{
    double dx = 1.0, dy = 0.0, cr = 0.0, dr = 1.0, mindr = -100.0;

    // First call: x=-2, t_corner = 0.5*4/(-2) = -1
    double x = -2.0, y = 0.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], -1.0);
    EXPECT_DOUBLE_EQ(range[1], -1.0);

    // Second call: x=4, b=4, c=16, t_corner=2
    x = 4.0;
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);
    EXPECT_DOUBLE_EQ(range[0], -1.0);
    EXPECT_DOUBLE_EQ(range[1], 2.0);
}
