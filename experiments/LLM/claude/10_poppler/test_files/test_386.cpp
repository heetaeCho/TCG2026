#include <gtest/gtest.h>
#include "GfxState.h"
#include <cmath>
#include <limits>

class MatrixTest_386 : public ::testing::Test {
protected:
    Matrix mat;
};

// ==================== init tests ====================

TEST_F(MatrixTest_386, InitSetsValues_386) {
    mat.init(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(mat.m[0], 1.0);
    EXPECT_DOUBLE_EQ(mat.m[1], 2.0);
    EXPECT_DOUBLE_EQ(mat.m[2], 3.0);
    EXPECT_DOUBLE_EQ(mat.m[3], 4.0);
    EXPECT_DOUBLE_EQ(mat.m[4], 5.0);
    EXPECT_DOUBLE_EQ(mat.m[5], 6.0);
}

TEST_F(MatrixTest_386, InitIdentityMatrix_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(mat.m[0], 1.0);
    EXPECT_DOUBLE_EQ(mat.m[1], 0.0);
    EXPECT_DOUBLE_EQ(mat.m[2], 0.0);
    EXPECT_DOUBLE_EQ(mat.m[3], 1.0);
    EXPECT_DOUBLE_EQ(mat.m[4], 0.0);
    EXPECT_DOUBLE_EQ(mat.m[5], 0.0);
}

TEST_F(MatrixTest_386, InitZeroMatrix_386) {
    mat.init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(mat.m[i], 0.0);
    }
}

TEST_F(MatrixTest_386, InitNegativeValues_386) {
    mat.init(-1.0, -2.0, -3.0, -4.0, -5.0, -6.0);
    EXPECT_DOUBLE_EQ(mat.m[0], -1.0);
    EXPECT_DOUBLE_EQ(mat.m[1], -2.0);
    EXPECT_DOUBLE_EQ(mat.m[2], -3.0);
    EXPECT_DOUBLE_EQ(mat.m[3], -4.0);
    EXPECT_DOUBLE_EQ(mat.m[4], -5.0);
    EXPECT_DOUBLE_EQ(mat.m[5], -6.0);
}

// ==================== determinant tests ====================

TEST_F(MatrixTest_386, DeterminantIdentity_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(mat.determinant(), 1.0);
}

TEST_F(MatrixTest_386, DeterminantZero_386) {
    mat.init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(mat.determinant(), 0.0);
}

TEST_F(MatrixTest_386, DeterminantGeneral_386) {
    // det = xx*yy - yx*xy = 1*4 - 2*3 = -2
    mat.init(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(mat.determinant(), -2.0);
}

TEST_F(MatrixTest_386, DeterminantSingular_386) {
    // Singular matrix: rows are proportional
    mat.init(2.0, 4.0, 1.0, 2.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(mat.determinant(), 0.0);
}

TEST_F(MatrixTest_386, DeterminantScaling_386) {
    // Scaling matrix: det = sx * sy = 3 * 5 = 15
    mat.init(3.0, 0.0, 0.0, 5.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(mat.determinant(), 15.0);
}

// ==================== transform tests ====================

TEST_F(MatrixTest_386, TransformIdentity_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tx, ty;
    mat.transform(3.0, 4.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 3.0);
    EXPECT_DOUBLE_EQ(ty, 4.0);
}

TEST_F(MatrixTest_386, TransformTranslation_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double tx, ty;
    mat.transform(3.0, 4.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 13.0);
    EXPECT_DOUBLE_EQ(ty, 24.0);
}

TEST_F(MatrixTest_386, TransformScaling_386) {
    mat.init(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double tx, ty;
    mat.transform(5.0, 7.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 10.0);
    EXPECT_DOUBLE_EQ(ty, 21.0);
}

TEST_F(MatrixTest_386, TransformGeneral_386) {
    // Affine transform: tx = xx*x + xy*y + x0, ty = yx*x + yy*y + y0
    mat.init(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    double tx, ty;
    mat.transform(1.0, 1.0, &tx, &ty);
    // tx = 1*1 + 3*1 + 5 = 9
    // ty = 2*1 + 4*1 + 6 = 12
    EXPECT_DOUBLE_EQ(tx, 9.0);
    EXPECT_DOUBLE_EQ(ty, 12.0);
}

TEST_F(MatrixTest_386, TransformOrigin_386) {
    mat.init(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    double tx, ty;
    mat.transform(0.0, 0.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 5.0);
    EXPECT_DOUBLE_EQ(ty, 6.0);
}

// ==================== invertTo tests ====================

TEST_F(MatrixTest_386, InvertIdentity_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    Matrix inv;
    bool result = mat.invertTo(&inv);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(inv.m[0], 1.0);
    EXPECT_DOUBLE_EQ(inv.m[1], 0.0);
    EXPECT_DOUBLE_EQ(inv.m[2], 0.0);
    EXPECT_DOUBLE_EQ(inv.m[3], 1.0);
    EXPECT_DOUBLE_EQ(inv.m[4], 0.0);
    EXPECT_DOUBLE_EQ(inv.m[5], 0.0);
}

TEST_F(MatrixTest_386, InvertSingularMatrixFails_386) {
    mat.init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Matrix inv;
    bool result = mat.invertTo(&inv);
    EXPECT_FALSE(result);
}

TEST_F(MatrixTest_386, InvertScaling_386) {
    mat.init(2.0, 0.0, 0.0, 4.0, 0.0, 0.0);
    Matrix inv;
    bool result = mat.invertTo(&inv);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(inv.m[0], 0.5);
    EXPECT_DOUBLE_EQ(inv.m[3], 0.25);
}

TEST_F(MatrixTest_386, InvertAndTransformRecoversOriginal_386) {
    mat.init(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix inv;
    bool result = mat.invertTo(&inv);
    EXPECT_TRUE(result);

    double tx, ty;
    mat.transform(7.0, 8.0, &tx, &ty);

    double rx, ry;
    inv.transform(tx, ty, &rx, &ry);

    EXPECT_NEAR(rx, 7.0, 1e-10);
    EXPECT_NEAR(ry, 8.0, 1e-10);
}

TEST_F(MatrixTest_386, InvertSingularRowProportional_386) {
    mat.init(2.0, 4.0, 1.0, 2.0, 0.0, 0.0);
    Matrix inv;
    bool result = mat.invertTo(&inv);
    EXPECT_FALSE(result);
}

// ==================== translate tests ====================

TEST_F(MatrixTest_386, TranslateFromIdentity_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    mat.translate(10.0, 20.0);
    double tx, ty;
    mat.transform(0.0, 0.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 10.0);
    EXPECT_DOUBLE_EQ(ty, 20.0);
}

TEST_F(MatrixTest_386, TranslateZero_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 5.0, 6.0);
    mat.translate(0.0, 0.0);
    double tx, ty;
    mat.transform(0.0, 0.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 5.0);
    EXPECT_DOUBLE_EQ(ty, 6.0);
}

TEST_F(MatrixTest_386, TranslateAccumulates_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    mat.translate(5.0, 10.0);
    mat.translate(3.0, 7.0);
    double tx, ty;
    mat.transform(0.0, 0.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 8.0);
    EXPECT_DOUBLE_EQ(ty, 17.0);
}

// ==================== scale tests ====================

TEST_F(MatrixTest_386, ScaleFromIdentity_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    mat.scale(2.0, 3.0);
    double tx, ty;
    mat.transform(5.0, 7.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 10.0);
    EXPECT_DOUBLE_EQ(ty, 21.0);
}

TEST_F(MatrixTest_386, ScaleByOne_386) {
    mat.init(2.0, 0.0, 0.0, 3.0, 4.0, 5.0);
    Matrix original;
    original.init(2.0, 0.0, 0.0, 3.0, 4.0, 5.0);
    mat.scale(1.0, 1.0);
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(mat.m[i], original.m[i]);
    }
}

TEST_F(MatrixTest_386, ScaleByZero_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    mat.scale(0.0, 0.0);
    double tx, ty;
    mat.transform(5.0, 7.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, 0.0);
    EXPECT_DOUBLE_EQ(ty, 0.0);
}

TEST_F(MatrixTest_386, ScaleNegative_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    mat.scale(-1.0, -1.0);
    double tx, ty;
    mat.transform(5.0, 7.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, -5.0);
    EXPECT_DOUBLE_EQ(ty, -7.0);
}

// ==================== norm tests ====================

TEST_F(MatrixTest_386, NormIdentity_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double n = mat.norm();
    EXPECT_GT(n, 0.0);
}

TEST_F(MatrixTest_386, NormZeroMatrix_386) {
    mat.init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    double n = mat.norm();
    EXPECT_DOUBLE_EQ(n, 0.0);
}

TEST_F(MatrixTest_386, NormScaling_386) {
    mat.init(3.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double n = mat.norm();
    // Norm should be positive and reflect the scaling
    EXPECT_GT(n, 0.0);
}

TEST_F(MatrixTest_386, NormIsNonNegative_386) {
    mat.init(-5.0, -3.0, -2.0, -7.0, -1.0, -4.0);
    double n = mat.norm();
    EXPECT_GE(n, 0.0);
}

// ==================== Boundary / edge cases ====================

TEST_F(MatrixTest_386, InitWithLargeValues_386) {
    double large = 1e15;
    mat.init(large, large, large, large, large, large);
    EXPECT_DOUBLE_EQ(mat.m[0], large);
    EXPECT_DOUBLE_EQ(mat.m[5], large);
}

TEST_F(MatrixTest_386, InitWithSmallValues_386) {
    double small = 1e-15;
    mat.init(small, small, small, small, small, small);
    EXPECT_DOUBLE_EQ(mat.m[0], small);
}

TEST_F(MatrixTest_386, InvertNearSingular_386) {
    // Near-singular matrix with very small determinant
    mat.init(1.0, 0.0, 0.0, 1e-300, 0.0, 0.0);
    Matrix inv;
    bool result = mat.invertTo(&inv);
    // It may or may not succeed depending on threshold, but shouldn't crash
    if (result) {
        // If it succeeds, verify the inverse is reasonable
        double tx, ty;
        mat.transform(1.0, 1.0, &tx, &ty);
        double rx, ry;
        inv.transform(tx, ty, &rx, &ry);
        EXPECT_NEAR(rx, 1.0, 1e-5);
        EXPECT_NEAR(ry, 1.0, 1e-5);
    }
}

TEST_F(MatrixTest_386, TransformWithNegativeCoordinates_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double tx, ty;
    mat.transform(-3.0, -4.0, &tx, &ty);
    EXPECT_DOUBLE_EQ(tx, -3.0);
    EXPECT_DOUBLE_EQ(ty, -4.0);
}

TEST_F(MatrixTest_386, DeterminantNegative_386) {
    // det = 1*1 - 2*3 = 1 - 6 = -5
    mat.init(1.0, 2.0, 3.0, 1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(mat.determinant(), -5.0);
}

TEST_F(MatrixTest_386, DeterminantPositive_386) {
    // det = 4*1 - 0*0 = 4
    mat.init(4.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(mat.determinant(), 4.0);
}

TEST_F(MatrixTest_386, ScaleThenTransformConsistent_386) {
    mat.init(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    mat.scale(2.0, 3.0);
    
    Matrix expected;
    expected.init(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    
    double tx1, ty1, tx2, ty2;
    mat.transform(4.0, 5.0, &tx1, &ty1);
    expected.transform(4.0, 5.0, &tx2, &ty2);
    
    EXPECT_DOUBLE_EQ(tx1, tx2);
    EXPECT_DOUBLE_EQ(ty1, ty2);
}

TEST_F(MatrixTest_386, TranslateWithNonIdentityBase_386) {
    mat.init(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    mat.translate(5.0, 7.0);
    double tx, ty;
    mat.transform(0.0, 0.0, &tx, &ty);
    // After translate, transforming origin should give the translated point
    // The translate should compose: new transform of (0,0) = old transform of (5,7)
    // which is (2*5, 3*7) = (10, 21)
    EXPECT_DOUBLE_EQ(tx, 10.0);
    EXPECT_DOUBLE_EQ(ty, 21.0);
}
