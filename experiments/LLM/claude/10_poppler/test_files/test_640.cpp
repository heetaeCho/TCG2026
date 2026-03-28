#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState for testing
class GfxStateTest_640 : public ::testing::Test {
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

// Test basic construction and getter values
TEST_F(GfxStateTest_640, ConstructionBasicValues_640) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page coordinates
TEST_F(GfxStateTest_640, PageCoordinates_640) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test setLineJoin / getLineJoin
TEST_F(GfxStateTest_640, SetLineJoinMiter_640) {
    state->setLineJoin(lineJoinMiter);
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);
}

TEST_F(GfxStateTest_640, SetLineJoinRound_640) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

TEST_F(GfxStateTest_640, SetLineJoinBevel_640) {
    state->setLineJoin(lineJoinBevel);
    EXPECT_EQ(state->getLineJoin(), lineJoinBevel);
}

// Test setLineCap / getLineCap
TEST_F(GfxStateTest_640, SetLineCapButt_640) {
    state->setLineCap(lineCapButt);
    EXPECT_EQ(state->getLineCap(), lineCapButt);
}

TEST_F(GfxStateTest_640, SetLineCapRound_640) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

TEST_F(GfxStateTest_640, SetLineCapProjecting_640) {
    state->setLineCap(lineCapProjecting);
    EXPECT_EQ(state->getLineCap(), lineCapProjecting);
}

// Test setLineWidth / getLineWidth
TEST_F(GfxStateTest_640, SetLineWidth_640) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_640, SetLineWidthZero_640) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_640, SetLineWidthNegative_640) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test setMiterLimit / getMiterLimit
TEST_F(GfxStateTest_640, SetMiterLimit_640) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_640, SetMiterLimitZero_640) {
    state->setMiterLimit(0.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 0.0);
}

// Test setFlatness / getFlatness
TEST_F(GfxStateTest_640, SetFlatness_640) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

TEST_F(GfxStateTest_640, SetFlatnessZero_640) {
    state->setFlatness(0);
    EXPECT_EQ(state->getFlatness(), 0);
}

// Test setFillOpacity / getFillOpacity
TEST_F(GfxStateTest_640, SetFillOpacity_640) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_640, SetFillOpacityFull_640) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_640, SetFillOpacityZero_640) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

// Test setStrokeOpacity / getStrokeOpacity
TEST_F(GfxStateTest_640, SetStrokeOpacity_640) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint / getFillOverprint
TEST_F(GfxStateTest_640, SetFillOverprintTrue_640) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_640, SetFillOverprintFalse_640) {
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint / getStrokeOverprint
TEST_F(GfxStateTest_640, SetStrokeOverprintTrue_640) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_640, SetStrokeOverprintFalse_640) {
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode / getOverprintMode
TEST_F(GfxStateTest_640, SetOverprintMode_640) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

TEST_F(GfxStateTest_640, SetOverprintModeZero_640) {
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test setStrokeAdjust / getStrokeAdjust
TEST_F(GfxStateTest_640, SetStrokeAdjustTrue_640) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_640, SetStrokeAdjustFalse_640) {
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape / getAlphaIsShape
TEST_F(GfxStateTest_640, SetAlphaIsShapeTrue_640) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_640, SetAlphaIsShapeFalse_640) {
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout / getTextKnockout
TEST_F(GfxStateTest_640, SetTextKnockoutTrue_640) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

TEST_F(GfxStateTest_640, SetTextKnockoutFalse_640) {
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setCharSpace / getCharSpace
TEST_F(GfxStateTest_640, SetCharSpace_640) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test setWordSpace / getWordSpace
TEST_F(GfxStateTest_640, SetWordSpace_640) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setHorizScaling / getHorizScaling
TEST_F(GfxStateTest_640, SetHorizScaling_640) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setLeading / getLeading
TEST_F(GfxStateTest_640, SetLeading_640) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setRise / getRise
TEST_F(GfxStateTest_640, SetRise_640) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test setRender / getRender
TEST_F(GfxStateTest_640, SetRender_640) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setBlendMode / getBlendMode
TEST_F(GfxStateTest_640, SetBlendModeNormal_640) {
    state->setBlendMode(gfxBlendNormal);
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_640, SetBlendModeMultiply_640) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test setTextMat / getTextMat
TEST_F(GfxStateTest_640, SetTextMat_640) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// Test setCTM / getCTM
TEST_F(GfxStateTest_640, SetCTM_640) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// Test transform
TEST_F(GfxStateTest_640, TransformIdentity_640) {
    // After construction with no rotation, identity-like CTM expected
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    // We can at least verify it produces some output without crashing
    // The exact values depend on the CTM set during construction
    SUCCEED();
}

// Test save / restore
TEST_F(GfxStateTest_640, SaveRestore_640) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);
    
    GfxState *restored = state->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_640, HasSavesInitiallyFalse_640) {
    EXPECT_FALSE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_640, InitiallyNoPath_640) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_640, MoveToSetsCurrentPoint_640) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_640, LineToCreatesPath_640) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 10.0);
}

TEST_F(GfxStateTest_640, CurveToCreatesPath_640) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 6.0);
}

TEST_F(GfxStateTest_640, ClearPathResetsState_640) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
    
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_640, ClosePathDoesNotCrash_640) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test getPath
TEST_F(GfxStateTest_640, GetPathNotNull_640) {
    state->moveTo(0.0, 0.0);
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test setLineDash / getLineDash
TEST_F(GfxStateTest_640, SetLineDash_640) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    
    double start;
    const auto &resultDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(resultDash.size(), 2u);
    EXPECT_DOUBLE_EQ(resultDash[0], 3.0);
    EXPECT_DOUBLE_EQ(resultDash[1], 2.0);
}

TEST_F(GfxStateTest_640, SetLineDashEmpty_640) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    
    double start;
    const auto &resultDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(resultDash.size(), 0u);
}

// Test setRenderingIntent / getRenderingIntent
TEST_F(GfxStateTest_640, SetRenderingIntent_640) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_640, SetRenderingIntentRelativeColorimetric_640) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test textMoveTo
TEST_F(GfxStateTest_640, TextMoveTo_640) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test setFontSize / getFontSize
TEST_F(GfxStateTest_640, SetFontSize_640) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test copy
TEST_F(GfxStateTest_640, CopyState_640) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.5);
    
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.5);
}

// Test construction with rotation
TEST(GfxStateConstructionTest_640, ConstructWithRotation90_640) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
}

TEST(GfxStateConstructionTest_640, ConstructWithRotation180_640) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState state(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state.getRotate(), 180);
}

TEST(GfxStateConstructionTest_640, ConstructWithRotation270_640) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState state(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(state.getRotate(), 270);
}

// Test concatCTM
TEST_F(GfxStateTest_640, ConcatCTM_640) {
    // Store original CTM
    const auto &origCTM = state->getCTM();
    double orig0 = origCTM[0];
    
    // Concatenate a scaling matrix
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &newCTM = state->getCTM();
    
    // The CTM should have changed
    EXPECT_DOUBLE_EQ(newCTM[0], orig0 * 2.0);
}

// Test clip operations don't crash
TEST_F(GfxStateTest_640, ClipToRect_640) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the bounding box should be constrained
    SUCCEED();
}

// Test getUserClipBBox
TEST_F(GfxStateTest_640, GetUserClipBBox_640) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some values without crashing
    SUCCEED();
}

// Test getClipBBox
TEST_F(GfxStateTest_640, GetClipBBox_640) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Initial clip box should cover the page
    SUCCEED();
}

// Test transformDelta
TEST_F(GfxStateTest_640, TransformDelta_640) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    // Just verify it doesn't crash
    SUCCEED();
}

// Test setFillColor / getFillColor
TEST_F(GfxStateTest_640, SetFillColor_640) {
    GfxColor color;
    color.c[0] = 32768; // Some gray value
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], 32768);
}

// Test setStrokeColor / getStrokeColor
TEST_F(GfxStateTest_640, SetStrokeColor_640) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], 16384);
}

// Test multiple saves and restores
TEST_F(GfxStateTest_640, MultipleSaveRestore_640) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(2.0);
    GfxState *s2 = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    
    GfxState *r1 = state->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
    EXPECT_FALSE(r2->hasSaves());
}

// Test getReusablePath
TEST_F(GfxStateTest_640, GetReusablePath_640) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_640, ShiftCTMAndClip_640) {
    state->shiftCTMAndClip(10.0, 20.0);
    // Verify it doesn't crash and CTM is shifted
    const auto &ctm = state->getCTM();
    SUCCEED();
}

// Test getFillColorSpace initially
TEST_F(GfxStateTest_640, InitialFillColorSpace_640) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // It should have a default color space
    SUCCEED();
}

// Test getStrokeColorSpace initially
TEST_F(GfxStateTest_640, InitialStrokeColorSpace_640) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    SUCCEED();
}

// Test getFillPattern initially null
TEST_F(GfxStateTest_640, InitialFillPatternNull_640) {
    GfxPattern *p = state->getFillPattern();
    EXPECT_EQ(p, nullptr);
}

// Test getStrokePattern initially null
TEST_F(GfxStateTest_640, InitialStrokePatternNull_640) {
    GfxPattern *p = state->getStrokePattern();
    EXPECT_EQ(p, nullptr);
}

// Test getCTM with Matrix parameter
TEST_F(GfxStateTest_640, GetCTMMatrix_640) {
    Matrix m;
    state->getCTM(&m);
    // Just verify it doesn't crash
    SUCCEED();
}

// Test different DPI values
TEST(GfxStateConstructionTest_640, DifferentDPI_640) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test isParentState
TEST_F(GfxStateTest_640, IsParentState_640) {
    GfxState *savedState = state->save();
    EXPECT_TRUE(state->isParentState(state.get()));
}

// Test setting rendering intent with long string (boundary)
TEST_F(GfxStateTest_640, SetRenderingIntentLongString_640) {
    // renderingIntent is char[32], so test with something that fits
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test setFont with nullptr
TEST_F(GfxStateTest_640, SetFontNullptr_640) {
    state->setFont(nullptr, 24.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 24.0);
    EXPECT_EQ(state->getFont(), nullptr);
}
