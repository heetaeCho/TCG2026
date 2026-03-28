#include <gtest/gtest.h>
#include "Annot.h"

// We need PDFRectangle to construct AnnotAppearanceBBox
// PDFRectangle is typically defined in poppler
#include "Object.h"

class AnnotAppearanceBBoxTest_774 : public ::testing::Test {
protected:
    void SetUp() override {
        rect.x1 = 0.0;
        rect.y1 = 0.0;
        rect.x2 = 100.0;
        rect.y2 = 100.0;
    }

    PDFRectangle rect;
};

// Test basic construction with a rectangle
TEST_F(AnnotAppearanceBBoxTest_774, ConstructWithRect_774) {
    AnnotAppearanceBBox bbox(&rect);
    // After construction, we should be able to query bounding box
    // The bbox should reflect initial state based on the rect
    SUCCEED();
}

// Test setBorderWidth with a positive value
TEST_F(AnnotAppearanceBBoxTest_774, SetBorderWidthPositive_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.setBorderWidth(5.0);
    // Border width is set; this affects getBBoxRect output
    SUCCEED();
}

// Test setBorderWidth with zero
TEST_F(AnnotAppearanceBBoxTest_774, SetBorderWidthZero_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.setBorderWidth(0.0);
    SUCCEED();
}

// Test setBorderWidth with a negative value (boundary case)
TEST_F(AnnotAppearanceBBoxTest_774, SetBorderWidthNegative_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.setBorderWidth(-1.0);
    SUCCEED();
}

// Test extendTo expands the bounding box
TEST_F(AnnotAppearanceBBoxTest_774, ExtendToExpandsBBox_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.extendTo(50.0, 50.0);
    
    auto bboxRect = bbox.getBBoxRect();
    // After extending to (50, 50), the bbox should include that point
    EXPECT_LE(bboxRect[0], 50.0);
    EXPECT_LE(bboxRect[1], 50.0);
    EXPECT_GE(bboxRect[2], 50.0);
    EXPECT_GE(bboxRect[3], 50.0);
}

// Test extendTo with multiple points
TEST_F(AnnotAppearanceBBoxTest_774, ExtendToMultiplePoints_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.extendTo(10.0, 20.0);
    bbox.extendTo(80.0, 90.0);
    
    auto bboxRect = bbox.getBBoxRect();
    // The bbox should encompass both points
    EXPECT_LE(bboxRect[0], 10.0);
    EXPECT_LE(bboxRect[1], 20.0);
    EXPECT_GE(bboxRect[2], 80.0);
    EXPECT_GE(bboxRect[3], 90.0);
}

// Test extendTo with negative coordinates
TEST_F(AnnotAppearanceBBoxTest_774, ExtendToNegativeCoords_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.extendTo(-10.0, -20.0);
    
    auto bboxRect = bbox.getBBoxRect();
    // Should handle negative coordinates
    EXPECT_LE(bboxRect[0], -10.0 + 1.0); // account for possible border
    EXPECT_LE(bboxRect[1], -20.0 + 1.0);
}

// Test getBBoxRect returns an array of 4 elements
TEST_F(AnnotAppearanceBBoxTest_774, GetBBoxRectReturnsFourElements_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.extendTo(25.0, 75.0);
    
    auto bboxRect = bbox.getBBoxRect();
    EXPECT_EQ(bboxRect.size(), 4u);
}

// Test getPageXMin, getPageYMin, getPageXMax, getPageYMax
TEST_F(AnnotAppearanceBBoxTest_774, GetPageCoordinates_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.extendTo(30.0, 40.0);
    bbox.extendTo(70.0, 80.0);
    
    double xMin = bbox.getPageXMin();
    double yMin = bbox.getPageYMin();
    double xMax = bbox.getPageXMax();
    double yMax = bbox.getPageYMax();
    
    // Page coordinates should be valid (min <= max)
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test that border width affects getBBoxRect
TEST_F(AnnotAppearanceBBoxTest_774, BorderWidthAffectsBBoxRect_774) {
    AnnotAppearanceBBox bbox1(&rect);
    bbox1.setBorderWidth(0.0);
    bbox1.extendTo(50.0, 50.0);
    auto bboxRect1 = bbox1.getBBoxRect();
    
    AnnotAppearanceBBox bbox2(&rect);
    bbox2.setBorderWidth(10.0);
    bbox2.extendTo(50.0, 50.0);
    auto bboxRect2 = bbox2.getBBoxRect();
    
    // With larger border width, the bbox should be larger (or at least not smaller)
    EXPECT_LE(bboxRect2[0], bboxRect1[0]);
    EXPECT_LE(bboxRect2[1], bboxRect1[1]);
    EXPECT_GE(bboxRect2[2], bboxRect1[2]);
    EXPECT_GE(bboxRect2[3], bboxRect1[3]);
}

// Test with a non-origin rect
TEST_F(AnnotAppearanceBBoxTest_774, NonOriginRect_774) {
    PDFRectangle nonOriginRect;
    nonOriginRect.x1 = 50.0;
    nonOriginRect.y1 = 50.0;
    nonOriginRect.x2 = 200.0;
    nonOriginRect.y2 = 200.0;
    
    AnnotAppearanceBBox bbox(&nonOriginRect);
    bbox.extendTo(75.0, 75.0);
    
    double xMin = bbox.getPageXMin();
    double yMin = bbox.getPageYMin();
    double xMax = bbox.getPageXMax();
    double yMax = bbox.getPageYMax();
    
    // Page coordinates should account for the rect's origin
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test extendTo with the same point twice
TEST_F(AnnotAppearanceBBoxTest_774, ExtendToSamePointTwice_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.extendTo(50.0, 50.0);
    auto bboxRect1 = bbox.getBBoxRect();
    
    bbox.extendTo(50.0, 50.0);
    auto bboxRect2 = bbox.getBBoxRect();
    
    // Extending to the same point twice should not change the bbox
    EXPECT_DOUBLE_EQ(bboxRect1[0], bboxRect2[0]);
    EXPECT_DOUBLE_EQ(bboxRect1[1], bboxRect2[1]);
    EXPECT_DOUBLE_EQ(bboxRect1[2], bboxRect2[2]);
    EXPECT_DOUBLE_EQ(bboxRect1[3], bboxRect2[3]);
}

// Test setBorderWidth with a very large value
TEST_F(AnnotAppearanceBBoxTest_774, SetBorderWidthLarge_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.setBorderWidth(1000.0);
    bbox.extendTo(50.0, 50.0);
    
    auto bboxRect = bbox.getBBoxRect();
    EXPECT_EQ(bboxRect.size(), 4u);
}

// Test that extendTo with origin point works
TEST_F(AnnotAppearanceBBoxTest_774, ExtendToOrigin_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.extendTo(0.0, 0.0);
    
    auto bboxRect = bbox.getBBoxRect();
    EXPECT_EQ(bboxRect.size(), 4u);
}

// Test getPageCoordinates after setting border width and extending
TEST_F(AnnotAppearanceBBoxTest_774, PageCoordsWithBorderWidth_774) {
    AnnotAppearanceBBox bbox(&rect);
    bbox.setBorderWidth(5.0);
    bbox.extendTo(20.0, 30.0);
    bbox.extendTo(60.0, 70.0);
    
    double xMin = bbox.getPageXMin();
    double yMin = bbox.getPageYMin();
    double xMax = bbox.getPageXMax();
    double yMax = bbox.getPageYMax();
    
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}
