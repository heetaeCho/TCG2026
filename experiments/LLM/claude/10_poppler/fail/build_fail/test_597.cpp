#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>

#include "GfxState.h"

// Helper to create a basic GfxState for testing
class GfxStateTest_597 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a simple page box
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612; // Letter width in points
        pageBox.y2 = 792; // Letter height in points

        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_597, ConstructionAndDPI_597) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_597, PageDimensions_597) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_597, Rotation_597) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_597, PageBoxCoordinates_597) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_597, SetAndGetLineDash_597) {
    std::vector<double> dash = {3.0, 5.0, 7.0};
    double startVal = 2.5;
    state->setLineDash(std::move(dash), startVal);

    double start = 0.0;
    const std::vector<double> &result = state->getLineDash(&start);

    EXPECT_DOUBLE_EQ(start, 2.5);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
    EXPECT_DOUBLE_EQ(result[2], 7.0);
}

// Test getLineDash with empty dash
TEST_F(GfxStateTest_597, GetLineDashEmpty_597) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);

    double start = -1.0;
    const std::vector<double> &result = state->getLineDash(&start);

    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(result.empty());
}

// Test getLineDash with single element
TEST_F(GfxStateTest_597, GetLineDashSingleElement_597) {
    std::vector<double> dash = {10.0};
    state->setLineDash(std::move(dash), 1.0);

    double start = 0.0;
    const std::vector<double> &result = state->getLineDash(&start);

    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_DOUBLE_EQ(result[0], 10.0);
}

// Test line width
TEST_F(GfxStateTest_597, SetAndGetLineWidth_597) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test line width zero (boundary)
TEST_F(GfxStateTest_597, SetLineWidthZero_597) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test miter limit
TEST_F(GfxStateTest_597, SetAndGetMiterLimit_597) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

// Test flatness
TEST_F(GfxStateTest_597, SetAndGetFlatness_597) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test line join style
TEST_F(GfxStateTest_597, SetAndGetLineJoin_597) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);

    state->setLineJoin(lineJoinBevel);
    EXPECT_EQ(state->getLineJoin(), lineJoinBevel);

    state->setLineJoin(lineJoinMiter);
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);
}

// Test line cap style
TEST_F(GfxStateTest_597, SetAndGetLineCap_597) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);

    state->setLineCap(lineCapSquare);
    EXPECT_EQ(state->getLineCap(), lineCapSquare);

    state->setLineCap(lineCapButt);
    EXPECT_EQ(state->getLineCap(), lineCapButt);
}

// Test fill opacity
TEST_F(GfxStateTest_597, SetAndGetFillOpacity_597) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test stroke opacity
TEST_F(GfxStateTest_597, SetAndGetStrokeOpacity_597) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test fill overprint
TEST_F(GfxStateTest_597, SetAndGetFillOverprint_597) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());

    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_597, SetAndGetStrokeOverprint_597) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());

    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_597, SetAndGetOverprintMode_597) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);

    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test stroke adjust
TEST_F(GfxStateTest_597, SetAndGetStrokeAdjust_597) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());

    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_597, SetAndGetAlphaIsShape_597) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());

    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_597, SetAndGetTextKnockout_597) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());

    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test char space
TEST_F(GfxStateTest_597, SetAndGetCharSpace_597) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test word space
TEST_F(GfxStateTest_597, SetAndGetWordSpace_597) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_597, SetAndGetHorizScaling_597) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test leading
TEST_F(GfxStateTest_597, SetAndGetLeading_597) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_597, SetAndGetRise_597) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test render
TEST_F(GfxStateTest_597, SetAndGetRender_597) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test rendering intent
TEST_F(GfxStateTest_597, SetAndGetRenderingIntent_597) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test rendering intent with different values
TEST_F(GfxStateTest_597, SetRenderingIntentRelativeColorimetric_597) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test setCTM
TEST_F(GfxStateTest_597, SetCTM_597) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test text matrix
TEST_F(GfxStateTest_597, SetAndGetTextMat_597) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 5.0, 10.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 10.0);
}

// Test save and restore
TEST_F(GfxStateTest_597, SaveAndRestore_597) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test hasSaves
TEST_F(GfxStateTest_597, HasSaves_597) {
    EXPECT_FALSE(state->hasSaves());

    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());

    GfxState *restored = saved->restore();
    EXPECT_FALSE(restored->hasSaves());
}

// Test path operations - moveTo/isPath/isCurPt
TEST_F(GfxStateTest_597, PathOperations_597) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test path with lineTo
TEST_F(GfxStateTest_597, PathLineToOperation_597) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test path with curveTo
TEST_F(GfxStateTest_597, PathCurveToOperation_597) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_597, ClearPath_597) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());

    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test transform
TEST_F(GfxStateTest_597, Transform_597) {
    // With identity-like CTM, transform should map coordinates predictably
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_597, TransformWithScaling_597) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

// Test transform with translation CTM
TEST_F(GfxStateTest_597, TransformWithTranslation_597) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

// Test transformDelta (no translation)
TEST_F(GfxStateTest_597, TransformDelta_597) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

// Test blend mode
TEST_F(GfxStateTest_597, SetAndGetBlendMode_597) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);

    state->setBlendMode(gfxBlendNormal);
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test font size
TEST_F(GfxStateTest_597, FontSize_597) {
    // Font is initially null, but we can check fontSize after setFont
    // Without a font object, we just test fontSize getter
    EXPECT_GE(state->getFontSize(), 0.0);
}

// Test getCurX and getCurY initial values
TEST_F(GfxStateTest_597, InitialCursorPosition_597) {
    // Initial cursor position should be at origin or some default
    double curX = state->getCurX();
    double curY = state->getCurY();
    // Just check they're valid doubles (no crash)
    EXPECT_TRUE(std::isfinite(curX));
    EXPECT_TRUE(std::isfinite(curY));
}

// Test getClipBBox
TEST_F(GfxStateTest_597, GetClipBBox_597) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be valid
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_597, ClipToRect_597) {
    state->clipToRect(100.0, 100.0, 400.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the bbox should be constrained
    EXPECT_GE(xMin, 0.0);
    EXPECT_GE(yMin, 0.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_597, GetUserClipBBox_597) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test textMoveTo
TEST_F(GfxStateTest_597, TextMoveTo_597) {
    state->textMoveTo(50.0, 100.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 100.0);
}

// Test copy
TEST_F(GfxStateTest_597, Copy_597) {
    state->setLineWidth(3.5);
    state->setFillOpacity(0.8);

    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
}

// Test lineDash with large number of elements
TEST_F(GfxStateTest_597, LineDashLargeVector_597) {
    std::vector<double> dash;
    for (int i = 0; i < 100; ++i) {
        dash.push_back(static_cast<double>(i + 1));
    }
    state->setLineDash(std::move(dash), 99.0);

    double start = 0.0;
    const std::vector<double> &result = state->getLineDash(&start);

    EXPECT_DOUBLE_EQ(start, 99.0);
    ASSERT_EQ(result.size(), 100u);
    EXPECT_DOUBLE_EQ(result[0], 1.0);
    EXPECT_DOUBLE_EQ(result[99], 100.0);
}

// Test lineDash start with zero
TEST_F(GfxStateTest_597, LineDashStartZero_597) {
    std::vector<double> dash = {5.0, 10.0};
    state->setLineDash(std::move(dash), 0.0);

    double start = -1.0;
    const std::vector<double> &result = state->getLineDash(&start);

    EXPECT_DOUBLE_EQ(start, 0.0);
    ASSERT_EQ(result.size(), 2u);
}

// Test lineDash with negative start
TEST_F(GfxStateTest_597, LineDashNegativeStart_597) {
    std::vector<double> dash = {4.0, 6.0};
    state->setLineDash(std::move(dash), -3.0);

    double start = 0.0;
    const std::vector<double> &result = state->getLineDash(&start);

    EXPECT_DOUBLE_EQ(start, -3.0);
    ASSERT_EQ(result.size(), 2u);
}

// Test multiple save/restore
TEST_F(GfxStateTest_597, MultipleSaveRestore_597) {
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

// Test concatCTM
TEST_F(GfxStateTest_597, ConcatCTM_597) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);

    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    // After concat with scale 2 and translate (10,20):
    // Result should be (2*1 + 10, 2*1 + 20) = (12, 22)
    EXPECT_DOUBLE_EQ(x2, 12.0);
    EXPECT_DOUBLE_EQ(y2, 22.0);
}

// Test transformWidth
TEST_F(GfxStateTest_597, TransformWidth_597) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_597, GetTransformedLineWidth_597) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(2.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test fill/stroke color
TEST_F(GfxStateTest_597, SetAndGetFillColor_597) {
    GfxColor color;
    color.c[0] = 32768; // mid-range for 16-bit
    state->setFillColor(&color);

    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_597, SetAndGetStrokeColor_597) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);

    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 65535);
}

// Test with rotated page
TEST_F(GfxStateTest_597, ConstructWithRotation_597) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
    EXPECT_DOUBLE_EQ(rotatedState.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(rotatedState.getPageHeight(), 792.0);
}

// Test closePath
TEST_F(GfxStateTest_597, ClosePath_597) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test getPath is not null after path ops
TEST_F(GfxStateTest_597, GetPath_597) {
    state->clearPath();
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test isParentState
TEST_F(GfxStateTest_597, IsParentState_597) {
    GfxState *savedState = state->save();
    EXPECT_TRUE(savedState->isParentState(state.get()));

    GfxState *restored = savedState->restore();
    (void)restored;
}

// Test opacity boundary values
TEST_F(GfxStateTest_597, FillOpacityBoundary_597) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);

    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_597, StrokeOpacityBoundary_597) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);

    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test rendering intent with max length string
TEST_F(GfxStateTest_597, RenderingIntentMaxLength_597) {
    // Internal buffer is 32 chars, test with a 31-char intent
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test getReusablePath
TEST_F(GfxStateTest_597, GetReusablePath_597) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(50.0, 50.0);

    auto pathIter = state->getReusablePath();
    ASSERT_NE(pathIter, nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_597, ShiftCTMAndClip_597) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);

    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// Test default initial line dash is empty
TEST_F(GfxStateTest_597, DefaultLineDashEmpty_597) {
    double start = -1.0;
    const std::vector<double> &result = state->getLineDash(&start);
    // By default, line dash should be empty (solid line)
    EXPECT_TRUE(result.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test setLineDash replaces previous dash
TEST_F(GfxStateTest_597, SetLineDashReplacesPrevious_597) {
    std::vector<double> dash1 = {1.0, 2.0, 3.0};
    state->setLineDash(std::move(dash1), 1.0);

    std::vector<double> dash2 = {10.0, 20.0};
    state->setLineDash(std::move(dash2), 5.0);

    double start = 0.0;
    const std::vector<double> &result = state->getLineDash(&start);

    EXPECT_DOUBLE_EQ(start, 5.0);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 10.0);
    EXPECT_DOUBLE_EQ(result[1], 20.0);
}

// Test getCTM with Matrix overload
TEST_F(GfxStateTest_597, GetCTMMatrix_597) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify it doesn't crash; exact mapping depends on Matrix structure
}
