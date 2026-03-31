#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with a simple page box
class GfxStateTest_601 : public ::testing::Test {
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

// Test default miter limit value
TEST_F(GfxStateTest_601, GetMiterLimit_DefaultValue_601) {
    double miterLimit = state->getMiterLimit();
    // Default miter limit per PDF spec is typically 10
    EXPECT_DOUBLE_EQ(miterLimit, 10.0);
}

// Test setting and getting miter limit
TEST_F(GfxStateTest_601, SetMiterLimit_NormalValue_601) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test setting miter limit to zero
TEST_F(GfxStateTest_601, SetMiterLimit_Zero_601) {
    state->setMiterLimit(0.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 0.0);
}

// Test setting miter limit to a large value
TEST_F(GfxStateTest_601, SetMiterLimit_LargeValue_601) {
    state->setMiterLimit(1000000.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 1000000.0);
}

// Test setting miter limit to minimum positive value
TEST_F(GfxStateTest_601, SetMiterLimit_SmallPositiveValue_601) {
    state->setMiterLimit(1.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 1.0);
}

// Test setting miter limit negative (edge case)
TEST_F(GfxStateTest_601, SetMiterLimit_NegativeValue_601) {
    state->setMiterLimit(-1.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), -1.0);
}

// Test that DPI values are correct
TEST_F(GfxStateTest_601, GetHDPI_601) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_601, GetVDPI_601) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_601, GetPageWidth_601) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_601, GetPageHeight_601) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_601, GetRotate_Default_601) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_601, GetX1_601) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_601, GetY1_601) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_601, GetX2_601) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_601, GetY2_601) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default line width
TEST_F(GfxStateTest_601, GetLineWidth_Default_601) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set/get line width
TEST_F(GfxStateTest_601, SetLineWidth_601) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_601, GetFlatness_Default_601) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set/get flatness
TEST_F(GfxStateTest_601, SetFlatness_601) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test default line join
TEST_F(GfxStateTest_601, GetLineJoin_Default_601) {
    EXPECT_EQ(state->getLineJoin(), 0); // miter join = 0
}

// Test set/get line join
TEST_F(GfxStateTest_601, SetLineJoin_601) {
    state->setLineJoin(static_cast<LineJoinStyle>(1));
    EXPECT_EQ(state->getLineJoin(), 1);
}

// Test default line cap
TEST_F(GfxStateTest_601, GetLineCap_Default_601) {
    EXPECT_EQ(state->getLineCap(), 0); // butt cap = 0
}

// Test set/get line cap
TEST_F(GfxStateTest_601, SetLineCap_601) {
    state->setLineCap(static_cast<LineCapStyle>(1));
    EXPECT_EQ(state->getLineCap(), 1);
}

// Test default fill opacity
TEST_F(GfxStateTest_601, GetFillOpacity_Default_601) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test set/get fill opacity
TEST_F(GfxStateTest_601, SetFillOpacity_601) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test default stroke opacity
TEST_F(GfxStateTest_601, GetStrokeOpacity_Default_601) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set/get stroke opacity
TEST_F(GfxStateTest_601, SetStrokeOpacity_601) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default fill overprint
TEST_F(GfxStateTest_601, GetFillOverprint_Default_601) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set/get fill overprint
TEST_F(GfxStateTest_601, SetFillOverprint_601) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_601, GetStrokeOverprint_Default_601) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set/get stroke overprint
TEST_F(GfxStateTest_601, SetStrokeOverprint_601) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_601, GetOverprintMode_Default_601) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set/get overprint mode
TEST_F(GfxStateTest_601, SetOverprintMode_601) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_601, GetStrokeAdjust_Default_601) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set/get stroke adjust
TEST_F(GfxStateTest_601, SetStrokeAdjust_601) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_601, GetAlphaIsShape_Default_601) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set/get alpha is shape
TEST_F(GfxStateTest_601, SetAlphaIsShape_601) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_601, GetTextKnockout_Default_601) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set/get text knockout
TEST_F(GfxStateTest_601, SetTextKnockout_601) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default font size
TEST_F(GfxStateTest_601, GetFontSize_Default_601) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default char space
TEST_F(GfxStateTest_601, GetCharSpace_Default_601) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set/get char space
TEST_F(GfxStateTest_601, SetCharSpace_601) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_601, GetWordSpace_Default_601) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set/get word space
TEST_F(GfxStateTest_601, SetWordSpace_601) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_601, GetHorizScaling_Default_601) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set/get horiz scaling
TEST_F(GfxStateTest_601, SetHorizScaling_601) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_601, GetLeading_Default_601) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set/get leading
TEST_F(GfxStateTest_601, SetLeading_601) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_601, GetRise_Default_601) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set/get rise
TEST_F(GfxStateTest_601, SetRise_601) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_601, GetRender_Default_601) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set/get render
TEST_F(GfxStateTest_601, SetRender_601) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default blend mode
TEST_F(GfxStateTest_601, GetBlendMode_Default_601) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set/get blend mode
TEST_F(GfxStateTest_601, SetBlendMode_601) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test CTM
TEST_F(GfxStateTest_601, GetCTM_601) {
    const auto &ctm = state->getCTM();
    // For 72 DPI, no rotation, upside down, the CTM should be identity-like with possible scaling
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_601, SetCTM_601) {
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
TEST_F(GfxStateTest_601, ConcatCTM_601) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform
TEST_F(GfxStateTest_601, Transform_601) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

// Test transformDelta
TEST_F(GfxStateTest_601, TransformDelta_601) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    double x2, y2;
    state->transformDelta(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test save and restore
TEST_F(GfxStateTest_601, SaveAndRestore_601) {
    state->setMiterLimit(7.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 7.0);

    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setMiterLimit(3.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 3.0);

    GfxState *restored = state->restore();
    // After restore, the state pointer may change; check the restored state
    if (restored) {
        EXPECT_DOUBLE_EQ(restored->getMiterLimit(), 7.0);
        // Update the unique_ptr to manage the restored state
        state.release();
        state.reset(restored);
    }
}

// Test hasSaves when no saves
TEST_F(GfxStateTest_601, HasSaves_NoSaves_601) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_601, HasSaves_AfterSave_601) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up
    GfxState *restored = state->restore();
    if (restored) {
        state.release();
        state.reset(restored);
    }
}

// Test path operations
TEST_F(GfxStateTest_601, IsPath_Default_601) {
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_601, IsCurPt_Default_601) {
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_601, MoveTo_CreatesPath_601) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_601, LineTo_AfterMoveTo_601) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_601, CurveTo_AfterMoveTo_601) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_601, ClosePath_AfterMoveTo_601) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_601, ClearPath_601) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

// Test setLineDash
TEST_F(GfxStateTest_601, SetLineDash_601) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test setLineDash with non-zero start
TEST_F(GfxStateTest_601, SetLineDash_WithStart_601) {
    std::vector<double> dash = {5.0};
    state->setLineDash(std::move(dash), 2.5);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_DOUBLE_EQ(result[0], 5.0);
    EXPECT_DOUBLE_EQ(start, 2.5);
}

// Test setLineDash empty
TEST_F(GfxStateTest_601, SetLineDash_Empty_601) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test getClipBBox
TEST_F(GfxStateTest_601, GetClipBBox_601) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip bbox should be initialized to page dimensions
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_601, ClipToRect_601) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// Test text mat
TEST_F(GfxStateTest_601, SetTextMat_601) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[2], 0.0);
    EXPECT_DOUBLE_EQ(textMat[3], 1.0);
    EXPECT_DOUBLE_EQ(textMat[4], 0.0);
    EXPECT_DOUBLE_EQ(textMat[5], 0.0);
}

// Test rendering intent
TEST_F(GfxStateTest_601, SetRenderingIntent_601) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test rendering intent with long string (boundary - 31 char max due to char[32])
TEST_F(GfxStateTest_601, SetRenderingIntent_MaxLength_601) {
    // "RelativeColorimetric" is 20 chars, fits fine
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test textMoveTo
TEST_F(GfxStateTest_601, TextMoveTo_601) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test copy
TEST_F(GfxStateTest_601, Copy_601) {
    state->setMiterLimit(15.0);
    state->setLineWidth(3.0);
    std::unique_ptr<GfxState> copy(state->copy());
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->getMiterLimit(), 15.0);
    EXPECT_DOUBLE_EQ(copy->getLineWidth(), 3.0);
}

// Test copy independence
TEST_F(GfxStateTest_601, Copy_Independence_601) {
    state->setMiterLimit(15.0);
    std::unique_ptr<GfxState> copy(state->copy());
    copy->setMiterLimit(20.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
    EXPECT_DOUBLE_EQ(copy->getMiterLimit(), 20.0);
}

// Test creating state with rotation
TEST_F(GfxStateTest_601, ConstructWithRotation_601) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test creating state with different DPI
TEST_F(GfxStateTest_601, ConstructWithDifferentDPI_601) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 300.0);
}

// Test transformWidth with identity CTM
TEST_F(GfxStateTest_601, TransformWidth_IdentityCTM_601) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double result = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// Test transformWidth with scaled CTM
TEST_F(GfxStateTest_601, TransformWidth_ScaledCTM_601) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double result = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(result, 10.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_601, GetTransformedLineWidth_601) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double result = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(result, 3.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_601, GetUserClipBBox_601) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test multiple miter limit changes
TEST_F(GfxStateTest_601, SetMiterLimit_Multiple_601) {
    state->setMiterLimit(1.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 1.0);
    state->setMiterLimit(100.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 100.0);
    state->setMiterLimit(0.5);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 0.5);
}

// Test fill/stroke color space defaults to null or device gray
TEST_F(GfxStateTest_601, GetFillColorSpace_Default_601) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // Should have a default color space
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_601, GetStrokeColorSpace_Default_601) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test fill/stroke pattern defaults
TEST_F(GfxStateTest_601, GetFillPattern_Default_601) {
    GfxPattern *p = state->getFillPattern();
    EXPECT_EQ(p, nullptr);
}

TEST_F(GfxStateTest_601, GetStrokePattern_Default_601) {
    GfxPattern *p = state->getStrokePattern();
    EXPECT_EQ(p, nullptr);
}

// Test font defaults
TEST_F(GfxStateTest_601, GetFont_Default_601) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getPath
TEST_F(GfxStateTest_601, GetPath_Default_601) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test curX/curY defaults
TEST_F(GfxStateTest_601, GetCurXY_Default_601) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test textMoveTo updates curTextX/curTextY
TEST_F(GfxStateTest_601, GetCurTextXY_AfterTextMoveTo_601) {
    state->textMoveTo(50.0, 60.0);
    // curTextX and curTextY should reflect the text position
    // These are in text space coordinates
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 60.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_601, ShiftCTMAndClip_601) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test multiple miter limit set and get for consistency
TEST_F(GfxStateTest_601, SetMiterLimit_Fractional_601) {
    state->setMiterLimit(3.14159);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 3.14159);
}
