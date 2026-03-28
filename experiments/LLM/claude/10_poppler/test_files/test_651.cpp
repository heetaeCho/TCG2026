#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_651 : public ::testing::Test {
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

// Test setRise and getRise - normal value
TEST_F(GfxStateTest_651, SetRiseNormalValue_651) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test setRise and getRise - zero value
TEST_F(GfxStateTest_651, SetRiseZero_651) {
    state->setRise(0.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test setRise and getRise - negative value
TEST_F(GfxStateTest_651, SetRiseNegative_651) {
    state->setRise(-3.5);
    EXPECT_DOUBLE_EQ(state->getRise(), -3.5);
}

// Test setRise and getRise - large positive value
TEST_F(GfxStateTest_651, SetRiseLargePositive_651) {
    state->setRise(1e10);
    EXPECT_DOUBLE_EQ(state->getRise(), 1e10);
}

// Test setRise and getRise - large negative value
TEST_F(GfxStateTest_651, SetRiseLargeNegative_651) {
    state->setRise(-1e10);
    EXPECT_DOUBLE_EQ(state->getRise(), -1e10);
}

// Test setRise - overwrite previous value
TEST_F(GfxStateTest_651, SetRiseOverwrite_651) {
    state->setRise(10.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 10.0);
    state->setRise(20.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 20.0);
}

// Test setRise - very small value
TEST_F(GfxStateTest_651, SetRiseVerySmall_651) {
    state->setRise(1e-15);
    EXPECT_DOUBLE_EQ(state->getRise(), 1e-15);
}

// Test initial rise value (should be 0 by default)
TEST_F(GfxStateTest_651, InitialRiseValue_651) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test construction parameters - DPI
TEST_F(GfxStateTest_651, ConstructionHDPI_651) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_651, ConstructionVDPI_651) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_651, PageWidth_651) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_651, PageHeight_651) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_651, Rotation_651) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test setCharSpace / getCharSpace
TEST_F(GfxStateTest_651, SetCharSpace_651) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

// Test setWordSpace / getWordSpace
TEST_F(GfxStateTest_651, SetWordSpace_651) {
    state->setWordSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 1.5);
}

// Test setHorizScaling / getHorizScaling
TEST_F(GfxStateTest_651, SetHorizScaling_651) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setLeading / getLeading
TEST_F(GfxStateTest_651, SetLeading_651) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setRender / getRender
TEST_F(GfxStateTest_651, SetRender_651) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setLineWidth / getLineWidth
TEST_F(GfxStateTest_651, SetLineWidth_651) {
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
}

// Test setMiterLimit / getMiterLimit
TEST_F(GfxStateTest_651, SetMiterLimit_651) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test setFlatness / getFlatness
TEST_F(GfxStateTest_651, SetFlatness_651) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test setFillOpacity / getFillOpacity
TEST_F(GfxStateTest_651, SetFillOpacity_651) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setStrokeOpacity / getStrokeOpacity
TEST_F(GfxStateTest_651, SetStrokeOpacity_651) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint / getFillOverprint
TEST_F(GfxStateTest_651, SetFillOverprint_651) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint / getStrokeOverprint
TEST_F(GfxStateTest_651, SetStrokeOverprint_651) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode / getOverprintMode
TEST_F(GfxStateTest_651, SetOverprintMode_651) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setStrokeAdjust / getStrokeAdjust
TEST_F(GfxStateTest_651, SetStrokeAdjust_651) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape / getAlphaIsShape
TEST_F(GfxStateTest_651, SetAlphaIsShape_651) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test setTextKnockout / getTextKnockout
TEST_F(GfxStateTest_651, SetTextKnockout_651) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test setLineJoin / getLineJoin
TEST_F(GfxStateTest_651, SetLineJoin_651) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test setLineCap / getLineCap
TEST_F(GfxStateTest_651, SetLineCap_651) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test setBlendMode / getBlendMode
TEST_F(GfxStateTest_651, SetBlendMode_651) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test save / restore
TEST_F(GfxStateTest_651, SaveAndRestore_651) {
    state->setRise(7.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setRise(14.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 14.0);

    GfxState *restored = state->restore();
    EXPECT_DOUBLE_EQ(restored->getRise(), 7.0);
}

// Test hasSaves before and after save
TEST_F(GfxStateTest_651, HasSaves_651) {
    EXPECT_FALSE(state->hasSaves());
    state->save();
    EXPECT_TRUE(state->hasSaves());
    state->restore();
    EXPECT_FALSE(state->hasSaves());
}

// Test moveTo / lineTo path operations
TEST_F(GfxStateTest_651, MoveToSetsCurrentPoint_651) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

TEST_F(GfxStateTest_651, LineToPath_651) {
    state->moveTo(0.0, 0.0);
    state->lineTo(50.0, 50.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 50.0);
}

// Test clearPath
TEST_F(GfxStateTest_651, ClearPath_651) {
    state->moveTo(10.0, 10.0);
    state->lineTo(20.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test textMoveTo
TEST_F(GfxStateTest_651, TextMoveTo_651) {
    state->textMoveTo(5.0, 10.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 10.0);
}

// Test setCTM
TEST_F(GfxStateTest_651, SetCTM_651) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test transform
TEST_F(GfxStateTest_651, TransformIdentity_651) {
    // Default CTM after construction with 72 DPI, 0 rotation, upsideDown=true
    // should transform coordinates appropriately
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Just verify it doesn't crash and produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test setTextMat / getTextMat
TEST_F(GfxStateTest_651, SetTextMat_651) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// Test setRenderingIntent / getRenderingIntent
TEST_F(GfxStateTest_651, SetRenderingIntent_651) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with long string (boundary - renderingIntent is char[32])
TEST_F(GfxStateTest_651, SetRenderingIntentLongString_651) {
    // The buffer is 32 chars, so a string of 31 chars + null should fit
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test setLineDash / getLineDash
TEST_F(GfxStateTest_651, SetLineDash_651) {
    std::vector<double> dash = {3.0, 5.0, 7.0};
    state->setLineDash(std::move(dash), 1.5);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.5);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
    EXPECT_DOUBLE_EQ(result[2], 7.0);
}

// Test setLineDash with empty dash
TEST_F(GfxStateTest_651, SetLineDashEmpty_651) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(result.empty());
}

// Test copy
TEST_F(GfxStateTest_651, CopyState_651) {
    state->setRise(42.0);
    state->setLineWidth(5.0);
    auto copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getRise(), 42.0);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 5.0);
    delete copied;
}

// Test curveTo
TEST_F(GfxStateTest_651, CurveTo_651) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_651, ClosePath_651) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    // After closePath, current point should return to the moveTo point
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test clipToRect
TEST_F(GfxStateTest_651, ClipToRect_651) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test getFontSize with no font set
TEST_F(GfxStateTest_651, GetFontSizeDefault_651) {
    // After construction, fontSize should be some default (likely 0)
    double fontSize = state->getFontSize();
    EXPECT_TRUE(std::isfinite(fontSize));
}

// Test construction with different rotations
TEST_F(GfxStateTest_651, ConstructWithRotation90_651) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_651, ConstructWithRotation180_651) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_651, ConstructWithRotation270_651) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_651, GetPageBounds_651) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_TRUE(std::isfinite(x1));
    EXPECT_TRUE(std::isfinite(y1));
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test multiple setRise calls
TEST_F(GfxStateTest_651, SetRiseMultipleTimes_651) {
    for (int i = 0; i < 100; ++i) {
        state->setRise(static_cast<double>(i));
        EXPECT_DOUBLE_EQ(state->getRise(), static_cast<double>(i));
    }
}

// Test setRise with infinity (boundary)
TEST_F(GfxStateTest_651, SetRiseInfinity_651) {
    state->setRise(std::numeric_limits<double>::infinity());
    EXPECT_EQ(state->getRise(), std::numeric_limits<double>::infinity());
}

// Test setRise with negative infinity (boundary)
TEST_F(GfxStateTest_651, SetRiseNegInfinity_651) {
    state->setRise(-std::numeric_limits<double>::infinity());
    EXPECT_EQ(state->getRise(), -std::numeric_limits<double>::infinity());
}

// Test getUserClipBBox
TEST_F(GfxStateTest_651, GetUserClipBBox_651) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test transformDelta
TEST_F(GfxStateTest_651, TransformDelta_651) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_651, ShiftCTMAndClip_651) {
    auto ctmBefore = state->getCTM();
    state->shiftCTMAndClip(10.0, 20.0);
    auto ctmAfter = state->getCTM();
    // The translation components should have changed
    // ctm[4] and ctm[5] should be shifted
    EXPECT_NE(ctmBefore[4], ctmAfter[4]);
}

// Test concatCTM
TEST_F(GfxStateTest_651, ConcatCTM_651) {
    auto ctmBefore = state->getCTM();
    // Concatenate a scaling matrix
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    auto ctmAfter = state->getCTM();
    // The CTM should have changed
    EXPECT_DOUBLE_EQ(ctmAfter[0], ctmBefore[0] * 2.0);
}

// Test transformWidth
TEST_F(GfxStateTest_651, TransformWidth_651) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_651, GetTransformedLineWidth_651) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}
