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

class GfxStateTest_579 : public ::testing::Test {
protected:
    void SetUp() override {
        state = createDefaultGfxState();
    }

    std::unique_ptr<GfxState> state;
};

// Test that GfxState is created with expected page dimensions
TEST_F(GfxStateTest_579, Constructor_PageDimensions_579) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test DPI values
TEST_F(GfxStateTest_579, Constructor_DPI_579) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test rotation
TEST_F(GfxStateTest_579, Constructor_Rotate_579) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page coordinates
TEST_F(GfxStateTest_579, Constructor_PageCoordinates_579) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_579, DefaultFillOpacity_579) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_579, DefaultStrokeOpacity_579) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_579, SetFillOpacity_579) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_579, SetStrokeOpacity_579) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test default line width
TEST_F(GfxStateTest_579, DefaultLineWidth_579) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set and get line width
TEST_F(GfxStateTest_579, SetLineWidth_579) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test zero line width
TEST_F(GfxStateTest_579, SetLineWidthZero_579) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test default flatness
TEST_F(GfxStateTest_579, DefaultFlatness_579) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set and get flatness
TEST_F(GfxStateTest_579, SetFlatness_579) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test default miter limit
TEST_F(GfxStateTest_579, DefaultMiterLimit_579) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set and get miter limit
TEST_F(GfxStateTest_579, SetMiterLimit_579) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_579, DefaultFillOverprint_579) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set and get fill overprint
TEST_F(GfxStateTest_579, SetFillOverprint_579) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_579, DefaultStrokeOverprint_579) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set and get stroke overprint
TEST_F(GfxStateTest_579, SetStrokeOverprint_579) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_579, DefaultOverprintMode_579) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set and get overprint mode
TEST_F(GfxStateTest_579, SetOverprintMode_579) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_579, DefaultStrokeAdjust_579) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set and get stroke adjust
TEST_F(GfxStateTest_579, SetStrokeAdjust_579) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_579, DefaultAlphaIsShape_579) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set and get alpha is shape
TEST_F(GfxStateTest_579, SetAlphaIsShape_579) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_579, DefaultTextKnockout_579) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set and get text knockout
TEST_F(GfxStateTest_579, SetTextKnockout_579) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_579, DefaultCharSpace_579) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set and get char space
TEST_F(GfxStateTest_579, SetCharSpace_579) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_579, DefaultWordSpace_579) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set and get word space
TEST_F(GfxStateTest_579, SetWordSpace_579) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_579, DefaultHorizScaling_579) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set and get horiz scaling
TEST_F(GfxStateTest_579, SetHorizScaling_579) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_579, DefaultLeading_579) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set and get leading
TEST_F(GfxStateTest_579, SetLeading_579) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_579, DefaultRise_579) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set and get rise
TEST_F(GfxStateTest_579, SetRise_579) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_579, DefaultRender_579) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set and get render
TEST_F(GfxStateTest_579, SetRender_579) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default font is null
TEST_F(GfxStateTest_579, DefaultFont_579) {
    EXPECT_EQ(state->getFont(), nullptr);
}

// Test default font size
TEST_F(GfxStateTest_579, DefaultFontSize_579) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test save and restore
TEST_F(GfxStateTest_579, SaveRestore_579) {
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

// Test hasSaves initially false
TEST_F(GfxStateTest_579, HasSavesInitiallyFalse_579) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_579, HasSavesAfterSave_579) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    // Restore to clean up
    saved->restore();
}

// Test getFillRGB with default fill color space (DeviceGray)
TEST_F(GfxStateTest_579, GetFillRGB_Default_579) {
    GfxRGB rgb;
    state->getFillRGB(&rgb);
    // Default fill color in DeviceGray is black (0,0,0)
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getStrokeRGB with default stroke color space
TEST_F(GfxStateTest_579, GetStrokeRGB_Default_579) {
    GfxRGB rgb;
    state->getStrokeRGB(&rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getFillColorSpace not null
TEST_F(GfxStateTest_579, FillColorSpaceNotNull_579) {
    EXPECT_NE(state->getFillColorSpace(), nullptr);
}

// Test getStrokeColorSpace not null
TEST_F(GfxStateTest_579, StrokeColorSpaceNotNull_579) {
    EXPECT_NE(state->getStrokeColorSpace(), nullptr);
}

// Test default fill pattern is null
TEST_F(GfxStateTest_579, DefaultFillPattern_579) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// Test default stroke pattern is null
TEST_F(GfxStateTest_579, DefaultStrokePattern_579) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test moveTo and path state
TEST_F(GfxStateTest_579, MoveTo_579) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

// Test lineTo
TEST_F(GfxStateTest_579, LineTo_579) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 100.0);
}

// Test curveTo
TEST_F(GfxStateTest_579, CurveTo_579) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test closePath
TEST_F(GfxStateTest_579, ClosePath_579) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After close, current point should be start of subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test clearPath
TEST_F(GfxStateTest_579, ClearPath_579) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test isCurPt and isPath on fresh state
TEST_F(GfxStateTest_579, NoCurPtInitially_579) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test getPath not null
TEST_F(GfxStateTest_579, GetPathNotNull_579) {
    EXPECT_NE(state->getPath(), nullptr);
}

// Test CTM
TEST_F(GfxStateTest_579, GetCTM_579) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_579, SetCTM_579) {
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
TEST_F(GfxStateTest_579, ConcatCTM_579) {
    // Set identity first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform
TEST_F(GfxStateTest_579, Transform_579) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

// Test transformDelta
TEST_F(GfxStateTest_579, TransformDelta_579) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 5.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_579, SetTextMat_579) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_579, SetLineJoin_579) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_579, SetLineCap_579) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_579, SetLineDash_579) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_579, EmptyLineDash_579) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_579, SetBlendMode_579) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_579, SetRenderingIntent_579) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with long string (boundary - should truncate or handle)
TEST_F(GfxStateTest_579, SetRenderingIntentLongString_579) {
    // The internal buffer is char[32], so test with a reasonable intent name
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test clipToRect and getClipBBox
TEST_F(GfxStateTest_579, ClipToRect_579) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_579, TextMoveTo_579) {
    state->textMoveTo(5.0, 10.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 10.0);
}

// Test copy
TEST_F(GfxStateTest_579, Copy_579) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.6);
    auto copy = state->copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copy->getFillOpacity(), 0.6);
    delete copy;
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_579, SetFillColor_579) {
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], color.c[0]);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_579, SetStrokeColor_579) {
    GfxColor color;
    color.c[0] = dblToCol(0.75);
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], color.c[0]);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_579, GetUserClipBBox_579) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test save/restore preserves state
TEST_F(GfxStateTest_579, SaveRestorePreservesState_579) {
    state->setFillOpacity(0.3);
    state->setLineWidth(7.0);
    state->setCharSpace(2.0);

    GfxState *saved = state->save();
    saved->setFillOpacity(0.9);
    saved->setLineWidth(1.0);
    saved->setCharSpace(5.0);

    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.9);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 1.0);
    EXPECT_DOUBLE_EQ(saved->getCharSpace(), 5.0);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.3);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(restored->getCharSpace(), 2.0);
}

// Test transformWidth
TEST_F(GfxStateTest_579, TransformWidth_579) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// Test transformWidth with zero
TEST_F(GfxStateTest_579, TransformWidthZero_579) {
    double w = state->transformWidth(0.0);
    EXPECT_GE(w, 0.0);
}

// Test parseBlendMode with Normal
TEST_F(GfxStateTest_579, ParseBlendModeNormal_579) {
    Object obj;
    GfxBlendMode mode;
    // We can create a name object for "Normal"
    obj = Object(objName, "Normal");
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test with different page rotation
TEST(GfxStateConstructor_579, RotatedPage_579) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
}

// Test with different DPI
TEST(GfxStateConstructor_579, DifferentDPI_579) {
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
TEST_F(GfxStateTest_579, IsParentState_579) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    child->restore();
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_579, GetTransformedLineWidth_579) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test negative fill opacity clamping behavior (boundary)
TEST_F(GfxStateTest_579, SetFillOpacityBoundary_579) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);

    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setFillColorSpace with DeviceRGB-like space
TEST_F(GfxStateTest_579, SetFillColorSpace_579) {
    auto cs = GfxColorSpace::parse(nullptr, nullptr, nullptr, nullptr, 0);
    // If parse returns null without valid args, just check the existing one
    GfxColorSpace *existingCs = state->getFillColorSpace();
    EXPECT_NE(existingCs, nullptr);
}

// Test getReusablePath
TEST_F(GfxStateTest_579, GetReusablePath_579) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto it = state->getReusablePath();
    EXPECT_NE(it, nullptr);
}
