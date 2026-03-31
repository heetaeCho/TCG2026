#include <gtest/gtest.h>
#include <memory>
#include <cmath>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "PDFRectangle.h"

class PageGetMediaHeight_707 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that PDFRectangle default constructor gives zero dimensions
TEST_F(PageGetMediaHeight_707, PDFRectangleDefaultHeight_707) {
    PDFRectangle rect;
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test PDFRectangle with known values computes correct height
TEST_F(PageGetMediaHeight_707, PDFRectangleKnownHeight_707) {
    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test PDFRectangle with non-zero y1
TEST_F(PageGetMediaHeight_707, PDFRectangleNonZeroY1_707) {
    PDFRectangle rect(0.0, 100.0, 612.0, 892.0);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test PDFRectangle with negative coordinates
TEST_F(PageGetMediaHeight_707, PDFRectangleNegativeCoords_707) {
    PDFRectangle rect(0.0, -100.0, 612.0, 692.0);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test PDFRectangle with y2 < y1 (inverted box)
TEST_F(PageGetMediaHeight_707, PDFRectangleInvertedY_707) {
    PDFRectangle rect(0.0, 792.0, 612.0, 0.0);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, -792.0);
}

// Test PDFRectangle with equal y1 and y2 (zero height)
TEST_F(PageGetMediaHeight_707, PDFRectangleZeroHeight_707) {
    PDFRectangle rect(0.0, 500.0, 612.0, 500.0);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test PDFRectangle with fractional values
TEST_F(PageGetMediaHeight_707, PDFRectangleFractionalHeight_707) {
    PDFRectangle rect(0.0, 0.5, 612.0, 792.5);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test PDFRectangle with very large values
TEST_F(PageGetMediaHeight_707, PDFRectangleLargeValues_707) {
    PDFRectangle rect(0.0, 0.0, 100000.0, 100000.0);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 100000.0);
}

// Test PDFRectangle with very small height
TEST_F(PageGetMediaHeight_707, PDFRectangleVerySmallHeight_707) {
    PDFRectangle rect(0.0, 0.0, 612.0, 0.001);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 0.001);
}

// Test standard US Letter page dimensions
TEST_F(PageGetMediaHeight_707, StandardLetterPageHeight_707) {
    // US Letter: 8.5 x 11 inches = 612 x 792 points
    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test standard A4 page dimensions
TEST_F(PageGetMediaHeight_707, StandardA4PageHeight_707) {
    // A4: 595.276 x 841.89 points
    PDFRectangle rect(0.0, 0.0, 595.276, 841.89);
    double height = rect.y2 - rect.y1;
    EXPECT_NEAR(height, 841.89, 0.001);
}

// Test both y coordinates negative
TEST_F(PageGetMediaHeight_707, PDFRectangleBothNegativeY_707) {
    PDFRectangle rect(0.0, -200.0, 612.0, -100.0);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 100.0);
}
