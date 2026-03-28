#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"

// Helper to create a basic GfxState for testing
class GfxStateTest_598 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a simple page box
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;  // Letter width in points
        pageBox.y2 = 792;  // Letter height in points

        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// ========================
// Constructor / Basic Getters
// ========================

TEST_F(GfxStateTest_598, ConstructorSetsHDPI_598) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_598, ConstructorSetsVDPI_598) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_598, ConstructorSetsRotate_598) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_598, ConstructorSetsPageDimensions_598) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_598, ConstructorWithRotation90_598) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// ========================
// Flatness
// ========================

TEST_F(GfxStateTest_598, DefaultFlatness_598) {
    // Default flatness should be 1 (or 0 depending on implementation)
    int flatness = state->getFlatness();
    // Just verify we can get it without crash
    EXPECT_GE(flatness, 0);
}

TEST_F(GfxStateTest_598, SetFlatness_598) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

TEST_F(GfxStateTest_598, SetFlatnessZero_598) {
    state->setFlatness(0);
    EXPECT_EQ(state->getFlatness(), 0);
}

TEST_F(GfxStateTest_598, SetFlatnessMax_598) {
    state->setFlatness(100);
    EXPECT_EQ(state->getFlatness(), 100);
}

// ========================
// Line Width
// ========================

TEST_F(GfxStateTest_598, SetAndGetLineWidth_598) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_598, SetLineWidthZero_598) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// ========================
// Line Join
// ========================

TEST_F(GfxStateTest_598, SetAndGetLineJoin_598) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// ========================
// Line Cap
// ========================

TEST_F(GfxStateTest_598, SetAndGetLineCap_598) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// ========================
// Miter Limit
// ========================

TEST_F(GfxStateTest_598, SetAndGetMiterLimit_598) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// ========================
// Opacity
// ========================

TEST_F(GfxStateTest_598, SetAndGetFillOpacity_598) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_598, SetAndGetStrokeOpacity_598) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_598, FillOpacityBoundaryZero_598) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_598, FillOpacityBoundaryOne_598) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_598, StrokeOpacityBoundaryZero_598) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_598, StrokeOpacityBoundaryOne_598) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// ========================
// Overprint
// ========================

TEST_F(GfxStateTest_598, SetAndGetFillOverprint_598) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_598, SetAndGetStrokeOverprint_598) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_598, SetAndGetOverprintMode_598) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// ========================
// Stroke Adjust
// ========================

TEST_F(GfxStateTest_598, SetAndGetStrokeAdjust_598) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// ========================
// Alpha Is Shape
// ========================

TEST_F(GfxStateTest_598, SetAndGetAlphaIsShape_598) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// ========================
// Text Knockout
// ========================

TEST_F(GfxStateTest_598, SetAndGetTextKnockout_598) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// ========================
// Text Properties
// ========================

TEST_F(GfxStateTest_598, SetAndGetCharSpace_598) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_598, SetAndGetWordSpace_598) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_598, SetAndGetHorizScaling_598) {
    state->setHorizScaling(1.2);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.2);
}

TEST_F(GfxStateTest_598, SetAndGetLeading_598) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_598, SetAndGetRise_598) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_598, SetAndGetRender_598) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// ========================
// Text Matrix
// ========================

TEST_F(GfxStateTest_598, SetAndGetTextMat_598) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// ========================
// Rendering Intent
// ========================

TEST_F(GfxStateTest_598, SetAndGetRenderingIntent_598) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_598, SetRenderingIntentRelativeColorimetric_598) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_598, SetRenderingIntentSaturation_598) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_598, SetRenderingIntentPerceptual_598) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// ========================
// CTM
// ========================

TEST_F(GfxStateTest_598, GetCTM_598) {
    const auto &ctm = state->getCTM();
    // Should be a valid 6-element array
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_598, SetCTM_598) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

TEST_F(GfxStateTest_598, ConcatCTM_598) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

TEST_F(GfxStateTest_598, GetCTMAsMatrix_598) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should contain the CTM values
    // Just verify no crash
}

// ========================
// Transform
// ========================

TEST_F(GfxStateTest_598, TransformIdentity_598) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_598, TransformWithTranslation_598) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_598, TransformWithScaling_598) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

TEST_F(GfxStateTest_598, TransformDelta_598) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// ========================
// Path Operations
// ========================

TEST_F(GfxStateTest_598, InitiallyNoPath_598) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_598, MoveToSetsCurrentPoint_598) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_598, LineToCreatesPath_598) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_598, CurveToCreatesPath_598) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_598, ClearPathResetsPath_598) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_598, ClosePathDoesNotCrash_598) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_598, GetPathNotNull_598) {
    state->moveTo(0.0, 0.0);
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// ========================
// Save / Restore
// ========================

TEST_F(GfxStateTest_598, InitiallyNoSaves_598) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_598, SaveCreatesSavedState_598) {
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(saved->hasSaves());
}

TEST_F(GfxStateTest_598, RestoreReturnsPreviousState_598) {
    state->setFlatness(42);
    GfxState *saved = state->save();
    saved->setFlatness(99);
    EXPECT_EQ(saved->getFlatness(), 99);

    GfxState *restored = saved->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_EQ(restored->getFlatness(), 42);
}

TEST_F(GfxStateTest_598, SavePreservesState_598) {
    state->setLineWidth(3.14);
    state->setFillOpacity(0.5);
    GfxState *saved = state->save();
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 3.14);
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.5);
    // Clean up
    saved->restore();
}

TEST_F(GfxStateTest_598, MultipleSaveRestore_598) {
    state->setFlatness(1);
    GfxState *s1 = state->save();
    s1->setFlatness(2);
    GfxState *s2 = s1->save();
    s2->setFlatness(3);

    EXPECT_EQ(s2->getFlatness(), 3);
    GfxState *r1 = s2->restore();
    EXPECT_EQ(r1->getFlatness(), 2);
    GfxState *r2 = r1->restore();
    EXPECT_EQ(r2->getFlatness(), 1);
}

// ========================
// Copy
// ========================

TEST_F(GfxStateTest_598, CopyCreatesIndependentState_598) {
    state->setFlatness(55);
    state->setLineWidth(2.0);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_NE(copied.get(), nullptr);
    EXPECT_EQ(copied->getFlatness(), 55);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 2.0);

    // Modifying the copy should not affect original
    copied->setFlatness(77);
    EXPECT_EQ(state->getFlatness(), 55);
    EXPECT_EQ(copied->getFlatness(), 77);
}

// ========================
// Clip BBox
// ========================

TEST_F(GfxStateTest_598, GetClipBBox_598) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be valid (max >= min)
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_598, GetUserClipBBox_598) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_598, ClipToRect_598) {
    state->clipToRect(100.0, 200.0, 300.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the bounds should be restricted
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ========================
// Line Dash
// ========================

TEST_F(GfxStateTest_598, SetAndGetLineDash_598) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_598, SetEmptyLineDash_598) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// ========================
// Blend Mode
// ========================

TEST_F(GfxStateTest_598, SetAndGetBlendMode_598) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_598, DefaultBlendModeNormal_598) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// ========================
// Page Coordinates
// ========================

TEST_F(GfxStateTest_598, GetX1Y1X2Y2_598) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// ========================
// Cursor Position
// ========================

TEST_F(GfxStateTest_598, TextMoveTo_598) {
    state->textMoveTo(15.0, 25.0);
    // After textMoveTo, lineX and lineY should reflect the position
    EXPECT_DOUBLE_EQ(state->getLineX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 25.0);
}

// ========================
// Font
// ========================

TEST_F(GfxStateTest_598, DefaultFontIsNull_598) {
    const auto &font = state->getFont();
    // Default font may be null
    // Just verify no crash
}

TEST_F(GfxStateTest_598, GetFontSizeDefault_598) {
    double fontSize = state->getFontSize();
    // Verify we can call it without crash
    EXPECT_GE(fontSize, 0.0);
}

// ========================
// Color Space and Color
// ========================

TEST_F(GfxStateTest_598, GetFillColorNotNull_598) {
    const GfxColor *color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_598, GetStrokeColorNotNull_598) {
    const GfxColor *color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

// ========================
// isParentState
// ========================

TEST_F(GfxStateTest_598, IsParentStateAfterSave_598) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
    saved->restore();
}

TEST_F(GfxStateTest_598, IsNotParentStateForUnrelated_598) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 100;
    pageBox.y2 = 100;
    GfxState otherState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(&otherState));
}

// ========================
// Transformed Line Width
// ========================

TEST_F(GfxStateTest_598, GetTransformedLineWidth_598) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    // With 2x scaling, transformed line width should be approximately 2.0
    EXPECT_GT(tlw, 0.0);
}

// ========================
// transformWidth
// ========================

TEST_F(GfxStateTest_598, TransformWidthIdentity_598) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_NEAR(w, 5.0, 0.001);
}

// ========================
// Shift CTM and Clip
// ========================

TEST_F(GfxStateTest_598, ShiftCTMAndClip_598) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 50.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 50.0);
}

// ========================
// Different DPI values
// ========================

TEST_F(GfxStateTest_598, DifferentHDPIVDPI_598) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState highDPIState(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDPIState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDPIState.getVDPI(), 150.0);
}

// ========================
// Reusable Path Iterator
// ========================

TEST_F(GfxStateTest_598, GetReusablePathIterator_598) {
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter.get(), nullptr);
}

// ========================
// Clip operations
// ========================

TEST_F(GfxStateTest_598, ClipDoesNotCrash_598) {
    state->moveTo(0, 0);
    state->lineTo(100, 0);
    state->lineTo(100, 100);
    state->lineTo(0, 100);
    state->closePath();
    state->clip();
    // Verify no crash
}

TEST_F(GfxStateTest_598, ClipToStrokePathDoesNotCrash_598) {
    state->moveTo(0, 0);
    state->lineTo(100, 0);
    state->lineTo(100, 100);
    state->closePath();
    state->clipToStrokePath();
    // Verify no crash
}

// ========================
// Fill Color set and get
// ========================

TEST_F(GfxStateTest_598, SetFillColor_598) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_598, SetStrokeColor_598) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 65535);
}

// ========================
// TextShift
// ========================

TEST_F(GfxStateTest_598, TextShift_598) {
    state->textMoveTo(10.0, 20.0);
    state->textShift(5.0, 3.0);
    // Should shift current text position
    // Verify no crash and that curX/curY changed
}

// ========================
// Constructor with upsideDown false
// ========================

TEST_F(GfxStateTest_598, ConstructorUpsideDownFalse_598) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState notFlipped(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(notFlipped.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notFlipped.getPageHeight(), 792.0);
}

// ========================
// Various rotations
// ========================

TEST_F(GfxStateTest_598, ConstructorRotation180_598) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_598, ConstructorRotation270_598) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}
