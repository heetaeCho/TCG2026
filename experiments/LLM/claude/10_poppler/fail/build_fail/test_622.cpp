#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makeRect(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_622 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle rect = makeRect(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &rect, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test constructor and basic getters
TEST_F(GfxStateTest_622, ConstructorInitializesHDPI_622) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_622, ConstructorInitializesVDPI_622) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_622, ConstructorInitializesPageDimensions_622) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_622, ConstructorInitializesRotate_622) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_622, GetX1Y1X2Y2_622) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test with rotation
TEST_F(GfxStateTest_622, ConstructorWithRotation90_622) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &rect, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

TEST_F(GfxStateTest_622, ConstructorWithRotation180_622) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &rect, 180, true);
    EXPECT_EQ(rotatedState->getRotate(), 180);
}

TEST_F(GfxStateTest_622, ConstructorWithRotation270_622) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &rect, 270, true);
    EXPECT_EQ(rotatedState->getRotate(), 270);
}

// Test CTM
TEST_F(GfxStateTest_622, GetCTMReturnsArray_622) {
    const auto& ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_622, SetCTM_622) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_622, ConcatCTM_622) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test line width
TEST_F(GfxStateTest_622, SetAndGetLineWidth_622) {
    state->setLineWidth(3.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.5);
}

TEST_F(GfxStateTest_622, SetLineWidthZero_622) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test flatness
TEST_F(GfxStateTest_622, SetAndGetFlatness_622) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test line join
TEST_F(GfxStateTest_622, SetAndGetLineJoin_622) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test line cap
TEST_F(GfxStateTest_622, SetAndGetLineCap_622) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test miter limit
TEST_F(GfxStateTest_622, SetAndGetMiterLimit_622) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

// Test stroke adjust
TEST_F(GfxStateTest_622, SetAndGetStrokeAdjust_622) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_622, SetAndGetAlphaIsShape_622) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_622, SetAndGetTextKnockout_622) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test fill opacity
TEST_F(GfxStateTest_622, SetAndGetFillOpacity_622) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_622, SetFillOpacityZero_622) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_622, SetFillOpacityOne_622) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test stroke opacity
TEST_F(GfxStateTest_622, SetAndGetStrokeOpacity_622) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test fill overprint
TEST_F(GfxStateTest_622, SetAndGetFillOverprint_622) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_622, SetAndGetStrokeOverprint_622) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_622, SetAndGetOverprintMode_622) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test char space
TEST_F(GfxStateTest_622, SetAndGetCharSpace_622) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

// Test word space
TEST_F(GfxStateTest_622, SetAndGetWordSpace_622) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test horiz scaling
TEST_F(GfxStateTest_622, SetAndGetHorizScaling_622) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test leading
TEST_F(GfxStateTest_622, SetAndGetLeading_622) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_622, SetAndGetRise_622) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test render
TEST_F(GfxStateTest_622, SetAndGetRender_622) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test rendering intent
TEST_F(GfxStateTest_622, SetAndGetRenderingIntent_622) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_622, SetRenderingIntentRelativeColorimetric_622) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_622, SetRenderingIntentSaturation_622) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_622, SetRenderingIntentAbsoluteColorimetric_622) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test text matrix
TEST_F(GfxStateTest_622, SetAndGetTextMat_622) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto& mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// Test font size
TEST_F(GfxStateTest_622, GetFontSize_622) {
    // Font size should have some default or set value
    double fs = state->getFontSize();
    // Just verify it returns a value (default is typically 0)
    EXPECT_GE(fs, 0.0);
}

// Test line dash
TEST_F(GfxStateTest_622, SetAndGetLineDash_622) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
}

TEST_F(GfxStateTest_622, SetLineDashEmpty_622) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(result.empty());
}

// Test blend mode
TEST_F(GfxStateTest_622, SetAndGetBlendMode_622) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_622, SetBlendModeNormal_622) {
    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// Test path operations
TEST_F(GfxStateTest_622, InitialPathState_622) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_622, MoveToSetsCurPt_622) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_622, MoveToLineTo_622) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_622, CurveTo_622) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_622, ClosePath_622) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_622, ClearPath_622) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test text position
TEST_F(GfxStateTest_622, TextMoveTo_622) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

TEST_F(GfxStateTest_622, GetLineY_622) {
    state->textMoveTo(50.0, 75.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 75.0);
}

TEST_F(GfxStateTest_622, GetLineX_622) {
    state->textMoveTo(50.0, 75.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
}

// Test save/restore
TEST_F(GfxStateTest_622, SaveCreatesNewState_622) {
    GfxState* saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
}

TEST_F(GfxStateTest_622, RestoreReturnsParentState_622) {
    state->setLineWidth(5.0);
    GfxState* child = state->save();
    child->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(child->getLineWidth(), 10.0);
    GfxState* parent = child->restore();
    EXPECT_NE(parent, nullptr);
    EXPECT_DOUBLE_EQ(parent->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_622, HasSavesInitiallyFalse_622) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_622, MultipleSaveRestore_622) {
    state->setLineWidth(1.0);
    GfxState* s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState* s2 = s1->save();
    s2->setLineWidth(3.0);

    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    GfxState* r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    GfxState* r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
}

// Test transform
TEST_F(GfxStateTest_622, TransformIdentity_622) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_622, TransformWithTranslation_622) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_622, TransformWithScaling_622) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

TEST_F(GfxStateTest_622, TransformDeltaIdentity_622) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test copy
TEST_F(GfxStateTest_622, CopyCreatesIndependentState_622) {
    state->setLineWidth(7.5);
    auto copied = state->copy();
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    copied->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 7.5);
    delete copied;
}

// Test clip operations
TEST_F(GfxStateTest_622, GetClipBBox_622) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip box should be initialized to the page bounds
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_622, GetUserClipBBox_622) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_622, ClipToRect_622) {
    state->clipToRect(100.0, 100.0, 300.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip box should be constrained
    EXPECT_GE(xMin, 0.0);
    EXPECT_GE(yMin, 0.0);
}

// Test getPath
TEST_F(GfxStateTest_622, GetPathNotNull_622) {
    const GfxPath* path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test getCurX/getCurY
TEST_F(GfxStateTest_622, GetCurXY_622) {
    // Initially should be at some default position
    double x = state->getCurX();
    double y = state->getCurY();
    // Just verifying it doesn't crash and returns values
    (void)x;
    (void)y;
}

// Test fill and stroke color
TEST_F(GfxStateTest_622, GetFillColor_622) {
    const GfxColor* color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_622, GetStrokeColor_622) {
    const GfxColor* color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_622, SetFillColor_622) {
    GfxColor color;
    color.c[0] = 32768;
    state->setFillColor(&color);
    const GfxColor* result = state->getFillColor();
    EXPECT_EQ(result->c[0], 32768);
}

TEST_F(GfxStateTest_622, SetStrokeColor_622) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor* result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 16384);
}

// Test transformWidth
TEST_F(GfxStateTest_622, TransformWidth_622) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

TEST_F(GfxStateTest_622, TransformWidthZero_622) {
    double w = state->transformWidth(0.0);
    EXPECT_GE(w, 0.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_622, ShiftCTMAndClip_622) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test isParentState
TEST_F(GfxStateTest_622, IsParentState_622) {
    GfxState* child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    child->restore();
}

// Test getReusablePath
TEST_F(GfxStateTest_622, GetReusablePath_622) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test with different DPI values
TEST_F(GfxStateTest_622, HighDPI_622) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto highDpiState = std::make_unique<GfxState>(300.0, 300.0, &rect, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState->getVDPI(), 300.0);
}

// Test with non-standard page size
TEST_F(GfxStateTest_622, NonStandardPageBox_622) {
    PDFRectangle rect = makeRect(10, 20, 400, 600);
    auto customState = std::make_unique<GfxState>(72.0, 72.0, &rect, 0, true);
    EXPECT_DOUBLE_EQ(customState->getPageWidth(), 390.0);
    EXPECT_DOUBLE_EQ(customState->getPageHeight(), 580.0);
}

// Test upsideDown false
TEST_F(GfxStateTest_622, NotUpsideDown_622) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    auto nonFlippedState = std::make_unique<GfxState>(72.0, 72.0, &rect, 0, false);
    EXPECT_DOUBLE_EQ(nonFlippedState->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(nonFlippedState->getPageHeight(), 792.0);
}

// Test getFont initially null
TEST_F(GfxStateTest_622, GetFontInitiallyNull_622) {
    const auto& font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_622, GetTransformedLineWidth_622) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test textShift
TEST_F(GfxStateTest_622, TextShift_622) {
    state->textMoveTo(10.0, 20.0);
    double origX = state->getCurX();
    double origY = state->getCurY();
    state->textShift(5.0, 3.0);
    // After text shift, current position should change
    // We just verify it doesn't crash
    (void)origX;
    (void)origY;
}

// Test save preserves properties
TEST_F(GfxStateTest_622, SavePreservesLineWidth_622) {
    state->setLineWidth(4.0);
    GfxState* saved = state->save();
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 4.0);
    saved->restore();
}

TEST_F(GfxStateTest_622, SavePreservesOpacity_622) {
    state->setFillOpacity(0.3);
    state->setStrokeOpacity(0.7);
    GfxState* saved = state->save();
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.3);
    EXPECT_DOUBLE_EQ(saved->getStrokeOpacity(), 0.7);
    saved->restore();
}

// Test parseBlendMode static method
TEST_F(GfxStateTest_622, ParseBlendModeNormal_622) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// Test clip
TEST_F(GfxStateTest_622, ClipWithPath_622) {
    state->moveTo(100.0, 100.0);
    state->lineTo(200.0, 100.0);
    state->lineTo(200.0, 200.0);
    state->closePath();
    state->clip();
    // Verify clip box has been updated
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_622, GetCTMWithMatrix_622) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify the matrix is populated (implementation-dependent order)
    // Just ensure it doesn't crash
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_622, GetTransformedFontSize_622) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tfSize = state->getTransformedFontSize();
    EXPECT_GE(tfSize, 0.0);
}

// Test getFontTransMat
TEST_F(GfxStateTest_622, GetFontTransMat_622) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Just verify it doesn't crash and returns values
    (void)m11;
    (void)m12;
    (void)m21;
    (void)m22;
}

// Test negative values
TEST_F(GfxStateTest_622, NegativeLineWidth_622) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

TEST_F(GfxStateTest_622, NegativeCharSpace_622) {
    state->setCharSpace(-2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), -2.0);
}

TEST_F(GfxStateTest_622, NegativeWordSpace_622) {
    state->setWordSpace(-1.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), -1.5);
}

TEST_F(GfxStateTest_622, NegativeRise_622) {
    state->setRise(-3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), -3.0);
}

// Test large values
TEST_F(GfxStateTest_622, LargeLineWidth_622) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}

TEST_F(GfxStateTest_622, LargeOpacity_622) {
    state->setFillOpacity(1e10);
    // Implementation may clamp or store as-is
    double opac = state->getFillOpacity();
    (void)opac; // Just ensure no crash
}
