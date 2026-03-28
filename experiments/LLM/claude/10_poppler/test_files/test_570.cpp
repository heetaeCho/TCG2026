#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cmath>

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

class GfxStateTest_570 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makeRect(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and page dimensions
TEST_F(GfxStateTest_570, ConstructorSetsPageDimensions_570) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test DPI getters
TEST_F(GfxStateTest_570, GetDPI_570) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_570, GetPageBounds_570) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotation getter
TEST_F(GfxStateTest_570, GetRotate_570) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test with rotation = 90
TEST_F(GfxStateTest_570, ConstructorWithRotation90_570) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

// Test default fill opacity
TEST_F(GfxStateTest_570, DefaultFillOpacity_570) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_570, DefaultStrokeOpacity_570) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set/get fill opacity
TEST_F(GfxStateTest_570, SetFillOpacity_570) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set/get stroke opacity
TEST_F(GfxStateTest_570, SetStrokeOpacity_570) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default line width
TEST_F(GfxStateTest_570, DefaultLineWidth_570) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set/get line width
TEST_F(GfxStateTest_570, SetLineWidth_570) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_570, DefaultFlatness_570) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set/get flatness
TEST_F(GfxStateTest_570, SetFlatness_570) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_570, DefaultMiterLimit_570) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set/get miter limit
TEST_F(GfxStateTest_570, SetMiterLimit_570) {
    state->setMiterLimit(4.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 4.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_570, DefaultFillOverprint_570) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set/get fill overprint
TEST_F(GfxStateTest_570, SetFillOverprint_570) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_570, DefaultStrokeOverprint_570) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set/get stroke overprint
TEST_F(GfxStateTest_570, SetStrokeOverprint_570) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_570, DefaultOverprintMode_570) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set/get overprint mode
TEST_F(GfxStateTest_570, SetOverprintMode_570) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_570, DefaultStrokeAdjust_570) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set/get stroke adjust
TEST_F(GfxStateTest_570, SetStrokeAdjust_570) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_570, DefaultAlphaIsShape_570) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set/get alpha is shape
TEST_F(GfxStateTest_570, SetAlphaIsShape_570) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_570, DefaultTextKnockout_570) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set/get text knockout
TEST_F(GfxStateTest_570, SetTextKnockout_570) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default font size
TEST_F(GfxStateTest_570, DefaultFontSize_570) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default char space
TEST_F(GfxStateTest_570, DefaultCharSpace_570) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set/get char space
TEST_F(GfxStateTest_570, SetCharSpace_570) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_570, DefaultWordSpace_570) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set/get word space
TEST_F(GfxStateTest_570, SetWordSpace_570) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_570, DefaultHorizScaling_570) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set/get horiz scaling
TEST_F(GfxStateTest_570, SetHorizScaling_570) {
    state->setHorizScaling(0.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test default leading
TEST_F(GfxStateTest_570, DefaultLeading_570) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set/get leading
TEST_F(GfxStateTest_570, SetLeading_570) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_570, DefaultRise_570) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set/get rise
TEST_F(GfxStateTest_570, SetRise_570) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_570, DefaultRender_570) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set/get render
TEST_F(GfxStateTest_570, SetRender_570) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default blend mode
TEST_F(GfxStateTest_570, DefaultBlendMode_570) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set/get blend mode
TEST_F(GfxStateTest_570, SetBlendMode_570) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test line join default
TEST_F(GfxStateTest_570, DefaultLineJoin_570) {
    // Default line join is miter (0)
    EXPECT_EQ(state->getLineJoin(), 0);
}

// Test set/get line join
TEST_F(GfxStateTest_570, SetLineJoin_570) {
    state->setLineJoin(1);
    EXPECT_EQ(state->getLineJoin(), 1);
}

// Test line cap default
TEST_F(GfxStateTest_570, DefaultLineCap_570) {
    EXPECT_EQ(state->getLineCap(), 0);
}

// Test set/get line cap
TEST_F(GfxStateTest_570, SetLineCap_570) {
    state->setLineCap(1);
    EXPECT_EQ(state->getLineCap(), 1);
}

// Test set/get rendering intent
TEST_F(GfxStateTest_570, SetRenderingIntent_570) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test default rendering intent
TEST_F(GfxStateTest_570, DefaultRenderingIntent_570) {
    // Should have some default
    const char *intent = state->getRenderingIntent();
    EXPECT_NE(intent, nullptr);
}

// Test CTM getter
TEST_F(GfxStateTest_570, GetCTM_570) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

// Test setCTM
TEST_F(GfxStateTest_570, SetCTM_570) {
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
TEST_F(GfxStateTest_570, ConcatCTM_570) {
    // Set identity first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 5.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// Test transform
TEST_F(GfxStateTest_570, Transform_570) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

// Test transformDelta
TEST_F(GfxStateTest_570, TransformDelta_570) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    double x2, y2;
    state->transformDelta(3.0, 4.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 6.0);
    EXPECT_DOUBLE_EQ(y2, 8.0);
}

// Test transformWidth
TEST_F(GfxStateTest_570, TransformWidth_570) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_DOUBLE_EQ(w, 2.0);
}

// Test save and restore
TEST_F(GfxStateTest_570, SaveRestore_570) {
    state->setLineWidth(5.0);
    EXPECT_FALSE(state->hasSaves());

    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

// Test hasSaves
TEST_F(GfxStateTest_570, HasSaves_570) {
    EXPECT_FALSE(state->hasSaves());
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    EXPECT_FALSE(restored->hasSaves());
}

// Test path operations: moveTo, lineTo, isPath, isCurPt
TEST_F(GfxStateTest_570, PathOperations_570) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test curX and curY after moveTo
TEST_F(GfxStateTest_570, CurXYAfterMoveTo_570) {
    state->moveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

// Test lineTo updates current point
TEST_F(GfxStateTest_570, LineToUpdatesCurXY_570) {
    state->moveTo(0.0, 0.0);
    state->lineTo(50.0, 75.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 75.0);
}

// Test curveTo updates current point
TEST_F(GfxStateTest_570, CurveToUpdatesCurXY_570) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test closePath
TEST_F(GfxStateTest_570, ClosePath_570) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closePath, current point should return to the start of the subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test clearPath
TEST_F(GfxStateTest_570, ClearPath_570) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

// Test getPath
TEST_F(GfxStateTest_570, GetPath_570) {
    state->clearPath();
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test textMoveTo
TEST_F(GfxStateTest_570, TextMoveTo_570) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_570, SetGetTextMat_570) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// Test clip bounding box
TEST_F(GfxStateTest_570, GetClipBBox_570) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should be at least as large as the page
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_570, GetUserClipBBox_570) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_570, ClipToRect_570) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 100.0);
    EXPECT_GE(yMin, 100.0);
    EXPECT_LE(xMax, 200.0);
    EXPECT_LE(yMax, 200.0);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_570, SetGetLineDash_570) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_570, EmptyLineDash_570) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test copy
TEST_F(GfxStateTest_570, Copy_570) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.8);
    auto *copy = state->copy();
    EXPECT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copy->getFillOpacity(), 0.8);
    delete copy;
}

// Test default fill/stroke color spaces are null initially
TEST_F(GfxStateTest_570, DefaultColorSpaceNull_570) {
    auto cs = state->copyDefaultGrayColorSpace();
    // By default, no custom default color spaces set; may be null
    // Just test it doesn't crash
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_570, SetGetFillColor_570) {
    GfxColor color;
    color.c[0] = 32768;
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    EXPECT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], 32768);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_570, SetGetStrokeColor_570) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    EXPECT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], 65535);
}

// Test getFont returns nullptr by default
TEST_F(GfxStateTest_570, DefaultFontNull_570) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getFillPattern returns null by default
TEST_F(GfxStateTest_570, DefaultFillPattern_570) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

// Test getStrokePattern returns null by default
TEST_F(GfxStateTest_570, DefaultStrokePattern_570) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test isParentState
TEST_F(GfxStateTest_570, IsParentState_570) {
    GfxState *parent = state.get();
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(parent));
    GfxState *restored = child->restore();
    (void)restored;
}

// Test different page box sizes
TEST_F(GfxStateTest_570, DifferentPageBox_570) {
    PDFRectangle pageBox = makeRect(0, 0, 1000, 500);
    auto s = std::make_unique<GfxState>(150.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s->getPageWidth(), 1000.0);
    EXPECT_DOUBLE_EQ(s->getPageHeight(), 500.0);
    EXPECT_DOUBLE_EQ(s->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(s->getVDPI(), 150.0);
}

// Test rotation 180
TEST_F(GfxStateTest_570, Rotation180_570) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto s = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(s->getRotate(), 180);
}

// Test rotation 270
TEST_F(GfxStateTest_570, Rotation270_570) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto s = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(s->getRotate(), 270);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_570, ShiftCTMAndClip_570) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_570, GetTransformedLineWidth_570) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 6.0);
}

// Test getCTM with Matrix output
TEST_F(GfxStateTest_570, GetCTMAsMatrix_570) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// Test multiple save/restore
TEST_F(GfxStateTest_570, MultipleSaveRestore_570) {
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

// Test upsideDown=false
TEST_F(GfxStateTest_570, UpsideDownFalse_570) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    auto s = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(s->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s->getPageHeight(), 792.0);
}

// Test getReusablePath doesn't return null
TEST_F(GfxStateTest_570, GetReusablePath_570) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}

// Test line dash start value only
TEST_F(GfxStateTest_570, LineDashStartOnly_570) {
    std::vector<double> dash = {1.0};
    state->setLineDash(std::move(dash), 7.5);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 7.5);
    EXPECT_EQ(d.size(), 1u);
}

// Test setRenderingIntent with long string (boundary: 31 chars max for buffer)
TEST_F(GfxStateTest_570, SetRenderingIntentBoundary_570) {
    // renderingIntent buffer is char[32], so max 31 characters + null
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test textTransform
TEST_F(GfxStateTest_570, TextTransform_570) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->textTransform(5.0, 5.0, &x2, &y2);
    // Result depends on text matrix and CTM interaction
    // Just verify it doesn't crash and produces finite numbers
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test textTransformDelta
TEST_F(GfxStateTest_570, TextTransformDelta_570) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(3.0, 4.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test zero line width
TEST_F(GfxStateTest_570, ZeroLineWidth_570) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test negative coordinates in page box
TEST_F(GfxStateTest_570, NegativePageBox_570) {
    PDFRectangle pageBox = makeRect(-100, -200, 500, 600);
    auto s = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s->getPageWidth(), 600.0);
    EXPECT_DOUBLE_EQ(s->getPageHeight(), 800.0);
}
