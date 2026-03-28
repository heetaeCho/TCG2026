#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_587 : public ::testing::Test {
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

// Test basic construction and DPI getters
TEST_F(GfxStateTest_587, ConstructorSetsDPI_587) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_587, PageDimensions_587) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_587, GetRotate_587) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page bounds
TEST_F(GfxStateTest_587, PageBounds_587) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_587, DefaultFillOpacity_587) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_587, DefaultStrokeOpacity_587) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set and get fill opacity
TEST_F(GfxStateTest_587, SetFillOpacity_587) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_587, SetStrokeOpacity_587) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default line width
TEST_F(GfxStateTest_587, DefaultLineWidth_587) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set and get line width
TEST_F(GfxStateTest_587, SetLineWidth_587) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test zero line width
TEST_F(GfxStateTest_587, SetLineWidthZero_587) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test default flatness
TEST_F(GfxStateTest_587, DefaultFlatness_587) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set flatness
TEST_F(GfxStateTest_587, SetFlatness_587) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_587, DefaultMiterLimit_587) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set miter limit
TEST_F(GfxStateTest_587, SetMiterLimit_587) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_587, DefaultFillOverprint_587) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set fill overprint
TEST_F(GfxStateTest_587, SetFillOverprint_587) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_587, DefaultStrokeOverprint_587) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set stroke overprint
TEST_F(GfxStateTest_587, SetStrokeOverprint_587) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_587, DefaultOverprintMode_587) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set overprint mode
TEST_F(GfxStateTest_587, SetOverprintMode_587) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_587, DefaultStrokeAdjust_587) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set stroke adjust
TEST_F(GfxStateTest_587, SetStrokeAdjust_587) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_587, DefaultAlphaIsShape_587) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set alpha is shape
TEST_F(GfxStateTest_587, SetAlphaIsShape_587) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_587, DefaultTextKnockout_587) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set text knockout
TEST_F(GfxStateTest_587, SetTextKnockout_587) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default font size
TEST_F(GfxStateTest_587, DefaultFontSize_587) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default char space
TEST_F(GfxStateTest_587, DefaultCharSpace_587) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set char space
TEST_F(GfxStateTest_587, SetCharSpace_587) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_587, DefaultWordSpace_587) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set word space
TEST_F(GfxStateTest_587, SetWordSpace_587) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_587, DefaultHorizScaling_587) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set horiz scaling
TEST_F(GfxStateTest_587, SetHorizScaling_587) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test default leading
TEST_F(GfxStateTest_587, DefaultLeading_587) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set leading
TEST_F(GfxStateTest_587, SetLeading_587) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_587, DefaultRise_587) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set rise
TEST_F(GfxStateTest_587, SetRise_587) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_587, DefaultRender_587) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set render
TEST_F(GfxStateTest_587, SetRender_587) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default blend mode
TEST_F(GfxStateTest_587, DefaultBlendMode_587) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set blend mode
TEST_F(GfxStateTest_587, SetBlendMode_587) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test default fill pattern is null
TEST_F(GfxStateTest_587, DefaultFillPatternNull_587) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// Test default stroke pattern is null
TEST_F(GfxStateTest_587, DefaultStrokePatternNull_587) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test getCTM returns 6 element array
TEST_F(GfxStateTest_587, GetCTMArray_587) {
    const auto& ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_587, SetCTM_587) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test concatCTM
TEST_F(GfxStateTest_587, ConcatCTM_587) {
    // Set identity first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 5.0);
    EXPECT_DOUBLE_EQ(ctm[5], 5.0);
}

// Test transform
TEST_F(GfxStateTest_587, TransformIdentity_587) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling
TEST_F(GfxStateTest_587, TransformScaling_587) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test transform with translation
TEST_F(GfxStateTest_587, TransformTranslation_587) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

// Test transformDelta (no translation component)
TEST_F(GfxStateTest_587, TransformDelta_587) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test save and restore
TEST_F(GfxStateTest_587, SaveRestore_587) {
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    // The save returns the new state, the old state is saved inside
    saved->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 5.0);
    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
    // Clean up: state is now pointing to the original
    state.release(); // prevent double free
    state.reset(restored);
}

// Test hasSaves
TEST_F(GfxStateTest_587, HasSavesDefault_587) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_587, HasSavesAfterSave_587) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    state.release();
    state.reset(restored);
}

// Test path operations
TEST_F(GfxStateTest_587, PathIsEmpty_587) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test moveTo creates current point
TEST_F(GfxStateTest_587, MoveToSetsCurPt_587) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test lineTo creates a path
TEST_F(GfxStateTest_587, LineToCreatesPath_587) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_587, ClearPath_587) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_587, ClosePath_587) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_587, CurveTo_587) {
    state->moveTo(0.0, 0.0);
    state->curveTo(5.0, 10.0, 10.0, 10.0, 15.0, 0.0);
    EXPECT_TRUE(state->isPath());
}

// Test getPath not null
TEST_F(GfxStateTest_587, GetPath_587) {
    EXPECT_NE(state->getPath(), nullptr);
}

// Test text matrix
TEST_F(GfxStateTest_587, SetTextMat_587) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 10.0);
    const auto& tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 10.0);
}

// Test rendering intent
TEST_F(GfxStateTest_587, SetRenderingIntent_587) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test rendering intent default
TEST_F(GfxStateTest_587, DefaultRenderingIntent_587) {
    const char* intent = state->getRenderingIntent();
    EXPECT_NE(intent, nullptr);
}

// Test rendering intent truncation (buffer is 32 chars)
TEST_F(GfxStateTest_587, RenderingIntentLongString_587) {
    // Should not crash even with a long string
    state->setRenderingIntent("ThisIsAVeryLongRenderingIntentNameThatExceedsBuffer");
    const char* intent = state->getRenderingIntent();
    EXPECT_NE(intent, nullptr);
    // Length should be within 31 chars (null-terminated)
    EXPECT_LE(strlen(intent), 31u);
}

// Test getClipBBox
TEST_F(GfxStateTest_587, GetClipBBox_587) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be set to something valid
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_587, ClipToRect_587) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_587, GetUserClipBBox_587) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setLineDash
TEST_F(GfxStateTest_587, SetLineDash_587) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test setLineDash with nonzero start
TEST_F(GfxStateTest_587, SetLineDashWithStart_587) {
    std::vector<double> dash = {5.0, 3.0, 1.0};
    state->setLineDash(std::move(dash), 2.5);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 2.5);
    EXPECT_EQ(d.size(), 3u);
}

// Test line join
TEST_F(GfxStateTest_587, SetLineJoin_587) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test line cap
TEST_F(GfxStateTest_587, SetLineCap_587) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test copy
TEST_F(GfxStateTest_587, Copy_587) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.6);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.6);
}

// Test construction with rotation
TEST_F(GfxStateTest_587, ConstructWithRotation_587) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
    EXPECT_DOUBLE_EQ(rotatedState->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(rotatedState->getPageHeight(), 792.0);
}

// Test construction with different DPI
TEST_F(GfxStateTest_587, ConstructWithDifferentDPI_587) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    auto highDpiState = std::make_unique<GfxState>(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState->getVDPI(), 150.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_587, TextMoveTo_587) {
    state->textMoveTo(50.0, 60.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 60.0);
}

// Test getCurX and getCurY after moveTo
TEST_F(GfxStateTest_587, GetCurXY_587) {
    state->moveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 25.0);
}

// Test fill color
TEST_F(GfxStateTest_587, SetFillColor_587) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    ASSERT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

// Test stroke color
TEST_F(GfxStateTest_587, SetStrokeColor_587) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    ASSERT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 16384);
}

// Test transformWidth
TEST_F(GfxStateTest_587, TransformWidth_587) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test transformWidth with zero
TEST_F(GfxStateTest_587, TransformWidthZero_587) {
    double tw = state->transformWidth(0.0);
    EXPECT_GE(tw, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_587, GetTransformedLineWidth_587) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test parseBlendMode with normal
TEST_F(GfxStateTest_587, ParseBlendModeNormal_587) {
    Object obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test construction with upside down false
TEST_F(GfxStateTest_587, ConstructUpsideDownFalse_587) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    auto s = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    EXPECT_NE(s, nullptr);
    EXPECT_DOUBLE_EQ(s->getHDPI(), 72.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_587, ShiftCTMAndClip_587) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test empty line dash by default
TEST_F(GfxStateTest_587, DefaultLineDash_587) {
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test default font is null
TEST_F(GfxStateTest_587, DefaultFont_587) {
    const auto& font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test isParentState
TEST_F(GfxStateTest_587, IsParentState_587) {
    // Without saves, isParentState should return false for itself
    EXPECT_FALSE(state->isParentState(state.get()));
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_587, MultipleSaveRestore_587) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);
    
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    EXPECT_TRUE(s2->hasSaves());
    
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
    
    state.release();
    state.reset(r2);
}

// Test getReusablePath
TEST_F(GfxStateTest_587, GetReusablePath_587) {
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test getCTM with Matrix overload
TEST_F(GfxStateTest_587, GetCTMMatrix_587) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify matrix is populated
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test display profile default is null
TEST_F(GfxStateTest_587, DefaultDisplayProfile_587) {
    auto profile = state->getDisplayProfile();
    // Default should be null/empty
    EXPECT_FALSE(profile);
}
