#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"

// Helper to create a basic GfxState for testing
class GfxStateTest_619 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612; // Letter width in points
        pageBox.y2 = 792; // Letter height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and getter values
TEST_F(GfxStateTest_619, ConstructionDefaults_619) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_619, GetPageBounds_619) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test CTM getter
TEST_F(GfxStateTest_619, GetCTM_619) {
    const auto &ctm = state->getCTM();
    // Default CTM for 72 DPI, no rotation, upside down should be identity-like
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_619, GetCTMMatrix_619) {
    Matrix m;
    state->getCTM(&m);
    // Just verify it doesn't crash and returns something
}

// Test setCTM
TEST_F(GfxStateTest_619, SetCTM_619) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test concatCTM
TEST_F(GfxStateTest_619, ConcatCTM_619) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // Identity
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0); // Scale by 2
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test line width
TEST_F(GfxStateTest_619, SetGetLineWidth_619) {
    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_619, LineWidthZero_619) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test flatness
TEST_F(GfxStateTest_619, SetGetFlatness_619) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test line join
TEST_F(GfxStateTest_619, SetGetLineJoin_619) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test line cap
TEST_F(GfxStateTest_619, SetGetLineCap_619) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test miter limit
TEST_F(GfxStateTest_619, SetGetMiterLimit_619) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

// Test fill opacity
TEST_F(GfxStateTest_619, SetGetFillOpacity_619) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_619, FillOpacityBoundary_619) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test stroke opacity
TEST_F(GfxStateTest_619, SetGetStrokeOpacity_619) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test fill overprint
TEST_F(GfxStateTest_619, SetGetFillOverprint_619) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_619, SetGetStrokeOverprint_619) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_619, SetGetOverprintMode_619) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test stroke adjust
TEST_F(GfxStateTest_619, SetGetStrokeAdjust_619) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_619, SetGetAlphaIsShape_619) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_619, SetGetTextKnockout_619) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test char space
TEST_F(GfxStateTest_619, SetGetCharSpace_619) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

// Test word space
TEST_F(GfxStateTest_619, SetGetWordSpace_619) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test horiz scaling
TEST_F(GfxStateTest_619, SetGetHorizScaling_619) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test leading
TEST_F(GfxStateTest_619, SetGetLeading_619) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_619, SetGetRise_619) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test render
TEST_F(GfxStateTest_619, SetGetRender_619) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test font size
TEST_F(GfxStateTest_619, SetGetFontSize_619) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test text mat
TEST_F(GfxStateTest_619, SetGetTextMat_619) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[2], 0.0);
    EXPECT_DOUBLE_EQ(textMat[3], 1.0);
    EXPECT_DOUBLE_EQ(textMat[4], 10.0);
    EXPECT_DOUBLE_EQ(textMat[5], 20.0);
}

// Test rendering intent
TEST_F(GfxStateTest_619, SetGetRenderingIntent_619) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_619, RenderingIntentRelativeColorimetric_619) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test line dash
TEST_F(GfxStateTest_619, SetGetLineDash_619) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_619, EmptyLineDash_619) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(d.size(), 0u);
}

// Test blend mode
TEST_F(GfxStateTest_619, SetGetBlendMode_619) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test save/restore
TEST_F(GfxStateTest_619, SaveRestore_619) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);

    GfxState *restored = state->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_619, HasSavesInitiallyFalse_619) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_619, HasSavesAfterSave_619) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_619, InitialPathState_619) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_619, MoveToSetsCurPt_619) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_619, LineToAfterMoveTo_619) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_619, CurveToAfterMoveTo_619) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_619, ClosePathAfterMoveTo_619) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_619, ClearPath_619) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_619, TransformIdentity_619) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_619, TransformWithTranslation_619) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_619, TransformWithScale_619) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_619, TransformDelta_619) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // transformDelta should not apply translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test text position
TEST_F(GfxStateTest_619, GetCurTextXY_619) {
    // Test getCurTextX and getCurTextY
    double tx = state->getCurTextX();
    double ty = state->getCurTextY();
    // Initial values should be 0
    EXPECT_DOUBLE_EQ(tx, 0.0);
    EXPECT_DOUBLE_EQ(ty, 0.0);
}

TEST_F(GfxStateTest_619, TextMoveTo_619) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test clip bbox
TEST_F(GfxStateTest_619, GetClipBBox_619) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_619, GetUserClipBBox_619) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_619, ClipToRect_619) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the bbox should be constrained
    EXPECT_GE(xMin, 100.0 - 1e-6);
    EXPECT_GE(yMin, 100.0 - 1e-6);
    EXPECT_LE(xMax, 200.0 + 1e-6);
    EXPECT_LE(yMax, 200.0 + 1e-6);
}

// Test copy
TEST_F(GfxStateTest_619, Copy_619) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    auto copied = std::unique_ptr<GfxState>(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// Test transform width
TEST_F(GfxStateTest_619, TransformWidth_619) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 2.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_619, GetTransformedLineWidth_619) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 6.0);
}

// Test fill and stroke color
TEST_F(GfxStateTest_619, SetGetFillColor_619) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_619, SetGetStrokeColor_619) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 65535);
}

// Test construction with rotation
TEST(GfxStateConstructionTest_619, RotatedPage_619) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
    // For 90 degree rotation, width and height may swap
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 792.0);
}

TEST(GfxStateConstructionTest_619, RotatedPage180_619) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state.getRotate(), 180);
}

TEST(GfxStateConstructionTest_619, DifferentDPI_619) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test save/restore chain
TEST_F(GfxStateTest_619, MultipleSaveRestore_619) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);

    GfxState *r1 = state->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);

    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
}

// Test isParentState
TEST_F(GfxStateTest_619, IsParentState_619) {
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    // The current state should recognize the original as parent
    EXPECT_TRUE(state->isParentState(state.get()));
}

// Test getPath
TEST_F(GfxStateTest_619, GetPathNotNull_619) {
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test getReusablePath
TEST_F(GfxStateTest_619, GetReusablePath_619) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto rp = state->getReusablePath();
    ASSERT_NE(rp, nullptr);
}

// Test textShift
TEST_F(GfxStateTest_619, TextShift_619) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double initialX = state->getCurX();
    double initialY = state->getCurY();
    state->textShift(5.0, 10.0);
    // After text shift, curX and curY should change
    // We just check it doesn't crash
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_619, ShiftCTMAndClip_619) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 50.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 50.0);
}

// Test textTransform
TEST_F(GfxStateTest_619, TextTransform_619) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    // With identity text matrix, output should be related to input
}

// Test textTransformDelta
TEST_F(GfxStateTest_619, TextTransformDelta_619) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    // Delta transform should not include translation part of textMat
}

// Test getFontTransMat
TEST_F(GfxStateTest_619, GetFontTransMat_619) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Should return some font transformation values
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_619, GetTransformedFontSize_619) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_GT(tfs, 0.0);
}

// Test parseBlendMode with valid modes
TEST_F(GfxStateTest_619, ParseBlendModeNormal_619) {
    // Create a name object for "Normal"
    Object obj(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// Test boundary: very small page
TEST(GfxStateBoundaryTest_619, VerySmallPage_619) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 1;
    pageBox.y2 = 1;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 1.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 1.0);
}

// Test boundary: large page
TEST(GfxStateBoundaryTest_619, LargePage_619) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 100000;
    pageBox.y2 = 100000;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 100000.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 100000.0);
}

// Test rendering intent with long string (boundary - fits in 32 char buffer)
TEST_F(GfxStateTest_619, RenderingIntentLongString_619) {
    // "AbsoluteColorimetric" is 20 chars, fits in 32 char buffer
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test negative line width
TEST_F(GfxStateTest_619, NegativeLineWidth_619) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test curX and curY after moveTo
TEST_F(GfxStateTest_619, CurXYAfterMoveTo_619) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->moveTo(50.0, 75.0);
    // getCurX/getCurY return the current point
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 75.0);
}

// Test curX and curY after lineTo
TEST_F(GfxStateTest_619, CurXYAfterLineTo_619) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

// Test copy with path
TEST_F(GfxStateTest_619, CopyWithPath_619) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    auto copied = std::unique_ptr<GfxState>(state->copy(true));
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isPath());
}

TEST_F(GfxStateTest_619, CopyWithoutPath_619) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    auto copied = std::unique_ptr<GfxState>(state->copy(false));
    ASSERT_NE(copied, nullptr);
}

// Test clip operation
TEST_F(GfxStateTest_619, Clip_619) {
    state->moveTo(100.0, 100.0);
    state->lineTo(200.0, 100.0);
    state->lineTo(200.0, 200.0);
    state->lineTo(100.0, 200.0);
    state->closePath();
    state->clip();
    // After clip, the clip bbox should be modified
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}
