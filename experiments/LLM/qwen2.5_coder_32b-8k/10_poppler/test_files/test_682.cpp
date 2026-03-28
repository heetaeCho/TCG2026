#include <gtest/gtest.h>

#include "PDFRectangle.h"



class PDFRectangleTest_682 : public ::testing::Test {

protected:

    PDFRectangle rect;

};



TEST_F(PDFRectangleTest_682, DefaultConstructorInitializesZero_682) {

    EXPECT_EQ(rect.x1, 0.);

    EXPECT_EQ(rect.y1, 0.);

    EXPECT_EQ(rect.x2, 0.);

    EXPECT_EQ(rect.y2, 0.);

}



TEST_F(PDFRectangleTest_682, ParameterizedConstructorSetsValues_682) {

    PDFRectangle rect(1.5, 2.5, 3.5, 4.5);

    EXPECT_EQ(rect.x1, 1.5);

    EXPECT_EQ(rect.y1, 2.5);

    EXPECT_EQ(rect.x2, 3.5);

    EXPECT_EQ(rect.y2, 4.5);

}



TEST_F(PDFRectangleTest_682, IsValidReturnsTrueForNonZero_682) {

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(rect.isValid());

}



TEST_F(PDFRectangleTest_682, IsValidReturnsFalseForZero_682) {

    PDFRectangle rect(0., 0., 0., 0.);

    EXPECT_FALSE(rect.isValid());

}



TEST_F(PDFRectangleTest_682, IsEmptyReturnsTrueForEqualCoordinates_682) {

    PDFRectangle rect(1.5, 1.5, 1.5, 1.5);

    EXPECT_TRUE(rect.isEmpty());

}



TEST_F(PDFRectangleTest_682, IsEmptyReturnsFalseForDifferentCoordinates_682) {

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(rect.isEmpty());

}



TEST_F(PDFRectangleTest_682, ContainsPointInsideRectangle_682) {

    PDFRectangle rect(1.0, 1.0, 5.0, 5.0);

    EXPECT_TRUE(rect.contains(3.0, 3.0));

}



TEST_F(PDFRectangleTest_682, ContainsPointOutsideRectangle_682) {

    PDFRectangle rect(1.0, 1.0, 5.0, 5.0);

    EXPECT_FALSE(rect.contains(6.0, 6.0));

}



TEST_F(PDFRectangleTest_682, ContainsPointOnBoundary_682) {

    PDFRectangle rect(1.0, 1.0, 5.0, 5.0);

    EXPECT_TRUE(rect.contains(1.0, 1.0)); // Bottom-left corner

    EXPECT_TRUE(rect.contains(5.0, 5.0)); // Top-right corner

}



TEST_F(PDFRectangleTest_682, ClipToReducesArea_682) {

    PDFRectangle rect(1.0, 1.0, 5.0, 5.0);

    PDFRectangle clipRect(2.0, 2.0, 4.0, 4.0);

    rect.clipTo(clipRect);

    EXPECT_EQ(rect.x1, 2.0);

    EXPECT_EQ(rect.y1, 2.0);

    EXPECT_EQ(rect.x2, 4.0);

    EXPECT_EQ(rect.y2, 4.0);

}



TEST_F(PDFRectangleTest_682, ClipToWithNoOverlapResultsInEmpty_682) {

    PDFRectangle rect(1.0, 1.0, 2.0, 2.0);

    PDFRectangle clipRect(3.0, 3.0, 4.0, 4.0);

    rect.clipTo(clipRect);

    EXPECT_TRUE(rect.isEmpty());

}



TEST_F(PDFRectangleTest_682, EqualityOperatorIdenticalRectangles_682) {

    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);

    PDFRectangle rect2(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(rect1 == rect2);

}



TEST_F(PDFRectangleTest_682, EqualityOperatorDifferentRectangles_682) {

    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);

    PDFRectangle rect2(5.0, 6.0, 7.0, 8.0);

    EXPECT_FALSE(rect1 == rect2);

}
