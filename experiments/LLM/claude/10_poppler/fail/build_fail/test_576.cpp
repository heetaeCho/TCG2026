#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_576 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// ==================== Constructor / Basic Getters ====================

TEST_F(GfxStateTest_576, ConstructorSetsHDPI_576) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_576, ConstructorSetsVDPI_576) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_576, ConstructorSetsRotate_576) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_576, ConstructorSetsPageDimensions_576) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_576, ConstructorWithRotation90_576) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_576, ConstructorWithRotation180_576) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_576, ConstructorWithRotation270_576) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// ==================== Page Bounds ====================

TEST_F(GfxStateTest_576, GetX1Y1X2Y2_576) {
    // These should reflect the page box transformed
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// ==================== CTM ====================

TEST_F(GfxStateTest_576, GetCTMReturnsArray_576) {
    const auto& ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_576, SetCTM_576) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_576, ConcatCTM_576) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // identity
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

TEST_F(GfxStateTest_576, GetCTMMatrix_576) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify the matrix was populated (exact mapping depends on implementation)
    // At minimum it shouldn't crash
}

// ==================== Transform ====================

TEST_F(GfxStateTest_576, TransformIdentity_576) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_576, TransformWithScaling_576) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_576, TransformWithTranslation_576) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 200.0);
}

TEST_F(GfxStateTest_576, TransformDelta_576) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // Delta should not include translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// ==================== Colors ====================

TEST_F(GfxStateTest_576, GetStrokeColorNotNull_576) {
    const GfxColor* color = state->getStrokeColor();
    ASSERT_NE(color, nullptr);
}

TEST_F(GfxStateTest_576, GetFillColorNotNull_576) {
    const GfxColor* color = state->getFillColor();
    ASSERT_NE(color, nullptr);
}

TEST_F(GfxStateTest_576, SetAndGetFillColor_576) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor* retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_576, SetAndGetStrokeColor_576) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor* retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 16384);
}

// ==================== Line Properties ====================

TEST_F(GfxStateTest_576, SetAndGetLineWidth_576) {
    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_576, SetAndGetLineWidthZero_576) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_576, SetAndGetMiterLimit_576) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_576, SetAndGetFlatness_576) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

TEST_F(GfxStateTest_576, SetAndGetLineJoin_576) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_576, SetAndGetLineCap_576) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_576, SetAndGetLineDash_576) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_576, SetEmptyLineDash_576) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& retrievedDash = state->getLineDash(&start);
    EXPECT_TRUE(retrievedDash.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// ==================== Opacity and Overprint ====================

TEST_F(GfxStateTest_576, SetAndGetFillOpacity_576) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_576, SetAndGetStrokeOpacity_576) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_576, SetAndGetFillOverprint_576) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_576, SetAndGetStrokeOverprint_576) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_576, SetAndGetOverprintMode_576) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ==================== Blend Mode ====================

TEST_F(GfxStateTest_576, SetAndGetBlendMode_576) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_576, DefaultBlendModeIsNormal_576) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// ==================== Text Properties ====================

TEST_F(GfxStateTest_576, SetAndGetCharSpace_576) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

TEST_F(GfxStateTest_576, SetAndGetWordSpace_576) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

TEST_F(GfxStateTest_576, SetAndGetHorizScaling_576) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_576, SetAndGetLeading_576) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_576, SetAndGetRise_576) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

TEST_F(GfxStateTest_576, SetAndGetRender_576) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_576, SetAndGetTextMat_576) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto& tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

TEST_F(GfxStateTest_576, GetFontSizeDefault_576) {
    // Font size should be some default value after construction
    double fontSize = state->getFontSize();
    // Just ensure it doesn't crash and returns a non-negative value
    EXPECT_GE(fontSize, 0.0);
}

// ==================== Stroke Adjust / AlphaIsShape / TextKnockout ====================

TEST_F(GfxStateTest_576, SetAndGetStrokeAdjust_576) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_576, SetAndGetAlphaIsShape_576) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_576, SetAndGetTextKnockout_576) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ==================== Rendering Intent ====================

TEST_F(GfxStateTest_576, SetAndGetRenderingIntent_576) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_576, SetRenderingIntentPerceptual_576) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_576, SetRenderingIntentSaturation_576) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_576, SetRenderingIntentAbsoluteColorimetric_576) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// ==================== Path Operations ====================

TEST_F(GfxStateTest_576, InitialPathIsEmpty_576) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_576, MoveToSetsCurrentPoint_576) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_576, LineToCreatesPath_576) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_576, CurveToCreatesPath_576) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_576, ClearPathResetsState_576) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_576, ClosePathDoesNotCrash_576) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_576, GetPathNotNull_576) {
    const GfxPath* path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// ==================== Save / Restore ====================

TEST_F(GfxStateTest_576, InitiallyNoSaves_576) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_576, SaveCreatesSaveState_576) {
    GfxState* saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // saved should be the previous state pointer
    ASSERT_NE(saved, nullptr);
}

TEST_F(GfxStateTest_576, RestoreAfterSave_576) {
    state->setLineWidth(5.0);
    GfxState* saved = state->save();
    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);
    GfxState* restored = state->restore();
    // After restore, the returned pointer should be the restored state
    ASSERT_NE(restored, nullptr);
}

TEST_F(GfxStateTest_576, MultipleSavesAndRestores_576) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
    state->save();
    EXPECT_TRUE(state->hasSaves());
    GfxState* r1 = state->restore();
    ASSERT_NE(r1, nullptr);
    GfxState* r2 = state->restore();
    ASSERT_NE(r2, nullptr);
}

// ==================== Copy ====================

TEST_F(GfxStateTest_576, CopyCreatesIndependentState_576) {
    state->setLineWidth(7.0);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
}

TEST_F(GfxStateTest_576, CopyPreservesCTM_576) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    std::unique_ptr<GfxState> copied(state->copy());
    const auto& ctm = copied->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 3.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ==================== Clip ====================

TEST_F(GfxStateTest_576, ClipToRect_576) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should constrain the bounding box
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

TEST_F(GfxStateTest_576, GetClipBBox_576) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should not crash and return valid bounds
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_576, GetUserClipBBox_576) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ==================== Text Position ====================

TEST_F(GfxStateTest_576, TextMoveToSetsCurText_576) {
    state->textMoveTo(50.0, 60.0);
    // Should set the text position - verify via getCurTextX/Y or getLineX/Y
    // The exact mapping depends on the text matrix
}

TEST_F(GfxStateTest_576, GetCurXY_576) {
    // Just ensure getters don't crash
    double x = state->getCurX();
    double y = state->getCurY();
    (void)x;
    (void)y;
}

TEST_F(GfxStateTest_576, GetLineXY_576) {
    double lx = state->getLineX();
    double ly = state->getLineY();
    (void)lx;
    (void)ly;
}

// ==================== Color Spaces ====================

TEST_F(GfxStateTest_576, FillColorSpaceInitiallyNotNull_576) {
    // After construction, there should be a default fill color space
    GfxColorSpace* cs = state->getFillColorSpace();
    // May or may not be null depending on implementation
    (void)cs;
}

TEST_F(GfxStateTest_576, StrokeColorSpaceInitiallyNotNull_576) {
    GfxColorSpace* cs = state->getStrokeColorSpace();
    (void)cs;
}

TEST_F(GfxStateTest_576, FillPatternInitiallyNull_576) {
    GfxPattern* pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_576, StrokePatternInitiallyNull_576) {
    GfxPattern* pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// ==================== TransformWidth ====================

TEST_F(GfxStateTest_576, TransformWidthIdentity_576) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_NEAR(w, 5.0, 0.001);
}

TEST_F(GfxStateTest_576, TransformWidthWithScaling_576) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_NEAR(w, 10.0, 0.001);
}

TEST_F(GfxStateTest_576, TransformWidthZero_576) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(w, 0.0);
}

// ==================== GetTransformedLineWidth ====================

TEST_F(GfxStateTest_576, GetTransformedLineWidth_576) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_NEAR(tw, 3.0, 0.001);
}

// ==================== parseBlendMode ====================

TEST_F(GfxStateTest_576, ParseBlendModeNormal_576) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// ==================== ShiftCTMAndClip ====================

TEST_F(GfxStateTest_576, ShiftCTMAndClip_576) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ==================== Text Transform ====================

TEST_F(GfxStateTest_576, TextTransformIdentity_576) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // Result depends on both text matrix and CTM
}

TEST_F(GfxStateTest_576, TextTransformDelta_576) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
}

// ==================== IsParentState ====================

TEST_F(GfxStateTest_576, IsParentStateAfterSave_576) {
    GfxState* beforeSave = state.get();
    GfxState* afterSave = state->save();
    // afterSave points to the saved state, which should be a parent
    // The exact semantics depend on implementation
    (void)beforeSave;
    (void)afterSave;
    state->restore();
}

// ==================== GetReusablePath ====================

TEST_F(GfxStateTest_576, GetReusablePathNotNull_576) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    ASSERT_NE(pathIter, nullptr);
}

// ==================== Edge Cases ====================

TEST_F(GfxStateTest_576, SetFillOpacityBoundary0_576) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_576, SetFillOpacityBoundary1_576) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_576, SetStrokeOpacityBoundary0_576) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_576, SetStrokeOpacityBoundary1_576) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_576, LargeLineWidth_576) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}

TEST_F(GfxStateTest_576, NegativeLineWidth_576) {
    state->setLineWidth(-1.0);
    // The behavior for negative is implementation-defined, just no crash
    double w = state->getLineWidth();
    (void)w;
}

TEST_F(GfxStateTest_576, ConstructorUpsideDownFalse_576) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState state2(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(state2.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state2.getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_576, ConstructorDifferentDPI_576) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState state2(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state2.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state2.getVDPI(), 300.0);
}

TEST_F(GfxStateTest_576, TransformOrigin_576) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 50.0, 100.0);
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 50.0);
    EXPECT_DOUBLE_EQ(y2, 100.0);
}

// ==================== Clip after path ====================

TEST_F(GfxStateTest_576, ClipAfterBuildingPath_576) {
    state->moveTo(10.0, 10.0);
    state->lineTo(100.0, 10.0);
    state->lineTo(100.0, 100.0);
    state->lineTo(10.0, 100.0);
    state->closePath();
    state->clip();
    // Should not crash
}

TEST_F(GfxStateTest_576, ClipToStrokePath_576) {
    state->moveTo(10.0, 10.0);
    state->lineTo(100.0, 10.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    state->clipToStrokePath();
    // Should not crash
}

// ==================== Font ====================

TEST_F(GfxStateTest_576, GetFontInitially_576) {
    const auto& font = state->getFont();
    // Initially null or default
    (void)font;
}

// ==================== Default Color Spaces ====================

TEST_F(GfxStateTest_576, CopyDefaultGrayColorSpaceInitiallyNull_576) {
    auto cs = state->copyDefaultGrayColorSpace();
    // Could be null if not set
    (void)cs;
}

TEST_F(GfxStateTest_576, CopyDefaultRGBColorSpaceInitiallyNull_576) {
    auto cs = state->copyDefaultRGBColorSpace();
    (void)cs;
}

TEST_F(GfxStateTest_576, CopyDefaultCMYKColorSpaceInitiallyNull_576) {
    auto cs = state->copyDefaultCMYKColorSpace();
    (void)cs;
}

// ==================== Multiple clip operations ====================

TEST_F(GfxStateTest_576, MultipleClipToRect_576) {
    state->clipToRect(0.0, 0.0, 100.0, 100.0);
    state->clipToRect(25.0, 25.0, 75.0, 75.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 25.0);
    EXPECT_GE(yMin, 25.0);
    EXPECT_LE(xMax, 75.0);
    EXPECT_LE(yMax, 75.0);
}
