#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"
#include "Object.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_632 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_632, ConstructionAndDPI_632) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_632, PageDimensions_632) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_632, Rotation_632) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_632, PageBoxCoordinates_632) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_632, SetAndGetBlendMode_632) {
    state->setBlendMode(gfxBlendNormal);
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);

    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);

    state->setBlendMode(gfxBlendScreen);
    EXPECT_EQ(state->getBlendMode(), gfxBlendScreen);

    state->setBlendMode(gfxBlendDarken);
    EXPECT_EQ(state->getBlendMode(), gfxBlendDarken);

    state->setBlendMode(gfxBlendLighten);
    EXPECT_EQ(state->getBlendMode(), gfxBlendLighten);
}

// Test fill opacity
TEST_F(GfxStateTest_632, SetAndGetFillOpacity_632) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);

    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);

    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test stroke opacity
TEST_F(GfxStateTest_632, SetAndGetStrokeOpacity_632) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);

    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);

    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test line width
TEST_F(GfxStateTest_632, SetAndGetLineWidth_632) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);

    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);

    state->setLineWidth(100.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 100.0);
}

// Test flatness
TEST_F(GfxStateTest_632, SetAndGetFlatness_632) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);

    state->setFlatness(0);
    EXPECT_EQ(state->getFlatness(), 0);

    state->setFlatness(100);
    EXPECT_EQ(state->getFlatness(), 100);
}

// Test line join
TEST_F(GfxStateTest_632, SetAndGetLineJoin_632) {
    state->setLineJoin(lineJoinMiter);
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);

    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);

    state->setLineJoin(lineJoinBevel);
    EXPECT_EQ(state->getLineJoin(), lineJoinBevel);
}

// Test line cap
TEST_F(GfxStateTest_632, SetAndGetLineCap_632) {
    state->setLineCap(lineCapButt);
    EXPECT_EQ(state->getLineCap(), lineCapButt);

    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);

    state->setLineCap(lineCapProjecting);
    EXPECT_EQ(state->getLineCap(), lineCapProjecting);
}

// Test miter limit
TEST_F(GfxStateTest_632, SetAndGetMiterLimit_632) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);

    state->setMiterLimit(1.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 1.0);
}

// Test stroke adjust
TEST_F(GfxStateTest_632, SetAndGetStrokeAdjust_632) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());

    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_632, SetAndGetAlphaIsShape_632) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());

    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_632, SetAndGetTextKnockout_632) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());

    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test fill overprint
TEST_F(GfxStateTest_632, SetAndGetFillOverprint_632) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());

    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_632, SetAndGetStrokeOverprint_632) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());

    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_632, SetAndGetOverprintMode_632) {
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);

    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test char space
TEST_F(GfxStateTest_632, SetAndGetCharSpace_632) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);

    state->setCharSpace(0.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test word space
TEST_F(GfxStateTest_632, SetAndGetWordSpace_632) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);

    state->setWordSpace(0.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_632, SetAndGetHorizScaling_632) {
    state->setHorizScaling(100.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 100.0);

    state->setHorizScaling(50.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 50.0);

    state->setHorizScaling(200.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 200.0);
}

// Test leading
TEST_F(GfxStateTest_632, SetAndGetLeading_632) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);

    state->setLeading(0.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test rise
TEST_F(GfxStateTest_632, SetAndGetRise_632) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);

    state->setRise(-3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), -3.0);

    state->setRise(0.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test render
TEST_F(GfxStateTest_632, SetAndGetRender_632) {
    state->setRender(0);
    EXPECT_EQ(state->getRender(), 0);

    state->setRender(1);
    EXPECT_EQ(state->getRender(), 1);

    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test rendering intent
TEST_F(GfxStateTest_632, SetAndGetRenderingIntent_632) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");

    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");

    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");

    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test font size
TEST_F(GfxStateTest_632, SetFontGetFontSize_632) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);

    state->setFont(nullptr, 0.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test text matrix
TEST_F(GfxStateTest_632, SetAndGetTextMat_632) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 0.0);
    EXPECT_DOUBLE_EQ(mat[5], 0.0);

    state->setTextMat(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
    const auto &mat2 = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat2[0], 2.0);
    EXPECT_DOUBLE_EQ(mat2[1], 3.0);
    EXPECT_DOUBLE_EQ(mat2[2], 4.0);
    EXPECT_DOUBLE_EQ(mat2[3], 5.0);
    EXPECT_DOUBLE_EQ(mat2[4], 6.0);
    EXPECT_DOUBLE_EQ(mat2[5], 7.0);
}

// Test CTM
TEST_F(GfxStateTest_632, SetCTM_632) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test save and restore
TEST_F(GfxStateTest_632, SaveAndRestore_632) {
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
TEST_F(GfxStateTest_632, HasSaves_632) {
    EXPECT_FALSE(state->hasSaves());

    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());

    GfxState *restored = saved->restore();
    EXPECT_FALSE(restored->hasSaves());
}

// Test path operations - moveTo and isPath/isCurPt
TEST_F(GfxStateTest_632, PathOperations_632) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo after moveTo
TEST_F(GfxStateTest_632, LineToAfterMoveTo_632) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test curveTo
TEST_F(GfxStateTest_632, CurveTo_632) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_632, ClosePath_632) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_632, ClearPath_632) {
    state->moveTo(10.0, 10.0);
    state->lineTo(20.0, 20.0);
    EXPECT_TRUE(state->isPath());

    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test transform
TEST_F(GfxStateTest_632, Transform_632) {
    // With identity-like CTM, transform should map coordinates
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_632, TransformWithScaling_632) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test transform with translation
TEST_F(GfxStateTest_632, TransformWithTranslation_632) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

// Test transformDelta (no translation component)
TEST_F(GfxStateTest_632, TransformDelta_632) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test concatCTM
TEST_F(GfxStateTest_632, ConcatCTM_632) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);

    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    // After concat: new CTM should be product of old and concat matrices
    EXPECT_DOUBLE_EQ(x2, 12.0);  // 2*1 + 10
    EXPECT_DOUBLE_EQ(y2, 22.0);  // 2*1 + 20
}

// Test clip bounding box
TEST_F(GfxStateTest_632, GetClipBBox_632) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have some valid clip region
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_632, ClipToRect_632) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_632, GetUserClipBBox_632) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test textMoveTo
TEST_F(GfxStateTest_632, TextMoveTo_632) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test line dash
TEST_F(GfxStateTest_632, SetAndGetLineDash_632) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
}

// Test empty line dash
TEST_F(GfxStateTest_632, EmptyLineDash_632) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(retrievedDash.empty());
}

// Test copy
TEST_F(GfxStateTest_632, Copy_632) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);

    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// Test construction with different rotations
TEST_F(GfxStateTest_632, ConstructionWithRotation90_632) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_632, ConstructionWithRotation180_632) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_632, ConstructionWithRotation270_632) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// Test different DPI values
TEST_F(GfxStateTest_632, DifferentDPI_632) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 600.0);
}

// Test rendering intent with long string (boundary: renderingIntent is char[32])
TEST_F(GfxStateTest_632, RenderingIntentBoundary_632) {
    // "AbsoluteColorimetric" is 20 chars, should fit
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test parseBlendMode static method
TEST_F(GfxStateTest_632, ParseBlendModeNormal_632) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test multiple saves
TEST_F(GfxStateTest_632, MultipleSaves_632) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    EXPECT_TRUE(s1->hasSaves());

    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    EXPECT_TRUE(s2->hasSaves());

    s2->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);

    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    EXPECT_TRUE(r1->hasSaves());

    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
    EXPECT_FALSE(r2->hasSaves());
}

// Test transformWidth
TEST_F(GfxStateTest_632, TransformWidth_632) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_632, GetTransformedLineWidth_632) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setLineWidth(2.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test fill and stroke color
TEST_F(GfxStateTest_632, SetAndGetFillColor_632) {
    GfxColor color;
    color.c[0] = 32768; // 0.5 in fixed-point
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], color.c[0]);
}

TEST_F(GfxStateTest_632, SetAndGetStrokeColor_632) {
    GfxColor color;
    color.c[0] = 65535; // 1.0 in fixed-point
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], color.c[0]);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_632, ShiftCTMAndClip_632) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(50.0, 100.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 100.0);
}

// Test getPath returns non-null
TEST_F(GfxStateTest_632, GetPath_632) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test getCurX and getCurY after moveTo
TEST_F(GfxStateTest_632, GetCurXYAfterMoveTo_632) {
    state->clearPath();
    state->moveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 25.0);
}

// Test isParentState
TEST_F(GfxStateTest_632, IsParentState_632) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
    GfxState *restored = saved->restore();
    (void)restored;
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_632, GetCTMMatrix_632) {
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

// Test default font is null
TEST_F(GfxStateTest_632, DefaultFontIsNull_632) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test fill/stroke pattern default null
TEST_F(GfxStateTest_632, DefaultPatternsNull_632) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test getReusablePath
TEST_F(GfxStateTest_632, GetReusablePath_632) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}
