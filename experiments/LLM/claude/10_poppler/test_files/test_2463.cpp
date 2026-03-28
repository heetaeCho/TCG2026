#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include necessary poppler headers
#include "poppler-page.h"
#include "poppler-private.h"
#include "PDFRectangle.h"

// If poppler_rectangle_new_from_pdf_rectangle is not declared in a public header,
// declare it externally
extern "C" {
#include <poppler.h>
}

// Forward declare if needed
PopplerRectangle *poppler_rectangle_new_from_pdf_rectangle(const PDFRectangle *rect);

class PopplerRectangleNewFromPdfRectangleTest_2463 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated rectangles
    }
};

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, BasicCoordinateCopy_2463) {
    PDFRectangle pdfRect(1.0, 2.0, 3.0, 4.0);
    PopplerRectangle *result = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 1.0);
    EXPECT_DOUBLE_EQ(result->y1, 2.0);
    EXPECT_DOUBLE_EQ(result->x2, 3.0);
    EXPECT_DOUBLE_EQ(result->y2, 4.0);
    
    poppler_rectangle_free(result);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, ZeroCoordinates_2463) {
    PDFRectangle pdfRect(0.0, 0.0, 0.0, 0.0);
    PopplerRectangle *result = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 0.0);
    EXPECT_DOUBLE_EQ(result->y1, 0.0);
    EXPECT_DOUBLE_EQ(result->x2, 0.0);
    EXPECT_DOUBLE_EQ(result->y2, 0.0);
    
    poppler_rectangle_free(result);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, NegativeCoordinates_2463) {
    PDFRectangle pdfRect(-10.5, -20.3, -1.0, -0.5);
    PopplerRectangle *result = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, -10.5);
    EXPECT_DOUBLE_EQ(result->y1, -20.3);
    EXPECT_DOUBLE_EQ(result->x2, -1.0);
    EXPECT_DOUBLE_EQ(result->y2, -0.5);
    
    poppler_rectangle_free(result);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, LargeCoordinates_2463) {
    PDFRectangle pdfRect(1e10, 1e10, 1e15, 1e15);
    PopplerRectangle *result = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 1e10);
    EXPECT_DOUBLE_EQ(result->y1, 1e10);
    EXPECT_DOUBLE_EQ(result->x2, 1e15);
    EXPECT_DOUBLE_EQ(result->y2, 1e15);
    
    poppler_rectangle_free(result);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, FractionalCoordinates_2463) {
    PDFRectangle pdfRect(0.123456789, 0.987654321, 100.111222333, 200.444555666);
    PopplerRectangle *result = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 0.123456789);
    EXPECT_DOUBLE_EQ(result->y1, 0.987654321);
    EXPECT_DOUBLE_EQ(result->x2, 100.111222333);
    EXPECT_DOUBLE_EQ(result->y2, 200.444555666);
    
    poppler_rectangle_free(result);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, DefaultConstructedPdfRect_2463) {
    PDFRectangle pdfRect;
    PopplerRectangle *result = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 0.0);
    EXPECT_DOUBLE_EQ(result->y1, 0.0);
    EXPECT_DOUBLE_EQ(result->x2, 0.0);
    EXPECT_DOUBLE_EQ(result->y2, 0.0);
    
    poppler_rectangle_free(result);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, InvertedCoordinates_2463) {
    // x2 < x1 and y2 < y1 (inverted rectangle)
    PDFRectangle pdfRect(100.0, 200.0, 10.0, 20.0);
    PopplerRectangle *result = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 100.0);
    EXPECT_DOUBLE_EQ(result->y1, 200.0);
    EXPECT_DOUBLE_EQ(result->x2, 10.0);
    EXPECT_DOUBLE_EQ(result->y2, 20.0);
    
    poppler_rectangle_free(result);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, MixedSignCoordinates_2463) {
    PDFRectangle pdfRect(-50.0, -30.0, 50.0, 30.0);
    PopplerRectangle *result = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, -50.0);
    EXPECT_DOUBLE_EQ(result->y1, -30.0);
    EXPECT_DOUBLE_EQ(result->x2, 50.0);
    EXPECT_DOUBLE_EQ(result->y2, 30.0);
    
    poppler_rectangle_free(result);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, VerySmallCoordinates_2463) {
    double tiny = std::numeric_limits<double>::min();
    PDFRectangle pdfRect(tiny, tiny, tiny * 2, tiny * 2);
    PopplerRectangle *result = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, tiny);
    EXPECT_DOUBLE_EQ(result->y1, tiny);
    EXPECT_DOUBLE_EQ(result->x2, tiny * 2);
    EXPECT_DOUBLE_EQ(result->y2, tiny * 2);
    
    poppler_rectangle_free(result);
}

TEST_F(PopplerRectangleNewFromPdfRectangleTest_2463, ReturnsNewAllocation_2463) {
    PDFRectangle pdfRect(1.0, 2.0, 3.0, 4.0);
    PopplerRectangle *result1 = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    PopplerRectangle *result2 = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);
    
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1, result2);
    
    EXPECT_DOUBLE_EQ(result1->x1, result2->x1);
    EXPECT_DOUBLE_EQ(result1->y1, result2->y1);
    EXPECT_DOUBLE_EQ(result1->x2, result2->x2);
    EXPECT_DOUBLE_EQ(result1->y2, result2->y2);
    
    poppler_rectangle_free(result1);
    poppler_rectangle_free(result2);
}
