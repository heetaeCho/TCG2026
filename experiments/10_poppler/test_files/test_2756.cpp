#include <gtest/gtest.h>

#include "PDFRectangle.h"



class PDFRectangleTest_2756 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(PDFRectangleTest_2756, ConstructorWithValuesSetsCoordinates_2756) {

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_EQ(rect.x1, 1.0);

    EXPECT_EQ(rect.y1, 2.0);

    EXPECT_EQ(rect.x2, 3.0);

    EXPECT_EQ(rect.y2, 4.0);

}



TEST_F(PDFRectangleTest_2756, DefaultConstructorInitializesZeroCoordinates_2756) {

    PDFRectangle rect;

    EXPECT_EQ(rect.x1, 0.0);

    EXPECT_EQ(rect.y1, 0.0);

    EXPECT_EQ(rect.x2, 0.0);

    EXPECT_EQ(rect.y2, 0.0);

}



TEST_F(PDFRectangleTest_2756, IsValidReturnsTrueForValidRectangle_2756) {

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(rect.isValid());

}



TEST_F(PDFRectangleTest_2756, IsValidReturnsFalseForInvalidRectangle_2756) {

    PDFRectangle rect(3.0, 4.0, 1.0, 2.0); // x2 < x1 and y2 < y1

    EXPECT_FALSE(rect.isValid());

}



TEST_F(PDFRectangleTest_2756, IsEmptyReturnsTrueForZeroAreaRectangle_2756) {

    PDFRectangle rect(1.0, 2.0, 1.0, 2.0);

    EXPECT_TRUE(rect.isEmpty());

}



TEST_F(PDFRectangleTest_2756, IsEmptyReturnsFalseForNonZeroAreaRectangle_2756) {

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(rect.isEmpty());

}



TEST_F(PDFRectangleTest_2756, ContainsPointInsideRectangle_2756) {

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(rect.contains(2.0, 3.0));

}



TEST_F(PDFRectangleTest_2756, ContainsPointOutsideRectangle_2756) {

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(rect.contains(0.0, 0.0));

}



TEST_F(PDFRectangleTest_2756, ContainsPointOnBoundary_2756) {

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(rect.contains(1.0, 2.0)); // Bottom-left corner

    EXPECT_TRUE(rect.contains(3.0, 4.0)); // Top-right corner

}



TEST_F(PDFRectangleTest_2756, EqualityOperatorForEqualRectangles_2756) {

    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);

    PDFRectangle rect2(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(rect1 == rect2);

}



TEST_F(PDFRectangleTest_2756, EqualityOperatorForDifferentRectangles_2756) {

    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);

    PDFRectangle rect2(2.0, 3.0, 4.0, 5.0);

    EXPECT_FALSE(rect1 == rect2);

}



TEST_F(PDFRectangleTest_2756, ClipToWithIntersectingRectangles_2756) {

    PDFRectangle rect(1.0, 1.0, 4.0, 4.0);

    PDFRectangle clipRect(2.0, 2.0, 3.0, 3.0);

    rect.clipTo(clipRect);

    EXPECT_EQ(rect.x1, 2.0);

    EXPECT_EQ(rect.y1, 2.0);

    EXPECT_EQ(rect.x2, 3.0);

    EXPECT_EQ(rect.y2, 3.0);

}



TEST_F(PDFRectangleTest_2756, ClipToWithNonIntersectingRectangles_2756) {

    PDFRectangle rect(1.0, 1.0, 2.0, 2.0);

    PDFRectangle clipRect(3.0, 3.0, 4.0, 4.0);

    rect.clipTo(clipRect);

    EXPECT_TRUE(rect.isEmpty());

}



TEST_F(PDFRectangleTest_2756, ClipToWithCompletelyInsideRectangles_2756) {

    PDFRectangle rect(1.0, 1.0, 3.0, 3.0);

    PDFRectangle clipRect(2.0, 2.0, 4.0, 4.0);

    rect.clipTo(clipRect);

    EXPECT_EQ(rect.x1, 2.0);

    EXPECT_EQ(rect.y1, 2.0);

    EXPECT_EQ(rect.x2, 3.0);

    EXPECT_EQ(rect.y2, 3.0);

}



TEST_F(PDFRectangleTest_2756, ClipToWithCompletelyOutsideRectangles_2756) {

    PDFRectangle rect(1.0, 1.0, 2.0, 2.0);

    PDFRectangle clipRect(3.0, 3.0, 4.0, 4.0);

    rect.clipTo(clipRect);

    EXPECT_TRUE(rect.isEmpty());

}
