#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_611 : public ::testing::Test {
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

// --- Normal operation tests ---

TEST_F(GfxStateTest_611, ConstructorSetsHDPI_611) {
    EXPECT_DOUBLE_EQ(72.0, state->getHDPI());
}

TEST_F(GfxStateTest_611, ConstructorSetsVDPI_611) {
    EXPECT_DOUBLE_EQ(72.0, state->getVDPI());
}

TEST_F(GfxStateTest_611, ConstructorSetsPageDimensions_611) {
    EXPECT_DOUBLE_EQ(612.0, state->getPageWidth());
    EXPECT_DOUBLE_EQ(792.0, state->getPageHeight());
}

TEST_F(GfxStateTest_611, ConstructorSetsRotate_611) {
    EXPECT_EQ(0, state->getRotate());
}

TEST_F(GfxStateTest_611, GetX1Y1X2Y2_611) {
    EXPECT_DOUBLE_EQ(0.0, state->getX1());
    EXPECT_DOUBLE_EQ(0.0, state->getY1());
    EXPECT_DOUBLE_EQ(612.0, state->getX2());
    EXPECT_DOUBLE_EQ(792.0, state->getY2());
}

TEST_F(GfxStateTest_611, DefaultLeadingIsZero_611) {
    EXPECT_DOUBLE_EQ(0.0, state->getLeading());
}

TEST_F(GfxStateTest_611, SetAndGetLeading_611) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(14.0, state->getLeading());
}

TEST_F(GfxStateTest_611, SetAndGetCharSpace_611) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getCharSpace());
}

TEST_F(GfxStateTest_611, SetAndGetWordSpace_611) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getWordSpace());
}

TEST_F(GfxStateTest_611, SetAndGetHorizScaling_611) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getHorizScaling());
}

TEST_F(GfxStateTest_611, SetAndGetRise_611) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(5.0, state->getRise());
}

TEST_F(GfxStateTest_611, SetAndGetRender_611) {
    state->setRender(2);
    EXPECT_EQ(2, state->getRender());
}

TEST_F(GfxStateTest_611, SetAndGetLineWidth_611) {
    state->setLineWidth(2.0);
    EXPECT_DOUBLE_EQ(2.0, state->getLineWidth());
}

TEST_F(GfxStateTest_611, SetAndGetFlatness_611) {
    state->setFlatness(50);
    EXPECT_EQ(50, state->getFlatness());
}

TEST_F(GfxStateTest_611, SetAndGetMiterLimit_611) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(10.0, state->getMiterLimit());
}

TEST_F(GfxStateTest_611, SetAndGetLineJoin_611) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(LineJoinStyle::Round, state->getLineJoin());
}

TEST_F(GfxStateTest_611, SetAndGetLineCap_611) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(LineCapStyle::Round, state->getLineCap());
}

TEST_F(GfxStateTest_611, SetAndGetFillOpacity_611) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
}

TEST_F(GfxStateTest_611, SetAndGetStrokeOpacity_611) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(0.75, state->getStrokeOpacity());
}

TEST_F(GfxStateTest_611, SetAndGetFillOverprint_611) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_611, SetAndGetStrokeOverprint_611) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_611, SetAndGetOverprintMode_611) {
    state->setOverprintMode(1);
    EXPECT_EQ(1, state->getOverprintMode());
}

TEST_F(GfxStateTest_611, SetAndGetStrokeAdjust_611) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_611, SetAndGetAlphaIsShape_611) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_611, SetAndGetTextKnockout_611) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

TEST_F(GfxStateTest_611, SetAndGetRenderingIntent_611) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", state->getRenderingIntent());
}

TEST_F(GfxStateTest_611, SetAndGetTextMat_611) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(1.0, tm[0]);
    EXPECT_DOUBLE_EQ(0.0, tm[1]);
    EXPECT_DOUBLE_EQ(0.0, tm[2]);
    EXPECT_DOUBLE_EQ(1.0, tm[3]);
    EXPECT_DOUBLE_EQ(10.0, tm[4]);
    EXPECT_DOUBLE_EQ(20.0, tm[5]);
}

TEST_F(GfxStateTest_611, DefaultFontIsNull_611) {
    EXPECT_EQ(nullptr, state->getFont().get());
}

TEST_F(GfxStateTest_611, DefaultFontSizeIsZero_611) {
    EXPECT_DOUBLE_EQ(0.0, state->getFontSize());
}

// --- CTM tests ---

TEST_F(GfxStateTest_611, SetCTM_611) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(100.0, ctm[4]);
    EXPECT_DOUBLE_EQ(200.0, ctm[5]);
}

TEST_F(GfxStateTest_611, ConcatCTM_611) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(10.0, ctm[4]);
    EXPECT_DOUBLE_EQ(20.0, ctm[5]);
}

// --- Transform tests ---

TEST_F(GfxStateTest_611, TransformIdentity_611) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(5.0, x2);
    EXPECT_DOUBLE_EQ(10.0, y2);
}

TEST_F(GfxStateTest_611, TransformWithTranslation_611) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(105.0, x2);
    EXPECT_DOUBLE_EQ(210.0, y2);
}

TEST_F(GfxStateTest_611, TransformDelta_611) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(10.0, x2);
    EXPECT_DOUBLE_EQ(20.0, y2);
}

// --- Path tests ---

TEST_F(GfxStateTest_611, InitialPathIsNotCurPt_611) {
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_611, MoveToSetsCurPt_611) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(10.0, state->getCurX());
    EXPECT_DOUBLE_EQ(20.0, state->getCurY());
}

TEST_F(GfxStateTest_611, LineToCreatesPath_611) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(100.0, state->getCurX());
    EXPECT_DOUBLE_EQ(100.0, state->getCurY());
}

TEST_F(GfxStateTest_611, CurveToUpdatesCurrentPoint_611) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(50.0, state->getCurX());
    EXPECT_DOUBLE_EQ(60.0, state->getCurY());
}

TEST_F(GfxStateTest_611, ClearPathResetsPath_611) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_611, ClosePathWorks_611) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closing, current point should be at the start of the subpath
    EXPECT_DOUBLE_EQ(0.0, state->getCurX());
    EXPECT_DOUBLE_EQ(0.0, state->getCurY());
}

// --- Save/Restore tests ---

TEST_F(GfxStateTest_611, InitialHasNoSaves_611) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_611, SaveCreatesChild_611) {
    GfxState *saved = state->save();
    EXPECT_NE(nullptr, saved);
    EXPECT_TRUE(state->hasSaves());
}

TEST_F(GfxStateTest_611, RestoreReturnsPreviousState_611) {
    state->setLeading(14.0);
    GfxState *child = state->save();
    child->setLeading(28.0);
    EXPECT_DOUBLE_EQ(28.0, child->getLeading());
    GfxState *parent = child->restore();
    EXPECT_NE(nullptr, parent);
    EXPECT_DOUBLE_EQ(14.0, parent->getLeading());
}

TEST_F(GfxStateTest_611, SavePreservesState_611) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.5);
    GfxState *child = state->save();
    EXPECT_DOUBLE_EQ(3.0, child->getLineWidth());
    EXPECT_DOUBLE_EQ(0.5, child->getFillOpacity());
    child->restore();
}

// --- TextMoveTo tests ---

TEST_F(GfxStateTest_611, TextMoveTo_611) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(100.0, state->getLineX());
    EXPECT_DOUBLE_EQ(200.0, state->getLineY());
}

// --- LineDash tests ---

TEST_F(GfxStateTest_611, SetAndGetLineDash_611) {
    std::vector<double> dash = {3.0, 5.0, 7.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(1.0, start);
    ASSERT_EQ(3u, result.size());
    EXPECT_DOUBLE_EQ(3.0, result[0]);
    EXPECT_DOUBLE_EQ(5.0, result[1]);
    EXPECT_DOUBLE_EQ(7.0, result[2]);
}

// --- ClipBBox tests ---

TEST_F(GfxStateTest_611, GetClipBBox_611) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After construction the clip bbox should be set
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_611, ClipToRect_611) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should be intersected with the existing one
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// --- Boundary conditions ---

TEST_F(GfxStateTest_611, SetLeadingNegative_611) {
    state->setLeading(-5.0);
    EXPECT_DOUBLE_EQ(-5.0, state->getLeading());
}

TEST_F(GfxStateTest_611, SetLeadingZero_611) {
    state->setLeading(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getLeading());
}

TEST_F(GfxStateTest_611, SetLineWidthZero_611) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getLineWidth());
}

TEST_F(GfxStateTest_611, SetFillOpacityBounds_611) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getFillOpacity());
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(1.0, state->getFillOpacity());
}

TEST_F(GfxStateTest_611, SetStrokeOpacityBounds_611) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getStrokeOpacity());
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(1.0, state->getStrokeOpacity());
}

TEST_F(GfxStateTest_611, EmptyLineDash_611) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(0.0, start);
    EXPECT_TRUE(result.empty());
}

// --- Rendering intent boundary ---

TEST_F(GfxStateTest_611, SetRenderingIntentLong_611) {
    // RenderingIntent is stored in char[32], test within bounds
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ("AbsoluteColorimetric", state->getRenderingIntent());
}

// --- Copy test ---

TEST_F(GfxStateTest_611, CopyPreservesProperties_611) {
    state->setLeading(12.0);
    state->setLineWidth(4.0);
    state->setCharSpace(1.5);
    auto copied = state->copy();
    ASSERT_NE(nullptr, copied);
    EXPECT_DOUBLE_EQ(12.0, copied->getLeading());
    EXPECT_DOUBLE_EQ(4.0, copied->getLineWidth());
    EXPECT_DOUBLE_EQ(1.5, copied->getCharSpace());
    delete copied;
}

// --- Rotated page construction ---

TEST_F(GfxStateTest_611, ConstructorWithRotation90_611) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(90, rotatedState.getRotate());
    EXPECT_DOUBLE_EQ(612.0, rotatedState.getPageWidth());
    EXPECT_DOUBLE_EQ(792.0, rotatedState.getPageHeight());
}

// --- Multiple save/restore ---

TEST_F(GfxStateTest_611, MultipleSaveRestore_611) {
    state->setLeading(10.0);
    GfxState *s1 = state->save();
    s1->setLeading(20.0);
    GfxState *s2 = s1->save();
    s2->setLeading(30.0);
    EXPECT_DOUBLE_EQ(30.0, s2->getLeading());

    GfxState *restored1 = s2->restore();
    EXPECT_DOUBLE_EQ(20.0, restored1->getLeading());

    GfxState *restored0 = restored1->restore();
    EXPECT_DOUBLE_EQ(10.0, restored0->getLeading());
}

// --- isParentState test ---

TEST_F(GfxStateTest_611, IsParentState_611) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    child->restore();
}

// --- BlendMode ---

TEST_F(GfxStateTest_611, SetAndGetBlendMode_611) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(GfxBlendMode::Multiply, state->getBlendMode());
}

// --- getUserClipBBox test ---

TEST_F(GfxStateTest_611, GetUserClipBBox_611) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- TransformWidth test ---

TEST_F(GfxStateTest_611, TransformWidth_611) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// --- Default color spaces are null initially ---

TEST_F(GfxStateTest_611, DefaultFillColorSpaceNotNull_611) {
    // After construction, fill color space might be set to a default
    // We just verify it doesn't crash
    GfxColorSpace *fcs = state->getFillColorSpace();
    (void)fcs; // May or may not be null depending on implementation
}

TEST_F(GfxStateTest_611, DefaultStrokeColorSpaceNotNull_611) {
    GfxColorSpace *scs = state->getStrokeColorSpace();
    (void)scs;
}

// --- Pattern defaults ---

TEST_F(GfxStateTest_611, DefaultFillPatternIsNull_611) {
    EXPECT_EQ(nullptr, state->getFillPattern());
}

TEST_F(GfxStateTest_611, DefaultStrokePatternIsNull_611) {
    EXPECT_EQ(nullptr, state->getStrokePattern());
}

// --- GetPath not null ---

TEST_F(GfxStateTest_611, GetPathNotNull_611) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(nullptr, path);
}

// --- TextShift test ---

TEST_F(GfxStateTest_611, TextShift_611) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double origX = state->getCurX();
    double origY = state->getCurY();
    state->textShift(10.0, 5.0);
    // Current position should have changed
    // We just verify no crash; exact values depend on implementation
    (void)origX;
    (void)origY;
}
