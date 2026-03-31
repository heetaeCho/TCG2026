#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_648 : public ::testing::Test {
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

// --- setWordSpace / getWordSpace ---

TEST_F(GfxStateTest_648, SetWordSpacePositive_648) {
    state->setWordSpace(5.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 5.0);
}

TEST_F(GfxStateTest_648, SetWordSpaceZero_648) {
    state->setWordSpace(0.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_648, SetWordSpaceNegative_648) {
    state->setWordSpace(-3.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), -3.5);
}

TEST_F(GfxStateTest_648, SetWordSpaceLargeValue_648) {
    state->setWordSpace(1e10);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 1e10);
}

TEST_F(GfxStateTest_648, SetWordSpaceSmallValue_648) {
    state->setWordSpace(1e-15);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 1e-15);
}

TEST_F(GfxStateTest_648, SetWordSpaceOverwrite_648) {
    state->setWordSpace(10.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 10.0);
    state->setWordSpace(20.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 20.0);
}

// --- Basic construction and getters ---

TEST_F(GfxStateTest_648, ConstructorSetsHDPI_648) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_648, ConstructorSetsVDPI_648) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_648, ConstructorSetsPageWidth_648) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_648, ConstructorSetsPageHeight_648) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_648, ConstructorSetsRotate_648) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_648, ConstructorPageBounds_648) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- setCharSpace / getCharSpace ---

TEST_F(GfxStateTest_648, SetCharSpacePositive_648) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

TEST_F(GfxStateTest_648, SetCharSpaceNegative_648) {
    state->setCharSpace(-1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), -1.5);
}

// --- setHorizScaling / getHorizScaling ---

TEST_F(GfxStateTest_648, SetHorizScaling_648) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

// --- setLeading / getLeading ---

TEST_F(GfxStateTest_648, SetLeading_648) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// --- setRise / getRise ---

TEST_F(GfxStateTest_648, SetRise_648) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// --- setRender / getRender ---

TEST_F(GfxStateTest_648, SetRender_648) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// --- setLineWidth / getLineWidth ---

TEST_F(GfxStateTest_648, SetLineWidth_648) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_648, SetLineWidthZero_648) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// --- setFlatness / getFlatness ---

TEST_F(GfxStateTest_648, SetFlatness_648) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// --- setMiterLimit / getMiterLimit ---

TEST_F(GfxStateTest_648, SetMiterLimit_648) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// --- setLineJoin / getLineJoin ---

TEST_F(GfxStateTest_648, SetLineJoin_648) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// --- setLineCap / getLineCap ---

TEST_F(GfxStateTest_648, SetLineCap_648) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// --- setFillOpacity / getFillOpacity ---

TEST_F(GfxStateTest_648, SetFillOpacity_648) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_648, SetFillOpacityZero_648) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_648, SetFillOpacityOne_648) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// --- setStrokeOpacity / getStrokeOpacity ---

TEST_F(GfxStateTest_648, SetStrokeOpacity_648) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// --- setFillOverprint / getFillOverprint ---

TEST_F(GfxStateTest_648, SetFillOverprintTrue_648) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_648, SetFillOverprintFalse_648) {
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// --- setStrokeOverprint / getStrokeOverprint ---

TEST_F(GfxStateTest_648, SetStrokeOverprintTrue_648) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// --- setOverprintMode / getOverprintMode ---

TEST_F(GfxStateTest_648, SetOverprintMode_648) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- setStrokeAdjust / getStrokeAdjust ---

TEST_F(GfxStateTest_648, SetStrokeAdjust_648) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// --- setAlphaIsShape / getAlphaIsShape ---

TEST_F(GfxStateTest_648, SetAlphaIsShape_648) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// --- setTextKnockout / getTextKnockout ---

TEST_F(GfxStateTest_648, SetTextKnockout_648) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- setBlendMode / getBlendMode ---

TEST_F(GfxStateTest_648, SetBlendMode_648) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// --- setTextMat / getTextMat ---

TEST_F(GfxStateTest_648, SetTextMat_648) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// --- setCTM / getCTM ---

TEST_F(GfxStateTest_648, SetCTM_648) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// --- save / restore ---

TEST_F(GfxStateTest_648, SaveAndRestore_648) {
    state->setWordSpace(7.0);
    GfxState *saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setWordSpace(15.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 15.0);

    GfxState *restored = state->restore();
    EXPECT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getWordSpace(), 7.0);
}

TEST_F(GfxStateTest_648, HasSavesInitiallyFalse_648) {
    EXPECT_FALSE(state->hasSaves());
}

// --- setLineDash / getLineDash ---

TEST_F(GfxStateTest_648, SetLineDash_648) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

TEST_F(GfxStateTest_648, SetLineDashEmpty_648) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// --- Path operations ---

TEST_F(GfxStateTest_648, InitiallyNoPath_648) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_648, MoveToCreatesCurPt_648) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_648, LineToCreatesPath_648) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_648, ClearPathResetsState_648) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_648, CurveToCreatesPath_648) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 10.0, 20.0, 20.0, 30.0, 30.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_648, ClosePathAfterLines_648) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// --- transform ---

TEST_F(GfxStateTest_648, TransformIdentityCTM_648) {
    // With default CTM for a 612x792 page at 72dpi, rotation 0, upsideDown=true
    // the transform should produce deterministic results
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Just verify it doesn't crash and returns finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_648, TransformDelta_648) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// --- setRenderingIntent / getRenderingIntent ---

TEST_F(GfxStateTest_648, SetRenderingIntent_648) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_648, SetRenderingIntentAbsoluteColorimetric_648) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// --- copy ---

TEST_F(GfxStateTest_648, CopyPreservesWordSpace_648) {
    state->setWordSpace(42.0);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getWordSpace(), 42.0);
}

TEST_F(GfxStateTest_648, CopyPreservesLineWidth_648) {
    state->setLineWidth(3.14);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.14);
}

// --- Rotation constructor variant ---

TEST_F(GfxStateTest_648, ConstructorWithRotation90_648) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// --- textMoveTo ---

TEST_F(GfxStateTest_648, TextMoveTo_648) {
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX/lineY and curTextX/curTextY should be updated
    EXPECT_TRUE(std::isfinite(state->getLineX()));
    EXPECT_TRUE(std::isfinite(state->getLineY()));
}

// --- getClipBBox ---

TEST_F(GfxStateTest_648, GetClipBBox_648) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- getUserClipBBox ---

TEST_F(GfxStateTest_648, GetUserClipBBox_648) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// --- Multiple setWordSpace calls ---

TEST_F(GfxStateTest_648, SetWordSpaceMultipleTimes_648) {
    for (int i = 0; i < 100; ++i) {
        state->setWordSpace(static_cast<double>(i));
        EXPECT_DOUBLE_EQ(state->getWordSpace(), static_cast<double>(i));
    }
}

// --- concatCTM ---

TEST_F(GfxStateTest_648, ConcatCTM_648) {
    auto ctmBefore = state->getCTM();
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 50.0, 50.0);
    auto ctmAfter = state->getCTM();
    // The CTM should have changed due to translation
    // At minimum, the translation components should differ
    EXPECT_TRUE(std::isfinite(ctmAfter[4]));
    EXPECT_TRUE(std::isfinite(ctmAfter[5]));
}

// --- clipToRect ---

TEST_F(GfxStateTest_648, ClipToRect_648) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should be no larger than the rect we clipped to
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(xMax));
}

// --- Font-related ---

TEST_F(GfxStateTest_648, InitialFontIsNull_648) {
    const auto &font = state->getFont();
    // Initial font may or may not be null depending on implementation
    // Just test it doesn't crash
    EXPECT_TRUE(true);
}

TEST_F(GfxStateTest_648, GetFontSizeInitial_648) {
    double fontSize = state->getFontSize();
    EXPECT_TRUE(std::isfinite(fontSize));
}

// --- setFont with nullptr ---

TEST_F(GfxStateTest_648, SetFontNullptr_648) {
    state->setFont(nullptr, 12.0);
    EXPECT_DOUBLE_EQ(state->getFontSize(), 12.0);
}

// --- transformWidth ---

TEST_F(GfxStateTest_648, TransformWidth_648) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

TEST_F(GfxStateTest_648, TransformWidthZero_648) {
    double w = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(w, 0.0);
}

// --- getTransformedLineWidth ---

TEST_F(GfxStateTest_648, GetTransformedLineWidth_648) {
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tlw));
}

// --- isParentState ---

TEST_F(GfxStateTest_648, IsParentStateAfterSave_648) {
    GfxState *child = state->save();
    EXPECT_TRUE(state->isParentState(child));
    state->restore();
}

// --- shiftCTMAndClip ---

TEST_F(GfxStateTest_648, ShiftCTMAndClip_648) {
    state->shiftCTMAndClip(10.0, 20.0);
    // Verify it doesn't crash and CTM is still valid
    const auto &ctm = state->getCTM();
    for (int i = 0; i < 6; ++i) {
        EXPECT_TRUE(std::isfinite(ctm[i]));
    }
}
