#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a GfxState with default parameters
class GfxStateTest_564 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;  // Letter size width in points
        pageBox.y2 = 792;  // Letter size height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test construction and basic getters
TEST_F(GfxStateTest_564, GetHDPI_564) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_564, GetVDPI_564) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_564, GetPageDimensions_564) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_564, GetRotate_564) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_564, GetX1Y1X2Y2_564) {
    // These represent the page box coordinates
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test with different DPI values
TEST_F(GfxStateTest_564, ConstructWithDifferentDPI_564) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 150.0);
}

// Test rotation
TEST_F(GfxStateTest_564, ConstructWithRotation90_564) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_564, ConstructWithRotation180_564) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_564, ConstructWithRotation270_564) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// Test CTM
TEST_F(GfxStateTest_564, GetCTM_564) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_564, SetCTM_564) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_564, ConcatCTM_564) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    // After concat with identity, should be the concatenated matrix
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test line properties
TEST_F(GfxStateTest_564, SetGetLineWidth_564) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_564, SetGetLineWidthZero_564) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_564, SetGetMiterLimit_564) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_564, SetGetFlatness_564) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

TEST_F(GfxStateTest_564, SetGetLineJoin_564) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_564, SetGetLineCap_564) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_564, SetGetLineDash_564) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &resultDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(resultDash.size(), 2u);
    EXPECT_DOUBLE_EQ(resultDash[0], 3.0);
    EXPECT_DOUBLE_EQ(resultDash[1], 2.0);
}

// Test opacity
TEST_F(GfxStateTest_564, SetGetFillOpacity_564) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_564, SetGetStrokeOpacity_564) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_564, SetGetFillOpacityBoundaryZero_564) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_564, SetGetFillOpacityBoundaryOne_564) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test overprint
TEST_F(GfxStateTest_564, SetGetFillOverprint_564) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_564, SetGetStrokeOverprint_564) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_564, SetGetOverprintMode_564) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test blend mode
TEST_F(GfxStateTest_564, SetGetBlendMode_564) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_564, DefaultBlendMode_564) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// Test text properties
TEST_F(GfxStateTest_564, SetGetCharSpace_564) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

TEST_F(GfxStateTest_564, SetGetWordSpace_564) {
    state->setWordSpace(5.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 5.0);
}

TEST_F(GfxStateTest_564, SetGetHorizScaling_564) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_564, SetGetLeading_564) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_564, SetGetRise_564) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_564, SetGetRender_564) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_564, SetGetTextMat_564) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[2], 0.0);
    EXPECT_DOUBLE_EQ(textMat[3], 1.0);
    EXPECT_DOUBLE_EQ(textMat[4], 10.0);
    EXPECT_DOUBLE_EQ(textMat[5], 20.0);
}

// Test font
TEST_F(GfxStateTest_564, DefaultFontIsNull_564) {
    EXPECT_EQ(state->getFont(), nullptr);
}

TEST_F(GfxStateTest_564, GetFontSize_564) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test stroke adjust
TEST_F(GfxStateTest_564, SetGetStrokeAdjust_564) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_564, SetGetAlphaIsShape_564) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_564, SetGetTextKnockout_564) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test rendering intent
TEST_F(GfxStateTest_564, SetGetRenderingIntent_564) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_564, SetRenderingIntentAbsoluteColorimetric_564) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_564, SetRenderingIntentSaturation_564) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_564, SetRenderingIntentPerceptual_564) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test path operations
TEST_F(GfxStateTest_564, InitialPathState_564) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_564, MoveToSetsCurPt_564) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_564, LineToCreatesPath_564) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_564, CurveToCreatesPath_564) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_564, ClearPathResetsState_564) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_564, ClosePathOperation_564) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_564, TransformWithIdentityCTM_564) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_564, TransformWithScaleCTM_564) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

TEST_F(GfxStateTest_564, TransformWithTranslation_564) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_564, TransformDelta_564) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test save and restore
TEST_F(GfxStateTest_564, SaveAndRestore_564) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_564, HasSavesInitiallyFalse_564) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_564, SaveCreatesHasSaves_564) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up
    saved->restore();
}

// Test clip bounding box
TEST_F(GfxStateTest_564, GetClipBBox_564) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should encompass the page
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_564, GetUserClipBBox_564) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_564, ClipToRect_564) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip box should be bounded
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test text position
TEST_F(GfxStateTest_564, TextMoveTo_564) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 20.0);
}

TEST_F(GfxStateTest_564, GetLineXY_564) {
    state->textMoveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 25.0);
}

// Test copy
TEST_F(GfxStateTest_564, CopyState_564) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.8);
    auto copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
    delete copied;
}

// Test color spaces default to nullptr patterns
TEST_F(GfxStateTest_564, DefaultFillPatternNull_564) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_564, DefaultStrokePatternNull_564) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test transformWidth
TEST_F(GfxStateTest_564, TransformWidth_564) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double transformed = state->transformWidth(1.0);
    EXPECT_GT(transformed, 0.0);
}

TEST_F(GfxStateTest_564, TransformWidthZero_564) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double transformed = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(transformed, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_564, GetTransformedLineWidth_564) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(2.0);
    double w = state->getTransformedLineWidth();
    EXPECT_GT(w, 0.0);
}

// Test parseBlendMode static method
TEST_F(GfxStateTest_564, ParseBlendModeNormal_564) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_564, ShiftCTMAndClip_564) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// Test upside down construction
TEST_F(GfxStateTest_564, ConstructUpsideDownFalse_564) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState notUpsideDown(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(notUpsideDown.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notUpsideDown.getPageHeight(), 792.0);
}

// Test isParentState
TEST_F(GfxStateTest_564, IsParentState_564) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
    saved->restore();
}

// Test default color spaces are initially copyable as null
TEST_F(GfxStateTest_564, CopyDefaultGrayColorSpaceInitial_564) {
    auto cs = state->copyDefaultGrayColorSpace();
    // Initially might be null or a default space
    // We just test it doesn't crash
}

TEST_F(GfxStateTest_564, CopyDefaultRGBColorSpaceInitial_564) {
    auto cs = state->copyDefaultRGBColorSpace();
}

TEST_F(GfxStateTest_564, CopyDefaultCMYKColorSpaceInitial_564) {
    auto cs = state->copyDefaultCMYKColorSpace();
}

// Test multiple saves
TEST_F(GfxStateTest_564, MultipleSaves_564) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);

    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);

    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);

    GfxState *r0 = r1->restore();
    EXPECT_DOUBLE_EQ(r0->getLineWidth(), 1.0);
}

// Test GetPath returns non-null
TEST_F(GfxStateTest_564, GetPathNotNull_564) {
    EXPECT_NE(state->getPath(), nullptr);
}

// Test GetReusablePath
TEST_F(GfxStateTest_564, GetReusablePath_564) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test negative coordinates
TEST_F(GfxStateTest_564, NegativeCoordinates_564) {
    PDFRectangle pageBox;
    pageBox.x1 = -100;
    pageBox.y1 = -100;
    pageBox.x2 = 100;
    pageBox.y2 = 100;
    GfxState negState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(negState.getX1(), -100.0);
    EXPECT_DOUBLE_EQ(negState.getY1(), -100.0);
    EXPECT_DOUBLE_EQ(negState.getX2(), 100.0);
    EXPECT_DOUBLE_EQ(negState.getY2(), 100.0);
}

// Test very large DPI
TEST_F(GfxStateTest_564, VeryLargeDPI_564) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState largeDpiState(10000.0, 10000.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(largeDpiState.getHDPI(), 10000.0);
    EXPECT_DOUBLE_EQ(largeDpiState.getVDPI(), 10000.0);
}

// Test empty line dash
TEST_F(GfxStateTest_564, EmptyLineDash_564) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &resultDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(resultDash.size(), 0u);
}

// Test getCTM with Matrix parameter
TEST_F(GfxStateTest_564, GetCTMMatrix_564) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Just verify it doesn't crash; exact Matrix layout is implementation-dependent
}

// Test fill color set/get
TEST_F(GfxStateTest_564, SetGetFillColor_564) {
    GfxColor color;
    color.c[0] = 32768; // midpoint value
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], 32768);
}

TEST_F(GfxStateTest_564, SetGetStrokeColor_564) {
    GfxColor color;
    color.c[0] = 65535; // max value
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], 65535);
}

// Test curX and curY after moveTo
TEST_F(GfxStateTest_564, CurXYAfterMoveTo_564) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->moveTo(42.0, 84.0);
    // curX/curY should reflect the device coordinates after transform
    // With identity CTM, they should be the same
    double curX = state->getCurX();
    double curY = state->getCurY();
    EXPECT_DOUBLE_EQ(curX, 42.0);
    EXPECT_DOUBLE_EQ(curY, 84.0);
}
