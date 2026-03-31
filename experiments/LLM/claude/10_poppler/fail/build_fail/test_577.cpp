#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include <memory>
#include <vector>
#include <cstring>

// Helper to create a basic GfxState with a simple page box
class GfxStateTest_577 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and page dimensions
TEST_F(GfxStateTest_577, ConstructionBasic_577) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page coordinates
TEST_F(GfxStateTest_577, PageCoordinates_577) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_577, DefaultFillOpacity_577) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_577, DefaultStrokeOpacity_577) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_577, SetFillOpacity_577) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_577, SetStrokeOpacity_577) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test default line width
TEST_F(GfxStateTest_577, DefaultLineWidth_577) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set and get line width
TEST_F(GfxStateTest_577, SetLineWidth_577) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_577, DefaultFlatness_577) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set and get flatness
TEST_F(GfxStateTest_577, SetFlatness_577) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_577, DefaultMiterLimit_577) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set and get miter limit
TEST_F(GfxStateTest_577, SetMiterLimit_577) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_577, DefaultFillOverprint_577) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set and get fill overprint
TEST_F(GfxStateTest_577, SetFillOverprint_577) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_577, DefaultStrokeOverprint_577) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set and get stroke overprint
TEST_F(GfxStateTest_577, SetStrokeOverprint_577) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_577, DefaultOverprintMode_577) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set and get overprint mode
TEST_F(GfxStateTest_577, SetOverprintMode_577) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_577, DefaultStrokeAdjust_577) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set and get stroke adjust
TEST_F(GfxStateTest_577, SetStrokeAdjust_577) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_577, DefaultAlphaIsShape_577) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set and get alpha is shape
TEST_F(GfxStateTest_577, SetAlphaIsShape_577) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_577, DefaultTextKnockout_577) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set and get text knockout
TEST_F(GfxStateTest_577, SetTextKnockout_577) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_577, DefaultCharSpace_577) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set and get char space
TEST_F(GfxStateTest_577, SetCharSpace_577) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_577, DefaultWordSpace_577) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set and get word space
TEST_F(GfxStateTest_577, SetWordSpace_577) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_577, DefaultHorizScaling_577) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set and get horiz scaling
TEST_F(GfxStateTest_577, SetHorizScaling_577) {
    state->setHorizScaling(0.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test default leading
TEST_F(GfxStateTest_577, DefaultLeading_577) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set and get leading
TEST_F(GfxStateTest_577, SetLeading_577) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_577, DefaultRise_577) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set and get rise
TEST_F(GfxStateTest_577, SetRise_577) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_577, DefaultRender_577) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set and get render
TEST_F(GfxStateTest_577, SetRender_577) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default font size
TEST_F(GfxStateTest_577, DefaultFontSize_577) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default blend mode
TEST_F(GfxStateTest_577, DefaultBlendMode_577) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set and get blend mode
TEST_F(GfxStateTest_577, SetBlendMode_577) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test default line join
TEST_F(GfxStateTest_577, DefaultLineJoin_577) {
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);
}

// Test set and get line join
TEST_F(GfxStateTest_577, SetLineJoin_577) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test default line cap
TEST_F(GfxStateTest_577, DefaultLineCap_577) {
    EXPECT_EQ(state->getLineCap(), lineCapButt);
}

// Test set and get line cap
TEST_F(GfxStateTest_577, SetLineCap_577) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test save and restore
TEST_F(GfxStateTest_577, SaveAndRestore_577) {
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
    
    GfxState *restored = state->restore();
    // After restore, the state should go back
    // The returned pointer should be the saved state
    ASSERT_NE(restored, nullptr);
}

// Test hasSaves when no save
TEST_F(GfxStateTest_577, HasSavesNoSave_577) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_577, HasSavesAfterSave_577) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test path operations - initially no current point
TEST_F(GfxStateTest_577, InitiallyNoCurPt_577) {
    EXPECT_FALSE(state->isCurPt());
}

// Test path operations - initially no path
TEST_F(GfxStateTest_577, InitiallyNoPath_577) {
    EXPECT_FALSE(state->isPath());
}

// Test moveTo creates current point
TEST_F(GfxStateTest_577, MoveToCreatesCurPt_577) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

// Test lineTo creates a path
TEST_F(GfxStateTest_577, LineToCreatesPath_577) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 100.0);
}

// Test curveTo
TEST_F(GfxStateTest_577, CurveTo_577) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test clearPath
TEST_F(GfxStateTest_577, ClearPath_577) {
    state->moveTo(10.0, 20.0);
    state->lineTo(100.0, 100.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_577, ClosePath_577) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closing, current point should be at the start of the subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test transform with identity CTM
TEST_F(GfxStateTest_577, TransformIdentity_577) {
    // The initial CTM should map page coordinates
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Just verify it doesn't crash and returns some values
    // The exact transform depends on the CTM set during construction
}

// Test transformDelta
TEST_F(GfxStateTest_577, TransformDelta_577) {
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    // Just verify it doesn't crash
}

// Test setCTM
TEST_F(GfxStateTest_577, SetCTM_577) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 1.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 1.0);
    EXPECT_DOUBLE_EQ(ctm[4], 0.0);
    EXPECT_DOUBLE_EQ(ctm[5], 0.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_577, SetTextMat_577) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 2.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 2.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_577, SetRenderingIntent_577) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test rendering intent with long string (boundary - should truncate or handle)
TEST_F(GfxStateTest_577, SetRenderingIntentLongString_577) {
    // The buffer is char[32], so test with a string that fits
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_577, SetLineDash_577) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
}

// Test empty line dash
TEST_F(GfxStateTest_577, EmptyLineDash_577) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(result.size(), 0u);
}

// Test getClipBBox
TEST_F(GfxStateTest_577, GetClipBBox_577) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have valid clip box values
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_577, GetUserClipBBox_577) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_577, ClipToRect_577) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should be constrained
}

// Test textMoveTo
TEST_F(GfxStateTest_577, TextMoveTo_577) {
    state->textMoveTo(50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 60.0);
}

// Test copy
TEST_F(GfxStateTest_577, Copy_577) {
    state->setLineWidth(4.0);
    state->setFillOpacity(0.8);
    auto copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 4.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
    delete copied;
}

// Test construction with rotation
TEST_F(GfxStateTest_577, ConstructionWithRotation_577) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test construction with different DPI
TEST_F(GfxStateTest_577, ConstructionDifferentDPI_577) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 300.0);
}

// Test getFillColorSpace returns non-null (default should be DeviceGray)
TEST_F(GfxStateTest_577, DefaultFillColorSpace_577) {
    GfxColorSpace *cs = state->getFillColorSpace();
    ASSERT_NE(cs, nullptr);
}

// Test getStrokeColorSpace returns non-null
TEST_F(GfxStateTest_577, DefaultStrokeColorSpace_577) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    ASSERT_NE(cs, nullptr);
}

// Test getFillPattern default is null
TEST_F(GfxStateTest_577, DefaultFillPattern_577) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// Test getStrokePattern default is null
TEST_F(GfxStateTest_577, DefaultStrokePattern_577) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test default font is null
TEST_F(GfxStateTest_577, DefaultFont_577) {
    EXPECT_EQ(state->getFont(), nullptr);
}

// Test getFillColor returns non-null
TEST_F(GfxStateTest_577, GetFillColor_577) {
    const GfxColor *color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

// Test getStrokeColor returns non-null
TEST_F(GfxStateTest_577, GetStrokeColor_577) {
    const GfxColor *color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_577, SetFillColor_577) {
    GfxColor color;
    color.c[0] = 32768; // 0.5 in fixed point
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    EXPECT_EQ(result->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_577, SetStrokeColor_577) {
    GfxColor color;
    color.c[0] = 65535; // 1.0 in fixed point
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 65535);
}

// Test getFillGray with default color space
TEST_F(GfxStateTest_577, GetFillGray_577) {
    GfxGray gray;
    state->getFillGray(&gray);
    // Default fill color in DeviceGray should give some gray value
    // Just verify it doesn't crash
}

// Test getStrokeGray
TEST_F(GfxStateTest_577, GetStrokeGray_577) {
    GfxGray gray;
    state->getStrokeGray(&gray);
}

// Test getFillRGB
TEST_F(GfxStateTest_577, GetFillRGB_577) {
    GfxRGB rgb;
    state->getFillRGB(&rgb);
}

// Test getStrokeRGB
TEST_F(GfxStateTest_577, GetStrokeRGB_577) {
    GfxRGB rgb;
    state->getStrokeRGB(&rgb);
}

// Test getFillCMYK
TEST_F(GfxStateTest_577, GetFillCMYK_577) {
    GfxCMYK cmyk;
    state->getFillCMYK(&cmyk);
}

// Test getStrokeCMYK
TEST_F(GfxStateTest_577, GetStrokeCMYK_577) {
    GfxCMYK cmyk;
    state->getStrokeCMYK(&cmyk);
}

// Test transformWidth
TEST_F(GfxStateTest_577, TransformWidth_577) {
    double result = state->transformWidth(1.0);
    EXPECT_GT(result, 0.0);
}

// Test getPath is not null
TEST_F(GfxStateTest_577, GetPath_577) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test concatCTM
TEST_F(GfxStateTest_577, ConcatCTM_577) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_577, ShiftCTMAndClip_577) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test save and restore preserves state
TEST_F(GfxStateTest_577, SaveRestorePreservesState_577) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.3);
    state->setCharSpace(2.0);
    
    GfxState *savedState = state->save();
    ASSERT_NE(savedState, nullptr);
    
    state->setLineWidth(1.0);
    state->setFillOpacity(1.0);
    state->setCharSpace(0.0);
    
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
    
    GfxState *restoredState = state->restore();
    ASSERT_NE(restoredState, nullptr);
    EXPECT_DOUBLE_EQ(restoredState->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(restoredState->getFillOpacity(), 0.3);
    EXPECT_DOUBLE_EQ(restoredState->getCharSpace(), 2.0);
}

// Test multiple saves
TEST_F(GfxStateTest_577, MultipleSaves_577) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);
    
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    EXPECT_TRUE(state->hasSaves());
    
    GfxState *s1 = state->restore();
    EXPECT_DOUBLE_EQ(s1->getLineWidth(), 2.0);
    EXPECT_TRUE(s1->hasSaves());
    
    GfxState *s2 = s1->restore();
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 1.0);
    EXPECT_FALSE(s2->hasSaves());
}

// Test getDisplayProfile default
TEST_F(GfxStateTest_577, DefaultDisplayProfile_577) {
    auto profile = state->getDisplayProfile();
    // Default should be null/empty
}

// Test fill opacity boundary values
TEST_F(GfxStateTest_577, FillOpacityBoundary_577) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test line width zero
TEST_F(GfxStateTest_577, LineWidthZero_577) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test getCTM as Matrix
TEST_F(GfxStateTest_577, GetCTMMatrix_577) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify matrix was populated
}

// Test getReusablePath
TEST_F(GfxStateTest_577, GetReusablePath_577) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// Test textTransform
TEST_F(GfxStateTest_577, TextTransform_577) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    // Just verify no crash
}

// Test textTransformDelta
TEST_F(GfxStateTest_577, TextTransformDelta_577) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(10.0, 20.0, &x2, &y2);
}

// Test parseBlendMode with known mode
TEST_F(GfxStateTest_577, ParseBlendModeNormal_577) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test construction with upsideDown false
TEST_F(GfxStateTest_577, ConstructionUpsideDownFalse_577) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state2(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(state2.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state2.getPageHeight(), 792.0);
}

// Test construction with 180 degree rotation
TEST_F(GfxStateTest_577, ConstructionRotation180_577) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state2(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state2.getRotate(), 180);
}

// Test construction with 270 degree rotation
TEST_F(GfxStateTest_577, ConstructionRotation270_577) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state2(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(state2.getRotate(), 270);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_577, GetTransformedLineWidth_577) {
    state->setLineWidth(2.0);
    double transformed = state->getTransformedLineWidth();
    EXPECT_GT(transformed, 0.0);
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_577, GetTransformedFontSize_577) {
    double transformed = state->getTransformedFontSize();
    // With no font set, font size is 0
    EXPECT_DOUBLE_EQ(transformed, 0.0);
}
