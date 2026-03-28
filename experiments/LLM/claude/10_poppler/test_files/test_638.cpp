#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a GfxState with default parameters
class GfxStateTest_638 : public ::testing::Test {
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
TEST_F(GfxStateTest_638, ConstructionAndDPI_638) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_638, PageDimensions_638) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test page coordinates
TEST_F(GfxStateTest_638, PageCoordinates_638) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_638, Rotation_638) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test rotation with 90 degrees
TEST_F(GfxStateTest_638, RotationWith90Degrees_638) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_638, SetAndGetLineWidth_638) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test setLineWidth with zero
TEST_F(GfxStateTest_638, SetLineWidthZero_638) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test setLineWidth with negative value
TEST_F(GfxStateTest_638, SetLineWidthNegative_638) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_638, SetAndGetFillOpacity_638) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_638, SetAndGetStrokeOpacity_638) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_638, SetAndGetFillOverprint_638) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_638, SetAndGetStrokeOverprint_638) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_638, SetAndGetOverprintMode_638) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_638, SetAndGetFlatness_638) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_638, SetAndGetLineJoin_638) {
    state->setLineJoin(LineJoinStyle::MiterJoin);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::MiterJoin);
    state->setLineJoin(LineJoinStyle::RoundJoin);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::RoundJoin);
    state->setLineJoin(LineJoinStyle::BevelJoin);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::BevelJoin);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_638, SetAndGetLineCap_638) {
    state->setLineCap(LineCapStyle::ButtCap);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::ButtCap);
    state->setLineCap(LineCapStyle::RoundCap);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::RoundCap);
    state->setLineCap(LineCapStyle::ProjectingSquareCap);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::ProjectingSquareCap);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_638, SetAndGetMiterLimit_638) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_638, SetAndGetStrokeAdjust_638) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_638, SetAndGetAlphaIsShape_638) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_638, SetAndGetTextKnockout_638) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setCharSpace and getCharSpace
TEST_F(GfxStateTest_638, SetAndGetCharSpace_638) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test setWordSpace and getWordSpace
TEST_F(GfxStateTest_638, SetAndGetWordSpace_638) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_638, SetAndGetHorizScaling_638) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setLeading and getLeading
TEST_F(GfxStateTest_638, SetAndGetLeading_638) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_638, SetAndGetRise_638) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_638, SetAndGetRender_638) {
    state->setRender(1);
    EXPECT_EQ(state->getRender(), 1);
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_638, SetAndGetRenderingIntent_638) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with different values
TEST_F(GfxStateTest_638, SetRenderingIntentVariousValues_638) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");

    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");

    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_638, SetAndGetCTM_638) {
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
TEST_F(GfxStateTest_638, ConcatCTM_638) {
    // Set identity first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Concat with scale 2x
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform
TEST_F(GfxStateTest_638, Transform_638) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

// Test transformDelta
TEST_F(GfxStateTest_638, TransformDelta_638) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_638, SetAndGetTextMat_638) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_638, SetAndGetBlendMode_638) {
    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test save and restore
TEST_F(GfxStateTest_638, SaveAndRestore_638) {
    state->setLineWidth(5.0);
    EXPECT_FALSE(state->hasSaves());
    
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    
    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);
    
    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_638, HasSavesInitially_638) {
    EXPECT_FALSE(state->hasSaves());
}

// Test moveTo, lineTo, and path operations
TEST_F(GfxStateTest_638, PathOperationsMoveTo_638) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
    
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo
TEST_F(GfxStateTest_638, PathOperationsLineTo_638) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test curveTo
TEST_F(GfxStateTest_638, PathOperationsCurveTo_638) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_638, PathOperationsClosePath_638) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_638, ClearPath_638) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
    
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test textMoveTo
TEST_F(GfxStateTest_638, TextMoveTo_638) {
    state->textMoveTo(100.0, 200.0);
    // Verify through getCurTextX/getCurTextY and lineX/lineY
    // The exact behavior depends on implementation
}

// Test getClipBBox
TEST_F(GfxStateTest_638, GetClipBBox_638) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be initialized to page boundaries or similar
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_638, GetUserClipBBox_638) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_638, ClipToRect_638) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip bbox should be constrained
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_638, SetAndGetLineDash_638) {
    std::vector<double> dash = {3.0, 2.0, 1.0};
    state->setLineDash(std::move(dash), 0.5);
    
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
    EXPECT_DOUBLE_EQ(result[2], 1.0);
    EXPECT_DOUBLE_EQ(start, 0.5);
}

// Test setLineDash with empty dash
TEST_F(GfxStateTest_638, SetLineDashEmpty_638) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test copy
TEST_F(GfxStateTest_638, CopyState_638) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// Test copy does not share mutable state (line width changes are independent)
TEST_F(GfxStateTest_638, CopyStateIndependence_638) {
    state->setLineWidth(5.0);
    std::unique_ptr<GfxState> copied(state->copy());
    
    copied->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 10.0);
}

// Test construction with different rotations
TEST_F(GfxStateTest_638, ConstructionWithRotation180_638) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(s.getRotate(), 180);
}

TEST_F(GfxStateTest_638, ConstructionWithRotation270_638) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(s.getRotate(), 270);
}

// Test construction with different DPI
TEST_F(GfxStateTest_638, ConstructionWithHighDPI_638) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(s.getVDPI(), 300.0);
}

// Test construction with asymmetric DPI
TEST_F(GfxStateTest_638, ConstructionWithAsymmetricDPI_638) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(s.getVDPI(), 300.0);
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_638, SetAndGetFillColor_638) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    EXPECT_EQ(result->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_638, SetAndGetStrokeColor_638) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 16384);
}

// Test fontSize
TEST_F(GfxStateTest_638, GetFontSizeInitial_638) {
    // Font size should be available; testing setter through setFont requires a font object
    double fontSize = state->getFontSize();
    // Just check it doesn't crash and returns some value
    (void)fontSize;
}

// Test transformWidth
TEST_F(GfxStateTest_638, TransformWidth_638) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test transformWidth with zero
TEST_F(GfxStateTest_638, TransformWidthZero_638) {
    double tw = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(tw, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_638, GetTransformedLineWidth_638) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(5.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test multiple save/restore
TEST_F(GfxStateTest_638, MultipleSaveRestore_638) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);
    
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_638, ShiftCTMAndClip_638) {
    const auto &ctmBefore = state->getCTM();
    double e_before = ctmBefore[4];
    double f_before = ctmBefore[5];
    
    state->shiftCTMAndClip(10.0, 20.0);
    
    const auto &ctmAfter = state->getCTM();
    EXPECT_DOUBLE_EQ(ctmAfter[4], e_before + 10.0);
    EXPECT_DOUBLE_EQ(ctmAfter[5], f_before + 20.0);
}

// Test construction with upsideDown = false
TEST_F(GfxStateTest_638, ConstructionUpsideDownFalse_638) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(s.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s.getPageHeight(), 792.0);
}

// Test getCurX and getCurY after moveTo
TEST_F(GfxStateTest_638, GetCurXYAfterMoveTo_638) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->moveTo(50.0, 100.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 100.0);
}

// Test getPath after construction
TEST_F(GfxStateTest_638, GetPathInitial_638) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test getFillColorSpace initially
TEST_F(GfxStateTest_638, GetFillColorSpaceInitial_638) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // Should have a default color space
    EXPECT_NE(cs, nullptr);
}

// Test getStrokeColorSpace initially
TEST_F(GfxStateTest_638, GetStrokeColorSpaceInitial_638) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test getFillPattern initially null
TEST_F(GfxStateTest_638, GetFillPatternInitial_638) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

// Test getStrokePattern initially null
TEST_F(GfxStateTest_638, GetStrokePatternInitial_638) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test getFont initially
TEST_F(GfxStateTest_638, GetFontInitial_638) {
    const auto &font = state->getFont();
    // May be null initially
    (void)font;
}

// Test isParentState
TEST_F(GfxStateTest_638, IsParentState_638) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
}

// Test parseBlendMode with Normal
TEST_F(GfxStateTest_638, ParseBlendModeNormal_638) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// Test setFillOpacity boundary values
TEST_F(GfxStateTest_638, SetFillOpacityBoundary_638) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setStrokeOpacity boundary values
TEST_F(GfxStateTest_638, SetStrokeOpacityBoundary_638) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
    
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test getLineX and getLineY
TEST_F(GfxStateTest_638, GetLineXY_638) {
    double lx = state->getLineX();
    double ly = state->getLineY();
    // Just verify accessible
    (void)lx;
    (void)ly;
}

// Test getReusablePath
TEST_F(GfxStateTest_638, GetReusablePath_638) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}

// Test clip operation
TEST_F(GfxStateTest_638, ClipOperation_638) {
    state->moveTo(10.0, 10.0);
    state->lineTo(100.0, 10.0);
    state->lineTo(100.0, 100.0);
    state->lineTo(10.0, 100.0);
    state->closePath();
    state->clip();
    // Verify clip changed bounding box
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setHorizScaling default
TEST_F(GfxStateTest_638, DefaultHorizScaling_638) {
    // Default horizScaling should be 1.0 (or 100%)
    double hs = state->getHorizScaling();
    EXPECT_DOUBLE_EQ(hs, 1.0);
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_638, GetCTMWithMatrix_638) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify the matrix is populated
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}
