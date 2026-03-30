#include <gtest/gtest.h>

#include "Annot.h"



class AnnotTest_783 : public ::testing::Test {

protected:

    PDFRectangle rect;

    Annot annot = Annot(nullptr, &rect);



    void SetUp() override {

        // Initialize the rectangle with some values

        rect.x1 = 0.0;

        rect.y1 = 0.0;

        rect.x2 = 10.0;

        rect.y2 = 10.0;

    }

};



TEST_F(AnnotTest_783, GetRect_ReturnsInitializedRectangle_783) {

    const PDFRectangle &returnedRect = annot.getRect();

    EXPECT_EQ(returnedRect.x1, rect.x1);

    EXPECT_EQ(returnedRect.y1, rect.y1);

    EXPECT_EQ(returnedRect.x2, rect.x2);

    EXPECT_EQ(returnedRect.y2, rect.y2);

}



TEST_F(AnnotTest_783, GetRect_BoundaryConditionZeroArea_783) {

    // Set the rectangle to have zero area

    rect.x1 = 5.0;

    rect.y1 = 5.0;

    rect.x2 = 5.0;

    rect.y2 = 5.0;



    const PDFRectangle &returnedRect = annot.getRect();

    EXPECT_EQ(returnedRect.x1, rect.x1);

    EXPECT_EQ(returnedRect.y1, rect.y1);

    EXPECT_EQ(returnedRect.x2, rect.x2);

    EXPECT_EQ(returnedRect.y2, rect.y2);

}



TEST_F(AnnotTest_783, GetRect_BoundaryConditionNegativeCoordinates_783) {

    // Set the rectangle with negative coordinates

    rect.x1 = -5.0;

    rect.y1 = -5.0;

    rect.x2 = 5.0;

    rect.y2 = 5.0;



    const PDFRectangle &returnedRect = annot.getRect();

    EXPECT_EQ(returnedRect.x1, rect.x1);

    EXPECT_EQ(returnedRect.y1, rect.y1);

    EXPECT_EQ(returnedRect.x2, rect.x2);

    EXPECT_EQ(returnedRect.y2, rect.y2);

}
