#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_608 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;  // Letter width in points
        pageBox.y2 = 792;  // Letter height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test default char space value
TEST_F(GfxStateTest_608, GetCharSpaceDefault_608) {
    EXPECT_DOUBLE_EQ(0.0, state->getCharSpace());
}

// Test setting and getting char space
TEST_F(GfxStateTest_608, SetCharSpace_608) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getCharSpace());
}

// Test setting char space to negative value
TEST_F(GfxStateTest_608, SetCharSpaceNegative_608) {
    state->setCharSpace(-1.0);
    EXPECT_DOUBLE_EQ(-1.0, state->getCharSpace());
}

// Test setting char space to zero
TEST_F(GfxStateTest_608, SetCharSpaceZero_608) {
    state->setCharSpace(5.0);
    state->setCharSpace(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getCharSpace());
}

// Test setting char space to a large value
TEST_F(GfxStateTest_608, SetCharSpaceLargeValue_608) {
    state->setCharSpace(1e10);
    EXPECT_DOUBLE_EQ(1e10, state->getCharSpace());
}

// Test default word space value
TEST_F(GfxStateTest_608, GetWordSpaceDefault_608) {
    EXPECT_DOUBLE_EQ(0.0, state->getWordSpace());
}

// Test setting and getting word space
TEST_F(GfxStateTest_608, SetWordSpace_608) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getWordSpace());
}

// Test default horiz scaling
TEST_F(GfxStateTest_608, GetHorizScalingDefault_608) {
    EXPECT_DOUBLE_EQ(1.0, state->getHorizScaling());
}

// Test setting horiz scaling
TEST_F(GfxStateTest_608, SetHorizScaling_608) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getHorizScaling());
}

// Test default leading
TEST_F(GfxStateTest_608, GetLeadingDefault_608) {
    EXPECT_DOUBLE_EQ(0.0, state->getLeading());
}

// Test setting leading
TEST_F(GfxStateTest_608, SetLeading_608) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(12.0, state->getLeading());
}

// Test default rise
TEST_F(GfxStateTest_608, GetRiseDefault_608) {
    EXPECT_DOUBLE_EQ(0.0, state->getRise());
}

// Test setting rise
TEST_F(GfxStateTest_608, SetRise_608) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(5.0, state->getRise());
}

// Test default render
TEST_F(GfxStateTest_608, GetRenderDefault_608) {
    EXPECT_EQ(0, state->getRender());
}

// Test setting render
TEST_F(GfxStateTest_608, SetRender_608) {
    state->setRender(2);
    EXPECT_EQ(2, state->getRender());
}

// Test DPI getters
TEST_F(GfxStateTest_608, GetDPI_608) {
    EXPECT_DOUBLE_EQ(72.0, state->getHDPI());
    EXPECT_DOUBLE_EQ(72.0, state->getVDPI());
}

// Test page dimensions
TEST_F(GfxStateTest_608, GetPageDimensions_608) {
    EXPECT_DOUBLE_EQ(612.0, state->getPageWidth());
    EXPECT_DOUBLE_EQ(792.0, state->getPageHeight());
}

// Test rotation
TEST_F(GfxStateTest_608, GetRotate_608) {
    EXPECT_EQ(0, state->getRotate());
}

// Test default line width
TEST_F(GfxStateTest_608, GetLineWidthDefault_608) {
    EXPECT_DOUBLE_EQ(1.0, state->getLineWidth());
}

// Test setting line width
TEST_F(GfxStateTest_608, SetLineWidth_608) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getLineWidth());
}

// Test default flatness
TEST_F(GfxStateTest_608, GetFlatnessDefault_608) {
    EXPECT_EQ(1, state->getFlatness());
}

// Test setting flatness
TEST_F(GfxStateTest_608, SetFlatness_608) {
    state->setFlatness(50);
    EXPECT_EQ(50, state->getFlatness());
}

// Test default miter limit
TEST_F(GfxStateTest_608, GetMiterLimitDefault_608) {
    EXPECT_DOUBLE_EQ(10.0, state->getMiterLimit());
}

// Test setting miter limit
TEST_F(GfxStateTest_608, SetMiterLimit_608) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(5.0, state->getMiterLimit());
}

// Test default fill opacity
TEST_F(GfxStateTest_608, GetFillOpacityDefault_608) {
    EXPECT_DOUBLE_EQ(1.0, state->getFillOpacity());
}

// Test setting fill opacity
TEST_F(GfxStateTest_608, SetFillOpacity_608) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
}

// Test default stroke opacity
TEST_F(GfxStateTest_608, GetStrokeOpacityDefault_608) {
    EXPECT_DOUBLE_EQ(1.0, state->getStrokeOpacity());
}

// Test setting stroke opacity
TEST_F(GfxStateTest_608, SetStrokeOpacity_608) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(0.3, state->getStrokeOpacity());
}

// Test default fill overprint
TEST_F(GfxStateTest_608, GetFillOverprintDefault_608) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setting fill overprint
TEST_F(GfxStateTest_608, SetFillOverprint_608) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_608, GetStrokeOverprintDefault_608) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setting stroke overprint
TEST_F(GfxStateTest_608, SetStrokeOverprint_608) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_608, GetOverprintModeDefault_608) {
    EXPECT_EQ(0, state->getOverprintMode());
}

// Test setting overprint mode
TEST_F(GfxStateTest_608, SetOverprintMode_608) {
    state->setOverprintMode(1);
    EXPECT_EQ(1, state->getOverprintMode());
}

// Test default stroke adjust
TEST_F(GfxStateTest_608, GetStrokeAdjustDefault_608) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test setting stroke adjust
TEST_F(GfxStateTest_608, SetStrokeAdjust_608) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_608, GetAlphaIsShapeDefault_608) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test setting alpha is shape
TEST_F(GfxStateTest_608, SetAlphaIsShape_608) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_608, GetTextKnockoutDefault_608) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setting text knockout
TEST_F(GfxStateTest_608, SetTextKnockout_608) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test save and restore
TEST_F(GfxStateTest_608, SaveAndRestore_608) {
    state->setCharSpace(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setCharSpace(10.0);
    EXPECT_DOUBLE_EQ(10.0, state->getCharSpace());
    
    GfxState *restored = state->restore();
    EXPECT_DOUBLE_EQ(5.0, restored->getCharSpace());
}

// Test hasSaves when no saves
TEST_F(GfxStateTest_608, HasSavesNoSaves_608) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_608, HasSavesAfterSave_608) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
    state->restore();
}

// Test CTM getters
TEST_F(GfxStateTest_608, GetCTM_608) {
    const auto &ctm = state->getCTM();
    EXPECT_EQ(6u, ctm.size());
}

// Test setCTM
TEST_F(GfxStateTest_608, SetCTM_608) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(100.0, ctm[4]);
    EXPECT_DOUBLE_EQ(200.0, ctm[5]);
}

// Test coordinate transformations
TEST_F(GfxStateTest_608, Transform_608) {
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Just verify it doesn't crash and returns values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transformDelta
TEST_F(GfxStateTest_608, TransformDelta_608) {
    double x2, y2;
    state->transformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test page coordinates
TEST_F(GfxStateTest_608, GetPageCoordinates_608) {
    EXPECT_DOUBLE_EQ(0.0, state->getX1());
    EXPECT_DOUBLE_EQ(0.0, state->getY1());
    EXPECT_DOUBLE_EQ(612.0, state->getX2());
    EXPECT_DOUBLE_EQ(792.0, state->getY2());
}

// Test getClipBBox
TEST_F(GfxStateTest_608, GetClipBBox_608) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(xMin <= xMax);
    EXPECT_TRUE(yMin <= yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_608, GetUserClipBBox_608) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(xMin <= xMax);
    EXPECT_TRUE(yMin <= yMax);
}

// Test setting line dash
TEST_F(GfxStateTest_608, SetLineDash_608) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(2u, d.size());
    EXPECT_DOUBLE_EQ(0.0, start);
    EXPECT_DOUBLE_EQ(3.0, d[0]);
    EXPECT_DOUBLE_EQ(2.0, d[1]);
}

// Test empty line dash
TEST_F(GfxStateTest_608, SetLineDashEmpty_608) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(0u, d.size());
    EXPECT_DOUBLE_EQ(0.0, start);
}

// Test moveTo and path operations
TEST_F(GfxStateTest_608, MoveToPath_608) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo
TEST_F(GfxStateTest_608, LineTo_608) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

// Test curveTo
TEST_F(GfxStateTest_608, CurveTo_608) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_608, ClosePath_608) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_608, ClearPath_608) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test text position operations
TEST_F(GfxStateTest_608, TextMoveTo_608) {
    state->textMoveTo(10.0, 20.0);
    // Verify line position is updated
    EXPECT_DOUBLE_EQ(10.0, state->getLineX());
    EXPECT_DOUBLE_EQ(20.0, state->getLineY());
}

// Test setting text matrix
TEST_F(GfxStateTest_608, SetTextMat_608) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(1.0, tm[0]);
    EXPECT_DOUBLE_EQ(0.0, tm[1]);
    EXPECT_DOUBLE_EQ(0.0, tm[2]);
    EXPECT_DOUBLE_EQ(1.0, tm[3]);
    EXPECT_DOUBLE_EQ(10.0, tm[4]);
    EXPECT_DOUBLE_EQ(20.0, tm[5]);
}

// Test font size
TEST_F(GfxStateTest_608, GetFontSizeDefault_608) {
    EXPECT_DOUBLE_EQ(0.0, state->getFontSize());
}

// Test setting rendering intent
TEST_F(GfxStateTest_608, SetRenderingIntent_608) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ("RelativeColorimetric", state->getRenderingIntent());
}

// Test setting rendering intent with various values
TEST_F(GfxStateTest_608, SetRenderingIntentAbsoluteColorimetric_608) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ("AbsoluteColorimetric", state->getRenderingIntent());
}

// Test setting rendering intent Perceptual
TEST_F(GfxStateTest_608, SetRenderingIntentPerceptual_608) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", state->getRenderingIntent());
}

// Test setting rendering intent Saturation
TEST_F(GfxStateTest_608, SetRenderingIntentSaturation_608) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ("Saturation", state->getRenderingIntent());
}

// Test default blend mode
TEST_F(GfxStateTest_608, GetBlendModeDefault_608) {
    EXPECT_EQ(GfxBlendMode::Normal, state->getBlendMode());
}

// Test setting blend mode
TEST_F(GfxStateTest_608, SetBlendMode_608) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(GfxBlendMode::Multiply, state->getBlendMode());
}

// Test line join style
TEST_F(GfxStateTest_608, SetLineJoin_608) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(LineJoinStyle::Round, state->getLineJoin());
}

// Test line cap style
TEST_F(GfxStateTest_608, SetLineCap_608) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(LineCapStyle::Round, state->getLineCap());
}

// Test clipToRect
TEST_F(GfxStateTest_608, ClipToRect_608) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
}

// Test copy
TEST_F(GfxStateTest_608, CopyState_608) {
    state->setCharSpace(7.5);
    state->setWordSpace(2.0);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(7.5, copied->getCharSpace());
    EXPECT_DOUBLE_EQ(2.0, copied->getWordSpace());
}

// Test with rotation
TEST(GfxStateRotateTest_608, RotatedState_608) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(90, rotatedState.getRotate());
}

// Test with different DPI
TEST(GfxStateDPITest_608, DifferentDPI_608) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(300.0, highDpiState.getHDPI());
    EXPECT_DOUBLE_EQ(600.0, highDpiState.getVDPI());
}

// Test getPath after construction
TEST_F(GfxStateTest_608, GetPathDefault_608) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(nullptr, path);
}

// Test concatCTM
TEST_F(GfxStateTest_608, ConcatCTM_608) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);  // identity
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);  // scale by 2
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_608, GetTransformedLineWidth_608) {
    state->setLineWidth(1.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test transformWidth
TEST_F(GfxStateTest_608, TransformWidth_608) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test getCTM as Matrix
TEST_F(GfxStateTest_608, GetCTMMatrix_608) {
    Matrix m;
    state->getCTM(&m);
    // Just verify it doesn't crash
    SUCCEED();
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_608, SetFillColor_608) {
    GfxColor color;
    color.c[0] = 32768;  // 0.5 in GfxColorComp
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    EXPECT_NE(nullptr, fc);
    EXPECT_EQ(32768, fc->c[0]);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_608, SetStrokeColor_608) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    EXPECT_NE(nullptr, sc);
    EXPECT_EQ(16384, sc->c[0]);
}

// Test multiple save/restore
TEST_F(GfxStateTest_608, MultipleSaveRestore_608) {
    state->setCharSpace(1.0);
    state->save();
    state->setCharSpace(2.0);
    state->save();
    state->setCharSpace(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getCharSpace());

    GfxState *s1 = state->restore();
    EXPECT_DOUBLE_EQ(2.0, s1->getCharSpace());

    GfxState *s2 = s1->restore();
    EXPECT_DOUBLE_EQ(1.0, s2->getCharSpace());
}

// Test getReusablePath
TEST_F(GfxStateTest_608, GetReusablePath_608) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(nullptr, rp);
}

// Test curX and curY after moveTo
TEST_F(GfxStateTest_608, CurXYAfterMoveTo_608) {
    state->moveTo(50.0, 75.0);
    EXPECT_DOUBLE_EQ(50.0, state->getCurX());
    EXPECT_DOUBLE_EQ(75.0, state->getCurY());
}

// Test default font
TEST_F(GfxStateTest_608, GetFontDefault_608) {
    const auto &font = state->getFont();
    // Default font should be null/empty shared_ptr
    EXPECT_EQ(nullptr, font.get());
}

// Test fill and stroke color spaces are not null by default
TEST_F(GfxStateTest_608, DefaultColorSpaces_608) {
    // The default fill/stroke color spaces should be set
    GfxColorSpace *fcs = state->getFillColorSpace();
    GfxColorSpace *scs = state->getStrokeColorSpace();
    EXPECT_NE(nullptr, fcs);
    EXPECT_NE(nullptr, scs);
}

// Test fill and stroke patterns default to null
TEST_F(GfxStateTest_608, DefaultPatterns_608) {
    EXPECT_EQ(nullptr, state->getFillPattern());
    EXPECT_EQ(nullptr, state->getStrokePattern());
}

// Test setCharSpace with very small value
TEST_F(GfxStateTest_608, SetCharSpaceVerySmall_608) {
    state->setCharSpace(1e-15);
    EXPECT_DOUBLE_EQ(1e-15, state->getCharSpace());
}

// Test multiple char space updates
TEST_F(GfxStateTest_608, SetCharSpaceMultipleUpdates_608) {
    state->setCharSpace(1.0);
    EXPECT_DOUBLE_EQ(1.0, state->getCharSpace());
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(2.0, state->getCharSpace());
    state->setCharSpace(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getCharSpace());
}

// Test isParentState
TEST_F(GfxStateTest_608, IsParentState_608) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
    child->restore();
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_608, ShiftCTMAndClip_608) {
    double xMin1, yMin1, xMax1, yMax1;
    state->getClipBBox(&xMin1, &yMin1, &xMax1, &yMax1);
    
    state->shiftCTMAndClip(10.0, 20.0);
    
    double xMin2, yMin2, xMax2, yMax2;
    state->getClipBBox(&xMin2, &yMin2, &xMax2, &yMax2);
    // Clip should have shifted
    EXPECT_TRUE(std::isfinite(xMin2));
    EXPECT_TRUE(std::isfinite(yMin2));
}

// Test textTransform
TEST_F(GfxStateTest_608, TextTransform_608) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test textTransformDelta
TEST_F(GfxStateTest_608, TextTransformDelta_608) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test lineDash with non-zero start
TEST_F(GfxStateTest_608, SetLineDashWithStart_608) {
    std::vector<double> dash = {5.0, 3.0, 1.0};
    state->setLineDash(std::move(dash), 2.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(3u, d.size());
    EXPECT_DOUBLE_EQ(2.0, start);
}
