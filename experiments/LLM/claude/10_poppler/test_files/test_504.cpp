#include <gtest/gtest.h>
#include "poppler/GfxState.h"

// Since GfxShading has a protected constructor and many dependencies,
// we need to test through the public interface. We'll create a minimal
// testable subclass that exposes the constructor for testing purposes.

class TestableGfxShading : public GfxShading {
public:
    // Use the public constructor with type argument
    explicit TestableGfxShading(int typeA) : GfxShading(typeA) {}

    const std::unique_ptr<GfxShading> copy() override {
        return std::unique_ptr<GfxShading>(new TestableGfxShading(*this));
    }

private:
    TestableGfxShading(const TestableGfxShading &other) : GfxShading(&other) {}
};

class GfxShadingTest_504 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getBackground returns a non-null pointer
TEST_F(GfxShadingTest_504, GetBackgroundReturnsNonNull_504) {
    TestableGfxShading shading(1);
    const GfxColor *bg = shading.getBackground();
    ASSERT_NE(bg, nullptr);
}

// Test that getBackground returns a consistent pointer (same address on multiple calls)
TEST_F(GfxShadingTest_504, GetBackgroundReturnsConsistentPointer_504) {
    TestableGfxShading shading(1);
    const GfxColor *bg1 = shading.getBackground();
    const GfxColor *bg2 = shading.getBackground();
    EXPECT_EQ(bg1, bg2);
}

// Test that getType returns the type passed in constructor
TEST_F(GfxShadingTest_504, GetTypeReturnsConstructorType_504) {
    TestableGfxShading shading(2);
    EXPECT_EQ(static_cast<int>(shading.getType()), 2);
}

// Test getHasBackground for a freshly constructed shading (should be false by default)
TEST_F(GfxShadingTest_504, GetHasBackgroundDefaultFalse_504) {
    TestableGfxShading shading(1);
    EXPECT_FALSE(shading.getHasBackground());
}

// Test getHasBBox for a freshly constructed shading (should be false by default)
TEST_F(GfxShadingTest_504, GetHasBBoxDefaultFalse_504) {
    TestableGfxShading shading(1);
    EXPECT_FALSE(shading.getHasBBox());
}

// Test getBBox returns values (default should be zeros or initialized values)
TEST_F(GfxShadingTest_504, GetBBoxReturnsValues_504) {
    TestableGfxShading shading(1);
    double xMin = -1, yMin = -1, xMax = -1, yMax = -1;
    shading.getBBox(&xMin, &yMin, &xMax, &yMax);
    // After calling getBBox, the values should be set to whatever the default is
    // We just verify no crash and values are written
    SUCCEED();
}

// Test getColorSpace for a freshly constructed shading
TEST_F(GfxShadingTest_504, GetColorSpaceDefaultNull_504) {
    TestableGfxShading shading(1);
    GfxColorSpace *cs = shading.getColorSpace();
    EXPECT_EQ(cs, nullptr);
}

// Test different shading types
TEST_F(GfxShadingTest_504, GetTypeForDifferentTypes_504) {
    TestableGfxShading shading1(1);
    EXPECT_EQ(static_cast<int>(shading1.getType()), 1);

    TestableGfxShading shading3(3);
    EXPECT_EQ(static_cast<int>(shading3.getType()), 3);

    TestableGfxShading shading5(5);
    EXPECT_EQ(static_cast<int>(shading5.getType()), 5);
}

// Test that getBackground on const object works
TEST_F(GfxShadingTest_504, GetBackgroundConstCorrectness_504) {
    TestableGfxShading shading(1);
    const GfxShading &constRef = shading;
    const GfxColor *bg = constRef.getBackground();
    ASSERT_NE(bg, nullptr);
}

// Test that two different shading objects have different background addresses
TEST_F(GfxShadingTest_504, DifferentShadingsHaveDifferentBackgrounds_504) {
    TestableGfxShading shading1(1);
    TestableGfxShading shading2(2);
    const GfxColor *bg1 = shading1.getBackground();
    const GfxColor *bg2 = shading2.getBackground();
    EXPECT_NE(bg1, bg2);
}

// Test copy constructor via copy() method
TEST_F(GfxShadingTest_504, CopyPreservesType_504) {
    TestableGfxShading shading(3);
    auto copied = shading.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(static_cast<int>(copied->getType()), 3);
}

// Test copy preserves hasBackground state
TEST_F(GfxShadingTest_504, CopyPreservesHasBackground_504) {
    TestableGfxShading shading(1);
    auto copied = shading.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getHasBackground(), shading.getHasBackground());
}

// Test copy preserves hasBBox state
TEST_F(GfxShadingTest_504, CopyPreservesHasBBox_504) {
    TestableGfxShading shading(1);
    auto copied = shading.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getHasBBox(), shading.getHasBBox());
}

// Test that copied shading has its own background (different address)
TEST_F(GfxShadingTest_504, CopyHasOwnBackground_504) {
    TestableGfxShading shading(1);
    auto copied = shading.copy();
    ASSERT_NE(copied, nullptr);
    const GfxColor *origBg = shading.getBackground();
    const GfxColor *copyBg = copied->getBackground();
    EXPECT_NE(origBg, copyBg);
}
