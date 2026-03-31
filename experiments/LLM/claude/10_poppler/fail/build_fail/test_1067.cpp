#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include "OutputDev.h"

// A concrete subclass that doesn't override tilingPatternFill, so it uses the default
class ConcreteOutputDev : public OutputDev
{
};

// A subclass that overrides tilingPatternFill to return true
class OverriddenOutputDev : public OutputDev
{
public:
    bool tilingPatternFill(GfxState *state, Gfx *gfx, Catalog *cat, GfxTilingPattern *tPat,
                           const std::array<double, 6> &mat, int x0, int y0, int x1, int y1,
                           double xStep, double yStep) override
    {
        return true;
    }
};

class OutputDevTest_1067 : public ::testing::Test
{
protected:
    ConcreteOutputDev defaultDev;
    OverriddenOutputDev overriddenDev;
};

// Test that the default implementation of tilingPatternFill returns false
TEST_F(OutputDevTest_1067, DefaultTilingPatternFillReturnsFalse_1067)
{
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    bool result = defaultDev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 100, 100, 1.0, 1.0);
    EXPECT_FALSE(result);
}

// Test that the default implementation returns false with all null pointers
TEST_F(OutputDevTest_1067, DefaultTilingPatternFillWithAllNullptrs_1067)
{
    std::array<double, 6> mat = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    bool result = defaultDev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 0, 0, 0.0, 0.0);
    EXPECT_FALSE(result);
}

// Test that the default implementation returns false with negative coordinates
TEST_F(OutputDevTest_1067, DefaultTilingPatternFillWithNegativeCoordinates_1067)
{
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    bool result = defaultDev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, -100, -100, -1, -1, 0.5, 0.5);
    EXPECT_FALSE(result);
}

// Test that the default implementation returns false with large values
TEST_F(OutputDevTest_1067, DefaultTilingPatternFillWithLargeValues_1067)
{
    std::array<double, 6> mat = {1e10, 1e10, 1e10, 1e10, 1e10, 1e10};
    bool result = defaultDev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat,
                                                INT_MIN, INT_MIN, INT_MAX, INT_MAX,
                                                1e15, 1e15);
    EXPECT_FALSE(result);
}

// Test that the default implementation returns false with zero step values
TEST_F(OutputDevTest_1067, DefaultTilingPatternFillWithZeroSteps_1067)
{
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    bool result = defaultDev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 10, 10, 0.0, 0.0);
    EXPECT_FALSE(result);
}

// Test that an overridden subclass can return true
TEST_F(OutputDevTest_1067, OverriddenTilingPatternFillReturnsTrue_1067)
{
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    bool result = overriddenDev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 100, 100, 1.0, 1.0);
    EXPECT_TRUE(result);
}

// Test polymorphic behavior through base pointer - default returns false
TEST_F(OutputDevTest_1067, PolymorphicDefaultReturnsFalse_1067)
{
    OutputDev *dev = &defaultDev;
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    bool result = dev->tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 50, 50, 2.0, 2.0);
    EXPECT_FALSE(result);
}

// Test polymorphic behavior through base pointer - overridden returns true
TEST_F(OutputDevTest_1067, PolymorphicOverriddenReturnsTrue_1067)
{
    OutputDev *dev = &overriddenDev;
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    bool result = dev->tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 50, 50, 2.0, 2.0);
    EXPECT_TRUE(result);
}

// Test with negative step values
TEST_F(OutputDevTest_1067, DefaultTilingPatternFillWithNegativeSteps_1067)
{
    std::array<double, 6> mat = {-1.0, 0.0, 0.0, -1.0, 0.0, 0.0};
    bool result = defaultDev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 10, 10, -1.0, -1.0);
    EXPECT_FALSE(result);
}

// Test with identity-like matrix values
TEST_F(OutputDevTest_1067, DefaultTilingPatternFillWithIdentityMatrix_1067)
{
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    bool result = defaultDev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 1, 1, 1.0, 1.0);
    EXPECT_FALSE(result);
}

// Test multiple calls return the same result consistently
TEST_F(OutputDevTest_1067, DefaultTilingPatternFillConsistentResult_1067)
{
    std::array<double, 6> mat = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    for (int i = 0; i < 10; ++i) {
        bool result = defaultDev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, i, i, i + 10, i + 10, 1.0, 1.0);
        EXPECT_FALSE(result);
    }
}
