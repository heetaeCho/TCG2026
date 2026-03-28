#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a GfxState with default parameters
class GfxStateTest_599 : public ::testing::Test {
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

// Test initial DPI values
TEST_F(GfxStateTest_599, GetHDPI_599) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_599, GetVDPI_599) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_599, GetPageWidth_599) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_599, GetPageHeight_599) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_599, GetRotate_599) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_599, GetX1_599) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_599, GetY1_599) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_599, GetX2_599) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_599, GetY2_599) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test line join default
TEST_F(GfxStateTest_599, GetLineJoinDefault_599) {
    // Default line join is typically miter (0)
    LineJoinStyle join = state->getLineJoin();
    EXPECT_EQ(join, 0);
}

// Test set and get line join
TEST_F(GfxStateTest_599, SetLineJoin_599) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

TEST_F(GfxStateTest_599, SetLineJoinBevel_599) {
    state->setLineJoin(lineJoinBevel);
    EXPECT_EQ(state->getLineJoin(), lineJoinBevel);
}

// Test line cap
TEST_F(GfxStateTest_599, GetLineCapDefault_599) {
    LineCapStyle cap = state->getLineCap();
    EXPECT_EQ(cap, 0);
}

TEST_F(GfxStateTest_599, SetLineCap_599) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test line width
TEST_F(GfxStateTest_599, GetLineWidthDefault_599) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_599, SetLineWidth_599) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_599, SetLineWidthZero_599) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test miter limit
TEST_F(GfxStateTest_599, GetMiterLimitDefault_599) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_599, SetMiterLimit_599) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test flatness
TEST_F(GfxStateTest_599, GetFlatnessDefault_599) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_599, SetFlatness_599) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test fill opacity
TEST_F(GfxStateTest_599, GetFillOpacityDefault_599) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_599, SetFillOpacity_599) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_599, SetFillOpacityZero_599) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

// Test stroke opacity
TEST_F(GfxStateTest_599, GetStrokeOpacityDefault_599) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_599, SetStrokeOpacity_599) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test fill overprint
TEST_F(GfxStateTest_599, GetFillOverprintDefault_599) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_599, SetFillOverprint_599) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_599, GetStrokeOverprintDefault_599) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_599, SetStrokeOverprint_599) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_599, GetOverprintModeDefault_599) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_599, SetOverprintMode_599) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test stroke adjust
TEST_F(GfxStateTest_599, GetStrokeAdjustDefault_599) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_599, SetStrokeAdjust_599) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_599, GetAlphaIsShapeDefault_599) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_599, SetAlphaIsShape_599) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_599, GetTextKnockoutDefault_599) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_599, SetTextKnockout_599) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test font size
TEST_F(GfxStateTest_599, GetFontSizeDefault_599) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test char space
TEST_F(GfxStateTest_599, GetCharSpaceDefault_599) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_599, SetCharSpace_599) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test word space
TEST_F(GfxStateTest_599, GetWordSpaceDefault_599) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_599, SetWordSpace_599) {
    state->setWordSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 1.5);
}

// Test horiz scaling
TEST_F(GfxStateTest_599, GetHorizScalingDefault_599) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_599, SetHorizScaling_599) {
    state->setHorizScaling(0.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test leading
TEST_F(GfxStateTest_599, GetLeadingDefault_599) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_599, SetLeading_599) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test rise
TEST_F(GfxStateTest_599, GetRiseDefault_599) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_599, SetRise_599) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test render
TEST_F(GfxStateTest_599, GetRenderDefault_599) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_599, SetRender_599) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test blend mode
TEST_F(GfxStateTest_599, GetBlendModeDefault_599) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_599, SetBlendMode_599) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test CTM
TEST_F(GfxStateTest_599, GetCTM_599) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_599, SetCTM_599) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test text mat
TEST_F(GfxStateTest_599, SetTextMat_599) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 5.0, 10.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 10.0);
}

// Test rendering intent
TEST_F(GfxStateTest_599, SetRenderingIntent_599) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_599, SetRenderingIntentRelativeColorimetric_599) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test line dash
TEST_F(GfxStateTest_599, SetLineDash_599) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_599, SetLineDashEmpty_599) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// Test path operations
TEST_F(GfxStateTest_599, IsPathDefaultFalse_599) {
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_599, IsCurPtDefaultFalse_599) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_599, MoveToCreatesPath_599) {
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_599, LineToAfterMoveTo_599) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_599, CurveToAfterMoveTo_599) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_599, ClosePathAfterMoveTo_599) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_599, ClearPath_599) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test save and restore
TEST_F(GfxStateTest_599, SaveAndRestore_599) {
    state->setLineWidth(5.0);
    GfxState *savedState = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);
    
    GfxState *restoredState = state->restore();
    EXPECT_NE(restoredState, nullptr);
    // After restore the state should be the previous one
}

TEST_F(GfxStateTest_599, HasSavesDefaultFalse_599) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_599, HasSavesAfterSave_599) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test transform
TEST_F(GfxStateTest_599, TransformIdentityCTM_599) {
    // With default identity-like CTM for 72 DPI
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Just verify it doesn't crash and returns some value
    SUCCEED();
}

TEST_F(GfxStateTest_599, TransformDelta_599) {
    double x2, y2;
    state->transformDelta(1.0, 1.0, &x2, &y2);
    SUCCEED();
}

// Test clip bbox
TEST_F(GfxStateTest_599, GetClipBBox_599) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be valid
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_599, GetUserClipBBox_599) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_599, ClipToRect_599) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip box should be within or equal to the specified rect
    SUCCEED();
}

// Test copy
TEST_F(GfxStateTest_599, CopyState_599) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.7);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
}

// Test text move
TEST_F(GfxStateTest_599, TextMoveTo_599) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test different page rotations
TEST(GfxStateRotationTest_599, Rotate90_599) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotState.getRotate(), 90);
}

TEST(GfxStateRotationTest_599, Rotate180_599) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotState.getRotate(), 180);
}

TEST(GfxStateRotationTest_599, Rotate270_599) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotState.getRotate(), 270);
}

// Test concatCTM
TEST_F(GfxStateTest_599, ConcatCTM_599) {
    auto ctmBefore = state->getCTM();
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // identity concatenation
    auto ctmAfter = state->getCTM();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(ctmBefore[i], ctmAfter[i]);
    }
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_599, ShiftCTMAndClip_599) {
    state->shiftCTMAndClip(10.0, 20.0);
    // Verify it doesn't crash
    SUCCEED();
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_599, GetCTMMatrix_599) {
    Matrix m;
    state->getCTM(&m);
    // Just verify no crash
    SUCCEED();
}

// Test transformWidth
TEST_F(GfxStateTest_599, TransformWidth_599) {
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

TEST_F(GfxStateTest_599, TransformWidthZero_599) {
    double w = state->transformWidth(0.0);
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_599, GetTransformedLineWidth_599) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_GT(tw, 0.0);
}

// Test getFillColorSpace and getStrokeColorSpace defaults
TEST_F(GfxStateTest_599, GetFillColorSpaceDefault_599) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // Default should not be null (typically DeviceGray)
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_599, GetStrokeColorSpaceDefault_599) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test getFillPattern and getStrokePattern defaults (should be null)
TEST_F(GfxStateTest_599, GetFillPatternDefault_599) {
    GfxPattern *p = state->getFillPattern();
    EXPECT_EQ(p, nullptr);
}

TEST_F(GfxStateTest_599, GetStrokePatternDefault_599) {
    GfxPattern *p = state->getStrokePattern();
    EXPECT_EQ(p, nullptr);
}

// Test getFont default (null)
TEST_F(GfxStateTest_599, GetFontDefault_599) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getPath
TEST_F(GfxStateTest_599, GetPathNotNull_599) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test getCurX and getCurY
TEST_F(GfxStateTest_599, GetCurXYDefault_599) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test clip
TEST_F(GfxStateTest_599, Clip_599) {
    state->moveTo(10.0, 10.0);
    state->lineTo(100.0, 10.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    state->clip();
    SUCCEED();
}

// Test clipToStrokePath
TEST_F(GfxStateTest_599, ClipToStrokePath_599) {
    state->moveTo(10.0, 10.0);
    state->lineTo(100.0, 10.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    state->clipToStrokePath();
    SUCCEED();
}

// Test isParentState
TEST_F(GfxStateTest_599, IsParentState_599) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->isParentState(saved));
}

// Test getReusablePath
TEST_F(GfxStateTest_599, GetReusablePath_599) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_599, MultipleSaveRestore_599) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    
    state->restore();
    // After first restore, should be back to 2.0
    // (implementation detail, but observable)
    
    state->restore();
    // After second restore, should be back to 1.0
}

// Test different DPI values
TEST(GfxStateDPITest_599, HighDPI_599) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpi(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpi.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpi.getVDPI(), 300.0);
}

TEST(GfxStateDPITest_599, DifferentHVDPI_599) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState diffDpi(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(diffDpi.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(diffDpi.getVDPI(), 300.0);
}

// Test set fill and stroke color
TEST_F(GfxStateTest_599, SetFillColor_599) {
    GfxColor color;
    color.c[0] = 32768; // midpoint gray
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_599, SetStrokeColor_599) {
    GfxColor color;
    color.c[0] = 65535; // white in DeviceGray
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 65535);
}

// Test textShift
TEST_F(GfxStateTest_599, TextShift_599) {
    state->textMoveTo(10.0, 20.0);
    state->textShift(5.0, 3.0);
    // Verify it doesn't crash
    SUCCEED();
}

// Test upsideDown = false
TEST(GfxStateUpsideDownTest_599, UpsideDownFalse_599) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState notFlipped(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(notFlipped.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(notFlipped.getPageHeight(), 792.0);
}

// Test parseBlendMode static method
TEST(GfxStateStaticTest_599, ParseBlendModeNormal_599) {
    GfxBlendMode mode;
    Object obj;
    obj = Object(new GooString("Normal"));
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test rendering intent for CMS
TEST_F(GfxStateTest_599, GetCmsRenderingIntent_599) {
    int intent = state->getCmsRenderingIntent();
    // Default rendering intent should be a valid value
    SUCCEED();
}

// Test setRenderingIntent with various known intents
TEST_F(GfxStateTest_599, SetRenderingIntentAbsoluteColorimetric_599) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_599, SetRenderingIntentSaturation_599) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test boundary: very large line width
TEST_F(GfxStateTest_599, SetLineWidthVeryLarge_599) {
    state->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1e10);
}

// Test boundary: negative line width
TEST_F(GfxStateTest_599, SetLineWidthNegative_599) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test boundary: fill opacity clamped or not
TEST_F(GfxStateTest_599, SetFillOpacityOne_599) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test getLineX getLineY defaults
TEST_F(GfxStateTest_599, GetLineXYDefault_599) {
    EXPECT_DOUBLE_EQ(state->getLineX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 0.0);
}

// Test getCurTextX getCurTextY
TEST_F(GfxStateTest_599, GetCurTextXYDefault_599) {
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 0.0);
}
