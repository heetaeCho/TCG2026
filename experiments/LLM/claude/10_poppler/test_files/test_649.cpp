#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState for testing
class GfxStateTest_649 : public ::testing::Test {
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

// Test setHorizScaling with normal value
TEST_F(GfxStateTest_649, SetHorizScalingNormalValue_649) {
    state->setHorizScaling(100.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test setHorizScaling with 200% scaling
TEST_F(GfxStateTest_649, SetHorizScaling200Percent_649) {
    state->setHorizScaling(200.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 2.0);
}

// Test setHorizScaling with 50% scaling
TEST_F(GfxStateTest_649, SetHorizScaling50Percent_649) {
    state->setHorizScaling(50.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test setHorizScaling with zero
TEST_F(GfxStateTest_649, SetHorizScalingZero_649) {
    state->setHorizScaling(0.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.0);
}

// Test setHorizScaling with negative value
TEST_F(GfxStateTest_649, SetHorizScalingNegative_649) {
    state->setHorizScaling(-100.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), -1.0);
}

// Test setHorizScaling with very small value
TEST_F(GfxStateTest_649, SetHorizScalingVerySmall_649) {
    state->setHorizScaling(1.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.01);
}

// Test setHorizScaling with very large value
TEST_F(GfxStateTest_649, SetHorizScalingVeryLarge_649) {
    state->setHorizScaling(10000.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 100.0);
}

// Test setHorizScaling overwrites previous value
TEST_F(GfxStateTest_649, SetHorizScalingOverwritesPrevious_649) {
    state->setHorizScaling(100.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
    state->setHorizScaling(50.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test setHorizScaling with fractional percentage
TEST_F(GfxStateTest_649, SetHorizScalingFractional_649) {
    state->setHorizScaling(33.33);
    EXPECT_NEAR(state->getHorizScaling(), 0.3333, 1e-10);
}

// Test initial construction values - DPI
TEST_F(GfxStateTest_649, ConstructorHDPI_649) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_649, ConstructorVDPI_649) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_649, PageWidth_649) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_649, PageHeight_649) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test setCharSpace and getCharSpace
TEST_F(GfxStateTest_649, SetCharSpace_649) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

// Test setWordSpace and getWordSpace
TEST_F(GfxStateTest_649, SetWordSpace_649) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test setLeading and getLeading
TEST_F(GfxStateTest_649, SetLeading_649) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_649, SetRise_649) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_649, SetRender_649) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_649, SetLineWidth_649) {
    state->setLineWidth(2.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.0);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_649, SetFlatness_649) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_649, SetMiterLimit_649) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_649, SetFillOpacity_649) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_649, SetStrokeOpacity_649) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_649, SetFillOverprint_649) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_649, SetStrokeOverprint_649) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_649, SetOverprintMode_649) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_649, SetStrokeAdjust_649) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_649, SetAlphaIsShape_649) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_649, SetTextKnockout_649) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test save and restore
TEST_F(GfxStateTest_649, SaveAndRestore_649) {
    state->setHorizScaling(200.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    EXPECT_DOUBLE_EQ(saved->getHorizScaling(), 2.0);

    GfxState *restored = state->restore();
    EXPECT_DOUBLE_EQ(restored->getHorizScaling(), 2.0);
}

// Test hasSaves returns false when no saves
TEST_F(GfxStateTest_649, HasSavesInitiallyFalse_649) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves returns true after save
TEST_F(GfxStateTest_649, HasSavesAfterSave_649) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test setCTM
TEST_F(GfxStateTest_649, SetCTM_649) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_649, SetTextMat_649) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// Test path operations - moveTo creates a current point
TEST_F(GfxStateTest_649, MoveToSetsCurPt_649) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

// Test path operations - lineTo creates a path
TEST_F(GfxStateTest_649, LineToCreatesPath_649) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_649, ClearPath_649) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_649, SetRenderingIntent_649) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with different values
TEST_F(GfxStateTest_649, SetRenderingIntentAbsoluteColorimetric_649) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test getRotate
TEST_F(GfxStateTest_649, GetRotate_649) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test construction with rotation
TEST_F(GfxStateTest_649, ConstructWithRotation_649) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test setLineDash
TEST_F(GfxStateTest_649, SetLineDash_649) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

// Test setLineDash with empty dash
TEST_F(GfxStateTest_649, SetLineDashEmpty_649) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// Test textMoveTo
TEST_F(GfxStateTest_649, TextMoveTo_649) {
    state->textMoveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 25.0);
}

// Test copy
TEST_F(GfxStateTest_649, Copy_649) {
    state->setHorizScaling(150.0);
    state->setCharSpace(3.0);
    auto copied = state->copy();
    EXPECT_DOUBLE_EQ(copied->getHorizScaling(), 1.5);
    EXPECT_DOUBLE_EQ(copied->getCharSpace(), 3.0);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_649, SetLineJoin_649) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_649, SetLineCap_649) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test transform
TEST_F(GfxStateTest_649, Transform_649) {
    // With identity-like CTM, transform should map coordinates
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    // We can't predict exact values without knowing CTM, but we can verify it doesn't crash
    // and returns finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test clipToRect
TEST_F(GfxStateTest_649, ClipToRect_649) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should be constrained
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_649, GetPageBounds_649) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test setHorizScaling with decimal precision
TEST_F(GfxStateTest_649, SetHorizScalingDecimalPrecision_649) {
    state->setHorizScaling(75.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.755);
}

// Test concatCTM
TEST_F(GfxStateTest_649, ConcatCTM_649) {
    auto ctmBefore = state->getCTM();
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // identity concat
    auto ctmAfter = state->getCTM();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(ctmBefore[i], ctmAfter[i]);
    }
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_649, SetBlendMode_649) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test fontSize
TEST_F(GfxStateTest_649, GetFontSizeDefault_649) {
    // Font size should have some default value
    double fontSize = state->getFontSize();
    EXPECT_TRUE(std::isfinite(fontSize));
}

// Test closePath after building a path
TEST_F(GfxStateTest_649, ClosePath_649) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_649, CurveTo_649) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 6.0);
}
