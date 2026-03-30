#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class MatrixTest_387 : public ::testing::Test {

protected:

    Matrix matrix;

};



TEST_F(MatrixTest_387, DeterminantOfIdentityMatrix_387) {

    // Initialize to identity matrix

    matrix.init(1, 0, 0, 1, 0, 0);

    EXPECT_EQ(matrix.determinant(), 1.0);

}



TEST_F(MatrixTest_387, DeterminantOfZeroMatrix_387) {

    // Initialize to zero matrix

    matrix.init(0, 0, 0, 0, 0, 0);

    EXPECT_EQ(matrix.determinant(), 0.0);

}



TEST_F(MatrixTest_387, InvertIdentityMatrix_387) {

    Matrix inverse;

    matrix.init(1, 0, 0, 1, 0, 0);

    EXPECT_TRUE(matrix.invertTo(&inverse));

    EXPECT_EQ(inverse.determinant(), 1.0);

}



TEST_F(MatrixTest_387, InvertNonInvertibleMatrix_387) {

    Matrix inverse;

    matrix.init(0, 0, 0, 0, 0, 0); // Non-invertible

    EXPECT_FALSE(matrix.invertTo(&inverse));

}



TEST_F(MatrixTest_387, TranslateAndTransform_387) {

    double tx = 1.0;

    double ty = 2.0;

    matrix.translate(tx, ty);

    double x = 0.0;

    double y = 0.0;

    double resultX = 0.0;

    double resultY = 0.0;

    matrix.transform(x, y, &resultX, &resultY);

    EXPECT_EQ(resultX, tx);

    EXPECT_EQ(resultY, ty);

}



TEST_F(MatrixTest_387, ScaleAndTransform_387) {

    double sx = 2.0;

    double sy = 3.0;

    matrix.scale(sx, sy);

    double x = 1.0;

    double y = 1.0;

    double resultX = 0.0;

    double resultY = 0.0;

    matrix.transform(x, y, &resultX, &resultY);

    EXPECT_EQ(resultX, sx * x);

    EXPECT_EQ(resultY, sy * y);

}



TEST_F(MatrixTest_387, NormOfIdentityMatrix_387) {

    matrix.init(1, 0, 0, 1, 0, 0); // Identity matrix

    EXPECT_DOUBLE_EQ(matrix.norm(), 1.0);

}



TEST_F(MatrixTest_387, NormOfZeroMatrix_387) {

    matrix.init(0, 0, 0, 0, 0, 0); // Zero matrix

    EXPECT_DOUBLE_EQ(matrix.norm(), 0.0);

}
