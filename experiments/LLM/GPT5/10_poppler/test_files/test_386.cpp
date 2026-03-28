// Matrix_init_test_386.cpp
// Unit tests for Matrix::init (GfxState.h)

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <cfloat>

#include "GfxState.h"

namespace {

class MatrixTest_386 : public ::testing::Test {};

TEST_F(MatrixTest_386, InitSetsAllElements_386)
{
    Matrix mtx;
    mtx.init(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    ASSERT_EQ(mtx.m.size(), 6u);
    EXPECT_DOUBLE_EQ(mtx.m[0], 1.0);
    EXPECT_DOUBLE_EQ(mtx.m[1], 2.0);
    EXPECT_DOUBLE_EQ(mtx.m[2], 3.0);
    EXPECT_DOUBLE_EQ(mtx.m[3], 4.0);
    EXPECT_DOUBLE_EQ(mtx.m[4], 5.0);
    EXPECT_DOUBLE_EQ(mtx.m[5], 6.0);
}

TEST_F(MatrixTest_386, InitOverwritesPreviousValues_386)
{
    Matrix mtx;
    mtx.init(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    mtx.init(-1.5, -2.5, -3.5, -4.5, -5.5, -6.5);

    EXPECT_DOUBLE_EQ(mtx.m[0], -1.5);
    EXPECT_DOUBLE_EQ(mtx.m[1], -2.5);
    EXPECT_DOUBLE_EQ(mtx.m[2], -3.5);
    EXPECT_DOUBLE_EQ(mtx.m[3], -4.5);
    EXPECT_DOUBLE_EQ(mtx.m[4], -5.5);
    EXPECT_DOUBLE_EQ(mtx.m[5], -6.5);
}

TEST_F(MatrixTest_386, InitHandlesNegativeAndZero_386)
{
    Matrix mtx;
    mtx.init(0.0, -0.0, -12.0, 0.0, -34.0, 56.0);

    EXPECT_DOUBLE_EQ(mtx.m[0], 0.0);
    EXPECT_DOUBLE_EQ(mtx.m[1], -0.0); // verify sign is acceptable via equality
    EXPECT_DOUBLE_EQ(mtx.m[2], -12.0);
    EXPECT_DOUBLE_EQ(mtx.m[3], 0.0);
    EXPECT_DOUBLE_EQ(mtx.m[4], -34.0);
    EXPECT_DOUBLE_EQ(mtx.m[5], 56.0);
}

TEST_F(MatrixTest_386, InitPreservesNaNAndInfinity_386)
{
    Matrix mtx;

    const double nan_v = std::nan("");
    const double pos_inf = std::numeric_limits<double>::infinity();
    const double neg_inf = -std::numeric_limits<double>::infinity();

    mtx.init(nan_v, pos_inf, neg_inf, 1.0, 2.0, 3.0);

    EXPECT_TRUE(std::isnan(mtx.m[0]));
    EXPECT_TRUE(std::isinf(mtx.m[1]));
    EXPECT_GT(mtx.m[1], 0.0);

    EXPECT_TRUE(std::isinf(mtx.m[2]));
    EXPECT_LT(mtx.m[2], 0.0);

    EXPECT_DOUBLE_EQ(mtx.m[3], 1.0);
    EXPECT_DOUBLE_EQ(mtx.m[4], 2.0);
    EXPECT_DOUBLE_EQ(mtx.m[5], 3.0);
}

TEST_F(MatrixTest_386, InitHandlesLargeFiniteValues_386)
{
    Matrix mtx;

    // Use large but finite values to avoid UB from overflows in test expectations.
    const double a = DBL_MAX / 4.0;
    const double b = -DBL_MAX / 5.0;
    const double c = DBL_MIN;        // smallest positive normalized
    const double d = -DBL_MIN;
    const double e = 1e308;
    const double f = -1e308;

    mtx.init(a, b, c, d, e, f);

    EXPECT_DOUBLE_EQ(mtx.m[0], a);
    EXPECT_DOUBLE_EQ(mtx.m[1], b);
    EXPECT_DOUBLE_EQ(mtx.m[2], c);
    EXPECT_DOUBLE_EQ(mtx.m[3], d);
    EXPECT_DOUBLE_EQ(mtx.m[4], e);
    EXPECT_DOUBLE_EQ(mtx.m[5], f);
}

} // namespace