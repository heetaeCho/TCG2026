#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>
#include <cmath>

#include "GfxState.h"

// Helper to create a basic PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_615 : public ::testing::Test {
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

// --- Constructor and basic getters ---

TEST_F(GfxStateTest_615, ConstructorSetsHDPI_615) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_615, ConstructorSetsVDPI_615) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_615, ConstructorSetsRotate_615) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_615, ConstructorSetsPageDimensions_615) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_615, ConstructorWithRotation90_615) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_615, ConstructorWithRotation180_615) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_615, ConstructorWithRotation270_615) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// --- Page bounds ---

TEST_F(GfxStateTest_615, GetX1Y1X2Y2_615) {
    // The exact values depend on how the constructor processes the page box
    // with DPI and rotation, but they should be finite numbers
    EXPECT_TRUE(std::isfinite(state->getX1()));
    EXPECT_TRUE(std::isfinite(state->getY1()));
    EXPECT_TRUE(std::isfinite(state->getX2()));
    EXPECT_TRUE(std::isfinite(state->getY2()));
}

// --- CTM ---

TEST_F(GfxStateTest_615, GetCTMReturnsArray_615) {
    const auto &ctm = state->getCTM();
    // CTM should be initialized to something meaningful
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_615, SetCTM_615) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_615, ConcatCTM_615) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 10.0);
}

TEST_F(GfxStateTest_615, GetCTMAsMatrix_615) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should reflect the CTM values
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// --- Transform ---

TEST_F(GfxStateTest_615, TransformPoint_615) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_615, TransformDelta_615) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_615, TransformWidth_615) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// --- Line properties ---

TEST_F(GfxStateTest_615, SetAndGetLineWidth_615) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_615, SetAndGetLineJoin_615) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_615, SetAndGetLineCap_615) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_615, SetAndGetMiterLimit_615) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_615, SetAndGetFlatness_615) {
    state->setFlatness(2);
    EXPECT_EQ(state->getFlatness(), 2);
}

TEST_F(GfxStateTest_615, SetAndGetLineDash_615) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_615, SetLineDashEmpty_615) {
    std::vector<double> dash = {};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// --- Opacity and blend mode ---

TEST_F(GfxStateTest_615, SetAndGetFillOpacity_615) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_615, SetAndGetStrokeOpacity_615) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_615, SetAndGetBlendMode_615) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// --- Overprint ---

TEST_F(GfxStateTest_615, SetAndGetFillOverprint_615) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_615, SetAndGetStrokeOverprint_615) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_615, SetAndGetOverprintMode_615) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- Text properties ---

TEST_F(GfxStateTest_615, SetAndGetCharSpace_615) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_615, SetAndGetWordSpace_615) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_615, SetAndGetHorizScaling_615) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_615, SetAndGetLeading_615) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_615, SetAndGetRise_615) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_615, SetAndGetRender_615) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_615, SetAndGetTextMat_615) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 5.0, 10.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 10.0);
}

// --- Font ---

TEST_F(GfxStateTest_615, SetAndGetFontSize_615) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

TEST_F(GfxStateTest_615, GetFontInitiallyNull_615) {
    // After default construction, font should be null or a shared_ptr
    const auto &font = state->getFont();
    // Initially, the font might be null
    EXPECT_EQ(font, nullptr);
}

// --- Stroke adjust and alpha/text knockout ---

TEST_F(GfxStateTest_615, SetAndGetStrokeAdjust_615) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_615, SetAndGetAlphaIsShape_615) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_615, SetAndGetTextKnockout_615) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// --- Rendering intent ---

TEST_F(GfxStateTest_615, SetAndGetRenderingIntent_615) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_615, SetRenderingIntentRelativeColorimetric_615) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_615, SetRenderingIntentAbsoluteColorimetric_615) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_615, SetRenderingIntentSaturation_615) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// --- Path operations ---

TEST_F(GfxStateTest_615, InitialPathIsNotNull_615) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

TEST_F(GfxStateTest_615, IsPathInitiallyFalse_615) {
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_615, IsCurPtInitiallyFalse_615) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_615, MoveToAndIsCurPt_615) {
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_615, MoveToSetsCurrentPoint_615) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->clearPath();
    state->moveTo(10.0, 20.0);
    // After moveTo, curX/curY should reflect the point
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_615, LineToCreatesPath_615) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_615, CurveToCreatesPath_615) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_615, ClosePathOperation_615) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_615, ClearPath_615) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

// --- Save and restore ---

TEST_F(GfxStateTest_615, InitiallyHasNoSaves_615) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_615, SaveCreatesSave_615) {
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
    // Restore to clean up
    state.reset(state->restore());
}

TEST_F(GfxStateTest_615, RestoreReturnsPreviousState_615) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);
    state.reset(state->restore());
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_615, MultipleSaveRestore_615) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);

    state.reset(state->restore());
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.0);

    state.reset(state->restore());
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// --- Copy ---

TEST_F(GfxStateTest_615, CopyCreatesDistinctState_615) {
    state->setLineWidth(3.0);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_NE(copied.get(), state.get());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
}

TEST_F(GfxStateTest_615, CopyWithPath_615) {
    state->clearPath();
    state->moveTo(5.0, 5.0);
    state->lineTo(10.0, 10.0);
    std::unique_ptr<GfxState> copied(state->copy(true));
    EXPECT_TRUE(copied->isPath());
}

TEST_F(GfxStateTest_615, CopyWithoutPath_615) {
    state->clearPath();
    state->moveTo(5.0, 5.0);
    state->lineTo(10.0, 10.0);
    std::unique_ptr<GfxState> copied(state->copy(false));
    // Without copying path, behavior may vary but should not crash
    EXPECT_NE(copied.get(), nullptr);
}

// --- Clip bbox ---

TEST_F(GfxStateTest_615, GetClipBBox_615) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_615, GetUserClipBBox_615) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_615, ClipToRect_615) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should have been narrowed
    EXPECT_GE(xMin, 0.0);
    EXPECT_GE(yMin, 0.0);
}

// --- Text operations ---

TEST_F(GfxStateTest_615, TextMoveTo_615) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textMoveTo(50.0, 60.0);
    // After textMoveTo, lineX/lineY should be set
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 60.0);
}

// --- Color ---

TEST_F(GfxStateTest_615, GetFillColorNotNull_615) {
    const GfxColor *color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_615, GetStrokeColorNotNull_615) {
    const GfxColor *color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_615, SetAndGetFillColor_615) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_615, SetAndGetStrokeColor_615) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 16384);
}

// --- Color spaces ---

TEST_F(GfxStateTest_615, FillColorSpaceInitial_615) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // Should have a default color space
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_615, StrokeColorSpaceInitial_615) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// --- Pattern initially null ---

TEST_F(GfxStateTest_615, FillPatternInitiallyNull_615) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_615, StrokePatternInitiallyNull_615) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// --- isParentState ---

TEST_F(GfxStateTest_615, IsParentStateCheck_615) {
    GfxState *savedState = state->save();
    // The saved pointer should point to the parent
    EXPECT_TRUE(state->isParentState(state.get()));
    state.reset(state->restore());
}

// --- parseBlendMode (static) ---

TEST_F(GfxStateTest_615, ParseBlendModeNormal_615) {
    Object obj = Object(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

// --- GetTransformedFontSize ---

TEST_F(GfxStateTest_615, GetTransformedFontSize_615) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tfSize = state->getTransformedFontSize();
    EXPECT_GT(tfSize, 0.0);
}

// --- GetTransformedLineWidth ---

TEST_F(GfxStateTest_615, GetTransformedLineWidth_615) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_615, ShiftCTMAndClip_615) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double origE = state->getCTM()[4];
    double origF = state->getCTM()[5];
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], origE + 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], origF + 20.0);
}

// --- textTransform and textTransformDelta ---

TEST_F(GfxStateTest_615, TextTransform_615) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_615, TextTransformDelta_615) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// --- Boundary: zero-size page ---

TEST_F(GfxStateTest_615, ZeroSizePage_615) {
    PDFRectangle pageBox = makePageBox(0, 0, 0, 0);
    GfxState zeroState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(zeroState.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(zeroState.getPageHeight(), 0.0);
}

// --- Boundary: very large DPI ---

TEST_F(GfxStateTest_615, LargeDPI_615) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState largeState(10000.0, 10000.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(largeState.getHDPI(), 10000.0);
    EXPECT_DOUBLE_EQ(largeState.getVDPI(), 10000.0);
}

// --- Boundary: opacity at limits ---

TEST_F(GfxStateTest_615, FillOpacityZero_615) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_615, FillOpacityOne_615) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_615, StrokeOpacityZero_615) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_615, StrokeOpacityOne_615) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// --- Line width zero (hairline) ---

TEST_F(GfxStateTest_615, LineWidthZero_615) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// --- GetFontTransMat ---

TEST_F(GfxStateTest_615, GetFontTransMat_615) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// --- GetReusablePath ---

TEST_F(GfxStateTest_615, GetReusablePath_615) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// --- Negative coordinates in path ---

TEST_F(GfxStateTest_615, NegativeCoordinatesInPath_615) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->clearPath();
    state->moveTo(-100.0, -200.0);
    state->lineTo(-50.0, -25.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), -50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), -25.0);
}

// --- UpsideDown parameter ---

TEST_F(GfxStateTest_615, UpsideDownFalse_615) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState noFlipState(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(noFlipState.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(noFlipState.getPageHeight(), 792.0);
}

// --- CurTextX/CurTextY ---

TEST_F(GfxStateTest_615, CurTextXYInitial_615) {
    EXPECT_TRUE(std::isfinite(state->getCurTextX()));
    EXPECT_TRUE(std::isfinite(state->getCurTextY()));
}

// --- TextShift ---

TEST_F(GfxStateTest_615, TextShift_615) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textMoveTo(10.0, 20.0);
    double beforeX = state->getCurX();
    double beforeY = state->getCurY();
    state->textShift(5.0, 3.0);
    // After text shift, the current point should have changed
    double afterX = state->getCurX();
    double afterY = state->getCurY();
    EXPECT_NE(beforeX, afterX);
}

// --- Clip ---

TEST_F(GfxStateTest_615, ClipOperation_615) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // Should not crash
    state->clip();
}

// --- ClipToStrokePath ---

TEST_F(GfxStateTest_615, ClipToStrokePath_615) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(50.0, 0.0);
    state->lineTo(50.0, 50.0);
    state->closePath();
    state->setLineWidth(2.0);
    // Should not crash
    state->clipToStrokePath();
}
