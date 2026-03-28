#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Form.h"
#include "./TestProjects/poppler/poppler/PDFRectangle.h"

class CalculateDxDyTest_1514 : public ::testing::Test {
protected:
    // Helper function to create the PDFRectangle
    PDFRectangle createRectangle(double x1, double y1, double x2, double y2) {
        return PDFRectangle(x1, y1, x2, y2);
    }
};

TEST_F(CalculateDxDyTest_1514, CalculateDxDyRotation0_1514) {
    PDFRectangle rect = createRectangle(0.0, 0.0, 5.0, 10.0);
    auto [dx, dy] = calculateDxDy(0, &rect);
    
    EXPECT_DOUBLE_EQ(dx, 5.0);
    EXPECT_DOUBLE_EQ(dy, 10.0);
}

TEST_F(CalculateDxDyTest_1514, CalculateDxDyRotation90_1514) {
    PDFRectangle rect = createRectangle(0.0, 0.0, 5.0, 10.0);
    auto [dx, dy] = calculateDxDy(90, &rect);
    
    EXPECT_DOUBLE_EQ(dx, 10.0);
    EXPECT_DOUBLE_EQ(dy, 5.0);
}

TEST_F(CalculateDxDyTest_1514, CalculateDxDyRotation180_1514) {
    PDFRectangle rect = createRectangle(0.0, 0.0, 5.0, 10.0);
    auto [dx, dy] = calculateDxDy(180, &rect);
    
    EXPECT_DOUBLE_EQ(dx, 10.0);
    EXPECT_DOUBLE_EQ(dy, 5.0);
}

TEST_F(CalculateDxDyTest_1514, CalculateDxDyRotation270_1514) {
    PDFRectangle rect = createRectangle(0.0, 0.0, 5.0, 10.0);
    auto [dx, dy] = calculateDxDy(270, &rect);
    
    EXPECT_DOUBLE_EQ(dx, 10.0);
    EXPECT_DOUBLE_EQ(dy, 5.0);
}

TEST_F(CalculateDxDyTest_1514, CalculateDxDyInvalidRotation_1514) {
    PDFRectangle rect = createRectangle(0.0, 0.0, 5.0, 10.0);
    auto [dx, dy] = calculateDxDy(45, &rect);  // Invalid rotation (not 0, 90, 180, 270)
    
    // Assuming the default case (rot == 0)
    EXPECT_DOUBLE_EQ(dx, 5.0);
    EXPECT_DOUBLE_EQ(dy, 10.0);
}

TEST_F(CalculateDxDyTest_1514, CalculateDxDyZeroAreaRectangle_1514) {
    PDFRectangle rect = createRectangle(0.0, 0.0, 0.0, 0.0);
    auto [dx, dy] = calculateDxDy(0, &rect);
    
    EXPECT_DOUBLE_EQ(dx, 0.0);
    EXPECT_DOUBLE_EQ(dy, 0.0);
}