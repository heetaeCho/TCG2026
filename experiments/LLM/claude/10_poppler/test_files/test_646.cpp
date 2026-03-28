#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include "GfxState.h"

// Helper to create a GfxState with a default page box
class GfxStateTest_646 : public ::testing::Test {
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

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_646, SetTextMatSetsAllValues_646) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

TEST_F(GfxStateTest_646, SetTextMatIdentity_646) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 0.0);
    EXPECT_DOUBLE_EQ(mat[5], 0.0);
}

TEST_F(GfxStateTest_646, SetTextMatZeroValues_646) {
    state->setTextMat(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 0.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 0.0);
    EXPECT_DOUBLE_EQ(mat[4], 0.0);
    EXPECT_DOUBLE_EQ(mat[5], 0.0);
}

TEST_F(GfxStateTest_646, SetTextMatNegativeValues_646) {
    state->setTextMat(-1.0, -2.5, -3.7, -4.2, -5.9, -6.1);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], -1.0);
    EXPECT_DOUBLE_EQ(mat[1], -2.5);
    EXPECT_DOUBLE_EQ(mat[2], -3.7);
    EXPECT_DOUBLE_EQ(mat[3], -4.2);
    EXPECT_DOUBLE_EQ(mat[4], -5.9);
    EXPECT_DOUBLE_EQ(mat[5], -6.1);
}

TEST_F(GfxStateTest_646, SetTextMatLargeValues_646) {
    state->setTextMat(1e10, 1e15, -1e10, -1e15, 1e20, -1e20);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1e10);
    EXPECT_DOUBLE_EQ(mat[1], 1e15);
    EXPECT_DOUBLE_EQ(mat[2], -1e10);
    EXPECT_DOUBLE_EQ(mat[3], -1e15);
    EXPECT_DOUBLE_EQ(mat[4], 1e20);
    EXPECT_DOUBLE_EQ(mat[5], -1e20);
}

TEST_F(GfxStateTest_646, SetTextMatOverwritesPrevious_646) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    state->setTextMat(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 10.0);
    EXPECT_DOUBLE_EQ(mat[1], 20.0);
    EXPECT_DOUBLE_EQ(mat[2], 30.0);
    EXPECT_DOUBLE_EQ(mat[3], 40.0);
    EXPECT_DOUBLE_EQ(mat[4], 50.0);
    EXPECT_DOUBLE_EQ(mat[5], 60.0);
}

TEST_F(GfxStateTest_646, SetTextMatFractionalValues_646) {
    state->setTextMat(0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 0.5);
    EXPECT_DOUBLE_EQ(mat[1], 0.25);
    EXPECT_DOUBLE_EQ(mat[2], 0.125);
    EXPECT_DOUBLE_EQ(mat[3], 0.0625);
    EXPECT_DOUBLE_EQ(mat[4], 0.03125);
    EXPECT_DOUBLE_EQ(mat[5], 0.015625);
}

// Test basic GfxState construction properties
TEST_F(GfxStateTest_646, ConstructorSetsHDPI_646) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_646, ConstructorSetsVDPI_646) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_646, ConstructorSetsPageWidth_646) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_646, ConstructorSetsPageHeight_646) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_646, ConstructorSetsRotate_646) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test setters and getters for various simple properties
TEST_F(GfxStateTest_646, SetAndGetCharSpace_646) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

TEST_F(GfxStateTest_646, SetAndGetWordSpace_646) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

TEST_F(GfxStateTest_646, SetAndGetHorizScaling_646) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_646, SetAndGetLeading_646) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_646, SetAndGetRise_646) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

TEST_F(GfxStateTest_646, SetAndGetRender_646) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_646, SetAndGetLineWidth_646) {
    state->setLineWidth(3.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.5);
}

TEST_F(GfxStateTest_646, SetAndGetFlatness_646) {
    state->setFlatness(10);
    EXPECT_EQ(state->getFlatness(), 10);
}

TEST_F(GfxStateTest_646, SetAndGetMiterLimit_646) {
    state->setMiterLimit(8.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 8.0);
}

TEST_F(GfxStateTest_646, SetAndGetFillOpacity_646) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_646, SetAndGetStrokeOpacity_646) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_646, SetAndGetFillOverprint_646) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_646, SetAndGetStrokeOverprint_646) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_646, SetAndGetOverprintMode_646) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

TEST_F(GfxStateTest_646, SetAndGetStrokeAdjust_646) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_646, SetAndGetAlphaIsShape_646) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_646, SetAndGetTextKnockout_646) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test CTM
TEST_F(GfxStateTest_646, SetCTM_646) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test save and restore
TEST_F(GfxStateTest_646, SaveAndRestore_646) {
    state->setLineWidth(5.0);
    GfxState *savedState = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);
    
    GfxState *restoredState = state->restore();
    // After restore, the state should have the old lineWidth
    // Note: restore returns the parent state
    EXPECT_NE(restoredState, nullptr);
}

TEST_F(GfxStateTest_646, HasSavesInitiallyFalse_646) {
    EXPECT_FALSE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_646, InitiallyNoCurPt_646) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_646, MoveToSetsCurPt_646) {
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_646, LineToAfterMoveTo_646) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_646, ClearPathResetsState_646) {
    state->moveTo(5.0, 5.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_646, TransformWithIdentityCTM_646) {
    // Default CTM should be identity-like for 72 DPI, no rotation
    double x2, y2;
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_646, TransformDeltaWithIdentityCTM_646) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_646, TransformWithScaleCTM_646) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 2.0 * 10.0 + 0.0 * 20.0 + 100.0);
    EXPECT_DOUBLE_EQ(y2, 0.0 * 10.0 + 3.0 * 20.0 + 200.0);
}

// Test textTransform
TEST_F(GfxStateTest_646, TextTransformWithIdentityTextMat_646) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // textTransform depends on both textMat and CTM
    // We just verify it doesn't crash and produces a result
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // The result depends on CTM as well, so just check it completes
}

// Test rendering intent
TEST_F(GfxStateTest_646, SetAndGetRenderingIntent_646) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_646, SetRenderingIntentPerceptual_646) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test lineDash
TEST_F(GfxStateTest_646, SetAndGetLineDash_646) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
}

TEST_F(GfxStateTest_646, SetLineDashEmpty_646) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(retrievedDash.empty());
}

// Test clip
TEST_F(GfxStateTest_646, ClipToRect_646) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should be bounded by the given rect
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_646, TextMoveTo_646) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test copy
TEST_F(GfxStateTest_646, CopyCreatesNewState_646) {
    state->setLineWidth(7.5);
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    const auto &mat = copied->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 2.0);
    EXPECT_DOUBLE_EQ(mat[3], 2.0);
}

// Test construction with rotation
TEST(GfxStateConstructionTest_646, ConstructWithRotation90_646) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
}

TEST(GfxStateConstructionTest_646, ConstructWithDifferentDPI_646) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test blendMode
TEST_F(GfxStateTest_646, SetAndGetBlendMode_646) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_646, DefaultBlendModeNormal_646) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// Test lineJoin and lineCap
TEST_F(GfxStateTest_646, SetAndGetLineJoin_646) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_646, SetAndGetLineCap_646) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test curveTo
TEST_F(GfxStateTest_646, CurveToAfterMoveTo_646) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 10.0, 20.0, 20.0, 30.0, 30.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_646, ClosePath_646) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test concatCTM
TEST_F(GfxStateTest_646, ConcatCTMWithIdentity_646) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_646, GetPageBounds_646) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test setTextMat with very small values
TEST_F(GfxStateTest_646, SetTextMatVerySmallValues_646) {
    state->setTextMat(1e-300, 1e-300, 1e-300, 1e-300, 1e-300, 1e-300);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1e-300);
    EXPECT_DOUBLE_EQ(mat[1], 1e-300);
    EXPECT_DOUBLE_EQ(mat[2], 1e-300);
    EXPECT_DOUBLE_EQ(mat[3], 1e-300);
    EXPECT_DOUBLE_EQ(mat[4], 1e-300);
    EXPECT_DOUBLE_EQ(mat[5], 1e-300);
}

// Test multiple set calls don't leak or interfere
TEST_F(GfxStateTest_646, SetTextMatMultipleTimes_646) {
    for (int i = 0; i < 100; ++i) {
        double v = static_cast<double>(i);
        state->setTextMat(v, v + 1, v + 2, v + 3, v + 4, v + 5);
    }
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 99.0);
    EXPECT_DOUBLE_EQ(mat[1], 100.0);
    EXPECT_DOUBLE_EQ(mat[2], 101.0);
    EXPECT_DOUBLE_EQ(mat[3], 102.0);
    EXPECT_DOUBLE_EQ(mat[4], 103.0);
    EXPECT_DOUBLE_EQ(mat[5], 104.0);
}

// Test fontSize
TEST_F(GfxStateTest_646, SetFontWithNullptr_646) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
    EXPECT_EQ(state->getFont(), nullptr);
}
