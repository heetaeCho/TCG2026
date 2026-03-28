#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "PDFDoc.h"

// Helper to create a GfxState for testing
class GfxStateTest_639 : public ::testing::Test {
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

// Test setFlatness and getFlatness - normal value
TEST_F(GfxStateTest_639, SetFlatness_NormalValue_639) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test setFlatness and getFlatness - zero value
TEST_F(GfxStateTest_639, SetFlatness_Zero_639) {
    state->setFlatness(0);
    EXPECT_EQ(state->getFlatness(), 0);
}

// Test setFlatness and getFlatness - boundary value 100
TEST_F(GfxStateTest_639, SetFlatness_MaxBoundary_639) {
    state->setFlatness(100);
    EXPECT_EQ(state->getFlatness(), 100);
}

// Test setFlatness and getFlatness - negative value
TEST_F(GfxStateTest_639, SetFlatness_NegativeValue_639) {
    state->setFlatness(-1);
    EXPECT_EQ(state->getFlatness(), -1);
}

// Test setFlatness and getFlatness - large value
TEST_F(GfxStateTest_639, SetFlatness_LargeValue_639) {
    state->setFlatness(1000);
    EXPECT_EQ(state->getFlatness(), 1000);
}

// Test setFlatness overwrites previous value
TEST_F(GfxStateTest_639, SetFlatness_Overwrite_639) {
    state->setFlatness(10);
    EXPECT_EQ(state->getFlatness(), 10);
    state->setFlatness(20);
    EXPECT_EQ(state->getFlatness(), 20);
}

// Test initial DPI values
TEST_F(GfxStateTest_639, GetHDPI_639) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_639, GetVDPI_639) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_639, GetPageWidth_639) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_639, GetPageHeight_639) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_639, GetRotate_639) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_639, GetX1_639) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
}

TEST_F(GfxStateTest_639, GetY1_639) {
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
}

TEST_F(GfxStateTest_639, GetX2_639) {
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
}

TEST_F(GfxStateTest_639, GetY2_639) {
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_639, SetLineWidth_Normal_639) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_639, SetLineWidth_Zero_639) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test setMiterLimit and getMiterLimit
TEST_F(GfxStateTest_639, SetMiterLimit_639) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test setLineJoin and getLineJoin
TEST_F(GfxStateTest_639, SetLineJoin_639) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test setLineCap and getLineCap
TEST_F(GfxStateTest_639, SetLineCap_639) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_639, SetFillOpacity_639) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_639, SetFillOpacity_Zero_639) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
}

TEST_F(GfxStateTest_639, SetFillOpacity_One_639) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_639, SetStrokeOpacity_639) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_639, SetFillOverprint_True_639) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_639, SetFillOverprint_False_639) {
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint and getStrokeOverprint
TEST_F(GfxStateTest_639, SetStrokeOverprint_True_639) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_639, SetStrokeOverprint_False_639) {
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test setOverprintMode and getOverprintMode
TEST_F(GfxStateTest_639, SetOverprintMode_639) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(GfxStateTest_639, SetStrokeAdjust_639) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test setAlphaIsShape and getAlphaIsShape
TEST_F(GfxStateTest_639, SetAlphaIsShape_639) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test setTextKnockout and getTextKnockout
TEST_F(GfxStateTest_639, SetTextKnockout_639) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test setCharSpace and getCharSpace
TEST_F(GfxStateTest_639, SetCharSpace_639) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test setWordSpace and getWordSpace
TEST_F(GfxStateTest_639, SetWordSpace_639) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test setHorizScaling and getHorizScaling
TEST_F(GfxStateTest_639, SetHorizScaling_639) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test setLeading and getLeading
TEST_F(GfxStateTest_639, SetLeading_639) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setRise and getRise
TEST_F(GfxStateTest_639, SetRise_639) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test setRender and getRender
TEST_F(GfxStateTest_639, SetRender_639) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_639, SetRenderingIntent_639) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_639, SetRenderingIntent_AbsoluteColorimetric_639) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test save and restore
TEST_F(GfxStateTest_639, SaveAndRestore_639) {
    state->setFlatness(42);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setFlatness(99);
    EXPECT_EQ(state->getFlatness(), 99);
    
    GfxState *restored = state->restore();
    // After restore, the returned state should have the original flatness
    EXPECT_EQ(restored->getFlatness(), 42);
    state.release(); // The state chain is managed
    state.reset(restored);
}

// Test hasSaves initially false
TEST_F(GfxStateTest_639, HasSaves_InitiallyFalse_639) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_639, HasSaves_AfterSave_639) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
    // Clean up
    GfxState *restored = state->restore();
    state.release();
    state.reset(restored);
}

// Test moveTo, lineTo, path operations
TEST_F(GfxStateTest_639, MoveTo_CreatesCurrentPoint_639) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
    state->clearPath();
}

TEST_F(GfxStateTest_639, IsPath_InitiallyFalse_639) {
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_639, IsCurPt_InitiallyFalse_639) {
    EXPECT_FALSE(state->isCurPt());
}

// Test clearPath
TEST_F(GfxStateTest_639, ClearPath_639) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test transform
TEST_F(GfxStateTest_639, Transform_IdentityCTM_639) {
    double x2, y2;
    // With default CTM for 72 DPI, 0 rotation, upside down
    state->transform(0.0, 0.0, &x2, &y2);
    // The result depends on the CTM setup, but we can at least verify it doesn't crash
    // and produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test setCTM
TEST_F(GfxStateTest_639, SetCTM_639) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 1.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 1.0);
    EXPECT_DOUBLE_EQ(ctm[4], 0.0);
    EXPECT_DOUBLE_EQ(ctm[5], 0.0);
}

// Test concatCTM
TEST_F(GfxStateTest_639, ConcatCTM_639) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_639, SetTextMat_639) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_639, SetBlendMode_639) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test getClipBBox
TEST_F(GfxStateTest_639, GetClipBBox_639) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test getUserClipBBox
TEST_F(GfxStateTest_639, GetUserClipBBox_639) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_639, SetLineDash_639) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_639, SetLineDash_Empty_639) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_639, TextMoveTo_639) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test copy
TEST_F(GfxStateTest_639, Copy_639) {
    state->setFlatness(55);
    state->setLineWidth(3.5);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_EQ(copied->getFlatness(), 55);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.5);
}

// Test with different rotation
TEST(GfxStateRotation_639, Rotate90_639) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test setFlatness multiple times
TEST_F(GfxStateTest_639, SetFlatness_MultipleTimes_639) {
    for (int i = 0; i <= 100; i++) {
        state->setFlatness(i);
        EXPECT_EQ(state->getFlatness(), i);
    }
}

// Test closePath after moveTo and lineTo
TEST_F(GfxStateTest_639, ClosePath_639) {
    state->moveTo(0, 0);
    state->lineTo(100, 0);
    state->lineTo(100, 100);
    state->closePath();
    EXPECT_TRUE(state->isPath());
    state->clearPath();
}

// Test curveTo
TEST_F(GfxStateTest_639, CurveTo_639) {
    state->moveTo(0, 0);
    state->curveTo(10, 20, 30, 40, 50, 60);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
    state->clearPath();
}

// Test transformWidth
TEST_F(GfxStateTest_639, TransformWidth_639) {
    double tw = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_639, GetTransformedLineWidth_639) {
    state->setLineWidth(2.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tlw));
    EXPECT_GE(tlw, 0.0);
}

// Test clipToRect
TEST_F(GfxStateTest_639, ClipToRect_639) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should be within the specified rect
    EXPECT_GE(xMin, 10.0 - 1e-6);
    EXPECT_GE(yMin, 20.0 - 1e-6);
    EXPECT_LE(xMax, 100.0 + 1e-6);
    EXPECT_LE(yMax, 200.0 + 1e-6);
}

// Test getFontSize initially
TEST_F(GfxStateTest_639, GetFontSize_Initial_639) {
    // Font size should be some default
    double fs = state->getFontSize();
    EXPECT_TRUE(std::isfinite(fs));
}

// Test setRenderingIntent with long string (should truncate to 31 chars)
TEST_F(GfxStateTest_639, SetRenderingIntent_LongString_639) {
    state->setRenderingIntent("AVeryLongRenderingIntentStringThatExceeds31Characters");
    const char *ri = state->getRenderingIntent();
    EXPECT_TRUE(strlen(ri) <= 31);
}
