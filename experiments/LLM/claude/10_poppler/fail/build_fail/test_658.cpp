#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "poppler/GfxState.h"

// Helper to create a GfxState with reasonable defaults
static std::unique_ptr<GfxState> createDefaultGfxState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_658 : public ::testing::Test {
protected:
    void SetUp() override {
        state = createDefaultGfxState();
    }

    std::unique_ptr<GfxState> state;
};

// Test that copyDefaultGrayColorSpace returns a non-null color space even when
// no default gray color space has been set (should return GfxDeviceGrayColorSpace)
TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_NoDefault_ReturnsDeviceGray_658) {
    auto cs = state->copyDefaultGrayColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceGray);
}

// Test that copyDefaultGrayColorSpace returns a copy of the set color space
TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_WithDefault_ReturnsCopy_658) {
    auto grayCs = std::make_unique<GfxDeviceGrayColorSpace>();
    state->setDefaultGrayColorSpace(std::move(grayCs));

    auto cs = state->copyDefaultGrayColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceGray);
}

// Test that copyDefaultRGBColorSpace returns a non-null color space when no default is set
TEST_F(GfxStateTest_658, CopyDefaultRGBColorSpace_NoDefault_ReturnsDeviceRGB_658) {
    auto cs = state->copyDefaultRGBColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceRGB);
}

// Test that copyDefaultCMYKColorSpace returns a non-null color space when no default is set
TEST_F(GfxStateTest_658, CopyDefaultCMYKColorSpace_NoDefault_ReturnsDeviceCMYK_658) {
    auto cs = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceCMYK);
}

// Test basic GfxState construction with normal parameters
TEST_F(GfxStateTest_658, Construction_NormalParameters_658) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test getters for initial default values
TEST_F(GfxStateTest_658, InitialDefaults_658) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
    EXPECT_FALSE(state->getFillOverprint());
    EXPECT_FALSE(state->getStrokeOverprint());
    EXPECT_EQ(state->getOverprintMode(), 0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
    EXPECT_EQ(state->getFlatness(), 1);
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test page coordinates
TEST_F(GfxStateTest_658, PageCoordinates_658) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_658, SetGetFillOpacity_658) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_658, SetGetStrokeOpacity_658) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test set and get fill overprint
TEST_F(GfxStateTest_658, SetGetFillOverprint_658) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set and get stroke overprint
TEST_F(GfxStateTest_658, SetGetStrokeOverprint_658) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test set and get overprint mode
TEST_F(GfxStateTest_658, SetGetOverprintMode_658) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test set and get line width
TEST_F(GfxStateTest_658, SetGetLineWidth_658) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test set and get flatness
TEST_F(GfxStateTest_658, SetGetFlatness_658) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test set and get line join
TEST_F(GfxStateTest_658, SetGetLineJoin_658) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test set and get line cap
TEST_F(GfxStateTest_658, SetGetLineCap_658) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test set and get miter limit
TEST_F(GfxStateTest_658, SetGetMiterLimit_658) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test set and get stroke adjust
TEST_F(GfxStateTest_658, SetGetStrokeAdjust_658) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set and get alpha is shape
TEST_F(GfxStateTest_658, SetGetAlphaIsShape_658) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test set and get text knockout
TEST_F(GfxStateTest_658, SetGetTextKnockout_658) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test set and get char space
TEST_F(GfxStateTest_658, SetGetCharSpace_658) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test set and get word space
TEST_F(GfxStateTest_658, SetGetWordSpace_658) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test set and get horiz scaling
TEST_F(GfxStateTest_658, SetGetHorizScaling_658) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test set and get leading
TEST_F(GfxStateTest_658, SetGetLeading_658) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test set and get rise
TEST_F(GfxStateTest_658, SetGetRise_658) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test set and get render
TEST_F(GfxStateTest_658, SetGetRender_658) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test set and get rendering intent
TEST_F(GfxStateTest_658, SetGetRenderingIntent_658) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test save and restore
TEST_F(GfxStateTest_658, SaveAndRestore_658) {
    state->setFillOpacity(0.5);
    EXPECT_FALSE(state->hasSaves());

    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(saved->hasSaves());

    saved->setFillOpacity(0.8);
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.8);

    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.5);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_658, HasSaves_InitiallyFalse_658) {
    EXPECT_FALSE(state->hasSaves());
}

// Test setCTM
TEST_F(GfxStateTest_658, SetCTM_658) {
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
TEST_F(GfxStateTest_658, Transform_Identity_658) {
    // With default CTM (identity for the coordinate system), test transform
    double x2, y2;
    state->transform(100.0, 200.0, &x2, &y2);
    // The transform depends on the CTM set during construction
    // We just verify it produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test moveTo and isPath/isCurPt
TEST_F(GfxStateTest_658, MoveToAndPath_658) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo
TEST_F(GfxStateTest_658, LineTo_658) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_658, CurveTo_658) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_658, ClosePath_658) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_658, ClearPath_658) {
    state->moveTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test clipToRect
TEST_F(GfxStateTest_658, ClipToRect_658) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_658, SetGetTextMat_658) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 10.0);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_658, SetGetLineDash_658) {
    std::vector<double> dash = {3.0, 2.0, 1.0};
    state->setLineDash(std::move(dash), 0.5);

    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.5);
    ASSERT_EQ(d.size(), 3u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
    EXPECT_DOUBLE_EQ(d[2], 1.0);
}

// Test setFillColorSpace
TEST_F(GfxStateTest_658, SetFillColorSpace_658) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    state->setFillColorSpace(std::move(cs));
    ASSERT_NE(state->getFillColorSpace(), nullptr);
    EXPECT_EQ(state->getFillColorSpace()->getMode(), csDeviceRGB);
}

// Test setStrokeColorSpace
TEST_F(GfxStateTest_658, SetStrokeColorSpace_658) {
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    state->setStrokeColorSpace(std::move(cs));
    ASSERT_NE(state->getStrokeColorSpace(), nullptr);
    EXPECT_EQ(state->getStrokeColorSpace()->getMode(), csDeviceCMYK);
}

// Test setBlendMode
TEST_F(GfxStateTest_658, SetGetBlendMode_658) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test copy method
TEST_F(GfxStateTest_658, Copy_658) {
    state->setFillOpacity(0.7);
    state->setLineWidth(3.0);
    auto copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    delete copied;
}

// Test textMoveTo
TEST_F(GfxStateTest_658, TextMoveTo_658) {
    state->textMoveTo(50.0, 100.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 100.0);
}

// Test construction with rotation
TEST(GfxStateConstructionTest_658, ConstructWithRotation_658) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
}

// Test construction with different DPI
TEST(GfxStateConstructionTest_658, ConstructWithDifferentDPI_658) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test setDefaultGrayColorSpace then copyDefaultGrayColorSpace
TEST_F(GfxStateTest_658, SetDefaultGrayThenCopy_658) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    state->setDefaultGrayColorSpace(std::move(cs));
    auto copy1 = state->copyDefaultGrayColorSpace();
    auto copy2 = state->copyDefaultGrayColorSpace();
    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    // They should be different objects
    EXPECT_NE(copy1.get(), copy2.get());
    EXPECT_EQ(copy1->getMode(), csDeviceGray);
    EXPECT_EQ(copy2->getMode(), csDeviceGray);
}

// Test setDefaultRGBColorSpace then copyDefaultRGBColorSpace
TEST_F(GfxStateTest_658, SetDefaultRGBThenCopy_658) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    state->setDefaultRGBColorSpace(std::move(cs));
    auto copy = state->copyDefaultRGBColorSpace();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getMode(), csDeviceRGB);
}

// Test setDefaultCMYKColorSpace then copyDefaultCMYKColorSpace
TEST_F(GfxStateTest_658, SetDefaultCMYKThenCopy_658) {
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    state->setDefaultCMYKColorSpace(std::move(cs));
    auto copy = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getMode(), csDeviceCMYK);
}

// Test getClipBBox returns valid initial clip
TEST_F(GfxStateTest_658, GetClipBBox_Initial_658) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_658, GetUserClipBBox_658) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test boundary: line width of zero
TEST_F(GfxStateTest_658, SetLineWidthZero_658) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test boundary: opacity at boundaries
TEST_F(GfxStateTest_658, OpacityBoundary_658) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_658, EmptyLineDash_658) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test rendering intent with long string (boundary: buffer is 32 chars)
TEST_F(GfxStateTest_658, RenderingIntentLongString_658) {
    // The internal buffer is 32 chars, so test with a string that fits
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test getPath after clearPath
TEST_F(GfxStateTest_658, GetPathAfterClear_658) {
    state->clearPath();
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test isParentState
TEST_F(GfxStateTest_658, IsParentState_658) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    GfxState *restored = child->restore();
    (void)restored;
}

// Test multiple save/restore
TEST_F(GfxStateTest_658, MultipleSaveRestore_658) {
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

// Test getReusablePath is not null
TEST_F(GfxStateTest_658, GetReusablePath_658) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rpi = state->getReusablePath();
    ASSERT_NE(rpi, nullptr);
}

// Test concatCTM
TEST_F(GfxStateTest_658, ConcatCTM_658) {
    const auto &ctmBefore = state->getCTM();
    double a0 = ctmBefore[0];
    // Concatenate with a scaling matrix
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctmAfter = state->getCTM();
    // The CTM should have changed
    // With identity * scale(2), the first element should be 2*a0
    EXPECT_DOUBLE_EQ(ctmAfter[0], 2.0 * a0);
}

// Test font size
TEST_F(GfxStateTest_658, SetGetFontSize_658) {
    // Set font with nullptr and a size
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
    EXPECT_EQ(state->getFont(), nullptr);
}
