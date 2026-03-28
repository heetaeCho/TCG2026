#include <gtest/gtest.h>
#include "GfxState.h"
#include <cmath>
#include <limits>

class MatrixTest_387 : public ::testing::Test {
protected:
    Matrix matrix;

    void SetUp() override {
        // Default setup - identity matrix
        matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    }
};

// ==================== determinant() tests ====================

TEST_F(MatrixTest_387, DeterminantOfIdentityMatrix_387) {
    // Identity matrix should have determinant = 1
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 1.0);
}

TEST_F(MatrixTest_387, DeterminantOfZeroMatrix_387) {
    // Zero matrix should have determinant = 0
    matrix.init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 0.0);
}

TEST_F(MatrixTest_387, DeterminantOfScalingMatrix_387) {
    // Scaling matrix [2, 0, 0, 3, 0, 0] => det = 2*3 - 0*0 = 6
    matrix.init(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 6.0);
}

TEST_F(MatrixTest_387, DeterminantOfSingularMatrix_387) {
    // Singular matrix [1, 2, 2, 4, 0, 0] => det = 1*4 - 2*2 = 0
    matrix.init(1.0, 2.0, 2.0, 4.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 0.0);
}

TEST_F(MatrixTest_387, DeterminantOfGeneralMatrix_387) {
    // [3, 1, 5, 2, 0, 0] => det = 3*2 - 1*5 = 1
    matrix.init(3.0, 1.0, 5.0, 2.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 1.0);
}

TEST_F(MatrixTest_387, DeterminantNegativeResult_387) {
    // [1, 3, 2, 1, 0, 0] => det = 1*1 - 3*2 = -5
    matrix.init(1.0, 3.0, 2.0, 1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), -5.0);
}

TEST_F(MatrixTest_387, DeterminantIgnoresTranslation_387) {
    // Translation components (m[4], m[5]) should not affect determinant
    matrix.init(1.0, 0.0, 0.0, 1.0, 100.0, 200.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 1.0);
}

TEST_F(MatrixTest_387, DeterminantWithFractionalValues_387) {
    // [0.5, 0.25, 0.1, 0.3, 0, 0] => det = 0.5*0.3 - 0.25*0.1 = 0.15 - 0.025 = 0.125
    matrix.init(0.5, 0.25, 0.1, 0.3, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 0.125);
}

TEST_F(MatrixTest_387, DeterminantWithNegativeValues_387) {
    // [-2, 3, 4, -5, 0, 0] => det = (-2)*(-5) - 3*4 = 10 - 12 = -2
    matrix.init(-2.0, 3.0, 4.0, -5.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), -2.0);
}

TEST_F(MatrixTest_387, DeterminantWithLargeValues_387) {
    matrix.init(1e10, 0.0, 0.0, 1e10, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 1e20);
}

TEST_F(MatrixTest_387, DeterminantWithVerySmallValues_387) {
    matrix.init(1e-10, 0.0, 0.0, 1e-10, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 1e-20);
}

// ==================== invertTo() tests ====================

TEST_F(MatrixTest_387, InvertIdentityMatrix_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    Matrix result;
    EXPECT_TRUE(matrix.invertTo(&result));
    // Inverse of identity is identity
    EXPECT_DOUBLE_EQ(result.m[0], 1.0);
    EXPECT_DOUBLE_EQ(result.m[1], 0.0);
    EXPECT_DOUBLE_EQ(result.m[2], 0.0);
    EXPECT_DOUBLE_EQ(result.m[3], 1.0);
    EXPECT_DOUBLE_EQ(result.m[4], 0.0);
    EXPECT_DOUBLE_EQ(result.m[5], 0.0);
}

TEST_F(MatrixTest_387, InvertSingularMatrixFails_387) {
    // Singular matrix (det = 0)
    matrix.init(1.0, 2.0, 2.0, 4.0, 0.0, 0.0);
    Matrix result;
    EXPECT_FALSE(matrix.invertTo(&result));
}

TEST_F(MatrixTest_387, InvertScalingMatrix_387) {
    matrix.init(2.0, 0.0, 0.0, 4.0, 0.0, 0.0);
    Matrix result;
    EXPECT_TRUE(matrix.invertTo(&result));
    EXPECT_DOUBLE_EQ(result.m[0], 0.5);
    EXPECT_DOUBLE_EQ(result.m[3], 0.25);
}

TEST_F(MatrixTest_387, InvertAndMultiplyShouldGiveIdentity_387) {
    // For a general invertible matrix, M * M^{-1} should be identity
    matrix.init(3.0, 1.0, 5.0, 2.0, 7.0, 11.0);
    Matrix inv;
    ASSERT_TRUE(matrix.invertTo(&inv));

    // Verify by transforming a point through both matrices
    double x = 5.0, y = 3.0;
    double tx, ty;
    matrix.transform(x, y, &tx, &ty);
    double rx, ry;
    inv.transform(tx, ty, &rx, &ry);
    EXPECT_NEAR(rx, x, 1e-10);
    EXPECT_NEAR(ry, y, 1e-10);
}

TEST_F(MatrixTest_387, InvertZeroMatrix_387) {
    matrix.init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Matrix result;
    EXPECT_FALSE(matrix.invertTo(&result));
}

// ==================== translate() tests ====================

TEST_F(MatrixTest_387, TranslateIdentityMatrix_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.translate(10.0, 20.0);
    // After translation, transforming origin should give (10, 20)
    double tx, ty;
    matrix.transform(0.0, 0.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 10.0);
    EXPECT_DOUBLE_EQ(ty, 20.0);
}

TEST_F(MatrixTest_387, TranslateByZero_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 5.0, 5.0);
    matrix.translate(0.0, 0.0);
    double tx, ty;
    matrix.transform(0.0, 0.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 5.0);
    EXPECT_DOUBLE_EQ(ty, 5.0);
}

TEST_F(MatrixTest_387, TranslateNegative_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.translate(-5.0, -10.0);
    double tx, ty;
    matrix.transform(0.0, 0.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, -5.0);
    EXPECT_DOUBLE_EQ(ty, -10.0);
}

// ==================== scale() tests ====================

TEST_F(MatrixTest_387, ScaleIdentityMatrix_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.scale(2.0, 3.0);
    double tx, ty;
    matrix.transform(1.0, 1.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 2.0);
    EXPECT_DOUBLE_EQ(ty, 3.0);
}

TEST_F(MatrixTest_387, ScaleByOne_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.scale(1.0, 1.0);
    double tx, ty;
    matrix.transform(5.0, 7.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 5.0);
    EXPECT_DOUBLE_EQ(ty, 7.0);
}

TEST_F(MatrixTest_387, ScaleByZero_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.scale(0.0, 0.0);
    double tx, ty;
    matrix.transform(5.0, 7.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 0.0);
    EXPECT_DOUBLE_EQ(ty, 0.0);
}

TEST_F(MatrixTest_387, ScaleNegative_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.scale(-1.0, -1.0);
    double tx, ty;
    matrix.transform(3.0, 4.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, -3.0);
    EXPECT_DOUBLE_EQ(ty, -4.0);
}

// ==================== transform() tests ====================

TEST_F(MatrixTest_387, TransformOriginWithIdentity_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tx, ty;
    matrix.transform(0.0, 0.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 0.0);
    EXPECT_DOUBLE_EQ(ty, 0.0);
}

TEST_F(MatrixTest_387, TransformPointWithIdentity_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tx, ty;
    matrix.transform(5.0, 3.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 5.0);
    EXPECT_DOUBLE_EQ(ty, 3.0);
}

TEST_F(MatrixTest_387, TransformWithTranslation_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double tx, ty;
    matrix.transform(1.0, 1.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 11.0);
    EXPECT_DOUBLE_EQ(ty, 21.0);
}

TEST_F(MatrixTest_387, TransformWithScaling_387) {
    matrix.init(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double tx, ty;
    matrix.transform(4.0, 5.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 8.0);
    EXPECT_DOUBLE_EQ(ty, 15.0);
}

TEST_F(MatrixTest_387, TransformWithGeneralMatrix_387) {
    // [a, b, c, d, e, f]
    // tx = a*x + c*y + e
    // ty = b*x + d*y + f
    matrix.init(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    double tx, ty;
    matrix.transform(1.0, 1.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 1.0 * 1.0 + 3.0 * 1.0 + 5.0);  // = 9
    EXPECT_DOUBLE_EQ(ty, 2.0 * 1.0 + 4.0 * 1.0 + 6.0);  // = 12
}

// ==================== norm() tests ====================

TEST_F(MatrixTest_387, NormOfIdentityMatrix_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double n = matrix.norm();
    EXPECT_GT(n, 0.0);
}

TEST_F(MatrixTest_387, NormOfZeroMatrix_387) {
    matrix.init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    double n = matrix.norm();
    EXPECT_DOUBLE_EQ(n, 0.0);
}

TEST_F(MatrixTest_387, NormIsNonNegative_387) {
    matrix.init(-3.0, -4.0, -5.0, -6.0, 0.0, 0.0);
    double n = matrix.norm();
    EXPECT_GE(n, 0.0);
}

TEST_F(MatrixTest_387, NormScalesWithMatrix_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double n1 = matrix.norm();

    matrix.init(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double n2 = matrix.norm();

    EXPECT_GT(n2, n1);
}

// ==================== init() tests ====================

TEST_F(MatrixTest_387, InitSetsValues_387) {
    matrix.init(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(matrix.m[0], 1.0);
    EXPECT_DOUBLE_EQ(matrix.m[1], 2.0);
    EXPECT_DOUBLE_EQ(matrix.m[2], 3.0);
    EXPECT_DOUBLE_EQ(matrix.m[3], 4.0);
    EXPECT_DOUBLE_EQ(matrix.m[4], 5.0);
    EXPECT_DOUBLE_EQ(matrix.m[5], 6.0);
}

TEST_F(MatrixTest_387, InitWithZeros_387) {
    matrix.init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(matrix.m[i], 0.0);
    }
}

// ==================== Combined operations tests ====================

TEST_F(MatrixTest_387, TranslateThenTransformPoint_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.translate(3.0, 4.0);

    double tx, ty;
    matrix.transform(1.0, 2.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 4.0);
    EXPECT_DOUBLE_EQ(ty, 6.0);
}

TEST_F(MatrixTest_387, ScaleThenTransformPoint_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.scale(3.0, 2.0);

    double tx, ty;
    matrix.transform(4.0, 5.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 12.0);
    EXPECT_DOUBLE_EQ(ty, 10.0);
}

TEST_F(MatrixTest_387, DeterminantAfterScale_387) {
    matrix.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.scale(3.0, 5.0);
    EXPECT_DOUBLE_EQ(matrix.determinant(), 15.0);
}

TEST_F(MatrixTest_387, DeterminantUnchangedByTranslation_387) {
    matrix.init(2.0, 1.0, 3.0, 4.0, 0.0, 0.0);
    double detBefore = matrix.determinant();
    matrix.translate(100.0, 200.0);
    double detAfter = matrix.determinant();
    EXPECT_DOUBLE_EQ(detBefore, detAfter);
}
