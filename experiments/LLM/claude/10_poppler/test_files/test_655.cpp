#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"
#include "Object.h"

// Helper to create a GfxState with reasonable defaults
static std::unique_ptr<GfxState> createDefaultState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_655 : public ::testing::Test {
protected:
    void SetUp() override {
        state = createDefaultState();
    }

    std::unique_ptr<GfxState> state;
};

// --- Constructor and basic getter tests ---

TEST_F(GfxStateTest_655, ConstructorSetsHDPI_655) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_655, ConstructorSetsVDPI_655) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_655, ConstructorSetsRotate_655) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_655, ConstructorSetsPageDimensions_655) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_655, ConstructorWithRotation_655) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

TEST_F(GfxStateTest_655, GetX1Y1X2Y2_655) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- Line width tests ---

TEST_F(GfxStateTest_655, SetAndGetLineWidth_655) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_655, SetLineWidthZero_655) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// --- Flatness tests ---

TEST_F(GfxStateTest_655, SetAndGetFlatness_655) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// --- Line join/cap tests ---

TEST_F(GfxStateTest_655, SetAndGetLineJoin_655) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

TEST_F(GfxStateTest_655, SetAndGetLineCap_655) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// --- Miter limit tests ---

TEST_F(GfxStateTest_655, SetAndGetMiterLimit_655) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// --- Opacity tests ---

TEST_F(GfxStateTest_655, SetAndGetFillOpacity_655) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_655, SetAndGetStrokeOpacity_655) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

TEST_F(GfxStateTest_655, FillOpacityBoundaryZero_655) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_655, FillOpacityBoundaryOne_655) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// --- Overprint tests ---

TEST_F(GfxStateTest_655, SetAndGetFillOverprint_655) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_655, SetAndGetStrokeOverprint_655) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_655, SetAndGetOverprintMode_655) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- Blend mode tests ---

TEST_F(GfxStateTest_655, SetAndGetBlendMode_655) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

TEST_F(GfxStateTest_655, DefaultBlendModeIsNormal_655) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// --- Text properties tests ---

TEST_F(GfxStateTest_655, SetAndGetCharSpace_655) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_655, SetAndGetWordSpace_655) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_655, SetAndGetHorizScaling_655) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_655, SetAndGetLeading_655) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_655, SetAndGetRise_655) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_655, SetAndGetRender_655) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// --- Text matrix tests ---

TEST_F(GfxStateTest_655, SetAndGetTextMat_655) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 1.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// --- Stroke adjust, alpha is shape, text knockout ---

TEST_F(GfxStateTest_655, SetAndGetStrokeAdjust_655) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_655, SetAndGetAlphaIsShape_655) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_655, SetAndGetTextKnockout_655) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- Rendering intent tests ---

TEST_F(GfxStateTest_655, SetAndGetRenderingIntent_655) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_655, SetRenderingIntentRelativeColorimetric_655) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// --- CTM tests ---

TEST_F(GfxStateTest_655, SetCTM_655) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

TEST_F(GfxStateTest_655, ConcatCTM_655) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// --- Transform tests ---

TEST_F(GfxStateTest_655, TransformIdentityCTM_655) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_655, TransformWithScaling_655) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

TEST_F(GfxStateTest_655, TransformDelta_655) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double dx2, dy2;
    state->transformDelta(5.0, 10.0, &dx2, &dy2);
    EXPECT_DOUBLE_EQ(dx2, 10.0);
    EXPECT_DOUBLE_EQ(dy2, 20.0);
}

// --- Path tests ---

TEST_F(GfxStateTest_655, InitiallyNoPath_655) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_655, MoveToSetsCurPt_655) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_655, LineToAfterMoveTo_655) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 100.0);
}

TEST_F(GfxStateTest_655, CurveToAfterMoveTo_655) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

TEST_F(GfxStateTest_655, ClosePathAfterLines_655) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    // After closePath, cur point should go back to start of subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

TEST_F(GfxStateTest_655, ClearPathResetsState_655) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// --- Save/Restore tests ---

TEST_F(GfxStateTest_655, SaveAndRestore_655) {
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
    
    GfxState *restored = state->restore();
    // After restore, we should be back at the saved state
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 3.0);
}

TEST_F(GfxStateTest_655, HasSavesInitiallyFalse_655) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_655, HasSavesAfterSave_655) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// --- Line dash tests ---

TEST_F(GfxStateTest_655, SetAndGetLineDash_655) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
}

TEST_F(GfxStateTest_655, SetEmptyLineDash_655) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(retrievedDash.empty());
}

// --- Clip tests ---

TEST_F(GfxStateTest_655, ClipToRect_655) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

TEST_F(GfxStateTest_655, GetUserClipBBox_655) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should return some valid bounding box
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Copy test ---

TEST_F(GfxStateTest_655, CopyState_655) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.8);
    
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
}

// --- Text position tests ---

TEST_F(GfxStateTest_655, TextMoveTo_655) {
    state->textMoveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 15.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 25.0);
}

// --- Font tests ---

TEST_F(GfxStateTest_655, SetFontNullptr_655) {
    state->setFont(nullptr, 12.0);
    EXPECT_EQ(state->getFont(), nullptr);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// --- Default color space tests ---

TEST_F(GfxStateTest_655, SetDefaultGrayColorSpaceNull_655) {
    state->setDefaultGrayColorSpace(nullptr);
    auto copy = state->copyDefaultGrayColorSpace();
    EXPECT_EQ(copy, nullptr);
}

TEST_F(GfxStateTest_655, SetDefaultRGBColorSpaceNull_655) {
    state->setDefaultRGBColorSpace(nullptr);
    auto copy = state->copyDefaultRGBColorSpace();
    EXPECT_EQ(copy, nullptr);
}

TEST_F(GfxStateTest_655, SetDefaultCMYKColorSpaceNull_655) {
    state->setDefaultCMYKColorSpace(nullptr);
    auto copy = state->copyDefaultCMYKColorSpace();
    EXPECT_EQ(copy, nullptr);
}

// --- Fill/Stroke color tests ---

TEST_F(GfxStateTest_655, SetAndGetFillColor_655) {
    GfxColor color;
    color.c[0] = 32768; // 0.5 in fixed point
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_655, SetAndGetStrokeColor_655) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 65535);
}

// --- parseBlendMode static method tests ---

TEST_F(GfxStateTest_655, ParseBlendModeNormalFromName_655) {
    Object obj(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendNormal);
}

TEST_F(GfxStateTest_655, ParseBlendModeMultiplyFromName_655) {
    Object obj(objName, "Multiply");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, gfxBlendMultiply);
}

// --- Shift CTM tests ---

TEST_F(GfxStateTest_655, ShiftCTMAndClip_655) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double xMinBefore, yMinBefore, xMaxBefore, yMaxBefore;
    state->getClipBBox(&xMinBefore, &yMinBefore, &xMaxBefore, &yMaxBefore);
    
    state->shiftCTMAndClip(10.0, 20.0);
    
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// --- isParentState tests ---

TEST_F(GfxStateTest_655, IsParentStateAfterSave_655) {
    GfxState *original = state.get();
    GfxState *child = state->save();
    EXPECT_TRUE(state->isParentState(original));
}

// --- Multiple save/restore tests ---

TEST_F(GfxStateTest_655, MultipleSaveRestore_655) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);
    
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    
    GfxState *r1 = state->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
}

// --- GetPath tests ---

TEST_F(GfxStateTest_655, GetPathNotNull_655) {
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// --- ReusablePathIterator tests ---

TEST_F(GfxStateTest_655, GetReusablePathIterator_655) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    ASSERT_NE(iter, nullptr);
}

// --- TransformWidth tests ---

TEST_F(GfxStateTest_655, TransformWidthIdentity_655) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double result = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(GfxStateTest_655, TransformWidthWithScaling_655) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double result = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(result, 10.0);
}

// --- Boundary: very large coordinates ---

TEST_F(GfxStateTest_655, MoveToLargeCoordinates_655) {
    state->moveTo(1e10, 1e10);
    EXPECT_DOUBLE_EQ(state->getCurX(), 1e10);
    EXPECT_DOUBLE_EQ(state->getCurY(), 1e10);
}

// --- Boundary: negative coordinates ---

TEST_F(GfxStateTest_655, MoveToNegativeCoordinates_655) {
    state->moveTo(-100.0, -200.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), -100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), -200.0);
}

// --- GetCTM with Matrix output ---

TEST_F(GfxStateTest_655, GetCTMAsMatrix_655) {
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
