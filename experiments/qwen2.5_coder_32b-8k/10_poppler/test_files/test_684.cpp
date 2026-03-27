#include <gtest/gtest.h>

#include "PDFRectangle.h"



class PDFRectangleTest_684 : public ::testing::Test {

protected:

    PDFRectangle rect;

};



TEST_F(PDFRectangleTest_684, DefaultConstructorInitializesZero_684) {

    EXPECT_EQ(rect.x1, 0.);

    EXPECT_EQ(rect.y1, 0.);

    EXPECT_EQ(rect.x2, 0.);

    EXPECT_EQ(rect.y2, 0.);

}



TEST_F(PDFRectangleTest_684, ParameterizedConstructorSetsValues_684) {

    PDFRectangle rect(1.5, 2.5, 3.5, 4.5);

    EXPECT_EQ(rect.x1, 1.5);

    EXPECT_EQ(rect.y1, 2.5);

    EXPECT_EQ(rect.x2, 3.5);

    EXPECT_EQ(rect.y2, 4.5);

}



TEST_F(PDFRectangleTest_684, EqualityOperatorReturnsTrueForSameValues_684) {

    PDFRectangle rect1(1., 2., 3., 4.);

    PDFRectangle rect2(1., 2., 3., 4.);

    EXPECT_TRUE(rect1 == rect2);

}



TEST_F(PDFRectangleTest_684, EqualityOperatorReturnsFalseForDifferentValues_684) {

    PDFRectangle rect1(1., 2., 3., 4.);

    PDFRectangle rect2(5., 6., 7., 8.);

    EXPECT_FALSE(rect1 == rect2);

}



TEST_F(PDFRectangleTest_684, IsValidReturnsTrueForValidRectangles_684) {

    PDFRectangle rect1(1., 2., 3., 4.);

    PDFRectangle rect2(-1., -2., 1., 1.);

    EXPECT_TRUE(rect1.isValid());

    EXPECT_TRUE(rect2.isValid());

}



TEST_F(PDFRectangleTest_684, IsValidReturnsFalseForInvalidRectangles_684) {

    PDFRectangle rect1(3., 4., 1., 2.); // x2 < x1

    PDFRectangle rect2(1., 4., 2., 1.); // y2 < y1

    EXPECT_FALSE(rect1.isValid());

    EXPECT_FALSE(rect2.isValid());

}



TEST_F(PDFRectangleTest_684, IsEmptyReturnsTrueForZeroAreaRectangles_684) {

    PDFRectangle rect1(0., 0., 0., 0.);

    PDFRectangle rect2(1., 2., 1., 2.); // width or height is zero

    EXPECT_TRUE(rect1.isEmpty());

    EXPECT_TRUE(rect2.isEmpty());

}



TEST_F(PDFRectangleTest_684, IsEmptyReturnsFalseForNonZeroAreaRectangles_684) {

    PDFRectangle rect(1., 2., 3., 4.);

    EXPECT_FALSE(rect.isEmpty());

}



TEST_F(PDFRectangleTest_684, ContainsReturnsTrueForPointsInside_684) {

    PDFRectangle rect(1., 2., 3., 4.);

    EXPECT_TRUE(rect.contains(2., 3.));

}



TEST_F(PDFRectangleTest_684, ContainsReturnsFalseForPointsOutside_684) {

    PDFRectangle rect(1., 2., 3., 4.);

    EXPECT_FALSE(rect.contains(0., 3.));

    EXPECT_FALSE(rect.contains(2., 5.));

    EXPECT_FALSE(rect.contains(4., 3.));

    EXPECT_FALSE(rect.contains(2., 1.));

}



TEST_F(PDFRectangleTest_684, ContainsReturnsTrueForPointsOnBoundary_684) {

    PDFRectangle rect(1., 2., 3., 4.);

    EXPECT_TRUE(rect.contains(1., 2.)); // bottom-left corner

    EXPECT_TRUE(rect.contains(3., 4.)); // top-right corner

    EXPECT_TRUE(rect.contains(1., 4.)); // top-left corner

    EXPECT_TRUE(rect.contains(3., 2.)); // bottom-right corner

}



TEST_F(PDFRectangleTest_684, ClipToUpdatesRectWithIntersection_684) {

    PDFRectangle rect(0., 0., 5., 5.);

    PDFRectangle clipper(1., 1., 4., 4.);

    rect.clipTo(clipper);

    EXPECT_EQ(rect.x1, 1.);

    EXPECT_EQ(rect.y1, 1.);

    EXPECT_EQ(rect.x2, 4.);

    EXPECT_EQ(rect.y2, 4.);

}



TEST_F(PDFRectangleTest_684, ClipToUpdateRectWithNoIntersection_684) {

    PDFRectangle rect(0., 0., 5., 5.);

    PDFRectangle clipper(10., 10., 15., 15.);

    rect.clipTo(clipper);

    EXPECT_TRUE(rect.isEmpty());

}



TEST_F(PDFRectangleTest_684, ClipToUpdateRectWithPartialIntersection_684) {

    PDFRectangle rect(0., 0., 3., 3.);

    PDFRectangle clipper(2., 2., 5., 5.);

    rect.clipTo(clipper);

    EXPECT_EQ(rect.x1, 2.);

    EXPECT_EQ(rect.y1, 2.);

    EXPECT_EQ(rect.x2, 3.);

    EXPECT_EQ(rect.y2, 3.);

}
