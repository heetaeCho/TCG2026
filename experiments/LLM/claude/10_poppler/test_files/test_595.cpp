#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

#include "GfxState.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class GfxStateTest_595 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a simple page box
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;  // Letter size width in points
        pageBox.y2 = 792;  // Letter size height in points

        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_595, ConstructionAndDPI_595) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_595, PageDimensions_595) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_595, Rotation_595) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page coordinates
TEST_F(GfxStateTest_595, PageCoordinates_595) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default line width
TEST_F(GfxStateTest_595, DefaultLineWidth_595) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_595, SetLineWidth_595) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_595, DefaultFlatness_595) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test setFlatness
TEST_F(GfxStateTest_595, SetFlatness_595) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_595, DefaultMiterLimit_595) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test setMiterLimit
TEST_F(GfxStateTest_595, SetMiterLimit_595) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_595, DefaultFillOpacity_595) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setFillOpacity
TEST_F(GfxStateTest_595, SetFillOpacity_595) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test default stroke opacity
TEST_F(GfxStateTest_595, DefaultStrokeOpacity_595) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test setStrokeOpacity
TEST_F(GfxStateTest_595, SetStrokeOpacity_595) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default fill overprint
TEST_F(GfxStateTest_595, DefaultFillOverprint_595) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setFillOverprint
TEST_F(GfxStateTest_595, SetFillOverprint_595) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_595, DefaultStrokeOverprint_595) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setStrokeOverprint
TEST_F(GfxStateTest_595, SetStrokeOverprint_595) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_595, DefaultOverprintMode_595) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test setOverprintMode
TEST_F(GfxStateTest_595, SetOverprintMode_595) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_595, DefaultStrokeAdjust_595) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setStrokeAdjust
TEST_F(GfxStateTest_595, SetStrokeAdjust_595) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_595, DefaultAlphaIsShape_595) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setAlphaIsShape
TEST_F(GfxStateTest_595, SetAlphaIsShape_595) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_595, DefaultTextKnockout_595) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setTextKnockout
TEST_F(GfxStateTest_595, SetTextKnockout_595) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default font size
TEST_F(GfxStateTest_595, DefaultFontSize_595) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default char space
TEST_F(GfxStateTest_595, DefaultCharSpace_595) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test setCharSpace
TEST_F(GfxStateTest_595, SetCharSpace_595) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test default word space
TEST_F(GfxStateTest_595, DefaultWordSpace_595) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test setWordSpace
TEST_F(GfxStateTest_595, SetWordSpace_595) {
    state->setWordSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 1.5);
}

// Test default horiz scaling
TEST_F(GfxStateTest_595, DefaultHorizScaling_595) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test setHorizScaling
TEST_F(GfxStateTest_595, SetHorizScaling_595) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_595, DefaultLeading_595) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test setLeading
TEST_F(GfxStateTest_595, SetLeading_595) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_595, DefaultRise_595) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test setRise
TEST_F(GfxStateTest_595, SetRise_595) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_595, DefaultRender_595) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test setRender
TEST_F(GfxStateTest_595, SetRender_595) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default blend mode
TEST_F(GfxStateTest_595, DefaultBlendMode_595) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test setBlendMode
TEST_F(GfxStateTest_595, SetBlendMode_595) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test save and restore
TEST_F(GfxStateTest_595, SaveAndRestore_595) {
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);

    GfxState *restored = state->restore();
    // After restore, the state pointer might change
    EXPECT_NE(restored, nullptr);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_595, HasSavesInitiallyFalse_595) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_595, HasSavesAfterSave_595) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test getTransfer returns vector
TEST_F(GfxStateTest_595, GetTransferReturnsVector_595) {
    const auto &transfer = state->getTransfer();
    // Default transfer should be empty or have default functions
    // We just check it doesn't crash
    SUCCEED();
}

// Test setTransfer with empty vector
TEST_F(GfxStateTest_595, SetTransferEmpty_595) {
    std::vector<std::unique_ptr<Function>> funcs;
    state->setTransfer(std::move(funcs));
    const auto &transfer = state->getTransfer();
    EXPECT_TRUE(transfer.empty());
}

// Test CTM getter
TEST_F(GfxStateTest_595, GetCTM_595) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_595, SetCTM_595) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 0.0);
    EXPECT_DOUBLE_EQ(ctm[5], 0.0);
}

// Test concatCTM
TEST_F(GfxStateTest_595, ConcatCTM_595) {
    // Get initial CTM
    const auto &ctmBefore = state->getCTM();
    double a0 = ctmBefore[0];

    // Concatenate identity - should not change
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &ctmAfter = state->getCTM();
    EXPECT_DOUBLE_EQ(ctmAfter[0], a0);
}

// Test transform
TEST_F(GfxStateTest_595, Transform_595) {
    double x2, y2;
    state->transform(100.0, 200.0, &x2, &y2);
    // Just verify it returns without crashing and gives some values
    SUCCEED();
}

// Test transformDelta
TEST_F(GfxStateTest_595, TransformDelta_595) {
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    SUCCEED();
}

// Test path operations: moveTo, lineTo, closePath
TEST_F(GfxStateTest_595, PathOperations_595) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());

    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isCurPt());

    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_595, ClearPath_595) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());

    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test curveTo
TEST_F(GfxStateTest_595, CurveTo_595) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test getClipBBox
TEST_F(GfxStateTest_595, GetClipBBox_595) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be valid (non-empty)
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_595, GetUserClipBBox_595) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_595, ClipToRect_595) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping to rect, clip box should be constrained
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_595, SetAndGetLineDash_595) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test setLineDash with empty dash array
TEST_F(GfxStateTest_595, SetEmptyLineDash_595) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_TRUE(retrievedDash.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_595, SetLineJoin_595) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_595, SetLineCap_595) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_595, SetTextMat_595) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_595, SetRenderingIntent_595) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test setRenderingIntent with long string (boundary)
TEST_F(GfxStateTest_595, SetRenderingIntentLongString_595) {
    // The internal buffer is char[32], so setting a very long string 
    // should be handled gracefully (truncated or similar)
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test textMoveTo
TEST_F(GfxStateTest_595, TextMoveTo_595) {
    state->textMoveTo(100.0, 200.0);
    // Verify through lineX, lineY
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test getPath
TEST_F(GfxStateTest_595, GetPath_595) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test copy
TEST_F(GfxStateTest_595, Copy_595) {
    state->setLineWidth(4.0);
    state->setFillOpacity(0.7);

    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 4.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
}

// Test copy with path
TEST_F(GfxStateTest_595, CopyWithPath_595) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);

    std::unique_ptr<GfxState> copied(state->copy(true));
    EXPECT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isPath());
}

// Test copy without path
TEST_F(GfxStateTest_595, CopyWithoutPath_595) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);

    std::unique_ptr<GfxState> copied(state->copy(false));
    EXPECT_NE(copied, nullptr);
}

// Test construction with rotation
TEST_F(GfxStateTest_595, ConstructionWithRotation_595) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

// Test construction with different DPI
TEST_F(GfxStateTest_595, ConstructionWithDifferentDPI_595) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    auto highDpiState = std::make_unique<GfxState>(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState->getVDPI(), 300.0);
}

// Test default font is null
TEST_F(GfxStateTest_595, DefaultFontIsNull_595) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test default fill color space is not null
TEST_F(GfxStateTest_595, DefaultFillColorSpace_595) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // Default should be DeviceGray
    EXPECT_NE(cs, nullptr);
}

// Test default stroke color space
TEST_F(GfxStateTest_595, DefaultStrokeColorSpace_595) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test default fill pattern is null
TEST_F(GfxStateTest_595, DefaultFillPattern_595) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

// Test default stroke pattern is null
TEST_F(GfxStateTest_595, DefaultStrokePattern_595) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test getCurX and getCurY default
TEST_F(GfxStateTest_595, DefaultCurXY_595) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_595, GetTransformedLineWidth_595) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    // Should be some positive value based on CTM and line width
    EXPECT_GE(tw, 0.0);
}

// Test transformWidth
TEST_F(GfxStateTest_595, TransformWidth_595) {
    double tw = state->transformWidth(1.0);
    EXPECT_GE(tw, 0.0);
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_595, SetAndGetFillColor_595) {
    GfxColor color;
    color.c[0] = 32768; // 0.5 in fixed point
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_595, SetAndGetStrokeColor_595) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test save multiple times and restore
TEST_F(GfxStateTest_595, MultipleSaveRestore_595) {
    state->setLineWidth(1.0);
    state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(2.0);
    state->save();

    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);

    GfxState *r1 = state->restore();
    EXPECT_NE(r1, nullptr);

    GfxState *r2 = r1->restore();
    EXPECT_NE(r2, nullptr);
    EXPECT_FALSE(r2->hasSaves());
}

// Test construction with upsideDown false
TEST_F(GfxStateTest_595, ConstructionUpsideDownFalse_595) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    auto state2 = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(state2->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state2->getPageHeight(), 792.0);
}

// Test getReusablePath
TEST_F(GfxStateTest_595, GetReusablePath_595) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// Test textTransform
TEST_F(GfxStateTest_595, TextTransform_595) {
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    SUCCEED();
}

// Test textTransformDelta
TEST_F(GfxStateTest_595, TextTransformDelta_595) {
    double x2, y2;
    state->textTransformDelta(10.0, 20.0, &x2, &y2);
    SUCCEED();
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_595, ShiftCTMAndClip_595) {
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    // Just verify no crash
    EXPECT_EQ(ctm.size(), 6u);
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_595, GetCTMAsMatrix_595) {
    Matrix m;
    state->getCTM(&m);
    // Matrix should be populated
    SUCCEED();
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_595, GetTransformedFontSize_595) {
    // With no font set, font size is 0, so transformed should also be related
    double tfs = state->getTransformedFontSize();
    EXPECT_GE(tfs, 0.0);
}

// Test getFontTransMat
TEST_F(GfxStateTest_595, GetFontTransMat_595) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Should return some valid matrix values
    SUCCEED();
}

// Test isParentState
TEST_F(GfxStateTest_595, IsParentState_595) {
    GfxState *saved = state->save();
    // state is now the child, and the saved state should be its parent
    EXPECT_TRUE(state->isParentState(saved));
}

// Test textShift
TEST_F(GfxStateTest_595, TextShift_595) {
    state->textMoveTo(0.0, 0.0);
    state->textShift(10.0, 20.0);
    // Verify through getCurTextX/Y - behavior depends on implementation
    SUCCEED();
}

// Test parseBlendMode with valid normal mode
TEST_F(GfxStateTest_595, ParseBlendModeNormal_595) {
    GfxBlendMode mode;
    Object obj(objName, "Normal");
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendNormal);
}

// Test setLineWidth to zero
TEST_F(GfxStateTest_595, SetLineWidthZero_595) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test setLineWidth to negative (boundary)
TEST_F(GfxStateTest_595, SetLineWidthNegative_595) {
    state->setLineWidth(-1.0);
    // Implementation may or may not validate - we just check it doesn't crash
    SUCCEED();
}

// Test default line join
TEST_F(GfxStateTest_595, DefaultLineJoin_595) {
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);
}

// Test default line cap
TEST_F(GfxStateTest_595, DefaultLineCap_595) {
    EXPECT_EQ(state->getLineCap(), lineCapButt);
}
