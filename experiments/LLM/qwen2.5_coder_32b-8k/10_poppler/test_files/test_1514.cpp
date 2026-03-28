#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/Form.cc"

#include "./TestProjects/poppler/poppler/PDFRectangle.h"



class CalculateDxDyTest : public ::testing::Test {

protected:

    PDFRectangle rect;

};



TEST_F(CalculateDxDyTest_NormalOperation_1514, Rotation0_ReturnsCorrectDxDy_1514) {

    rect = PDFRectangle(1.0, 2.0, 3.0, 4.0);

    auto [dx, dy] = calculateDxDy(0, &rect);

    EXPECT_DOUBLE_EQ(dx, 2.0);

    EXPECT_DOUBLE_EQ(dy, 2.0);

}



TEST_F(CalculateDxDyTest_NormalOperation_1514, Rotation90_ReturnsCorrectDxDy_1514) {

    rect = PDFRectangle(1.0, 2.0, 3.0, 4.0);

    auto [dx, dy] = calculateDxDy(90, &rect);

    EXPECT_DOUBLE_EQ(dx, 2.0);

    EXPECT_DOUBLE_EQ(dy, 2.0);

}



TEST_F(CalculateDxDyTest_NormalOperation_1514, Rotation180_ReturnsCorrectDxDy_1514) {

    rect = PDFRectangle(1.0, 2.0, 3.0, 4.0);

    auto [dx, dy] = calculateDxDy(180, &rect);

    EXPECT_DOUBLE_EQ(dx, -1.0);

    EXPECT_DOUBLE_EQ(dy, 2.0);

}



TEST_F(CalculateDxDyTest_NormalOperation_1514, Rotation270_ReturnsCorrectDxDy_1514) {

    rect = PDFRectangle(1.0, 2.0, 3.0, 4.0);

    auto [dx, dy] = calculateDxDy(270, &rect);

    EXPECT_DOUBLE_EQ(dx, 2.0);

    EXPECT_DOUBLE_EQ(dy, 2.0);

}



TEST_F(CalculateDxDyTest_BoundaryConditions_1514, RotationNegative_ReturnsDefaultDxDy_1514) {

    rect = PDFRectangle(1.0, 2.0, 3.0, 4.0);

    auto [dx, dy] = calculateDxDy(-90, &rect);

    EXPECT_DOUBLE_EQ(dx, 2.0);

    EXPECT_DOUBLE_EQ(dy, 2.0);

}



TEST_F(CalculateDxDyTest_BoundaryConditions_1514, Rotation360_ReturnsDefaultDxDy_1514) {

    rect = PDFRectangle(1.0, 2.0, 3.0, 4.0);

    auto [dx, dy] = calculateDxDy(360, &rect);

    EXPECT_DOUBLE_EQ(dx, 2.0);

    EXPECT_DOUBLE_EQ(dy, 2.0);

}



TEST_F(CalculateDxDyTest_BoundaryConditions_1514, RectangleZeroArea_ReturnsZeroDxDy_1514) {

    rect = PDFRectangle(1.0, 2.0, 1.0, 2.0);

    auto [dx, dy] = calculateDxDy(0, &rect);

    EXPECT_DOUBLE_EQ(dx, 0.0);

    EXPECT_DOUBLE_EQ(dy, 0.0);

}



TEST_F(CalculateDxDyTest_ExceptionalCases_1514, RectangleInvalid_ReturnsDefaultDxDy_1514) {

    rect = PDFRectangle(3.0, 2.0, 1.0, 4.0); // Invalid rectangle where x2 < x1

    auto [dx, dy] = calculateDxDy(0, &rect);

    EXPECT_DOUBLE_EQ(dx, -2.0);

    EXPECT_DOUBLE_EQ(dy, 2.0);

}
