#include <gtest/gtest.h>
#include "GfxState.h"

// Helper to create a GfxState with a known CTM
// The constructor takes (hDPI, vDPI, pageBox, rotate, upsideDown)
// We'll use a simple page box and identity-like CTM, then set CTM explicitly.

class GfxStateTransformDeltaTest_626 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = new GfxState(72, 72, &pageBox, 0, false);
    }

    void TearDown() override {
        delete state;
    }

    GfxState *state;
};

// Test transformDelta with identity CTM
TEST_F(GfxStateTransformDeltaTest_626, IdentityCTM_TransformDelta_626) {
    // Set CTM to identity: a=1, b=0, c=0, d=1, e=0, f=0
    state->setCTM(1, 0, 0, 1, 0, 0);

    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);

    // With identity: x2 = 1*5 + 0*10 = 5, y2 = 0*5 + 1*10 = 10
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test transformDelta with zero input
TEST_F(GfxStateTransformDeltaTest_626, ZeroInput_626) {
    state->setCTM(2, 3, 4, 5, 6, 7);

    double x2, y2;
    state->transformDelta(0.0, 0.0, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 0.0);
}

// Test transformDelta with scaling CTM
TEST_F(GfxStateTransformDeltaTest_626, ScalingCTM_626) {
    // CTM: a=2, b=0, c=0, d=3, e=10, f=20
    // transformDelta ignores e,f (translation)
    state->setCTM(2, 0, 0, 3, 10, 20);

    double x2, y2;
    state->transformDelta(4.0, 5.0, &x2, &y2);

    // x2 = 2*4 + 0*5 = 8, y2 = 0*4 + 3*5 = 15
    EXPECT_DOUBLE_EQ(x2, 8.0);
    EXPECT_DOUBLE_EQ(y2, 15.0);
}

// Test transformDelta with rotation-like CTM
TEST_F(GfxStateTransformDeltaTest_626, RotationCTM_626) {
    // 90 degree rotation: a=0, b=1, c=-1, d=0
    state->setCTM(0, 1, -1, 0, 0, 0);

    double x2, y2;
    state->transformDelta(3.0, 4.0, &x2, &y2);

    // x2 = 0*3 + (-1)*4 = -4, y2 = 1*3 + 0*4 = 3
    EXPECT_DOUBLE_EQ(x2, -4.0);
    EXPECT_DOUBLE_EQ(y2, 3.0);
}

// Test transformDelta with general affine (non-trivial all elements)
TEST_F(GfxStateTransformDeltaTest_626, GeneralCTM_626) {
    // CTM: a=2, b=3, c=4, d=5, e=100, f=200
    state->setCTM(2, 3, 4, 5, 100, 200);

    double x2, y2;
    state->transformDelta(1.0, 1.0, &x2, &y2);

    // x2 = 2*1 + 4*1 = 6, y2 = 3*1 + 5*1 = 8
    EXPECT_DOUBLE_EQ(x2, 6.0);
    EXPECT_DOUBLE_EQ(y2, 8.0);
}

// Test transformDelta with negative inputs
TEST_F(GfxStateTransformDeltaTest_626, NegativeInputs_626) {
    state->setCTM(1, 0, 0, 1, 0, 0);

    double x2, y2;
    state->transformDelta(-3.0, -7.0, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, -3.0);
    EXPECT_DOUBLE_EQ(y2, -7.0);
}

// Test transformDelta with negative CTM values
TEST_F(GfxStateTransformDeltaTest_626, NegativeCTMValues_626) {
    state->setCTM(-1, -2, -3, -4, 0, 0);

    double x2, y2;
    state->transformDelta(2.0, 3.0, &x2, &y2);

    // x2 = (-1)*2 + (-3)*3 = -2 -9 = -11
    // y2 = (-2)*2 + (-4)*3 = -4 -12 = -16
    EXPECT_DOUBLE_EQ(x2, -11.0);
    EXPECT_DOUBLE_EQ(y2, -16.0);
}

// Test transformDelta with very large values
TEST_F(GfxStateTransformDeltaTest_626, LargeValues_626) {
    state->setCTM(1e6, 0, 0, 1e6, 0, 0);

    double x2, y2;
    state->transformDelta(1e6, 1e6, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 1e12);
    EXPECT_DOUBLE_EQ(y2, 1e12);
}

// Test transformDelta with very small values
TEST_F(GfxStateTransformDeltaTest_626, SmallValues_626) {
    state->setCTM(1e-10, 0, 0, 1e-10, 0, 0);

    double x2, y2;
    state->transformDelta(1e-10, 1e-10, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 1e-20);
    EXPECT_DOUBLE_EQ(y2, 1e-20);
}

// Test that transformDelta does NOT include translation (e, f)
// Unlike transform(), transformDelta should only use the matrix part
TEST_F(GfxStateTransformDeltaTest_626, NoTranslation_626) {
    state->setCTM(1, 0, 0, 1, 500, 600);

    double x2_delta, y2_delta;
    state->transformDelta(0.0, 0.0, &x2_delta, &y2_delta);

    // Delta transform of zero should be zero regardless of translation
    EXPECT_DOUBLE_EQ(x2_delta, 0.0);
    EXPECT_DOUBLE_EQ(y2_delta, 0.0);
}

// Test transformDelta with only x input (y=0)
TEST_F(GfxStateTransformDeltaTest_626, OnlyXInput_626) {
    state->setCTM(3, 4, 5, 6, 0, 0);

    double x2, y2;
    state->transformDelta(2.0, 0.0, &x2, &y2);

    // x2 = 3*2 + 5*0 = 6, y2 = 4*2 + 6*0 = 8
    EXPECT_DOUBLE_EQ(x2, 6.0);
    EXPECT_DOUBLE_EQ(y2, 8.0);
}

// Test transformDelta with only y input (x=0)
TEST_F(GfxStateTransformDeltaTest_626, OnlyYInput_626) {
    state->setCTM(3, 4, 5, 6, 0, 0);

    double x2, y2;
    state->transformDelta(0.0, 2.0, &x2, &y2);

    // x2 = 3*0 + 5*2 = 10, y2 = 4*0 + 6*2 = 12
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 12.0);
}

// Test transformDelta after concatCTM
TEST_F(GfxStateTransformDeltaTest_626, AfterConcatCTM_626) {
    // Start with identity
    state->setCTM(1, 0, 0, 1, 0, 0);
    // Concatenate a scaling of 2x in x, 3x in y
    state->concatCTM(2, 0, 0, 3, 0, 0);

    double x2, y2;
    state->transformDelta(5.0, 7.0, &x2, &y2);

    // After concat with identity, CTM should be the scaling matrix
    // x2 = 2*5 + 0*7 = 10, y2 = 0*5 + 3*7 = 21
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 21.0);
}

// Test that transformDelta is consistent with getCTM
TEST_F(GfxStateTransformDeltaTest_626, ConsistentWithGetCTM_626) {
    state->setCTM(2.5, 1.5, -0.5, 3.0, 10, 20);

    const auto &ctm = state->getCTM();
    double x1 = 4.0, y1 = 6.0;
    double x2, y2;
    state->transformDelta(x1, y1, &x2, &y2);

    // Manually compute using CTM array
    double expected_x2 = ctm[0] * x1 + ctm[2] * y1;
    double expected_y2 = ctm[1] * x1 + ctm[3] * y1;

    EXPECT_DOUBLE_EQ(x2, expected_x2);
    EXPECT_DOUBLE_EQ(y2, expected_y2);
}

// Test transformDelta with zero CTM (degenerate case)
TEST_F(GfxStateTransformDeltaTest_626, ZeroCTM_626) {
    state->setCTM(0, 0, 0, 0, 0, 0);

    double x2, y2;
    state->transformDelta(100.0, 200.0, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 0.0);
}

// Test transformDelta with fractional values
TEST_F(GfxStateTransformDeltaTest_626, FractionalValues_626) {
    state->setCTM(0.5, 0.25, 0.75, 1.5, 0, 0);

    double x2, y2;
    state->transformDelta(2.0, 4.0, &x2, &y2);

    // x2 = 0.5*2 + 0.75*4 = 1 + 3 = 4
    // y2 = 0.25*2 + 1.5*4 = 0.5 + 6 = 6.5
    EXPECT_DOUBLE_EQ(x2, 4.0);
    EXPECT_DOUBLE_EQ(y2, 6.5);
}
