#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// We need to test GfxImageColorMap::getMatteColor() which depends on
// the internal state of useMatte and matteColor. Since we can only
// interact through the public interface, we use setMatteColor to set
// state and getMatteColor to observe it.

// Helper to create a valid GfxImageColorMap. We need a valid colorspace
// and decode object. DeviceGray is simplest.
static std::unique_ptr<GfxImageColorMap> createTestColorMap(int bits = 8) {
    // Create a DeviceGray color space
    auto cs = GfxColorSpace::parse(nullptr, &Object(objName, "DeviceGray"), nullptr, nullptr, nullptr, 0);
    if (!cs) {
        // Try alternate creation
        Object obj;
        obj = Object(objName, "DeviceGray");
        cs = GfxColorSpace::parse(nullptr, &obj, nullptr, nullptr, nullptr, 0);
    }
    
    Object decode;
    decode = Object(objNull);
    
    auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decode, std::move(cs));
    return colorMap;
}

class GfxImageColorMapTest_540 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that getMatteColor returns nullptr when no matte color has been set
TEST_F(GfxImageColorMapTest_540, GetMatteColorReturnsNullWhenNotSet_540) {
    Object csObj(objName, "DeviceGray");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Cannot create color space for testing";
    }
    
    Object decode(objNull);
    GfxImageColorMap colorMap(8, &decode, std::move(cs));
    
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    // Without calling setMatteColor, useMatte should be false
    const GfxColor *result = colorMap.getMatteColor();
    EXPECT_EQ(result, nullptr);
}

// Test that getMatteColor returns non-null after setMatteColor is called
TEST_F(GfxImageColorMapTest_540, GetMatteColorReturnsColorAfterSet_540) {
    Object csObj(objName, "DeviceGray");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Cannot create color space for testing";
    }
    
    Object decode(objNull);
    GfxImageColorMap colorMap(8, &decode, std::move(cs));
    
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    GfxColor matteColor;
    matteColor.c[0] = dblToCol(0.5);
    colorMap.setMatteColor(&matteColor);
    
    const GfxColor *result = colorMap.getMatteColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], matteColor.c[0]);
}

// Test that setMatteColor with a specific color and getMatteColor returns matching values
TEST_F(GfxImageColorMapTest_540, GetMatteColorReturnsCorrectValues_540) {
    Object csObj(objName, "DeviceGray");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Cannot create color space for testing";
    }
    
    Object decode(objNull);
    GfxImageColorMap colorMap(8, &decode, std::move(cs));
    
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    GfxColor matteColor;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        matteColor.c[i] = dblToCol((double)i / gfxColorMaxComps);
    }
    
    colorMap.setMatteColor(&matteColor);
    
    const GfxColor *result = colorMap.getMatteColor();
    ASSERT_NE(result, nullptr);
    
    // Check that at least the first component matches
    EXPECT_EQ(result->c[0], matteColor.c[0]);
}

// Test with zero matte color values
TEST_F(GfxImageColorMapTest_540, GetMatteColorWithZeroValues_540) {
    Object csObj(objName, "DeviceGray");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Cannot create color space for testing";
    }
    
    Object decode(objNull);
    GfxImageColorMap colorMap(8, &decode, std::move(cs));
    
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    GfxColor matteColor;
    memset(&matteColor, 0, sizeof(GfxColor));
    
    colorMap.setMatteColor(&matteColor);
    
    const GfxColor *result = colorMap.getMatteColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], 0);
}

// Test with maximum matte color values
TEST_F(GfxImageColorMapTest_540, GetMatteColorWithMaxValues_540) {
    Object csObj(objName, "DeviceGray");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Cannot create color space for testing";
    }
    
    Object decode(objNull);
    GfxImageColorMap colorMap(8, &decode, std::move(cs));
    
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    GfxColor matteColor;
    matteColor.c[0] = dblToCol(1.0);
    
    colorMap.setMatteColor(&matteColor);
    
    const GfxColor *result = colorMap.getMatteColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], dblToCol(1.0));
}

// Test const correctness - getMatteColor on const object
TEST_F(GfxImageColorMapTest_540, GetMatteColorConstCorrectness_540) {
    Object csObj(objName, "DeviceGray");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Cannot create color space for testing";
    }
    
    Object decode(objNull);
    GfxImageColorMap colorMap(8, &decode, std::move(cs));
    
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    const GfxImageColorMap &constRef = colorMap;
    
    // Should return nullptr when matte not set
    EXPECT_EQ(constRef.getMatteColor(), nullptr);
    
    GfxColor matteColor;
    matteColor.c[0] = dblToCol(0.75);
    colorMap.setMatteColor(&matteColor);
    
    // Now should return non-null through const reference
    const GfxColor *result = constRef.getMatteColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], dblToCol(0.75));
}
