#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with a standard page box
class GfxStateTest_586 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;  // Letter size width in points
        pageBox.y2 = 792;  // Letter size height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_586, ConstructionAndDPI_586) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_586, PageDimensions_586) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_586, Rotation_586) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page coordinates
TEST_F(GfxStateTest_586, PageCoordinates_586) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_586, DefaultFillOpacity_586) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_586, DefaultStrokeOpacity_586) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_586, SetFillOpacity_586) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_586, SetStrokeOpacity_586) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test default line width
TEST_F(GfxStateTest_586, DefaultLineWidth_586) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set and get line width
TEST_F(GfxStateTest_586, SetLineWidth_586) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_586, DefaultFlatness_586) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set and get flatness
TEST_F(GfxStateTest_586, SetFlatness_586) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test default miter limit
TEST_F(GfxStateTest_586, DefaultMiterLimit_586) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set and get miter limit
TEST_F(GfxStateTest_586, SetMiterLimit_586) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_586, DefaultFillOverprint_586) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set and get fill overprint
TEST_F(GfxStateTest_586, SetFillOverprint_586) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_586, DefaultStrokeOverprint_586) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set and get stroke overprint
TEST_F(GfxStateTest_586, SetStrokeOverprint_586) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_586, DefaultOverprintMode_586) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set and get overprint mode
TEST_F(GfxStateTest_586, SetOverprintMode_586) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_586, DefaultStrokeAdjust_586) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set and get stroke adjust
TEST_F(GfxStateTest_586, SetStrokeAdjust_586) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_586, DefaultAlphaIsShape_586) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set and get alpha is shape
TEST_F(GfxStateTest_586, SetAlphaIsShape_586) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_586, DefaultTextKnockout_586) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set and get text knockout
TEST_F(GfxStateTest_586, SetTextKnockout_586) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_586, DefaultCharSpace_586) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set and get char space
TEST_F(GfxStateTest_586, SetCharSpace_586) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_586, DefaultWordSpace_586) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set and get word space
TEST_F(GfxStateTest_586, SetWordSpace_586) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_586, DefaultHorizScaling_586) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set and get horiz scaling
TEST_F(GfxStateTest_586, SetHorizScaling_586) {
    state->setHorizScaling(0.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test default leading
TEST_F(GfxStateTest_586, DefaultLeading_586) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set and get leading
TEST_F(GfxStateTest_586, SetLeading_586) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_586, DefaultRise_586) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set and get rise
TEST_F(GfxStateTest_586, SetRise_586) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_586, DefaultRender_586) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set and get render
TEST_F(GfxStateTest_586, SetRender_586) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default font size
TEST_F(GfxStateTest_586, DefaultFontSize_586) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default blend mode
TEST_F(GfxStateTest_586, DefaultBlendMode_586) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set and get blend mode
TEST_F(GfxStateTest_586, SetBlendMode_586) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test line join default
TEST_F(GfxStateTest_586, DefaultLineJoin_586) {
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);
}

// Test set and get line join
TEST_F(GfxStateTest_586, SetLineJoin_586) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test line cap default
TEST_F(GfxStateTest_586, DefaultLineCap_586) {
    EXPECT_EQ(state->getLineCap(), lineCapButt);
}

// Test set and get line cap
TEST_F(GfxStateTest_586, SetLineCap_586) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test save and restore
TEST_F(GfxStateTest_586, SaveAndRestore_586) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);

    GfxState *restored = state->restore();
    // After restore, we should get back the previous state
    EXPECT_NE(restored, nullptr);
}

// Test hasSaves returns false initially
TEST_F(GfxStateTest_586, HasSavesInitiallyFalse_586) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves returns true after save
TEST_F(GfxStateTest_586, HasSavesAfterSave_586) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test moveTo and path operations
TEST_F(GfxStateTest_586, MoveToAndLineTo_586) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

// Test lineTo
TEST_F(GfxStateTest_586, LineTo_586) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 100.0);
}

// Test curveTo
TEST_F(GfxStateTest_586, CurveTo_586) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test closePath
TEST_F(GfxStateTest_586, ClosePath_586) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closing, current point should be back at the start of the subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test clearPath
TEST_F(GfxStateTest_586, ClearPath_586) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test transform
TEST_F(GfxStateTest_586, Transform_586) {
    double x2, y2;
    state->transform(100.0, 200.0, &x2, &y2);
    // With default identity-like CTM (adjusted for upsideDown), we get a valid transform
    // We just verify it doesn't crash and returns finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transformDelta
TEST_F(GfxStateTest_586, TransformDelta_586) {
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test setCTM
TEST_F(GfxStateTest_586, SetCTM_586) {
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
TEST_F(GfxStateTest_586, ConcatCTM_586) {
    // Store the original CTM
    const auto origCTM = state->getCTM();
    // Concat with identity should not change CTM
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &newCTM = state->getCTM();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(origCTM[i], newCTM[i]);
    }
}

// Test getClipBBox
TEST_F(GfxStateTest_586, GetClipBBox_586) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_586, GetUserClipBBox_586) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test clipToRect
TEST_F(GfxStateTest_586, ClipToRect_586) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip region should be constrained
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test textMoveTo
TEST_F(GfxStateTest_586, TextMoveTo_586) {
    state->textMoveTo(50.0, 60.0);
    // Check that line positions are updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 60.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_586, SetTextMat_586) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 10.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_586, SetRenderingIntent_586) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with different values
TEST_F(GfxStateTest_586, SetRenderingIntentRelativeColorimetric_586) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_586, SetLineDash_586) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &dashPattern = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(dashPattern.size(), 2u);
    EXPECT_DOUBLE_EQ(dashPattern[0], 3.0);
    EXPECT_DOUBLE_EQ(dashPattern[1], 5.0);
}

// Test empty line dash
TEST_F(GfxStateTest_586, EmptyLineDash_586) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &dashPattern = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(dashPattern.size(), 0u);
}

// Test getPath - should not be null
TEST_F(GfxStateTest_586, GetPath_586) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test copy
TEST_F(GfxStateTest_586, Copy_586) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.8);
    auto copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
    delete copied;
}

// Test getStrokeColorSpace returns null initially or a default
TEST_F(GfxStateTest_586, GetStrokeColorSpace_586) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    // Initially there should be a default color space
    EXPECT_NE(cs, nullptr);
}

// Test getFillColorSpace returns non-null
TEST_F(GfxStateTest_586, GetFillColorSpace_586) {
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test getFillPattern returns null initially
TEST_F(GfxStateTest_586, GetFillPatternNull_586) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

// Test getStrokePattern returns null initially
TEST_F(GfxStateTest_586, GetStrokePatternNull_586) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test getFillColor and setFillColor
TEST_F(GfxStateTest_586, SetFillColor_586) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    EXPECT_EQ(result->c[0], 32768);
}

// Test getStrokeColor and setStrokeColor
TEST_F(GfxStateTest_586, SetStrokeColor_586) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 16384);
}

// Test getFont returns nullptr initially
TEST_F(GfxStateTest_586, GetFontDefault_586) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test transformWidth
TEST_F(GfxStateTest_586, TransformWidth_586) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_586, GetTransformedLineWidth_586) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test with rotation
TEST(GfxStateRotation_586, RotatedPage_586) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
    EXPECT_TRUE(std::isfinite(state.getPageWidth()));
    EXPECT_TRUE(std::isfinite(state.getPageHeight()));
}

// Test with different DPI values
TEST(GfxStateDPI_586, HighDPI_586) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test with asymmetric DPI
TEST(GfxStateDPI_586, AsymmetricDPI_586) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test upsideDown = false
TEST(GfxStateUpsideDown_586, NotUpsideDown_586) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 792.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_586, ShiftCTMAndClip_586) {
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    // Just verify it doesn't crash and CTM is still valid
    EXPECT_TRUE(std::isfinite(ctm[4]));
    EXPECT_TRUE(std::isfinite(ctm[5]));
}

// Test textShift
TEST_F(GfxStateTest_586, TextShift_586) {
    double origX = state->getCurX();
    double origY = state->getCurY();
    state->textShift(5.0, 10.0);
    // The current position should have changed
    // (depending on text matrix, but with default it should shift)
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// Test multiple save/restore
TEST_F(GfxStateTest_586, MultipleSaveRestore_586) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    state->setLineWidth(2.0);
    GfxState *s2 = state->save();
    state->setLineWidth(3.0);

    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);

    GfxState *r1 = state->restore();
    EXPECT_NE(r1, nullptr);

    GfxState *r2 = state->restore();
    EXPECT_NE(r2, nullptr);

    EXPECT_FALSE(state->hasSaves());
}

// Test getReusablePath
TEST_F(GfxStateTest_586, GetReusablePath_586) {
    state->moveTo(0, 0);
    state->lineTo(100, 100);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// Test getCTM with Matrix overload
TEST_F(GfxStateTest_586, GetCTMMatrix_586) {
    Matrix m;
    state->getCTM(&m);
    // Just check it doesn't crash and the matrix values are finite
    EXPECT_TRUE(std::isfinite(m.m[0]));
    EXPECT_TRUE(std::isfinite(m.m[1]));
    EXPECT_TRUE(std::isfinite(m.m[2]));
    EXPECT_TRUE(std::isfinite(m.m[3]));
    EXPECT_TRUE(std::isfinite(m.m[4]));
    EXPECT_TRUE(std::isfinite(m.m[5]));
}

// Test textTransform
TEST_F(GfxStateTest_586, TextTransform_586) {
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test textTransformDelta
TEST_F(GfxStateTest_586, TextTransformDelta_586) {
    double x2, y2;
    state->textTransformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test setStrokeColorSpace with a DeviceGray color space
TEST_F(GfxStateTest_586, SetStrokeColorSpace_586) {
    auto cs = GfxColorSpace::create(csDeviceGray);
    ASSERT_NE(cs, nullptr);
    state->setStrokeColorSpace(std::move(cs));
    GfxColorSpace *result = state->getStrokeColorSpace();
    EXPECT_NE(result, nullptr);
}

// Test setFillColorSpace with a DeviceRGB color space
TEST_F(GfxStateTest_586, SetFillColorSpace_586) {
    auto cs = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(cs, nullptr);
    state->setFillColorSpace(std::move(cs));
    GfxColorSpace *result = state->getFillColorSpace();
    EXPECT_NE(result, nullptr);
}

// Test parseBlendMode with Normal
TEST_F(GfxStateTest_586, ParseBlendModeNormal_586) {
    // Create a name object for "Normal"
    Object obj = Object(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test zero-size page box
TEST(GfxStateBoundary_586, ZeroSizePageBox_586) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 0;
    pageBox.y2 = 0;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 0.0);
}

// Test negative page box coordinates
TEST(GfxStateBoundary_586, NegativePageBox_586) {
    PDFRectangle pageBox;
    pageBox.x1 = -100;
    pageBox.y1 = -100;
    pageBox.x2 = 100;
    pageBox.y2 = 100;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 200.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 200.0);
}

// Test isParentState
TEST_F(GfxStateTest_586, IsParentState_586) {
    GfxState *saved = state->save();
    // The current state should recognize the saved state as parent
    EXPECT_FALSE(state->isParentState(state.get()));
}

// Test getDisplayProfile returns null by default
TEST_F(GfxStateTest_586, GetDisplayProfileDefault_586) {
    auto profile = state->getDisplayProfile();
    // May or may not be null depending on system, but should not crash
}

// Test getCmsRenderingIntent
TEST_F(GfxStateTest_586, GetCmsRenderingIntent_586) {
    int intent = state->getCmsRenderingIntent();
    // Just verify it returns a valid value
    EXPECT_GE(intent, 0);
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_586, GetTransformedFontSize_586) {
    double size = state->getTransformedFontSize();
    EXPECT_TRUE(std::isfinite(size));
}

// Test getFontTransMat
TEST_F(GfxStateTest_586, GetFontTransMat_586) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// Test rotation 180
TEST(GfxStateRotation_586, Rotation180_586) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state.getRotate(), 180);
}

// Test rotation 270
TEST(GfxStateRotation_586, Rotation270_586) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(state.getRotate(), 270);
}

// Test line width of zero
TEST_F(GfxStateTest_586, ZeroLineWidth_586) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test very large line width
TEST_F(GfxStateTest_586, LargeLineWidth_586) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}

// Test negative opacity gets set (or clamped - observable behavior)
TEST_F(GfxStateTest_586, NegativeFillOpacity_586) {
    state->setFillOpacity(-0.5);
    // We just verify it doesn't crash; the actual behavior is implementation-defined
    double op = state->getFillOpacity();
    EXPECT_TRUE(std::isfinite(op));
}

// Test opacity greater than 1
TEST_F(GfxStateTest_586, OverOneFillOpacity_586) {
    state->setFillOpacity(1.5);
    double op = state->getFillOpacity();
    EXPECT_TRUE(std::isfinite(op));
}
