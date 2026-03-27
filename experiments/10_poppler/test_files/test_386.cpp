#include <gtest/gtest.h>

#include "GfxState.h"



class MatrixTest_386 : public ::testing::Test {

protected:

    Matrix matrix;



    void SetUp() override {

        // Initialize matrix to a known state

        matrix.init(1, 0, 0, 1, 0, 0);

    }

};



TEST_F(MatrixTest_386, InitSetsValuesCorrectly_386) {

    double xx = 2.5, yx = 1.5, xy = 0.5, yy = 2.0, x0 = 1.0, y0 = -1.0;

    matrix.init(xx, yx, xy, yy, x0, y0);

    EXPECT_DOUBLE_EQ(matrix.m[0], xx);

    EXPECT_DOUBLE_EQ(matrix.m[1], yx);

    EXPECT_DOUBLE_EQ(matrix.m[2], xy);

    EXPECT_DOUBLE_EQ(matrix.m[3], yy);

    EXPECT_DOUBLE_EQ(matrix.m[4], x0);

    EXPECT_DOUBLE_EQ(matrix.m[5], y0);

}



TEST_F(MatrixTest_386, TranslateModifiesMatrixCorrectly_386) {

    matrix.translate(2.0, 3.0);

    EXPECT_DOUBLE_EQ(matrix.m[4], 2.0);

    EXPECT_DOUBLE_EQ(matrix.m[5], 3.0);

}



TEST_F(MatrixTest_386, ScaleModifiesMatrixCorrectly_386) {

    matrix.scale(2.0, 3.0);

    EXPECT_DOUBLE_EQ(matrix.m[0], 2.0);

    EXPECT_DOUBLE_EQ(matrix.m[1], 0.0);

    EXPECT_DOUBLE_EQ(matrix.m[2], 0.0);

    EXPECT_DOUBLE_EQ(matrix.m[3], 3.0);

}



TEST_F(MatrixTest_386, TransformAppliesMatrixCorrectly_386) {

    double x = 1.0, y = 2.0;

    double tx, ty;

    matrix.transform(x, y, &tx, &ty);

    EXPECT_DOUBLE_EQ(tx, x);

    EXPECT_DOUBLE_EQ(ty, y);



    matrix.translate(2.0, 3.0);

    matrix.transform(x, y, &tx, &ty);

    EXPECT_DOUBLE_EQ(tx, 3.0);

    EXPECT_DOUBLE_EQ(ty, 5.0);

}



TEST_F(MatrixTest_386, NormCalculatesCorrectlyForIdentityMatrix_386) {

    EXPECT_DOUBLE_EQ(matrix.norm(), 1.0);

}



TEST_F(MatrixTest_386, DeterminantOfIdentityMatrixIsOne_386) {

    EXPECT_DOUBLE_EQ(matrix.determinant(), 1.0);

}



TEST_F(MatrixTest_386, InvertToHandlesInversionProperly_386) {

    Matrix inverse;

    matrix.scale(2.0, 3.0); // Non-identity matrix

    bool success = matrix.invertTo(&inverse);



    EXPECT_TRUE(success);

    double expectedInverse[6] = {0.5, 0.0, 0.0, 1.0/3.0, 0.0, 0.0};

    for (int i = 0; i < 6; ++i) {

        EXPECT_DOUBLE_EQ(inverse.m[i], expectedInverse[i]);

    }

}



TEST_F(MatrixTest_386, InvertToFailsForSingularMatrix_386) {

    Matrix singular;

    singular.init(1, 2, 2, 4, 0, 0); // Singular matrix

    Matrix inverse;

    bool success = singular.invertTo(&inverse);



    EXPECT_FALSE(success);

}
