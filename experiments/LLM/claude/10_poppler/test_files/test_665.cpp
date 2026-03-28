#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Helper to create a GfxState with default parameters
class GfxStateTest_665 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = new GfxState(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        delete state;
    }

    GfxState *state;
};

// Test textMoveTo sets lineX and lineY and updates curTextX/curTextY
TEST_F(GfxStateTest_665, TextMoveTo_SetsLineCoordinates_665) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

TEST_F(GfxStateTest_665, TextMoveTo_UpdatesCurTextCoordinates_665) {
    state->textMoveTo(10.0, 20.0);
    // curTextX and curTextY should be set via textTransform
    // We can at least verify they are accessible
    double curTextX = state->getCurTextX();
    double curTextY = state->getCurTextY();
    // With default identity text matrix, textTransform should produce predictable results
    // Just verify they are set (not NaN or uninitialized)
    EXPECT_FALSE(std::isnan(curTextX));
    EXPECT_FALSE(std::isnan(curTextY));
}

TEST_F(GfxStateTest_665, TextMoveTo_ZeroCoordinates_665) {
    state->textMoveTo(0.0, 0.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 0.0);
}

TEST_F(GfxStateTest_665, TextMoveTo_NegativeCoordinates_665) {
    state->textMoveTo(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), -5.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), -10.0);
}

TEST_F(GfxStateTest_665, TextMoveTo_LargeCoordinates_665) {
    state->textMoveTo(1e10, 1e10);
    EXPECT_DOUBLE_EQ(state->getLineX(), 1e10);
    EXPECT_DOUBLE_EQ(state->getLineY(), 1e10);
}

TEST_F(GfxStateTest_665, TextMoveTo_VerySmallCoordinates_665) {
    state->textMoveTo(1e-15, 1e-15);
    EXPECT_DOUBLE_EQ(state->getLineX(), 1e-15);
    EXPECT_DOUBLE_EQ(state->getLineY(), 1e-15);
}

TEST_F(GfxStateTest_665, TextMoveTo_CalledMultipleTimes_665) {
    state->textMoveTo(1.0, 2.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 1.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 2.0);

    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

TEST_F(GfxStateTest_665, TextMoveTo_WithCustomTextMat_665) {
    // Set a non-identity text matrix
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    state->textMoveTo(3.0, 4.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 3.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 4.0);
    // curTextX and curTextY should reflect the text transformation
    double curTextX = state->getCurTextX();
    double curTextY = state->getCurTextY();
    EXPECT_FALSE(std::isnan(curTextX));
    EXPECT_FALSE(std::isnan(curTextY));
}

// Test basic construction and getters
TEST_F(GfxStateTest_665, Constructor_BasicProperties_665) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test default line properties
TEST_F(GfxStateTest_665, DefaultLineWidth_665) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_665, SetAndGetLineWidth_665) {
    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_665, SetAndGetCharSpace_665) {
    state->setCharSpace(2.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.5);
}

TEST_F(GfxStateTest_665, SetAndGetWordSpace_665) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

TEST_F(GfxStateTest_665, SetAndGetHorizScaling_665) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_665, SetAndGetLeading_665) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_665, SetAndGetRise_665) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

TEST_F(GfxStateTest_665, SetAndGetRender_665) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

TEST_F(GfxStateTest_665, SetAndGetFillOpacity_665) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_665, SetAndGetStrokeOpacity_665) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

TEST_F(GfxStateTest_665, SetAndGetFillOverprint_665) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_665, SetAndGetStrokeOverprint_665) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_665, SetAndGetOverprintMode_665) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

TEST_F(GfxStateTest_665, SetAndGetFlatness_665) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

TEST_F(GfxStateTest_665, SetAndGetMiterLimit_665) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_665, SetAndGetStrokeAdjust_665) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_665, SetAndGetAlphaIsShape_665) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_665, SetAndGetTextKnockout_665) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

TEST_F(GfxStateTest_665, SetAndGetBlendMode_665) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

TEST_F(GfxStateTest_665, SetAndGetRenderingIntent_665) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_665, RenderingIntent_LongString_665) {
    // The internal buffer is 32 chars, so test boundary
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test save and restore
TEST_F(GfxStateTest_665, SaveAndRestore_665) {
    state->setLineWidth(10.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(20.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 20.0);

    GfxState *restored = state->restore();
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 10.0);
    state = restored;
}

TEST_F(GfxStateTest_665, HasSaves_InitiallyFalse_665) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_665, HasSaves_AfterSave_665) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    state = state->restore();
}

// Test path operations
TEST_F(GfxStateTest_665, InitialPath_IsNotPath_665) {
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_665, MoveTo_CreatesCurPt_665) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_665, LineTo_CreatesPath_665) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 20.0);
}

TEST_F(GfxStateTest_665, CurveTo_CreatesPath_665) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 5.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 6.0);
}

TEST_F(GfxStateTest_665, ClearPath_ResetsPath_665) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_665, ClosePath_665) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    // After closing, curX/curY should be back at moveTo point
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test CTM operations
TEST_F(GfxStateTest_665, SetCTM_665) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

TEST_F(GfxStateTest_665, Transform_665) {
    // With default CTM (identity-like for 0 rotation, upsideDown=true)
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Just verify it doesn't crash and produces finite values
    EXPECT_FALSE(std::isnan(x2));
    EXPECT_FALSE(std::isnan(y2));
}

TEST_F(GfxStateTest_665, TransformDelta_665) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_FALSE(std::isnan(x2));
    EXPECT_FALSE(std::isnan(y2));
}

// Test text transform
TEST_F(GfxStateTest_665, TextTransform_665) {
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    EXPECT_FALSE(std::isnan(x2));
    EXPECT_FALSE(std::isnan(y2));
}

TEST_F(GfxStateTest_665, TextTransformDelta_665) {
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_FALSE(std::isnan(x2));
    EXPECT_FALSE(std::isnan(y2));
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_665, SetAndGetTextMat_665) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// Test textShift
TEST_F(GfxStateTest_665, TextShift_665) {
    state->textMoveTo(10.0, 20.0);
    double prevX = state->getCurTextX();
    double prevY = state->getCurTextY();
    state->textShift(5.0, 3.0);
    // After shifting, curTextX and curTextY should change
    // Just verify they're different or at least valid
    EXPECT_FALSE(std::isnan(state->getCurTextX()));
    EXPECT_FALSE(std::isnan(state->getCurTextY()));
}

// Test clip operations
TEST_F(GfxStateTest_665, ClipBBox_665) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip bbox should be finite values
    EXPECT_FALSE(std::isnan(xMin));
    EXPECT_FALSE(std::isnan(yMin));
    EXPECT_FALSE(std::isnan(xMax));
    EXPECT_FALSE(std::isnan(yMax));
}

TEST_F(GfxStateTest_665, ClipToRect_665) {
    state->clipToRect(100.0, 100.0, 200.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the bbox should be constrained
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_665, GetUserClipBBox_665) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(std::isnan(xMin));
    EXPECT_FALSE(std::isnan(yMin));
    EXPECT_FALSE(std::isnan(xMax));
    EXPECT_FALSE(std::isnan(yMax));
}

// Test page coordinates
TEST_F(GfxStateTest_665, GetPageCoordinates_665) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test font size
TEST_F(GfxStateTest_665, DefaultFontSize_665) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test copy
TEST_F(GfxStateTest_665, Copy_665) {
    state->setLineWidth(7.0);
    state->setCharSpace(1.5);
    std::unique_ptr<GfxState> copyState(state->copy());
    ASSERT_NE(copyState, nullptr);
    EXPECT_DOUBLE_EQ(copyState->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copyState->getCharSpace(), 1.5);
}

// Test line dash
TEST_F(GfxStateTest_665, SetAndGetLineDash_665) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

// Test setLineJoin and setLineCap
TEST_F(GfxStateTest_665, SetAndGetLineJoin_665) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_665, SetAndGetLineCap_665) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test textMoveTo after setting custom text matrix
TEST_F(GfxStateTest_665, TextMoveTo_WithScaledTextMatrix_665) {
    state->setTextMat(10.0, 0.0, 0.0, 10.0, 0.0, 0.0);
    state->textMoveTo(1.0, 1.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 1.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 1.0);
    // The text transform should scale by 10
    double tx, ty;
    state->textTransform(1.0, 1.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(state->getCurTextX(), tx);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), ty);
}

// Test with different rotation
class GfxStateRotatedTest_665 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = new GfxState(72.0, 72.0, &pageBox, 90, true);
    }

    void TearDown() override {
        delete state;
    }

    GfxState *state;
};

TEST_F(GfxStateRotatedTest_665, RotatedState_Properties_665) {
    EXPECT_EQ(state->getRotate(), 90);
}

TEST_F(GfxStateRotatedTest_665, TextMoveTo_RotatedState_665) {
    state->textMoveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
    EXPECT_FALSE(std::isnan(state->getCurTextX()));
    EXPECT_FALSE(std::isnan(state->getCurTextY()));
}

// Test transformWidth
TEST_F(GfxStateTest_665, TransformWidth_665) {
    double w = state->transformWidth(1.0);
    EXPECT_GT(w, 0.0);
    EXPECT_FALSE(std::isnan(w));
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_665, GetTransformedLineWidth_665) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_FALSE(std::isnan(tw));
    EXPECT_GE(tw, 0.0);
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_665, GetTransformedFontSize_665) {
    double fs = state->getTransformedFontSize();
    EXPECT_FALSE(std::isnan(fs));
}

// Test getFontTransMat
TEST_F(GfxStateTest_665, GetFontTransMat_665) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_FALSE(std::isnan(m11));
    EXPECT_FALSE(std::isnan(m12));
    EXPECT_FALSE(std::isnan(m21));
    EXPECT_FALSE(std::isnan(m22));
}

// Test isParentState
TEST_F(GfxStateTest_665, IsParentState_665) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->isParentState(saved));
    state = state->restore();
}

// Test parseBlendMode
TEST_F(GfxStateTest_665, ParseBlendMode_Normal_665) {
    // Create a name object for "Normal"
    Object obj(objName, "Normal");
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    EXPECT_TRUE(result);
    EXPECT_EQ(mode, GfxBlendMode::Normal);
}

// Test concatCTM
TEST_F(GfxStateTest_665, ConcatCTM_665) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test getReusablePath
TEST_F(GfxStateTest_665, GetReusablePath_665) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    ASSERT_NE(pathIter, nullptr);
}
