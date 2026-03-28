#include <gtest/gtest.h>
#include "GfxState.h"

class GfxStateTest_661 : public ::testing::Test {
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

// Test moveTo sets curX and curY
TEST_F(GfxStateTest_661, MoveToSetsCurXAndCurY_661) {
    state->moveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

// Test moveTo with zero coordinates
TEST_F(GfxStateTest_661, MoveToZeroCoordinates_661) {
    state->moveTo(0.0, 0.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test moveTo with negative coordinates
TEST_F(GfxStateTest_661, MoveToNegativeCoordinates_661) {
    state->moveTo(-50.0, -100.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), -50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), -100.0);
}

// Test moveTo with large coordinates
TEST_F(GfxStateTest_661, MoveToLargeCoordinates_661) {
    state->moveTo(1e10, 1e10);
    EXPECT_DOUBLE_EQ(state->getCurX(), 1e10);
    EXPECT_DOUBLE_EQ(state->getCurY(), 1e10);
}

// Test moveTo with very small coordinates
TEST_F(GfxStateTest_661, MoveToVerySmallCoordinates_661) {
    state->moveTo(1e-15, 1e-15);
    EXPECT_DOUBLE_EQ(state->getCurX(), 1e-15);
    EXPECT_DOUBLE_EQ(state->getCurY(), 1e-15);
}

// Test multiple moveTo calls overwrite previous values
TEST_F(GfxStateTest_661, MoveToMultipleCalls_661) {
    state->moveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);

    state->moveTo(30.0, 40.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 30.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 40.0);
}

// Test moveTo creates a current point (isCurPt should be true)
TEST_F(GfxStateTest_661, MoveToCreatesCurPt_661) {
    state->moveTo(5.0, 10.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test that path reflects moveTo
TEST_F(GfxStateTest_661, MoveToAffectsPath_661) {
    state->moveTo(50.0, 75.0);
    const GfxPath* path = state->getPath();
    ASSERT_NE(path, nullptr);
    EXPECT_TRUE(path->isCurPt());
}

// Test moveTo followed by lineTo
TEST_F(GfxStateTest_661, MoveToFollowedByLineTo_661) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 30.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 40.0);
    EXPECT_TRUE(state->isPath());
}

// Test moveTo followed by curveTo
TEST_F(GfxStateTest_661, MoveToFollowedByCurveTo_661) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test initial state construction - DPI
TEST_F(GfxStateTest_661, ConstructorSetsDPI_661) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test initial state construction - page dimensions
TEST_F(GfxStateTest_661, ConstructorSetsPageDimensions_661) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test initial state construction - rotate
TEST_F(GfxStateTest_661, ConstructorSetsRotate_661) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test getters and setters for line width
TEST_F(GfxStateTest_661, SetAndGetLineWidth_661) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test getters and setters for flatness
TEST_F(GfxStateTest_661, SetAndGetFlatness_661) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test getters and setters for miter limit
TEST_F(GfxStateTest_661, SetAndGetMiterLimit_661) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test getters and setters for line join
TEST_F(GfxStateTest_661, SetAndGetLineJoin_661) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test getters and setters for line cap
TEST_F(GfxStateTest_661, SetAndGetLineCap_661) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test getters and setters for fill opacity
TEST_F(GfxStateTest_661, SetAndGetFillOpacity_661) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test getters and setters for stroke opacity
TEST_F(GfxStateTest_661, SetAndGetStrokeOpacity_661) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test getters and setters for fill overprint
TEST_F(GfxStateTest_661, SetAndGetFillOverprint_661) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test getters and setters for stroke overprint
TEST_F(GfxStateTest_661, SetAndGetStrokeOverprint_661) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test getters and setters for overprint mode
TEST_F(GfxStateTest_661, SetAndGetOverprintMode_661) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test getters and setters for stroke adjust
TEST_F(GfxStateTest_661, SetAndGetStrokeAdjust_661) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test getters and setters for alpha is shape
TEST_F(GfxStateTest_661, SetAndGetAlphaIsShape_661) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test getters and setters for text knockout
TEST_F(GfxStateTest_661, SetAndGetTextKnockout_661) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test getters and setters for char space
TEST_F(GfxStateTest_661, SetAndGetCharSpace_661) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test getters and setters for word space
TEST_F(GfxStateTest_661, SetAndGetWordSpace_661) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test getters and setters for horiz scaling
TEST_F(GfxStateTest_661, SetAndGetHorizScaling_661) {
    state->setHorizScaling(1.2);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.2);
}

// Test getters and setters for leading
TEST_F(GfxStateTest_661, SetAndGetLeading_661) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test getters and setters for rise
TEST_F(GfxStateTest_661, SetAndGetRise_661) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test getters and setters for render
TEST_F(GfxStateTest_661, SetAndGetRender_661) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test getters and setters for font size
TEST_F(GfxStateTest_661, GetFontSize_661) {
    // Font size is set via setFont; we test the getter
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test save and restore
TEST_F(GfxStateTest_661, SaveAndRestore_661) {
    state->setLineWidth(3.0);
    GfxState* savedState = state->save();
    ASSERT_NE(savedState, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);

    GfxState* restoredState = state->restore();
    ASSERT_NE(restoredState, nullptr);
    EXPECT_DOUBLE_EQ(restoredState->getLineWidth(), 3.0);
    // Note: after restore, state pointer changes
    state = restoredState;
}

// Test hasSaves returns false initially
TEST_F(GfxStateTest_661, HasSavesInitiallyFalse_661) {
    EXPECT_FALSE(state->hasSaves());
}

// Test clearPath
TEST_F(GfxStateTest_661, ClearPath_661) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test textMoveTo sets text position
TEST_F(GfxStateTest_661, TextMoveTo_661) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_661, SetAndGetTextMat_661) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto& tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// Test setCTM
TEST_F(GfxStateTest_661, SetCTM_661) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// Test transform with identity-like CTM
TEST_F(GfxStateTest_661, TransformWithCTM_661) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_661, TransformWithScalingCTM_661) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

// Test transformDelta
TEST_F(GfxStateTest_661, TransformDelta_661) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test rendering intent
TEST_F(GfxStateTest_661, SetAndGetRenderingIntent_661) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test rendering intent with long string (boundary: 31 chars max due to char[32])
TEST_F(GfxStateTest_661, SetRenderingIntentBoundary_661) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test setLineDash
TEST_F(GfxStateTest_661, SetAndGetLineDash_661) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
}

// Test closePath after moveTo and lineTo
TEST_F(GfxStateTest_661, ClosePath_661) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closePath, current point should return to the start of the subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test path with multiple subpaths via moveTo
TEST_F(GfxStateTest_661, MultipleSubpathsViaMoveeTo_661) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->moveTo(20.0, 20.0);
    state->lineTo(30.0, 30.0);

    const GfxPath* path = state->getPath();
    ASSERT_NE(path, nullptr);
    EXPECT_GE(path->getNumSubpaths(), 2);
}

// Test copy
TEST_F(GfxStateTest_661, CopyState_661) {
    state->setLineWidth(4.5);
    state->setFillOpacity(0.8);
    GfxState* copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 4.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
    delete copied;
}

// Test clip bounding box
TEST_F(GfxStateTest_661, GetClipBBox_661) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After construction, clip should be set to some valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect narrows the clip region
TEST_F(GfxStateTest_661, ClipToRect_661) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// Test moveTo with mixed positive/negative coordinates
TEST_F(GfxStateTest_661, MoveToMixedCoordinates_661) {
    state->moveTo(-100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), -100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

// Test construction with rotation
TEST(GfxStateConstructionTest_661, RotatedState_661) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test construction with different DPI
TEST(GfxStateConstructionTest_661, DifferentDPI_661) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 300.0);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_661, GetPageBounds_661) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test blend mode
TEST_F(GfxStateTest_661, SetAndGetBlendMode_661) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test concatCTM
TEST_F(GfxStateTest_661, ConcatCTM_661) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test isPath before and after adding path elements
TEST_F(GfxStateTest_661, IsPathBeforeAndAfter_661) {
    EXPECT_FALSE(state->isPath());
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

// Test save creates saves and hasSaves returns true
TEST_F(GfxStateTest_661, SaveCreatesNestedState_661) {
    EXPECT_FALSE(state->hasSaves());
    state->save();
    EXPECT_TRUE(state->hasSaves());
    state->restore();
}
