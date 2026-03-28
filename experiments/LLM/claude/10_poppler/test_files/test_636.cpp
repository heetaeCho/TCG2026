#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

// Helper to create a basic GfxState for testing
class GfxStateTest_636 : public ::testing::Test {
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

// Test stroke overprint setter and getter
TEST_F(GfxStateTest_636, SetStrokeOverprintTrue_636) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_636, SetStrokeOverprintFalse_636) {
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_636, SetStrokeOverprintToggle_636) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test fill overprint setter and getter
TEST_F(GfxStateTest_636, SetFillOverprintTrue_636) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_636, SetFillOverprintFalse_636) {
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_636, SetOverprintMode_636) {
    state->setOverprintMode(1);
    EXPECT_EQ(1, state->getOverprintMode());
}

TEST_F(GfxStateTest_636, SetOverprintModeZero_636) {
    state->setOverprintMode(0);
    EXPECT_EQ(0, state->getOverprintMode());
}

// Test basic constructor values
TEST_F(GfxStateTest_636, ConstructorHDPI_636) {
    EXPECT_DOUBLE_EQ(72.0, state->getHDPI());
}

TEST_F(GfxStateTest_636, ConstructorVDPI_636) {
    EXPECT_DOUBLE_EQ(72.0, state->getVDPI());
}

TEST_F(GfxStateTest_636, ConstructorRotate_636) {
    EXPECT_EQ(0, state->getRotate());
}

TEST_F(GfxStateTest_636, ConstructorPageWidth_636) {
    EXPECT_DOUBLE_EQ(612.0, state->getPageWidth());
}

TEST_F(GfxStateTest_636, ConstructorPageHeight_636) {
    EXPECT_DOUBLE_EQ(792.0, state->getPageHeight());
}

// Test line width
TEST_F(GfxStateTest_636, SetLineWidth_636) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getLineWidth());
}

TEST_F(GfxStateTest_636, SetLineWidthZero_636) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getLineWidth());
}

// Test flatness
TEST_F(GfxStateTest_636, SetFlatness_636) {
    state->setFlatness(50);
    EXPECT_EQ(50, state->getFlatness());
}

// Test line join
TEST_F(GfxStateTest_636, SetLineJoin_636) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(LineJoinStyle::Round, state->getLineJoin());
}

// Test line cap
TEST_F(GfxStateTest_636, SetLineCap_636) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(LineCapStyle::Round, state->getLineCap());
}

// Test miter limit
TEST_F(GfxStateTest_636, SetMiterLimit_636) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(5.0, state->getMiterLimit());
}

// Test stroke adjust
TEST_F(GfxStateTest_636, SetStrokeAdjust_636) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_636, SetAlphaIsShape_636) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
    state->setAlphaIsShape(false);
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_636, SetTextKnockout_636) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
    state->setTextKnockout(false);
    EXPECT_FALSE(state->getTextKnockout());
}

// Test fill opacity
TEST_F(GfxStateTest_636, SetFillOpacity_636) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
}

TEST_F(GfxStateTest_636, SetFillOpacityZero_636) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getFillOpacity());
}

TEST_F(GfxStateTest_636, SetFillOpacityOne_636) {
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(1.0, state->getFillOpacity());
}

// Test stroke opacity
TEST_F(GfxStateTest_636, SetStrokeOpacity_636) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(0.75, state->getStrokeOpacity());
}

TEST_F(GfxStateTest_636, SetStrokeOpacityZero_636) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getStrokeOpacity());
}

// Test char space
TEST_F(GfxStateTest_636, SetCharSpace_636) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getCharSpace());
}

// Test word space
TEST_F(GfxStateTest_636, SetWordSpace_636) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(2.0, state->getWordSpace());
}

// Test horiz scaling
TEST_F(GfxStateTest_636, SetHorizScaling_636) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(150.0, state->getHorizScaling());
}

// Test leading
TEST_F(GfxStateTest_636, SetLeading_636) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(12.0, state->getLeading());
}

// Test rise
TEST_F(GfxStateTest_636, SetRise_636) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getRise());
}

// Test render
TEST_F(GfxStateTest_636, SetRender_636) {
    state->setRender(2);
    EXPECT_EQ(2, state->getRender());
}

// Test font size
TEST_F(GfxStateTest_636, GetFontSizeDefault_636) {
    // Default font size should be some value (typically 0 or unset)
    double fs = state->getFontSize();
    EXPECT_GE(fs, 0.0);
}

// Test rendering intent
TEST_F(GfxStateTest_636, SetRenderingIntent_636) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ("RelativeColorimetric", state->getRenderingIntent());
}

TEST_F(GfxStateTest_636, SetRenderingIntentAbsolute_636) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ("AbsoluteColorimetric", state->getRenderingIntent());
}

TEST_F(GfxStateTest_636, SetRenderingIntentPerceptual_636) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", state->getRenderingIntent());
}

TEST_F(GfxStateTest_636, SetRenderingIntentSaturation_636) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ("Saturation", state->getRenderingIntent());
}

// Test save and restore
TEST_F(GfxStateTest_636, SaveAndRestore_636) {
    state->setLineWidth(3.0);
    GfxState *saved = state->save();
    ASSERT_NE(nullptr, saved);
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(5.0, state->getLineWidth());

    GfxState *restored = state->restore();
    // After restore, we should be back in previous state context
    ASSERT_NE(nullptr, restored);
}

TEST_F(GfxStateTest_636, HasSavesInitially_636) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_636, HasSavesAfterSave_636) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_636, InitiallyNoPath_636) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_636, MoveToSetsCurPt_636) {
    state->clearPath();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_636, LineToCreatesPath_636) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_636, CurveToCreatesPath_636) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_636, ClearPathResetsState_636) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test text matrix
TEST_F(GfxStateTest_636, SetTextMat_636) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(1.0, tm[0]);
    EXPECT_DOUBLE_EQ(0.0, tm[1]);
    EXPECT_DOUBLE_EQ(0.0, tm[2]);
    EXPECT_DOUBLE_EQ(1.0, tm[3]);
    EXPECT_DOUBLE_EQ(10.0, tm[4]);
    EXPECT_DOUBLE_EQ(20.0, tm[5]);
}

// Test CTM
TEST_F(GfxStateTest_636, SetCTM_636) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(100.0, ctm[4]);
    EXPECT_DOUBLE_EQ(200.0, ctm[5]);
}

// Test transform
TEST_F(GfxStateTest_636, TransformIdentity_636) {
    // With default identity-like CTM (from constructor), transform should map coordinates
    double x2, y2;
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(10.0, x2);
    EXPECT_DOUBLE_EQ(20.0, y2);
}

TEST_F(GfxStateTest_636, TransformWithScale_636) {
    double x2, y2;
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(20.0, x2);
    EXPECT_DOUBLE_EQ(40.0, y2);
}

TEST_F(GfxStateTest_636, TransformWithTranslation_636) {
    double x2, y2;
    state->setCTM(1.0, 0.0, 0.0, 1.0, 50.0, 100.0);
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(60.0, x2);
    EXPECT_DOUBLE_EQ(120.0, y2);
}

TEST_F(GfxStateTest_636, TransformDeltaNoTranslation_636) {
    double x2, y2;
    state->setCTM(2.0, 0.0, 0.0, 2.0, 50.0, 100.0);
    state->transformDelta(10.0, 20.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(20.0, x2);
    EXPECT_DOUBLE_EQ(40.0, y2);
}

// Test concatCTM
TEST_F(GfxStateTest_636, ConcatCTM_636) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    // After concatenation with scale 2 and translate (10,20):
    // new CTM = [2,0,0,2,10,20] * [1,0,0,1,0,0] = [2,0,0,2,10,20]
    EXPECT_DOUBLE_EQ(12.0, x2);
    EXPECT_DOUBLE_EQ(22.0, y2);
}

// Test blend mode
TEST_F(GfxStateTest_636, SetBlendMode_636) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(GfxBlendMode::Multiply, state->getBlendMode());
}

TEST_F(GfxStateTest_636, SetBlendModeNormal_636) {
    state->setBlendMode(GfxBlendMode::Normal);
    EXPECT_EQ(GfxBlendMode::Normal, state->getBlendMode());
}

// Test clip bounding box
TEST_F(GfxStateTest_636, GetClipBBox_636) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have some valid clip bbox from constructor
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_636, ClipToRect_636) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test text move
TEST_F(GfxStateTest_636, TextMoveTo_636) {
    state->textMoveTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(15.0, state->getLineX());
    EXPECT_DOUBLE_EQ(25.0, state->getLineY());
}

// Test line dash
TEST_F(GfxStateTest_636, SetLineDash_636) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(2u, d.size());
    EXPECT_DOUBLE_EQ(3.0, d[0]);
    EXPECT_DOUBLE_EQ(5.0, d[1]);
    EXPECT_DOUBLE_EQ(1.0, start);
}

TEST_F(GfxStateTest_636, SetLineDashEmpty_636) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(0u, d.size());
    EXPECT_DOUBLE_EQ(0.0, start);
}

// Test copy
TEST_F(GfxStateTest_636, CopyPreservesProperties_636) {
    state->setLineWidth(7.5);
    state->setStrokeOverprint(true);
    state->setFillOpacity(0.3);
    
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(nullptr, copied);
    EXPECT_DOUBLE_EQ(7.5, copied->getLineWidth());
    EXPECT_TRUE(copied->getStrokeOverprint());
    EXPECT_DOUBLE_EQ(0.3, copied->getFillOpacity());
}

// Test page coordinates
TEST_F(GfxStateTest_636, GetPageCoordinates_636) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test with different rotations
class GfxStateRotateTest_636 : public ::testing::TestWithParam<int> {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, GetParam(), true);
    }
    std::unique_ptr<GfxState> state;
};

TEST_P(GfxStateRotateTest_636, RotateValue_636) {
    EXPECT_EQ(GetParam(), state->getRotate());
}

TEST_P(GfxStateRotateTest_636, PageDimensionsValid_636) {
    EXPECT_GT(state->getPageWidth(), 0);
    EXPECT_GT(state->getPageHeight(), 0);
}

INSTANTIATE_TEST_SUITE_P(Rotations_636, GfxStateRotateTest_636,
                         ::testing::Values(0, 90, 180, 270));

// Test getUserClipBBox
TEST_F(GfxStateTest_636, GetUserClipBBox_636) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test transformWidth
TEST_F(GfxStateTest_636, TransformWidthIdentity_636) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(5.0, w);
}

TEST_F(GfxStateTest_636, TransformWidthScaled_636) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double w = state->transformWidth(5.0);
    EXPECT_DOUBLE_EQ(10.0, w);
}

TEST_F(GfxStateTest_636, TransformWidthZero_636) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double w = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, w);
}

// Test isParentState
TEST_F(GfxStateTest_636, IsParentStateAfterSave_636) {
    GfxState *child = state->save();
    ASSERT_NE(nullptr, child);
    // child should consider state as parent
    // The current state pointer is the child after save
    // state->save() returns the new state (saved on stack)
}

// Test getPath is not null
TEST_F(GfxStateTest_636, GetPathNotNull_636) {
    EXPECT_NE(nullptr, state->getPath());
}

// Test closePath after creating a subpath
TEST_F(GfxStateTest_636, ClosePath_636) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_636, ShiftCTMAndClip_636) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(10.0, ctm[4]);
    EXPECT_DOUBLE_EQ(20.0, ctm[5]);
}

// Test setting fill/stroke color
TEST_F(GfxStateTest_636, SetFillColor_636) {
    GfxColor color;
    color.c[0] = 32768; // mid-range
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    ASSERT_NE(nullptr, fc);
    EXPECT_EQ(32768, fc->c[0]);
}

TEST_F(GfxStateTest_636, SetStrokeColor_636) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    ASSERT_NE(nullptr, sc);
    EXPECT_EQ(65535, sc->c[0]);
}

// Test getCTM with Matrix parameter
TEST_F(GfxStateTest_636, GetCTMMatrix_636) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should be populated from CTM
    // Just verify it doesn't crash and values are reasonable
    EXPECT_DOUBLE_EQ(1.0, state->getCTM()[0]);
}

// Test getReusablePath
TEST_F(GfxStateTest_636, GetReusablePath_636) {
    state->clearPath();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(nullptr, rp);
}
