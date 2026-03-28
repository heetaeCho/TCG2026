#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_660 : public ::testing::Test {
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

// Test copyDefaultCMYKColorSpace when no default is set (should return GfxDeviceCMYKColorSpace)
TEST_F(GfxStateTest_660, CopyDefaultCMYKColorSpace_NoDefault_ReturnsDeviceCMYK_660) {
    auto cs = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceCMYK);
}

// Test copyDefaultCMYKColorSpace when a default CMYK color space is set
TEST_F(GfxStateTest_660, CopyDefaultCMYKColorSpace_WithDefault_ReturnsCopy_660) {
    auto cmykCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    state->setDefaultCMYKColorSpace(std::move(cmykCS));
    auto cs = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceCMYK);
}

// Test copyDefaultGrayColorSpace when no default is set
TEST_F(GfxStateTest_660, CopyDefaultGrayColorSpace_NoDefault_ReturnsDeviceGray_660) {
    auto cs = state->copyDefaultGrayColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceGray);
}

// Test copyDefaultRGBColorSpace when no default is set
TEST_F(GfxStateTest_660, CopyDefaultRGBColorSpace_NoDefault_ReturnsDeviceRGB_660) {
    auto cs = state->copyDefaultRGBColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceRGB);
}

// Test copyDefaultGrayColorSpace after setting a default
TEST_F(GfxStateTest_660, CopyDefaultGrayColorSpace_WithDefault_ReturnsCopy_660) {
    auto grayCS = std::make_unique<GfxDeviceGrayColorSpace>();
    state->setDefaultGrayColorSpace(std::move(grayCS));
    auto cs = state->copyDefaultGrayColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceGray);
}

// Test copyDefaultRGBColorSpace after setting a default
TEST_F(GfxStateTest_660, CopyDefaultRGBColorSpace_WithDefault_ReturnsCopy_660) {
    auto rgbCS = std::make_unique<GfxDeviceRGBColorSpace>();
    state->setDefaultRGBColorSpace(std::move(rgbCS));
    auto cs = state->copyDefaultRGBColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceRGB);
}

// Test that the returned copy is independent (different pointer)
TEST_F(GfxStateTest_660, CopyDefaultCMYKColorSpace_ReturnsDifferentPointers_660) {
    auto cs1 = state->copyDefaultCMYKColorSpace();
    auto cs2 = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(cs1, nullptr);
    ASSERT_NE(cs2, nullptr);
    EXPECT_NE(cs1.get(), cs2.get());
}

// Test basic GfxState construction parameters
TEST_F(GfxStateTest_660, Construction_BasicParameters_660) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test default fill/stroke opacity
TEST_F(GfxStateTest_660, DefaultFillOpacity_660) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_660, DefaultStrokeOpacity_660) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_660, SetFillOpacity_660) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_660, SetStrokeOpacity_660) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_660, SetLineWidth_660) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test setLineWidth with zero
TEST_F(GfxStateTest_660, SetLineWidthZero_660) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_660, SetFlatness_660) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_660, SetLineJoin_660) {
    state->setLineJoin(LineJoinStyle::lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::lineJoinRound);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_660, SetLineCap_660) {
    state->setLineCap(LineCapStyle::lineCapRound);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::lineCapRound);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_660, SetMiterLimit_660) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test setCharSpace and getCharSpace
TEST_F(GfxStateTest_660, SetCharSpace_660) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test setWordSpace and getWordSpace
TEST_F(GfxStateTest_660, SetWordSpace_660) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_660, SetHorizScaling_660) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setLeading and getLeading
TEST_F(GfxStateTest_660, SetLeading_660) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_660, SetRise_660) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_660, SetRender_660) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_660, SetFillOverprint_660) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_660, SetStrokeOverprint_660) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_660, SetOverprintMode_660) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_660, SetStrokeAdjust_660) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_660, SetAlphaIsShape_660) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_660, SetTextKnockout_660) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test save and restore
TEST_F(GfxStateTest_660, SaveAndRestore_660) {
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

// Test hasSaves when no saves
TEST_F(GfxStateTest_660, HasSaves_NoSaves_660) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after saving
TEST_F(GfxStateTest_660, HasSaves_AfterSave_660) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up by restoring
    saved->restore();
}

// Test transform
TEST_F(GfxStateTest_660, Transform_660) {
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // With default CTM, transforming (0,0) should give known results
    // We just check it doesn't crash and returns finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transformDelta
TEST_F(GfxStateTest_660, TransformDelta_660) {
    double x2, y2;
    state->transformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test moveTo and path operations
TEST_F(GfxStateTest_660, MoveToCreatesCurrentPoint_660) {
    EXPECT_FALSE(state->isCurPt());
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test isPath after lineTo
TEST_F(GfxStateTest_660, LineToCreatesPath_660) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_660, ClearPath_660) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test closePath
TEST_F(GfxStateTest_660, ClosePath_660) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_660, CurveTo_660) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(state->isPath());
}

// Test getPath returns non-null
TEST_F(GfxStateTest_660, GetPath_660) {
    ASSERT_NE(state->getPath(), nullptr);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_660, SetBlendMode_660) {
    state->setBlendMode(GfxBlendMode::gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::gfxBlendMultiply);
}

// Test default blend mode
TEST_F(GfxStateTest_660, DefaultBlendMode_660) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::gfxBlendNormal);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_660, SetRenderingIntent_660) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with another value
TEST_F(GfxStateTest_660, SetRenderingIntentRelativeColorimetric_660) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test setCTM
TEST_F(GfxStateTest_660, SetCTM_660) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_660, GetPageBounds_660) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_660, SetLineDash_660) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
}

// Test empty dash
TEST_F(GfxStateTest_660, SetLineDashEmpty_660) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_660, SetTextMat_660) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 5.0, 10.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 10.0);
}

// Test setFillColorSpace with DeviceRGB
TEST_F(GfxStateTest_660, SetFillColorSpace_660) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    state->setFillColorSpace(std::move(cs));
    ASSERT_NE(state->getFillColorSpace(), nullptr);
    EXPECT_EQ(state->getFillColorSpace()->getMode(), csDeviceRGB);
}

// Test setStrokeColorSpace with DeviceGray
TEST_F(GfxStateTest_660, SetStrokeColorSpace_660) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    state->setStrokeColorSpace(std::move(cs));
    ASSERT_NE(state->getStrokeColorSpace(), nullptr);
    EXPECT_EQ(state->getStrokeColorSpace()->getMode(), csDeviceGray);
}

// Test getClipBBox
TEST_F(GfxStateTest_660, GetClipBBox_660) {
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
TEST_F(GfxStateTest_660, GetUserClipBBox_660) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test clipToRect
TEST_F(GfxStateTest_660, ClipToRect_660) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip box should be constrained
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test textMoveTo
TEST_F(GfxStateTest_660, TextMoveTo_660) {
    state->textMoveTo(10.0, 20.0);
    // Check that line position is set
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test construction with rotation
TEST(GfxStateConstructionTest_660, RotatedPage_660) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 792.0);
}

// Test construction with upsideDown=false
TEST(GfxStateConstructionTest_660, UpsideDownFalse_660) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 100;
    pageBox.y2 = 200;
    GfxState state(300.0, 300.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test copy
TEST_F(GfxStateTest_660, Copy_660) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.8);
    auto copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
    delete copied;
}

// Test getFont default is null
TEST_F(GfxStateTest_660, DefaultFontIsNull_660) {
    EXPECT_EQ(state->getFont(), nullptr);
}

// Test getFontSize default
TEST_F(GfxStateTest_660, DefaultFontSize_660) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test concatCTM
TEST_F(GfxStateTest_660, ConcatCTM_660) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transformWidth
TEST_F(GfxStateTest_660, TransformWidth_660) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GT(w, 0.0);
}

// Test multiple copies of default color spaces are independent
TEST_F(GfxStateTest_660, CopyDefaultCMYKColorSpace_MultipleCopiesIndependent_660) {
    auto cs1 = state->copyDefaultCMYKColorSpace();
    auto cs2 = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(cs1, nullptr);
    ASSERT_NE(cs2, nullptr);
    EXPECT_NE(cs1.get(), cs2.get());
    EXPECT_EQ(cs1->getMode(), cs2->getMode());
}

// Test setting and copying default CMYK returns the correct type
TEST_F(GfxStateTest_660, SetAndCopyDefaultCMYK_ReturnsCorrectType_660) {
    auto cmyk = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxColorSpace *rawPtr = cmyk.get();
    state->setDefaultCMYKColorSpace(std::move(cmyk));
    auto copy = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(copy, nullptr);
    // The copy should not be the same object as the original
    EXPECT_NE(copy.get(), rawPtr);
    EXPECT_EQ(copy->getMode(), csDeviceCMYK);
}

// Test getNComps for returned color spaces
TEST_F(GfxStateTest_660, CopyDefaultCMYKColorSpace_NComps_660) {
    auto cs = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getNComps(), 4);
}

TEST_F(GfxStateTest_660, CopyDefaultRGBColorSpace_NComps_660) {
    auto cs = state->copyDefaultRGBColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getNComps(), 3);
}

TEST_F(GfxStateTest_660, CopyDefaultGrayColorSpace_NComps_660) {
    auto cs = state->copyDefaultGrayColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getNComps(), 1);
}
