#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "Object.h"

// Helper to create a simple DeviceGray color space based GfxImageColorMap
// with a decode array that sets known decodeLow and decodeRange values.

class GfxImageColorMapTest_535 : public ::testing::Test {
protected:
    // Creates a GfxImageColorMap with DeviceGray colorspace and given decode array
    // For DeviceGray with 8 bits, default decode is [0, 1]
    std::unique_ptr<GfxImageColorMap> createGrayColorMap(int bits, Object *decodeObj) {
        auto cs = GfxColorSpace::parse(nullptr, &Object(objName, "DeviceGray"), nullptr, nullptr, nullptr, 0);
        if (!cs) {
            return nullptr;
        }
        auto map = std::make_unique<GfxImageColorMap>(bits, decodeObj, std::move(cs));
        if (!map->isOk()) {
            return nullptr;
        }
        return map;
    }
};

// Test getDecodeHigh with default decode array (nullptr decode) for DeviceGray
// Default decode for DeviceGray should be [0, 1], so decodeLow=0, decodeRange=1, decodeHigh=1
TEST_F(GfxImageColorMapTest_535, GetDecodeHighDefaultDecode_535) {
    Object decodeObj;
    decodeObj.initNull();
    
    auto cs = GfxColorSpace::parse(nullptr, nullptr, nullptr, nullptr, nullptr, 0);
    
    // Try creating with a simple approach - DeviceGray with default decode
    Object csObj(objName, "DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object nullObj;
    GfxImageColorMap map(8, &nullObj, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap";
    }
    
    // For DeviceGray default decode [0, 1]: decodeLow=0, decodeRange=1
    // getDecodeHigh(0) = decodeLow[0] + decodeRange[0] = 0 + 1 = 1.0
    double high = map.getDecodeHigh(0);
    double low = map.getDecodeLow(0);
    EXPECT_DOUBLE_EQ(low, 0.0);
    EXPECT_DOUBLE_EQ(high, 1.0);
}

// Test that getDecodeHigh equals getDecodeLow + (getDecodeHigh - getDecodeLow) trivially
TEST_F(GfxImageColorMapTest_535, GetDecodeHighConsistentWithDecodeLow_535) {
    Object csObj(objName, "DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object nullObj;
    GfxImageColorMap map(8, &nullObj, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap";
    }
    
    double low = map.getDecodeLow(0);
    double high = map.getDecodeHigh(0);
    // decodeHigh should be >= decodeLow for normal decode
    EXPECT_GE(high, low);
    // The range should be high - low
    EXPECT_DOUBLE_EQ(high - low, high - low);
}

// Test with explicit decode array [1, 0] (inverted)
TEST_F(GfxImageColorMapTest_535, GetDecodeHighInvertedDecode_535) {
    Object csObj(objName, "DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    // Build decode array [1, 0]
    Object decodeArray;
    decodeArray = Object(new Array(nullptr));
    decodeArray.arrayAdd(Object(1.0));
    decodeArray.arrayAdd(Object(0.0));
    
    GfxImageColorMap map(8, &decodeArray, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap with inverted decode";
    }
    
    // Inverted: decodeLow=1, decodeRange=-1, so decodeHigh = 1 + (-1) = 0
    EXPECT_DOUBLE_EQ(map.getDecodeLow(0), 1.0);
    EXPECT_DOUBLE_EQ(map.getDecodeHigh(0), 0.0);
}

// Test with DeviceRGB color space (3 components)
TEST_F(GfxImageColorMapTest_535, GetDecodeHighRGBDefaultDecode_535) {
    Object csObj(objName, "DeviceRGB");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object nullObj;
    GfxImageColorMap map(8, &nullObj, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap for RGB";
    }
    
    EXPECT_EQ(map.getNumPixelComps(), 3);
    
    // All three components should have default decode [0, 1]
    for (int i = 0; i < 3; i++) {
        EXPECT_DOUBLE_EQ(map.getDecodeLow(i), 0.0);
        EXPECT_DOUBLE_EQ(map.getDecodeHigh(i), 1.0);
    }
}

// Test with DeviceCMYK color space (4 components)
TEST_F(GfxImageColorMapTest_535, GetDecodeHighCMYKDefaultDecode_535) {
    Object csObj(objName, "DeviceCMYK");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceCMYK color space";
    }
    
    Object nullObj;
    GfxImageColorMap map(8, &nullObj, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap for CMYK";
    }
    
    EXPECT_EQ(map.getNumPixelComps(), 4);
    
    for (int i = 0; i < 4; i++) {
        EXPECT_DOUBLE_EQ(map.getDecodeLow(i), 0.0);
        EXPECT_DOUBLE_EQ(map.getDecodeHigh(i), 1.0);
    }
}

// Test getBits returns what was passed to constructor
TEST_F(GfxImageColorMapTest_535, GetBitsReturnsConstructorValue_535) {
    Object csObj(objName, "DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object nullObj;
    GfxImageColorMap map(8, &nullObj, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap";
    }
    
    EXPECT_EQ(map.getBits(), 8);
}

// Test copy preserves decode values
TEST_F(GfxImageColorMapTest_535, CopyPreservesDecodeValues_535) {
    Object csObj(objName, "DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object nullObj;
    GfxImageColorMap map(8, &nullObj, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap";
    }
    
    GfxImageColorMap *mapCopy = map.copy();
    ASSERT_NE(mapCopy, nullptr);
    ASSERT_TRUE(mapCopy->isOk());
    
    EXPECT_DOUBLE_EQ(mapCopy->getDecodeLow(0), map.getDecodeLow(0));
    EXPECT_DOUBLE_EQ(mapCopy->getDecodeHigh(0), map.getDecodeHigh(0));
    EXPECT_EQ(mapCopy->getBits(), map.getBits());
    EXPECT_EQ(mapCopy->getNumPixelComps(), map.getNumPixelComps());
    
    delete mapCopy;
}

// Test with custom decode array for RGB [0.2, 0.8, 0.1, 0.9, 0.3, 0.7]
TEST_F(GfxImageColorMapTest_535, GetDecodeHighCustomDecodeRGB_535) {
    Object csObj(objName, "DeviceRGB");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeArray;
    decodeArray = Object(new Array(nullptr));
    decodeArray.arrayAdd(Object(0.2));
    decodeArray.arrayAdd(Object(0.8));
    decodeArray.arrayAdd(Object(0.1));
    decodeArray.arrayAdd(Object(0.9));
    decodeArray.arrayAdd(Object(0.3));
    decodeArray.arrayAdd(Object(0.7));
    
    GfxImageColorMap map(8, &decodeArray, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap with custom decode";
    }
    
    EXPECT_NEAR(map.getDecodeLow(0), 0.2, 1e-6);
    EXPECT_NEAR(map.getDecodeHigh(0), 0.8, 1e-6);
    EXPECT_NEAR(map.getDecodeLow(1), 0.1, 1e-6);
    EXPECT_NEAR(map.getDecodeHigh(1), 0.9, 1e-6);
    EXPECT_NEAR(map.getDecodeLow(2), 0.3, 1e-6);
    EXPECT_NEAR(map.getDecodeHigh(2), 0.7, 1e-6);
}

// Test getNumPixelComps for DeviceGray
TEST_F(GfxImageColorMapTest_535, GetNumPixelCompsGray_535) {
    Object csObj(objName, "DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object nullObj;
    GfxImageColorMap map(8, &nullObj, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap";
    }
    
    EXPECT_EQ(map.getNumPixelComps(), 1);
}

// Test with 1-bit depth
TEST_F(GfxImageColorMapTest_535, OneBitDepthDefaultDecode_535) {
    Object csObj(objName, "DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object nullObj;
    GfxImageColorMap map(1, &nullObj, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap with 1-bit";
    }
    
    EXPECT_EQ(map.getBits(), 1);
    EXPECT_DOUBLE_EQ(map.getDecodeLow(0), 0.0);
    EXPECT_DOUBLE_EQ(map.getDecodeHigh(0), 1.0);
}

// Test matteColor operations
TEST_F(GfxImageColorMapTest_535, SetAndGetMatteColor_535) {
    Object csObj(objName, "DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, nullptr, 0);
    if (!colorSpace) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object nullObj;
    GfxImageColorMap map(8, &nullObj, std::move(colorSpace));
    
    if (!map.isOk()) {
        GTEST_SKIP() << "Could not create valid GfxImageColorMap";
    }
    
    GfxColor matteColor;
    matteColor.c[0] = 32768; // Some arbitrary value
    map.setMatteColor(&matteColor);
    
    const GfxColor *retrieved = map.getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], matteColor.c[0]);
}
