#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "PreScanOutputDev.h"
#include "GfxState.h"
#include "GlobalParams.h"

class PreScanOutputDevTest_1656 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test construction with different PSLevel values
TEST_F(PreScanOutputDevTest_1656, ConstructWithPSLevel1_1656) {
    PreScanOutputDev dev(psLevel1);
    // After construction, default stats should indicate simplest case
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

TEST_F(PreScanOutputDevTest_1656, ConstructWithPSLevel2_1656) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

TEST_F(PreScanOutputDevTest_1656, ConstructWithPSLevel3_1656) {
    PreScanOutputDev dev(psLevel3);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test useDrawChar returns true
TEST_F(PreScanOutputDevTest_1656, UseDrawCharReturnsTrue_1656) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.useDrawChar());
}

// Test upsideDown
TEST_F(PreScanOutputDevTest_1656, UpsideDownReturnValue_1656) {
    PreScanOutputDev dev(psLevel1);
    // OutputDev typically returns true for upsideDown
    bool result = dev.upsideDown();
    EXPECT_TRUE(result);
}

// Test useTilingPatternFill
TEST_F(PreScanOutputDevTest_1656, UseTilingPatternFillReturnsTrue_1656) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// Test useShadedFills
TEST_F(PreScanOutputDevTest_1656, UseShadedFillsReturnsTrue_1656) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.useShadedFills(1));
    EXPECT_TRUE(dev.useShadedFills(2));
    EXPECT_TRUE(dev.useShadedFills(3));
}

// Test interpretType3Chars
TEST_F(PreScanOutputDevTest_1656, InterpretType3CharsReturnsTrue_1656) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.interpretType3Chars());
}

// Test clearStats resets all flags to defaults
TEST_F(PreScanOutputDevTest_1656, ClearStatsResetsFlags_1656) {
    PreScanOutputDev dev(psLevel1);
    dev.clearStats();
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test that after beginTransparencyGroup, transparency is detected
TEST_F(PreScanOutputDevTest_1656, BeginTransparencyGroupSetsTransparency_1656) {
    PreScanOutputDev dev(psLevel1);
    std::array<double, 4> bbox = {0, 0, 100, 100};
    dev.beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false);
    EXPECT_TRUE(dev.usesTransparency());
}

// Test stroke with a GfxState - creating a minimal state to test
TEST_F(PreScanOutputDevTest_1656, StrokeWithNullState_1656) {
    PreScanOutputDev dev(psLevel1);
    // We test that stroke doesn't crash with a valid state
    // Creating a minimal GfxState
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    dev.stroke(&state);
    // After stroke with default DeviceGray black, should still be mono and gray
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
}

// Test fill with a GfxState
TEST_F(PreScanOutputDevTest_1656, FillWithDefaultState_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    dev.fill(&state);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
}

// Test eoFill with a GfxState
TEST_F(PreScanOutputDevTest_1656, EoFillWithDefaultState_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    dev.eoFill(&state);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
}

// Test that fill with RGB color updates mono/gray flags
TEST_F(PreScanOutputDevTest_1656, FillWithRGBColorNotMono_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    
    // Set fill color to a non-gray RGB
    GfxColor color;
    color.c[0] = 65535; // R
    color.c[1] = 0;     // G
    color.c[2] = 0;     // B
    
    auto cs = GfxColorSpace::create(csDeviceRGB);
    state.setFillColorSpace(cs.get());
    state.setFillColor(&color);
    
    dev.fill(&state);
    
    // Should no longer be monochrome or gray since we used a red fill
    EXPECT_FALSE(dev.isMonochrome());
    EXPECT_FALSE(dev.isGray());
}

// Test that fill with gray color keeps gray but might not be mono
TEST_F(PreScanOutputDevTest_1656, FillWithGrayColor_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    
    GfxColor color;
    color.c[0] = 32768; // middle gray
    
    auto cs = GfxColorSpace::create(csDeviceGray);
    state.setFillColorSpace(cs.get());
    state.setFillColor(&color);
    
    dev.fill(&state);
    
    // Gray color should keep isGray true but not mono
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.isMonochrome());
}

// Test that transparency flag is set with non-1.0 opacity
TEST_F(PreScanOutputDevTest_1656, FillWithTransparency_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    
    state.setFillOpacity(0.5);
    dev.fill(&state);
    
    EXPECT_TRUE(dev.usesTransparency());
}

// Test startPage and endPage don't crash
TEST_F(PreScanOutputDevTest_1656, StartEndPageNoCrash_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    dev.startPage(1, &state, nullptr);
    dev.endPage();
}

// Test clip and eoClip don't crash
TEST_F(PreScanOutputDevTest_1656, ClipNoCrash_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    dev.clip(&state);
    dev.eoClip(&state);
}

// Test beginStringOp and endStringOp don't crash
TEST_F(PreScanOutputDevTest_1656, StringOpNoCrash_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    dev.beginStringOp(&state);
    dev.endStringOp(&state);
}

// Test that clearStats works after modifications
TEST_F(PreScanOutputDevTest_1656, ClearStatsAfterModification_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    
    // Trigger transparency
    state.setFillOpacity(0.5);
    dev.fill(&state);
    EXPECT_TRUE(dev.usesTransparency());
    
    // Clear and verify reset
    dev.clearStats();
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test paintTransparencyGroup sets transparency
TEST_F(PreScanOutputDevTest_1656, PaintTransparencyGroupSetsTransparency_1656) {
    PreScanOutputDev dev(psLevel1);
    std::array<double, 4> bbox = {0, 0, 100, 100};
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    dev.paintTransparencyGroup(&state, bbox);
    // paintTransparencyGroup should mark transparency
    EXPECT_TRUE(dev.usesTransparency());
}

// Test setSoftMask sets transparency
TEST_F(PreScanOutputDevTest_1656, SetSoftMaskSetsTransparency_1656) {
    PreScanOutputDev dev(psLevel1);
    std::array<double, 4> bbox = {0, 0, 100, 100};
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    dev.setSoftMask(&state, bbox, false, nullptr, nullptr);
    EXPECT_TRUE(dev.usesTransparency());
}

// Test endType3Char doesn't crash
TEST_F(PreScanOutputDevTest_1656, EndType3CharNoCrash_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    dev.endType3Char(&state);
}

// Test functionShadedFill
TEST_F(PreScanOutputDevTest_1656, FunctionShadedFillReturnValue_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    bool result = dev.functionShadedFill(&state, nullptr);
    // Should return true since PreScanOutputDev handles shaded fills
    EXPECT_TRUE(result);
}

// Test axialShadedFill
TEST_F(PreScanOutputDevTest_1656, AxialShadedFillReturnValue_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    bool result = dev.axialShadedFill(&state, nullptr, 0.0, 1.0);
    EXPECT_TRUE(result);
}

// Test radialShadedFill
TEST_F(PreScanOutputDevTest_1656, RadialShadedFillReturnValue_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    bool result = dev.radialShadedFill(&state, nullptr, 0.0, 1.0);
    EXPECT_TRUE(result);
}

// Test stroke with non-normal blend mode triggers transparency
TEST_F(PreScanOutputDevTest_1656, StrokeWithBlendModeSetsTransparency_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    
    state.setBlendMode(gfxBlendMultiply);
    dev.stroke(&state);
    
    EXPECT_TRUE(dev.usesTransparency());
}

// Test multiple clearStats calls
TEST_F(PreScanOutputDevTest_1656, MultipleClearStats_1656) {
    PreScanOutputDev dev(psLevel1);
    dev.clearStats();
    dev.clearStats();
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test monochrome with pure black (0) fill in DeviceGray
TEST_F(PreScanOutputDevTest_1656, FillWithBlackRemainsMono_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    
    GfxColor color;
    color.c[0] = 0; // black
    
    auto cs = GfxColorSpace::create(csDeviceGray);
    state.setFillColorSpace(cs.get());
    state.setFillColor(&color);
    
    dev.fill(&state);
    
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
}

// Test monochrome with pure white fill in DeviceGray
TEST_F(PreScanOutputDevTest_1656, FillWithWhiteRemainsMono_1656) {
    PreScanOutputDev dev(psLevel1);
    PDFRectangle box(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &box, 0, false);
    
    GfxColor color;
    color.c[0] = 65535; // white
    
    auto cs = GfxColorSpace::create(csDeviceGray);
    state.setFillColorSpace(cs.get());
    state.setFillColor(&color);
    
    dev.fill(&state);
    
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
}
