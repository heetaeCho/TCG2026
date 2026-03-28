#include <gtest/gtest.h>
#include <QRectF>
#include <QPointF>
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"

// We need to test fromPdfRectangle. Since it depends on fillTransformationMTX
// and the class has complex dependencies, we test with default-constructed
// AnnotationPrivate where pdfPage is nullptr.

namespace Poppler {

class AnnotationPrivateTestHelper_1386 : public AnnotationPrivate {
public:
    AnnotationPrivateTestHelper_1386() : AnnotationPrivate() {
        // pdfPage is nullptr by default, so fillTransformationMTX
        // should produce an identity-like matrix
    }
};

class FromPdfRectangleTest_1386 : public ::testing::Test {
protected:
    AnnotationPrivateTestHelper_1386 annotPrivate;
};

// Test that a zero-area rectangle at origin returns a zero-area QRectF
TEST_F(FromPdfRectangleTest_1386, ZeroRectAtOrigin_1386) {
    PDFRectangle r(0.0, 0.0, 0.0, 0.0);
    QRectF result = annotPrivate.fromPdfRectangle(r);
    EXPECT_DOUBLE_EQ(result.width(), 0.0);
    EXPECT_DOUBLE_EQ(result.height(), 0.0);
}

// Test that a normal rectangle produces a valid QRectF with non-negative dimensions
TEST_F(FromPdfRectangleTest_1386, NormalRectangle_1386) {
    PDFRectangle r(0.0, 0.0, 1.0, 1.0);
    QRectF result = annotPrivate.fromPdfRectangle(r);
    EXPECT_GE(result.width(), 0.0);
    EXPECT_GE(result.height(), 0.0);
    // The result should be a valid rectangle
    EXPECT_TRUE(result.isValid() || result.isNull());
}

// Test that swapped coordinates (x1 > x2) still produce a normalized QRectF
TEST_F(FromPdfRectangleTest_1386, SwappedXCoordinates_1386) {
    PDFRectangle r(1.0, 0.0, 0.0, 1.0);
    QRectF result = annotPrivate.fromPdfRectangle(r);
    // After normalization, topLeft.x <= bottomRight.x
    EXPECT_LE(result.topLeft().x(), result.bottomRight().x());
}

// Test that swapped Y coordinates still produce a normalized QRectF
TEST_F(FromPdfRectangleTest_1386, SwappedYCoordinates_1386) {
    PDFRectangle r(0.0, 1.0, 1.0, 0.0);
    QRectF result = annotPrivate.fromPdfRectangle(r);
    EXPECT_LE(result.topLeft().y(), result.bottomRight().y());
}

// Test that both coordinates swapped still produce a normalized QRectF
TEST_F(FromPdfRectangleTest_1386, BothCoordinatesSwapped_1386) {
    PDFRectangle r(1.0, 1.0, 0.0, 0.0);
    QRectF result = annotPrivate.fromPdfRectangle(r);
    EXPECT_LE(result.topLeft().x(), result.bottomRight().x());
    EXPECT_LE(result.topLeft().y(), result.bottomRight().y());
}

// Test with negative coordinates
TEST_F(FromPdfRectangleTest_1386, NegativeCoordinates_1386) {
    PDFRectangle r(-2.0, -3.0, -1.0, -1.0);
    QRectF result = annotPrivate.fromPdfRectangle(r);
    EXPECT_LE(result.topLeft().x(), result.bottomRight().x());
    EXPECT_LE(result.topLeft().y(), result.bottomRight().y());
}

// Test with large coordinate values
TEST_F(FromPdfRectangleTest_1386, LargeCoordinates_1386) {
    PDFRectangle r(0.0, 0.0, 10000.0, 10000.0);
    QRectF result = annotPrivate.fromPdfRectangle(r);
    EXPECT_GE(result.width(), 0.0);
    EXPECT_GE(result.height(), 0.0);
}

// Test that identical normal and swapped rectangles produce same result
TEST_F(FromPdfRectangleTest_1386, NormalAndSwappedProduceSameResult_1386) {
    PDFRectangle r1(0.0, 0.0, 1.0, 1.0);
    PDFRectangle r2(1.0, 1.0, 0.0, 0.0);
    QRectF result1 = annotPrivate.fromPdfRectangle(r1);
    QRectF result2 = annotPrivate.fromPdfRectangle(r2);
    // Both should produce the same normalized rectangle
    EXPECT_DOUBLE_EQ(result1.left(), result2.left());
    EXPECT_DOUBLE_EQ(result1.top(), result2.top());
    EXPECT_DOUBLE_EQ(result1.right(), result2.right());
    EXPECT_DOUBLE_EQ(result1.bottom(), result2.bottom());
}

// Test with fractional coordinates
TEST_F(FromPdfRectangleTest_1386, FractionalCoordinates_1386) {
    PDFRectangle r(0.25, 0.5, 0.75, 1.0);
    QRectF result = annotPrivate.fromPdfRectangle(r);
    EXPECT_LE(result.topLeft().x(), result.bottomRight().x());
    EXPECT_LE(result.topLeft().y(), result.bottomRight().y());
}

// Test that result width and height are non-negative
TEST_F(FromPdfRectangleTest_1386, ResultDimensionsNonNegative_1386) {
    PDFRectangle r(5.0, 3.0, 2.0, 7.0);
    QRectF result = annotPrivate.fromPdfRectangle(r);
    EXPECT_GE(result.width(), 0.0);
    EXPECT_GE(result.height(), 0.0);
}

} // namespace Poppler
