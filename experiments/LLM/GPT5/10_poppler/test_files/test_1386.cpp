#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QRectF>
#include <QPointF>
#include "PDFRectangle.h"
#include "poppler-annotation-private.h"

// Mock class for external dependencies (e.g., Annot, Page, DocumentData)
class MockAnnot : public Poppler::Annot {
public:
    MOCK_METHOD(void, someMethod, (), (override));  // Example mock method
};

class AnnotationPrivateTest_1386 : public ::testing::Test {
protected:
    Poppler::AnnotationPrivate annotationPrivate;
};

// Test normal operation of fromPdfRectangle function
TEST_F(AnnotationPrivateTest_1386, FromPdfRectangleNormal_1386) {
    PDFRectangle pdfRect(0.0, 0.0, 10.0, 20.0);
    QRectF result = annotationPrivate.fromPdfRectangle(pdfRect);

    EXPECT_DOUBLE_EQ(result.topLeft().x(), 0.0);
    EXPECT_DOUBLE_EQ(result.topLeft().y(), 0.0);
    EXPECT_DOUBLE_EQ(result.bottomRight().x(), 10.0);
    EXPECT_DOUBLE_EQ(result.bottomRight().y(), 20.0);
}

// Test boundary conditions with a PDFRectangle that has zero width and height
TEST_F(AnnotationPrivateTest_1386, FromPdfRectangleZeroDimensions_1386) {
    PDFRectangle pdfRect(0.0, 0.0, 0.0, 0.0);
    QRectF result = annotationPrivate.fromPdfRectangle(pdfRect);

    EXPECT_DOUBLE_EQ(result.topLeft().x(), 0.0);
    EXPECT_DOUBLE_EQ(result.topLeft().y(), 0.0);
    EXPECT_DOUBLE_EQ(result.bottomRight().x(), 0.0);
    EXPECT_DOUBLE_EQ(result.bottomRight().y(), 0.0);
}

// Test boundary conditions with a reversed rectangle (x1 > x2, y1 > y2)
TEST_F(AnnotationPrivateTest_1386, FromPdfRectangleReversedCoordinates_1386) {
    PDFRectangle pdfRect(10.0, 20.0, 0.0, 0.0);
    QRectF result = annotationPrivate.fromPdfRectangle(pdfRect);

    EXPECT_DOUBLE_EQ(result.topLeft().x(), 0.0);
    EXPECT_DOUBLE_EQ(result.topLeft().y(), 0.0);
    EXPECT_DOUBLE_EQ(result.bottomRight().x(), 10.0);
    EXPECT_DOUBLE_EQ(result.bottomRight().y(), 20.0);
}

// Test exceptional case with invalid PDFRectangle
TEST_F(AnnotationPrivateTest_1386, FromPdfRectangleInvalid_1386) {
    // Mock an invalid PDFRectangle (could be a result of erroneous transformation)
    PDFRectangle invalidRect;
    invalidRect.x1 = -1;  // Invalid coordinate, out of expected range

    QRectF result = annotationPrivate.fromPdfRectangle(invalidRect);

    EXPECT_FALSE(result.isValid());  // Expect an invalid QRectF as the result
}

// Test external interaction: tieToNativeAnnot
TEST_F(AnnotationPrivateTest_1386, TieToNativeAnnot_1386) {
    MockAnnot mockAnnot;
    ::Page *mockPage = nullptr;
    Poppler::DocumentData *mockDoc = nullptr;

    // Mock the interaction and verify behavior
    EXPECT_CALL(mockAnnot, someMethod()).Times(1);
    annotationPrivate.tieToNativeAnnot(std::make_shared<MockAnnot>(), mockPage, mockDoc);
}

// Test boundary condition with a large PDFRectangle
TEST_F(AnnotationPrivateTest_1386, FromPdfRectangleLargeValues_1386) {
    PDFRectangle pdfRect(1e6, 1e6, 1e7, 1e7);
    QRectF result = annotationPrivate.fromPdfRectangle(pdfRect);

    EXPECT_DOUBLE_EQ(result.topLeft().x(), 1e6);
    EXPECT_DOUBLE_EQ(result.topLeft().y(), 1e6);
    EXPECT_DOUBLE_EQ(result.bottomRight().x(), 1e7);
    EXPECT_DOUBLE_EQ(result.bottomRight().y(), 1e7);
}