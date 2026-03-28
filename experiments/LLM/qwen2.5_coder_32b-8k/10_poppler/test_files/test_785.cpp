#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"



// Mock class for PDFDoc if needed (Not required in this case as no external collaborators are involved)



class AnnotTest_785 : public ::testing::Test {

protected:

    Annot* annot;



    virtual void SetUp() {

        // Assuming a constructor that initializes the page number to 0 or any valid default

        PDFDoc* docA = nullptr; // Placeholder, actual usage would require a valid PDFDoc instance

        PDFRectangle rectA(0, 0, 100, 100);

        annot = new Annot(docA, &rectA);

    }



    virtual void TearDown() {

        delete annot;

    }

};



TEST_F(AnnotTest_785, GetPageNum_DefaultValue_785) {

    EXPECT_EQ(annot->getPageNum(), 0); // Assuming default page number is set to 0

}



TEST_F(AnnotTest_785, GetPageNum_SetValue_785) {

    int testPageNumber = 5;

    annot->setPage(testPageNumber, true);

    EXPECT_EQ(annot->getPageNum(), testPageNumber);

}



// Assuming there are boundary conditions for getPageNum, like minimum and maximum page numbers

TEST_F(AnnotTest_785, GetPageNum_MinValue_785) {

    int minPageNumber = 0;

    annot->setPage(minPageNumber, true);

    EXPECT_EQ(annot->getPageNum(), minPageNumber);

}



// Assuming a reasonable upper limit for page numbers

TEST_F(AnnotTest_785, GetPageNum_MaxValue_785) {

    int maxPageNumber = 1000; // Arbitrary large number representing max pages in a document

    annot->setPage(maxPageNumber, true);

    EXPECT_EQ(annot->getPageNum(), maxPageNumber);

}



TEST_F(AnnotTest_785, GetRect_DefaultValue_785) {

    double x1, y1, x2, y2;

    annot->getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 0.0);

    EXPECT_DOUBLE_EQ(y1, 0.0);

    EXPECT_DOUBLE_EQ(x2, 100.0);

    EXPECT_DOUBLE_EQ(y2, 100.0);

}



TEST_F(AnnotTest_785, GetRect_SetValue_785) {

    double newX1 = 10.0, newY1 = 20.0, newX2 = 30.0, newY2 = 40.0;

    annot->setRect(newX1, newY1, newX2, newY2);

    double x1, y1, x2, y2;

    annot->getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, newX1);

    EXPECT_DOUBLE_EQ(y1, newY1);

    EXPECT_DOUBLE_EQ(x2, newX2);

    EXPECT_DOUBLE_EQ(y2, newY2);

}



TEST_F(AnnotTest_785, InRect_ValidPointInside_785) {

    EXPECT_TRUE(annot->inRect(50.0, 50.0)); // Point inside the rectangle

}



TEST_F(AnnotTest_785, InRect_PointOutside_785) {

    EXPECT_FALSE(annot->inRect(150.0, 150.0)); // Point outside the rectangle

}
