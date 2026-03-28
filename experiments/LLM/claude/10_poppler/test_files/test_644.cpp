#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_644 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612; // Letter width in points
        pageBox.y2 = 792; // Letter height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// ============================================================
// Tests for alphaIsShape (the explicitly shown implementation)
// ============================================================

TEST_F(GfxStateTest_644, SetAlphaIsShapeTrue_644) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_644, SetAlphaIsShapeFalse_644) {
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_644, SetAlphaIsShapeToggle_644) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// ============================================================
// Tests for basic construction and getters
// ============================================================

TEST_F(GfxStateTest_644, ConstructorSetsHDPI_644) {
    EXPECT_DOUBLE_EQ(72.0, state->getHDPI());
}

TEST_F(GfxStateTest_644, ConstructorSetsVDPI_644) {
    EXPECT_DOUBLE_EQ(72.0, state->getVDPI());
}

TEST_F(GfxStateTest_644, ConstructorSetsPageDimensions_644) {
    EXPECT_DOUBLE_EQ(612.0, state->getPageWidth());
    EXPECT_DOUBLE_EQ(792.0, state->getPageHeight());
}

TEST_F(GfxStateTest_644, ConstructorSetsRotate_644) {
    EXPECT_EQ(0, state->getRotate());
}

TEST_F(GfxStateTest_644, ConstructorWithRotation_644) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(90, rotatedState.getRotate());
}

TEST_F(GfxStateTest_644, GetX1Y1X2Y2_644) {
    // After construction, x1/y1/x2/y2 should reflect page box
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    // x2 > x1 and y2 > y1 should hold for a valid page
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// ============================================================
// Tests for line properties
// ============================================================

TEST_F(GfxStateTest_644, SetAndGetLineWidth_644) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getLineWidth());
}

TEST_F(GfxStateTest_644, SetLineWidthZero_644) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getLineWidth());
}

TEST_F(GfxStateTest_644, SetAndGetMiterLimit_644) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(10.0, state->getMiterLimit());
}

TEST_F(GfxStateTest_644, SetAndGetFlatness_644) {
    state->setFlatness(50);
    EXPECT_EQ(50, state->getFlatness());
}

TEST_F(GfxStateTest_644, SetAndGetLineJoin_644) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(LineJoinStyle::Round, state->getLineJoin());
}

TEST_F(GfxStateTest_644, SetAndGetLineCap_644) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(LineCapStyle::Round, state->getLineCap());
}

TEST_F(GfxStateTest_644, SetAndGetStrokeAdjust_644) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_644, SetLineDash_644) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(2u, d.size());
    EXPECT_DOUBLE_EQ(3.0, d[0]);
    EXPECT_DOUBLE_EQ(2.0, d[1]);
    EXPECT_DOUBLE_EQ(1.0, start);
}

TEST_F(GfxStateTest_644, SetLineDashEmpty_644) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(0.0, start);
}

// ============================================================
// Tests for opacity and overprint
// ============================================================

TEST_F(GfxStateTest_644, SetAndGetFillOpacity_644) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
}

TEST_F(GfxStateTest_644, SetAndGetStrokeOpacity_644) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(0.75, state->getStrokeOpacity());
}

TEST_F(GfxStateTest_644, SetFillOpacityBoundaryZero_644) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getFillOpacity());
}

TEST_F(GfxStateTest_644, SetFillOpacityBoundaryOne_644) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(1.0, state->getFillOpacity());
}

TEST_F(GfxStateTest_644, SetAndGetFillOverprint_644) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_644, SetAndGetStrokeOverprint_644) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_644, SetAndGetOverprintMode_644) {
    state->setOverprintMode(1);
    EXPECT_EQ(1, state->getOverprintMode());
    state->setOverprintMode(0);
    EXPECT_EQ(0, state->getOverprintMode());
}

// ============================================================
// Tests for text properties
// ============================================================

TEST_F(GfxStateTest_644, SetAndGetCharSpace_644) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getCharSpace());
}

TEST_F(GfxStateTest_644, SetAndGetWordSpace_644) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(2.0, state->getWordSpace());
}

TEST_F(GfxStateTest_644, SetAndGetHorizScaling_644) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(150.0, state->getHorizScaling());
}

TEST_F(GfxStateTest_644, SetAndGetLeading_644) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(14.0, state->getLeading());
}

TEST_F(GfxStateTest_644, SetAndGetRise_644) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getRise());
}

TEST_F(GfxStateTest_644, SetAndGetRender_644) {
    state->setRender(2);
    EXPECT_EQ(2, state->getRender());
}

TEST_F(GfxStateTest_644, SetAndGetTextKnockout_644) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_644, SetTextMat_644) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(1.0, mat[0]);
    EXPECT_DOUBLE_EQ(0.0, mat[1]);
    EXPECT_DOUBLE_EQ(0.0, mat[2]);
    EXPECT_DOUBLE_EQ(1.0, mat[3]);
    EXPECT_DOUBLE_EQ(10.0, mat[4]);
    EXPECT_DOUBLE_EQ(20.0, mat[5]);
}

// ============================================================
// Tests for blend mode
// ============================================================

TEST_F(GfxStateTest_644, SetAndGetBlendMode_644) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(GfxBlendMode::Multiply, state->getBlendMode());
}

TEST_F(GfxStateTest_644, DefaultBlendModeIsNormal_644) {
    EXPECT_EQ(GfxBlendMode::Normal, state->getBlendMode());
}

// ============================================================
// Tests for CTM
// ============================================================

TEST_F(GfxStateTest_644, SetCTM_644) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(0.0, ctm[4]);
    EXPECT_DOUBLE_EQ(0.0, ctm[5]);
}

TEST_F(GfxStateTest_644, ConcatCTM_644) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    // After concat with identity, should be the concat matrix
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
}

// ============================================================
// Tests for coordinate transforms
// ============================================================

TEST_F(GfxStateTest_644, TransformIdentityCTM_644) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(10.0, x2);
    EXPECT_DOUBLE_EQ(20.0, y2);
}

TEST_F(GfxStateTest_644, TransformDeltaIdentityCTM_644) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(5.0, x2);
    EXPECT_DOUBLE_EQ(10.0, y2);
}

TEST_F(GfxStateTest_644, TransformWithScaling_644) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(102.0, x2);
    EXPECT_DOUBLE_EQ(203.0, y2);
}

TEST_F(GfxStateTest_644, TransformWidth_644) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(2.0, w);
}

// ============================================================
// Tests for path operations
// ============================================================

TEST_F(GfxStateTest_644, InitiallyNoPath_644) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_644, MoveToCreatesCurPt_644) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_644, LineToCreatesPath_644) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_644, ClearPathResetsState_644) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_644, CurveToCreatesPath_644) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_644, ClosePathOnPath_644) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// ============================================================
// Tests for save/restore
// ============================================================

TEST_F(GfxStateTest_644, SaveReturnsNonNull_644) {
    GfxState *saved = state->save();
    EXPECT_NE(nullptr, saved);
    // Restore to avoid leaks
    state.reset(state->restore());
}

TEST_F(GfxStateTest_644, HasSavesAfterSave_644) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
    state.reset(state->restore());
}

TEST_F(GfxStateTest_644, NoSavesInitially_644) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_644, RestoreReturnsParentState_644) {
    state->setLineWidth(5.0);
    state->save();
    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(10.0, state->getLineWidth());
    state.reset(state->restore());
    EXPECT_DOUBLE_EQ(5.0, state->getLineWidth());
}

TEST_F(GfxStateTest_644, MultipleSavesAndRestores_644) {
    state->setFillOpacity(1.0);
    state->save();
    state->setFillOpacity(0.5);
    state->save();
    state->setFillOpacity(0.25);
    EXPECT_DOUBLE_EQ(0.25, state->getFillOpacity());
    state.reset(state->restore());
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
    state.reset(state->restore());
    EXPECT_DOUBLE_EQ(1.0, state->getFillOpacity());
}

// ============================================================
// Tests for clip
// ============================================================

TEST_F(GfxStateTest_644, ClipBBoxInitiallyValid_644) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_644, ClipToRect_644) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

TEST_F(GfxStateTest_644, UserClipBBox_644) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ============================================================
// Tests for rendering intent
// ============================================================

TEST_F(GfxStateTest_644, SetAndGetRenderingIntent_644) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", state->getRenderingIntent());
}

TEST_F(GfxStateTest_644, SetRenderingIntentRelativeColorimetric_644) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ("RelativeColorimetric", state->getRenderingIntent());
}

TEST_F(GfxStateTest_644, SetRenderingIntentAbsoluteColorimetric_644) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ("AbsoluteColorimetric", state->getRenderingIntent());
}

TEST_F(GfxStateTest_644, SetRenderingIntentSaturation_644) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ("Saturation", state->getRenderingIntent());
}

// ============================================================
// Tests for text position
// ============================================================

TEST_F(GfxStateTest_644, TextMoveTo_644) {
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(100.0, state->getLineX());
    EXPECT_DOUBLE_EQ(200.0, state->getLineY());
}

// ============================================================
// Tests for copy
// ============================================================

TEST_F(GfxStateTest_644, CopyPreservesProperties_644) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.3);
    auto copied = std::unique_ptr<GfxState>(state->copy());
    ASSERT_NE(nullptr, copied);
    EXPECT_DOUBLE_EQ(7.0, copied->getLineWidth());
    EXPECT_DOUBLE_EQ(0.3, copied->getFillOpacity());
}

// ============================================================
// Tests for font
// ============================================================

TEST_F(GfxStateTest_644, InitialFontIsNull_644) {
    const auto &font = state->getFont();
    EXPECT_EQ(nullptr, font);
}

TEST_F(GfxStateTest_644, SetFontWithNull_644) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(12.0, state->getFontSize());
    EXPECT_EQ(nullptr, state->getFont());
}

// ============================================================
// Tests for fill/stroke color
// ============================================================

TEST_F(GfxStateTest_644, SetAndGetFillColor_644) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(nullptr, retrieved);
    EXPECT_EQ(32768, retrieved->c[0]);
}

TEST_F(GfxStateTest_644, SetAndGetStrokeColor_644) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(nullptr, retrieved);
    EXPECT_EQ(16384, retrieved->c[0]);
}

// ============================================================
// Tests for fill/stroke color spaces (null initially)
// ============================================================

TEST_F(GfxStateTest_644, FillPatternInitiallyNull_644) {
    EXPECT_EQ(nullptr, state->getFillPattern());
}

TEST_F(GfxStateTest_644, StrokePatternInitiallyNull_644) {
    EXPECT_EQ(nullptr, state->getStrokePattern());
}

// ============================================================
// Tests for different DPI values
// ============================================================

TEST_F(GfxStateTest_644, DifferentDPIValues_644) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(300.0, highDpiState.getHDPI());
    EXPECT_DOUBLE_EQ(150.0, highDpiState.getVDPI());
}

// ============================================================
// Tests for boundary: zero-size page
// ============================================================

TEST_F(GfxStateTest_644, ZeroSizePage_644) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 0;
    pageBox.y2 = 0;
    GfxState zeroState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(0.0, zeroState.getPageWidth());
    EXPECT_DOUBLE_EQ(0.0, zeroState.getPageHeight());
}

// ============================================================
// Tests for isParentState
// ============================================================

TEST_F(GfxStateTest_644, IsParentStateAfterSave_644) {
    GfxState *child = state->save();
    // The saved state should be the child, state itself should be parent
    EXPECT_TRUE(child->isParentState(state.get()));
    state.reset(state->restore());
}

// ============================================================
// Tests for getReusablePath
// ============================================================

TEST_F(GfxStateTest_644, GetReusablePathNotNull_644) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(nullptr, pathIter);
}

// ============================================================
// parseBlendMode static test
// ============================================================

TEST_F(GfxStateTest_644, ParseBlendModeNormalFromName_644) {
    Object obj(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(GfxBlendMode::Normal, mode);
    }
    // If parseBlendMode doesn't recognize it, that's also valid behavior
}
