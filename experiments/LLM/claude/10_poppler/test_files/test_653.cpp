#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <memory>
#include <vector>

#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_653 : public ::testing::Test {
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
TEST_F(GfxStateTest_653, ConstructionAndDPI_653) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_653, PageDimensions_653) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_653, GetRotate_653) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_653, SetAndGetRenderingIntent_653) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test setRenderingIntent with long string (truncation at 31 chars)
TEST_F(GfxStateTest_653, SetRenderingIntentTruncation_653) {
    // String longer than 31 characters should be truncated
    const char *longIntent = "ThisIsAVeryLongRenderingIntentNameThatExceeds31Chars";
    state->setRenderingIntent(longIntent);
    const char *result = state->getRenderingIntent();
    EXPECT_LE(strlen(result), 31u);
}

// Test setRenderingIntent with empty string
TEST_F(GfxStateTest_653, SetRenderingIntentEmpty_653) {
    state->setRenderingIntent("");
    EXPECT_STREQ(state->getRenderingIntent(), "");
}

// Test setRenderingIntent overwrites previous value
TEST_F(GfxStateTest_653, SetRenderingIntentOverwrite_653) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test line width
TEST_F(GfxStateTest_653, SetAndGetLineWidth_653) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test line width zero
TEST_F(GfxStateTest_653, SetLineWidthZero_653) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test flatness
TEST_F(GfxStateTest_653, SetAndGetFlatness_653) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test line join
TEST_F(GfxStateTest_653, SetAndGetLineJoin_653) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test line cap
TEST_F(GfxStateTest_653, SetAndGetLineCap_653) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test miter limit
TEST_F(GfxStateTest_653, SetAndGetMiterLimit_653) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test fill opacity
TEST_F(GfxStateTest_653, SetAndGetFillOpacity_653) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test stroke opacity
TEST_F(GfxStateTest_653, SetAndGetStrokeOpacity_653) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test fill overprint
TEST_F(GfxStateTest_653, SetAndGetFillOverprint_653) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_653, SetAndGetStrokeOverprint_653) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_653, SetAndGetOverprintMode_653) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test stroke adjust
TEST_F(GfxStateTest_653, SetAndGetStrokeAdjust_653) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_653, SetAndGetAlphaIsShape_653) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_653, SetAndGetTextKnockout_653) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test char space
TEST_F(GfxStateTest_653, SetAndGetCharSpace_653) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test word space
TEST_F(GfxStateTest_653, SetAndGetWordSpace_653) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_653, SetAndGetHorizScaling_653) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test leading
TEST_F(GfxStateTest_653, SetAndGetLeading_653) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_653, SetAndGetRise_653) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test render
TEST_F(GfxStateTest_653, SetAndGetRender_653) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test font size
TEST_F(GfxStateTest_653, SetFontAndGetFontSize_653) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test text matrix
TEST_F(GfxStateTest_653, SetAndGetTextMat_653) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[2], 0.0);
    EXPECT_DOUBLE_EQ(textMat[3], 1.0);
    EXPECT_DOUBLE_EQ(textMat[4], 10.0);
    EXPECT_DOUBLE_EQ(textMat[5], 20.0);
}

// Test CTM
TEST_F(GfxStateTest_653, SetAndGetCTM_653) {
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
TEST_F(GfxStateTest_653, ConcatCTM_653) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    // After concatenation with identity, should be the new matrix
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform
TEST_F(GfxStateTest_653, Transform_653) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

// Test transformDelta
TEST_F(GfxStateTest_653, TransformDelta_653) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test save and restore
TEST_F(GfxStateTest_653, SaveAndRestore_653) {
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
TEST_F(GfxStateTest_653, HasSavesInitiallyFalse_653) {
    EXPECT_FALSE(state->hasSaves());
}

// Test path operations: moveTo, lineTo, closePath
TEST_F(GfxStateTest_653, PathOperations_653) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());

    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());

    state->closePath();
}

// Test clearPath
TEST_F(GfxStateTest_653, ClearPath_653) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());

    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test curveTo
TEST_F(GfxStateTest_653, CurveTo_653) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test clip bounding box
TEST_F(GfxStateTest_653, GetClipBBox_653) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have some valid clip bounds after construction
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_653, GetUserClipBBox_653) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_653, ClipToRect_653) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping to a rect, the clip bounds should be within those values
    EXPECT_GE(xMin, 0.0);
    EXPECT_GE(yMin, 0.0);
}

// Test blend mode
TEST_F(GfxStateTest_653, SetAndGetBlendMode_653) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test line dash
TEST_F(GfxStateTest_653, SetAndGetLineDash_653) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    ASSERT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
}

// Test empty line dash
TEST_F(GfxStateTest_653, SetLineDashEmpty_653) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 0u);
}

// Test textMoveTo
TEST_F(GfxStateTest_653, TextMoveTo_653) {
    state->textMoveTo(100.0, 200.0);
    // lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test copy
TEST_F(GfxStateTest_653, CopyState_653) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// Test construction with rotation
TEST_F(GfxStateTest_653, ConstructionWithRotation_653) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test construction with different DPI
TEST_F(GfxStateTest_653, ConstructionDifferentDPI_653) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 150.0);
}

// Test fill and stroke color
TEST_F(GfxStateTest_653, SetAndGetFillColor_653) {
    GfxColor color;
    color.c[0] = 32768; // example value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_653, SetAndGetStrokeColor_653) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test getPath returns non-null
TEST_F(GfxStateTest_653, GetPathNotNull_653) {
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test transformWidth
TEST_F(GfxStateTest_653, TransformWidth_653) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_653, GetTransformedLineWidth_653) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_653, ShiftCTMAndClip_653) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// Test fill/stroke color space initially
TEST_F(GfxStateTest_653, InitialColorSpaces_653) {
    GfxColorSpace *fillCS = state->getFillColorSpace();
    GfxColorSpace *strokeCS = state->getStrokeColorSpace();
    // After construction, color spaces should be set to something (DeviceGray typically)
    ASSERT_NE(fillCS, nullptr);
    ASSERT_NE(strokeCS, nullptr);
}

// Test initial fill/stroke pattern is null
TEST_F(GfxStateTest_653, InitialPatterns_653) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test initial blend mode is Normal
TEST_F(GfxStateTest_653, InitialBlendMode_653) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// Test initial opacity values
TEST_F(GfxStateTest_653, InitialOpacityValues_653) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_653, MultipleSaveRestore_653) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(2.0);
    GfxState *s2 = state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);

    GfxState *r2 = state->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 2.0);

    GfxState *r1 = r2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 1.0);
    EXPECT_FALSE(r1->hasSaves());
}

// Test getRenderingIntent with known values
TEST_F(GfxStateTest_653, RenderingIntentKnownValues_653) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");

    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");

    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test getReusablePath
TEST_F(GfxStateTest_653, GetReusablePath_653) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto rp = state->getReusablePath();
    ASSERT_NE(rp, nullptr);
}

// Test boundary: rendering intent exactly 31 characters
TEST_F(GfxStateTest_653, RenderingIntentExactly31Chars_653) {
    // 31 character string
    const char *intent31 = "1234567890123456789012345678901";
    ASSERT_EQ(strlen(intent31), 31u);
    state->setRenderingIntent(intent31);
    EXPECT_STREQ(state->getRenderingIntent(), intent31);
}

// Test getCTM with Matrix overload
TEST_F(GfxStateTest_653, GetCTMMatrix_653) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // The matrix should be populated from the CTM
    // We just verify it doesn't crash and has reasonable values
}
