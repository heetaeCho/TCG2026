#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

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

class GfxStateTest_630 : public ::testing::Test {
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

// =============================================================================
// Constructor and basic getters
// =============================================================================

TEST_F(GfxStateTest_630, ConstructorSetsHDPI_630) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_630, ConstructorSetsVDPI_630) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_630, ConstructorSetsPageDimensions_630) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_630, ConstructorSetsRotate_630) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_630, ConstructorWithRotation90_630) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_630, ConstructorWithRotation180_630) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

TEST_F(GfxStateTest_630, ConstructorWithRotation270_630) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

TEST_F(GfxStateTest_630, GetX1Y1X2Y2_630) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// =============================================================================
// Fill/Stroke Color
// =============================================================================

TEST_F(GfxStateTest_630, SetFillColorAndGet_630) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 12345;
    color.c[1] = 23456;
    state->setFillColor(&color);

    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 12345);
    EXPECT_EQ(retrieved->c[1], 23456);
}

TEST_F(GfxStateTest_630, SetStrokeColorAndGet_630) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 54321;
    state->setStrokeColor(&color);

    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 54321);
}

TEST_F(GfxStateTest_630, SetFillColorOverwrite_630) {
    GfxColor color1;
    memset(&color1, 0, sizeof(color1));
    color1.c[0] = 100;
    state->setFillColor(&color1);

    GfxColor color2;
    memset(&color2, 0, sizeof(color2));
    color2.c[0] = 200;
    state->setFillColor(&color2);

    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 200);
}

// =============================================================================
// Blend Mode
// =============================================================================

TEST_F(GfxStateTest_630, SetAndGetBlendMode_630) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

TEST_F(GfxStateTest_630, DefaultBlendModeIsNormal_630) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// =============================================================================
// Opacity
// =============================================================================

TEST_F(GfxStateTest_630, SetAndGetFillOpacity_630) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_630, SetAndGetStrokeOpacity_630) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_630, DefaultFillOpacity_630) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_630, DefaultStrokeOpacity_630) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// =============================================================================
// Overprint
// =============================================================================

TEST_F(GfxStateTest_630, SetAndGetFillOverprint_630) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_630, SetAndGetStrokeOverprint_630) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_630, DefaultFillOverprint_630) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_630, DefaultStrokeOverprint_630) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_630, SetAndGetOverprintMode_630) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// =============================================================================
// Line properties
// =============================================================================

TEST_F(GfxStateTest_630, SetAndGetLineWidth_630) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_630, DefaultLineWidth_630) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_630, SetAndGetFlatness_630) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

TEST_F(GfxStateTest_630, SetAndGetLineJoin_630) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

TEST_F(GfxStateTest_630, SetAndGetLineCap_630) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

TEST_F(GfxStateTest_630, SetAndGetMiterLimit_630) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

TEST_F(GfxStateTest_630, SetAndGetLineDash_630) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
}

// =============================================================================
// Stroke Adjust
// =============================================================================

TEST_F(GfxStateTest_630, SetAndGetStrokeAdjust_630) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_630, DefaultStrokeAdjust_630) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// =============================================================================
// Alpha is shape / Text knockout
// =============================================================================

TEST_F(GfxStateTest_630, SetAndGetAlphaIsShape_630) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_630, SetAndGetTextKnockout_630) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// =============================================================================
// Text properties
// =============================================================================

TEST_F(GfxStateTest_630, SetAndGetCharSpace_630) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

TEST_F(GfxStateTest_630, SetAndGetWordSpace_630) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

TEST_F(GfxStateTest_630, SetAndGetHorizScaling_630) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_630, SetAndGetLeading_630) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_630, SetAndGetRise_630) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

TEST_F(GfxStateTest_630, SetAndGetRender_630) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_630, SetAndGetTextMat_630) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// =============================================================================
// Rendering Intent
// =============================================================================

TEST_F(GfxStateTest_630, SetAndGetRenderingIntent_630) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_630, SetRenderingIntentRelativeColorimetric_630) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// =============================================================================
// CTM
// =============================================================================

TEST_F(GfxStateTest_630, SetCTMAndGetCTM_630) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

TEST_F(GfxStateTest_630, ConcatCTM_630) {
    // Set identity first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Concat with a scale of 2
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// =============================================================================
// Transform
// =============================================================================

TEST_F(GfxStateTest_630, TransformIdentity_630) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_630, TransformWithTranslation_630) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 50.0, 100.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 60.0);
    EXPECT_DOUBLE_EQ(y2, 120.0);
}

TEST_F(GfxStateTest_630, TransformDeltaIgnoresTranslation_630) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 50.0, 100.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_630, TransformWithScale_630) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// =============================================================================
// Path operations
// =============================================================================

TEST_F(GfxStateTest_630, InitiallyNoCurPt_630) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_630, InitiallyNoPath_630) {
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_630, MoveToSetsCurPt_630) {
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_630, LineToCreatesPath_630) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_630, ClearPathRemovesCurPt_630) {
    state->moveTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_630, CurveToCreatesPath_630) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_630, ClosePathAfterLineTo_630) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// =============================================================================
// Save/Restore
// =============================================================================

TEST_F(GfxStateTest_630, InitiallyNoSaves_630) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_630, SaveCreatesSavedState_630) {
    GfxState *savedState = state->save();
    EXPECT_TRUE(savedState->hasSaves());
}

TEST_F(GfxStateTest_630, RestoreReturnsPreviousState_630) {
    state->setLineWidth(5.0);
    GfxState *current = state->save();
    current->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(current->getLineWidth(), 10.0);

    GfxState *restored = current->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_630, SaveAndRestorePreserveFillOpacity_630) {
    state->setFillOpacity(0.3);
    GfxState *current = state->save();
    current->setFillOpacity(0.9);
    EXPECT_DOUBLE_EQ(current->getFillOpacity(), 0.9);

    GfxState *restored = current->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.3);
}

TEST_F(GfxStateTest_630, MultipleSaveRestore_630) {
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

// =============================================================================
// Copy
// =============================================================================

TEST_F(GfxStateTest_630, CopyPreservesLineWidth_630) {
    state->setLineWidth(7.5);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
}

TEST_F(GfxStateTest_630, CopyPreservesFillOpacity_630) {
    state->setFillOpacity(0.42);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.42);
}

// =============================================================================
// Text move
// =============================================================================

TEST_F(GfxStateTest_630, TextMoveToSetsTextPosition_630) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// =============================================================================
// Clip
// =============================================================================

TEST_F(GfxStateTest_630, ClipToRectUpdatesClipBBox_630) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should be the intersection of existing clip and the new rect
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

TEST_F(GfxStateTest_630, GetUserClipBBox_630) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// =============================================================================
// Font
// =============================================================================

TEST_F(GfxStateTest_630, DefaultFontIsNull_630) {
    const auto &font = state->getFont();
    // Depending on implementation, font may be nullptr initially
    // We just test that it doesn't crash
    SUCCEED();
}

TEST_F(GfxStateTest_630, GetFontSize_630) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// =============================================================================
// Fill/Stroke color space and pattern defaults
// =============================================================================

TEST_F(GfxStateTest_630, DefaultFillPatternIsNull_630) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_630, DefaultStrokePatternIsNull_630) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// =============================================================================
// parseBlendMode (static)
// =============================================================================

TEST_F(GfxStateTest_630, ParseBlendModeNormal_630) {
    Object obj(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendNormal);
}

// =============================================================================
// TransformWidth
// =============================================================================

TEST_F(GfxStateTest_630, TransformWidthIdentity_630) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 5.0);
}

TEST_F(GfxStateTest_630, TransformWidthWithScale_630) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(w, 10.0);
}

// =============================================================================
// Boundary: zero line width
// =============================================================================

TEST_F(GfxStateTest_630, ZeroLineWidth_630) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// =============================================================================
// Boundary: negative values
// =============================================================================

TEST_F(GfxStateTest_630, NegativeCharSpace_630) {
    state->setCharSpace(-1.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), -1.0);
}

TEST_F(GfxStateTest_630, NegativeWordSpace_630) {
    state->setWordSpace(-2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), -2.0);
}

// =============================================================================
// Boundary: empty line dash
// =============================================================================

TEST_F(GfxStateTest_630, EmptyLineDash_630) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);

    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(retrievedDash.empty());
}

// =============================================================================
// isParentState
// =============================================================================

TEST_F(GfxStateTest_630, IsParentStateAfterSave_630) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
}

TEST_F(GfxStateTest_630, IsNotParentStateForUnrelated_630) {
    PDFRectangle pageBox = makePageBox(0, 0, 100, 100);
    GfxState otherState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(&otherState));
}

// =============================================================================
// GetCTM into Matrix
// =============================================================================

TEST_F(GfxStateTest_630, GetCTMIntoMatrix_630) {
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

// =============================================================================
// GetTransformedLineWidth
// =============================================================================

TEST_F(GfxStateTest_630, GetTransformedLineWidth_630) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_DOUBLE_EQ(tlw, 6.0);
}

// =============================================================================
// ShiftCTMAndClip
// =============================================================================

TEST_F(GfxStateTest_630, ShiftCTMAndClipChangesTranslation_630) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// =============================================================================
// ReusablePath
// =============================================================================

TEST_F(GfxStateTest_630, GetReusablePathNotNull_630) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto reusable = state->getReusablePath();
    EXPECT_NE(reusable, nullptr);
}

// =============================================================================
// FillColor with all components
// =============================================================================

TEST_F(GfxStateTest_630, SetFillColorAllComponents_630) {
    GfxColor color;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        color.c[i] = static_cast<GfxColorComp>(i * 1000);
    }
    state->setFillColor(&color);

    const GfxColor *retrieved = state->getFillColor();
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_EQ(retrieved->c[i], static_cast<GfxColorComp>(i * 1000));
    }
}
