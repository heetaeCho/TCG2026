#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makeRect(double x1, double y1, double x2, double y2) {
    PDFRectangle rect;
    rect.x1 = x1;
    rect.y1 = y1;
    rect.x2 = x2;
    rect.y2 = y2;
    return rect;
}

class GfxStateTest_574 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle rect = makeRect(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &rect, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test constructor initializes rotation correctly
TEST_F(GfxStateTest_574, GetRotate_DefaultZero_574) {
    EXPECT_EQ(0, state->getRotate());
}

// Test constructor with rotation
TEST(GfxStateConstructor_574, GetRotate_90_574) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    GfxState s(72.0, 72.0, &rect, 90, true);
    EXPECT_EQ(90, s.getRotate());
}

TEST(GfxStateConstructor_574, GetRotate_180_574) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    GfxState s(72.0, 72.0, &rect, 180, true);
    EXPECT_EQ(180, s.getRotate());
}

TEST(GfxStateConstructor_574, GetRotate_270_574) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    GfxState s(72.0, 72.0, &rect, 270, true);
    EXPECT_EQ(270, s.getRotate());
}

// Test DPI getters
TEST_F(GfxStateTest_574, GetHDPI_574) {
    EXPECT_DOUBLE_EQ(72.0, state->getHDPI());
}

TEST_F(GfxStateTest_574, GetVDPI_574) {
    EXPECT_DOUBLE_EQ(72.0, state->getVDPI());
}

// Test page dimensions
TEST_F(GfxStateTest_574, GetPageWidth_574) {
    EXPECT_DOUBLE_EQ(612.0, state->getPageWidth());
}

TEST_F(GfxStateTest_574, GetPageHeight_574) {
    EXPECT_DOUBLE_EQ(792.0, state->getPageHeight());
}

// Test page box coordinates
TEST_F(GfxStateTest_574, GetX1_574) {
    EXPECT_DOUBLE_EQ(0.0, state->getX1());
}

TEST_F(GfxStateTest_574, GetY1_574) {
    EXPECT_DOUBLE_EQ(0.0, state->getY1());
}

TEST_F(GfxStateTest_574, GetX2_574) {
    EXPECT_DOUBLE_EQ(612.0, state->getX2());
}

TEST_F(GfxStateTest_574, GetY2_574) {
    EXPECT_DOUBLE_EQ(792.0, state->getY2());
}

// Test line width
TEST_F(GfxStateTest_574, SetGetLineWidth_574) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getLineWidth());
}

TEST_F(GfxStateTest_574, SetLineWidthZero_574) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getLineWidth());
}

// Test flatness
TEST_F(GfxStateTest_574, SetGetFlatness_574) {
    state->setFlatness(5);
    EXPECT_EQ(5, state->getFlatness());
}

// Test line join
TEST_F(GfxStateTest_574, SetGetLineJoin_574) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(LineJoinStyle::Round, state->getLineJoin());
}

// Test line cap
TEST_F(GfxStateTest_574, SetGetLineCap_574) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(LineCapStyle::Round, state->getLineCap());
}

// Test miter limit
TEST_F(GfxStateTest_574, SetGetMiterLimit_574) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(15.0, state->getMiterLimit());
}

// Test stroke adjust
TEST_F(GfxStateTest_574, SetGetStrokeAdjust_574) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_574, SetGetAlphaIsShape_574) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_574, SetGetTextKnockout_574) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test fill opacity
TEST_F(GfxStateTest_574, SetGetFillOpacity_574) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
}

TEST_F(GfxStateTest_574, FillOpacityBoundary_Zero_574) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getFillOpacity());
}

TEST_F(GfxStateTest_574, FillOpacityBoundary_One_574) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(1.0, state->getFillOpacity());
}

// Test stroke opacity
TEST_F(GfxStateTest_574, SetGetStrokeOpacity_574) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(0.75, state->getStrokeOpacity());
}

// Test fill overprint
TEST_F(GfxStateTest_574, SetGetFillOverprint_574) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_574, SetGetStrokeOverprint_574) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_574, SetGetOverprintMode_574) {
    state->setOverprintMode(1);
    EXPECT_EQ(1, state->getOverprintMode());
}

// Test char space
TEST_F(GfxStateTest_574, SetGetCharSpace_574) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(2.0, state->getCharSpace());
}

// Test word space
TEST_F(GfxStateTest_574, SetGetWordSpace_574) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getWordSpace());
}

// Test horizontal scaling
TEST_F(GfxStateTest_574, SetGetHorizScaling_574) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(150.0, state->getHorizScaling());
}

// Test leading
TEST_F(GfxStateTest_574, SetGetLeading_574) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(14.0, state->getLeading());
}

// Test rise
TEST_F(GfxStateTest_574, SetGetRise_574) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(5.0, state->getRise());
}

// Test render
TEST_F(GfxStateTest_574, SetGetRender_574) {
    state->setRender(2);
    EXPECT_EQ(2, state->getRender());
}

// Test font size
TEST_F(GfxStateTest_574, GetFontSize_Default_574) {
    EXPECT_DOUBLE_EQ(0.0, state->getFontSize());
}

// Test blend mode
TEST_F(GfxStateTest_574, SetGetBlendMode_574) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(GfxBlendMode::Multiply, state->getBlendMode());
}

// Test rendering intent
TEST_F(GfxStateTest_574, SetGetRenderingIntent_574) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", state->getRenderingIntent());
}

TEST_F(GfxStateTest_574, SetRenderingIntentRelativeColorimetric_574) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ("RelativeColorimetric", state->getRenderingIntent());
}

// Test text matrix
TEST_F(GfxStateTest_574, SetGetTextMat_574) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(1.0, tm[0]);
    EXPECT_DOUBLE_EQ(0.0, tm[1]);
    EXPECT_DOUBLE_EQ(0.0, tm[2]);
    EXPECT_DOUBLE_EQ(1.0, tm[3]);
    EXPECT_DOUBLE_EQ(10.0, tm[4]);
    EXPECT_DOUBLE_EQ(20.0, tm[5]);
}

// Test CTM
TEST_F(GfxStateTest_574, GetCTM_574) {
    const auto &ctm = state->getCTM();
    // CTM should be set based on constructor parameters
    EXPECT_EQ(6u, ctm.size());
}

TEST_F(GfxStateTest_574, SetCTM_574) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(100.0, ctm[4]);
    EXPECT_DOUBLE_EQ(200.0, ctm[5]);
}

TEST_F(GfxStateTest_574, ConcatCTM_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(10.0, ctm[4]);
    EXPECT_DOUBLE_EQ(20.0, ctm[5]);
}

// Test transform
TEST_F(GfxStateTest_574, Transform_Identity_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(5.0, x2);
    EXPECT_DOUBLE_EQ(10.0, y2);
}

TEST_F(GfxStateTest_574, Transform_WithTranslation_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(105.0, x2);
    EXPECT_DOUBLE_EQ(210.0, y2);
}

TEST_F(GfxStateTest_574, TransformDelta_Identity_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(5.0, x2);
    EXPECT_DOUBLE_EQ(10.0, y2);
}

TEST_F(GfxStateTest_574, Transform_WithScale_574) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(10.0, x2);
    EXPECT_DOUBLE_EQ(30.0, y2);
}

// Test save and restore
TEST_F(GfxStateTest_574, SaveAndRestore_574) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(10.0, saved->getLineWidth());

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(5.0, restored->getLineWidth());
}

TEST_F(GfxStateTest_574, HasSaves_InitiallyFalse_574) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_574, HasSaves_AfterSave_574) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    // Restore to clean up
    saved->restore();
}

// Test path operations
TEST_F(GfxStateTest_574, IsPath_InitiallyFalse_574) {
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_574, IsCurPt_InitiallyFalse_574) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_574, MoveTo_SetsCurPt_574) {
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_574, LineTo_CreatesPath_574) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_574, CurveTo_CreatesPath_574) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_574, ClearPath_ResetsPath_574) {
    state->moveTo(10.0, 20.0);
    state->lineTo(100.0, 100.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test getCurX / getCurY after moveTo
TEST_F(GfxStateTest_574, GetCurXY_AfterMoveTo_574) {
    state->clearPath();
    state->moveTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(42.0, state->getCurX());
    EXPECT_DOUBLE_EQ(84.0, state->getCurY());
}

// Test textMoveTo
TEST_F(GfxStateTest_574, TextMoveTo_574) {
    state->textMoveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(15.0, state->getLineX());
    EXPECT_DOUBLE_EQ(25.0, state->getLineY());
}

// Test line dash
TEST_F(GfxStateTest_574, SetGetLineDash_574) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(2u, d.size());
    EXPECT_DOUBLE_EQ(3.0, d[0]);
    EXPECT_DOUBLE_EQ(5.0, d[1]);
    EXPECT_DOUBLE_EQ(1.0, start);
}

TEST_F(GfxStateTest_574, SetLineDash_Empty_574) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(0u, d.size());
    EXPECT_DOUBLE_EQ(0.0, start);
}

// Test clip bounding box
TEST_F(GfxStateTest_574, GetClipBBox_574) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After construction, clip should cover the page
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect narrows clip
TEST_F(GfxStateTest_574, ClipToRect_574) {
    state->clipToRect(100.0, 200.0, 300.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 200.0);
    EXPECT_LE(xMax, 300.0);
    EXPECT_LE(yMax, 400.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_574, GetUserClipBBox_574) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test copy
TEST_F(GfxStateTest_574, Copy_574) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    auto copied = state->copy();
    ASSERT_NE(nullptr, copied);
    EXPECT_DOUBLE_EQ(7.5, copied->getLineWidth());
    EXPECT_DOUBLE_EQ(0.3, copied->getFillOpacity());
}

// Test transformWidth
TEST_F(GfxStateTest_574, TransformWidth_Identity_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(5.0, w);
}

TEST_F(GfxStateTest_574, TransformWidth_Scaled_574) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(10.0, w);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_574, GetTransformedLineWidth_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(3.0, tw);
}

// Test with different DPI values
TEST(GfxStateConstructorDPI_574, DifferentDPI_574) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    GfxState s(150.0, 300.0, &rect, 0, true);
    EXPECT_DOUBLE_EQ(150.0, s.getHDPI());
    EXPECT_DOUBLE_EQ(300.0, s.getVDPI());
}

// Test with upsideDown = false
TEST(GfxStateConstructorUpsideDown_574, UpsideDownFalse_574) {
    PDFRectangle rect = makeRect(0, 0, 612, 792);
    GfxState s(72.0, 72.0, &rect, 0, false);
    EXPECT_EQ(0, s.getRotate());
    EXPECT_DOUBLE_EQ(612.0, s.getPageWidth());
    EXPECT_DOUBLE_EQ(792.0, s.getPageHeight());
}

// Test fill/stroke color space is initially set
TEST_F(GfxStateTest_574, FillColorSpace_InitialNotNull_574) {
    // Default fill color space should be set (typically DeviceGray)
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(nullptr, cs);
}

TEST_F(GfxStateTest_574, StrokeColorSpace_InitialNotNull_574) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(nullptr, cs);
}

// Test fill/stroke pattern initially null
TEST_F(GfxStateTest_574, FillPattern_InitialNull_574) {
    EXPECT_EQ(nullptr, state->getFillPattern());
}

TEST_F(GfxStateTest_574, StrokePattern_InitialNull_574) {
    EXPECT_EQ(nullptr, state->getStrokePattern());
}

// Test fill/stroke color
TEST_F(GfxStateTest_574, FillColor_NotNull_574) {
    const GfxColor *c = state->getFillColor();
    EXPECT_NE(nullptr, c);
}

TEST_F(GfxStateTest_574, StrokeColor_NotNull_574) {
    const GfxColor *c = state->getStrokeColor();
    EXPECT_NE(nullptr, c);
}

// Test getPath not null
TEST_F(GfxStateTest_574, GetPath_NotNull_574) {
    EXPECT_NE(nullptr, state->getPath());
}

// Test font is initially null/empty
TEST_F(GfxStateTest_574, GetFont_InitialNull_574) {
    const auto &font = state->getFont();
    EXPECT_EQ(nullptr, font);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_574, ShiftCTMAndClip_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(50.0, ctm[4]);
    EXPECT_DOUBLE_EQ(100.0, ctm[5]);
}

// Test isParentState
TEST_F(GfxStateTest_574, IsParentState_574) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    child->restore();
}

// Test closePath
TEST_F(GfxStateTest_574, ClosePath_574) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test textShift
TEST_F(GfxStateTest_574, TextShift_574) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double initialX = state->getCurX();
    double initialY = state->getCurY();
    state->textShift(10.0, 0.0);
    // After text shift, the cursor should have moved
    // (exact behavior depends on implementation, but we just check it doesn't crash)
}

// Test save/restore preserves rendering intent
TEST_F(GfxStateTest_574, SaveRestore_PreservesRenderingIntent_574) {
    state->setRenderingIntent("Saturation");
    GfxState *child = state->save();
    child->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", child->getRenderingIntent());
    GfxState *restored = child->restore();
    EXPECT_STREQ("Saturation", restored->getRenderingIntent());
}

// Test getReusablePath
TEST_F(GfxStateTest_574, GetReusablePath_574) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(nullptr, iter);
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_574, MultipleSaveRestore_574) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(3.0, s2->getLineWidth());

    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(2.0, r1->getLineWidth());

    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(1.0, r2->getLineWidth());
}

// Test CMS rendering intent
TEST_F(GfxStateTest_574, GetCmsRenderingIntent_574) {
    int intent = state->getCmsRenderingIntent();
    // Just verify it returns a valid value without crashing
    EXPECT_GE(intent, 0);
}

// Test getTransformedFontSize with identity CTM
TEST_F(GfxStateTest_574, GetTransformedFontSize_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Without a font set, font size is 0
    double tfs = state->getTransformedFontSize();
    EXPECT_DOUBLE_EQ(0.0, tfs);
}

// Test getFontTransMat
TEST_F(GfxStateTest_574, GetFontTransMat_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Values depend on implementation but should not crash
}

// Test boundary: very large line width
TEST_F(GfxStateTest_574, SetLineWidth_VeryLarge_574) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(1e10, state->getLineWidth());
}

// Test boundary: negative line width
TEST_F(GfxStateTest_574, SetLineWidth_Negative_574) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(-1.0, state->getLineWidth());
}

// Test non-standard page rect
TEST(GfxStateNonStandardRect_574, SmallRect_574) {
    PDFRectangle rect = makeRect(10, 20, 100, 200);
    GfxState s(72.0, 72.0, &rect, 0, true);
    EXPECT_DOUBLE_EQ(90.0, s.getPageWidth());
    EXPECT_DOUBLE_EQ(180.0, s.getPageHeight());
}

// Test textTransform
TEST_F(GfxStateTest_574, TextTransform_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // Should not crash; exact values depend on current text position
}

// Test textTransformDelta
TEST_F(GfxStateTest_574, TextTransformDelta_574) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(10.0, x2);
    EXPECT_DOUBLE_EQ(20.0, y2);
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_574, GetCTM_Matrix_574) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    EXPECT_DOUBLE_EQ(1.0, m.m[0]);
    EXPECT_DOUBLE_EQ(2.0, m.m[1]);
    EXPECT_DOUBLE_EQ(3.0, m.m[2]);
    EXPECT_DOUBLE_EQ(4.0, m.m[3]);
    EXPECT_DOUBLE_EQ(5.0, m.m[4]);
    EXPECT_DOUBLE_EQ(6.0, m.m[5]);
}
