#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with default parameters
static GfxState* createDefaultState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return new GfxState(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_612 : public ::testing::Test {
protected:
    GfxState* state;

    void SetUp() override {
        state = createDefaultState();
    }

    void TearDown() override {
        delete state;
    }
};

// ============================================================
// Constructor and basic getter tests
// ============================================================

TEST_F(GfxStateTest_612, ConstructorSetsHDPI_612) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_612, ConstructorSetsVDPI_612) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_612, ConstructorSetsRotate_612) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_612, ConstructorSetsPageWidth_612) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_612, ConstructorSetsPageHeight_612) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_612, GetX1_612) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_612, GetY1_612) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_612, GetX2_612) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_612, GetY2_612) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// ============================================================
// Rise getter/setter tests
// ============================================================

TEST_F(GfxStateTest_612, DefaultRiseIsZero_612) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_612, SetRisePositive_612) {
    state->setRise(5.5);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.5);
}

TEST_F(GfxStateTest_612, SetRiseNegative_612) {
    state->setRise(-3.2);
    EXPECT_DOUBLE_EQ(state->getRise(), -3.2);
}

TEST_F(GfxStateTest_612, SetRiseZero_612) {
    state->setRise(10.0);
    state->setRise(0.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// ============================================================
// Line width tests
// ============================================================

TEST_F(GfxStateTest_612, SetLineWidth_612) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_612, SetLineWidthZero_612) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// ============================================================
// Fill and stroke opacity tests
// ============================================================

TEST_F(GfxStateTest_612, DefaultFillOpacity_612) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_612, DefaultStrokeOpacity_612) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_612, SetFillOpacity_612) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_612, SetStrokeOpacity_612) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// ============================================================
// Overprint tests
// ============================================================

TEST_F(GfxStateTest_612, DefaultFillOverprintFalse_612) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_612, DefaultStrokeOverprintFalse_612) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_612, SetFillOverprint_612) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_612, SetStrokeOverprint_612) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_612, DefaultOverprintMode_612) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_612, SetOverprintMode_612) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ============================================================
// Text property tests
// ============================================================

TEST_F(GfxStateTest_612, DefaultCharSpaceIsZero_612) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_612, SetCharSpace_612) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_612, DefaultWordSpaceIsZero_612) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_612, SetWordSpace_612) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_612, DefaultHorizScaling_612) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_612, SetHorizScaling_612) {
    state->setHorizScaling(0.8);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.8);
}

TEST_F(GfxStateTest_612, DefaultLeadingIsZero_612) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_612, SetLeading_612) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_612, DefaultRender_612) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_612, SetRender_612) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// ============================================================
// Flatness tests
// ============================================================

TEST_F(GfxStateTest_612, DefaultFlatness_612) {
    EXPECT_EQ(state->getFlatness(), 0);
}

TEST_F(GfxStateTest_612, SetFlatness_612) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// ============================================================
// Miter limit tests
// ============================================================

TEST_F(GfxStateTest_612, SetMiterLimit_612) {
    state->setMiterLimit(8.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 8.0);
}

// ============================================================
// Stroke adjust, alpha is shape, text knockout
// ============================================================

TEST_F(GfxStateTest_612, DefaultStrokeAdjust_612) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_612, SetStrokeAdjust_612) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_612, DefaultAlphaIsShape_612) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_612, SetAlphaIsShape_612) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_612, DefaultTextKnockout_612) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_612, SetTextKnockout_612) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// ============================================================
// Line join and line cap tests
// ============================================================

TEST_F(GfxStateTest_612, SetLineJoin_612) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_612, SetLineCap_612) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// ============================================================
// CTM tests
// ============================================================

TEST_F(GfxStateTest_612, GetCTMReturnsArray_612) {
    const auto& ctm = state->getCTM();
    // Identity-like CTM for default state (scaled by DPI/72)
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_612, SetCTM_612) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_612, ConcatCTM_612) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// ============================================================
// Transform tests
// ============================================================

TEST_F(GfxStateTest_612, TransformIdentity_612) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_612, TransformWithScale_612) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_612, TransformDelta_612) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// ============================================================
// Text matrix tests
// ============================================================

TEST_F(GfxStateTest_612, SetTextMat_612) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto& tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// ============================================================
// Path operations tests
// ============================================================

TEST_F(GfxStateTest_612, InitiallyNoPath_612) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_612, MoveToSetsCurPt_612) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_612, LineToCreatesPath_612) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_612, ClearPathResetsState_612) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_612, CurveToCreatesPath_612) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_612, ClosePathOnPath_612) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// ============================================================
// Save/Restore tests
// ============================================================

TEST_F(GfxStateTest_612, SaveReturnsSavedState_612) {
    GfxState* saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
    // Restore to clean up
    state = state->restore();
}

TEST_F(GfxStateTest_612, RestoreReturnsParentState_612) {
    state->setRise(7.0);
    GfxState* savedState = state->save();
    savedState->setRise(15.0);
    EXPECT_DOUBLE_EQ(savedState->getRise(), 15.0);
    GfxState* restored = savedState->restore();
    EXPECT_DOUBLE_EQ(restored->getRise(), 7.0);
    // restored should be the original state
    state = restored;
}

TEST_F(GfxStateTest_612, HasSavesInitiallyFalse_612) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_612, MultipleSaveRestore_612) {
    state->setLineWidth(1.0);
    GfxState* s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState* s2 = s1->save();
    s2->setLineWidth(3.0);
    
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    GfxState* r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    GfxState* r0 = r1->restore();
    EXPECT_DOUBLE_EQ(r0->getLineWidth(), 1.0);
    state = r0;
}

// ============================================================
// Copy test
// ============================================================

TEST_F(GfxStateTest_612, CopyPreservesProperties_612) {
    state->setRise(3.14);
    state->setLineWidth(2.5);
    state->setFillOpacity(0.7);
    
    GfxState* copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getRise(), 3.14);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 2.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    delete copied;
}

// ============================================================
// Blend mode tests
// ============================================================

TEST_F(GfxStateTest_612, DefaultBlendMode_612) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_612, SetBlendMode_612) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// ============================================================
// LineDash tests
// ============================================================

TEST_F(GfxStateTest_612, SetLineDash_612) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
}

TEST_F(GfxStateTest_612, EmptyLineDash_612) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// ============================================================
// Rendering intent tests
// ============================================================

TEST_F(GfxStateTest_612, SetRenderingIntent_612) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_612, SetRenderingIntentRelativeColorimetric_612) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// ============================================================
// Clip bounding box tests
// ============================================================

TEST_F(GfxStateTest_612, GetClipBBox_612) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be set to some valid values
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_612, ClipToRect_612) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ============================================================
// Font tests
// ============================================================

TEST_F(GfxStateTest_612, DefaultFontIsNull_612) {
    const auto& font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxStateTest_612, DefaultFontSizeIsZero_612) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// ============================================================
// Color space tests (null by default for fill/stroke patterns)
// ============================================================

TEST_F(GfxStateTest_612, DefaultFillPatternIsNull_612) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_612, DefaultStrokePatternIsNull_612) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// ============================================================
// Text position tests
// ============================================================

TEST_F(GfxStateTest_612, TextMoveTo_612) {
    state->textMoveTo(10.0, 20.0);
    // After textMoveTo, the line position should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// ============================================================
// isParentState test
// ============================================================

TEST_F(GfxStateTest_612, IsParentState_612) {
    GfxState* child = state->save();
    EXPECT_TRUE(child->isParentState(state));
    state = child->restore();
}

// ============================================================
// Rotate constructor test
// ============================================================

TEST(GfxStateRotateTest_612, ConstructWithRotate90_612) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState* st = new GfxState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(st->getRotate(), 90);
    EXPECT_GT(st->getPageWidth(), 0);
    EXPECT_GT(st->getPageHeight(), 0);
    delete st;
}

TEST(GfxStateRotateTest_612, ConstructWithRotate180_612) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState* st = new GfxState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(st->getRotate(), 180);
    delete st;
}

TEST(GfxStateRotateTest_612, ConstructWithRotate270_612) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState* st = new GfxState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(st->getRotate(), 270);
    delete st;
}

// ============================================================
// Different DPI test
// ============================================================

TEST(GfxStateDPITest_612, HighDPI_612) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState* st = new GfxState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(st->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(st->getVDPI(), 300.0);
    delete st;
}

// ============================================================
// TransformWidth test
// ============================================================

TEST_F(GfxStateTest_612, TransformWidth_612) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

TEST_F(GfxStateTest_612, TransformWidthZero_612) {
    double w = state->transformWidth(0.0);
    EXPECT_GE(w, 0.0);
}

// ============================================================
// getUserClipBBox test
// ============================================================

TEST_F(GfxStateTest_612, GetUserClipBBox_612) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ============================================================
// ShiftCTMAndClip test
// ============================================================

TEST_F(GfxStateTest_612, ShiftCTMAndClip_612) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ============================================================
// GetReusablePath test
// ============================================================

TEST_F(GfxStateTest_612, GetReusablePathNotNull_612) {
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// ============================================================
// Boundary: very large values
// ============================================================

TEST_F(GfxStateTest_612, VeryLargeRise_612) {
    state->setRise(1e15);
    EXPECT_DOUBLE_EQ(state->getRise(), 1e15);
}

TEST_F(GfxStateTest_612, VerySmallNegativeRise_612) {
    state->setRise(-1e15);
    EXPECT_DOUBLE_EQ(state->getRise(), -1e15);
}

TEST_F(GfxStateTest_612, VeryLargeLineWidth_612) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}
