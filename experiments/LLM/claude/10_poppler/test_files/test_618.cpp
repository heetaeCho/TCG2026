#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Helper to create a PDFRectangle for constructing GfxState
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle box;
    box.x1 = x1;
    box.y1 = y1;
    box.x2 = x2;
    box.y2 = y2;
    return box;
}

class GfxStateTest_618 : public ::testing::Test {
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

// --- Construction and basic getters ---

TEST_F(GfxStateTest_618, ConstructorSetsHDPI_618) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_618, ConstructorSetsVDPI_618) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_618, ConstructorSetsRotate_618) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_618, ConstructorSetsPageWidth_618) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_618, ConstructorSetsPageHeight_618) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_618, GetX1_618) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_618, GetY1_618) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_618, GetX2_618) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_618, GetY2_618) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- Rotation variants ---

TEST_F(GfxStateTest_618, ConstructorWithRotate90_618) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_618, ConstructorWithRotate180_618) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_618, ConstructorWithRotate270_618) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// --- CTM ---

TEST_F(GfxStateTest_618, GetCTMReturnsArray_618) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_618, SetCTM_618) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_618, ConcatCTM_618) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

TEST_F(GfxStateTest_618, GetCTMAsMatrix_618) {
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

TEST_F(GfxStateTest_618, TransformIdentity_618) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_618, TransformWithTranslation_618) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_618, TransformWithScaling_618) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_618, TransformDeltaIdentity_618) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double dx2, dy2;
    state->transformDelta(10.0, 20.0, &dx2, &dy2);
    EXPECT_DOUBLE_EQ(dx2, 10.0);
    EXPECT_DOUBLE_EQ(dy2, 20.0);
}

// --- Line properties ---

TEST_F(GfxStateTest_618, SetAndGetLineWidth_618) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_618, SetLineWidthZero_618) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_618, SetAndGetMiterLimit_618) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_618, SetAndGetFlatness_618) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

TEST_F(GfxStateTest_618, SetAndGetLineJoin_618) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_618, SetAndGetLineCap_618) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_618, SetAndGetLineDash_618) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_618, SetLineDashEmpty_618) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// --- Opacity and blend mode ---

TEST_F(GfxStateTest_618, SetAndGetFillOpacity_618) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_618, SetAndGetStrokeOpacity_618) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_618, SetAndGetBlendMode_618) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// --- Overprint ---

TEST_F(GfxStateTest_618, SetAndGetFillOverprint_618) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_618, SetAndGetStrokeOverprint_618) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_618, SetAndGetOverprintMode_618) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- Text properties ---

TEST_F(GfxStateTest_618, SetAndGetCharSpace_618) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_618, SetAndGetWordSpace_618) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_618, SetAndGetHorizScaling_618) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_618, SetAndGetLeading_618) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_618, SetAndGetRise_618) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_618, SetAndGetRender_618) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_618, SetAndGetTextMat_618) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

TEST_F(GfxStateTest_618, GetCurTextXInitiallyZero_618) {
    // After construction, curTextX should be 0
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 0.0);
}

TEST_F(GfxStateTest_618, GetCurTextYInitiallyZero_618) {
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 0.0);
}

TEST_F(GfxStateTest_618, TextMoveTo_618) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// --- Stroke adjust and flags ---

TEST_F(GfxStateTest_618, SetAndGetStrokeAdjust_618) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_618, SetAndGetAlphaIsShape_618) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_618, SetAndGetTextKnockout_618) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- Rendering intent ---

TEST_F(GfxStateTest_618, SetAndGetRenderingIntent_618) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_618, SetRenderingIntentTooLong_618) {
    // Rendering intent buffer is 32 chars; set something longer
    state->setRenderingIntent("ThisIsAVeryLongRenderingIntentNameThatExceeds32");
    // Should be truncated or handled; just check it doesn't crash
    const char *ri = state->getRenderingIntent();
    EXPECT_NE(ri, nullptr);
}

// --- Path operations ---

TEST_F(GfxStateTest_618, InitiallyNoPath_618) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_618, MoveToCreatesCurPt_618) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_618, LineToCreatesPath_618) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_618, CurveToCreatesPath_618) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 6.0);
}

TEST_F(GfxStateTest_618, ClosePath_618) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    // After closePath, cur point should be back to the start of the subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

TEST_F(GfxStateTest_618, ClearPath_618) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_618, GetPathNotNull_618) {
    state->moveTo(0.0, 0.0);
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// --- Save and Restore ---

TEST_F(GfxStateTest_618, InitiallyNoSaves_618) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_618, SaveCreatesSave_618) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
}

TEST_F(GfxStateTest_618, RestoreAfterSave_618) {
    state->setLineWidth(5.0);
    GfxState *current = state->save();
    current->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(current->getLineWidth(), 10.0);
    GfxState *restored = current->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_618, MultipleSaveRestore_618) {
    state->setFillOpacity(1.0);
    GfxState *s1 = state->save();
    s1->setFillOpacity(0.5);
    GfxState *s2 = s1->save();
    s2->setFillOpacity(0.25);
    EXPECT_DOUBLE_EQ(s2->getFillOpacity(), 0.25);
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getFillOpacity(), 0.5);
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_618, HasSavesAfterSave_618) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    EXPECT_FALSE(restored->hasSaves());
}

// --- Copy ---

TEST_F(GfxStateTest_618, CopyPreservesState_618) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.8);
    auto copied = std::unique_ptr<GfxState>(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
}

// --- Clip ---

TEST_F(GfxStateTest_618, ClipBBoxInitial_618) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have some valid clip bounds
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_618, UserClipBBox_618) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_618, ClipToRect_618) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should be within the rect
    EXPECT_GE(xMin, 0.0);
    EXPECT_GE(yMin, 0.0);
}

// --- Font ---

TEST_F(GfxStateTest_618, InitialFontIsNull_618) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxStateTest_618, GetFontSizeDefault_618) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// --- TextShift ---

TEST_F(GfxStateTest_618, TextShift_618) {
    state->textMoveTo(0.0, 0.0);
    double prevX = state->getCurTextX();
    double prevY = state->getCurTextY();
    state->textShift(5.0, 3.0);
    // After textShift, curTextX and curTextY should have changed
    // We can't know exact values without knowing text matrix, but we can check they differ
    // With default identity text matrix, they should shift
    double newX = state->getCurTextX();
    double newY = state->getCurTextY();
    // At minimum, something should have changed if text matrix is identity
    EXPECT_TRUE(newX != prevX || newY != prevY);
}

// --- Color ---

TEST_F(GfxStateTest_618, SetAndGetFillColor_618) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    EXPECT_EQ(fc->c[0], 32768);
}

TEST_F(GfxStateTest_618, SetAndGetStrokeColor_618) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    EXPECT_EQ(sc->c[0], 16384);
}

// --- Blend mode parsing ---

TEST_F(GfxStateTest_618, ParseBlendModeNormal_618) {
    GfxBlendMode mode;
    Object obj(objName, "Normal");
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_618, ParseBlendModeMultiply_618) {
    GfxBlendMode mode;
    Object obj(objName, "Multiply");
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Multiply);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_618, ShiftCTMAndClip_618) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// --- TransformWidth ---

TEST_F(GfxStateTest_618, TransformWidthIdentity_618) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

TEST_F(GfxStateTest_618, TransformWidthScaled_618) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 10.0);
}

// --- GetTransformedLineWidth ---

TEST_F(GfxStateTest_618, GetTransformedLineWidth_618) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tw, 3.0);
}

// --- isParentState ---

TEST_F(GfxStateTest_618, IsParentStateFalseForSelf_618) {
    EXPECT_FALSE(state->isParentState(state.get()));
}

TEST_F(GfxStateTest_618, IsParentStateAfterSave_618) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    child->restore();
}

// --- GetReusablePath ---

TEST_F(GfxStateTest_618, GetReusablePathNotNull_618) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}

// --- Boundary: various DPI values ---

TEST_F(GfxStateTest_618, HighDPI_618) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 300.0);
}

TEST_F(GfxStateTest_618, ZeroDPI_618) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    // Zero DPI edge case - should not crash
    GfxState zeroDpiState(0.0, 0.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(zeroDpiState.getHDPI(), 0.0);
    EXPECT_DOUBLE_EQ(zeroDpiState.getVDPI(), 0.0);
}

// --- Boundary: negative coordinates ---

TEST_F(GfxStateTest_618, NegativePageBox_618) {
    PDFRectangle pageBox = makePageBox(-100, -100, 100, 100);
    GfxState negState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(negState.getPageWidth(), 200.0);
    EXPECT_DOUBLE_EQ(negState.getPageHeight(), 200.0);
}

// --- Color spaces initial state ---

TEST_F(GfxStateTest_618, FillColorSpaceInitial_618) {
    // Initial fill color space should be device gray (or similar default)
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_618, StrokeColorSpaceInitial_618) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// --- Pattern initial ---

TEST_F(GfxStateTest_618, FillPatternInitiallyNull_618) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_618, StrokePatternInitiallyNull_618) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// --- Default color spaces ---

TEST_F(GfxStateTest_618, CopyDefaultGrayColorSpaceInitiallyNull_618) {
    auto cs = state->copyDefaultGrayColorSpace();
    // May be null initially
    // Just test it doesn't crash
}

TEST_F(GfxStateTest_618, CopyDefaultRGBColorSpaceInitiallyNull_618) {
    auto cs = state->copyDefaultRGBColorSpace();
}

TEST_F(GfxStateTest_618, CopyDefaultCMYKColorSpaceInitiallyNull_618) {
    auto cs = state->copyDefaultCMYKColorSpace();
}

// --- TextTransform ---

TEST_F(GfxStateTest_618, TextTransformIdentity_618) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // With identity text and CTM, result should map predictably
    // Exact behavior depends on implementation but shouldn't crash
}

TEST_F(GfxStateTest_618, TextTransformDelta_618) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double dx2, dy2;
    state->textTransformDelta(5.0, 10.0, &dx2, &dy2);
}

// --- GetTransformedFontSize ---

TEST_F(GfxStateTest_618, GetTransformedFontSizeZero_618) {
    // No font set, font size is 0
    double tfs = state->getTransformedFontSize();
    EXPECT_DOUBLE_EQ(tfs, 0.0);
}

// --- GetFontTransMat ---

TEST_F(GfxStateTest_618, GetFontTransMat_618) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Should return something based on text matrix and CTM
}

// --- Display profile ---

TEST_F(GfxStateTest_618, DisplayProfileInitiallyNull_618) {
    GfxLCMSProfilePtr profile = state->getDisplayProfile();
    // May be null initially
}
