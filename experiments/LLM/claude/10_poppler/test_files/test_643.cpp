#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <cstring>

class GfxStateTest_643 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a default page box
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = new GfxState(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        delete state;
    }

    GfxState *state;
};

// Test basic construction and DPI values
TEST_F(GfxStateTest_643, GetHDPI_ReturnsCorrectValue_643) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_643, GetVDPI_ReturnsCorrectValue_643) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_643, GetPageWidth_ReturnsCorrectValue_643) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_643, GetPageHeight_ReturnsCorrectValue_643) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_643, GetRotate_ReturnsZeroForNoRotation_643) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test stroke adjust
TEST_F(GfxStateTest_643, SetStrokeAdjust_True_643) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_643, SetStrokeAdjust_False_643) {
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_643, SetStrokeAdjust_ToggleTrueThenFalse_643) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test line width
TEST_F(GfxStateTest_643, SetLineWidth_ReturnsCorrectValue_643) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_643, SetLineWidth_Zero_643) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_643, SetLineWidth_LargeValue_643) {
    state->setLineWidth(1000.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1000.0);
}

// Test flatness
TEST_F(GfxStateTest_643, SetFlatness_ReturnsCorrectValue_643) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

TEST_F(GfxStateTest_643, SetFlatness_Zero_643) {
    state->setFlatness(0);
    EXPECT_EQ(state->getFlatness(), 0);
}

// Test line join
TEST_F(GfxStateTest_643, SetLineJoin_Miter_643) {
    state->setLineJoin(LineJoinStyle::Miter);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Miter);
}

TEST_F(GfxStateTest_643, SetLineJoin_Round_643) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_643, SetLineJoin_Bevel_643) {
    state->setLineJoin(LineJoinStyle::Bevel);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Bevel);
}

// Test line cap
TEST_F(GfxStateTest_643, SetLineCap_Butt_643) {
    state->setLineCap(LineCapStyle::Butt);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Butt);
}

TEST_F(GfxStateTest_643, SetLineCap_Round_643) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_643, SetLineCap_Projecting_643) {
    state->setLineCap(LineCapStyle::Projecting);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Projecting);
}

// Test miter limit
TEST_F(GfxStateTest_643, SetMiterLimit_ReturnsCorrectValue_643) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_643, SetMiterLimit_SmallValue_643) {
    state->setMiterLimit(1.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 1.0);
}

// Test fill opacity
TEST_F(GfxStateTest_643, SetFillOpacity_ReturnsCorrectValue_643) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_643, SetFillOpacity_Zero_643) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_643, SetFillOpacity_One_643) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test stroke opacity
TEST_F(GfxStateTest_643, SetStrokeOpacity_ReturnsCorrectValue_643) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_643, SetStrokeOpacity_Zero_643) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// Test fill overprint
TEST_F(GfxStateTest_643, SetFillOverprint_True_643) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_643, SetFillOverprint_False_643) {
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_643, SetStrokeOverprint_True_643) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_643, SetStrokeOverprint_False_643) {
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_643, SetOverprintMode_ReturnsCorrectValue_643) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

TEST_F(GfxStateTest_643, SetOverprintMode_Zero_643) {
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test alpha is shape
TEST_F(GfxStateTest_643, SetAlphaIsShape_True_643) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_643, SetAlphaIsShape_False_643) {
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_643, SetTextKnockout_True_643) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

TEST_F(GfxStateTest_643, SetTextKnockout_False_643) {
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test char space
TEST_F(GfxStateTest_643, SetCharSpace_ReturnsCorrectValue_643) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_643, SetCharSpace_Zero_643) {
    state->setCharSpace(0.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_643, SetCharSpace_Negative_643) {
    state->setCharSpace(-0.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), -0.5);
}

// Test word space
TEST_F(GfxStateTest_643, SetWordSpace_ReturnsCorrectValue_643) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_643, SetWordSpace_Zero_643) {
    state->setWordSpace(0.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_643, SetHorizScaling_ReturnsCorrectValue_643) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_643, SetHorizScaling_Default_643) {
    state->setHorizScaling(100.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 100.0);
}

// Test leading
TEST_F(GfxStateTest_643, SetLeading_ReturnsCorrectValue_643) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_643, SetRise_ReturnsCorrectValue_643) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_643, SetRise_Negative_643) {
    state->setRise(-2.0);
    EXPECT_DOUBLE_EQ(state->getRise(), -2.0);
}

// Test render
TEST_F(GfxStateTest_643, SetRender_ReturnsCorrectValue_643) {
    state->setRender(1);
    EXPECT_EQ(state->getRender(), 1);
}

TEST_F(GfxStateTest_643, SetRender_Zero_643) {
    state->setRender(0);
    EXPECT_EQ(state->getRender(), 0);
}

// Test rendering intent
TEST_F(GfxStateTest_643, SetRenderingIntent_AbsoluteColorimetric_643) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_643, SetRenderingIntent_Perceptual_643) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_643, SetRenderingIntent_RelativeColorimetric_643) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_643, SetRenderingIntent_Saturation_643) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test font size
TEST_F(GfxStateTest_643, GetFontSize_Default_643) {
    // Font size should be whatever the default is (0 likely)
    // We just ensure it doesn't crash
    double fs = state->getFontSize();
    (void)fs;
}

// Test CTM operations
TEST_F(GfxStateTest_643, SetCTM_ReturnsCorrectValues_643) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_643, ConcatCTM_ModifiesCTM_643) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 10.0);
}

// Test transform
TEST_F(GfxStateTest_643, Transform_IdentityCTM_643) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_643, Transform_ScaledCTM_643) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_643, Transform_WithTranslation_643) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

TEST_F(GfxStateTest_643, TransformDelta_IdentityCTM_643) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test save and restore
TEST_F(GfxStateTest_643, SaveAndRestore_643) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
    state = restored;
}

TEST_F(GfxStateTest_643, HasSaves_InitiallyFalse_643) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_643, HasSaves_TrueAfterSave_643) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    state = saved->restore();
}

// Test path operations
TEST_F(GfxStateTest_643, IsPath_InitiallyFalse_643) {
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_643, IsCurPt_InitiallyFalse_643) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_643, MoveTo_SetsCurrentPoint_643) {
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_643, LineTo_AddsToPath_643) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_643, CurveTo_AddsToPath_643) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_643, ClosePath_ClosesSubpath_643) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_643, ClearPath_ResetsPath_643) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test text operations
TEST_F(GfxStateTest_643, TextMoveTo_SetsTextPosition_643) {
    state->textMoveTo(100.0, 200.0);
    // Verify line position is updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test text matrix
TEST_F(GfxStateTest_643, SetTextMat_ReturnsCorrectValues_643) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// Test blend mode
TEST_F(GfxStateTest_643, SetBlendMode_Normal_643) {
    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_643, SetBlendMode_Multiply_643) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test clip bbox
TEST_F(GfxStateTest_643, GetClipBBox_ReturnsValues_643) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Just ensure it returns without crashing and values are reasonable
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test user clip bbox
TEST_F(GfxStateTest_643, GetUserClipBBox_ReturnsValues_643) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clip to rect
TEST_F(GfxStateTest_643, ClipToRect_NarrowsClipRegion_643) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// Test copy
TEST_F(GfxStateTest_643, Copy_CopiesState_643) {
    state->setLineWidth(7.5);
    state->setStrokeAdjust(true);
    state->setFillOpacity(0.3);

    GfxState *copied = state->copy();
    ASSERT_NE(copied, nullptr);

    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_TRUE(copied->getStrokeAdjust());
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);

    delete copied;
}

// Test page coordinates
TEST_F(GfxStateTest_643, GetX1Y1X2Y2_ReturnPageBounds_643) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test line dash
TEST_F(GfxStateTest_643, SetLineDash_ReturnsCorrectValues_643) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_643, SetLineDash_EmptyDash_643) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(d.size(), 0u);
}

TEST_F(GfxStateTest_643, SetLineDash_WithNonZeroStart_643) {
    std::vector<double> dash = {2.0, 4.0, 6.0};
    state->setLineDash(std::move(dash), 1.5);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.5);
    ASSERT_EQ(d.size(), 3u);
}

// Test with different page orientations
TEST_F(GfxStateTest_643, ConstructWithRotation90_643) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState *rotatedState = new GfxState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
    EXPECT_DOUBLE_EQ(rotatedState->getPageWidth(), 792.0);
    EXPECT_DOUBLE_EQ(rotatedState->getPageHeight(), 612.0);
    delete rotatedState;
}

// Test transform width
TEST_F(GfxStateTest_643, TransformWidth_IdentityCTM_643) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

TEST_F(GfxStateTest_643, TransformWidth_ScaledCTM_643) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 10.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_643, GetTransformedLineWidth_643) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tw, 3.0);
}

// Test text shift
TEST_F(GfxStateTest_643, TextShift_UpdatesPosition_643) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textMoveTo(0.0, 0.0);
    double initialX = state->getCurX();
    double initialY = state->getCurY();
    state->textShift(10.0, 5.0);
    // After shift, position should change
    // We just verify it doesn't crash and that curX/curY changed
    double newX = state->getCurX();
    double newY = state->getCurY();
    // The exact behavior depends on the text matrix, but with identity it should shift
    EXPECT_NE(newX, initialX);
}

// Test isParentState
TEST_F(GfxStateTest_643, IsParentState_AfterSave_643) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state));
    state = child->restore();
}

TEST_F(GfxStateTest_643, IsParentState_NoRelation_643) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState *other = new GfxState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(other));
    delete other;
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_643, ShiftCTMAndClip_643) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// Test multiple save/restore operations
TEST_F(GfxStateTest_643, MultipleSaveRestore_643) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);

    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);

    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);

    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);

    state = r2;
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_643, GetCTM_Matrix_643) {
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

// Test fill color
TEST_F(GfxStateTest_643, SetFillColor_643) {
    GfxColor color;
    color.c[0] = 65535;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0;
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    EXPECT_EQ(fc->c[0], 65535);
}

// Test stroke color
TEST_F(GfxStateTest_643, SetStrokeColor_643) {
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 65535;
    color.c[2] = 0;
    color.c[3] = 0;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    EXPECT_EQ(sc->c[1], 65535);
}

// Test getReusablePath doesn't return null
TEST_F(GfxStateTest_643, GetReusablePath_NotNull_643) {
    state->clearPath();
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto path = state->getReusablePath();
    EXPECT_NE(path, nullptr);
}

// Test getPath doesn't return null
TEST_F(GfxStateTest_643, GetPath_NotNull_643) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test construction with different DPI
TEST_F(GfxStateTest_643, ConstructWithDifferentDPI_643) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState *highDpiState = new GfxState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState->getVDPI(), 300.0);
    delete highDpiState;
}

// Test construction with non-uniform DPI
TEST_F(GfxStateTest_643, ConstructWithNonUniformDPI_643) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState *nonUniformState = new GfxState(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(nonUniformState->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(nonUniformState->getVDPI(), 300.0);
    delete nonUniformState;
}
