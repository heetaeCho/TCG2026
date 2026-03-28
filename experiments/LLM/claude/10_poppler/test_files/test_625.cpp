#include <gtest/gtest.h>
#include <cmath>
#include "GfxState.h"

// Helper to create a GfxState with a known configuration
// Using a simple page box and no rotation for predictable CTM
class GfxStateTest_625 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;  // Letter width in points
        pageBox.y2 = 792;  // Letter height in points
        state = new GfxState(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        delete state;
    }

    GfxState *state;
};

// Test transform with identity-like CTM (default after construction with no rotation)
TEST_F(GfxStateTest_625, TransformOrigin_625) {
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // The transform result depends on the CTM set during construction.
    // For origin, x2 = ctm[4], y2 = ctm[5]
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(x2, ctm[4]);
    EXPECT_DOUBLE_EQ(y2, ctm[5]);
}

// Test transform with a known point (1, 0)
TEST_F(GfxStateTest_625, TransformUnitX_625) {
    double x2, y2;
    state->transform(1.0, 0.0, &x2, &y2);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(x2, ctm[0] * 1.0 + ctm[4]);
    EXPECT_DOUBLE_EQ(y2, ctm[1] * 1.0 + ctm[5]);
}

// Test transform with a known point (0, 1)
TEST_F(GfxStateTest_625, TransformUnitY_625) {
    double x2, y2;
    state->transform(0.0, 1.0, &x2, &y2);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(x2, ctm[2] * 1.0 + ctm[4]);
    EXPECT_DOUBLE_EQ(y2, ctm[3] * 1.0 + ctm[5]);
}

// Test transform with arbitrary point
TEST_F(GfxStateTest_625, TransformArbitraryPoint_625) {
    double x2, y2;
    double x1 = 3.5, y1 = 7.2;
    state->transform(x1, y1, &x2, &y2);
    const auto &ctm = state->getCTM();
    double expectedX = ctm[0] * x1 + ctm[2] * y1 + ctm[4];
    double expectedY = ctm[1] * x1 + ctm[3] * y1 + ctm[5];
    EXPECT_DOUBLE_EQ(x2, expectedX);
    EXPECT_DOUBLE_EQ(y2, expectedY);
}

// Test transform after setCTM to identity
TEST_F(GfxStateTest_625, TransformAfterSetCTMIdentity_625) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test transform after setCTM with translation only
TEST_F(GfxStateTest_625, TransformWithTranslation_625) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 105.0);
    EXPECT_DOUBLE_EQ(y2, 210.0);
}

// Test transform after setCTM with scaling
TEST_F(GfxStateTest_625, TransformWithScaling_625) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test transform after setCTM with rotation (90 degrees)
TEST_F(GfxStateTest_625, TransformWithRotation90_625) {
    // 90 degree rotation: cos(90)=0, sin(90)=1
    state->setCTM(0.0, 1.0, -1.0, 0.0, 0.0, 0.0);
    double x2, y2;
    state->transform(1.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 1.0);
}

// Test transform with negative coordinates
TEST_F(GfxStateTest_625, TransformNegativeCoordinates_625) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(-5.0, -10.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, -5.0);
    EXPECT_DOUBLE_EQ(y2, -10.0);
}

// Test transform with very large coordinates
TEST_F(GfxStateTest_625, TransformLargeCoordinates_625) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(1e10, 1e10, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 1e10);
    EXPECT_DOUBLE_EQ(y2, 1e10);
}

// Test transform with very small coordinates
TEST_F(GfxStateTest_625, TransformSmallCoordinates_625) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(1e-15, 1e-15, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 1e-15);
    EXPECT_DOUBLE_EQ(y2, 1e-15);
}

// Test transform with zero CTM (degenerate)
TEST_F(GfxStateTest_625, TransformZeroCTM_625) {
    state->setCTM(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    double x2, y2;
    state->transform(100.0, 200.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 0.0);
}

// Test transform with full affine CTM
TEST_F(GfxStateTest_625, TransformFullAffine_625) {
    // a=2, b=1, c=3, d=4, e=5, f=6
    state->setCTM(2.0, 1.0, 3.0, 4.0, 5.0, 6.0);
    double x2, y2;
    state->transform(7.0, 8.0, &x2, &y2);
    // x2 = 2*7 + 3*8 + 5 = 14 + 24 + 5 = 43
    // y2 = 1*7 + 4*8 + 6 = 7 + 32 + 6 = 45
    EXPECT_DOUBLE_EQ(x2, 43.0);
    EXPECT_DOUBLE_EQ(y2, 45.0);
}

// Test transform after concatCTM
TEST_F(GfxStateTest_625, TransformAfterConcatCTM_625) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // Concat a scaling by 2
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(5.0, 10.0, &x2, &y2);
    const auto &ctm = state->getCTM();
    double expectedX = ctm[0] * 5.0 + ctm[2] * 10.0 + ctm[4];
    double expectedY = ctm[1] * 5.0 + ctm[3] * 10.0 + ctm[5];
    EXPECT_DOUBLE_EQ(x2, expectedX);
    EXPECT_DOUBLE_EQ(y2, expectedY);
}

// Test that getCTM returns consistent values with transform
TEST_F(GfxStateTest_625, GetCTMConsistentWithTransform_625) {
    state->setCTM(1.5, 0.5, -0.5, 1.5, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 1.5);
    EXPECT_DOUBLE_EQ(ctm[1], 0.5);
    EXPECT_DOUBLE_EQ(ctm[2], -0.5);
    EXPECT_DOUBLE_EQ(ctm[3], 1.5);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);

    double x2, y2;
    state->transform(3.0, 4.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 1.5 * 3.0 + (-0.5) * 4.0 + 10.0);
    EXPECT_DOUBLE_EQ(y2, 0.5 * 3.0 + 1.5 * 4.0 + 20.0);
}

// Test basic getters after construction
TEST_F(GfxStateTest_625, BasicGettersAfterConstruction_625) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    EXPECT_EQ(state->getRotate(), 0);
}

// Test save and restore
TEST_F(GfxStateTest_625, SaveAndRestore_625) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());

    // Modify the current state
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 2.0);
    EXPECT_DOUBLE_EQ(y2, 2.0);

    // Restore
    GfxState *restored = state->restore();
    // After restore, the state pointer changes
    EXPECT_NE(restored, nullptr);
}

// Test setters and getters for line properties
TEST_F(GfxStateTest_625, LineWidthSetGet_625) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_625, MiterLimitSetGet_625) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 15.0);
}

TEST_F(GfxStateTest_625, FlatnessSetGet_625) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test blend mode setters/getters
TEST_F(GfxStateTest_625, BlendModeSetGet_625) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test opacity setters/getters
TEST_F(GfxStateTest_625, FillOpacitySetGet_625) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_625, StrokeOpacitySetGet_625) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test overprint setters/getters
TEST_F(GfxStateTest_625, FillOverprintSetGet_625) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_625, StrokeOverprintSetGet_625) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test text properties
TEST_F(GfxStateTest_625, CharSpaceSetGet_625) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_625, WordSpaceSetGet_625) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_625, HorizScalingSetGet_625) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_625, LeadingSetGet_625) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

TEST_F(GfxStateTest_625, RiseSetGet_625) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_625, RenderSetGet_625) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test stroke adjust
TEST_F(GfxStateTest_625, StrokeAdjustSetGet_625) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_625, AlphaIsShapeSetGet_625) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_625, TextKnockoutSetGet_625) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test line join and cap
TEST_F(GfxStateTest_625, LineJoinSetGet_625) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_625, LineCapSetGet_625) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test path operations
TEST_F(GfxStateTest_625, PathOperations_625) {
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());

    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());

    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

// Test rendering intent
TEST_F(GfxStateTest_625, RenderingIntentSetGet_625) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test rendering intent with long string (boundary - should truncate or handle gracefully)
TEST_F(GfxStateTest_625, RenderingIntentLongString_625) {
    // The internal buffer is char[32], so test with exactly 31 chars + null
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test text matrix
TEST_F(GfxStateTest_625, TextMatSetGet_625) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 2.0);
    EXPECT_DOUBLE_EQ(mat[2], 3.0);
    EXPECT_DOUBLE_EQ(mat[3], 4.0);
    EXPECT_DOUBLE_EQ(mat[4], 5.0);
    EXPECT_DOUBLE_EQ(mat[5], 6.0);
}

// Test hasSaves when no saves have been done
TEST_F(GfxStateTest_625, NoSavesInitially_625) {
    EXPECT_FALSE(state->hasSaves());
}

// Test line dash
TEST_F(GfxStateTest_625, LineDashSetGet_625) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

// Test overprint mode
TEST_F(GfxStateTest_625, OverprintModeSetGet_625) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test transform with setCTM using negative values
TEST_F(GfxStateTest_625, TransformNegativeCTMValues_625) {
    state->setCTM(-1.0, 0.0, 0.0, -1.0, 100.0, 100.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, -10.0 + 100.0);
    EXPECT_DOUBLE_EQ(y2, -20.0 + 100.0);
}

// Test transformDelta (no translation component)
TEST_F(GfxStateTest_625, TransformDelta_625) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // transformDelta should only apply the linear part, not translation
    const auto &ctm = state->getCTM();
    double expectedX = ctm[0] * 5.0 + ctm[2] * 10.0;
    double expectedY = ctm[1] * 5.0 + ctm[3] * 10.0;
    EXPECT_DOUBLE_EQ(x2, expectedX);
    EXPECT_DOUBLE_EQ(y2, expectedY);
}

// Test page dimensions for rotated state
class GfxStateRotated_625 : public ::testing::Test {
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

TEST_F(GfxStateRotated_625, RotatedStateBasics_625) {
    EXPECT_EQ(state->getRotate(), 90);
    // Page width and height should be swapped for 90-degree rotation
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 792.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 612.0);
}

// Test copy
TEST_F(GfxStateTest_625, CopyState_625) {
    state->setCTM(2.0, 0.0, 0.0, 3.0, 10.0, 20.0);
    state->setLineWidth(5.0);
    GfxState *copied = state->copy();
    ASSERT_NE(copied, nullptr);

    double x2orig, y2orig, x2copy, y2copy;
    state->transform(1.0, 1.0, &x2orig, &y2orig);
    copied->transform(1.0, 1.0, &x2copy, &y2copy);
    EXPECT_DOUBLE_EQ(x2orig, x2copy);
    EXPECT_DOUBLE_EQ(y2orig, y2copy);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 5.0);

    delete copied;
}

// Test clipToRect and getClipBBox
TEST_F(GfxStateTest_625, ClipToRect_625) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip bbox should be intersected with the existing clip
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

// Test transform with zero input
TEST_F(GfxStateTest_625, TransformZeroInput_625) {
    state->setCTM(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 6.0);
    EXPECT_DOUBLE_EQ(y2, 7.0);
}

// Test multiple concatCTM operations
TEST_F(GfxStateTest_625, MultipleConcatCTM_625) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 10.0, 0.0);
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 20.0);
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(x2, ctm[4]);
    EXPECT_DOUBLE_EQ(y2, ctm[5]);
}
