#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Helper to create a basic GfxState with reasonable defaults
class GfxStateTest_584 : public ::testing::Test {
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

// Test getStrokeDeviceN with default stroke color space
TEST_F(GfxStateTest_584, GetStrokeDeviceN_DefaultColorSpace_584) {
    GfxColor deviceN;
    // Initialize deviceN to known values
    for (int i = 0; i < gfxColorMaxComps; i++) {
        deviceN.c[i] = 0;
    }
    // The default stroke color space should be set and getStrokeDeviceN should not crash
    state->getStrokeDeviceN(&deviceN);
    // We can't assert specific values without knowing the implementation,
    // but we verify the function completes without error
}

// Test getStrokeDeviceN after setting stroke color
TEST_F(GfxStateTest_584, GetStrokeDeviceN_AfterSetStrokeColor_584) {
    GfxColor color;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = 0;
    }
    color.c[0] = dblToCol(1.0);
    state->setStrokeColor(&color);

    GfxColor deviceN;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        deviceN.c[i] = 0;
    }
    state->getStrokeDeviceN(&deviceN);
    // Verify function completes; exact values depend on color space implementation
}

// Test getStrokeDeviceN after setting stroke color with all zeros
TEST_F(GfxStateTest_584, GetStrokeDeviceN_ZeroColor_584) {
    GfxColor color;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = 0;
    }
    state->setStrokeColor(&color);

    GfxColor deviceN;
    state->getStrokeDeviceN(&deviceN);
    // Function should complete without error
}

// Test getStrokeDeviceN after setting stroke color with max values
TEST_F(GfxStateTest_584, GetStrokeDeviceN_MaxColor_584) {
    GfxColor color;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = dblToCol(1.0);
    }
    state->setStrokeColor(&color);

    GfxColor deviceN;
    state->getStrokeDeviceN(&deviceN);
    // Function should complete without error
}

// Test basic constructor and page dimensions
TEST_F(GfxStateTest_584, Constructor_PageDimensions_584) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test DPI values
TEST_F(GfxStateTest_584, Constructor_DPI_584) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test rotate
TEST_F(GfxStateTest_584, Constructor_Rotate_584) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test default fill/stroke opacity
TEST_F(GfxStateTest_584, DefaultOpacity_584) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_584, SetGetStrokeOpacity_584) {
    state->setStrokeOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.5);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_584, SetGetFillOpacity_584) {
    state->setFillOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.3);
}

// Test default line width
TEST_F(GfxStateTest_584, DefaultLineWidth_584) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test setLineWidth
TEST_F(GfxStateTest_584, SetGetLineWidth_584) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test setCharSpace / getCharSpace
TEST_F(GfxStateTest_584, SetGetCharSpace_584) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test setWordSpace / getWordSpace
TEST_F(GfxStateTest_584, SetGetWordSpace_584) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setHorizScaling / getHorizScaling
TEST_F(GfxStateTest_584, SetGetHorizScaling_584) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setLeading / getLeading
TEST_F(GfxStateTest_584, SetGetLeading_584) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test setRise / getRise
TEST_F(GfxStateTest_584, SetGetRise_584) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test setRender / getRender
TEST_F(GfxStateTest_584, SetGetRender_584) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setFlatness / getFlatness
TEST_F(GfxStateTest_584, SetGetFlatness_584) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test setMiterLimit / getMiterLimit
TEST_F(GfxStateTest_584, SetGetMiterLimit_584) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test setStrokeAdjust / getStrokeAdjust
TEST_F(GfxStateTest_584, SetGetStrokeAdjust_584) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape / getAlphaIsShape
TEST_F(GfxStateTest_584, SetGetAlphaIsShape_584) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout / getTextKnockout
TEST_F(GfxStateTest_584, SetGetTextKnockout_584) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setFillOverprint / getFillOverprint
TEST_F(GfxStateTest_584, SetGetFillOverprint_584) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint / getStrokeOverprint
TEST_F(GfxStateTest_584, SetGetStrokeOverprint_584) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode / getOverprintMode
TEST_F(GfxStateTest_584, SetGetOverprintMode_584) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test save and restore
TEST_F(GfxStateTest_584, SaveRestore_584) {
    state->setLineWidth(5.0);
    GfxState *savedState = state->save();
    EXPECT_TRUE(state->hasSaves());

    savedState->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(savedState->getLineWidth(), 10.0);

    GfxState *restored = savedState->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test hasSaves returns false initially
TEST_F(GfxStateTest_584, HasSaves_InitiallyFalse_584) {
    EXPECT_FALSE(state->hasSaves());
}

// Test setFillColor / getFillColor
TEST_F(GfxStateTest_584, SetGetFillColor_584) {
    GfxColor color;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = 0;
    }
    color.c[0] = dblToCol(0.5);
    state->setFillColor(&color);

    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], dblToCol(0.5));
}

// Test setStrokeColor / getStrokeColor
TEST_F(GfxStateTest_584, SetGetStrokeColor_584) {
    GfxColor color;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = 0;
    }
    color.c[0] = dblToCol(0.75);
    state->setStrokeColor(&color);

    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], dblToCol(0.75));
}

// Test transform
TEST_F(GfxStateTest_584, Transform_584) {
    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    // With default CTM (identity scaled by DPI), result should be valid
    // We just verify the function runs without error
}

// Test transformDelta
TEST_F(GfxStateTest_584, TransformDelta_584) {
    double x2, y2;
    state->transformDelta(1.0, 1.0, &x2, &y2);
}

// Test moveTo and path operations
TEST_F(GfxStateTest_584, PathOperations_584) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo after moveTo
TEST_F(GfxStateTest_584, LineTo_584) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_584, CurveTo_584) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_584, ClosePath_584) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_584, ClearPath_584) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());

    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test getClipBBox
TEST_F(GfxStateTest_584, GetClipBBox_584) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip box should be initialized to page dimensions or similar
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_584, GetUserClipBBox_584) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setRenderingIntent / getRenderingIntent
TEST_F(GfxStateTest_584, SetGetRenderingIntent_584) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with AbsoluteColorimetric
TEST_F(GfxStateTest_584, SetGetRenderingIntent_AbsoluteColorimetric_584) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test setCTM
TEST_F(GfxStateTest_584, SetCTM_584) {
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
TEST_F(GfxStateTest_584, ConcatCTM_584) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test setTextMat / getTextMat
TEST_F(GfxStateTest_584, SetGetTextMat_584) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[4], 10.0);
    EXPECT_DOUBLE_EQ(textMat[5], 20.0);
}

// Test setLineDash / getLineDash
TEST_F(GfxStateTest_584, SetGetLineDash_584) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
}

// Test copy
TEST_F(GfxStateTest_584, Copy_584) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.7);

    auto copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    delete copied;
}

// Test clipToRect
TEST_F(GfxStateTest_584, ClipToRect_584) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, bounds should be within or equal to the clip rect
    EXPECT_GE(xMin, 10.0 - 0.001);
    EXPECT_GE(yMin, 10.0 - 0.001);
    EXPECT_LE(xMax, 100.0 + 0.001);
    EXPECT_LE(yMax, 100.0 + 0.001);
}

// Test setLineJoin / getLineJoin
TEST_F(GfxStateTest_584, SetGetLineJoin_584) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
    state->setLineJoin(lineJoinBevel);
    EXPECT_EQ(state->getLineJoin(), lineJoinBevel);
    state->setLineJoin(lineJoinMiter);
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);
}

// Test setLineCap / getLineCap
TEST_F(GfxStateTest_584, SetGetLineCap_584) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
    state->setLineCap(lineCapSquare);
    EXPECT_EQ(state->getLineCap(), lineCapSquare);
    state->setLineCap(lineCapButt);
    EXPECT_EQ(state->getLineCap(), lineCapButt);
}

// Test getStrokeColorSpace default
TEST_F(GfxStateTest_584, GetStrokeColorSpace_Default_584) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test getFillColorSpace default
TEST_F(GfxStateTest_584, GetFillColorSpace_Default_584) {
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test getFillDeviceN with default color space
TEST_F(GfxStateTest_584, GetFillDeviceN_Default_584) {
    GfxColor deviceN;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        deviceN.c[i] = 0;
    }
    state->getFillDeviceN(&deviceN);
    // Should complete without error
}

// Test textMoveTo
TEST_F(GfxStateTest_584, TextMoveTo_584) {
    state->textMoveTo(100.0, 200.0);
    // Verify through getCurTextX/getCurTextY or lineX/lineY
}

// Test different page rotation
TEST_F(GfxStateTest_584, ConstructorWithRotation_584) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test fontSize
TEST_F(GfxStateTest_584, GetFontSize_Default_584) {
    // Default font size should be some value (likely 0 or uninitialized)
    double fontSize = state->getFontSize();
    // Just verify it doesn't crash
    (void)fontSize;
}

// Test getBlendMode default
TEST_F(GfxStateTest_584, GetBlendMode_Default_584) {
    GfxBlendMode mode = state->getBlendMode();
    EXPECT_EQ(mode, gfxBlendNormal);
}

// Test setBlendMode
TEST_F(GfxStateTest_584, SetBlendMode_584) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_584, GetPageBounds_584) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test getPath
TEST_F(GfxStateTest_584, GetPath_584) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test save and isParentState
TEST_F(GfxStateTest_584, IsParentState_584) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
}

// Test transformWidth
TEST_F(GfxStateTest_584, TransformWidth_584) {
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_584, GetTransformedLineWidth_584) {
    state->setLineWidth(2.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test boundary: zero line width
TEST_F(GfxStateTest_584, ZeroLineWidth_584) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test boundary: negative opacity clamping or acceptance
TEST_F(GfxStateTest_584, BoundaryOpacityValues_584) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_584, EmptyLineDash_584) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}
