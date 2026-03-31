#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

// Since GfxShading has protected members and we need to test getBBox,
// we create a test subclass that allows us to set the protected bbox fields.
class TestableGfxShading : public GfxShading {
public:
    TestableGfxShading() : GfxShading(1) {}

    void setBBox(double xMin, double yMin, double xMax, double yMax) {
        bbox_xMin = xMin;
        bbox_yMin = yMin;
        bbox_xMax = xMax;
        bbox_yMax = yMax;
    }

    const std::unique_ptr<GfxShading> copy() override {
        return nullptr;
    }
};

class GfxShadingTest_506 : public ::testing::Test {
protected:
    void SetUp() override {
        shading = std::make_unique<TestableGfxShading>();
    }

    std::unique_ptr<TestableGfxShading> shading;
};

TEST_F(GfxShadingTest_506, GetBBoxReturnsSetValues_506) {
    shading->setBBox(1.0, 2.0, 3.0, 4.0);

    double xMin, yMin, xMax, yMax;
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 1.0);
    EXPECT_DOUBLE_EQ(yMin, 2.0);
    EXPECT_DOUBLE_EQ(xMax, 3.0);
    EXPECT_DOUBLE_EQ(yMax, 4.0);
}

TEST_F(GfxShadingTest_506, GetBBoxWithZeroValues_506) {
    shading->setBBox(0.0, 0.0, 0.0, 0.0);

    double xMin, yMin, xMax, yMax;
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 0.0);
    EXPECT_DOUBLE_EQ(yMin, 0.0);
    EXPECT_DOUBLE_EQ(xMax, 0.0);
    EXPECT_DOUBLE_EQ(yMax, 0.0);
}

TEST_F(GfxShadingTest_506, GetBBoxWithNegativeValues_506) {
    shading->setBBox(-10.5, -20.3, -1.0, -0.5);

    double xMin, yMin, xMax, yMax;
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, -10.5);
    EXPECT_DOUBLE_EQ(yMin, -20.3);
    EXPECT_DOUBLE_EQ(xMax, -1.0);
    EXPECT_DOUBLE_EQ(yMax, -0.5);
}

TEST_F(GfxShadingTest_506, GetBBoxWithLargeValues_506) {
    shading->setBBox(1e10, 1e15, 1e20, 1e25);

    double xMin, yMin, xMax, yMax;
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 1e10);
    EXPECT_DOUBLE_EQ(yMin, 1e15);
    EXPECT_DOUBLE_EQ(xMax, 1e20);
    EXPECT_DOUBLE_EQ(yMax, 1e25);
}

TEST_F(GfxShadingTest_506, GetBBoxWithVerySmallValues_506) {
    shading->setBBox(1e-300, 1e-300, 1e-300, 1e-300);

    double xMin, yMin, xMax, yMax;
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 1e-300);
    EXPECT_DOUBLE_EQ(yMin, 1e-300);
    EXPECT_DOUBLE_EQ(xMax, 1e-300);
    EXPECT_DOUBLE_EQ(yMax, 1e-300);
}

TEST_F(GfxShadingTest_506, GetBBoxWithMixedPositiveAndNegative_506) {
    shading->setBBox(-100.0, -200.0, 100.0, 200.0);

    double xMin, yMin, xMax, yMax;
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, -100.0);
    EXPECT_DOUBLE_EQ(yMin, -200.0);
    EXPECT_DOUBLE_EQ(xMax, 100.0);
    EXPECT_DOUBLE_EQ(yMax, 200.0);
}

TEST_F(GfxShadingTest_506, GetBBoxWithFractionalValues_506) {
    shading->setBBox(0.123456789, 0.987654321, 1.111111111, 2.222222222);

    double xMin, yMin, xMax, yMax;
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 0.123456789);
    EXPECT_DOUBLE_EQ(yMin, 0.987654321);
    EXPECT_DOUBLE_EQ(xMax, 1.111111111);
    EXPECT_DOUBLE_EQ(yMax, 2.222222222);
}

TEST_F(GfxShadingTest_506, GetBBoxCalledMultipleTimes_506) {
    shading->setBBox(5.0, 10.0, 15.0, 20.0);

    double xMin1, yMin1, xMax1, yMax1;
    shading->getBBox(&xMin1, &yMin1, &xMax1, &yMax1);

    double xMin2, yMin2, xMax2, yMax2;
    shading->getBBox(&xMin2, &yMin2, &xMax2, &yMax2);

    EXPECT_DOUBLE_EQ(xMin1, xMin2);
    EXPECT_DOUBLE_EQ(yMin1, yMin2);
    EXPECT_DOUBLE_EQ(xMax1, xMax2);
    EXPECT_DOUBLE_EQ(yMax1, yMax2);
}

TEST_F(GfxShadingTest_506, GetBBoxAfterUpdate_506) {
    shading->setBBox(1.0, 2.0, 3.0, 4.0);

    double xMin, yMin, xMax, yMax;
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 1.0);
    EXPECT_DOUBLE_EQ(yMin, 2.0);
    EXPECT_DOUBLE_EQ(xMax, 3.0);
    EXPECT_DOUBLE_EQ(yMax, 4.0);

    shading->setBBox(10.0, 20.0, 30.0, 40.0);
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 10.0);
    EXPECT_DOUBLE_EQ(yMin, 20.0);
    EXPECT_DOUBLE_EQ(xMax, 30.0);
    EXPECT_DOUBLE_EQ(yMax, 40.0);
}

TEST_F(GfxShadingTest_506, GetBBoxWithInfinity_506) {
    double inf = std::numeric_limits<double>::infinity();
    shading->setBBox(-inf, -inf, inf, inf);

    double xMin, yMin, xMax, yMax;
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_EQ(xMin, -inf);
    EXPECT_EQ(yMin, -inf);
    EXPECT_EQ(xMax, inf);
    EXPECT_EQ(yMax, inf);
}

TEST_F(GfxShadingTest_506, GetTypeReturnsCorrectType_506) {
    // The TestableGfxShading constructor passes type 1
    EXPECT_EQ(shading->getType(), static_cast<ShadingType>(1));
}
