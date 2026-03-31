#include <gtest/gtest.h>
#include <cmath>
#include <cfloat>
#include <limits>

// We need to access the inline functions from GfxState.cc
// Since radialCorner2 and radialExtendRange are inline functions in the .cc file,
// we include them directly for testing purposes.
#include "poppler/GfxState.cc"

class RadialCorner2Test_1891 : public ::testing::Test {
protected:
    double b, c, d;
    bool valid;
    double range[2];

    void SetUp() override {
        b = 0.0;
        c = 0.0;
        d = 0.0;
        valid = false;
        range[0] = 0.0;
        range[1] = 0.0;
    }
};

// Test with discriminant negative (d < 0) - no updates should happen
TEST_F(RadialCorner2Test_1891, NegativeDiscriminant_NoUpdate_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // Choose parameters such that d = b*b - a*c < 0
    // x=0, y=0, cr=0 => b=0, c=0, d=0... need different values
    // x=1, y=0, a=1, dx=0, dy=0, cr=0, dr=1, mindr=0
    // b = 1*0 + 0*0 + 0*1 = 0
    // c = 1 + 0 - 0 = 1
    // d = 0 - 1*1 = -1 < 0
    double x = 1.0, y = 0.0, a = 1.0;
    double dx = 0.0, dy = 0.0, cr = 0.0;
    double inva = 1.0, dr = 1.0, mindr = 0.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    EXPECT_FALSE(valid);
}

// Test with discriminant zero (d == 0) - single root
TEST_F(RadialCorner2Test_1891, ZeroDiscriminant_SingleRoot_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // We need d = b*b - a*c = 0
    // Let x=1, y=0, dx=1, dy=0, cr=0, dr=1, a=1
    // b = 1*1 + 0*0 + 0*1 = 1
    // c = 1 + 0 - 0 = 1
    // d = 1 - 1*1 = 0
    double x = 1.0, y = 0.0, a = 1.0;
    double dx = 1.0, dy = 0.0, cr = 0.0;
    double inva = 1.0, dr = 1.0, mindr = 0.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    // t_corner = (1 + 0) * 1 = 1 and (1 - 0) * 1 = 1
    // Both t_corner * dr = 1 >= mindr=0, so valid should be true
    EXPECT_TRUE(valid);
}

// Test with positive discriminant yielding two valid roots
TEST_F(RadialCorner2Test_1891, PositiveDiscriminant_TwoRoots_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // x=2, y=0, dx=1, dy=0, cr=1, dr=1, a=1
    // b = 2*1 + 0*0 + 1*1 = 3
    // c = 4 + 0 - 1 = 3
    // d = 9 - 1*3 = 6 > 0
    double x = 2.0, y = 0.0, a = 1.0;
    double dx = 1.0, dy = 0.0, cr = 1.0;
    double inva = 1.0, dr = 1.0, mindr = 0.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    // sqrt(6) ~ 2.449
    // t1 = (3 + 2.449) * 1 = 5.449
    // t2 = (3 - 2.449) * 1 = 0.551
    // Both * dr=1 >= mindr=0, so valid
    EXPECT_TRUE(valid);
    EXPECT_LE(range[0], range[1]);
}

// Test where t_corner * dr < mindr filters out roots
TEST_F(RadialCorner2Test_1891, MindrFiltersRoots_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // Same as above but with very large mindr
    double x = 2.0, y = 0.0, a = 1.0;
    double dx = 1.0, dy = 0.0, cr = 1.0;
    double inva = 1.0, dr = 1.0, mindr = 100.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    // t1 ~ 5.449, t2 ~ 0.551, both * 1 < 100
    EXPECT_FALSE(valid);
}

// Test with negative dr and appropriate mindr
TEST_F(RadialCorner2Test_1891, NegativeDr_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // x=2, y=0, dx=1, dy=0, cr=1, dr=-1, a=1
    // b = 2*1 + 0*0 + 1*(-1) = 1
    // c = 4 + 0 - 1 = 3
    // d = 1 - 3 = -2 < 0
    double x = 2.0, y = 0.0, a = 1.0;
    double dx = 1.0, dy = 0.0, cr = 1.0;
    double inva = 1.0, dr = -1.0, mindr = -10.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    // d < 0, so no update
    EXPECT_FALSE(valid);
}

// Test with a != 1 (non-unit coefficient)
TEST_F(RadialCorner2Test_1891, NonUnitA_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // a=2, inva=0.5
    // x=3, y=0, dx=1, dy=0, cr=0, dr=1
    // b = 3*1 + 0 + 0 = 3
    // c = 9 + 0 - 0 = 9
    // d = 9 - 2*9 = -9 < 0
    double x = 3.0, y = 0.0, a = 2.0;
    double dx = 1.0, dy = 0.0, cr = 0.0;
    double inva = 0.5, dr = 1.0, mindr = 0.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    EXPECT_FALSE(valid);
}

// Test with larger cr to ensure positive discriminant with a=2
TEST_F(RadialCorner2Test_1891, NonUnitA_PositiveDiscriminant_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // a=2, inva=0.5
    // x=3, y=0, dx=1, dy=0, cr=3, dr=1
    // b = 3*1 + 0 + 3*1 = 6
    // c = 9 + 0 - 9 = 0
    // d = 36 - 2*0 = 36 > 0
    double x = 3.0, y = 0.0, a = 2.0;
    double dx = 1.0, dy = 0.0, cr = 3.0;
    double inva = 0.5, dr = 1.0, mindr = 0.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    // sqrt(36)=6
    // t1 = (6+6)*0.5 = 6, t1*dr=6>=0 valid
    // t2 = (6-6)*0.5 = 0, t2*dr=0>=0 valid
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.0);
    EXPECT_DOUBLE_EQ(range[1], 6.0);
}

// Test with y != 0 and dy != 0
TEST_F(RadialCorner2Test_1891, NonZeroYComponents_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // x=1, y=1, dx=1, dy=1, cr=0, dr=1, a=1, inva=1, mindr=0
    // b = 1*1 + 1*1 + 0 = 2
    // c = 1 + 1 - 0 = 2
    // d = 4 - 1*2 = 2 > 0
    double x = 1.0, y = 1.0, a = 1.0;
    double dx = 1.0, dy = 1.0, cr = 0.0;
    double inva = 1.0, dr = 1.0, mindr = 0.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    double expected_d = sqrt(2.0);
    double t1 = 2.0 + expected_d;
    double t2 = 2.0 - expected_d;

    EXPECT_TRUE(valid);
    EXPECT_NEAR(range[0], t2, 1e-10);
    EXPECT_NEAR(range[1], t1, 1e-10);
}

// Test that valid starts as true and range is extended
TEST_F(RadialCorner2Test_1891, ValidStartsTrue_RangeExtended_1891) {
    valid = true;
    range[0] = 1.0;
    range[1] = 2.0;

    // Use parameters that produce t_corner outside [1,2]
    // x=3, y=0, dx=1, dy=0, cr=3, dr=1, a=2, inva=0.5, mindr=0
    // t1=6, t2=0 as computed above
    double x = 3.0, y = 0.0, a = 2.0;
    double dx = 1.0, dy = 0.0, cr = 3.0;
    double inva = 0.5, dr = 1.0, mindr = 0.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    EXPECT_TRUE(valid);
    // Range should be extended to include 0 and 6
    EXPECT_NEAR(range[0], 0.0, 1e-10);
    EXPECT_NEAR(range[1], 6.0, 1e-10);
}

// Test with all zeros for x, y, dx, dy, cr
TEST_F(RadialCorner2Test_1891, AllZeroInputs_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // b = 0, c = 0, d = 0 - 1*0 = 0
    // t_corner = (0+0)*1 = 0, t_corner*1=0 >= 0 => valid
    double x = 0.0, y = 0.0, a = 1.0;
    double dx = 0.0, dy = 0.0, cr = 0.0;
    double inva = 1.0, dr = 1.0, mindr = 0.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 0.0);
    EXPECT_DOUBLE_EQ(range[1], 0.0);
}

// Test that mindr boundary condition works (t_corner * dr == mindr)
TEST_F(RadialCorner2Test_1891, MindrBoundaryExact_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // We want t_corner * dr == mindr exactly
    // From previous: x=3, y=0, a=2, dx=1, dy=0, cr=3, dr=1, inva=0.5
    // t1=6, t2=0
    // Set mindr=6 so t1*1=6>=6 passes, t2*1=0<6 fails
    double x = 3.0, y = 0.0, a = 2.0;
    double dx = 1.0, dy = 0.0, cr = 3.0;
    double inva = 0.5, dr = 1.0, mindr = 6.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 6.0);
    EXPECT_DOUBLE_EQ(range[1], 6.0);
}

// Test with negative x and y values
TEST_F(RadialCorner2Test_1891, NegativeCoordinates_1891) {
    valid = false;
    range[0] = 0.0;
    range[1] = 0.0;

    // x=-3, y=0, dx=1, dy=0, cr=3, dr=1, a=2, inva=0.5, mindr=-10
    // b = -3*1 + 0 + 3*1 = 0
    // c = 9 + 0 - 9 = 0
    // d = 0 - 0 = 0
    // t_corner = (0+0)*0.5 = 0 and (0-0)*0.5 = 0
    // t_corner*1 = 0 >= -10 => valid
    double x = -3.0, y = 0.0, a = 2.0;
    double dx = 1.0, dy = 0.0, cr = 3.0;
    double inva = 0.5, dr = 1.0, mindr = -10.0;

    radialCorner2(x, y, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);

    EXPECT_TRUE(valid);
}
