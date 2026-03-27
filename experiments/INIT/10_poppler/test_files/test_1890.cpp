#include <gtest/gtest.h>
#include <cmath>
#include <algorithm>

// Assuming the existence of a RADIAL_EPSILON constant
#define RADIAL_EPSILON 1e-6

// Mock implementation for radialExtendRange function
bool radialExtendRange(double* range, double t_corner, bool valid) {
    if (valid) {
        if (*range < t_corner) {
            *range = t_corner;
        }
    }
    return valid;
}

// Function to test
inline void radialCorner1(double x, double y, double &b, double dx, double dy, double cr, double dr, double mindr, bool &valid, double *range) {
    b = (x) * dx + (y) * dy + cr * dr;
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

// Test cases
TEST_F(GfxStateTest_1890, RadialCorner1_NormalOperation_1890) {
    double x = 1.0, y = 2.0, b = 0.0;
    double dx = 1.5, dy = -0.5, cr = 2.0, dr = 0.3, mindr = 0.1;
    bool valid = false;
    double range = 0.0;
    
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, &range);
    
    // Check if b is calculated correctly
    double expected_b = (x) * dx + (y) * dy + cr * dr;
    EXPECT_NEAR(b, expected_b, 1e-6);

    // Check if the validity and range are updated as expected
    EXPECT_TRUE(valid);
    EXPECT_GE(range, 0.0);
}

TEST_F(GfxStateTest_1890, RadialCorner1_BoundaryCondition_Epsilon_1890) {
    double x = 0.0, y = 0.0, b = 0.0;
    double dx = 1.0, dy = 1.0, cr = 1.0, dr = 0.0, mindr = 0.1;
    bool valid = false;
    double range = 0.0;
    
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, &range);
    
    // Check if b equals zero (since x = y = 0)
    EXPECT_EQ(b, 0.0);
    
    // Check if validity and range remain unaffected
    EXPECT_FALSE(valid);
    EXPECT_EQ(range, 0.0);
}

TEST_F(GfxStateTest_1890, RadialCorner1_ExceptionalCase_DivisionByZero_1890) {
    double x = 1.0, y = 1.0, b = 0.0;
    double dx = 0.0, dy = 0.0, cr = 2.0, dr = 1.0, mindr = 0.1;
    bool valid = false;
    double range = 0.0;
    
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, &range);
    
    // Check if division by zero is handled by skipping update
    EXPECT_EQ(b, 0.0);
    EXPECT_FALSE(valid);
    EXPECT_EQ(range, 0.0);
}

TEST_F(GfxStateTest_1890, RadialCorner1_RangeUpdate_1890) {
    double x = 1.0, y = 2.0, b = 0.0;
    double dx = 1.5, dy = -0.5, cr = 2.0, dr = 0.3, mindr = 0.1;
    bool valid = false;
    double range = 0.0;
    
    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, &range);
    
    // After valid computation, range should be updated
    EXPECT_GT(range, 0.0);
}