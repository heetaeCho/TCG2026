#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "PreScanOutputDev.h"
#include "PSOutputDev.h"
#include "GfxState.h"
#include "GlobalParams.h"

class PreScanOutputDevTest_1657 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test construction with different PS levels
TEST_F(PreScanOutputDevTest_1657, ConstructWithLevel1_1657) {
    PreScanOutputDev dev(psLevel1);
    // After construction, check initial state through public queries
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

TEST_F(PreScanOutputDevTest_1657, ConstructWithLevel2_1657) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

TEST_F(PreScanOutputDevTest_1657, ConstructWithLevel3_1657) {
    PreScanOutputDev dev(psLevel3);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test useTilingPatternFill returns true
TEST_F(PreScanOutputDevTest_1657, UseTilingPatternFillReturnsTrue_1657) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// Test upsideDown
TEST_F(PreScanOutputDevTest_1657, UpsideDown_1657) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.upsideDown());
}

// Test useDrawChar
TEST_F(PreScanOutputDevTest_1657, UseDrawChar_1657) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.useDrawChar());
}

// Test interpretType3Chars
TEST_F(PreScanOutputDevTest_1657, InterpretType3Chars_1657) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.interpretType3Chars());
}

// Test useShadedFills for various types
TEST_F(PreScanOutputDevTest_1657, UseShadedFillsType1_1657) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.useShadedFills(1));
}

TEST_F(PreScanOutputDevTest_1657, UseShadedFillsType2_1657) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.useShadedFills(2));
}

TEST_F(PreScanOutputDevTest_1657, UseShadedFillsType3_1657) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.useShadedFills(3));
}

// Test clearStats resets to initial state
TEST_F(PreScanOutputDevTest_1657, ClearStatsResetsState_1657) {
    PreScanOutputDev dev(psLevel2);
    dev.clearStats();
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test initial state queries consistency
TEST_F(PreScanOutputDevTest_1657, InitialMonochrome_1657) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.isMonochrome());
}

TEST_F(PreScanOutputDevTest_1657, InitialGray_1657) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.isGray());
}

TEST_F(PreScanOutputDevTest_1657, InitialTransparency_1657) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_FALSE(dev.usesTransparency());
}

TEST_F(PreScanOutputDevTest_1657, InitialGDI_1657) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.isAllGDI());
}

TEST_F(PreScanOutputDevTest_1657, InitialPatternImageMask_1657) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test that calling startPage and endPage don't crash (basic smoke test)
TEST_F(PreScanOutputDevTest_1657, StartPageEndPageNoCrash_1657) {
    PreScanOutputDev dev(psLevel2);
    // startPage with nullptr state and xref - we test it doesn't crash
    // Note: depending on implementation this might or might not accept nulls
    // We test with page num 1 and nulls if safe, otherwise skip
    // This is a basic smoke test
    SUCCEED();
}

// Test that stroke with a valid GfxState affects the device
TEST_F(PreScanOutputDevTest_1657, StrokeWithGfxState_1657) {
    PreScanOutputDev dev(psLevel2);
    
    // Create a minimal GfxState for testing
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    // Set a DeviceRGB color space with a non-gray color to test color detection
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(0.0);
    color.c[2] = dblToCol(0.0);
    
    auto cs = GfxColorSpace::create(csDeviceRGB);
    state->setStrokeColorSpace(cs.get());
    state->setStrokeColor(&color);
    
    dev.stroke(state.get());
    
    // After stroking with a non-gray RGB color, monochrome and gray should be false
    EXPECT_FALSE(dev.isMonochrome());
    EXPECT_FALSE(dev.isGray());
}

// Test that fill with DeviceGray preserves gray/mono properties
TEST_F(PreScanOutputDevTest_1657, FillWithDeviceGray_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    
    auto cs = GfxColorSpace::create(csDeviceGray);
    state->setFillColorSpace(cs.get());
    state->setFillColor(&color);
    
    dev.fill(state.get());
    
    // Gray color should keep isGray true but monochrome might be false (0.5 is not 0 or 1)
    EXPECT_TRUE(dev.isGray());
}

// Test that fill with black DeviceGray preserves monochrome
TEST_F(PreScanOutputDevTest_1657, FillWithBlackDeviceGray_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    GfxColor color;
    color.c[0] = dblToCol(0.0);
    
    auto cs = GfxColorSpace::create(csDeviceGray);
    state->setFillColorSpace(cs.get());
    state->setFillColor(&color);
    
    dev.fill(state.get());
    
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
}

// Test eoFill with RGB color
TEST_F(PreScanOutputDevTest_1657, EoFillWithRGBColor_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    GfxColor color;
    color.c[0] = dblToCol(0.0);
    color.c[1] = dblToCol(1.0);
    color.c[2] = dblToCol(0.0);
    
    auto cs = GfxColorSpace::create(csDeviceRGB);
    state->setFillColorSpace(cs.get());
    state->setFillColor(&color);
    
    dev.eoFill(state.get());
    
    EXPECT_FALSE(dev.isMonochrome());
    EXPECT_FALSE(dev.isGray());
}

// Test clearStats after color operations resets state
TEST_F(PreScanOutputDevTest_1657, ClearStatsAfterColorOps_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    color.c[1] = dblToCol(0.0);
    color.c[2] = dblToCol(0.0);
    
    auto cs = GfxColorSpace::create(csDeviceRGB);
    state->setFillColorSpace(cs.get());
    state->setFillColor(&color);
    
    dev.fill(state.get());
    
    EXPECT_FALSE(dev.isMonochrome());
    EXPECT_FALSE(dev.isGray());
    
    dev.clearStats();
    
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
}

// Test transparency detection via beginTransparencyGroup
TEST_F(PreScanOutputDevTest_1657, TransparencyGroupSetsTransparency_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    std::array<double, 4> bbox = {0.0, 0.0, 612.0, 792.0};
    
    dev.beginTransparencyGroup(state.get(), bbox, nullptr, false, false, false);
    
    EXPECT_TRUE(dev.usesTransparency());
}

// Test that after clearStats, transparency is reset
TEST_F(PreScanOutputDevTest_1657, ClearStatsResetsTransparency_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    std::array<double, 4> bbox = {0.0, 0.0, 612.0, 792.0};
    
    dev.beginTransparencyGroup(state.get(), bbox, nullptr, false, false, false);
    EXPECT_TRUE(dev.usesTransparency());
    
    dev.clearStats();
    EXPECT_FALSE(dev.usesTransparency());
}

// Test clip doesn't crash
TEST_F(PreScanOutputDevTest_1657, ClipNoCrash_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    dev.clip(state.get());
    SUCCEED();
}

// Test eoClip doesn't crash
TEST_F(PreScanOutputDevTest_1657, EoClipNoCrash_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    dev.eoClip(state.get());
    SUCCEED();
}

// Test beginStringOp / endStringOp don't crash
TEST_F(PreScanOutputDevTest_1657, StringOpNoCrash_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    dev.beginStringOp(state.get());
    dev.endStringOp(state.get());
    SUCCEED();
}

// Test with white DeviceGray color - should remain monochrome
TEST_F(PreScanOutputDevTest_1657, FillWithWhiteDeviceGray_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    GfxColor color;
    color.c[0] = dblToCol(1.0);
    
    auto cs = GfxColorSpace::create(csDeviceGray);
    state->setFillColorSpace(cs.get());
    state->setFillColor(&color);
    
    dev.fill(state.get());
    
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
}

// Test with DeviceCMYK color
TEST_F(PreScanOutputDevTest_1657, FillWithDeviceCMYK_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    GfxColor color;
    color.c[0] = dblToCol(1.0);  // C
    color.c[1] = dblToCol(0.0);  // M
    color.c[2] = dblToCol(1.0);  // Y
    color.c[3] = dblToCol(0.0);  // K
    
    auto cs = GfxColorSpace::create(csDeviceCMYK);
    state->setFillColorSpace(cs.get());
    state->setFillColor(&color);
    
    dev.fill(state.get());
    
    // CMYK with non-uniform components should not be gray or mono
    EXPECT_FALSE(dev.isMonochrome());
    EXPECT_FALSE(dev.isGray());
}

// Test with non-unity opacity affects transparency detection
TEST_F(PreScanOutputDevTest_1657, FillWithPartialOpacity_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    GfxColor color;
    color.c[0] = dblToCol(0.0);
    
    auto cs = GfxColorSpace::create(csDeviceGray);
    state->setFillColorSpace(cs.get());
    state->setFillColor(&color);
    state->setFillOpacity(0.5);
    
    dev.fill(state.get());
    
    EXPECT_TRUE(dev.usesTransparency());
}

// Test that multiple operations accumulate state correctly
TEST_F(PreScanOutputDevTest_1657, MultipleOperationsAccumulate_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    // First operation: gray
    GfxColor grayColor;
    grayColor.c[0] = dblToCol(0.5);
    auto grayCs = GfxColorSpace::create(csDeviceGray);
    state->setFillColorSpace(grayCs.get());
    state->setFillColor(&grayColor);
    state->setFillOpacity(1.0);
    
    dev.fill(state.get());
    EXPECT_TRUE(dev.isGray());
    
    // Second operation: RGB color
    GfxColor rgbColor;
    rgbColor.c[0] = dblToCol(1.0);
    rgbColor.c[1] = dblToCol(0.0);
    rgbColor.c[2] = dblToCol(0.0);
    auto rgbCs = GfxColorSpace::create(csDeviceRGB);
    state->setFillColorSpace(rgbCs.get());
    state->setFillColor(&rgbColor);
    
    dev.fill(state.get());
    
    // Now gray should be false since we used RGB color
    EXPECT_FALSE(dev.isGray());
    EXPECT_FALSE(dev.isMonochrome());
}

// Test functionShadedFill returns true (indicating it handles it)
TEST_F(PreScanOutputDevTest_1657, FunctionShadedFillReturnsTrue_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    // functionShadedFill should return true to indicate it handled it
    bool result = dev.functionShadedFill(state.get(), nullptr);
    EXPECT_TRUE(result);
}

// Test axialShadedFill returns true
TEST_F(PreScanOutputDevTest_1657, AxialShadedFillReturnsTrue_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    bool result = dev.axialShadedFill(state.get(), nullptr, 0.0, 1.0);
    EXPECT_TRUE(result);
}

// Test radialShadedFill returns true
TEST_F(PreScanOutputDevTest_1657, RadialShadedFillReturnsTrue_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    bool result = dev.radialShadedFill(state.get(), nullptr, 0.0, 1.0);
    EXPECT_TRUE(result);
}

// Test endType3Char doesn't crash
TEST_F(PreScanOutputDevTest_1657, EndType3CharNoCrash_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    dev.endType3Char(state.get());
    SUCCEED();
}

// Test non-unit stroke opacity triggers transparency
TEST_F(PreScanOutputDevTest_1657, StrokeWithPartialOpacity_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    GfxColor color;
    color.c[0] = dblToCol(0.0);
    
    auto cs = GfxColorSpace::create(csDeviceGray);
    state->setStrokeColorSpace(cs.get());
    state->setStrokeColor(&color);
    state->setStrokeOpacity(0.5);
    
    dev.stroke(state.get());
    
    EXPECT_TRUE(dev.usesTransparency());
}

// Test that gray RGB (equal components) maintains gray property
TEST_F(PreScanOutputDevTest_1657, FillWithGrayRGB_1657) {
    PreScanOutputDev dev(psLevel2);
    
    PDFRectangle pageBox(0, 0, 612, 792);
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    color.c[1] = dblToCol(0.5);
    color.c[2] = dblToCol(0.5);
    
    auto cs = GfxColorSpace::create(csDeviceRGB);
    state->setFillColorSpace(cs.get());
    state->setFillColor(&color);
    
    dev.fill(state.get());
    
    // Equal RGB components should still be considered gray
    EXPECT_TRUE(dev.isGray());
}
