#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState for testing
class GfxStateTest_635 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test setFillOverprint and getFillOverprint - set to true
TEST_F(GfxStateTest_635, SetFillOverprintTrue_635) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test setFillOverprint and getFillOverprint - set to false
TEST_F(GfxStateTest_635, SetFillOverprintFalse_635) {
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test toggling fillOverprint from false to true
TEST_F(GfxStateTest_635, ToggleFillOverprintFalseToTrue_635) {
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test toggling fillOverprint from true to false
TEST_F(GfxStateTest_635, ToggleFillOverprintTrueToFalse_635) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test multiple sets to same value
TEST_F(GfxStateTest_635, SetFillOverprintMultipleTimes_635) {
    state->setFillOverprint(true);
    state->setFillOverprint(true);
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test initial DPI values
TEST_F(GfxStateTest_635, InitialHDPI_635) {
    EXPECT_DOUBLE_EQ(72.0, state->getHDPI());
}

TEST_F(GfxStateTest_635, InitialVDPI_635) {
    EXPECT_DOUBLE_EQ(72.0, state->getVDPI());
}

// Test page dimensions
TEST_F(GfxStateTest_635, PageWidth_635) {
    EXPECT_DOUBLE_EQ(612.0, state->getPageWidth());
}

TEST_F(GfxStateTest_635, PageHeight_635) {
    EXPECT_DOUBLE_EQ(792.0, state->getPageHeight());
}

// Test initial rotate
TEST_F(GfxStateTest_635, InitialRotate_635) {
    EXPECT_EQ(0, state->getRotate());
}

// Test page coordinates
TEST_F(GfxStateTest_635, PageCoordinates_635) {
    EXPECT_DOUBLE_EQ(0.0, state->getX1());
    EXPECT_DOUBLE_EQ(0.0, state->getY1());
    EXPECT_DOUBLE_EQ(612.0, state->getX2());
    EXPECT_DOUBLE_EQ(792.0, state->getY2());
}

// Test setStrokeOverprint
TEST_F(GfxStateTest_635, SetStrokeOverprintTrue_635) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_635, SetStrokeOverprintFalse_635) {
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode
TEST_F(GfxStateTest_635, SetOverprintMode_635) {
    state->setOverprintMode(1);
    EXPECT_EQ(1, state->getOverprintMode());
}

TEST_F(GfxStateTest_635, SetOverprintModeZero_635) {
    state->setOverprintMode(0);
    EXPECT_EQ(0, state->getOverprintMode());
}

// Test setFillOpacity
TEST_F(GfxStateTest_635, SetFillOpacity_635) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
}

TEST_F(GfxStateTest_635, SetFillOpacityZero_635) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getFillOpacity());
}

TEST_F(GfxStateTest_635, SetFillOpacityOne_635) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(1.0, state->getFillOpacity());
}

// Test setStrokeOpacity
TEST_F(GfxStateTest_635, SetStrokeOpacity_635) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(0.75, state->getStrokeOpacity());
}

// Test setLineWidth
TEST_F(GfxStateTest_635, SetLineWidth_635) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getLineWidth());
}

TEST_F(GfxStateTest_635, SetLineWidthZero_635) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getLineWidth());
}

// Test setFlatness
TEST_F(GfxStateTest_635, SetFlatness_635) {
    state->setFlatness(50);
    EXPECT_EQ(50, state->getFlatness());
}

// Test setLineJoin
TEST_F(GfxStateTest_635, SetLineJoin_635) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(LineJoinStyle::Round, state->getLineJoin());
}

// Test setLineCap
TEST_F(GfxStateTest_635, SetLineCap_635) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(LineCapStyle::Round, state->getLineCap());
}

// Test setMiterLimit
TEST_F(GfxStateTest_635, SetMiterLimit_635) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(5.0, state->getMiterLimit());
}

// Test setStrokeAdjust
TEST_F(GfxStateTest_635, SetStrokeAdjust_635) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape
TEST_F(GfxStateTest_635, SetAlphaIsShape_635) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout
TEST_F(GfxStateTest_635, SetTextKnockout_635) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setCharSpace
TEST_F(GfxStateTest_635, SetCharSpace_635) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getCharSpace());
}

// Test setWordSpace
TEST_F(GfxStateTest_635, SetWordSpace_635) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(2.0, state->getWordSpace());
}

// Test setHorizScaling
TEST_F(GfxStateTest_635, SetHorizScaling_635) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getHorizScaling());
}

// Test setLeading
TEST_F(GfxStateTest_635, SetLeading_635) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(14.0, state->getLeading());
}

// Test setRise
TEST_F(GfxStateTest_635, SetRise_635) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getRise());
}

// Test setRender
TEST_F(GfxStateTest_635, SetRender_635) {
    state->setRender(2);
    EXPECT_EQ(2, state->getRender());
}

// Test setRenderingIntent
TEST_F(GfxStateTest_635, SetRenderingIntent_635) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", state->getRenderingIntent());
}

TEST_F(GfxStateTest_635, SetRenderingIntentRelativeColorimetric_635) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ("RelativeColorimetric", state->getRenderingIntent());
}

// Test setTextMat
TEST_F(GfxStateTest_635, SetTextMat_635) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(1.0, tm[0]);
    EXPECT_DOUBLE_EQ(0.0, tm[1]);
    EXPECT_DOUBLE_EQ(0.0, tm[2]);
    EXPECT_DOUBLE_EQ(1.0, tm[3]);
    EXPECT_DOUBLE_EQ(10.0, tm[4]);
    EXPECT_DOUBLE_EQ(20.0, tm[5]);
}

// Test save and restore
TEST_F(GfxStateTest_635, SaveAndRestore_635) {
    state->setFillOverprint(true);
    state->setLineWidth(3.0);

    GfxState *savedState = state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setFillOverprint(false);
    state->setLineWidth(5.0);
    EXPECT_FALSE(state->getFillOverprint());
    EXPECT_DOUBLE_EQ(5.0, state->getLineWidth());

    GfxState *restoredState = state->restore();
    // After restore, we should get back previous state
    EXPECT_TRUE(restoredState->getFillOverprint());
    EXPECT_DOUBLE_EQ(3.0, restoredState->getLineWidth());
}

// Test hasSaves initially
TEST_F(GfxStateTest_635, InitialHasSaves_635) {
    EXPECT_FALSE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_635, InitialIsPath_635) {
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_635, InitialIsCurPt_635) {
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_635, MoveToCreatesPath_635) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_635, LineToAfterMoveTo_635) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_635, ClearPath_635) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test setCTM
TEST_F(GfxStateTest_635, SetCTM_635) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(100.0, ctm[4]);
    EXPECT_DOUBLE_EQ(200.0, ctm[5]);
}

// Test transform
TEST_F(GfxStateTest_635, TransformIdentity_635) {
    // Default CTM should be identity-like for the page setup
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Just verify transform produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transform with explicit CTM
TEST_F(GfxStateTest_635, TransformWithCTM_635) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 3.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(20.0, x2);  // 2*5 + 0*3 + 10 = 20
    EXPECT_DOUBLE_EQ(26.0, y2);  // 0*5 + 2*3 + 20 = 26
}

// Test transformDelta
TEST_F(GfxStateTest_635, TransformDeltaWithCTM_635) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    double x2, y2;
    state->transformDelta(5.0, 3.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(10.0, x2);  // 2*5 + 0*3 = 10
    EXPECT_DOUBLE_EQ(6.0, y2);   // 0*5 + 2*3 = 6
}

// Test concatCTM
TEST_F(GfxStateTest_635, ConcatCTM_635) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(10.0, ctm[4]);
    EXPECT_DOUBLE_EQ(20.0, ctm[5]);
}

// Test setLineDash
TEST_F(GfxStateTest_635, SetLineDash_635) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(1.0, start);
    ASSERT_EQ(2u, d.size());
    EXPECT_DOUBLE_EQ(3.0, d[0]);
    EXPECT_DOUBLE_EQ(5.0, d[1]);
}

// Test setLineDash with empty dash
TEST_F(GfxStateTest_635, SetLineDashEmpty_635) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(0.0, start);
    EXPECT_EQ(0u, d.size());
}

// Test textMoveTo and text coordinates
TEST_F(GfxStateTest_635, TextMoveTo_635) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(100.0, state->getLineX());
    EXPECT_DOUBLE_EQ(200.0, state->getLineY());
}

// Test clipToRect and getClipBBox
TEST_F(GfxStateTest_635, ClipToRect_635) {
    state->clipToRect(50.0, 100.0, 200.0, 300.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 200.0);
    EXPECT_LE(yMin, 300.0);
    EXPECT_GE(xMax, 50.0);
    EXPECT_GE(yMax, 100.0);
}

// Test copy
TEST_F(GfxStateTest_635, CopyState_635) {
    state->setFillOverprint(true);
    state->setLineWidth(7.5);
    state->setCharSpace(2.0);

    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_TRUE(copied->getFillOverprint());
    EXPECT_DOUBLE_EQ(7.5, copied->getLineWidth());
    EXPECT_DOUBLE_EQ(2.0, copied->getCharSpace());
}

// Test copy independence
TEST_F(GfxStateTest_635, CopyIsIndependent_635) {
    state->setFillOverprint(true);
    std::unique_ptr<GfxState> copied(state->copy());
    
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
    EXPECT_TRUE(copied->getFillOverprint());
}

// Test with different rotation
TEST(GfxStateRotateTest_635, RotatedState_635) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(90, rotatedState.getRotate());
}

// Test with different DPI
TEST(GfxStateDPITest_635, DifferentDPI_635) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(300.0, highDpiState.getHDPI());
    EXPECT_DOUBLE_EQ(150.0, highDpiState.getVDPI());
}

// Test setBlendMode
TEST_F(GfxStateTest_635, SetBlendMode_635) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(GfxBlendMode::Multiply, state->getBlendMode());
}

// Test closePath
TEST_F(GfxStateTest_635, ClosePath_635) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->lineTo(50.0, 60.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_635, CurveTo_635) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test getCTM with Matrix overload
TEST_F(GfxStateTest_635, GetCTMMatrix_635) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify matrix was populated (just check it doesn't crash)
    // The exact layout depends on Matrix definition
}

// Test setRenderingIntent with long string (boundary: 31 chars max)
TEST_F(GfxStateTest_635, SetRenderingIntentLong_635) {
    // renderingIntent is char[32], so max 31 chars + null
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ("AbsoluteColorimetric", state->getRenderingIntent());
}

// Test getUserClipBBox
TEST_F(GfxStateTest_635, GetUserClipBBox_635) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test save multiple times
TEST_F(GfxStateTest_635, MultipleSaves_635) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(2.0);
    GfxState *s2 = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getLineWidth());
    
    GfxState *r1 = state->restore();
    EXPECT_DOUBLE_EQ(2.0, r1->getLineWidth());
    
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(1.0, r2->getLineWidth());
    EXPECT_FALSE(r2->hasSaves());
}

// Test font size
TEST_F(GfxStateTest_635, SetFontSize_635) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(12.0, state->getFontSize());
}

// Test transformWidth
TEST_F(GfxStateTest_635, TransformWidth_635) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test transformWidth with zero
TEST_F(GfxStateTest_635, TransformWidthZero_635) {
    double tw = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, tw);
}
