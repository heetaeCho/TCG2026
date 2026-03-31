#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"
#include "Object.h"

// Helper to create a basic GfxState for testing
class GfxStateTest_657 : public ::testing::Test {
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
TEST_F(GfxStateTest_657, ConstructorSetsDPI_657) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_657, PageDimensions_657) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test page coordinates
TEST_F(GfxStateTest_657, PageCoordinates_657) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_657, RotateDefault_657) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test with rotation
TEST(GfxStateRotateTest_657, ConstructorWithRotation_657) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test set and get line width
TEST_F(GfxStateTest_657, SetGetLineWidth_657) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test set and get line width zero
TEST_F(GfxStateTest_657, SetLineWidthZero_657) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test set and get flatness
TEST_F(GfxStateTest_657, SetGetFlatness_657) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test set and get line join
TEST_F(GfxStateTest_657, SetGetLineJoin_657) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test set and get line cap
TEST_F(GfxStateTest_657, SetGetLineCap_657) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test set and get miter limit
TEST_F(GfxStateTest_657, SetGetMiterLimit_657) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_657, SetGetFillOpacity_657) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_657, SetGetStrokeOpacity_657) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test set and get fill overprint
TEST_F(GfxStateTest_657, SetGetFillOverprint_657) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set and get stroke overprint
TEST_F(GfxStateTest_657, SetGetStrokeOverprint_657) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set and get overprint mode
TEST_F(GfxStateTest_657, SetGetOverprintMode_657) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test set and get stroke adjust
TEST_F(GfxStateTest_657, SetGetStrokeAdjust_657) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set and get alpha is shape
TEST_F(GfxStateTest_657, SetGetAlphaIsShape_657) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set and get text knockout
TEST_F(GfxStateTest_657, SetGetTextKnockout_657) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set and get char space
TEST_F(GfxStateTest_657, SetGetCharSpace_657) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test set and get word space
TEST_F(GfxStateTest_657, SetGetWordSpace_657) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test set and get horiz scaling
TEST_F(GfxStateTest_657, SetGetHorizScaling_657) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test set and get leading
TEST_F(GfxStateTest_657, SetGetLeading_657) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test set and get rise
TEST_F(GfxStateTest_657, SetGetRise_657) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test set and get render
TEST_F(GfxStateTest_657, SetGetRender_657) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test set and get rendering intent
TEST_F(GfxStateTest_657, SetGetRenderingIntent_657) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test rendering intent with various values
TEST_F(GfxStateTest_657, SetRenderingIntentRelativeColorimetric_657) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test set and get blend mode
TEST_F(GfxStateTest_657, SetGetBlendMode_657) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test set and get font size
TEST_F(GfxStateTest_657, SetGetFontSize_657) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test text matrix
TEST_F(GfxStateTest_657, SetGetTextMat_657) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// Test CTM
TEST_F(GfxStateTest_657, SetCTM_657) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// Test concatCTM
TEST_F(GfxStateTest_657, ConcatCTM_657) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform
TEST_F(GfxStateTest_657, Transform_657) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling
TEST_F(GfxStateTest_657, TransformWithScaling_657) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test transformDelta
TEST_F(GfxStateTest_657, TransformDelta_657) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test save and restore
TEST_F(GfxStateTest_657, SaveRestore_657) {
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
TEST_F(GfxStateTest_657, HasSavesInitiallyFalse_657) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_657, HasSavesAfterSave_657) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up by restoring
    saved->restore();
}

// Test path operations - moveTo, lineTo, isPath, isCurPt
TEST_F(GfxStateTest_657, PathOperationsMoveTo_657) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test path operations - lineTo
TEST_F(GfxStateTest_657, PathOperationsLineTo_657) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

// Test path operations - curveTo
TEST_F(GfxStateTest_657, PathOperationsCurveTo_657) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test path operations - closePath
TEST_F(GfxStateTest_657, PathOperationsClosePath_657) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_657, ClearPath_657) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test getCurX/getCurY after moveTo
TEST_F(GfxStateTest_657, GetCurXYAfterMoveTo_657) {
    state->clearPath();
    state->moveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 25.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_657, TextMoveTo_657) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test clip bounding box
TEST_F(GfxStateTest_657, GetClipBBox_657) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After construction, clip should cover the page
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_657, ClipToRect_657) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_657, GetUserClipBBox_657) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setLineDash
TEST_F(GfxStateTest_657, SetGetLineDash_657) {
    std::vector<double> dash = {5.0, 3.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 5.0);
    EXPECT_DOUBLE_EQ(result[1], 3.0);
}

// Test setLineDash with empty dash
TEST_F(GfxStateTest_657, SetLineDashEmpty_657) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(result.empty());
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_657, SetGetFillColor_657) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_657, SetGetStrokeColor_657) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->c[0], 16384);
}

// Test copy
TEST_F(GfxStateTest_657, Copy_657) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// Test setDefaultCMYKColorSpace
TEST_F(GfxStateTest_657, SetDefaultCMYKColorSpace_657) {
    // Setting to nullptr should be safe
    state->setDefaultCMYKColorSpace(nullptr);
    auto cs = state->copyDefaultCMYKColorSpace();
    EXPECT_EQ(cs, nullptr);
}

// Test setDefaultGrayColorSpace
TEST_F(GfxStateTest_657, SetDefaultGrayColorSpace_657) {
    state->setDefaultGrayColorSpace(nullptr);
    auto cs = state->copyDefaultGrayColorSpace();
    EXPECT_EQ(cs, nullptr);
}

// Test setDefaultRGBColorSpace
TEST_F(GfxStateTest_657, SetDefaultRGBColorSpace_657) {
    state->setDefaultRGBColorSpace(nullptr);
    auto cs = state->copyDefaultRGBColorSpace();
    EXPECT_EQ(cs, nullptr);
}

// Test getPath returns non-null initially
TEST_F(GfxStateTest_657, GetPathNotNull_657) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test transformWidth
TEST_F(GfxStateTest_657, TransformWidth_657) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

// Test transformWidth with scaling
TEST_F(GfxStateTest_657, TransformWidthWithScaling_657) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 10.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_657, GetTransformedLineWidth_657) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tw, 3.0);
}

// Test different page rotations
TEST(GfxStateRotationTest_657, Rotation180_657) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(s.getRotate(), 180);
    EXPECT_DOUBLE_EQ(s.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s.getPageHeight(), 792.0);
}

TEST(GfxStateRotationTest_657, Rotation270_657) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(s.getRotate(), 270);
}

// Test different DPI values
TEST(GfxStateDPITest_657, HighDPI_657) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(s.getVDPI(), 300.0);
}

// Test non-square DPI
TEST(GfxStateDPITest_657, NonSquareDPI_657) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(s.getVDPI(), 300.0);
}

// Test parseBlendMode with Normal
TEST_F(GfxStateTest_657, ParseBlendModeNormal_657) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// Test fill and stroke color space initial state
TEST_F(GfxStateTest_657, InitialFillColorSpace_657) {
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_657, InitialStrokeColorSpace_657) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test initial fill and stroke patterns are null
TEST_F(GfxStateTest_657, InitialFillPattern_657) {
    GfxPattern *p = state->getFillPattern();
    EXPECT_EQ(p, nullptr);
}

TEST_F(GfxStateTest_657, InitialStrokePattern_657) {
    GfxPattern *p = state->getStrokePattern();
    EXPECT_EQ(p, nullptr);
}

// Test getReusablePath
TEST_F(GfxStateTest_657, GetReusablePath_657) {
    state->clearPath();
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto it = state->getReusablePath();
    EXPECT_NE(it, nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_657, ShiftCTMAndClip_657) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// Test isParentState
TEST_F(GfxStateTest_657, IsParentState_657) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
}

// Test upside down false
TEST(GfxStateUpsideDownTest_657, UpsideDownFalse_657) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(s.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s.getPageHeight(), 792.0);
}

// Test setting multiple properties and verifying isolation
TEST_F(GfxStateTest_657, MultiplePropertySet_657) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.8);
    state->setStrokeOpacity(0.6);
    state->setCharSpace(2.0);
    state->setWordSpace(1.0);

    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.8);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.6);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 1.0);
}

// Test save/restore preserves state properties correctly
TEST_F(GfxStateTest_657, SaveRestorePreservesProperties_657) {
    state->setLineWidth(4.0);
    state->setFillOpacity(0.9);
    state->setCharSpace(1.5);

    GfxState *saved = state->save();
    saved->setLineWidth(8.0);
    saved->setFillOpacity(0.1);
    saved->setCharSpace(3.0);

    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 8.0);
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.1);
    EXPECT_DOUBLE_EQ(saved->getCharSpace(), 3.0);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 4.0);
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.9);
    EXPECT_DOUBLE_EQ(restored->getCharSpace(), 1.5);
}

// Test getCTM with Matrix output
TEST_F(GfxStateTest_657, GetCTMMatrix_657) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test default blend mode is Normal
TEST_F(GfxStateTest_657, DefaultBlendMode_657) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// Test boundary: very large line width
TEST_F(GfxStateTest_657, VeryLargeLineWidth_657) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}

// Test boundary: negative line width
TEST_F(GfxStateTest_657, NegativeLineWidth_657) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test boundary: opacity at limits
TEST_F(GfxStateTest_657, OpacityBoundary_657) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test rendering intent long string (boundary for 32 char buffer)
TEST_F(GfxStateTest_657, RenderingIntentMaxLength_657) {
    // The buffer is 32 chars, test with exactly 31 character intent + null
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}
