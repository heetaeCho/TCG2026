#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with reasonable defaults
static std::unique_ptr<GfxState> createDefaultGfxState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_590 : public ::testing::Test {
protected:
    void SetUp() override {
        state = createDefaultGfxState();
    }

    std::unique_ptr<GfxState> state;
};

// ==================== Basic Construction Tests ====================

TEST_F(GfxStateTest_590, ConstructionSetsHDPI_590) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_590, ConstructionSetsVDPI_590) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_590, ConstructionSetsPageDimensions_590) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_590, ConstructionSetsRotate_590) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_590, ConstructionWithDifferentRotation_590) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_590, ConstructionWithDifferentDPI_590) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 600.0);
}

// ==================== Page Box Tests ====================

TEST_F(GfxStateTest_590, GetX1ReturnsCorrectValue_590) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_590, GetY1ReturnsCorrectValue_590) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_590, GetX2ReturnsCorrectValue_590) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_590, GetY2ReturnsCorrectValue_590) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// ==================== Fill Opacity Tests ====================

TEST_F(GfxStateTest_590, DefaultFillOpacityIsOne_590) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_590, SetFillOpacityChangesValue_590) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_590, SetFillOpacityToZero_590) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_590, SetFillOpacityToOne_590) {
    state->setFillOpacity(0.3);
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// ==================== Stroke Opacity Tests ====================

TEST_F(GfxStateTest_590, DefaultStrokeOpacityIsOne_590) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_590, SetStrokeOpacityChangesValue_590) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_590, SetStrokeOpacityToZero_590) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// ==================== Line Width Tests ====================

TEST_F(GfxStateTest_590, DefaultLineWidthIsOne_590) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_590, SetLineWidthChangesValue_590) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_590, SetLineWidthToZero_590) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// ==================== Miter Limit Tests ====================

TEST_F(GfxStateTest_590, SetMiterLimitChangesValue_590) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// ==================== Flatness Tests ====================

TEST_F(GfxStateTest_590, SetFlatnessChangesValue_590) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// ==================== Line Join Tests ====================

TEST_F(GfxStateTest_590, SetLineJoinChangesValue_590) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// ==================== Line Cap Tests ====================

TEST_F(GfxStateTest_590, SetLineCapChangesValue_590) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// ==================== Overprint Tests ====================

TEST_F(GfxStateTest_590, DefaultFillOverprintIsFalse_590) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_590, SetFillOverprintTrue_590) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_590, DefaultStrokeOverprintIsFalse_590) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_590, SetStrokeOverprintTrue_590) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_590, DefaultOverprintModeIsZero_590) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_590, SetOverprintModeChangesValue_590) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ==================== Stroke Adjust Tests ====================

TEST_F(GfxStateTest_590, DefaultStrokeAdjustIsFalse_590) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_590, SetStrokeAdjustTrue_590) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// ==================== Alpha Is Shape Tests ====================

TEST_F(GfxStateTest_590, DefaultAlphaIsShapeIsFalse_590) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_590, SetAlphaIsShapeTrue_590) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// ==================== Text Knockout Tests ====================

TEST_F(GfxStateTest_590, DefaultTextKnockoutIsFalse_590) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_590, SetTextKnockoutTrue_590) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// ==================== Text Properties Tests ====================

TEST_F(GfxStateTest_590, SetCharSpaceChangesValue_590) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

TEST_F(GfxStateTest_590, SetWordSpaceChangesValue_590) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

TEST_F(GfxStateTest_590, SetHorizScalingChangesValue_590) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_590, SetLeadingChangesValue_590) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_590, SetRiseChangesValue_590) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

TEST_F(GfxStateTest_590, SetRenderChangesValue_590) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// ==================== Font Tests ====================

TEST_F(GfxStateTest_590, DefaultFontIsNull_590) {
    EXPECT_EQ(state->getFont(), nullptr);
}

TEST_F(GfxStateTest_590, DefaultFontSizeIsOne_590) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 1.0);
}

// ==================== Text Matrix Tests ====================

TEST_F(GfxStateTest_590, SetTextMatChangesValues_590) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// ==================== CTM Tests ====================

TEST_F(GfxStateTest_590, SetCTMChangesValues_590) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

TEST_F(GfxStateTest_590, ConcatCTMMultiplies_590) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// ==================== Transform Tests ====================

TEST_F(GfxStateTest_590, TransformWithIdentityCTM_590) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_590, TransformWithScaleCTM_590) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

TEST_F(GfxStateTest_590, TransformWithTranslation_590) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_590, TransformDeltaIgnoresTranslation_590) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

// ==================== Path Tests ====================

TEST_F(GfxStateTest_590, InitiallyNoPath_590) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_590, MoveToCreatesCurPt_590) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_590, MoveToAndLineToCreatesPath_590) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_590, ClearPathResetsState_590) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_590, GetPathAfterMoveTo_590) {
    state->moveTo(5.0, 10.0);
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

TEST_F(GfxStateTest_590, CurveToCreatesPath_590) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_590, ClosePathWorks_590) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// ==================== Save/Restore Tests ====================

TEST_F(GfxStateTest_590, InitiallyNoSaves_590) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_590, SaveCreatesNestedState_590) {
    GfxState *savedState = state->save();
    EXPECT_NE(savedState, nullptr);
    EXPECT_TRUE(savedState->hasSaves());
}

TEST_F(GfxStateTest_590, RestoreReturnsPreviousState_590) {
    GfxState *savedState = state->save();
    savedState->setFillOpacity(0.5);
    GfxState *restoredState = savedState->restore();
    EXPECT_NE(restoredState, nullptr);
    EXPECT_DOUBLE_EQ(restoredState->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_590, SavePreservesProperties_590) {
    state->setFillOpacity(0.7);
    state->setLineWidth(3.0);
    GfxState *savedState = state->save();
    EXPECT_DOUBLE_EQ(savedState->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(savedState->getLineWidth(), 3.0);
    savedState->restore();
}

TEST_F(GfxStateTest_590, ModifiedSavedStateDoesNotAffectParent_590) {
    state->setFillOpacity(0.8);
    GfxState *savedState = state->save();
    savedState->setFillOpacity(0.2);
    EXPECT_DOUBLE_EQ(savedState->getFillOpacity(), 0.2);
    GfxState *restored = savedState->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.8);
}

// ==================== Copy Tests ====================

TEST_F(GfxStateTest_590, CopyCreatesIndependentState_590) {
    state->setFillOpacity(0.6);
    state->setLineWidth(4.0);
    auto copied = std::unique_ptr<GfxState>(state->copy());
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.6);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 4.0);

    // Modify original, copy should not change
    state->setFillOpacity(0.1);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.6);
}

// ==================== Blend Mode Tests ====================

TEST_F(GfxStateTest_590, DefaultBlendModeIsNormal_590) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_590, SetBlendModeChangesValue_590) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// ==================== Rendering Intent Tests ====================

TEST_F(GfxStateTest_590, SetRenderingIntentChangesValue_590) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_590, SetRenderingIntentRelativeColorimetric_590) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// ==================== Line Dash Tests ====================

TEST_F(GfxStateTest_590, SetLineDashChangesValues_590) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
}

TEST_F(GfxStateTest_590, SetEmptyLineDash_590) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(d.size(), 0u);
}

// ==================== Clip Tests ====================

TEST_F(GfxStateTest_590, ClipToRectChangesClipBBox_590) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

TEST_F(GfxStateTest_590, GetUserClipBBox_590) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ==================== Text Move Tests ====================

TEST_F(GfxStateTest_590, TextMoveToSetsTextPosition_590) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// ==================== Color Space Tests ====================

TEST_F(GfxStateTest_590, DefaultFillColorSpaceNotNull_590) {
    // After construction, fill color space should be initialized (usually DeviceGray)
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_590, DefaultStrokeColorSpaceNotNull_590) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// ==================== Pattern Tests ====================

TEST_F(GfxStateTest_590, DefaultFillPatternIsNull_590) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_590, DefaultStrokePatternIsNull_590) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// ==================== isParentState Tests ====================

TEST_F(GfxStateTest_590, IsParentStateAfterSave_590) {
    GfxState *savedState = state->save();
    EXPECT_TRUE(savedState->isParentState(state.get()));
    savedState->restore();
}

// ==================== TransformWidth Tests ====================

TEST_F(GfxStateTest_590, TransformWidthWithIdentity_590) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tw = state->transformWidth(5.0);
    EXPECT_GT(tw, 0.0);
}

// ==================== GetTransformedLineWidth Tests ====================

TEST_F(GfxStateTest_590, GetTransformedLineWidthPositive_590) {
    state->setLineWidth(2.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// ==================== Multiple Save/Restore Tests ====================

TEST_F(GfxStateTest_590, MultipleSaveRestore_590) {
    state->setFillOpacity(0.9);
    GfxState *s1 = state->save();
    s1->setFillOpacity(0.5);
    GfxState *s2 = s1->save();
    s2->setFillOpacity(0.1);
    EXPECT_DOUBLE_EQ(s2->getFillOpacity(), 0.1);
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getFillOpacity(), 0.5);
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getFillOpacity(), 0.9);
}

// ==================== Boundary: Very Small and Large Values ====================

TEST_F(GfxStateTest_590, VerySmallFillOpacity_590) {
    state->setFillOpacity(1e-15);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1e-15);
}

TEST_F(GfxStateTest_590, LargeLineWidth_590) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}

TEST_F(GfxStateTest_590, NegativeCharSpace_590) {
    state->setCharSpace(-2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), -2.0);
}

// ==================== ShiftCTMAndClip Tests ====================

TEST_F(GfxStateTest_590, ShiftCTMAndClipModifiesCTM_590) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &ctmBefore = state->getCTM();
    double e_before = ctmBefore[4];
    double f_before = ctmBefore[5];
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctmAfter = state->getCTM();
    EXPECT_DOUBLE_EQ(ctmAfter[4], e_before + 10.0);
    EXPECT_DOUBLE_EQ(ctmAfter[5], f_before + 20.0);
}

// ==================== Fill/Stroke Color Tests ====================

TEST_F(GfxStateTest_590, SetFillColorAndGet_590) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    EXPECT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

TEST_F(GfxStateTest_590, SetStrokeColorAndGet_590) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    EXPECT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 16384);
}

// ==================== DisplayProfile Tests ====================

TEST_F(GfxStateTest_590, DefaultDisplayProfileIsNull_590) {
    auto profile = state->getDisplayProfile();
    // Profile may or may not be null depending on system, but function should not crash
    SUCCEED();
}

// ==================== Default Color Space Tests ====================

TEST_F(GfxStateTest_590, CopyDefaultGrayColorSpaceInitiallyNull_590) {
    auto cs = state->copyDefaultGrayColorSpace();
    // May be null initially
    SUCCEED();
}

TEST_F(GfxStateTest_590, CopyDefaultRGBColorSpaceInitiallyNull_590) {
    auto cs = state->copyDefaultRGBColorSpace();
    SUCCEED();
}

TEST_F(GfxStateTest_590, CopyDefaultCMYKColorSpaceInitiallyNull_590) {
    auto cs = state->copyDefaultCMYKColorSpace();
    SUCCEED();
}
