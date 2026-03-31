#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QRectF>

// Include necessary poppler headers
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"

// We need access to PDFRectangle and Page from poppler core
#include "Page.h"
#include "PDFDoc.h"

namespace {

using namespace Poppler;

class AnnotationPrivateTest_1388 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test boundaryToPdfRectangle with null pdfPage
// When pdfPage is nullptr (default), the conversion should still produce some result
TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangleNullPage_1388) {
    AnnotationPrivate annotPrivate;
    // pdfPage defaults to nullptr
    QRectF boundary(0.0, 0.0, 1.0, 1.0);
    int flags = 0;
    
    // Should not crash with null page - behavior depends on implementation
    // We just verify it doesn't segfault
    PDFRectangle result = annotPrivate.boundaryToPdfRectangle(boundary, flags);
    // With null page, we expect some default transformation
    SUCCEED();
}

// Test with a zero-size boundary rectangle
TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangleZeroSize_1388) {
    AnnotationPrivate annotPrivate;
    QRectF boundary(0.0, 0.0, 0.0, 0.0);
    int flags = 0;
    
    PDFRectangle result = annotPrivate.boundaryToPdfRectangle(boundary, flags);
    // For a zero-size rect at origin, x1 should equal x2 and y1 should equal y2
    EXPECT_DOUBLE_EQ(result.x1, result.x2);
    EXPECT_DOUBLE_EQ(result.y1, result.y2);
}

// Test with a unit boundary rectangle at origin
TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangleUnitRect_1388) {
    AnnotationPrivate annotPrivate;
    QRectF boundary(0.0, 0.0, 1.0, 1.0);
    int flags = 0;
    
    PDFRectangle result = annotPrivate.boundaryToPdfRectangle(boundary, flags);
    // x1 should be <= x2 for a valid PDF rectangle
    EXPECT_LE(result.x1, result.x2);
}

// Test with different flags values
TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangleWithFlags_1388) {
    AnnotationPrivate annotPrivate;
    QRectF boundary(0.1, 0.2, 0.5, 0.3);
    
    PDFRectangle result0 = annotPrivate.boundaryToPdfRectangle(boundary, 0);
    PDFRectangle result1 = annotPrivate.boundaryToPdfRectangle(boundary, 1);
    
    // Different flags may produce different results
    // We just verify both calls complete without error
    SUCCEED();
}

// Test with normalized coordinates (typical annotation boundaries are 0-1 range)
TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangleNormalizedCoords_1388) {
    AnnotationPrivate annotPrivate;
    QRectF boundary(0.25, 0.25, 0.5, 0.5);
    int flags = 0;
    
    PDFRectangle result = annotPrivate.boundaryToPdfRectangle(boundary, flags);
    // Result should have valid coordinates
    EXPECT_TRUE(std::isfinite(result.x1));
    EXPECT_TRUE(std::isfinite(result.y1));
    EXPECT_TRUE(std::isfinite(result.x2));
    EXPECT_TRUE(std::isfinite(result.y2));
}

// Test with negative position boundary
TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangleNegativePosition_1388) {
    AnnotationPrivate annotPrivate;
    QRectF boundary(-0.5, -0.5, 1.0, 1.0);
    int flags = 0;
    
    PDFRectangle result = annotPrivate.boundaryToPdfRectangle(boundary, flags);
    EXPECT_TRUE(std::isfinite(result.x1));
    EXPECT_TRUE(std::isfinite(result.y1));
    EXPECT_TRUE(std::isfinite(result.x2));
    EXPECT_TRUE(std::isfinite(result.y2));
}

// Test that two identical inputs produce identical outputs (determinism)
TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangleDeterministic_1388) {
    AnnotationPrivate annotPrivate;
    QRectF boundary(0.1, 0.2, 0.3, 0.4);
    int flags = 0;
    
    PDFRectangle result1 = annotPrivate.boundaryToPdfRectangle(boundary, flags);
    PDFRectangle result2 = annotPrivate.boundaryToPdfRectangle(boundary, flags);
    
    EXPECT_DOUBLE_EQ(result1.x1, result2.x1);
    EXPECT_DOUBLE_EQ(result1.y1, result2.y1);
    EXPECT_DOUBLE_EQ(result1.x2, result2.x2);
    EXPECT_DOUBLE_EQ(result1.y2, result2.y2);
}

// Test default construction state
TEST_F(AnnotationPrivateTest_1388, DefaultConstruction_1388) {
    AnnotationPrivate annotPrivate;
    EXPECT_EQ(annotPrivate.pdfPage, nullptr);
    EXPECT_EQ(annotPrivate.parentDoc, nullptr);
    EXPECT_EQ(annotPrivate.pdfAnnot, nullptr);
}

// Test with a very small boundary rectangle
TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangleVerySmall_1388) {
    AnnotationPrivate annotPrivate;
    QRectF boundary(0.5, 0.5, 0.0001, 0.0001);
    int flags = 0;
    
    PDFRectangle result = annotPrivate.boundaryToPdfRectangle(boundary, flags);
    EXPECT_TRUE(std::isfinite(result.x1));
    EXPECT_TRUE(std::isfinite(result.y1));
    EXPECT_TRUE(std::isfinite(result.x2));
    EXPECT_TRUE(std::isfinite(result.y2));
}

// Test with full page boundary (0,0 to 1,1)
TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangleFullPage_1388) {
    AnnotationPrivate annotPrivate;
    QRectF boundary(0.0, 0.0, 1.0, 1.0);
    int flags = 0;
    
    PDFRectangle result = annotPrivate.boundaryToPdfRectangle(boundary, flags);
    // Width of result should be non-negative
    EXPECT_LE(result.x1, result.x2);
}

} // namespace
