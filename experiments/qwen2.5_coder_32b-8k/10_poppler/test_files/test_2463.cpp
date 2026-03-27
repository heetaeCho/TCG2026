#include <gtest/gtest.h>

#include "./TestProjects/poppler/glib/poppler-page.h"

#include "./TestProjects/poppler/poppler/PDFRectangle.h"



class PopplerRectangleTest_2463 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(PopplerRectangleTest_2463, NormalOperation_2463) {

    PDFRectangle pdfRect(1.0, 2.0, 3.0, 4.0);

    PopplerRectangle* popplerRect = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);



    EXPECT_EQ(popplerRect->x1, 1.0);

    EXPECT_EQ(popplerRect->y1, 2.0);

    EXPECT_EQ(popplerRect->x2, 3.0);

    EXPECT_EQ(popplerRect->y2, 4.0);

}



TEST_F(PopplerRectangleTest_2463, BoundaryConditionsZero_2463) {

    PDFRectangle pdfRect(0.0, 0.0, 0.0, 0.0);

    PopplerRectangle* popplerRect = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);



    EXPECT_EQ(popplerRect->x1, 0.0);

    EXPECT_EQ(popplerRect->y1, 0.0);

    EXPECT_EQ(popplerRect->x2, 0.0);

    EXPECT_EQ(popplerRect->y2, 0.0);

}



TEST_F(PopplerRectangleTest_2463, BoundaryConditionsNegative_2463) {

    PDFRectangle pdfRect(-1.0, -2.0, -3.0, -4.0);

    PopplerRectangle* popplerRect = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);



    EXPECT_EQ(popplerRect->x1, -1.0);

    EXPECT_EQ(popplerRect->y1, -2.0);

    EXPECT_EQ(popplerRect->x2, -3.0);

    EXPECT_EQ(popplerRect->y2, -4.0);

}



TEST_F(PopplerRectangleTest_2463, BoundaryConditionsLargeNumbers_2463) {

    PDFRectangle pdfRect(1e9, 2e9, 3e9, 4e9);

    PopplerRectangle* popplerRect = poppler_rectangle_new_from_pdf_rectangle(&pdfRect);



    EXPECT_EQ(popplerRect->x1, 1e9);

    EXPECT_EQ(popplerRect->y1, 2e9);

    EXPECT_EQ(popplerRect->x2, 3e9);

    EXPECT_EQ(popplerRect->y2, 4e9);

}
