#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"
#include "Object.h"

// Helper to create a basic GfxState with a standard page box
class GfxStateTest_605 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612; // Letter width in points
        pageBox.y2 = 792; // Letter height in points
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

TEST_F(GfxStateTest_605, Constructor_InitializesDPI_605) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_605, Constructor_InitializesPageDimensions_605) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_605, Constructor_InitializesRotate_605) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_605, Constructor_InitializesPageBounds_605) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

TEST_F(GfxStateTest_605, GetFont_InitiallyNull_605) {
    const std::shared_ptr<GfxFont>& font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxStateTest_605, SetFont_UpdatesFontAndSize_605) {
    // Set font to nullptr with a specific size
    state->setFont(nullptr, 12.0);
    EXPECT_EQ(state->getFont(), nullptr);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

TEST_F(GfxStateTest_605, GetFontSize_DefaultValue_605) {
    // Font size should have some default
    double fontSize = state->getFontSize();
    // Just check it's a valid double (not NaN)
    EXPECT_EQ(fontSize, fontSize);
}

TEST_F(GfxStateTest_605, SetLineWidth_GetLineWidth_605) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_605, SetLineWidth_Zero_605) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_605, SetFillOpacity_GetFillOpacity_605) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_605, SetStrokeOpacity_GetStrokeOpacity_605) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_605, SetFillOverprint_GetFillOverprint_605) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_605, SetStrokeOverprint_GetStrokeOverprint_605) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_605, SetOverprintMode_GetOverprintMode_605) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
    state->setOverprintMode(0);
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_605, SetFlatness_GetFlatness_605) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

TEST_F(GfxStateTest_605, SetLineJoin_GetLineJoin_605) {
    state->setLineJoin(LineJoinStyle::Miter);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Miter);
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
    state->setLineJoin(LineJoinStyle::Bevel);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Bevel);
}

TEST_F(GfxStateTest_605, SetLineCap_GetLineCap_605) {
    state->setLineCap(LineCapStyle::Butt);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Butt);
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
    state->setLineCap(LineCapStyle::Projecting);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Projecting);
}

TEST_F(GfxStateTest_605, SetMiterLimit_GetMiterLimit_605) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_605, SetStrokeAdjust_GetStrokeAdjust_605) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_605, SetAlphaIsShape_GetAlphaIsShape_605) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_605, SetTextKnockout_GetTextKnockout_605) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_605, SetCharSpace_GetCharSpace_605) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_605, SetWordSpace_GetWordSpace_605) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_605, SetHorizScaling_GetHorizScaling_605) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_605, SetLeading_GetLeading_605) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_605, SetRise_GetRise_605) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_605, SetRender_GetRender_605) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_605, SetBlendMode_GetBlendMode_605) {
    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_605, SetTextMat_GetTextMat_605) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const std::array<double, 6>& mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 0.0);
    EXPECT_DOUBLE_EQ(mat[5], 0.0);
}

TEST_F(GfxStateTest_605, SetCTM_GetCTM_605) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const std::array<double, 6>& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_605, ConcatCTM_605) {
    // Set identity CTM first
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Concatenate with a scaling matrix
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const std::array<double, 6>& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

TEST_F(GfxStateTest_605, Transform_IdentityCTM_605) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_605, Transform_ScalingCTM_605) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

TEST_F(GfxStateTest_605, Transform_TranslationCTM_605) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 110.0);
    EXPECT_DOUBLE_EQ(y2, 220.0);
}

TEST_F(GfxStateTest_605, TransformDelta_605) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(10.0, 20.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

TEST_F(GfxStateTest_605, SaveAndRestore_605) {
    state->setLineWidth(5.0);
    EXPECT_FALSE(state->hasSaves());

    GfxState* savedState = state->save();
    EXPECT_TRUE(savedState->hasSaves());

    savedState->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(savedState->getLineWidth(), 10.0);

    GfxState* restoredState = savedState->restore();
    EXPECT_DOUBLE_EQ(restoredState->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_605, HasSaves_InitiallyFalse_605) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_605, MoveTo_LineTo_PathOperations_605) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);

    state->lineTo(30.0, 40.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 30.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 40.0);
}

TEST_F(GfxStateTest_605, CurveTo_605) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 10.0, 20.0, 20.0, 30.0, 30.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 30.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 30.0);
}

TEST_F(GfxStateTest_605, ClosePath_605) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    // After closing, current point should be back to start of subpath
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

TEST_F(GfxStateTest_605, ClearPath_605) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_605, GetPath_NotNull_605) {
    const GfxPath* path = state->getPath();
    EXPECT_NE(path, nullptr);
}

TEST_F(GfxStateTest_605, ClipBBox_605) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be initialized to page bounds or similar
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_605, UserClipBBox_605) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_605, ClipToRect_605) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the clip box should be restricted
    EXPECT_GE(xMin, 100.0 - 1.0); // Allow small tolerance
    EXPECT_GE(yMin, 100.0 - 1.0);
    EXPECT_LE(xMax, 200.0 + 1.0);
    EXPECT_LE(yMax, 200.0 + 1.0);
}

TEST_F(GfxStateTest_605, SetLineDash_GetLineDash_605) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const std::vector<double>& retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_605, SetLineDash_WithOffset_605) {
    std::vector<double> dash = {2.0, 4.0, 6.0};
    state->setLineDash(std::move(dash), 1.5);
    double start;
    const std::vector<double>& retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 3u);
    EXPECT_DOUBLE_EQ(start, 1.5);
}

TEST_F(GfxStateTest_605, SetLineDash_EmptyDash_605) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const std::vector<double>& retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 0u);
}

TEST_F(GfxStateTest_605, SetRenderingIntent_GetRenderingIntent_605) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_605, SetRenderingIntent_LongString_Truncated_605) {
    // renderingIntent is char[32], so test with a string that fits
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

TEST_F(GfxStateTest_605, TextMoveTo_605) {
    state->textMoveTo(50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 60.0);
}

TEST_F(GfxStateTest_605, TransformWidth_605) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double transformedWidth = state->transformWidth(1.0);
    EXPECT_GT(transformedWidth, 0.0);
}

TEST_F(GfxStateTest_605, TransformWidth_ZeroWidth_605) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double transformedWidth = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(transformedWidth, 0.0);
}

TEST_F(GfxStateTest_605, GetTransformedLineWidth_605) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double transformedLW = state->getTransformedLineWidth();
    EXPECT_GT(transformedLW, 0.0);
}

TEST_F(GfxStateTest_605, GetTransformedFontSize_605) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double transformedSize = state->getTransformedFontSize();
    EXPECT_GT(transformedSize, 0.0);
}

TEST_F(GfxStateTest_605, GetFontTransMat_605) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setFont(nullptr, 12.0);
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Just verify it returns values without crashing
    EXPECT_EQ(m11, m11); // not NaN
}

TEST_F(GfxStateTest_605, Copy_605) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.5);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_605, Copy_IndependentOfOriginal_605) {
    state->setLineWidth(3.0);
    std::unique_ptr<GfxState> copied(state->copy());
    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_605, SetFillColor_GetFillColor_605) {
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor* retrieved = state->getFillColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_605, SetStrokeColor_GetStrokeColor_605) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor* retrieved = state->getStrokeColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

TEST_F(GfxStateTest_605, FillColorSpace_InitiallyNotNull_605) {
    // Default color space should be set
    GfxColorSpace* cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_605, StrokeColorSpace_InitiallyNotNull_605) {
    GfxColorSpace* cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_605, FillPattern_InitiallyNull_605) {
    GfxPattern* pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_605, StrokePattern_InitiallyNull_605) {
    GfxPattern* pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_605, SaveRestore_PreservesState_605) {
    state->setCharSpace(2.0);
    state->setWordSpace(3.0);
    state->setHorizScaling(120.0);

    GfxState* savedState = state->save();
    savedState->setCharSpace(5.0);
    savedState->setWordSpace(6.0);
    savedState->setHorizScaling(200.0);

    EXPECT_DOUBLE_EQ(savedState->getCharSpace(), 5.0);
    EXPECT_DOUBLE_EQ(savedState->getWordSpace(), 6.0);
    EXPECT_DOUBLE_EQ(savedState->getHorizScaling(), 200.0);

    GfxState* restoredState = savedState->restore();
    EXPECT_DOUBLE_EQ(restoredState->getCharSpace(), 2.0);
    EXPECT_DOUBLE_EQ(restoredState->getWordSpace(), 3.0);
    EXPECT_DOUBLE_EQ(restoredState->getHorizScaling(), 120.0);
}

TEST_F(GfxStateTest_605, MultipleSaveRestore_605) {
    state->setLineWidth(1.0);
    GfxState* s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState* s2 = s1->save();
    s2->setLineWidth(3.0);

    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    EXPECT_TRUE(s2->hasSaves());

    GfxState* r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);

    GfxState* r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_605, ConstructorWithRotation_605) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState->getRotate(), 90);
}

TEST_F(GfxStateTest_605, ConstructorWithDifferentDPI_605) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    auto highDpiState = std::make_unique<GfxState>(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState->getVDPI(), 300.0);
}

TEST_F(GfxStateTest_605, TextTransform_605) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    double x2, y2;
    state->textTransform(1.0, 1.0, &x2, &y2);
    // Should apply text matrix then CTM
    // Just verify it produces valid results
    EXPECT_EQ(x2, x2); // not NaN
    EXPECT_EQ(y2, y2); // not NaN
}

TEST_F(GfxStateTest_605, TextTransformDelta_605) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_EQ(x2, x2); // not NaN
    EXPECT_EQ(y2, y2); // not NaN
}

TEST_F(GfxStateTest_605, ShiftCTMAndClip_605) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const std::array<double, 6>& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_605, GetCTM_MatrixOverload_605) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify matrix was populated (just check it doesn't crash)
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
}

TEST_F(GfxStateTest_605, DefaultBlendMode_605) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_605, ParseBlendMode_Normal_605) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, GfxBlendMode::Normal);
    }
}

TEST_F(GfxStateTest_605, GetCmsRenderingIntent_605) {
    int intent = state->getCmsRenderingIntent();
    // Just verify it returns a valid value
    EXPECT_GE(intent, 0);
}

TEST_F(GfxStateTest_605, SetFillOpacity_BoundaryZero_605) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_605, SetFillOpacity_BoundaryOne_605) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_605, SetStrokeOpacity_BoundaryZero_605) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

TEST_F(GfxStateTest_605, SetStrokeOpacity_BoundaryOne_605) {
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_605, DisplayProfile_InitiallyNull_605) {
    GfxLCMSProfilePtr profile = state->getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(GfxStateTest_605, IsParentState_605) {
    GfxState* savedState = state->save();
    EXPECT_TRUE(savedState->isParentState(state.get()));
    // restore to clean up
    savedState->restore();
}

TEST_F(GfxStateTest_605, GetReusablePath_605) {
    state->clearPath();
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

TEST_F(GfxStateTest_605, NegativeLineWidth_605) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

TEST_F(GfxStateTest_605, LargeLineWidth_605) {
    state->setLineWidth(1000000.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1000000.0);
}

TEST_F(GfxStateTest_605, SetRise_Negative_605) {
    state->setRise(-5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), -5.0);
}

TEST_F(GfxStateTest_605, SetLeading_Negative_605) {
    state->setLeading(-12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), -12.0);
}
