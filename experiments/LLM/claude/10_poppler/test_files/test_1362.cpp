#include <gtest/gtest.h>
#include <QPointF>
#include <cmath>

// Include the header under test
#include "poppler-annotation-helper.h"

using namespace Poppler;

class XPDFReaderInvTransformTest_1362 : public ::testing::Test {
protected:
    XPDFReader reader;
};

// Test identity matrix: M = [1,0,0,1,0,0] should return the same point
TEST_F(XPDFReaderInvTransformTest_1362, IdentityMatrix_1362) {
    double M[6] = {1, 0, 0, 1, 0, 0};
    QPointF p(3.0, 7.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 7.0);
}

// Test identity matrix with translation: M = [1,0,0,1,tx,ty]
TEST_F(XPDFReaderInvTransformTest_1362, IdentityWithTranslation_1362) {
    double M[6] = {1, 0, 0, 1, 5.0, 10.0};
    QPointF p(8.0, 15.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    // xt = 8-5 = 3, yt = 15-10 = 5
    // invM for identity is identity, so x=3, y=5
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 5.0);
}

// Test scaling matrix: M = [2,0,0,3,0,0]
TEST_F(XPDFReaderInvTransformTest_1362, ScalingMatrix_1362) {
    double M[6] = {2, 0, 0, 3, 0, 0};
    QPointF p(6.0, 9.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    // det = 2*3 - 0*0 = 6
    // invM = [3/6, 0, 0, 2/6] = [0.5, 0, 0, 1/3]
    // x = 0.5*6 + 0*9 = 3
    // y = 0*6 + (1/3)*9 = 3
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 3.0);
}

// Test singular matrix: M = [0,0,0,0,0,0] should return x=0, y=0
TEST_F(XPDFReaderInvTransformTest_1362, SingularMatrix_1362) {
    double M[6] = {0, 0, 0, 0, 0, 0};
    QPointF p(5.0, 10.0);
    double x, y;
    x = 999.0;
    y = 999.0;
    reader.invTransform(M, p, x, y);
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

// Test another singular matrix where det = M[0]*M[3] - M[1]*M[2] = 0
TEST_F(XPDFReaderInvTransformTest_1362, SingularMatrixNonZeroEntries_1362) {
    // M = [2, 4, 1, 2, 0, 0], det = 2*2 - 4*1 = 0
    double M[6] = {2, 4, 1, 2, 0, 0};
    QPointF p(1.0, 1.0);
    double x, y;
    x = 123.0;
    y = 456.0;
    reader.invTransform(M, p, x, y);
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

// Test origin point with identity matrix
TEST_F(XPDFReaderInvTransformTest_1362, OriginPoint_1362) {
    double M[6] = {1, 0, 0, 1, 0, 0};
    QPointF p(0.0, 0.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

// Test rotation-like matrix (90 degrees): M = [0, 1, -1, 0, 0, 0]
TEST_F(XPDFReaderInvTransformTest_1362, RotationMatrix90Degrees_1362) {
    double M[6] = {0, 1, -1, 0, 0, 0};
    QPointF p(3.0, 4.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    // det = 0*0 - 1*(-1) = 1
    // invM = [0/1, -1/1, -(-1)/1, 0/1] = [0, -1, 1, 0]
    // xt = 3, yt = 4
    // x = 0*3 + 1*4 = 4
    // y = -1*3 + 0*4 = -3
    EXPECT_DOUBLE_EQ(x, 4.0);
    EXPECT_DOUBLE_EQ(y, -3.0);
}

// Test general affine matrix
TEST_F(XPDFReaderInvTransformTest_1362, GeneralAffineMatrix_1362) {
    // M = [2, 1, 1, 3, 4, 5]
    // det = 2*3 - 1*1 = 5
    // invM = [3/5, -1/5, -1/5, 2/5]
    // p = (10, 15)
    // xt = 10-4 = 6, yt = 15-5 = 10
    // x = (3/5)*6 + (-1/5)*10 = 18/5 - 10/5 = 8/5 = 1.6
    // y = (-1/5)*6 + (2/5)*10 = -6/5 + 20/5 = 14/5 = 2.8
    double M[6] = {2, 1, 1, 3, 4, 5};
    QPointF p(10.0, 15.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    EXPECT_DOUBLE_EQ(x, 1.6);
    EXPECT_DOUBLE_EQ(y, 2.8);
}

// Test negative values in matrix and point
TEST_F(XPDFReaderInvTransformTest_1362, NegativeValues_1362) {
    double M[6] = {-1, 0, 0, -1, 0, 0};
    QPointF p(5.0, 3.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    // det = (-1)*(-1) - 0*0 = 1
    // invM = [-1/1, 0, 0, -1/1] = [-1, 0, 0, -1]
    // x = -1*5 + 0*3 = -5
    // y = 0*5 + (-1)*3 = -3
    EXPECT_DOUBLE_EQ(x, -5.0);
    EXPECT_DOUBLE_EQ(y, -3.0);
}

// Test with fractional values
TEST_F(XPDFReaderInvTransformTest_1362, FractionalValues_1362) {
    double M[6] = {0.5, 0, 0, 0.5, 1.0, 2.0};
    QPointF p(3.0, 4.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    // det = 0.5*0.5 - 0 = 0.25
    // invM = [0.5/0.25, 0, 0, 0.5/0.25] = [2, 0, 0, 2]
    // xt = 3-1 = 2, yt = 4-2 = 2
    // x = 2*2 + 0*2 = 4
    // y = 0*2 + 2*2 = 4
    EXPECT_DOUBLE_EQ(x, 4.0);
    EXPECT_DOUBLE_EQ(y, 4.0);
}

// Test large values
TEST_F(XPDFReaderInvTransformTest_1362, LargeValues_1362) {
    double M[6] = {1000, 0, 0, 1000, 500, 500};
    QPointF p(1500.0, 2500.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    // det = 1000*1000 = 1000000
    // invM = [1000/1e6, 0, 0, 1000/1e6] = [0.001, 0, 0, 0.001]
    // xt = 1500-500 = 1000, yt = 2500-500 = 2000
    // x = 0.001*1000 = 1.0
    // y = 0.001*2000 = 2.0
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
}

// Test with very small determinant (near-singular but not singular)
TEST_F(XPDFReaderInvTransformTest_1362, SmallDeterminant_1362) {
    double M[6] = {1e-10, 0, 0, 1e-10, 0, 0};
    QPointF p(1e-10, 1e-10);
    double x, y;
    reader.invTransform(M, p, x, y);
    // det = 1e-20
    // invM = [1e-10/1e-20, 0, 0, 1e-10/1e-20] = [1e10, 0, 0, 1e10]
    // x = 1e10 * 1e-10 = 1.0
    // y = 1e10 * 1e-10 = 1.0
    EXPECT_NEAR(x, 1.0, 1e-6);
    EXPECT_NEAR(y, 1.0, 1e-6);
}

// Test point at translation offset should give origin
TEST_F(XPDFReaderInvTransformTest_1362, PointAtTranslationOffset_1362) {
    double M[6] = {3, 0, 0, 3, 7.0, 11.0};
    QPointF p(7.0, 11.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    // xt = 0, yt = 0 => x = 0, y = 0
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

// Test with shear matrix
TEST_F(XPDFReaderInvTransformTest_1362, ShearMatrix_1362) {
    // Shear: M = [1, 0, 2, 1, 0, 0]
    // det = 1*1 - 0*2 = 1
    // invM = [1, 0, -2, 1]
    // p = (5, 3)
    // x = 1*5 + (-2)*3 = 5 - 6 = -1
    // y = 0*5 + 1*3 = 3
    double M[6] = {1, 0, 2, 1, 0, 0};
    QPointF p(5.0, 3.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    EXPECT_DOUBLE_EQ(x, -1.0);
    EXPECT_DOUBLE_EQ(y, 3.0);
}

// Test negative translation
TEST_F(XPDFReaderInvTransformTest_1362, NegativeTranslation_1362) {
    double M[6] = {1, 0, 0, 1, -3.0, -7.0};
    QPointF p(2.0, 3.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    // xt = 2-(-3) = 5, yt = 3-(-7) = 10
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}

// Test negative point coordinates
TEST_F(XPDFReaderInvTransformTest_1362, NegativePointCoordinates_1362) {
    double M[6] = {1, 0, 0, 1, 0, 0};
    QPointF p(-4.0, -6.0);
    double x, y;
    reader.invTransform(M, p, x, y);
    EXPECT_DOUBLE_EQ(x, -4.0);
    EXPECT_DOUBLE_EQ(y, -6.0);
}
