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

class GfxStateTest_594 : public ::testing::Test {
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

TEST_F(GfxStateTest_594, ConstructorSetsHDPI_594) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_594, ConstructorSetsVDPI_594) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_594, ConstructorSetsRotate_594) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_594, ConstructorSetsPageDimensions_594) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_594, ConstructorSetsPageBox_594) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- Rotation variants ---

TEST_F(GfxStateTest_594, ConstructorWithRotation90_594) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_594, ConstructorWithRotation180_594) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_594, ConstructorWithRotation270_594) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// --- Overprint mode ---

TEST_F(GfxStateTest_594, DefaultOverprintMode_594) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_594, SetOverprintMode_594) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

TEST_F(GfxStateTest_594, SetOverprintModeMultipleTimes_594) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// --- Fill/Stroke opacity ---

TEST_F(GfxStateTest_594, DefaultFillOpacity_594) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_594, DefaultStrokeOpacity_594) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_594, SetFillOpacity_594) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_594, SetStrokeOpacity_594) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

TEST_F(GfxStateTest_594, SetFillOpacityZero_594) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_594, SetStrokeOpacityZero_594) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// --- Fill/Stroke overprint ---

TEST_F(GfxStateTest_594, DefaultFillOverprint_594) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_594, DefaultStrokeOverprint_594) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_594, SetFillOverprint_594) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_594, SetStrokeOverprint_594) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// --- Line width ---

TEST_F(GfxStateTest_594, DefaultLineWidth_594) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_594, SetLineWidth_594) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_594, SetLineWidthZero_594) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// --- Flatness ---

TEST_F(GfxStateTest_594, DefaultFlatness_594) {
    EXPECT_EQ(state->getFlatness(), 0);
}

TEST_F(GfxStateTest_594, SetFlatness_594) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// --- Line join ---

TEST_F(GfxStateTest_594, DefaultLineJoin_594) {
    EXPECT_EQ(state->getLineJoin(), 0); // miter join = 0
}

TEST_F(GfxStateTest_594, SetLineJoin_594) {
    state->setLineJoin(static_cast<LineJoinStyle>(1)); // round join
    EXPECT_EQ(state->getLineJoin(), 1);
}

// --- Line cap ---

TEST_F(GfxStateTest_594, DefaultLineCap_594) {
    EXPECT_EQ(state->getLineCap(), 0); // butt cap = 0
}

TEST_F(GfxStateTest_594, SetLineCap_594) {
    state->setLineCap(static_cast<LineCapStyle>(1)); // round cap
    EXPECT_EQ(state->getLineCap(), 1);
}

// --- Miter limit ---

TEST_F(GfxStateTest_594, DefaultMiterLimit_594) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_594, SetMiterLimit_594) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// --- Stroke adjust ---

TEST_F(GfxStateTest_594, DefaultStrokeAdjust_594) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_594, SetStrokeAdjust_594) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// --- Alpha is shape ---

TEST_F(GfxStateTest_594, DefaultAlphaIsShape_594) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_594, SetAlphaIsShape_594) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// --- Text knockout ---

TEST_F(GfxStateTest_594, DefaultTextKnockout_594) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_594, SetTextKnockout_594) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- Font size ---

TEST_F(GfxStateTest_594, DefaultFontSize_594) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// --- Char space ---

TEST_F(GfxStateTest_594, DefaultCharSpace_594) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_594, SetCharSpace_594) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// --- Word space ---

TEST_F(GfxStateTest_594, DefaultWordSpace_594) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_594, SetWordSpace_594) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// --- Horizontal scaling ---

TEST_F(GfxStateTest_594, DefaultHorizScaling_594) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_594, SetHorizScaling_594) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// --- Leading ---

TEST_F(GfxStateTest_594, DefaultLeading_594) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_594, SetLeading_594) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// --- Rise ---

TEST_F(GfxStateTest_594, DefaultRise_594) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_594, SetRise_594) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// --- Render ---

TEST_F(GfxStateTest_594, DefaultRender_594) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_594, SetRender_594) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// --- Rendering intent ---

TEST_F(GfxStateTest_594, SetRenderingIntent_594) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_594, SetRenderingIntentRelativeColorimetric_594) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_594, SetRenderingIntentSaturation_594) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_594, SetRenderingIntentAbsoluteColorimetric_594) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// --- CTM ---

TEST_F(GfxStateTest_594, GetCTM_594) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_594, SetCTM_594) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_594, ConcatCTM_594) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // identity
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// --- Transform ---

TEST_F(GfxStateTest_594, TransformWithIdentityCTM_594) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_594, TransformDeltaWithIdentityCTM_594) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transformDelta(5.0, 3.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 3.0);
}

TEST_F(GfxStateTest_594, TransformWithScaleCTM_594) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 2.0 * 10.0 + 100.0);
    EXPECT_DOUBLE_EQ(y2, 3.0 * 20.0 + 200.0);
}

// --- Path operations ---

TEST_F(GfxStateTest_594, DefaultPathIsEmpty_594) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_594, MoveToCreatesCurrentPoint_594) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_594, LineToAfterMoveTo_594) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_594, CurveToAfterMoveTo_594) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_594, ClosePathAfterMoveTo_594) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_594, ClearPath_594) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// --- Save and restore ---

TEST_F(GfxStateTest_594, SaveAndRestore_594) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_594, HasSavesInitiallyFalse_594) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_594, HasSavesAfterSave_594) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up
    saved->restore();
}

// --- Blend mode ---

TEST_F(GfxStateTest_594, DefaultBlendMode_594) {
    EXPECT_EQ(state->getBlendMode(), static_cast<GfxBlendMode>(0)); // Normal
}

TEST_F(GfxStateTest_594, SetBlendMode_594) {
    state->setBlendMode(static_cast<GfxBlendMode>(1));
    EXPECT_EQ(state->getBlendMode(), static_cast<GfxBlendMode>(1));
}

// --- Text mat ---

TEST_F(GfxStateTest_594, SetTextMat_594) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 2.0);
    EXPECT_DOUBLE_EQ(textMat[2], 3.0);
    EXPECT_DOUBLE_EQ(textMat[3], 4.0);
    EXPECT_DOUBLE_EQ(textMat[4], 5.0);
    EXPECT_DOUBLE_EQ(textMat[5], 6.0);
}

// --- Line dash ---

TEST_F(GfxStateTest_594, SetLineDash_594) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_594, SetLineDashEmpty_594) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// --- Clip bbox ---

TEST_F(GfxStateTest_594, GetClipBBox_594) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have reasonable clip bbox after construction
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_594, GetUserClipBBox_594) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_594, ClipToRect_594) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Text position ---

TEST_F(GfxStateTest_594, TextMoveTo_594) {
    state->textMoveTo(10.0, 20.0);
    // We can read back lineX and lineY after textMoveTo
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// --- Copy ---

TEST_F(GfxStateTest_594, CopyState_594) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.5);
    auto copy = state->copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copy->getFillOpacity(), 0.5);
    delete copy;
}

// --- TransformWidth ---

TEST_F(GfxStateTest_594, TransformWidth_594) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

TEST_F(GfxStateTest_594, TransformWidthZero_594) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tw = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(tw, 0.0);
}

// --- GetTransformedLineWidth ---

TEST_F(GfxStateTest_594, GetTransformedLineWidth_594) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// --- Different DPI construction ---

TEST_F(GfxStateTest_594, ConstructorWithDifferentDPI_594) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpi(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpi.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpi.getVDPI(), 300.0);
}

TEST_F(GfxStateTest_594, ConstructorWithAsymmetricDPI_594) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState asymDpi(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(asymDpi.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(asymDpi.getVDPI(), 300.0);
}

// --- isParentState ---

TEST_F(GfxStateTest_594, IsParentState_594) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    child->restore();
}

// --- parseBlendMode ---

TEST_F(GfxStateTest_594, ParseBlendModeNormal_594) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    // If it parses, mode should be set. We just check it doesn't crash.
    // The actual return depends on the object being a valid name.
}

// --- Boundary: page box with negative coords ---

TEST_F(GfxStateTest_594, ConstructorWithNegativePageBox_594) {
    PDFRectangle pageBox = makePageBox(-100, -200, 500, 600);
    GfxState negState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(negState.getPageWidth(), 600.0);  // 500 - (-100)
    EXPECT_DOUBLE_EQ(negState.getPageHeight(), 800.0);  // 600 - (-200)
}

// --- Boundary: zero-size page box ---

TEST_F(GfxStateTest_594, ConstructorWithZeroSizePageBox_594) {
    PDFRectangle pageBox = makePageBox(0, 0, 0, 0);
    GfxState zeroState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(zeroState.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(zeroState.getPageHeight(), 0.0);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_594, ShiftCTMAndClip_594) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 60.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 60.0);
}

// --- GetPath ---

TEST_F(GfxStateTest_594, GetPathNotNull_594) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// --- GetCurX and GetCurY after moveTo ---

TEST_F(GfxStateTest_594, GetCurXYAfterMoveTo_594) {
    state->moveTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 42.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 84.0);
}

// --- Multiple save/restore ---

TEST_F(GfxStateTest_594, MultipleSaveRestore_594) {
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

// --- Font getter when no font set ---

TEST_F(GfxStateTest_594, DefaultFontIsNull_594) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// --- Fill/Stroke color space initially ---

TEST_F(GfxStateTest_594, DefaultFillColorSpace_594) {
    GfxColorSpace *cs = state->getFillColorSpace();
    // After construction, there should be a default color space
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_594, DefaultStrokeColorSpace_594) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// --- Fill/Stroke pattern initially null ---

TEST_F(GfxStateTest_594, DefaultFillPatternNull_594) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_594, DefaultStrokePatternNull_594) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// --- GetReusablePath ---

TEST_F(GfxStateTest_594, GetReusablePath_594) {
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}
