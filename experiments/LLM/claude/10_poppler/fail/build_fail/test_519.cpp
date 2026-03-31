#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "GfxState.h"

// Since GfxRadialShading requires Function objects and has complex constructors,
// we need to work with what's available. We'll test getCoords through the
// copy constructor path or by creating instances where possible.

class GfxRadialShadingTest_519 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getCoords returns the coordinates that were set during construction
TEST_F(GfxRadialShadingTest_519, GetCoordsReturnsConstructorValues_519)
{
    double x0 = 1.0, y0 = 2.0, r0 = 3.0;
    double x1 = 4.0, y1 = 5.0, r1 = 6.0;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), false, false);

    double ox0, oy0, or0, ox1, oy1, or1;
    shading.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    EXPECT_DOUBLE_EQ(ox0, 1.0);
    EXPECT_DOUBLE_EQ(oy0, 2.0);
    EXPECT_DOUBLE_EQ(or0, 3.0);
    EXPECT_DOUBLE_EQ(ox1, 4.0);
    EXPECT_DOUBLE_EQ(oy1, 5.0);
    EXPECT_DOUBLE_EQ(or1, 6.0);
}

// Test getCoords with zero values
TEST_F(GfxRadialShadingTest_519, GetCoordsWithZeroValues_519)
{
    double x0 = 0.0, y0 = 0.0, r0 = 0.0;
    double x1 = 0.0, y1 = 0.0, r1 = 0.0;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), false, false);

    double ox0, oy0, or0, ox1, oy1, or1;
    shading.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    EXPECT_DOUBLE_EQ(ox0, 0.0);
    EXPECT_DOUBLE_EQ(oy0, 0.0);
    EXPECT_DOUBLE_EQ(or0, 0.0);
    EXPECT_DOUBLE_EQ(ox1, 0.0);
    EXPECT_DOUBLE_EQ(oy1, 0.0);
    EXPECT_DOUBLE_EQ(or1, 0.0);
}

// Test getCoords with negative values
TEST_F(GfxRadialShadingTest_519, GetCoordsWithNegativeValues_519)
{
    double x0 = -10.5, y0 = -20.3, r0 = 0.5;
    double x1 = -5.0, y1 = -15.7, r1 = 100.0;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), false, false);

    double ox0, oy0, or0, ox1, oy1, or1;
    shading.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    EXPECT_DOUBLE_EQ(ox0, -10.5);
    EXPECT_DOUBLE_EQ(oy0, -20.3);
    EXPECT_DOUBLE_EQ(or0, 0.5);
    EXPECT_DOUBLE_EQ(ox1, -5.0);
    EXPECT_DOUBLE_EQ(oy1, -15.7);
    EXPECT_DOUBLE_EQ(or1, 100.0);
}

// Test getCoords with very large values
TEST_F(GfxRadialShadingTest_519, GetCoordsWithLargeValues_519)
{
    double x0 = 1e15, y0 = 1e15, r0 = 1e10;
    double x1 = -1e15, y1 = -1e15, r1 = 1e10;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), false, false);

    double ox0, oy0, or0, ox1, oy1, or1;
    shading.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    EXPECT_DOUBLE_EQ(ox0, 1e15);
    EXPECT_DOUBLE_EQ(oy0, 1e15);
    EXPECT_DOUBLE_EQ(or0, 1e10);
    EXPECT_DOUBLE_EQ(ox1, -1e15);
    EXPECT_DOUBLE_EQ(oy1, -1e15);
    EXPECT_DOUBLE_EQ(or1, 1e10);
}

// Test getCoords with very small (near-zero) values
TEST_F(GfxRadialShadingTest_519, GetCoordsWithVerySmallValues_519)
{
    double x0 = 1e-15, y0 = 1e-15, r0 = 1e-15;
    double x1 = -1e-15, y1 = -1e-15, r1 = 1e-15;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), false, false);

    double ox0, oy0, or0, ox1, oy1, or1;
    shading.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    EXPECT_DOUBLE_EQ(ox0, 1e-15);
    EXPECT_DOUBLE_EQ(oy0, 1e-15);
    EXPECT_DOUBLE_EQ(or0, 1e-15);
    EXPECT_DOUBLE_EQ(ox1, -1e-15);
    EXPECT_DOUBLE_EQ(oy1, -1e-15);
    EXPECT_DOUBLE_EQ(or1, 1e-15);
}

// Test getCoords after copy construction preserves coordinates
TEST_F(GfxRadialShadingTest_519, GetCoordsAfterCopyConstruction_519)
{
    double x0 = 10.0, y0 = 20.0, r0 = 30.0;
    double x1 = 40.0, y1 = 50.0, r1 = 60.0;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading original(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), false, false);

    GfxRadialShading copied(&original);

    double ox0, oy0, or0, ox1, oy1, or1;
    copied.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    EXPECT_DOUBLE_EQ(ox0, 10.0);
    EXPECT_DOUBLE_EQ(oy0, 20.0);
    EXPECT_DOUBLE_EQ(or0, 30.0);
    EXPECT_DOUBLE_EQ(ox1, 40.0);
    EXPECT_DOUBLE_EQ(oy1, 50.0);
    EXPECT_DOUBLE_EQ(or1, 60.0);
}

// Test that getCoords with same start and end coordinates works
TEST_F(GfxRadialShadingTest_519, GetCoordsWithSameStartAndEnd_519)
{
    double x0 = 5.0, y0 = 5.0, r0 = 1.0;
    double x1 = 5.0, y1 = 5.0, r1 = 10.0;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), false, false);

    double ox0, oy0, or0, ox1, oy1, or1;
    shading.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    EXPECT_DOUBLE_EQ(ox0, 5.0);
    EXPECT_DOUBLE_EQ(oy0, 5.0);
    EXPECT_DOUBLE_EQ(or0, 1.0);
    EXPECT_DOUBLE_EQ(ox1, 5.0);
    EXPECT_DOUBLE_EQ(oy1, 5.0);
    EXPECT_DOUBLE_EQ(or1, 10.0);
}

// Test with extend flags set to true
TEST_F(GfxRadialShadingTest_519, GetCoordsWithExtendFlags_519)
{
    double x0 = 100.0, y0 = 200.0, r0 = 50.0;
    double x1 = 300.0, y1 = 400.0, r1 = 150.0;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), true, true);

    double ox0, oy0, or0, ox1, oy1, or1;
    shading.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    // Coordinates should be unchanged regardless of extend flags
    EXPECT_DOUBLE_EQ(ox0, 100.0);
    EXPECT_DOUBLE_EQ(oy0, 200.0);
    EXPECT_DOUBLE_EQ(or0, 50.0);
    EXPECT_DOUBLE_EQ(ox1, 300.0);
    EXPECT_DOUBLE_EQ(oy1, 400.0);
    EXPECT_DOUBLE_EQ(or1, 150.0);
}

// Test getCoords with fractional values
TEST_F(GfxRadialShadingTest_519, GetCoordsWithFractionalValues_519)
{
    double x0 = 0.123456789, y0 = 0.987654321, r0 = 0.111111111;
    double x1 = 0.222222222, y1 = 0.333333333, r1 = 0.444444444;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), false, false);

    double ox0, oy0, or0, ox1, oy1, or1;
    shading.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    EXPECT_DOUBLE_EQ(ox0, 0.123456789);
    EXPECT_DOUBLE_EQ(oy0, 0.987654321);
    EXPECT_DOUBLE_EQ(or0, 0.111111111);
    EXPECT_DOUBLE_EQ(ox1, 0.222222222);
    EXPECT_DOUBLE_EQ(oy1, 0.333333333);
    EXPECT_DOUBLE_EQ(or1, 0.444444444);
}

// Test that copy() preserves coordinates
TEST_F(GfxRadialShadingTest_519, CopyPreservesCoords_519)
{
    double x0 = 7.0, y0 = 8.0, r0 = 9.0;
    double x1 = 17.0, y1 = 18.0, r1 = 19.0;
    double t0 = 0.0, t1 = 1.0;

    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(funcs), false, false);

    auto copiedShading = shading.copy();
    ASSERT_NE(copiedShading, nullptr);

    GfxRadialShading *copiedRadial = dynamic_cast<GfxRadialShading *>(copiedShading.get());
    ASSERT_NE(copiedRadial, nullptr);

    double ox0, oy0, or0, ox1, oy1, or1;
    copiedRadial->getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);

    EXPECT_DOUBLE_EQ(ox0, 7.0);
    EXPECT_DOUBLE_EQ(oy0, 8.0);
    EXPECT_DOUBLE_EQ(or0, 9.0);
    EXPECT_DOUBLE_EQ(ox1, 17.0);
    EXPECT_DOUBLE_EQ(oy1, 18.0);
    EXPECT_DOUBLE_EQ(or1, 19.0);
}
