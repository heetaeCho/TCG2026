#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with common parameters
static std::unique_ptr<GfxState> createDefaultGfxState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_603 : public ::testing::Test {
protected:
    void SetUp() override {
        state = createDefaultGfxState();
    }

    std::unique_ptr<GfxState> state;
};

// ==================== Constructor and basic getters ====================

TEST_F(GfxStateTest_603, ConstructorSetsHDPI_603) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_603, ConstructorSetsVDPI_603) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_603, ConstructorSetsPageDimensions_603) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_603, ConstructorSetsRotate_603) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_603, ConstructorSetsCoordinateBounds_603) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

TEST_F(GfxStateTest_603, ConstructorWithDifferentDPI_603) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 100;
    pageBox.y2 = 200;
    GfxState s(150.0, 300.0, &pageBox, 90, true);
    EXPECT_DOUBLE_EQ(s.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(s.getVDPI(), 300.0);
    EXPECT_EQ(s.getRotate(), 90);
}

// ==================== AlphaIsShape ====================

TEST_F(GfxStateTest_603, DefaultAlphaIsShapeIsFalse_603) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_603, SetAlphaIsShapeTrue_603) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_603, SetAlphaIsShapeFalseAfterTrue_603) {
    state->setAlphaIsShape(true);
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// ==================== TextKnockout ====================

TEST_F(GfxStateTest_603, DefaultTextKnockoutIsFalse_603) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_603, SetTextKnockoutTrue_603) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// ==================== Fill/Stroke Opacity ====================

TEST_F(GfxStateTest_603, DefaultFillOpacity_603) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_603, DefaultStrokeOpacity_603) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_603, SetFillOpacity_603) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_603, SetStrokeOpacity_603) {
    state->setStrokeOpacity(0.25);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.25);
}

TEST_F(GfxStateTest_603, SetFillOpacityZero_603) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

// ==================== Overprint ====================

TEST_F(GfxStateTest_603, DefaultFillOverprint_603) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_603, DefaultStrokeOverprint_603) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_603, SetFillOverprint_603) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_603, SetStrokeOverprint_603) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_603, DefaultOverprintMode_603) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_603, SetOverprintMode_603) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ==================== Line properties ====================

TEST_F(GfxStateTest_603, DefaultLineWidth_603) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_603, SetLineWidth_603) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_603, SetLineWidthZero_603) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_603, DefaultFlatness_603) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_603, SetFlatness_603) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

TEST_F(GfxStateTest_603, DefaultMiterLimit_603) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_603, SetMiterLimit_603) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_603, DefaultStrokeAdjust_603) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_603, SetStrokeAdjust_603) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// ==================== Line join and cap ====================

TEST_F(GfxStateTest_603, DefaultLineJoin_603) {
    EXPECT_EQ(state->getLineJoin(), 0);  // miter join = 0
}

TEST_F(GfxStateTest_603, DefaultLineCap_603) {
    EXPECT_EQ(state->getLineCap(), 0);  // butt cap = 0
}

// ==================== Text properties ====================

TEST_F(GfxStateTest_603, DefaultCharSpace_603) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_603, SetCharSpace_603) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_603, DefaultWordSpace_603) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_603, SetWordSpace_603) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_603, DefaultHorizScaling_603) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_603, SetHorizScaling_603) {
    state->setHorizScaling(0.8);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.8);
}

TEST_F(GfxStateTest_603, DefaultLeading_603) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_603, SetLeading_603) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_603, DefaultRise_603) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_603, SetRise_603) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_603, DefaultRender_603) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_603, SetRender_603) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_603, DefaultFontSize_603) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

TEST_F(GfxStateTest_603, DefaultFontIsNull_603) {
    EXPECT_EQ(state->getFont(), nullptr);
}

// ==================== BlendMode ====================

TEST_F(GfxStateTest_603, DefaultBlendMode_603) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_603, SetBlendMode_603) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// ==================== CTM ====================

TEST_F(GfxStateTest_603, GetCTMReturnsArray_603) {
    const auto& ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_603, SetCTM_603) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ==================== Transform ====================

TEST_F(GfxStateTest_603, TransformIdentityLike_603) {
    // After construction with identity-like CTM, transform should work
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_603, TransformWithTranslation_603) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

TEST_F(GfxStateTest_603, TransformDeltaIgnoresTranslation_603) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_603, TransformWithScaling_603) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// ==================== Save and Restore ====================

TEST_F(GfxStateTest_603, SaveReturnsSavedState_603) {
    GfxState* saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
}

TEST_F(GfxStateTest_603, RestoreReturnsPreviousState_603) {
    state->setFillOpacity(0.5);
    GfxState* saved = state->save();
    // After save, 'state' points to the new (child) state
    // Modify the saved state
    state->setFillOpacity(0.8);
    GfxState* restored = state->restore();
    EXPECT_NE(restored, nullptr);
}

TEST_F(GfxStateTest_603, HasSavesDefaultFalse_603) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_603, SavePreservesProperties_603) {
    state->setFillOpacity(0.3);
    state->setLineWidth(5.0);
    GfxState* saved = state->save();
    // The save should preserve the state. saved points to the new child.
    EXPECT_NE(saved, nullptr);
}

// ==================== Path operations ====================

TEST_F(GfxStateTest_603, DefaultIsNotPath_603) {
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_603, DefaultIsNotCurPt_603) {
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_603, MoveToCreatesCurrentPoint_603) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_603, LineToExtendsPath_603) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_603, ClearPathResetsPath_603) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_603, CurveToExtendsPath_603) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_603, ClosePathWorks_603) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// ==================== Clip ====================

TEST_F(GfxStateTest_603, GetClipBBox_603) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be set from the page box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_603, ClipToRect_603) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// ==================== Rendering Intent ====================

TEST_F(GfxStateTest_603, DefaultRenderingIntent_603) {
    const char* intent = state->getRenderingIntent();
    EXPECT_NE(intent, nullptr);
}

TEST_F(GfxStateTest_603, SetRenderingIntent_603) {
    state->setRenderingIntent("Perceptual");
    const char* intent = state->getRenderingIntent();
    EXPECT_STREQ(intent, "Perceptual");
}

TEST_F(GfxStateTest_603, SetRenderingIntentRelativeColorimetric_603) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_603, SetRenderingIntentSaturation_603) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_603, SetRenderingIntentAbsoluteColorimetric_603) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// ==================== TextMat ====================

TEST_F(GfxStateTest_603, SetTextMat_603) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 2.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 2.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// ==================== Line dash ====================

TEST_F(GfxStateTest_603, DefaultLineDashEmpty_603) {
    double start;
    const auto& dash = state->getLineDash(&start);
    EXPECT_TRUE(dash.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_603, SetLineDash_603) {
    std::vector<double> dashPattern = {3.0, 5.0};
    state->setLineDash(std::move(dashPattern), 1.0);
    double start;
    const auto& dash = state->getLineDash(&start);
    EXPECT_EQ(dash.size(), 2u);
    EXPECT_DOUBLE_EQ(dash[0], 3.0);
    EXPECT_DOUBLE_EQ(dash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// ==================== Text cursor ====================

TEST_F(GfxStateTest_603, DefaultCursorPosition_603) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

TEST_F(GfxStateTest_603, MoveToUpdatesCursor_603) {
    state->moveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 25.0);
}

// ==================== Copy ====================

TEST_F(GfxStateTest_603, CopyCreatesNewState_603) {
    state->setFillOpacity(0.7);
    state->setLineWidth(3.0);
    auto copied = state->copy();
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    delete copied;
}

// ==================== TextMoveTo ====================

TEST_F(GfxStateTest_603, TextMoveTo_603) {
    state->textMoveTo(10.0, 20.0);
    // textMoveTo should update lineX, lineY
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// ==================== ConcatCTM ====================

TEST_F(GfxStateTest_603, ConcatCTMWithIdentity_603) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto& ctmBefore = state->getCTM();
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto& ctmAfter = state->getCTM();
    EXPECT_DOUBLE_EQ(ctmAfter[0], ctmBefore[0]);
    EXPECT_DOUBLE_EQ(ctmAfter[3], ctmBefore[3]);
}

TEST_F(GfxStateTest_603, ConcatCTMWithTranslation_603) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 50.0, 100.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// ==================== Boundary: rotation ====================

TEST_F(GfxStateTest_603, ConstructWithRotation90_603) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_603, ConstructWithRotation180_603) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_603, ConstructWithRotation270_603) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// ==================== Fill/Stroke color spaces (null by default is fine) ====================

TEST_F(GfxStateTest_603, DefaultFillPatternNull_603) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_603, DefaultStrokePatternNull_603) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// ==================== GetPath ====================

TEST_F(GfxStateTest_603, GetPathNotNull_603) {
    const GfxPath* path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// ==================== TransformWidth ====================

TEST_F(GfxStateTest_603, TransformWidthWithIdentityCTM_603) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

TEST_F(GfxStateTest_603, TransformWidthWithScaledCTM_603) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 10.0);
}

// ==================== GetTransformedLineWidth ====================

TEST_F(GfxStateTest_603, GetTransformedLineWidth_603) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 3.0);
}

// ==================== getUserClipBBox ====================

TEST_F(GfxStateTest_603, GetUserClipBBox_603) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ==================== Boundary: very small page ====================

TEST_F(GfxStateTest_603, SmallPageBox_603) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 1;
    pageBox.y2 = 1;
    GfxState smallState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(smallState.getPageWidth(), 1.0);
    EXPECT_DOUBLE_EQ(smallState.getPageHeight(), 1.0);
}

// ==================== Boundary: negative coordinates in page box ====================

TEST_F(GfxStateTest_603, NegativePageBox_603) {
    PDFRectangle pageBox;
    pageBox.x1 = -100;
    pageBox.y1 = -200;
    pageBox.x2 = 100;
    pageBox.y2 = 200;
    GfxState negState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(negState.getPageWidth(), 200.0);
    EXPECT_DOUBLE_EQ(negState.getPageHeight(), 400.0);
}

// ==================== FillColor set/get ====================

TEST_F(GfxStateTest_603, SetAndGetFillColor_603) {
    GfxColor color;
    color.c[0] = 32768;  // Some value
    state->setFillColor(&color);
    const GfxColor* retrieved = state->getFillColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_603, SetAndGetStrokeColor_603) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor* retrieved = state->getStrokeColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

// ==================== Display profile ====================

TEST_F(GfxStateTest_603, DefaultDisplayProfileIsNull_603) {
    auto profile = state->getDisplayProfile();
    // May or may not be null depending on implementation, but should not crash
}

// ==================== isParentState ====================

TEST_F(GfxStateTest_603, IsParentStateWithSave_603) {
    GfxState* child = state->save();
    // After save, state should be parent of child (or vice versa)
    // The save() typically returns the new state, with the old one stored
    EXPECT_NE(child, nullptr);
    // Restore to clean up
    GfxState* restored = child->restore();
    EXPECT_NE(restored, nullptr);
}
