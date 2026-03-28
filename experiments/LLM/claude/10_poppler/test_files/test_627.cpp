#include <gtest/gtest.h>
#include <cmath>
#include "GfxState.h"

// Helper to create a GfxState with default parameters
static GfxState* createDefaultGfxState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return new GfxState(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTextTransformTest_627 : public ::testing::Test {
protected:
    GfxState* state;

    void SetUp() override {
        state = createDefaultGfxState();
    }

    void TearDown() override {
        delete state;
    }
};

// Test identity text matrix transform
TEST_F(GfxStateTextTransformTest_627, IdentityTextMatrix_627) {
    // Set identity text matrix: a=1, b=0, c=0, d=1, e=0, f=0
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test text transform with translation only
TEST_F(GfxStateTextTransformTest_627, TranslationOnly_627) {
    // textMat = [1, 0, 0, 1, 100, 200]
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);

    double x2, y2;
    state->textTransform(0.0, 0.0, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 200.0);
}

// Test text transform with scaling
TEST_F(GfxStateTextTransformTest_627, ScalingTransform_627) {
    // textMat = [2, 0, 0, 3, 0, 0]
    state->setTextMat(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);

    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 10.0);  // 2*5 + 0*10 + 0
    EXPECT_DOUBLE_EQ(y2, 30.0);  // 0*5 + 3*10 + 0
}

// Test text transform with full affine matrix
TEST_F(GfxStateTextTransformTest_627, FullAffineTransform_627) {
    // textMat = [1, 2, 3, 4, 5, 6]
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    double x2, y2;
    state->textTransform(1.0, 1.0, &x2, &y2);

    // x2 = 1*1 + 3*1 + 5 = 9
    // y2 = 2*1 + 4*1 + 6 = 12
    EXPECT_DOUBLE_EQ(x2, 9.0);
    EXPECT_DOUBLE_EQ(y2, 12.0);
}

// Test text transform with zero input
TEST_F(GfxStateTextTransformTest_627, ZeroInput_627) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    double x2, y2;
    state->textTransform(0.0, 0.0, &x2, &y2);

    // x2 = 1*0 + 3*0 + 5 = 5
    // y2 = 2*0 + 4*0 + 6 = 6
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 6.0);
}

// Test text transform with negative values
TEST_F(GfxStateTextTransformTest_627, NegativeValues_627) {
    state->setTextMat(-1.0, -2.0, -3.0, -4.0, -5.0, -6.0);

    double x2, y2;
    state->textTransform(1.0, 1.0, &x2, &y2);

    // x2 = -1*1 + -3*1 + -5 = -9
    // y2 = -2*1 + -4*1 + -6 = -12
    EXPECT_DOUBLE_EQ(x2, -9.0);
    EXPECT_DOUBLE_EQ(y2, -12.0);
}

// Test text transform with rotation-like matrix (90 degrees)
TEST_F(GfxStateTextTransformTest_627, RotationMatrix90Degrees_627) {
    // 90 degree rotation: [cos90, sin90, -sin90, cos90, 0, 0] = [0, 1, -1, 0, 0, 0]
    state->setTextMat(0.0, 1.0, -1.0, 0.0, 0.0, 0.0);

    double x2, y2;
    state->textTransform(1.0, 0.0, &x2, &y2);

    // x2 = 0*1 + -1*0 + 0 = 0
    // y2 = 1*1 + 0*0 + 0 = 1
    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 1.0);
}

// Test text transform with large values
TEST_F(GfxStateTextTransformTest_627, LargeValues_627) {
    state->setTextMat(1e6, 0.0, 0.0, 1e6, 1e6, 1e6);

    double x2, y2;
    state->textTransform(1e6, 1e6, &x2, &y2);

    // x2 = 1e6 * 1e6 + 0 * 1e6 + 1e6 = 1e12 + 1e6
    // y2 = 0 * 1e6 + 1e6 * 1e6 + 1e6 = 1e12 + 1e6
    EXPECT_DOUBLE_EQ(x2, 1e12 + 1e6);
    EXPECT_DOUBLE_EQ(y2, 1e12 + 1e6);
}

// Test text transform with fractional values
TEST_F(GfxStateTextTransformTest_627, FractionalValues_627) {
    state->setTextMat(0.5, 0.25, 0.75, 0.125, 0.1, 0.2);

    double x2, y2;
    state->textTransform(2.0, 4.0, &x2, &y2);

    // x2 = 0.5*2 + 0.75*4 + 0.1 = 1.0 + 3.0 + 0.1 = 4.1
    // y2 = 0.25*2 + 0.125*4 + 0.2 = 0.5 + 0.5 + 0.2 = 1.2
    EXPECT_DOUBLE_EQ(x2, 4.1);
    EXPECT_DOUBLE_EQ(y2, 1.2);
}

// Test text transform with only x input (y=0)
TEST_F(GfxStateTextTransformTest_627, OnlyXInput_627) {
    state->setTextMat(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

    double x2, y2;
    state->textTransform(10.0, 0.0, &x2, &y2);

    // x2 = 2*10 + 4*0 + 6 = 26
    // y2 = 3*10 + 5*0 + 7 = 37
    EXPECT_DOUBLE_EQ(x2, 26.0);
    EXPECT_DOUBLE_EQ(y2, 37.0);
}

// Test text transform with only y input (x=0)
TEST_F(GfxStateTextTransformTest_627, OnlyYInput_627) {
    state->setTextMat(2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

    double x2, y2;
    state->textTransform(0.0, 10.0, &x2, &y2);

    // x2 = 2*0 + 4*10 + 6 = 46
    // y2 = 3*0 + 5*10 + 7 = 57
    EXPECT_DOUBLE_EQ(x2, 46.0);
    EXPECT_DOUBLE_EQ(y2, 57.0);
}

// Test text transform with zero matrix
TEST_F(GfxStateTextTransformTest_627, ZeroMatrix_627) {
    state->setTextMat(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 0.0);
}

// Test that textTransform uses the current textMat properly after setting it multiple times
TEST_F(GfxStateTextTransformTest_627, MatrixUpdate_627) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    double x2, y2;
    state->textTransform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 5.0);

    // Now update the text matrix
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);

    state->textTransform(5.0, 5.0, &x2, &y2);
    // x2 = 2*5 + 0*5 + 10 = 20
    // y2 = 0*5 + 2*5 + 20 = 30
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 30.0);
}

// Test textTransform with negative input coordinates
TEST_F(GfxStateTextTransformTest_627, NegativeInputCoordinates_627) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);

    double x2, y2;
    state->textTransform(-5.0, -10.0, &x2, &y2);

    // x2 = 1*(-5) + 0*(-10) + 10 = 5
    // y2 = 0*(-5) + 1*(-10) + 20 = 10
    EXPECT_DOUBLE_EQ(x2, 5.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// Test textTransform consistency with getTextMat
TEST_F(GfxStateTextTransformTest_627, ConsistencyWithGetTextMat_627) {
    state->setTextMat(1.5, 2.5, 3.5, 4.5, 5.5, 6.5);

    const auto& mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.5);
    EXPECT_DOUBLE_EQ(mat[1], 2.5);
    EXPECT_DOUBLE_EQ(mat[2], 3.5);
    EXPECT_DOUBLE_EQ(mat[3], 4.5);
    EXPECT_DOUBLE_EQ(mat[4], 5.5);
    EXPECT_DOUBLE_EQ(mat[5], 6.5);

    double x2, y2;
    double x1 = 3.0, y1 = 7.0;
    state->textTransform(x1, y1, &x2, &y2);

    double expectedX = mat[0] * x1 + mat[2] * y1 + mat[4];
    double expectedY = mat[1] * x1 + mat[3] * y1 + mat[5];
    EXPECT_DOUBLE_EQ(x2, expectedX);
    EXPECT_DOUBLE_EQ(y2, expectedY);
}

// Test textTransformDelta (no translation component)
TEST_F(GfxStateTextTransformTest_627, TextTransformDelta_627) {
    state->setTextMat(2.0, 3.0, 4.0, 5.0, 100.0, 200.0);

    double x2, y2;
    state->textTransformDelta(1.0, 1.0, &x2, &y2);

    // Delta should not include translation:
    // x2 = 2*1 + 4*1 = 6
    // y2 = 3*1 + 5*1 = 8
    EXPECT_DOUBLE_EQ(x2, 6.0);
    EXPECT_DOUBLE_EQ(y2, 8.0);
}

// Test textTransformDelta with zero input
TEST_F(GfxStateTextTransformTest_627, TextTransformDeltaZeroInput_627) {
    state->setTextMat(2.0, 3.0, 4.0, 5.0, 100.0, 200.0);

    double x2, y2;
    state->textTransformDelta(0.0, 0.0, &x2, &y2);

    EXPECT_DOUBLE_EQ(x2, 0.0);
    EXPECT_DOUBLE_EQ(y2, 0.0);
}

// Test that copy preserves textMat and thus textTransform behavior
TEST_F(GfxStateTextTransformTest_627, CopyPreservesTextMat_627) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    GfxState* copied = state->copy();
    ASSERT_NE(copied, nullptr);

    double x2_orig, y2_orig, x2_copy, y2_copy;
    state->textTransform(7.0, 8.0, &x2_orig, &y2_orig);
    copied->textTransform(7.0, 8.0, &x2_copy, &y2_copy);

    EXPECT_DOUBLE_EQ(x2_orig, x2_copy);
    EXPECT_DOUBLE_EQ(y2_orig, y2_copy);

    delete copied;
}

// Test save/restore preserves text matrix
TEST_F(GfxStateTextTransformTest_627, SaveRestorePreservesTextMat_627) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    GfxState* saved = state->save();
    ASSERT_NE(saved, nullptr);

    // Modify textMat on saved state
    saved->setTextMat(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);

    double x2, y2;
    saved->textTransform(1.0, 1.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0 + 30.0 + 50.0);  // 90
    EXPECT_DOUBLE_EQ(y2, 20.0 + 40.0 + 60.0);   // 120

    // Restore
    GfxState* restored = saved->restore();

    double x2r, y2r;
    restored->textTransform(1.0, 1.0, &x2r, &y2r);
    EXPECT_DOUBLE_EQ(x2r, 1.0 + 3.0 + 5.0);   // 9
    EXPECT_DOUBLE_EQ(y2r, 2.0 + 4.0 + 6.0);    // 12
}
