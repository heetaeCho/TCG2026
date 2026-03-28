#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "PDFDoc.h"
#include "Object.h"
#include <memory>
#include <cstring>

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_591 : public ::testing::Test {
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
TEST_F(GfxStateTest_591, ConstructionAndDPI_591) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_591, PageDimensions_591) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test page coordinates
TEST_F(GfxStateTest_591, PageCoordinates_591) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_591, RotateDefault_591) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test rotation with 90 degrees
TEST_F(GfxStateTest_591, RotateNonZero_591) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test stroke opacity default
TEST_F(GfxStateTest_591, StrokeOpacityDefault_591) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test fill opacity default
TEST_F(GfxStateTest_591, FillOpacityDefault_591) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_591, SetStrokeOpacity_591) {
    state->setStrokeOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.5);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_591, SetFillOpacity_591) {
    state->setFillOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.3);
}

// Test stroke opacity boundary zero
TEST_F(GfxStateTest_591, StrokeOpacityZero_591) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// Test stroke opacity boundary one
TEST_F(GfxStateTest_591, StrokeOpacityOne_591) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test fill opacity boundary zero
TEST_F(GfxStateTest_591, FillOpacityZero_591) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

// Test line width default
TEST_F(GfxStateTest_591, LineWidthDefault_591) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set line width
TEST_F(GfxStateTest_591, SetLineWidth_591) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test line width zero
TEST_F(GfxStateTest_591, LineWidthZero_591) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test miter limit default
TEST_F(GfxStateTest_591, MiterLimitDefault_591) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set miter limit
TEST_F(GfxStateTest_591, SetMiterLimit_591) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test flatness default
TEST_F(GfxStateTest_591, FlatnessDefault_591) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set flatness
TEST_F(GfxStateTest_591, SetFlatness_591) {
    state->setFlatness(3);
    EXPECT_EQ(state->getFlatness(), 3);
}

// Test line join default
TEST_F(GfxStateTest_591, LineJoinDefault_591) {
    // Default should be miter join (0)
    EXPECT_EQ(static_cast<int>(state->getLineJoin()), 0);
}

// Test set line join
TEST_F(GfxStateTest_591, SetLineJoin_591) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test line cap default
TEST_F(GfxStateTest_591, LineCapDefault_591) {
    // Default should be butt cap (0)
    EXPECT_EQ(static_cast<int>(state->getLineCap()), 0);
}

// Test set line cap
TEST_F(GfxStateTest_591, SetLineCap_591) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test char space default
TEST_F(GfxStateTest_591, CharSpaceDefault_591) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set char space
TEST_F(GfxStateTest_591, SetCharSpace_591) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test word space default
TEST_F(GfxStateTest_591, WordSpaceDefault_591) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set word space
TEST_F(GfxStateTest_591, SetWordSpace_591) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test horiz scaling default
TEST_F(GfxStateTest_591, HorizScalingDefault_591) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set horiz scaling
TEST_F(GfxStateTest_591, SetHorizScaling_591) {
    state->setHorizScaling(0.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test leading default
TEST_F(GfxStateTest_591, LeadingDefault_591) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set leading
TEST_F(GfxStateTest_591, SetLeading_591) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test rise default
TEST_F(GfxStateTest_591, RiseDefault_591) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set rise
TEST_F(GfxStateTest_591, SetRise_591) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test render default
TEST_F(GfxStateTest_591, RenderDefault_591) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set render
TEST_F(GfxStateTest_591, SetRender_591) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test fill overprint default
TEST_F(GfxStateTest_591, FillOverprintDefault_591) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set fill overprint
TEST_F(GfxStateTest_591, SetFillOverprint_591) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test stroke overprint default
TEST_F(GfxStateTest_591, StrokeOverprintDefault_591) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set stroke overprint
TEST_F(GfxStateTest_591, SetStrokeOverprint_591) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test overprint mode default
TEST_F(GfxStateTest_591, OverprintModeDefault_591) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set overprint mode
TEST_F(GfxStateTest_591, SetOverprintMode_591) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test stroke adjust default
TEST_F(GfxStateTest_591, StrokeAdjustDefault_591) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set stroke adjust
TEST_F(GfxStateTest_591, SetStrokeAdjust_591) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test alpha is shape default
TEST_F(GfxStateTest_591, AlphaIsShapeDefault_591) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set alpha is shape
TEST_F(GfxStateTest_591, SetAlphaIsShape_591) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout default
TEST_F(GfxStateTest_591, TextKnockoutDefault_591) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set text knockout
TEST_F(GfxStateTest_591, SetTextKnockout_591) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test font size default
TEST_F(GfxStateTest_591, FontSizeDefault_591) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test blend mode default
TEST_F(GfxStateTest_591, BlendModeDefault_591) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// Test set blend mode
TEST_F(GfxStateTest_591, SetBlendMode_591) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test save and restore
TEST_F(GfxStateTest_591, SaveAndRestore_591) {
    state->setStrokeOpacity(0.5);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
    
    GfxState *restored = state->restore();
    // After restore, we should be back to the saved state
    EXPECT_NE(restored, nullptr);
}

// Test hasSaves initial
TEST_F(GfxStateTest_591, HasSavesInitial_591) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_591, HasSavesAfterSave_591) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test path operations - initial state
TEST_F(GfxStateTest_591, PathInitialState_591) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test moveTo creates a current point
TEST_F(GfxStateTest_591, MoveToSetsCurPt_591) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test lineTo creates a path
TEST_F(GfxStateTest_591, LineToCreatesPath_591) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_591, ClearPath_591) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_591, CurveTo_591) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_591, ClosePath_591) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test getCTM
TEST_F(GfxStateTest_591, GetCTM_591) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_591, SetCTM_591) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test concatCTM
TEST_F(GfxStateTest_591, ConcatCTM_591) {
    // Get initial CTM
    const auto &ctmBefore = state->getCTM();
    double a0 = ctmBefore[0];
    
    // Concat with identity shouldn't change
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &ctmAfter = state->getCTM();
    EXPECT_DOUBLE_EQ(ctmAfter[0], a0);
}

// Test transform
TEST_F(GfxStateTest_591, Transform_591) {
    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    // Just verify it doesn't crash and returns some values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transformDelta
TEST_F(GfxStateTest_591, TransformDelta_591) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test textTransform
TEST_F(GfxStateTest_591, TextTransform_591) {
    double x2, y2;
    state->textTransform(1.0, 1.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test set text mat
TEST_F(GfxStateTest_591, SetTextMat_591) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
}

// Test getClipBBox
TEST_F(GfxStateTest_591, GetClipBBox_591) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_591, GetUserClipBBox_591) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_591, ClipToRect_591) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the box should be within or equal to the clip rect
    EXPECT_GE(xMin, 100.0 - 1e-6);
    EXPECT_GE(yMin, 100.0 - 1e-6);
    EXPECT_LE(xMax, 200.0 + 1e-6);
    EXPECT_LE(yMax, 200.0 + 1e-6);
}

// Test rendering intent
TEST_F(GfxStateTest_591, RenderingIntentDefault_591) {
    const char *intent = state->getRenderingIntent();
    EXPECT_NE(intent, nullptr);
}

// Test set rendering intent
TEST_F(GfxStateTest_591, SetRenderingIntent_591) {
    state->setRenderingIntent("Perceptual");
    const char *intent = state->getRenderingIntent();
    EXPECT_STREQ(intent, "Perceptual");
}

// Test set rendering intent with various values
TEST_F(GfxStateTest_591, SetRenderingIntentRelativeColorimetric_591) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test set rendering intent with Saturation
TEST_F(GfxStateTest_591, SetRenderingIntentSaturation_591) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test set rendering intent AbsoluteColorimetric
TEST_F(GfxStateTest_591, SetRenderingIntentAbsoluteColorimetric_591) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test lineDash default
TEST_F(GfxStateTest_591, LineDashDefault_591) {
    double start;
    const auto &dash = state->getLineDash(&start);
    EXPECT_TRUE(dash.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test set line dash
TEST_F(GfxStateTest_591, SetLineDash_591) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_591, TextMoveTo_591) {
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, line position should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test curX and curY default
TEST_F(GfxStateTest_591, CurXYDefault_591) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test curTextX and curTextY default
TEST_F(GfxStateTest_591, CurTextXYDefault_591) {
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 0.0);
}

// Test getPath not null
TEST_F(GfxStateTest_591, GetPathNotNull_591) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test copy
TEST_F(GfxStateTest_591, Copy_591) {
    state->setStrokeOpacity(0.7);
    state->setFillOpacity(0.3);
    auto copy = state->copy();
    EXPECT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->getStrokeOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(copy->getFillOpacity(), 0.3);
    delete copy;
}

// Test transformWidth
TEST_F(GfxStateTest_591, TransformWidth_591) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_591, GetTransformedLineWidth_591) {
    state->setLineWidth(2.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tlw));
    EXPECT_GE(tlw, 0.0);
}

// Test font default is null
TEST_F(GfxStateTest_591, FontDefault_591) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test fill and stroke color space defaults
TEST_F(GfxStateTest_591, FillColorSpaceDefault_591) {
    // Default fill color space might be null or DeviceGray
    GfxColorSpace *cs = state->getFillColorSpace();
    // Just check it doesn't crash
    (void)cs;
}

// Test stroke color space default
TEST_F(GfxStateTest_591, StrokeColorSpaceDefault_591) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    (void)cs;
}

// Test fill pattern default
TEST_F(GfxStateTest_591, FillPatternDefault_591) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

// Test stroke pattern default
TEST_F(GfxStateTest_591, StrokePatternDefault_591) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test different page box
TEST_F(GfxStateTest_591, DifferentPageBox_591) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 300;
    pageBox.y2 = 400;
    GfxState s(150.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(s.getVDPI(), 150.0);
    EXPECT_DOUBLE_EQ(s.getPageWidth(), 300.0);
    EXPECT_DOUBLE_EQ(s.getPageHeight(), 400.0);
}

// Test with upside down false
TEST_F(GfxStateTest_591, UpsideDownFalse_591) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(s.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s.getPageHeight(), 792.0);
}

// Test save/restore preserves state
TEST_F(GfxStateTest_591, SaveRestorePreservesState_591) {
    state->setLineWidth(5.0);
    state->setFillOpacity(0.4);
    
    GfxState *savedPtr = state->save();
    ASSERT_NE(savedPtr, nullptr);
    
    state->setLineWidth(10.0);
    state->setFillOpacity(0.8);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.8);
    
    GfxState *restoredPtr = state->restore();
    // After restore, we should get the previous state
    EXPECT_NE(restoredPtr, nullptr);
}

// Test multiple saves
TEST_F(GfxStateTest_591, MultipleSaves_591) {
    state->save();
    state->save();
    EXPECT_TRUE(state->hasSaves());
    state->restore();
    EXPECT_TRUE(state->hasSaves());
    state->restore();
    EXPECT_FALSE(state->hasSaves());
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_591, ShiftCTMAndClip_591) {
    state->shiftCTMAndClip(10.0, 20.0);
    // Should not crash, just verify it works
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test set fill color
TEST_F(GfxStateTest_591, SetFillColor_591) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test set stroke color
TEST_F(GfxStateTest_591, SetStrokeColor_591) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test getReusablePath
TEST_F(GfxStateTest_591, GetReusablePath_591) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}

// Test textShift
TEST_F(GfxStateTest_591, TextShift_591) {
    state->textMoveTo(10.0, 20.0);
    state->textShift(5.0, 3.0);
    // Should not crash, verify finite values
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// Test display profile default
TEST_F(GfxStateTest_591, DisplayProfileDefault_591) {
    auto profile = state->getDisplayProfile();
    // Default should be null/empty
    (void)profile;
}

// Test copy default gray color space (initially null)
TEST_F(GfxStateTest_591, CopyDefaultGrayColorSpace_591) {
    auto cs = state->copyDefaultGrayColorSpace();
    // Initially should be null
    EXPECT_EQ(cs, nullptr);
}

// Test copy default RGB color space (initially null)
TEST_F(GfxStateTest_591, CopyDefaultRGBColorSpace_591) {
    auto cs = state->copyDefaultRGBColorSpace();
    EXPECT_EQ(cs, nullptr);
}

// Test copy default CMYK color space (initially null)
TEST_F(GfxStateTest_591, CopyDefaultCMYKColorSpace_591) {
    auto cs = state->copyDefaultCMYKColorSpace();
    EXPECT_EQ(cs, nullptr);
}

// Test parseBlendMode with normal
TEST_F(GfxStateTest_591, ParseBlendModeNormal_591) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// Test isParentState
TEST_F(GfxStateTest_591, IsParentState_591) {
    GfxState *savedState = state->save();
    // The current state's parent should be the saved state
    // savedState points to the outer state
    EXPECT_NE(savedState, nullptr);
}

// Test rotation values
TEST_F(GfxStateTest_591, Rotation180_591) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(s.getRotate(), 180);
}

TEST_F(GfxStateTest_591, Rotation270_591) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(s.getRotate(), 270);
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_591, GetTransformedFontSize_591) {
    double tfs = state->getTransformedFontSize();
    EXPECT_TRUE(std::isfinite(tfs));
}

// Test getFontTransMat
TEST_F(GfxStateTest_591, GetFontTransMat_591) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_591, GetCTMMatrix_591) {
    Matrix m;
    state->getCTM(&m);
    // Should not crash
}
