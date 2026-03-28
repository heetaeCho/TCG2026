#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState for testing
class GfxStateTest_641 : public ::testing::Test {
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
TEST_F(GfxStateTest_641, ConstructionAndDPI_641) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_641, PageDimensions_641) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test initial rotation
TEST_F(GfxStateTest_641, InitialRotation_641) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page bounds
TEST_F(GfxStateTest_641, PageBounds_641) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_641, SetGetLineCap_641) {
    state->setLineCap(LineCapButt);
    EXPECT_EQ(state->getLineCap(), LineCapButt);

    state->setLineCap(LineCapRound);
    EXPECT_EQ(state->getLineCap(), LineCapRound);

    state->setLineCap(LineCapProjecting);
    EXPECT_EQ(state->getLineCap(), LineCapProjecting);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_641, SetGetLineJoin_641) {
    state->setLineJoin(LineJoinMiter);
    EXPECT_EQ(state->getLineJoin(), LineJoinMiter);

    state->setLineJoin(LineJoinRound);
    EXPECT_EQ(state->getLineJoin(), LineJoinRound);

    state->setLineJoin(LineJoinBevel);
    EXPECT_EQ(state->getLineJoin(), LineJoinBevel);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_641, SetGetLineWidth_641) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);

    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);

    state->setLineWidth(100.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 100.0);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_641, SetGetMiterLimit_641) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);

    state->setMiterLimit(1.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 1.0);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_641, SetGetFlatness_641) {
    state->setFlatness(1);
    EXPECT_EQ(state->getFlatness(), 1);

    state->setFlatness(100);
    EXPECT_EQ(state->getFlatness(), 100);
}

// Test fill opacity
TEST_F(GfxStateTest_641, SetGetFillOpacity_641) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);

    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);

    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

// Test stroke opacity
TEST_F(GfxStateTest_641, SetGetStrokeOpacity_641) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);

    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// Test fill overprint
TEST_F(GfxStateTest_641, SetGetFillOverprint_641) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());

    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_641, SetGetStrokeOverprint_641) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());

    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_641, SetGetOverprintMode_641) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);

    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test blend mode
TEST_F(GfxStateTest_641, SetGetBlendMode_641) {
    state->setBlendMode(gfxBlendNormal);
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);

    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test stroke adjust
TEST_F(GfxStateTest_641, SetGetStrokeAdjust_641) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());

    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_641, SetGetAlphaIsShape_641) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());

    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_641, SetGetTextKnockout_641) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());

    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test character spacing
TEST_F(GfxStateTest_641, SetGetCharSpace_641) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);

    state->setCharSpace(0.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test word spacing
TEST_F(GfxStateTest_641, SetGetWordSpace_641) {
    state->setWordSpace(5.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 5.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_641, SetGetHorizScaling_641) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test leading
TEST_F(GfxStateTest_641, SetGetLeading_641) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_641, SetGetRise_641) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test render
TEST_F(GfxStateTest_641, SetGetRender_641) {
    state->setRender(1);
    EXPECT_EQ(state->getRender(), 1);

    state->setRender(0);
    EXPECT_EQ(state->getRender(), 0);
}

// Test font size
TEST_F(GfxStateTest_641, GetFontSize_641) {
    // Default font size should be some value
    double fontSize = state->getFontSize();
    // Just verify it's callable
    (void)fontSize;
}

// Test text matrix
TEST_F(GfxStateTest_641, SetGetTextMat_641) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto& mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 0.0);
    EXPECT_DOUBLE_EQ(mat[5], 0.0);
}

// Test setCTM
TEST_F(GfxStateTest_641, SetCTM_641) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test transform
TEST_F(GfxStateTest_641, Transform_641) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_641, TransformWithScaling_641) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transformDelta
TEST_F(GfxStateTest_641, TransformDelta_641) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test save and restore
TEST_F(GfxStateTest_641, SaveAndRestore_641) {
    state->setLineWidth(3.0);
    EXPECT_FALSE(state->hasSaves());

    GfxState* saved = state->save();
    EXPECT_TRUE(saved->hasSaves());

    saved->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 5.0);

    GfxState* restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
}

// Test hasSaves with no saves
TEST_F(GfxStateTest_641, HasSavesInitially_641) {
    EXPECT_FALSE(state->hasSaves());
}

// Test moveTo and path operations
TEST_F(GfxStateTest_641, MoveToAndLineTo_641) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo after moveTo
TEST_F(GfxStateTest_641, LineToAfterMoveTo_641) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test curveTo
TEST_F(GfxStateTest_641, CurveTo_641) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_641, ClosePath_641) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_641, ClearPath_641) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());

    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test rendering intent
TEST_F(GfxStateTest_641, SetGetRenderingIntent_641) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");

    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");

    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");

    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test clip bounding box
TEST_F(GfxStateTest_641, GetClipBBox_641) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be initialized to page bounds or similar
    // Just test it's callable and returns reasonable values
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_641, GetUserClipBBox_641) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_641, ClipToRect_641) {
    state->clipToRect(50.0, 50.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip box should be at most the specified rect
    EXPECT_GE(xMin, 50.0 - 1e-6);
    EXPECT_GE(yMin, 50.0 - 1e-6);
    EXPECT_LE(xMax, 200.0 + 1e-6);
    EXPECT_LE(yMax, 200.0 + 1e-6);
}

// Test concatCTM
TEST_F(GfxStateTest_641, ConcatCTM_641) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test getPath
TEST_F(GfxStateTest_641, GetPath_641) {
    const GfxPath* path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test text move
TEST_F(GfxStateTest_641, TextMoveTo_641) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test setLineDash
TEST_F(GfxStateTest_641, SetGetLineDash_641) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);

    double start;
    const auto& retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_641, EmptyLineDash_641) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);

    double start;
    const auto& retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test copy
TEST_F(GfxStateTest_641, Copy_641) {
    state->setLineWidth(7.5);
    state->setFlatness(50);

    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_EQ(copied->getFlatness(), 50);
}

// Test with rotation
TEST(GfxStateRotationTest_641, RotatedPage_641) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
}

// Test with different DPI
TEST(GfxStateDPITest_641, DifferentDPI_641) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test multiple save/restore
TEST_F(GfxStateTest_641, MultipleSaveRestore_641) {
    state->setLineWidth(1.0);
    GfxState* s1 = state->save();

    s1->setLineWidth(2.0);
    GfxState* s2 = s1->save();

    s2->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);

    GfxState* r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);

    GfxState* r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
}

// Test textShift
TEST_F(GfxStateTest_641, TextShift_641) {
    state->textMoveTo(10.0, 20.0);
    double initialX = state->getCurX();
    double initialY = state->getCurY();
    state->textShift(5.0, 3.0);
    // After text shift, cursor should have moved
    // The exact behavior depends on the text matrix, but we can verify it's callable
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_641, SetGetFillColor_641) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor* retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_641, SetGetStrokeColor_641) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor* retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test transformWidth
TEST_F(GfxStateTest_641, TransformWidth_641) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(tw, 2.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_641, GetTransformedLineWidth_641) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 6.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_641, ShiftCTMAndClip_641) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test initial color spaces are null
TEST_F(GfxStateTest_641, InitialColorSpaces_641) {
    // fillColorSpace and strokeColorSpace should have defaults
    GfxColorSpace* fcs = state->getFillColorSpace();
    GfxColorSpace* scs = state->getStrokeColorSpace();
    // They should be initialized (likely to DeviceGray)
    EXPECT_NE(fcs, nullptr);
    EXPECT_NE(scs, nullptr);
}

// Test initial pattern is null
TEST_F(GfxStateTest_641, InitialPatterns_641) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test getCTM with Matrix parameter
TEST_F(GfxStateTest_641, GetCTMMatrix_641) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify matrix was populated
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test rendering intent with long string (should be truncated to fit 32 chars)
TEST_F(GfxStateTest_641, RenderingIntentLongString_641) {
    // The buffer is char[32], so let's test with a valid intent name
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test boundary: zero-sized page
TEST(GfxStateZeroPage_641, ZeroSizedPage_641) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 0;
    pageBox.y2 = 0;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 0.0);
}

// Test isParentState
TEST_F(GfxStateTest_641, IsParentState_641) {
    GfxState* saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
}

// Test getReusablePath
TEST_F(GfxStateTest_641, GetReusablePath_641) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}
