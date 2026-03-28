#include <gtest/gtest.h>
#include <QPointF>
#include <cmath>

// Include the header under test
#include "poppler-annotation-helper.h"

using namespace Poppler;

class XPDFReaderTransformTest_1361 : public ::testing::Test {
protected:
    XPDFReader reader;
};

// Test identity transformation: M = [1, 0, 0, 1, 0, 0]
// res.x = 1*x + 0*y + 0, res.y = 0*x + 1*y + 0
TEST_F(XPDFReaderTransformTest_1361, IdentityTransform_1361) {
    double M[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    QPointF res;
    reader.transform(M, 3.0, 4.0, res);
    EXPECT_DOUBLE_EQ(res.x(), 3.0);
    EXPECT_DOUBLE_EQ(res.y(), 4.0);
}

// Test pure translation: M = [1, 0, 0, 1, tx, ty]
TEST_F(XPDFReaderTransformTest_1361, PureTranslation_1361) {
    double M[6] = {1.0, 0.0, 0.0, 1.0, 10.0, 20.0};
    QPointF res;
    reader.transform(M, 5.0, 7.0, res);
    EXPECT_DOUBLE_EQ(res.x(), 15.0);
    EXPECT_DOUBLE_EQ(res.y(), 27.0);
}

// Test scaling: M = [sx, 0, 0, sy, 0, 0]
TEST_F(XPDFReaderTransformTest_1361, ScalingTransform_1361) {
    double M[6] = {2.0, 0.0, 0.0, 3.0, 0.0, 0.0};
    QPointF res;
    reader.transform(M, 4.0, 5.0, res);
    EXPECT_DOUBLE_EQ(res.x(), 8.0);
    EXPECT_DOUBLE_EQ(res.y(), 15.0);
}

// Test with zero input coordinates
TEST_F(XPDFReaderTransformTest_1361, ZeroInputCoordinates_1361) {
    double M[6] = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
    QPointF res;
    reader.transform(M, 0.0, 0.0, res);
    EXPECT_DOUBLE_EQ(res.x(), 6.0); // M[4]
    EXPECT_DOUBLE_EQ(res.y(), 7.0); // M[5]
}

// Test general affine transformation
TEST_F(XPDFReaderTransformTest_1361, GeneralAffineTransform_1361) {
    // M = [a, b, c, d, e, f]
    // res.x = a*x + c*y + e
    // res.y = b*x + d*y + f
    double M[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    QPointF res;
    reader.transform(M, 7.0, 8.0, res);
    // res.x = 1*7 + 3*8 + 5 = 7 + 24 + 5 = 36
    // res.y = 2*7 + 4*8 + 6 = 14 + 32 + 6 = 52
    EXPECT_DOUBLE_EQ(res.x(), 36.0);
    EXPECT_DOUBLE_EQ(res.y(), 52.0);
}

// Test with negative coordinates
TEST_F(XPDFReaderTransformTest_1361, NegativeCoordinates_1361) {
    double M[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    QPointF res;
    reader.transform(M, -3.0, -4.0, res);
    EXPECT_DOUBLE_EQ(res.x(), -3.0);
    EXPECT_DOUBLE_EQ(res.y(), -4.0);
}

// Test with negative matrix entries
TEST_F(XPDFReaderTransformTest_1361, NegativeMatrixEntries_1361) {
    double M[6] = {-1.0, 0.0, 0.0, -1.0, 0.0, 0.0};
    QPointF res;
    reader.transform(M, 5.0, 10.0, res);
    EXPECT_DOUBLE_EQ(res.x(), -5.0);
    EXPECT_DOUBLE_EQ(res.y(), -10.0);
}

// Test rotation by 90 degrees: M = [cos90, sin90, -sin90, cos90, 0, 0] = [0, 1, -1, 0, 0, 0]
TEST_F(XPDFReaderTransformTest_1361, Rotation90Degrees_1361) {
    double M[6] = {0.0, 1.0, -1.0, 0.0, 0.0, 0.0};
    QPointF res;
    reader.transform(M, 1.0, 0.0, res);
    // res.x = 0*1 + (-1)*0 + 0 = 0
    // res.y = 1*1 + 0*0 + 0 = 1
    EXPECT_DOUBLE_EQ(res.x(), 0.0);
    EXPECT_DOUBLE_EQ(res.y(), 1.0);
}

// Test with fractional values
TEST_F(XPDFReaderTransformTest_1361, FractionalValues_1361) {
    double M[6] = {0.5, 0.25, 0.75, 1.5, 0.1, 0.2};
    QPointF res;
    reader.transform(M, 2.0, 4.0, res);
    // res.x = 0.5*2 + 0.75*4 + 0.1 = 1.0 + 3.0 + 0.1 = 4.1
    // res.y = 0.25*2 + 1.5*4 + 0.2 = 0.5 + 6.0 + 0.2 = 6.7
    EXPECT_DOUBLE_EQ(res.x(), 4.1);
    EXPECT_DOUBLE_EQ(res.y(), 6.7);
}

// Test with very large values
TEST_F(XPDFReaderTransformTest_1361, LargeValues_1361) {
    double M[6] = {1.0, 0.0, 0.0, 1.0, 1e10, 1e10};
    QPointF res;
    reader.transform(M, 1e10, 1e10, res);
    EXPECT_DOUBLE_EQ(res.x(), 2e10);
    EXPECT_DOUBLE_EQ(res.y(), 2e10);
}

// Test with very small values
TEST_F(XPDFReaderTransformTest_1361, SmallValues_1361) {
    double M[6] = {1e-10, 0.0, 0.0, 1e-10, 0.0, 0.0};
    QPointF res;
    reader.transform(M, 1.0, 1.0, res);
    EXPECT_DOUBLE_EQ(res.x(), 1e-10);
    EXPECT_DOUBLE_EQ(res.y(), 1e-10);
}

// Test all matrix elements contribute
TEST_F(XPDFReaderTransformTest_1361, AllMatrixElementsContribute_1361) {
    double M[6] = {2.0, 3.0, 5.0, 7.0, 11.0, 13.0};
    QPointF res;
    reader.transform(M, 1.0, 1.0, res);
    // res.x = 2*1 + 5*1 + 11 = 18
    // res.y = 3*1 + 7*1 + 13 = 23
    EXPECT_DOUBLE_EQ(res.x(), 18.0);
    EXPECT_DOUBLE_EQ(res.y(), 23.0);
}

// Test that result overwrites previous QPointF value
TEST_F(XPDFReaderTransformTest_1361, ResultOverwritesPreviousValue_1361) {
    double M[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    QPointF res(999.0, 999.0);
    reader.transform(M, 1.0, 2.0, res);
    EXPECT_DOUBLE_EQ(res.x(), 1.0);
    EXPECT_DOUBLE_EQ(res.y(), 2.0);
}

// Test zero matrix
TEST_F(XPDFReaderTransformTest_1361, ZeroMatrix_1361) {
    double M[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    QPointF res;
    reader.transform(M, 100.0, 200.0, res);
    EXPECT_DOUBLE_EQ(res.x(), 0.0);
    EXPECT_DOUBLE_EQ(res.y(), 0.0);
}

// Test that x only affects M[0] and M[1] contributions, y only affects M[2] and M[3]
TEST_F(XPDFReaderTransformTest_1361, XOnlyContribution_1361) {
    double M[6] = {2.0, 3.0, 0.0, 0.0, 0.0, 0.0};
    QPointF res;
    reader.transform(M, 5.0, 0.0, res);
    EXPECT_DOUBLE_EQ(res.x(), 10.0);
    EXPECT_DOUBLE_EQ(res.y(), 15.0);
}

TEST_F(XPDFReaderTransformTest_1361, YOnlyContribution_1361) {
    double M[6] = {0.0, 0.0, 4.0, 6.0, 0.0, 0.0};
    QPointF res;
    reader.transform(M, 0.0, 3.0, res);
    EXPECT_DOUBLE_EQ(res.x(), 12.0);
    EXPECT_DOUBLE_EQ(res.y(), 18.0);
}
