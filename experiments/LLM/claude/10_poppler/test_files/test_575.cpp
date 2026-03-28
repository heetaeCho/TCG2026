#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a basic GfxState for testing
class GfxStateTest_575 : public ::testing::Test {
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
TEST_F(GfxStateTest_575, ConstructionAndDPI_575) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_575, PageDimensions_575) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test page bounds
TEST_F(GfxStateTest_575, PageBounds_575) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_575, Rotation_575) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test rotation with 90 degrees
TEST_F(GfxStateTest_575, RotationWith90Degrees_575) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test default fill opacity
TEST_F(GfxStateTest_575, DefaultFillOpacity_575) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_575, DefaultStrokeOpacity_575) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_575, SetFillOpacity_575) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_575, SetStrokeOpacity_575) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test default line width
TEST_F(GfxStateTest_575, DefaultLineWidth_575) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set line width
TEST_F(GfxStateTest_575, SetLineWidth_575) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_575, DefaultFlatness_575) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set flatness
TEST_F(GfxStateTest_575, SetFlatness_575) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_575, DefaultMiterLimit_575) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set miter limit
TEST_F(GfxStateTest_575, SetMiterLimit_575) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_575, DefaultFillOverprint_575) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set fill overprint
TEST_F(GfxStateTest_575, SetFillOverprint_575) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_575, DefaultStrokeOverprint_575) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set stroke overprint
TEST_F(GfxStateTest_575, SetStrokeOverprint_575) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_575, DefaultOverprintMode_575) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set overprint mode
TEST_F(GfxStateTest_575, SetOverprintMode_575) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_575, DefaultStrokeAdjust_575) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set stroke adjust
TEST_F(GfxStateTest_575, SetStrokeAdjust_575) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_575, DefaultAlphaIsShape_575) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set alpha is shape
TEST_F(GfxStateTest_575, SetAlphaIsShape_575) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_575, DefaultTextKnockout_575) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set text knockout
TEST_F(GfxStateTest_575, SetTextKnockout_575) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_575, DefaultCharSpace_575) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set char space
TEST_F(GfxStateTest_575, SetCharSpace_575) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test default word space
TEST_F(GfxStateTest_575, DefaultWordSpace_575) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set word space
TEST_F(GfxStateTest_575, SetWordSpace_575) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_575, DefaultHorizScaling_575) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set horiz scaling
TEST_F(GfxStateTest_575, SetHorizScaling_575) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_575, DefaultLeading_575) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set leading
TEST_F(GfxStateTest_575, SetLeading_575) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_575, DefaultRise_575) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set rise
TEST_F(GfxStateTest_575, SetRise_575) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test default render
TEST_F(GfxStateTest_575, DefaultRender_575) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set render
TEST_F(GfxStateTest_575, SetRender_575) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default font size
TEST_F(GfxStateTest_575, DefaultFontSize_575) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test getFillColor returns non-null
TEST_F(GfxStateTest_575, GetFillColorNotNull_575) {
    const GfxColor *color = state->getFillColor();
    ASSERT_NE(color, nullptr);
}

// Test getStrokeColor returns non-null
TEST_F(GfxStateTest_575, GetStrokeColorNotNull_575) {
    const GfxColor *color = state->getStrokeColor();
    ASSERT_NE(color, nullptr);
}

// Test set fill color
TEST_F(GfxStateTest_575, SetFillColor_575) {
    GfxColor color;
    color.c[0] = 32768; // midpoint for 16-bit color
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    EXPECT_EQ(result->c[0], 32768);
}

// Test set stroke color
TEST_F(GfxStateTest_575, SetStrokeColor_575) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 65535);
}

// Test save and restore
TEST_F(GfxStateTest_575, SaveAndRestore_575) {
    state->setFillOpacity(0.5);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setFillOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.3);

    GfxState *restored = state->restore();
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_575, HasSavesInitiallyFalse_575) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_575, HasSavesAfterSave_575) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test CTM
TEST_F(GfxStateTest_575, GetCTM_575) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_575, SetCTM_575) {
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
TEST_F(GfxStateTest_575, ConcatCTM_575) {
    // Get the initial CTM
    const auto &ctmBefore = state->getCTM();
    double a0 = ctmBefore[0], b0 = ctmBefore[1];
    double c0 = ctmBefore[2], d0 = ctmBefore[3];

    // Concatenate identity
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &ctmAfter = state->getCTM();
    EXPECT_DOUBLE_EQ(ctmAfter[0], a0);
    EXPECT_DOUBLE_EQ(ctmAfter[3], d0);
}

// Test transform
TEST_F(GfxStateTest_575, Transform_575) {
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // After transform of origin, should get the translation components of CTM
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(x2, ctm[4]);
    EXPECT_DOUBLE_EQ(y2, ctm[5]);
}

// Test transformDelta
TEST_F(GfxStateTest_575, TransformDelta_575) {
    double x2, y2;
    state->transformDelta(0.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 0.0);
}

// Test path operations - initially no path
TEST_F(GfxStateTest_575, InitialPathState_575) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test moveTo creates a current point
TEST_F(GfxStateTest_575, MoveToCreatesCurrentPoint_575) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo after moveTo
TEST_F(GfxStateTest_575, LineToAfterMoveTo_575) {
    state->moveTo(100.0, 200.0);
    state->lineTo(300.0, 400.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test curveTo after moveTo
TEST_F(GfxStateTest_575, CurveToAfterMoveTo_575) {
    state->moveTo(100.0, 200.0);
    state->curveTo(150.0, 250.0, 200.0, 300.0, 250.0, 350.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test closePath
TEST_F(GfxStateTest_575, ClosePath_575) {
    state->moveTo(100.0, 200.0);
    state->lineTo(300.0, 400.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_575, ClearPath_575) {
    state->moveTo(100.0, 200.0);
    state->lineTo(300.0, 400.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test getPath returns non-null
TEST_F(GfxStateTest_575, GetPathNotNull_575) {
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test clipToRect
TEST_F(GfxStateTest_575, ClipToRect_575) {
    state->clipToRect(10.0, 20.0, 500.0, 700.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should be constrained
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 500.0);
    EXPECT_LE(yMax, 700.0);
}

// Test getClipBBox
TEST_F(GfxStateTest_575, GetClipBBox_575) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have valid clip bounds
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_575, GetUserClipBBox_575) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_575, SetAndGetBlendMode_575) {
    state->setBlendMode(gfxBlendNormal);
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_575, SetAndGetLineJoin_575) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_575, SetAndGetLineCap_575) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_575, SetAndGetRenderingIntent_575) {
    state->setRenderingIntent("Perceptual");
    const char *intent = state->getRenderingIntent();
    ASSERT_NE(intent, nullptr);
    EXPECT_STREQ(intent, "Perceptual");
}

// Test rendering intent with different values
TEST_F(GfxStateTest_575, RenderingIntentRelativeColorimetric_575) {
    state->setRenderingIntent("RelativeColorimetric");
    const char *intent = state->getRenderingIntent();
    ASSERT_NE(intent, nullptr);
    EXPECT_STREQ(intent, "RelativeColorimetric");
}

// Test rendering intent truncation for long strings (buffer is 32 chars)
TEST_F(GfxStateTest_575, RenderingIntentLongString_575) {
    // The internal buffer is 32 chars, so a very long string should be truncated
    state->setRenderingIntent("ThisIsAVeryLongRenderingIntentStringThatExceedsBuffer");
    const char *intent = state->getRenderingIntent();
    ASSERT_NE(intent, nullptr);
    EXPECT_LE(strlen(intent), 31u);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_575, SetAndGetTextMat_575) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_575, TextMoveTo_575) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test getLineDash
TEST_F(GfxStateTest_575, SetAndGetLineDash_575) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
}

// Test copy
TEST_F(GfxStateTest_575, CopyState_575) {
    state->setFillOpacity(0.7);
    state->setLineWidth(3.0);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
}

// Test construction with different DPI values
TEST_F(GfxStateTest_575, DifferentDPI_575) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 150.0);
}

// Test construction with upside down false
TEST_F(GfxStateTest_575, UpsideDownFalse_575) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState notFlipped(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(notFlipped.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notFlipped.getPageHeight(), 792.0);
}

// Test default fill color space is nullptr initially (DeviceGray set by default)
TEST_F(GfxStateTest_575, DefaultFillColorSpace_575) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // Default should be set (DeviceGray typically)
    ASSERT_NE(cs, nullptr);
}

// Test default stroke color space
TEST_F(GfxStateTest_575, DefaultStrokeColorSpace_575) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    ASSERT_NE(cs, nullptr);
}

// Test null fill pattern initially
TEST_F(GfxStateTest_575, DefaultFillPattern_575) {
    GfxPattern *pattern = state->getFillPattern();
    EXPECT_EQ(pattern, nullptr);
}

// Test null stroke pattern initially
TEST_F(GfxStateTest_575, DefaultStrokePattern_575) {
    GfxPattern *pattern = state->getStrokePattern();
    EXPECT_EQ(pattern, nullptr);
}

// Test default font is null
TEST_F(GfxStateTest_575, DefaultFontNull_575) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getCurX and getCurY defaults
TEST_F(GfxStateTest_575, DefaultCurXY_575) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_575, MultipleSaveRestore_575) {
    state->setFillOpacity(0.8);
    state->save();
    state->setFillOpacity(0.5);
    state->save();
    state->setFillOpacity(0.2);

    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.2);

    state->restore();
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);

    state->restore();
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.8);
}

// Test setLineDash with empty dash
TEST_F(GfxStateTest_575, SetEmptyLineDash_575) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test boundary: zero line width
TEST_F(GfxStateTest_575, ZeroLineWidth_575) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test boundary: negative line width
TEST_F(GfxStateTest_575, NegativeLineWidth_575) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test fill opacity boundary: 0.0
TEST_F(GfxStateTest_575, FillOpacityZero_575) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

// Test fill opacity boundary: 1.0
TEST_F(GfxStateTest_575, FillOpacityOne_575) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_575, ShiftCTMAndClip_575) {
    const auto &ctmBefore = state->getCTM();
    double e_before = ctmBefore[4];
    double f_before = ctmBefore[5];

    state->shiftCTMAndClip(10.0, 20.0);

    const auto &ctmAfter = state->getCTM();
    // Translation should have changed
    EXPECT_NE(ctmAfter[4], e_before);
}

// Test textTransform
TEST_F(GfxStateTest_575, TextTransform_575) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    // Results depend on CTM and text matrix combination
    // Just verify it doesn't crash and returns finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test textTransformDelta
TEST_F(GfxStateTest_575, TextTransformDelta_575) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(0.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_575, GetTransformedLineWidth_575) {
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tlw));
    EXPECT_GE(tlw, 0.0);
}

// Test transformWidth
TEST_F(GfxStateTest_575, TransformWidth_575) {
    double tw = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test transformWidth with zero
TEST_F(GfxStateTest_575, TransformWidthZero_575) {
    double tw = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(tw, 0.0);
}

// Test rotation 180
TEST_F(GfxStateTest_575, Rotation180_575) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

// Test rotation 270
TEST_F(GfxStateTest_575, Rotation270_575) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// Test getCTM with Matrix overload
TEST_F(GfxStateTest_575, GetCTMMatrix_575) {
    Matrix m;
    state->getCTM(&m);
    // Just verify it doesn't crash; Matrix should have valid values
    EXPECT_TRUE(std::isfinite(m.m[0]));
}

// Test isParentState
TEST_F(GfxStateTest_575, IsParentState_575) {
    GfxState *savedState = state->save();
    // state should be the parent of savedState chain
    // The current state after save() should recognize the old state as parent
    // This test verifies the function doesn't crash
    EXPECT_FALSE(state->isParentState(state.get()));
    state->restore();
}

// Test getReusablePath
TEST_F(GfxStateTest_575, GetReusablePath_575) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    auto pathIter = state->getReusablePath();
    ASSERT_NE(pathIter, nullptr);
}
