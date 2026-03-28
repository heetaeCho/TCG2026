#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Test fixture for GfxPatternColorSpace
class GfxPatternColorSpaceTest_487 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getMode returns csPattern when constructed with nullptr (no underlying color space)
TEST_F(GfxPatternColorSpaceTest_487, GetModeReturnsCSPattern_487) {
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    EXPECT_EQ(patternCS.getMode(), csPattern);
}

// Test that getMode returns csPattern value which is 10
TEST_F(GfxPatternColorSpaceTest_487, GetModeReturnsCorrectEnumValue_487) {
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    EXPECT_EQ(static_cast<int>(patternCS.getMode()), 10);
}

// Test that getUnder returns nullptr when no underlying color space is provided
TEST_F(GfxPatternColorSpaceTest_487, GetUnderReturnsNullWhenNoUnder_487) {
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    EXPECT_EQ(patternCS.getUnder(), nullptr);
}

// Test that getUnder returns the underlying color space when one is provided
TEST_F(GfxPatternColorSpaceTest_487, GetUnderReturnsUnderlyingColorSpace_487) {
    auto deviceGray = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxColorSpace* rawPtr = deviceGray.get();
    GfxPatternColorSpace patternCS(std::move(deviceGray));
    EXPECT_EQ(patternCS.getUnder(), rawPtr);
}

// Test that getUnder's underlying color space has the correct mode
TEST_F(GfxPatternColorSpaceTest_487, GetUnderHasCorrectMode_487) {
    auto deviceRGB = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxPatternColorSpace patternCS(std::move(deviceRGB));
    ASSERT_NE(patternCS.getUnder(), nullptr);
    EXPECT_EQ(patternCS.getUnder()->getMode(), csDeviceRGB);
}

// Test getNComps returns expected value (should be related to the pattern color space)
TEST_F(GfxPatternColorSpaceTest_487, GetNCompsWithNoUnder_487) {
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    // Pattern color space with no underlying typically has a specific nComps
    int nComps = patternCS.getNComps();
    // getNComps should return some non-negative value
    EXPECT_GE(nComps, 0);
}

// Test getDefaultColor
TEST_F(GfxPatternColorSpaceTest_487, GetDefaultColor_487) {
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    GfxColor color;
    // Should not crash
    patternCS.getDefaultColor(&color);
}

// Test copy creates a valid copy
TEST_F(GfxPatternColorSpaceTest_487, CopyReturnsValidObject_487) {
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    auto copied = patternCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csPattern);
}

// Test copy preserves underlying color space
TEST_F(GfxPatternColorSpaceTest_487, CopyPreservesUnderlyingColorSpace_487) {
    auto deviceGray = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxPatternColorSpace patternCS(std::move(deviceGray));
    auto copied = patternCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csPattern);
    // The copied pattern should also have an underlying color space
    GfxPatternColorSpace* copiedPattern = dynamic_cast<GfxPatternColorSpace*>(copied.get());
    ASSERT_NE(copiedPattern, nullptr);
    ASSERT_NE(copiedPattern->getUnder(), nullptr);
    EXPECT_EQ(copiedPattern->getUnder()->getMode(), csDeviceGray);
}

// Test copy when no underlying color space
TEST_F(GfxPatternColorSpaceTest_487, CopyWithNoUnder_487) {
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    auto copied = patternCS.copy();
    ASSERT_NE(copied, nullptr);
    GfxPatternColorSpace* copiedPattern = dynamic_cast<GfxPatternColorSpace*>(copied.get());
    ASSERT_NE(copiedPattern, nullptr);
    EXPECT_EQ(copiedPattern->getUnder(), nullptr);
}

// Test getGray with underlying DeviceGray color space
TEST_F(GfxPatternColorSpaceTest_487, GetGrayWithUnder_487) {
    auto deviceGray = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxPatternColorSpace patternCS(std::move(deviceGray));
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    // Should not crash
    patternCS.getGray(&color, &gray);
}

// Test getRGB with underlying DeviceRGB color space
TEST_F(GfxPatternColorSpaceTest_487, GetRGBWithUnder_487) {
    auto deviceRGB = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxPatternColorSpace patternCS(std::move(deviceRGB));
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    // Should not crash
    patternCS.getRGB(&color, &rgb);
}

// Test getCMYK with underlying DeviceCMYK color space
TEST_F(GfxPatternColorSpaceTest_487, GetCMYKWithUnder_487) {
    auto deviceCMYK = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxPatternColorSpace patternCS(std::move(deviceCMYK));
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0;
    GfxCMYK cmyk;
    // Should not crash
    patternCS.getCMYK(&color, &cmyk);
}

// Test that csPattern enum value is 10
TEST_F(GfxPatternColorSpaceTest_487, CSPatternEnumValue_487) {
    EXPECT_EQ(csPattern, 10);
}

// Test getMode is const and consistent across multiple calls
TEST_F(GfxPatternColorSpaceTest_487, GetModeIsConsistent_487) {
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    EXPECT_EQ(patternCS.getMode(), csPattern);
    EXPECT_EQ(patternCS.getMode(), csPattern);
    EXPECT_EQ(patternCS.getMode(), patternCS.getMode());
}

// Test with DeviceCMYK as underlying
TEST_F(GfxPatternColorSpaceTest_487, WithDeviceCMYKUnder_487) {
    auto deviceCMYK = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxPatternColorSpace patternCS(std::move(deviceCMYK));
    EXPECT_EQ(patternCS.getMode(), csPattern);
    ASSERT_NE(patternCS.getUnder(), nullptr);
    EXPECT_EQ(patternCS.getUnder()->getMode(), csDeviceCMYK);
}
