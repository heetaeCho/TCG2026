#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_642 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_642, ConstructionAndDPI_642) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_642, PageDimensions_642) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_642, Rotation_642) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page coordinates
TEST_F(GfxStateTest_642, PageCoordinates_642) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_642, SetMiterLimitNormal_642) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_642, SetMiterLimitZero_642) {
    state->setMiterLimit(0.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 0.0);
}

TEST_F(GfxStateTest_642, SetMiterLimitNegative_642) {
    state->setMiterLimit(-5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), -5.0);
}

TEST_F(GfxStateTest_642, SetMiterLimitLargeValue_642) {
    state->setMiterLimit(1e10);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 1e10);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_642, SetLineWidth_642) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_642, SetLineWidthZero_642) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_642, SetFlatness_642) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_642, SetLineJoin_642) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_642, SetLineCap_642) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_642, SetFillOpacity_642) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_642, SetFillOpacityZero_642) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_642, SetFillOpacityOne_642) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_642, SetStrokeOpacity_642) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_642, SetFillOverprint_642) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_642, SetStrokeOverprint_642) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_642, SetOverprintMode_642) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_642, SetStrokeAdjust_642) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_642, SetAlphaIsShape_642) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_642, SetTextKnockout_642) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setCharSpace and getCharSpace
TEST_F(GfxStateTest_642, SetCharSpace_642) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test setWordSpace and getWordSpace
TEST_F(GfxStateTest_642, SetWordSpace_642) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_642, SetHorizScaling_642) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setLeading and getLeading
TEST_F(GfxStateTest_642, SetLeading_642) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_642, SetRise_642) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_642, SetRender_642) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_642, SetBlendMode_642) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_642, SetRenderingIntent_642) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_642, SetRenderingIntentRelativeColorimetric_642) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_642, SetRenderingIntentSaturation_642) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_642, SetRenderingIntentAbsoluteColorimetric_642) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_642, SetTextMat_642) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_642, SetCTM_642) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// Test concatCTM
TEST_F(GfxStateTest_642, ConcatCTM_642) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform
TEST_F(GfxStateTest_642, Transform_642) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_642, TransformWithScaling_642) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test transformDelta
TEST_F(GfxStateTest_642, TransformDelta_642) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test save and restore
TEST_F(GfxStateTest_642, SaveAndRestore_642) {
    state->setMiterLimit(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    
    saved->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(saved->getMiterLimit(), 10.0);
    
    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getMiterLimit(), 5.0);
}

// Test hasSaves
TEST_F(GfxStateTest_642, HasSavesInitiallyFalse_642) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_642, HasSavesAfterSave_642) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    (void)restored;
}

// Test path operations
TEST_F(GfxStateTest_642, PathOperationsMoveTo_642) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
    
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_642, PathOperationsLineTo_642) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_642, PathOperationsCurveTo_642) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(5.0, 5.0, 10.0, 10.0, 15.0, 15.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_642, PathOperationsClosePath_642) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_642, ClearPath_642) {
    state->moveTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test getPath
TEST_F(GfxStateTest_642, GetPath_642) {
    state->clearPath();
    state->moveTo(5.0, 5.0);
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test clip operations
TEST_F(GfxStateTest_642, ClipToRect_642) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_642, GetUserClipBBox_642) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return valid clip bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getClipBBox
TEST_F(GfxStateTest_642, GetClipBBox_642) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test textMoveTo
TEST_F(GfxStateTest_642, TextMoveTo_642) {
    state->textMoveTo(50.0, 100.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 100.0);
}

// Test setLineDash
TEST_F(GfxStateTest_642, SetLineDash_642) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_642, SetLineDashWithStart_642) {
    std::vector<double> dash = {2.0, 4.0, 6.0};
    state->setLineDash(std::move(dash), 1.5);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 3u);
    EXPECT_DOUBLE_EQ(start, 1.5);
}

TEST_F(GfxStateTest_642, SetLineDashEmpty_642) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 0u);
}

// Test setFont
TEST_F(GfxStateTest_642, SetFont_642) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test copy
TEST_F(GfxStateTest_642, Copy_642) {
    state->setMiterLimit(7.5);
    state->setLineWidth(3.0);
    state->setFillOpacity(0.8);
    
    auto copied = state->copy();
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getMiterLimit(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
    delete copied;
}

// Test with different page rotations
TEST_F(GfxStateTest_642, ConstructionWithRotation90_642) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

TEST_F(GfxStateTest_642, ConstructionWithRotation180_642) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState->getRotate(), 180);
}

TEST_F(GfxStateTest_642, ConstructionWithRotation270_642) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState->getRotate(), 270);
}

// Test with upsideDown false
TEST_F(GfxStateTest_642, ConstructionUpsideDownFalse_642) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto noFlipState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(noFlipState->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(noFlipState->getVDPI(), 72.0);
}

// Test different DPI values
TEST_F(GfxStateTest_642, ConstructionDifferentDPI_642) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto highDpiState = std::make_unique<GfxState>(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState->getVDPI(), 600.0);
}

// Test transformWidth
TEST_F(GfxStateTest_642, TransformWidth_642) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double result = state->transformWidth(1.0);
    EXPECT_GT(result, 0.0);
}

TEST_F(GfxStateTest_642, TransformWidthZero_642) {
    double result = state->transformWidth(0.0);
    EXPECT_GE(result, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_642, GetTransformedLineWidth_642) {
    state->setLineWidth(1.0);
    double result = state->getTransformedLineWidth();
    EXPECT_GT(result, 0.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_642, ShiftCTMAndClip_642) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// Test getCTM with Matrix output
TEST_F(GfxStateTest_642, GetCTMMatrix_642) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // The Matrix should contain the CTM values
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test textTransform
TEST_F(GfxStateTest_642, TextTransform_642) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    // Result depends on the combination of text matrix and CTM
    // Just verify it produces some output
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test textTransformDelta
TEST_F(GfxStateTest_642, TextTransformDelta_642) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test multiple set/get cycles for miter limit
TEST_F(GfxStateTest_642, SetMiterLimitMultipleTimes_642) {
    state->setMiterLimit(1.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 1.0);
    
    state->setMiterLimit(100.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 100.0);
    
    state->setMiterLimit(0.5);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 0.5);
}

// Test getFillColor and setFillColor
TEST_F(GfxStateTest_642, SetAndGetFillColor_642) {
    GfxColor color;
    color.c[0] = 32768; // mid value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test getStrokeColor and setStrokeColor
TEST_F(GfxStateTest_642, SetAndGetStrokeColor_642) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 65535);
}

// Test save/restore preserves state
TEST_F(GfxStateTest_642, SaveRestorePreservesMultipleProperties_642) {
    state->setLineWidth(5.0);
    state->setMiterLimit(15.0);
    state->setFillOpacity(0.3);
    state->setStrokeOpacity(0.7);
    state->setCharSpace(2.0);
    
    GfxState *saved = state->save();
    saved->setLineWidth(10.0);
    saved->setMiterLimit(20.0);
    saved->setFillOpacity(0.9);
    saved->setStrokeOpacity(0.1);
    saved->setCharSpace(5.0);
    
    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
    EXPECT_DOUBLE_EQ(restored->getMiterLimit(), 15.0);
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.3);
    EXPECT_DOUBLE_EQ(restored->getStrokeOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(restored->getCharSpace(), 2.0);
}

// Test nested save/restore
TEST_F(GfxStateTest_642, NestedSaveRestore_642) {
    state->setMiterLimit(1.0);
    
    GfxState *s1 = state->save();
    s1->setMiterLimit(2.0);
    
    GfxState *s2 = s1->save();
    s2->setMiterLimit(3.0);
    EXPECT_DOUBLE_EQ(s2->getMiterLimit(), 3.0);
    
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getMiterLimit(), 2.0);
    
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getMiterLimit(), 1.0);
}

// Test isParentState
TEST_F(GfxStateTest_642, IsParentState_642) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
    GfxState *restored = saved->restore();
    (void)restored;
}

// Test getCurX/getCurY after moveTo
TEST_F(GfxStateTest_642, GetCurXYAfterMoveTo_642) {
    state->clearPath();
    state->moveTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 42.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 84.0);
}

// Test getFontSize
TEST_F(GfxStateTest_642, GetFontSizeDefault_642) {
    // Before setting, fontSize should have some default value
    double fontSize = state->getFontSize();
    EXPECT_TRUE(std::isfinite(fontSize));
}

// Test setFont with a size
TEST_F(GfxStateTest_642, SetFontSize_642) {
    state->setFont(nullptr, 24.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 24.0);
}

// Test getReusablePath
TEST_F(GfxStateTest_642, GetReusablePath_642) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test parseBlendMode - static method
TEST_F(GfxStateTest_642, ParseBlendModeNormal_642) {
    // This test depends on being able to construct Object appropriately
    // We'll test with a known blend mode name
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// Test clip
TEST_F(GfxStateTest_642, Clip_642) {
    state->clearPath();
    state->moveTo(10.0, 10.0);
    state->lineTo(100.0, 10.0);
    state->lineTo(100.0, 100.0);
    state->lineTo(10.0, 100.0);
    state->closePath();
    state->clip();
    
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}
