#include <gtest/gtest.h>
#include <cmath>
#include "GfxState.h"

// Helper to create a GfxState with a simple page box
class GfxStateTest_628 : public ::testing::Test {
protected:
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

    GfxState *state;
};

// Test textTransformDelta with identity text matrix (default)
TEST_F(GfxStateTest_628, TextTransformDeltaIdentity_628) {
    // Default text matrix should be identity-like [1,0,0,1,0,0]
    // So textTransformDelta should pass through values
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(3.0, 4.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 3.0);
    EXPECT_DOUBLE_EQ(y2, 4.0);
}

// Test textTransformDelta with zero input
TEST_F(GfxStateTest_628, TextTransformDeltaZeroInput_628) {
    state->setTextMat(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
    double x2, y2;
    state->textTransformDelta(0.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 0.0);
}

// Test textTransformDelta with scaling matrix
TEST_F(GfxStateTest_628, TextTransformDeltaScaling_628) {
    // textMat = [2, 0, 0, 3, tx, ty]
    // x2 = 2*x1 + 0*y1 = 2*x1
    // y2 = 0*x1 + 3*y1 = 3*y1
    state->setTextMat(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    double x2, y2;
    state->textTransformDelta(5.0, 7.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);  // 2*5 + 0*7
    EXPECT_DOUBLE_EQ(y2, 21.0);  // 0*5 + 3*7
}

// Test textTransformDelta with rotation-like matrix
TEST_F(GfxStateTest_628, TextTransformDeltaRotation_628) {
    // 90 degree rotation: textMat = [0, 1, -1, 0, 0, 0]
    // x2 = 0*x1 + (-1)*y1 = -y1
    // y2 = 1*x1 + 0*y1 = x1
    state->setTextMat(0.0, 1.0, -1.0, 0.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(3.0, 4.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, -4.0);
    EXPECT_DOUBLE_EQ(y2, 3.0);
}

// Test textTransformDelta with general matrix
TEST_F(GfxStateTest_628, TextTransformDeltaGeneralMatrix_628) {
    // textMat = [a, b, c, d, e, f] = [1.5, 2.5, 3.5, 4.5, 100, 200]
    // x2 = 1.5*x1 + 3.5*y1
    // y2 = 2.5*x1 + 4.5*y1
    state->setTextMat(1.5, 2.5, 3.5, 4.5, 100.0, 200.0);
    double x2, y2;
    state->textTransformDelta(2.0, 3.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 1.5 * 2.0 + 3.5 * 3.0);  // 3.0 + 10.5 = 13.5
    EXPECT_DOUBLE_EQ(y2, 2.5 * 2.0 + 4.5 * 3.0);  // 5.0 + 13.5 = 18.5
}

// Test textTransformDelta with negative inputs
TEST_F(GfxStateTest_628, TextTransformDeltaNegativeInputs_628) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(-5.0, -10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, -5.0);
    EXPECT_DOUBLE_EQ(y2, -10.0);
}

// Test textTransformDelta with negative matrix elements
TEST_F(GfxStateTest_628, TextTransformDeltaNegativeMatrix_628) {
    state->setTextMat(-1.0, -2.0, -3.0, -4.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, -1.0 + (-3.0));  // -4.0
    EXPECT_DOUBLE_EQ(y2, -2.0 + (-4.0));  // -6.0
}

// Test textTransformDelta only x component (y1 = 0)
TEST_F(GfxStateTest_628, TextTransformDeltaOnlyX_628) {
    state->setTextMat(2.0, 3.0, 4.0, 5.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 2.0);  // 2*1 + 4*0
    EXPECT_DOUBLE_EQ(y2, 3.0);  // 3*1 + 5*0
}

// Test textTransformDelta only y component (x1 = 0)
TEST_F(GfxStateTest_628, TextTransformDeltaOnlyY_628) {
    state->setTextMat(2.0, 3.0, 4.0, 5.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(0.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 4.0);  // 2*0 + 4*1
    EXPECT_DOUBLE_EQ(y2, 5.0);  // 3*0 + 5*1
}

// Test textTransformDelta with very large values
TEST_F(GfxStateTest_628, TextTransformDeltaLargeValues_628) {
    state->setTextMat(1e10, 0.0, 0.0, 1e10, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(1e10, 1e10, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 1e20);
    EXPECT_DOUBLE_EQ(y2, 1e20);
}

// Test textTransformDelta with very small values
TEST_F(GfxStateTest_628, TextTransformDeltaSmallValues_628) {
    state->setTextMat(1e-10, 0.0, 0.0, 1e-10, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(1e-10, 1e-10, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 1e-20);
    EXPECT_DOUBLE_EQ(y2, 1e-20);
}

// Test that translation components (e, f) of textMat do not affect delta transform
TEST_F(GfxStateTest_628, TextTransformDeltaIgnoresTranslation_628) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 999.0, 888.0);
    double x2, y2;
    state->textTransformDelta(5.0, 7.0, &x2, &y2);
    // Delta should not include translation
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 7.0);
}

// Test basic GfxState construction and getters
TEST_F(GfxStateTest_628, ConstructionBasics_628) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_628, SetAndGetTextMat_628) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_628, SetAndGetLineWidth_628) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_628, SetAndGetFillOpacity_628) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_628, SetAndGetStrokeOpacity_628) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setCharSpace and getCharSpace
TEST_F(GfxStateTest_628, SetAndGetCharSpace_628) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test setWordSpace and getWordSpace
TEST_F(GfxStateTest_628, SetAndGetWordSpace_628) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_628, SetAndGetHorizScaling_628) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setLeading and getLeading
TEST_F(GfxStateTest_628, SetAndGetLeading_628) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_628, SetAndGetRise_628) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_628, SetAndGetRender_628) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_628, SetAndGetFillOverprint_628) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_628, SetAndGetStrokeOverprint_628) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_628, SetAndGetOverprintMode_628) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_628, SetAndGetFlatness_628) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_628, SetAndGetMiterLimit_628) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_628, SetAndGetStrokeAdjust_628) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_628, SetAndGetAlphaIsShape_628) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_628, SetAndGetTextKnockout_628) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test save and restore
TEST_F(GfxStateTest_628, SaveAndRestore_628) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    
    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);
    
    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test hasSaves before any save
TEST_F(GfxStateTest_628, HasSavesInitiallyFalse_628) {
    EXPECT_FALSE(state->hasSaves());
}

// Test path operations - moveTo, lineTo, isPath, isCurPt
TEST_F(GfxStateTest_628, PathOperations_628) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
    
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
    
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_628, ClearPath_628) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
    
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test setFontSize and getFontSize
TEST_F(GfxStateTest_628, SetAndGetFontSize_628) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_628, SetAndGetCTM_628) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_628, SetAndGetRenderingIntent_628) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_628, SetAndGetLineDash_628) {
    std::vector<double> dash = {3.0, 2.0, 1.0};
    state->setLineDash(std::move(dash), 5.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 5.0);
    ASSERT_EQ(retrievedDash.size(), 3u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 2.0);
    EXPECT_DOUBLE_EQ(retrievedDash[2], 1.0);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_628, SetAndGetLineJoin_628) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
    state->setLineJoin(lineJoinBevel);
    EXPECT_EQ(state->getLineJoin(), lineJoinBevel);
    state->setLineJoin(lineJoinMiter);
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_628, SetAndGetLineCap_628) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
    state->setLineCap(lineCapSquare);
    EXPECT_EQ(state->getLineCap(), lineCapSquare);
    state->setLineCap(lineCapButt);
    EXPECT_EQ(state->getLineCap(), lineCapButt);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_628, SetAndGetBlendMode_628) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
    state->setBlendMode(gfxBlendNormal);
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_628, GetPageBounds_628) {
    // The page box was set to (0,0)-(612,792)
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_DOUBLE_EQ(x1, 0.0);
    EXPECT_DOUBLE_EQ(y1, 0.0);
    EXPECT_DOUBLE_EQ(x2, 612.0);
    EXPECT_DOUBLE_EQ(y2, 792.0);
}

// Test copy
TEST_F(GfxStateTest_628, CopyState_628) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    GfxState *copied = state->copy();
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
    delete copied;
}

// Test textTransformDelta with unit vectors after shear matrix
TEST_F(GfxStateTest_628, TextTransformDeltaShearMatrix_628) {
    // Shear: textMat = [1, 0, 0.5, 1, 0, 0]
    // x2 = 1*x1 + 0.5*y1
    // y2 = 0*x1 + 1*y1
    state->setTextMat(1.0, 0.0, 0.5, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 1.5);
    EXPECT_DOUBLE_EQ(y2, 1.0);
}

// Test textTransformDelta multiple calls with same state
TEST_F(GfxStateTest_628, TextTransformDeltaMultipleCalls_628) {
    state->setTextMat(2.0, 1.0, 1.0, 2.0, 0.0, 0.0);
    
    double x2a, y2a, x2b, y2b;
    state->textTransformDelta(1.0, 0.0, &x2a, &y2a);
    state->textTransformDelta(0.0, 1.0, &x2b, &y2b);
    
    EXPECT_DOUBLE_EQ(x2a, 2.0);
    EXPECT_DOUBLE_EQ(y2a, 1.0);
    EXPECT_DOUBLE_EQ(x2b, 1.0);
    EXPECT_DOUBLE_EQ(y2b, 2.0);
}

// Test with rotated page construction
TEST(GfxStateRotated_628, ConstructionWithRotation_628) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState *state = new GfxState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state->getRotate(), 90);
    // Page dimensions should be swapped for 90-degree rotation
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 792.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 612.0);
    delete state;
}

// Test different DPI
TEST(GfxStateDPI_628, DifferentDPI_628) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState *state = new GfxState(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 300.0);
    delete state;
}
