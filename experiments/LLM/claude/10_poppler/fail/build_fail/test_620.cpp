#include <gtest/gtest.h>
#include "GfxState.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <cstring>

class GfxStateTest_620 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<GfxState> createDefaultState(double hDPI = 72.0, double vDPI = 72.0,
                                                   double x1 = 0, double y1 = 0,
                                                   double x2 = 612, double y2 = 792,
                                                   int rotate = 0, bool upsideDown = true) {
        PDFRectangle pageBox;
        pageBox.x1 = x1;
        pageBox.y1 = y1;
        pageBox.x2 = x2;
        pageBox.y2 = y2;
        return std::make_unique<GfxState>(hDPI, vDPI, &pageBox, rotate, upsideDown);
    }
};

// ==================== getClipBBox Tests ====================

TEST_F(GfxStateTest_620, GetClipBBox_DefaultState_620) {
    auto state = createDefaultState();
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip bounding box should be set to the page dimensions
    EXPECT_DOUBLE_EQ(xMin, 0.0);
    EXPECT_DOUBLE_EQ(yMin, 0.0);
    EXPECT_LE(xMax, 612.0 + 1.0); // allow small tolerance
    EXPECT_LE(yMax, 792.0 + 1.0);
}

TEST_F(GfxStateTest_620, GetClipBBox_AfterClipToRect_620) {
    auto state = createDefaultState();
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_DOUBLE_EQ(xMin, 10.0);
    EXPECT_DOUBLE_EQ(yMin, 20.0);
    EXPECT_DOUBLE_EQ(xMax, 100.0);
    EXPECT_DOUBLE_EQ(yMax, 200.0);
}

TEST_F(GfxStateTest_620, GetClipBBox_AfterMultipleClipToRect_620) {
    auto state = createDefaultState();
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    state->clipToRect(50.0, 50.0, 80.0, 150.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Intersection of the two rectangles
    EXPECT_DOUBLE_EQ(xMin, 50.0);
    EXPECT_DOUBLE_EQ(yMin, 50.0);
    EXPECT_DOUBLE_EQ(xMax, 80.0);
    EXPECT_DOUBLE_EQ(yMax, 150.0);
}

// ==================== Constructor / Basic Getters ====================

TEST_F(GfxStateTest_620, ConstructorSetsHDPI_620) {
    auto state = createDefaultState(150.0, 300.0);
    EXPECT_DOUBLE_EQ(state->getHDPI(), 150.0);
}

TEST_F(GfxStateTest_620, ConstructorSetsVDPI_620) {
    auto state = createDefaultState(150.0, 300.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 300.0);
}

TEST_F(GfxStateTest_620, ConstructorSetsPageDimensions_620) {
    auto state = createDefaultState(72.0, 72.0, 0, 0, 612, 792);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_620, ConstructorSetsRotate_620) {
    PDFRectangle pageBox;
    pageBox.x1 = 0; pageBox.y1 = 0; pageBox.x2 = 612; pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
}

// ==================== Line Width ====================

TEST_F(GfxStateTest_620, SetAndGetLineWidth_620) {
    auto state = createDefaultState();
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_620, SetLineWidthZero_620) {
    auto state = createDefaultState();
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// ==================== Fill/Stroke Opacity ====================

TEST_F(GfxStateTest_620, SetAndGetFillOpacity_620) {
    auto state = createDefaultState();
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_620, SetAndGetStrokeOpacity_620) {
    auto state = createDefaultState();
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_620, FillOpacityBoundaryZero_620) {
    auto state = createDefaultState();
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_620, FillOpacityBoundaryOne_620) {
    auto state = createDefaultState();
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// ==================== Overprint ====================

TEST_F(GfxStateTest_620, SetAndGetFillOverprint_620) {
    auto state = createDefaultState();
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_620, SetAndGetStrokeOverprint_620) {
    auto state = createDefaultState();
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_620, SetAndGetOverprintMode_620) {
    auto state = createDefaultState();
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ==================== Flatness ====================

TEST_F(GfxStateTest_620, SetAndGetFlatness_620) {
    auto state = createDefaultState();
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// ==================== Line Join / Line Cap ====================

TEST_F(GfxStateTest_620, SetAndGetLineJoin_620) {
    auto state = createDefaultState();
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_620, SetAndGetLineCap_620) {
    auto state = createDefaultState();
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// ==================== Miter Limit ====================

TEST_F(GfxStateTest_620, SetAndGetMiterLimit_620) {
    auto state = createDefaultState();
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// ==================== Stroke Adjust ====================

TEST_F(GfxStateTest_620, SetAndGetStrokeAdjust_620) {
    auto state = createDefaultState();
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// ==================== Alpha Is Shape ====================

TEST_F(GfxStateTest_620, SetAndGetAlphaIsShape_620) {
    auto state = createDefaultState();
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// ==================== Text Knockout ====================

TEST_F(GfxStateTest_620, SetAndGetTextKnockout_620) {
    auto state = createDefaultState();
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ==================== Text Properties ====================

TEST_F(GfxStateTest_620, SetAndGetCharSpace_620) {
    auto state = createDefaultState();
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_620, SetAndGetWordSpace_620) {
    auto state = createDefaultState();
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_620, SetAndGetHorizScaling_620) {
    auto state = createDefaultState();
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_620, SetAndGetLeading_620) {
    auto state = createDefaultState();
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_620, SetAndGetRise_620) {
    auto state = createDefaultState();
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_620, SetAndGetRender_620) {
    auto state = createDefaultState();
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// ==================== Rendering Intent ====================

TEST_F(GfxStateTest_620, SetAndGetRenderingIntent_620) {
    auto state = createDefaultState();
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_620, SetRenderingIntentRelativeColorimetric_620) {
    auto state = createDefaultState();
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_620, SetRenderingIntentSaturation_620) {
    auto state = createDefaultState();
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_620, SetRenderingIntentAbsoluteColorimetric_620) {
    auto state = createDefaultState();
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// ==================== Font ====================

TEST_F(GfxStateTest_620, GetFontSizeDefault_620) {
    auto state = createDefaultState();
    // Default font size should be some value (likely 0)
    EXPECT_GE(state->getFontSize(), 0.0);
}

// ==================== Text Matrix ====================

TEST_F(GfxStateTest_620, SetAndGetTextMat_620) {
    auto state = createDefaultState();
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// ==================== CTM ====================

TEST_F(GfxStateTest_620, SetCTM_620) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// ==================== Blend Mode ====================

TEST_F(GfxStateTest_620, SetAndGetBlendMode_620) {
    auto state = createDefaultState();
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_620, BlendModeDefaultNormal_620) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// ==================== Save/Restore ====================

TEST_F(GfxStateTest_620, SaveAndRestore_620) {
    auto state = createDefaultState();
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    saved->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 5.0);

    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
}

TEST_F(GfxStateTest_620, HasSavesInitiallyFalse_620) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_620, HasSavesTrueAfterSave_620) {
    auto state = createDefaultState();
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up by restoring
    saved->restore();
}

// ==================== Path Operations ====================

TEST_F(GfxStateTest_620, InitiallyNoPath_620) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_620, MoveToSetsCurPt_620) {
    auto state = createDefaultState();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_620, LineToCreatesPath_620) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_620, ClearPathResetsState_620) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_620, CurveToCreatesPath_620) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_620, ClosePathDoesNotClearPath_620) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// ==================== Transform ====================

TEST_F(GfxStateTest_620, TransformWithIdentityCTM_620) {
    auto state = createDefaultState();
    // After construction with identity-like CTM (72 DPI, no rotation), 
    // transform should map coordinates
    double x2, y2;
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_620, TransformDeltaWithScaling_620) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double dx2, dy2;
    state->transformDelta(5.0, 10.0, &dx2, &dy2);
    EXPECT_DOUBLE_EQ(dx2, 10.0);
    EXPECT_DOUBLE_EQ(dy2, 30.0);
}

// ==================== TextMoveTo ====================

TEST_F(GfxStateTest_620, TextMoveToUpdatesTextPosition_620) {
    auto state = createDefaultState();
    state->textMoveTo(5.0, 10.0);
    // After textMoveTo, line position should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 10.0);
}

// ==================== Line Dash ====================

TEST_F(GfxStateTest_620, SetAndGetLineDash_620) {
    auto state = createDefaultState();
    std::vector<double> dash = {3.0, 2.0, 1.0};
    state->setLineDash(std::move(dash), 0.5);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.5);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
    EXPECT_DOUBLE_EQ(result[2], 1.0);
}

TEST_F(GfxStateTest_620, SetLineDashEmpty_620) {
    auto state = createDefaultState();
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(result.empty());
}

// ==================== Copy ====================

TEST_F(GfxStateTest_620, CopyPreservesProperties_620) {
    auto state = createDefaultState();
    state->setLineWidth(4.5);
    state->setFillOpacity(0.3);
    state->setCharSpace(2.0);

    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 4.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
    EXPECT_DOUBLE_EQ(copied->getCharSpace(), 2.0);
}

// ==================== Clip to Rect with degenerate bounds ====================

TEST_F(GfxStateTest_620, ClipToRectZeroArea_620) {
    auto state = createDefaultState();
    state->clipToRect(50.0, 50.0, 50.0, 50.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_DOUBLE_EQ(xMin, 50.0);
    EXPECT_DOUBLE_EQ(yMin, 50.0);
    EXPECT_DOUBLE_EQ(xMax, 50.0);
    EXPECT_DOUBLE_EQ(yMax, 50.0);
}

// ==================== Different page rotations ====================

TEST_F(GfxStateTest_620, RotatedPage90_620) {
    PDFRectangle pageBox;
    pageBox.x1 = 0; pageBox.y1 = 0; pageBox.x2 = 612; pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_620, RotatedPage180_620) {
    PDFRectangle pageBox;
    pageBox.x1 = 0; pageBox.y1 = 0; pageBox.x2 = 612; pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state.getRotate(), 180);
}

TEST_F(GfxStateTest_620, RotatedPage270_620) {
    PDFRectangle pageBox;
    pageBox.x1 = 0; pageBox.y1 = 0; pageBox.x2 = 612; pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(state.getRotate(), 270);
}

// ==================== parseBlendMode ====================

TEST_F(GfxStateTest_620, ParseBlendModeNormal_620) {
    // We test with a Name object "Normal"
    Object obj(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Normal);
}

// ==================== getUserClipBBox ====================

TEST_F(GfxStateTest_620, GetUserClipBBox_DefaultState_620) {
    auto state = createDefaultState();
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // User clip bbox should cover the page area
    EXPECT_LE(xMin, 0.0 + 1.0);
    EXPECT_LE(yMin, 0.0 + 1.0);
    EXPECT_GE(xMax, 612.0 - 1.0);
    EXPECT_GE(yMax, 792.0 - 1.0);
}

// ==================== Negative / Edge values ====================

TEST_F(GfxStateTest_620, SetNegativeLineWidth_620) {
    auto state = createDefaultState();
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

TEST_F(GfxStateTest_620, SetLargeCharSpace_620) {
    auto state = createDefaultState();
    state->setCharSpace(1e10);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1e10);
}

TEST_F(GfxStateTest_620, SetNegativeWordSpace_620) {
    auto state = createDefaultState();
    state->setWordSpace(-5.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), -5.0);
}

// ==================== ConcatCTM ====================

TEST_F(GfxStateTest_620, ConcatCTMWithIdentity_620) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 1.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 1.0);
    EXPECT_DOUBLE_EQ(ctm[4], 0.0);
    EXPECT_DOUBLE_EQ(ctm[5], 0.0);
}

TEST_F(GfxStateTest_620, ConcatCTMScaling_620) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 3.0);
}

// ==================== shiftCTMAndClip ====================

TEST_F(GfxStateTest_620, ShiftCTMAndClip_620) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->clipToRect(0.0, 0.0, 100.0, 100.0);
    state->shiftCTMAndClip(10.0, 20.0);

    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);

    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_DOUBLE_EQ(xMin, -10.0);
    EXPECT_DOUBLE_EQ(yMin, -20.0);
    EXPECT_DOUBLE_EQ(xMax, 90.0);
    EXPECT_DOUBLE_EQ(yMax, 80.0);
}

// ==================== Page coordinates ====================

TEST_F(GfxStateTest_620, GetPageCoordinates_620) {
    auto state = createDefaultState(72.0, 72.0, 10.0, 20.0, 500.0, 700.0);
    EXPECT_DOUBLE_EQ(state->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 500.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 700.0);
}

// ==================== isParentState ====================

TEST_F(GfxStateTest_620, IsParentState_620) {
    auto state = createDefaultState();
    GfxState *saved = state->save();
    EXPECT_TRUE(state->isParentState(saved));
}

// ==================== transformWidth ====================

TEST_F(GfxStateTest_620, TransformWidth_620) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 2.0);
}

TEST_F(GfxStateTest_620, TransformWidthZero_620) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(w, 0.0);
}
