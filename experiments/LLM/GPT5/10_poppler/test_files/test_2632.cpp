// File: HtmlUtilsTest_2632.cpp

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <limits>

// Adjust include path as needed for your build setup.
#include "TestProjects/poppler/utils/HtmlUtils.h"

namespace {

class HtmlUtilsTest_2632 : public ::testing::Test {
protected:
    static std::array<double, 6> MakeMat(double a0, double a1) {
        std::array<double, 6> mat{};
        mat[0] = a0;
        mat[1] = a1;
        // Remaining elements are irrelevant for isMatRotOrSkew().
        return mat;
    }
};

TEST_F(HtmlUtilsTest_2632, NegativeA0ReturnsTrue_2632)
{
    const auto mat = MakeMat(-1.0, 0.0);
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(HtmlUtilsTest_2632, NegativeA0OverridesBWithinTolerance_2632)
{
    // Even if mat[1] is plausibly "within", negative mat[0] should still return true.
    const auto mat = MakeMat(-0.0001, 0.0);
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(HtmlUtilsTest_2632, NonNegativeA0AndBExactlyZeroReturnsFalse_2632)
{
    const auto mat = MakeMat(0.0, 0.0);
    EXPECT_FALSE(isMatRotOrSkew(mat));
}

TEST_F(HtmlUtilsTest_2632, NonNegativeA0AndBWellWithinToleranceReturnsFalse_2632)
{
    // Choose a value safely within typical tolerance logic for (.1 around 0).
    const auto mat = MakeMat(1.0, 0.05);
    EXPECT_FALSE(isMatRotOrSkew(mat));
}

TEST_F(HtmlUtilsTest_2632, NonNegativeA0AndBWellOutsideToleranceReturnsTrue_2632)
{
    const auto mat = MakeMat(1.0, 0.5);
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(HtmlUtilsTest_2632, NonNegativeA0AndBJustAboveToleranceReturnsTrue_2632)
{
    // Pick a value slightly above 0.1 to avoid depending on inclusive/exclusive boundary behavior.
    const auto mat = MakeMat(1.0, 0.1000001);
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(HtmlUtilsTest_2632, NonNegativeA0AndBNaNReturnsTrue_2632)
{
    // Exceptional-ish input: NaN. Comparison mat[0] < 0 will be false if mat[0] is not NaN.
    // For typical "within" helpers, NaN is not within any range, so the function should report skew/rot.
    const auto mat = MakeMat(1.0, std::numeric_limits<double>::quiet_NaN());
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

} // namespace