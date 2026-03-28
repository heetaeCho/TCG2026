#include <gtest/gtest.h>

#include "PDFRectangle.h"



class PDFRectangleTest_683 : public ::testing::Test {

protected:

    PDFRectangle rect;

    PDFRectangle rect1234;



    void SetUp() override {

        rect = PDFRectangle();

        rect1234 = PDFRectangle(1, 2, 3, 4);

    }

};



TEST_F(PDFRectangleTest_683, DefaultConstructorInitializesToZero_683) {

    EXPECT_EQ(rect.x1, 0.);

    EXPECT_EQ(rect.y1, 0.);

    EXPECT_EQ(rect.x2, 0.);

    EXPECT_EQ(rect.y2, 0.);

}



TEST_F(PDFRectangleTest_683, ParameterizedConstructorSetsCoordinates_683) {

    EXPECT_EQ(rect1234.x1, 1.);

    EXPECT_EQ(rect1234.y1, 2.);

    EXPECT_EQ(rect1234.x2, 3.);

    EXPECT_EQ(rect1234.y2, 4.);

}



TEST_F(PDFRectangleTest_683, ContainsReturnsTrueForPointInside_683) {

    EXPECT_TRUE(rect1234.contains(2, 3));

}



TEST_F(PDFRectangleTest_683, ContainsReturnsFalseForPointOutside_683) {

    EXPECT_FALSE(rect1234.contains(0, 0));

}



TEST_F(PDFRectangleTest_683, ContainsReturnsTrueForBoundaryPoints_683) {

    EXPECT_TRUE(rect1234.contains(1, 2));

    EXPECT_TRUE(rect1234.contains(3, 4));

    EXPECT_TRUE(rect1234.contains(1, 4));

    EXPECT_TRUE(rect1234.contains(3, 2));

}



TEST_F(PDFRectangleTest_683, IsValidReturnsTrueForValidRectangles_683) {

    EXPECT_TRUE(rect1234.isValid());

}



TEST_F(PDFRectangleTest_683, IsValidReturnsFalseForInvalidRectangles_683) {

    PDFRectangle invalidRect(3, 4, 1, 2);

    EXPECT_FALSE(invalidRect.isValid());

}



TEST_F(PDFRectangleTest_683, IsEmptyReturnsTrueForZeroSizedRectangles_683) {

    EXPECT_TRUE(rect.isEmpty());

}



TEST_F(PDFRectangleTest_683, IsEmptyReturnsFalseForNonZeroSizedRectangles_683) {

    EXPECT_FALSE(rect1234.isEmpty());

}



TEST_F(PDFRectangleTest_683, ClipToAdjustsRectangleToFitAnother_683) {

    PDFRectangle clipRect(0.5, 2.5, 3.5, 3.5);

    rect1234.clipTo(clipRect);

    EXPECT_EQ(rect1234.x1, 1.);

    EXPECT_EQ(rect1234.y1, 2.5);

    EXPECT_EQ(rect1234.x2, 3.5);

    EXPECT_EQ(rect1234.y2, 3.5);

}



TEST_F(PDFRectangleTest_683, EqualityOperatorReturnsTrueForEqualRectangles_683) {

    PDFRectangle rectCopy(1, 2, 3, 4);

    EXPECT_TRUE(rect1234 == rectCopy);

}



TEST_F(PDFRectangleTest_683, EqualityOperatorReturnsFalseForDifferentRectangles_683) {

    PDFRectangle differentRect(0, 0, 5, 5);

    EXPECT_FALSE(rect1234 == differentRect);

}
