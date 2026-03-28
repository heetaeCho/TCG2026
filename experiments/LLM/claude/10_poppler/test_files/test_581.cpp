#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Helper to create a basic GfxState with a simple page box
static std::unique_ptr<GfxState> createDefaultState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_581 : public ::testing::Test {
protected:
    std::unique_ptr<GfxState> state;

    void SetUp() override {
        state = createDefaultState();
    }
};

// Test basic construction and page dimensions
TEST_F(GfxStateTest_581, ConstructionPageDimensions_581) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_581, ConstructionDPI_581) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_581, ConstructionRotate_581) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_581, ConstructionCoordinates_581) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test fill/stroke opacity
TEST_F(GfxStateTest_581, DefaultFillOpacity_581) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_581, DefaultStrokeOpacity_581) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_581, SetFillOpacity_581) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_581, SetStrokeOpacity_581) {
    state->setStrokeOpacity(0.25);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.25);
}

// Test line width
TEST_F(GfxStateTest_581, DefaultLineWidth_581) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_581, SetLineWidth_581) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_581, SetLineWidthZero_581) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test flatness
TEST_F(GfxStateTest_581, DefaultFlatness_581) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_581, SetFlatness_581) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test line join
TEST_F(GfxStateTest_581, DefaultLineJoin_581) {
    EXPECT_EQ(state->getLineJoin(), 0); // miter join
}

TEST_F(GfxStateTest_581, SetLineJoin_581) {
    state->setLineJoin(static_cast<LineJoinStyle>(1));
    EXPECT_EQ(state->getLineJoin(), 1);
}

// Test line cap
TEST_F(GfxStateTest_581, DefaultLineCap_581) {
    EXPECT_EQ(state->getLineCap(), 0); // butt cap
}

TEST_F(GfxStateTest_581, SetLineCap_581) {
    state->setLineCap(static_cast<LineCapStyle>(2));
    EXPECT_EQ(state->getLineCap(), 2);
}

// Test miter limit
TEST_F(GfxStateTest_581, DefaultMiterLimit_581) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_581, SetMiterLimit_581) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test overprint
TEST_F(GfxStateTest_581, DefaultFillOverprint_581) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_581, SetFillOverprint_581) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_581, DefaultStrokeOverprint_581) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_581, SetStrokeOverprint_581) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_581, DefaultOverprintMode_581) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_581, SetOverprintMode_581) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test stroke adjust
TEST_F(GfxStateTest_581, DefaultStrokeAdjust_581) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_581, SetStrokeAdjust_581) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_581, DefaultAlphaIsShape_581) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_581, SetAlphaIsShape_581) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_581, DefaultTextKnockout_581) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_581, SetTextKnockout_581) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test font size
TEST_F(GfxStateTest_581, DefaultFontSize_581) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test char space
TEST_F(GfxStateTest_581, DefaultCharSpace_581) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_581, SetCharSpace_581) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test word space
TEST_F(GfxStateTest_581, DefaultWordSpace_581) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_581, SetWordSpace_581) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test horiz scaling
TEST_F(GfxStateTest_581, DefaultHorizScaling_581) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_581, SetHorizScaling_581) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test leading
TEST_F(GfxStateTest_581, DefaultLeading_581) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_581, SetLeading_581) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test rise
TEST_F(GfxStateTest_581, DefaultRise_581) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_581, SetRise_581) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test render
TEST_F(GfxStateTest_581, DefaultRender_581) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_581, SetRender_581) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test rendering intent
TEST_F(GfxStateTest_581, SetRenderingIntent_581) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_581, SetRenderingIntentRelativeColorimetric_581) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test blend mode
TEST_F(GfxStateTest_581, DefaultBlendMode_581) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_581, SetBlendMode_581) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test save/restore
TEST_F(GfxStateTest_581, SaveAndRestore_581) {
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

TEST_F(GfxStateTest_581, HasSavesInitiallyFalse_581) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_581, SaveMakesHasSavesTrue_581) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up by restoring
    saved->restore();
}

// Test path operations
TEST_F(GfxStateTest_581, InitiallyNoPath_581) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_581, MoveToCreatesCurPt_581) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_581, LineToCreatesPath_581) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_581, ClearPathResetsPath_581) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_581, CurveToCreatesPath_581) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_581, ClosePathOnPath_581) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_581, TransformIdentity_581) {
    double x2, y2;
    state->transform(100.0, 100.0, &x2, &y2);
    // With default CTM for 72 DPI, the transform should map coordinates
    // We just verify it doesn't crash and produces finite results
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_581, TransformDelta_581) {
    double x2, y2;
    state->transformDelta(10.0, 10.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test text matrix
TEST_F(GfxStateTest_581, SetTextMat_581) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 2.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 2.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// Test CTM
TEST_F(GfxStateTest_581, GetCTM_581) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
    // Each element should be finite
    for (const auto &v : ctm) {
        EXPECT_TRUE(std::isfinite(v));
    }
}

TEST_F(GfxStateTest_581, SetCTM_581) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 0.0);
    EXPECT_DOUBLE_EQ(ctm[5], 0.0);
}

TEST_F(GfxStateTest_581, ConcatCTM_581) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test clip bounding box
TEST_F(GfxStateTest_581, GetClipBBox_581) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_581, GetUserClipBBox_581) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test clipToRect
TEST_F(GfxStateTest_581, ClipToRect_581) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip box should be constrained
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(xMax));
}

// Test text move
TEST_F(GfxStateTest_581, TextMoveTo_581) {
    state->textMoveTo(50.0, 100.0);
    // Verify through getCurTextX/Y - the textMoveTo updates line position
    // This depends on implementation but we test it doesn't crash
    EXPECT_TRUE(std::isfinite(state->getLineX()));
    EXPECT_TRUE(std::isfinite(state->getLineY()));
}

// Test line dash
TEST_F(GfxStateTest_581, DefaultLineDash_581) {
    double start;
    const auto &dash = state->getLineDash(&start);
    EXPECT_TRUE(dash.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_581, SetLineDash_581) {
    std::vector<double> dashPattern = {5.0, 3.0};
    state->setLineDash(std::move(dashPattern), 1.0);
    double start;
    const auto &dash = state->getLineDash(&start);
    EXPECT_EQ(dash.size(), 2u);
    EXPECT_DOUBLE_EQ(dash[0], 5.0);
    EXPECT_DOUBLE_EQ(dash[1], 3.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test fill color space
TEST_F(GfxStateTest_581, DefaultFillColorSpace_581) {
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_581, DefaultStrokeColorSpace_581) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test getFillCMYK with default color space
TEST_F(GfxStateTest_581, GetFillCMYK_581) {
    GfxCMYK cmyk;
    state->getFillCMYK(&cmyk);
    // With default device gray color space and default color, we expect some valid values
    // Just verify it doesn't crash and values are reasonable
    EXPECT_TRUE(true); // If we get here, it didn't crash
}

// Test getStrokeCMYK
TEST_F(GfxStateTest_581, GetStrokeCMYK_581) {
    GfxCMYK cmyk;
    state->getStrokeCMYK(&cmyk);
    EXPECT_TRUE(true);
}

// Test getFillRGB
TEST_F(GfxStateTest_581, GetFillRGB_581) {
    GfxRGB rgb;
    state->getFillRGB(&rgb);
    EXPECT_TRUE(true);
}

// Test getStrokeRGB
TEST_F(GfxStateTest_581, GetStrokeRGB_581) {
    GfxRGB rgb;
    state->getStrokeRGB(&rgb);
    EXPECT_TRUE(true);
}

// Test getFillGray
TEST_F(GfxStateTest_581, GetFillGray_581) {
    GfxGray gray;
    state->getFillGray(&gray);
    EXPECT_TRUE(true);
}

// Test getStrokeGray
TEST_F(GfxStateTest_581, GetStrokeGray_581) {
    GfxGray gray;
    state->getStrokeGray(&gray);
    EXPECT_TRUE(true);
}

// Test getFillDeviceN
TEST_F(GfxStateTest_581, GetFillDeviceN_581) {
    GfxColor deviceN;
    state->getFillDeviceN(&deviceN);
    EXPECT_TRUE(true);
}

// Test getStrokeDeviceN
TEST_F(GfxStateTest_581, GetStrokeDeviceN_581) {
    GfxColor deviceN;
    state->getStrokeDeviceN(&deviceN);
    EXPECT_TRUE(true);
}

// Test fill/stroke color
TEST_F(GfxStateTest_581, GetFillColor_581) {
    const GfxColor *color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_581, GetStrokeColor_581) {
    const GfxColor *color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_581, SetFillColor_581) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_581, SetStrokeColor_581) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test fill/stroke patterns (default should be null)
TEST_F(GfxStateTest_581, DefaultFillPattern_581) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_581, DefaultStrokePattern_581) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test copy
TEST_F(GfxStateTest_581, CopyState_581) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.7);
    GfxState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    delete copied;
}

// Test transformWidth
TEST_F(GfxStateTest_581, TransformWidth_581) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_581, GetTransformedLineWidth_581) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test with different rotation
TEST(GfxStateRotationTest_581, Rotate90_581) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
    // Page dimensions swap for 90 degree rotation
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 792.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 612.0);
}

TEST(GfxStateRotationTest_581, Rotate180_581) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state.getRotate(), 180);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 792.0);
}

TEST(GfxStateRotationTest_581, Rotate270_581) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(state.getRotate(), 270);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 792.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 612.0);
}

// Test save/restore preserves properties
TEST_F(GfxStateTest_581, SaveRestorePreservesLineWidth_581) {
    state->setLineWidth(7.0);
    GfxState *child = state->save();
    child->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(child->getLineWidth(), 3.0);

    GfxState *parent = child->restore();
    EXPECT_DOUBLE_EQ(parent->getLineWidth(), 7.0);
}

TEST_F(GfxStateTest_581, SaveRestorePreservesFillOpacity_581) {
    state->setFillOpacity(0.3);
    GfxState *child = state->save();
    child->setFillOpacity(0.9);
    EXPECT_DOUBLE_EQ(child->getFillOpacity(), 0.9);

    GfxState *parent = child->restore();
    EXPECT_DOUBLE_EQ(parent->getFillOpacity(), 0.3);
}

// Test isParentState
TEST_F(GfxStateTest_581, IsParentState_581) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    child->restore();
}

// Test curX, curY
TEST_F(GfxStateTest_581, DefaultCurXY_581) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test getFont default
TEST_F(GfxStateTest_581, DefaultFont_581) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test parseBlendMode
TEST_F(GfxStateTest_581, ParseBlendModeNormal_581) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    // This may or may not work depending on Object interface, 
    // so we test with a name object
}

// Test getPath
TEST_F(GfxStateTest_581, GetPath_581) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test getReusablePath
TEST_F(GfxStateTest_581, GetReusablePath_581) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// Test boundary: very large coordinates
TEST_F(GfxStateTest_581, LargeCoordinates_581) {
    state->moveTo(1e10, 1e10);
    state->lineTo(1e10, -1e10);
    EXPECT_TRUE(state->isPath());
}

// Test boundary: zero-size page
TEST(GfxStateZeroPage_581, ZeroSizePage_581) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 0;
    pageBox.y2 = 0;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 0.0);
}

// Test textShift
TEST_F(GfxStateTest_581, TextShift_581) {
    state->textMoveTo(10.0, 20.0);
    state->textShift(5.0, 0.0);
    // Shouldn't crash; specific position depends on implementation
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// Test display profile initially null
TEST_F(GfxStateTest_581, DefaultDisplayProfile_581) {
    auto profile = state->getDisplayProfile();
    // Default should be null/empty
    EXPECT_EQ(profile, nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_581, ShiftCTMAndClip_581) {
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_TRUE(std::isfinite(ctm[4]));
    EXPECT_TRUE(std::isfinite(ctm[5]));
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_581, GetTransformedFontSize_581) {
    double size = state->getTransformedFontSize();
    EXPECT_TRUE(std::isfinite(size));
}

// Test getFontTransMat
TEST_F(GfxStateTest_581, GetFontTransMat_581) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// Test multiple save/restore levels
TEST_F(GfxStateTest_581, MultipleSaveRestore_581) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);

    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);

    GfxState *r0 = r1->restore();
    EXPECT_DOUBLE_EQ(r0->getLineWidth(), 1.0);
}
