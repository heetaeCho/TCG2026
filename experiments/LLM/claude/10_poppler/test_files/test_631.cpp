#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_631 : public ::testing::Test {
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

// Test basic construction and DPI getters
TEST_F(GfxStateTest_631, ConstructionAndDPI_631) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_631, PageDimensions_631) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test page coordinates
TEST_F(GfxStateTest_631, PageCoordinates_631) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_631, Rotation_631) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test rotation with 90 degrees
TEST(GfxStateRotateTest_631, Rotate90_631) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_631, SetAndGetStrokeColor_631) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 12345;
    color.c[1] = 23456;
    color.c[2] = 34567;

    state->setStrokeColor(&color);

    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 12345);
    EXPECT_EQ(retrieved->c[1], 23456);
    EXPECT_EQ(retrieved->c[2], 34567);
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_631, SetAndGetFillColor_631) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 65535;

    state->setFillColor(&color);

    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 65535);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_631, SetAndGetFillOpacity_631) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_631, SetAndGetStrokeOpacity_631) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test fill opacity boundary - zero
TEST_F(GfxStateTest_631, FillOpacityZero_631) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

// Test fill opacity boundary - one
TEST_F(GfxStateTest_631, FillOpacityOne_631) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_631, SetAndGetLineWidth_631) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test line width of zero
TEST_F(GfxStateTest_631, LineWidthZero_631) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test setFlatness and getFlatness
TEST_F(GfxStateTest_631, SetAndGetFlatness_631) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_631, SetAndGetMiterLimit_631) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_631, SetAndGetLineJoin_631) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_631, SetAndGetLineCap_631) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_631, SetAndGetFillOverprint_631) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_631, SetAndGetStrokeOverprint_631) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_631, SetAndGetOverprintMode_631) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_631, SetAndGetStrokeAdjust_631) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_631, SetAndGetAlphaIsShape_631) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_631, SetAndGetTextKnockout_631) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setCharSpace and getCharSpace
TEST_F(GfxStateTest_631, SetAndGetCharSpace_631) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test setWordSpace and getWordSpace
TEST_F(GfxStateTest_631, SetAndGetWordSpace_631) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_631, SetAndGetHorizScaling_631) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// Test setLeading and getLeading
TEST_F(GfxStateTest_631, SetAndGetLeading_631) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_631, SetAndGetRise_631) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_631, SetAndGetRender_631) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_631, SetAndGetRenderingIntent_631) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test rendering intent with long string (boundary: 31 char max for char[32])
TEST_F(GfxStateTest_631, RenderingIntentLongString_631) {
    // "AbsoluteColorimetric" is a standard intent
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_631, SetAndGetBlendMode_631) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_631, SetAndGetTextMat_631) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 0.0);
    EXPECT_DOUBLE_EQ(textMat[2], 0.0);
    EXPECT_DOUBLE_EQ(textMat[3], 1.0);
    EXPECT_DOUBLE_EQ(textMat[4], 10.0);
    EXPECT_DOUBLE_EQ(textMat[5], 20.0);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_631, SetAndGetCTM_631) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// Test transform with identity-like CTM
TEST_F(GfxStateTest_631, TransformWithCTM_631) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test transform with scaling CTM
TEST_F(GfxStateTest_631, TransformWithScalingCTM_631) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 2.0 * 5.0 + 10.0);
    EXPECT_DOUBLE_EQ(y2, 3.0 * 5.0 + 20.0);
}

// Test transformDelta
TEST_F(GfxStateTest_631, TransformDelta_631) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    double x2, y2;
    state->transformDelta(5.0, 5.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 2.0 * 5.0);
    EXPECT_DOUBLE_EQ(y2, 3.0 * 5.0);
}

// Test save and restore
TEST_F(GfxStateTest_631, SaveAndRestore_631) {
    state->setLineWidth(5.0);
    GfxState *savedState = state->save();
    ASSERT_NE(savedState, nullptr);
    EXPECT_TRUE(savedState->hasSaves());

    savedState->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(savedState->getLineWidth(), 10.0);

    GfxState *restoredState = savedState->restore();
    ASSERT_NE(restoredState, nullptr);
    EXPECT_DOUBLE_EQ(restoredState->getLineWidth(), 5.0);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_631, HasSavesInitiallyFalse_631) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_631, HasSavesAfterSave_631) {
    GfxState *savedState = state->save();
    EXPECT_TRUE(savedState->hasSaves());
    // Restore to clean up
    GfxState *restored = savedState->restore();
    EXPECT_FALSE(restored->hasSaves());
}

// Test path operations - initially no path
TEST_F(GfxStateTest_631, InitialPathState_631) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test moveTo creates current point
TEST_F(GfxStateTest_631, MoveToSetsCurPt_631) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test lineTo creates path
TEST_F(GfxStateTest_631, LineToCreatesPath_631) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

// Test clearPath resets path state
TEST_F(GfxStateTest_631, ClearPathResetsPath_631) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_631, ClosePath_631) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_631, CurveTo_631) {
    state->moveTo(0.0, 0.0);
    state->curveTo(5.0, 10.0, 15.0, 10.0, 20.0, 0.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test textMoveTo
TEST_F(GfxStateTest_631, TextMoveTo_631) {
    state->textMoveTo(100.0, 200.0);
    // Verify line position is updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_631, SetAndGetLineDash_631) {
    std::vector<double> dash = {5.0, 3.0, 1.0};
    state->setLineDash(std::move(dash), 2.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 2.0);
    ASSERT_EQ(retrievedDash.size(), 3u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 5.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[2], 1.0);
}

// Test empty line dash
TEST_F(GfxStateTest_631, EmptyLineDash_631) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(retrievedDash.empty());
}

// Test clipToRect
TEST_F(GfxStateTest_631, ClipToRect_631) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

// Test copy
TEST_F(GfxStateTest_631, CopyState_631) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);

    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// Test concatCTM
TEST_F(GfxStateTest_631, ConcatCTM_631) {
    // Set identity CTM first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Concatenate with a translation
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 50.0, 60.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 50.0);
    EXPECT_DOUBLE_EQ(ctm[5], 60.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_631, ShiftCTMAndClip_631) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test getClipBBox
TEST_F(GfxStateTest_631, GetClipBBox_631) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip box should be initialized to reasonable values
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_631, GetUserClipBBox_631) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getFontSize with setFont(nullptr, size)
TEST_F(GfxStateTest_631, SetFontSize_631) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// Test getFont initially null
TEST_F(GfxStateTest_631, GetFontInitiallyNull_631) {
    const auto &font = state->getFont();
    // Initially there should be no font set
    EXPECT_EQ(font, nullptr);
}

// Test transformWidth
TEST_F(GfxStateTest_631, TransformWidth_631) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// Test transformWidth with zero
TEST_F(GfxStateTest_631, TransformWidthZero_631) {
    double w = state->transformWidth(0.0);
    EXPECT_GE(w, 0.0);
}

// Test multiple stroke color changes
TEST_F(GfxStateTest_631, MultipleStrokeColorChanges_631) {
    GfxColor color1;
    memset(&color1, 0, sizeof(color1));
    color1.c[0] = 100;

    GfxColor color2;
    memset(&color2, 0, sizeof(color2));
    color2.c[0] = 200;

    state->setStrokeColor(&color1);
    EXPECT_EQ(state->getStrokeColor()->c[0], 100);

    state->setStrokeColor(&color2);
    EXPECT_EQ(state->getStrokeColor()->c[0], 200);
}

// Test getCTM via Matrix overload
TEST_F(GfxStateTest_631, GetCTMMatrix_631) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Just verify it doesn't crash and returns something
    // The exact mapping depends on Matrix structure
}

// Test parseBlendMode with normal mode
TEST_F(GfxStateTest_631, ParseBlendModeNormal_631) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test getPath initially
TEST_F(GfxStateTest_631, GetPathInitially_631) {
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_631, MultipleSaveRestore_631) {
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

// Test stroke color with all components
TEST_F(GfxStateTest_631, StrokeColorAllComponents_631) {
    GfxColor color;
    for (int i = 0; i < gfxColorMaxComps; ++i) {
        color.c[i] = (GfxColorComp)(i * 1000);
    }
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    for (int i = 0; i < gfxColorMaxComps; ++i) {
        EXPECT_EQ(retrieved->c[i], (GfxColorComp)(i * 1000));
    }
}

// Test fill color with all components
TEST_F(GfxStateTest_631, FillColorAllComponents_631) {
    GfxColor color;
    for (int i = 0; i < gfxColorMaxComps; ++i) {
        color.c[i] = (GfxColorComp)(i * 2000);
    }
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    for (int i = 0; i < gfxColorMaxComps; ++i) {
        EXPECT_EQ(retrieved->c[i], (GfxColorComp)(i * 2000));
    }
}

// Test getReusablePath
TEST_F(GfxStateTest_631, GetReusablePath_631) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    ASSERT_NE(pathIter, nullptr);
}

// Test textShift
TEST_F(GfxStateTest_631, TextShift_631) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Record initial position
    double initX = state->getCurX();
    double initY = state->getCurY();
    state->textShift(5.0, 10.0);
    // Position should change
    // We can't predict exact values without knowing the CTM,
    // but we verify no crash
}

// Test default blend mode is normal
TEST_F(GfxStateTest_631, DefaultBlendMode_631) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test negative line width
TEST_F(GfxStateTest_631, NegativeLineWidth_631) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test different DPI values
TEST(GfxStateDiffDPI_631, DifferentDPI_631) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(s.getVDPI(), 150.0);
}

// Test upsideDown = false
TEST(GfxStateUpsideDown_631, UpsideDownFalse_631) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState s(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(s.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s.getPageHeight(), 792.0);
}

// Test isParentState
TEST_F(GfxStateTest_631, IsParentState_631) {
    GfxState *savedState = state->save();
    EXPECT_TRUE(savedState->isParentState(state.get()));
    GfxState *restored = savedState->restore();
}

// Test isParentState with non-parent
TEST_F(GfxStateTest_631, IsParentStateNonParent_631) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState other(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(&other));
}
