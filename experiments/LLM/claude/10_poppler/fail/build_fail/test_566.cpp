#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <array>
#include <vector>

#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with default parameters
class GfxStateTest_566 : public ::testing::Test {
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

// Test: getCTM returns a valid 6-element array after construction
TEST_F(GfxStateTest_566, GetCTM_ReturnsValidArray_566) {
    const std::array<double, 6> &ctm = state->getCTM();
    // CTM should be initialized; at minimum we can check it has 6 elements
    EXPECT_EQ(ctm.size(), 6u);
}

// Test: setCTM sets the CTM correctly
TEST_F(GfxStateTest_566, SetCTM_UpdatesCTM_566) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const std::array<double, 6> &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test: concatCTM concatenates matrix correctly
TEST_F(GfxStateTest_566, ConcatCTM_ConcatenatesMatrix_566) {
    // Set identity first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 3.0, 5.0, 7.0);
    const std::array<double, 6> &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 3.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 7.0);
}

// Test: getHDPI and getVDPI return the values passed to constructor
TEST_F(GfxStateTest_566, GetDPI_ReturnsConstructedValues_566) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test: getPageWidth and getPageHeight
TEST_F(GfxStateTest_566, GetPageDimensions_566) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test: getRotate returns 0 for rotate=0
TEST_F(GfxStateTest_566, GetRotate_ReturnsZero_566) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test: getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_566, GetPageBounds_566) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    // These should be set based on the page box
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test: setLineWidth and getLineWidth
TEST_F(GfxStateTest_566, SetGetLineWidth_566) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test: setLineWidth with zero
TEST_F(GfxStateTest_566, SetLineWidth_Zero_566) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test: setFlatness and getFlatness
TEST_F(GfxStateTest_566, SetGetFlatness_566) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test: setLineJoin and getLineJoin
TEST_F(GfxStateTest_566, SetGetLineJoin_566) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test: setLineCap and getLineCap
TEST_F(GfxStateTest_566, SetGetLineCap_566) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test: setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_566, SetGetMiterLimit_566) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

// Test: setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_566, SetGetFillOpacity_566) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test: setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_566, SetGetStrokeOpacity_566) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test: setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_566, SetGetFillOverprint_566) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test: setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_566, SetGetStrokeOverprint_566) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test: setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_566, SetGetOverprintMode_566) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test: setCharSpace and getCharSpace
TEST_F(GfxStateTest_566, SetGetCharSpace_566) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test: setWordSpace and getWordSpace
TEST_F(GfxStateTest_566, SetGetWordSpace_566) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test: setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_566, SetGetHorizScaling_566) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test: setLeading and getLeading
TEST_F(GfxStateTest_566, SetGetLeading_566) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test: setRise and getRise
TEST_F(GfxStateTest_566, SetGetRise_566) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test: setRender and getRender
TEST_F(GfxStateTest_566, SetGetRender_566) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test: setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_566, SetGetStrokeAdjust_566) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test: setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_566, SetGetAlphaIsShape_566) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test: setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_566, SetGetTextKnockout_566) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test: setTextMat and getTextMat
TEST_F(GfxStateTest_566, SetGetTextMat_566) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const std::array<double, 6> &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// Test: setFontSize and getFontSize
TEST_F(GfxStateTest_566, GetFontSize_566) {
    // Default font size - just check it returns something
    double fs = state->getFontSize();
    EXPECT_GE(fs, 0.0);
}

// Test: setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_566, SetGetRenderingIntent_566) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test: setRenderingIntent with AbsoluteColorimetric
TEST_F(GfxStateTest_566, SetGetRenderingIntent_AbsoluteColorimetric_566) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test: setLineDash and getLineDash
TEST_F(GfxStateTest_566, SetGetLineDash_566) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const std::vector<double> &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test: setLineDash with empty dash
TEST_F(GfxStateTest_566, SetGetLineDash_Empty_566) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const std::vector<double> &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test: save and restore
TEST_F(GfxStateTest_566, SaveAndRestore_566) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    // After save, hasSaves should be true
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);

    GfxState *restored = state->restore();
    // restored should be the previous state
    EXPECT_NE(restored, nullptr);
}

// Test: hasSaves when no save has been done
TEST_F(GfxStateTest_566, HasSaves_NoSave_566) {
    EXPECT_FALSE(state->hasSaves());
}

// Test: transform with identity CTM
TEST_F(GfxStateTest_566, Transform_IdentityCTM_566) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test: transform with scaling CTM
TEST_F(GfxStateTest_566, Transform_ScalingCTM_566) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test: transform with translation CTM
TEST_F(GfxStateTest_566, Transform_TranslationCTM_566) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

// Test: transformDelta with scaling CTM (no translation effect)
TEST_F(GfxStateTest_566, TransformDelta_ScalingCTM_566) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test: moveTo and isCurPt
TEST_F(GfxStateTest_566, MoveTo_SetsCurPt_566) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test: lineTo after moveTo creates a path
TEST_F(GfxStateTest_566, LineTo_CreatesPath_566) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

// Test: clearPath clears the path
TEST_F(GfxStateTest_566, ClearPath_ClearsPath_566) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test: closePath
TEST_F(GfxStateTest_566, ClosePath_566) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    // After closing, the path should still exist
    EXPECT_TRUE(state->isPath());
}

// Test: curveTo
TEST_F(GfxStateTest_566, CurveTo_566) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

// Test: textMoveTo
TEST_F(GfxStateTest_566, TextMoveTo_566) {
    state->textMoveTo(100.0, 200.0);
    // Check that text position is updated
    // getCurTextX/getCurTextY might not directly reflect textMoveTo
    // but lineX and lineY should
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test: clipToRect
TEST_F(GfxStateTest_566, ClipToRect_566) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test: getBlendMode default
TEST_F(GfxStateTest_566, GetBlendMode_Default_566) {
    GfxBlendMode mode = state->getBlendMode();
    EXPECT_EQ(mode, gfxBlendNormal);
}

// Test: setBlendMode and getBlendMode
TEST_F(GfxStateTest_566, SetGetBlendMode_566) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test: copy creates a copy
TEST_F(GfxStateTest_566, Copy_566) {
    state->setLineWidth(7.5);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
}

// Test: copy with path
TEST_F(GfxStateTest_566, CopyWithPath_566) {
    state->clearPath();
    state->moveTo(1.0, 2.0);
    state->lineTo(3.0, 4.0);
    std::unique_ptr<GfxState> copied(state->copy(true));
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isPath());
}

// Test: transformWidth
TEST_F(GfxStateTest_566, TransformWidth_Identity_566) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tw = state->transformWidth(2.0);
    EXPECT_DOUBLE_EQ(tw, 2.0);
}

// Test: transformWidth with scaling
TEST_F(GfxStateTest_566, TransformWidth_Scaling_566) {
    state->setCTM(3.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double tw = state->transformWidth(2.0);
    EXPECT_DOUBLE_EQ(tw, 6.0);
}

// Test: getTransformedLineWidth
TEST_F(GfxStateTest_566, GetTransformedLineWidth_566) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 6.0);
}

// Test: construction with rotation
TEST_F(GfxStateTest_566, ConstructWithRotation_566) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test: construction with different DPIs
TEST_F(GfxStateTest_566, ConstructWithDifferentDPI_566) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDPI(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDPI.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDPI.getVDPI(), 150.0);
}

// Test: setFillColor and getFillColor
TEST_F(GfxStateTest_566, SetGetFillColor_566) {
    GfxColor color;
    color.c[0] = 32768; // ~0.5 in fixed point
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test: setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_566, SetGetStrokeColor_566) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 65535);
}

// Test: getFillColorSpace default
TEST_F(GfxStateTest_566, GetFillColorSpace_Default_566) {
    // After construction, fill color space may be set to default
    GfxColorSpace *cs = state->getFillColorSpace();
    // Can be nullptr or a valid default
    // Just verify we can call it without crash
    (void)cs;
}

// Test: getStrokeColorSpace default
TEST_F(GfxStateTest_566, GetStrokeColorSpace_Default_566) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    (void)cs;
}

// Test: getFillPattern default (nullptr)
TEST_F(GfxStateTest_566, GetFillPattern_Default_566) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

// Test: getStrokePattern default (nullptr)
TEST_F(GfxStateTest_566, GetStrokePattern_Default_566) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test: default fill opacity is 1.0
TEST_F(GfxStateTest_566, DefaultFillOpacity_566) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test: default stroke opacity is 1.0
TEST_F(GfxStateTest_566, DefaultStrokeOpacity_566) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test: getClipBBox
TEST_F(GfxStateTest_566, GetClipBBox_566) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test: getUserClipBBox
TEST_F(GfxStateTest_566, GetUserClipBBox_566) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test: getPath is not null initially
TEST_F(GfxStateTest_566, GetPath_NotNull_566) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test: default isPath is false
TEST_F(GfxStateTest_566, DefaultIsPath_False_566) {
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

// Test: shiftCTMAndClip
TEST_F(GfxStateTest_566, ShiftCTMAndClip_566) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const std::array<double, 6> &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test: getCTM with Matrix
TEST_F(GfxStateTest_566, GetCTM_Matrix_566) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test: setFillOpacity boundary - zero
TEST_F(GfxStateTest_566, FillOpacity_Zero_566) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

// Test: setStrokeOpacity boundary - zero
TEST_F(GfxStateTest_566, StrokeOpacity_Zero_566) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// Test: negative line width
TEST_F(GfxStateTest_566, SetLineWidth_Negative_566) {
    state->setLineWidth(-1.0);
    // Behavior may vary, just ensure no crash
    double lw = state->getLineWidth();
    (void)lw;
}

// Test: textTransform
TEST_F(GfxStateTest_566, TextTransform_566) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // With identity text matrix, should yield results based on CTM applied
    // Just check no crash and values are returned
    (void)x2;
    (void)y2;
}

// Test: textTransformDelta
TEST_F(GfxStateTest_566, TextTransformDelta_566) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(3.0, 4.0, &x2, &y2);
    (void)x2;
    (void)y2;
}

// Test: getCurX and getCurY after moveTo
TEST_F(GfxStateTest_566, GetCurXY_AfterMoveTo_566) {
    state->clearPath();
    state->moveTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 42.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 84.0);
}

// Test: multiple save/restore
TEST_F(GfxStateTest_566, MultipleSaveRestore_566) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(2.0);
    GfxState *s2 = state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);

    GfxState *r1 = state->restore();
    EXPECT_NE(r1, nullptr);

    GfxState *r2 = state->restore();
    EXPECT_NE(r2, nullptr);

    EXPECT_FALSE(state->hasSaves());
}

// Test: getFont default is nullptr
TEST_F(GfxStateTest_566, GetFont_Default_566) {
    const std::shared_ptr<GfxFont> &font = state->getFont();
    // Default font may be nullptr
    EXPECT_EQ(font, nullptr);
}

// Test: getDisplayProfile default
TEST_F(GfxStateTest_566, GetDisplayProfile_Default_566) {
    GfxLCMSProfilePtr profile = state->getDisplayProfile();
    // May be nullptr by default
    (void)profile;
}

// Test: setRenderingIntent with long string (boundary: buffer is 32 chars)
TEST_F(GfxStateTest_566, SetRenderingIntent_LongString_566) {
    // The buffer is char[32], so a very long string should be truncated or handled
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test: concatCTM with non-trivial matrix
TEST_F(GfxStateTest_566, ConcatCTM_NonTrivial_566) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 5.0, 5.0);
    const std::array<double, 6> &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 15.0);
    EXPECT_DOUBLE_EQ(ctm[5], 25.0);
}
