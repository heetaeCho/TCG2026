#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstring>

#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with default parameters
class GfxStateTest_614 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test default rendering intent
TEST_F(GfxStateTest_614, DefaultRenderingIntent_614) {
    const char *intent = state->getRenderingIntent();
    ASSERT_NE(intent, nullptr);
    // Default rendering intent should be some valid string (likely empty or a known value)
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_614, SetAndGetRenderingIntent_614) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test setRenderingIntent with different values
TEST_F(GfxStateTest_614, SetRenderingIntentAbsoluteColorimetric_614) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_614, SetRenderingIntentSaturation_614) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_614, SetRenderingIntentPerceptual_614) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test that renderingIntent buffer doesn't overflow (max 31 chars + null)
TEST_F(GfxStateTest_614, SetRenderingIntentLongString_614) {
    // The internal buffer is char[32], so strings >= 32 chars should be truncated or handled
    state->setRenderingIntent("ThisIsAVeryLongRenderingIntentStringThatExceedsBuffer");
    const char *intent = state->getRenderingIntent();
    ASSERT_NE(intent, nullptr);
    // Just verify it doesn't crash and returns something
    EXPECT_LE(strlen(intent), 31u);
}

// Test DPI getters
TEST_F(GfxStateTest_614, GetHDPI_614) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_614, GetVDPI_614) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_614, GetPageWidth_614) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_614, GetPageHeight_614) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_614, GetRotate_614) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page coordinate bounds
TEST_F(GfxStateTest_614, GetX1Y1X2Y2_614) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_614, DefaultFillOpacity_614) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_614, DefaultStrokeOpacity_614) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_614, SetFillOpacity_614) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_614, SetStrokeOpacity_614) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test default line width
TEST_F(GfxStateTest_614, DefaultLineWidth_614) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set and get line width
TEST_F(GfxStateTest_614, SetLineWidth_614) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_614, DefaultFlatness_614) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set and get flatness
TEST_F(GfxStateTest_614, SetFlatness_614) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_614, DefaultMiterLimit_614) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set and get miter limit
TEST_F(GfxStateTest_614, SetMiterLimit_614) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default overprint
TEST_F(GfxStateTest_614, DefaultFillOverprint_614) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_614, DefaultStrokeOverprint_614) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set and get fill overprint
TEST_F(GfxStateTest_614, SetFillOverprint_614) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test set and get stroke overprint
TEST_F(GfxStateTest_614, SetStrokeOverprint_614) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_614, DefaultOverprintMode_614) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_614, SetOverprintMode_614) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default char space
TEST_F(GfxStateTest_614, DefaultCharSpace_614) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_614, SetCharSpace_614) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_614, DefaultWordSpace_614) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_614, SetWordSpace_614) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_614, DefaultHorizScaling_614) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_614, SetHorizScaling_614) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_614, DefaultLeading_614) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_614, SetLeading_614) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_614, DefaultRise_614) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_614, SetRise_614) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_614, DefaultRender_614) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_614, SetRender_614) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default stroke adjust
TEST_F(GfxStateTest_614, DefaultStrokeAdjust_614) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_614, SetStrokeAdjust_614) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_614, DefaultAlphaIsShape_614) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_614, SetAlphaIsShape_614) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_614, DefaultTextKnockout_614) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_614, SetTextKnockout_614) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test set and get line join
TEST_F(GfxStateTest_614, SetLineJoin_614) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test set and get line cap
TEST_F(GfxStateTest_614, SetLineCap_614) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test save and restore
TEST_F(GfxStateTest_614, SaveAndRestore_614) {
    state->setLineWidth(5.0);
    GfxState *savedState = state->save();
    ASSERT_NE(savedState, nullptr);
    EXPECT_TRUE(state->hasSaves());
    
    savedState->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(savedState->getLineWidth(), 10.0);
    
    GfxState *restoredState = savedState->restore();
    ASSERT_NE(restoredState, nullptr);
    EXPECT_DOUBLE_EQ(restoredState->getLineWidth(), 5.0);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_614, InitialHasSaves_614) {
    EXPECT_FALSE(state->hasSaves());
}

// Test CTM getter
TEST_F(GfxStateTest_614, GetCTM_614) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_614, SetCTM_614) {
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
TEST_F(GfxStateTest_614, ConcatCTM_614) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform
TEST_F(GfxStateTest_614, Transform_614) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

// Test transformDelta
TEST_F(GfxStateTest_614, TransformDelta_614) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 3.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 6.0);
}

// Test path operations - moveTo, lineTo, isPath, isCurPt
TEST_F(GfxStateTest_614, PathOperations_614) {
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
    
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
    
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_614, CurveTo_614) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 10.0, 20.0, 20.0, 30.0, 30.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_614, ClosePath_614) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_614, ClearPath_614) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test getClipBBox
TEST_F(GfxStateTest_614, GetClipBBox_614) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should have valid extents
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_614, GetUserClipBBox_614) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_614, ClipToRect_614) {
    state->clipToRect(100.0, 200.0, 300.0, 400.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_614, SetTextMat_614) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// Test font size
TEST_F(GfxStateTest_614, DefaultFontSize_614) {
    // Initially font size may be 0 or some default
    double fs = state->getFontSize();
    EXPECT_GE(fs, 0.0);
}

// Test getCurX and getCurY
TEST_F(GfxStateTest_614, GetCurXY_614) {
    state->clearPath();
    state->moveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 25.0);
}

// Test getLineX and getLineY
TEST_F(GfxStateTest_614, GetLineXY_614) {
    // Initially these should have some value
    double lx = state->getLineX();
    double ly = state->getLineY();
    // Just verify they are accessible
    (void)lx;
    (void)ly;
}

// Test textMoveTo
TEST_F(GfxStateTest_614, TextMoveTo_614) {
    state->textMoveTo(100.0, 200.0);
    // Should affect line position
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_614, SetLineDash_614) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test setLineDash with empty dash
TEST_F(GfxStateTest_614, SetLineDashEmpty_614) {
    std::vector<double> dash = {};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test blend mode
TEST_F(GfxStateTest_614, DefaultBlendMode_614) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_614, SetBlendMode_614) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test copy
TEST_F(GfxStateTest_614, CopyState_614) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    auto *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
    delete copied;
}

// Test transformWidth
TEST_F(GfxStateTest_614, TransformWidth_614) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_614, GetTransformedLineWidth_614) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test with rotation
class GfxStateRotateTest_614 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    }

    std::unique_ptr<GfxState> state;
};

TEST_F(GfxStateRotateTest_614, RotatedState_614) {
    EXPECT_EQ(state->getRotate(), 90);
}

// Test with different DPI
class GfxStateHighDPITest_614 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(300.0, 300.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

TEST_F(GfxStateHighDPITest_614, HighDPI_614) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 300.0);
}

// Test fill and stroke color
TEST_F(GfxStateTest_614, SetFillColor_614) {
    GfxColor color;
    color.c[0] = 32768; // midpoint value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    ASSERT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

TEST_F(GfxStateTest_614, SetStrokeColor_614) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    ASSERT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 65535);
}

// Test getPath
TEST_F(GfxStateTest_614, GetPath_614) {
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test getReusablePath
TEST_F(GfxStateTest_614, GetReusablePath_614) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    ASSERT_NE(pathIter, nullptr);
}

// Test isParentState
TEST_F(GfxStateTest_614, IsParentState_614) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
}

// Test setRenderingIntent with empty string
TEST_F(GfxStateTest_614, SetRenderingIntentEmpty_614) {
    state->setRenderingIntent("");
    EXPECT_STREQ(state->getRenderingIntent(), "");
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_614, ShiftCTMAndClip_614) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// Test textShift
TEST_F(GfxStateTest_614, TextShift_614) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textShift(5.0, 10.0);
    // Verify the text position changes - use getCurTextX/Y or textMat
    // This should not crash
}

// Test save/restore chain
TEST_F(GfxStateTest_614, SaveRestoreChain_614) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);
    
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    EXPECT_TRUE(s2->hasSaves());
    
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    
    GfxState *r0 = r1->restore();
    EXPECT_DOUBLE_EQ(r0->getLineWidth(), 1.0);
}

// Test getCTM with Matrix overload
TEST_F(GfxStateTest_614, GetCTMMatrix_614) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // The matrix should be populated
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test line width zero boundary
TEST_F(GfxStateTest_614, SetLineWidthZero_614) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test opacity boundary values
TEST_F(GfxStateTest_614, SetFillOpacityBoundary_614) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_614, SetStrokeOpacityBoundary_614) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
    
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test negative line width
TEST_F(GfxStateTest_614, SetLineWidthNegative_614) {
    state->setLineWidth(-1.0);
    // The behavior may vary, but it shouldn't crash
    double lw = state->getLineWidth();
    (void)lw;
}

// Test textTransform
TEST_F(GfxStateTest_614, TextTransform_614) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // Should produce some result without crashing
}

// Test textTransformDelta
TEST_F(GfxStateTest_614, TextTransformDelta_614) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    // Should produce some result without crashing
}

// Test getCurTextX/getCurTextY
TEST_F(GfxStateTest_614, GetCurTextXY_614) {
    double tx = state->getCurTextX();
    double ty = state->getCurTextY();
    // Just verify accessibility
    (void)tx;
    (void)ty;
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_614, GetTransformedFontSize_614) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_GE(tfs, 0.0);
}

// Test getFontTransMat
TEST_F(GfxStateTest_614, GetFontTransMat_614) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Just verify it doesn't crash and produces values
}

// Test font getter (initially null)
TEST_F(GfxStateTest_614, DefaultFont_614) {
    const auto &font = state->getFont();
    // Initially font may be null
    EXPECT_EQ(font, nullptr);
}

// Test null color spaces initially
TEST_F(GfxStateTest_614, DefaultFillColorSpace_614) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // May or may not be null depending on initialization
    (void)cs;
}

TEST_F(GfxStateTest_614, DefaultStrokeColorSpace_614) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    (void)cs;
}

// Test fill and stroke pattern (initially null)
TEST_F(GfxStateTest_614, DefaultFillPattern_614) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_614, DefaultStrokePattern_614) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test display profile (initially null)
TEST_F(GfxStateTest_614, DefaultDisplayProfile_614) {
    auto profile = state->getDisplayProfile();
    // May be null
}
