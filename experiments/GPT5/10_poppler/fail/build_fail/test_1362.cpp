#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QPointF>

// Assuming the namespace and class are already declared as per the provided partial code
namespace Poppler {
    class XPDFReader {
    public:
        void invTransform(const double *M, const QPointF p, double &x, double &y) {
            const double det = M[0] * M[3] - M[1] * M[2];
            if (det == 0) {
                qWarning("Tried to invert singular matrix, something won't work");
                x = 0;
                y = 0;
                return;
            }
            const double invM[4] = { M[3] / det, -M[1] / det, -M[2] / det, M[0] / det };
            const double xt = p.x() - M[4];
            const double yt = p.y() - M[5];
            x = invM[0] * xt + invM[2] * yt;
            y = invM[1] * xt + invM[3] * yt;
        }
    };
}

// Test Fixture class
class XPDFReaderTest_1362 : public ::testing::Test {
protected:
    Poppler::XPDFReader reader;
};

// Test case for normal operation of invTransform
TEST_F(XPDFReaderTest_1362, InvTransformNormalOperation_1362) {
    double M[6] = {1, 0, 0, 1, 5, 5};  // Identity matrix with translation
    QPointF p(10, 10);  // Example point
    double x = 0, y = 0;

    reader.invTransform(M, p, x, y);

    EXPECT_DOUBLE_EQ(x, 5);  // Expected transformation result
    EXPECT_DOUBLE_EQ(y, 5);  // Expected transformation result
}

// Test case for handling singular matrix in invTransform (det == 0)
TEST_F(XPDFReaderTest_1362, InvTransformSingularMatrix_1362) {
    double M[6] = {0, 0, 0, 0, 0, 0};  // Singular matrix
    QPointF p(10, 10);
    double x = 0, y = 0;

    reader.invTransform(M, p, x, y);

    // Since matrix is singular, x and y should be 0, and a warning should be logged
    EXPECT_DOUBLE_EQ(x, 0);
    EXPECT_DOUBLE_EQ(y, 0);
}

// Test case for normal operation of transform
TEST_F(XPDFReaderTest_1362, TransformNormalOperation_1362) {
    double M[6] = {1, 0, 0, 1, 5, 5};  // Identity matrix with translation
    double x = 10, y = 10;
    QPointF res(0, 0);

    reader.transform(M, x, y, res);

    EXPECT_DOUBLE_EQ(res.x(), 15);  // Expected transformed result
    EXPECT_DOUBLE_EQ(res.y(), 15);  // Expected transformed result
}

// Test case for boundary values in transform
TEST_F(XPDFReaderTest_1362, TransformBoundaryValues_1362) {
    double M[6] = {1, 0, 0, 1, 0, 0};  // Identity matrix with no translation
    double x = 0, y = 0;
    QPointF res(0, 0);

    reader.transform(M, x, y, res);

    EXPECT_DOUBLE_EQ(res.x(), 0);  // Boundary value, should remain unchanged
    EXPECT_DOUBLE_EQ(res.y(), 0);  // Boundary value, should remain unchanged
}

// Test case for exceptional case with invalid input to transform (e.g., out of bounds)
TEST_F(XPDFReaderTest_1362, TransformInvalidInput_1362) {
    double M[6] = {1, 0, 0, 1, 5, 5};  // Identity matrix with translation
    double x = -10000, y = 10000;  // Extremely large input values
    QPointF res(0, 0);

    reader.transform(M, x, y, res);

    // Verify that the result is handled correctly, expected to still transform the point
    EXPECT_DOUBLE_EQ(res.x(), -9995);
    EXPECT_DOUBLE_EQ(res.y(), 10005);
}