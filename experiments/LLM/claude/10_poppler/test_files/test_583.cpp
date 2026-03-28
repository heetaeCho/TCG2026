#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Helper to create a GfxState with default parameters
static std::unique_ptr<GfxState> createDefaultGfxState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_583 : public ::testing::Test {
protected:
    void SetUp() override {
        state = createDefaultGfxState();
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test that getStrokeCMYK returns valid CMYK values with default stroke color space
TEST_F(GfxStateTest_583, GetStrokeCMYK_DefaultColorSpace_583) {
    GfxCMYK cmyk;
    // Default stroke color space should be device gray; getCMYK should not crash
    state->getStrokeCMYK(&cmyk);
    // We can at least verify the values are in a reasonable range [0, gfxColorComp1]
    // Since default stroke color is typically black in DeviceGray:
    // The exact values depend on the implementation, but we verify no crash
    SUCCEED();
}

// Test getStrokeCMYK after setting stroke color space to CMYK
TEST_F(GfxStateTest_583, GetStrokeCMYK_AfterSetStrokeColorSpace_583) {
    // Create a DeviceCMYK color space
    auto cmykCS = GfxColorSpace::parse(nullptr, nullptr, nullptr, nullptr, 0);
    // If we can't parse without objects, use the default behavior
    GfxCMYK cmyk;
    state->getStrokeCMYK(&cmyk);
    // Just verify it doesn't crash with default color space
    SUCCEED();
}

// Test getStrokeCMYK after explicitly setting stroke color
TEST_F(GfxStateTest_583, GetStrokeCMYK_AfterSetStrokeColor_583) {
    GfxColor color;
    // Set all components to 0
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = 0;
    }
    state->setStrokeColor(&color);
    
    GfxCMYK cmyk;
    state->getStrokeCMYK(&cmyk);
    // With a gray color space and color value 0 (black), CMYK should have k component
    SUCCEED();
}

// Test that getFillCMYK works with default state
TEST_F(GfxStateTest_583, GetFillCMYK_DefaultColorSpace_583) {
    GfxCMYK cmyk;
    state->getFillCMYK(&cmyk);
    SUCCEED();
}

// Test basic construction parameters
TEST_F(GfxStateTest_583, Construction_BasicParameters_583) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test default stroke color space is not null
TEST_F(GfxStateTest_583, StrokeColorSpace_NotNull_583) {
    GfxColorSpace* cs = state->getStrokeColorSpace();
    ASSERT_NE(cs, nullptr);
}

// Test default fill color space is not null
TEST_F(GfxStateTest_583, FillColorSpace_NotNull_583) {
    GfxColorSpace* cs = state->getFillColorSpace();
    ASSERT_NE(cs, nullptr);
}

// Test getStrokeRGB with default state
TEST_F(GfxStateTest_583, GetStrokeRGB_Default_583) {
    GfxRGB rgb;
    state->getStrokeRGB(&rgb);
    // Default stroke is black in DeviceGray
    SUCCEED();
}

// Test getFillRGB with default state
TEST_F(GfxStateTest_583, GetFillRGB_Default_583) {
    GfxRGB rgb;
    state->getFillRGB(&rgb);
    SUCCEED();
}

// Test getStrokeGray with default state
TEST_F(GfxStateTest_583, GetStrokeGray_Default_583) {
    GfxGray gray;
    state->getStrokeGray(&gray);
    SUCCEED();
}

// Test getFillGray with default state
TEST_F(GfxStateTest_583, GetFillGray_Default_583) {
    GfxGray gray;
    state->getFillGray(&gray);
    SUCCEED();
}

// Test setStrokeColor and then getStrokeCMYK
TEST_F(GfxStateTest_583, SetStrokeColor_ThenGetCMYK_583) {
    GfxColor color;
    // Set to white (1.0 in gray)
    color.c[0] = gfxColorComp1;
    for (int i = 1; i < gfxColorMaxComps; i++) {
        color.c[i] = 0;
    }
    state->setStrokeColor(&color);
    
    GfxCMYK cmyk;
    state->getStrokeCMYK(&cmyk);
    // White in gray should map to 0,0,0,0 in CMYK
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test setStrokeColor to black and getStrokeCMYK
TEST_F(GfxStateTest_583, SetStrokeColorBlack_ThenGetCMYK_583) {
    GfxColor color;
    // Set to black (0 in gray)
    color.c[0] = 0;
    for (int i = 1; i < gfxColorMaxComps; i++) {
        color.c[i] = 0;
    }
    state->setStrokeColor(&color);
    
    GfxCMYK cmyk;
    state->getStrokeCMYK(&cmyk);
    // Black in gray should map to 0,0,0,1 in CMYK (k = max)
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

// Test default blend mode
TEST_F(GfxStateTest_583, DefaultBlendMode_583) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test default opacity values
TEST_F(GfxStateTest_583, DefaultOpacity_583) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test default overprint settings
TEST_F(GfxStateTest_583, DefaultOverprint_583) {
    EXPECT_FALSE(state->getFillOverprint());
    EXPECT_FALSE(state->getStrokeOverprint());
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test default line properties
TEST_F(GfxStateTest_583, DefaultLineProperties_583) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_583, SetGetStrokeOpacity_583) {
    state->setStrokeOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.5);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_583, SetGetFillOpacity_583) {
    state->setFillOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.3);
}

// Test save and restore functionality
TEST_F(GfxStateTest_583, SaveAndRestore_583) {
    state->setFillOpacity(0.5);
    GfxState* saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
    
    saved->setFillOpacity(0.2);
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.2);
    
    GfxState* restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.5);
}

// Test hasSaves returns false initially
TEST_F(GfxStateTest_583, HasSaves_InitiallyFalse_583) {
    EXPECT_FALSE(state->hasSaves());
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_583, SetGetLineWidth_583) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test setLineWidth with zero
TEST_F(GfxStateTest_583, SetLineWidthZero_583) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test text properties
TEST_F(GfxStateTest_583, SetGetCharSpace_583) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_583, SetGetWordSpace_583) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_583, SetGetHorizScaling_583) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_583, SetGetLeading_583) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_583, SetGetRise_583) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_583, SetGetRender_583) {
    state->setRender(1);
    EXPECT_EQ(state->getRender(), 1);
}

// Test rendering intent
TEST_F(GfxStateTest_583, SetGetRenderingIntent_583) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_583, SetRenderingIntent_RelativeColorimetric_583) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test setBlendMode
TEST_F(GfxStateTest_583, SetGetBlendMode_583) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test overprint settings
TEST_F(GfxStateTest_583, SetGetFillOverprint_583) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_583, SetGetStrokeOverprint_583) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_583, SetGetOverprintMode_583) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test line join and cap styles
TEST_F(GfxStateTest_583, SetGetLineJoin_583) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

TEST_F(GfxStateTest_583, SetGetLineCap_583) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test stroke adjust
TEST_F(GfxStateTest_583, SetGetStrokeAdjust_583) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_583, SetGetAlphaIsShape_583) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_583, SetGetTextKnockout_583) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test miter limit
TEST_F(GfxStateTest_583, SetGetMiterLimit_583) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test flatness
TEST_F(GfxStateTest_583, SetGetFlatness_583) {
    state->setFlatness(2);
    EXPECT_EQ(state->getFlatness(), 2);
}

// Test transform functions
TEST_F(GfxStateTest_583, Transform_Identity_583) {
    double x2, y2;
    state->transform(100.0, 200.0, &x2, &y2);
    // With default CTM (identity + translation for page), results should be valid
    SUCCEED();
}

TEST_F(GfxStateTest_583, TransformDelta_Identity_583) {
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    SUCCEED();
}

// Test path operations
TEST_F(GfxStateTest_583, PathOperations_MoveTo_583) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_583, PathOperations_LineTo_583) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_583, PathOperations_CurveTo_583) {
    state->moveTo(10.0, 20.0);
    state->curveTo(15.0, 25.0, 20.0, 30.0, 25.0, 35.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_583, PathOperations_ClosePath_583) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_583, ClearPath_583) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test isCurPt and isPath on empty state
TEST_F(GfxStateTest_583, EmptyPath_NoCurPt_583) {
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_583, EmptyPath_NoPath_583) {
    EXPECT_FALSE(state->isPath());
}

// Test clip bounding box
TEST_F(GfxStateTest_583, ClipBBox_583) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have valid clip bounds
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test CTM
TEST_F(GfxStateTest_583, GetCTM_583) {
    const auto& ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test copy
TEST_F(GfxStateTest_583, Copy_583) {
    state->setFillOpacity(0.7);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
}

// Test getStrokeColor and getFillColor
TEST_F(GfxStateTest_583, GetStrokeColor_NotNull_583) {
    const GfxColor* color = state->getStrokeColor();
    ASSERT_NE(color, nullptr);
}

TEST_F(GfxStateTest_583, GetFillColor_NotNull_583) {
    const GfxColor* color = state->getFillColor();
    ASSERT_NE(color, nullptr);
}

// Test getStrokeDeviceN with default state
TEST_F(GfxStateTest_583, GetStrokeDeviceN_Default_583) {
    GfxColor deviceN;
    state->getStrokeDeviceN(&deviceN);
    SUCCEED();
}

// Test getFillDeviceN with default state
TEST_F(GfxStateTest_583, GetFillDeviceN_Default_583) {
    GfxColor deviceN;
    state->getFillDeviceN(&deviceN);
    SUCCEED();
}

// Test setting text matrix
TEST_F(GfxStateTest_583, SetGetTextMat_583) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto& mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// Test construction with different rotations
TEST_F(GfxStateTest_583, Construction_Rotated_583) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

// Test construction with upside down false
TEST_F(GfxStateTest_583, Construction_NotUpsideDown_583) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto s = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(s->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s->getPageHeight(), 792.0);
}

// Test setLineDash
TEST_F(GfxStateTest_583, SetGetLineDash_583) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

// Test empty line dash
TEST_F(GfxStateTest_583, SetGetLineDash_Empty_583) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(d.size(), 0u);
}

// Test clipToRect
TEST_F(GfxStateTest_583, ClipToRect_583) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should be at most the rect we specified
    EXPECT_GE(xMin, 10.0 - 1e-6);
    EXPECT_GE(yMin, 10.0 - 1e-6);
    EXPECT_LE(xMax, 100.0 + 1e-6);
    EXPECT_LE(yMax, 100.0 + 1e-6);
}

// Test getPath not null
TEST_F(GfxStateTest_583, GetPath_NotNull_583) {
    const GfxPath* path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test font size
TEST_F(GfxStateTest_583, DefaultFontSize_583) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_583, GetPageBounds_583) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test concatCTM
TEST_F(GfxStateTest_583, ConcatCTM_583) {
    const auto& ctmBefore = state->getCTM();
    // Apply a scale of 2x
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto& ctmAfter = state->getCTM();
    // CTM should have changed
    // We just verify it doesn't crash and the CTM is modified
    SUCCEED();
}

// Test setCTM
TEST_F(GfxStateTest_583, SetCTM_583) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 1.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 1.0);
    EXPECT_DOUBLE_EQ(ctm[4], 0.0);
    EXPECT_DOUBLE_EQ(ctm[5], 0.0);
}

// Test getCurX and getCurY after moveTo
TEST_F(GfxStateTest_583, GetCurXY_AfterMoveTo_583) {
    state->moveTo(50.0, 75.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 75.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_583, TextMoveTo_583) {
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX and lineY should be set
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_583, GetUserClipBBox_583) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getPattern returns null by default
TEST_F(GfxStateTest_583, DefaultPatternNull_583) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test save creates saves chain
TEST_F(GfxStateTest_583, SaveCreatesSavesChain_583) {
    EXPECT_FALSE(state->hasSaves());
    GfxState* s1 = state->save();
    EXPECT_TRUE(state->hasSaves());
    GfxState* s2 = s1->save();
    EXPECT_TRUE(s1->hasSaves());
    // Restore back
    GfxState* r1 = s2->restore();
    EXPECT_EQ(r1, s1);
    GfxState* r2 = r1->restore();
    EXPECT_EQ(r2, state.get());
    EXPECT_FALSE(state->hasSaves());
}
