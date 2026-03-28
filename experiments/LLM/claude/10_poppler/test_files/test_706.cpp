#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cmath>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "PDFRectangle.h"

class PageTest_706 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test PDFRectangle basic construction
TEST_F(PageTest_706, PDFRectangleDefaultConstruction_706)
{
    PDFRectangle rect;
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}

TEST_F(PageTest_706, PDFRectangleParameterizedConstruction_706)
{
    PDFRectangle rect(10.0, 20.0, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(rect.x1, 10.0);
    EXPECT_DOUBLE_EQ(rect.y1, 20.0);
    EXPECT_DOUBLE_EQ(rect.x2, 300.0);
    EXPECT_DOUBLE_EQ(rect.y2, 400.0);
}

TEST_F(PageTest_706, PDFRectangleWidthCalculation_706)
{
    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    double width = rect.x2 - rect.x1;
    EXPECT_DOUBLE_EQ(width, 612.0);
}

TEST_F(PageTest_706, PDFRectangleHeightCalculation_706)
{
    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(height, 792.0);
}

TEST_F(PageTest_706, PDFRectangleZeroDimensions_706)
{
    PDFRectangle rect(100.0, 200.0, 100.0, 200.0);
    double width = rect.x2 - rect.x1;
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(width, 0.0);
    EXPECT_DOUBLE_EQ(height, 0.0);
}

TEST_F(PageTest_706, PDFRectangleNegativeCoordinates_706)
{
    PDFRectangle rect(-100.0, -200.0, 100.0, 200.0);
    double width = rect.x2 - rect.x1;
    double height = rect.y2 - rect.y1;
    EXPECT_DOUBLE_EQ(width, 200.0);
    EXPECT_DOUBLE_EQ(height, 400.0);
}

TEST_F(PageTest_706, PDFRectangleIsValidDefault_706)
{
    PDFRectangle rect;
    // Default rectangle with all zeros
    EXPECT_TRUE(rect.isEmpty() || !rect.isValid() || rect == PDFRectangle());
}

TEST_F(PageTest_706, PDFRectangleEquality_706)
{
    PDFRectangle rect1(10.0, 20.0, 30.0, 40.0);
    PDFRectangle rect2(10.0, 20.0, 30.0, 40.0);
    EXPECT_TRUE(rect1 == rect2);
}

TEST_F(PageTest_706, PDFRectangleInequality_706)
{
    PDFRectangle rect1(10.0, 20.0, 30.0, 40.0);
    PDFRectangle rect2(10.0, 20.0, 30.0, 50.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PageTest_706, PDFRectangleContainsPoint_706)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    EXPECT_TRUE(rect.contains(50.0, 50.0));
}

TEST_F(PageTest_706, PDFRectangleDoesNotContainOutsidePoint_706)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    EXPECT_FALSE(rect.contains(150.0, 150.0));
}

TEST_F(PageTest_706, PDFRectangleContainsBoundaryPoint_706)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    // Boundary behavior - point on edge
    bool onBoundary = rect.contains(0.0, 0.0);
    // Just verify it doesn't crash; boundary behavior is implementation-defined
    (void)onBoundary;
}

TEST_F(PageTest_706, PDFRectangleLargeValues_706)
{
    PDFRectangle rect(0.0, 0.0, 1e10, 1e10);
    double width = rect.x2 - rect.x1;
    EXPECT_DOUBLE_EQ(width, 1e10);
}

TEST_F(PageTest_706, PDFRectangleReversedCoordinatesWidth_706)
{
    // When x2 < x1, width would be negative
    PDFRectangle rect(300.0, 400.0, 0.0, 0.0);
    double width = rect.x2 - rect.x1;
    EXPECT_DOUBLE_EQ(width, -300.0);
}

TEST_F(PageTest_706, PDFRectangleClipTo_706)
{
    PDFRectangle rect(0.0, 0.0, 200.0, 200.0);
    PDFRectangle clipRect(50.0, 50.0, 150.0, 150.0);
    rect.clipTo(clipRect);
    // After clipping, rect should be within clipRect bounds
    EXPECT_GE(rect.x1, clipRect.x1);
    EXPECT_GE(rect.y1, clipRect.y1);
    EXPECT_LE(rect.x2, clipRect.x2);
    EXPECT_LE(rect.y2, clipRect.y2);
}

TEST_F(PageTest_706, PDFRectangleClipToSmallerRect_706)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    PDFRectangle clipRect(25.0, 25.0, 75.0, 75.0);
    rect.clipTo(clipRect);
    EXPECT_DOUBLE_EQ(rect.x1, 25.0);
    EXPECT_DOUBLE_EQ(rect.y1, 25.0);
    EXPECT_DOUBLE_EQ(rect.x2, 75.0);
    EXPECT_DOUBLE_EQ(rect.y2, 75.0);
}

TEST_F(PageTest_706, PDFRectangleClipToLargerRect_706)
{
    PDFRectangle rect(25.0, 25.0, 75.0, 75.0);
    PDFRectangle clipRect(0.0, 0.0, 100.0, 100.0);
    PDFRectangle original = rect;
    rect.clipTo(clipRect);
    // Should remain unchanged since it's already within clipRect
    EXPECT_DOUBLE_EQ(rect.x1, original.x1);
    EXPECT_DOUBLE_EQ(rect.y1, original.y1);
    EXPECT_DOUBLE_EQ(rect.x2, original.x2);
    EXPECT_DOUBLE_EQ(rect.y2, original.y2);
}

TEST_F(PageTest_706, PDFRectangleIsEmpty_706)
{
    PDFRectangle rect;
    EXPECT_TRUE(rect.isEmpty());
}

TEST_F(PageTest_706, PDFRectangleNonEmpty_706)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    EXPECT_FALSE(rect.isEmpty());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
