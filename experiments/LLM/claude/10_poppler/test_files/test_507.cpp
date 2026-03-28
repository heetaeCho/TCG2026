#include <gtest/gtest.h>
#include "GfxState.h"

// Since GfxShading has protected members and we can't directly construct
// instances easily without the full implementation, we create a test
// subclass that allows us to set the protected members for testing purposes.
class TestableGfxShading : public GfxShading {
public:
    // Use the constructor that takes an int (ShadingType)
    TestableGfxShading(int typeA) : GfxShading(typeA) {}

    // Expose setters for protected members we need to test
    void setHasBBox(bool val) { hasBBox = val; }
    void setHasBackground(bool val) { hasBackground = val; }
    void setBBox(double xMin, double yMin, double xMax, double yMax) {
        bbox_xMin = xMin;
        bbox_yMin = yMin;
        bbox_xMax = xMax;
        bbox_yMax = yMax;
    }

    // Override pure/virtual methods if needed
    const std::unique_ptr<GfxShading> copy() override {
        return std::unique_ptr<GfxShading>(nullptr);
    }
};

class GfxShadingTest_507 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getHasBBox returns false when hasBBox is false
TEST_F(GfxShadingTest_507, GetHasBBoxReturnsFalseWhenNotSet_507) {
    TestableGfxShading shading(1);
    shading.setHasBBox(false);
    EXPECT_FALSE(shading.getHasBBox());
}

// Test that getHasBBox returns true when hasBBox is true
TEST_F(GfxShadingTest_507, GetHasBBoxReturnsTrueWhenSet_507) {
    TestableGfxShading shading(1);
    shading.setHasBBox(true);
    EXPECT_TRUE(shading.getHasBBox());
}

// Test that getHasBackground returns false when not set
TEST_F(GfxShadingTest_507, GetHasBackgroundReturnsFalseWhenNotSet_507) {
    TestableGfxShading shading(1);
    shading.setHasBackground(false);
    EXPECT_FALSE(shading.getHasBackground());
}

// Test that getHasBackground returns true when set
TEST_F(GfxShadingTest_507, GetHasBackgroundReturnsTrueWhenSet_507) {
    TestableGfxShading shading(1);
    shading.setHasBackground(true);
    EXPECT_TRUE(shading.getHasBackground());
}

// Test getType returns the type passed in constructor
TEST_F(GfxShadingTest_507, GetTypeReturnsConstructorType_507) {
    TestableGfxShading shading(2);
    EXPECT_EQ(static_cast<int>(shading.getType()), 2);
}

// Test getBBox returns the correct bounding box values
TEST_F(GfxShadingTest_507, GetBBoxReturnsCorrectValues_507) {
    TestableGfxShading shading(1);
    shading.setHasBBox(true);
    shading.setBBox(1.0, 2.0, 3.0, 4.0);

    double xMin, yMin, xMax, yMax;
    shading.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 1.0);
    EXPECT_DOUBLE_EQ(yMin, 2.0);
    EXPECT_DOUBLE_EQ(xMax, 3.0);
    EXPECT_DOUBLE_EQ(yMax, 4.0);
}

// Test getBBox with zero-area bounding box
TEST_F(GfxShadingTest_507, GetBBoxZeroArea_507) {
    TestableGfxShading shading(1);
    shading.setHasBBox(true);
    shading.setBBox(0.0, 0.0, 0.0, 0.0);

    double xMin, yMin, xMax, yMax;
    shading.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 0.0);
    EXPECT_DOUBLE_EQ(yMin, 0.0);
    EXPECT_DOUBLE_EQ(xMax, 0.0);
    EXPECT_DOUBLE_EQ(yMax, 0.0);
}

// Test getBBox with negative coordinate values
TEST_F(GfxShadingTest_507, GetBBoxNegativeCoordinates_507) {
    TestableGfxShading shading(1);
    shading.setHasBBox(true);
    shading.setBBox(-10.5, -20.3, -1.0, -0.5);

    double xMin, yMin, xMax, yMax;
    shading.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, -10.5);
    EXPECT_DOUBLE_EQ(yMin, -20.3);
    EXPECT_DOUBLE_EQ(xMax, -1.0);
    EXPECT_DOUBLE_EQ(yMax, -0.5);
}

// Test toggling hasBBox from true to false
TEST_F(GfxShadingTest_507, GetHasBBoxToggle_507) {
    TestableGfxShading shading(1);
    shading.setHasBBox(true);
    EXPECT_TRUE(shading.getHasBBox());

    shading.setHasBBox(false);
    EXPECT_FALSE(shading.getHasBBox());
}

// Test that getColorSpace returns nullptr initially (no colorspace set)
TEST_F(GfxShadingTest_507, GetColorSpaceInitiallyNull_507) {
    TestableGfxShading shading(1);
    EXPECT_EQ(shading.getColorSpace(), nullptr);
}

// Test different shading types
TEST_F(GfxShadingTest_507, GetTypeDifferentShadingTypes_507) {
    for (int i = 1; i <= 7; ++i) {
        TestableGfxShading shading(i);
        EXPECT_EQ(static_cast<int>(shading.getType()), i);
    }
}

// Test getBBox with very large values
TEST_F(GfxShadingTest_507, GetBBoxLargeValues_507) {
    TestableGfxShading shading(1);
    shading.setHasBBox(true);
    shading.setBBox(1e10, 1e10, 1e15, 1e15);

    double xMin, yMin, xMax, yMax;
    shading.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 1e10);
    EXPECT_DOUBLE_EQ(yMin, 1e10);
    EXPECT_DOUBLE_EQ(xMax, 1e15);
    EXPECT_DOUBLE_EQ(yMax, 1e15);
}

// Test getBackground returns a non-null pointer
TEST_F(GfxShadingTest_507, GetBackgroundReturnsNonNull_507) {
    TestableGfxShading shading(1);
    const GfxColor *bg = shading.getBackground();
    EXPECT_NE(bg, nullptr);
}
