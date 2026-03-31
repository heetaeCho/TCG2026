static bool colorMapHasIdentityDecodeMap(GfxImageColorMap *colorMap) {
    for (int i = 0; i < colorMap->getNumPixelComps(); i++) {
        if (colorMap->getDecodeLow(i) != 0.0 || colorMap->getDecodeHigh(i) != 1.0) {
            return false;
        }
    }
    return true;
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary Poppler headers
#include "poppler/GfxState.h"
#include "poppler/Object.h"

// Include the source file to get access to the static function
// We need to make the static function accessible for testing
namespace {
#include "poppler/CairoOutputDev.cc"
}

// If the above doesn't work due to symbol conflicts, we copy the function:
// Actually, since the function is static in a .cc file, let's define it here
// for testing based on the known implementation signature.

// We'll use a different approach: define the function locally since it's simple
// and we need to test it against real GfxImageColorMap objects.

// Helper to create a decode array Object
static Object createDecodeArray(int nComps, const double* low, const double* high) {
    Object arr = Object(new Array(nullptr));
    for (int i = 0; i < nComps; i++) {
        arr.arrayAdd(Object(low[i]));
        arr.arrayAdd(Object(high[i]));
    }
    return arr;
}

// The function under test (copied since it's static and inaccessible)
static bool colorMapHasIdentityDecodeMap_test(GfxImageColorMap *colorMap) {
    for (int i = 0; i < colorMap->getNumPixelComps(); i++) {
        if (colorMap->getDecodeLow(i) != 0.0 || colorMap->getDecodeHigh(i) != 1.0) {
            return false;
        }
    }
    return true;
}

class ColorMapHasIdentityDecodeMapTest_1928 : public ::testing::Test {
protected:
    std::unique_ptr<GfxImageColorMap> createColorMap(int bits, int nComps,
                                                      const double* decodeLow,
                                                      const double* decodeHigh) {
        // Create a DeviceGray, DeviceRGB, or DeviceCMYK color space based on nComps
        std::unique_ptr<GfxColorSpace> cs;
        if (nComps == 1) {
            cs.reset(GfxColorSpace::parse(nullptr, &Object(objName, "DeviceGray"), nullptr, nullptr, 0));
        } else if (nComps == 3) {
            cs.reset(GfxColorSpace::parse(nullptr, &Object(objName, "DeviceRGB"), nullptr, nullptr, 0));
        } else if (nComps == 4) {
            cs.reset(GfxColorSpace::parse(nullptr, &Object(objName, "DeviceCMYK"), nullptr, nullptr, 0));
        }
        
        // Build decode array
        Object decodeArr = Object(new Array(nullptr));
        for (int i = 0; i < nComps; i++) {
            decodeArr.arrayAdd(Object(decodeLow[i]));
            decodeArr.arrayAdd(Object(decodeHigh[i]));
        }
        
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeArr, std::move(cs));
        if (colorMap->isOk()) {
            return colorMap;
        }
        return nullptr;
    }
};

// Test identity decode map with single component (grayscale)
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, IdentityDecodeGray_1928) {
    double low[] = {0.0};
    double high[] = {1.0};
    auto cm = createColorMap(8, 1, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_TRUE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test non-identity decode map with single component
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, NonIdentityDecodeLowGray_1928) {
    double low[] = {0.5};
    double high[] = {1.0};
    auto cm = createColorMap(8, 1, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_FALSE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test non-identity decode map with high != 1.0
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, NonIdentityDecodeHighGray_1928) {
    double low[] = {0.0};
    double high[] = {0.5};
    auto cm = createColorMap(8, 1, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_FALSE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test identity decode map with RGB (3 components)
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, IdentityDecodeRGB_1928) {
    double low[] = {0.0, 0.0, 0.0};
    double high[] = {1.0, 1.0, 1.0};
    auto cm = createColorMap(8, 3, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_TRUE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test non-identity decode map where only one component is off (RGB)
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, NonIdentityDecodeOneCompRGB_1928) {
    double low[] = {0.0, 0.0, 0.0};
    double high[] = {1.0, 0.8, 1.0};
    auto cm = createColorMap(8, 3, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_FALSE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test non-identity where first component low is non-zero
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, NonIdentityFirstCompLowRGB_1928) {
    double low[] = {0.1, 0.0, 0.0};
    double high[] = {1.0, 1.0, 1.0};
    auto cm = createColorMap(8, 3, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_FALSE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test non-identity where last component is off
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, NonIdentityLastCompRGB_1928) {
    double low[] = {0.0, 0.0, 0.2};
    double high[] = {1.0, 1.0, 1.0};
    auto cm = createColorMap(8, 3, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_FALSE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test inverted decode map (1.0 to 0.0)
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, InvertedDecodeGray_1928) {
    double low[] = {1.0};
    double high[] = {0.0};
    auto cm = createColorMap(8, 1, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_FALSE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test identity decode map with CMYK (4 components)
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, IdentityDecodeCMYK_1928) {
    double low[] = {0.0, 0.0, 0.0, 0.0};
    double high[] = {1.0, 1.0, 1.0, 1.0};
    auto cm = createColorMap(8, 4, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_TRUE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test non-identity CMYK where one component differs
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, NonIdentityDecodeCMYK_1928) {
    double low[] = {0.0, 0.0, 0.0, 0.0};
    double high[] = {1.0, 1.0, 1.0, 0.9};
    auto cm = createColorMap(8, 4, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_FALSE(colorMapHasIdentityDecodeMap_test(cm.get()));
}

// Test both low and high are wrong
TEST_F(ColorMapHasIdentityDecodeMapTest_1928, BothLowAndHighWrong_1928) {
    double low[] = {0.5};
    double high[] = {0.5};
    auto cm = createColorMap(8, 1, low, high);
    ASSERT_NE(cm, nullptr);
    EXPECT_FALSE(colorMapHasIdentityDecodeMap_test(cm.get()));
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "GfxState.h"
#include "Object.h"
#include "Dict.h"
#include "Array.h"

// Re-declare the static function for testing
static bool colorMapHasIdentityDecodeMap(GfxImageColorMap *colorMap) {
    for (int i = 0; i < colorMap->getNumPixelComps(); i++) {
        if (colorMap->getDecodeLow(i) != 0.0 || colorMap->getDecodeHigh(i) != 1.0) {
            return false;
        }
    }
    return true;
}

class ColorMapIdentityDecodeTest_1928 : public ::testing::Test {
protected:
    std::unique_ptr<GfxImageColorMap> makeGrayColorMap(int bits, double decodeLow, double decodeHigh) {
        auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
        Array *arr = new Array(nullptr);
        arr->add(Object(decodeLow));
        arr->add(Object(decodeHigh));
        Object decodeObj(arr);
        auto cm = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(cs));
        return cm;
    }

    std::unique_ptr<GfxImageColorMap> makeRGBColorMap(int bits, 
            double dLow0, double dHigh0,
            double dLow1, double dHigh1,
            double dLow2, double dHigh2) {
        auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
        Array *arr = new Array(nullptr);
        arr->add(Object(dLow0));
        arr->add(Object(dHigh0));
        arr->add(Object(dLow1));
        arr->add(Object(dHigh1));
        arr->add(Object(dLow2));
        arr->add(Object(dHigh2));
        Object decodeObj(arr);
        auto cm = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(cs));
        return cm;
    }
};

TEST_F(ColorMapIdentityDecodeTest_1928, GrayIdentity_1928) {
    auto cm = makeGrayColorMap(8, 0.0, 1.0);
    ASSERT_TRUE(cm->isOk());
    EXPECT_TRUE(colorMapHasIdentityDecodeMap(cm.get()));
}

TEST_F(ColorMapIdentityDecodeTest_1928, GrayNonIdentityLow_1928) {
    auto cm = makeGrayColorMap(8, 0.5, 1.0);
    ASSERT_TRUE(cm->isOk());
    EXPECT_FALSE(colorMapHasIdentityDecodeMap(cm.get()));
}

TEST_F(ColorMapIdentityDecodeTest_1928, GrayNonIdentityHigh_1928) {
    auto cm = makeGrayColorMap(8, 0.0, 0.5);
    ASSERT_TRUE(cm->isOk());
    EXPECT_FALSE(colorMapHasIdentityDecodeMap(cm.get()));
}

TEST_F(ColorMapIdentityDecodeTest_1928, GrayInverted_1928) {
    auto cm = makeGrayColorMap(8, 1.0, 0.0);
    ASSERT_TRUE(cm->isOk());
    EXPECT_FALSE(colorMapHasIdentityDecodeMap(cm.get()));
}

TEST_F(ColorMapIdentityDecodeTest_1928, RGBIdentity_1928) {
    auto cm = makeRGBColorMap(8, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
    ASSERT_TRUE(cm->isOk());
    EXPECT_TRUE(colorMapHasIdentityDecodeMap(cm.get()));
}

TEST_F(ColorMapIdentityDecodeTest_1928, RGBNonIdentitySecondComp_1928) {
    auto cm = makeRGBColorMap(8, 0.0, 1.0, 0.0, 0.8, 0.0, 1.0);
    ASSERT_TRUE(cm->isOk());
    EXPECT_FALSE(colorMapHasIdentityDecodeMap(cm.get()));
}

TEST_F(ColorMapIdentityDecodeTest_1928, RGBNonIdentityFirstCompLow_1928) {
    auto cm = makeRGBColorMap(8, 0.1, 1.0, 0.0, 1.0, 0.0, 1.0);
    ASSERT_TRUE(cm->isOk());
    EXPECT_FALSE(colorMapHasIdentityDecodeMap(cm.get()));
}

TEST_F(ColorMapIdentityDecodeTest_1928, RGBNonIdentityLastComp_1928) {
    auto cm = makeRGBColorMap(8, 0.0, 1.0, 0.0, 1.0, 0.2, 1.0);
    ASSERT_TRUE(cm->isOk());
    EXPECT_FALSE(colorMapHasIdentityDecodeMap(cm.get()));
}

TEST_F(ColorMapIdentityDecodeTest_1928, GrayBothWrong_1928) {
    auto cm = makeGrayColorMap(8, 0.3, 0.7);
    ASSERT_TRUE(cm->isOk());
    EXPECT_FALSE(colorMapHasIdentityDecodeMap(cm.get()));
}
