#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
static std::unique_ptr<GfxState> createDefaultGfxState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_580 : public ::testing::Test {
protected:
    void SetUp() override {
        state = createDefaultGfxState();
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI values
TEST_F(GfxStateTest_580, ConstructionDPI_580) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_580, PageDimensions_580) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test page width and height
TEST_F(GfxStateTest_580, PageWidthHeight_580) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_580, Rotate_580) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test default fill opacity
TEST_F(GfxStateTest_580, DefaultFillOpacity_580) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_580, DefaultStrokeOpacity_580) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test setting fill opacity
TEST_F(GfxStateTest_580, SetFillOpacity_580) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setting stroke opacity
TEST_F(GfxStateTest_580, SetStrokeOpacity_580) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default line width
TEST_F(GfxStateTest_580, DefaultLineWidth_580) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test setting line width
TEST_F(GfxStateTest_580, SetLineWidth_580) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_580, DefaultFlatness_580) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test setting flatness
TEST_F(GfxStateTest_580, SetFlatness_580) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_580, DefaultMiterLimit_580) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test setting miter limit
TEST_F(GfxStateTest_580, SetMiterLimit_580) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_580, DefaultFillOverprint_580) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setting fill overprint
TEST_F(GfxStateTest_580, SetFillOverprint_580) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_580, DefaultStrokeOverprint_580) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setting stroke overprint
TEST_F(GfxStateTest_580, SetStrokeOverprint_580) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_580, DefaultOverprintMode_580) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test setting overprint mode
TEST_F(GfxStateTest_580, SetOverprintMode_580) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_580, DefaultStrokeAdjust_580) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setting stroke adjust
TEST_F(GfxStateTest_580, SetStrokeAdjust_580) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_580, DefaultAlphaIsShape_580) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setting alpha is shape
TEST_F(GfxStateTest_580, SetAlphaIsShape_580) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_580, DefaultTextKnockout_580) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setting text knockout
TEST_F(GfxStateTest_580, SetTextKnockout_580) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default font size
TEST_F(GfxStateTest_580, DefaultFontSize_580) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test setting char space
TEST_F(GfxStateTest_580, SetCharSpace_580) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test default char space
TEST_F(GfxStateTest_580, DefaultCharSpace_580) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test setting word space
TEST_F(GfxStateTest_580, SetWordSpace_580) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test default word space
TEST_F(GfxStateTest_580, DefaultWordSpace_580) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test setting horiz scaling
TEST_F(GfxStateTest_580, SetHorizScaling_580) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_580, DefaultHorizScaling_580) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test setting leading
TEST_F(GfxStateTest_580, SetLeading_580) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test default leading
TEST_F(GfxStateTest_580, DefaultLeading_580) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test setting rise
TEST_F(GfxStateTest_580, SetRise_580) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test default rise
TEST_F(GfxStateTest_580, DefaultRise_580) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test setting render
TEST_F(GfxStateTest_580, SetRender_580) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default render
TEST_F(GfxStateTest_580, DefaultRender_580) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test save and restore
TEST_F(GfxStateTest_580, SaveRestore_580) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);

    GfxState *restored = state->restore();
    // After restore we should be back to the state before the save
    // The returned pointer is the saved state
    EXPECT_NE(restored, nullptr);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_580, HasSavesInitiallyFalse_580) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_580, HasSavesAfterSave_580) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test getStrokeRGB with default stroke color space
TEST_F(GfxStateTest_580, GetStrokeRGBDefault_580) {
    GfxRGB rgb;
    state->getStrokeRGB(&rgb);
    // Default stroke color space should be DeviceGray with default color
    // We just verify it doesn't crash and returns some value
    // Default gray color 0 should map to RGB (0,0,0)
    SUCCEED();
}

// Test getFillRGB with default fill color space
TEST_F(GfxStateTest_580, GetFillRGBDefault_580) {
    GfxRGB rgb;
    state->getFillRGB(&rgb);
    SUCCEED();
}

// Test getCTM
TEST_F(GfxStateTest_580, GetCTM_580) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_580, SetCTM_580) {
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
TEST_F(GfxStateTest_580, ConcatCTM_580) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform
TEST_F(GfxStateTest_580, Transform_580) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

// Test transformDelta
TEST_F(GfxStateTest_580, TransformDelta_580) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test path operations - moveTo and isCurPt
TEST_F(GfxStateTest_580, MoveToSetsCurPt_580) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test path operations - lineTo
TEST_F(GfxStateTest_580, LineTo_580) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

// Test path operations - curveTo
TEST_F(GfxStateTest_580, CurveTo_580) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(state->isPath());
}

// Test path operations - closePath
TEST_F(GfxStateTest_580, ClosePath_580) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_580, ClearPath_580) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

// Test initially no path
TEST_F(GfxStateTest_580, InitiallyNoPath_580) {
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test setLineDash
TEST_F(GfxStateTest_580, SetLineDash_580) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test setLineJoin
TEST_F(GfxStateTest_580, SetLineJoin_580) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test setLineCap
TEST_F(GfxStateTest_580, SetLineCap_580) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test setRenderingIntent
TEST_F(GfxStateTest_580, SetRenderingIntent_580) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with different values
TEST_F(GfxStateTest_580, SetRenderingIntentRelativeColorimetric_580) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test setTextMat
TEST_F(GfxStateTest_580, SetTextMat_580) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 0.0);
    EXPECT_DOUBLE_EQ(mat[5], 0.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_580, TextMoveTo_580) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test getClipBBox
TEST_F(GfxStateTest_580, GetClipBBox_580) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have some valid clip bounds
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_580, GetUserClipBBox_580) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_580, ClipToRect_580) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the bounds should be restricted
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test copy
TEST_F(GfxStateTest_580, Copy_580) {
    state->setLineWidth(3.5);
    state->setFillOpacity(0.7);
    GfxState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    delete copied;
}

// Test different page box and rotation
TEST_F(GfxStateTest_580, RotatedPageBox_580) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 792;
    pageBox.y2 = 612;
    auto rotatedState = std::make_unique<GfxState>(150.0, 150.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
    EXPECT_DOUBLE_EQ(rotatedState->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(rotatedState->getVDPI(), 150.0);
}

// Test getPath returns non-null
TEST_F(GfxStateTest_580, GetPath_580) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test getStrokeColorSpace returns non-null by default
TEST_F(GfxStateTest_580, DefaultStrokeColorSpace_580) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test getFillColorSpace returns non-null by default
TEST_F(GfxStateTest_580, DefaultFillColorSpace_580) {
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test default blend mode
TEST_F(GfxStateTest_580, DefaultBlendMode_580) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test setBlendMode
TEST_F(GfxStateTest_580, SetBlendMode_580) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test getFillColor and setFillColor
TEST_F(GfxStateTest_580, SetGetFillColor_580) {
    GfxColor color;
    color.c[0] = 32768; // midpoint
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test getStrokeColor and setStrokeColor
TEST_F(GfxStateTest_580, SetGetStrokeColor_580) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 65535);
}

// Test getFillPattern initially null
TEST_F(GfxStateTest_580, DefaultFillPatternNull_580) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// Test getStrokePattern initially null
TEST_F(GfxStateTest_580, DefaultStrokePatternNull_580) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test transformWidth
TEST_F(GfxStateTest_580, TransformWidth_580) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test setLineWidth to zero (boundary)
TEST_F(GfxStateTest_580, SetLineWidthZero_580) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test setFillOpacity boundary values
TEST_F(GfxStateTest_580, SetFillOpacityZero_580) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_580, SetFillOpacityOne_580) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setStrokeOpacity boundary values
TEST_F(GfxStateTest_580, SetStrokeOpacityZero_580) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_580, MultipleSaveRestore_580) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    EXPECT_TRUE(state->hasSaves());

    state->restore();
    // After first restore
    EXPECT_TRUE(state->hasSaves());

    state->restore();
    EXPECT_FALSE(state->hasSaves());
}

// Test curX and curY after moveTo
TEST_F(GfxStateTest_580, CurXYAfterMoveTo_580) {
    state->moveTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 42.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 84.0);
}

// Test empty lineDash by default
TEST_F(GfxStateTest_580, DefaultLineDashEmpty_580) {
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test setRenderingIntent with long string (boundary - buffer is 32 chars)
TEST_F(GfxStateTest_580, SetRenderingIntentLongString_580) {
    // The internal buffer is char[32], so test with a string that fits
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_580, GetTransformedLineWidth_580) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}
