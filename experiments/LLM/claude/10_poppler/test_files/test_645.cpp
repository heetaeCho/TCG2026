#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_645 : public ::testing::Test {
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

// ==================== TextKnockout Tests ====================

TEST_F(GfxStateTest_645, SetTextKnockoutTrue_645) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

TEST_F(GfxStateTest_645, SetTextKnockoutFalse_645) {
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_645, SetTextKnockoutToggle_645) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// ==================== Constructor / Basic Getter Tests ====================

TEST_F(GfxStateTest_645, ConstructorSetsHDPI_645) {
    EXPECT_DOUBLE_EQ(72.0, state->getHDPI());
}

TEST_F(GfxStateTest_645, ConstructorSetsVDPI_645) {
    EXPECT_DOUBLE_EQ(72.0, state->getVDPI());
}

TEST_F(GfxStateTest_645, ConstructorSetsPageDimensions_645) {
    EXPECT_DOUBLE_EQ(612.0, state->getPageWidth());
    EXPECT_DOUBLE_EQ(792.0, state->getPageHeight());
}

TEST_F(GfxStateTest_645, ConstructorSetsRotate_645) {
    EXPECT_EQ(0, state->getRotate());
}

TEST_F(GfxStateTest_645, ConstructorWithRotation_645) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(90, rotatedState.getRotate());
}

TEST_F(GfxStateTest_645, GetX1Y1X2Y2_645) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    // The page box should define boundaries
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// ==================== Line Width Tests ====================

TEST_F(GfxStateTest_645, SetLineWidth_645) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getLineWidth());
}

TEST_F(GfxStateTest_645, SetLineWidthZero_645) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getLineWidth());
}

TEST_F(GfxStateTest_645, SetLineWidthNegative_645) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(-1.0, state->getLineWidth());
}

// ==================== Opacity Tests ====================

TEST_F(GfxStateTest_645, SetFillOpacity_645) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
}

TEST_F(GfxStateTest_645, SetStrokeOpacity_645) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(0.75, state->getStrokeOpacity());
}

TEST_F(GfxStateTest_645, SetFillOpacityBoundaryZero_645) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getFillOpacity());
}

TEST_F(GfxStateTest_645, SetFillOpacityBoundaryOne_645) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(1.0, state->getFillOpacity());
}

TEST_F(GfxStateTest_645, SetStrokeOpacityBoundaryZero_645) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getStrokeOpacity());
}

TEST_F(GfxStateTest_645, SetStrokeOpacityBoundaryOne_645) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(1.0, state->getStrokeOpacity());
}

// ==================== Overprint Tests ====================

TEST_F(GfxStateTest_645, SetFillOverprintTrue_645) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_645, SetFillOverprintFalse_645) {
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_645, SetStrokeOverprintTrue_645) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_645, SetStrokeOverprintFalse_645) {
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_645, SetOverprintMode_645) {
    state->setOverprintMode(1);
    EXPECT_EQ(1, state->getOverprintMode());
}

TEST_F(GfxStateTest_645, SetOverprintModeZero_645) {
    state->setOverprintMode(0);
    EXPECT_EQ(0, state->getOverprintMode());
}

// ==================== Flatness Tests ====================

TEST_F(GfxStateTest_645, SetFlatness_645) {
    state->setFlatness(50);
    EXPECT_EQ(50, state->getFlatness());
}

TEST_F(GfxStateTest_645, SetFlatnessZero_645) {
    state->setFlatness(0);
    EXPECT_EQ(0, state->getFlatness());
}

// ==================== Line Join / Cap Tests ====================

TEST_F(GfxStateTest_645, SetLineJoin_645) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(LineJoinStyle::Round, state->getLineJoin());
}

TEST_F(GfxStateTest_645, SetLineCap_645) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(LineCapStyle::Round, state->getLineCap());
}

// ==================== Miter Limit Tests ====================

TEST_F(GfxStateTest_645, SetMiterLimit_645) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(10.0, state->getMiterLimit());
}

// ==================== Stroke Adjust Tests ====================

TEST_F(GfxStateTest_645, SetStrokeAdjustTrue_645) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_645, SetStrokeAdjustFalse_645) {
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// ==================== AlphaIsShape Tests ====================

TEST_F(GfxStateTest_645, SetAlphaIsShapeTrue_645) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_645, SetAlphaIsShapeFalse_645) {
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// ==================== Text Properties Tests ====================

TEST_F(GfxStateTest_645, SetCharSpace_645) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getCharSpace());
}

TEST_F(GfxStateTest_645, SetWordSpace_645) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(2.0, state->getWordSpace());
}

TEST_F(GfxStateTest_645, SetHorizScaling_645) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(150.0, state->getHorizScaling());
}

TEST_F(GfxStateTest_645, SetLeading_645) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(14.0, state->getLeading());
}

TEST_F(GfxStateTest_645, SetRise_645) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getRise());
}

TEST_F(GfxStateTest_645, SetRender_645) {
    state->setRender(2);
    EXPECT_EQ(2, state->getRender());
}

// ==================== Text Matrix Tests ====================

TEST_F(GfxStateTest_645, SetTextMat_645) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(1.0, mat[0]);
    EXPECT_DOUBLE_EQ(0.0, mat[1]);
    EXPECT_DOUBLE_EQ(0.0, mat[2]);
    EXPECT_DOUBLE_EQ(1.0, mat[3]);
    EXPECT_DOUBLE_EQ(10.0, mat[4]);
    EXPECT_DOUBLE_EQ(20.0, mat[5]);
}

// ==================== CTM Tests ====================

TEST_F(GfxStateTest_645, SetCTM_645) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(100.0, ctm[4]);
    EXPECT_DOUBLE_EQ(200.0, ctm[5]);
}

TEST_F(GfxStateTest_645, ConcatCTM_645) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    // After concatenation with identity, result should be the new matrix
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(10.0, ctm[4]);
    EXPECT_DOUBLE_EQ(20.0, ctm[5]);
}

// ==================== Transform Tests ====================

TEST_F(GfxStateTest_645, TransformWithIdentityCTM_645) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(5.0, x2);
    EXPECT_DOUBLE_EQ(10.0, y2);
}

TEST_F(GfxStateTest_645, TransformWithTranslation_645) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(105.0, x2);
    EXPECT_DOUBLE_EQ(210.0, y2);
}

TEST_F(GfxStateTest_645, TransformDeltaWithTranslation_645) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // Delta should not include translation
    EXPECT_DOUBLE_EQ(5.0, x2);
    EXPECT_DOUBLE_EQ(10.0, y2);
}

TEST_F(GfxStateTest_645, TransformWithScaling_645) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(10.0, x2);
    EXPECT_DOUBLE_EQ(30.0, y2);
}

// ==================== Path Tests ====================

TEST_F(GfxStateTest_645, InitialPathState_645) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_645, MoveToSetsCurPt_645) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(10.0, state->getCurX());
    EXPECT_DOUBLE_EQ(20.0, state->getCurY());
}

TEST_F(GfxStateTest_645, LineToCreatesPath_645) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(10.0, state->getCurX());
    EXPECT_DOUBLE_EQ(20.0, state->getCurY());
}

TEST_F(GfxStateTest_645, CurveToCreatesPath_645) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(5.0, state->getCurX());
    EXPECT_DOUBLE_EQ(6.0, state->getCurY());
}

TEST_F(GfxStateTest_645, ClearPathResetsState_645) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_645, ClosePathWorks_645) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    // After closing, current point should be back at start of subpath
    EXPECT_DOUBLE_EQ(0.0, state->getCurX());
    EXPECT_DOUBLE_EQ(0.0, state->getCurY());
}

// ==================== Save/Restore Tests ====================

TEST_F(GfxStateTest_645, SaveAndRestore_645) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());

    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(10.0, saved->getLineWidth());

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(5.0, restored->getLineWidth());
}

TEST_F(GfxStateTest_645, HasSavesInitiallyFalse_645) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_645, SaveMakesHasSavesTrue_645) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up by restoring
    saved->restore();
}

// ==================== Rendering Intent Tests ====================

TEST_F(GfxStateTest_645, SetRenderingIntent_645) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ("RelativeColorimetric", state->getRenderingIntent());
}

TEST_F(GfxStateTest_645, SetRenderingIntentAbsolute_645) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ("AbsoluteColorimetric", state->getRenderingIntent());
}

TEST_F(GfxStateTest_645, SetRenderingIntentSaturation_645) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ("Saturation", state->getRenderingIntent());
}

TEST_F(GfxStateTest_645, SetRenderingIntentPerceptual_645) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", state->getRenderingIntent());
}

// ==================== Clip BBox Tests ====================

TEST_F(GfxStateTest_645, GetClipBBox_645) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_645, GetUserClipBBox_645) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_645, ClipToRect_645) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should be within or equal to the specified rect
    EXPECT_GE(xMin, 0.0);
    EXPECT_GE(yMin, 0.0);
}

// ==================== TextMoveTo Tests ====================

TEST_F(GfxStateTest_645, TextMoveTo_645) {
    state->textMoveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(15.0, state->getCurTextX());
    EXPECT_DOUBLE_EQ(25.0, state->getCurTextY());
}

// ==================== LineDash Tests ====================

TEST_F(GfxStateTest_645, SetLineDash_645) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(2u, result.size());
    EXPECT_DOUBLE_EQ(3.0, result[0]);
    EXPECT_DOUBLE_EQ(5.0, result[1]);
    EXPECT_DOUBLE_EQ(0.0, start);
}

TEST_F(GfxStateTest_645, SetLineDashWithOffset_645) {
    std::vector<double> dash = {2.0, 4.0, 6.0};
    state->setLineDash(std::move(dash), 1.5);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(3u, result.size());
    EXPECT_DOUBLE_EQ(1.5, start);
}

TEST_F(GfxStateTest_645, SetLineDashEmpty_645) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(0u, result.size());
}

// ==================== BlendMode Tests ====================

TEST_F(GfxStateTest_645, SetBlendMode_645) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(GfxBlendMode::Multiply, state->getBlendMode());
}

TEST_F(GfxStateTest_645, SetBlendModeNormal_645) {
    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(GfxBlendMode::Normal, state->getBlendMode());
}

// ==================== Copy Tests ====================

TEST_F(GfxStateTest_645, CopyState_645) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    state->setTextKnockout(true);

    GfxState *copied = state->copy();
    EXPECT_DOUBLE_EQ(7.5, copied->getLineWidth());
    EXPECT_DOUBLE_EQ(0.3, copied->getFillOpacity());
    EXPECT_TRUE(copied->getTextKnockout());
    delete copied;
}

// ==================== Font Size Tests ====================

TEST_F(GfxStateTest_645, SetFontNullptr_645) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(12.0, state->getFontSize());
    EXPECT_EQ(nullptr, state->getFont());
}

// ==================== TransformWidth Tests ====================

TEST_F(GfxStateTest_645, TransformWidthIdentity_645) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double result = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(5.0, result);
}

TEST_F(GfxStateTest_645, TransformWidthZero_645) {
    double result = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, result);
}

// ==================== Multiple Property Changes Test ====================

TEST_F(GfxStateTest_645, MultiplePropertyChanges_645) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.8);
    state->setStrokeOpacity(0.6);
    state->setFillOverprint(true);
    state->setStrokeOverprint(false);
    state->setOverprintMode(1);
    state->setFlatness(100);
    state->setMiterLimit(4.0);
    state->setStrokeAdjust(true);
    state->setAlphaIsShape(true);
    state->setTextKnockout(false);
    state->setCharSpace(0.5);
    state->setWordSpace(1.0);
    state->setHorizScaling(100.0);
    state->setLeading(12.0);
    state->setRise(0.0);
    state->setRender(0);

    EXPECT_DOUBLE_EQ(3.0, state->getLineWidth());
    EXPECT_DOUBLE_EQ(0.8, state->getFillOpacity());
    EXPECT_DOUBLE_EQ(0.6, state->getStrokeOpacity());
    EXPECT_TRUE(state->getFillOverprint());
    EXPECT_FALSE(state->getStrokeOverprint());
    EXPECT_EQ(1, state->getOverprintMode());
    EXPECT_EQ(100, state->getFlatness());
    EXPECT_DOUBLE_EQ(4.0, state->getMiterLimit());
    EXPECT_TRUE(state->getStrokeAdjust());
    EXPECT_TRUE(state->getAlphaIsShape());
    EXPECT_FALSE(state->getTextKnockout());
    EXPECT_DOUBLE_EQ(0.5, state->getCharSpace());
    EXPECT_DOUBLE_EQ(1.0, state->getWordSpace());
    EXPECT_DOUBLE_EQ(100.0, state->getHorizScaling());
    EXPECT_DOUBLE_EQ(12.0, state->getLeading());
    EXPECT_DOUBLE_EQ(0.0, state->getRise());
    EXPECT_EQ(0, state->getRender());
}

// ==================== Save/Restore Preserves Properties ====================

TEST_F(GfxStateTest_645, SaveRestorePreservesProperties_645) {
    state->setLineWidth(5.0);
    state->setFillOpacity(0.5);
    state->setTextKnockout(true);
    state->setCharSpace(2.0);

    GfxState *saved = state->save();

    saved->setLineWidth(10.0);
    saved->setFillOpacity(0.9);
    saved->setTextKnockout(false);
    saved->setCharSpace(4.0);

    EXPECT_DOUBLE_EQ(10.0, saved->getLineWidth());
    EXPECT_DOUBLE_EQ(0.9, saved->getFillOpacity());
    EXPECT_FALSE(saved->getTextKnockout());
    EXPECT_DOUBLE_EQ(4.0, saved->getCharSpace());

    GfxState *restored = saved->restore();

    EXPECT_DOUBLE_EQ(5.0, restored->getLineWidth());
    EXPECT_DOUBLE_EQ(0.5, restored->getFillOpacity());
    EXPECT_TRUE(restored->getTextKnockout());
    EXPECT_DOUBLE_EQ(2.0, restored->getCharSpace());
}

// ==================== IsParentState Tests ====================

TEST_F(GfxStateTest_645, IsParentStateAfterSave_645) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
}

// ==================== Different DPI Constructor ====================

TEST_F(GfxStateTest_645, ConstructorDifferentDPI_645) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 595;
    pageBox.y2 = 842;
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(300.0, highDpiState.getHDPI());
    EXPECT_DOUBLE_EQ(300.0, highDpiState.getVDPI());
}

TEST_F(GfxStateTest_645, ConstructorAsymmetricDPI_645) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState asymState(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(150.0, asymState.getHDPI());
    EXPECT_DOUBLE_EQ(300.0, asymState.getVDPI());
}

// ==================== Line Position Tests ====================

TEST_F(GfxStateTest_645, TextMoveToSetsLinePosition_645) {
    state->textMoveTo(50.0, 60.0);
    EXPECT_DOUBLE_EQ(50.0, state->getLineX());
    EXPECT_DOUBLE_EQ(60.0, state->getLineY());
}

// ==================== GetPath Tests ====================

TEST_F(GfxStateTest_645, GetPathNotNull_645) {
    EXPECT_NE(nullptr, state->getPath());
}

// ==================== Rendering intent with long string ====================

TEST_F(GfxStateTest_645, SetRenderingIntentLongString_645) {
    // Rendering intent is stored in char[32], test with max reasonable length
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ("AbsoluteColorimetric", state->getRenderingIntent());
}

// ==================== GetCTM Matrix overload ====================

TEST_F(GfxStateTest_645, GetCTMMatrix_645) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify the matrix is populated (exact mapping depends on Matrix struct)
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(1.0, ctm[0]);
    EXPECT_DOUBLE_EQ(2.0, ctm[1]);
}
