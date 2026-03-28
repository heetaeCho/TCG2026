#include <gtest/gtest.h>
#include "GfxState.h"

class GfxStateTest_623 : public ::testing::Test {
protected:
    GfxState* state;

    void SetUp() override {
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
};

// Test isCurPt returns false when no path operations have been performed
TEST_F(GfxStateTest_623, IsCurPtReturnsFalseInitially_623) {
    EXPECT_FALSE(state->isCurPt());
}

// Test isCurPt returns true after moveTo (moveTo sets a current point)
TEST_F(GfxStateTest_623, IsCurPtReturnsTrueAfterMoveTo_623) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test isCurPt returns true after moveTo followed by lineTo
TEST_F(GfxStateTest_623, IsCurPtReturnsTrueAfterLineTo_623) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test isCurPt returns true after curveTo
TEST_F(GfxStateTest_623, IsCurPtReturnsTrueAfterCurveTo_623) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 10.0, 20.0, 20.0, 30.0, 30.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test isCurPt returns false after clearPath
TEST_F(GfxStateTest_623, IsCurPtReturnsFalseAfterClearPath_623) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
}

// Test isCurPt returns true after closePath (still has current point)
TEST_F(GfxStateTest_623, IsCurPtAfterClosePath_623) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isCurPt());
}

// Test isPath returns false initially
TEST_F(GfxStateTest_623, IsPathReturnsFalseInitially_623) {
    EXPECT_FALSE(state->isPath());
}

// Test isPath returns true after constructing a line segment
TEST_F(GfxStateTest_623, IsPathReturnsTrueAfterLineTo_623) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

// Test that moveTo alone is not considered a "path" (just a current point)
TEST_F(GfxStateTest_623, IsPathReturnsFalseAfterMoveToOnly_623) {
    state->moveTo(5.0, 5.0);
    // moveTo alone doesn't create a path segment
    EXPECT_FALSE(state->isPath());
}

// Test getPath returns non-null
TEST_F(GfxStateTest_623, GetPathReturnsNonNull_623) {
    EXPECT_NE(state->getPath(), nullptr);
}

// Test initial DPI values
TEST_F(GfxStateTest_623, GetDPIValues_623) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test initial page dimensions
TEST_F(GfxStateTest_623, GetPageDimensions_623) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test getRotate returns initial rotation
TEST_F(GfxStateTest_623, GetRotateReturnsInitial_623) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test setting and getting line width
TEST_F(GfxStateTest_623, SetAndGetLineWidth_623) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test setting and getting fill opacity
TEST_F(GfxStateTest_623, SetAndGetFillOpacity_623) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setting and getting stroke opacity
TEST_F(GfxStateTest_623, SetAndGetStrokeOpacity_623) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setting and getting flatness
TEST_F(GfxStateTest_623, SetAndGetFlatness_623) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test setting and getting miter limit
TEST_F(GfxStateTest_623, SetAndGetMiterLimit_623) {
    state->setMiterLimit(8.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 8.0);
}

// Test setting and getting char space
TEST_F(GfxStateTest_623, SetAndGetCharSpace_623) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test setting and getting word space
TEST_F(GfxStateTest_623, SetAndGetWordSpace_623) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setting and getting horizontal scaling
TEST_F(GfxStateTest_623, SetAndGetHorizScaling_623) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setting and getting leading
TEST_F(GfxStateTest_623, SetAndGetLeading_623) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setting and getting rise
TEST_F(GfxStateTest_623, SetAndGetRise_623) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test setting and getting render
TEST_F(GfxStateTest_623, SetAndGetRender_623) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setting and getting fill overprint
TEST_F(GfxStateTest_623, SetAndGetFillOverprint_623) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setting and getting stroke overprint
TEST_F(GfxStateTest_623, SetAndGetStrokeOverprint_623) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test setting and getting overprint mode
TEST_F(GfxStateTest_623, SetAndGetOverprintMode_623) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setting and getting stroke adjust
TEST_F(GfxStateTest_623, SetAndGetStrokeAdjust_623) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setting and getting alpha is shape
TEST_F(GfxStateTest_623, SetAndGetAlphaIsShape_623) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test setting and getting text knockout
TEST_F(GfxStateTest_623, SetAndGetTextKnockout_623) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test setting and getting line join style
TEST_F(GfxStateTest_623, SetAndGetLineJoin_623) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test setting and getting line cap style
TEST_F(GfxStateTest_623, SetAndGetLineCap_623) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test save and restore
TEST_F(GfxStateTest_623, SaveAndRestore_623) {
    state->setLineWidth(5.0);
    EXPECT_FALSE(state->hasSaves());

    GfxState* savedState = state->save();
    EXPECT_TRUE(savedState->hasSaves());

    savedState->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(savedState->getLineWidth(), 10.0);

    GfxState* restoredState = savedState->restore();
    EXPECT_DOUBLE_EQ(restoredState->getLineWidth(), 5.0);
    state = restoredState;  // Update for TearDown
}

// Test hasSaves returns false initially
TEST_F(GfxStateTest_623, HasSavesReturnsFalseInitially_623) {
    EXPECT_FALSE(state->hasSaves());
}

// Test getCurX and getCurY after moveTo
TEST_F(GfxStateTest_623, GetCurXYAfterMoveTo_623) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test multiple moveTo operations - last one should be the current point
TEST_F(GfxStateTest_623, MultipleMoveToCurPt_623) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    state->moveTo(30.0, 40.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test clearPath resets both isCurPt and isPath
TEST_F(GfxStateTest_623, ClearPathResetsState_623) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test isCurPt after moveTo followed by clearPath followed by moveTo
TEST_F(GfxStateTest_623, IsCurPtAfterClearAndMoveTo_623) {
    state->moveTo(0.0, 0.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    state->moveTo(5.0, 5.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test setting rendering intent
TEST_F(GfxStateTest_623, SetAndGetRenderingIntent_623) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setting text matrix
TEST_F(GfxStateTest_623, SetAndGetTextMat_623) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto& mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// Test CTM getter
TEST_F(GfxStateTest_623, GetCTM_623) {
    const auto& ctm = state->getCTM();
    // CTM should be a valid 6-element array
    EXPECT_EQ(ctm.size(), 6u);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_623, GetBoundingBox_623) {
    // These should return the page box values (possibly transformed)
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    // x2 should be >= x1 and y2 should be >= y1
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test getClipBBox
TEST_F(GfxStateTest_623, GetClipBBox_623) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test transform
TEST_F(GfxStateTest_623, TransformPoint_623) {
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Result depends on CTM, but should not crash
}

// Test transformDelta
TEST_F(GfxStateTest_623, TransformDelta_623) {
    double x2, y2;
    state->transformDelta(1.0, 1.0, &x2, &y2);
    // Should not crash
}

// Test copy
TEST_F(GfxStateTest_623, CopyState_623) {
    state->setLineWidth(3.0);
    GfxState* copied = state->copy();
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    delete copied;
}

// Test copy with path
TEST_F(GfxStateTest_623, CopyStateWithPath_623) {
    state->moveTo(10.0, 20.0);
    GfxState* copied = state->copy(true);
    EXPECT_TRUE(copied->isCurPt());
    delete copied;
}

// Test copy without path
TEST_F(GfxStateTest_623, CopyStateWithoutPath_623) {
    state->moveTo(10.0, 20.0);
    GfxState* copied = state->copy(false);
    // Without copying path, the new state should have a fresh path
    EXPECT_FALSE(copied->isCurPt());
    delete copied;
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_623, SetAndGetLineDash_623) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
}

// Test blend mode
TEST_F(GfxStateTest_623, SetAndGetBlendMode_623) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test fontSize
TEST_F(GfxStateTest_623, GetFontSizeDefault_623) {
    double fontSize = state->getFontSize();
    // Default font size should be some reasonable value
    EXPECT_GE(fontSize, 0.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_623, TextMoveTo_623) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test that a complex path retains isCurPt
TEST_F(GfxStateTest_623, ComplexPathRetainsCurPt_623) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->lineTo(0.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test setting CTM
TEST_F(GfxStateTest_623, SetCTM_623) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test boundary: zero line width
TEST_F(GfxStateTest_623, ZeroLineWidth_623) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test boundary: negative line width (should still be settable)
TEST_F(GfxStateTest_623, NegativeLineWidth_623) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test boundary: opacity at extremes
TEST_F(GfxStateTest_623, OpacityBoundary_623) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test save/restore preserves isCurPt state
TEST_F(GfxStateTest_623, SaveRestorePreservesPathState_623) {
    state->moveTo(5.0, 5.0);
    EXPECT_TRUE(state->isCurPt());

    GfxState* savedState = state->save();
    EXPECT_TRUE(savedState->isCurPt());

    savedState->clearPath();
    EXPECT_FALSE(savedState->isCurPt());

    GfxState* restoredState = savedState->restore();
    EXPECT_TRUE(restoredState->isCurPt());
    state = restoredState;
}

// Test empty line dash
TEST_F(GfxStateTest_623, EmptyLineDash_623) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(result.empty());
}

// Test getUserClipBBox
TEST_F(GfxStateTest_623, GetUserClipBBox_623) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_623, ClipToRect_623) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip box should be intersected with the new rect
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}
