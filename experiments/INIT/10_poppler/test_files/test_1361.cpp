#include <gtest/gtest.h>
#include <QPointF>
#include <stdexcept>
#include <cmath>

// Assuming the header file is already included: ./TestProjects/poppler/qt5/src/poppler-annotation-helper.h

namespace Poppler {
    class XPDFReaderTest_1361 : public ::testing::Test {
    protected:
        // Initialize the class instance or any needed setup here if necessary.
        XPDFReaderTest_1361() : reader() {}

        XPDFReader reader;  // Instance of XPDFReader to be used in tests
    };

    // Normal operation test for transform method (TEST_ID 1361)
    TEST_F(XPDFReaderTest_1361, Transform_NormalOperation_1361) {
        double M[6] = {1.0, 0.0, 0.0, 1.0, 10.0, 20.0};  // Identity matrix with a translation of (10, 20)
        double x = 5.0, y = 5.0;
        QPointF res(0, 0);
        
        reader.transform(M, x, y, res);
        
        // Expected result: point (5, 5) should be transformed to (5+10, 5+20) = (15, 25)
        EXPECT_DOUBLE_EQ(res.x(), 15.0);
        EXPECT_DOUBLE_EQ(res.y(), 25.0);
    }

    // Boundary case for transform method with point at origin (0, 0) (TEST_ID 1362)
    TEST_F(XPDFReaderTest_1361, Transform_OriginPoint_1362) {
        double M[6] = {1.0, 0.0, 0.0, 1.0, 10.0, 20.0};  // Identity matrix with translation
        double x = 0.0, y = 0.0;
        QPointF res(0, 0);
        
        reader.transform(M, x, y, res);
        
        // Expected result: origin point (0, 0) should be transformed to (10, 20)
        EXPECT_DOUBLE_EQ(res.x(), 10.0);
        EXPECT_DOUBLE_EQ(res.y(), 20.0);
    }

    // Exceptional case for transform method with invalid matrix (TEST_ID 1363)
    TEST_F(XPDFReaderTest_1361, Transform_InvalidMatrix_1363) {
        double M[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};  // Invalid matrix (all zeros)
        double x = 5.0, y = 5.0;
        QPointF res(0, 0);
        
        // Check for invalid transformation, expected to result in a point (0, 0)
        reader.transform(M, x, y, res);
        
        EXPECT_DOUBLE_EQ(res.x(), 0.0);
        EXPECT_DOUBLE_EQ(res.y(), 0.0);
    }

    // Normal operation test for invTransform method (TEST_ID 1364)
    TEST_F(XPDFReaderTest_1361, InvTransform_NormalOperation_1364) {
        double M[6] = {1.0, 0.0, 0.0, 1.0, 10.0, 20.0};  // Identity matrix with translation
        QPointF p(15.0, 25.0);
        double x = 0.0, y = 0.0;
        
        reader.invTransform(M, p, x, y);
        
        // Expected result: point (15, 25) should be transformed back to (5, 5) using inverse of translation
        EXPECT_DOUBLE_EQ(x, 5.0);
        EXPECT_DOUBLE_EQ(y, 5.0);
    }

    // Boundary case for invTransform method with point at origin (TEST_ID 1365)
    TEST_F(XPDFReaderTest_1361, InvTransform_OriginPoint_1365) {
        double M[6] = {1.0, 0.0, 0.0, 1.0, 10.0, 20.0};  // Identity matrix with translation
        QPointF p(10.0, 20.0);
        double x = 0.0, y = 0.0;
        
        reader.invTransform(M, p, x, y);
        
        // Expected result: point (10, 20) should be transformed back to origin (0, 0)
        EXPECT_DOUBLE_EQ(x, 0.0);
        EXPECT_DOUBLE_EQ(y, 0.0);
    }

    // Exceptional case for invTransform method with invalid matrix (TEST_ID 1366)
    TEST_F(XPDFReaderTest_1361, InvTransform_InvalidMatrix_1366) {
        double M[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};  // Invalid matrix (all zeros)
        QPointF p(15.0, 25.0);
        double x = 0.0, y = 0.0;
        
        // Check for invalid inverse transformation, expected to result in undefined behavior or default point (0, 0)
        reader.invTransform(M, p, x, y);
        
        EXPECT_DOUBLE_EQ(x, 0.0);
        EXPECT_DOUBLE_EQ(y, 0.0);
    }
}