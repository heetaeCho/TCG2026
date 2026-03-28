#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <memory>
#include <vector>

#include "GfxState.h"

// Helper to create a PDFRectangle for constructing GfxState
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle box;
    box.x1 = x1;
    box.y1 = y1;
    box.x2 = x2;
    box.y2 = y2;
    return box;
}

class GfxStateTest_607 : public ::testing::Test {
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

// ==================== getTextMat tests ====================

TEST_F(GfxStateTest_607, GetTextMatReturnsDefaultIdentityLike_607) {
    const std::array<double, 6> &textMat = state->getTextMat();
    // Default text matrix should be identity-like: [1, 0, 0, 1, 0, 0]
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[2], 0.0);
    EXPECT_DOUBLE_EQ(textMat[3], 1.0);
    EXPECT_DOUBLE_EQ(textMat[4], 0.0);
    EXPECT_DOUBLE_EQ(textMat[5], 0.0);
}

TEST_F(GfxStateTest_607, SetTextMatUpdatesTextMat_607) {
    state->setTextMat(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
    const std::array<double, 6> &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 2.0);
    EXPECT_DOUBLE_EQ(textMat[1], 3.0);
    EXPECT_DOUBLE_EQ(textMat[2], 4.0);
    EXPECT_DOUBLE_EQ(textMat[3], 5.0);
    EXPECT_DOUBLE_EQ(textMat[4], 6.0);
    EXPECT_DOUBLE_EQ(textMat[5], 7.0);
}

TEST_F(GfxStateTest_607, SetTextMatZeroMatrix_607) {
    state->setTextMat(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    const std::array<double, 6> &textMat = state->getTextMat();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(textMat[i], 0.0);
    }
}

TEST_F(GfxStateTest_607, SetTextMatNegativeValues_607) {
    state->setTextMat(-1.0, -2.0, -3.0, -4.0, -5.0, -6.0);
    const std::array<double, 6> &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], -1.0);
    EXPECT_DOUBLE_EQ(textMat[1], -2.0);
    EXPECT_DOUBLE_EQ(textMat[2], -3.0);
    EXPECT_DOUBLE_EQ(textMat[3], -4.0);
    EXPECT_DOUBLE_EQ(textMat[4], -5.0);
    EXPECT_DOUBLE_EQ(textMat[5], -6.0);
}

TEST_F(GfxStateTest_607, SetTextMatLargeValues_607) {
    state->setTextMat(1e10, 1e10, 1e10, 1e10, 1e10, 1e10);
    const std::array<double, 6> &textMat = state->getTextMat();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(textMat[i], 1e10);
    }
}

TEST_F(GfxStateTest_607, SetTextMatVerySmallValues_607) {
    state->setTextMat(1e-15, 1e-15, 1e-15, 1e-15, 1e-15, 1e-15);
    const std::array<double, 6> &textMat = state->getTextMat();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(textMat[i], 1e-15);
    }
}

TEST_F(GfxStateTest_607, GetTextMatReturnsReference_607) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const std::array<double, 6> &ref1 = state->getTextMat();
    const std::array<double, 6> &ref2 = state->getTextMat();
    // Both references should point to the same data
    EXPECT_EQ(&ref1, &ref2);
}

TEST_F(GfxStateTest_607, TextMatSurvivesMultipleSets_607) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const std::array<double, 6> &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 2.0);
    EXPECT_DOUBLE_EQ(textMat[3], 2.0);
    EXPECT_DOUBLE_EQ(textMat[4], 10.0);
    EXPECT_DOUBLE_EQ(textMat[5], 20.0);
}

// ==================== Constructor / basic getters ====================

TEST_F(GfxStateTest_607, ConstructorSetsHDPI_607) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_607, ConstructorSetsVDPI_607) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_607, ConstructorSetsPageWidth_607) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_607, ConstructorSetsPageHeight_607) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_607, ConstructorSetsRotate_607) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_607, ConstructorWithRotation_607) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// ==================== CTM tests ====================

TEST_F(GfxStateTest_607, GetCTMReturnsArray_607) {
    const std::array<double, 6> &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_607, SetCTMUpdatesCTM_607) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const std::array<double, 6> &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// ==================== Line properties ====================

TEST_F(GfxStateTest_607, SetGetLineWidth_607) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_607, SetLineWidthZero_607) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_607, SetGetMiterLimit_607) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

TEST_F(GfxStateTest_607, SetGetFlatness_607) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

TEST_F(GfxStateTest_607, SetGetLineJoin_607) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

TEST_F(GfxStateTest_607, SetGetLineCap_607) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

TEST_F(GfxStateTest_607, SetGetLineDash_607) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const std::vector<double> &resultDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(resultDash.size(), 2u);
    EXPECT_DOUBLE_EQ(resultDash[0], 3.0);
    EXPECT_DOUBLE_EQ(resultDash[1], 5.0);
}

TEST_F(GfxStateTest_607, SetLineDashEmpty_607) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const std::vector<double> &resultDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(resultDash.size(), 0u);
}

// ==================== Text properties ====================

TEST_F(GfxStateTest_607, SetGetCharSpace_607) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_607, SetGetWordSpace_607) {
    state->setWordSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.5);
}

TEST_F(GfxStateTest_607, SetGetHorizScaling_607) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_607, SetGetLeading_607) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_607, SetGetRise_607) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_607, SetGetRender_607) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// ==================== Opacity and blend mode ====================

TEST_F(GfxStateTest_607, SetGetFillOpacity_607) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_607, SetGetStrokeOpacity_607) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_607, SetGetFillOverprint_607) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_607, SetGetStrokeOverprint_607) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_607, SetGetOverprintMode_607) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

TEST_F(GfxStateTest_607, SetGetStrokeAdjust_607) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_607, SetGetAlphaIsShape_607) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_607, SetGetTextKnockout_607) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// ==================== Save / Restore ====================

TEST_F(GfxStateTest_607, SaveAndRestore_607) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);

    GfxState *restored = state->restore();
    // After restore, we should get back the original state
    EXPECT_NE(restored, nullptr);
}

TEST_F(GfxStateTest_607, HasSavesInitiallyFalse_607) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_607, HasSavesTrueAfterSave_607) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// ==================== Path operations ====================

TEST_F(GfxStateTest_607, InitiallyNoCurrentPoint_607) {
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_607, InitiallyNoPath_607) {
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_607, MoveToSetsCurPt_607) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_607, LineToCreatesPath_607) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_607, ClearPathResetsState_607) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_607, ClosePathOnMovedTo_607) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// ==================== Transform ====================

TEST_F(GfxStateTest_607, TransformWithIdentityCTM_607) {
    // Set identity CTM first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_607, TransformDeltaWithIdentityCTM_607) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_607, TransformWithScaledCTM_607) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_607, TransformWithTranslation_607) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 200.0);
}

// ==================== Text transform ====================

TEST_F(GfxStateTest_607, TextTransformWithDefaultMat_607) {
    double x2, y2;
    state->textTransform(1.0, 0.0, &x2, &y2);
    // With default text matrix [1,0,0,1,0,0], should pass through
    // but then gets transformed by CTM
}

// ==================== Rendering intent ====================

TEST_F(GfxStateTest_607, SetGetRenderingIntent_607) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_607, SetRenderingIntentAbsoluteColorimetric_607) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_607, SetRenderingIntentPerceptual_607) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_607, SetRenderingIntentSaturation_607) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// ==================== Copy ====================

TEST_F(GfxStateTest_607, CopyPreservesTextMat_607) {
    state->setTextMat(3.0, 1.0, 2.0, 4.0, 5.0, 6.0);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    const std::array<double, 6> &textMat = copied->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 3.0);
    EXPECT_DOUBLE_EQ(textMat[1], 1.0);
    EXPECT_DOUBLE_EQ(textMat[2], 2.0);
    EXPECT_DOUBLE_EQ(textMat[3], 4.0);
    EXPECT_DOUBLE_EQ(textMat[4], 5.0);
    EXPECT_DOUBLE_EQ(textMat[5], 6.0);
}

TEST_F(GfxStateTest_607, CopyPreservesLineWidth_607) {
    state->setLineWidth(7.5);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
}

TEST_F(GfxStateTest_607, CopyPreservesOpacity_607) {
    state->setFillOpacity(0.3);
    state->setStrokeOpacity(0.6);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
    EXPECT_DOUBLE_EQ(copied->getStrokeOpacity(), 0.6);
}

// ==================== Clip bbox ====================

TEST_F(GfxStateTest_607, GetClipBBox_607) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid clip box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_607, GetUserClipBBox_607) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ==================== ClipToRect ====================

TEST_F(GfxStateTest_607, ClipToRectRestrictsClipBBox_607) {
    state->clipToRect(100.0, 200.0, 300.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0 - 1e-6);
    EXPECT_GE(yMin, 200.0 - 1e-6);
    EXPECT_LE(xMax, 300.0 + 1e-6);
    EXPECT_LE(yMax, 400.0 + 1e-6);
}

// ==================== Font ====================

TEST_F(GfxStateTest_607, DefaultFontIsNull_607) {
    const std::shared_ptr<GfxFont> &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxStateTest_607, DefaultFontSizeIsZero_607) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// ==================== Coordinate getters ====================

TEST_F(GfxStateTest_607, GetCurXY_607) {
    // Should return default values without crash
    double x = state->getCurX();
    double y = state->getCurY();
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

TEST_F(GfxStateTest_607, GetLineXY_607) {
    double x = state->getLineX();
    double y = state->getLineY();
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

// ==================== textMoveTo ====================

TEST_F(GfxStateTest_607, TextMoveToUpdatesLineCoords_607) {
    state->textMoveTo(10.0, 20.0);
    // lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// ==================== Page box coordinates ====================

TEST_F(GfxStateTest_607, GetX1Y1X2Y2_607) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// ==================== Different page boxes ====================

TEST_F(GfxStateTest_607, ConstructorDifferentPageBox_607) {
    PDFRectangle pageBox = makePageBox(0, 0, 1000, 2000);
    GfxState bigState(150.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(bigState.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(bigState.getVDPI(), 150.0);
    EXPECT_DOUBLE_EQ(bigState.getPageWidth(), 1000.0);
    EXPECT_DOUBLE_EQ(bigState.getPageHeight(), 2000.0);
}

// ==================== ConcatCTM ====================

TEST_F(GfxStateTest_607, ConcatCTMWithIdentity_607) {
    const std::array<double, 6> ctmBefore = state->getCTM();
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const std::array<double, 6> &ctmAfter = state->getCTM();
    for (int i = 0; i < 6; i++) {
        EXPECT_NEAR(ctmAfter[i], ctmBefore[i], 1e-10);
    }
}

// ==================== GetPath ====================

TEST_F(GfxStateTest_607, GetPathNotNull_607) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// ==================== Color getters (default state) ====================

TEST_F(GfxStateTest_607, GetFillColorNotNull_607) {
    const GfxColor *color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_607, GetStrokeColorNotNull_607) {
    const GfxColor *color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

// ==================== Blend mode ====================

TEST_F(GfxStateTest_607, DefaultBlendMode_607) {
    GfxBlendMode mode = state->getBlendMode();
    EXPECT_EQ(mode, gfxBlendNormal);
}

TEST_F(GfxStateTest_607, SetBlendMode_607) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// ==================== TransformWidth ====================

TEST_F(GfxStateTest_607, TransformWidthZero_607) {
    double w = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(w, 0.0);
}

TEST_F(GfxStateTest_607, TransformWidthPositive_607) {
    double w = state->transformWidth(1.0);
    EXPECT_GE(w, 0.0);
}

// ==================== ShiftCTMAndClip ====================

TEST_F(GfxStateTest_607, ShiftCTMAndClipDoesNotCrash_607) {
    state->shiftCTMAndClip(10.0, 20.0);
    // Verify CTM translation components changed
    const std::array<double, 6> &ctm = state->getCTM();
    // Just ensure no crash, and CTM is still valid
    EXPECT_EQ(ctm.size(), 6u);
}

// ==================== Set fill/stroke color ====================

TEST_F(GfxStateTest_607, SetFillColorAndGet_607) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_607, SetStrokeColorAndGet_607) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 65535);
}

// ==================== GetCTM to Matrix ====================

TEST_F(GfxStateTest_607, GetCTMAsMatrix_607) {
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

// ==================== GetTransformedLineWidth ====================

TEST_F(GfxStateTest_607, GetTransformedLineWidthDefault_607) {
    double w = state->getTransformedLineWidth();
    EXPECT_GE(w, 0.0);
}

// ==================== CurveTo ====================

TEST_F(GfxStateTest_607, CurveToCreatesPath_607) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}
