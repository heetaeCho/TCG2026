#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a basic GfxState with a simple page box
class GfxStateTest_668 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;  // Letter width in points
        pageBox.y2 = 792;  // Letter height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_668, ConstructionAndDPI_668) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_668, PageDimensions_668) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotate
TEST_F(GfxStateTest_668, RotateValue_668) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_668, PageBoxCoordinates_668) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default blend mode
TEST_F(GfxStateTest_668, DefaultBlendMode_668) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test default fill opacity
TEST_F(GfxStateTest_668, DefaultFillOpacity_668) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_668, DefaultStrokeOpacity_668) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_668, SetFillOpacity_668) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_668, SetStrokeOpacity_668) {
    state->setStrokeOpacity(0.25);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.25);
}

// Test default fill overprint
TEST_F(GfxStateTest_668, DefaultFillOverprint_668) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set fill overprint
TEST_F(GfxStateTest_668, SetFillOverprint_668) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_668, DefaultStrokeOverprint_668) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set stroke overprint
TEST_F(GfxStateTest_668, SetStrokeOverprint_668) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_668, DefaultOverprintMode_668) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set overprint mode
TEST_F(GfxStateTest_668, SetOverprintMode_668) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default line width
TEST_F(GfxStateTest_668, DefaultLineWidth_668) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set line width
TEST_F(GfxStateTest_668, SetLineWidth_668) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_668, DefaultFlatness_668) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set flatness
TEST_F(GfxStateTest_668, SetFlatness_668) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default line join
TEST_F(GfxStateTest_668, DefaultLineJoin_668) {
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);
}

// Test set line join
TEST_F(GfxStateTest_668, SetLineJoin_668) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test default line cap
TEST_F(GfxStateTest_668, DefaultLineCap_668) {
    EXPECT_EQ(state->getLineCap(), lineCapButt);
}

// Test set line cap
TEST_F(GfxStateTest_668, SetLineCap_668) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test default miter limit
TEST_F(GfxStateTest_668, DefaultMiterLimit_668) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set miter limit
TEST_F(GfxStateTest_668, SetMiterLimit_668) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default stroke adjust
TEST_F(GfxStateTest_668, DefaultStrokeAdjust_668) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set stroke adjust
TEST_F(GfxStateTest_668, SetStrokeAdjust_668) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_668, DefaultAlphaIsShape_668) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set alpha is shape
TEST_F(GfxStateTest_668, SetAlphaIsShape_668) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_668, DefaultTextKnockout_668) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set text knockout
TEST_F(GfxStateTest_668, SetTextKnockout_668) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default font size
TEST_F(GfxStateTest_668, DefaultFontSize_668) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default char space
TEST_F(GfxStateTest_668, DefaultCharSpace_668) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set char space
TEST_F(GfxStateTest_668, SetCharSpace_668) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test default word space
TEST_F(GfxStateTest_668, DefaultWordSpace_668) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set word space
TEST_F(GfxStateTest_668, SetWordSpace_668) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_668, DefaultHorizScaling_668) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set horiz scaling
TEST_F(GfxStateTest_668, SetHorizScaling_668) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_668, DefaultLeading_668) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set leading
TEST_F(GfxStateTest_668, SetLeading_668) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_668, DefaultRise_668) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set rise
TEST_F(GfxStateTest_668, SetRise_668) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test default render
TEST_F(GfxStateTest_668, DefaultRender_668) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set render
TEST_F(GfxStateTest_668, SetRender_668) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test set rendering intent
TEST_F(GfxStateTest_668, SetRenderingIntent_668) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test set rendering intent with long string (boundary: 32 char buffer)
TEST_F(GfxStateTest_668, SetRenderingIntentLongString_668) {
    // The buffer is 32 chars, so test with a string close to that limit
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test path operations - initial state has no path
TEST_F(GfxStateTest_668, InitialPathState_668) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test moveTo creates current point
TEST_F(GfxStateTest_668, MoveToCreatesCurPt_668) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

// Test lineTo after moveTo creates a path
TEST_F(GfxStateTest_668, LineToCreatesPath_668) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 100.0);
}

// Test curveTo
TEST_F(GfxStateTest_668, CurveTo_668) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test closePath
TEST_F(GfxStateTest_668, ClosePath_668) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closing, the current point should be back at the start of the subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test clearPath
TEST_F(GfxStateTest_668, ClearPath_668) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test save and restore
TEST_F(GfxStateTest_668, SaveAndRestore_668) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test hasSaves returns false initially
TEST_F(GfxStateTest_668, HasSavesInitially_668) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves returns true after save
TEST_F(GfxStateTest_668, HasSavesAfterSave_668) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    // Restore to clean up
    saved->restore();
}

// Test CTM getter
TEST_F(GfxStateTest_668, GetCTM_668) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_668, SetCTM_668) {
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
TEST_F(GfxStateTest_668, ConcatCTM_668) {
    // Set identity CTM first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform with identity CTM
TEST_F(GfxStateTest_668, TransformWithIdentity_668) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_668, TransformWithScaling_668) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

// Test transform with translation
TEST_F(GfxStateTest_668, TransformWithTranslation_668) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 5.0, 10.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test transformDelta (no translation component)
TEST_F(GfxStateTest_668, TransformDelta_668) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

// Test setBlendMode
TEST_F(GfxStateTest_668, SetBlendMode_668) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test text matrix
TEST_F(GfxStateTest_668, SetTextMat_668) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_668, TextMoveTo_668) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 200.0);
}

// Test set line dash
TEST_F(GfxStateTest_668, SetLineDash_668) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
}

// Test empty line dash
TEST_F(GfxStateTest_668, EmptyLineDash_668) {
    std::vector<double> dash = {};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(result.size(), 0u);
}

// Test clip bounding box
TEST_F(GfxStateTest_668, GetClipBBox_668) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should encompass the page initially
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_668, ClipToRect_668) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_668, GetUserClipBBox_668) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getPath returns non-null
TEST_F(GfxStateTest_668, GetPathNotNull_668) {
    EXPECT_NE(state->getPath(), nullptr);
}

// Test getReusablePath
TEST_F(GfxStateTest_668, GetReusablePath_668) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto reusablePath = state->getReusablePath();
    EXPECT_NE(reusablePath, nullptr);
}

// Test transformWidth
TEST_F(GfxStateTest_668, TransformWidth_668) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// Test copy
TEST_F(GfxStateTest_668, CopyState_668) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.3);
    GfxState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
    delete copied;
}

// Test construction with rotation
TEST(GfxStateConstructionTest_668, RotatedPage_668) {
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

// Test construction with different DPI
TEST(GfxStateConstructionTest_668, DifferentDPI_668) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_668, ShiftCTMAndClip_668) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test multiple save/restore
TEST_F(GfxStateTest_668, MultipleSaveRestore_668) {
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

// Test getTransformedLineWidth
TEST_F(GfxStateTest_668, GetTransformedLineWidth_668) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_GT(tw, 0.0);
}

// Test fill color set and get
TEST_F(GfxStateTest_668, SetFillColor_668) {
    GfxColor color;
    color.c[0] = 32768; // 0.5 in fixed point
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test stroke color set and get
TEST_F(GfxStateTest_668, SetStrokeColor_668) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test lineX and lineY
TEST_F(GfxStateTest_668, LineXY_668) {
    state->textMoveTo(50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 60.0);
}

// Test parseBlendMode with null object
TEST_F(GfxStateTest_668, ParseBlendModeNormal_668) {
    // Create a name object for "Normal"
    Object obj = Object(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test construction with upsideDown false
TEST(GfxStateConstructionTest_668, UpsideDownFalse_668) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 72.0);
}

// Test zero line width
TEST_F(GfxStateTest_668, ZeroLineWidth_668) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test negative coordinates in moveTo
TEST_F(GfxStateTest_668, NegativeCoordinatesMoveTo_668) {
    state->moveTo(-10.0, -20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), -10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), -20.0);
}

// Test isParentState
TEST_F(GfxStateTest_668, IsParentState_668) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
    saved->restore();
}

// Test getCTM with Matrix parameter
TEST_F(GfxStateTest_668, GetCTMMatrix_668) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should contain the same values
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test font is null initially
TEST_F(GfxStateTest_668, InitialFontNull_668) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test fill color space is not null by default (should be DeviceGray)
TEST_F(GfxStateTest_668, DefaultFillColorSpace_668) {
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test stroke color space is not null by default
TEST_F(GfxStateTest_668, DefaultStrokeColorSpace_668) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test fill pattern null by default
TEST_F(GfxStateTest_668, DefaultFillPatternNull_668) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// Test stroke pattern null by default
TEST_F(GfxStateTest_668, DefaultStrokePatternNull_668) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}
