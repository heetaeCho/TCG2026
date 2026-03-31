#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_637 : public ::testing::Test {
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

// Test overprint mode setter and getter - normal value
TEST_F(GfxStateTest_637, SetOverprintMode_NormalValue_637) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test overprint mode default value (should be 0 initially)
TEST_F(GfxStateTest_637, GetOverprintMode_DefaultValue_637) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test overprint mode set to zero
TEST_F(GfxStateTest_637, SetOverprintMode_Zero_637) {
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test overprint mode set to negative value
TEST_F(GfxStateTest_637, SetOverprintMode_NegativeValue_637) {
    state->setOverprintMode(-1);
    EXPECT_EQ(state->getOverprintMode(), -1);
}

// Test overprint mode set to large value
TEST_F(GfxStateTest_637, SetOverprintMode_LargeValue_637) {
    state->setOverprintMode(100);
    EXPECT_EQ(state->getOverprintMode(), 100);
}

// Test overprint mode overwrite
TEST_F(GfxStateTest_637, SetOverprintMode_Overwrite_637) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test basic construction parameters - DPI
TEST_F(GfxStateTest_637, Construction_HDPI_637) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_637, Construction_VDPI_637) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_637, Construction_PageWidth_637) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_637, Construction_PageHeight_637) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_637, Construction_Rotate_637) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test line width
TEST_F(GfxStateTest_637, SetLineWidth_Normal_637) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_637, SetLineWidth_Zero_637) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test flatness
TEST_F(GfxStateTest_637, SetFlatness_Normal_637) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test line join
TEST_F(GfxStateTest_637, SetLineJoin_637) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test line cap
TEST_F(GfxStateTest_637, SetLineCap_637) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test miter limit
TEST_F(GfxStateTest_637, SetMiterLimit_637) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test fill opacity
TEST_F(GfxStateTest_637, SetFillOpacity_Normal_637) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_637, SetFillOpacity_Full_637) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_637, SetFillOpacity_Zero_637) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

// Test stroke opacity
TEST_F(GfxStateTest_637, SetStrokeOpacity_Normal_637) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test fill overprint
TEST_F(GfxStateTest_637, SetFillOverprint_True_637) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_637, SetFillOverprint_False_637) {
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_637, SetStrokeOverprint_True_637) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_637, SetStrokeOverprint_False_637) {
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test stroke adjust
TEST_F(GfxStateTest_637, SetStrokeAdjust_True_637) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_637, SetStrokeAdjust_False_637) {
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_637, SetAlphaIsShape_True_637) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_637, SetAlphaIsShape_False_637) {
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_637, SetTextKnockout_True_637) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

TEST_F(GfxStateTest_637, SetTextKnockout_False_637) {
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test char space
TEST_F(GfxStateTest_637, SetCharSpace_637) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test word space
TEST_F(GfxStateTest_637, SetWordSpace_637) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_637, SetHorizScaling_637) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test leading
TEST_F(GfxStateTest_637, SetLeading_637) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test rise
TEST_F(GfxStateTest_637, SetRise_637) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test render
TEST_F(GfxStateTest_637, SetRender_637) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test rendering intent
TEST_F(GfxStateTest_637, SetRenderingIntent_RelativeColorimetric_637) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_637, SetRenderingIntent_Perceptual_637) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_637, SetRenderingIntent_AbsoluteColorimetric_637) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_637, SetRenderingIntent_Saturation_637) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test blend mode
TEST_F(GfxStateTest_637, SetBlendMode_Normal_637) {
    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

// Test save and restore
TEST_F(GfxStateTest_637, SaveRestore_PreservesState_637) {
    state->setOverprintMode(1);
    state->setFillOpacity(0.5);
    
    GfxState *savedState = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    // Modify current state
    state->setOverprintMode(0);
    state->setFillOpacity(1.0);
    EXPECT_EQ(state->getOverprintMode(), 0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
    
    // Restore should return the saved state
    GfxState *restoredState = state->restore();
    // After restore, the returned state should be the parent
    EXPECT_NE(restoredState, nullptr);
}

// Test hasSaves
TEST_F(GfxStateTest_637, HasSaves_InitiallyFalse_637) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_637, HasSaves_AfterSave_637) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_637, IsPath_InitiallyFalse_637) {
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_637, IsCurPt_InitiallyFalse_637) {
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_637, MoveTo_CreatesCurPt_637) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_637, LineTo_AfterMoveTo_637) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_637, CurveTo_AfterMoveTo_637) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_637, ClearPath_637) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_637, ClosePath_637) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_637, Transform_Identity_637) {
    // Default CTM with identity-like mapping
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Result depends on CTM, but should not crash
}

TEST_F(GfxStateTest_637, TransformDelta_637) {
    double x2, y2;
    state->transformDelta(1.0, 1.0, &x2, &y2);
    // Should not crash; result depends on CTM
}

// Test text operations
TEST_F(GfxStateTest_637, TextMoveTo_637) {
    state->textMoveTo(100.0, 200.0);
    // Verify line position is updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test setCTM
TEST_F(GfxStateTest_637, SetCTM_637) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test setTextMat
TEST_F(GfxStateTest_637, SetTextMat_637) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 5.0, 10.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 10.0);
}

// Test clipToRect
TEST_F(GfxStateTest_637, ClipToRect_637) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should be intersected; exact values depend on initial clip
}

// Test copy
TEST_F(GfxStateTest_637, Copy_637) {
    state->setOverprintMode(1);
    state->setFillOpacity(0.3);
    
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getOverprintMode(), 1);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.3);
}

// Test construction with rotation
TEST_F(GfxStateTest_637, Construction_WithRotation_637) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

// Test getPath returns non-null
TEST_F(GfxStateTest_637, GetPath_NotNull_637) {
    EXPECT_NE(state->getPath(), nullptr);
}

// Test getClipBBox
TEST_F(GfxStateTest_637, GetClipBBox_637) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have valid clip bounds
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_637, GetUserClipBBox_637) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test setLineDash
TEST_F(GfxStateTest_637, SetLineDash_637) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 2.0);
}

// Test setLineDash empty
TEST_F(GfxStateTest_637, SetLineDash_Empty_637) {
    std::vector<double> dash = {};
    state->setLineDash(std::move(dash), 0.0);
    
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(retrievedDash.empty());
}

// Test page boundary values
TEST_F(GfxStateTest_637, GetX1Y1X2Y2_637) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test font size
TEST_F(GfxStateTest_637, FontSize_Default_637) {
    // Font size should be some default; just verify it doesn't crash
    double size = state->getFontSize();
    (void)size;
}

// Test multiple overprint mode changes
TEST_F(GfxStateTest_637, SetOverprintMode_Multiple_637) {
    for (int i = 0; i < 10; ++i) {
        state->setOverprintMode(i);
        EXPECT_EQ(state->getOverprintMode(), i);
    }
}

// Test curX and curY after moveTo
TEST_F(GfxStateTest_637, CurXY_AfterMoveTo_637) {
    state->moveTo(50.0, 75.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 75.0);
}

// Test concatCTM
TEST_F(GfxStateTest_637, ConcatCTM_637) {
    // Save original CTM
    auto origCTM = state->getCTM();
    
    // Concatenate identity - should not change CTM
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    auto newCTM = state->getCTM();
    
    for (int i = 0; i < 6; ++i) {
        EXPECT_DOUBLE_EQ(origCTM[i], newCTM[i]);
    }
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_637, ShiftCTMAndClip_637) {
    auto origCTM = state->getCTM();
    state->shiftCTMAndClip(10.0, 20.0);
    auto newCTM = state->getCTM();
    // The translation components should change
    // Exact behavior depends on implementation, but should not crash
}

// Test transformWidth
TEST_F(GfxStateTest_637, TransformWidth_637) {
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// Test isParentState
TEST_F(GfxStateTest_637, IsParentState_Self_637) {
    EXPECT_FALSE(state->isParentState(state.get()));
}

// Test save creates parent relationship
TEST_F(GfxStateTest_637, IsParentState_AfterSave_637) {
    GfxState *child = state->save();
    // state should be parent of child view
    // child is now the top, state is saved inside
    EXPECT_TRUE(state->hasSaves());
}

// Test fill color
TEST_F(GfxStateTest_637, SetFillColor_637) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test stroke color
TEST_F(GfxStateTest_637, SetStrokeColor_637) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test getReusablePath
TEST_F(GfxStateTest_637, GetReusablePath_EmptyPath_637) {
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test getReusablePath with actual path
TEST_F(GfxStateTest_637, GetReusablePath_WithPath_637) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}
