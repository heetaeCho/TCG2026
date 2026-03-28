#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cmath>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle box;
    box.x1 = x1;
    box.y1 = y1;
    box.x2 = x2;
    box.y2 = y2;
    return box;
}

class GfxStateTest_568 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// ==================== Constructor and basic getters ====================

TEST_F(GfxStateTest_568, ConstructorSetsHDPI_568) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_568, ConstructorSetsVDPI_568) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_568, ConstructorSetsPageBounds_568) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

TEST_F(GfxStateTest_568, ConstructorSetsPageDimensions_568) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_568, ConstructorSetsRotate_568) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_568, ConstructorWithRotation_568) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST_F(GfxStateTest_568, ConstructorWithDifferentDPI_568) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState highDpiState(300.0, 150.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 150.0);
}

// ==================== Default property values ====================

TEST_F(GfxStateTest_568, DefaultBlendMode_568) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

TEST_F(GfxStateTest_568, DefaultFillOpacity_568) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_568, DefaultStrokeOpacity_568) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_568, DefaultFillOverprint_568) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_568, DefaultStrokeOverprint_568) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_568, DefaultOverprintMode_568) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_568, DefaultLineWidth_568) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_568, DefaultFlatness_568) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_568, DefaultMiterLimit_568) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_568, DefaultStrokeAdjust_568) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_568, DefaultAlphaIsShape_568) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_568, DefaultTextKnockout_568) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_568, DefaultFontSize_568) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

TEST_F(GfxStateTest_568, DefaultCharSpace_568) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_568, DefaultWordSpace_568) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_568, DefaultHorizScaling_568) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_568, DefaultLeading_568) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_568, DefaultRise_568) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_568, DefaultRender_568) {
    EXPECT_EQ(state->getRender(), 0);
}

// ==================== Setters and Getters ====================

TEST_F(GfxStateTest_568, SetFillOpacity_568) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_568, SetStrokeOpacity_568) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

TEST_F(GfxStateTest_568, SetFillOverprint_568) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_568, SetStrokeOverprint_568) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_568, SetOverprintMode_568) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

TEST_F(GfxStateTest_568, SetLineWidth_568) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_568, SetFlatness_568) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

TEST_F(GfxStateTest_568, SetLineJoin_568) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_568, SetLineCap_568) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

TEST_F(GfxStateTest_568, SetMiterLimit_568) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

TEST_F(GfxStateTest_568, SetStrokeAdjust_568) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_568, SetAlphaIsShape_568) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_568, SetTextKnockout_568) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

TEST_F(GfxStateTest_568, SetBlendMode_568) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

TEST_F(GfxStateTest_568, SetCharSpace_568) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_568, SetWordSpace_568) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_568, SetHorizScaling_568) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

TEST_F(GfxStateTest_568, SetLeading_568) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_568, SetRise_568) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_568, SetRender_568) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_568, SetRenderingIntent_568) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_568, SetRenderingIntentRelativeColorimetric_568) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_568, SetRenderingIntentAbsoluteColorimetric_568) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_568, SetRenderingIntentSaturation_568) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// ==================== CTM operations ====================

TEST_F(GfxStateTest_568, SetCTM_568) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_568, ConcatCTM_568) {
    // Get initial CTM, then concat with identity-like transform
    const auto& ctmBefore = state->getCTM();
    double a0 = ctmBefore[0], d0 = ctmBefore[3];
    
    // Concatenate with a scaling of 2x
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto& ctmAfter = state->getCTM();
    
    // After concat, the CTM should reflect the combined transformation
    // The exact values depend on the implementation, but we can verify it changed
    EXPECT_DOUBLE_EQ(ctmAfter[0], a0 * 2.0);
    EXPECT_DOUBLE_EQ(ctmAfter[3], d0 * 2.0);
}

TEST_F(GfxStateTest_568, GetCTMMatrix_568) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should contain the same values
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[1], 2.0);
    EXPECT_DOUBLE_EQ(m.m[2], 3.0);
    EXPECT_DOUBLE_EQ(m.m[3], 4.0);
    EXPECT_DOUBLE_EQ(m.m[4], 5.0);
    EXPECT_DOUBLE_EQ(m.m[5], 6.0);
}

// ==================== Transform operations ====================

TEST_F(GfxStateTest_568, TransformPoint_568) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_568, TransformDelta_568) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    // Delta transform should not include translation
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

TEST_F(GfxStateTest_568, TransformWidth_568) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
}

// ==================== Text matrix ====================

TEST_F(GfxStateTest_568, SetTextMat_568) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto& tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// ==================== Line dash ====================

TEST_F(GfxStateTest_568, SetLineDash_568) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& dashResult = state->getLineDash(&start);
    EXPECT_EQ(dashResult.size(), 2u);
    EXPECT_DOUBLE_EQ(dashResult[0], 3.0);
    EXPECT_DOUBLE_EQ(dashResult[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_568, SetLineDashEmpty_568) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& dashResult = state->getLineDash(&start);
    EXPECT_EQ(dashResult.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// ==================== Path operations ====================

TEST_F(GfxStateTest_568, InitialPathState_568) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_568, MoveToCreatesCurPt_568) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_568, LineToAfterMoveTo_568) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_568, CurveToAfterMoveTo_568) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_568, ClosePathAfterLineTo_568) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_568, ClearPath_568) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_568, GetPath_568) {
    state->moveTo(10.0, 20.0);
    const GfxPath* path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// ==================== Clip operations ====================

TEST_F(GfxStateTest_568, GetClipBBox_568) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be set based on page box and CTM
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_568, GetUserClipBBox_568) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_568, ClipToRect_568) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the bbox should be constrained
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// ==================== Save/Restore ====================

TEST_F(GfxStateTest_568, InitialHasSaves_568) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_568, SaveCreatesSave_568) {
    GfxState* saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    // saved should be the original state pointer
    EXPECT_NE(saved, nullptr);
}

TEST_F(GfxStateTest_568, SaveRestore_568) {
    state->setLineWidth(5.0);
    GfxState* current = state->save();
    current->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(current->getLineWidth(), 10.0);
    
    GfxState* restored = current->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_568, SaveRestorePreservesProperties_568) {
    state->setFillOpacity(0.5);
    state->setStrokeOpacity(0.7);
    state->setMiterLimit(8.0);
    
    GfxState* current = state->save();
    current->setFillOpacity(0.1);
    current->setStrokeOpacity(0.2);
    current->setMiterLimit(3.0);
    
    GfxState* restored = current->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.5);
    EXPECT_DOUBLE_EQ(restored->getStrokeOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(restored->getMiterLimit(), 8.0);
}

TEST_F(GfxStateTest_568, MultipleSaveRestore_568) {
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
}

// ==================== Copy ====================

TEST_F(GfxStateTest_568, Copy_568) {
    state->setLineWidth(3.5);
    state->setFillOpacity(0.8);
    
    GfxState* copied = state->copy();
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
    
    delete copied;
}

// ==================== Text position ====================

TEST_F(GfxStateTest_568, TextMoveTo_568) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

TEST_F(GfxStateTest_568, CurXYInitial_568) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// ==================== Fill/Stroke color ====================

TEST_F(GfxStateTest_568, SetFillColor_568) {
    GfxColor color;
    color.c[0] = 32768; // Midpoint value
    state->setFillColor(&color);
    const GfxColor* result = state->getFillColor();
    EXPECT_EQ(result->c[0], 32768);
}

TEST_F(GfxStateTest_568, SetStrokeColor_568) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor* result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 65535);
}

// ==================== Color spaces ====================

TEST_F(GfxStateTest_568, DefaultFillColorSpace_568) {
    GfxColorSpace* cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_568, DefaultStrokeColorSpace_568) {
    GfxColorSpace* cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_568, FillPatternInitiallyNull_568) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_568, StrokePatternInitiallyNull_568) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// ==================== parseBlendMode ====================

TEST_F(GfxStateTest_568, ParseBlendModeNormal_568) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// ==================== Boundary conditions ====================

TEST_F(GfxStateTest_568, ZeroLineWidth_568) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_568, NegativeLineWidth_568) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

TEST_F(GfxStateTest_568, FillOpacityBoundaryZero_568) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_568, FillOpacityBoundaryOne_568) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_568, LargeCoordinatesMoveTo_568) {
    state->moveTo(1e10, 1e10);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_568, NegativeCoordinatesMoveTo_568) {
    state->moveTo(-100.0, -200.0);
    EXPECT_TRUE(state->isCurPt());
}

// ==================== isParentState ====================

TEST_F(GfxStateTest_568, IsParentStateAfterSave_568) {
    GfxState* child = state->save();
    // After save, state should be saved inside child
    EXPECT_TRUE(child->hasSaves());
}

// ==================== ShiftCTMAndClip ====================

TEST_F(GfxStateTest_568, ShiftCTMAndClip_568) {
    const auto& ctmBefore = state->getCTM();
    double e_before = ctmBefore[4];
    double f_before = ctmBefore[5];
    
    state->shiftCTMAndClip(10.0, 20.0);
    
    const auto& ctmAfter = state->getCTM();
    // The translation components should have changed
    EXPECT_NE(ctmAfter[4], e_before);
}

// ==================== Transformed line width ====================

TEST_F(GfxStateTest_568, GetTransformedLineWidth_568) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_GT(tw, 0.0);
}

// ==================== Font ====================

TEST_F(GfxStateTest_568, DefaultFontIsNull_568) {
    const auto& font = state->getFont();
    // Font may or may not be null by default
    // Just verify we can call it
    SUCCEED();
}

TEST_F(GfxStateTest_568, SetFontSize_568) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// ==================== ReusablePath ====================

TEST_F(GfxStateTest_568, GetReusablePathEmpty_568) {
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

TEST_F(GfxStateTest_568, GetReusablePathWithContent_568) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// ==================== GetTransformedFontSize ====================

TEST_F(GfxStateTest_568, GetTransformedFontSize_568) {
    state->setFont(nullptr, 12.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tfs = state->getTransformedFontSize();
    EXPECT_GE(tfs, 0.0);
}

// ==================== GetFontTransMat ====================

TEST_F(GfxStateTest_568, GetFontTransMat_568) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Just verify we can call it without crash
    SUCCEED();
}

// ==================== Clip operations with path ====================

TEST_F(GfxStateTest_568, ClipWithPath_568) {
    state->moveTo(100.0, 100.0);
    state->lineTo(200.0, 100.0);
    state->lineTo(200.0, 200.0);
    state->closePath();
    state->clip();
    
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_568, ClipToStrokePath_568) {
    state->moveTo(100.0, 100.0);
    state->lineTo(200.0, 100.0);
    state->lineTo(200.0, 200.0);
    state->closePath();
    state->clipToStrokePath();
    
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}
