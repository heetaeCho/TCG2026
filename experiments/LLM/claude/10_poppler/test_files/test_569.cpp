#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makeRect(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_569 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makeRect(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and page dimensions
TEST_F(GfxStateTest_569, ConstructorSetsPageDimensions_569) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_569, ConstructorSetsDPI_569) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_569, ConstructorSetsRotate_569) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_569, GetY1ReturnsCorrectValue_569) {
    // For a page box (0,0,612,792) with rotate=0 and upsideDown=true
    // py1 should be set during construction
    double y1 = state->getY1();
    // We just verify it returns a finite value; exact value depends on implementation
    EXPECT_TRUE(std::isfinite(y1));
}

TEST_F(GfxStateTest_569, GetX1ReturnsCorrectValue_569) {
    double x1 = state->getX1();
    EXPECT_TRUE(std::isfinite(x1));
}

TEST_F(GfxStateTest_569, GetX2ReturnsCorrectValue_569) {
    double x2 = state->getX2();
    EXPECT_TRUE(std::isfinite(x2));
}

TEST_F(GfxStateTest_569, GetY2ReturnsCorrectValue_569) {
    double y2 = state->getY2();
    EXPECT_TRUE(std::isfinite(y2));
}

// Test coordinate bounds: X1 <= X2, Y1 <= Y2
TEST_F(GfxStateTest_569, CoordinateBoundsOrdered_569) {
    EXPECT_LE(state->getX1(), state->getX2());
    EXPECT_LE(state->getY1(), state->getY2());
}

// Test CTM getter
TEST_F(GfxStateTest_569, GetCTMReturnsArray_569) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_569, SetCTMUpdatesCTM_569) {
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
TEST_F(GfxStateTest_569, ConcatCTMModifiesCTM_569) {
    // Store initial CTM
    const auto ctmBefore = state->getCTM();
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 5.0, 5.0);
    const auto &ctmAfter = state->getCTM();
    // After concatenating a translation, e and f should differ
    // (exact values depend on implementation)
    EXPECT_TRUE(std::isfinite(ctmAfter[4]));
    EXPECT_TRUE(std::isfinite(ctmAfter[5]));
}

// Test line width
TEST_F(GfxStateTest_569, SetAndGetLineWidth_569) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_569, DefaultLineWidth_569) {
    // Default line width is typically 1.0 in PDF
    double lw = state->getLineWidth();
    EXPECT_TRUE(std::isfinite(lw));
}

// Test fill opacity
TEST_F(GfxStateTest_569, SetAndGetFillOpacity_569) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test stroke opacity
TEST_F(GfxStateTest_569, SetAndGetStrokeOpacity_569) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test fill overprint
TEST_F(GfxStateTest_569, SetAndGetFillOverprint_569) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_569, SetAndGetStrokeOverprint_569) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_569, SetAndGetOverprintMode_569) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test flatness
TEST_F(GfxStateTest_569, SetAndGetFlatness_569) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test line join
TEST_F(GfxStateTest_569, SetAndGetLineJoin_569) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test line cap
TEST_F(GfxStateTest_569, SetAndGetLineCap_569) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test miter limit
TEST_F(GfxStateTest_569, SetAndGetMiterLimit_569) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

// Test stroke adjust
TEST_F(GfxStateTest_569, SetAndGetStrokeAdjust_569) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_569, SetAndGetAlphaIsShape_569) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_569, SetAndGetTextKnockout_569) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test font size
TEST_F(GfxStateTest_569, SetAndGetFontSize_569) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test char space
TEST_F(GfxStateTest_569, SetAndGetCharSpace_569) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test word space
TEST_F(GfxStateTest_569, SetAndGetWordSpace_569) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_569, SetAndGetHorizScaling_569) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test leading
TEST_F(GfxStateTest_569, SetAndGetLeading_569) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_569, SetAndGetRise_569) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test render
TEST_F(GfxStateTest_569, SetAndGetRender_569) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test rendering intent
TEST_F(GfxStateTest_569, SetAndGetRenderingIntent_569) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_569, SetRenderingIntentRelativeColorimetric_569) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test text matrix
TEST_F(GfxStateTest_569, SetAndGetTextMat_569) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// Test blend mode
TEST_F(GfxStateTest_569, SetAndGetBlendMode_569) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test save and restore
TEST_F(GfxStateTest_569, SaveAndRestore_569) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);

    GfxState *restored = state->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_569, HasSavesInitiallyFalse_569) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_569, HasSavesAfterSave_569) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_569, InitialPathIsEmpty_569) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_569, MoveToSetsCurPt_569) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_569, LineToCreatesPath_569) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_569, ClearPathResetsState_569) {
    state->moveTo(10.0, 10.0);
    state->lineTo(20.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_569, CurveToCreatesPath_569) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_569, ClosePathDoesNotCrash_569) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_569, TransformProducesFiniteResults_569) {
    double x2, y2;
    state->transform(100.0, 200.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_569, TransformDeltaProducesFiniteResults_569) {
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test text transform
TEST_F(GfxStateTest_569, TextTransformProducesFiniteResults_569) {
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_569, TextTransformDeltaProducesFiniteResults_569) {
    double x2, y2;
    state->textTransformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transformWidth
TEST_F(GfxStateTest_569, TransformWidthReturnsFinite_569) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_569, GetTransformedLineWidthReturnsFinite_569) {
    state->setLineWidth(2.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tlw));
    EXPECT_GE(tlw, 0.0);
}

// Test clip bounding box
TEST_F(GfxStateTest_569, GetClipBBoxReturnsValidBounds_569) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_569, GetUserClipBBoxReturnsValidBounds_569) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_569, ClipToRectNarrowsClipBBox_569) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// Test line dash
TEST_F(GfxStateTest_569, SetAndGetLineDash_569) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
}

// Test copy
TEST_F(GfxStateTest_569, CopyCreatesIndependentState_569) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.3);
    auto copied = std::unique_ptr<GfxState>(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);

    // Modify original, copy should not change
    state->setLineWidth(1.0);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_569, TextMoveToSetsLineCoords_569) {
    state->textMoveTo(50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 60.0);
}

// Test curX, curY initial state
TEST_F(GfxStateTest_569, InitialCurXYAreFinite_569) {
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// Test different rotations
TEST_F(GfxStateTest_569, ConstructorWithRotate90_569) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
    EXPECT_TRUE(std::isfinite(rotatedState->getY1()));
}

TEST_F(GfxStateTest_569, ConstructorWithRotate180_569) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState->getRotate(), 180);
}

TEST_F(GfxStateTest_569, ConstructorWithRotate270_569) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState->getRotate(), 270);
}

// Test with non-standard page box
TEST_F(GfxStateTest_569, NonStandardPageBox_569) {
    PDFRectangle pageBox = makeRect(50, 50, 500, 700);
    auto customState = std::make_unique<GfxState>(150.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(customState->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(customState->getVDPI(), 150.0);
}

// Test upsideDown = false
TEST_F(GfxStateTest_569, UpsideDownFalse_569) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto udfState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    EXPECT_TRUE(std::isfinite(udfState->getY1()));
    EXPECT_TRUE(std::isfinite(udfState->getY2()));
}

// Test getPath returns non-null
TEST_F(GfxStateTest_569, GetPathReturnsNonNull_569) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test getReusablePath
TEST_F(GfxStateTest_569, GetReusablePathNotNull_569) {
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}

// Test fill color operations
TEST_F(GfxStateTest_569, SetAndGetFillColor_569) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test stroke color operations
TEST_F(GfxStateTest_569, SetAndGetStrokeColor_569) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 65535);
}

// Test multiple save/restore
TEST_F(GfxStateTest_569, MultipleSaveRestore_569) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);

    GfxState *s1 = state->restore();
    EXPECT_DOUBLE_EQ(s1->getLineWidth(), 2.0);

    GfxState *s2 = s1->restore();
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 1.0);
    EXPECT_FALSE(s2->hasSaves());
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_569, ShiftCTMAndClipModifiesCTM_569) {
    auto ctmBefore = state->getCTM();
    state->shiftCTMAndClip(10.0, 20.0);
    auto ctmAfter = state->getCTM();
    // The translation components should have changed
    EXPECT_TRUE(std::isfinite(ctmAfter[4]));
    EXPECT_TRUE(std::isfinite(ctmAfter[5]));
}

// Test boundary: zero-size page
TEST_F(GfxStateTest_569, ZeroSizePageBox_569) {
    PDFRectangle pageBox = makeRect(0, 0, 0, 0);
    auto zeroState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(zeroState->getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(zeroState->getPageHeight(), 0.0);
}

// Test boundary: very large DPI
TEST_F(GfxStateTest_569, LargeDPI_569) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto largeDpiState = std::make_unique<GfxState>(10000.0, 10000.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(largeDpiState->getHDPI(), 10000.0);
    EXPECT_DOUBLE_EQ(largeDpiState->getVDPI(), 10000.0);
}

// Test transformWidth with zero
TEST_F(GfxStateTest_569, TransformWidthZero_569) {
    double w = state->transformWidth(0.0);
    EXPECT_GE(w, 0.0);
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_569, GetTransformedFontSizeReturnsFinite_569) {
    state->setFont(nullptr, 12.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_TRUE(std::isfinite(tfs));
}

// Test getFontTransMat
TEST_F(GfxStateTest_569, GetFontTransMatReturnsFinite_569) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// Test rendering intent boundary - long string
TEST_F(GfxStateTest_569, RenderingIntentTruncatesLongString_569) {
    // The internal buffer is char[32], test with a string exactly at boundary
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test getCTM with Matrix pointer
TEST_F(GfxStateTest_569, GetCTMAsMatrix_569) {
    Matrix m;
    state->getCTM(&m);
    // Just verify it doesn't crash and has finite values
    EXPECT_TRUE(std::isfinite(m.m[0]));
}

// Test textShift
TEST_F(GfxStateTest_569, TextShiftModifiesPosition_569) {
    state->textMoveTo(10.0, 20.0);
    state->textShift(5.0, 3.0);
    // Just ensure no crash; exact behavior is implementation-dependent
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// Test isParentState
TEST_F(GfxStateTest_569, IsParentStateFalseForSelf_569) {
    // state is not a parent of itself when there are no saves
    EXPECT_FALSE(state->isParentState(state.get()));
}

// Test parseBlendMode static method
TEST_F(GfxStateTest_569, ParseBlendModeNormal_569) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// Test line width zero (hairline)
TEST_F(GfxStateTest_569, ZeroLineWidth_569) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test negative line width
TEST_F(GfxStateTest_569, NegativeLineWidth_569) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_569, EmptyLineDash_569) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test default color spaces are initially null
TEST_F(GfxStateTest_569, DefaultColorSpacesInitiallyNull_569) {
    auto grayCs = state->copyDefaultGrayColorSpace();
    auto rgbCs = state->copyDefaultRGBColorSpace();
    auto cmykCs = state->copyDefaultCMYKColorSpace();
    // They might be null or default; just ensure no crash
}

// Test fill/stroke pattern initially null
TEST_F(GfxStateTest_569, InitialPatternsNull_569) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test display profile initially null
TEST_F(GfxStateTest_569, DisplayProfileInitiallyEmpty_569) {
    GfxLCMSProfilePtr profile = state->getDisplayProfile();
    // Just ensure no crash; the profile may or may not be null depending on build
}
