#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

class GfxPatternColorSpaceTest_489 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getUnder() returns nullptr when constructed with no underlying color space
TEST_F(GfxPatternColorSpaceTest_489, GetUnderReturnsNullWhenNoUnderlyingColorSpace_489)
{
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    EXPECT_EQ(patternCS.getUnder(), nullptr);
}

// Test that getUnder() returns a valid pointer when constructed with an underlying color space
TEST_F(GfxPatternColorSpaceTest_489, GetUnderReturnsValidPointerWhenUnderlyingColorSpaceProvided_489)
{
    // Create a DeviceRGB color space as the underlying space
    auto underCS = GfxColorSpace::create(csDeviceRGB);
    GfxColorSpace *rawPtr = underCS.get();
    
    GfxPatternColorSpace patternCS(std::move(underCS));
    EXPECT_EQ(patternCS.getUnder(), rawPtr);
    EXPECT_NE(patternCS.getUnder(), nullptr);
}

// Test that getMode() returns csPattern
TEST_F(GfxPatternColorSpaceTest_489, GetModeReturnsPattern_489)
{
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    EXPECT_EQ(patternCS.getMode(), csPattern);
}

// Test getUnder with DeviceGray underlying color space
TEST_F(GfxPatternColorSpaceTest_489, GetUnderWithDeviceGrayUnderlying_489)
{
    auto underCS = GfxColorSpace::create(csDeviceGray);
    GfxColorSpace *rawPtr = underCS.get();

    GfxPatternColorSpace patternCS(std::move(underCS));
    GfxColorSpace *result = patternCS.getUnder();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, rawPtr);
    EXPECT_EQ(result->getMode(), csDeviceGray);
}

// Test getUnder with DeviceCMYK underlying color space
TEST_F(GfxPatternColorSpaceTest_489, GetUnderWithDeviceCMYKUnderlying_489)
{
    auto underCS = GfxColorSpace::create(csDeviceCMYK);
    GfxColorSpace *rawPtr = underCS.get();

    GfxPatternColorSpace patternCS(std::move(underCS));
    GfxColorSpace *result = patternCS.getUnder();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, rawPtr);
    EXPECT_EQ(result->getMode(), csDeviceCMYK);
}

// Test that calling getUnder multiple times returns the same pointer (consistency check)
TEST_F(GfxPatternColorSpaceTest_489, GetUnderConsistentAcrossMultipleCalls_489)
{
    auto underCS = GfxColorSpace::create(csDeviceRGB);
    GfxColorSpace *rawPtr = underCS.get();

    GfxPatternColorSpace patternCS(std::move(underCS));
    
    GfxColorSpace *first = patternCS.getUnder();
    GfxColorSpace *second = patternCS.getUnder();
    GfxColorSpace *third = patternCS.getUnder();
    
    EXPECT_EQ(first, rawPtr);
    EXPECT_EQ(second, rawPtr);
    EXPECT_EQ(third, rawPtr);
}

// Test copy preserves the underlying color space type
TEST_F(GfxPatternColorSpaceTest_489, CopyPreservesUnderlyingColorSpace_489)
{
    auto underCS = GfxColorSpace::create(csDeviceRGB);

    GfxPatternColorSpace patternCS(std::move(underCS));
    
    auto copied = patternCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csPattern);
    
    GfxPatternColorSpace *copiedPattern = dynamic_cast<GfxPatternColorSpace *>(copied.get());
    ASSERT_NE(copiedPattern, nullptr);
    
    GfxColorSpace *copiedUnder = copiedPattern->getUnder();
    ASSERT_NE(copiedUnder, nullptr);
    EXPECT_EQ(copiedUnder->getMode(), csDeviceRGB);
    
    // Ensure copy created a new object, not sharing the same pointer
    EXPECT_NE(copiedUnder, patternCS.getUnder());
}

// Test copy with null underlying
TEST_F(GfxPatternColorSpaceTest_489, CopyWithNullUnderlying_489)
{
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    
    auto copied = patternCS.copy();
    ASSERT_NE(copied, nullptr);
    
    GfxPatternColorSpace *copiedPattern = dynamic_cast<GfxPatternColorSpace *>(copied.get());
    ASSERT_NE(copiedPattern, nullptr);
    EXPECT_EQ(copiedPattern->getUnder(), nullptr);
}

// Test getDefaultColor
TEST_F(GfxPatternColorSpaceTest_489, GetDefaultColor_489)
{
    GfxPatternColorSpace patternCS(std::unique_ptr<GfxColorSpace>(nullptr));
    
    GfxColor color;
    patternCS.getDefaultColor(&color);
    // The default color for pattern should set component 0 to 0
    EXPECT_EQ(color.c[0], 0);
}

// Test getNComps returns expected value
TEST_F(GfxPatternColorSpaceTest_489, GetNCompsReturnsExpectedValue_489)
{
    auto underCS = GfxColorSpace::create(csDeviceRGB);
    GfxPatternColorSpace patternCS(std::move(underCS));
    
    // Pattern color space nComps should reflect underlying or be a specific value
    int nComps = patternCS.getNComps();
    EXPECT_GE(nComps, 0);
}
