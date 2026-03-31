#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with default parameters
class GfxStateTest_647 : public ::testing::Test {
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

// Test setCharSpace and getCharSpace - normal value
TEST_F(GfxStateTest_647, SetCharSpaceNormal_647) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

// Test setCharSpace and getCharSpace - zero value
TEST_F(GfxStateTest_647, SetCharSpaceZero_647) {
    state->setCharSpace(0.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test setCharSpace and getCharSpace - negative value
TEST_F(GfxStateTest_647, SetCharSpaceNegative_647) {
    state->setCharSpace(-1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), -1.5);
}

// Test setCharSpace and getCharSpace - large value
TEST_F(GfxStateTest_647, SetCharSpaceLargeValue_647) {
    state->setCharSpace(999999.99);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 999999.99);
}

// Test setCharSpace overwrite
TEST_F(GfxStateTest_647, SetCharSpaceOverwrite_647) {
    state->setCharSpace(5.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 5.0);
    state->setCharSpace(10.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 10.0);
}

// Test setWordSpace and getWordSpace - normal
TEST_F(GfxStateTest_647, SetWordSpaceNormal_647) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test setWordSpace and getWordSpace - zero
TEST_F(GfxStateTest_647, SetWordSpaceZero_647) {
    state->setWordSpace(0.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test setWordSpace and getWordSpace - negative
TEST_F(GfxStateTest_647, SetWordSpaceNegative_647) {
    state->setWordSpace(-2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), -2.0);
}

// Test setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_647, SetHorizScaling_647) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setLeading and getLeading
TEST_F(GfxStateTest_647, SetLeading_647) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_647, SetRise_647) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_647, SetRender_647) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_647, SetLineWidth_647) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test setLineWidth zero
TEST_F(GfxStateTest_647, SetLineWidthZero_647) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_647, SetFlatness_647) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_647, SetMiterLimit_647) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_647, SetLineJoin_647) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_647, SetLineCap_647) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_647, SetFillOpacity_647) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_647, SetStrokeOpacity_647) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_647, SetFillOverprint_647) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_647, SetStrokeOverprint_647) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_647, SetOverprintMode_647) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_647, SetStrokeAdjust_647) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_647, SetAlphaIsShape_647) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_647, SetTextKnockout_647) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test initial DPI values
TEST_F(GfxStateTest_647, InitialDPI_647) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_647, PageDimensions_647) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test getPageWidth and getPageHeight
TEST_F(GfxStateTest_647, PageWidthHeight_647) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test getRotate
TEST_F(GfxStateTest_647, GetRotate_647) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_647, SetCTM_647) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 1.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 1.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_647, SetTextMat_647) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 5.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_647, SetRenderingIntent_647) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with long string (boundary - truncation)
TEST_F(GfxStateTest_647, SetRenderingIntentLong_647) {
    // The internal buffer is char[32], so strings >= 32 chars should be truncated
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test save and restore
TEST_F(GfxStateTest_647, SaveRestore_647) {
    state->setCharSpace(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setCharSpace(10.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 10.0);

    GfxState *restored = state->restore();
    // After restore, we get back to the previous state
    EXPECT_DOUBLE_EQ(restored->getCharSpace(), 5.0);
}

// Test hasSaves - initially false
TEST_F(GfxStateTest_647, HasSavesInitially_647) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_647, HasSavesAfterSave_647) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test moveTo, lineTo path operations
TEST_F(GfxStateTest_647, PathOperations_647) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo updates current point
TEST_F(GfxStateTest_647, LineToUpdatesCurPt_647) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test curveTo
TEST_F(GfxStateTest_647, CurveTo_647) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test closePath
TEST_F(GfxStateTest_647, ClosePath_647) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_647, ClearPath_647) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_647, Transform_647) {
    // With identity-like CTM (default for 72 DPI, no rotation scenario)
    double x2, y2;
    state->transform(100.0, 200.0, &x2, &y2);
    // We don't know exact values without knowing CTM, but we can verify it runs
    // With upsideDown=true and 72 DPI, the CTM should map coordinates
    // Just verify it doesn't crash and produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transformDelta
TEST_F(GfxStateTest_647, TransformDelta_647) {
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test textMoveTo
TEST_F(GfxStateTest_647, TextMoveTo_647) {
    state->textMoveTo(50.0, 100.0);
    // Verify text position was updated
    // The actual values depend on text matrix
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// Test getClipBBox
TEST_F(GfxStateTest_647, GetClipBBox_647) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_647, GetUserClipBBox_647) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_647, ClipToRect_647) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip bbox should be within or equal to the rect
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_647, SetLineDash_647) {
    std::vector<double> dash = {5.0, 3.0, 1.0};
    state->setLineDash(std::move(dash), 2.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 2.0);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_DOUBLE_EQ(result[0], 5.0);
    EXPECT_DOUBLE_EQ(result[1], 3.0);
    EXPECT_DOUBLE_EQ(result[2], 1.0);
}

// Test setLineDash empty
TEST_F(GfxStateTest_647, SetLineDashEmpty_647) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(result.empty());
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_647, SetBlendMode_647) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test copy
TEST_F(GfxStateTest_647, CopyState_647) {
    state->setCharSpace(7.5);
    state->setWordSpace(3.0);
    state->setLineWidth(2.0);
    
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getCharSpace(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getWordSpace(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 2.0);
}

// Test concatCTM
TEST_F(GfxStateTest_647, ConcatCTM_647) {
    // Get initial CTM
    const auto &ctmBefore = state->getCTM();
    
    // Concatenate identity matrix - should not change CTM
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &ctmAfter = state->getCTM();
    
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(ctmBefore[i], ctmAfter[i]);
    }
}

// Test with rotated page
TEST(GfxStateRotatedTest_647, RotatedPage_647) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
    EXPECT_DOUBLE_EQ(rotatedState.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(rotatedState.getPageHeight(), 792.0);
}

// Test with different DPI
TEST(GfxStateDPITest_647, DifferentDPI_647) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState highDPI(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDPI.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDPI.getVDPI(), 300.0);
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_647, SetFillColor_647) {
    GfxColor color;
    color.c[0] = 32768; // 0.5 in GfxColorComp
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_647, SetStrokeColor_647) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], 65535);
}

// Test getFontSize default
TEST_F(GfxStateTest_647, GetFontSizeDefault_647) {
    // Font size should be some value (likely 0 or default)
    double fs = state->getFontSize();
    EXPECT_TRUE(std::isfinite(fs));
}

// Test textShift
TEST_F(GfxStateTest_647, TextShift_647) {
    double initialX = state->getCurX();
    double initialY = state->getCurY();
    state->textShift(10.0, 0.0);
    // After shift, position should have changed
    // We can't predict exact values without knowing internal state,
    // but at minimum it should be finite
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// Test getPath after clearing
TEST_F(GfxStateTest_647, GetPathAfterClear_647) {
    state->clearPath();
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_647, ShiftCTMAndClip_647) {
    state->shiftCTMAndClip(10.0, 20.0);
    // Verify CTM was modified
    const auto &ctm = state->getCTM();
    EXPECT_TRUE(std::isfinite(ctm[4]));
    EXPECT_TRUE(std::isfinite(ctm[5]));
}

// Test getLineX and getLineY
TEST_F(GfxStateTest_647, GetLineXY_647) {
    EXPECT_TRUE(std::isfinite(state->getLineX()));
    EXPECT_TRUE(std::isfinite(state->getLineY()));
}

// Test multiple saves and restores
TEST_F(GfxStateTest_647, MultipleSavesRestores_647) {
    state->setCharSpace(1.0);
    state->save();
    state->setCharSpace(2.0);
    state->save();
    state->setCharSpace(3.0);
    
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 3.0);
    
    GfxState *s1 = state->restore();
    EXPECT_DOUBLE_EQ(s1->getCharSpace(), 2.0);
    
    GfxState *s2 = s1->restore();
    EXPECT_DOUBLE_EQ(s2->getCharSpace(), 1.0);
    EXPECT_FALSE(s2->hasSaves());
}

// Test transformWidth
TEST_F(GfxStateTest_647, TransformWidth_647) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_647, GetTransformedLineWidth_647) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test setCharSpace with very small value
TEST_F(GfxStateTest_647, SetCharSpaceVerySmall_647) {
    state->setCharSpace(0.0001);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0001);
}

// Test setFillOpacity boundary values
TEST_F(GfxStateTest_647, SetFillOpacityBoundary_647) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setStrokeOpacity boundary values
TEST_F(GfxStateTest_647, SetStrokeOpacityBoundary_647) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
    
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_647, GetCTMMatrix_647) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    Matrix m;
    state->getCTM(&m);
    EXPECT_DOUBLE_EQ(m.m[0], 2.0);
    EXPECT_DOUBLE_EQ(m.m[3], 3.0);
}

// Test getReusablePath
TEST_F(GfxStateTest_647, GetReusablePath_647) {
    state->moveTo(0, 0);
    state->lineTo(100, 100);
    auto pathIter = state->getReusablePath();
    ASSERT_NE(pathIter, nullptr);
}

// Test clip operation
TEST_F(GfxStateTest_647, ClipOperation_647) {
    state->moveTo(50.0, 50.0);
    state->lineTo(200.0, 50.0);
    state->lineTo(200.0, 200.0);
    state->lineTo(50.0, 200.0);
    state->closePath();
    state->clip();
    
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}
