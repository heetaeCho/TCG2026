#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "GfxState.h"
#include "Function.h"

class GfxAxialShadingTest_518 : public ::testing::Test {
protected:
    std::unique_ptr<GfxAxialShading> createShading(double x0, double y0, double x1, double y1) {
        std::vector<std::unique_ptr<Function>> funcs;
        return std::make_unique<GfxAxialShading>(x0, y0, x1, y1, 0.0, 1.0, std::move(funcs), false, false);
    }
};

TEST_F(GfxAxialShadingTest_518, GetCoordsReturnsConstructorValues_518) {
    auto shading = createShading(1.0, 2.0, 3.0, 4.0);
    double x0, y0, x1, y1;
    shading->getCoords(&x0, &y0, &x1, &y1);
    EXPECT_DOUBLE_EQ(x0, 1.0);
    EXPECT_DOUBLE_EQ(y0, 2.0);
    EXPECT_DOUBLE_EQ(x1, 3.0);
    EXPECT_DOUBLE_EQ(y1, 4.0);
}

TEST_F(GfxAxialShadingTest_518, GetCoordsWithZeroCoordinates_518) {
    auto shading = createShading(0.0, 0.0, 0.0, 0.0);
    double x0, y0, x1, y1;
    shading->getCoords(&x0, &y0, &x1, &y1);
    EXPECT_DOUBLE_EQ(x0, 0.0);
    EXPECT_DOUBLE_EQ(y0, 0.0);
    EXPECT_DOUBLE_EQ(x1, 0.0);
    EXPECT_DOUBLE_EQ(y1, 0.0);
}

TEST_F(GfxAxialShadingTest_518, GetCoordsWithNegativeCoordinates_518) {
    auto shading = createShading(-10.5, -20.3, -30.7, -40.9);
    double x0, y0, x1, y1;
    shading->getCoords(&x0, &y0, &x1, &y1);
    EXPECT_DOUBLE_EQ(x0, -10.5);
    EXPECT_DOUBLE_EQ(y0, -20.3);
    EXPECT_DOUBLE_EQ(x1, -30.7);
    EXPECT_DOUBLE_EQ(y1, -40.9);
}

TEST_F(GfxAxialShadingTest_518, GetCoordsWithLargeValues_518) {
    auto shading = createShading(1e15, 1e15, -1e15, -1e15);
    double x0, y0, x1, y1;
    shading->getCoords(&x0, &y0, &x1, &y1);
    EXPECT_DOUBLE_EQ(x0, 1e15);
    EXPECT_DOUBLE_EQ(y0, 1e15);
    EXPECT_DOUBLE_EQ(x1, -1e15);
    EXPECT_DOUBLE_EQ(y1, -1e15);
}

TEST_F(GfxAxialShadingTest_518, GetCoordsWithSmallFractionalValues_518) {
    auto shading = createShading(0.000001, 0.000002, 0.000003, 0.000004);
    double x0, y0, x1, y1;
    shading->getCoords(&x0, &y0, &x1, &y1);
    EXPECT_DOUBLE_EQ(x0, 0.000001);
    EXPECT_DOUBLE_EQ(y0, 0.000002);
    EXPECT_DOUBLE_EQ(x1, 0.000003);
    EXPECT_DOUBLE_EQ(y1, 0.000004);
}

TEST_F(GfxAxialShadingTest_518, GetCoordsWithMixedSignValues_518) {
    auto shading = createShading(-5.5, 10.2, 3.3, -7.8);
    double x0, y0, x1, y1;
    shading->getCoords(&x0, &y0, &x1, &y1);
    EXPECT_DOUBLE_EQ(x0, -5.5);
    EXPECT_DOUBLE_EQ(y0, 10.2);
    EXPECT_DOUBLE_EQ(x1, 3.3);
    EXPECT_DOUBLE_EQ(y1, -7.8);
}

TEST_F(GfxAxialShadingTest_518, CopyPreservesCoords_518) {
    auto shading = createShading(11.0, 22.0, 33.0, 44.0);
    auto copied = shading->copy();
    GfxAxialShading* copiedAxial = dynamic_cast<GfxAxialShading*>(copied.get());
    ASSERT_NE(copiedAxial, nullptr);
    double x0, y0, x1, y1;
    copiedAxial->getCoords(&x0, &y0, &x1, &y1);
    EXPECT_DOUBLE_EQ(x0, 11.0);
    EXPECT_DOUBLE_EQ(y0, 22.0);
    EXPECT_DOUBLE_EQ(x1, 33.0);
    EXPECT_DOUBLE_EQ(y1, 44.0);
}

TEST_F(GfxAxialShadingTest_518, CopyConstructorPreservesCoords_518) {
    auto shading = createShading(100.0, 200.0, 300.0, 400.0);
    GfxAxialShading copiedShading(shading.get());
    double x0, y0, x1, y1;
    copiedShading.getCoords(&x0, &y0, &x1, &y1);
    EXPECT_DOUBLE_EQ(x0, 100.0);
    EXPECT_DOUBLE_EQ(y0, 200.0);
    EXPECT_DOUBLE_EQ(x1, 300.0);
    EXPECT_DOUBLE_EQ(y1, 400.0);
}

TEST_F(GfxAxialShadingTest_518, GetCoordsCalledMultipleTimes_518) {
    auto shading = createShading(7.7, 8.8, 9.9, 10.10);
    for (int i = 0; i < 5; ++i) {
        double x0, y0, x1, y1;
        shading->getCoords(&x0, &y0, &x1, &y1);
        EXPECT_DOUBLE_EQ(x0, 7.7);
        EXPECT_DOUBLE_EQ(y0, 8.8);
        EXPECT_DOUBLE_EQ(x1, 9.9);
        EXPECT_DOUBLE_EQ(y1, 10.10);
    }
}

TEST_F(GfxAxialShadingTest_518, GetCoordsIdenticalStartAndEnd_518) {
    auto shading = createShading(5.5, 5.5, 5.5, 5.5);
    double x0, y0, x1, y1;
    shading->getCoords(&x0, &y0, &x1, &y1);
    EXPECT_DOUBLE_EQ(x0, 5.5);
    EXPECT_DOUBLE_EQ(y0, 5.5);
    EXPECT_DOUBLE_EQ(x1, 5.5);
    EXPECT_DOUBLE_EQ(y1, 5.5);
}
