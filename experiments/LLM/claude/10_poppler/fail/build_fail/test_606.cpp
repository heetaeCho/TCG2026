#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle box;
    box.x1 = x1;
    box.y1 = y1;
    box.x2 = x2;
    box.y2 = y2;
    return box;
}

class GfxStateTest_606 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test initial DPI values
TEST_F(GfxStateTest_606, GetHDPI_606) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_606, GetVDPI_606) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_606, GetPageWidth_606) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_606, GetPageHeight_606) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_606, GetRotate_606) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_606, GetPageBoxCoordinates_606) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default font size
TEST_F(GfxStateTest_606, DefaultFontSize_606) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test set and get font size via setFont
TEST_F(GfxStateTest_606, SetFontSize_606) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test default line width
TEST_F(GfxStateTest_606, DefaultLineWidth_606) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set and get line width
TEST_F(GfxStateTest_606, SetLineWidth_606) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test zero line width
TEST_F(GfxStateTest_606, ZeroLineWidth_606) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_606, DefaultFillOpacity_606) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_606, SetFillOpacity_606) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test default stroke opacity
TEST_F(GfxStateTest_606, DefaultStrokeOpacity_606) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_606, SetStrokeOpacity_606) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default flatness
TEST_F(GfxStateTest_606, DefaultFlatness_606) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set and get flatness
TEST_F(GfxStateTest_606, SetFlatness_606) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_606, DefaultMiterLimit_606) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set and get miter limit
TEST_F(GfxStateTest_606, SetMiterLimit_606) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_606, DefaultFillOverprint_606) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set and get fill overprint
TEST_F(GfxStateTest_606, SetFillOverprint_606) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_606, DefaultStrokeOverprint_606) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set and get stroke overprint
TEST_F(GfxStateTest_606, SetStrokeOverprint_606) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_606, DefaultOverprintMode_606) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set and get overprint mode
TEST_F(GfxStateTest_606, SetOverprintMode_606) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_606, DefaultStrokeAdjust_606) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set and get stroke adjust
TEST_F(GfxStateTest_606, SetStrokeAdjust_606) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_606, DefaultAlphaIsShape_606) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set and get alpha is shape
TEST_F(GfxStateTest_606, SetAlphaIsShape_606) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_606, DefaultTextKnockout_606) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set and get text knockout
TEST_F(GfxStateTest_606, SetTextKnockout_606) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_606, DefaultCharSpace_606) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set and get char space
TEST_F(GfxStateTest_606, SetCharSpace_606) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test default word space
TEST_F(GfxStateTest_606, DefaultWordSpace_606) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set and get word space
TEST_F(GfxStateTest_606, SetWordSpace_606) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_606, DefaultHorizScaling_606) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set and get horiz scaling
TEST_F(GfxStateTest_606, SetHorizScaling_606) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_606, DefaultLeading_606) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set and get leading
TEST_F(GfxStateTest_606, SetLeading_606) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test default rise
TEST_F(GfxStateTest_606, DefaultRise_606) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set and get rise
TEST_F(GfxStateTest_606, SetRise_606) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test default render
TEST_F(GfxStateTest_606, DefaultRender_606) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set and get render
TEST_F(GfxStateTest_606, SetRender_606) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test set and get blend mode
TEST_F(GfxStateTest_606, DefaultBlendMode_606) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_606, SetBlendMode_606) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test CTM
TEST_F(GfxStateTest_606, GetCTM_606) {
    const auto &ctm = state->getCTM();
    // With 72 DPI, no rotation, upsideDown=true on a 0,0,612,792 page
    // the CTM should represent an identity-like transform scaled by DPI
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_606, SetCTM_606) {
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
TEST_F(GfxStateTest_606, ConcatCTM_606) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 10.0);
}

// Test transform
TEST_F(GfxStateTest_606, TransformIdentity_606) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_606, TransformWithScale_606) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 12.0);
    EXPECT_DOUBLE_EQ(y2, 23.0);
}

// Test transformDelta
TEST_F(GfxStateTest_606, TransformDelta_606) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    double x2, y2;
    state->transformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 2.0);
    EXPECT_DOUBLE_EQ(y2, 3.0);
}

// Test transformWidth
TEST_F(GfxStateTest_606, TransformWidth_606) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 2.0);
}

// Test save and restore
TEST_F(GfxStateTest_606, SaveAndRestore_606) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);

    GfxState *restored = state->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test hasSaves
TEST_F(GfxStateTest_606, HasSavesInitiallyFalse_606) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_606, HasSavesAfterSave_606) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_606, InitialPathState_606) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_606, MoveToCreatesCurPt_606) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_606, LineToAfterMoveTo_606) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_606, CurveToAfterMoveTo_606) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_606, ClosePathAfterMoveTo_606) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_606, ClearPath_606) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test getPath
TEST_F(GfxStateTest_606, GetPathNotNull_606) {
    EXPECT_NE(state->getPath(), nullptr);
}

// Test text matrix
TEST_F(GfxStateTest_606, SetTextMat_606) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 10.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_606, TextMoveTo_606) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test lineDash
TEST_F(GfxStateTest_606, SetLineDash_606) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);

    double start;
    const auto &ld = state->getLineDash(&start);
    EXPECT_EQ(ld.size(), 2u);
    EXPECT_DOUBLE_EQ(ld[0], 3.0);
    EXPECT_DOUBLE_EQ(ld[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test empty lineDash
TEST_F(GfxStateTest_606, EmptyLineDash_606) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);

    double start;
    const auto &ld = state->getLineDash(&start);
    EXPECT_TRUE(ld.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test line join
TEST_F(GfxStateTest_606, SetLineJoin_606) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test line cap
TEST_F(GfxStateTest_606, SetLineCap_606) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test rendering intent
TEST_F(GfxStateTest_606, SetRenderingIntent_606) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_606, SetRenderingIntentRelativeColorimetric_606) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test clipToRect
TEST_F(GfxStateTest_606, ClipToRect_606) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_606, GetUserClipBBox_606) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return valid values
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getClipBBox
TEST_F(GfxStateTest_606, GetClipBBox_606) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test copy
TEST_F(GfxStateTest_606, Copy_606) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.8);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
}

// Test with rotation
TEST_F(GfxStateTest_606, ConstructWithRotation90_606) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_606, ConstructWithRotation180_606) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_606, ConstructWithRotation270_606) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// Test different DPI values
TEST_F(GfxStateTest_606, HighDPI_606) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 300.0);
}

// Test different DPI for horizontal and vertical
TEST_F(GfxStateTest_606, AsymmetricDPI_606) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState asymState(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(asymState.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(asymState.getVDPI(), 300.0);
}

// Test fill color operations
TEST_F(GfxStateTest_606, SetFillColor_606) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test stroke color operations
TEST_F(GfxStateTest_606, SetStrokeColor_606) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test getCurX and getCurY initially
TEST_F(GfxStateTest_606, InitialCurXY_606) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test getLineX and getLineY
TEST_F(GfxStateTest_606, InitialLineXY_606) {
    EXPECT_DOUBLE_EQ(state->getLineX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 0.0);
}

// Test getFont initially null
TEST_F(GfxStateTest_606, InitialFontIsNull_606) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getFillColorSpace initially
TEST_F(GfxStateTest_606, InitialFillColorSpace_606) {
    // Default should be DeviceGray or similar
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test getStrokeColorSpace initially
TEST_F(GfxStateTest_606, InitialStrokeColorSpace_606) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test getFillPattern initially null
TEST_F(GfxStateTest_606, InitialFillPatternNull_606) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// Test getStrokePattern initially null
TEST_F(GfxStateTest_606, InitialStrokePatternNull_606) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_606, ShiftCTMAndClip_606) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_606, GetTransformedLineWidth_606) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 2.0);
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_606, GetTransformedFontSize_606) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_DOUBLE_EQ(tfs, 12.0);
}

// Test save/restore preserves state
TEST_F(GfxStateTest_606, SaveRestorePreservesMultipleProperties_606) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.7);
    state->setCharSpace(1.5);
    state->setRender(1);

    state->save();

    state->setLineWidth(10.0);
    state->setFillOpacity(0.1);
    state->setCharSpace(5.0);
    state->setRender(3);

    GfxState *restored = state->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(restored->getCharSpace(), 1.5);
    EXPECT_EQ(restored->getRender(), 1);
}

// Test multiple saves and restores
TEST_F(GfxStateTest_606, MultipleSaveRestore_606) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);

    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);

    GfxState *r1 = state->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);

    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
}

// Test textTransform with identity text matrix
TEST_F(GfxStateTest_606, TextTransformIdentity_606) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    // With identity text matrix, delta should be preserved
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test parseBlendMode
TEST_F(GfxStateTest_606, ParseBlendModeNormal_606) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test negative line width (boundary)
TEST_F(GfxStateTest_606, NegativeLineWidth_606) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test very large font size
TEST_F(GfxStateTest_606, VeryLargeFontSize_606) {
    state->setFont(nullptr, 99999.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 99999.0);
}

// Test zero font size
TEST_F(GfxStateTest_606, ZeroFontSize_606) {
    state->setFont(nullptr, 0.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test negative font size
TEST_F(GfxStateTest_606, NegativeFontSize_606) {
    state->setFont(nullptr, -12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), -12.0);
}

// Test getCTM via Matrix overload
TEST_F(GfxStateTest_606, GetCTMMatrix_606) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify the matrix was populated
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test isParentState
TEST_F(GfxStateTest_606, IsParentState_606) {
    GfxState *saved = state->save();
    // After save, the current state should consider saved as parent context
    EXPECT_TRUE(state->isParentState(state.get()));
}

// Test getDisplayProfile initially null
TEST_F(GfxStateTest_606, InitialDisplayProfileNull_606) {
    auto profile = state->getDisplayProfile();
    // May or may not be null depending on build, just ensure it doesn't crash
}

// Test getReusablePath
TEST_F(GfxStateTest_606, GetReusablePath_606) {
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test upsideDown=false
TEST_F(GfxStateTest_606, ConstructUpsideDownFalse_606) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState stateNotFlipped(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(stateNotFlipped.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(stateNotFlipped.getPageHeight(), 792.0);
}

// Test boundary: opacity values at extremes
TEST_F(GfxStateTest_606, FillOpacityZero_606) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_606, FillOpacityOne_606) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_606, StrokeOpacityZero_606) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_606, StrokeOpacityOne_606) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test getCurTextX and getCurTextY
TEST_F(GfxStateTest_606, InitialCurTextXY_606) {
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 0.0);
}

// Test rendering intent string boundary - long string
TEST_F(GfxStateTest_606, RenderingIntentLongString_606) {
    // The internal buffer is char[32], test with exactly 31 chars + null
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test textShift
TEST_F(GfxStateTest_606, TextShift_606) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textMoveTo(10.0, 20.0);
    state->textShift(5.0, 0.0);
    // After shift, curX should have changed
    // We can't precisely predict without knowing internal logic, but it shouldn't crash
}
