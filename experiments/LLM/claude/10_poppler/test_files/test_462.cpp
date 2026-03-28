#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Test fixture for GfxICCBasedColorSpace
class GfxICCBasedColorSpaceTest_462 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getRef returns the iccProfileStream Ref that was set during construction
TEST_F(GfxICCBasedColorSpaceTest_462, GetRefReturnsProfileStreamRef_462) {
    // Create a Ref to use as the ICC profile stream reference
    Ref testRef = Ref::INVALID();
    
    // Create a simple alternate color space (DeviceGray with 1 component)
    auto altColorSpace = std::make_unique<GfxDeviceGrayColorSpace>();
    
    // Construct the ICCBased color space with 1 component
    GfxICCBasedColorSpace iccCS(1, std::move(altColorSpace), &testRef);
    
    Ref result = iccCS.getRef();
    EXPECT_EQ(result, testRef);
}

// Test getRef with a valid (non-invalid) Ref
TEST_F(GfxICCBasedColorSpaceTest_462, GetRefReturnsValidRef_462) {
    Ref testRef = {10, 0};
    
    auto altColorSpace = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccCS(1, std::move(altColorSpace), &testRef);
    
    Ref result = iccCS.getRef();
    EXPECT_EQ(result.num, 10);
    EXPECT_EQ(result.gen, 0);
}

// Test getRef with different ref values
TEST_F(GfxICCBasedColorSpaceTest_462, GetRefWithDifferentRefValues_462) {
    Ref testRef = {42, 5};
    
    auto altColorSpace = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccCS(3, std::move(altColorSpace), &testRef);
    
    Ref result = iccCS.getRef();
    EXPECT_EQ(result.num, 42);
    EXPECT_EQ(result.gen, 5);
}

// Test that getRef is consistent across multiple calls
TEST_F(GfxICCBasedColorSpaceTest_462, GetRefIsConsistentAcrossMultipleCalls_462) {
    Ref testRef = {100, 2};
    
    auto altColorSpace = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccCS(1, std::move(altColorSpace), &testRef);
    
    Ref result1 = iccCS.getRef();
    Ref result2 = iccCS.getRef();
    
    EXPECT_EQ(result1.num, result2.num);
    EXPECT_EQ(result1.gen, result2.gen);
}

// Test getRef after copying the color space
TEST_F(GfxICCBasedColorSpaceTest_462, GetRefAfterCopy_462) {
    Ref testRef = {55, 3};
    
    auto altColorSpace = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccCS(1, std::move(altColorSpace), &testRef);
    
    auto copied = iccCS.copyAsOwnType();
    ASSERT_NE(copied, nullptr);
    
    Ref originalRef = iccCS.getRef();
    Ref copiedRef = copied->getRef();
    
    EXPECT_EQ(originalRef.num, copiedRef.num);
    EXPECT_EQ(originalRef.gen, copiedRef.gen);
}

// Test getMode returns ICCBased
TEST_F(GfxICCBasedColorSpaceTest_462, GetModeReturnsICCBased_462) {
    Ref testRef = {1, 0};
    
    auto altColorSpace = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccCS(1, std::move(altColorSpace), &testRef);
    
    EXPECT_EQ(iccCS.getMode(), csICCBased);
}

// Test getNComps returns the number of components passed during construction
TEST_F(GfxICCBasedColorSpaceTest_462, GetNCompsReturnsCorrectValue_462) {
    Ref testRef = {1, 0};
    
    auto altColorSpace1 = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccCS1(1, std::move(altColorSpace1), &testRef);
    EXPECT_EQ(iccCS1.getNComps(), 1);
    
    auto altColorSpace3 = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccCS3(3, std::move(altColorSpace3), &testRef);
    EXPECT_EQ(iccCS3.getNComps(), 3);
    
    auto altColorSpace4 = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace iccCS4(4, std::move(altColorSpace4), &testRef);
    EXPECT_EQ(iccCS4.getNComps(), 4);
}

// Test getAlt returns a non-null alternate color space
TEST_F(GfxICCBasedColorSpaceTest_462, GetAltReturnsAlternateColorSpace_462) {
    Ref testRef = {1, 0};
    
    auto altColorSpace = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccCS(3, std::move(altColorSpace), &testRef);
    
    GfxColorSpace* alt = iccCS.getAlt();
    ASSERT_NE(alt, nullptr);
    EXPECT_EQ(alt->getMode(), csDeviceRGB);
}

// Test getDefaultColor sets color values
TEST_F(GfxICCBasedColorSpaceTest_462, GetDefaultColorSetsValues_462) {
    Ref testRef = {1, 0};
    
    auto altColorSpace = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccCS(1, std::move(altColorSpace), &testRef);
    
    GfxColor color;
    iccCS.getDefaultColor(&color);
    // The default color should be set; we just verify it doesn't crash
    // and produces some value
}

// Test with CMYK alternate (4 components)
TEST_F(GfxICCBasedColorSpaceTest_462, ConstructWithCMYKAlternate_462) {
    Ref testRef = {20, 1};
    
    auto altColorSpace = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace iccCS(4, std::move(altColorSpace), &testRef);
    
    EXPECT_EQ(iccCS.getNComps(), 4);
    EXPECT_EQ(iccCS.getMode(), csICCBased);
    
    Ref result = iccCS.getRef();
    EXPECT_EQ(result.num, 20);
    EXPECT_EQ(result.gen, 1);
}

// Test getRef with zero ref values
TEST_F(GfxICCBasedColorSpaceTest_462, GetRefWithZeroValues_462) {
    Ref testRef = {0, 0};
    
    auto altColorSpace = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccCS(1, std::move(altColorSpace), &testRef);
    
    Ref result = iccCS.getRef();
    EXPECT_EQ(result.num, 0);
    EXPECT_EQ(result.gen, 0);
}

// Test copy preserves all properties
TEST_F(GfxICCBasedColorSpaceTest_462, CopyPreservesProperties_462) {
    Ref testRef = {77, 8};
    
    auto altColorSpace = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccCS(3, std::move(altColorSpace), &testRef);
    
    auto copied = iccCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csICCBased);
    EXPECT_EQ(copied->getNComps(), 3);
}
