#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <cstring>

class GfxStateTest_602 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a simple page box
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
    }

    PDFRectangle pageBox;

    std::unique_ptr<GfxState> createDefaultState(int rotate = 0, bool upsideDown = true) {
        return std::make_unique<GfxState>(72.0, 72.0, &pageBox, rotate, upsideDown);
    }
};

// Test construction with default parameters
TEST_F(GfxStateTest_602, ConstructionDefaultParams_602) {
    auto state = createDefaultState();
    ASSERT_NE(state, nullptr);
}

// Test getHDPI and getVDPI
TEST_F(GfxStateTest_602, GetDPI_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test different DPI values
TEST_F(GfxStateTest_602, GetDPIDifferentValues_602) {
    auto state = std::make_unique<GfxState>(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 300.0);
}

// Test page dimensions
TEST_F(GfxStateTest_602, GetPageDimensions_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_602, GetPageBounds_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotate
TEST_F(GfxStateTest_602, GetRotate_602) {
    auto state = createDefaultState(90);
    EXPECT_EQ(state->getRotate(), 90);
}

// Test rotate 0
TEST_F(GfxStateTest_602, GetRotateZero_602) {
    auto state = createDefaultState(0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test default stroke adjust
TEST_F(GfxStateTest_602, DefaultStrokeAdjust_602) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setStrokeAdjust
TEST_F(GfxStateTest_602, SetStrokeAdjust_602) {
    auto state = createDefaultState();
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test default line width
TEST_F(GfxStateTest_602, DefaultLineWidth_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test setLineWidth
TEST_F(GfxStateTest_602, SetLineWidth_602) {
    auto state = createDefaultState();
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test setLineWidth zero
TEST_F(GfxStateTest_602, SetLineWidthZero_602) {
    auto state = createDefaultState();
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test default flatness
TEST_F(GfxStateTest_602, DefaultFlatness_602) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test setFlatness
TEST_F(GfxStateTest_602, SetFlatness_602) {
    auto state = createDefaultState();
    state->setFlatness(10);
    EXPECT_EQ(state->getFlatness(), 10);
}

// Test default miter limit
TEST_F(GfxStateTest_602, DefaultMiterLimit_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test setMiterLimit
TEST_F(GfxStateTest_602, SetMiterLimit_602) {
    auto state = createDefaultState();
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_602, DefaultFillOpacity_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setFillOpacity
TEST_F(GfxStateTest_602, SetFillOpacity_602) {
    auto state = createDefaultState();
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test default stroke opacity
TEST_F(GfxStateTest_602, DefaultStrokeOpacity_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test setStrokeOpacity
TEST_F(GfxStateTest_602, SetStrokeOpacity_602) {
    auto state = createDefaultState();
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default fill overprint
TEST_F(GfxStateTest_602, DefaultFillOverprint_602) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setFillOverprint
TEST_F(GfxStateTest_602, SetFillOverprint_602) {
    auto state = createDefaultState();
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_602, DefaultStrokeOverprint_602) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setStrokeOverprint
TEST_F(GfxStateTest_602, SetStrokeOverprint_602) {
    auto state = createDefaultState();
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_602, DefaultOverprintMode_602) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test setOverprintMode
TEST_F(GfxStateTest_602, SetOverprintMode_602) {
    auto state = createDefaultState();
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default alpha is shape
TEST_F(GfxStateTest_602, DefaultAlphaIsShape_602) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setAlphaIsShape
TEST_F(GfxStateTest_602, SetAlphaIsShape_602) {
    auto state = createDefaultState();
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_602, DefaultTextKnockout_602) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setTextKnockout
TEST_F(GfxStateTest_602, SetTextKnockout_602) {
    auto state = createDefaultState();
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_602, DefaultCharSpace_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test setCharSpace
TEST_F(GfxStateTest_602, SetCharSpace_602) {
    auto state = createDefaultState();
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_602, DefaultWordSpace_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test setWordSpace
TEST_F(GfxStateTest_602, SetWordSpace_602) {
    auto state = createDefaultState();
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_602, DefaultHorizScaling_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test setHorizScaling
TEST_F(GfxStateTest_602, SetHorizScaling_602) {
    auto state = createDefaultState();
    state->setHorizScaling(0.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test default leading
TEST_F(GfxStateTest_602, DefaultLeading_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test setLeading
TEST_F(GfxStateTest_602, SetLeading_602) {
    auto state = createDefaultState();
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_602, DefaultRise_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test setRise
TEST_F(GfxStateTest_602, SetRise_602) {
    auto state = createDefaultState();
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_602, DefaultRender_602) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getRender(), 0);
}

// Test setRender
TEST_F(GfxStateTest_602, SetRender_602) {
    auto state = createDefaultState();
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default font size
TEST_F(GfxStateTest_602, DefaultFontSize_602) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default blend mode
TEST_F(GfxStateTest_602, DefaultBlendMode_602) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test setBlendMode
TEST_F(GfxStateTest_602, SetBlendMode_602) {
    auto state = createDefaultState();
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test getCTM returns 6 element array
TEST_F(GfxStateTest_602, GetCTM_602) {
    auto state = createDefaultState();
    const auto &ctm = state->getCTM();
    // CTM should be a valid 6-element array
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_602, SetCTM_602) {
    auto state = createDefaultState();
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
TEST_F(GfxStateTest_602, ConcatCTM_602) {
    auto state = createDefaultState();
    // Set identity-like CTM first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test save and restore
TEST_F(GfxStateTest_602, SaveAndRestore_602) {
    auto state = createDefaultState();
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    saved->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 5.0);

    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
}

// Test hasSaves
TEST_F(GfxStateTest_602, HasSaves_602) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->hasSaves());
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    EXPECT_FALSE(restored->hasSaves());
}

// Test path operations - initially no path
TEST_F(GfxStateTest_602, InitialPathState_602) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test moveTo creates current point
TEST_F(GfxStateTest_602, MoveToCreatesCurPt_602) {
    auto state = createDefaultState();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test lineTo after moveTo creates path
TEST_F(GfxStateTest_602, LineToCreatesPath_602) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test clearPath
TEST_F(GfxStateTest_602, ClearPath_602) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test curX and curY after moveTo
TEST_F(GfxStateTest_602, CurXYAfterMoveTo_602) {
    auto state = createDefaultState();
    state->moveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 25.0);
}

// Test closePath
TEST_F(GfxStateTest_602, ClosePath_602) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    // After closing, current point goes back to start of subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test curveTo
TEST_F(GfxStateTest_602, CurveTo_602) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 6.0);
    EXPECT_TRUE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_602, Transform_602) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transformDelta
TEST_F(GfxStateTest_602, TransformDelta_602) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 100.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_602, TransformWithScaling_602) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);  // 2*5 + 10
    EXPECT_DOUBLE_EQ(y2, 35.0);  // 3*5 + 20
}

// Test getClipBBox
TEST_F(GfxStateTest_602, GetClipBBox_602) {
    auto state = createDefaultState();
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be valid (max >= min)
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_602, ClipToRect_602) {
    auto state = createDefaultState();
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 10.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 100.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_602, GetUserClipBBox_602) {
    auto state = createDefaultState();
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_602, SetGetTextMat_602) {
    auto state = createDefaultState();
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_602, SetGetRenderingIntent_602) {
    auto state = createDefaultState();
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with different values
TEST_F(GfxStateTest_602, SetRenderingIntentRelativeColorimetric_602) {
    auto state = createDefaultState();
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_602, SetGetLineDash_602) {
    auto state = createDefaultState();
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_602, EmptyLineDash_602) {
    auto state = createDefaultState();
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test lineJoin
TEST_F(GfxStateTest_602, SetGetLineJoin_602) {
    auto state = createDefaultState();
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test lineCap
TEST_F(GfxStateTest_602, SetGetLineCap_602) {
    auto state = createDefaultState();
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test textMoveTo
TEST_F(GfxStateTest_602, TextMoveTo_602) {
    auto state = createDefaultState();
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test copy
TEST_F(GfxStateTest_602, Copy_602) {
    auto state = createDefaultState();
    state->setLineWidth(7.5);
    state->setStrokeAdjust(true);
    auto copy = std::unique_ptr<GfxState>(state->copy());
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->getLineWidth(), 7.5);
    EXPECT_TRUE(copy->getStrokeAdjust());
}

// Test that copy is independent
TEST_F(GfxStateTest_602, CopyIsIndependent_602) {
    auto state = createDefaultState();
    state->setLineWidth(7.5);
    auto copy = std::unique_ptr<GfxState>(state->copy());
    copy->setLineWidth(2.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copy->getLineWidth(), 2.0);
}

// Test getPath initially not null
TEST_F(GfxStateTest_602, GetPathNotNull_602) {
    auto state = createDefaultState();
    EXPECT_NE(state->getPath(), nullptr);
}

// Test save/restore preserves state correctly
TEST_F(GfxStateTest_602, SaveRestorePreservesMultipleProperties_602) {
    auto state = createDefaultState();
    state->setLineWidth(3.0);
    state->setStrokeAdjust(true);
    state->setFillOpacity(0.7);
    state->setCharSpace(2.0);

    GfxState *saved = state->save();
    saved->setLineWidth(10.0);
    saved->setStrokeAdjust(false);
    saved->setFillOpacity(0.2);
    saved->setCharSpace(5.0);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
    EXPECT_TRUE(restored->getStrokeAdjust());
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(restored->getCharSpace(), 2.0);
}

// Test rotation 180
TEST_F(GfxStateTest_602, Rotation180_602) {
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state->getRotate(), 180);
}

// Test rotation 270
TEST_F(GfxStateTest_602, Rotation270_602) {
    auto state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(state->getRotate(), 270);
}

// Test default font is null
TEST_F(GfxStateTest_602, DefaultFontNull_602) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getFont(), nullptr);
}

// Test default fill color space
TEST_F(GfxStateTest_602, DefaultFillColorSpace_602) {
    auto state = createDefaultState();
    GfxColorSpace *cs = state->getFillColorSpace();
    ASSERT_NE(cs, nullptr);
}

// Test default stroke color space
TEST_F(GfxStateTest_602, DefaultStrokeColorSpace_602) {
    auto state = createDefaultState();
    GfxColorSpace *cs = state->getStrokeColorSpace();
    ASSERT_NE(cs, nullptr);
}

// Test default fill pattern is null
TEST_F(GfxStateTest_602, DefaultFillPatternNull_602) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// Test default stroke pattern is null
TEST_F(GfxStateTest_602, DefaultStrokePatternNull_602) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test fill and stroke colors exist
TEST_F(GfxStateTest_602, FillAndStrokeColorsExist_602) {
    auto state = createDefaultState();
    EXPECT_NE(state->getFillColor(), nullptr);
    EXPECT_NE(state->getStrokeColor(), nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_602, ShiftCTMAndClip_602) {
    auto state = createDefaultState();
    const auto &ctmBefore = state->getCTM();
    double e_before = ctmBefore[4];
    double f_before = ctmBefore[5];
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctmAfter = state->getCTM();
    EXPECT_DOUBLE_EQ(ctmAfter[4], e_before + 10.0);
    EXPECT_DOUBLE_EQ(ctmAfter[5], f_before + 20.0);
}

// Test getTransformedLineWidth with identity CTM
TEST_F(GfxStateTest_602, GetTransformedLineWidth_602) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(2.0);
    double transformed = state->getTransformedLineWidth();
    EXPECT_GT(transformed, 0.0);
}

// Test transformWidth
TEST_F(GfxStateTest_602, TransformWidth_602) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double result = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(result, 2.0);
}

// Test multiple save operations
TEST_F(GfxStateTest_602, MultipleSaves_602) {
    auto state = createDefaultState();
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

// Test getCTM with Matrix pointer
TEST_F(GfxStateTest_602, GetCTMMatrix_602) {
    auto state = createDefaultState();
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // The matrix should reflect the CTM values
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_602, SetFillColor_602) {
    auto state = createDefaultState();
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    EXPECT_EQ(result->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_602, SetStrokeColor_602) {
    auto state = createDefaultState();
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 16384);
}

// Test isParentState
TEST_F(GfxStateTest_602, IsParentState_602) {
    auto state = createDefaultState();
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
}

// Test isParentState returns false for unrelated state
TEST_F(GfxStateTest_602, IsParentStateReturnsFalse_602) {
    auto state1 = createDefaultState();
    auto state2 = createDefaultState();
    EXPECT_FALSE(state1->isParentState(state2.get()));
}
