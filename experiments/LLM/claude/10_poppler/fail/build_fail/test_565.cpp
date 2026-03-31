#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a GfxState with a simple page box
class GfxStateTest_565 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;  // Letter size width in points
        pageBox.y2 = 792;  // Letter size height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test DPI getters
TEST_F(GfxStateTest_565, GetHDPI_565) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_565, GetVDPI_565) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_565, GetPageWidth_565) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_565, GetPageHeight_565) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test page box coordinates
TEST_F(GfxStateTest_565, GetX1_565) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_565, GetY1_565) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_565, GetX2_565) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_565, GetY2_565) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_565, GetRotate_565) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test CTM
TEST_F(GfxStateTest_565, GetCTM_565) {
    const auto& ctm = state->getCTM();
    // With 72 DPI, no rotation, upside down, CTM should be identity-like scaled
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_565, GetCTMMatrix_565) {
    Matrix m;
    state->getCTM(&m);
    // Just verify it doesn't crash; matrix should be valid
}

// Test default line properties
TEST_F(GfxStateTest_565, DefaultLineWidth_565) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_565, DefaultMiterLimit_565) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_565, DefaultFlatness_565) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_565, DefaultLineJoin_565) {
    EXPECT_EQ(state->getLineJoin(), static_cast<LineJoinStyle>(0));
}

TEST_F(GfxStateTest_565, DefaultLineCap_565) {
    EXPECT_EQ(state->getLineCap(), static_cast<LineCapStyle>(0));
}

// Test set/get line width
TEST_F(GfxStateTest_565, SetLineWidth_565) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_565, SetLineWidthZero_565) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test set/get miter limit
TEST_F(GfxStateTest_565, SetMiterLimit_565) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test set/get flatness
TEST_F(GfxStateTest_565, SetFlatness_565) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test set/get line join
TEST_F(GfxStateTest_565, SetLineJoin_565) {
    state->setLineJoin(static_cast<LineJoinStyle>(1));
    EXPECT_EQ(state->getLineJoin(), static_cast<LineJoinStyle>(1));
}

// Test set/get line cap
TEST_F(GfxStateTest_565, SetLineCap_565) {
    state->setLineCap(static_cast<LineCapStyle>(1));
    EXPECT_EQ(state->getLineCap(), static_cast<LineCapStyle>(1));
}

// Test opacity
TEST_F(GfxStateTest_565, DefaultFillOpacity_565) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_565, DefaultStrokeOpacity_565) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_565, SetFillOpacity_565) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_565, SetStrokeOpacity_565) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test overprint
TEST_F(GfxStateTest_565, DefaultFillOverprint_565) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_565, DefaultStrokeOverprint_565) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_565, SetFillOverprint_565) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_565, SetStrokeOverprint_565) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_565, DefaultOverprintMode_565) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_565, SetOverprintMode_565) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test text properties
TEST_F(GfxStateTest_565, DefaultCharSpace_565) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_565, SetCharSpace_565) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_565, DefaultWordSpace_565) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_565, SetWordSpace_565) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_565, DefaultHorizScaling_565) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_565, SetHorizScaling_565) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_565, DefaultLeading_565) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_565, SetLeading_565) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_565, DefaultRise_565) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_565, SetRise_565) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_565, DefaultRender_565) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_565, SetRender_565) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test font size
TEST_F(GfxStateTest_565, DefaultFontSize_565) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test stroke adjust
TEST_F(GfxStateTest_565, DefaultStrokeAdjust_565) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_565, SetStrokeAdjust_565) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_565, DefaultAlphaIsShape_565) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_565, SetAlphaIsShape_565) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_565, DefaultTextKnockout_565) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_565, SetTextKnockout_565) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test blend mode
TEST_F(GfxStateTest_565, DefaultBlendMode_565) {
    EXPECT_EQ(state->getBlendMode(), static_cast<GfxBlendMode>(0));
}

TEST_F(GfxStateTest_565, SetBlendMode_565) {
    state->setBlendMode(static_cast<GfxBlendMode>(1));
    EXPECT_EQ(state->getBlendMode(), static_cast<GfxBlendMode>(1));
}

// Test rendering intent
TEST_F(GfxStateTest_565, SetRenderingIntent_565) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_565, SetRenderingIntentLongString_565) {
    // The buffer is char[32], so test with a string that's within bounds
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test text matrix
TEST_F(GfxStateTest_565, SetTextMat_565) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// Test save/restore
TEST_F(GfxStateTest_565, SaveRestore_565) {
    state->setLineWidth(5.0);
    GfxState* saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
    
    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);
    
    GfxState* restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_565, HasSavesInitiallyFalse_565) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_565, SaveCreatesSaveState_565) {
    GfxState* saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up: restore to avoid leaks
    saved->restore();
}

// Test path operations
TEST_F(GfxStateTest_565, InitiallyNoPath_565) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_565, MoveToCreatesCurPt_565) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_565, LineToCreatesPath_565) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_565, ClearPathResetsState_565) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_565, CurveToCreatesPath_565) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_565, ClosePathAfterLines_565) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_565, TransformIdentityCTM_565) {
    // Default CTM with 72 DPI, page 612x792, rotate 0, upside down
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Just ensure it doesn't crash and produces some output
    // The exact values depend on internal CTM setup
}

TEST_F(GfxStateTest_565, TransformDelta_565) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    // Just ensure it doesn't crash
}

// Test setCTM
TEST_F(GfxStateTest_565, SetCTM_565) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 1.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 1.0);
    EXPECT_DOUBLE_EQ(ctm[4], 0.0);
    EXPECT_DOUBLE_EQ(ctm[5], 0.0);
}

TEST_F(GfxStateTest_565, ConcatCTM_565) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test line dash
TEST_F(GfxStateTest_565, SetLineDash_565) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
}

TEST_F(GfxStateTest_565, SetLineDashEmpty_565) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// Test clip bounding box
TEST_F(GfxStateTest_565, GetClipBBox_565) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After initialization, clip should encompass some region
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_565, GetUserClipBBox_565) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_565, ClipToRect_565) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip box should be constrained
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test different DPI values
TEST(GfxStateConstructorTest_565, DifferentDPI_565) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test with rotation
TEST(GfxStateConstructorTest_565, WithRotation90_565) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
}

TEST(GfxStateConstructorTest_565, WithRotation180_565) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state.getRotate(), 180);
}

TEST(GfxStateConstructorTest_565, WithRotation270_565) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(state.getRotate(), 270);
}

// Test not upside down
TEST(GfxStateConstructorTest_565, NotUpsideDown_565) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 792.0);
}

// Test text operations
TEST_F(GfxStateTest_565, TextMoveTo_565) {
    state->textMoveTo(10.0, 20.0);
    // Verify line position is updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test copy
TEST_F(GfxStateTest_565, CopyState_565) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.7);
    auto copy = state->copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copy->getFillOpacity(), 0.7);
    delete copy;
}

// Test transformWidth
TEST_F(GfxStateTest_565, TransformWidth_565) {
    double w = state->transformWidth(1.0);
    EXPECT_GE(w, 0.0);
}

TEST_F(GfxStateTest_565, TransformWidthZero_565) {
    double w = state->transformWidth(0.0);
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_565, GetTransformedLineWidth_565) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_GE(tw, 0.0);
}

// Test fill/stroke color space (nullptr initially or device gray)
TEST_F(GfxStateTest_565, InitialFillColorSpace_565) {
    GfxColorSpace* cs = state->getFillColorSpace();
    // Should have a default color space
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_565, InitialStrokeColorSpace_565) {
    GfxColorSpace* cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test fill/stroke pattern (nullptr initially)
TEST_F(GfxStateTest_565, InitialFillPattern_565) {
    GfxPattern* pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_565, InitialStrokePattern_565) {
    GfxPattern* pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test font (nullptr initially)
TEST_F(GfxStateTest_565, InitialFont_565) {
    const auto& font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getPath
TEST_F(GfxStateTest_565, GetPathNotNull_565) {
    const GfxPath* path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test curX/curY defaults
TEST_F(GfxStateTest_565, DefaultCurXY_565) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_565, ShiftCTMAndClip_565) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test multiple save/restore chain
TEST_F(GfxStateTest_565, MultipleSaveRestore_565) {
    state->setLineWidth(1.0);
    GfxState* s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState* s2 = s1->save();
    s2->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    
    GfxState* r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    
    GfxState* r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
}

// Test isParentState
TEST_F(GfxStateTest_565, IsParentState_565) {
    GfxState* saved = state->save();
    EXPECT_TRUE(state->isParentState(saved));
    saved->restore();
}

// Test setFillColor/getFillColor
TEST_F(GfxStateTest_565, SetFillColor_565) {
    GfxColor color;
    color.c[0] = 32768; // ~0.5 in fixed point
    state->setFillColor(&color);
    const GfxColor* fc = state->getFillColor();
    ASSERT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

// Test setStrokeColor/getStrokeColor
TEST_F(GfxStateTest_565, SetStrokeColor_565) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor* sc = state->getStrokeColor();
    ASSERT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 16384);
}

// Test text transform
TEST_F(GfxStateTest_565, TextTransform_565) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // Should not crash; values depend on combined CTM and text mat
}

TEST_F(GfxStateTest_565, TextTransformDelta_565) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(1.0, 1.0, &x2, &y2);
    // Should not crash
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_565, GetTransformedFontSize_565) {
    double fsize = state->getTransformedFontSize();
    EXPECT_GE(fsize, 0.0);
}

// Test getFontTransMat
TEST_F(GfxStateTest_565, GetFontTransMat_565) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Should not crash
}

// Test textShift
TEST_F(GfxStateTest_565, TextShift_565) {
    state->textMoveTo(0.0, 0.0);
    state->textShift(5.0, 0.0);
    // Should update text position
}

// Test getReusablePath
TEST_F(GfxStateTest_565, GetReusablePath_565) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// Boundary test: very large coordinates
TEST_F(GfxStateTest_565, LargeCoordinates_565) {
    state->moveTo(1e10, 1e10);
    state->lineTo(1e10 + 1.0, 1e10 + 1.0);
    EXPECT_TRUE(state->isPath());
}

// Boundary test: negative coordinates
TEST_F(GfxStateTest_565, NegativeCoordinates_565) {
    state->moveTo(-100.0, -200.0);
    state->lineTo(-50.0, -100.0);
    EXPECT_TRUE(state->isPath());
}

// Test zero-size page
TEST(GfxStateConstructorTest_565, ZeroSizePage_565) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 0;
    pageBox.y2 = 0;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 0.0);
}

// Test non-origin page box
TEST(GfxStateConstructorTest_565, NonOriginPageBox_565) {
    PDFRectangle pageBox;
    pageBox.x1 = 100;
    pageBox.y1 = 200;
    pageBox.x2 = 500;
    pageBox.y2 = 700;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 400.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 500.0);
}
