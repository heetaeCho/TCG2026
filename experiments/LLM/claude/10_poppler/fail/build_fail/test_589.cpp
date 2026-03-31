#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "PDFDoc.h"
#include "Object.h"

// Helper to create a GfxState with reasonable defaults
static GfxState* createDefaultGfxState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return new GfxState(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_589 : public ::testing::Test {
protected:
    GfxState* state;

    void SetUp() override {
        state = createDefaultGfxState();
    }

    void TearDown() override {
        delete state;
    }
};

// --- Construction and basic getters ---

TEST_F(GfxStateTest_589, ConstructorSetsHDPI_589) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_589, ConstructorSetsVDPI_589) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_589, ConstructorSetsPageDimensions_589) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_589, ConstructorSetsRotate_589) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_589, ConstructorSetsCoordinateBounds_589) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- Blend Mode ---

TEST_F(GfxStateTest_589, DefaultBlendModeIsNormal_589) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_589, SetBlendMode_589) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

TEST_F(GfxStateTest_589, SetBlendModeScreen_589) {
    state->setBlendMode(gfxBlendScreen);
    EXPECT_EQ(state->getBlendMode(), gfxBlendScreen);
}

// --- Opacity ---

TEST_F(GfxStateTest_589, DefaultFillOpacity_589) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_589, DefaultStrokeOpacity_589) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_589, SetFillOpacity_589) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_589, SetStrokeOpacity_589) {
    state->setStrokeOpacity(0.25);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.25);
}

TEST_F(GfxStateTest_589, SetFillOpacityZero_589) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_589, SetStrokeOpacityZero_589) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// --- Overprint ---

TEST_F(GfxStateTest_589, DefaultFillOverprint_589) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_589, DefaultStrokeOverprint_589) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_589, SetFillOverprint_589) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_589, SetStrokeOverprint_589) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_589, DefaultOverprintMode_589) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_589, SetOverprintMode_589) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- Line properties ---

TEST_F(GfxStateTest_589, DefaultLineWidth_589) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_589, SetLineWidth_589) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_589, SetLineWidthZero_589) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_589, DefaultFlatness_589) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_589, SetFlatness_589) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

TEST_F(GfxStateTest_589, DefaultMiterLimit_589) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_589, SetMiterLimit_589) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_589, DefaultLineJoin_589) {
    EXPECT_EQ(state->getLineJoin(), 0); // miter join
}

TEST_F(GfxStateTest_589, SetLineJoin_589) {
    state->setLineJoin(static_cast<LineJoinStyle>(1)); // round join
    EXPECT_EQ(state->getLineJoin(), 1);
}

TEST_F(GfxStateTest_589, DefaultLineCap_589) {
    EXPECT_EQ(state->getLineCap(), 0); // butt cap
}

TEST_F(GfxStateTest_589, SetLineCap_589) {
    state->setLineCap(static_cast<LineCapStyle>(1)); // round cap
    EXPECT_EQ(state->getLineCap(), 1);
}

// --- Stroke adjust and alpha ---

TEST_F(GfxStateTest_589, DefaultStrokeAdjust_589) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_589, SetStrokeAdjust_589) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_589, DefaultAlphaIsShape_589) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_589, SetAlphaIsShape_589) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_589, DefaultTextKnockout_589) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_589, SetTextKnockout_589) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- Text properties ---

TEST_F(GfxStateTest_589, DefaultCharSpace_589) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_589, SetCharSpace_589) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_589, DefaultWordSpace_589) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_589, SetWordSpace_589) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_589, DefaultHorizScaling_589) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_589, SetHorizScaling_589) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_589, DefaultLeading_589) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_589, SetLeading_589) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_589, DefaultRise_589) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_589, SetRise_589) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_589, DefaultRender_589) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_589, SetRender_589) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_589, DefaultFontSize_589) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// --- CTM ---

TEST_F(GfxStateTest_589, GetCTMReturnsArray_589) {
    const auto& ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_589, SetCTM_589) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_589, ConcatCTM_589) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // identity
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 10.0);
}

// --- Transform ---

TEST_F(GfxStateTest_589, TransformIdentityCTM_589) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_589, TransformWithTranslation_589) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

TEST_F(GfxStateTest_589, TransformDeltaNoTranslation_589) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

TEST_F(GfxStateTest_589, TransformWithScaling_589) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// --- TextMat ---

TEST_F(GfxStateTest_589, SetTextMat_589) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto& tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// --- Path operations ---

TEST_F(GfxStateTest_589, InitiallyNoPath_589) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_589, MoveToCreatesCurPt_589) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_589, LineToCreatesPath_589) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_589, ClearPathResetsState_589) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_589, CurveToCreatesPath_589) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_589, ClosePathWorks_589) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// --- Save and Restore ---

TEST_F(GfxStateTest_589, InitiallyNoSaves_589) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_589, SaveCreatesSavedState_589) {
    GfxState* saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    // restore to clean up
    state = saved->restore();
}

TEST_F(GfxStateTest_589, RestoreReturnsParentState_589) {
    state->setFillOpacity(0.5);
    GfxState* saved = state->save();
    saved->setFillOpacity(0.3);
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.3);
    GfxState* restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.5);
    state = restored;
}

TEST_F(GfxStateTest_589, SaveRestorePreservesBlendMode_589) {
    state->setBlendMode(gfxBlendMultiply);
    GfxState* saved = state->save();
    saved->setBlendMode(gfxBlendScreen);
    EXPECT_EQ(saved->getBlendMode(), gfxBlendScreen);
    GfxState* restored = saved->restore();
    EXPECT_EQ(restored->getBlendMode(), gfxBlendMultiply);
    state = restored;
}

// --- LineDash ---

TEST_F(GfxStateTest_589, SetLineDash_589) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
}

TEST_F(GfxStateTest_589, SetEmptyLineDash_589) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// --- Clip bbox ---

TEST_F(GfxStateTest_589, GetClipBBox_589) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be set after construction
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_589, ClipToRect_589) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// --- Rendering Intent ---

TEST_F(GfxStateTest_589, DefaultRenderingIntent_589) {
    const char* intent = state->getRenderingIntent();
    EXPECT_NE(intent, nullptr);
}

TEST_F(GfxStateTest_589, SetRenderingIntent_589) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_589, SetRenderingIntentRelativeColorimetric_589) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// --- Coordinate getters ---

TEST_F(GfxStateTest_589, DefaultCurXY_589) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

TEST_F(GfxStateTest_589, DefaultLineXY_589) {
    EXPECT_DOUBLE_EQ(state->getLineX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 0.0);
}

// --- TextMoveTo ---

TEST_F(GfxStateTest_589, TextMoveTo_589) {
    state->textMoveTo(50.0, 100.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 100.0);
}

// --- Copy ---

TEST_F(GfxStateTest_589, CopyPreservesState_589) {
    state->setFillOpacity(0.7);
    state->setBlendMode(gfxBlendMultiply);
    state->setLineWidth(3.5);
    auto* copied = state->copy();
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    EXPECT_EQ(copied->getBlendMode(), gfxBlendMultiply);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.5);
    delete copied;
}

// --- parseBlendMode ---

TEST_F(GfxStateTest_589, ParseBlendModeNormal_589) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendNormal);
}

TEST_F(GfxStateTest_589, ParseBlendModeMultiply_589) {
    Object obj;
    obj = Object(new GooString("Multiply"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendMultiply);
}

TEST_F(GfxStateTest_589, ParseBlendModeInvalid_589) {
    Object obj;
    obj = Object(new GooString("InvalidBlendMode"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_FALSE(result);
}

// --- isParentState ---

TEST_F(GfxStateTest_589, IsParentStateAfterSave_589) {
    GfxState* child = state->save();
    EXPECT_TRUE(child->isParentState(state));
    state = child->restore();
}

// --- Rotated page box ---

TEST(GfxStateRotatedTest_589, ConstructWithRotation90_589) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState* s = new GfxState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(s->getRotate(), 90);
    EXPECT_DOUBLE_EQ(s->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s->getPageHeight(), 792.0);
    delete s;
}

TEST(GfxStateRotatedTest_589, ConstructWithRotation180_589) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState* s = new GfxState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(s->getRotate(), 180);
    delete s;
}

TEST(GfxStateRotatedTest_589, ConstructWithRotation270_589) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState* s = new GfxState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(s->getRotate(), 270);
    delete s;
}

// --- Different DPI ---

TEST(GfxStateDPITest_589, HighDPI_589) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState* s = new GfxState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(s->getVDPI(), 300.0);
    delete s;
}

TEST(GfxStateDPITest_589, AsymmetricDPI_589) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState* s = new GfxState(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(s->getVDPI(), 300.0);
    delete s;
}

// --- GetUserClipBBox ---

TEST_F(GfxStateTest_589, GetUserClipBBox_589) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- TransformWidth ---

TEST_F(GfxStateTest_589, TransformWidthIdentity_589) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 1.0);
}

TEST_F(GfxStateTest_589, TransformWidthScaled_589) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 2.0);
}

// --- GetPath ---

TEST_F(GfxStateTest_589, GetPathNotNull_589) {
    const GfxPath* path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// --- Multiple save/restore ---

TEST_F(GfxStateTest_589, MultipleSaveRestore_589) {
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
    
    state = r2;
}

// --- Fill/Stroke color ---

TEST_F(GfxStateTest_589, GetFillColorNotNull_589) {
    const GfxColor* color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_589, GetStrokeColorNotNull_589) {
    const GfxColor* color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_589, SetFillColor_589) {
    GfxColor color;
    color.c[0] = 32768;  // some value
    state->setFillColor(&color);
    const GfxColor* retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_589, SetStrokeColor_589) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor* retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 16384);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_589, ShiftCTMAndClip_589) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// --- GetTransformedLineWidth ---

TEST_F(GfxStateTest_589, GetTransformedLineWidthIdentity_589) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tw, 2.0);
}

// --- GetReusablePath ---

TEST_F(GfxStateTest_589, GetReusablePathNotNull_589) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}
