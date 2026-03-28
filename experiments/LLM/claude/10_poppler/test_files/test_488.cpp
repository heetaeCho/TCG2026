#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

class GfxPatternColorSpaceTest_488 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getNComps returns 0 for GfxPatternColorSpace without underlying color space
TEST_F(GfxPatternColorSpaceTest_488, GetNCompsReturnsZero_488) {
    GfxPatternColorSpace patternCS(nullptr);
    EXPECT_EQ(patternCS.getNComps(), 0);
}

// Test that getMode returns the correct mode for pattern color space
TEST_F(GfxPatternColorSpaceTest_488, GetModeReturnsPattern_488) {
    GfxPatternColorSpace patternCS(nullptr);
    EXPECT_EQ(patternCS.getMode(), csPattern);
}

// Test that getUnder returns nullptr when no underlying color space is set
TEST_F(GfxPatternColorSpaceTest_488, GetUnderReturnsNullWhenNoUnder_488) {
    GfxPatternColorSpace patternCS(nullptr);
    EXPECT_EQ(patternCS.getUnder(), nullptr);
}

// Test that getUnder returns a valid pointer when an underlying color space is provided
TEST_F(GfxPatternColorSpaceTest_488, GetUnderReturnsValidPointerWhenUnderSet_488) {
    auto underCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxColorSpace* rawPtr = underCS.get();
    GfxPatternColorSpace patternCS(std::move(underCS));
    EXPECT_EQ(patternCS.getUnder(), rawPtr);
}

// Test that getNComps still returns 0 even with an underlying color space
TEST_F(GfxPatternColorSpaceTest_488, GetNCompsReturnsZeroWithUnder_488) {
    auto underCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxPatternColorSpace patternCS(std::move(underCS));
    EXPECT_EQ(patternCS.getNComps(), 0);
}

// Test getDefaultColor sets color component to 0
TEST_F(GfxPatternColorSpaceTest_488, GetDefaultColorSetsToZero_488) {
    GfxPatternColorSpace patternCS(nullptr);
    GfxColor color;
    // Initialize to non-zero to verify it gets set
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = 12345;
    }
    patternCS.getDefaultColor(&color);
    // Pattern color space with 0 components, first component should be set to 0
    EXPECT_EQ(color.c[0], 0);
}

// Test copy creates a valid copy
TEST_F(GfxPatternColorSpaceTest_488, CopyCreatesValidCopy_488) {
    GfxPatternColorSpace patternCS(nullptr);
    auto copied = patternCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csPattern);
    EXPECT_EQ(copied->getNComps(), 0);
}

// Test copy with underlying color space
TEST_F(GfxPatternColorSpaceTest_488, CopyWithUnderPreservesUnder_488) {
    auto underCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxPatternColorSpace patternCS(std::move(underCS));
    auto copied = patternCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csPattern);
    
    // Cast to GfxPatternColorSpace to check under
    GfxPatternColorSpace* copiedPattern = dynamic_cast<GfxPatternColorSpace*>(copied.get());
    ASSERT_NE(copiedPattern, nullptr);
    EXPECT_NE(copiedPattern->getUnder(), nullptr);
}

// Test getGray with underlying color space
TEST_F(GfxPatternColorSpaceTest_488, GetGrayWithUnder_488) {
    auto underCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxPatternColorSpace patternCS(std::move(underCS));
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    patternCS.getGray(&color, &gray);
    // Black RGB should produce black gray
    EXPECT_EQ(gray, 0);
}

// Test getRGB with underlying color space
TEST_F(GfxPatternColorSpaceTest_488, GetRGBWithUnder_488) {
    auto underCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxPatternColorSpace patternCS(std::move(underCS));
    GfxColor color;
    color.c[0] = 65535; // max value for R
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    patternCS.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 65535);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getCMYK with underlying color space
TEST_F(GfxPatternColorSpaceTest_488, GetCMYKWithUnder_488) {
    auto underCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxPatternColorSpace patternCS(std::move(underCS));
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxCMYK cmyk;
    patternCS.getCMYK(&color, &cmyk);
    // Black RGB should map to K=1 in CMYK
    EXPECT_EQ(cmyk.k, 65535);
}

// Test that mode is csPattern
TEST_F(GfxPatternColorSpaceTest_488, ModeIsPattern_488) {
    auto underCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxPatternColorSpace patternCS(std::move(underCS));
    EXPECT_EQ(patternCS.getMode(), csPattern);
}
