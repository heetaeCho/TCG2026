#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_652 : public ::testing::Test {
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
TEST_F(GfxStateTest_652, ConstructionDefaults_652) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page dimensions
TEST_F(GfxStateTest_652, PageDimensions_652) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_652, SetRender_652) {
    state->setRender(0);
    EXPECT_EQ(state->getRender(), 0);

    state->setRender(1);
    EXPECT_EQ(state->getRender(), 1);

    state->setRender(3);
    EXPECT_EQ(state->getRender(), 3);

    state->setRender(7);
    EXPECT_EQ(state->getRender(), 7);
}

// Test setRender with boundary values
TEST_F(GfxStateTest_652, SetRenderBoundary_652) {
    state->setRender(-1);
    EXPECT_EQ(state->getRender(), -1);

    state->setRender(0);
    EXPECT_EQ(state->getRender(), 0);

    state->setRender(INT_MAX);
    EXPECT_EQ(state->getRender(), INT_MAX);

    state->setRender(INT_MIN);
    EXPECT_EQ(state->getRender(), INT_MIN);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_652, SetLineWidth_652) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);

    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);

    state->setLineWidth(100.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 100.0);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_652, SetFillOpacity_652) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);

    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);

    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_652, SetStrokeOpacity_652) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_652, SetFillOverprint_652) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());

    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_652, SetStrokeOverprint_652) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());

    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_652, SetOverprintMode_652) {
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);

    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_652, SetFlatness_652) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);

    state->setFlatness(0);
    EXPECT_EQ(state->getFlatness(), 0);

    state->setFlatness(100);
    EXPECT_EQ(state->getFlatness(), 100);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_652, SetMiterLimit_652) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);

    state->setMiterLimit(1.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 1.0);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_652, SetStrokeAdjust_652) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());

    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_652, SetAlphaIsShape_652) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());

    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_652, SetTextKnockout_652) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());

    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setCharSpace and getCharSpace
TEST_F(GfxStateTest_652, SetCharSpace_652) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);

    state->setCharSpace(0.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);

    state->setCharSpace(-0.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), -0.5);
}

// Test setWordSpace and getWordSpace
TEST_F(GfxStateTest_652, SetWordSpace_652) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_652, SetHorizScaling_652) {
    state->setHorizScaling(100.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 100.0);

    state->setHorizScaling(50.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 50.0);
}

// Test setLeading and getLeading
TEST_F(GfxStateTest_652, SetLeading_652) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_652, SetRise_652) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);

    state->setRise(-3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), -3.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_652, SetTextMat_652) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 0.0);
    EXPECT_DOUBLE_EQ(mat[5], 0.0);
}

// Test setTextMat with non-identity matrix
TEST_F(GfxStateTest_652, SetTextMatNonIdentity_652) {
    state->setTextMat(2.0, 0.5, -0.5, 2.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 2.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.5);
    EXPECT_DOUBLE_EQ(mat[2], -0.5);
    EXPECT_DOUBLE_EQ(mat[3], 2.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_652, SetCTM_652) {
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
TEST_F(GfxStateTest_652, ConcatCTM_652) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test transform
TEST_F(GfxStateTest_652, Transform_652) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_652, TransformWithScaling_652) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test transformDelta
TEST_F(GfxStateTest_652, TransformDelta_652) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test save and restore
TEST_F(GfxStateTest_652, SaveRestore_652) {
    state->setRender(5);
    state->setLineWidth(3.0);

    GfxState *savedState = state->save();
    ASSERT_NE(savedState, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setRender(2);
    state->setLineWidth(1.0);
    EXPECT_EQ(state->getRender(), 2);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);

    GfxState *restoredState = state->restore();
    ASSERT_NE(restoredState, nullptr);
    // After restore, the pointer changes - restoredState is the parent
    // The parent should have the original values
}

// Test hasSaves
TEST_F(GfxStateTest_652, HasSavesInitiallyFalse_652) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_652, HasSavesAfterSave_652) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test path operations - moveTo, lineTo
TEST_F(GfxStateTest_652, PathOperations_652) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test path operations - lineTo
TEST_F(GfxStateTest_652, PathLineToAfterMoveTo_652) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test clearPath
TEST_F(GfxStateTest_652, ClearPath_652) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());

    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_652, CurveTo_652) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test closePath
TEST_F(GfxStateTest_652, ClosePath_652) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_652, SetLineDash_652) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 0.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    ASSERT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 2.0);
}

// Test setLineDash with non-zero start
TEST_F(GfxStateTest_652, SetLineDashWithStart_652) {
    std::vector<double> dash = {5.0, 3.0, 1.0};
    state->setLineDash(std::move(dash), 2.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 2.0);
    ASSERT_EQ(retrievedDash.size(), 3u);
}

// Test empty line dash
TEST_F(GfxStateTest_652, SetLineDashEmpty_652) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(retrievedDash.empty());
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_652, SetLineJoin_652) {
    state->setLineJoin(LineJoinStyle::Miter);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Miter);

    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);

    state->setLineJoin(LineJoinStyle::Bevel);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Bevel);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_652, SetLineCap_652) {
    state->setLineCap(LineCapStyle::Butt);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Butt);

    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);

    state->setLineCap(LineCapStyle::Projecting);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Projecting);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_652, SetRenderingIntent_652) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");

    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");

    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");

    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_652, SetBlendMode_652) {
    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);

    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test textMoveTo
TEST_F(GfxStateTest_652, TextMoveTo_652) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test clipToRect
TEST_F(GfxStateTest_652, ClipToRect_652) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should have been intersected with the existing clip
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
}

// Test getClipBBox
TEST_F(GfxStateTest_652, GetClipBBox_652) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have some valid clip box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_652, GetUserClipBBox_652) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test copy
TEST_F(GfxStateTest_652, Copy_652) {
    state->setRender(3);
    state->setLineWidth(5.0);
    state->setFillOpacity(0.8);

    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getRender(), 3);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 5.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
}

// Test with rotation
TEST_F(GfxStateTest_652, ConstructionWithRotation_652) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test with 180 rotation
TEST_F(GfxStateTest_652, ConstructionWithRotation180_652) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

// Test with 270 rotation
TEST_F(GfxStateTest_652, ConstructionWithRotation270_652) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// Test with upsideDown = false
TEST_F(GfxStateTest_652, ConstructionNotUpsideDown_652) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState notUpsideDownState(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(notUpsideDownState.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notUpsideDownState.getPageHeight(), 792.0);
}

// Test different DPI values
TEST_F(GfxStateTest_652, ConstructionDifferentDPI_652) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState highDPIState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDPIState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDPIState.getVDPI(), 300.0);
}

// Test different horizontal and vertical DPI
TEST_F(GfxStateTest_652, ConstructionAsymmetricDPI_652) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState asymDPIState(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(asymDPIState.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(asymDPIState.getVDPI(), 300.0);
}

// Test getPath returns non-null
TEST_F(GfxStateTest_652, GetPathNotNull_652) {
    EXPECT_NE(state->getPath(), nullptr);
}

// Test isParentState
TEST_F(GfxStateTest_652, IsParentState_652) {
    GfxState *child = state->save();
    ASSERT_NE(child, nullptr);
    // state is now the child, and it should recognize its parent
    EXPECT_TRUE(state->isParentState(child));
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_652, SetFillColor_652) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_652, SetStrokeColor_652) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_652, GetTransformedLineWidth_652) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_GT(tw, 0.0);
}

// Test transformWidth
TEST_F(GfxStateTest_652, TransformWidth_652) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_652, GetTransformedFontSize_652) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double fs = state->getTransformedFontSize();
    // The result depends on font size and text mat; just check it doesn't crash
    EXPECT_GE(fs, 0.0);
}

// Test getFontTransMat
TEST_F(GfxStateTest_652, GetFontTransMat_652) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Just verifying no crash and values are obtained
    SUCCEED();
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_652, ShiftCTMAndClip_652) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 50.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 50.0);
}

// Test getReusablePath
TEST_F(GfxStateTest_652, GetReusablePath_652) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}

// Test setFont and getFont
TEST_F(GfxStateTest_652, SetFontNullptr_652) {
    state->setFont(nullptr, 12.0);
    EXPECT_EQ(state->getFont(), nullptr);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test multiple save/restore
TEST_F(GfxStateTest_652, MultipleSaveRestore_652) {
    state->setRender(1);
    state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setRender(2);
    state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setRender(3);
    EXPECT_EQ(state->getRender(), 3);

    GfxState *restored1 = state->restore();
    ASSERT_NE(restored1, nullptr);

    GfxState *restored2 = restored1->restore();
    ASSERT_NE(restored2, nullptr);
    EXPECT_FALSE(restored2->hasSaves());
}

// Test textShift
TEST_F(GfxStateTest_652, TextShift_652) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Just test it doesn't crash
    state->textShift(5.0, 10.0);
    SUCCEED();
}

// Test textTransform
TEST_F(GfxStateTest_652, TextTransform_652) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    // With identity text matrix, should pass through
    SUCCEED();
}

// Test textTransformDelta
TEST_F(GfxStateTest_652, TextTransformDelta_652) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    SUCCEED();
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_652, GetCTMMatrix_652) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Just check it doesn't crash
    SUCCEED();
}
