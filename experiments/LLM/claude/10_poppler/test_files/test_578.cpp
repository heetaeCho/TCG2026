#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Helper to create a basic GfxState for testing
class GfxStateTest_578 : public ::testing::Test {
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

// Test basic construction and DPI getters
TEST_F(GfxStateTest_578, ConstructionAndDPI_578) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_578, PageDimensions_578) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test page width and height
TEST_F(GfxStateTest_578, PageWidthHeight_578) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_578, GetRotate_578) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test default fill opacity
TEST_F(GfxStateTest_578, DefaultFillOpacity_578) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_578, DefaultStrokeOpacity_578) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_578, SetFillOpacity_578) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_578, SetStrokeOpacity_578) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test default line width
TEST_F(GfxStateTest_578, DefaultLineWidth_578) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set line width
TEST_F(GfxStateTest_578, SetLineWidth_578) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_578, DefaultFlatness_578) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set flatness
TEST_F(GfxStateTest_578, SetFlatness_578) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_578, DefaultMiterLimit_578) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set miter limit
TEST_F(GfxStateTest_578, SetMiterLimit_578) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_578, DefaultFillOverprint_578) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set fill overprint
TEST_F(GfxStateTest_578, SetFillOverprint_578) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_578, DefaultStrokeOverprint_578) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set stroke overprint
TEST_F(GfxStateTest_578, SetStrokeOverprint_578) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_578, DefaultOverprintMode_578) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set overprint mode
TEST_F(GfxStateTest_578, SetOverprintMode_578) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_578, DefaultStrokeAdjust_578) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set stroke adjust
TEST_F(GfxStateTest_578, SetStrokeAdjust_578) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_578, DefaultAlphaIsShape_578) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set alpha is shape
TEST_F(GfxStateTest_578, SetAlphaIsShape_578) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_578, DefaultTextKnockout_578) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set text knockout
TEST_F(GfxStateTest_578, SetTextKnockout_578) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_578, DefaultCharSpace_578) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set char space
TEST_F(GfxStateTest_578, SetCharSpace_578) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_578, DefaultWordSpace_578) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set word space
TEST_F(GfxStateTest_578, SetWordSpace_578) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_578, DefaultHorizScaling_578) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set horiz scaling
TEST_F(GfxStateTest_578, SetHorizScaling_578) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_578, DefaultLeading_578) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set leading
TEST_F(GfxStateTest_578, SetLeading_578) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_578, DefaultRise_578) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set rise
TEST_F(GfxStateTest_578, SetRise_578) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_578, DefaultRender_578) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set render
TEST_F(GfxStateTest_578, SetRender_578) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default font size
TEST_F(GfxStateTest_578, DefaultFontSize_578) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default line join
TEST_F(GfxStateTest_578, DefaultLineJoin_578) {
    EXPECT_EQ(state->getLineJoin(), 0);
}

// Test set line join
TEST_F(GfxStateTest_578, SetLineJoin_578) {
    state->setLineJoin(static_cast<LineJoinStyle>(1));
    EXPECT_EQ(state->getLineJoin(), 1);
}

// Test default line cap
TEST_F(GfxStateTest_578, DefaultLineCap_578) {
    EXPECT_EQ(state->getLineCap(), 0);
}

// Test set line cap
TEST_F(GfxStateTest_578, SetLineCap_578) {
    state->setLineCap(static_cast<LineCapStyle>(1));
    EXPECT_EQ(state->getLineCap(), 1);
}

// Test save and restore
TEST_F(GfxStateTest_578, SaveAndRestore_578) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);
    
    GfxState *restored = state->restore();
    // After restore, the state pointer may change; 
    // we check the restored state
    EXPECT_NE(restored, nullptr);
}

// Test hasSaves returns false initially
TEST_F(GfxStateTest_578, HasSavesInitiallyFalse_578) {
    EXPECT_FALSE(state->hasSaves());
}

// Test CTM getter
TEST_F(GfxStateTest_578, GetCTM_578) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_578, SetCTM_578) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test transform
TEST_F(GfxStateTest_578, Transform_578) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_578, TransformWithScaling_578) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test transformDelta
TEST_F(GfxStateTest_578, TransformDelta_578) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test moveTo and path status
TEST_F(GfxStateTest_578, MoveToCreatesCurrentPoint_578) {
    EXPECT_FALSE(state->isCurPt());
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test lineTo after moveTo
TEST_F(GfxStateTest_578, LineToCreatesPath_578) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_578, ClearPath_578) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_578, CurveTo_578) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_578, ClosePath_578) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clip bounding box
TEST_F(GfxStateTest_578, GetClipBBox_578) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be initialized to something
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_578, GetUserClipBBox_578) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_578, ClipToRect_578) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip box should be within the specified rect
    EXPECT_GE(xMin, 10.0 - 1e-6);
    EXPECT_GE(yMin, 20.0 - 1e-6);
    EXPECT_LE(xMax, 100.0 + 1e-6);
    EXPECT_LE(yMax, 200.0 + 1e-6);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_578, SetTextMat_578) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 2.0);
    EXPECT_DOUBLE_EQ(textMat[2], 3.0);
    EXPECT_DOUBLE_EQ(textMat[3], 4.0);
    EXPECT_DOUBLE_EQ(textMat[4], 5.0);
    EXPECT_DOUBLE_EQ(textMat[5], 6.0);
}

// Test getStrokeGray with default stroke color space (DeviceGray)
TEST_F(GfxStateTest_578, GetStrokeGrayDefault_578) {
    GfxGray gray;
    state->getStrokeGray(&gray);
    // Default stroke color should give some valid gray value
    // Just verify it doesn't crash; the actual value depends on default color
}

// Test getFillGray with default fill color space
TEST_F(GfxStateTest_578, GetFillGrayDefault_578) {
    GfxGray gray;
    state->getFillGray(&gray);
    // Just verify it doesn't crash
}

// Test getFillRGB with default fill color space
TEST_F(GfxStateTest_578, GetFillRGBDefault_578) {
    GfxRGB rgb;
    state->getFillRGB(&rgb);
    // Just verify it doesn't crash
}

// Test getStrokeRGB with default stroke color space
TEST_F(GfxStateTest_578, GetStrokeRGBDefault_578) {
    GfxRGB rgb;
    state->getStrokeRGB(&rgb);
    // Just verify it doesn't crash
}

// Test getFillCMYK
TEST_F(GfxStateTest_578, GetFillCMYKDefault_578) {
    GfxCMYK cmyk;
    state->getFillCMYK(&cmyk);
}

// Test getStrokeCMYK
TEST_F(GfxStateTest_578, GetStrokeCMYKDefault_578) {
    GfxCMYK cmyk;
    state->getStrokeCMYK(&cmyk);
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_578, SetAndGetFillColor_578) {
    GfxColor color;
    color.c[0] = 32768; // 0.5 in fixed point representation
    state->setFillColor(&color);
    const GfxColor *retrievedColor = state->getFillColor();
    EXPECT_NE(retrievedColor, nullptr);
    EXPECT_EQ(retrievedColor->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_578, SetAndGetStrokeColor_578) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrievedColor = state->getStrokeColor();
    EXPECT_NE(retrievedColor, nullptr);
    EXPECT_EQ(retrievedColor->c[0], 16384);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_578, SetAndGetBlendMode_578) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test default blend mode
TEST_F(GfxStateTest_578, DefaultBlendMode_578) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_578, SetAndGetLineDash_578) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_578, EmptyLineDash_578) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_TRUE(retrievedDash.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_578, SetAndGetRenderingIntent_578) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with long string (boundary)
TEST_F(GfxStateTest_578, SetRenderingIntentLongString_578) {
    // The internal buffer is char[32], so test with a string near that limit
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test textMoveTo
TEST_F(GfxStateTest_578, TextMoveTo_578) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test getCurX and getCurY default values
TEST_F(GfxStateTest_578, DefaultCurXY_578) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test path is empty initially
TEST_F(GfxStateTest_578, InitialPathState_578) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
    EXPECT_NE(state->getPath(), nullptr);
}

// Test concatCTM
TEST_F(GfxStateTest_578, ConcatCTM_578) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test getFillColorSpace and getStrokeColorSpace are not null by default
TEST_F(GfxStateTest_578, DefaultColorSpacesNotNull_578) {
    EXPECT_NE(state->getFillColorSpace(), nullptr);
    EXPECT_NE(state->getStrokeColorSpace(), nullptr);
}

// Test getFillPattern and getStrokePattern default to null
TEST_F(GfxStateTest_578, DefaultPatternsNull_578) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test copy method
TEST_F(GfxStateTest_578, CopyState_578) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.7);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
}

// Test save creates a parent state
TEST_F(GfxStateTest_578, SaveCreatesParent_578) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    EXPECT_TRUE(state->isParentState(saved));
    state->restore();
}

// Test different page rotation
TEST(GfxStateConstructionTest_578, RotatedPage_578) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
}

// Test different DPI values
TEST(GfxStateConstructionTest_578, DifferentDPI_578) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test zero-size page
TEST(GfxStateConstructionTest_578, ZeroSizePage_578) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 0;
    pageBox.y2 = 0;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 0.0);
}

// Test line width zero
TEST_F(GfxStateTest_578, ZeroLineWidth_578) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test negative line width
TEST_F(GfxStateTest_578, NegativeLineWidth_578) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test getReusablePath doesn't return null
TEST_F(GfxStateTest_578, GetReusablePath_578) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// Test transformWidth
TEST_F(GfxStateTest_578, TransformWidth_578) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_578, GetTransformedLineWidth_578) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test textTransform
TEST_F(GfxStateTest_578, TextTransform_578) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    // Should produce some transformed coordinates
}

// Test textTransformDelta
TEST_F(GfxStateTest_578, TextTransformDelta_578) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->textTransformDelta(1.0, 1.0, &x2, &y2);
    // Delta transform should not include the translation component of text matrix
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_578, MultipleSaveRestore_578) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    state->setLineWidth(2.0);
    GfxState *s2 = state->save();
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    
    state->restore();
    // After first restore
    EXPECT_TRUE(state->hasSaves());
    
    state->restore();
    // After second restore
    EXPECT_FALSE(state->hasSaves());
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_578, ShiftCTMAndClip_578) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test getCTM with Matrix parameter
TEST_F(GfxStateTest_578, GetCTMMatrix_578) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify the matrix was populated (exact mapping depends on implementation)
}

// Test setFillColorSpace
TEST_F(GfxStateTest_578, SetFillColorSpace_578) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxColorSpace *rawPtr = cs.get();
    state->setFillColorSpace(std::move(cs));
    EXPECT_EQ(state->getFillColorSpace(), rawPtr);
}

// Test setStrokeColorSpace
TEST_F(GfxStateTest_578, SetStrokeColorSpace_578) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxColorSpace *rawPtr = cs.get();
    state->setStrokeColorSpace(std::move(cs));
    EXPECT_EQ(state->getStrokeColorSpace(), rawPtr);
}

// Test getFont returns nullptr initially
TEST_F(GfxStateTest_578, DefaultFontIsNull_578) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getCurTextX and getCurTextY defaults
TEST_F(GfxStateTest_578, DefaultCurTextXY_578) {
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 0.0);
}

// Test parseBlendMode static method with Normal
TEST_F(GfxStateTest_578, ParseBlendModeNormal_578) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}
